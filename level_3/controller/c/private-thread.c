#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-entry.h"
#include "private-rule.h"
#include "private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_cleanup_
  void * controller_thread_cleanup(void *arguments) {

    const controller_main_t *main = (controller_main_t *) arguments;

    if (!main->thread->enabled) f_thread_exit(0);

    const unsigned int interval = main->data->parameters[controller_parameter_test].result == f_console_result_found ? controller_thread_cleanup_interval_short : controller_thread_cleanup_interval_long;

    while (main->thread->enabled) {

      sleep(interval);

      if (main->thread->enabled && f_thread_lock_write_try(&main->thread->lock.process) == F_none) {
        controller_process_t *process = 0;

        f_array_length_t i = 0;

        for (; i < main->thread->processs.used && main->thread->enabled; ++i) {

          process = &main->thread->processs.array[i];

          if (f_thread_lock_write_try(&process->active) != F_none) {
            continue;
          }

          if (f_thread_lock_write_try(&process->lock) != F_none) {
            f_thread_unlock(&process->active);

            continue;
          }

          if (process->state == controller_process_state_active || process->state == controller_process_state_busy) {
            f_thread_unlock(&process->active);
            f_thread_unlock(&process->lock);

            continue;
          }

          if (process->id_thread) {
            f_thread_join(process->id_thread, 0);

            f_thread_lock_write(&process->lock);

            process->state = controller_process_state_idle;
            process->id_thread = 0;

            f_thread_unlock(&process->lock);
          }

          // deallocate dynamic portions of the structure that are only ever needed while the process is running.
          controller_cache_delete_simple(&process->cache);
          f_type_array_lengths_resize(0, &process->stack);

          f_thread_unlock(&process->active);
          f_thread_unlock(&process->lock);
        } // for

        if (main->thread->processs.used) {
          for (i = main->thread->processs.used - 1; main->thread->processs.used && main->thread->enabled; --i) {

            process = &main->thread->processs.array[i];

            if (f_thread_lock_write_try(&process->active) != F_none) {
              break;
            }

            if (f_thread_lock_write_try(&process->lock) != F_none) {
              f_thread_unlock(&process->active);

              break;
            }

            if (process->state == controller_process_state_active || process->state == controller_process_state_busy) {
              f_thread_unlock(&process->active);
              f_thread_unlock(&process->lock);

              break;
            }

            if (process->id_thread) {
              f_thread_join(process->id_thread, 0);

              f_thread_lock_write(&process->lock);

              process->state = controller_process_state_idle;
              process->id_thread = 0;

              f_thread_unlock(&process->lock);
            }

            // deallocate dynamic portions of the structure that are only ever needed while the rule is being processed.
            controller_cache_delete_simple(&process->cache);
            f_type_array_lengths_resize(0, &process->stack);

            --main->thread->processs.used;

            f_thread_unlock(&process->active);
            f_thread_unlock(&process->lock);
          } // for
        }

        f_thread_unlock(&main->thread->lock.process);
      }
    } // while

    f_thread_exit(0);
  }
#endif // _di_controller_thread_cleanup_

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void *arguments) {

    controller_main_t *main = (controller_main_t *) arguments;

    if (!main->thread->enabled) f_thread_exit(0);

    f_thread_exit(0);
  }
#endif // _di_controller_thread_control_

#ifndef _di_controller_thread_exit_force_
  void * controller_thread_exit_force(void *arguments) {

    controller_main_t *main = (controller_main_t *) arguments;

    f_thread_lock_read(&main->thread->lock.process);

    // @todo redesign this to use timed waits, that include a counter and a max wait such that when max wait is reached, send kill signals.
    //       this would, in theory, allow faster exits without as much waiting when there is nothing to wait for.

    if (main->thread->processs.used) {
      f_thread_unlock(&main->thread->lock.process);

      usleep(controller_thread_exit_process_force_timeout);

      f_thread_lock_read(&main->thread->lock.process);

      for (f_array_length_t i = 0; i < main->thread->processs.used; ++i) {

        if (main->thread->processs.array[i].child > 0) {
          f_signal_send(F_signal_kill, main->thread->processs.array[i].child);
        }

        if (main->thread->processs.array[i].id_thread) {
          f_thread_signal(main->thread->processs.array[i].id_thread, F_signal_kill);
        }
      } // for
    }

    f_thread_unlock(&main->thread->lock.process);

    usleep(controller_thread_exit_main_force_timeout);

    if (main->thread->id_cleanup) {
      f_thread_signal(main->thread->id_cleanup, F_signal_kill);
    }

    if (main->thread->id_control) {
      f_thread_signal(main->thread->id_control, F_signal_kill);
    }

    if (main->thread->id_rule) {
      f_thread_signal(main->thread->id_rule, F_signal_kill);
    }

    f_thread_exit(0);
  }
#endif // _di_controller_thread_exit_force_

