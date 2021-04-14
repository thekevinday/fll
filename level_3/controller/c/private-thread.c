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

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    const controller_main_t *main = (controller_main_t *) arguments;

    if (!main->thread->enabled) return 0;

    const unsigned int interval = main->data->parameters[controller_parameter_test].result == f_console_result_found ? controller_thread_cleanup_interval_short : controller_thread_cleanup_interval_long;

    f_status_t status = F_none;

    while (main->thread->enabled) {

      sleep(interval);

      if (main->thread->enabled && f_thread_lock_write_try(&main->thread->lock.process) == F_none) {
        controller_process_t *process = 0;

        f_array_length_t i = 0;

        for (; i < main->thread->processs.size && main->thread->enabled; ++i) {

          if (!main->thread->processs.array[i]) continue;

          process = main->thread->processs.array[i];

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

          f_thread_unlock(&process->lock);

          // close any still open thread.
          if (process->id_thread) {
            f_thread_join(process->id_thread, 0);

            if (!main->thread->enabled) {
              f_thread_unlock(&process->active);

              break;
            }

            status = controller_lock_write(main->thread, &process->lock);

            if (status == F_signal || F_status_is_error(status)) {
              controller_lock_error_critical_print(main->data->error, F_status_set_fine(status), F_false, main->thread);

              f_thread_unlock(&process->active);

              break;
            }

            process->state = controller_process_state_idle;
            process->id_thread = 0;

            f_thread_unlock(&process->lock);
          }

          // deallocate dynamic portions of the structure that are only ever needed while the process is running.
          controller_cache_delete_simple(&process->cache);
          f_type_array_lengths_resize(0, &process->stack);

          // deallocate any rules in the space that is declared to be unused.
          if (i >= main->thread->processs.used) {
            controller_rule_delete_simple(&process->rule);
          }

          f_thread_unlock(&process->active);
        } // for

        f_thread_unlock(&main->thread->lock.process);
      }
    } // while

    return 0;
  }
#endif // _di_controller_thread_cleanup_

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_t *main = (controller_main_t *) arguments;

    if (!main->thread->enabled) return 0;

    return 0;
  }
