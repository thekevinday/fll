#include "execute.h"
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_execute_arguments_add_
  f_status_t fll_execute_arguments_add(const f_string_t source, const f_string_length_t length, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add(source, length, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_add_

#ifndef _di_fll_execute_arguments_add_parameter_
  f_status_t fll_execute_arguments_add_parameter(const f_string_t prefix, const f_string_length_t prefix_length, const f_string_t name, const f_string_length_t name_length, const f_string_t value, const f_string_length_t value_length, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add_parameter(prefix, prefix_length, name, name_length, value, value_length, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_add_parameter_

#ifndef _di_fll_execute_arguments_add_parameter_set_
  f_status_t fll_execute_arguments_add_parameter_set(const f_string_t prefix[], const f_string_length_t prefix_length[], const f_string_t name[], const f_string_length_t name_length[], const f_string_t value[], const f_string_length_t value_length[], const f_array_length_t size, f_string_dynamics_t *arguments) {
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
  f_status_t fll_execute_arguments_add_set(const f_string_t source[], const f_string_length_t length[], const f_array_length_t size, f_string_dynamics_t *arguments) {
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
  f_status_t fll_execute_arguments_dynamic_add(const f_string_static_t source, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add(source.string, source.used, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_dynamic_add_

#ifndef _di_fll_execute_arguments_dynamic_add_parameter_
  f_status_t fll_execute_arguments_dynamic_add_parameter(const f_string_static_t prefix, const f_string_static_t name, const f_string_static_t value, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add_parameter(prefix.string, prefix.used, name.string, name.used, value.string, value.used, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_dynamic_add_parameter_

#ifndef _di_fll_execute_arguments_dynamic_add_parameter_set_
  f_status_t fll_execute_arguments_dynamic_add_parameter_set(const f_string_static_t prefix[], const f_string_static_t name[], const f_string_static_t value[], const f_array_length_t size, f_string_dynamics_t *arguments) {
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
  f_status_t fll_execute_arguments_dynamic_add_set(const f_string_static_t source[], const f_array_length_t size, f_string_dynamics_t *arguments) {
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

#ifndef _di_fll_execute_into_
  f_status_t fll_execute_into(const f_string_t program, const f_string_statics_t arguments, const uint8_t option, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (!program && !arguments.used) return F_status_set_error(F_parameter);
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];

    const f_string_t last_slash = strrchr(program ? program : arguments.array[0].string, f_path_separator_s[0]);
    const f_string_length_t name_size = last_slash ? strnlen(last_slash, f_path_length_max) : strnlen(program ? program : arguments.array[0].string, f_path_length_max);

    char program_name[name_size + 1];

    program_name[name_size] = 0;

    private_fll_execute_path_arguments_fixate(last_slash ? last_slash : program ? program : arguments.array[0].string, arguments, !program, name_size, program_name, fixed_arguments);

    const int code = option & fl_execute_parameter_option_path ? execv(program, fixed_arguments) : execvp(program, fixed_arguments);

    // generally this does not return, but in some cases (such as with scripts) this does return so handle the results.
    if (result) {
      *result = code;
    }

    if (option & fl_execute_parameter_option_exit) {
      exit(code);
    }

    if (code) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fll_execute_into_

#ifndef _di_fll_execute_program_
  f_status_t fll_execute_program(const f_string_t program, const f_string_statics_t arguments, fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (!program && !arguments.used) return F_status_set_error(F_parameter);
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];

    const f_string_t last_slash = strrchr(program ? program : arguments.array[0].string, f_path_separator_s[0]);
    const f_string_length_t name_size = last_slash ? strnlen(last_slash, f_path_length_max) : strnlen(program ? program : arguments.array[0].string, f_path_length_max);

    char program_name[name_size + 1];

    program_name[name_size] = 0;

    private_fll_execute_path_arguments_fixate(last_slash ? last_slash : program ? program : arguments.array[0].string, arguments, !program, name_size, program_name, fixed_arguments);

    // when the environment is to be cleared, a full path must be used.
    if (parameter && !(parameter->option & fl_execute_parameter_option_path) && parameter->environment) {
      f_string_dynamic_t path = f_string_dynamic_t_initialize;
      f_string_dynamics_t paths = f_string_dynamics_t_initialize;

      f_status_t status = f_environment_get(f_path_environment_s, &path);

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
        f_string_dynamic_delete(&path);
        f_string_dynamics_delete(&paths);

        return status;
      }

      status = f_string_dynamic_delete(&path);

      if (F_status_is_error(status)) {
        f_macro_string_dynamics_t_delete_simple(paths);

        return status;
      }

      f_string_dynamic_t *found = 0;

      for (f_array_length_t i = 0; i < paths.used; i++) {

        status = f_string_append(program_name, name_size, &paths.array[i]);

        if (F_status_is_error_not(status)) {
          status = f_string_dynamic_terminate(&paths.array[i]);
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
          f_string_dynamics_delete(&paths);

          return status;
        }
      } // for

      if (!found) {
        f_string_dynamics_delete(&paths);

        return F_status_set_error(F_file_found_not);
      }

      char program_path[found->used];

      memcpy(&program_path, found->string, found->used);

      status = f_string_dynamics_delete(&paths);
      if (F_status_is_error(status)) return status;

      if (parameter && parameter->data) {
        return private_fll_execute_fork_data(program_path, fixed_arguments, parameter, as, result);
      }

      return private_fll_execute_fork(program_path, fixed_arguments, parameter, as, result);
    }

    if (parameter && parameter->data) {
      return private_fll_execute_fork_data(program, fixed_arguments, parameter, as, result);
    }

    return private_fll_execute_fork(program, fixed_arguments, parameter, as, result);
  }
#endif // _di_fll_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif
