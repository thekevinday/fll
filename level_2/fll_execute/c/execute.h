/**
 * FLL - Level 2
 *
 * Project: Execute
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides program execution operations similar to system().
 */
#ifndef _FLL_execute_h
#define _FLL_execute_h

// libc includes
#include <memory.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/environment.h>
#include <level_0/execute.h>
#include <level_0/file.h>
#include <level_0/path.h>
#include <level_0/signal.h>

// fll-1 includes
#include <level_1/environment.h>
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see f_macro_string_dynamics_t_resize()
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_add_
  extern f_return_status fll_execute_arguments_add(const f_string_t source, const f_string_length_t length, f_string_dynamics_t *arguments);
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_add_parameter_
  extern f_return_status fll_execute_arguments_add_parameter(const f_string_t prefix, const f_string_length_t prefix_length, const f_string_t name, const f_string_length_t name_length, const f_string_t value, const f_string_length_t value_length, f_string_dynamics_t *arguments);
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_add_parameter_set_
  extern f_return_status fll_execute_arguments_add_parameter_set(const f_string_t prefix[], const f_string_length_t prefix_length[], const f_string_t name[], const f_string_length_t name_length[], const f_string_t value[], const f_string_length_t value_length[], const f_array_length_t size, f_string_dynamics_t *arguments);
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_add_set_
  extern f_return_status fll_execute_arguments_add_set(const f_string_t source[], const f_string_length_t length[], const f_array_length_t size, f_string_dynamics_t *arguments);
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_dynamic_add_
  extern f_return_status fll_execute_arguments_dynamic_add(const f_string_static_t source, f_string_dynamics_t *arguments);
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_dynamic_add_parameter_
  extern f_return_status fll_execute_arguments_dynamic_add_parameter(const f_string_static_t prefix, const f_string_static_t name, const f_string_static_t value, f_string_dynamics_t *arguments);
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_dynamic_add_parameter_set_
  extern f_return_status fll_execute_arguments_dynamic_add_parameter_set(const f_string_static_t prefix[], const f_string_static_t name[], const f_string_static_t value[], const f_array_length_t size, f_string_dynamics_t *arguments);
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_fll_execute_arguments_dynamic_add_set_
  extern f_return_status fll_execute_arguments_dynamic_add_set(const f_string_static_t source[], const f_array_length_t size, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_dynamic_add_set_

/**
 * Execute a program given some path + program name (such as "/bin/bash").
 *
 * This does validate that the program path exists.
 *
 * This does not call exit() when the child process exits.
 * Instead, this returns F_child and assigns the child's return code to result for the child process.
 * The caller is expected to handle the appropriate exit procedures and memory deallocation for the child process.
 *
 * @param program_path
 *   The entire path to the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param signals
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param pipe
 *   (optional) A pointer to a string to pipe as standard input to the child process.
 *   Set to 0 to disable.
 * @param result
 *   The code returned after finishing execution of program_path.
 *
 * @return
 *   F_none on success.
 *   F_child on success but this is the child thread.
 *   F_failure (with error bit) on execution failure.
 *   F_fork (with error bit) on fork failure.
 *   F_pipe (with error bit) on pipe failure.
 *
 *   Errors (with error bit) from: f_file_exists().
 *   Errors (with error bit) from: f_signal_set_handle().
 *
 * @see close()
 * @see dup2()
 * @see execv()
 * @see execvp()
 * @see fork()
 * @see pipe()
 * @see waitpid()
 *
 * @see f_file_exists()
 * @see f_signal_set_handle()
 */
#ifndef _di_fll_execute_path_
  extern f_return_status fll_execute_path(const f_string_t program_path, const f_string_statics_t arguments, const f_signal_how_t *signals, f_string_static_t * const pipe, int *result);
#endif // _di_fll_execute_path_

/**
 * Execute a program given some path + program name (such as "/bin/bash").
 *
 * Uses the provided environment array to designate the environment for the program being executed.
 * The environment is defined by the names and values pair.
 *
 * This does validate that the program path exists.
 *
 * This does not call exit() when the child process exits.
 * Instead, this returns F_child and assigns the child's return code to result for the child process.
 * The caller is expected to handle the appropriate exit procedures and memory deallocation for the child process.
 *
 * @param program_path
 *   The entire path to the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param names
 *   An array of strings representing the environment variable names.
 *   At most names.used variables are created.
 *   Duplicate names are overwritten.
 * @param values
 *   An array of strings representing the environment variable names.
 *   The values.used must be of at least names.used.
 *   Set individual strings.used to 0 for empty/NULL values.
 * @param signals
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param pipe
 *   (optional) A pointer to a string to pipe as standard input to the child process.
 *   Set to 0 to disable.
 * @param result
 *   The code returned after finishing execution of program_path.
 *
 * @return
 *   F_none on success.
 *   F_child on success but this is the child thread.
 *   F_failure (with error bit) on execution failure.
 *   F_fork (with error bit) on fork failure.
 *   F_pipe (with error bit) on pipe failure.
 *
 *   Errors (with error bit) from: f_environment_set_dynamic().
 *   Errors (with error bit) from: f_file_exists().
 *   Errors (with error bit) from: f_signal_set_handle().
 *
 * @see close()
 * @see clearenv()
 * @see dup2()
 * @see execvp()
 * @see fork()
 * @see memcpy()
 * @see pipe()
 * @see strnlen()
 * @see waitpid()
 *
 * @see f_environment_set_dynamic()
 * @see f_file_exists()
 * @see f_signal_set_handle()
 */
#ifndef _di_fll_execute_path_environment_
  extern f_return_status fll_execute_path_environment(const f_string_t program_path, const f_string_statics_t arguments, const f_string_statics_t names, const f_string_statics_t values, const f_signal_how_t *signals, f_string_static_t * const pipe, int *result);
#endif // _di_fll_execute_path_environment_

/**
 * Execute a program given by name found in the PATH environment (such as "bash").
 *
 * This does not validate the path to the program.
 *
 * This does not call exit() when the child process exits.
 * Instead, this returns F_child and assigns the child's return code to result for the child process.
 * The caller is expected to handle the appropriate exit procedures and memory deallocation for the child process.
 *
 * @param program_name
 *   The name of the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param signals
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param pipe
 *   (optional) A pointer to a string to pipe as standard input to the child process.
 *   Set to 0 to disable.
 * @param result
 *   The code returned after finishing execution of program.
 *
 * @return
 *   F_none on success.
 *   F_child on success but this is the child thread.
 *   F_failure (with error bit) on execution failure.
 *   F_fork (with error bit) on fork failure.
 *   F_pipe (with error bit) on pipe failure.
 *
 *   Errors (with error bit) from: f_file_exists().
 *   Errors (with error bit) from: f_signal_set_handle().
 *
 * @see close()
 * @see dup2()
 * @see execv()
 * @see execvp()
 * @see fork()
 * @see pipe()
 * @see waitpid()
 *
 * @see f_file_exists()
 * @see f_signal_set_handle()
 */
#ifndef _di_fll_execute_program_
  extern f_return_status fll_execute_program(const f_string_t program_name, const f_string_statics_t arguments, const f_signal_how_t *signals, f_string_static_t * const pipe, int *result);
#endif // _di_fll_execute_program_

/**
 * Execute a program given by name found in the PATH environment (such as "bash").
 *
 * Uses the provided environment array to designate the environment for the program being executed.
 * The environment is defined by the names and values pair.
 *
 * This does not validate the path to the program.
 *
 * This does not call exit() when the child process exits.
 * Instead, this returns F_child and assigns the child's return code to result for the child process.
 * The caller is expected to handle the appropriate exit procedures and memory deallocation for the child process.
 *
 * @param program_name
 *   The name of the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param names
 *   An array of strings representing the environment variable names.
 *   At most names.used variables are created.
 *   Duplicate names are overwritten.
 * @param values
 *   An array of strings representing the environment variable names.
 *   The values.used must be of at least names.used.
 *   Set individual strings.used to 0 for empty/null values.
 * @param signals
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param pipe
 *   (optional) A pointer to a string to pipe as standard input to the child process.
 *   Set to 0 to disable.
 * @param result
 *   The code returned after finishing execution of program.
 *
 * @return
 *   F_none on success.
 *   F_child on success but this is the child thread.
 *   F_failure (with error bit) on execution failure.
 *   F_fork (with error bit) on fork failure.
 *   F_pipe (with error bit) on pipe failure.
 *
 *   Errors (with error bit) from: f_environment_get().
 *   Errors (with error bit) from: f_file_exists().
 *   Errors (with error bit) from: f_macro_string_dynamic_t_delete().
 *   Errors (with error bit) from: f_macro_string_dynamics_t_delete().
 *   Errors (with error bit) from: f_signal_set_handle().
 *   Errors (with error bit) from: fl_environment_path_explode_dynamic().
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *
 * @see close()
 * @see clearenv()
 * @see dup2()
 * @see execvp()
 * @see fork()
 * @see memcpy()
 * @see pipe()
 * @see strnlen()
 * @see waitpid()
 *
 * @see f_environment_get()
 * @see f_file_exists()
 * @see f_signal_set_handle()
 * @see fl_environment_path_explode_dynamic()
 * @see fl_string_append()
 * @see fl_string_dynamic_terminate()
 */
#ifndef _di_fll_execute_program_environment_
  extern f_return_status fll_execute_program_environment(const f_string_t program_name, const f_string_statics_t arguments, const f_string_statics_t names, const f_string_statics_t values, const f_signal_how_t *signals, f_string_static_t * const pipe, int *result);
#endif // _di_fll_execute_program_environment_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_execute_h
