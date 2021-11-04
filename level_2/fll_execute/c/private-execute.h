/**
 * FLL - Level 2
 *
 * Project: Execute
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FLL_execute_h
#define _PRIVATE_FLL_execute_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fll_execute_arguments_add().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The string to add to the arguments array.
 * @param length
 *   Length of string to prepend.
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_resize()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 * @see fll_execute_arguments_add()
 * @see fll_execute_arguments_add_set()
 * @see fll_execute_arguments_dynamic_add()
 * @see fll_execute_arguments_dynamic_add_set()
 */
#if !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)
  extern f_status_t private_fll_execute_arguments_add(const f_string_t source, const f_array_length_t length, f_string_dynamics_t *arguments) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)

/**
 * Private implementation of fll_execute_arguments_add_parameter().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param prefix
 *   The string prepend to the name.
 * @param prefix_length
 *   Length of prefix to prepend.
 * @param name
 *   The string to add to the arguments array.
 * @param name_length
 *   Length of name to prepend.
 * @param value
 *   The string prepend to the name.
 * @param value_length
 *   Length of value to prepend.
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_resize()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 * @see fll_execute_arguments_add_parameter()
 * @see fll_execute_arguments_add_parameter_set()
 * @see fll_execute_arguments_dynamic_add_parameter()
 * @see fll_execute_arguments_dynamic_add_parameter_set()
 */
#if !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)
  extern f_status_t private_fll_execute_arguments_add_parameter(const f_string_t prefix, const f_array_length_t prefix_length, const f_string_t name, const f_array_length_t name_length, const f_string_t value, const f_array_length_t value_length, f_string_dynamics_t *arguments) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)

/**
 * Private function for perform the execute as operations.
 *
 * This should be executed in the child thread.
 *
 * @param as
 *   The "as" operations to perform.
 * @param parameter
 *   (optional) This and most of its fields are optional and are disabled when set to 0.
 *   This function only cares about "option" on this structure.
 *   option:
 *     A bitwise set of options, such as: FL_execute_parameter_option_exit_d, and FL_execute_parameter_option_path_d.
 * @param result
 *   The code returned after finishing execution of program.
 *
 * @return
 *   F_none on success.
 *
 *   F_capability (with error bit) on failure to set capabilities.
 *   F_group (with error bit) on failure to set GID.
 *   F_nice (with error bit) on failure to set process niceness.
 *   F_user (with error bit) on failure to set UID.
 *
 * @see exit()
 * @see getpid()
 * @see nice()
 * @see sched_setaffinity()
 * @see sched_setscheduler()
 * @see setgid()
 * @see setgroups()
 * @see setuid()
 *
 * @see f_capability_process_set()
 * @see fll_execute_program()
 */
#if !defined(_di_fll_execute_program_)
  extern f_status_t private_fll_execute_as_child(const fl_execute_as_t as, fl_execute_parameter_t * const parameter, int *result) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_execute_program_)

/**
 * Private function for perform the execute as operations.
 *
 * This should be executed in the parent thread.
 *
 * @param as
 *   The "as" operations to perform.
 * @param id_child
 *   The child PID.
 * @param parameter
 *   (optional) This and most of its fields are optional and are disabled when set to 0.
 *   This function only cares about "option" on this structure.
 *   option:
 *     A bitwise set of options, such as: FL_execute_parameter_option_exit_d, and FL_execute_parameter_option_path_d.
 * @param result
 *   A NULL termianted 2-byte string array where the first character represents the return code ('0' for success, '1' for failure).
 *
 * @return
 *   F_none on success.
 *
 *   F_control_group (with error bit) on failure to set control group.
 *   F_limit (with error bit) on failure to set a resource limit.
 *   F_processor (with error bit) on failure to set processor (cpu) affinity.
 *   F_schedule (with error bit) on failure to set scheduler.
 *
 * @see exit()
 * @see getpid()
 * @see nice()
 * @see sched_setaffinity()
 * @see sched_setscheduler()
 * @see setgid()
 * @see setgroups()
 * @see setuid()
 *
 * @see f_capability_process_set()
 * @see f_limit_process()
 * @see fll_execute_program()
 */
