#include "controller.h"
#include "private-common.h"
#include "private-thread.h"
#include "private-rule.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_string_s_
  const f_string_t controller_string_action_s = controller_string_action;
  const f_string_t controller_string_actions_s = controller_string_actions;
  const f_string_t controller_string_affinity_s = controller_string_affinity;
  const f_string_t controller_string_as_s = controller_string_as;
  const f_string_t controller_string_asynchronous_s = controller_string_asynchronous;
  const f_string_t controller_string_bash_s = controller_string_bash;
  const f_string_t controller_string_batch_s = controller_string_batch;
  const f_string_t controller_string_capability_s = controller_string_capability;
  const f_string_t controller_string_create_s = controller_string_create;
  const f_string_t controller_string_command_s = controller_string_command;
  const f_string_t controller_string_consider_s = controller_string_consider;
  const f_string_t controller_string_control_s = controller_string_control;
  const f_string_t controller_string_control_group_s = controller_string_control_group;
  const f_string_t controller_string_cpu_s = controller_string_cpu;
  const f_string_t controller_string_core_s = controller_string_core;
  const f_string_t controller_string_data_s = controller_string_data;
  const f_string_t controller_string_deadline_s = controller_string_deadline;
  const f_string_t controller_string_default_s = controller_string_default;
  const f_string_t controller_string_define_s = controller_string_define;
  const f_string_t controller_string_entry_s = controller_string_entry;
  const f_string_t controller_string_entries_s = controller_string_entries;
  const f_string_t controller_string_environment_s = controller_string_environment;
  const f_string_t controller_string_existing_s = controller_string_existing;
  const f_string_t controller_string_execute_s = controller_string_execute;
  const f_string_t controller_string_exit_s = controller_string_exit;
  const f_string_t controller_string_exits_s = controller_string_exits;
  const f_string_t controller_string_fail_s = controller_string_fail;
  const f_string_t controller_string_failsafe_s = controller_string_failsafe;
  const f_string_t controller_string_fifo_s = controller_string_fifo;
  const f_string_t controller_string_freeze_s = controller_string_freeze;
  const f_string_t controller_string_fsize_s = controller_string_fsize;
  const f_string_t controller_string_full_path_s = controller_string_full_path;
  const f_string_t controller_string_group_s = controller_string_group;
  const f_string_t controller_string_groups_s = controller_string_groups;
  const f_string_t controller_string_how_s = controller_string_how;
  const f_string_t controller_string_idle_s = controller_string_idle;
  const f_string_t controller_string_item_s = controller_string_item;
  const f_string_t controller_string_kill_s = controller_string_kill;
  const f_string_t controller_string_limit_s = controller_string_limit;
  const f_string_t controller_string_locks_s = controller_string_locks;
  const f_string_t controller_string_main_s = controller_string_main;
  const f_string_t controller_string_memlock_s = controller_string_memlock;
  const f_string_t controller_string_method_s = controller_string_method;
  const f_string_t controller_string_mode_s = controller_string_mode;
  const f_string_t controller_string_msgqueue_s = controller_string_msgqueue;
  const f_string_t controller_string_name_s = controller_string_name;
  const f_string_t controller_string_need_s = controller_string_need;
  const f_string_t controller_string_new_s = controller_string_new;
  const f_string_t controller_string_nice_s = controller_string_nice;
  const f_string_t controller_string_no_s = controller_string_no;
  const f_string_t controller_string_nofile_s = controller_string_nofile;
  const f_string_t controller_string_nproc_s = controller_string_nproc;
  const f_string_t controller_string_on_s = controller_string_on;
  const f_string_t controller_string_optional_s = controller_string_optional;
  const f_string_t controller_string_other_s = controller_string_other;
  const f_string_t controller_string_parameter_s = controller_string_parameter;
  const f_string_t controller_string_path_s = controller_string_path;
  const f_string_t controller_string_pause_s = controller_string_pause;
  const f_string_t controller_string_pid_file_s = controller_string_pid_file;
  const f_string_t controller_string_processor_s = controller_string_processor;
  const f_string_t controller_string_program_s = controller_string_program;
  const f_string_t controller_string_ready_s = controller_string_ready;
  const f_string_t controller_string_reload_s = controller_string_reload;
  const f_string_t controller_string_require_s = controller_string_require;
  const f_string_t controller_string_required_s = controller_string_required;
  const f_string_t controller_string_restart_s = controller_string_restart;
  const f_string_t controller_string_resume_s = controller_string_resume;
  const f_string_t controller_string_round_robin_s = controller_string_round_robin;
  const f_string_t controller_string_rss_s = controller_string_rss;
  const f_string_t controller_string_rtprio_s = controller_string_rtprio;
  const f_string_t controller_string_rttime_s = controller_string_rttime;
  const f_string_t controller_string_rule_s = controller_string_rule;
  const f_string_t controller_string_rules_s = controller_string_rules;
  const f_string_t controller_string_scheduler_s = controller_string_scheduler;
  const f_string_t controller_string_script_s = controller_string_script;
  const f_string_t controller_string_service_s = controller_string_service;
  const f_string_t controller_string_setting_s = controller_string_setting;
  const f_string_t controller_string_sigpending_s = controller_string_sigpending;
  const f_string_t controller_string_stack_s = controller_string_stack;
  const f_string_t controller_string_start_s = controller_string_start;
  const f_string_t controller_string_stop_s = controller_string_stop;
  const f_string_t controller_string_succeed_s = controller_string_succeed;
  const f_string_t controller_string_synchronous_s = controller_string_synchronous;
  const f_string_t controller_string_thaw_s = controller_string_thaw;
  const f_string_t controller_string_timeout_s = controller_string_timeout;
  const f_string_t controller_string_type_s = controller_string_type;
  const f_string_t controller_string_use_s = controller_string_use;
  const f_string_t controller_string_user_s = controller_string_user;
  const f_string_t controller_string_utility_s = controller_string_utility;
  const f_string_t controller_string_wait_s = controller_string_wait;
  const f_string_t controller_string_want_s = controller_string_want;
  const f_string_t controller_string_wish_s = controller_string_wish;
  const f_string_t controller_string_with_s = controller_string_with;
  const f_string_t controller_string_yes_s = controller_string_yes;
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
  void controller_error_file_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t name, const f_string_t operation, const uint8_t type, controller_thread_t *thread) {

    if (print.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->lock.print);

      fll_error_file_print(print, status, function, fallback, name, operation, type);

      controller_print_unlock_flush(print.to.stream, &thread->lock.print);
    }
  }
