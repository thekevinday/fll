#include "../controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_action_t_
  const f_string_static_t controller_rule_action_method_string_extended_s = macro_f_string_static_t_initialize(CONTROLLER_rule_action_method_string_extended_s, 0, CONTROLLER_rule_action_method_string_extended_s_length);
  const f_string_static_t controller_rule_action_method_string_extended_list_s = macro_f_string_static_t_initialize(CONTROLLER_rule_action_method_string_extended_list_s, 0, CONTROLLER_rule_action_method_string_extended_list_s_length);
#endif // _di_controller_rule_action_t_

#ifndef _di_controller_rule_action_delete_simple_
  void controller_rule_action_delete_simple(controller_rule_action_t * const action) {

    f_string_dynamics_resize(0, &action->parameters);
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
  f_status_t controller_rule_actions_increase_by(const f_array_length_t amount, controller_rule_actions_t * const actions) {

    if (actions->used + amount > actions->size) {
      if (actions->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize(actions->size, actions->used + amount, sizeof(controller_rule_action_t), (void **) & actions->array);

      if (F_status_is_error_not(status)) {
        actions->size = actions->used + amount;
      }

      return status;
    }

    return F_data_not;
  }
#endif // _di_controller_rule_actions_increase_by_

#ifndef _di_controller_rule_delete_simple_
  void controller_rule_delete_simple(controller_rule_t * const rule) {

    f_string_dynamic_resize(0, &rule->alias);
    f_string_dynamic_resize(0, &rule->name);
    f_string_dynamic_resize(0, &rule->path);
    f_string_dynamic_resize(0, &rule->script);

    f_string_maps_resize(0, &rule->define);
    f_string_maps_resize(0, &rule->parameter);

    f_string_dynamics_resize(0, &rule->environment);

    macro_f_int32s_t_delete_simple(rule->affinity)
    macro_f_control_group_t_delete_simple(rule->cgroup)
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
  void controller_rule_item_delete_simple(controller_rule_item_t * const item) {

    f_string_dynamic_resize(0, &item->pid_file);

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

    f_string_dynamics_resize(0, &on->need);
    f_string_dynamics_resize(0, &on->want);
    f_string_dynamics_resize(0, &on->wish);
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
  f_status_t controller_rule_ons_resize(const f_array_length_t length, controller_rule_ons_t * const ons) {

    for (f_array_length_t i = length; i < ons->size; ++i) {
      controller_rule_on_delete_simple(&ons->array[i]);
    } // for

    const f_status_t status = f_memory_resize(ons->size, length, sizeof(controller_rule_on_t), (void **) & ons->array);

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
  void controller_rules_delete_simple(controller_rules_t * const rules) {

    controller_rules_resize(0, rules);
  }
#endif // _di_controller_rules_delete_simple_

#ifndef _di_controller_rules_increase_
  f_status_t controller_rules_increase(controller_rules_t * const rules) {

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
  f_status_t controller_rules_resize(const f_array_length_t length, controller_rules_t * const rules) {

    for (f_array_length_t i = length; i < rules->size; ++i) {
      controller_rule_delete_simple(&rules->array[i]);
    } // for

    const f_status_t status = f_memory_resize(rules->size, length, sizeof(controller_rule_t), (void **) & rules->array);

    if (F_status_is_error_not(status)) {
      rules->size = length;

      if (rules->used > rules->size) {
        rules->used = length;
      }
    }

    return status;
  }
#endif // _di_controller_rules_resize_

#ifdef __cplusplus
} // extern "C"
#endif
