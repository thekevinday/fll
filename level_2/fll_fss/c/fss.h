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
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_macro.h>
#include <level_1/fss_status.h>
#include <level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

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
  extern f_return_status fll_fss_snatch(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, f_string_dynamic *values[]);
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
  extern f_return_status fll_fss_snatch_apart(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, f_string_dynamics *values[]);
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
  extern f_return_status fll_fss_snatch_map(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, f_string_maps *values[]);
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
  extern f_return_status fll_fss_snatch_map_apart(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, f_string_map_multis *values[]);
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
  extern f_return_status fll_fss_snatch_map_mash(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, const f_string glue, const f_string_length glue_length, f_string_maps *values[]);
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
  extern f_return_status fll_fss_snatch_map_mash_apart(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, const f_string glue, const f_string_length glue_length, f_string_map_multis *values[]);
#endif // _di_fll_fss_snatch_map_mash_apart__

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
  extern f_return_status fll_fss_snatch_map_together(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, const f_string glue, const f_string_length glue_length, f_string_maps *values[]);
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
  extern f_return_status fll_fss_snatch_mash(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, const f_string glue, const f_string_length glue_length, f_string_dynamic *values[]);
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
  extern f_return_status fll_fss_snatch_mash_apart(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, const f_string glue, const f_string_length glue_length, f_string_dynamics *values[]);
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
  extern f_return_status fll_fss_snatch_together(const f_string_static buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], const f_string_length size, const f_string glue, const f_string_length glue_length, f_string_dynamic *values[]);
#endif // _di_fll_fss_snatch_together_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_h
