#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-entry.h"
#include "private-rule.h"
#include "private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_asynchronous_
  void * controller_thread_asynchronous(void *arguments) {

    controller_asynchronous_t *asynchronous = (controller_asynchronous_t *) arguments;
    controller_thread_t *thread_main = (controller_thread_t *) asynchronous->thread;

    if (!thread_main->enabled) {
      return 0;
    }

    controller_thread_t thread = controller_thread_t_initialize;

    f_thread_mutex_lock(&thread_main->setting->rules.array[asynchronous->index].lock);
    f_thread_mutex_lock(&asynchronous->lock);

    thread.cache_main = thread_main->cache_main;
    thread.cache_action = &asynchronous->cache;
    thread.data = thread_main->data;
    thread.lock = thread_main->lock;
    thread.setting = thread_main->setting;
    thread.stack = &asynchronous->stack;

    if (controller_rule_process(asynchronous->index, asynchronous->action, asynchronous->options, &thread, asynchronous) != F_child) {
      asynchronous->state = controller_asynchronous_state_done;
    }

    f_thread_mutex_unlock(&asynchronous->lock);

    f_thread_condition_signal(&thread_main->setting->rules.array[asynchronous->index].wait);
    f_thread_mutex_unlock(&thread_main->setting->rules.array[asynchronous->index].lock);

    return 0;
  }
#endif // _di_controller_thread_asynchronous_

#ifndef _di_controller_thread_asynchronous_cancel_
  void controller_thread_asynchronous_cancel(controller_thread_t *thread) {

    thread->enabled = F_false;

    f_thread_mutex_lock(&thread->lock.asynchronous);

    for (f_array_length_t i = 0; i < thread->asynchronouss.used; ++i) {

      if (!thread->asynchronouss.array[i].state) continue;

      if (f_thread_mutex_lock_try(&thread->asynchronouss.array[i].lock) == F_none) {
        f_thread_cancel(thread->asynchronouss.array[i].id);
        f_thread_detach(thread->asynchronouss.array[i].id);
        f_thread_mutex_unlock(&thread->asynchronouss.array[i].lock);
      }
      else {
        if (thread->asynchronouss.array[i].child > 0) {
          f_signal_send(F_signal_termination, thread->asynchronouss.array[i].child);
        }
        else {
          f_thread_cancel(thread->asynchronouss.array[i].id);
        }

        // the cancel make take time so detach the process to allow it to exit on its own.
        f_thread_detach(thread->asynchronouss.array[i].id);
      }
    } // for

    thread->asynchronouss.used = 0;

    f_thread_unlock(&thread->lock.asynchronous);
  }
#endif // _di_controller_thread_asynchronous_cancel_

#ifndef _di_controller_thread_cleanup_
  void * controller_thread_cleanup(void *arguments) {

    controller_thread_data_t *thread_data = (controller_thread_data_t *) arguments;

    const unsigned int interval = thread_data->data->parameters[controller_parameter_test].result == f_console_result_found ? controller_thread_cache_cleanup_interval_short : controller_thread_cache_cleanup_interval_long;

    f_array_length_t i = 0;

    for (; thread_data->thread->enabled; ) {
      sleep(interval);

      /*
      if (f_thread_lock_write_try(&thread_data->thread->lock.asynchronous) == F_none) {
        controller_thread_t *thread = &thread_data->thread;

        if (thread->asynchronouss.used) {
          for (i = 0; i < thread->asynchronouss.used; ++i) {

            if (!thread->enabled) break;
            if (!thread->asynchronouss.array[i].state) continue;

            if (f_thread_lock_write_try(&thread->asynchronouss.array[i].lock) != F_none) continue;

            if (f_thread_lock_write_try(&thread_data->setting->rules.array[thread->asynchronouss.array[i].index].lock) == F_none) {

              if (thread->asynchronouss.array[i].state == controller_asynchronous_state_done) {
                f_thread_join(thread->asynchronouss.array[i].id, 0);
                thread->asynchronouss.array[i].state = controller_asynchronous_state_joined;
              }

              if (thread->asynchronouss.array[i].state == controller_asynchronous_state_joined) {
                controller_macro_asynchronous_t_delete_simple(thread->asynchronouss.array[i]);

                thread->asynchronouss.array[i].state = 0;
              }

              f_thread_condition_signal(&thread_data->setting->rules.array[thread->asynchronouss.array[i].index].wait);
              f_thread_mutex_unlock(&thread_data->setting->rules.array[thread->asynchronouss.array[i].index].lock);
            }

            f_thread_mutex_unlock(&thread->asynchronouss.array[i].lock);
          } // for

          for (i = thread->asynchronouss.used - 1; thread->asynchronouss.used; --i, --thread->asynchronouss.used) {

            if (!thread->enabled) break;

            if (f_thread_mutex_lock_try(&thread->asynchronouss.array[i].lock) != F_none) break;

            if (thread->asynchronouss.array[i].state == controller_asynchronous_state_joined) {
              controller_macro_asynchronous_t_delete_simple(thread->asynchronouss.array[i]);

              thread->asynchronouss.array[i].state = 0;
            }
            else if (thread->asynchronouss.array[i].state) {
              f_thread_unlock(&thread->asynchronouss.array[i].lock);
              break;
            }

            f_thread_unlock(&thread->asynchronouss.array[i].lock);
          } // for
        }

        if (thread->enabled && thread->asynchronouss.used < thread->asynchronouss.size) {
          controller_asynchronouss_resize(thread->asynchronouss.used, &thread->asynchronouss);
        }

        f_thread_unlock(&thread->lock.asynchronous);
      }
      */
    } // for

    return 0;
  }
