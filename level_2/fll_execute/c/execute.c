#include <level_2/execute.h>
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_execute_arguments_add_
  f_return_status fll_execute_arguments_add(const f_string source, const f_string_length length, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments->used > arguments->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (length == 0) return f_no_data;

    f_status status = f_none;

    status = private_fll_execute_arguments_add(source, length, arguments);

    if (f_status_is_error(status)) return status;

    return f_none;
  }
#endif // _di_fll_execute_arguments_add_

#ifndef _di_fll_execute_arguments_add_parameter_
  f_return_status fll_execute_arguments_add_parameter(const f_string prefix, const f_string_length prefix_length, const f_string name, const f_string_length name_length, const f_string value, const f_string_length value_length, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments->used > arguments->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (name_length == 0) return f_no_data;
    if (value_length == 0) return f_no_data;

    f_status status = f_none;

    status = private_fll_execute_arguments_add_parameter(prefix, prefix_length, name, name_length, value, value_length, arguments);

    if (f_status_is_error(status)) return status;

    return f_none;
  }
#endif // _di_fll_execute_arguments_add_parameter_

#ifndef _di_fll_execute_arguments_add_parameter_set_
  f_return_status fll_execute_arguments_add_parameter_set(const f_string prefix[], const f_string_length prefix_length[], const f_string name[], const f_string_length name_length[], const f_string value[], const f_string_length value_length[], const f_array_length size, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments->used > arguments->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (size == 0) return f_no_data;

    f_status status = f_none;

    for (f_array_length i = 0; i < size; i++) {
      if (name_length[i] == 0) continue;
      if (value_length[i] == 0) continue;

      status = private_fll_execute_arguments_add_parameter(prefix[i], prefix_length[i], name[i], name_length[i], value[i], value_length[i], arguments);

      if (f_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_add_parameter_set_

#ifndef _di_fll_execute_arguments_add_set_
  f_return_status fll_execute_arguments_add_set(const f_string source[], const f_string_length length[], const f_array_length size, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments->used > arguments->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (size == 0) return f_no_data;

    f_status status = f_none;

    for (f_array_length i = 0; i < size; i++) {
      if (length[i] == 0) continue;

      status = private_fll_execute_arguments_add(source[i], length[i], arguments);

      if (f_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_add_set_

#ifndef _di_fll_execute_arguments_dynamic_add_
  f_return_status fll_execute_arguments_dynamic_add(const f_string_static source, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (source.used > source.size) return f_status_set_error(f_invalid_parameter);
      if (arguments == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments->used > arguments->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (source.used == 0) return f_no_data;

    f_status status = f_none;

    status = private_fll_execute_arguments_add(source.string, source.used, arguments);

    if (f_status_is_error(status)) return status;

    return f_none;
  }
#endif // _di_fll_execute_arguments_dynamic_add_

#ifndef _di_fll_execute_arguments_dynamic_add_parameter_
  f_return_status fll_execute_arguments_dynamic_add_parameter(const f_string_static prefix, const f_string_static name, const f_string_static value, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (prefix.used > prefix.size) return f_status_set_error(f_invalid_parameter);
      if (name.used > name.size) return f_status_set_error(f_invalid_parameter);
      if (value.used > value.size) return f_status_set_error(f_invalid_parameter);
      if (arguments == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments->used > arguments->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (name.used == 0) return f_no_data;
    if (value.used == 0) return f_no_data;

    f_status status = f_none;

    status = private_fll_execute_arguments_add_parameter(prefix.string, prefix.used, name.string, name.used, value.string, value.used, arguments);

    if (f_status_is_error(status)) return status;

    return f_none;
  }
#endif // _di_fll_execute_arguments_dynamic_add_parameter_

#ifndef _di_fll_execute_arguments_dynamic_add_parameter_set_
  f_return_status fll_execute_arguments_dynamic_add_parameter_set(const f_string_static prefix[], const f_string_static name[], const f_string_static value[], const f_array_length size, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments->used > arguments->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (size == 0) return f_no_data;

    f_status status = f_none;

    for (f_array_length i = 0; i < size; i++) {
      if (prefix[i].used > prefix[i].size) continue;
      if (name[i].used == 0) continue;
      if (name[i].used > name[i].size) continue;
      if (value[i].used == 0) continue;
      if (value[i].used > value[i].size) continue;

      status = private_fll_execute_arguments_add_parameter(prefix[i].string, prefix[i].used, name[i].string, name[i].used, value[i].string, value[i].used, arguments);

      if (f_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_dynamic_add_parameter_set_

#ifndef _di_fll_execute_arguments_dynamic_add_set_
  f_return_status fll_execute_arguments_dynamic_add_set(const f_string_static source[], const f_array_length size, f_string_dynamics *arguments) {
    #ifndef _di_level_2_parameter_checking_
      if (arguments == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments->used > arguments->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (size == 0) return f_no_data;

    f_status status = f_none;

    for (f_array_length i = 0; i < size; i++) {
      if (source[i].used == 0) continue;
      if (source[i].used > source[i].size) continue;

      status = private_fll_execute_arguments_add(source[i].string, source[i].used, arguments);

      if (f_status_is_error(status)) return status;
    } // for

    return status;
  }
#endif // _di_fll_execute_arguments_dynamic_add_set_

#ifndef _di_fll_execute_path_
  f_return_status fll_execute_path(const f_string program_path, const f_string_statics arguments, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (result == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments.used > arguments.size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string fixed_arguments[arguments.used + 2];

    f_string last_slash = f_string_initialize;
    f_string program_name = f_string_initialize;

    f_string_length name_size = 0;

    f_status status = f_none;

    memset(&fixed_arguments, 0, sizeof(f_string) * (arguments.used + 2));

    last_slash = strrchr(program_path, '/');

    if (last_slash != 0) {
      name_size = strnlen(last_slash, PATH_MAX);

      if (name_size > 1) {
        f_macro_string_new(status, program_name, name_size + 1);

        if (f_status_is_error(status)) return status;

        memcpy(program_name, last_slash + 1, sizeof(f_string_length) * name_size);
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

      if (f_status_is_error(status)) {
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

    // @todo validate that the file at program_path actually exists before attempting to fork and execute
    int process_id = 0;

    process_id = vfork();

    if (process_id < 0) {
      if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return f_status_set_error(f_fork_failed);
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

    if (*result != 0) return f_status_set_error(f_failure);

    return f_none;
  }
#endif // _di_fll_execute_path_

#ifndef _di_fll_execute_path_environment_
  f_return_status fll_execute_path_environment(const f_string program_path, const f_string_statics arguments, const f_string_statics names, const f_string_statics values, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (result == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments.used > arguments.size) return f_status_set_error(f_invalid_parameter);
      if (names.used > names.size) return f_status_set_error(f_invalid_parameter);
      if (values.used > values.size) return f_status_set_error(f_invalid_parameter);
      if (names.used > values.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string fixed_arguments[arguments.used + 2];

    f_string last_slash = f_string_initialize;
    f_string program_name = f_string_initialize;

    f_string_length name_size = 0;

    f_status status = f_none;

    memset(&fixed_arguments, 0, sizeof(f_string) * (arguments.used + 2));

    last_slash = strrchr(program_path, '/');

    if (last_slash != 0) {
      name_size = strnlen(last_slash, PATH_MAX);

      if (name_size > 1) {
        f_macro_string_new(status, program_name, name_size + 1);

        if (f_status_is_error(status)) return status;

        memcpy(program_name, last_slash + 1, sizeof(f_string_length) * name_size);
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

      if (f_status_is_error(status)) {
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

    // @todo validate that the file at program_path actually exists before attempting to fork and execute
    int process_id = 0;

    process_id = vfork();

    if (process_id < 0) {
      if (name_size > 0) f_macro_string_delete_simple(program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return f_status_set_error(f_fork_failed);
    }

    // child
    if (process_id == 0) {
      clearenv();

      for (f_array_length i = 0; i < names.used; i++) {
        f_environment_set_dynamic(names.array[i], values.array[i], true);
      }

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

    if (*result != 0) return f_status_set_error(f_failure);

    return f_none;
  }
#endif // _di_fll_execute_path_environment_

#ifndef _di_fll_execute_program_
  f_return_status fll_execute_program(const f_string program_name, const f_string_statics arguments, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (result == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments.used > arguments.size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string fixed_arguments[arguments.used + 2];

    memset(&fixed_arguments, 0, sizeof(f_string) * (arguments.used + 2));
    fixed_arguments[0] = program_name;

    f_status status = f_none;

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_new(status, fixed_arguments[i + 1], arguments.array[i].used + 1);

      if (f_status_is_error(status)) {
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

    // @todo validate that the file at program_path actually exists before attempting to fork and execute
    int process_id = 0;

    process_id = vfork();

    if (process_id < 0) {
      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return f_status_set_error(f_fork_failed);
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

    if (*result != 0) return f_status_set_error(f_failure);

    return f_none;
  }
#endif // _di_fll_execute_program_

#ifndef _di_fll_execute_program_environment_
  f_return_status fll_execute_program_environment(const f_string program_name, const f_string_statics arguments, const f_string_statics names, const f_string_statics values, int *result) {
    #ifndef _di_level_2_parameter_checking_
      if (result == 0) return f_status_set_error(f_invalid_parameter);
      if (arguments.used > arguments.size) return f_status_set_error(f_invalid_parameter);
      if (names.used > names.size) return f_status_set_error(f_invalid_parameter);
      if (values.used > values.size) return f_status_set_error(f_invalid_parameter);
      if (names.used > values.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls.
    f_string fixed_arguments[arguments.used + 2];

    memset(&fixed_arguments, 0, sizeof(f_string) * (arguments.used + 2));
    fixed_arguments[0] = program_name;

    f_status status = f_none;

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_new(status, fixed_arguments[i + 1], arguments.array[i].used + 1);

      if (f_status_is_error(status)) {
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

    // @todo validate that the file at program_path actually exists before attempting to fork and execute
    int process_id = 0;

    process_id = vfork();

    if (process_id < 0) {
      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for

      return f_status_set_error(f_fork_failed);
    }

    // child
    if (process_id == 0) {
      clearenv();

      for (f_array_length i = 0; i < names.used; i++) {
        f_environment_set_dynamic(names.array[i], values.array[i], true);
      }

      execvp(program_name, fixed_arguments);

      // according to manpages, calling _exit() is safer and should be called here instead of exit()
      _exit(-1);
    }

    // have the parent wait for the child process to finish
    waitpid(process_id, result, 0);

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_delete_simple(fixed_arguments[i + 1], arguments.array[i].used + 1);
    } // for

    if (*result != 0) return f_status_set_error(f_failure);

    return f_none;
  }
#endif // _di_fll_execute_program_environment_

#ifdef __cplusplus
} // extern "C"
#endif
