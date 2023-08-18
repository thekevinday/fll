/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print data functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_print_data_h
#define _status_code_print_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic code.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param code
 *   The code to print.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_data_code_
  extern f_status_t status_code_print_data_code(fl_print_t * const print, const uint16_t code);
#endif // _di_status_code_print_data_code_

/**
 * Print generic context wrapped value.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param context
 *   The context string to wrap the variable with.
 * @param value
 *   The value string.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_data_context_value_
  extern f_status_t status_code_print_data_context_value(fl_print_t * const print, const f_color_set_t context, const f_string_static_t value);
#endif // _di_status_code_print_data_context_value_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_print_data_h
