/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print data functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_print_data_h
#define _iki_read_print_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the given range at the given index.
 *
 * This expects the caller to have the output locked appropriately.
 *
 * This detects and prints any applicable substitution matching the vocabulary at the given index.
 * If there is no substitution, then this prints the given range at the given index.
 *
 * @param print
 *   The output structure to print to.
 *
 *   The setting.map_wraps is expected to be defined as a valid pointer to an array.
 *   The setting.map_replaces is expected to be defined as a valid pointer to an array.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param index
 *   The index used to identify the desired range in variable, content, and ranges.
 *
 * @see f_print_dynamic()
 * @see f_print_dynamic_partial()
 *
 * @see iki_read_identify_substitution()
 * @see iki_read_print_data_wrap_prepend()
 * @see iki_read_print_data_wrap_append()
 */
#ifndef _di_iki_read_print_data_
  extern void iki_read_print_data(fl_print_t * const print, const f_number_unsigned_t index) F_attribute_visibility_internal_d;
#endif // _di_iki_read_print_data_

/**
 * Print the append part of the wrap at the given index, if valid.
 *
 * This expects the caller to have the output locked appropriately.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param index
 *   The index within the setting->map_wraps array to print.
 *
 * @see f_print_dynamic()
 */
#ifndef _di_iki_read_print_data_wrap_append_
  extern void iki_read_print_data_wrap_append(fl_print_t * const print, const f_number_unsigned_t index) F_attribute_visibility_internal_d;
#endif // _di_iki_read_print_data_wrap_append_

/**
 * Print the prepend part of the wrap at the given index, if valid.
 *
 * This expects the caller to have the output locked appropriately.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param index
 *   The index within the setting->map_wraps array to print.
 *
 * @see f_print_dynamic()
 */
#ifndef _di_iki_read_print_data_wrap_prepend_
  extern void iki_read_print_data_wrap_prepend(fl_print_t * const print, const f_number_unsigned_t index) F_attribute_visibility_internal_d;
#endif // _di_iki_read_print_data_wrap_prepend_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_print_data_h
