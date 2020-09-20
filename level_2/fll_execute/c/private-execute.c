#include "execute.h"
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)
  f_return_status private_fll_execute_arguments_add(const f_string_t source, const f_string_length_t length, f_string_dynamics_t *arguments) {
    f_status_t status = F_none;

    if (arguments->used == arguments->size) {
      if (arguments->size + f_memory_default_allocation_step > f_array_length_t_size) {
        if (arguments->size + 1 > f_array_length_t_size) return F_buffer_too_large;
        f_macro_string_dynamics_resize(status, (*arguments), arguments->size + 1);
      }
      else {
        f_macro_string_dynamics_resize(status, (*arguments), arguments->size + f_memory_default_allocation_step);
      }

      if (F_status_is_error(status)) return status;
    }

    f_string_dynamic_t argument = f_string_dynamic_t_initialize;

    status = fl_string_append(source, length, &argument);

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_t_delete_simple(argument);
      return status;
    }

    status = fl_string_dynamic_terminate(&argument);

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_t_delete_simple(argument);
      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    return F_none;
  }
#endif // !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)

#if !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)
  f_return_status private_fll_execute_arguments_add_parameter(const f_string_t prefix, const f_string_length_t prefix_length, const f_string_t name, const f_string_length_t name_length, const f_string_t value, const f_string_length_t value_length, f_string_dynamics_t *arguments) {
    f_status_t status = F_none;

    if (arguments->used + 1 >= arguments->size) {
      if (arguments->size + f_memory_default_allocation_step > f_array_length_t_size) {
        if (arguments->size + 2 > f_array_length_t_size) return F_buffer_too_large;
        f_macro_string_dynamics_resize(status, (*arguments), arguments->size + 2);
      }
      else {
        f_macro_string_dynamics_resize(status, (*arguments), arguments->size + f_memory_default_allocation_step + 1);
      }

      if (F_status_is_error(status)) return status;
    }

    f_string_dynamic_t argument = f_string_dynamic_t_initialize;

    if (prefix_length > 0) {
      status = fl_string_append(prefix, prefix_length, &argument);

      if (F_status_is_error(status)) {
        f_macro_string_dynamic_t_delete_simple(argument);
        return status;
      }
    }

    status = fl_string_append(name, name_length, &argument);

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_t_delete_simple(argument);
      return status;
    }

    status = fl_string_dynamic_terminate(&argument);

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_t_delete_simple(argument);
      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    f_macro_string_dynamic_t_clear(argument);

    status = fl_string_append(value, value_length, &argument);

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_t_delete_simple(argument);
      return status;
    }

    status = fl_string_dynamic_terminate(&argument);

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_t_delete_simple(argument);
      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    return F_none;
  }
#endif // !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)

#ifdef __cplusplus
} // extern "C"
#endif
