/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide common FSS functions.
 *
 * @todo add "snatch" functions to grab contents in separate sets instead of appending (such as for fss extended).
 */
#ifndef _FLL_fss_h
#define _FLL_fss_h

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/fss.h>

// fll-1 includes
#include <level_1/conversion.h>
#include <level_1/fss.h>
#include <level_1/fss_macro.h>
#include <level_1/fss_status.h>
#include <level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify FSS type from a buffered string.
 *
 * @param buffer
 *   The string to process.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_none on success
 *   FL_fss_header_not if no header is found.
 *   FL_fss_accepted_invalid (with warning bit) if header is technically invalid but can be identified.
 *   FL_fss_header_not (with error bit) if the an error occurred prior to identifying a valid header.
 *
 *   Errors from (with error bit): fl_conversion_string_to_hexidecimal_unsigned().
 */
#ifndef _di_fll_fss_identify_
  extern f_return_status fll_fss_identify(const f_string_static_t buffer, f_fss_header_t *header);
#endif // _di_fll_fss_identify_

/**
 * Identify FSS type from a file.
 *
 * @param file
 *   The file information.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_none on success.
 *   FL_fss_header_not if no header is found.
 *   FL_fss_accepted_invalid (with warning bit) if header is technically invalid but can be identified.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   FL_fss_header_not (with error bit) if the an error occurred prior to identifying a valid header.
 *
 *   Errors from (with error bit): fl_conversion_string_to_hexidecimal_unsigned().
 *   Errors from (with error bit): f_file_read_until().
 *   Errors from (with error bit): f_file_seek().
 *
 * @see f_file_read_until()
 */
#ifndef _di_fll_fss_identify_file_
  extern f_return_status fll_fss_identify_file(f_file_t *file, f_fss_header_t *header);
#endif // _di_fll_fss_identify_file_

/**
 * Perform simple search through all objects against the given set, saving all values when matched.
 *
 * Only the first match for each distinct object is snatched.
 * Only the first content for each object is snatched.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param values
 *   An array of values where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_append_nulless().
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_append_nulless()
 */
#ifndef _di_fll_fss_snatch_
  extern f_return_status fll_fss_snatch(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, f_string_dynamic_t *values[], f_array_length_t *indexs[]);
#endif // _di_fll_fss_snatch_

/**
 * Perform simple search through all objects against the given set, saving all values when matched.
 *
 * All matches for each object is snatched.
 * All content for each object is snatched.
 *
 * Multiple contents for a single object are stored in separate strings.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param values
 *   An array of values where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_append_nulless().
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_append_nulless()
 */
#ifndef _di_fll_fss_snatch_apart_
  extern f_return_status fll_fss_snatch_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, f_string_dynamics_t *values[], f_array_lengths_t *indexs[]);
#endif // _di_fll_fss_snatch_apart_

/**
 * Perform simple search through all objects against the given set, saving all values to a map when matched.
 *
 * Only the first match for each distinct object and map name is snatched (map names are therefore distinct).
 * Only the first content map value for each object and map name is snatched.
 *
 * The first content is considered the map name, all other content are considered a map value.
 *
 * This will ignore any object that has no map name.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param values
 *   An array of map arrays where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_append_nulless().
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_append_nulless()
 */
#ifndef _di_fll_fss_snatch_map_
  extern f_return_status fll_fss_snatch_map(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, f_string_maps_t *values[], f_array_lengths_t *indexs[]);
#endif // _di_fll_fss_snatch_map_

/**
 * Perform simple search through all objects against the given set, saving all values to a multi map when matched.
 *
 * All matches for each object and map name is snatched.
 * All content map values for each object and map name is snatched.
 *
 * The first content value is considered the map name, all other content values are considered a map value.
 * Multiple contents, after the first, for a single object are stored in separate map value strings.
 * Content for multiple identical objects and map names are added in separate maps from other objects (map names are therefore non-distinct).
 *
 * This will ignore any object that has no map name.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param values
 *   An array of multi map arrays where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_append_nulless().
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_append_nulless()
 */
#ifndef _di_fll_fss_snatch_map_apart_
  extern f_return_status fll_fss_snatch_map_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, f_string_map_multis_t *values[], f_array_lengths_t *indexs[]);
#endif // _di_fll_fss_snatch_map_apart_

/**
 * Perform simple search through all objects against the given set, saving all values to a map when matched.
 *
 * Only the first match for each distinct object and map name is snatched (map names are therefore distinct).
 * All content values for each object and map name is snatched.
 *
 * The first content value is considered the map name, all other content values are considered a map value.
 * Multiple contents, after the first, for a single object are appended to a single map value string using the provided glue.
 *
 * This will ignore any object that has no map name.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param glue
 *   A string to append between each duplicate name found when "snatching".
 * @param glue_length
 *   The length of the glue string
 * @param values
 *   An array of multi map value arrays where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_mash_nulless().
 */
