/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_fake_print_h
#define _PRIVATE_fake_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print build operation file error messages.
 *
 * @param main
 *   The main program data.
 * @param status
 *   The error status code to report on.
 * @param function
 *   The name of the function where the error happened.
 * @param operation
 *   The operation performed.
 * @param source
 *   The operation source.
 *   Set to 0 to disable.
 * @param destination
 *   The operation destination, if applicable.
 *   Requires source to be non-zero.
 *   Set to 0 to disable.
 * @param how
 *   The how the operation is perform, such as "to" in "copy" source "to" destination.
 *   Requires source and destination to be non-zero.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_fake_print_error_operation_file_
  extern bool fake_print_error_build_operation_file(fake_main_t * const main, const f_status_t status, const f_string_t function, const f_string_t operation, const f_string_t source, const f_string_t destination, const f_string_t how, const bool fallback) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_operation_file_

/**
 * Print FSS error messages.
 *
 * @param main
 *   The main program data.
 * @param status
 *   The error status code to report on.
 * @param function
 *   The function call that returned the error.
 * @param path_file
 *   The path to the file.
 * @param range
 *   The range representing the position in the buffer such that range.start is where the error happened.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 */
#ifndef _di_fake_print_error_fss_
  extern bool fake_print_error_fss(fake_main_t * const main, const f_status_t status, const f_string_t function, const f_string_t path_file, const f_string_range_t range, const bool fallback) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_fss_

/**
 * Print an error message for when the parameter is missing its accompanying value.
 *
 * @param main
 *   The main program data.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_fake_print_error_parameter_missing_value_
  extern void fake_print_error_parameter_missing_value(fake_main_t * const main, const f_string_t parameter) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_parameter_missing_value_

/**
 * Print an error message for when the parameter is specified too many times.
 *
 * @param main
 *   The main program data.
 * @param parameter
 *   The parameter name.
 */
#ifndef _di_fake_print_error_parameter_too_many_
  extern void fake_print_error_parameter_too_many(fake_main_t * const main, const f_string_t parameter) F_attribute_visibility_internal_d;
#endif // _di_fake_print_error_parameter_too_many_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation failed.
 *
 * @param main
 *   The main program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 */
#ifndef _di_fake_print_message_section_operation_failed_
  extern void fake_print_message_section_operation_failed(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_failed_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation has a path outside of the project root.
 *
 * @param main
 *   The main program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param status
 *   The status code representing an error.
 * @param function
 *   The name of the function where the error happened.
 * @param path
 *   The path that is outside of the project path.
 */
#ifndef _di_fake_print_message_section_operation_path_outside_
  extern void fake_print_message_section_operation_path_outside(fake_main_t * const main, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_t path) F_attribute_visibility_internal_d;
#endif // _fake_print_message_section_operation_path_outside_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation.
 *
 * @param main
 *   The main program data.
 * @param error
 *   Designates how the section error/warning should be printed.
 * @param status
 *   The status code representing an error.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param path
 *   The path to the directory.
 */
#ifndef _di_fake_print_message_section_operation_path_stack_max_
  extern void fake_print_message_section_operation_path_stack_max(fake_main_t * const main, fl_print_t error, const f_status_t status, const f_string_t function, const f_string_t path) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_path_stack_max_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that the max stack depth is reached.
 *
 * @param main
 *   The main program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 * @param stack_max
 *   The max stack depth.
 */
#ifndef _di_fake_print_message_section_operation_stack_max_
  extern void fake_print_message_section_operation_stack_max(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_stack_max_

/**
 * Print error messages when processing some fakefile section, for a specific line and operation, and that operation is invalid.
 *
 * @param main
 *   The main program data.
 * @param print
 *   Designates how the section error/warning should be printed.
 * @param buffer
 *   The buffer containing the fakefile data.
 * @param section_name
 *   The range within the buffer representing the section name.
 * @param operation_name
 *   The range within the buffer representing the operation name within the section.
 */
#ifndef _di_fake_print_message_section_operation_unknown_
  extern void fake_print_message_section_operation_unknown(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) F_attribute_visibility_internal_d;
#endif // _di_fake_print_message_section_operation_unknown_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 * @param signal
 *   The signal received.
 */
#ifndef _di_fake_print_signal_received_
  extern void fake_print_signal_received(fake_main_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_fake_print_signal_received_

/**
 * Print message when fake settings content is empty.
 *
 * @param main
 *   The main program data.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param range_object
 *   The range within the buffer representing the object.
 * @param settings_name
 *   The name of the setting that has an invalid value.
 */
#ifndef _di_fake_print_warning_settings_content_empty_
  extern void fake_print_warning_settings_content_empty(fake_main_t * const main, const f_string_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_t settings_name) F_attribute_visibility_internal_d;
#endif // _di_fake_print_warning_settings_content_empty_

/**
 * Print warning message when fake settings content is invalid.
 *
 * @param main
 *   The main program data.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param range_object
 *   The range within the buffer representing the object.
 * @param range_content
 *   The range within the buffer representing the content.
 * @param settings_name
 *   The name of the setting that has an invalid value.
 */
#ifndef _di_fake_print_warning_settings_content_invalid_
  extern void fake_print_warning_settings_content_invalid(fake_main_t * const main, const f_string_t path_file, const f_string_dynamic_t buffer, const f_string_range_t range_object, const f_string_range_t range_content, const f_string_t settings_name) F_attribute_visibility_internal_d;
#endif // _di_fake_print_warning_settings_content_invalid_

/**
 * Print warning message when settings content has too many values.
 *
 * @param main
 *   The main program data.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param name_object
 *   The name of the object.
 */
#ifndef _di_fake_print_warning_settings_content_multiple_
  extern void fake_print_warning_settings_content_multiple(fake_main_t * const main, const f_string_t path_file, const f_string_t name_object) F_attribute_visibility_internal_d;
#endif // _di_fake_print_warning_settings_content_multiple_

/**
 * Print warning message when fakefile has too many objects with the same name.
 *
 * @param main
 *   The main program data.
 * @param path_file
 *   The path to the fakefile.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param label
 *   A label describing what this object belongs to.
 * @param name_object
 *   The name of the object.
 */
#ifndef _di_fake_print_warning_settings_object_multiple_
  extern void fake_print_warning_settings_object_multiple(fake_main_t * const main, const f_string_t path_file, const f_string_t label, const f_string_t name_object) F_attribute_visibility_internal_d;
#endif // _di_fake_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fake_print_h
