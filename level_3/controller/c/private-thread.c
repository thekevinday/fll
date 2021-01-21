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
    controller_thread_t thread = controller_thread_t_initialize;

    {
      controller_thread_t *thread_main = (controller_thread_t *) asynchronous->thread;

      f_thread_mutex_lock(&thread_main->setting->rules.array[asynchronous->index].lock);

      thread.cache_main = thread_main->cache_main;
      thread.cache_action = &asynchronous->cache;
      thread.data = thread_main->data;
      thread.mutex = thread_main->mutex;
      thread.setting = thread_main->setting;
      thread.stack = &asynchronous->stack;
    }

    controller_rule_process(asynchronous->index, asynchronous->action, asynchronous->options, &thread);

    f_thread_mutex_unlock(&thread.setting->rules.array[asynchronous->index].lock);

    return 0;
  }
#endif // _di_controller_thread_asynchronous_

#ifndef _di_controller_thread_asynchronous_cancel_
  void controller_thread_asynchronous_cancel(controller_thread_t *thread) {

    f_thread_mutex_lock(&thread->mutex->asynchronous);

    for (f_array_length_t i = 0; i < thread->asynchronouss.used; ++i) {

      if (!thread->asynchronouss.array[i].state) continue;

      f_thread_cancel(thread->asynchronouss.array[i].id);
      f_thread_join(thread->asynchronouss.array[i].id, 0);

      thread->asynchronouss.array[i].state = 0;

      controller_macro_cache_action_t_clear(thread->asynchronouss.array[i].cache);
    } // for

    thread->asynchronouss.used = 0;

    f_thread_mutex_unlock(&thread->mutex->asynchronous);
  }
#endif // _di_controller_thread_asynchronous_cancel_

#ifndef _di_controller_thread_cache_
  void * controller_thread_cache(void *arguments) {

    controller_thread_t *thread = (controller_thread_t *) arguments;
    f_array_length_t i = 0;

    for (;;) {

      // @todo depend on a posix mutex condition that will designate when to sleep and perform actions.
      //       when the condition is on/off, then the program will either sleep until condition is toggled or sleep a given interval.
      //       when sleeping a given interval, then after each interval expiration, perform process cleanups until there are no asynchronous processes to cleanup.
      //       once all asynchronous processes are cleaned up, toggle the condition again and wait indefinitely.
      sleep(controller_thread_cache_cleanup_interval_long);

      if (f_thread_mutex_lock_try(&thread->mutex->cache) == F_none) {
        controller_macro_cache_t_delete_simple((*thread->cache_main));
        controller_macro_cache_action_t_delete_simple((*thread->cache_action));

        if (f_thread_mutex_lock_try(&thread->mutex->asynchronous) == F_none) {

          for (i = 0; i < thread->asynchronouss.size; ++i) {

            if (thread->asynchronouss.array[i].state == controller_asynchronous_state_done) {
              f_thread_join(thread->asynchronouss.array[i].id, 0);
              thread->asynchronouss.array[i].state = controller_asynchronous_state_joined;
            }

            if (thread->asynchronouss.array[i].state == controller_asynchronous_state_joined) {
              controller_macro_cache_action_t_clear(thread->asynchronouss.array[i].cache);
              thread->asynchronouss.array[i].state = 0;
            }
          } // for

          for (i = thread->asynchronouss.size; i; --i) {
            if (thread->asynchronouss.array[i - 1].state) break;

            controller_macro_asynchronous_t_delete_simple(thread->asynchronouss.array[i])
          } // for

          thread->asynchronouss.used = i;

          if (thread->asynchronouss.used < thread->asynchronouss.size) {
            controller_asynchronouss_resize(thread->asynchronouss.used, &thread->asynchronouss);
          }

          f_thread_mutex_unlock(&thread->mutex->asynchronous);
        }

        f_thread_mutex_unlock(&thread->mutex->cache);
      }
    } // for

    return 0;
  }
#endif // _di_controller_thread_cache_

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void *arguments) {

    controller_thread_t *thread = (controller_thread_t *) arguments;

    // @todo

    return 0;
  }
#endif // _di_controller_thread_control_