#if !defined(_di_fll_execute_program_)
  extern f_status_t private_fll_execute_as_parent(const fl_execute_as_t as, const pid_t id_child, fl_execute_parameter_t * const parameter, char *result) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_execute_program_)

/**
 * Private function for performing the fork and execute operation.
 *
 * This implementation ignores parameter.data.
 *
 * @param direct
 *   If TRUE, then use execv() to directly execute.
 *   If FALSE, then use execvp() to search for in PATH then execute.
 * @param program
 *   The name or path of the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param parameter
 *   (optional) This and most of its fields are optional and are disabled when set to 0.
 *   option:
 *     A bitwise set of options, such as: FL_execute_parameter_option_exit_d, and FL_execute_parameter_option_path_d.
 *   names:
 *     An array of strings representing the environment variable names.
 *     At most names.used variables are created.
 *     Duplicate names are overwritten.
 *   values:
 *     An array of strings representing the environment variable values.
 *     The values.used must be of at least names.used.
 *     Set individual strings.used to 0 for empty/null values.
 *   signals:
 *     A pointer to the set of signals to have the child process block or not block.
 *     When not specified, the child process uses the signal blocking behavior of the parent process.
 *   data:
 *     A pointer to a string to pipe as standard input to the child process.
 *     The parent will block until the standard input is fully read or the child process exits.
 * @param as
 *   (optional) This and most of its fields are optional and are disabled when set to NULL.
 * @param result
 *   (optional) The execute status code returned after finishing or attempting to finish execution of program.
 *   When FL_execute_parameter_option_return_d is passed via parameter.option, then this instead stores the child process id (PID).
 *   This is should be of (int *) except when FL_execute_parameter_option_return_d this should instead be (pid_t *).
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_child on success and this is the child thread.
 *   F_parent on success and this is the parent thread (only happens when FL_execute_parameter_option_return_d is passed).
 *
 *   F_capability (with error bit) on failure to set capabilities in the child (only the child process returns this).
 *   F_control_group (with error bit) on failure to set control group in the child (only the parent process returns this).
 *   F_child (with error bit) on any failure without an explicit failure code (like F_group) before calling execute but this is the child thread.
 *   F_failure (with error bit) on execution failure.
 *   F_fork (with error bit) on fork failure.
 *   F_group (with error bit) on failure to set GID in the child (only the child process returns this).
 *   F_limit (with error bit) on failure to set a resource limit in the child (only the parent process returns this).
 *   F_nice (with error bit) on failure to set process niceness in the child (only the child process returns this).
 *   F_pipe (with error bit) on pipe failure.
 *   F_processor (with error bit) on failure to set a processor (cpu) affinity in the child (only the parent process returns this).
 *   F_schedule (with error bit) on failure to set scheduler in the child (only the parent process returns this).
 *   F_user (with error bit) on failure to set UID in the child (only the child process returns this).
 *
 * @see clearenv()
 * @see close()
 * @see dup2()
 * @see execv()
 * @see execvp()
 * @see fork()
 * @see pipe()
 * @see waitpid()
 *
 * @see f_environment_set_dynamic()
 * @see f_limit_process()
 * @see f_signal_mask()
 * @see f_thread_signal_mask()
 * @see fl_control_group_apply()
 * @see fll_execute_program()
 */
#if !defined(_di_fll_execute_program_)
  extern f_status_t private_fll_execute_fork(const bool direct, const f_string_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, void *result) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_execute_program_)

