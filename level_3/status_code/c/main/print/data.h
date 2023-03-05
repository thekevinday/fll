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
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param code
 *   The code to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_data_code_
  extern f_status_t status_code_print_data_code(status_code_setting_t * const setting, const fl_print_t print, const uint16_t code);
#endif // _di_status_code_print_data_code_

/**
 * Print generic context wrapped value.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param context
 *   The context string to wrap the variable with.
 * @param value
 *   The value string.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_status_code_print_data_context_value_
  extern f_status_t status_code_print_data_context_value(status_code_setting_t * const setting, const fl_print_t print, const f_color_set_t context, const f_string_static_t value);
#endif // _di_status_code_print_data_context_value_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_print_data_h