#endif // _di_controller_thread_control_

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

            controller_print_unlock_flush(data->error.to.stream, &thread.lock.print);
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
          if (status == F_child) {
            controller_thread_delete_simple(&thread);

            return F_child;
          }

          f_thread_join(thread.id_rule, 0);

          thread.id_rule = 0;
          status = thread.status;
        }
      }
    }

    // only make the rule and control threads available once any/all pre-processing and are completed.
    if (F_status_is_error_not(status) && status != F_signal && status != F_child && thread.enabled) {

      if (data->parameters[controller_parameter_validate].result == f_console_result_none) {

        if (thread.id_rule) {

          // wait for the entry thread to complete before starting the rule thread.
          f_thread_join(thread.id_rule, 0);

          if (thread.status == F_child) {
            controller_thread_delete_simple(&thread);

            return F_child;
          }

          thread.id_rule = 0;
        }

        if (thread.enabled) {
          status = f_thread_create(0, &thread.id_rule, &controller_thread_rule, (void *) &main);

          if (F_status_is_error(status)) {
            thread.id_rule = 0;
          }
          else {
            status = f_thread_create(0, &thread.id_control, &controller_thread_control, (void *) &main);
          }

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
    }

    if (status == F_child) {
      controller_thread_delete_simple(&thread);

      return F_child;
    }

    if (F_status_is_error(status) || status == F_signal || !(data->parameters[controller_parameter_validate].result == f_console_result_none || data->parameters[controller_parameter_test].result == f_console_result_found)) {

      if (status != F_signal && thread.id_signal) {
        f_thread_cancel(thread.id_signal);
      }
    }
    else if (data->parameters[controller_parameter_validate].result == f_console_result_none) {

      if (thread.id_signal) {
        f_thread_join(thread.id_signal, 0);

        thread.id_signal = 0;
      }
    }
    else {
      f_thread_cancel(thread.id_signal);
    }

    controller_thread_process_cancel(&main);

    if (thread.id_signal) f_thread_join(thread.id_signal, 0);
    if (thread.id_cleanup) f_thread_join(thread.id_cleanup, 0);
    if (thread.id_control) f_thread_join(thread.id_control, 0);
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

#ifndef _di_controller_thread_process_
  void * controller_thread_process(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_process_t *process = (controller_process_t *) arguments;

    {
      controller_thread_t *thread = (controller_thread_t *) process->main_thread;

      if (!thread->enabled) return 0;
    }

    const f_status_t status = controller_rule_process_do(controller_process_option_asynchronous, process);

    if (status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      // Deallocate as much as possible.

      controller_data_t *data = (controller_data_t *) process->main_data;
      controller_setting_t *setting = (controller_setting_t *) process->main_setting;
      controller_thread_t *thread = (controller_thread_t *) process->main_thread;

      controller_thread_delete_simple(thread);
      controller_setting_delete_simple(setting);
      controller_delete_data(data);
    }

    return 0;
  }
#endif // _di_controller_thread_process_

#ifndef _di_controller_thread_process_cancel_
  void controller_thread_process_cancel(controller_main_t *main) {

    // only cancel when enabled.
    if (!main->thread->enabled) {
      return;
    }

    // this must be set, regardless of lock state and only this function changes this.
    main->thread->enabled = F_false;

    f_status_t status = F_none;
    f_array_length_t spent = 0;

    struct timespec time;

    controller_process_t *process = 0;

    f_array_length_t i = 0;

    if (main->thread->id_cleanup) {
      f_thread_cancel(main->thread->id_cleanup);
    }

    if (main->thread->id_control) {
      f_thread_cancel(main->thread->id_control);
    }

    if (main->thread->id_rule) {
      f_thread_cancel(main->thread->id_rule);
    }

    for (; i < main->thread->processs.used; ++i) {

      if (!main->thread->processs.array[i]) continue;

      process = main->thread->processs.array[i];

      if (process->child > 0) {
        f_signal_send(F_signal_termination, process->child);
      }
    } // for

    for (i = 0; i < main->thread->processs.used; ++i) {

      if (!main->thread->processs.array[i]) continue;

      process = main->thread->processs.array[i];

      if (process->id_thread) {
        controller_time(0, controller_thread_exit_process_cancel_wait, &time);

        status = f_thread_join_timed(process->id_thread, time, 0);

        if (status == F_none) {
          process->child = 0;
          process->id_thread = 0;
        }
        else {
          f_thread_cancel(process->id_thread);
        }
      }
    } // for

    for (i = 0; i < main->thread->processs.size && spent < controller_thread_exit_process_cancel_total; ++i) {

      if (!main->thread->processs.array[i]) continue;

      process = main->thread->processs.array[i];

      do {
        controller_time(0, controller_thread_exit_process_cancel_wait, &time);

        status = f_thread_join_timed(process->id_thread, time, 0);

        if (status == F_none) {
          process->child = 0;
          process->id_thread = 0;
        }

        spent++;

      } while (status == F_time && spent < controller_thread_exit_process_cancel_total);
    } // for

    for (i = 0; i < main->thread->processs.size; ++i) {
      if (!main->thread->processs.array[i]) continue;

      process = main->thread->processs.array[i];

      if (process->id_thread) {

        if (process->child > 0) {
          f_signal_send(F_signal_kill, process->child);

          time.tv_sec = 0;
          time.tv_nsec = controller_thread_exit_process_cancel_wait;

          nanosleep(&time, 0);
        }

        f_thread_join(process->id_thread, 0);

        process->child = 0;
        process->id_thread = 0;
      }
    } // for
  }
#endif // _di_controller_thread_process_cancel_

#ifndef _di_controller_thread_entry_
  void * controller_thread_entry(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_entry_t *entry = (controller_main_entry_t *) arguments;

    if (!entry->main->thread->enabled) return 0;

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

            controller_print_unlock_flush(data->error.to.stream, &entry->main->thread->lock.print);
          }

          entry->setting->ready = controller_setting_ready_fail;
          *status = F_status_set_error(F_available_not);
        }
        else {
          *status = controller_process_entry(F_false, entry->main, cache);

          if (F_status_is_error(*status)) {
            entry->setting->ready = controller_setting_ready_fail;

            if (F_status_set_fine(*status) == F_require && entry->main->setting->failsafe_enabled) {
              const f_status_t status_failsafe = controller_process_entry(F_true, entry->main, cache);

              if (F_status_is_error(status_failsafe)) {
                if (data->error.verbosity != f_console_verbosity_quiet) {
                  f_thread_mutex_lock(&entry->main->thread->lock.print);

                  fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(data->error.to.stream, "%s%sFailed while processing requested failsafe item '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
                  fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, entry->main->setting->entry.items.array[entry->main->setting->failsafe_enabled].name.string, data->error.notable.after->string);
                  fprintf(data->error.to.stream, "%s'.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);

                  controller_print_unlock_flush(data->error.to.stream, &entry->main->thread->lock.print);
                }
              }
            }
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

    if (*status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      // Deallocate as much as possible.

      controller_thread_delete_simple(entry->main->thread);
      controller_setting_delete_simple(entry->main->setting);
      controller_delete_data(entry->main->data);
    }

    return 0;
  }
#endif // _di_controller_thread_entry_

#ifndef _di_controller_thread_rule_
  void * controller_thread_rule(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_t *main = (controller_main_t *) arguments;

    if (!main->thread->enabled) return 0;

    return 0;
  }
#endif // _di_controller_thread_rule_

#ifndef _di_controller_thread_signal_
  void * controller_thread_signal(void *arguments) {

    controller_main_t *main = (controller_main_t *) arguments;

    if (!main->thread->enabled) return 0;

    for (int signal = 0; main->thread->enabled; ) {

      sigwait(&main->data->signal.set, &signal);

      if (main->data->parameters[controller_parameter_interruptable].result == f_console_result_found) {
        if (signal == F_signal_interrupt || signal == F_signal_abort || signal == F_signal_quit || signal == F_signal_termination) {
          main->thread->signal = signal;

          controller_thread_process_cancel(main);
          break;
        }
      }
    } // for

    return 0;
  }
#endif // _di_controller_thread_signal_

#ifdef __cplusplus
} // extern "C"
#endif
