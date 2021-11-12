/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_embedded_list_read_h
#define _PRIVATE_fss_embedded_list_read_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Pre-process the parameters, parsing out and handling the depth and depth related parameters.
 *
 * Will handle depth-sensitive parameter conflicts, such as --name being used with --at (which is not allowed).
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The console arguments to pre-process.
 * @param depths
 *   This stores the pre-processed depth parameters.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fss_embedded_list_read_main_preprocess_depth_
  extern f_status_t fss_embedded_list_read_main_preprocess_depth(fss_embedded_list_read_main_t * const main, const f_console_arguments_t *arguments, fss_embedded_list_read_depths_t *depths) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_main_preprocess_depth_

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
 * @param comments
 *   An array of ranges representing where comments are found within any valid content.
 *   This only stores comments found within valid content only.
 *
 * @see fss_embedded_list_read_main_preprocess_depth()
 * @see fss_embedded_list_read_main_process_for_depth()
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fss_embedded_list_read_main_process_file_
  extern f_status_t fss_embedded_list_read_main_process_file(fss_embedded_list_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, const fss_embedded_list_read_depths_t depths, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits, f_fss_comments_t *comments) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_main_process_file_

/**
 * Process the items for a given depth.
 *
 * This will recursively continue down the depth chain until the final depth is reached.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The console arguments passed to the program.
 * @param file_name
 *   The name of the file being processed.
 * @param depths
 *   The array of all depth related parameter settings.
 * @param depths_index
 *   The array location within depth being worked on.
 * @param line
 *   The line number parameter value, used for printing a specific line number for content.
 * @param parents
 *   The skip status of any parent lists.
 *   Set parents.length to 0 for depth 0.
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
 * @see fss_embedded_list_read_main_process_file()
 */
#ifndef _di_fss_embedded_list_read_main_process_for_depth_
  extern f_status_t fss_embedded_list_read_main_process_for_depth(fss_embedded_list_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t filename, const fss_embedded_list_read_depths_t depths, const f_array_length_t depths_index, const f_array_length_t line, const fss_embedded_list_read_skip_t parents, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_main_process_for_depth_

/**
 * Print the ignore character for content.
 *
 * This is only used in pipe output mode.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_embedded_list_read_print_content_ignore_
  extern void fss_embedded_list_read_print_content_ignore(fss_embedded_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_print_content_ignore_

/**
 * Print the end of an object (which is essentially the start of a content).
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_embedded_list_read_print_object_end_
  extern void fss_embedded_list_read_print_object_end(fss_embedded_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_print_object_end_

/**
 * Print the end of an object/content set.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_embedded_list_read_print_set_end_
  extern void fss_embedded_list_read_print_set_end(fss_embedded_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_print_set_end_

/**
 * Rewrite the object and content delimit ranges to be within the given depth range.
 *
 * @param main
 *   The main program data.
 * @param objects_delimits
 *   An array of delimits detected during processing, for top-level objects.
 * @param contents_delimits
 *   An array of delimits detected during processing, for contents.
 *
 * @see fss_embedded_list_read_main_process_file()
 */
#ifndef _di_fss_embedded_list_read_process_delimits_
  extern void fss_embedded_list_read_process_delimits(fss_embedded_list_read_main_t * const main, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_process_delimits_

/**
 * Write the given delimits at the given depth back into the new delimits array, specifically for contents.
 *
 * @param main
 *   The main program data.
 * @param depth
 *   The depth in which to process.
 * @param original_delimits
 *   The original delimits structure.
 * @param original_used
 *   The size of the original delimits structure.
 * @param delimits
 *   The delimits array in which the delimits are written to.
 *
 * @see fss_embedded_list_read_process_delimits()
 */
#ifndef _di_fss_embedded_list_read_process_delimits_contents_
  extern void fss_embedded_list_read_process_delimits_contents(fss_embedded_list_read_main_t * const main, const f_array_length_t depth, const f_array_length_t original_delimits[], const f_array_length_t original_used, f_fss_delimits_t *delimits) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_process_delimits_contents_

/**
 * Write the given delimits at the given depth back into the new delimits array, specifically for objects.
 *
 * @param main
 *   The main program data.
 * @param depth
 *   The depth in which to process.
 * @param original_delimits
 *   The original delimits structure.
 * @param original_used
 *   The size of the original delimits structure.
 * @param delimits
 *   The delimits array in which the delimits are written to.
 *
 * @see fss_embedded_list_read_process_delimits()
 */
#ifndef _di_fss_embedded_list_read_process_delimits_objects_
  extern void fss_embedded_list_read_process_delimits_objects(fss_embedded_list_read_main_t * const main, const f_array_length_t depth, const f_array_length_t original_delimits[], const f_array_length_t original_used, f_fss_delimits_t *delimits) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_process_delimits_objects_

/**
 * Determine if the given location is actually within another depth.
 *
 * @param main
 *   The main program data.
 * @param depth
 *   The depth in which to process.
 * @param location
 *   The location to investigate.
 *
 * @return
 *   TRUE if location is within a greater depth.
 *   FALSE if location is not within a greater depth.
 *
 * @see fss_embedded_list_read_process_delimits_objects()
 * @see fss_embedded_list_read_process_delimits_contents()
 */
#ifndef _di_fss_embedded_list_read_process_delimits_within_greater_
  extern f_status_t fss_embedded_list_read_process_delimits_within_greater(fss_embedded_list_read_main_t * const main, const f_array_length_t depth, const f_array_length_t location) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_process_delimits_within_greater_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_embedded_list_read_h
