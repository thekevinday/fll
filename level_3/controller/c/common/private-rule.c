#include "../controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_action_t_
  const f_string_static_t controller_rule_action_method_string_extended_s = macro_f_string_static_t_initialize_1(CONTROLLER_rule_action_method_string_extended_s, 0, CONTROLLER_rule_action_method_string_extended_s_length);
  const f_string_static_t controller_rule_action_method_string_extended_list_s = macro_f_string_static_t_initialize_1(CONTROLLER_rule_action_method_string_extended_list_s, 0, CONTROLLER_rule_action_method_string_extended_list_s_length);
#endif // _di_controller_rule_action_t_

#ifndef _di_controller_rule_action_delete_simple_
  void controller_rule_action_delete_simple(controller_rule_action_t * const action) {

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);
  }
#endif // _di_controller_rule_action_delete_simple_

#ifndef _di_controller_rule_actions_delete_simple_
  void controller_rule_actions_delete_simple(controller_rule_actions_t * const actions) {

    actions->used = actions->size;

    while (actions->used) {
      controller_rule_action_delete_simple(&actions->array[--actions->used]);
    } // while

    f_memory_delete(actions->size, sizeof(controller_rule_action_t), (void **) & actions->array);
    actions->size = 0;
  }
#endif // _di_controller_rule_actions_delete_simple_

#ifndef _di_controller_rule_actions_increase_by_
  f_status_t controller_rule_actions_increase_by(const f_number_unsigned_t amount, controller_rule_actions_t * const actions) {

    if (amount) {
      if (actions->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = actions->used + amount;

      if (length > actions->size) {
        const f_status_t status = f_memory_resize(actions->size, length, sizeof(controller_rule_action_t), (void **) & actions->array);

        if (F_status_is_error_not(status)) {
          actions->size = actions->used + amount;
        }

        return status;
      }
    }

    return F_data_not;
  }
#endif // _di_controller_rule_actions_increase_by_

#ifndef _di_controller_rule_delete_simple_
  void controller_rule_delete_simple(controller_rule_t * const rule) {

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->engine.string, &rule->engine.used, &rule->engine.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->name.string, &rule->name.used, &rule->name.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->path.string, &rule->path.used, &rule->path.size);

    f_string_maps_resize(0, &rule->define);
    f_string_maps_resize(0, &rule->parameter);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->engine_arguments.array, &rule->engine_arguments.used, &rule->engine_arguments.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->environment.array, &rule->environment.used, &rule->environment.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(int32_t), (void **) &rule->affinity.array, &rule->affinity.used, &rule->affinity.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->cgroup.path.string, &rule->cgroup.path.used, &rule->cgroup.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->cgroup.groups.array, &rule->cgroup.groups.used, &rule->cgroup.groups.size, &f_string_dynamics_delete_callback);
    f_memory_array_resize(0, sizeof(int32_t), (void **) &rule->groups.array, &rule->groups.used, &rule->groups.size);
    f_memory_array_resize(0, sizeof(f_limit_set_t), (void **) &rule->limits.array, &rule->limits.used, &rule->limits.size);

    if (rule->capability) {
      f_capability_delete(&rule->capability);
    }

    controller_rule_ons_delete_simple(&rule->ons);
    controller_rule_items_delete_simple(&rule->items);
  }
#endif // _di_controller_rule_delete_simple_

#ifndef _di_controller_rule_item_delete_simple_
  void controller_rule_item_delete_simple(controller_rule_item_t * const item) {

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &item->pid_file.string, &item->pid_file.used, &item->pid_file.size);

    controller_rule_actions_delete_simple(&item->actions);
  }
#endif // _di_controller_rule_item_delete_simple_

#ifndef _di_controller_rule_items_delete_simple_
  void controller_rule_items_delete_simple(controller_rule_items_t * const items) {

    items->used = items->size;

    while (items->used) {
      controller_rule_item_delete_simple(&items->array[--items->used]);
    } // while

    f_memory_delete(items->size, sizeof(controller_rule_item_t), (void **) & items->array);
    items->size = 0;
  }
#endif // _di_controller_rule_items_delete_simple_

#ifndef _di_controller_rule_on_delete_simple_
  void controller_rule_on_delete_simple(controller_rule_on_t * const on) {

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->need.array, &on->need.used, &on->need.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->want.array, &on->want.used, &on->want.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->wish.array, &on->wish.used, &on->wish.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_controller_rule_on_delete_simple_

#ifndef _di_controller_rule_ons_delete_simple_
  void controller_rule_ons_delete_simple(controller_rule_ons_t * const ons) {

    ons->used = ons->size;

    while (ons->used) {
      controller_rule_on_delete_simple(&ons->array[--ons->used]);
    } // while

    f_memory_delete(ons->size, sizeof(controller_rule_on_t), (void **) & ons->array);
    ons->size = 0;
  }
#endif // _di_controller_rule_ons_delete_simple_

#ifndef _di_controller_rule_ons_increase_
  f_status_t controller_rule_ons_increase(controller_rule_ons_t * const ons) {

    if (ons->used + 1 > ons->size) {
      f_number_unsigned_t length = ons->used + controller_common_allocation_small_d;

      if (length > F_number_t_size_unsigned_d) {
        if (ons->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        length = F_number_t_size_unsigned_d;
      }

      return controller_rule_ons_resize(length, ons);
    }

    return F_data_not;
  }
#endif // _di_controller_rule_ons_increase_

#ifndef _di_controller_rule_ons_resize_
  f_status_t controller_rule_ons_resize(const f_number_unsigned_t length, controller_rule_ons_t * const ons) {

    for (f_number_unsigned_t i = length; i < ons->size; ++i) {
      controller_rule_on_delete_simple(&ons->array[i]);
    } // for

    const f_status_t status = f_memory_resize(ons->size, length, sizeof(controller_rule_on_t), (void **) & ons->array);
    if (F_status_is_error(status)) return status;

    ons->size = length;

    if (ons->used > ons->size) {
      ons->used = length;
    }

    return F_okay;
  }
#endif // _di_controller_rule_ons_resize_

#ifndef _di_controller_rules_delete_simple_
  void controller_rules_delete_simple(controller_rules_t * const rules) {

    controller_rules_resize(0, rules);
  }
#endif // _di_controller_rules_delete_simple_

#ifndef _di_controller_rules_increase_
  f_status_t controller_rules_increase(controller_rules_t * const rules) {

    if (rules->used + 1 > rules->size) {
      f_number_unsigned_t length = rules->used + controller_common_allocation_small_d;

      if (length > F_number_t_size_unsigned_d) {
        if (rules->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        length = F_number_t_size_unsigned_d;
      }

      return controller_rules_resize(length, rules);
    }

    return F_data_not;
  }
#endif // _di_controller_rules_increase_

#ifndef _di_controller_rules_resize_
  f_status_t controller_rules_resize(const f_number_unsigned_t length, controller_rules_t * const rules) {

    for (f_number_unsigned_t i = length; i < rules->size; ++i) {
      controller_rule_delete_simple(&rules->array[i]);
    } // for

    const f_status_t status = f_memory_resize(rules->size, length, sizeof(controller_rule_t), (void **) & rules->array);
    if (F_status_is_error(status)) return status;

    rules->size = length;

    if (rules->used > rules->size) {
      rules->used = length;
    }

    return F_okay;
  }
#endif // _di_controller_rules_resize_

#ifdef __cplusplus
} // extern "C"
#endif
