#include <level_2/execute.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_execute_path_
  f_return_status fll_execute_path(const f_string program_path, const f_string_dynamics arguments, int *results) {
    #ifndef _di_level_2_parameter_checking_
      if (results == 0) return f_status_set_error(f_invalid_parameter);

      if (arguments.used < 0) return f_status_set_error(f_invalid_parameter);
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
      fixed_arguments[0] = f_string_eos;
    }
    else {
      fixed_arguments[0] = program_name;
    }

    for (f_string_length i = 0; i < arguments.used; i++) {
      f_macro_string_new(status, fixed_arguments[i + 1], arguments.array[i].used + 1);

      if (f_status_is_error(status)) {
        f_status status2 = f_none;

        if (name_size > 0) f_macro_string_delete(status, program_name, name_size);

        for (f_string_length j = 0; j < i; j++) {
          f_macro_string_delete(status2, fixed_arguments[i + 1], arguments.array[j].used + 1);
        }

        return status;
      }

      memcpy(fixed_arguments[i + 1], arguments.array[i].string, arguments.array[i].used);
      fixed_arguments[i + 1][arguments.array[i].used] = f_string_eos;
    } // for

    // insert the required array terminated
    fixed_arguments[arguments.used + 2] = 0;

    // TODO: validate that the file at program_path actually exists before attempting to fork and execute
    int process_id = 0;

    process_id = vfork();

    if (process_id < 0) {
      f_status status2 = f_none;

      if (name_size > 0) f_macro_string_delete(status, program_name, name_size);

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete(status2, fixed_arguments[i + 1], arguments.array[i].used + 1);
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
    waitpid(process_id, results, 0);

    if (name_size > 0) f_macro_string_delete(status, program_name, name_size);

    {
      f_status status2 = f_none;

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete(status2, fixed_arguments[i + 1], arguments.array[i].used + 1);
      } // for
    }

    if (*results != 0) return f_status_set_error(f_failure);

    return f_none;
  }
#endif // _di_fll_execute_path_

#ifndef _di_fll_execute_program_
  f_return_status fll_execute_program(const f_string program_name, const f_string_dynamics arguments, int *results) {
    #ifndef _di_level_2_parameter_checking_
      if (results == 0) return f_status_set_error(f_invalid_parameter);

      if (arguments.used < 0) return f_status_set_error(f_invalid_parameter);
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
        f_status status2 = f_none;

        for (f_string_length j = 0; j < i; j++) {
          f_macro_string_delete(status2, fixed_arguments[i + 1], arguments.array[j].used + 1);
        }

        return status;
      }

      memcpy(fixed_arguments[i + 1], arguments.array[i].string, arguments.array[i].used);
      fixed_arguments[i + 1][arguments.array[i].used] = f_string_eos;
    } // for

    // insert the required array terminated
    fixed_arguments[arguments.used + 2] = 0;

    // TODO: validate that the file at program_path actually exists before attempting to fork and execute
    int process_id = 0;

    process_id = vfork();

    if (process_id < 0) {
      f_status status2 = f_none;

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete(status2, fixed_arguments[i + 1], arguments.array[i].used + 1);
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
    waitpid(process_id, results, 0);

    {
      f_status status2 = f_none;

      for (f_string_length i = 0; i < arguments.used; i++) {
        f_macro_string_delete(status2, fixed_arguments[i + 1], arguments.array[i].used + 1);
      }
    }

    if (*results != 0) return f_status_set_error(f_failure);

    return f_none;
  }
#endif // _di_fll_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif
