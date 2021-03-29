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

    const unsigned int interval = main->data->parameters[controller_parameter_test].result == f_console_result_found ? controller_thread_cache_cleanup_interval_short : controller_thread_cache_cleanup_interval_long;

    while (main->thread->enabled) {

      sleep(interval);

      if (f_thread_lock_write_try(&main->thread->lock.process) == F_none) {
        controller_process_t *process = 0;

        // index 0 is reserved for "main thread".
        f_array_length_t i = 1;

        for (; j < main->thread->processs.used; ++i) {

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

          if (process->state == controller_process_state_done) {
            f_thread_detach(process->id_thread);
            process->state = controller_process_state_idle;
          }

          // deallocate dynamic portions of the structure that are only ever needed while the process is running.
          controller_cache_delete_simple(&process->cache);
          f_type_array_lengths_resize(0, &process->stack);

          f_thread_unlock(&process->active);
          f_thread_unlock(&process->lock);
        } // for

        for (i = main->thread->processs.used - 1; main->thread->processs.used; --i, --main->thread->processs.used) {

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

          if (process->state == controller_process_state_done) {
            f_thread_detach(process->id_thread);
            process->state = controller_process_state_idle;
          }

          // deallocate dynamic portions of the structure that are only ever needed while the process is running.
          controller_cache_delete_simple(&process->cache);
          f_type_array_lengths_resize(0, &process->stack);

          --main->thread->processs.used;

          f_thread_unlock(&process->active);
          f_thread_unlock(&process->lock);
        } // for

        f_thread_unlock(&main->thread->lock.process);
      }
    } // while

    return 0;
  }
#endif // _di_controller_thread_cleanup_

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void *arguments) {

    controller_main_t *main = (controller_main_t *) arguments;

    // @todo

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

      if (data->error.verbosity != f_console_verbosity_quiet) {
        controller_error_print(data->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
      }
    }

    if (F_status_is_error_not(status)) {
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

        // index 0 is reserved for running the main thread cache.
        thread.processs.used = 1;

        status = controller_entry_read(entry_name, main, &thread.processs.array[0].cache);

        if (F_status_is_error(status)) {
          setting->ready = controller_setting_ready_fail;
        }
        else if (status != F_signal && status != F_child) {
          status = controller_preprocess_entry(main, &thread.processs.array[0].cache);
        }

        if (F_status_is_error_not(status) && status != F_signal && status != F_child) {

          if (data->parameters[controller_parameter_validate].result == f_console_result_none || data->parameters[controller_parameter_test].result == f_console_result_found) {

            if (f_file_exists(setting->path_pid.string) == F_true) {
              if (data->error.verbosity != f_console_verbosity_quiet) {

                f_thread_mutex_lock(&thread.lock.print);

                fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data->error.to.stream, "%s%sThe pid file '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
                fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, setting->path_pid.string, data->error.notable.after->string);
                fprintf(data->error.to.stream, "%s' must not already exist.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);

                f_thread_mutex_unlock(&thread.lock.print);
              }

              setting->ready = controller_setting_ready_fail;
              status = F_status_set_error(F_available_not);
            }
            else {
              status = controller_process_entry(main, &thread.processs.array[0].cache);

              if (F_status_is_error(status)) {
                setting->ready = controller_setting_ready_fail;
              }
              else if (status == F_signal || status == F_child) {
                setting->ready = controller_setting_ready_abort;
              }
              else {
                setting->ready = controller_setting_ready_done;
              }
            }
          }
        }

        if (status == F_child) {
          controller_thread_delete_simple(&thread);

          return F_child;
        }
      }
    }

    if (status != F_signal && setting->signal) {
      status = F_signal;
    }

    // only make the rule and control threads available once any/all pre-processing and are completed.
    if (F_status_is_error_not(status) && status != F_signal && status != F_child) {

      if (data->parameters[controller_parameter_validate].result == f_console_result_none) {
        controller_rule_wait_all(main);

        status = f_thread_create(0, &thread.id_control, &controller_thread_control, (void *) &main);

        if (F_status_is_error_not(status)) {
          status = f_thread_create(0, &thread.id_cleanup, &controller_thread_cleanup, (void *) &main);
        }

        if (F_status_is_error(status)) {
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

    // @todo consider f_thread_detach() over f_thread_join() when exiting.
    if (F_status_is_error_not(status) && status != F_signal && (data->parameters[controller_parameter_validate].result == f_console_result_none || data->parameters[controller_parameter_test].result == f_console_result_found)) {

      // wait until signal thread exits, which happens on any termination signal.
      f_thread_join(thread.id_signal, 0);
    }
    else {
      f_thread_cancel(thread.id_signal);
      f_thread_join(thread.id_signal, 0);
    }

    if (thread.enabled) {
      controller_thread_process_cancel(main);
    }

    f_thread_cancel(thread.id_cleanup);
    f_thread_cancel(thread.id_control);

    f_thread_detach(thread.id_cleanup);
    f_thread_detach(thread.id_control);

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

    controller_rule_process_do(F_true, (controller_process_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_process_

#ifndef _di_controller_thread_process_cancel_
  void controller_thread_process_cancel(const controller_main_t main) {

    // this must be set, regardless of lock state and only this function changes this.
    main.thread->enabled = F_false;

    f_thread_lock_write(&main.thread->lock.process);

    if (!main.thread->processs.used) {
      f_thread_unlock(&main.thread->lock.process);

      return;
    }

    controller_process_t *process = 0;

    bool locked = 0;

    //pid_t[main.thread->processs.used] pids;
    //memset(&pids, 0, sizeof(pid_t) * main.thread->processs.used);

    // index 0 is reserved for running the main thread cache.
    for (f_array_length_t i = 1; i < main.thread->processs.used; ++i) {

      process = &main.thread->processs.array[i];

      locked = f_thread_lock_write_try(&process->lock) == F_none;

      if (!locked) {
        locked = f_thread_lock_read_try(&process->lock) == F_none;
      }

      if (locked) {
        if (process->child > 0) {
          f_signal_send(F_signal_quit, process->child);
        }

        if (process->state == controller_process_state_active || process->state == controller_process_state_busy) {
          f_thread_cancel(process->id_thread);
          f_thread_detach(process->id_thread);
        }
        else if (process->state == controller_process_state_done) {
          f_thread_detach(process->id_thread);
        }

        f_thread_unlock(&process->lock);
      }
    } // for

    main.thread->processs.used = 0;

    // @todo: sleep a little, check to see if child processes quit, and if not then sen F_signal_quit_termination.
    //        this will likely need to be done by:
    //        1) create an array of child process ids from above loop.
    //        2) search through loop at this location in the code and if the process id is found, sleep a little.
    //        3) check again to see if the child process quit and if not, then send the F_signal_quit_termination.
    //        4) continue to next child until entire array is processed.

    f_thread_unlock(&main.thread->lock.process);
  }
#endif // _di_controller_thread_process_cancel_

#ifndef _di_controller_thread_signal_
  void * controller_thread_signal(void *arguments) {

    controller_main_t *main = (controller_main_t *) arguments;

    for (int signal = 0; main->thread->enabled; ) {

      sigwait(&main->data->signal.set, &signal);

      if (main->data->parameters[controller_parameter_interruptable].result == f_console_result_found) {
        if (signal == F_signal_interrupt || signal == F_signal_abort || signal == F_signal_quit || signal == F_signal_termination) {
          main->thread->signal = signal;

          controller_thread_process_cancel(*main);
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
