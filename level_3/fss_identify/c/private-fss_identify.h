/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_identify_h
#define _PRIVATE_fss_identify_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load a pipe or a file 1 block at a time untul a newline is found.
 *
 * @param main
 *   The main data.
 * @param file
 *   The file or pipe to load from.
 * @param name
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
  extern f_status_t fss_identify_load_line(const fss_identify_main_t main, const f_file_t file, const f_string_t name, f_string_static_t *buffer, f_string_range_t *range) f_attribute_visibility_internal;
#endif // _di_fss_identify_load_line_

/**
 * Print the given FLL Identifier.
 *
 * @param main
 *   The main data.
 * @param id
 *   The Identifier to print.
 */
#ifndef _di_fss_identify_print_
  extern void fss_identify_print(const fss_identify_main_t main, f_fll_id_t id) f_attribute_visibility_internal;
#endif // _di_fss_identify_print_

/**
 * Process a given pipe or file.
 *
 * @param main
 *   The main data.
 * @param name
 *   The name of the file.
 *   Set to NULL to designate that this is a pipe.
 * @param buffer
 *   The string representing the file to process.
 * @param range
 *   The range representing the line in the buffer.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: fll_fss_identify().
 *
 * @see fll_fss_identify()
 */
#ifndef _di_fss_identify_process_
  extern f_status_t fss_identify_process(const fss_identify_main_t main, const f_string_t name, const f_string_static_t buffer, f_string_range_t *range, fss_identify_data_t *data) f_attribute_visibility_internal;
#endif // _di_fss_identify_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_identify_h
