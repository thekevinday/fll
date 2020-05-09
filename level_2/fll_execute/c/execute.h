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
#include <linux/limits.h> // defines PATH_MAX
#include <memory.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>

// fll-1 includes
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
 *   f_none on success.
 *   f_no_data if source length is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 */
#ifndef _di_fll_execute_arguments_add_
  extern f_return_status fll_execute_arguments_add(const f_string source, const f_string_length length, f_string_dynamics *arguments);
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
 *   f_none on success.
 *   f_no_data if source length is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 */
#ifndef _di_fll_execute_arguments_add_parameter_
  extern f_return_status fll_execute_arguments_add_parameter(const f_string prefix, const f_string_length prefix_length, const f_string name, const f_string_length name_length, const f_string value, const f_string_length value_length, f_string_dynamics *arguments);
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
 *   f_none on success.
 *   f_no_data if size is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 */
#ifndef _di_fll_execute_arguments_add_parameter_set_
  extern f_return_status fll_execute_arguments_add_parameter_set(const f_string prefix[], const f_string_length prefix_length[], const f_string name[], const f_string_length name_length[], const f_string value[], const f_string_length value_length[], const f_array_length size, f_string_dynamics *arguments);
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
 *   f_none on success.
 *   f_no_data if size is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 */
#ifndef _di_fll_execute_arguments_add_set_
  extern f_return_status fll_execute_arguments_add_set(const f_string source[], const f_string_length length[], const f_array_length size, f_string_dynamics *arguments);
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
 *   f_none on success.
 *   f_no_data if source length is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 */
#ifndef _di_fll_execute_arguments_dynamic_add_
  extern f_return_status fll_execute_arguments_dynamic_add(const f_string_static source, f_string_dynamics *arguments);
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
 *   f_none on success.
 *   f_no_data if source length is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 */
#ifndef _di_fll_execute_arguments_dynamic_add_parameter_
  extern f_return_status fll_execute_arguments_dynamic_add_parameter(const f_string_static prefix, const f_string_static name, const f_string_static value, f_string_dynamics *arguments);
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
 *   f_none on success.
 *   f_no_data if source length is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 */
#ifndef _di_fll_execute_arguments_dynamic_add_parameter_set_
  extern f_return_status fll_execute_arguments_dynamic_add_parameter_set(const f_string_static prefix[], const f_string_static name[], const f_string_static value[], const f_array_length size, f_string_dynamics *arguments);
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
 *   f_none on success.
 *   f_no_data if source length is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 */
#ifndef _di_fll_execute_arguments_dynamic_add_set_
  extern f_return_status fll_execute_arguments_dynamic_add_set(const f_string_static source[], const f_array_length size, f_string_dynamics *arguments);
#endif // _di_fll_execute_arguments_dynamic_add_set_

/**
 * Execute a program given some path + program name (such as "/bin/bash").
 *
 * @param program_path
 *   The entire path to the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param result
 *   The code returned after finishing execution of program_path.
 *
 * @return
 *   f_none on success.
 *   f_failure (with error bit) if result is non-zero.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *
 * @see execv()
 */
#ifndef _di_fll_execute_path_
  extern f_return_status fll_execute_path(const f_string program_path, const f_string_dynamics arguments, int *result);
#endif // _di_fll_execute_path_

/**
 * Execute a program given by name found in the PATH environment (such as "bash").
 *
 * @param program_name
 *   The name of the program.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param result
 *   The code returned after finishing execution of program.
 *
 * @return
 *   f_none on success.
 *   f_failure (with error bit) if result is non-zero.
 *   f_fork_failed (with error bit) on fork failure.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *
 * @see execvp()
 */
#ifndef _di_fll_execute_program_
  extern f_return_status fll_execute_program(const f_string program_name, const f_string_dynamics arguments, int *result);
#endif // _di_fll_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_execute_h
