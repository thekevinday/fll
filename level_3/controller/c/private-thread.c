#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-controller_print.h"
#include "private-lock.h"
#include "private-lock_print.h"
#include "private-rule.h"
#include "private-thread.h"
#include "private-thread_control.h"
#include "private-thread_entry.h"
#include "private-thread_process.h"
#include "private-thread_rule.h"
#include "private-thread_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_cleanup_
  void * controller_thread_cleanup(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    const controller_global_t *global = (controller_global_t *) arguments;

    if (global->thread->enabled != controller_thread_enabled) return 0;

    const struct timespec delay = controller_time_seconds(global->main->parameters[controller_parameter_simulate].result == f_console_result_found ? controller_thread_cleanup_interval_short_d : controller_thread_cleanup_interval_long_d);

    f_status_t status = F_none;

    while (global->thread->enabled == controller_thread_enabled) {

      controller_time_sleep_nanoseconds(global->main, global->setting, delay);

      if (global->thread->enabled != controller_thread_enabled) break;

      if (f_thread_lock_write_try(&global->thread->lock.process) == F_none) {
        controller_process_t *process = 0;

        f_array_length_t i = 0;

        for (; i < global->thread->processs.size && global->thread->enabled == controller_thread_enabled; ++i) {

          if (!global->thread->processs.array[i]) continue;

          process = global->thread->processs.array[i];

          // if "active" has a read lock, then do not attempt to clean it.
          if (f_thread_lock_write_try(&process->active) != F_none) {
            continue;
          }

          // if "lock" has a read or write lock, then do not attempt to clean it.
          if (f_thread_lock_write_try(&process->lock) != F_none) {
            f_thread_unlock(&process->active);

            continue;
          }

          // if process is active or busy, then do not attempt to clean it.
          if (process->state == controller_process_state_active || process->state == controller_process_state_busy) {
            f_thread_unlock(&process->active);
            f_thread_unlock(&process->lock);

            continue;
          }

          // if process has a PID file, then it is running in the background, only cleanup if the PID file no longer exists.
          if (process->path_pids.used) {
            f_array_length_t j = 0;

            for (; j < process->path_pids.used; ++j) {

              if (process->path_pids.array[j].used && f_file_exists(process->path_pids.array[j].string) == F_true) {
                break;
              }
            } // for

            if (j < process->path_pids.used) {
              f_thread_unlock(&process->active);
              f_thread_unlock(&process->lock);

              continue;
            }
          }

          f_thread_unlock(&process->lock);

          // close any still open thread.
          if (process->id_thread) {
            status = f_thread_join(process->id_thread, 0);

            if (F_status_is_error_not(status) || F_status_set_fine(status) == F_found_not) {
              status = f_thread_lock_write(&process->lock);

              if (F_status_is_error(status)) {
                controller_lock_print_error_critical(global->main->error, F_status_set_fine(status), F_false, global->thread);

                f_thread_unlock(&process->active);
                continue;
              }

              process->state = controller_process_state_idle;
              process->id_thread = 0;

              f_thread_mutex_lock(&process->wait_lock);
              f_thread_condition_signal_all(&process->wait);
              f_thread_mutex_unlock(&process->wait_lock);

              f_thread_unlock(&process->lock);
            }
            else {
              f_thread_unlock(&process->active);

              continue;
            }
          }

          // deallocate dynamic portions of the structure that are only ever needed while the process is running.
          controller_cache_delete_simple(&process->cache);
          f_type_array_lengths_resize(0, &process->stack);

          // shrink the childs array.
          if (process->childs.used) {
            for (; process->childs.used; --process->childs.used) {
              if (process->childs.array[process->childs.used]) break;
            } // for

            if (process->childs.used < process->childs.size) {
              controller_pids_resize(process->childs.used, &process->childs);
            }
          }

          // deallocate the PID files.
          if (process->path_pids.used) {
            process->path_pids.used = 0;
            f_string_dynamics_resize(0, &process->path_pids);
          }

          // deallocate any rules in the space that is declared to be unused.
          if (i >= global->thread->processs.used) {
            controller_rule_delete_simple(&process->rule);
          }

          f_thread_unlock(&process->active);
        } // for

        f_thread_unlock(&global->thread->lock.process);
      }
    } // while

    return 0;
  }
#endif // _di_controller_thread_cleanup_

#ifndef _di_controller_thread_is_enabled_
  f_status_t controller_thread_is_enabled(const bool is_normal, controller_thread_t *thread) {

    if (is_normal) {
      return thread->enabled == controller_thread_enabled;
    }

    return thread->enabled;
  }
#endif // _di_controller_thread_is_enabled_

#ifndef _di_controller_thread_is_enabled_process_
  f_status_t controller_thread_is_enabled_process(controller_process_t * const process, controller_thread_t *thread) {

    return controller_thread_is_enabled_process_type(process->type, thread);
  }
#endif // _di_controller_thread_is_enabled_process_

#ifndef _di_controller_thread_is_enabled_process_type_
  f_status_t controller_thread_is_enabled_process_type(const uint8_t type, controller_thread_t *thread) {

    return controller_thread_is_enabled(type != controller_process_type_exit, thread);
  }
#endif // _di_controller_thread_is_enabled_process_type_

