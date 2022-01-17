/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provide common FSS functions.
 *
 * @todo add "snatch" functions to grab contents in separate sets instead of appending (such as for fss extended).
 */
#ifndef _FLL_fss_h
#define _FLL_fss_h

// fll-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/fss.h>

// fll-1 includes
#include <fll/level_1/conversion.h>
#include <fll/level_1/fss.h>
#include <fll/level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify FSS type from a buffered string.
 *
 * The operates on the assumption that the first character provided is the start of the line.
 * This will process until the stop point or the end of the line.
 * This stop point should always be after the end of the line, except when there is an error.
 *
 * This expects there to be at least a single "fss-XXXX" FSS Identifier.
 * If one is not found but the line contains valid FLL Identifiers, then this returns F_maybe.
 *
 * See the fl_string_fll_identify() function for details on individual FLL/FSS Identifier processing.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The caller must ensure that the stop point does not exceed the buffer size.
 *
 *   The range->start may be updated by this function.
 *   On failure, the range->start may represent the last position looked at.
 *   On success, the range->start should be after the last valid position (for example for "# fss-1234 fss-4321\n", the ast valid position would be the byte after the "\n").
 * @param ids
 *   (optional) The FLL Identifiers to populate with results of this function.
 *   Set to NULL to not use.
 *
 *   When non-NULL, this will have its length reset to 0.
 *   FLL/FSS Identifiers will then be appended to this array.
 *
 * @return
 *   F_data_not if length is 0.
 *   F_found if the buffer does represent a valid FSS Identifier.
 *   F_found_not if the buffer does not represent a valid FSS Identifier.
 *   F_maybe if the buffer is a valid FLL Identifier but does not have an FSS Identifier ("fss-XXXX").
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *
 *   Errors (with error bit) from: f_type_fll_ids_increase().
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *   Errors (with error bit) from: fl_string_fll_identify().
 *
 * @see f_type_fll_ids_increase()
 * @see f_utf_is_whitespace()
 * @see fl_string_fll_identify()
 */
#ifndef _di_fll_fss_identify_
  extern f_status_t fll_fss_identify(const f_string_t buffer, f_string_range_t *range, f_fll_ids_t *ids);
#endif // _di_fll_fss_identify_

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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_string_dynamic_partial_append_nulless()
 * @see fl_string_compare_trim()
 */
#ifndef _di_fll_fss_snatch_
  extern f_status_t fll_fss_snatch(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, f_string_dynamic_t *values[], bool matches[], f_array_length_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_string_dynamic_partial_append_nulless()
 * @see fl_string_compare_trim()
 */
#ifndef _di_fll_fss_snatch_apart_
  extern f_status_t fll_fss_snatch_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, f_string_dynamics_t *values[], bool matches[], f_array_lengths_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_string_dynamic_partial_append_nulless()
 * @see fl_string_compare_trim()
 */
#ifndef _di_fll_fss_snatch_map_
  extern f_status_t fll_fss_snatch_map(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, f_string_maps_t *values[], bool matches[], f_array_lengths_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_string_dynamic_partial_append_nulless()
 * @see fl_string_compare_trim()
 */
#ifndef _di_fll_fss_snatch_map_apart_
  extern f_status_t fll_fss_snatch_map_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, f_string_map_multis_t *values[], bool matches[], f_array_lengths_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_mash_nulless().
 */
#ifndef _di_fll_fss_snatch_map_mash_
  extern f_status_t fll_fss_snatch_map_mash(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_maps_t *values[], bool matches[], f_array_lengths_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_string_dynamic_partial_mash_nulless()
 * @see fl_string_compare_trim()
 */
#ifndef _di_fll_fss_snatch_map_mash_apart_
  extern f_status_t fll_fss_snatch_map_mash_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_map_multis_t *values[], bool matches[], f_array_lengths_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_string_dynamic_partial_mash_nulless()
 * @see fl_string_compare_trim()
 */
#ifndef _di_fll_fss_snatch_map_together_
  extern f_status_t fll_fss_snatch_map_together(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_maps_t *values[], bool matches[], f_array_lengths_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_mash_nulless().
 */
#ifndef _di_fll_fss_snatch_mash_
  extern f_status_t fll_fss_snatch_mash(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_dynamic_t *values[], bool matches[], f_array_length_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_append_nulless().
 *
 * @see f_string_dynamic_partial_mash_nulless()
 * @see fl_string_compare_trim()
 */
#ifndef _di_fll_fss_snatch_mash_apart_
  extern f_status_t fll_fss_snatch_mash_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_dynamics_t *values[], bool matches[], f_array_lengths_t *indexs[]);
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
 * @param matches
 *   An array representing the if an Object was matched.
 *   Set the pointer address to 0 to disable.
 * @param indexs
 *   An array representing the index within the Objects where the Content match was made.
 *   Set the pointer address to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_data_not when there is no buffer, objects or contents to process.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_string_compare_trim().
 *   Errors (with error bit) from: f_string_dynamic_partial_mash_nulless().
 *
 * @see f_string_dynamic_partial_append_nulless()
 * @see fl_string_compare_trim()
 */
#ifndef _di_fll_fss_snatch_together_
  extern f_status_t fll_fss_snatch_together(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_dynamic_t *values[], bool matches[], f_array_length_t *indexs[]);
#endif // _di_fll_fss_snatch_together_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_h
