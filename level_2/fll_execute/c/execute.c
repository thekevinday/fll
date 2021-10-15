#include "execute.h"
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_execute_arguments_add_
  f_status_t fll_execute_arguments_add(const f_string_t source, const f_array_length_t length, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add(source, length, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_add_

#ifndef _di_fll_execute_arguments_add_parameter_
  f_status_t fll_execute_arguments_add_parameter(const f_string_t prefix, const f_array_length_t prefix_length, const f_string_t name, const f_array_length_t name_length, const f_string_t value, const f_array_length_t value_length, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_status_t status = private_fll_execute_arguments_add_parameter(prefix, prefix_length, name, name_length, value, value_length, arguments);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_add_parameter_

#ifndef _di_fll_execute_arguments_add_parameter_set_
  f_status_t fll_execute_arguments_add_parameter_set(const f_string_t prefix[], const f_array_length_t prefix_length[], const f_string_t name[], const f_array_length_t name_length[], const f_string_t value[], const f_array_length_t value_length[], const f_array_length_t size, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < size; ++i) {

      status = private_fll_execute_arguments_add_parameter(prefix[i], prefix_length[i], name[i], name_length[i], value[i], value_length[i], arguments);
      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_add_parameter_set_

#ifndef _di_fll_execute_arguments_add_set_
  f_status_t fll_execute_arguments_add_set(const f_string_t source[], const f_array_length_t length[], const f_array_length_t size, f_string_dynamics_t *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < size; ++i) {

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

    for (f_array_length_t i = 0; i < size; ++i) {

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

    for (f_array_length_t i = 0; i < size; ++i) {

      status = private_fll_execute_arguments_add(source[i].string, source[i].used, arguments);
      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_dynamic_add_set_

#ifndef _di_fll_execute_into_
  f_status_t fll_execute_into(const f_string_t program, const f_string_statics_t arguments, const uint8_t option, const f_string_maps_t *environment, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (!program && !arguments.used) return F_status_set_error(F_parameter);
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];

    const f_string_t last_slash = strrchr(program ? program : arguments.array[0].string, f_path_separator_s[0]);
    const f_array_length_t size_name = last_slash ? strnlen(last_slash + 1, f_path_length_max) : strnlen(program ? program : arguments.array[0].string, f_path_length_max);

    char program_name[size_name + 1];

    private_fll_execute_path_arguments_fixate(program ? program : arguments.array[0].string, arguments, last_slash, !program, size_name, program_name, fixed_arguments);

    int code = 0;

    // full path is explicitly requested.
    if (option & fl_execute_parameter_option_path) {
      f_string_dynamic_t path = f_string_dynamic_t_initialize;
      f_string_dynamics_t paths = f_string_dynamics_t_initialize;
      f_string_dynamic_t *found = 0;

      f_status_t status = F_none;

      if (last_slash) {
        status = f_file_exists(program ? program : arguments.array[0].string);

        if (status != F_true) {
          macro_f_string_dynamics_t_delete_simple(paths);

          return F_status_set_error(F_file_found_not);
        }

        path.string = program ? program : arguments.array[0].string;
        path.used = strnlen(program ? program : arguments.array[0].string, f_path_length_max);
        found = &path;
      }
      else {
        status = f_environment_get(f_path_environment_s, &path);

        if (F_status_is_error(status)) {

          // Do not consider PATH is not available (or valid?) to be an error.
          if (F_status_set_fine(status) == F_valid_not || F_status_set_fine(status) == F_failure) {
            status = F_none;
          }
        }
        else {
          status = fl_environment_path_explode_dynamic(path, &paths);
        }

        macro_f_string_dynamic_t_delete_simple(path);

        if (F_status_is_error(status)) {
          macro_f_string_dynamics_t_delete_simple(paths);

          return status;
        }

        for (f_array_length_t i = 0; i < paths.used; ++i) {

          status = f_string_append(program_name, size_name, &paths.array[i]);

          if (F_status_is_error_not(status)) {
            status = f_string_dynamic_terminate_after(&paths.array[i]);
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
            macro_f_string_dynamics_t_delete_simple(paths);

            return status;
          }
        } // for

        if (!found) {
          macro_f_string_dynamics_t_delete_simple(paths);

          return F_status_set_error(F_file_found_not);
        }
      }

      char program_path[found->used + 1];
      program_path[found->used] = 0;

      memcpy(&program_path, found->string, found->used);

      status = macro_f_string_dynamics_t_delete_simple(paths);
      if (F_status_is_error(status)) return status;

      fixed_arguments[0] = program_path;

      if (environment) {
        clearenv();

        for (f_array_length_t i = 0; i < environment->used; ++i) {
          f_environment_set_dynamic(environment->array[i].name, environment->array[i].value, F_true);
        } // for
      }

      code = execv(program_path, fixed_arguments);
    }
    else {
      if (environment) {
        clearenv();

        for (f_array_length_t i = 0; i < environment->used; ++i) {
          f_environment_set_dynamic(environment->array[i].name, environment->array[i].value, F_true);
        } // for
      }

      code = last_slash ? execv(program ? program : arguments.array[0].string, fixed_arguments) : execvp(program ? program : arguments.array[0].string, fixed_arguments);
    }

    // generally this does not return, but in some cases (such as with scripts) this does return so handle the results.
    if (code < 0) {
      if (errno == EACCES) code = F_execute_access;
      else if (errno == E2BIG) code = F_execute_too_large;
      else if (errno == EAGAIN) code = F_execute_resource_not;
      else if (errno == EFAULT) code = F_execute_buffer;
      else if (errno == EINVAL) code = F_execute_parameter;
      else if (errno == EIO) code = F_execute_input_output;
      else if (errno == EISDIR) code = F_execute_file_type_directory;
      else if (errno == EIO) code = F_execute_input_output;
      else if (errno == ELIBBAD) code = F_execute_valid_not;
      else if (errno == ELOOP) code = F_execute_loop;
      else if (errno == EMFILE) code = F_execute_resource_not;
      else if (errno == ENAMETOOLONG) code = F_execute_name_not;
      else if (errno == ENFILE) code = F_execute_resource_not;
      else if (errno == ENOENT) code = F_execute_file_found_not;
      else if (errno == ENOEXEC) code = F_execute_bad;
      else if (errno == ENOMEM) code = F_execute_memory_not;
      else if (errno == ENOTDIR) code = F_execute_directory_not;
      else if (errno == EPERM) code = F_execute_prohibited;
      else if (errno == ETXTBSY) code = F_execute_busy;
      else code = F_execute_failure;
    }
    else {
      code = 0;
    }

    if (result) {
      int *r = (int *) result;
      *r = code;
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
  f_status_t fll_execute_program(const f_string_t program, const f_string_statics_t arguments, fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, void *result) {
    #ifndef _di_level_2_parameter_checking_
      if (!program && !arguments.used) return F_status_set_error(F_parameter);
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];

    const f_string_t last_slash = strrchr(program ? program : arguments.array[0].string, f_path_separator_s[0]);
    const f_array_length_t size_name = last_slash ? strnlen(last_slash + 1, f_path_length_max) : strnlen(program ? program : arguments.array[0].string, f_path_length_max);

    char program_name[size_name + 1];

    private_fll_execute_path_arguments_fixate(program ? program : arguments.array[0].string, arguments, last_slash, !program, size_name, program_name, fixed_arguments);

    // determine full path when the environment is to be cleared or full path is explicitly requested.
    if (parameter && parameter->environment || parameter && (parameter->option & fl_execute_parameter_option_path)) {
      f_string_dynamic_t path = f_string_dynamic_t_initialize;
      f_string_dynamics_t paths = f_string_dynamics_t_initialize;
      f_string_dynamic_t *found = 0;

      f_status_t status = F_none;

      if (last_slash) {
        status = f_file_exists(program ? program : arguments.array[0].string);

        if (status != F_true) {
          macro_f_string_dynamics_t_delete_simple(paths);

          return F_status_set_error(F_file_found_not);
        }

        path.string = program ? program : arguments.array[0].string;
        path.used = strnlen(program ? program : arguments.array[0].string, f_path_length_max);
        found = &path;
      }
      else {
        status = f_environment_get(f_path_environment_s, &path);

        if (F_status_is_error(status)) {

          // Do not consider PATH is not available (or valid?) to be an error.
          if (F_status_set_fine(status) == F_valid_not || F_status_set_fine(status) == F_failure) {
            status = F_none;
          }
        }
        else {
          status = fl_environment_path_explode_dynamic(path, &paths);
        }

        macro_f_string_dynamic_t_delete_simple(path);

        if (F_status_is_error(status)) {
          macro_f_string_dynamics_t_delete_simple(paths);

          return status;
        }

        for (f_array_length_t i = 0; i < paths.used; ++i) {

          status = f_string_append(program_name, size_name, &paths.array[i]);

          if (F_status_is_error_not(status)) {
            status = f_string_dynamic_terminate_after(&paths.array[i]);
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
            macro_f_string_dynamics_t_delete_simple(paths);

            return status;
          }
        } // for

        if (!found) {
          macro_f_string_dynamics_t_delete_simple(paths);

          return F_status_set_error(F_file_found_not);
        }
      }

      char program_path[found->used + 1];
      program_path[found->used] = 0;

      memcpy(&program_path, found->string, found->used);

      status = macro_f_string_dynamics_t_delete_simple(paths);
      if (F_status_is_error(status)) return status;

      if (parameter && (parameter->option & fl_execute_parameter_option_path)) {
        fixed_arguments[0] = program_path;
      }

      if (parameter && parameter->data) {
        return private_fll_execute_fork_data(F_true, program_path, fixed_arguments, parameter, as, result);
      }

      return private_fll_execute_fork(F_true, program_path, fixed_arguments, parameter, as, result);
    }

    if (parameter && parameter->data) {
      return private_fll_execute_fork_data(last_slash, program ? program : arguments.array[0].string, fixed_arguments, parameter, as, result);
    }

    return private_fll_execute_fork(last_slash, program ? program : arguments.array[0].string, fixed_arguments, parameter, as, result);
  }
#endif // _di_fll_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif
