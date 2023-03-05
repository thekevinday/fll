/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_print_h
#define _fake_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a message about generating skeleton.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_generating_skeleton_
  extern f_status_t fake_print_generating_skeleton(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_generating_skeleton_

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic_raw()
 * @see fl_print_format()
 * @see fll_program_print_help_header()
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_option_other()
 * @see fll_program_print_help_option_standard()
 * @see fll_program_print_help_usage()
 */
#ifndef _di_fake_print_help_
  extern f_status_t fake_print_help(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_help_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * Once the first line is processed (printed or not), then this will print new lines normally.
 *
 * This function locks and then unlocks the input stream when printing.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_fake_print_line_first_
  extern f_status_t fake_print_line_first(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_first_

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
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_dynamic_raw()
 */
#ifndef _di_fake_print_line_last_
  extern f_status_t fake_print_line_last(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_last_

/**
 * Print simple message.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param message
 *   The message to print.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_simple_
  extern void fake_print_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t message);
#endif // _di_fake_print_simple_

/**
 * Print simple verbose message with a value.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param message
 *   The message to print.
 * @param variable
 *   The string representing the variable.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_simple_variable_
  extern void fake_print_simple_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t message, const f_string_static_t variable);
#endif // _di_fake_print_simple_variable_

/**
 * Print wrapped message with a value.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param before
 *   The string being printed before the variable.
 *   Likely should have a space added at the end of the string.
 *   Set to NULL to disable.
 * @param variable
 *   The string representing the variable.
 * @param after
 *   The string being printed after the variable.
 *   Likely should have a space added at the start of the string.
 *   Set to NULL to disable.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_wrapped_variable_
  extern void fake_print_wrapped_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after);
#endif // _di_fake_print_wrapped_variable_

/**
 * Print a wrapped message with a before string, a middle strng, an after string, and two string variables.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param before
 *   The string being printed before the variable.
 *   Likely should have a space added at the end of the string.
 * @param first
 *   The string representing the first variable.
 * @param between
 *   The string being printed before the variable.
 *   Likely should have a space added at the start and end of the string.
 * @param second
 *   The string representing the second variable.
 * @param after
 *   The string being printed after the variable.
 *   Likely should have a space added at the start of the string.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_wrapped_variables_
  extern void fake_print_wrapped_variables(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after);
#endif // _di_fake_print_wrapped_variables_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_h
