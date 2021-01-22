#include "controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_asynchronouss_increase_
  f_status_t controller_asynchronouss_increase(controller_asynchronouss_t *asynchronouss) {

    if (asynchronouss->used + 1 > asynchronouss->size) {
      f_array_length_t size = asynchronouss->used + controller_thread_asynchronous_allocation_step;

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
      controller_macro_asynchronous_t_delete_simple(asynchronouss->array[i]);
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

#ifndef _di_controller_rules_increase_
  f_status_t controller_rules_increase(controller_rules_t *rules) {

    if (rules->used + 1 > rules->size) {
      f_array_length_t size = rules->used + controller_default_allocation_step;

      if (size > f_string_length_t_size) {
        if (rules->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      const f_status_t status = f_memory_resize(rules->size, size, sizeof(controller_rule_t), (void **) & rules->array);

      if (F_status_is_error_not(status)) {
        rules->size = size;
      }

      return status;
    }

    return F_none;
  }
#endif // _di_controller_rules_increase_

#ifndef _di_controller_error_print_locked_
  void controller_error_print_locked(const fll_error_print_t error, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) {

    if (error.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->mutex->print);

      fll_error_print(error, status, function, fallback);

      f_thread_mutex_unlock(&thread->mutex->print);
    }
  }
#endif // _di_controller_error_print_locked_

#ifdef __cplusplus
} // extern "C"
#endif
