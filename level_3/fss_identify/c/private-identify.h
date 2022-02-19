/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_identify_h
#define _PRIVATE_identify_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load a pipe or a file 1 block at a time untul a newline is found.
 *
 * @param main
 *   The main program data.
 * @param file
 *   The file or pipe to load from.
 * @param file_name
 *   The name of the file.
 *   Set to NULL to designate that this is a pipe.
 * @param buffer
 *   The string representing the file to process.
 * @param range
 *   The range representing the line in the buffer.
 *
 * @return
 *   Status from: f_file_stream_read_block().
 *
 *   Errors (with error bit) from: f_file_stream_read_block().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_file_stream_read_block()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_fss_identify_load_line_
  extern f_status_t fss_identify_load_line(fll_program_data_t * const main, const f_file_t file, const f_string_static_t file_name, f_string_static_t *buffer, f_string_range_t *range) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_load_line_

/**
 * Process a given pipe or file.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 * @param file_name
 *   The name of the file.
 *   Set to NULL to designate that this is a pipe.
 * @param buffer
 *   The string representing the file to process.
 * @param range
 *   The range representing the line in the buffer.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: fll_fss_identify().
 *
 * @see fll_fss_identify()
 */
#ifndef _di_fss_identify_process_
  extern f_status_t fss_identify_process(fll_program_data_t * const main, fss_identify_data_t * const data, const f_string_static_t file_name, const f_string_static_t buffer, f_string_range_t *range) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_process_

/**
 * Determine if the given FLL ID matches the requested range.
 *
 * @param data
 *   The program data.
 * @param id
 *   The FLL ID to compare against.
 * @param mode
 *   A mode specifying how to compare.
 *   0 = Compare against just the ID Name (such as "fss" in "fss-0001").
 *   1 = Compare against just the ID Type (such as "0001" in "fss-0001").
 *   2 = Compare against the full name (such as "fss-0001" in "fss-0001").
 *
 * @return
 *   F_true on match.
 *   F_false on no match.
 *
 *   Errors (with error bit) from fl_conversion_string_to_hexidecimal_unsigned().
 *   Errors (with error bit) from fl_string_dynamic_compare_string().
 *
 * @see fl_conversion_string_to_hexidecimal_unsigned()
 * @see fl_string_dynamic_compare_string()
 */
#ifndef _di_fss_identify_process_name_compare_
  f_status_t fss_identify_process_name_compare(fss_identify_data_t * const data, const f_fll_id_t id, const uint8_t mode) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_process_name_compare_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_identify_h
