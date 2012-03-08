/* FLL - Level 1
 * Project:       Execute
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides program execution operations similart to system()
 * TODO: I should implement a function that will find the program based on PATH so that static paths do not have to be used
 */
#include <level_2/execute.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fll_execute_path_
  f_return_status fll_execute_path(const f_string program_path, const f_dynamic_strings arguments, f_s_int *results){
    #ifndef _di_level_1_parameter_checking_
      if (results == f_null) return f_invalid_parameter;

      if (arguments.used <= 0)              return f_invalid_parameter;
      if (arguments.used  > arguments.size) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    // create a string array that is compatible with execv() calls
    f_status   status            = f_status_initialize;
    f_autochar **arguments_array = 0;

    status = f_new_array((void **) & arguments_array, sizeof(f_autochar **), arguments.used + 1);

    if (f_macro_test_for_allocation_errors(status)) return status;

    {
      f_string_length counter = f_string_length_initialize;

      for (; counter < arguments.used; counter++){
        arguments_array[counter] = arguments.array[counter].string;
      }

      // insert the required array terminated
      arguments_array[arguments.used] = 0;
    }

    // TODO: validate that the file at program_path actually exists before attempting to fork and execute
    f_s_int process_id = 0;

    process_id = vfork();

    if (process_id < 0){
      return f_fork_failed;
    }

    if (process_id == 0){ // child
      execv(program_path, arguments_array);

      // according to manpages, calling _exit() is safer and should be called here instead of exit()
      _exit(-1);
    }

    // have the parent wait for the child process to finish
    waitpid(process_id, results, 0);

    f_delete((void **) & arguments_array, sizeof(f_autochar), arguments.used + 1);

    if (*results != 0) return f_failure;

    return f_none;
  }
#endif // _di_fll_execute_path_

#ifdef __cplusplus
} // extern "C"
#endif
