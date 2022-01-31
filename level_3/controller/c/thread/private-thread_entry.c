#include "../controller.h"
#include "../common/private-common.h"
#include "../entry/private-entry.h"
#include "../lock/private-lock_print.h"
#include "../thread/private-thread.h"
#include "private-thread_entry.h"
#include "private-thread_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_entry_
  void * controller_thread_entry(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_entry_t *entry = (controller_main_entry_t *) arguments;

    if (!controller_thread_is_enabled(F_true, entry->global->thread)) return 0;

    controller_main_t *main = entry->global->main;
    controller_cache_t *cache = &entry->global->thread->cache;
    f_status_t *status = &entry->global->thread->status;

    *status = controller_entry_read(*entry->global, F_true, cache);

    if (F_status_set_fine(*status) == F_interrupt) {
      entry->setting->ready = controller_setting_ready_abort_e;
    }
    else if (F_status_is_error(*status)) {
      entry->setting->ready = controller_setting_ready_fail_e;
    }
    else if (*status != F_child) {
      *status = controller_entry_preprocess(*entry->global, F_true, cache);
    }

    if (F_status_is_error_not(*status) && *status != F_child) {
      if (main->parameters.array[controller_parameter_validate_e].result == f_console_result_none_e || main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e) {

        if (entry->setting->entry.pid == controller_entry_pid_require_e && f_file_exists(entry->setting->path_pid.string) == F_true) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            controller_lock_print(main->error.to, entry->global->thread);

            fl_print_format("%q%[%QThe pid file '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, entry->setting->path_pid, main->error.notable);
            fl_print_format("%[' must not already exist.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            controller_unlock_print_flush(main->error.to, entry->global->thread);
          }

          entry->setting->ready = controller_setting_ready_fail_e;
          *status = F_status_set_error(F_available_not);
        }
        else {
          *status = controller_entry_process(entry->global, cache, F_false, F_true);

          if (F_status_is_error(*status)) {
            entry->setting->ready = controller_setting_ready_fail_e;

            if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && entry->global->setting->failsafe_enabled) {
              const uint8_t original_enabled = entry->global->thread->enabled;

              // Restore operating mode so that the failsafe can execute.
              *status = f_thread_mutex_lock(&entry->global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                entry->global->thread->enabled = controller_thread_enabled_e;

                f_thread_mutex_unlock(&entry->global->thread->lock.alert);
              }

              // Restart the signal thread to allow for signals while operating the failsafe Items.
              if (!entry->global->thread->id_signal) {
                f_thread_create(0, &entry->global->thread->id_signal, &controller_thread_signal_normal, (void *) entry->global);
              }

              const f_status_t status_failsafe = controller_entry_process(entry->global, cache, F_true, F_true);

              if (F_status_is_error(status_failsafe)) {
                if (main->error.verbosity != f_console_verbosity_quiet_e) {
                  controller_lock_print(main->error.to, entry->global->thread);

                  fl_print_format("%q%[%QFailed while processing requested failsafe item '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                  fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, entry->global->setting->entry.items.array[entry->global->setting->failsafe_enabled].name, main->error.notable);
                  fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                  controller_unlock_print_flush(main->error.to, entry->global->thread);
                }

                *status = F_status_set_error(F_failure);
              }
              else {

                // Restore operating mode to value prior to failsafe mode.
                *status = f_thread_mutex_lock(&entry->global->thread->lock.alert);

                if (F_status_is_error_not(*status)) {
                  entry->global->thread->enabled = original_enabled;

                  f_thread_mutex_unlock(&entry->global->thread->lock.alert);
                }

                *status = F_failure;
              }
            }
          }
          else if (F_status_set_fine(*status) == F_interrupt) {
            entry->setting->ready = controller_setting_ready_abort_e;
          }
          else if (*status != F_child) {
            entry->setting->ready = controller_setting_ready_done_e;
          }
        }
      }
    }

    if (*status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      // Deallocate as much as possible.
      controller_thread_delete_simple(entry->global->thread);
      controller_setting_delete_simple(entry->global->setting);
      controller_main_delete(entry->global->main);

      // According to the manpages, pthread_exit() calls exit(0), which is not good because a non-zero exit code may be returned.
      if (main->child) exit(main->child);

      return 0;
    }

    f_thread_condition_signal_all(&entry->global->thread->lock.alert_condition);

    return 0;
  }