#endif // _di_controller_error_file_print_

#ifndef _di_controller_error_pid_bad_match_print_
  void controller_error_pid_bad_match_print(const fll_error_print_t print, const f_string_t path, controller_thread_t *thread) {

    if (thread) f_thread_mutex_lock(&thread->lock.print);

    fprintf(print.to.stream, "%c", f_string_eol_s[0]);
    fprintf(print.to.stream, "%s%sThe pid file '", print.context.before->string, print.prefix ? print.prefix : f_string_empty_s);
    fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, path, print.notable.after->string);
    fprintf(print.to.stream, "%s' doesn't contain the expected number, not deleting file.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

    if (thread) controller_print_unlock_flush(print.to.stream, &thread->lock.print);
  }
#endif // _di_controller_error_pid_bad_match_print_

#ifndef _di_controller_error_print_
  void controller_error_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) {

    if (print.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->lock.print);

      fll_error_print(print, status, function, fallback);

      controller_print_unlock_flush(print.to.stream, &thread->lock.print);
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
  void controller_lock_error_critical_print(const fll_error_print_t print, const f_status_t status, const bool read, controller_thread_t *thread) {

    // A signal is not an error.
    if (status == F_signal) {
      return;
    }

    if (print.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->lock.print);

      fprintf(print.to.stream, "%c", f_string_eol_s[0]);
      fprintf(print.to.stream, "%s%sCritical failure while attempting to establish ", print.context.before->string, print.prefix ? print.prefix : f_string_empty_s);
      fprintf(print.to.stream, "%s%s%s lock%s", print.context.after->string, print.notable.before->string, read ? "read" : "write", print.notable.after->string);

      if (status != F_failure) {
        fprintf(print.to.stream, "%s' due to %s", print.context.before->string, print.context.after->string);

        if (status == F_parameter) {
          fprintf(print.to.stream, "%s%s%s", print.notable.before->string, "Invalid Parameter", print.notable.after->string);
        }
        else if (status == F_deadlock) {
          fprintf(print.to.stream, "%s%s%s", print.notable.before->string, "Deadlock", print.notable.after->string);
        }
        else if (status == F_resource_not) {
          fprintf(print.to.stream, "%s%s%s", print.notable.before->string, "Too Many Locks", print.notable.after->string);
        }
      }

      fprintf(print.to.stream, "%s.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);

      controller_print_unlock_flush(print.to.stream, &thread->lock.print);
    }
  }
#endif // _di_controller_lock_error_critical_print_

#ifndef _di_controller_lock_read_
  f_status_t controller_lock_read(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) {

    struct timespec time;

    f_status_t status = F_none;

    for (;;) {

      controller_time(controller_thread_lock_read_timeout_seconds, controller_thread_lock_read_timeout_nanoseconds, &time);

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

      controller_time(controller_thread_lock_write_timeout_seconds, controller_thread_lock_write_timeout_nanoseconds, &time);

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
      f_array_length_t size = pids->used + controller_common_allocation_small;

      if (size > f_array_length_t_size) {
        if (pids->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
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

#ifndef _di_controller_print_unlock_flush_
  void controller_print_unlock_flush(FILE * const stream, f_thread_mutex_t *mutex) {

    if (stream == 0 || mutex == 0) {
      return;
    }

    fflush(stream);
    f_thread_mutex_unlock(mutex);
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

      if (count < controller_thread_wait_timeout_1_before) {
        controller_time(controller_thread_wait_timeout_1_seconds, controller_thread_wait_timeout_1_nanoseconds, &time);
      }
      else if (count < controller_thread_wait_timeout_2_before) {
        controller_time(controller_thread_wait_timeout_2_seconds, controller_thread_wait_timeout_2_nanoseconds, &time);
      }
      else if (count < controller_thread_wait_timeout_3_before) {
        controller_time(controller_thread_wait_timeout_3_seconds, controller_thread_wait_timeout_3_nanoseconds, &time);
      }
      else {
        controller_time(controller_thread_wait_timeout_4_seconds, controller_thread_wait_timeout_4_nanoseconds, &time);
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
        if (count < controller_thread_wait_timeout_2_before) {
          count = 0;
        }
        else if (count < controller_thread_wait_timeout_3_before) {
          count = controller_thread_wait_timeout_1_before;
        }
        else {
          count = controller_thread_wait_timeout_2_before;
        }
      }

      f_thread_unlock(&process->lock);

      if (count < controller_thread_wait_timeout_3_before) {
        count++;
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
      f_array_length_t size = processs->used + controller_common_allocation_small;

      if (size > f_array_length_t_size) {
        if (processs->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
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
      f_array_length_t size = ons->used + controller_common_allocation_small;

      if (size > f_array_length_t_size) {
        if (ons->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
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
      f_array_length_t size = rules->used + controller_common_allocation_small;

      if (size > f_array_length_t_size) {
        if (rules->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
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

#ifdef __cplusplus
} // extern "C"
#endif
