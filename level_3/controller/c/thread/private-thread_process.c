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
  void controller_thread_process(const bool is_normal, controller_process_t * const process) {

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
      controller_setting_t *setting = (controller_setting_t *) process->main_setting;
      controller_thread_t *thread = (controller_thread_t *) process->main_thread;

      controller_thread_delete_simple(thread);
      controller_setting_delete_simple(setting);
      controller_main_delete(main);

      // According to the manpages, pthread_exit() calls exit(0), which is not good because a non-zero exit code may be returned.
      if (main->child) exit(main->child);
    }
  }
#endif // _di_controller_thread_process_

#ifndef _di_controller_thread_process_cancel_
  void controller_thread_process_cancel(const controller_global_t global, const bool is_normal, const uint8_t by, controller_process_t * const caller) {

    // Only cancel when enabled.
    if (!controller_thread_is_enabled(is_normal, global.thread)) {
      return;
    }

    // Use the alert lock to toggle enabled (being used as if it were a write like and signal lock).
    f_status_t status = f_thread_mutex_lock(&global.thread->lock.alert);

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

    f_array_length_t spent = 0;

    struct timespec time;

    controller_process_t *process = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    pid_t pid = 0;

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

    for (; i < global.thread->processs.used; ++i) {

      if (!global.thread->processs.array[i]) continue;
      if (caller && i == caller->id) continue;

      process = global.thread->processs.array[i];

      // Do not cancel exit processes, when not performing "execute" during exit.
      if (process->type == controller_process_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) {
        continue;
      }

      for (j = 0; j < process->childs.used; ++j) {

        if (process->childs.array[j] > 0) {
          f_signal_send(global.thread->signal ? global.thread->signal : F_signal_termination, process->childs.array[j]);
        }
      } // for

      for (j = 0; j < process->path_pids.used; ++j) {

        if (process->path_pids.array[j].used && f_file_exists(process->path_pids.array[j]) == F_true) {
          status = controller_file_pid_read(process->path_pids.array[j], &pid);

          if (pid) {
            f_signal_send(global.thread->signal ? global.thread->signal : F_signal_termination, pid);
          }
        }
      } // for
    } // for

    for (i = 0; i < global.thread->processs.size && spent < controller_thread_exit_process_cancel_total_d; ++i) {

      if (!global.thread->processs.array[i]) continue;
      if (caller && i == caller->id) continue;

      process = global.thread->processs.array[i];

      // Do not cancel exit processes, when not performing "execute" during exit.
      if (process->type == controller_process_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) continue;

      do {
        if (!process->id_thread) break;

        f_thread_signal(process->id_thread, global.thread->signal ? global.thread->signal : F_signal_termination);

        controller_time(0, controller_thread_exit_process_cancel_wait_d, &time);

        status = f_thread_join_timed(process->id_thread, time, 0);

        if (status == F_none) {
          for (j = 0; j < process->childs.size; ++j) {
            process->childs.array[j] = 0;
          } // for

          process->childs.used = 0;
          process->id_thread = 0;
        }

        ++spent;

      } while (status == F_time && spent < controller_thread_exit_process_cancel_total_d);

      if (process->path_pids.used) {
        for (j = 0; j < process->path_pids.used; ++j) {

          for (; spent < controller_thread_exit_process_cancel_total_d; ++spent) {

            if (process->path_pids.array[j].used && f_file_exists(process->path_pids.array[j]) == F_true) {
              status = controller_file_pid_read(process->path_pids.array[j], &pid);

              if (pid) {

                // A hackish way to determine if the pid exists while waiting.
                if (getpgid(pid) >= 0) {
                  time.tv_sec = 0;
                  time.tv_nsec = controller_thread_exit_process_cancel_wait_d;

                  nanosleep(&time, 0);

                  continue;
                }
                else {
                  f_file_remove(process->path_pids.array[j]);
                  process->path_pids.array[j].used = 0;
                }
              }
            }

            break;
          } // for
        } // for
      }
    } // for

    for (i = 0; i < global.thread->processs.size; ++i) {

      if (!global.thread->processs.array[i]) continue;
      if (caller && i == caller->id) continue;

      process = global.thread->processs.array[i];

      // Do not kill exit processes, when not performing "execute" during exit.
      if (process->type == controller_process_type_exit_e && global.thread->enabled != controller_thread_enabled_exit_execute_e) continue;

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

      for (j = 0; j < process->childs.size; ++j) {
        process->childs.array[j] = 0;
      } // for

      process->childs.used = 0;

      for (j = 0; j < process->path_pids.used; ++j) {

        if (f_file_exists(process->path_pids.array[j]) == F_true) {
          status = controller_file_pid_read(process->path_pids.array[j], &pid);

          if (pid) {
            f_signal_send(F_signal_kill, pid);
          }

          f_file_remove(process->path_pids.array[j]);
          process->path_pids.array[j].used = 0;
        }
      } // for

      process->path_pids.used = 0;
    } // for
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

      const controller_main_entry_t entry = macro_controller_main_entry_t_initialize(global, global->setting);

      f_status_t status = f_thread_create(0, &global->thread->id_entry, &controller_thread_exit, (void *) &entry);

      if (F_status_is_error(status)) {
        if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_thread_create", F_true);
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

      controller_thread_process_cancel(*global, F_false, controller_thread_cancel_exit_e, 0);
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

    controller_thread_process(F_true, (controller_process_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_process_normal_

#ifndef _di_controller_thread_process_other_
  void * controller_thread_process_other(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_process(F_false, (controller_process_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_process_other_

#ifdef __cplusplus
} // extern "C"
#endif
