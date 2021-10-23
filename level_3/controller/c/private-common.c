#include "controller.h"
#include "private-common.h"
#include "private-thread.h"
#include "private-rule.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_string_s_
  const f_string_t controller_action_s = CONTROLLER_action_s;
  const f_string_t controller_actions_s = CONTROLLER_actions_s;
  const f_string_t controller_affinity_s = CONTROLLER_affinity_s;
  const f_string_t controller_as_s = CONTROLLER_as_s;
  const f_string_t controller_asynchronous_s = CONTROLLER_asynchronous_s;
  const f_string_t controller_bash_s = CONTROLLER_bash_s;
  const f_string_t controller_batch_s = CONTROLLER_batch_s;
  const f_string_t controller_capability_s = CONTROLLER_capability_s;
  const f_string_t controller_create_s = CONTROLLER_create_s;
  const f_string_t controller_command_s = CONTROLLER_command_s;
  const f_string_t controller_consider_s = CONTROLLER_consider_s;
  const f_string_t controller_control_s = CONTROLLER_control_s;
  const f_string_t controller_control_group_s = CONTROLLER_control_group_s;
  const f_string_t controller_cpu_s = CONTROLLER_cpu_s;
  const f_string_t controller_core_s = CONTROLLER_core_s;
  const f_string_t controller_data_s = CONTROLLER_data_s;
  const f_string_t controller_deadline_s = CONTROLLER_deadline_s;
  const f_string_t controller_default_s = CONTROLLER_default_s;
  const f_string_t controller_define_s = CONTROLLER_define_s;
  const f_string_t controller_delay_s = CONTROLLER_delay_s;
  const f_string_t controller_disable_s = CONTROLLER_disable_s;
  const f_string_t controller_entry_s = CONTROLLER_entry_s;
  const f_string_t controller_entries_s = CONTROLLER_entries_s;
  const f_string_t controller_environment_s = CONTROLLER_environment_s;
  const f_string_t controller_execute_s = CONTROLLER_execute_s;
  const f_string_t controller_existing_s = CONTROLLER_existing_s;
  const f_string_t controller_exit_s = CONTROLLER_exit_s;
  const f_string_t controller_exits_s = CONTROLLER_exits_s;
  const f_string_t controller_fail_s = CONTROLLER_fail_s;
  const f_string_t controller_failsafe_s = CONTROLLER_failsafe_s;
  const f_string_t controller_failure_s = CONTROLLER_failure_s;
  const f_string_t controller_fifo_s = CONTROLLER_fifo_s;
  const f_string_t controller_freeze_s = CONTROLLER_freeze_s;
  const f_string_t controller_fsize_s = CONTROLLER_fsize_s;
  const f_string_t controller_full_path_s = CONTROLLER_full_path_s;
  const f_string_t controller_group_s = CONTROLLER_group_s;
  const f_string_t controller_groups_s = CONTROLLER_groups_s;
  const f_string_t controller_how_s = CONTROLLER_how_s;
  const f_string_t controller_idle_s = CONTROLLER_idle_s;
  const f_string_t controller_item_s = CONTROLLER_item_s;
  const f_string_t controller_init_s = CONTROLLER_init_s;
  const f_string_t controller_kill_s = CONTROLLER_kill_s;
  const f_string_t controller_limit_s = CONTROLLER_limit_s;
  const f_string_t controller_locks_s = CONTROLLER_locks_s;
  const f_string_t controller_main_s = CONTROLLER_main_s;
  const f_string_t controller_max_s = CONTROLLER_max_s;
  const f_string_t controller_memlock_s = CONTROLLER_memlock_s;
  const f_string_t controller_method_s = CONTROLLER_method_s;
  const f_string_t controller_mode_s = CONTROLLER_mode_s;
  const f_string_t controller_msgqueue_s = CONTROLLER_msgqueue_s;
  const f_string_t controller_name_s = CONTROLLER_name_s;
  const f_string_t controller_need_s = CONTROLLER_need_s;
  const f_string_t controller_new_s = CONTROLLER_new_s;
  const f_string_t controller_nice_s = CONTROLLER_nice_s;
  const f_string_t controller_no_s = CONTROLLER_no_s;
  const f_string_t controller_nofile_s = CONTROLLER_nofile_s;
  const f_string_t controller_normal_s = CONTROLLER_normal_s;
  const f_string_t controller_nproc_s = CONTROLLER_nproc_s;
  const f_string_t controller_on_s = CONTROLLER_on_s;
  const f_string_t controller_optional_s = CONTROLLER_optional_s;
  const f_string_t controller_other_s = CONTROLLER_other_s;
  const f_string_t controller_parameter_s = CONTROLLER_parameter_s;
  const f_string_t controller_parameters_s = CONTROLLER_parameters_s;
  const f_string_t controller_path_s = CONTROLLER_path_s;
  const f_string_t controller_pause_s = CONTROLLER_pause_s;
  const f_string_t controller_pid_s = CONTROLLER_pid_s;
  const f_string_t controller_pid_file_s = CONTROLLER_pid_file_s;
  const f_string_t controller_processor_s = CONTROLLER_processor_s;
  const f_string_t controller_program_s = CONTROLLER_program_s;
  const f_string_t controller_ready_s = CONTROLLER_ready_s;
  const f_string_t controller_reload_s = CONTROLLER_reload_s;
  const f_string_t controller_require_s = CONTROLLER_require_s;
  const f_string_t controller_required_s = CONTROLLER_required_s;
  const f_string_t controller_rerun_s = CONTROLLER_rerun_s;
  const f_string_t controller_reset_s = CONTROLLER_reset_s;
  const f_string_t controller_restart_s = CONTROLLER_restart_s;
  const f_string_t controller_resume_s = CONTROLLER_resume_s;
  const f_string_t controller_round_robin_s = CONTROLLER_round_robin_s;
  const f_string_t controller_rss_s = CONTROLLER_rss_s;
  const f_string_t controller_rtprio_s = CONTROLLER_rtprio_s;
  const f_string_t controller_rttime_s = CONTROLLER_rttime_s;
  const f_string_t controller_rule_s = CONTROLLER_rule_s;
  const f_string_t controller_rules_s = CONTROLLER_rules_s;
  const f_string_t controller_same_s = CONTROLLER_same_s;
  const f_string_t controller_scheduler_s = CONTROLLER_scheduler_s;
  const f_string_t controller_script_s = CONTROLLER_script_s;
  const f_string_t controller_service_s = CONTROLLER_service_s;
  const f_string_t controller_setting_s = CONTROLLER_setting_s;
  const f_string_t controller_session_s = CONTROLLER_session_s;
  const f_string_t controller_session_new_s = CONTROLLER_session_new_s;
  const f_string_t controller_session_same_s = CONTROLLER_session_same_s;
  const f_string_t controller_show_s = CONTROLLER_show_s;
  const f_string_t controller_sigpending_s = CONTROLLER_sigpending_s;
  const f_string_t controller_stack_s = CONTROLLER_stack_s;
  const f_string_t controller_start_s = CONTROLLER_start_s;
  const f_string_t controller_stop_s = CONTROLLER_stop_s;
  const f_string_t controller_succeed_s = CONTROLLER_succeed_s;
  const f_string_t controller_success_s = CONTROLLER_success_s;
  const f_string_t controller_synchronous_s = CONTROLLER_synchronous_s;
  const f_string_t controller_thaw_s = CONTROLLER_thaw_s;
  const f_string_t controller_timeout_s = CONTROLLER_timeout_s;
  const f_string_t controller_type_s = CONTROLLER_type_s;
  const f_string_t controller_use_s = CONTROLLER_use_s;
  const f_string_t controller_user_s = CONTROLLER_user_s;
  const f_string_t controller_utility_s = CONTROLLER_utility_s;
  const f_string_t controller_value_s = CONTROLLER_value_s;
  const f_string_t controller_wait_s = CONTROLLER_wait_s;
  const f_string_t controller_want_s = CONTROLLER_want_s;
  const f_string_t controller_wish_s = CONTROLLER_wish_s;
  const f_string_t controller_with_s = CONTROLLER_with_s;
  const f_string_t controller_yes_s = CONTROLLER_yes_s;
