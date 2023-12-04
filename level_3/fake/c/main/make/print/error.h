/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make error print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_print_error_h
#define _fake_make_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print error about a define setting containing an invalid character.
 *
 * These only allow valid characters in an environment variable name.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The invalid section name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_argument_invalid_section_
  extern f_status_t fake_make_print_error_argument_invalid_section(fl_print_t * const print, const f_string_static_t name);
#endif // _di_fake_make_print_error_argument_invalid_section_

/**
 * Print error about a compiler not being specified.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The action that cannot be performed due to a lack of a compiler.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_compiler_not_specified_
  extern f_status_t fake_make_print_error_compiler_not_specified(fl_print_t * const print, const f_string_static_t action);
#endif // _di_fake_make_print_error_compiler_not_specified_

/**
 * Print error about a define setting containing an invalid character.
 *
 * These only allow valid characters in an environment variable name.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the variable containing one or more invalid characters.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_define_invalid_character_
  extern f_status_t fake_make_print_error_define_invalid_character(fl_print_t * const print, const f_string_static_t name);
#endif // _di_fake_make_print_error_define_invalid_character_

/**
 * Print error about a given fakefile missing a section.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param section
 *   The name of the missing section.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_fakefile_section_missing_
  extern f_status_t fake_make_print_error_fakefile_section_missing(fl_print_t * const print, const f_string_static_t fakefile, const f_string_static_t section);
#endif // _di_fake_make_print_error_fakefile_section_missing_

/**
 * Print error about a file name being an empty string.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_file_name_empty_
  extern f_status_t fake_make_print_error_file_name_empty(fl_print_t * const print);
#endif // _di_fake_make_print_error_file_name_empty_

/**
 * Print error about the second file not being of a directory.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param content
 *   A string representing which content.
 * @param file
 *   The second content that should be a directory.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_content_not_directory_
  extern f_status_t fake_make_print_error_content_not_directory(fl_print_t * const print, const f_string_t content, const f_string_static_t file);
#endif // _di_fake_make_print_error_content_not_directory_

/**
 * Print error about a define name being an empty string.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_define_name_empty_
  extern f_status_t fake_make_print_error_define_name_empty(fl_print_t * const print);
#endif // _di_fake_make_print_error_define_name_empty_

/**
 * Print error about a file not being of a specific type.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param type
 *   The expected type of the file.
 * @param file
 *   The file path or name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_file_type_
  extern f_status_t fake_make_print_error_file_type(fl_print_t * const print, const f_string_static_t type, const f_string_static_t file);
#endif // _di_fake_make_print_error_file_type_

/**
 * Print error about a indexer not being specified.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param action
 *   The action that cannot be performed due to a lack of a compiler.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_indexer_not_specified_
  extern f_status_t fake_make_print_error_indexer_not_specified(fl_print_t * const print, const f_string_static_t action);
#endif // _di_fake_make_print_error_indexer_not_specified_

/**
 * Print error about how using something after a condition statement.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param message
 *   The message describing how in relation to the after condition.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_after_condition_
  extern f_status_t fake_make_print_error_after_condition(fl_print_t * const print, const f_string_t message);
#endif // _di_fake_make_print_error_after_condition_

/**
 * Print error about how using something after a condition statement, for the "may only" case.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_after_condition_may_only_
  extern f_status_t fake_make_print_error_after_condition_may_only(fl_print_t * const print);
#endif // _di_fake_make_print_error_after_condition_may_only_

/**
 * Print error about how using something after a condition statement, for the "must not" case.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_after_condition_must_not_
  extern f_status_t fake_make_print_error_after_condition_must_not(fl_print_t * const print);
#endif // _di_fake_make_print_error_after_condition_must_not_

/**
 * Print error about how using something after a condition statement, for the "no preceding" case.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_after_condition_no_preceding_
  extern f_status_t fake_make_print_error_after_condition_no_preceding(fl_print_t * const print);
#endif // _di_fake_make_print_error_after_condition_no_preceding_

/**
 * Print error about an incomplete operation at the end of a section.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param operation
 *   The code of the operation.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_operation_incomplete_
  extern f_status_t fake_make_print_error_operation_incomplete(fl_print_t * const print, const uint8_t operation);
#endif // _di_fake_make_print_error_operation_incomplete_

/**
 * Print error about an operation recursion not being allowed.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param buffer
 *   The buffer containing the range to use.
 * @param range
 *   The range within the buffer representing the operation name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_operation_recursion_
  extern f_status_t fake_make_print_error_operation_recursion(fl_print_t * const print, const f_string_static_t buffer, const f_range_t range);
#endif // _di_fake_make_print_error_operation_recursion_

/**
 * Print error about an operation section not being found.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the operation.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_operation_section_not_found_
  extern f_status_t fake_make_print_error_operation_section_not_found(fl_print_t * const print, const f_string_static_t name);
#endif // _di_fake_make_print_error_operation_section_not_found_

/**
 * Print error about number being out of range.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param number
 *   The string representing the number.
 * @param minimum
 *   The minimum number allowed, represented as a negative.
 * @param maximum
 *   The number allowed, represented as a positive.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_out_of_range_number_
  extern f_status_t fake_make_print_error_out_of_range_number(fl_print_t * const print, const f_string_static_t number, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum);
#endif // _di_fake_make_print_error_out_of_range_number_

/**
 * Print error about attempting to pop last path off the project path stack.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_pop_last_path_
  extern f_status_t fake_make_print_error_pop_last_path(fl_print_t * const print);
#endif // _di_fake_make_print_error_pop_last_path_

/**
 * Print error about program failed.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param return_code
 *   The return code from the program.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_program_failed_
  extern f_status_t fake_make_print_error_program_failed(fl_print_t * const print, const int return_code);
#endif // _di_fake_make_print_error_program_failed_

/**
 * Print error about program not being found.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param program
 *   The program name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_program_not_found_
  extern f_status_t fake_make_print_error_program_not_found(fl_print_t * const print, const f_string_static_t program);
#endif // _di_fake_make_print_error_program_not_found_

/**
 * Print error about attempting to assign to a reserved parameter name.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The reserved parameter name.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_reserved_parameter_name_
  extern f_status_t fake_make_print_error_reserved_parameter_name(fl_print_t * const print, const f_string_static_t name);
#endif // _di_fake_make_print_error_reserved_parameter_name_

/**
 * Print error about a target file name being an empty string.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_target_file_name_empty_
  extern f_status_t fake_make_print_error_target_file_name_empty(fl_print_t * const print);
#endif // _di_fake_make_print_error_target_file_name_empty_

/**
 * Print error about number not being supported.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param number
 *   The string representing the number.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_unsupported_number_
  extern f_status_t fake_make_print_error_unsupported_number(fl_print_t * const print, const f_string_static_t number);
#endif // _di_fake_make_print_error_unsupported_number_

/**
 * Print error about type not being supported.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param type
 *   The string representing the type.
 * @param value
 *   The value that is unsupported for the type.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_error_unsupported_type_
  extern f_status_t fake_make_print_error_unsupported_type(fl_print_t * const print, const f_string_static_t type, const f_string_static_t value);
#endif // _di_fake_make_print_error_unsupported_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_print_error_h
