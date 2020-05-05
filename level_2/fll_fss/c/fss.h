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
 * Only the first match for each name is snatched, all others are ignored.
 *
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL charactes when copying.
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
 * @param values
 *   An array of values where "snatched" content is stored.
 *   Each of these must be of type f_string_dynamic.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 *
 * @return
 *   f_none on success.
 *   f_no_data when there is no buffer, objects or contents to process.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fll_fss_snatch_
  extern f_return_status fll_fss_snatch(const f_string_dynamic buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], f_string_dynamic *values[], const f_string_length size);
#endif // _di_fll_fss_snatch_

/**
 * Perform simple search through all objects against the given set, saving all values when matched.
 *
 * This will append all duplicates using the provided glue.
 * This will trim the object names when comparing (removing leading/trailing whitespace).
 * This will strip NULL charactes when copying.
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
 *   Each of these must be of type f_string.
 * @param lengths
 *   An array of lengths for each names string.
 *   Each of these must be of type f_string_length.
 * @param values
 *   An array of values where "snatched" content is stored.
 *   Each of these must be of type f_string_dynamic.
 * @param size
 *   The total size of the names, lengths, and values arrays.
 * @param glue
 *   A string to append between each duplicate name found when "snatching".
 * @param glue_length
 *   The length of the glue string.
 *
 * @return
 *   f_none on success.
 *   f_no_data when there is no buffer, objects or contents to process.
 *   f_error_reallocation (with error bit) on reallocation error.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fll_fss_snatch_mash_
  extern f_return_status fll_fss_snatch_mash(const f_string_dynamic buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], f_string_dynamic *values[], const f_string_length size, const f_string glue, const f_string_length glue_length);
#endif // _di_fll_fss_snatch_mash_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_h
