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
 * Print a simple context message with prefix and a single string message.
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
 *   The string to print.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_line_first_unlocked()
 */
#ifndef _di_fake_print_context_simple_
  extern void fake_print_context_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t message);
#endif // _di_fake_print_context_simple_

/**
 * Print a variable context message with a before string, an after string, and a string variable.
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
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_line_first_unlocked()
 */
#ifndef _di_fake_print_context_simple_variable_
  extern void fake_print_context_simple_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after);
#endif // _di_fake_print_context_simple_variable_

/**
 * Print a variable context message with a before string, an after string, and an unsigned number variable.
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
 * @param number
 *   The number representing the variable.
 * @param after
 *   The string being printed after the variable.
 *   Likely should have a space added at the start of the string.
 *   Set to NULL to disable.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_line_first_unlocked()
 */
#ifndef _di_fake_print_context_wrapped_number_
  extern void fake_print_context_wrapped_number(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_number_unsigned_t number, const f_string_t after);
#endif // _di_fake_print_context_wrapped_number_

/**
 * Print a parameter context message with a before string, an after string, a string symbol, and a parameter name.
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
 * @param symbol
 *   The string representing the symbol for the parameter.
 *   Set to f_string_empty_s to disable.
 * @param name
 *   The string representing the parameter name.
 * @param after
 *   The string being printed after the variable.
 *   Likely should have a space added at the start of the string.
 *   Set to NULL to disable.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_line_first_unlocked()
 */
#ifndef _di_fake_print_context_wrapped_parameter_
  extern void fake_print_context_wrapped_parameter(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t symbol, const f_string_static_t name, const f_string_t after);
#endif // _di_fake_print_context_wrapped_parameter_

/**
 * Print a parameter context message with a there parameters, with symbols, and wrapping strings.
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
 * @param symbol_1
 *   The string representing the symbol for the parameter.
 *   Set to f_string_empty_s to disable.
 * @param name_1
 *   The string representing the parameter name.
 * @param middle_1
 *   The string being printed before the variable.
 *   Likely should have a space added at the end of the string.
 *   Set to NULL to disable.
 * @param symbol_2
 *   The string representing the symbol for the parameter.
 *   Set to f_string_empty_s to disable.
 * @param name_2
 *   The string representing the parameter name.
 * @param middle_2
 *   The string being printed before the variable.
 *   Likely should have a space added at the end of the string.
 *   Set to NULL to disable.
 * @param symbol_3
 *   The string representing the symbol for the parameter.
 *   Set to f_string_empty_s to disable.
 * @param name_3
 *   The string representing the parameter name.
 * @param after
 *   The string being printed after the variable.
 *   Likely should have a space added at the start of the string.
 *   Set to NULL to disable.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_line_first_unlocked()
 */
#ifndef _di_fake_print_context_wrapped_parameter_
  extern void fake_print_context_wrapped_parameters(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t symbol_1, const f_string_static_t name_1, const f_string_t between_1, const f_string_static_t symbol_2, const f_string_static_t name_2, const f_string_t between_2, const f_string_static_t symbol_3, const f_string_static_t name_3, const f_string_t after);
#endif // _di_fake_print_context_wrapped_parameter_

/**
 * Print a wrapped context message with a before string, an after string, and a string variable.
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
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 *
 * @see fake_print_line_first_unlocked()
 */
#ifndef _di_fake_print_context_wrapped_variable_
  extern void fake_print_context_wrapped_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after);
#endif // _di_fake_print_context_wrapped_variable_

/**
 * Print a wrapped context message with a before string, a middle strng, an after string, and two string variables.
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
 *
 * @see fake_print_line_first_unlocked()
 */
#ifndef _di_fake_print_context_wrapped_variables_
  extern void fake_print_context_wrapped_variables(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after);
#endif // _di_fake_print_context_wrapped_variables_

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
 *
 * @see fake_print_line_first_unlocked()
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
 */
#ifndef _di_fake_print_help_
  extern f_status_t fake_print_help(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_help_

/**
 * Print a simple message with context set to important but without prefix and suffix.
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
 *   The string to print.
 *
 * @see fake_print_context_simple()
 */
#ifndef _di_fake_print_important_simple_
  extern void fake_print_important_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t message);
#endif // _di_fake_print_important_simple_

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
 */
#ifndef _di_fake_print_line_first_locked_
  extern f_status_t fake_print_line_first_locked(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_line_first_locked_

/**
 * Print first new line, unless verbosity says otherwise.
 *
 * This is generally either the first line in the program or the first line printed before an error message.
 *
 * Once the first line is processed (printed or not), then this will print new lines normally.
 *
 * This function neither locks nor unlocks the input stream.
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
 *   This does not alter setting.state.status.
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
 *   This does not alter setting.state.status.
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
 *   This does not alter setting.state.status.
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

/**
 * Print message for when the operation is cancelled.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation
 *   The identifier of the operation that failed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_print_operation_cancelled_
  extern f_status_t fake_print_operation_cancelled(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation);
#endif // _di_fake_print_operation_cancelled_

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
 *
 * @see fake_print_line_first_unlocked()
 */
#ifndef _di_fake_print_wrapped_variables_
  extern void fake_print_wrapped_variables(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after);
#endif // _di_fake_print_wrapped_variables_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_h
