/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fake_h
#define _PRIVATE_fake_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_common_
  #define fake_common_initial_buffer_max 131072 // 128k max default initial buffer size.

  #define fake_common_setting_bool_yes "yes"
  #define fake_common_setting_bool_no  "no"

  #define fake_common_setting_bool_yes_length 3
  #define fake_common_setting_bool_no_length  2
#endif // _di_fake_common_

/**
 * Execute the given command and arguments.
 *
 * Will print the command if in verbose mode.
 *
 * @param main
 *   The main data.
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
 */
#ifndef _di_fake_execute_
  extern int fake_execute(const fake_main_t main, const f_string_maps_t environment, const f_string_static_t program, const f_string_statics_t arguments, f_status_t *status) f_attribute_visibility_internal;
#endif // _di_fake_execute_

/**
 * Load the contents of a file into the given buffer, handling all potential errors.
 *
 * @param main
 *   The main data.
 * @param path_file
 *   The path to the file to load.
 * @param buffer
 *   A buffer containing the contents of the file.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_file_buffer_
  extern f_status_t fake_file_buffer(const fake_main_t main, const f_string_t path_file, f_string_dynamic_t *buffer) f_attribute_visibility_internal;
#endif // _di_fake_file_buffer_

/**
 * Generate all appropriate paths based on runtime information.
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_path_generate_
  extern f_status_t fake_path_generate(fake_main_t *main) f_attribute_visibility_internal;
#endif // _di_fake_path_generate_

/**
 * Generate all appropriate paths based on runtime information from dynamic strings.
 *
 * @param main
 *   The main data.
 * @param source
 *   The string to copy from.
 * @param destination
 *   An array of pointers to the strings to append onto.
 * @param length
 *   The size of the values.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_path_generate_string_dynamic_
  extern f_status_t fake_path_generate_string_dynamic(fake_main_t *main, const f_string_dynamic_t source, f_string_dynamic_t *destination[], const uint8_t size) f_attribute_visibility_internal;
#endif // _di_fake_path_generate_string_dynamic_

/**
 * Validate console arguments and print any relating error messages.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_process_console_parameters_
  extern f_status_t fake_process_console_parameters(const f_console_arguments_t arguments, fake_main_t *main) f_attribute_visibility_internal;
#endif // _di_validate_console_parameters_

/**
 * Check to see if a termination signal has been received.
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_true if a termination signal is received.
 *   F_false if no termination signal is received.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_signal_read_
  extern f_status_t fake_signal_received(const fake_main_t main) f_attribute_visibility_internal;
#endif // _di_fake_signal_read_

/**
 * Validate directories and print any relating error messages.
 *
 * This should not be called for skeleton as in that case the directories probably do not exist.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_validate_parameter_directories_
  extern f_status_t fake_validate_parameter_directories(const f_console_arguments_t arguments, const fake_main_t main) f_attribute_visibility_internal;
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
  extern void fake_verbose_print_clone(const f_file_t output, const f_string_t source, const f_string_t destination) f_attribute_visibility_internal;
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
  extern void fake_verbose_print_copy(const f_file_t output, const f_string_t source, const f_string_t destination) f_attribute_visibility_internal;
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
  extern void fake_verbose_print_move(const f_file_t output, const f_string_t source, const f_string_t destination) f_attribute_visibility_internal;
#endif // _di_fake_verbose_print_move_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fake_h
