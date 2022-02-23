/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_print_h
#define _PRIVATE_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print any applicable substition and if there is non then print the given range at the given index.
 *
 * @param main
 *   The main program data.
 * @param iki_data
 *   The IKI data.
 * @param ranges
 *   The ranges containing the desired range to print as specified by index.
 * @param substitutions
 *   The substitions associated with the variable for the given range at the given index to use for potential printing.
 * @param index
 *   The index used to identify the desired range in variable, content, and ranges.
 * @param content_only
 *   Set to TRUE to only print the content when printing substituted text.
 *   Set to FALSE to print the entire variable when printing substituted text.
 */
#ifndef _di_iki_read_substitutions_print_
  extern void iki_read_substitutions_print(iki_read_main_t * const main, const f_iki_data_t iki_data, const f_string_ranges_t ranges, const iki_read_substitutions_t substitutions, const f_array_length_t index, const bool content_only) F_attribute_visibility_internal_d;
#endif // _di_iki_read_substitutions_print_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_print_h
