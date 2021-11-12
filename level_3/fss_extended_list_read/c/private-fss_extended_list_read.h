/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_extended_list_read_h
#define _PRIVATE_fss_extended_list_read_h

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
#ifndef _di_fss_extended_list_read_delimit_content_is_
  extern f_status_t fss_extended_list_read_delimit_content_is(const f_array_length_t depth, fss_extended_list_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_delimit_content_is_

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
#ifndef _di_fss_extended_list_read_delimit_object_is_
  extern f_status_t fss_extended_list_read_delimit_object_is(const f_array_length_t depth, fss_extended_list_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_delimit_object_is_

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
 *   Errors (with error bit) from: fss_extended_list_read_depths_resize().
 *
 * @see f_string_append()
 * @see fl_string_rip()
 * @see fl_conversion_string_to_number_unsigned()
 *
 * @see fss_extended_list_read_depths_resize()
 */
#ifndef _di_fss_extended_list_read_depth_process_
  extern f_status_t fss_extended_list_read_depth_process(fss_extended_list_read_main_t * const main, const f_console_arguments_t *arguments, fss_extended_list_read_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_depth_process_

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
#ifndef _di_fss_extended_list_read_file_identify_
  extern f_string_t fss_extended_list_read_file_identify(const f_array_length_t at, const fss_extended_list_read_files_t files) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_file_identify_

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
 *   Errors (with error bit) from: fll_fss_extended_list_read()
 *
 * @see fll_fss_extended_list_read()
 *
 * @see fss_extended_list_read_process_option()
 */
#ifndef _di_fss_extended_list_read_load_
  extern f_status_t fss_extended_list_read_load(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_load_

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
 * @see fss_extended_list_read_depths_resize()
 */
#ifndef _di_fss_extended_list_read_load_number_
  extern f_status_t fss_extended_list_read_load_number(fss_extended_list_read_main_t * const main, const f_array_length_t parameter, const f_string_t name, const f_console_arguments_t *arguments, f_number_unsigned_t *number) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_load_number_

/**
 * Print the Object and Content at the given position.
 *
 * Only what is requested to print (Object, Content, both, or neither) will be printed, if there is something to print.
 *
 * @param main
 *   The main program data.
 * @param at
 *   The index in the Objects and Contents to print.
 * @param delimits_object
 *   The delimits to be applied to an Object.
 * @param delimits_content
 *   The delimits to be applied to Content.
 * @param data
 *   The program data.
 */
#ifndef _di_fss_extended_list_read_print_at_
  extern void fss_extended_list_read_print_at(fss_extended_list_read_main_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_extended_list_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_print_at_

/**
 * Explicitly print the Object at the given position.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 * @param at
 *   The index in the Objects and Contents to print.
 * @param delimits_object
 *   The delimits to be applied to an Object.
 */
#ifndef _di_fss_extended_list_read_print_at_object_
  extern void fss_extended_list_read_print_at_object(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t * const data, const f_array_length_t at, const f_fss_delimits_t delimits_object) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_print_at_object_

/**
 * Print the ignore character for Content.
 *
 * This is only used in pipe output mode.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_extended_list_read_print_content_ignore_
  extern void fss_extended_list_read_print_content_ignore(fss_extended_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_print_content_ignore_

/**
 * Print the end of an Object (which is essentially the start of Content).
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 */
#ifndef _di_fss_extended_list_read_print_object_end_
  extern void fss_extended_list_read_print_object_end(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_print_object_end_

/**
 * Print the number one and a newline.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_extended_list_read_print_one_
  extern void fss_extended_list_read_print_one(fss_extended_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_print_one_

/**
 * Print the end of an Object/Content set.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 */
#ifndef _di_fss_extended_list_read_print_set_end_
  extern void fss_extended_list_read_print_set_end(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_print_set_end_

/**
 * Print the number zero and a newline.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_extended_list_read_print_zero_
  extern void fss_extended_list_read_print_zero(fss_extended_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_print_zero_

/**
 * Perform the basic read processing on the buffer.
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
 *   Errors (with error bit) from: fss_extended_list_read_load()
 *   Errors (with error bit) from: fss_extended_list_read_process_option()
 *
 * @see fss_extended_list_read_load()
 * @see fss_extended_list_read_process_option()
 */
#ifndef _di_fss_extended_list_read_process_
  extern f_status_t fss_extended_list_read_process(fss_extended_list_read_main_t * const main, const f_console_arguments_t *arguments, fss_extended_list_read_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_process_

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
 *
 * @see fss_extended_list_read_process_at_line()
 */
#ifndef _di_fss_extended_list_read_process_at_
  extern f_status_t fss_extended_list_read_process_at(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_process_at_

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
#ifndef _di_fss_extended_list_read_process_columns_
  extern f_status_t fss_extended_list_read_process_columns(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_process_columns_

/**
 * Process based on at parameter for some line.
 *
 * @param main
 *   The main program data.
 * @param delimits_object
 *   The delimits to be applied to an Object.
 * @param delimits_content
 *   The delimits to be applied to Content.
 * @param data
 *   The program data.
 * @param line
 *   The current line being processed.
 *   This will be incremented as necessary.
 *
 * @return
 *   F_none on success but no line was matched (and possibly printed).
 *   F_success on success and the line was matched (and possibly printed).
 */
#ifndef _di_fss_extended_list_read_process_at_line_
  extern f_status_t fss_extended_list_read_process_at_line(fss_extended_list_read_main_t * const main, const f_array_length_t at, const f_array_lengths_t delimits_object, const f_array_lengths_t delimits_content, fss_extended_list_read_data_t *data, f_array_length_t *line) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_process_at_line_

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
#ifndef _di_fss_extended_list_read_process_line_
  extern f_status_t fss_extended_list_read_process_line(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_process_line_

/**
 * Process the Objects in the buffer, determining if the Object name is to be used or not.
 *
 * How an Object name is determined to be used or not is dependent on several parameters, such as --name, --depth, --at, and --line.
 *
 * @param data
 *   The program data.
 * @param names
 *   An array of booleans representing whether or not some Object name is to be used.
 *   (If TRUE, then the name is to be used and if FALSE, then the name is not to be used.)
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_extended_list_read_process_name_
  extern f_status_t fss_extended_list_read_process_name(fss_extended_list_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_process_name_

/**
 * Process the parameters, populating the option property of the program data.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: fss_extended_list_read_load_setting()
 *
 * @see fll_fss_extended_list_read()
 *
 * @see fss_extended_list_read_load_setting()
 */
#ifndef _di_fss_extended_list_read_process_option_
  extern f_status_t fss_extended_list_read_process_option(fss_extended_list_read_main_t * const main, const f_console_arguments_t *arguments, fss_extended_list_read_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_process_option_

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
#ifndef _di_fss_extended_list_read_process_total_
  extern f_status_t fss_extended_list_read_process_total(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t *data, bool names[]) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_list_read_process_total_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_extended_list_read_h
