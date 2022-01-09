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
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: fl_string_rip().
 *   Errors (with error bit) from: fl_conversion_string_to_number_unsigned().
 *
 *   Errors (with error bit) from: fss_extended_read_depths_resize().
 *
 * @see f_string_append()
 * @see fl_string_rip()
 * @see fl_conversion_string_to_number_unsigned()
 *
 * @see fss_extended_read_depths_resize()
 */
#ifndef _di_fss_extended_read_depth_process_
  extern f_status_t fss_extended_read_depth_process(fss_extended_read_main_t * const main, const f_console_arguments_t *arguments, fss_extended_read_data_t *data) F_attribute_visibility_internal_d;
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
  extern f_string_t fss_extended_read_file_identify(const f_array_length_t at, const fss_extended_read_files_t files) F_attribute_visibility_internal_d;
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
  extern f_status_t fss_extended_read_load(fss_extended_read_main_t * const main, fss_extended_read_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_load_

/**
 * Load a given number parameter.
 *
 * This will print an error message on error.
 *
 * @param main
 *   The main program data.
 * @param parameter
 *   An ID representing the parameter.
 * @param name
 *   The parameter name to print on error.
 * @param arguments
 *   The console arguments passed to the program.
 * @param number
 *   The location to store the loaded number.
 *
 * @return
 *   F_true on success and the parameter was found (and is valid).
 *   F_false on success and the parameter was not found.
 *
 *   Errors (with error bit) from: fl_conversion_string_to_number_unsigned().
 *
 * @see fl_conversion_string_to_number_unsigned()
 *
 * @see fss_extended_read_depths_resize()
 */
#ifndef _di_fss_extended_read_load_number_
  extern f_status_t fss_extended_read_load_number(fss_extended_read_main_t * const main, const f_array_length_t parameter, const f_string_t name, const f_console_arguments_t *arguments, f_number_unsigned_t *number) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_load_number_

/**
 * Perform the extended read processing on the buffer.
 *
 * This will print an error message on error.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
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
  extern f_status_t fss_extended_read_process(fss_extended_read_main_t * const main, const f_console_arguments_t *arguments, fss_extended_read_data_t *data) F_attribute_visibility_internal_d;
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
  extern f_status_t fss_extended_read_process_at(fss_extended_read_main_t * const main, fss_extended_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
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
  extern f_status_t fss_extended_read_process_columns(fss_extended_read_main_t * const main, fss_extended_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
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
  extern f_status_t fss_extended_read_process_line(fss_extended_read_main_t * const main, fss_extended_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
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
  extern f_status_t fss_extended_read_process_name(fss_extended_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_name_

/**
 * Process the parameters, populating the option property of the program data.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
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
  extern f_status_t fss_extended_read_process_option(fss_extended_read_main_t * const main, const f_console_arguments_t *arguments, fss_extended_read_data_t *data) F_attribute_visibility_internal_d;
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
  extern f_status_t fss_extended_read_process_total(fss_extended_read_main_t * const main, fss_extended_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_process_total_

/**
 * Determine if the given depth is to be delimited or not.
 *
 * @param main
 *   The main program data.
 * @param depth
 *   The depth to check.
 *
 * @return
 *   F_true if delimited.
 *   F_false if not delimited.
 */
#ifndef _di_fss_extended_read_is_delimited_at_depth_
  extern f_status_t fss_extended_read_is_delimited_at_depth(fss_extended_read_main_t * const main, const f_array_length_t depth) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_is_delimited_at_depth_

/**
 * Process a given file.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param depths
 *   The processed depth parameters.
 * @param objects_delimits
 *   An array of delimits detected during processing, for top-level objects.
 * @param contents_delimits
 *   An array of delimits detected during processing, for contents.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_extended_read_main_preprocess_depth()
 */
#ifndef _di_fss_extended_read_main_process_file_
  extern f_status_t fss_extended_read_main_process_file(fss_extended_read_main_t * const main, const f_console_arguments_t arguments, const f_string_t file_name, const fss_extended_read_depths_t depths, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_main_process_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_read_h
