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
 *
 *   Errors (with error bit) from: f_macro_string_dynamic_t_delete_simple().
 *   Errors (with error bit) from: f_macro_string_dynamics_t_resize().
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see f_macro_string_dynamic_t_delete_simple()
 * @see f_macro_string_dynamics_t_resize()
 * @see fl_string_append()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
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
 *
 *   Errors (with error bit) from: f_macro_string_dynamic_t_delete_simple().
 *   Errors (with error bit) from: f_macro_string_dynamics_t_resize().
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see f_macro_string_dynamic_t_delete_simple()
 * @see f_macro_string_dynamics_t_resize()
 * @see fl_string_append()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamics_increase()
 * @see fll_execute_arguments_add_parameter()
 * @see fll_execute_arguments_add_parameter_set()
 * @see fll_execute_arguments_dynamic_add_parameter()
 * @see fll_execute_arguments_dynamic_add_parameter_set()
 */
#if !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)
  extern f_return_status private_fll_execute_arguments_add_parameter(const f_string_t prefix, const f_string_length_t prefix_length, const f_string_t name, const f_string_length_t name_length, const f_string_t value, const f_string_length_t value_length, f_string_dynamics_t *arguments) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)

/**
 * Private function for performing the fork and execute operation.
 *
 * @param program_path
 *   The part of the path to the program representing the program name to copy from.
 * @param fixed_arguments
 *   A fixed array of strings representing the arguments.
 * @param program_is
 *   If TRUE then execvp() is called to perform execution.
 *   If FALSE then execv() is called to perform execution.
 * @param set_signal
 *   (optional) A pointer to the set of signals.
 *   Set to 0 to disable.
 * @param pipe
 *   (optional) A pointer to the set of pipe desciptors (I/O) to be used by the child process.
 *   When a non-zero address, the child process will assign these as the standard I/O file descriptors for piping to/from the parent/child.
 *   For each pipe, setting a value of -1 means to use the default pipe.
 *   Set to 0 to disable.
 * @param result
 *   The code returned after finishing execution of program_path.
 *
 * @return
 *   F_none on success.
 *   F_child on success but this is the child thread.
 *   F_parent on success but this is the parent thread and pipe is non-zero (function is not blocking).
 *   F_failure (with error bit set) on execution failure.
 *   F_fork (with error bit set) on fork failure.
 *
 * @see execv()
 * @see execvp()
 * @see fll_execute_path()
 * @see fll_execute_program()
 */
#if !defined(_di_fll_execute_path_) || !defined(_di_fll_execute_program_)
  extern f_return_status private_fll_execute_fork(const f_string_t program_path, const f_string_t fixed_arguments[], const bool program_is, const f_signal_how_t *signals, f_execute_pipe_t * const pipe, int *result) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_path_) || !defined(_di_fll_execute_program_)

/**
 * Private function for performing the fork and execute operation using a specified environment.
 *
 * @param program_path
 *   The part of the path to the program representing the program name to copy from.
 * @param fixed_arguments
 *   A fixed array of strings representing the arguments.
 * @param program_is
 *   If TRUE then execvp() is called to perform execution.
 *   If FALSE then execv() is called to perform execution.
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
 *   (optional) A pointer to the set of pipe desciptors (I/O) to be used by the child process.
 *   When a non-zero address, the child process will assign these as the standard I/O file descriptors for piping to/from the parent/child.
 *   For each pipe, setting a value of -1 means to use the default pipe.
 *   Set to 0 to disable.
 * @param result
 *   The code returned after finishing execution of program_path.
 *
 * @return
 *   F_none on success.
 *   F_child on success but this is the child thread.
 *   F_parent on success but this is the parent thread and pipe is non-zero (function is not blocking).
 *   F_failure (with error bit set) on execution failure.
 *   F_fork (with error bit set) on fork failure.
 *
 * @see execv()
 * @see execvpe()
 * @see fll_execute_path_environment()
 * @see fll_execute_program_environment()
 */
#if !defined(_di_fll_execute_path_environment_) || !defined(_di_fll_execute_program_environment_)
  extern f_return_status private_fll_execute_fork_environment(const f_string_t program_path, const f_string_t fixed_arguments[], const bool program_is, const f_string_statics_t names, const f_string_statics_t values, const f_signal_how_t *signals, f_execute_pipe_t * const pipe, int *result) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_path_environment_) || !defined(_di_fll_execute_program_environment_)

/**
 * Private function for reconstructing the arguments into a fixed array.
 *
 * @param program_path
 *   The part of the path to the program representing the program name to copy from.
 * @param arguments
 *   An array of strings representing the arguments.
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
 * @see fll_execute_path()
 * @see fll_execute_path_environment()
 */
#if !defined(_di_fll_execute_path_) || !defined(_di_fll_execute_path_environment_)
  extern void private_fll_execute_path_arguments_fixate(const f_string_t program_path, const f_string_statics_t arguments, const f_string_length_t name_size, char program_name[], f_string_t fixed_arguments[]) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_path_) || !defined(_di_fll_execute_path_environment_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_execute_h
