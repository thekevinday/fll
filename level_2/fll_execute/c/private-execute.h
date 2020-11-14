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
 *   F_none on success.
 *   F_data_not if name_length is 0.
 *   F_array_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fll_execute_arguments_add()
 * @see fll_execute_arguments_add_set()
 * @see fll_execute_arguments_dynamic_add()
 * @see fll_execute_arguments_dynamic_add_set()
 */
#if !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)
  extern f_return_status private_fll_execute_arguments_add(const f_string_t source, const f_string_length_t length, f_string_dynamics_t *arguments) f_gcc_attribute_visibility_internal;
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
 *   F_data_not if name_length is 0.
 *   F_array_too_large (with error bit) if arguments array is too large for further allocation.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fll_execute_arguments_add_parameter()
 * @see fll_execute_arguments_add_parameter_set()
 * @see fll_execute_arguments_dynamic_add_parameter()
 * @see fll_execute_arguments_dynamic_add_parameter_set()
 */
#if !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)
  extern f_return_status private_fll_execute_arguments_add_parameter(const f_string_t prefix, const f_string_length_t prefix_length, const f_string_t name, const f_string_length_t name_length, const f_string_t value, const f_string_length_t value_length, f_string_dynamics_t *arguments) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_execute_h
