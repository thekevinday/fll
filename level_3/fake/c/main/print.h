/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fake_print_h
#define _fake_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param status
 *   The status to use.
 *   This is provided, ignoring setting.status, for thread-safety reasons.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_print()
 */
#ifndef _di_fake_print_error_
  extern f_status_t fake_print_error(fake_setting_t * const setting, const f_status_t status, const fl_print_t print, const f_string_t function);
#endif // _di_fake_print_error_

/**
 * Print generic error message regarding a function failing in some way, setting fallback to F_false and returning result.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param status
 *   The status to use.
 *   This is provided, ignoring setting.status, for thread-safety reasons.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_print()
 */
#ifndef _di_fake_print_error_fallback_
  extern f_status_t fake_print_error_fallback(fake_setting_t * const setting, const f_status_t status, const fl_print_t print, const f_string_t function);
#endif // _di_fake_print_error_fallback_

/**
 * Print file related error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param status
 *   The status to use.
 *   This is provided, ignoring setting.status, for thread-safety reasons.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_file_
  extern f_status_t fake_print_error_file(fake_setting_t * const setting, const f_status_t status, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fake_print_error_file_

/**
 * Print file related error message regarding a function failing in some way, setting fallback to F_false and returning result..
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param status
 *   The status to use.
 *   This is provided, ignoring setting.status, for thread-safety reasons.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_true is returned if the status code has no print message.
 *   F_false is returned on successful print of known errors.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_fake_print_error_file_fallback_
  extern f_status_t fake_print_error_file_fallback(fake_setting_t * const setting, const f_status_t status, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_fake_print_error_file_fallback_

/**
 * Print error message for when an operation fails.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation
 *   The identifier of the operation that failed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_failure_operation_
  extern f_status_t fake_print_error_failure_operation(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation);
#endif // _di_fake_print_error_failure_operation_

/**
 * Print error message for when an operation fails.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param script
 *   The name of the script that failed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_failure_script_
  extern f_status_t fake_print_error_failure_script(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t script);
#endif // _di_fake_print_error_failure_script_

/**
 * Print error message for when the parameter value is an empty string.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param symbol
 *   The symbol of the parameter.
 * @param name
 *   The name of the parameter.
 * @param value
 *   The value that is invalid.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_parameter_not_empty_
  extern f_status_t fake_print_error_parameter_not_empty(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fake_print_error_parameter_not_empty_

/**
 * Print error message for when the parameter value contains a non-word, non-minus, and non-plus character.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param symbol
 *   The symbol of the parameter.
 * @param name
 *   The name of the parameter.
 * @param value
 *   The value that is invalid.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_parameter_not_word_
  extern f_status_t fake_print_error_parameter_not_word(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value);
#endif // _di_fake_print_error_parameter_not_word_

/**
 * Print error message for when two designated operations cannot be used together.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation_1
 *   The name of the first operation that cannot be used.
 * @param operation_2
 *   The name of the second operation that cannot be used.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_error_parameter_operation_not_with_
  extern f_status_t fake_print_error_parameter_operation_not_with(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t operation_1, const f_string_static_t operation_2);
#endif // _di_fake_print_error_parameter_operation_not_with_

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_help_
  extern f_status_t fake_print_help(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_help_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_line_first_locked_
  extern f_status_t fake_print_line_first_locked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_first_locked_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_line_first_unlocked_
  extern f_status_t fake_print_line_first_unlocked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_first_unlocked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_line_last_locked_
  extern f_status_t fake_print_line_last_locked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_last_locked_

/**
 * Print last new line when the main is complete, unless verbosity says otherwise.
 *
 * This is generally the very last line printed in the program.
 *
 * This function neither locks nor unlocks the input stream.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_line_last_unlocked_
  extern f_status_t fake_print_line_last_unlocked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_last_unlocked_

/**
 * Print message for when all operates successfully complete.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_operation_all_complete_
  extern f_status_t fake_print_operation_all_complete(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_operation_all_complete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_h