#ifndef _di_controller_thread_main_
  f_status_t controller_thread_main(const f_string_static_t entry_name, controller_data_t *data, controller_setting_t *setting) {

    f_status_t status = F_none;

    controller_thread_t thread = controller_thread_t_initialize;
    controller_main_t main = controller_macro_main_t_initialize(data, setting, &thread);

    // the main locks must be initialized, but only once, so initialize immediately upon allocation.
    status = controller_lock_create(&thread.lock);

    if (F_status_is_error(status)) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fll_error_print(data->error, status, "controller_lock_create", F_true);
      }
    }
    else {
      status = controller_processs_increase(&thread.processs);

      if (F_status_is_error(status)) {
        controller_error_print(data->error, F_status_set_fine(status), "controller_processs_increase", F_true, &thread);
      }
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_create(0, &thread.id_signal, &controller_thread_signal, (void *) &main);
    }

    if (F_status_is_error(status)) {
      thread.id_signal = 0;

      if (data->error.verbosity != f_console_verbosity_quiet) {
        controller_error_print(data->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
      }
    }
    else {
      if (data->parameters[controller_parameter_daemon].result == f_console_result_found) {

        setting->ready = controller_setting_ready_done;

        if (f_file_exists(setting->path_pid.string) == F_true) {
          if (data->error.verbosity != f_console_verbosity_quiet) {

            f_thread_mutex_lock(&thread.lock.print);

            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data->error.to.stream, "%s%sThe pid file '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
            fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, setting->path_pid.string, data->error.notable.after->string);
            fprintf(data->error.to.stream, "%s' must not already exist.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);

            f_thread_mutex_unlock(&thread.lock.print);
          }

          setting->ready = controller_setting_ready_abort;
          status = F_status_set_error(F_available_not);
        }
      }
      else {
        const controller_main_entry_t entry = controller_macro_main_entry_t_initialize(&entry_name, &main, setting);

        // the entry processing runs using the rule thread.
        status = f_thread_create(0, &thread.id_rule, &controller_thread_entry, (void *) &entry);

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            controller_error_print(data->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
          }
        }
        else {
          f_thread_join(thread.id_rule, 0);

          thread.id_rule = 0;
          status = thread.status;
        }

        if (status == F_child) {
          controller_thread_delete_simple(&thread);

          return F_child;
        }
      }
    }

    // only make the rule and control threads available once any/all pre-processing and are completed.
    if (F_status_is_error_not(status) && status != F_signal && status != F_child && thread.enabled) {

      if (data->parameters[controller_parameter_validate].result == f_console_result_none && thread.id_rule) {

        // wait for the entry thread to complete before starting the rule thread.
        f_thread_join(thread.id_rule, 0);

        thread.id_rule = 0;

        if (thread.enabled) {
          status = f_thread_create(0, &thread.id_rule, &controller_thread_rule, (void *) &main);
        }

        status = f_thread_create(0, &thread.id_control, &controller_thread_control, (void *) &main);

        if (F_status_is_error(status)) {
          thread.id_control = 0;
        }
        else {
          status = f_thread_create(0, &thread.id_cleanup, &controller_thread_cleanup, (void *) &main);
        }

        if (F_status_is_error(status)) {
          thread.id_cleanup = 0;

          if (data->error.verbosity != f_console_verbosity_quiet) {
            controller_error_print(data->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
          }
        }
      }
    }

    if (status == F_child) {
      controller_thread_delete_simple(&thread);

      return F_child;
    }

    if (F_status_is_error(status) || status == F_signal || !(data->parameters[controller_parameter_validate].result == f_console_result_none || data->parameters[controller_parameter_test].result == f_console_result_found)) {

      if (status != F_signal && thread.id_signal) {
        f_thread_cancel(thread.id_signal);
      }

      controller_thread_process_cancel(&main);
    }

    // wait until signal thread exits, which happens on any termination signal.
    if (thread.id_signal) f_thread_join(thread.id_signal, 0);

    controller_thread_process_cancel(&main);

    if (thread.id_cleanup) f_thread_cancel(thread.id_cleanup);
    if (thread.id_control) f_thread_cancel(thread.id_control);
    if (thread.id_rule) f_thread_cancel(thread.id_rule);

    if (thread.id_cleanup) f_thread_join(thread.id_cleanup, 0);
    if (thread.id_control) f_thread_join(thread.id_control, 0);
    if (thread.id_rule) f_thread_join(thread.id_rule, 0);

    // if made it here, then the threads no longer need to be killed.
    f_thread_join(thread.id_exit, 0);

    thread.id_cleanup = 0;
    thread.id_control = 0;
    thread.id_rule = 0;
    thread.id_signal = 0;
    thread.id_exit = 0;

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

#ifndef _di_controller_thread_process_
  void * controller_thread_process(void *arguments) {

    controller_process_t *process = (controller_process_t *) arguments;

    {
      controller_thread_t *thread = (controller_thread_t *) process->main_thread;

      if (!thread->enabled) f_thread_exit(0);
    }

    controller_rule_process_do(F_true, process);

    f_thread_exit(0);
  }
#endif // _di_controller_thread_process_

#ifndef _di_controller_thread_process_cancel_
  void controller_thread_process_cancel(controller_main_t *main) {

    f_thread_lock_read(&main->thread->lock.process);

    // only cancel when enabled.
    if (!main->thread->enabled || main->thread->id_exit) {
      f_thread_unlock(&main->thread->lock.process);

      return;
    }

    // this must be set, regardless of lock state and only this function changes this.
    main->thread->enabled = F_false;

    f_thread_create(0, &main->thread->id_exit, &controller_thread_exit_force, (void *) main);

    controller_process_t *process = 0;

    f_array_length_t i = 0;

    for (; i < main->thread->processs.used; ++i) {

      process = &main->thread->processs.array[i];

      f_thread_lock_read(&process->lock);

      if (process->child > 0) {
        f_signal_send(F_signal_termination, process->child);
      }

      f_thread_unlock(&process->lock);
    } // for

    for (i = 0; i < main->thread->processs.used; ++i) {

      process = &main->thread->processs.array[i];

      f_thread_lock_read(&process->lock);

      if (process->id_thread) {
        f_thread_cancel(process->id_thread);
      }

      f_thread_unlock(&process->lock);
    } // for

    for (i = 0; i < main->thread->processs.size; ++i) {

      process = &main->thread->processs.array[i];

      if (process->id_thread) {
        f_thread_join(process->id_thread, 0);

        f_thread_lock_write(&process->lock);

        process->id_thread = 0;

        f_thread_unlock(&process->lock);
      }
    } // for

    f_thread_unlock(&main->thread->lock.process);
    f_thread_lock_write(&main->thread->lock.process);

    main->thread->processs.used = 0;

    f_thread_unlock(&main->thread->lock.process);
  }
#endif // _di_controller_thread_process_cancel_

#ifndef _di_controller_thread_entry_
  void * controller_thread_entry(void *arguments) {

    controller_main_entry_t *entry = (controller_main_entry_t *) arguments;

    if (!entry->main->thread->enabled) f_thread_exit(0);

    controller_data_t *data = entry->main->data;
    controller_cache_t *cache = &entry->main->thread->cache;
    f_status_t *status = &entry->main->thread->status;

    *status = controller_entry_read(*entry->name, *entry->main, cache);

    if (F_status_is_error(*status)) {
      entry->setting->ready = controller_setting_ready_fail;
    }
    else if (*status != F_signal && *status != F_child) {
      *status = controller_preprocess_entry(*entry->main, cache);
    }

    if (F_status_is_error_not(*status) && *status != F_signal && *status != F_child) {

      if (data->parameters[controller_parameter_validate].result == f_console_result_none || data->parameters[controller_parameter_test].result == f_console_result_found) {

        if (f_file_exists(entry->setting->path_pid.string) == F_true) {
          if (data->error.verbosity != f_console_verbosity_quiet) {

            f_thread_mutex_lock(&entry->main->thread->lock.print);

            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data->error.to.stream, "%s%sThe pid file '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
            fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, entry->setting->path_pid.string, data->error.notable.after->string);
            fprintf(data->error.to.stream, "%s' must not already exist.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);

            f_thread_mutex_unlock(&entry->main->thread->lock.print);
          }

          entry->setting->ready = controller_setting_ready_fail;
          *status = F_status_set_error(F_available_not);
        }
        else {
          *status = controller_process_entry(*entry->main, cache);

          if (F_status_is_error(*status)) {
            entry->setting->ready = controller_setting_ready_fail;
          }
          else if (*status == F_signal || *status == F_child) {
            entry->setting->ready = controller_setting_ready_abort;
          }
          else {
            entry->setting->ready = controller_setting_ready_done;
          }
        }
      }
    }

    f_thread_exit(0);
  }
#endif // _di_controller_thread_entry_

#ifndef _di_controller_thread_rule_
  void * controller_thread_rule(void *arguments) {

    controller_main_t *main = (controller_main_t *) arguments;

    if (!main->thread->enabled) f_thread_exit(0);

    f_thread_exit(0);
  }
#endif // _di_controller_thread_rule_

#ifndef _di_controller_thread_signal_
  void * controller_thread_signal(void *arguments) {

    controller_main_t *main = (controller_main_t *) arguments;

    if (!main->thread->enabled) f_thread_exit(0);

    for (int signal = 0; main->thread->enabled; ) {

      sigwait(&main->data->signal.set, &signal);

      if (main->data->parameters[controller_parameter_interruptable].result == f_console_result_found) {
        if (signal == F_signal_interrupt || signal == F_signal_abort || signal == F_signal_quit || signal == F_signal_termination) {
          main->thread->signal = signal; // @todo determine if I need signal saved anymore.

          controller_thread_process_cancel(main);
          break;
        }
      }
    } // for

    f_thread_exit(0);
  }
#endif // _di_controller_thread_signal_

#ifdef __cplusplus
} // extern "C"
#endif