#endif // _di_controller_string_s_

#ifndef _di_controller_cache_action_delete_simple_
  void controller_cache_action_delete_simple(controller_cache_action_t *cache) {

    f_string_dynamic_resize(0, &cache->name_action);
    f_string_dynamic_resize(0, &cache->name_file);
    f_string_dynamic_resize(0, &cache->name_item);
    f_string_dynamic_resize(0, &cache->generic);
    f_string_dynamic_resize(0, &cache->name_action);
  }
#endif // _di_controller_cache_action_delete_simple_

#ifndef _di_controller_cache_delete_simple_
  void controller_cache_delete_simple(controller_cache_t *cache) {

    macro_f_array_lengths_t_delete_simple(cache->ats)
    macro_f_array_lengths_t_delete_simple(cache->stack)
    macro_f_fss_delimits_t_delete_simple(cache->delimits)

    f_string_dynamic_resize(0, &cache->buffer_file);
    f_string_dynamic_resize(0, &cache->buffer_item);
    f_string_dynamic_resize(0, &cache->buffer_path);

    f_string_ranges_resize(0, &cache->comments);
    f_string_ranges_resize(0, &cache->content_action);
    f_string_ranges_resize(0, &cache->object_actions);
    f_string_ranges_resize(0, &cache->object_items);

    f_string_rangess_resize(0, &cache->content_actions);
    f_string_rangess_resize(0, &cache->content_items);

    controller_cache_action_delete_simple(&cache->action);
  }
