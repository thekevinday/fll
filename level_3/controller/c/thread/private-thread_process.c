#include "../controller.h"
#include "../common/private-common.h"
#include "../controller/private-controller.h"
#include "../controller/private-controller_print.h"
#include "../rule/private-rule.h"
#include "private-thread.h"
#include "private-thread_entry.h"
#include "private-thread_process.h"
#include "private-thread_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_process_
  void controller_thread_process(const bool is_normal, controller_data_t * const process) {

    {
      controller_thread_t *thread = (controller_thread_t *) process->main_thread;

      if (!controller_thread_is_enabled(is_normal, thread)) return;
    }

    const f_status_t status = controller_rule_process_do(controller_process_option_asynchronous_d, process);

    if (status == F_child) {

      // A forked child process should deallocate memory on exit.
      // It seems that this function doesn't return to the calling thread for a forked child process, even with the "return 0;" below.
      // Deallocate as much as possible.
      controller_main_t *main = (controller_main_t *) process->main_data;
      controller_process_t *setting = (controller_process_t *) process->main_setting;
      controller_thread_t *thread = (controller_thread_t *) process->main_thread;

      controller_thread_delete_simple(thread);
      controller_process_delete(setting);
      controller_main_delete(main);

      // According to the manpages, pthread_exit() calls exit(0), which is not good because a non-zero exit code may be returned.
      if (main->program.child) exit(main->program.child);
    }
  }
#endif // _di_controller_thread_process_