/**
 * Private function for performing the fork and execute operation.
 *
 * This implementation requires parameter.data.
 *
 * @param direct
 *   If TRUE, then use execv() to directly execute.
 *   If FALSE, then use execvp() to search for in PATH then execute.
 * @param program
 *   The name or path of the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param parameter
 *   (optional) This and most of its fields are optional and are disabled when set to 0.
 *   option:
 *     A bitwise set of options, such as: FL_execute_parameter_option_exit_d, and FL_execute_parameter_option_path_d.
 *   names:
 *     An array of strings representing the environment variable names.
 *     At most names.used variables are created.
 *     Duplicate names are overwritten.
 *   values:
 *     An array of strings representing the environment variable values.
 *     The values.used must be of at least names.used.
 *     Set individual strings.used to 0 for empty/null values.
 *   signals:
 *     A pointer to the set of signals to have the child process block or not block.
 *     When not specified, the child process uses the signal blocking behavior of the parent process.
 *   data:
 *     A pointer to a string to pipe as standard input to the child process.
 *     The parent will block until the standard input is fully read or the child process exits.
 * @param as
 *   (optional) This and most of its fields are optional and are disabled when set to NULL.
 * @param result
 *   (optional) The execute status code returned after finishing or attempting to finish execution of program.
 *   When FL_execute_parameter_option_return_d is passed via parameter.option, then this instead stores the child process id (PID).
 *   This is should be of (int *) except when FL_execute_parameter_option_return_d this should instead be (pid_t *).
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_child on success and this is the child thread.
 *   F_parent on success and this is the parent thread (only happens when FL_execute_parameter_option_return_d is passed).
 *
 *   F_capability (with error bit) on failure to set capabilities in the child (only the child process returns this).
 *   F_control_group (with error bit) on failure to set control group in the child (only the parent process returns this).
 *   F_child (with error bit) on any failure without an explicit failure code (like F_group) before calling execute but this is the child thread.
 *   F_failure (with error bit) on execution failure.
 *   F_fork (with error bit) on fork failure.
 *   F_group (with error bit) on failure to set GID in the child (only the child process returns this).
 *   F_limit (with error bit) on failure to set a resource limit in the child (only the parent process returns this).
 *   F_nice (with error bit) on failure to set process niceness in the child (only the child process returns this).
 *   F_pipe (with error bit) on pipe failure.
 *   F_processor (with error bit) on failure to set a processor (cpu) affinity in the child (only the parent process returns this).
 *   F_schedule (with error bit) on failure to set scheduler in the child (only the parent process returns this).
 *   F_user (with error bit) on failure to set UID in the child (only the child process returns this).
 *
 * @see clearenv()
 * @see close()
 * @see dup2()
 * @see execv()
 * @see execvp()
 * @see fork()
 * @see pipe()
 * @see waitpid()
 *
 * @see f_environment_set_dynamic()
 * @see f_limit_process()
 * @see f_signal_mask()
 * @see f_thread_signal_mask()
 * @see fll_execute_program()
 */
#if !defined(_di_fll_execute_program_)
  extern f_status_t private_fll_execute_fork_data(const bool direct, const f_string_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, void *result) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_execute_program_)

/**
 * Private function for reconstructing the arguments into a fixed array.
 *
 * @param program_path
 *   The full path to the program or the program name to copy from.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param last_slash
 *   A pointer to the last slash.
 *   Set to NULL if there is no slash in the program_path.
 * @param fixated_is
 *   If TRUE, then the program_path is already fixated in the fixed_arguments at index 0.
 *   If FALSE, then the program_path needs to be fixated in the fixed_arguments at index 0.
 * @param name_size
 *   The size of the program_path to copy.
 * @param program_name
 *   The destination to copy the name to.
 * @param fixed_arguments
 *   The array of arguments to be updated with the program name.
 *
 * @return
 *   F_none on success.
 *
 * @see fll_execute_program()
 */
#if !defined(_di_fll_execute_program_)
  extern void private_fll_execute_path_arguments_fixate(const f_string_t program_path, const f_string_statics_t arguments, const f_string_t last_slash, const bool fixated_is, const f_array_length_t name_size, char program_name[], f_string_t fixed_arguments[]) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_execute_program_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_execute_h