#endif // _di_controller_cache_delete_simple_

#ifndef _di_controller_entry_action_delete_simple_
  void controller_entry_action_delete_simple(controller_entry_action_t *action) {

    f_string_dynamics_resize(0, &action->parameters);
  }
#endif // _di_controller_entry_action_delete_simple_

#ifndef _di_controller_entry_actions_delete_simple_
  void controller_entry_actions_delete_simple(controller_entry_actions_t *actions) {

    actions->used = actions->size;

    while (actions->used) {
      controller_entry_action_delete_simple(&actions->array[--actions->used]);
    } // while

    f_memory_delete(actions->size, sizeof(controller_entry_action_t), (void **) & actions->array);
    actions->size = 0;
  }
#endif // _di_controller_entry_actions_delete_simple_

#ifndef _di_controller_entry_item_delete_simple_
  void controller_entry_item_delete_simple(controller_entry_item_t *item) {

    f_string_dynamic_resize(0, &item->name);

    controller_entry_actions_delete_simple(&item->actions);
  }
#endif // _di_controller_entry_item_delete_simple_

#ifndef _di_controller_entry_items_delete_simple_
  void controller_entry_items_delete_simple(controller_entry_items_t *items) {

    items->used = items->size;

    while (items->used) {
      controller_entry_item_delete_simple(&items->array[--items->used]);
    } // while

    f_memory_delete(items->size, sizeof(controller_entry_item_t), (void **) & items->array);
    items->size = 0;
  }
#endif // _di_controller_entry_items_delete_simple_