#endif // _di_controller_thread_cleanup_

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void *arguments) {

    controller_thread_data_t *thread_data = (controller_thread_data_t *) arguments;

    // @todo

    return 0;
  }
#endif // _di_controller_thread_control_

#ifndef _di_controller_thread_main_
  f_status_t controller_thread_main(const f_string_static_t entry_name, controller_data_t *data, controller_setting_t *setting) {

    f_status_t status = F_none;

    controller_thread_t thread = controller_thread_t_initialize;
    controller_processs_t processs = controller_processs_t_initialize;
    controller_thread_data_t data_main = controller_macro_thread_data_t_initialize(0, data, setting, &processs, &thread);

    status = controller_asynchronouss_increase(&thread.asynchronouss);

    if (F_status_is_error_not(status)) {
      status = f_thread_create(0, &thread.id_signal, &controller_thread_signal, (void *) &data_main);
    }

    if (F_status_is_error(status)) {
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

        status = controller_entry_read(entry_name, data_main, &thread.asynchronouss.array[0].cache);

        if (F_status_is_error(status)) {
          setting->ready = controller_setting_ready_fail;
        }
        else if (status != F_signal && status != F_child) {
          status = controller_preprocess_entry(data_main, &thread.asynchronouss.array[0].cache);
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
              status = controller_process_entry(data_main, &thread.asynchronouss.array[0].cache);

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

    // only make the rule and control threads available once any/all pre-processing and is completed.
    if (F_status_is_error_not(status) && status != F_signal && status != F_child) {

      if (data->parameters[controller_parameter_validate].result == f_console_result_none) {
        controller_rule_wait_all(&thread);

        status = f_thread_create(0, &thread.id_rule, &controller_thread_rule, (void *) &data_main);

        if (F_status_is_error_not(status)) {
          status = f_thread_create(0, &thread.id_control, &controller_thread_control, (void *) &data_main);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_create(0, &thread.id_cleanup, &controller_thread_cleanup, (void *) &data_main);
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
      controller_thread_asynchronous_cancel(&thread);
    }

    // @todo when cancelling, make sure that whatever has a lock, no longer has any lock.
    f_thread_cancel(thread.id_cleanup);
    f_thread_cancel(thread.id_control);
    f_thread_cancel(thread.id_rule);

    f_thread_join(thread.id_cleanup, 0);
    f_thread_join(thread.id_control, 0);
    f_thread_join(thread.id_rule, 0);

    controller_processs_delete_simple(&processs);
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

#ifndef _di_controller_thread_rule_
  void * controller_thread_rule(void *arguments) {

    controller_thread_data_t *thread_data = (controller_thread_data_t *) arguments;

    // @todo
    // f_thread_mutex_lock(&thread_data->lock.rule);
    // f_thread_mutex_unlock(&thread_data->lock.rule);

    return 0;
  }
#endif // _di_controller_thread_rule_

#ifndef _di_controller_thread_signal_
  void * controller_thread_signal(void *arguments) {

    controller_thread_data_t *thread_data = (controller_thread_data_t *) arguments;

    for (int signal = 0; thread_data->thread->enabled; ) {

      sigwait(&thread_data->data->signal.set, &signal);

      if (thread_data->data->parameters[controller_parameter_interruptable].result == f_console_result_found) {
        if (signal == F_signal_interrupt || signal == F_signal_abort || signal == F_signal_quit || signal == F_signal_termination) {
          thread_data->setting->signal = signal;

          controller_thread_asynchronous_cancel(thread_data->thread);
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
