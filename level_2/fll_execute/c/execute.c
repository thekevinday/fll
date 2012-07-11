/* FLL - Level 2
 * Project:       Execute
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides program execution operations similart to system().
 */
#include <level_2/execute.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fll_execute_path_
  f_return_status fll_execute_path(const f_string program_path, const f_dynamic_strings arguments, f_s_int *results) {
    #ifndef _di_level_2_parameter_checking_
      if (results == f_null) return f_error_set_error(f_invalid_parameter);

      if (arguments.used < 0) return f_error_set_error(f_invalid_parameter);
      if (arguments.used > arguments.size) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls
    f_status   status            = f_none;
    f_autochar **arguments_array = 0;

    f_string        last_slash   = f_string_initialize;
    f_string        program_name = f_string_initialize;
    f_string_length name_size    = 0;

    last_slash = strrchr(program_path, '/');

    if (last_slash != f_null) {
      name_size = strnlen(last_slash, PATH_MAX);

      if (name_size > 1) {
        f_new_string(status, program_name, name_size + 1);

        if (f_error_is_error(status)) return status;

        memcpy(program_name, last_slash + 1, name_size);
        memset(program_name, name_size, 0);
      } else {
        name_size = 0;
      }
    }

    status = f_new_array((void **) & arguments_array, sizeof(f_autochar **), arguments.used + 2);

    if (f_error_is_error(status)) {
      f_status tmp_status = f_none;

      f_delete_string(tmp_status, program_name, name_size);
      return status;
    }

    {
      f_string_length counter = 0;

      arguments_array[0] = program_name;
      counter++;

      for (; counter < arguments.used; counter++) {
        arguments_array[counter] = arguments.array[counter].string;
      }

      // insert the required array terminated
      arguments_array[arguments.used + 1] = 0;
    }

    // TODO: validate that the file at program_path actually exists before attempting to fork and execute
    f_s_int process_id = 0;

    process_id = vfork();

    if (process_id < 0) {
      return f_error_set_error(f_fork_failed);
    }

    if (process_id == 0) { // child
      execv(program_path, arguments_array);

      // according to manpages, calling _exit() is safer and should be called here instead of exit()
      _exit(-1);
    }

    // have the parent wait for the child process to finish
    waitpid(process_id, results, 0);

    if (name_size > 0) f_delete_string(status, program_name, name_size);
    f_delete((void **) & arguments_array, sizeof(f_autochar), arguments.used + 2);

    if (*results != 0) return f_error_set_error(f_failure);

    return f_none;
  }
#endif // _di_fll_execute_path_

#ifndef _di_fll_execute_program_
  f_return_status fll_execute_program(const f_string program_name, const f_dynamic_strings arguments, f_s_int *results) {
    #ifndef _di_level_2_parameter_checking_
      if (results == f_null) return f_error_set_error(f_invalid_parameter);

      if (arguments.used < 0) return f_error_set_error(f_invalid_parameter);
      if (arguments.used > arguments.size) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    // create a string array that is compatible with execv() calls
    f_status   status            = f_none;
    f_autochar **arguments_array = 0;

    status = f_new_array((void **) & arguments_array, sizeof(f_autochar **), arguments.used + 2);

    if (f_error_is_error(status)) return status;

    {
      f_string_length counter = 0;

      arguments_array[0] = program_name;
      counter++;

      for (; counter < arguments.used; counter++) {
        arguments_array[counter] = arguments.array[counter].string;
      }

      // insert the required array terminated
      arguments_array[arguments.used + 1] = 0;
    }

    // TODO: validate that the file at program_path actually exists before attempting to fork and execute
    f_s_int process_id = 0;

    process_id = vfork();

    if (process_id < 0) {
      return f_error_set_error(f_fork_failed);
    }

    if (process_id == 0) { // child
      execvp(program_name, arguments_array);

      // according to manpages, calling _exit() is safer and should be called here instead of exit()
      _exit(-1);
    }

    // have the parent wait for the child process to finish
    waitpid(process_id, results, 0);

    f_delete((void **) & arguments_array, sizeof(f_autochar), arguments.used + 2);

    if (*results != 0) return f_error_set_error(f_failure);

    return f_none;
  }
#endif // _di_fll_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif
