/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
 * Licenses: lgplv2.1
 *
 * Defines UTF-8 string data.
 *
 * This is auto-included by utf.h and should not need to be explicitly included.
 */
#ifndef _F_utf_string_h
#define _F_utf_string_h

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_f_utf_string_append_
  extern f_status_t f_utf_string_append(const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_append_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_f_utf_string_append_assure_
  extern f_status_t f_utf_string_append_assure(const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_append_assure_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_append_assure_nulless_
  extern f_status_t f_utf_string_append_assure_nulless(const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_append_assure_nulless_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_append_nulless_
  extern f_status_t f_utf_string_append_nulless(const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_append_nulless_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_mash_
  extern f_status_t f_utf_string_mash(const f_utf_string_t glue, const f_number_unsigned_t glue_length, const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_mash_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_mash_nulless_
  extern f_status_t f_utf_string_mash_nulless(const f_utf_string_t glue, const f_number_unsigned_t glue_length, const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_mash_nulless_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_mish_
  extern f_status_t f_utf_string_mish(const f_utf_string_t glue, const f_number_unsigned_t glue_length, const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_mish_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_mish_nulless_
  extern f_status_t f_utf_string_mish_nulless(const f_utf_string_t glue, const f_number_unsigned_t glue_length, const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_mish_nulless_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_prepend_
  extern f_status_t f_utf_string_prepend(const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_prepend_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_prepend_assure_
  extern f_status_t f_utf_string_prepend_assure(const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_prepend_assure_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_prepend_assure_nulless_
  extern f_status_t f_utf_string_prepend_assure_nulless(const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_prepend_assure_nulless_

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
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_prepend_nulless_
  extern f_status_t f_utf_string_prepend_nulless(const f_utf_string_t source, const f_number_unsigned_t length, f_utf_string_dynamic_t * const destination);
#endif // _di_f_utf_string_prepend_nulless_

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
 *   F_okay on success.
 *   F_okay_stop on success, but stopped at end of range.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_utf_string_seek_line_
  extern f_status_t f_utf_string_seek_line(const f_utf_string_t string, f_string_range_t * const range);
#endif // _di_f_utf_string_seek_line_

/**
 * Seek the string location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to
 *   A character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_stop on success, but stopped at the stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_string_seek_line_to_
  extern f_status_t f_utf_string_seek_line_to(const f_utf_string_t string, const f_utf_char_t seek_to, f_string_range_t * const range);
#endif // _di_f_utf_string_seek_line_to_

/**
 * Seek the string location forward until the character (1-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to
 *   A character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_stop on success, but stopped at the stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *   F_utf_not (with error bit) if unicode is an invalid Unicode character.
 */
#ifndef _di_f_utf_string_seek_to_
  extern f_status_t f_utf_string_seek_to(const f_utf_string_t string, const f_utf_char_t seek_to, f_string_range_t * const range);
#endif // _di_f_utf_string_seek_to_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_string_h
