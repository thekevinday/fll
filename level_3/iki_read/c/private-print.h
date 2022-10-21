/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_print_h
#define _PRIVATE_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the given range at the given index.
 *
 * This detects and prints any applicable substitution matching the vocabulary at the given index.
 * If there is no substitution, then this prints the given range at the given index.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   The setting.map_wraps is expected to be defined as a valid pointer to an array.
 *   The setting.map_replaces is expected to be defined as a valid pointer to an array.
 *
 *   This does not alter setting.status.
 * @param index
 *   The index used to identify the desired range in variable, content, and ranges.
 * @param content_only
 *   Set to TRUE to only print the value (Content) when printing.
 *   Set to FALSE to print the entire variable when printing.
 */
#ifndef _di_iki_read_print_
  extern void iki_read_print(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index, const bool content_only) F_attribute_visibility_internal_d;
#endif // _di_iki_read_print_

/**
 * Print the append part of the wrap at the given index, if valid.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param index
 *   The index within the setting->map_wraps array to print.
 */
#ifndef _di_iki_read_print_wrap_append_
  extern void iki_read_print_wrap_append(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_iki_read_print_wrap_append_

/**
 * Print the prepend part of the wrap at the given index, if valid.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param index
 *   The index within the setting->map_wraps array to print.
 */
#ifndef _di_iki_read_print_wrap_prepend_
  extern void iki_read_print_wrap_prepend(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_array_length_t index) F_attribute_visibility_internal_d;
#endif // _di_iki_read_print_wrap_prepend_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_print_h
