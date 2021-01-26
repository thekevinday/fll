/**
 * FLL - Level 2
 *
 * Project: Execute
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides program execution operations similar to system().
 *
 * Some functions support capabilities, which are POSIX compliant as of POSIX 1003.1e (as a draft).
 * Because it is only in POSIX as a draft, they are available via libcap instead of libc.
 */
#ifndef _FLL_execute_h
#define _FLL_execute_h

// include pre-requirements
#define _GNU_SOURCE

// libc includes
#include <memory.h>
#include <sched.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/capability.h>
#include <level_0/control_group.h>
#include <level_0/environment.h>
#include <level_0/execute.h>
#include <level_0/file.h>
#include <level_0/limit.h>
#include <level_0/path.h>
#include <level_0/signal.h>

#ifndef _di_pthread_support_
  #include <level_0/thread.h>
#endif // _di_pthread_support_

// fll-1 includes
#include <level_1/control_group.h>
#include <level_1/environment.h>
#include <level_1/execute.h>
#include <level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Add an argument to the execution arguments array.
 *
 * This guarantees that an end of string exists at the end of the copied string.
 * This does not check for NULL characters anywhere else in the string.
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
 *   Errors (with error bit) from: f_macro_string_dynamics_t_resize().
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_macro_string_dynamics_t_resize()
 * @see f_string_append()
 * @see f_string_dynamic_delete()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_add_
  extern f_status_t fll_execute_arguments_add(const f_string_t source, const f_string_length_t length, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_add_

/**
 * Add parameters as arguments to the execution arguments array.
 *
 * This is intended to simplify adding arguments that have prefixes and values such as those common in console parameters.
 * For example, a pefix of '--', a name of 'do', and a value of 'something' would result in two arguments added:
 *   '--do' and 'something'.
 *
 * The arguments are only appended if the length of name and value are not 0.
 *
 * This guarantees that an end of string exists at the end of each argument.
 * This does not check for NULL characters anywhere else in the string.
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
 *   The string to add to the arguments array.
 * @param value_length
 *   Length of value to prepend.
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_delete()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_add_parameter_
  extern f_status_t fll_execute_arguments_add_parameter(const f_string_t prefix, const f_string_length_t prefix_length, const f_string_t name, const f_string_length_t name_length, const f_string_t value, const f_string_length_t value_length, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_add_parameter_

/**
 * Add set of parameters as arguments to the execution arguments array.
 *
 * This is intended to simplify adding arguments that have prefixes and values such as those common in console parameters.
 * For example, a pefix of '--', a name of 'do', and a value of 'something' would result in two arguments added:
 *   '--do' and 'something'.
 *
 * The arguments are only appended if the length of name and value are not 0.
 *
 * This guarantees that an end of string exists at the end of each argument.
 * This does not check for NULL characters anywhere else in the string.
 *
 * @param prefix
 *   An array of the strings prepend to the name.
 * @param prefix_length
 *   Length of prefix to prepend.
 * @param name
 *   An array of the strings to add to the arguments array.
 * @param name_length
 *   Length of name to prepend.
 * @param value
 *   An array of the strings to add to the arguments array.
 * @param value_length
 *   Length of value to prepend.
 * @param size
 *   The array size of prefix, prefix_length, name, name_length, value, and value_length (all of which must be of the same array size).
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_delete()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_add_parameter_set_
  extern f_status_t fll_execute_arguments_add_parameter_set(const f_string_t prefix[], const f_string_length_t prefix_length[], const f_string_t name[], const f_string_length_t name_length[], const f_string_t value[], const f_string_length_t value_length[], const f_array_length_t size, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_add_parameter_set_

/**
 * Add a set of arguments to the execution arguments array.
 *
 * This guarantees that an end of string exists at the end of the copied string.
 * This does not check for NULL characters anywhere else in the string.
 *
 * @param source
 *   An array of strings to add to the arguments array.
 * @param length
 *   An array of lengths of each string to prepend.
 * @param size
 *   The array size of source and length (all of which must be of the same array size).
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_delete()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_add_set_
  extern f_status_t fll_execute_arguments_add_set(const f_string_t source[], const f_string_length_t length[], const f_array_length_t size, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_add_set_

/**
 * Add an argument to the execution arguments array.
 *
 * This guarantees that an end of string exists at the end of the copied string.
 * This does not check for NULL characters anywhere else in the string.
 *
 * @param source
 *   The string to add to the arguments array.
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_delete()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_dynamic_add_
  extern f_status_t fll_execute_arguments_dynamic_add(const f_string_static_t source, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_dynamic_add_

/**
 * Add parameters as arguments to the execution arguments array.
 *
 * This is intended to simplify adding arguments that have prefixes and values such as those common in console parameters.
 * For example, a pefix of '--', a name of 'do', and a value of 'something' would result in two arguments added:
 *   '--do' and 'something'.
 *
 * The arguments are only appended if the length of name and value are not 0.
 *
 * This guarantees that an end of string exists at the end of each argument.
 * This does not check for NULL characters anywhere else in the string.
 *
 * @param prefix
 *   The string prepend to the name.
 * @param name
 *   The string to add to the arguments array.
 * @param value
 *   The string to add to the arguments array.
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_delete()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_dynamic_add_parameter_
  extern f_status_t fll_execute_arguments_dynamic_add_parameter(const f_string_static_t prefix, const f_string_static_t name, const f_string_static_t value, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_dynamic_add_parameter_

/**
 * Add set of parameters as arguments to the execution arguments array.
 *
 * This is intended to simplify adding arguments that have prefixes and values such as those common in console parameters.
 * For example, a pefix of '--', a name of 'do', and a value of 'something' would result in two arguments added:
 *   '--do' and 'something'.
 *
 * The arguments are only appended if the length of name and value are not 0.
 *
 * This guarantees that an end of string exists at the end of each argument.
 * This does not check for NULL characters anywhere else in the string.
 *
 * @param prefix
 *   The string prepend to the name.
 * @param name
 *   The string to add to the arguments array.
 * @param value
 *   The string prepend to the name.
 * @param size
 *   The array size of buffer.
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_delete()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_dynamic_add_parameter_set_
  extern f_status_t fll_execute_arguments_dynamic_add_parameter_set(const f_string_static_t prefix[], const f_string_static_t name[], const f_string_static_t value[], const f_array_length_t size, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_dynamic_add_parameter_set_

/**
 * Add a set of arguments to the execution arguments array.
 *
 * This guarantees that an end of string exists at the end of the copied string.
 * This does not check for NULL characters anywhere else in the string.
 *
 * @param source
 *   An array of strings to add to the arguments array.
 * @param size
 *   The array size of buffer.
 * @param arguments
 *   The array of string arguments intended to pass to the execute functions.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *   Errors (with error bit) from: f_string_dynamics_increase().
 *
 * @see f_string_append()
 * @see f_string_dynamic_delete()
 * @see f_string_dynamic_terminate()
 * @see f_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_dynamic_add_set_
  extern f_status_t fll_execute_arguments_dynamic_add_set(const f_string_static_t source[], const f_array_length_t size, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_dynamic_add_set_

/**
 * Execute a program given by program name found in the PATH environment (such as "bash") or program path (such as "/bin/bash").
 *
 * The program will be executed directly and not via a child process.
 *
 * Because this directly executes a program, it potentially may not return.
 * If and when it does, the executed program is finished executing (be it failure or success).
 * Often times scripts may return and binaries may not.
 *
 * @param program
 *   The name or path of the program.
 *   The string pointer may be set to 0, to designate that the first index in arguments is assumed to be the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param option
 *   A bitwise set of options, such as: fl_execute_parameter_option_exit, and fl_execute_parameter_option_path.
 *   If fl_execute_parameter_option_exit: this will call exit() at the end of execution (be it success or failure).
 *   If fl_execute_parameter_option_path: this is a program path (such as "/bin/bash"), otherwise this is a program (such as "bash").
 * @param result
 *   The code returned after finishing execution of program.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on execution failure.
 *
 * @see execv()
 * @see execvp()
 * @see exit()
 * @see memcpy()
 * @see strnlen()
 */
#ifndef _di_fll_execute_into_
  extern f_status_t fll_execute_into(const f_string_t program, const f_string_statics_t arguments, const uint8_t option, int *result);
#endif // _di_fll_execute_into_

/**
 * Execute a program given by program name found in the PATH environment (such as "bash") or program path (such as "/bin/bash").
 *
 * The program will be executed via a forked child process.
 *
 * If parameter.names is specified:
 *   Uses the provided environment array to designate the environment for the program being executed.
 *   The environment is defined by the names and values pair.
 *   This requires paramete.values to also be specified with the same used length as parameter.names.
 *
 * When parameter.option has the fl_execute_parameter_option_path bit set, then this does validate the path to the program.
 * Otherwise, this does not validate the path to the program.
 *
 * When the parameter.option has the fl_execute_parameter_option_exit bit set, then this calls exit() when the child process returns.
 * Otherwise, this returns F_child and assigns the child's return code to result for the child process.
 * The caller is expected to handle the appropriate exit procedures and memory deallocation for the child process when F_child is returned.
 *
 * This returns F_capability, F_group, and F_user only by the child process and must be treated the same as F_child for the purposes of understanding what the current process is.
 * These are essentialy F_child with explicit error codes that are returned instead of performing the desired execution.
 *
 * This returns F_control_group, F_limit, F_processor, and F_schedule only by the parent process and represents that the child process could not be executed.
 *
 * @param program
 *   The name or path of the program.
 *   The string pointer may be set to 0, to designate that the first index in arguments is assumed to be the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param parameter
 *   (optional) This and most of its fields are optional and are disabled when set to 0.
 *   option:
 *     A bitwise set of options, such as: fl_execute_parameter_option_exit, and fl_execute_parameter_option_path.
 *   names:
 *     An array of strings representing the environment variable names.
 *     At most names.used variables are created.
 *     Duplicate names are overwritten.
 *   values:
 *     An array of strings representing the environment variable names.
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
 *   (optional) The code returned after finishing execution of program.
 *   When fl_execute_parameter_option_return is passed via parameter.option, then this instead stores the child process id (PID).
 *   Set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *   F_child on success and this is the child thread.
 *   F_parent on success and this is the parent thread (only happens when fl_execute_parameter_option_return is passed).
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
 *   Errors (with error bit) from: f_capability_process_set().
 *   Errors (with error bit) from: f_environment_get().
 *   Errors (with error bit) from: f_file_exists().
 *   Errors (with error bit) from: f_limit_process().
 *   Errors (with error bit) from: f_macro_string_dynamics_t_delete().
 *   Errors (with error bit) from: f_signal_mask().
 *   Errors (with error bit) from: f_thread_signal_mask().
 *   Errors (with error bit) from: fl_environment_path_explode_dynamic().
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_dynamic_delete().
 *   Errors (with error bit) from: f_string_dynamic_terminate().
 *
 * @see close()
 * @see clearenv()
 * @see dup2()
 * @see execv()
 * @see execvp()
 * @see exit()
 * @see fork()
 * @see getpid()
 * @see memcpy()
 * @see nice()
 * @see pipe()
 * @see sched_setaffinity()
 * @see sched_setscheduler()
 * @see setgid()
 * @see setgroups()
 * @see setuid()
 * @see strnlen()
 * @see waitpid()
 *
 * @see f_capability_process_set()
 * @see f_environment_get()
 * @see f_file_exists()
 * @see f_limit_process()
 * @see f_signal_mask()
 * @see f_thread_signal_mask()
 * @see fl_control_group_apply()
 * @see fl_environment_path_explode_dynamic()
 * @see f_string_append()
 * @see f_string_dynamic_terminate()
 */
#ifndef _di_fll_execute_program_
  extern f_status_t fll_execute_program(const f_string_t program, const f_string_statics_t arguments, fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, int *result);
#endif // _di_fll_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_execute_h
