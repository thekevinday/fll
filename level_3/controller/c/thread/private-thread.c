#include "../controller.h"
#include "../common/private-common.h"
#include "../controller/private-controller.h"
#include "../controller/private-controller_print.h"
#include "../lock/private-lock.h"
#include "../lock/private-lock_print.h"
#include "../rule/private-rule.h"
#include "../thread/private-thread.h"
#include "../thread/private-thread_control.h"
#include "../thread/private-thread_entry.h"
#include "../thread/private-thread_process.h"
#include "../thread/private-thread_rule.h"
#include "../thread/private-thread_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_cleanup_
  void * controller_thread_cleanup(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    const controller_global_t *global = (controller_global_t *) arguments;

    if (global->thread->enabled != controller_thread_enabled_e) return 0;

    const struct timespec delay = controller_time_seconds((global->main->parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) ? controller_thread_cleanup_interval_short_d : controller_thread_cleanup_interval_long_d);

    f_status_t status = F_none;

    while (global->thread->enabled == controller_thread_enabled_e) {

      nanosleep(&delay, 0);

      if (global->thread->enabled != controller_thread_enabled_e) break;

      if (f_thread_lock_write_try(&global->thread->lock.process) == F_none) {
        controller_process_t *process = 0;

        f_array_length_t i = 0;

        for (; i < global->thread->processs.size && global->thread->enabled == controller_thread_enabled_e; ++i) {

          if (!global->thread->processs.array[i]) continue;

          process = global->thread->processs.array[i];

          // If "active" has a read lock, then do not attempt to clean it.
          if (f_thread_lock_write_try(&process->active) != F_none) {
            continue;
          }

          // If "lock" has a read or write lock, then do not attempt to clean it.
          if (f_thread_lock_write_try(&process->lock) != F_none) {
            f_thread_unlock(&process->active);

            continue;
          }

          // If process is active or busy, then do not attempt to clean it.
          if (process->state == controller_process_state_active_e || process->state == controller_process_state_busy_e) {
            f_thread_unlock(&process->active);
            f_thread_unlock(&process->lock);

            continue;
          }

          // If process has a PID file, then it is running in the background, only cleanup if the PID file no longer exists.
          if (process->path_pids.used) {
            f_array_length_t j = 0;

            for (; j < process->path_pids.used; ++j) {

              if (process->path_pids.array[j].used && f_file_exists(process->path_pids.array[j], F_true) == F_true) {
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

          // Close any still open thread.
          if (process->id_thread) {
            status = f_thread_join(process->id_thread, 0);

            if (F_status_is_error_not(status) || F_status_set_fine(status) == F_found_not) {
              status = f_thread_lock_write(&process->lock);

              if (F_status_is_error(status)) {
                controller_lock_print_error_critical(global->main->error, F_status_set_fine(status), F_false, global->thread);

                f_thread_unlock(&process->active);
                continue;
              }

              process->state = controller_process_state_idle_e;
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

          // Deallocate dynamic portions of the structure that are only ever needed while the process is running.
          controller_cache_delete_simple(&process->cache);
          f_array_lengths_resize(0, &process->stack);

          // Shrink the childs array.
          if (process->childs.used) {
            for (; process->childs.used; --process->childs.used) {
              if (process->childs.array[process->childs.used]) break;
            } // for

            if (process->childs.used < process->childs.size) {
              controller_pids_resize(process->childs.used, &process->childs);
            }
          }

          // Deallocate the PID files.
          if (process->path_pids.used) {
            process->path_pids.used = 0;
            f_string_dynamics_resize(0, &process->path_pids);
          }

          // Deallocate any rules in the space that is declared to be unused.
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

#ifndef _di_controller_thread_detach_
  f_status_t controller_thread_detach(f_thread_id_t * const id) {

    if (!id || !*id) return F_data_not;

    const f_status_t status = f_thread_detach(*id);

    if (F_status_is_error_not(status) || F_status_set_fine(status) == F_found_not) {
      *id = 0;
    }

    return status;
  }
#endif // _di_controller_thread_detach_

#ifndef _di_controller_thread_is_enabled_
  f_status_t controller_thread_is_enabled(const bool is_normal, controller_thread_t * const thread) {

    if (is_normal) {
      return thread->enabled == controller_thread_enabled_e;
    }

    return thread->enabled;
  }
#endif // _di_controller_thread_is_enabled_

#ifndef _di_controller_thread_is_enabled_process_
  f_status_t controller_thread_is_enabled_process(controller_process_t * const process, controller_thread_t * const thread) {

    return controller_thread_is_enabled_process_type(process->type, thread);
  }
#endif // _di_controller_thread_is_enabled_process_

#ifndef _di_controller_thread_is_enabled_process_type_
  f_status_t controller_thread_is_enabled_process_type(const uint8_t type, controller_thread_t * const thread) {

    return controller_thread_is_enabled(type != controller_process_type_exit_e, thread);
  }
#endif // _di_controller_thread_is_enabled_process_type_

#ifndef _di_controller_thread_main_
  f_status_t controller_thread_main(controller_main_t * const main, controller_setting_t * const setting) {

    f_status_t status = F_none;

    controller_thread_t thread = controller_thread_t_initialize;
    controller_global_t global = macro_controller_global_t_initialize_1(main, setting, &thread);

    // The global locks must be initialized, but only once, so initialize immediately upon allocation.
    status = controller_lock_create(&thread.lock);

    if (F_status_is_error(status)) {
      if (main->error.verbosity > f_console_verbosity_quiet_e) {
        fll_error_print(main->error, status, "controller_lock_create", fll_error_file_flag_fallback_e);
      }
    }
    else {
      status = controller_processs_increase(&thread.processs);

      if (F_status_is_error(status)) {
        controller_print_error(&thread, main->error, F_status_set_fine(status), "controller_processs_increase", F_true);
      }
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_create(0, &thread.id_signal, &controller_thread_signal_normal, (void *) &global);
    }

    if (F_status_is_error(status)) {
      thread.id_signal = 0;

      if (main->error.verbosity > f_console_verbosity_quiet_e) {
        controller_print_error(&thread, main->error, F_status_set_fine(status), "f_thread_create", F_true);
      }
    }
    else {
      if (main->parameters.array[controller_parameter_daemon_e].result & f_console_result_found_e) {
        setting->ready = controller_setting_ready_done_e;

        if (f_file_exists(setting->path_pid, F_true) == F_true) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            controller_lock_print(main->error.to, &thread);

            fl_print_format("%r%[%QThe pid file '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%Q%]", main->error.to, main->error.notable, setting->path_pid, main->error.notable);
            fl_print_format("%[' must not already exist.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            controller_unlock_print_flush(main->error.to, &thread);
          }

          setting->ready = controller_setting_ready_abort_e;
          status = F_status_set_error(F_available_not);
        }
      }
      else if (global.setting->name_entry.used) {
        const controller_main_entry_t entry = macro_controller_main_entry_t_initialize_1(&global, global.setting);

        status = f_thread_create(0, &thread.id_entry, &controller_thread_entry, (void *) &entry);

        if (F_status_is_error(status)) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            controller_print_error(&thread, main->error, F_status_set_fine(status), "f_thread_create", F_true);
          }
        }
        else {
          controller_thread_join(&thread.id_entry);

          status = thread.status;
          thread.id_entry = 0;
        }
      }
    }

    // Only make the rule and control threads available once any/all pre-processing and are completed.
    if (F_status_is_error_not(status) && status != F_failure && status != F_child && thread.enabled == controller_thread_enabled_e) {
      if (!(main->parameters.array[controller_parameter_validate_e].result & f_console_result_found_e)) {

        // Wait for the entry thread to complete before starting the rule thread.
        controller_thread_join(&thread.id_rule);

        if (thread.enabled && setting->mode == controller_setting_mode_service_e) {
          status = f_thread_create(0, &thread.id_rule, &controller_thread_rule, (void *) &global);

          if (F_status_is_error(status)) {
            thread.id_rule = 0;
          }
          else {
            status = f_thread_create(0, &thread.id_cleanup, &controller_thread_cleanup, (void *) &global);
          }

          if (F_status_is_error(status)) {
            thread.id_cleanup = 0;

            if (main->error.verbosity > f_console_verbosity_quiet_e) {
              controller_print_error(&thread, main->error, F_status_set_fine(status), "f_thread_create", F_true);
            }
          }
        }
      }
    }

    if (status == F_child) {
      controller_thread_delete_simple(&thread);

      return F_child;
    }

    if (F_status_is_error_not(status) && status != F_failure && !(main->parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) && controller_thread_is_enabled(F_true, &thread)) {

      if (setting->mode == controller_setting_mode_service_e) {
        controller_thread_join(&thread.id_signal);
      }
      else if (setting->mode == controller_setting_mode_helper_e) {
        status = controller_rule_wait_all(global, F_true, F_false, 0);
      }
      else if (setting->mode == controller_setting_mode_program_e) {
        status = controller_rule_wait_all(global, F_true, F_false);
      }
    }

    controller_thread_process_cancel(global, F_true, controller_thread_cancel_call_e);

    controller_thread_process_exit(&global);

    if (thread.id_signal) f_thread_join(thread.id_signal, 0);
    if (thread.id_cleanup) f_thread_join(thread.id_cleanup, 0);
    if (thread.id_control) f_thread_join(thread.id_control, 0);
    if (thread.id_entry) f_thread_join(thread.id_entry, 0);
    if (thread.id_rule) f_thread_join(thread.id_rule, 0);

    thread.id_cleanup = 0;
    thread.id_control = 0;
    thread.id_entry = 0;
    thread.id_rule = 0;
    thread.id_signal = 0;

    controller_thread_delete_simple(&thread);

    if (F_status_is_error(status)) {
      return F_status_set_error(F_failure);
    }

    if (F_status_set_fine(status) == F_interrupt) {
      fll_program_print_signal_received(main->warning, thread.signal);

      if (main->output.verbosity != f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->output.to);
      }

      return F_status_set_error(F_interrupt);
    }

    return F_none;
  }
#endif // _di_controller_thread_main_

#ifndef _di_controller_thread_join_
  f_status_t controller_thread_join(f_thread_id_t * const id) {

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