#ifndef _di_controller_thread_process_cancel_
  void controller_thread_process_cancel(const controller_global_t global, const bool is_normal, const uint8_t by) {

    f_thread_mutex_lock(&global.thread->lock.cancel);

    // Only cancel when enabled.
    if (!controller_thread_is_enabled(is_normal, global.thread)) {
      f_thread_mutex_unlock(&global.thread->lock.cancel);

      return;
    }

    struct timespec time;

    controller_entry_t *entry = 0;
    controller_data_t *process = 0;

    f_status_t status = F_okay;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    pid_t pid = 0;

    if (is_normal) {
      entry = &global.setting->entry;
    }
    else {
      entry = &global.setting->exit;
    }

    // A simple but inaccurate interval counter (expect this to be replaced in the future).
    const f_number_unsigned_t interval_nanoseconds = entry->timeout_exit < 1000 ? (entry->timeout_exit < 100 ? 5000000 : 100000000) : 500000000;
    const f_number_unsigned_t interval_milliseconds = entry->timeout_exit < 1000 ? (entry->timeout_exit < 100 ? 5 : 100) : 500;

    time.tv_sec = 0;
    time.tv_nsec = interval_nanoseconds;

    if (global.setting->mode == controller_setting_mode_helper_e && global.main->program.parameters.array[controller_parameter_validate_e].result == f_console_result_none_e) {
      int value = 0;
      f_number_unsigned_t lapsed = 0;

      for (i = 0; i < global.thread->processs.used; ++i) {

        if (!global.thread->processs.array[i]) continue;
        //if (caller && i == caller->id) continue; // @fixme "caller" disappeared at some point.

        process = global.thread->processs.array[i];

        if (!process->id_thread) continue;

        controller_thread_detach(&process->id_thread);

        process->id_thread = 0;
      } // for
    }

    // Use the alert lock to toggle enabled (using it as if it is a write like and a signal lock).
    status = f_thread_mutex_lock(&global.thread->lock.alert);

    if (F_status_is_error(status)) {
      global.thread->enabled = controller_thread_enabled_not_e;
    }
    else {
      if (by == controller_thread_cancel_execute_e) {
        global.thread->enabled = controller_thread_enabled_execute_e;
      }
      else if (by == controller_thread_cancel_exit_e) {
        global.thread->enabled = controller_thread_enabled_not_e;
      }
      else if (by == controller_thread_cancel_exit_execute_e) {
        global.thread->enabled = controller_thread_enabled_exit_execute_e;
      }
      else {
        global.thread->enabled = controller_thread_enabled_exit_e;
      }

      f_thread_mutex_unlock(&global.thread->lock.alert);
    }

    if (global.thread->id_cleanup) {
      f_thread_cancel(global.thread->id_cleanup);
      f_thread_join(global.thread->id_cleanup, 0);

      global.thread->id_cleanup = 0;
    }

    if (global.thread->id_control) {
      f_thread_cancel(global.thread->id_control);
      f_thread_join(global.thread->id_control, 0);

      global.thread->id_control = 0;
    }

    // The sigtimedwait() function that is run inside of signal must be interrupted via the f_thread_cancel().
    if (by != controller_thread_cancel_signal_e && global.thread->id_signal) {
      f_thread_cancel(global.thread->id_signal);
      f_thread_join(global.thread->id_signal, 0);

      global.thread->id_signal = 0;
    }

    if (global.setting->mode == controller_setting_mode_helper_e && global.main->program.parameters.array[controller_parameter_validate_e].result == f_console_result_none_e) {
      f_thread_mutex_unlock(&global.thread->lock.cancel);

      return;
    }

    for (; i < global.thread->processs.used; ++i) {

      if (!global.thread->processs.array[i]) continue;

      process = global.thread->processs.array[i];

      // Do not cancel exit processes, when not performing "execute" during exit.
      if (process->type == controller_data_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) {
        continue;
      }

      for (j = 0; j < process->childs.used; ++j) {

        if (process->childs.array[j] > 0) {
          f_signal_send(global.thread->signal ? global.thread->signal : F_signal_termination, process->childs.array[j]);
        }
      } // for

      for (j = 0; j < process->path_pids.used; ++j) {

        if (process->path_pids.array[j].used && f_file_exists(process->path_pids.array[j], F_true) == F_true) {
          status = controller_file_pid_read(process->path_pids.array[j], &pid);

          if (pid) {
            f_signal_send(global.thread->signal ? global.thread->signal : F_signal_termination, pid);
          }
        }
      } // for
    } // for

    if (entry->timeout_exit && !(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
      f_number_unsigned_t lapsed = 0;

      for (i = 0; i < global.thread->processs.used && lapsed < entry->timeout_exit; ++i) {

        if (!global.thread->processs.array[i]) continue;

        process = global.thread->processs.array[i];

        // Do not wait for processes, when not performing "execute" during exit.
        if (process->type == controller_data_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) {
          continue;
        }

        for (j = 0; j < process->childs.used && lapsed < entry->timeout_exit; ++j) {

          while (process->childs.array[j] > 0 && lapsed < entry->timeout_exit) {

            // A hackish way to determine if the child process exists while waiting.
            if (getpgid(process->childs.array[j]) >= 0) {
              time.tv_sec = 0;
              time.tv_nsec = interval_nanoseconds;

              nanosleep(&time, 0);

              lapsed += interval_milliseconds;
            }
            else {
              process->childs.array[j] = 0;

              break;
            }
          } // while
        } // for

        for (j = 0; j < process->path_pids.used && lapsed < entry->timeout_exit; ++j) {

          if (process->path_pids.array[j].used && f_file_exists(process->path_pids.array[j], F_true) == F_true) {
            status = controller_file_pid_read(process->path_pids.array[j], &pid);

            if (pid) {
              while (lapsed < entry->timeout_exit) {

                // A hackish way to determine if the process exists while waiting.
                if (getpgid(pid) >= 0) {
                  time.tv_sec = 0;
                  time.tv_nsec = interval_nanoseconds;

                  nanosleep(&time, 0);

                  lapsed += interval_milliseconds;
                }
                else {
                  process->path_pids.array[j].used = 0;

                  break;
                }
              } // while
            }
          }
        } // for
      } // for
    }

    for (i = 0; i < global.thread->processs.size; ++i) {

      if (!global.thread->processs.array[i]) continue;

      process = global.thread->processs.array[i];

      // Do not kill exit processes, when not performing "execute" during exit.
      if (process->type == controller_data_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) continue;

      if (process->id_thread) {
        if (process->childs.used) {
          for (j = 0; j < process->childs.used; ++j) {

            if (process->childs.array[j] > 0) {
              f_signal_send(F_signal_kill, process->childs.array[j]);

              time.tv_sec = 0;
              time.tv_nsec = controller_thread_exit_process_cancel_wait_d;

              process->childs.array[j] = 0;
            }
          } // for

          nanosleep(&time, 0);
        }

        f_thread_join(process->id_thread, 0);

        process->id_thread = 0;
      }

      if (!(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
        for (j = 0; j < process->childs.size; ++j) {

          // Do not kill exit processes, when not performing "execute" during exit.
          if (process->type == controller_data_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) continue;

          if (process->childs.array[j]) {

            // A hackish way to determine if the child process exists, and if it does then forcibly terminate it.
            if (getpgid(process->childs.array[j]) >= 0) {
              f_signal_send(F_signal_kill, process->childs.array[j]);
            }

            process->childs.array[j] = 0;
          }
        } // for
      }

      if (!(entry->flag & controller_entry_flag_timeout_exit_no_e)) {
        for (j = 0; j < process->path_pids.used; ++j) {

          // Do not kill exit processes, when not performing "execute" during exit.
          if (process->type == controller_data_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) continue;

          if (f_file_exists(process->path_pids.array[j], F_true) == F_true) {
            status = controller_file_pid_read(process->path_pids.array[j], &pid);

            if (pid) {
              f_signal_send(F_signal_kill, pid);
            }

            f_file_remove(process->path_pids.array[j]);
            process->path_pids.array[j].used = 0;
          }
        } // for
      }

      // Shrink the child pids as much as possible.
      while (process->childs.used) {

        // Do not shrink below an exit processes, when not performing "execute" during exit.
        if (process->type == controller_data_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) break;
        if (process->childs.array[j] > 0) break;

        --process->childs.used;
      } // while

      // Shrink the path pids as much as possible.
      while (process->path_pids.used) {

        // Do not shrink below an exit processes, when not performing "execute" during exit.
        if (process->type == controller_data_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) break;
        if (process->path_pids.array[j].used) break;

        --process->path_pids.used;
      } // while
    } // for

    f_thread_mutex_unlock(&global.thread->lock.cancel);
  }
#endif // _di_controller_thread_process_cancel_

#ifndef _di_controller_thread_process_exit_
  void controller_thread_process_exit(controller_global_t * const global) {

    if (global->thread->enabled != controller_thread_enabled_exit_e) {
      return;
    }

    if (global->setting->ready == controller_setting_ready_done_e) {

      // The exit processing runs using the entry thread.
      if (global->thread->id_entry) {
        f_thread_cancel(global->thread->id_entry);
        f_thread_join(global->thread->id_entry, 0);

        global->thread->id_entry = 0;
      }

      // Restart the signal thread to allow for signals while operating the Exit.
      if (!global->thread->id_signal) {
        f_thread_create(0, &global->thread->id_signal, &controller_thread_signal_other, (void *) global);
      }

      const controller_main_entry_t entry = macro_controller_main_entry_t_initialize_1(global, global->setting);

      f_status_t status = f_thread_create(0, &global->thread->id_entry, &controller_thread_exit, (void *) &entry);

      if (F_status_is_error(status)) {
        if (global->main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_print_error(global->thread, global->main->program.error, F_status_set_fine(status), "f_thread_create", F_true);
        }

        if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
          global->thread->enabled = controller_thread_enabled_not_e;

          f_thread_mutex_unlock(&global->thread->lock.alert);
        }
        else {
          global->thread->enabled = controller_thread_enabled_not_e;
        }
      }
      else {
        struct timespec time;

        do {
          status = f_thread_mutex_lock(&global->thread->lock.alert);

          if (F_status_is_error(status)) {
            global->thread->enabled = controller_thread_enabled_not_e;

            break;
          }

          controller_time(controller_thread_exit_ready_timeout_seconds_d, controller_thread_exit_ready_timeout_nanoseconds_d, &time);

          status = f_thread_condition_wait_timed(&time, &global->thread->lock.alert_condition, &global->thread->lock.alert);

          f_thread_mutex_unlock(&global->thread->lock.alert);

        } while (F_status_is_error_not(status) && global->thread->enabled == controller_thread_enabled_exit_e);

        if (F_status_is_error(status)) {
          if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
            global->thread->enabled = controller_thread_enabled_not_e;

            f_thread_mutex_unlock(&global->thread->lock.alert);
          }
          else {
            global->thread->enabled = controller_thread_enabled_not_e;
          }
        }
      }

      // The sigtimedwait() function that is run inside of signal must be interrupted via the f_thread_cancel().
      if (global->thread->id_signal) {
        f_thread_cancel(global->thread->id_signal);
        f_thread_join(global->thread->id_signal, 0);

        global->thread->id_signal = 0;
      }

      controller_thread_process_cancel(*global, F_false, controller_thread_cancel_exit_e);
    }
    else {
      if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
        global->thread->enabled = controller_thread_enabled_not_e;

        f_thread_mutex_unlock(&global->thread->lock.alert);
      }
      else {
        global->thread->enabled = controller_thread_enabled_not_e;
      }
    }
  }
#endif // _di_controller_thread_process_exit_

#ifndef _di_controller_thread_process_normal_
  void * controller_thread_process_normal(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_process(F_true, (controller_data_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_process_normal_

#ifndef _di_controller_thread_process_other_
  void * controller_thread_process_other(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_process(F_false, (controller_data_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_process_other_

#ifdef __cplusplus
} // extern "C"
#endif
