/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides print context functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_print_context_h
#define _fake_print_context_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a simple message with context set to important but without prefix and suffix.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param message
 *   The string to print.
 *
 * @see fake_print_context_simple()
 */
#ifndef _di_fake_print_context_important_simple_
  extern void fake_print_context_important_simple(fl_print_t * const print, const f_string_t message);
#endif // _di_fake_print_context_important_simple_

/**
 * Print a variable context message with a before string, an after string, and a string variable with context set to important but without prefix and suffix.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
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
 */
#ifndef _di_fake_print_context_important_simple_variable_
  extern void fake_print_context_important_simple_variable(fl_print_t * const print, const f_string_t before, const f_string_static_t variable, const f_string_t after);
#endif // _di_fake_print_context_important_simple_variable_

/**
 * Print a simple context message with prefix and a single string message.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param message
 *   The string to print.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_context_simple_
  extern void fake_print_context_simple(fl_print_t * const print, const f_string_t message);
#endif // _di_fake_print_context_simple_

/**
 * Print a variable context message with a before string, an after string, and a string variable.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
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
 */
#ifndef _di_fake_print_context_simple_variable_
  extern void fake_print_context_simple_variable(fl_print_t * const print, const f_string_t before, const f_string_static_t variable, const f_string_t after);
#endif // _di_fake_print_context_simple_variable_

/**
 * Print a variable context message with a before string, an after string, and an unsigned number variable.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
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
 */
#ifndef _di_fake_print_context_wrapped_number_
  extern void fake_print_context_wrapped_number(fl_print_t * const print, const f_string_t before, const f_number_unsigned_t number, const f_string_t after);
#endif // _di_fake_print_context_wrapped_number_

/**
 * Print a parameter context message with a before string, an after string, a string symbol, and a parameter name.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
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
 */
#ifndef _di_fake_print_context_wrapped_parameter_
  extern void fake_print_context_wrapped_parameter(fl_print_t * const print, const f_string_t before, const f_string_static_t symbol, const f_string_static_t name, const f_string_t after);
#endif // _di_fake_print_context_wrapped_parameter_

/**
 * Print a parameter context message with a before string, a middle string, an after string, a string symbol, a parameter name, and the parameter value.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param before
 *   The string being printed before the variable.
 *   Likely should have a space added at the end of the string.
 *   Set to NULL to disable.
 * @param symbol
 *   The string representing the symbol for the parameter.
 *   Set to f_string_empty_s to disable.
 * @param name
 *   The string representing the parameter name.
 * @param between
 *   The string being printed after the parameter name and before the parameter value.
 * @param value
 *   The value associated with the given parameter name.
 * @param after
 *   The string being printed after the variable.
 *   Likely should have a space added at the start of the string.
 *   Set to NULL to disable.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_context_wrapped_parameter_value_
  extern void fake_print_context_wrapped_parameter_value(fl_print_t * const print, const f_string_t before, const f_string_static_t symbol, const f_string_static_t name, const f_string_t between, const f_string_static_t value, const f_string_t after);
#endif // _di_fake_print_context_wrapped_parameter_value_

/**
 * Print a parameter context message with a there parameters, with symbols, and wrapping strings.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
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
 */
#ifndef _di_fake_print_context_wrapped_parameter_
  extern void fake_print_context_wrapped_parameters(fl_print_t * const print, const f_string_t before, const f_string_static_t symbol_1, const f_string_static_t name_1, const f_string_t between_1, const f_string_static_t symbol_2, const f_string_static_t name_2, const f_string_t between_2, const f_string_static_t symbol_3, const f_string_static_t name_3, const f_string_t after);
#endif // _di_fake_print_context_wrapped_parameter_

/**
 * Print a wrapped context message with a before string, an after string, and a string variable.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
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
 */
#ifndef _di_fake_print_context_wrapped_variable_
  extern void fake_print_context_wrapped_variable(fl_print_t * const print, const f_string_t before, const f_string_static_t variable, const f_string_t after);
#endif // _di_fake_print_context_wrapped_variable_

/**
 * Print a wrapped context message with a before string, a middle strng, an after string, and two string variables.
 *
 * This is primarily used by numerous print functions to reduce code.
 * This is not used for any print functions that has complex format structures.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
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
#ifndef _di_fake_print_context_wrapped_variables_
  extern void fake_print_context_wrapped_variables(fl_print_t * const print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after);
#endif // _di_fake_print_context_wrapped_variables_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_context_h