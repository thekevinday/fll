/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_fake_h
#define _PRIVATE_fake_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the given command and arguments.
 *
 * Will print the command if in verbose mode.
 *
 * @param data
 *   The program data.
 * @param environment
 *   The environment variable data.
 * @param program
 *   The program to be executed.
 * @param arguments
 *   The arguments to be passed to the program.
 * @param status
 *   The return status.
 *
 * @return
 *   The return code result from execution.
 *   A value of 1 is returned if status has the error bit set.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 */
#ifndef _di_fake_execute_
  extern int fake_execute(fake_data_t * const data, const f_string_maps_t environment, const f_string_static_t program, const f_string_statics_t arguments, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_execute_

/**
 * Load the contents of a file into the given buffer, handling all potential errors.
 *
 * @param data
 *   The program data.
 * @param path_file
 *   The path to the file to load.
 * @param buffer
 *   A buffer containing the contents of the file.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_file_buffer_
  extern f_status_t fake_file_buffer(fake_data_t * const data, const f_string_static_t path_file, f_string_dynamic_t * const buffer) F_attribute_visibility_internal_d;
#endif // _di_fake_file_buffer_

/**
 * Validate console arguments and print any relating error messages.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_process_console_parameters_
  extern f_status_t fake_process_console_parameters(fake_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_validate_console_parameters_

/**
 * Callback passed to FSS functions for checking for interrupts.
 *
 * @param state
 *   The f_state_t data.
 * @param internal
 *   Not used.
 *
 * @return
 *   F_interrupt_not if not interrupted.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 */
#ifndef _di_fake_signal_state_interrupt_fss_
  extern f_status_t fake_signal_state_interrupt_fss(void * const state, void * const internal) F_attribute_visibility_internal_d;
#endif // _di_fake_signal_state_interrupt_fss_

/**
 * Callback passed to IKI functions for checking for interrupts.
 *
 * @param state
 *   The f_state_t data.
 * @param internal
 *   Not used.
 *
 * @return
 *   F_interrupt_not if not interrupted.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 */
#ifndef _di_fake_signal_state_interrupt_iki_
  extern f_status_t fake_signal_state_interrupt_iki(void * const state, void * const internal) F_attribute_visibility_internal_d;
#endif // _di_fake_signal_state_interrupt_iki_

/**
 * Validate directories and print any relating error messages.
 *
 * This should not be called for skeleton as in that case the directories probably do not exist.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_validate_parameter_directories_
  extern f_status_t fake_validate_parameter_directories(fake_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fake_validate_parameter_directories_

/**
 * Helper function for performing a verbose print for a file clone operation.
 *
 * @param output
 *   A file to print to.
 * @param source
 *   The source string.
 * @param destination
 *   The destination string.
 */
#ifndef _di_fake_verbose_print_clone_
  extern void fake_verbose_print_clone(const f_file_t output, const f_string_static_t source, const f_string_static_t destination) F_attribute_visibility_internal_d;
#endif // _di_fake_verbose_print_clone_

/**
 * Helper function for performing a verbose print for a file copy operation.
 *
 * @param output
 *   A file to print to.
 * @param source
 *   The source string.
 * @param destination
 *   The destination string.
 */
#ifndef _di_fake_verbose_print_copy_
  extern void fake_verbose_print_copy(const f_file_t output, const f_string_static_t source, const f_string_static_t destination) F_attribute_visibility_internal_d;
#endif // _di_fake_verbose_print_copy_

/**
 * Helper function for performing a verbose print for a file move operation.
 *
 * @param output
 *   A file to print to.
 * @param source
 *   The source string.
 * @param destination
 *   The destination string.
 */
#ifndef _di_fake_verbose_print_move_
  extern void fake_verbose_print_move(const f_file_t output, const f_string_static_t source, const f_string_static_t destination) F_attribute_visibility_internal_d;
#endif // _di_fake_verbose_print_move_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fake_h