#ifndef _di_fll_fss_snatch_map_mash_
  extern f_return_status fll_fss_snatch_map_mash(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_maps_t *values[], f_array_lengths_t *indexs[]);
#endif // _di_fll_fss_snatch_map_mash_

/**
 * Perform simple search through all objects against the given set, saving all values to a multi map when matched.
 *
 * All matches for each object is snatched.
 * All content for each object and map name is snatched.
 *
 * The first content value is considered the map name, all other content values are considered a map value.
 * Multiple contents, after the first, for a single object are appended to a single map value string using the provided glue.
 * Content for multiple identical objects are added in separate maps from other objects (map names are therefore non-distinct).
 *
 * This will ignore any object that has no map name.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param glue
 *   A string to append between each duplicate name found when "snatching".
 * @param glue_length
 *   The length of the glue string
 * @param values
 *   An array of multi map value arrays where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_append_nulless().
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_mash_nulless()
 */
#ifndef _di_fll_fss_snatch_map_mash_apart_
  extern f_return_status fll_fss_snatch_map_mash_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_map_multis_t *values[], f_array_lengths_t *indexs[]);
#endif // _di_fll_fss_snatch_map_mash_apart_

/**
 * Perform simple search through all objects against the given set, saving all values to a map when matched.
 *
 * All matches for each distinct object and map name is snatched.
 * All content map values for each distinct object and map name is snatched.
 *
 * The first content is considered the map name, all other content are considered a map value.
 * Multiple contents, after the first, for each distinct object and map names are appended to a single map value string using the provided glue (map names are therefore distinct).
 *
 * This will ignore any object that has no map name.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param glue
 *   A string to append between each duplicate name found when "snatching".
 * @param glue_length
 *   The length of the glue string
 * @param values
 *   An array of map arrays where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_append_nulless().
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_mash_nulless()
 */
#ifndef _di_fll_fss_snatch_map_together_
  extern f_return_status fll_fss_snatch_map_together(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_maps_t *values[], f_array_lengths_t *indexs[]);
#endif // _di_fll_fss_snatch_map_together_

/**
 * Perform simple search through all objects against the given set, saving all values when matched.
 *
 * Only the first match for each distinct object is snatched.
 * All content for each object is snatched.
 *
 * Multiple contents for a single object are appended using the provided glue.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param glue
 *   A string to append between each duplicate name found when "snatching".
 * @param glue_length
 *   The length of the glue string.
 * @param values
 *   An array of values where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_mash_nulless().
 */
#ifndef _di_fll_fss_snatch_mash_
  extern f_return_status fll_fss_snatch_mash(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_dynamic_t *values[], f_array_length_t *indexs[]);
#endif // _di_fll_fss_snatch_mash_

/**
 * Perform simple search through all objects against the given set, saving all values when matched.
 *
 * All matches for each object is snatched.
 * All content for each object is snatched.
 *
 * Multiple contents for a single object are appended using the provided glue.
 * Content for multiple identical objects are added in separate strings from other objects.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param glue
 *   A string to append between each duplicate name found when "snatching".
 * @param glue_length
 *   The length of the glue string
 * @param values
 *   An array of values where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_append_nulless().
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_mash_nulless()
 */
#ifndef _di_fll_fss_snatch_mash_apart_
  extern f_return_status fll_fss_snatch_mash_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_dynamics_t *values[], f_array_lengths_t *indexs[]);
#endif // _di_fll_fss_snatch_mash_apart_

/**
 * Perform simple search through all objects against the given set, saving all values when matched.
 *
 * All matches for each object is snatched.
 * Multiple contents for all objects are appended using the provided glue.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL characters when copying.
 *
 * This performs only a simple search algorithm that should be acceptable for small sets where performance is generally not a concern.
 *
 * @param buffer
 *   The buffer to read from.
 * @param objects
 *   This object mappings to process.
 * @param contents
 *   This content mappings to process.
 * @param names
 *   An array of strings to "snatch" from the buffer.
 * @param lengths
 *   An array of lengths for each names string.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param values
 *   An array of values where "snatched" content is stored.
 * @param indexs
 *   An array representing the index within the objects where the match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors from (with error bit): fl_string_compare_trim().
 *   Errors from (with error bit): fl_string_dynamic_partial_mash_nulless().
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_append_nulless()
 */
#ifndef _di_fll_fss_snatch_together_
  extern f_return_status fll_fss_snatch_together(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_dynamic_t *values[], f_array_length_t *indexs[]);
#endif // _di_fll_fss_snatch_together_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_h
