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
 *   F_data_not if source length is 0.
 *   F_buffer_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
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
 *   F_data_not if source length is 0.
 *   F_buffer_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
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
 *   F_data_not if size is 0.
 *   F_buffer_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
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
 *   F_data_not if size is 0.
 *   F_buffer_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
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
 *   F_data_not if source length is 0.
 *   F_buffer_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
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
 *   F_data_not if source length is 0.
 *   F_buffer_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
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
 *   F_data_not if source length is 0.
 *   F_buffer_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
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
 *   F_data_not if source length is 0.
 *   F_buffer_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 */
#ifndef _di_fll_execute_arguments_dynamic_add_set_
  extern f_return_status fll_execute_arguments_dynamic_add_set(const f_string_static_t source[], const f_array_length_t size, f_string_dynamics_t *arguments);
#endif // _di_fll_execute_arguments_dynamic_add_set_

/**
 * Execute a program given some path + program name (such as "/bin/bash").
 *
 * This does validate that the program path exists.
 *
 * @param program_path
 *   The entire path to the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param set_signal
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param result
 *   The code returned after finishing execution of program_path.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied for program_path.
 *   F_directory (with error bit) on invalid directory in program_path.
 *   F_failure (with error bit) if result is non-zero.
 *   F_file_found_not (with error bit) if file does not exist at the program_path.
 *   F_file_stat (with error bit) on stat error while checking the program_path.
 *   F_loop (with error bit) on loop error while checking the program_path.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_file_exists().
 *
 * @see execv()
 */
#ifndef _di_fll_execute_path_
  extern f_return_status fll_execute_path(const f_string_t program_path, const f_string_statics_t arguments, const f_signal_how_t *signals, int *result);
#endif // _di_fll_execute_path_

/**
 * Execute a program given some path + program name (such as "/bin/bash").
 *
 * This does validate that the program path exists.
 *
 * The environment is defined by the names and values pair.
 *
 * @param program_path
 *   The entire path to the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param names
 *   An array of strings representing the environment variable names.
 *   At most names.used variables are created.
 *   Duplicate names are overwritten.
 * @param set_signal
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param values
 *   An array of strings representing the environment variable names.
 *   The values.used must be of at least names.used.
 *   Set individual strings.used to 0 for empty/NULL values.
 * @param result
 *   The code returned after finishing execution of program_path.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied for program_path.
 *   F_directory (with error bit) on invalid directory in program_path.
 *   F_failure (with error bit) if result is non-zero.
 *   F_file_found_not (with error bit) if file does not exist at the program_path.
 *   F_file_stat (with error bit) on stat error while checking the program_path.
 *   F_loop (with error bit) on loop error while checking the program_path.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_file_exists().
 *
 * @see execv()
 */
#ifndef _di_fll_execute_path_environment_
  f_return_status fll_execute_path_environment(const f_string_t program_path, const f_string_statics_t arguments, const f_signal_how_t *signals, const f_string_statics_t names, const f_string_statics_t values, int *result);
#endif // _di_fll_execute_path_environment_

/**
 * Execute a program given by name found in the PATH environment (such as "bash").
 *
 * This does not validate the path to the program.
 *
 * @param program_name
 *   The name of the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param set_signal
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param result
 *   The code returned after finishing execution of program.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) if result is non-zero.
 *   F_file_found_not (with error bit) if file does not exist at the program_path.
 *   F_fork (with error bit) on fork failure.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string (generated from PATH) is too large.
 *
 *   Errors (with error bit) from: f_file_exists().
 *
 * @see execvp()
 */
#ifndef _di_fll_execute_program_
  extern f_return_status fll_execute_program(const f_string_t program_name, const f_string_statics_t arguments, const f_signal_how_t *signals, int *result);
#endif // _di_fll_execute_program_

/**
 * Execute a program given by name found in the PATH environment (such as "bash").
 *
 * Uses the provided environment array to designate the environment for the called program.
 *
 * This does validate the path to the program because it completes the path to the program.
 * This is done because the PATH environment will get cleared or may be set differently.
 * Execution of program_name is done using the PATH environment prior to clearing and reassigning the environment variables.
 *
 * @param program_name
 *   The name of the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param names
 *   An array of strings representing the environment variable names.
 *   At most names.used variables are created.
 *   Duplicate names are overwritten.
 * @param set_signal
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param values
 *   An array of strings representing the environment variable names.
 *   The values.used must be of at least names.used.
 *   Set individual strings.used to 0 for empty/null values.
 * @param result
 *   The code returned after finishing execution of program.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied for program_path.
 *   F_buffer_too_large (with error bit) if paths array (generated from PATH) is too large for further addressing.
 *   F_directory (with error bit) on invalid directory in program_path.
 *   F_failure (with error bit) if result is non-zero.
 *   F_file_found_not (with error bit) if file does not exist at the program_path.
 *   F_fork (with error bit) on fork failure.
 *   F_loop (with error bit) on loop error while checking the program_path.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string (generated from PATH) is too large.
 *
 *   Errors (with error bit) from: f_file_exists().
 *   Errors (with error bit) from: fl_environment_path_explode_dynamic().
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *
 * @see execvpe()
 */
#ifndef _di_fll_execute_program_environment_
  extern f_return_status fll_execute_program_environment(const f_string_t program_name, const f_string_statics_t arguments, const f_signal_how_t *signals, const f_string_statics_t names, const f_string_statics_t values, int *result);
#endif // _di_fll_execute_program_environment_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_execute_h
