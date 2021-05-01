/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_extended_read_h
#define _PRIVATE_fss_extended_read_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine if the given depth is to be delimited or not.
 *
 * @param main
 *   The program specific main.
 * @param depth
 *   The depth to check.
 *
 * @return
 *   F_true if delimited.
 *   F_false if not delimited.
 */
#ifndef _di_fss_extended_read_is_delimited_at_depth_
  extern f_status_t fss_extended_read_is_delimited_at_depth(const fss_extended_read_main_t main, const f_array_length_t depth) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_is_delimited_at_depth_

/**
 * Pre-process the parameters, parsing out and handling the depth and depth related parameters.
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
#ifndef _di_fss_extended_read_main_preprocess_depth_
  extern f_status_t fss_extended_read_main_preprocess_depth(const f_console_arguments_t arguments, const fss_extended_read_main_t main, fss_extended_read_depths_t *depths) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_main_preprocess_depth_

/**
 * Process a given file.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param main
 *   The program specific main.
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
  extern f_status_t fss_extended_read_main_process_file(const f_console_arguments_t arguments, fss_extended_read_main_t *main, const f_string_t file_name, const fss_extended_read_depths_t depths, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_main_process_file_

/**
 * Print the end of an object (which is essentially the start of a content).
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_extended_read_print_object_end_
  extern void fss_extended_read_print_object_end(const fss_extended_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_print_object_end_

/**
 * Print the end of an content.
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_extended_read_print_content_end_
  extern void fss_extended_read_print_content_end(const fss_extended_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_print_content_end_

/**
 * Print the end of an object/content set.
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_extended_read_print_set_end_
  extern void fss_extended_read_print_set_end(const fss_extended_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_print_set_end_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_extended_read_h
