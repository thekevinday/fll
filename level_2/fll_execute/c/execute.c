#include "execute.h"
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_execute_arguments_add_
  f_return_status fll_execute_arguments_add(const f_string_t source, const f_string_length_t length, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add(source, length, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_add_

#ifndef _di_fll_execute_arguments_add_parameter_
  f_return_status fll_execute_arguments_add_parameter(const f_string_t prefix, const f_string_length_t prefix_length, const f_string_t name, const f_string_length_t name_length, const f_string_t value, const f_string_length_t value_length, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add_parameter(prefix, prefix_length, name, name_length, value, value_length, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_add_parameter_

#ifndef _di_fll_execute_arguments_add_parameter_set_
  f_return_status fll_execute_arguments_add_parameter_set(const f_string_t prefix[], const f_string_length_t prefix_length[], const f_string_t name[], const f_string_length_t name_length[], const f_string_t value[], const f_string_length_t value_length[], const f_array_length_t size, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < size; i++) {

      status = private_fll_execute_arguments_add_parameter(prefix[i], prefix_length[i], name[i], name_length[i], value[i], value_length[i], arguments);
      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_add_parameter_set_

#ifndef _di_fll_execute_arguments_add_set_
  f_return_status fll_execute_arguments_add_set(const f_string_t source[], const f_string_length_t length[], const f_array_length_t size, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < size; i++) {

      status = private_fll_execute_arguments_add(source[i], length[i], arguments);
      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_add_set_

#ifndef _di_fll_execute_arguments_dynamic_add_
  f_return_status fll_execute_arguments_dynamic_add(const f_string_static_t source, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add(source.string, source.used, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_dynamic_add_

#ifndef _di_fll_execute_arguments_dynamic_add_parameter_
  f_return_status fll_execute_arguments_dynamic_add_parameter(const f_string_static_t prefix, const f_string_static_t name, const f_string_static_t value, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add_parameter(prefix.string, prefix.used, name.string, name.used, value.string, value.used, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_dynamic_add_parameter_

#ifndef _di_fll_execute_arguments_dynamic_add_parameter_set_
  f_return_status fll_execute_arguments_dynamic_add_parameter_set(const f_string_static_t prefix[], const f_string_static_t name[], const f_string_static_t value[], const f_array_length_t size, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < size; i++) {

      status = private_fll_execute_arguments_add_parameter(prefix[i].string, prefix[i].used, name[i].string, name[i].used, value[i].string, value[i].used, arguments);
      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_dynamic_add_parameter_set_

#ifndef _di_fll_execute_arguments_dynamic_add_set_
  f_return_status fll_execute_arguments_dynamic_add_set(const f_string_static_t source[], const f_array_length_t size, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < size; i++) {

      status = private_fll_execute_arguments_add(source[i].string, source[i].used, arguments);
      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_dynamic_add_set_

#ifndef _di_fll_execute_path_
  f_return_status fll_execute_path(const f_string_t program_path, const f_string_statics_t arguments, const f_signal_how_t *signals, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];

    const f_string_t last_slash = strrchr(program_path, '/');
    const f_string_length_t name_size = last_slash ? strnlen(last_slash, f_path_max) : strnlen(program_path, f_path_max);

    char program_name[name_size + 1];

    program_name[name_size] = 0;

    private_fll_execute_path_arguments_fixate(last_slash ? last_slash : program_path, arguments, name_size, program_name, fixed_arguments);

    {
      const f_status_t status = f_file_exists(program_path);

      if (F_status_is_error(status)) {
        return status;
      }
      else if (status == F_false) {
        return F_status_set_error(F_file_found_not);
      }
    }

    return private_fll_execute_fork(program_name, fixed_arguments, F_false, signals, result);
  }
#endif // _di_fll_execute_path_

#ifndef _di_fll_execute_path_environment_
  f_return_status fll_execute_path_environment(const f_string_t program_path, const f_string_statics_t arguments, const f_string_statics_t names, const f_string_statics_t values, const f_signal_how_t *signals, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];

    const f_string_t last_slash = strrchr(program_path, '/');
    const f_string_length_t name_size = last_slash ? strnlen(last_slash, f_path_max) : strnlen(program_path, f_path_max);

    char program_name[name_size + 1];

    private_fll_execute_path_arguments_fixate(last_slash ? last_slash : program_path, arguments, name_size, program_name, fixed_arguments);

    {
      const f_status_t status = f_file_exists(program_path);

      if (F_status_is_error(status)) {
        return status;
      }
      else if (status == F_false) {
        return F_status_set_error(F_file_found_not);
      }
    }

    return private_fll_execute_fork_environment(program_name, fixed_arguments, F_false, names, values, signals, result);
  }
#endif // _di_fll_execute_path_environment_

#ifndef _di_fll_execute_program_
  f_return_status fll_execute_program(const f_string_t program_name, const f_string_statics_t arguments, const f_signal_how_t *signals, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];

    fixed_arguments[0] = program_name;

    for (f_array_length_t i = 0; i < arguments.used; i++) {
      fixed_arguments[i + 1] = arguments.array[i].string;
    } // for

    // insert the required array terminated.
    fixed_arguments[arguments.used + 1] = 0;

    return private_fll_execute_fork(program_name, fixed_arguments, F_true, signals, result);
  }
#endif // _di_fll_execute_program_

#ifndef _di_fll_execute_program_environment_
  f_return_status fll_execute_program_environment(const f_string_t program_name, const f_string_statics_t arguments, const f_string_statics_t names, const f_string_statics_t values, const f_signal_how_t *signals, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];

    fixed_arguments[0] = program_name;

    for (f_array_length_t i = 0; i < arguments.used; i++) {
      fixed_arguments[i + 1] = arguments.array[i].string;
    } // for

    // insert the required array terminated.
    fixed_arguments[arguments.used + 1] = 0;

    f_string_dynamic_t path = f_string_dynamic_t_initialize;
    f_string_dynamics_t paths = f_string_dynamics_t_initialize;

    f_status_t status = f_environment_get("PATH", &path);

    if (F_status_is_error(status)) {

      // Do not consider PATH is not available (or valid?) to be an error.
      if (F_status_set_fine(status) == F_valid_not || F_status_set_fine(status) == F_failure) {
        status = F_none;
      }
    }
    else {
      status = fl_environment_path_explode_dynamic(path, &paths);
    }

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_t_delete_simple(path);
      f_macro_string_dynamics_t_delete_simple(paths);
      return status;
    }

    f_macro_string_dynamic_t_delete(status, path);

    if (F_status_is_error(status)) {
      f_macro_string_dynamics_t_delete_simple(paths);
      return status;
    }

    const f_string_length_t program_name_length = strnlen(program_name, f_path_max);
    f_string_dynamic_t *found = 0;

    for (f_array_length_t i = 0; i < paths.used; i++) {

      status = fl_string_append(program_name, program_name_length, &paths.array[i]);

      if (F_status_is_error_not(status)) {
        status = fl_string_dynamic_terminate(&paths.array[i]);
      }

      if (F_status_is_error_not(status)) {
        status = f_file_exists(paths.array[i].string);

        if (status == F_true) {
          found = &paths.array[i];
          break;
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          // don't consider bad/non-accessible paths an error, just ignore them.
          if (status == F_name) {
            continue;
          }
          else if (status == F_directory) {
            continue;
          }
          else if (status == F_access_denied) {
            continue;
          }
        }
      }

      if (F_status_is_error(status)) {
        f_macro_string_dynamics_t_delete_simple(paths);
        return status;
      }
    } // for

    if (!found) {
      f_macro_string_dynamics_t_delete_simple(paths);
      return F_status_set_error(F_file_found_not);
    }

    char program_path[found->used];

    memcpy(&program_path, found->string, found->used);

    f_macro_string_dynamics_t_delete(status, paths);
    if (F_status_is_error(status)) return status;

    return private_fll_execute_fork_environment(program_name, fixed_arguments, F_true, names, values, signals, result);
  }
#endif // _di_fll_execute_program_environment_

#ifdef __cplusplus
} // extern "C"
#endif
