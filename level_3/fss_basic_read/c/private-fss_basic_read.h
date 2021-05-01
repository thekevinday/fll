/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_basic_read_h
#define _PRIVATE_fss_basic_read_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process the parameters, parsing out and handling the depth and depth related parameters.
 *
 * Will handle depth-sensitive parameter conflicts, such as --name being used with --at (which is not allowed).
 *
 * @param arguments
 *   The console arguments to pre-process.
 * @param main
 *   The program specific main.
 * @param depths
 *   This stores the pre-processed depth parameters.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fss_basic_read_depth_process_
  extern f_status_t fss_basic_read_depth_process(const f_console_arguments_t arguments, const fss_basic_read_main_t main, fss_basic_read_depths_t *depths) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_depth_process_

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
#ifndef _di_fss_basic_read_file_identify_
  extern f_string_t fss_basic_read_file_identify(const f_array_length_t at, const fss_basic_read_files_t files) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_file_identify_

/**
 * Load a given number parameter.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param main
 *   The program specific main.
 * @param parameter
 *   An ID representing the parameter.
 * @param name
 *   The parameter name to print on error.
 * @param number
 *   The location to store the loaded number.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fss_basic_read_load_number_
  extern f_status_t fss_basic_read_load_number(const f_console_arguments_t arguments, const fss_basic_read_main_t main, const f_array_length_t parameter, const f_string_t name, f_number_unsigned_t *number) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_load_number_

/**
 * Print the Object and Content at the given position.
 *
 * Only what is requested to print (Object, Content, both, or neither) will be printed, if there is something to print.
 *
 * @param main
 *   The program specific main.
 * @param at
 *   The index in the Objects and Contents to print.
 * @param include_empty
 *   If TRUE, empty Content is printed.
 *   If FALSE, empty Content is ignored.
 * @param delimits
 *   The delimits in the objects and contents.
 * @param print_this
 *   Set bit 0x1 for printing Object.
 *   Set bit 0x2 for printing Content.
 *
 *   This is a temporary parameter to be used until other structural changes are made and completed.
 */
#ifndef _di_fss_basic_read_print_at_
  extern void fss_basic_read_print_at(const fss_basic_read_main_t main, const f_array_length_t at, const bool include_empty, const f_fss_delimits_t delimits, const uint8_t print_this) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_at_

/**
 * Print the end of an object (which is essentially the start of a content).
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_basic_read_print_object_end_
  extern void fss_basic_read_print_object_end(const fss_basic_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_object_end_

/**
 * Print the number one and a newline.
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_basic_read_print_one_
  extern void fss_basic_read_print_one(const fss_basic_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_one_

/**
 * Print the end of an object/content set.
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_basic_read_print_set_end_
  extern void fss_basic_read_print_set_end(const fss_basic_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_set_end_

/**
 * Print the number zero and a newline.
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_basic_read_print_zero_
  extern void fss_basic_read_print_zero(const fss_basic_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_zero_

/**
 * Perform the basic read processing on the buffer.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param files
 *   An array representing the ranges in which a given file exists in the buffer.
 * @param depths
 *   The processed depth parameters.
 * @param main
 *   The program specific main.
 * @param delimits
 *   An array of delimits detected during processing.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_basic_read_load_setting()
 */
#ifndef _di_fss_basic_read_process_
  extern f_status_t fss_basic_read_process(const f_console_arguments_t arguments, const fss_basic_read_files_t files, const fss_basic_read_depths_t depths, fss_basic_read_main_t *main, f_fss_delimits_t *delimits) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_basic_read_h
