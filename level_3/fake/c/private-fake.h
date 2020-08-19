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

#ifndef _di_fake_environment_
  typedef struct {
    f_string_dynamics names;
    f_string_dynamics values;
  } fake_environment;

  #define fake_environment_initialize { \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
  }

  #define fake_macro_environment_delete_simple(environment) \
    f_macro_string_dynamics_delete_simple(environment.names) \
    f_macro_string_dynamics_delete_simple(environment.values)
#endif // _di_fake_environment_

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
 */
#ifndef _di_fake_execute_
  extern void fake_execute(const fake_data data, const fake_environment environment, const f_string_static program, const f_string_statics arguments, f_status *status) f_gcc_attribute_visibility_internal;
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
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_file_buffer_
  extern f_return_status fake_file_buffer(const fake_data data, const f_string path_file, f_string_dynamic *buffer) f_gcc_attribute_visibility_internal;
#endif // _di_fake_file_buffer_

/**
 * Generate all appropriate paths based on runtime information.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_path_generate_
  extern f_return_status fake_path_generate(fake_data *data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_path_generate_

/**
 * Generate all appropriate paths based on runtime information from dynamic strings.
 *
 * @param data
 *   The program data.
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
  extern f_return_status fake_path_generate_string_dynamic(fake_data *data, const f_string_dynamic source, f_string_dynamic *destination[], const uint8_t size) f_gcc_attribute_visibility_internal;
#endif // _di_fake_path_generate_string_dynamic_

/**
 * Validate console arguments and print any relating error messages.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_process_console_parameters_
  extern f_return_status fake_process_console_parameters(const f_console_arguments arguments, fake_data *data) f_gcc_attribute_visibility_internal;
#endif // _di_validate_console_parameters_

/**
 * Validate directories and print any relating error messages.
 *
 * This should not be called for skeleton as in that case the directories probably do not exist.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_validate_parameter_directories_
  extern f_return_status fake_validate_parameter_directories(const f_console_arguments arguments, const fake_data data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_validate_parameter_directories_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fake_h
