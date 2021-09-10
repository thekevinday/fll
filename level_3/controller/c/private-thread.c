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

    const controller_global_t *global = (controller_global_t *) arguments;

    if (global->thread->enabled != controller_thread_enabled) return 0;

    const unsigned int interval = global->main->parameters[controller_parameter_simulate].result == f_console_result_found ? controller_thread_cleanup_interval_short : controller_thread_cleanup_interval_long;

    f_status_t status = F_none;

    while (global->thread->enabled == controller_thread_enabled) {

      sleep(interval);

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
                controller_lock_error_critical_print(global->main->error, F_status_set_fine(status), F_false, global->thread);

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

#ifndef _di_controller_thread_control_
  void * controller_thread_control(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_global_t *global = (controller_global_t *) arguments;

    if (global->thread->enabled != controller_thread_enabled) return 0;

    return 0;
  }
#endif // _di_controller_thread_control_

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
        controller_error_print(main->error, F_status_set_fine(status), "controller_processs_increase", F_true, &thread);
      }
    }

    if (F_status_is_error_not(status)) {
      status = f_thread_create(0, &thread.id_signal, &controller_thread_signal_normal, (void *) &global);
    }

    if (F_status_is_error(status)) {
      thread.id_signal = 0;

      if (main->error.verbosity != f_console_verbosity_quiet) {
        controller_error_print(main->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
      }
    }
    else {
      if (main->parameters[controller_parameter_daemon].result == f_console_result_found) {

        setting->ready = controller_setting_ready_done;

        if (f_file_exists(setting->path_pid.string) == F_true) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&thread.lock.print);

            flockfile(main->error.to.stream);

            fl_print_format("%c%[%SThe pid file '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
            fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, setting->path_pid.string, main->error.notable);
            fl_print_format("%[' must not already exist.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);

            controller_print_unlock_flush(main->error.to.stream, &thread.lock.print);
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
            controller_error_print(main->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
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
              controller_error_print(main->error, F_status_set_fine(status), "f_thread_create", F_true, &thread);
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
        controller_rule_wait_all(F_true, global, F_false, 0);
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

#ifndef _di_controller_thread_process_
  void controller_thread_process(const bool is_normal, controller_process_t *process) {

    {
      controller_thread_t *thread = (controller_thread_t *) process->main_thread;

      if (!controller_thread_is_enabled(is_normal, thread)) return;
    }

    const f_status_t status = controller_rule_process_do(controller_process_option_asynchronous, process);

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
    }
  }
#endif // _di_controller_thread_process_

#ifndef _di_controller_thread_process_normal_
  void * controller_thread_process_normal(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_process(F_true, (controller_process_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_process_normal_

#ifndef _di_controller_thread_process_other_
  void * controller_thread_process_other(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_process(F_false, (controller_process_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_process_other_

#ifndef _di_controller_thread_process_cancel_
  void controller_thread_process_cancel(const bool is_normal, const uint8_t by, controller_global_t *global, controller_process_t *caller) {

    // only cancel when enabled.
    if (!controller_thread_is_enabled(is_normal, global->thread)) {
      return;
    }

    // use the alert lock to toggle enabled (being used as if it were a write like and signal lock).
    f_status_t status = f_thread_mutex_lock(&global->thread->lock.alert);

    if (F_status_is_error(status)) {
      global->thread->enabled = controller_thread_enabled_not;
    }
    else {
      if (by == controller_thread_cancel_execute) {
        global->thread->enabled = controller_thread_enabled_execute;
      }
      else if (by == controller_thread_cancel_exit) {
        global->thread->enabled = controller_thread_enabled_not;
      }
      else if (by == controller_thread_cancel_exit_execute) {
        global->thread->enabled = controller_thread_enabled_exit_execute;
      }
      else {
        global->thread->enabled = controller_thread_enabled_exit;
      }

      f_thread_mutex_unlock(&global->thread->lock.alert);
    }

    f_array_length_t spent = 0;

    struct timespec time;

    controller_process_t *process = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    pid_t pid = 0;

    // the sleep() function that is run inside the cleanup function must be interrupted via the f_thread_cancel().
    // @todo consider switching to nanosleep() which may act better with interrupts and not require f_thread_cancel().
    if (global->thread->id_cleanup) {
      f_thread_cancel(global->thread->id_cleanup);
      f_thread_join(global->thread->id_cleanup, 0);

      global->thread->id_cleanup = 0;
    }

    // the sigtimedwait() function that is run inside of signal must be interrupted via the f_thread_cancel().
    if (by != controller_thread_cancel_signal && global->thread->id_signal) {
      f_thread_cancel(global->thread->id_signal);
      f_thread_join(global->thread->id_signal, 0);

      global->thread->id_signal = 0;
    }

    for (; i < global->thread->processs.used; ++i) {

      if (!global->thread->processs.array[i]) continue;
      if (caller && i == caller->id) continue;

      process = global->thread->processs.array[i];

      // do not cancel exit processes, when not performing "execute" during exit.
      if (process->type == controller_process_type_exit && global->thread->enabled != controller_thread_enabled_exit_execute) {
        continue;
      }

      for (j = 0; j < process->childs.used; ++j) {

        if (process->childs.array[j] > 0) {
          f_signal_send(F_signal_termination, process->childs.array[j]);
        }
      } // for

      for (j = 0; j < process->path_pids.used; ++j) {

        if (process->path_pids.array[j].used && f_file_exists(process->path_pids.array[j].string) == F_true) {
          status = controller_file_pid_read(process->path_pids.array[j], &pid);

          if (pid) {
            f_signal_send(F_signal_termination, pid);
          }
        }
      } // for
    } // for

    for (i = 0; i < global->thread->processs.size && spent < controller_thread_exit_process_cancel_total; ++i) {

      if (!global->thread->processs.array[i]) continue;
      if (caller && i == caller->id) continue;

      process = global->thread->processs.array[i];

      // do not cancel exit processes, when not performing "execute" during exit.
      if (process->type == controller_process_type_exit && global->thread->enabled != controller_thread_enabled_exit_execute) continue;

      do {
        if (!process->id_thread) break;

        controller_time(0, controller_thread_exit_process_cancel_wait, &time);

        status = f_thread_join_timed(process->id_thread, time, 0);

        if (status == F_none) {
          for (j = 0; j < process->childs.size; ++j) {
            process->childs.array[j] = 0;
          } // for

          process->childs.used = 0;
          process->id_thread = 0;
        }

        ++spent;

      } while (status == F_time && spent < controller_thread_exit_process_cancel_total);

      if (process->path_pids.used) {
        for (j = 0; j < process->path_pids.used; ++j) {

          for (; spent < controller_thread_exit_process_cancel_total; ++spent) {

            if (process->path_pids.array[j].used && f_file_exists(process->path_pids.array[j].string) == F_true) {
              status = controller_file_pid_read(process->path_pids.array[j], &pid);

              if (pid) {

                // a hackish way to determine if the pid exists while waiting.
                if (getpgid(pid) >= 0) {
                  time.tv_sec = 0;
                  time.tv_nsec = controller_thread_exit_process_cancel_wait;

                  nanosleep(&time, 0);
                  continue;
                }
                else {
                  f_file_remove(process->path_pids.array[j].string);
                  process->path_pids.array[j].used = 0;
                }
              }
            }

            break;
          } // for
        } // for
      }
    } // for

    for (i = 0; i < global->thread->processs.size; ++i) {

      if (!global->thread->processs.array[i]) continue;
      if (caller && i == caller->id) continue;

      process = global->thread->processs.array[i];

      // do not kill exit processes, when not performing "execute" during exit.
      if (process->type == controller_process_type_exit && global->thread->enabled != controller_thread_enabled_exit_execute) continue;

      if (process->id_thread) {
        if (process->childs.used) {
          for (j = 0; j < process->childs.used; ++j) {

            if (process->childs.array[j] > 0) {
              f_signal_send(F_signal_kill, process->childs.array[j]);

              time.tv_sec = 0;
              time.tv_nsec = controller_thread_exit_process_cancel_wait;

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

        if (f_file_exists(process->path_pids.array[j].string) == F_true) {
          status = controller_file_pid_read(process->path_pids.array[j], &pid);

          if (pid) {
            f_signal_send(F_signal_kill, pid);
          }

          f_file_remove(process->path_pids.array[j].string);
          process->path_pids.array[j].used = 0;
        }
      } // for

      process->path_pids.used = 0;
    } // for
  }
#endif // _di_controller_thread_process_cancel_

#ifndef _di_controller_thread_process_exit_
  void controller_thread_process_exit(controller_global_t *global) {

    if (global->thread->enabled != controller_thread_enabled_exit) {
      return;
    }

    if (global->setting->ready == controller_setting_ready_done) {

      // the exit processing runs using the entry thread.
      if (global->thread->id_entry) {
        f_thread_cancel(global->thread->id_entry);
        f_thread_join(global->thread->id_entry, 0);

        global->thread->id_entry = 0;
      }

      // restart the signal thread to allow for signals while operating the Exit.
      if (!global->thread->id_signal) {
        f_thread_create(0, &global->thread->id_signal, &controller_thread_signal_other, (void *) global);
      }

      const controller_main_entry_t entry = macro_controller_main_entry_t_initialize(global, global->setting);

      f_status_t status = f_thread_create(0, &global->thread->id_entry, &controller_thread_exit, (void *) &entry);

      if (F_status_is_error(status)) {
        if (global->main->error.verbosity != f_console_verbosity_quiet) {
          controller_error_print(global->main->error, F_status_set_fine(status), "f_thread_create", F_true, global->thread);
        }

        if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
          global->thread->enabled = controller_thread_enabled_not;

          f_thread_mutex_unlock(&global->thread->lock.alert);
        }
        else {
          global->thread->enabled = controller_thread_enabled_not;
        }
      }
      else {
        struct timespec time;

        do {
          status = f_thread_mutex_lock(&global->thread->lock.alert);

          if (F_status_is_error(status)) {
            global->thread->enabled = controller_thread_enabled_not;

            break;
          }

          controller_time(controller_thread_exit_ready_timeout_seconds, controller_thread_exit_ready_timeout_nanoseconds, &time);

          status = f_thread_condition_wait_timed(&time, &global->thread->lock.alert_condition, &global->thread->lock.alert);

          f_thread_mutex_unlock(&global->thread->lock.alert);

        } while (F_status_is_error_not(status) && global->thread->enabled == controller_thread_enabled_exit);

        if (F_status_is_error(status)) {
          if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
            global->thread->enabled = controller_thread_enabled_not;

            f_thread_mutex_unlock(&global->thread->lock.alert);
          }
          else {
            global->thread->enabled = controller_thread_enabled_not;
          }
        }
      }

      // the sigtimedwait() function that is run inside of signal must be interrupted via the f_thread_cancel().
      if (global->thread->id_signal) {
        f_thread_cancel(global->thread->id_signal);
        f_thread_join(global->thread->id_signal, 0);

        global->thread->id_signal = 0;
      }

      controller_thread_process_cancel(F_false, controller_thread_cancel_exit, global, 0);
    }
    else {
      if (F_status_is_error_not(f_thread_mutex_lock(&global->thread->lock.alert))) {
        global->thread->enabled = controller_thread_enabled_not;

        f_thread_mutex_unlock(&global->thread->lock.alert);
      }
      else {
        global->thread->enabled = controller_thread_enabled_not;
      }
    }
  }
#endif // _di_controller_thread_process_exit_

#ifndef _di_controller_thread_entry_
  void * controller_thread_entry(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_entry_t *entry = (controller_main_entry_t *) arguments;

    if (!controller_thread_is_enabled(F_true, entry->global->thread)) return 0;

    controller_main_t *main = entry->global->main;
    controller_cache_t *cache = &entry->global->thread->cache;
    f_status_t *status = &entry->global->thread->status;

    *status = controller_entry_read(F_true, *entry->global, cache);

    if (F_status_is_error(*status)) {
      entry->setting->ready = controller_setting_ready_fail;
    }
    else if (*status != F_signal && *status != F_child) {
      *status = controller_preprocess_entry(F_true, *entry->global, cache);
    }

    if (F_status_is_error_not(*status) && *status != F_signal && *status != F_child) {
      if (main->parameters[controller_parameter_validate].result == f_console_result_none || main->parameters[controller_parameter_simulate].result == f_console_result_found) {

        if (f_file_exists(entry->setting->path_pid.string) == F_true) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&entry->global->thread->lock.print);

            flockfile(main->error.to.stream);

            fl_print_format("%c%[%SThe pid file '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
            fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, entry->setting->path_pid, main->error.notable);
            fl_print_format("%[' must not already exist.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);

            controller_print_unlock_flush(main->error.to.stream, &entry->global->thread->lock.print);
          }

          entry->setting->ready = controller_setting_ready_fail;
          *status = F_status_set_error(F_available_not);
        }
        else {
          *status = controller_process_entry(F_false, F_true, entry->global, cache);

          if (F_status_is_error(*status)) {
            entry->setting->ready = controller_setting_ready_fail;

            if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && entry->global->setting->failsafe_enabled) {

              const uint8_t original_enabled = entry->global->thread->enabled;

              // restore operating mode so that the failsafe can execute.
              *status = f_thread_mutex_lock(&entry->global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                entry->global->thread->enabled = controller_thread_enabled;

                f_thread_mutex_unlock(&entry->global->thread->lock.alert);
              }

              // restart the signal thread to allow for signals while operating the failsafe Items.
              if (!entry->global->thread->id_signal) {
                f_thread_create(0, &entry->global->thread->id_signal, &controller_thread_signal_normal, (void *) entry->global);
              }

              const f_status_t status_failsafe = controller_process_entry(F_true, F_true, entry->global, cache);

              if (F_status_is_error(status_failsafe)) {
                if (main->error.verbosity != f_console_verbosity_quiet) {
                  f_thread_mutex_lock(&entry->global->thread->lock.print);

                  flockfile(main->error.to.stream);

                  fl_print_format("%c%[%SFailed while processing requested failsafe item '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
                  fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, entry->global->setting->entry.items.array[entry->global->setting->failsafe_enabled].name, main->error.notable);
                  fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

                  funlockfile(main->error.to.stream);

                  controller_print_unlock_flush(main->error.to.stream, &entry->global->thread->lock.print);
                }

                *status = F_status_set_error(F_failure);
              }
              else {

                // restore operating mode to value prior to failsafe mode.
                *status = f_thread_mutex_lock(&entry->global->thread->lock.alert);

                if (F_status_is_error_not(*status)) {
                  entry->global->thread->enabled = original_enabled;

                  f_thread_mutex_unlock(&entry->global->thread->lock.alert);
                }

                *status = F_failure;
              }
            }
          }
          else if (*status == F_signal) {
            entry->setting->ready = controller_setting_ready_abort;
          }
          else if (*status != F_child) {
            entry->setting->ready = controller_setting_ready_done;
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

      return 0;
    }

    f_thread_condition_signal_all(&entry->global->thread->lock.alert_condition);

    return 0;
  }
#endif // _di_controller_thread_entry_

#ifndef _di_controller_thread_exit_
  void * controller_thread_exit(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_main_entry_t *entry = (controller_main_entry_t *) arguments;

    controller_main_t *main = entry->global->main;
    controller_cache_t *cache = &entry->global->thread->cache;
    f_status_t *status = &entry->global->thread->status;

    *status = controller_entry_read(F_false, *entry->global, cache);

    if (F_status_is_error(*status)) {
      entry->setting->ready = controller_setting_ready_fail;
    }
    else if (*status == F_file_found_not) {
      entry->setting->ready = controller_setting_ready_done;
    }
    else if (*status != F_signal && *status != F_child) {
      *status = controller_preprocess_entry(F_false, *entry->global, cache);
    }

    if (F_status_is_error_not(*status) && *status != F_signal && *status != F_child && *status != F_file_found_not) {
      if (main->parameters[controller_parameter_validate].result == f_console_result_none || main->parameters[controller_parameter_simulate].result == f_console_result_found) {

        *status = controller_process_entry(F_false, F_false, entry->global, cache);

        if (F_status_is_error(*status)) {
          entry->setting->ready = controller_setting_ready_fail;

          if ((F_status_set_fine(*status) == F_execute || F_status_set_fine(*status) == F_require) && entry->global->setting->failsafe_enabled) {

            const uint8_t original_enabled = entry->global->thread->enabled;

            // restore operating mode so that the failsafe can execute.
            if (F_status_set_fine(*status) == F_execute) {
              *status = f_thread_mutex_lock(&entry->global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                entry->global->thread->enabled = controller_thread_enabled_exit;

                f_thread_mutex_unlock(&entry->global->thread->lock.alert);
              }

              // restart the signal thread to allow for signals while operating the failsafe Items.
              if (!entry->global->thread->id_signal) {
                f_thread_create(0, &entry->global->thread->id_signal, &controller_thread_signal_other, (void *) entry->global);
              }
            }

            const f_status_t status_failsafe = controller_process_entry(F_true, F_false, entry->global, cache);

            if (F_status_is_error(status_failsafe)) {
              if (main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&entry->global->thread->lock.print);

                flockfile(main->error.to.stream);

                fl_print_format("%c%[%SFailed while processing requested failsafe item '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
                fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, entry->global->setting->entry.items.array[entry->global->setting->failsafe_enabled].name, main->error.notable);
                fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

                funlockfile(main->error.to.stream);

                controller_print_unlock_flush(main->error.to.stream, &entry->global->thread->lock.print);
              }

              *status = F_status_set_error(F_failure);
            }
            else {

              // restore operating mode to value prior to failsafe mode.
              *status = f_thread_mutex_lock(&entry->global->thread->lock.alert);

              if (F_status_is_error_not(*status)) {
                entry->global->thread->enabled = original_enabled;

                f_thread_mutex_unlock(&entry->global->thread->lock.alert);
              }

              *status = F_failure;
            }
          }
        }
        else if (*status == F_signal) {
          entry->setting->ready = controller_setting_ready_abort;
        }
        else if (*status != F_child) {
          entry->setting->ready = controller_setting_ready_done;
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
      entry->global->thread->enabled = controller_thread_enabled_not;

      f_thread_mutex_unlock(&entry->global->thread->lock.alert);
    }

    f_thread_condition_signal_all(&entry->global->thread->lock.alert_condition);

    return 0;
  }
#endif // _di_controller_thread_exit_

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

#ifndef _di_controller_thread_rule_
  void * controller_thread_rule(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_global_t *global = (controller_global_t *) arguments;

    if (!controller_thread_is_enabled(F_true, global->thread)) return 0;

    return 0;
  }
#endif // _di_controller_thread_rule_

#ifndef _di_controller_thread_signal_
  void controller_thread_signal(const bool is_normal, controller_global_t *global) {

    if (!controller_thread_is_enabled(is_normal, global->thread)) return;

    siginfo_t information;
    struct timespec time;
    int error = 0;

    while (controller_thread_is_enabled(is_normal, global->thread)) {

      controller_time(controller_thread_exit_ready_timeout_seconds, controller_thread_exit_ready_timeout_nanoseconds, &time);

      error = sigtimedwait(&global->main->signal.set, &information, &time);

      if (error == -1) {
        if (errno == EAGAIN) continue;
      }

      if (global->setting->interruptable) {
        if (information.si_signo == F_signal_interrupt || information.si_signo == F_signal_abort || information.si_signo == F_signal_quit || information.si_signo == F_signal_termination) {

          global->thread->signal = information.si_signo;

          controller_thread_process_cancel(is_normal, controller_thread_cancel_signal, global, 0);

          break;
        }
      }
    } // while
  }
#endif // _di_controller_thread_signal_

#ifndef _di_controller_thread_signal_state_fss_
  f_status_t controller_thread_signal_state_fss(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t *state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    controller_state_interrupt_t *custom = (controller_state_interrupt_t *) state_ptr->custom;
    controller_thread_t *thread = custom->thread;

    if (!controller_thread_is_enabled(custom->is_normal, thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (thread->signal == F_signal_interrupt || thread->signal == F_signal_abort || thread->signal == F_signal_quit || thread->signal == F_signal_termination) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_controller_thread_signal_state_fss_

#ifndef _di_controller_thread_signal_state_iki_
  f_status_t controller_thread_signal_state_iki(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t *state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    controller_state_interrupt_t *custom = (controller_state_interrupt_t *) state_ptr->custom;
    controller_thread_t *thread = custom->thread;

    if (!controller_thread_is_enabled(custom->is_normal, thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (thread->signal == F_signal_interrupt || thread->signal == F_signal_abort || thread->signal == F_signal_quit || thread->signal == F_signal_termination) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_controller_thread_signal_state_iki_

#ifndef _di_controller_thread_signal_normal_
  void * controller_thread_signal_normal(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal(F_true, (controller_global_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_signal_normal_

#ifndef _di_controller_thread_signal_other_
  void * controller_thread_signal_other(void *arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    controller_thread_signal(F_false, (controller_global_t *) arguments);

    return 0;
  }
#endif // _di_controller_thread_signal_other_

#ifdef __cplusplus
} // extern "C"
#endif
