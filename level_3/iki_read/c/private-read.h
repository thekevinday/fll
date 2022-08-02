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
 * Determine the range based on the --at parameter.
 *
 * If the --at parameter is not specified in the console arguments, then range is untouched.
 * The range.start will be greater than main->buffer.used if the --at range is not found before buffer end is reached.
 *
 * @param data
 *   The program data.
 * @param range
 *   The range value to represent the --at values.
 *
 * @return
 *   F_true is returned if the range is processed.
 *   F_false is returned if the range is not processed.
 *   F_data_not if the range is processed, but the requested line is out of range.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_at_
  extern f_status_t iki_read_process_at(iki_read_data_t * const data, f_string_range_t *range) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_at_

/**
 * Process a given buffer.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but nothing done.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_
  extern f_status_t iki_read_process_buffer(iki_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_

/**
 * Process a given buffer, printing the given range.
 *
 * @param data
 *   The program data.
 * @param buffer_range
 *   The range within the buffer to process.
 * @param iki_data
 *   The IKI data.
 * @param ranges
 *   The ranges to print when matched.
 *   Should be one of: variable, vocabulary, or content.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but nothing to print.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_ranges_
  extern f_status_t iki_read_process_buffer_ranges(iki_read_data_t * const data, f_string_range_t *buffer_range, f_iki_data_t *iki_data, f_string_ranges_t *ranges) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_ranges_

/**
 * Process a given buffer, printing the given buffer in whole mode based on the given ranges.
 *
 * The entire variable is replaced with the range from the associated ranges.
 *
 * @param data
 *   The program data.
 * @param buffer_range
 *   The range within the buffer to process.
 * @param iki_data
 *   The IKI data.
 * @param ranges
 *   The ranges to print when matched.
 *   Should be one of: variable, vocabulary, or content.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but nothing to print.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_ranges_whole_
  extern f_status_t iki_read_process_buffer_ranges_whole(iki_read_data_t * const data, const f_string_range_t buffer_range, f_iki_data_t *iki_data, f_string_ranges_t *ranges) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_ranges_whole_

/**
 * Process a given buffer, printing the total.
 *
 * @param data
 *   The program data.
 * @param iki_data
 *   The IKI data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_total_
  extern f_status_t iki_read_process_buffer_total(iki_read_data_t * const data, f_iki_data_t *iki_data) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_total_

/**
 * Process the arguments, associating replacement with a given vocabulary.
 *
 * The replace property is not used by the --replace option parameter.
 * The replace property is instead used to designate whether or not a match is found.
 * The replace.string property should, therefore, never be accessed because this would likely result in an invalid read.
 *
 * When multiple replacements are found, only use the last specified replacement (right-most).
 *
 * @param data
 *   The program data.
 * @param vocabulary
 *   The ranges representing a vocabulary.
 * @param replacements
 *   An array of replacements representing an index in the respective vocabulary array.
 *   This sets replacements[].replace.used to F_false when there are no matches and F_true when there are matches.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_replacements_identify_
  extern f_status_t iki_read_replacements_identify(iki_read_data_t * const data, f_iki_vocabulary_t *vocabulary, iki_read_substitution_t *replacements) F_attribute_visibility_internal_d;
#endif // _di_iki_read_replacements_identify_

/**
 * Process the arguments, associating substitutions with a given vocabulary.
 *
 * @param data
 *   The program data.
 * @param vocabulary
 *   The ranges representing a vocabulary.
 * @param substitutionss
 *   An array of substitutions with each index representing an index for in the respective vocabulary array.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_substitutions_identify_
  extern f_status_t iki_read_substitutions_identify(iki_read_data_t * const data, f_iki_vocabulary_t *vocabulary, iki_read_substitutions_t *substitutionss) F_attribute_visibility_internal_d;
#endif // _di_iki_read_substitutions_identify_

/**
 * Process the arguments, associating wraps with a given vocabulary.
 *
 * @param data
 *   The program data.
 * @param vocabulary
 *   The ranges representing a vocabulary.
 * @param wraps
 *   An array of substitutions with each index representing an index for in the respective vocabulary array.
 *   The replacements[].replace is used to represent the "before".
 *   The replacements[].with is used to represent the "after".
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_wraps_identify_
  extern f_status_t iki_read_wraps_identify(iki_read_data_t * const data, f_iki_vocabulary_t *vocabulary, iki_read_substitution_t *wraps) F_attribute_visibility_internal_d;
#endif // _di_iki_read_wraps_identify_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_read_h