#endif // _di_controller_thread_entry_

#ifndef _di_controller_thread_exit_
  void * controller_thread_exit(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_entry_t *entry = (controller_main_entry_t *) arguments;

    controller_main_t *main = entry->global->main;
    controller_cache_t *cache = &entry->global->thread->cache;
    f_status_t *status = &entry->global->thread->status;

    *status = controller_entry_read(*entry->global, F_false, cache);

    if (F_status_set_fine(*status) == F_interrupt) {
      entry->setting->ready = controller_setting_ready_abort_e;
    }
    else if (F_status_is_error(*status)) {
      entry->setting->ready = controller_setting_ready_fail_e;
    }
    else if (*status == F_file_found_not) {
      entry->setting->ready = controller_setting_ready_done_e;
    }
    else if (*status != F_child) {
      *status = controller_entry_preprocess(*entry->global, F_false, cache);
    }

    if (F_status_is_error_not(*status) && *status != F_child && *status != F_file_found_not) {
      if (main->parameters.array[controller_parameter_validate_e].result == f_console_result_none_e || main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e) {

        *status = controller_entry_process(entry->global, cache, F_false, F_false);

        if (F_status_is_error(*status)) {
          entry->setting->ready = controller_setting_ready_fail_e;

          if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && entry->global->setting->failsafe_enabled) {

            const uint8_t original_enabled = entry->global->thread->enabled;

            // Restore operating mode so that the failsafe can execute.
            if (F_status_set_fine(*status) == F_execute) {
              *status = f_thread_mutex_lock(&entry->global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                entry->global->thread->enabled = controller_thread_enabled_exit_e;

                f_thread_mutex_unlock(&entry->global->thread->lock.alert);
              }

              // Restart the signal thread to allow for signals while operating the failsafe Items.
              if (!entry->global->thread->id_signal) {
                f_thread_create(0, &entry->global->thread->id_signal, &controller_thread_signal_other, (void *) entry->global);
              }
            }

            const f_status_t status_failsafe = controller_entry_process(entry->global, cache, F_true, F_false);

            if (F_status_is_error(status_failsafe)) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(main->error.to, entry->global->thread);

                fl_print_format("%q%[%QFailed while processing requested failsafe item '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, entry->global->setting->entry.items.array[entry->global->setting->failsafe_enabled].name, main->error.notable);
                fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                controller_unlock_print_flush(main->error.to, entry->global->thread);
              }

              *status = F_status_set_error(F_failure);
            }
            else {

              // Restore operating mode to value prior to failsafe mode.
              *status = f_thread_mutex_lock(&entry->global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                entry->global->thread->enabled = original_enabled;

                f_thread_mutex_unlock(&entry->global->thread->lock.alert);
              }

              *status = F_failure;
            }
          }
        }
        else if (F_status_set_fine(*status) == F_interrupt) {
          entry->setting->ready = controller_setting_ready_abort_e;
        }
        else if (*status != F_child) {
          entry->setting->ready = controller_setting_ready_done_e;
        }
      }
    }

    if (*status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      // Deallocate as much as possible.

      controller_thread_delete_simple(entry->global->thread);
      controller_setting_delete_simple(entry->global->setting);
      controller_main_delete(entry->global->main);

      return 0;
    }

    if (F_status_is_error_not(f_thread_mutex_lock(&entry->global->thread->lock.alert))) {
      entry->global->thread->enabled = controller_thread_enabled_not_e;

      f_thread_mutex_unlock(&entry->global->thread->lock.alert);
    }

    f_thread_condition_signal_all(&entry->global->thread->lock.alert_condition);

    return 0;
  }
#endif // _di_controller_thread_exit_

#ifdef __cplusplus
} // extern "C"
#endif
