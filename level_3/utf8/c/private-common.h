/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print error message for when no sources are provided.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_utf8_print_error_no_from_
  extern void utf8_print_error_no_from(utf8_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_no_from_

/**
 * Print error message for when no sources are provided.
 *
 * @param main
 *   The main program data.
 * @param parameter_1
 *   The long parameter name.
 */
#ifndef _di_utf8_print_error_no_value_
  extern void utf8_print_error_no_value(utf8_main_t * const main, const f_string_t parameter) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_no_value_

/**
 * Print error message for two parameters not being allowed to be used together.
 *
 * @param main
 *   The main program data.
 * @param first
 *   The long parameter name for the first parameter.
 * @param second
 *   The long parameter name for the second parameter.
 */
#ifndef _di_utf8_print_error_parameter_conflict_
  extern void utf8_print_error_parameter_conflict(utf8_main_t * const main, const f_string_t first, const f_string_t second) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_parameter_conflict_

/**
 * Print error message for when the file parameter is an empty string.
 *
 * @param main
 *   The main program data.
 * @param index
 *   The index within the argv[] array where the empty string is found.
 */
#ifndef _di_utf8_print_error_parameter_file_name_empty_
  extern void utf8_print_error_parameter_file_name_empty(utf8_main_t * const main, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_parameter_file_name_empty_

/**
 * Print error message for when no sources are provided in the main program parameters.
 *
 * @param main
 *   The main program data.
 * @param from
 *   If TRUE, then this is a from file (source file).
 *   If FALSE, then this is a to file (destination file).
 * @param name
 *   The file path name.
 */
#ifndef _di_utf8_print_error_parameter_file_not_found_
  extern void utf8_print_error_parameter_file_not_found(utf8_main_t * const main, const bool from, const f_string_t name) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_parameter_file_not_found_

/**
 * Print error message for when too many 'to' destinations are specified.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  extern void utf8_print_error_parameter_file_to_too_many(utf8_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_error_parameter_file_to_too_many_

/**
 * Print the input file section header.
 *
 * @param main
 *   The main program data.
 * @param name
 *   The name of the file.
 */
#ifndef _di_utf8_print_section_header_file_
  extern void utf8_print_section_header_file(utf8_main_t * const main, const f_string_t name) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_section_header_file_

/**
 * Print the input parameter section header.
 *
 * @param main
 *   The main program data.
 * @param index
 *   The index position of the parameter.
 */
#ifndef _di_utf8_print_section_header_parameter_
  extern void utf8_print_section_header_parameter(utf8_main_t * const main, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_section_header_parameter_

/**
 * Print the input pipe section header.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_utf8_print_section_header_pipe_
  extern void utf8_print_section_header_pipe(utf8_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_section_header_pipe_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 * @param signal
 *   The signal code received.
 */
#ifndef _di_utf8_print_signal_received_
  extern void utf8_print_signal_received(utf8_main_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_utf8_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h