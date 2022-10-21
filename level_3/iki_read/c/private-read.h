/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_read_h
#define _PRIVATE_read_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process the arguments, associating replacements and wraps with a given vocabulary.
 *
 * This does not handle substitutions because substitutions must match both name and value (Object and Content).
 * This function does not know the value (Content).
 *
 * @param setting
 *   The main program settings.
 * @param replaces
 *   A map to the last matching replacment or a value of setting->data.vocabulary.used if there is no matching replacement.
 *   Must be an array of length setting->data.vocabulary.used.
 * @param wraps
 *   A map to the last matching wrap or a value of setting->data.vocabulary.used if there is no matching wrap.
 *   Must be an array of length setting->data.vocabulary.used.
 *
 * @return
 *   The matching setting->data.vocabulary index or if no match then setting->data.vocabulary.used.
 */
#ifndef _di_iki_read_identify_alteration_
  extern void iki_read_identify_alteration(iki_read_setting_t * const setting) F_attribute_visibility_internal_d;
#endif // _di_iki_read_identify_alteration_

/**
 * Process the arguments, associating the last matching substitution with a given vocabulary name and value (Object and Content).
 *
 * This function expects appropriate sanity checks are performed on the substitutions array before calling.
 *
 * @param setting
 *   The main program settings.
 * @param name
 *   A range within setting->buffer representing the name (Object) to match.
 * @param value
 *   A range within setting->buffer representing the value (Content) to match.
 *
 * @return
 *   The matched substitution.
 *   The value of setting->substitute.used is returned on no match.
 */
#ifndef _di_iki_read_identify_substitution_
  extern f_array_length_t iki_read_identify_substitution(iki_read_setting_t * const setting, const f_string_range_t name, const f_string_range_t value) F_attribute_visibility_internal_d;
#endif // _di_iki_read_identify_substitution_

/**
 * Determine the range based on the --line parameter.
 *
 * If the --line parameter is not specified in the console arguments, then range is untouched.
 * The range.start will be greater than main->buffer.used if the --line is not found before buffer end is reached.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_true is returned if the range is processed.
 *     F_false is returned if the range is not processed.
 *     F_data_not if the range is processed, but the requested line is out of range.
 * @param range
 *   The range value to represent the --line values.
 */
#ifndef _di_iki_read_process_line_
  extern void iki_read_process_line(fll_program_data_t * const main, iki_read_setting_t * const setting, f_string_range_t *range) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_line_

/**
 * Process a given buffer.
 *
 * This will print error messages.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success, but nothing done.
 *
 *     F_interrupt (with error bit) on (exit) signal received.
 *
 *     Errors (with error bit) from: iki_read_process_at().
 *     Errors (with error bit) from: iki_read_process_buffer_ranges().
 *     Errors (with error bit) from: iki_read_process_buffer_ranges_whole().
 *
 * @see iki_read_process_at()
 * @see iki_read_process_buffer_ranges()
 * @see iki_read_process_buffer_ranges_whole()
 */
#ifndef _di_iki_read_process_buffer_
  extern void iki_read_process_buffer(fll_program_data_t * const main, iki_read_setting_t * const setting) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_

/**
 * Process a given buffer, printing the given range.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 * @param buffer_range
 *   The range within the buffer to process.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but nothing to print.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_ranges_
  extern void iki_read_process_buffer_ranges(fll_program_data_t * const main, iki_read_setting_t * const setting, f_string_range_t *buffer_range) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_ranges_

/**
 * Process a given buffer, printing the given buffer in whole mode based on the given ranges.
 *
 * The entire variable is replaced with the value from the associated ranges.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 * @param buffer_range
 *   The range within the buffer to process.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but nothing to print.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_ranges_whole_
  extern void iki_read_process_buffer_ranges_whole(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_string_range_t buffer_range) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_ranges_whole_

/**
 * Process a given buffer, printing the total.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_total_
  extern void iki_read_process_buffer_total(fll_program_data_t * const main, iki_read_setting_t * const setting) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_total_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_read_h
