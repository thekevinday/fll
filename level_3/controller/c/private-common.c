#include "controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_asynchronous_delete_simple_
  void controller_asynchronous_delete_simple(controller_asynchronous_t *asynchronous) {

    f_macro_array_lengths_t_delete_simple(asynchronous->stack)

    controller_cache_delete_simple(&asynchronous->cache);
    controller_rule_delete_simple(&asynchronous->rule);
  }
#endif // _di_controller_asynchronous_delete_simple_

#ifndef _di_controller_asynchronouss_increase_
  f_status_t controller_asynchronouss_increase(controller_asynchronouss_t *asynchronouss) {

    if (asynchronouss->used + 1 > asynchronouss->size) {
      f_array_length_t size = asynchronouss->used + controller_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (asynchronouss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return controller_asynchronouss_resize(size, asynchronouss);
    }

    return F_data_not;
  }
#endif // _di_controller_asynchronous_increase_

#ifndef _di_controller_asynchronouss_resize_
  f_status_t controller_asynchronouss_resize(const f_array_length_t length, controller_asynchronouss_t *asynchronouss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < asynchronouss->size; ++i) {
      controller_asynchronous_delete_simple(&asynchronouss->array[i]);
    } // for

    status = f_memory_resize(asynchronouss->size, length, sizeof(controller_asynchronous_t), (void **) & asynchronouss->array);

    if (F_status_is_error_not(status)) {
      asynchronouss->size = length;

      if (asynchronouss->used > asynchronouss->size) {
        asynchronouss->used = length;
      }
    }

    return status;
  }
#endif // _di_controller_asynchronouss_resize_

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

#ifndef _di_controller_error_print_locked_
  void controller_error_print_locked(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) {

    if (error.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->mutex.print);

      fll_error_print(error, status, function, fallback);

      f_thread_mutex_unlock(&thread->mutex.print);
    }
  }
#endif // _di_controller_error_print_locked_

#ifndef _di_controller_process_delete_simple_
  void controller_process_delete_simple(controller_process_t *process) {

    f_string_dynamic_resize(0, &process->id);
    f_thread_mutex_delete(&process->lock);
    f_thread_condition_delete(&process->wait);
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

    f_macro_thread_mutex_t_delete_simple(rule->lock)
    f_macro_thread_condition_t_delete_simple(rule->wait)
    f_macro_string_maps_t_delete_simple(rule->define)
    f_macro_string_maps_t_delete_simple(rule->parameter)
    f_macro_string_dynamics_t_delete_simple(rule->environment)
    f_macro_string_dynamics_t_delete_simple(rule->need)
    f_macro_string_dynamics_t_delete_simple(rule->want)
    f_macro_string_dynamics_t_delete_simple(rule->wish)
    f_macro_int32s_t_delete_simple(rule->affinity)
    f_macro_control_group_t_delete_simple(rule->control_group)
    f_macro_int32s_t_delete_simple(rule->groups)
    f_macro_limit_sets_t_delete_simple(rule->limits)

    f_string_dynamic_resize(0, &rule->id);
    f_string_dynamic_resize(0, &rule->name);
    f_string_dynamic_resize(0, &rule->path);
    f_string_dynamic_resize(0, &rule->script);

    f_capability_delete(&rule->capability);

    controller_rule_items_delete_simple(&rule->items);
  }
#endif // _di_controller_rule_delete_simple_

#ifndef _di_controller_rule_item_delete_simple_
  void controller_rule_item_delete_simple(controller_rule_item_t *item) {

    f_string_dynamic_resize(0, item->actions);
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

    f_thread_mutex_unlock(&thread->mutex.asynchronous);
    f_thread_mutex_unlock(&thread->mutex.print);
    f_thread_mutex_unlock(&thread->mutex.process);
    f_thread_mutex_unlock(&thread->mutex.rule);

    controller_asynchronouss_resize(0, &thread->asynchronouss);
  }
#endif // _di_controller_thread_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif
