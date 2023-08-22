#include "../controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_delete_simple_
  void controller_entry_action_delete_simple(controller_entry_action_t * const action) {

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_controller_entry_action_delete_simple_

#ifndef _di_controller_entry_actions_delete_simple_
  void controller_entry_actions_delete_simple(controller_entry_actions_t * const actions) {

    // @todo Determine if this should be replaced with a resize callback strategy.
    actions->used = actions->size;

    while (actions->used) {
      controller_entry_action_delete_simple(&actions->array[--actions->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_entry_action_t), (void **) &actions->array, &actions->used, &actions->size);
  }
#endif // _di_controller_entry_actions_delete_simple_

#ifndef _di_controller_entry_actions_increase_by_
  f_status_t controller_entry_actions_increase_by(const f_number_unsigned_t amount, controller_entry_actions_t * const actions) {

    if (amount) {
      if (actions->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = actions->used + amount;

      if (length > actions->size) {
        const f_status_t status = f_memory_resize(actions->size, length, sizeof(controller_entry_action_t), (void **) & actions->array);

        if (F_status_is_error_not(status)) {
          actions->size = actions->used + amount;
        }

        return status;
      }
    }

    return F_data_not;
  }
#endif // _di_controller_entry_actions_increase_by_

#ifndef _di_controller_entry_item_delete_simple_
  void controller_entry_item_delete_simple(controller_entry_item_t * const item) {

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &item->name.string, &item->name.used, &item->name.size);

    controller_entry_actions_delete_simple(&item->actions);
  }
#endif // _di_controller_entry_item_delete_simple_

#ifndef _di_controller_entry_items_delete_simple_
  void controller_entry_items_delete_simple(controller_entry_items_t * const items) {

    // @todo Determine if this should be replaced with a resize callback strategy.
    items->used = items->size;

    while (items->used) {
      controller_entry_item_delete_simple(&items->array[--items->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_entry_item_t), (void **) &items->array, &items->used, &items->size);
  }
#endif // _di_controller_entry_items_delete_simple_

#ifndef _di_controller_entry_items_increase_by_
  f_status_t controller_entry_items_increase_by(const f_number_unsigned_t amount, controller_entry_items_t * const items) {

    if (amount) {
      if (items->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = items->used + amount;

      if (length > items->size) {
        const f_status_t status = f_memory_resize(items->size, length, sizeof(controller_entry_item_t), (void **) & items->array);

        if (F_status_is_error_not(status)) {
          items->size = items->used + amount;
        }

        return status;
      }
    }

    return F_data_not;
  }
#endif // _di_controller_entry_items_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif
