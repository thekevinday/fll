/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_iki_read_h
#define _PRIVATE_iki_read_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine the range based on the --at parameter.
 *
 * If the --at parameter is not specified in the console arguments, then range is untouched.
 * The range.start will be greater than main->buffer.used if the --at range is not found before buffer end is reached.
 *
 * @param main
 *   The main program data.
 * @param file_name
 *   The name of the file being processed.
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
  extern f_status_t iki_read_process_at(iki_read_main_t * const main, const f_string_t file_name, f_string_range_t *range) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_at_

/**
 * Process a given buffer.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but nothing done.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_
  extern f_status_t iki_read_process_buffer(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_

/**
 * Process a given buffer, printing the given range.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
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
  extern f_status_t iki_read_process_buffer_ranges(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, f_string_range_t *buffer_range, iki_data_t *iki_data, f_string_ranges_t *ranges) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_ranges_

/**
 * Process a given buffer, printing the given buffer in whole mode based on the given ranges.
 *
 * The entire variable is replaced with the range from the associated ranges.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
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
  extern f_status_t iki_read_process_buffer_ranges_whole(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, const f_string_range_t buffer_range, iki_data_t *iki_data, f_string_ranges_t *ranges) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_ranges_whole_

/**
 * Process a given buffer, printing the total.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param iki_data
 *   The IKI data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_total_
  extern f_status_t iki_read_process_buffer_total(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, iki_data_t *iki_data) F_attribute_visibility_internal_d;
#endif // _di_iki_read_process_buffer_total_

/**
 * Process the arguments, associating substitions with a given vocabulary.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param vocabulary
 *   The ranges representing a vocabulary.
 * @param substitutionss
 *   An array of substitutionss with each index representing an index for in the respective vocabulary array.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_substitutions_identify_
  extern f_status_t iki_read_substitutions_identify(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, f_iki_vocabulary_t *vocabulary, iki_read_substitutions_t *substitutionss) F_attribute_visibility_internal_d;
#endif // _di_iki_read_substitutions_identify_

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
  extern void iki_read_substitutions_print(iki_read_main_t * const main, const iki_data_t iki_data, const f_string_ranges_t ranges, const iki_read_substitutions_t substitutions, const f_array_length_t index, const bool content_only) F_attribute_visibility_internal_d;
#endif // _di_iki_read_substitutions_print_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_iki_read_h
