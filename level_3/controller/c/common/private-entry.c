#include "../controller/controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_delete_simple_
  void controller_entry_action_delete_simple(controller_entry_action_t * const action) {

    f_string_dynamics_resize(0, &action->parameters);
  }
#endif // _di_controller_entry_action_delete_simple_

#ifndef _di_controller_entry_actions_delete_simple_
  void controller_entry_actions_delete_simple(controller_entry_actions_t * const actions) {

    actions->used = actions->size;

    while (actions->used) {
      controller_entry_action_delete_simple(&actions->array[--actions->used]);
    } // while

    f_memory_delete(actions->size, sizeof(controller_entry_action_t), (void **) & actions->array);
    actions->size = 0;
  }
#endif // _di_controller_entry_actions_delete_simple_

#ifndef _di_controller_entry_actions_increase_by_
  f_status_t controller_entry_actions_increase_by(const f_array_length_t amount, controller_entry_actions_t * const actions) {

    if (actions->used + amount > actions->size) {
      if (actions->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize(actions->size, actions->used + amount, sizeof(controller_entry_action_t), (void **) & actions->array);

      if (F_status_is_error_not(status)) {
        actions->size = actions->used + amount;
      }

      return status;
    }

    return F_data_not;
  }
#endif // _di_controller_entry_actions_increase_by_

#ifndef _di_controller_entry_item_delete_simple_
  void controller_entry_item_delete_simple(controller_entry_item_t * const item) {

    f_string_dynamic_resize(0, &item->name);

    controller_entry_actions_delete_simple(&item->actions);
  }
#endif // _di_controller_entry_item_delete_simple_

#ifndef _di_controller_entry_items_delete_simple_
  void controller_entry_items_delete_simple(controller_entry_items_t * const items) {

    items->used = items->size;

    while (items->used) {
      controller_entry_item_delete_simple(&items->array[--items->used]);
    } // while

    f_memory_delete(items->size, sizeof(controller_entry_item_t), (void **) & items->array);
    items->size = 0;
  }
#endif // _di_controller_entry_items_delete_simple_

#ifndef _di_controller_entry_items_increase_by_
  f_status_t controller_entry_items_increase_by(const f_array_length_t amount, controller_entry_items_t * const items) {

    if (items->used + amount > items->size) {
      if (items->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize(items->size, items->used + amount, sizeof(controller_entry_item_t), (void **) & items->array);

      if (F_status_is_error_not(status)) {
        items->size = items->used + amount;
      }

      return status;
    }

    return F_data_not;
  }
#endif // _di_controller_entry_items_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif
