/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides string capabilities.
 *
 * It is highly recommended that all string arrays are set to a max size of F_array_length_t_size_d.
 * Any calculations against the length (aka: string.used) can always perform (A < B) operators such that the B is F_array_length_t_size_d + 1 without integer overflow.
 */
#ifndef _F_string_h
#define _F_string_h

// Libc includes.
#include <string.h>

// FLL-0 includes.
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type.h>

// FLL-0 string includes.
#include <fll/level_0/string/common.h>
#include <fll/level_0/string/range.h>
#include <fll/level_0/string/static.h>
#include <fll/level_0/string/dynamic.h>
#include <fll/level_0/string/map.h>
#include <fll/level_0/string/map_multi.h>
#include <fll/level_0/string/quantity.h>
#include <fll/level_0/string/triple.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_append_
  extern f_status_t f_string_append(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_append_

/**
 * Append the source string onto the destination only if the string is not already at the end.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_append_assure_
  extern f_status_t f_string_append_assure(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_append_assure_

/**
 * Append the source string onto the destination only if the string is not already at the end.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_append_assure_nulless_
  extern f_status_t f_string_append_assure_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_append_assure_nulless_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_append_nulless_
  extern f_status_t f_string_append_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_append_nulless_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mash_
  extern f_status_t f_string_mash(const f_string_t glue, const f_array_length_t glue_length, const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_mash_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mash_nulless_
  extern f_status_t f_string_mash_nulless(const f_string_t glue, const f_array_length_t glue_length, const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mish_
  extern f_status_t f_string_mish(const f_string_t glue, const f_array_length_t glue_length, const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_mish_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_mish_nulless_
  extern f_status_t f_string_mish_nulless(const f_string_t glue, const f_array_length_t glue_length, const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_mish_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_prepend_
  extern f_status_t f_string_prepend(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_prepend_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_prepend_assure_
  extern f_status_t f_string_prepend_assure(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_prepend_assure_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when prepending.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_prepend_assure_nulless_
  extern f_status_t f_string_prepend_assure_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when prepending.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_prepend_nulless_
  extern f_status_t f_string_prepend_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t * const destination);
#endif // _di_f_string_prepend_nulless_

/**
 * Seek the string location forward until EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_seek_line_
  extern f_status_t f_string_seek_line(const f_string_t string, f_string_range_t * const range);
#endif // _di_f_string_seek_line_

/**
 * Seek the string location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_seek_line_to_
  extern f_status_t f_string_seek_line_to(const f_string_t string, const uint8_t seek_to, f_string_range_t * const range);
#endif // _di_f_string_seek_line_to_

/**
 * Seek the string location forward until the character (1-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_seek_to_
  extern f_status_t f_string_seek_to(const f_string_t string, const uint8_t seek_to, f_string_range_t * const range);
#endif // _di_f_string_seek_to_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_h