#ifndef _di_controller_error_file_print_
  void controller_error_file_print(const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t name, const f_string_t operation, const uint8_t type, controller_thread_t *thread) {

    if (print.verbosity == f_console_verbosity_quiet) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_print_lock().
    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    fll_error_file_print(print, status, function, fallback, name, operation, type);

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_error_file_print_
#ifndef _di_controller_error_print_
  void controller_error_print(const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) {

    if (print.verbosity == f_console_verbosity_quiet) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_print_lock().
    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    fll_error_print(print, status, function, fallback);

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_error_print_

#ifndef _di_controller_lock_create_
  f_status_t controller_lock_create(controller_lock_t *lock) {

    f_status_t status = f_thread_mutex_create(0, &lock->print);
    if (F_status_is_error(status)) return status;

    status = f_thread_mutex_create(0, &lock->alert);
    if (F_status_is_error(status)) return status;

    status = f_thread_lock_create(0, &lock->process);
    if (F_status_is_error(status)) return status;

    status = f_thread_lock_create(0, &lock->rule);
    if (F_status_is_error(status)) return status;

    status = f_thread_condition_create(0, &lock->alert_condition);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_lock_create_

#ifndef _di_controller_lock_delete_mutex_
  void controller_lock_delete_mutex(f_thread_mutex_t *mutex) {

    const f_status_t status = f_thread_mutex_delete(mutex);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_busy) {
        if (f_thread_mutex_delete(mutex) == F_none) {
          mutex = 0;
        }
      }
    }
    else {
      mutex = 0;
    }
  }
#endif // _di_controller_lock_delete_mutex_

#ifndef _di_controller_lock_delete_rw_
  void controller_lock_delete_rw(f_thread_lock_t *lock) {

    const f_status_t status = f_thread_lock_delete(lock);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_busy) {
        if (f_thread_lock_delete(lock) == F_none) {
          lock = 0;
        }
      }
    }
    else {
      lock = 0;
    }
  }
#endif // _di_controller_lock_delete_rw_

#ifndef _di_controller_lock_delete_simple_
  void controller_lock_delete_simple(controller_lock_t *lock) {

    controller_lock_delete_mutex(&lock->print);
    controller_lock_delete_mutex(&lock->alert);

    controller_lock_delete_rw(&lock->process);
    controller_lock_delete_rw(&lock->rule);

    f_thread_condition_delete(&lock->alert_condition);
  }
#endif // _di_controller_lock_delete_simple_

#ifndef _di_controller_lock_error_critical_print_
  void controller_lock_error_critical_print(const fl_print_t print, const f_status_t status, const bool read, controller_thread_t *thread) {

    // A signal is not an error.
    if (status == F_signal) {
      return;
    }

    if (print.verbosity != f_console_verbosity_quiet) {
      controller_print_lock(print.to, thread);

      fl_print_format("%c%[%SThe pid file '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix ? print.prefix : f_string_empty_s, print.context);
      fl_print_format("%['Critical failure while attempting to establish '%]", print.to.stream, print.context, print.context);
      fl_print_format("%[%s lock%]", print.to.stream, print.notable, read ? "read" : "write", print.notable);

      if (status != F_failure) {
        fl_print_format(" %['due to%] ", print.to.stream, print.context, print.context);

        if (status == F_parameter) {
          fl_print_format("%[Invalid Parameter%]", print.to.stream, print.notable, print.notable);
        }
        else if (status == F_deadlock) {
          fl_print_format("%[Deadlock%]", print.to.stream, print.notable, print.notable);
        }
        else if (status == F_resource_not) {
          fl_print_format("%[Too Many Locks%]", print.to.stream, print.notable, print.notable);
        }
        else {
          fl_print_format("%[Unknown Error%]", print.to.stream, print.notable, print.notable);
        }
      }

      fl_print_format("%['.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);

      controller_print_unlock_flush(print.to, thread);
    }
  }
#endif // _di_controller_lock_error_critical_print_

#ifndef _di_controller_lock_read_
  f_status_t controller_lock_read(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) {

    struct timespec time;

    f_status_t status = F_none;

    for (;;) {

      controller_time(controller_thread_lock_read_timeout_seconds_d, controller_thread_lock_read_timeout_nanoseconds_d, &time);

      status = f_thread_lock_read_timed(&time, lock);

      if (status == F_time) {
        if (!controller_thread_is_enabled(is_normal, thread)) {
          return F_signal;
        }
      }
      else {
        break;
      }
    } // for

    return status;
  }
#endif // _di_controller_lock_read_

#ifndef _di_controller_lock_read_process_
  f_status_t controller_lock_read_process(controller_process_t * const process, controller_thread_t * const thread, f_thread_lock_t *lock) {

    return controller_lock_read_process_type(process->type, thread, lock);
  }
#endif // _di_controller_lock_read_process_

#ifndef _di_controller_lock_read_process_type_
  f_status_t controller_lock_read_process_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t *lock) {

    return controller_lock_read(type != controller_process_type_exit, thread, lock);
  }
#endif // _di_controller_lock_read_process_type_

#ifndef _di_controller_lock_write_
  f_status_t controller_lock_write(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) {

    struct timespec time;

    f_status_t status = F_none;

    for (;;) {

      controller_time(controller_thread_lock_write_timeout_seconds_d, controller_thread_lock_write_timeout_nanoseconds_d, &time);

      status = f_thread_lock_write_timed(&time, lock);

      if (status == F_time) {
        if (!controller_thread_is_enabled(is_normal, thread)) {
          return F_signal;
        }
      }
      else {
        break;
      }
    } // for

    return status;
  }
#endif // _di_controller_lock_write_

#ifndef _di_controller_lock_write_process_
  f_status_t controller_lock_write_process(controller_process_t * const process, controller_thread_t * const thread, f_thread_lock_t *lock) {

    return controller_lock_write_process_type(process->type, thread, lock);
  }
#endif // _di_controller_lock_write_process_

#ifndef _di_controller_lock_write_process_type_
  f_status_t controller_lock_write_process_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t *lock) {

    return controller_lock_write(type != controller_process_type_exit, thread, lock);
  }