#ifndef _di_controller_thread_main_
  f_status_t controller_thread_main(controller_main_t *main, controller_setting_t *setting) {

    f_status_t status = F_none;

    controller_thread_t thread = controller_thread_t_initialize;
    controller_global_t global = macro_controller_global_t_initialize(main, setting, &thread);

    // the global locks must be initialized, but only once, so initialize immediately upon allocation.
    status = controller_lock_create(&thread.lock);

    if (F_status_is_error(status)) {
      if (main->error.verbosity != f_console_verbosity_quiet) {
        fll_error_print(main->error, status, "controller_lock_create", F_true);
      }
    }
    else {
      status = controller_processs_increase(&thread.processs);

      if (F_status_is_error(status)) {
        controller_print_error(main->error, F_status_set_fine(status), "controller_processs_increase", F_true, &thread);
      }
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_create(0, &thread.id_signal, &controller_thread_signal_normal, (void *) &global);
    }

    if (F_status_is_error(status)) {
      thread.id_signal = 0;

      if (main->error.verbosity != f_console_verbosity_quiet) {
        controller_print_error(main->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
      }
    }
    else {
      if (main->parameters[controller_parameter_daemon].result == f_console_result_found) {
        setting->ready = controller_setting_ready_done;

        if (f_file_exists(setting->path_pid.string) == F_true) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            controller_lock_print(main->error.to, &thread);

            fl_print_format("%c%[%SThe pid file '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
            fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, setting->path_pid.string, main->error.notable);
            fl_print_format("%[' must not already exist.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            controller_unlock_print_flush(main->error.to, &thread);
          }

          setting->ready = controller_setting_ready_abort;
          status = F_status_set_error(F_available_not);
        }
      }
      else if (global.setting->name_entry.used) {
        const controller_main_entry_t entry = macro_controller_main_entry_t_initialize(&global, global.setting);

        status = f_thread_create(0, &thread.id_entry, &controller_thread_entry, (void *) &entry);

        if (F_status_is_error(status)) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            controller_print_error(main->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
          }
        }
        else {
          controller_thread_join(&thread.id_entry);

          status = thread.status;
          thread.id_entry = 0;
        }
      }
    }

    // only make the rule and control threads available once any/all pre-processing and are completed.
    if (F_status_is_error_not(status) && status != F_signal && status != F_failure && status != F_child && thread.enabled == controller_thread_enabled) {
      if (main->parameters[controller_parameter_validate].result == f_console_result_none) {

        // wait for the entry thread to complete before starting the rule thread.
        controller_thread_join(&thread.id_rule);

        if (thread.enabled && setting->mode == controller_setting_mode_service) {
          status = f_thread_create(0, &thread.id_rule, &controller_thread_rule, (void *) &global);

          if (F_status_is_error(status)) {
            thread.id_rule = 0;
          }
          else {
            status = f_thread_create(0, &thread.id_control, &controller_thread_control, (void *) &global);
          }

          if (F_status_is_error(status)) {
            thread.id_control = 0;
          }
          else {
            status = f_thread_create(0, &thread.id_cleanup, &controller_thread_cleanup, (void *) &global);
          }

          if (F_status_is_error(status)) {
            thread.id_cleanup = 0;

            if (main->error.verbosity != f_console_verbosity_quiet) {
              controller_print_error(main->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
            }
          }
        }
      }
    }

    if (status == F_child) {
      controller_thread_delete_simple(&thread);

      return F_child;
    }

    if (F_status_is_error_not(status) && status != F_signal && status != F_failure && main->parameters[controller_parameter_validate].result == f_console_result_none && controller_thread_is_enabled(F_true, &thread)) {

      if (setting->mode == controller_setting_mode_service) {
        controller_thread_join(&thread.id_signal);
      }
      else if (setting->mode == controller_setting_mode_program) {
        status = controller_rule_wait_all(F_true, global, F_false, 0);
      }
    }

    controller_thread_process_cancel(F_true, controller_thread_cancel_call, &global, 0);

    controller_thread_process_exit(&global);

    if (thread.id_signal) f_thread_join(thread.id_signal, 0);
    if (thread.id_cleanup) f_thread_join(thread.id_cleanup, 0);
    if (thread.id_control) f_thread_join(thread.id_control, 0);
    if (thread.id_entry) f_thread_join(thread.id_entry, 0);
    if (thread.id_rule) f_thread_join(thread.id_rule, 0);

    thread.id_cleanup = 0;
    thread.id_control = 0;
    thread.id_rule = 0;
    thread.id_signal = 0;

    controller_thread_delete_simple(&thread);

    if (F_status_is_error(status)) {
      return F_status_set_error(F_failure);
    }

    if (status == F_signal) {
      return F_signal;
    }

    return F_none;
  }
#endif // _di_controller_thread_main_

#ifndef _di_controller_thread_join_
  f_status_t controller_thread_join(f_thread_id_t *id) {

    if (!id || !*id) return F_data_not;

    const f_status_t status = f_thread_join(*id, 0);

    if (F_status_is_error_not(status) || F_status_set_fine(status) == F_found_not) {
      *id = 0;
    }

    return status;
  }
#endif // _di_controller_thread_join_

#ifdef __cplusplus
} // extern "C"
#endif
