#include "controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

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

    f_macro_array_lengths_t_delete_simple(cache->ats)
    f_macro_array_lengths_t_delete_simple(cache->stack)
    f_macro_fss_delimits_t_delete_simple(cache->delimits)

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

#ifndef _di_controller_error_print_
  void controller_error_print(const fll_error_print_t print, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) {

    if (print.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->lock.print);

      fll_error_print(print, status, function, fallback);

      f_thread_mutex_unlock(&thread->lock.print);
    }
  }
#endif // _di_controller_error_print_

#ifndef _di_controller_lock_create_
  f_status_t controller_lock_create(controller_lock_t *lock) {

    f_status_t status = f_thread_mutex_create(0, &lock->print);
    if (F_status_is_error(status)) return status;

    status = f_thread_lock_create(0, &lock->process);
    if (F_status_is_error(status)) return status;

    status = f_thread_lock_create(0, &lock->rule);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_lock_create_

#ifndef _di_controller_lock_delete_simple_
  void controller_lock_delete_simple(controller_lock_t *lock) {

    f_thread_mutex_delete(&lock->print);

    f_thread_lock_delete(&lock->process);
    f_thread_lock_delete(&lock->rule);
  }
#endif // _di_controller_lock_delete_simple_

#ifndef _di_controller_process_delete_simple_
  void controller_process_delete_simple(controller_process_t *process) {

    f_thread_lock_delete(&process->lock);
    f_thread_lock_delete(&process->active);

    f_thread_mutex_lock(&process->wait_lock);
    f_thread_condition_signal_all(&process->wait);
    f_thread_mutex_unlock(&process->wait_lock);
    f_thread_mutex_delete(&process->wait_lock);

    controller_cache_delete_simple(&process->cache);
    controller_rule_delete_simple(&process->rule);

    f_macro_array_lengths_t_delete_simple(process->stack)
  }
#endif // _di_controller_process_delete_simple_

#ifndef _di_controller_processs_delete_simple_
  void controller_processs_delete_simple(controller_processs_t *processs) {

    controller_processs_resize(0, processs);
  }
#endif // _di_controller_processs_delete_simple_

#ifndef _di_controller_processs_increase_
  f_status_t controller_processs_increase(controller_processs_t *processs) {

    if (processs->used + 1 > processs->size) {
      f_array_length_t size = processs->used + controller_default_allocation_step;

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
      controller_process_delete_simple(&processs->array[i]);
    } // for

    status = f_memory_resize(processs->size, length, sizeof(controller_process_t), (void **) & processs->array);

    if (F_status_is_error_not(status)) {

      // the lock must be initialized, but only once, so initialize immediately upon allocation.
      for (; processs->size < length; ++processs->size) {

        status = f_thread_lock_create(0, &processs->array[processs->size].lock);

        if (F_status_is_error_not(status)) {
          status = f_thread_lock_create(0, &processs->array[processs->size].active);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_condition_create(0, &processs->array[processs->size].wait);
        }

        if (F_status_is_error_not(status)) {
          status = f_thread_mutex_create(0, &processs->array[processs->size].wait_lock);
        }

        if (F_status_is_error(status)) {
          processs->size = length;
          return status;
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
    f_string_dynamics_resize(0, &rule->need);
    f_string_dynamics_resize(0, &rule->want);
    f_string_dynamics_resize(0, &rule->wish);

    f_macro_int32s_t_delete_simple(rule->affinity)
    f_macro_control_group_t_delete_simple(rule->control_group)
    f_macro_int32s_t_delete_simple(rule->groups)
    f_macro_limit_sets_t_delete_simple(rule->limits)

    f_capability_delete(&rule->capability);

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

#ifndef _di_controller_rules_delete_simple_
  void controller_rules_delete_simple(controller_rules_t *rules) {

    controller_rules_resize(0, rules);
  }
#endif // _di_controller_rules_delete_simple_

#ifndef _di_controller_rules_increase_
  f_status_t controller_rules_increase(controller_rules_t *rules) {

    if (rules->used + 1 > rules->size) {
      f_array_length_t size = rules->used + controller_default_allocation_step;

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

    controller_entry_items_delete_simple(&setting->entry.items);
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

#ifdef __cplusplus
} // extern "C"
#endif
