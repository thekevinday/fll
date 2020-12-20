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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
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
 *   Errors (with error bit) from: fl_string_append().
 *   Errors (with error bit) from: fl_string_dynamic_delete().
 *   Errors (with error bit) from: fl_string_dynamic_terminate().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see fl_string_append()
 * @see fl_string_dynamic_delete()
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
 * This implementation ignores parameter.data.
 *
 * @param program
 *   The name or path of the program.
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
 *     An array of strings representing the environment variable values.
 *     The values.used must be of at least names.used.
 *     Set individual strings.used to 0 for empty/null values.
 *   signals:
 *     A pointer to the set of signals to have the child process block or not block.
 *     When not specified, the child process uses the signal blocking behavior of the parent process.
 *   data:
 *     A pointer to a string to pipe as standard input to the child process.
 *     The parent will block until the standard input is fully read or the child process exits.
 * @param result
 *   The code returned after finishing execution of program.
 *
 * @return
 *   F_none on success.
 *   F_child on success but this is the child thread.
 *   F_failure (with error bit) on execution failure.
 *   F_fork (with error bit) on fork failure.
 *
 * @see clearenv()
 * @see execv()
 * @see execvp()
 * @see fork()
 * @see waitpid()
 *
 * @see f_environment_set_dynamic()
 * @see f_signal_set_handle()
 * @see fll_execute_program()
 */
#if !defined(_di_fll_execute_program_)
  extern f_return_status private_fll_execute_fork(const f_string_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, int *result) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_program_)

/**
 * Private function for performing the fork and execute operation.
 *
 * This implementation requires parameter.data.
 *
 * @param program
 *   The name or path of the program.
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
 *     An array of strings representing the environment variable values.
 *     The values.used must be of at least names.used.
 *     Set individual strings.used to 0 for empty/null values.
 *   signals:
 *     A pointer to the set of signals to have the child process block or not block.
 *     When not specified, the child process uses the signal blocking behavior of the parent process.
 *   data:
 *     A pointer to a string to pipe as standard input to the child process.
 *     The parent will block until the standard input is fully read or the child process exits.
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
 * @see f_signal_set_handle()
 * @see fll_execute_program()
 */
#if !defined(_di_fll_execute_program_)
  extern f_return_status private_fll_execute_fork_data(const f_string_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, int *result) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_program_)

/**
 * Private function for reconstructing the arguments into a fixed array.
 *
 * @param program_path
 *   The part of the path to the program representing the program name to copy from.
 * @param arguments
 *   An array of strings representing the arguments.
 * @param fixated_is
 *   If TRUE, then this is a path to a program (such as "/bin/bash").
 *   If FALSE, then this is not a path to a program (such as "bash").
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
  extern void private_fll_execute_path_arguments_fixate(const f_string_t program_path, const f_string_statics_t arguments, const bool fixated_is, const f_string_length_t name_size, char program_name[], f_string_t fixed_arguments[]) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_execute_program_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_execute_h
