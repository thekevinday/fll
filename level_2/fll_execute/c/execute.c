#include "execute.h"
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_execute_arguments_add_
  f_status_t fll_execute_arguments_add(const f_string_static_t source, f_string_dynamics_t * const arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &arguments->array, &arguments->used, &arguments->size);
      if (F_status_is_error(status)) return status;

      status = private_fll_execute_arguments_add(source, arguments);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_fll_execute_arguments_add_

#ifndef _di_fll_execute_arguments_add_parameter_
  f_status_t fll_execute_arguments_add_parameter(const f_string_static_t prefix, const f_string_static_t name, const f_string_static_t value, f_string_dynamics_t * const arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &arguments->array, &arguments->used, &arguments->size);
      if (F_status_is_error(status)) return status;

      status = private_fll_execute_arguments_add_parameter(prefix, name, value, arguments);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_fll_execute_arguments_add_parameter_

#ifndef _di_fll_execute_arguments_add_parameter_set_
  f_status_t fll_execute_arguments_add_parameter_set(const f_string_static_t prefix[], const f_string_static_t name[], const f_string_static_t value[], const f_number_unsigned_t size, f_string_dynamics_t * const arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    {
      // Allocate "size * 2" to ensure space for both the name and value are available.
      f_status_t status = f_memory_array_increase_by(size * 2, sizeof(f_string_dynamic_t), (void **) &arguments->array, &arguments->used, &arguments->size);

      for (f_number_unsigned_t i = 0; i < size; ++i) {

        status = private_fll_execute_arguments_add_parameter(prefix[i], name[i], value[i], arguments);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_fll_execute_arguments_add_parameter_set_

#ifndef _di_fll_execute_arguments_add_set_
  f_status_t fll_execute_arguments_add_set(const f_string_static_t source[], const f_number_unsigned_t size, f_string_dynamics_t * const arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    {
      f_status_t status = f_memory_array_increase_by(size, sizeof(f_string_dynamic_t), (void **) &arguments->array, &arguments->used, &arguments->size);

      for (f_number_unsigned_t i = 0; i < size; ++i) {

        status = private_fll_execute_arguments_add(source[i], arguments);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_fll_execute_arguments_add_set_

#ifndef _di_fll_execute_into_
  f_status_t fll_execute_into(const f_string_static_t program, const f_string_statics_t arguments, const uint8_t option, const f_string_maps_t *environment, int * const result) {
    #ifndef _di_level_2_parameter_checking_
      if (!program.used && !arguments.used) return F_status_set_error(F_parameter);
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // Create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];
    f_string_static_t program_name = f_string_static_t_initialize;

    const f_string_t last_slash = (f_string_t) strrchr((program.used ? program.string : arguments.array[0].string), (char) f_path_separator_s.string[0]);

    if (last_slash) {
      program_name.used = strnlen((last_slash + 1), F_path_length_max_d);
    }
    else {
      program_name.used = program.used ? program.used : arguments.array[0].used;
    }

    f_char_t program_name_string[program_name.used + 1];
    program_name.string = program_name_string;

    private_fll_execute_path_arguments_fixate(program.used ? program : arguments.array[0], arguments, last_slash, !program.used, program_name, fixed_arguments);

    int code = 0;

    if (option & FL_execute_parameter_option_session_d) {
      setsid();
    }

    // Full path is explicitly requested.
    if (option & FL_execute_parameter_option_path_d) {
      f_string_dynamic_t path = f_string_dynamic_t_initialize;
      f_string_dynamics_t paths = f_string_dynamics_t_initialize;
      f_string_dynamic_t *found = 0;

      f_status_t status = F_okay;

      if (last_slash) {
        status = f_file_exists(program.used ? program : arguments.array[0], F_true);

        if (status != F_true) {
          return F_status_set_error(F_file_found_not);
        }

        path.string = program.used ? program.string : arguments.array[0].string;
        path.used = program.used ? program.used : arguments.array[0].used;
        found = &path;
      }
      else {
        status = f_environment_get(f_path_environment_s, &path);

        if (F_status_is_error(status)) {

          // Do not consider PATH is not available (or not valid?) to be an error.
          if (F_status_set_fine(status) == F_valid_not || F_status_set_fine(status) == F_failure) {
            status = F_okay;
          }
        }
        else {
          status = fl_environment_path_explode(path, &paths);
        }

        f_memory_array_resize(0, sizeof(f_char_t), (void **) &path.string, &path.used, &path.size);

        if (F_status_is_error(status)) {
          f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

          return status;
        }

        // Search each individual path in PATH until a match is found.
        for (f_number_unsigned_t i = 0; i < paths.used; ++i) {

          status = f_string_dynamic_append(program_name, &paths.array[i]);

          if (F_status_is_error_not(status)) {
            status = f_file_exists(paths.array[i], F_true);

            if (status == F_true) {
              found = &paths.array[i];

              break;
            }

            if (F_status_is_error(status)) {
              status = F_status_set_fine(status);

              // Don't consider bad/non-accessible paths an error, just ignore them.
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
            f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

            return status;
          }
        } // for

        if (!found) {
          f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

          return F_status_set_error(F_file_found_not);
        }
      }

      f_char_t program_path[found->used + 1];
      program_path[found->used] = 0;

      memcpy(&program_path, found->string, sizeof(f_char_t) * found->used);

      f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

      fixed_arguments[0] = program_path;

      if (environment) {
        clearenv();

        for (f_number_unsigned_t i = 0; i < environment->used; ++i) {
          f_environment_set(environment->array[i].key, environment->array[i].value, F_true);
        } // for
      }

      code = execv(program_path, (char **) fixed_arguments);
    }
    else {
      if (environment) {
        clearenv();

        for (f_number_unsigned_t i = 0; i < environment->used; ++i) {
          f_environment_set(environment->array[i].key, environment->array[i].value, F_true);
        } // for
      }

      if (last_slash) {
        code = execv((program.used ? program.string : arguments.array[0].string), (char **) fixed_arguments);
      }
      else {
        code = execvp((program.used ? program.string : arguments.array[0].string), (char **) fixed_arguments);
      }
    }

    // Generally this does not return, but in some cases (such as with scripts) this does return so handle the results.
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

    if (option & FL_execute_parameter_option_exit_d) {
      exit(code);
    }

    if (code) {
      return F_status_set_error(F_failure);
    }

    return F_okay;
  }
#endif // _di_fll_execute_into_

#ifndef _di_fll_execute_program_
  f_status_t fll_execute_program(const f_string_static_t program, const f_string_statics_t arguments, fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, void * const result) {
    #ifndef _di_level_2_parameter_checking_
      if (!program.used && !arguments.used) return F_status_set_error(F_parameter);
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // Create a string array that is compatible with execv() calls.
    f_string_t fixed_arguments[arguments.used + 2];
    f_string_static_t program_name = f_string_static_t_initialize;

    const f_string_t last_slash = program.used
      ? (f_string_t) strrchr(program.string, (char) f_path_separator_s.string[0])
      : arguments.used && arguments.array[0].used
        ? (f_string_t) strrchr(arguments.array[0].string, (char) f_path_separator_s.string[0])
        : 0;

    if (last_slash) {
      program_name.used = strnlen((last_slash + 1), F_path_length_max_d);
    }
    else {
      program_name.used = program.used
        ? program.used
        : arguments.used && arguments.array[0].used
          ? arguments.array[0].used
          : 0;
    }

    f_char_t program_name_string[program_name.used + 1];
    program_name.string = program_name_string;

    private_fll_execute_path_arguments_fixate(program.used ? program : arguments.array[0], arguments, last_slash, !program.used, program_name, fixed_arguments);

    // Determine full path when the environment is to be cleared or full path is explicitly requested.
    if ((parameter && parameter->environment) || (parameter && (parameter->option & FL_execute_parameter_option_path_d))) {
      f_string_dynamic_t path = f_string_dynamic_t_initialize;
      f_string_dynamics_t paths = f_string_dynamics_t_initialize;
      f_string_dynamic_t *found = 0;

      f_status_t status = F_okay;

      if (last_slash) {
        status = f_file_exists(program.used ? program : arguments.array[0], F_true);

        if (status != F_true) {
          f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

          return F_status_set_error(F_file_found_not);
        }

        path.string = program.used ? program.string : arguments.array[0].string;
        path.used = program.used ? program.used : arguments.array[0].used;
        found = &path;
      }
      else {
        status = f_environment_get(f_path_environment_s, &path);

        if (F_status_is_error(status)) {

          // Do not consider PATH to be not available (or not valid?) to be an error.
          if (F_status_set_fine(status) == F_valid_not || F_status_set_fine(status) == F_failure) {
            status = F_okay;
          }
        }
        else {
          status = fl_environment_path_explode(path, &paths);
        }

        f_memory_array_resize(0, sizeof(f_char_t), (void **) &path.string, &path.used, &path.size);

        if (F_status_is_error(status)) {
          f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

          return status;
        }

        // Search each individual path in PATH until a match is found.
        for (f_number_unsigned_t i = 0; i < paths.used; ++i) {

          status = f_string_dynamic_append(program_name, &paths.array[i]);

          if (F_status_is_error_not(status)) {
            status = f_file_exists(paths.array[i], F_true);

            if (status == F_true) {
              found = &paths.array[i];

              break;
            }

            if (F_status_is_error(status)) {
              status = F_status_set_fine(status);

              // Don't consider bad/non-accessible paths an error, just ignore them.
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
            f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

            return status;
          }
        } // for

        if (!found) {
          f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

          return F_status_set_error(F_file_found_not);
        }
      }

      f_char_t program_path[found->used + 1];
      program_path[found->used] = 0;

      memcpy(&program_path, found->string, sizeof(f_char_t) * found->used);

      program_name.string = program_path;
      program_name.used = found->used;

      f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &paths.array, &paths.used, &paths.size, &f_string_dynamics_delete_callback);

      if (parameter && (parameter->option & FL_execute_parameter_option_path_d)) {
        fixed_arguments[0] = program_path;
      }

      if (parameter && parameter->data) {
        return private_fll_execute_fork_data(F_true, program_name, fixed_arguments, parameter, as, result);
      }

      return private_fll_execute_fork(F_true, program_name, fixed_arguments, parameter, as, result);
    }

    if (parameter && parameter->data) {
      return private_fll_execute_fork_data(last_slash, program.used ? program : arguments.array[0], fixed_arguments, parameter, as, result);
    }

    return private_fll_execute_fork(last_slash, program.used ? program : arguments.array[0], fixed_arguments, parameter, as, result);
  }
#endif // _di_fll_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif
