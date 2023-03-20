/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides print common functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_print_common_h
#define _fake_print_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print simple message.
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
 *   The message to print.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_common_simple_
  extern void fake_print_common_simple(fl_print_t * const print, const f_string_t message);
#endif // _di_fake_print_common_simple_

/**
 * Print simple verbose message with a value.
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
 *   The message to print.
 * @param variable
 *   The string representing the variable.
 *
 * @see fll_print_format()
 */
#ifndef _di_fake_print_common_simple_variable_
  extern void fake_print_common_simple_variable(fl_print_t * const print, const f_string_t message, const f_string_static_t variable);
#endif // _di_fake_print_common_simple_variable_

/**
 * Print wrapped message with a value.
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
 * @see fll_print_format()
 */
#ifndef _di_fake_print_common_wrapped_variable_
  extern void fake_print_common_wrapped_variable(fl_print_t * const print, const f_string_t before, const f_string_static_t variable, const f_string_t after);
#endif // _di_fake_print_common_wrapped_variable_

/**
 * Print a wrapped message with a before string, a middle strng, an after string, and two string variables.
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
#ifndef _di_fake_print_common_wrapped_variables_
  extern void fake_print_common_wrapped_variables(fl_print_t * const print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after);
#endif // _di_fake_print_common_wrapped_variables_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_common_h
