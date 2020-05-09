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
 *   f_none on success.
 *   f_no_data if length is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 *
 * @see fll_execute_arguments_add()
 * @see fll_execute_arguments_add_set()
 * @see fll_execute_arguments_dynamic_add()
 * @see fll_execute_arguments_dynamic_add_set()
 */
#if !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)
  extern f_return_status private_fll_execute_arguments_add(const f_string source, const f_string_length length, f_string_dynamics *arguments) f_gcc_attribute_visibility_internal;
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
 *   f_none on success.
 *   f_no_data if name_length is 0.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on allocation error.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_buffer_too_large (with error bit) if arguments array is too larger for further allocation.
 *
 * @see fll_execute_arguments_add_parameter()
 * @see fll_execute_arguments_add_parameter_set()
 * @see fll_execute_arguments_dynamic_add_parameter()
 * @see fll_execute_arguments_dynamic_add_parameter_set()
 */
#if !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)
  extern f_return_status private_fll_execute_arguments_add_parameter(const f_string prefix, const f_string_length prefix_length, const f_string name, const f_string_length name_length, const f_string value, const f_string_length value_length, f_string_dynamics *arguments) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_execute_h
