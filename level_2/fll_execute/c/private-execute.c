#include <level_2/execute.h>
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)
  f_return_status private_fll_execute_arguments_add(const f_string source, const f_string_length length, f_string_dynamics *arguments) {
    f_status status = f_none;

    if (arguments->used >= arguments->size) {
      if (arguments->size + f_memory_default_allocation_step > f_array_length_size) {
        if (arguments->size + 1 > f_array_length_size) return f_array_too_large;
        f_macro_string_dynamics_resize(status, (*arguments), arguments->size + 1);
      }
      else {
        f_macro_string_dynamics_resize(status, (*arguments), arguments->size + f_memory_default_allocation_step);
      }

      if (f_status_is_error(status)) return status;
    }

    f_string_dynamic argument = f_string_dynamic_initialize;

    status = fl_string_append(source, 0, length - 1, &argument);
    if (f_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(argument);
      return status;
    }

    status = fl_string_dynamic_terminate(&argument);
    if (f_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(argument);
      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    return f_none;
  }
#endif // !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)

#if !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)
  f_return_status private_fll_execute_arguments_add_parameter(const f_string prefix, const f_string_length prefix_length, const f_string name, const f_string_length name_length, const f_string value, const f_string_length value_length, f_string_dynamics *arguments) {
    f_status status = f_none;

    if (arguments->used + 1 >= arguments->size) {
      if (arguments->size + f_memory_default_allocation_step > f_array_length_size) {
        if (arguments->size + 2 > f_array_length_size) return f_array_too_large;
        f_macro_string_dynamics_resize(status, (*arguments), arguments->size + 2);
      }
      else {
        f_macro_string_dynamics_resize(status, (*arguments), arguments->size + f_memory_default_allocation_step + 1);
      }

      if (f_status_is_error(status)) return status;
    }

    f_string_dynamic argument = f_string_dynamic_initialize;

    if (prefix_length > 0) {
      status = fl_string_append(prefix, 0, prefix_length - 1, &argument);
      if (f_status_is_error(status)) {
        f_macro_string_dynamic_delete_simple(argument);
        return status;
      }
    }

    status = fl_string_append(name, 0, name_length - 1, &argument);
    if (f_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(argument);
      return status;
    }

    status = fl_string_dynamic_terminate(&argument);
    if (f_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(argument);
      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    f_macro_string_dynamic_clear(argument);

    status = fl_string_append(value, 0, value_length - 1, &argument);
    if (f_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(argument);
      return status;
    }

    status = fl_string_dynamic_terminate(&argument);
    if (f_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(argument);
      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    return f_none;
  }
#endif // !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)

#ifdef __cplusplus
} // extern "C"
#endif