#endif // _di_controller_lock_write_process_type_

#ifndef _di_controller_pids_increase_
  f_status_t controller_pids_increase(controller_pids_t *pids) {

    if (pids->used + 1 > pids->size) {
      f_array_length_t size = pids->used + controller_common_allocation_small_d;

      if (size > F_array_length_t_size_d) {
        if (pids->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return controller_pids_resize(size, pids);
    }

    return F_data_not;
  }
#endif // _di_controller_pids_increase_

#ifndef _di_controller_pids_resize_
  f_status_t controller_pids_resize(const f_array_length_t length, controller_pids_t *pids) {

    f_status_t status = F_none;

    status = f_memory_resize(pids->size, length, sizeof(controller_rule_t), (void **) & pids->array);

    if (F_status_is_error_not(status)) {
      pids->size = length;

      if (pids->used > pids->size) {
        pids->used = length;
      }
    }

    return status;
  }
#endif // _di_controller_pids_resize_

#ifndef _di_controller_print_lock_
  void controller_print_lock(const f_file_t to, controller_thread_t * const thread) {

    if (thread) {
      f_thread_mutex_lock(&thread->lock.print);
    }

    flockfile(to.stream);
  }
#endif // _di_controller_print_lock_

#ifndef _di_controller_print_unlock_flush_
  void controller_print_unlock_flush(const f_file_t to, controller_thread_t * const thread) {

    fflush(to.stream);
    funlockfile(to.stream);

    if (thread) {
      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_print_unlock_flush_

#ifndef _di_controller_process_delete_simple_
  void controller_process_delete_simple(controller_process_t *process) {

    if (process->id_thread) {
      f_thread_signal(process->id_thread, F_signal_kill);
      f_thread_join(process->id_thread, 0);

      process->id_thread = 0;
    }

    f_thread_condition_delete(&process->wait);

    controller_lock_delete_rw(&process->lock);
    controller_lock_delete_rw(&process->active);
    controller_lock_delete_mutex(&process->wait_lock);

    controller_cache_delete_simple(&process->cache);
    controller_pids_resize(0, &process->childs);
    controller_rule_delete_simple(&process->rule);

    f_string_dynamics_resize(0, &process->path_pids);

    macro_f_array_lengths_t_delete_simple(process->stack)
  }
#endif // _di_controller_process_delete_simple_

#ifndef _di_controller_process_wait_
  f_status_t controller_process_wait(const controller_global_t global, controller_process_t *process) {

    if (!controller_thread_is_enabled_process(process, global.thread)) {
      return F_signal;
    }

    struct timespec time;

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    uint8_t count = 0;

    do {
      f_thread_mutex_lock(&process->wait_lock);

      if (count < controller_thread_wait_timeout_1_before_d) {
        controller_time(controller_thread_wait_timeout_1_seconds_d, controller_thread_wait_timeout_1_nanoseconds_d, &time);
      }
      else if (count < controller_thread_wait_timeout_2_before_d) {
        controller_time(controller_thread_wait_timeout_2_seconds_d, controller_thread_wait_timeout_2_nanoseconds_d, &time);
      }
      else if (count < controller_thread_wait_timeout_3_before_d) {
        controller_time(controller_thread_wait_timeout_3_seconds_d, controller_thread_wait_timeout_3_nanoseconds_d, &time);
      }
      else {
        controller_time(controller_thread_wait_timeout_4_seconds_d, controller_thread_wait_timeout_4_nanoseconds_d, &time);
      }

      status = f_thread_condition_wait_timed(&time, &process->wait, &process->wait_lock);

      f_thread_mutex_unlock(&process->wait_lock);

      if (!controller_thread_is_enabled_process(process, global.thread)) {
        return F_signal;
      }

      if (F_status_is_error(status)) {
        break;
      }

      status_lock = controller_lock_read_process(process, global.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

        break;
      }

      if (!controller_rule_status_is_available(process->action, process->rule) && !(process->state == controller_process_state_active || process->state == controller_process_state_busy)) {
        f_thread_unlock(&process->lock);

        return F_none;
      }
      else if (status != F_time) {

        // move up the wait timer after a trigger was received.
        if (count < controller_thread_wait_timeout_2_before_d) {
          count = 0;
        }
        else if (count < controller_thread_wait_timeout_3_before_d) {
          count = controller_thread_wait_timeout_1_before_d;
        }
        else {
          count = controller_thread_wait_timeout_2_before_d;
        }
      }

      f_thread_unlock(&process->lock);

      if (count < controller_thread_wait_timeout_3_before_d) {
        ++count;
      }

    } while (status == F_time && controller_thread_is_enabled_process(process, global.thread));

    return status;
  }
#endif // _di_controller_process_wait_

#ifndef _di_controller_processs_delete_simple_
  void controller_processs_delete_simple(controller_processs_t *processs) {

    controller_processs_resize(0, processs);
  }
#endif // _di_controller_processs_delete_simple_

#ifndef _di_controller_processs_increase_
  f_status_t controller_processs_increase(controller_processs_t *processs) {

    if (processs->used + 1 > processs->size) {
      f_array_length_t size = processs->used + controller_common_allocation_small_d;

      if (size > F_array_length_t_size_d) {
        if (processs->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return controller_processs_resize(size, processs);
    }

    return F_data_not;
  }
#endif // _di_controller_processs_increase_

#ifndef _di_controller_processs_resize_
  f_status_t controller_processs_resize(const f_array_length_t length, controller_processs_t *processs) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < processs->size; ++i) {

      if (processs->array[i]) {
        controller_process_delete_simple(processs->array[i]);

        f_memory_delete(1, sizeof(f_array_length_t *), (void **) & processs->array[i]);
      }
    } // for

    status = f_memory_resize(processs->size, length, sizeof(controller_process_t), (void **) & processs->array);

    if (F_status_is_error_not(status) && length) {

      controller_process_t *process = 0;

      // the lock must be initialized, but only once, so initialize immediately upon allocation.
      for (; processs->size < length; ++processs->size) {

        status = f_memory_new(1, sizeof(controller_process_t), (void **) &processs->array[processs->size]);

        if (F_status_is_error_not(status)) {
          process = processs->array[processs->size];

          status = f_thread_lock_create(0, &process->lock);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_lock_create(0, &process->active);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_condition_create(0, &process->wait);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_mutex_create(0, &process->wait_lock);
        }

        if (F_status_is_error(status)) {
          processs->size = length;

          return status;
        }
        else {
          for (f_array_length_t i = 0; i < controller_rule_action_type__enum_size; ++i) {
            process->rule.status[i] = F_known_not;
          } // for
        }
      } // for

      processs->size = length;

      if (processs->used > processs->size) {
        processs->used = length;
      }
    }

    return status;
  }
#endif // _di_controller_processs_resize_

#ifndef _di_controller_rule_action_delete_simple_
  void controller_rule_action_delete_simple(controller_rule_action_t *action) {

    f_string_dynamics_resize(0, &action->parameters);
  }
#endif // _di_controller_rule_action_delete_simple_

#ifndef _di_controller_rule_actions_delete_simple_
  void controller_rule_actions_delete_simple(controller_rule_actions_t *actions) {

    actions->used = actions->size;

    while (actions->used) {
      controller_rule_action_delete_simple(&actions->array[--actions->used]);
    } // while

    f_memory_delete(actions->size, sizeof(controller_rule_action_t), (void **) & actions->array);
    actions->size = 0;
  }
#endif // _di_controller_rule_actions_delete_simple_

#ifndef _di_controller_rule_delete_simple_
  void controller_rule_delete_simple(controller_rule_t *rule) {

    f_string_dynamic_resize(0, &rule->alias);
    f_string_dynamic_resize(0, &rule->name);
    f_string_dynamic_resize(0, &rule->path);
    f_string_dynamic_resize(0, &rule->script);

    f_string_maps_resize(0, &rule->define);
    f_string_maps_resize(0, &rule->parameter);

    f_string_dynamics_resize(0, &rule->environment);

    macro_f_int32s_t_delete_simple(rule->affinity)
    macro_f_control_group_t_delete_simple(rule->control_group)
    macro_f_int32s_t_delete_simple(rule->groups)
    macro_f_limit_sets_t_delete_simple(rule->limits)

    if (rule->capability) {
      f_capability_delete(&rule->capability);
    }

    controller_rule_ons_delete_simple(&rule->ons);
    controller_rule_items_delete_simple(&rule->items);
  }
#endif // _di_controller_rule_delete_simple_

#ifndef _di_controller_rule_item_delete_simple_
  void controller_rule_item_delete_simple(controller_rule_item_t *item) {

    f_string_dynamic_resize(0, &item->pid_file);

    controller_rule_actions_delete_simple(&item->actions);
  }
#endif // _di_controller_rule_item_delete_simple_

#ifndef _di_controller_rule_items_delete_simple_
  void controller_rule_items_delete_simple(controller_rule_items_t *items) {

    items->used = items->size;

    while (items->used) {
      controller_rule_item_delete_simple(&items->array[--items->used]);
    } // while

    f_memory_delete(items->size, sizeof(controller_rule_item_t), (void **) & items->array);
    items->size = 0;
  }
#endif // _di_controller_rule_items_delete_simple_

#ifndef _di_controller_rule_on_delete_simple_
  void controller_rule_on_delete_simple(controller_rule_on_t *on) {

    f_string_dynamics_resize(0, &on->need);
    f_string_dynamics_resize(0, &on->want);
    f_string_dynamics_resize(0, &on->wish);
  }
#endif // _di_controller_rule_on_delete_simple_

#ifndef _di_controller_rule_ons_delete_simple_
  void controller_rule_ons_delete_simple(controller_rule_ons_t *ons) {

    ons->used = ons->size;

    while (ons->used) {
      controller_rule_on_delete_simple(&ons->array[--ons->used]);
    } // while

    f_memory_delete(ons->size, sizeof(controller_rule_on_t), (void **) & ons->array);
    ons->size = 0;
  }
#endif // _di_controller_rule_ons_delete_simple_

#ifndef _di_controller_rule_ons_increase_
  f_status_t controller_rule_ons_increase(controller_rule_ons_t *ons) {

    if (ons->used + 1 > ons->size) {
      f_array_length_t size = ons->used + controller_common_allocation_small_d;

      if (size > F_array_length_t_size_d) {
        if (ons->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return controller_rule_ons_resize(size, ons);
    }

    return F_data_not;
  }
#endif // _di_controller_rule_ons_increase_

#ifndef _di_controller_rule_ons_resize_
  f_status_t controller_rule_ons_resize(const f_array_length_t length, controller_rule_ons_t *ons) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < ons->size; ++i) {
      controller_rule_on_delete_simple(&ons->array[i]);
    } // for

    status = f_memory_resize(ons->size, length, sizeof(controller_rule_on_t), (void **) & ons->array);

    if (F_status_is_error_not(status)) {
      ons->size = length;

      if (ons->used > ons->size) {
        ons->used = length;
      }
    }

    return status;
  }
#endif // _di_controller_rule_ons_resize_

#ifndef _di_controller_rules_delete_simple_
  void controller_rules_delete_simple(controller_rules_t *rules) {

    controller_rules_resize(0, rules);
  }
#endif // _di_controller_rules_delete_simple_

#ifndef _di_controller_rules_increase_
  f_status_t controller_rules_increase(controller_rules_t *rules) {

    if (rules->used + 1 > rules->size) {
      f_array_length_t size = rules->used + controller_common_allocation_small_d;

      if (size > F_array_length_t_size_d) {
        if (rules->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return controller_rules_resize(size, rules);
    }

    return F_data_not;
  }
#endif // _di_controller_rules_increase_

#ifndef _di_controller_rules_resize_
  f_status_t controller_rules_resize(const f_array_length_t length, controller_rules_t *rules) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < rules->size; ++i) {
      controller_rule_delete_simple(&rules->array[i]);
    } // for

    status = f_memory_resize(rules->size, length, sizeof(controller_rule_t), (void **) & rules->array);

    if (F_status_is_error_not(status)) {
      rules->size = length;

      if (rules->used > rules->size) {
        rules->used = length;
      }
    }

    return status;
  }
#endif // _di_controller_rules_resize_

#ifndef _di_controller_setting_delete_simple_
  void controller_setting_delete_simple(controller_setting_t *setting) {

    f_string_dynamic_resize(0, &setting->path_control);
    f_string_dynamic_resize(0, &setting->path_pid);
    f_string_dynamic_resize(0, &setting->path_setting);

    f_string_dynamic_resize(0, &setting->name_entry);

    controller_entry_items_delete_simple(&setting->entry.items);
    controller_entry_items_delete_simple(&setting->exit.items);
    controller_rules_delete_simple(&setting->rules);
  }
#endif // _di_controller_setting_delete_simple_

#ifndef _di_controller_thread_delete_simple_
  void controller_thread_delete_simple(controller_thread_t *thread) {

    controller_lock_delete_simple(&thread->lock);
    controller_processs_resize(0, &thread->processs);
    controller_cache_delete_simple(&thread->cache);
  }
#endif // _di_controller_thread_delete_simple_

#ifndef _di_controller_time_
  void controller_time(const time_t seconds, const long nanoseconds, struct timespec *time) {

    struct timeval now;

    gettimeofday(&now, 0);

    time->tv_sec = now.tv_sec + seconds;
    time->tv_nsec = (now.tv_usec * 1000) + nanoseconds;

    // If tv_nsec is 1 second or greater, then increment seconds.
    if (time->tv_nsec >= 1000000000) {
      ++(time->tv_sec);

      time->tv_nsec -= 1000000000;
    }
  }
#endif // _di_controller_time_

#ifndef _di_controller_time_micro_
  struct timespec controller_time_micro(const f_number_unsigned_t microseconds) {

    struct timespec time;
    time.tv_sec = microseconds / 1000;
    time.tv_nsec = (time.tv_sec ? microseconds - time.tv_sec : microseconds) * 1000;

    return time;
  }
#endif // _di_controller_time_micro_

#ifdef __cplusplus
} // extern "C"
#endif