#ifndef _di_controller_thread_main_
  f_status_t controller_thread_main(const f_string_static_t entry_name, controller_cache_t *cache, controller_thread_t *thread) {

    f_thread_id_t thread_cache = 0;
    f_thread_id_t thread_control = 0;
    f_thread_id_t thread_rule = 0;
    f_thread_id_t thread_signal = 0;

    f_status_t status = f_thread_create(0, &thread_signal, &controller_thread_signal, (void *) thread);

    if (F_status_is_error_not(status)) {
      status = f_thread_create(0, &thread_cache, &controller_thread_cache, (void *) thread);
    }

    if (F_status_is_error(status)) {
      if (thread->data->error.verbosity != f_console_verbosity_quiet) {
        fll_error_print(thread->data->error, F_status_set_fine(status), "f_thread_create", F_true);
      }
    }
    else {
      if (thread->data->parameters[controller_parameter_daemon].result == f_console_result_found) {
        thread->setting->ready = controller_setting_ready_done;

        if (f_file_exists(thread->setting->path_pid.string) == F_true) {
          if (thread->data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(thread->data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(thread->data->error.to.stream, "%s%sThe pid file '", thread->data->error.context.before->string, thread->data->error.prefix ? thread->data->error.prefix : f_string_empty_s);
            fprintf(thread->data->error.to.stream, "%s%s%s%s", thread->data->error.context.after->string, thread->data->error.notable.before->string, thread->setting->path_pid.string, thread->data->error.notable.after->string);
            fprintf(thread->data->error.to.stream, "%s' must not already exist.%s%c", thread->data->error.context.before->string, thread->data->error.context.after->string, f_string_eol_s[0]);
          }

          thread->setting->ready = controller_setting_ready_abort;
          status = F_status_set_error(F_available_not);
        }
      }
      else {
        f_thread_mutex_lock(&thread->mutex->cache);

        status = controller_entry_read(*thread->data, *thread->setting, entry_name, cache, &thread->setting->entry);

        if (F_status_is_error(status)) {
          thread->setting->ready = controller_setting_ready_fail;
        }
        else if (status != F_signal && status != F_child) {
          status = controller_preprocess_entry(cache, thread);
        }

        if (F_status_is_error_not(status) && status != F_signal && status != F_child) {
          if (thread->data->parameters[controller_parameter_validate].result == f_console_result_none || thread->data->parameters[controller_parameter_test].result == f_console_result_found) {

            if (f_file_exists(thread->setting->path_pid.string) == F_true) {
              if (thread->data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(thread->data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(thread->data->error.to.stream, "%s%sThe pid file '", thread->data->error.context.before->string, thread->data->error.prefix ? thread->data->error.prefix : f_string_empty_s);
                fprintf(thread->data->error.to.stream, "%s%s%s%s", thread->data->error.context.after->string, thread->data->error.notable.before->string, thread->setting->path_pid.string, thread->data->error.notable.after->string);
                fprintf(thread->data->error.to.stream, "%s' must not already exist.%s%c", thread->data->error.context.before->string, thread->data->error.context.after->string, f_string_eol_s[0]);
              }

              thread->setting->ready = controller_setting_ready_fail;
              status = F_status_set_error(F_available_not);
            }
            else {
              status = controller_process_entry(cache, thread);

              if (F_status_is_error(status)) {
                thread->setting->ready = controller_setting_ready_fail;
              }
              else if (status == F_signal || status == F_child) {
                thread->setting->ready = controller_setting_ready_abort;
              }
              else {
                thread->setting->ready = controller_setting_ready_done;
              }
            }
          }
        }

        f_thread_mutex_unlock(&thread->mutex->cache);
      }
    }

    if (status != F_signal && thread->setting->signal) {
      status = F_signal;
    }

    // only make the rule and control threads available once any/all pre-processing and is completed.
    if (F_status_is_error_not(status) && status != F_signal && status != F_child) {

      controller_rule_wait_all(thread);

      status = f_thread_create(0, &thread_rule, &controller_thread_rule, (void *) thread);

      if (F_status_is_error_not(status)) {
        status = f_thread_create(0, &thread_control, &controller_thread_control, (void *) thread);
      }

      if (F_status_is_error(status)) {
        if (thread->data->error.verbosity != f_console_verbosity_quiet) {
          fll_error_print(thread->data->error, F_status_set_fine(status), "f_thread_create", F_true);
        }
      }
    }

    if (F_status_is_error_not(status) && status != F_signal && status != F_child) {

      // wait until signal thread exits, which happens on any termination signal.
      f_thread_join(thread_signal, 0);
    }
    else {
      f_thread_cancel(thread_signal);
      f_thread_join(thread_signal, 0);
    }

    controller_thread_asynchronous_cancel(thread);

    f_thread_cancel(thread_cache);
    f_thread_cancel(thread_control);
    f_thread_cancel(thread_rule);

    f_thread_join(thread_cache, 0);
    f_thread_join(thread_control, 0);
    f_thread_join(thread_rule, 0);

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

    controller_thread_t *thread = (controller_thread_t *) arguments;

    // @todo
    // f_thread_mutex_lock(&thread->mutex->rule);
    // f_thread_mutex_unlock(&thread->mutex->rule);

    return 0;
  }
#endif // _di_controller_thread_rule_

#ifndef _di_controller_thread_signal_
  void * controller_thread_signal(void *arguments) {

    controller_thread_t *thread = (controller_thread_t *) arguments;

    for (int signal = 0; ; ) {

      sigwait(&thread->data->signal.set, &signal);

      if (thread->data->parameters[controller_parameter_interruptable].result == f_console_result_found) {
        if (signal == F_signal_interrupt || signal == F_signal_abort || signal == F_signal_quit || signal == F_signal_termination) {
          thread->setting->signal = signal;
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
