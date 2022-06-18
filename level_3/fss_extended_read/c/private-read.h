/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_read_h
#define _PRIVATE_read_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine if the given depth is to be delimited or not for Content.
 *
 * @param depth
 *   The depth to check.
 * @param data
 *   The program data.
 *
 * @return
 *   F_true if to apply delimits.
 *   F_false if to not apply delimits.
 */
#ifndef _di_fss_extended_read_delimit_content_is_
  extern f_status_t fss_extended_read_delimit_content_is(const f_array_length_t depth, fss_extended_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_delimit_content_is_

/**
 * Determine if the given depth is to be delimited or not for an Object.
 *
 * @param depth
 *   The depth to check.
 * @param data
 *   The program data.
 *
 * @return
 *   F_true if to apply delimits.
 *   F_false if to not apply delimits.
 */
#ifndef _di_fss_extended_read_delimit_object_is_
  extern f_status_t fss_extended_read_delimit_object_is(const f_array_length_t depth, fss_extended_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_delimit_object_is_

/**
 * Process the parameters, parsing out and handling the depth and depth related parameters.
 *
 * Will handle depth-sensitive parameter conflicts, such as --name being used with --at (which is not allowed).
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *   Errors (with error bit) from: fl_string_dynamic_rip().
 *
 *   Errors (with error bit) from: fss_extended_read_depths_resize().
 *
 * @see f_string_append()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see fl_string_dynamic_rip()
 *
 * @see fss_extended_read_depths_resize()
 */
#ifndef _di_fss_extended_read_depth_process_
  extern f_status_t fss_extended_read_depth_process(fll_program_data_t * const main, fss_extended_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_depth_process_

/**
 * Get the name of the file the given position represents within the buffer.
 *
 * @param at
 *   The position within the buffer.
 * @param files
 *   The representation of files and their respective ranges within the buffer.
 *
 * @return
 *   A string with the name when found.
 *   NULL is returned if the range represents the STDIN pipe.
 *
 *   On failure to identify, an empty string is returned.
 */
#ifndef _di_fss_extended_read_file_identify_
  extern f_string_static_t fss_extended_read_file_identify(const f_array_length_t at, const fss_extended_read_files_t files) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_file_identify_

/**
 * Process the buffer, loading the FSS data.
 *
 * This will print an error message on error.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_data_not_stop (with warning bit) on no valid FSS data found and reached stopping point.
 *   F_data_not_eos (with warning bit) on no valid FSS data found and reached end of string.
 *
 *   Errors (with error bit) from: fll_fss_extended_read()
 *
 * @see fll_fss_extended_read()
 *
 * @see fss_extended_read_process_option()
 */
#ifndef _di_fss_extended_read_load_
  extern f_status_t fss_extended_read_load(fll_program_data_t * const main, fss_extended_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_load_

/**
 * Load a given number parameter.
 *
 * This will print an error message on error.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 * @param parameter
 *   An ID representing the parameter.
 * @param name
 *   The parameter name to print on error.
 * @param number
 *   The location to store the loaded number.
 *
 * @return
 *   F_true on success and the parameter was found (and is valid).
 *   F_false on success and the parameter was not found.
 *
 *   Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 *
 * @see fss_extended_read_depths_resize()
 */
#ifndef _di_fss_extended_read_load_number_
  extern f_status_t fss_extended_read_load_number(fll_program_data_t * const main, fss_extended_read_data_t * const data, const f_array_length_t parameter, const f_string_static_t name, f_number_unsigned_t *number) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_load_number_

/**
 * Perform the extended read processing on the buffer.
 *
 * This will print an error message on error.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: fss_extended_read_load()
 *   Errors (with error bit) from: fss_extended_read_process_option()
 *
 * @see fss_extended_read_load()
 * @see fss_extended_read_process_option()
 */
#ifndef _di_fss_extended_read_process_
  extern f_status_t fss_extended_read_process(fll_program_data_t * const main, fss_extended_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_

/**
 * Process based on at parameter.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 * @param names
 *   An array of booleans representing whether or not some Object name is to be used.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_extended_read_process_at_
  extern f_status_t fss_extended_read_process_at(fll_program_data_t * const main, fss_extended_read_data_t * const data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_at_

/**
 * Process based on columns parameter.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 * @param names
 *   An array of booleans representing whether or not some Object name is to be used.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_extended_read_process_columns_
  extern f_status_t fss_extended_read_process_columns(fll_program_data_t * const main, fss_extended_read_data_t * const data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_columns_

/**
 * Process based on line parameter.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 * @param names
 *   An array of booleans representing whether or not some Object name is to be used.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_extended_read_process_line_
  extern f_status_t fss_extended_read_process_line(fll_program_data_t * const main, fss_extended_read_data_t * const data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_line_

/**
 * Process the Objects in the buffer, determining if the Object name is to be used or not.
 *
 * How an Object name is determined to be used or not is dependent on several parameters, such as --name, --depth, --at, and --line.
 *
 * @param main
 *   The main program data.
 * @param names
 *   An array of booleans representing whether or not some Object name is to be used.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_extended_read_process_name_
  extern f_status_t fss_extended_read_process_name(fss_extended_read_data_t * const data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_name_

/**
 * Process the parameters, populating the option property of the program data.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: fss_extended_read_load_setting()
 *
 * @see fll_fss_extended_read()
 *
 * @see fss_extended_read_load_setting()
 */
#ifndef _di_fss_extended_read_process_option_
  extern f_status_t fss_extended_read_process_option(fll_program_data_t * const main, fss_extended_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_option_

/**
 * Process based on total parameter.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 * @param names
 *   An array of booleans representing whether or not some Object name is to be used.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_extended_read_process_total_
  extern f_status_t fss_extended_read_process_total(fll_program_data_t * const main, fss_extended_read_data_t * const data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_total_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_read_h
