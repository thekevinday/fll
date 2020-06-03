#include <level_2/execute.h>
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_execute_arguments_add_
  f_return_status fll_execute_arguments_add(const f_string source, const f_string_length length, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return F_status_set_error(F_parameter);
      if (arguments->used > arguments->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (length == 0) return F_data_not;

    f_status status = F_none;

    status = private_fll_execute_arguments_add(source, length, arguments);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_add_

#ifndef _di_fll_execute_arguments_add_parameter_
  f_return_status fll_execute_arguments_add_parameter(const f_string prefix, const f_string_length prefix_length, const f_string name, const f_string_length name_length, const f_string value, const f_string_length value_length, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return F_status_set_error(F_parameter);
      if (arguments->used > arguments->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (name_length == 0) return F_data_not;
    if (value_length == 0) return F_data_not;

    f_status status = F_none;

    status = private_fll_execute_arguments_add_parameter(prefix, prefix_length, name, name_length, value, value_length, arguments);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_add_parameter_

#ifndef _di_fll_execute_arguments_add_parameter_set_
  f_return_status fll_execute_arguments_add_parameter_set(const f_string prefix[], const f_string_length prefix_length[], const f_string name[], const f_string_length name_length[], const f_string value[], const f_string_length value_length[], const f_array_length size, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return F_status_set_error(F_parameter);
      if (arguments->used > arguments->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (size == 0) return F_data_not;

    f_status status = F_none;

    for (f_array_length i = 0; i < size; i++) {
      if (name_length[i] == 0) continue;
      if (value_length[i] == 0) continue;

      status = private_fll_execute_arguments_add_parameter(prefix[i], prefix_length[i], name[i], name_length[i], value[i], value_length[i], arguments);

      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_add_parameter_set_

#ifndef _di_fll_execute_arguments_add_set_
  f_return_status fll_execute_arguments_add_set(const f_string source[], const f_string_length length[], const f_array_length size, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return F_status_set_error(F_parameter);
      if (arguments->used > arguments->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (size == 0) return F_data_not;

    f_status status = F_none;

    for (f_array_length i = 0; i < size; i++) {
      if (length[i] == 0) continue;

      status = private_fll_execute_arguments_add(source[i], length[i], arguments);

      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_add_set_

#ifndef _di_fll_execute_arguments_dynamic_add_
  f_return_status fll_execute_arguments_dynamic_add(const f_string_static source, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (source.used > source.size) return F_status_set_error(F_parameter);
      if (arguments == 0) return F_status_set_error(F_parameter);
      if (arguments->used > arguments->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (source.used == 0) return F_data_not;

    f_status status = F_none;

    status = private_fll_execute_arguments_add(source.string, source.used, arguments);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_dynamic_add_

#ifndef _di_fll_execute_arguments_dynamic_add_parameter_
  f_return_status fll_execute_arguments_dynamic_add_parameter(const f_string_static prefix, const f_string_static name, const f_string_static value, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (prefix.used > prefix.size) return F_status_set_error(F_parameter);
      if (name.used > name.size) return F_status_set_error(F_parameter);
      if (value.used > value.size) return F_status_set_error(F_parameter);
      if (arguments == 0) return F_status_set_error(F_parameter);
      if (arguments->used > arguments->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (name.used == 0) return F_data_not;
    if (value.used == 0) return F_data_not;

    f_status status = F_none;

    status = private_fll_execute_arguments_add_parameter(prefix.string, prefix.used, name.string, name.used, value.string, value.used, arguments);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_execute_arguments_dynamic_add_parameter_

#ifndef _di_fll_execute_arguments_dynamic_add_parameter_set_
  f_return_status fll_execute_arguments_dynamic_add_parameter_set(const f_string_static prefix[], const f_string_static name[], const f_string_static value[], const f_array_length size, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return F_status_set_error(F_parameter);
      if (arguments->used > arguments->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (size == 0) return F_data_not;

    f_status status = F_none;

    for (f_array_length i = 0; i < size; i++) {
      if (prefix[i].used > prefix[i].size) continue;
      if (name[i].used == 0) continue;
      if (name[i].used > name[i].size) continue;
      if (value[i].used == 0) continue;
      if (value[i].used > value[i].size) continue;

      status = private_fll_execute_arguments_add_parameter(prefix[i].string, prefix[i].used, name[i].string, name[i].used, value[i].string, value[i].used, arguments);

      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_dynamic_add_parameter_set_

#ifndef _di_fll_execute_arguments_dynamic_add_set_
  f_return_status fll_execute_arguments_dynamic_add_set(const f_string_static source[], const f_array_length size, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return F_status_set_error(F_parameter);
      if (arguments->used > arguments->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (size == 0) return F_data_not;

    f_status status = F_none;

    for (f_array_length i = 0; i < size; i++) {
      if (source[i].used == 0) continue;
      if (source[i].used > source[i].size) continue;

      status = private_fll_execute_arguments_add(source[i].string, source[i].used, arguments);

      if (F_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_dynamic_add_set_

#ifndef _di_fll_execute_path_
  f_return_status fll_execute_path(const f_string program_path, const f_string_statics arguments, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (result == 0) return F_status_set_error(F_parameter);
      if (arguments.used > arguments.size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string fixed_arguments[arguments.used + 2];

    f_string last_slash = f_string_initialize;
    f_string program_name = f_string_initialize;

    f_string_length name_size = 0;

    f_status status = F_none;

    memset(&fixed_arguments, 0, sizeof(f_string) * (arguments.used + 2));

    last_slash = strrchr(program_path, '/');

    if (last_slash == 0) {
      name_size = strnlen(program_path, f_path_max);

      if (name_size > 1) {
        f_macro_string_new(status, program_name, name_size + 1);

        if (F_status_is_error(status)) return status;

        memcpy(program_name, program_path, name_size);
        memset(program_name, name_size, 0);
      }
      else {
        name_size = 0;
      }
    }
    else {
      name_size = strnlen(last_slash, f_path_max);

      if (name_size > 1) {
        f_macro_string_new(status, program_name, name_size + 1);

        if (F_status_is_error(status)) return status;

        memcpy(program_name, last_slash + 1, name_size);
        memset(program_name, name_size, 0);
      }
      else {
        name_size = 0;
      }
    }

    if (name_size == 0) {
      fixed_arguments[0] = 0;
    }
    else {
      fixed_arguments[0] = program_name;
    }

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_new(status, fixed_arguments[i + 1], arguments.array[i].used + 1);

      if (F_status_is_error(status)) {
        if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

        for (f_string_length j = 0; j < i; j++) {
          f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[j].used + 1);
        } // for

        return status;
      }

      memcpy(fixed_arguments[i + 1], arguments.array[i].string, arguments.array[i].used);
      fixed_arguments[i + 1][arguments.array[i].used] = 0;
    } // for

    // insert the required array terminated
    fixed_arguments[arguments.used + 2] = 0;

    status = f_file_exists(program_path);
    if (F_status_is_error(status)) {
      if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return status;
    }
    else if (status == F_false) {
      if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return F_status_set_error(F_file_found_not);
    }

    pid_t process_id = 0;

    process_id = fork();

    if (process_id < 0) {
      if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return F_status_set_error(F_fork);
    }

    // child
    if (process_id == 0) {
      execv(program_path, fixed_arguments);

      // according to manpages, calling _exit() is safer and should be called here instead of exit()
      _exit(-1);
    }

    // have the parent wait for the child process to finish
    waitpid(process_id, result, 0);

    if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
    } // for

    if (result != 0 && *result != 0) return F_status_set_error(F_failure);

    return F_none;
  }
#endif // _di_fll_execute_path_

#ifndef _di_fll_execute_path_environment_
  f_return_status fll_execute_path_environment(const f_string program_path, const f_string_statics arguments, const f_string_statics names, const f_string_statics values, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (result == 0) return F_status_set_error(F_parameter);
      if (arguments.used > arguments.size) return F_status_set_error(F_parameter);
      if (names.used > names.size) return F_status_set_error(F_parameter);
      if (values.used > values.size) return F_status_set_error(F_parameter);
      if (names.used > values.used) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string fixed_arguments[arguments.used + 2];

    f_string last_slash = f_string_initialize;
    f_string program_name = f_string_initialize;

    f_string_length name_size = 0;

    f_status status = F_none;

    memset(&fixed_arguments, 0, sizeof(f_string) * (arguments.used + 2));

    last_slash = strrchr(program_path, '/');

    if (last_slash == 0) {
      name_size = strnlen(program_path, f_path_max);

      if (name_size > 1) {
        f_macro_string_new(status, program_name, name_size + 1);

        if (F_status_is_error(status)) return status;

        memcpy(program_name, program_path, name_size);
        memset(program_name, name_size, 0);
      }
      else {
        name_size = 0;
      }
    }
    else {
      name_size = strnlen(last_slash, f_path_max);

      if (name_size > 1) {
        f_macro_string_new(status, program_name, name_size + 1);

        if (F_status_is_error(status)) return status;

        memcpy(program_name, last_slash + 1, name_size);
        memset(program_name, name_size, 0);
      }
      else {
        name_size = 0;
      }
    }

    if (name_size == 0) {
      fixed_arguments[0] = 0;
    }
    else {
      fixed_arguments[0] = program_name;
    }

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_new(status, fixed_arguments[i + 1], arguments.array[i].used + 1);

      if (F_status_is_error(status)) {
        if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

        for (f_string_length j = 0; j < i; j++) {
          f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[j].used + 1);
        } // for

        return status;
      }

      memcpy(fixed_arguments[i + 1], arguments.array[i].string, arguments.array[i].used);
      fixed_arguments[i + 1][arguments.array[i].used] = 0;
    } // for

    // insert the required array terminated
    fixed_arguments[arguments.used + 2] = 0;

    status = f_file_exists(program_path);

    if (F_status_is_error(status)) {
      if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return status;
    }
    else if (status == F_false) {
      if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return F_status_set_error(F_file_found_not);
    }

    pid_t process_id = 0;

    process_id = fork();

    if (process_id < 0) {
      if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return F_status_set_error(F_fork);
    }

    // child
    if (process_id == 0) {
      clearenv();

      for (f_array_length i = 0; i < names.used; i++) {
        f_environment_set_dynamic(names.array[i], values.array[i], F_true);
      } // for

      execv(program_path, fixed_arguments);

      // according to manpages, calling _exit() is safer and should be called here instead of exit()
      _exit(-1);
    }

    // have the parent wait for the child process to finish
    waitpid(process_id, result, 0);

    if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
    } // for

    if (result != 0 && *result != 0) return F_status_set_error(F_failure);

    return F_none;
  }
#endif // _di_fll_execute_path_environment_

#ifndef _di_fll_execute_program_
  f_return_status fll_execute_program(const f_string program_name, const f_string_statics arguments, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (result == 0) return F_status_set_error(F_parameter);
      if (arguments.used > arguments.size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string fixed_arguments[arguments.used + 2];

    memset(&fixed_arguments, 0, sizeof(f_string) * (arguments.used + 2));
    fixed_arguments[0] = program_name;

    f_status status = F_none;
    f_string_length i = 0;

    for (; i < arguments.used; i++) {
      f_macro_string_new(status, fixed_arguments[i + 1], arguments.array[i].used + 1);

      if (F_status_is_error(status)) {
        for (f_string_length j = 0; j < i; j++) {
          f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[j].used + 1);
        } // for

        return status;
      }

      memcpy(fixed_arguments[i + 1], arguments.array[i].string, arguments.array[i].used);
      fixed_arguments[i + 1][arguments.array[i].used] = 0;
    } // for

    // insert the required array terminated
    fixed_arguments[arguments.used + 2] = 0;

    pid_t process_id = 0;

    process_id = fork();

    if (process_id < 0) {
      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return F_status_set_error(F_fork);
    }

    // child
    if (process_id == 0) {
      execvp(program_name, fixed_arguments);

      // according to manpages, calling _exit() is safer and should be called here instead of exit()
      _exit(-1);
    }

    // have the parent wait for the child process to finish
    waitpid(process_id, result, 0);

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
    } // for

    if (result != 0 && *result != 0) return F_status_set_error(F_failure);

    return F_none;
  }
#endif // _di_fll_execute_program_

#ifndef _di_fll_execute_program_environment_
  f_return_status fll_execute_program_environment(const f_string program_name, const f_string_statics arguments, const f_string_statics names, const f_string_statics values, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (result == 0) return F_status_set_error(F_parameter);
      if (arguments.used > arguments.size) return F_status_set_error(F_parameter);
      if (names.used > names.size) return F_status_set_error(F_parameter);
      if (values.used > values.size) return F_status_set_error(F_parameter);
      if (names.used > values.used) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string fixed_arguments[arguments.used + 2];

    memset(&fixed_arguments, 0, sizeof(f_string) * (arguments.used + 2));
    fixed_arguments[0] = program_name;

    f_status status = F_none;
    f_string_length i = 0;

    for (; i < arguments.used; i++) {
      f_macro_string_new(status, fixed_arguments[i + 1], arguments.array[i].used + 1);

      if (F_status_is_error(status)) {
        for (f_string_length j = 0; j < i; j++) {
          f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[j].used + 1);
        } // for

        return status;
      }

      memcpy(fixed_arguments[i + 1], arguments.array[i].string, arguments.array[i].used);
      fixed_arguments[i + 1][arguments.array[i].used] = 0;
    } // for

    // insert the required array terminated
    fixed_arguments[arguments.used + 2] = 0;

    f_string_dynamic path = f_string_dynamic_initialize;
    f_string_dynamics paths = f_string_dynamics_initialize;

    status = f_environment_get("PATH", &path);

    if (F_status_is_error(status)) {
      // Do not consider PATH is not available (or valid?) to be an error.
      if (F_status_set_fine(status) == F_invalid || F_status_set_fine(status) == F_failure) {
        status = F_none;
      }
    }
    else {
      status = f_path_explode_dynamic(path, &paths);
    }

    if (F_status_is_error(status)) {
      f_macro_string_dynamic_delete_simple(path);
      f_macro_string_dynamics_delete_simple(paths);
      return status;
    }

    f_macro_string_dynamic_delete(status, path);
    if (F_status_is_error(status)) {
      f_macro_string_dynamics_delete_simple(paths);
      return status;
    }

    const f_string_length program_name_length = strnlen(program_name, f_path_max);
    f_string_dynamic *found = 0;

    for (i = 0; i < paths.used; i++) {
      status = fl_string_append(program_name, program_name_length, &paths.array[i]);

      if (!F_status_is_error(status)) {
        status = fl_string_dynamic_terminate(&paths.array[i]);
      }

      if (!F_status_is_error(status)) {
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
        f_macro_string_dynamics_delete_simple(paths);
        return status;
      }
    } // for

    if (found == 0) {
      f_macro_string_dynamics_delete_simple(paths);
      return F_status_set_error(F_file_found_not);
    }

    char program_path[found->used];

    memcpy(&program_path, found->string, found->used);

    f_macro_string_dynamics_delete(status, paths);
    if (F_status_is_error(status)) {
      return status;
    }

    pid_t process_id = 0;

    process_id = fork();

    if (process_id < 0) {
      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return F_status_set_error(F_fork);
    }

    // child
    if (process_id == 0) {
      clearenv();

      for (f_array_length i = 0; i < names.used; i++) {
        f_environment_set_dynamic(names.array[i], values.array[i], F_true);
      }

      execvp(program_path, fixed_arguments);

      // according to manpages, calling _exit() is safer and should be called here instead of exit()
      _exit(-1);
    }

    // have the parent wait for the child process to finish
    waitpid(process_id, result, 0);

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
    } // for

    if (result != 0 && *result != 0) return F_status_set_error(F_failure);

    return F_none;
  }
#endif // _di_fll_execute_program_environment_

#ifdef __cplusplus
} // extern "C"
#endif
