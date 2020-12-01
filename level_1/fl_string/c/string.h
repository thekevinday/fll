/**
 * FLL - Level 1
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides basic string manipulation and processing capabilities.
 *
 * UTF-8 is handled within these functions via normal string characters (f_string_t).
 * Unlike f_utf_string_t, these f_string_t base functions do not force padding of ASCII or UTF-8 characters.
 * With f_string_t, a 1-byte wide ASCII character is stored as 1 byte and a 4-byte wide UTF-8 character is stored as 4 bytes.
 *
 * This shortens the size of the string at the cost of complexity vs f_utf_string_t.
 *
 * Because of the variable width, it is generally unsafe to ignore invalid UTF-8 sequences.
 * Invalid UTF-8 will be generally result in an error.
 */
#ifndef _FL_string_h
#define _FL_string_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_append_
  extern f_return_status fl_string_append(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_append_

/**
 * Append the source string onto the destination, but only if the string is not already at the end.
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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_append_assure_
  extern f_return_status fl_string_append_assure(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_append_assure_

/**
 * Append the source string onto the destination, but only if the string is not already at the end.
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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_append_assure_nulless_
  extern f_return_status fl_string_append_assure_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_append_assure_nulless_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_append_nulless_
  extern f_return_status fl_string_append_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_append_nulless_

/**
 * Compare two strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   Length of string1.
 * @param length2
 *   Length of string2.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_compare_
  extern f_return_status fl_string_compare(const f_string_t string1, const f_string_t string2, const f_string_length_t length1, const f_string_length_t length2);
#endif // _di_fl_string_compare_

/**
 * Compare two strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   Length of string1.
 * @param length2
 *   Length of string2.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_compare_except_
  extern f_return_status fl_string_compare_except(const f_string_t string1, const f_string_t string2, const f_string_length_t length1, const f_string_length_t length2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_compare_except_

/**
 * Compare two strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   Length of string1.
 * @param length2
 *   Length of string2.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_compare_except_trim_
  extern f_return_status fl_string_compare_except_trim(const f_string_t string1, const f_string_t string2, const f_string_length_t length1, const f_string_length_t length2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_compare_except_trim_

/**
 * Compare two strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   Length of string1.
 * @param length2
 *   Length of string2.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_compare_trim_
  extern f_return_status fl_string_compare_trim(const f_string_t string1, const f_string_t string2, const f_string_length_t length1, const f_string_length_t length2);
#endif // _di_fl_string_compare_trim_

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_append_
  extern f_return_status fl_string_dynamic_append(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_append_

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_append_assure_
  extern f_return_status fl_string_dynamic_append_assure(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_append_assure_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_append_assure_nulless_
  extern f_return_status fl_string_dynamic_append_assure_nulless(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_append_assure_nulless_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_append_nulless_
  extern f_return_status fl_string_dynamic_append_nulless(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_append_nulless_

/**
 * Compare two strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_compare_
  extern f_return_status fl_string_dynamic_compare(const f_string_static_t string1, const f_string_static_t string2);
#endif // _di_fl_string_dynamic_compare_

/**
 * Compare two strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_compare_except_
  extern f_return_status fl_string_dynamic_compare_except(const f_string_static_t string1, const f_string_static_t string2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_compare_except_

/**
 * Compare two strings, similar to strncmp().
 *
 * This operates with the first string being a traditional string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   The length of string1.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_except_string_
  extern f_return_status fl_string_dynamic_compare_except_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_compare_except_string_

/**
 * Compare two strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_except_trim_
  extern f_return_status fl_string_dynamic_compare_except_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_compare_except_trim_

/**
 * Compare two strings, similar to strncmp().
 *
 * This operates with the first string being a traditional string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   The length of string1.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_except_trim_string_
  extern f_return_status fl_string_dynamic_compare_except_trim_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_compare_except_trim_string_

/**
 * Compare two strings, similar to strncmp().
 *
 * This operates with the first string being a traditional string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   The length of string1.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_string_
  extern f_return_status fl_string_dynamic_compare_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1);
#endif // _di_fl_string_dynamic_compare_string_

/**
 * Compare two strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_trim_
  extern f_return_status fl_string_dynamic_compare_trim(const f_string_static_t string1, const f_string_static_t string2);
#endif // _di_fl_string_dynamic_compare_trim_

/**
 * Compare two strings, similar to strncmp().
 *
 * This operates with the first string being a traditional string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   The length of string1.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_trim_string_
  extern f_return_status fl_string_dynamic_compare_trim_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1);
#endif // _di_fl_string_dynamic_compare_trim_string_

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
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_mash_
  extern f_return_status fl_string_dynamic_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_mash_

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
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_mash_nulless_
  extern f_return_status fl_string_dynamic_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_mash_nulless_

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
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_mish_
  extern f_return_status fl_string_dynamic_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_mish_

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
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_mish_nulless_
  extern f_return_status fl_string_dynamic_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_mish_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_append_
  extern f_return_status fl_string_dynamic_partial_append(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_append_

/**
 * Append the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_append_assure_
  extern f_return_status fl_string_dynamic_partial_append_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_append_assure_

/**
 * Append the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_append_assure_nulless_
  extern f_return_status fl_string_dynamic_partial_append_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_append_assure_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_append_nulless_
  extern f_return_status fl_string_dynamic_partial_append_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_append_nulless_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given ranges.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range1
 *   A range within the string1 to restrict the comparison to.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_
  extern f_return_status fl_string_dynamic_partial_compare(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given ranges.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range1
 *   A range within the string1 to restrict the comparison to.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_
  extern f_return_status fl_string_dynamic_partial_compare_except(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given range for the second string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_dynamic_
  extern f_return_status fl_string_dynamic_partial_compare_except_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_dynamic_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given range for the second string.
 *
 * This operates with the first string being a traditional string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   The length of string1.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_string_
  extern f_return_status fl_string_dynamic_partial_compare_except_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_string_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given range for the second string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_trim_dynamic_
  extern f_return_status fl_string_dynamic_partial_compare_except_trim_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_trim_dynamic_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given range for the second string.
 *
 * This operates with the first string being a traditional string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   The length of string1.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_trim_string_
  extern f_return_status fl_string_dynamic_partial_compare_except_trim_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_trim_string_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given ranges.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 * All 1-byte characters in except1 and except2 are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range1
 *   A range within the string1 to restrict the comparison to.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 * @param except1
 *   A set of locations within string1 to ignore.
 *   This assumes/requires that the locations be in linear order.
 * @param except2
 *   A set of locations within string2 to ignore.
 *   This assumes/requires that the locations be in linear order.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_trim_
  extern f_return_status fl_string_dynamic_partial_compare_except_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_string_lengths_t except1, const f_string_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_trim_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given range for the second string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_dynamic_
  extern f_return_status fl_string_dynamic_partial_compare_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_dynamic_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given range for the second string.
 *
 * This operates with the first string being a traditional string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   The length of string1.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_string_
  extern f_return_status fl_string_dynamic_partial_compare_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_string_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given range for the second string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_trim_dynamic_
  extern f_return_status fl_string_dynamic_partial_compare_trim_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_trim_dynamic_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given range for the second string.
 *
 * This operates with the first string being a traditional string.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   The length of string1.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_trim_string_
  extern f_return_status fl_string_dynamic_partial_compare_trim_string(const f_string_t string1, const f_string_static_t string2, const f_string_length_t length1, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_trim_string_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given ranges.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range1
 *   A range within the string1 to restrict the comparison to.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_trim_
  extern f_return_status fl_string_dynamic_partial_compare_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_trim_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_mash_
  extern f_return_status fl_string_dynamic_partial_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_mash_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
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
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_mash_nulless_
  extern f_return_status fl_string_dynamic_partial_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_mish_
  extern f_return_status fl_string_dynamic_partial_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_mish_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
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
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_mish_nulless_
  extern f_return_status fl_string_dynamic_partial_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_mish_nulless_

/**
 * Prepend the source string onto the destination, but restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_prepend_
  extern f_return_status fl_string_dynamic_partial_prepend(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_prepend_assure_
  extern f_return_status fl_string_dynamic_partial_prepend_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_prepend_assure_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_prepend_assure_nulless_
  extern f_return_status fl_string_dynamic_partial_prepend_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination, but restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_partial_prepend_nulless_
  extern f_return_status fl_string_dynamic_partial_prepend_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_partial_prepend_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_prepend_
  extern f_return_status fl_string_dynamic_prepend(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_prepend_assure_
  extern f_return_status fl_string_dynamic_prepend_assure(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_prepend_assure_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_prepend_assure_nulless_
  extern f_return_status fl_string_dynamic_prepend_assure_nulless(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_prepend_nulless_
  extern f_return_status fl_string_dynamic_prepend_nulless(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_prepend_nulless_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested range.
 *
 * @param source
 *   The buffer to rip from.
 * @param range
 *   A range within the buffer representing the string to rip.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_rip_
  extern f_return_status fl_string_dynamic_rip(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_rip_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested range.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The string to rip from.
 * @param range
 *   A range within the buffer representing the string to rip.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_rip_nulless_
  extern f_return_status fl_string_dynamic_rip_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_rip_nulless_

/**
 * Resize the dynamic string to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param string
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_decrease_
  extern f_return_status fl_string_dynamic_decrease(f_string_dynamic_t *string);
#endif // _di_fl_string_dynamic_decrease_

/**
 * Resize the dynamic string to a smaller size.
 *
 * This will resize making the string smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param string
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_decrease_by_
  extern f_return_status fl_string_dynamic_decrease_by(const f_string_length_t amount, f_string_dynamic_t *string);
#endif // _di_fl_string_dynamic_decrease_by_

/**
 * Resize the dynamic string to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_string_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param string
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_string_too_large on success, but the requested length is too large for the buffer.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_increase_
  extern f_return_status fl_string_dynamic_increase(f_string_dynamic_t *string);
#endif // _di_fl_string_dynamic_increase_

/**
 * Resize the dynamic string to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_string_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param string
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_string_too_large on success, but the requested length is too large for the buffer.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_increase_by_
  extern f_return_status fl_string_dynamic_increase_by(const f_string_length_t amount, f_string_dynamic_t *string);
#endif // _di_fl_string_dynamic_increase_by_

/**
 * Seek the buffer location forward until EOL is reached.
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
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_seek_line_
  extern f_return_status fl_string_dynamic_seek_line(const f_string_t string, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_line_

/**
 * Seek the buffer location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_seek_line_to_
  extern f_return_status fl_string_dynamic_seek_line_to(const f_string_t string, const int8_t seek_to_this, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_line_to_

/**
 * Seek the buffer location forward until the character (up to 4-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to_this
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *
 * @see f_utf_char_to_character()
 */
#ifndef _di_fl_string_dynamic_seek_line_to_utf_character_
  extern f_return_status fl_string_dynamic_seek_line_to_utf_character(const f_string_t string, const f_utf_character_t seek_to_this, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_line_to_utf_character_

/**
 * Increment buffer location until a graph character (including UTF-8) or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_fl_string_dynamic_seek_line_until_graph_
  extern f_return_status fl_string_dynamic_seek_line_until_graph(const f_string_t string, const int8_t placeholder, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_line_until_graph_

/**
 * Increment buffer location until a non-graph character (including UTF-8) or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_fl_string_dynamic_seek_line_until_non_graph_
  extern f_return_status fl_string_dynamic_seek_line_until_non_graph(const f_string_t string, const int8_t placeholder, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_line_until_non_graph_

/**
 * Seek the buffer location forward until the character (1-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_seek_to_
  extern f_return_status fl_string_dynamic_seek_to(const f_string_t string, const int8_t seek_to_this, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_to_

/**
 * Seek the buffer location forward until the UTF-8 character (up to 4-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to_this
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *
 * @see f_utf_char_to_character()
 */
#ifndef _di_fl_string_dynamic_seek_to_utf_character_
  extern f_return_status fl_string_dynamic_seek_to_utf_character(const f_string_t string, const f_utf_character_t seek_to_this, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_to_utf_character_

/**
 * Guarantee that an end of string (NULL) exists at the end of the string.
 *
 * This is intended to be used for anything requiring NULL terminated strings.
 * This will reallocate more space if necessary.
 *
 * If destination size is 0, then it will be reallocated and have the NULL assigned at index 0.
 *
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 */
#ifndef _di_fl_string_dynamic_terminate_
  extern f_return_status fl_string_dynamic_terminate(f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_terminate_

/**
 * Guarantee that an end of string (NULL) exists at the end of the string.
 *
 * This ensures that the terminating NULL not only exists but is not counted in destination.used.
 *
 * This is intended to be used for anything requiring NULL terminated strings whose used length cannot be counted.
 * This will reallocate more space if necessary.
 *
 * If destination size is 0, then it will be reallocated and have the NULL assigned at index 0.
 *
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 */
#ifndef _di_fl_string_dynamic_terminate_after_
  extern f_return_status fl_string_dynamic_terminate_after(f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_terminate_after_

/**
 * Resize the dynamic string array to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param strings
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamics_decrease_
  extern f_return_status fl_string_dynamics_decrease(f_string_dynamics_t *strings);
#endif // _di_fl_string_dynamics_decrease_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param strings
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamics_decrease_by_
  extern f_return_status fl_string_dynamics_decrease_by(const f_array_length_t amount, f_string_dynamics_t *strings);
#endif // _di_fl_string_dynamics_decrease_by_

/**
 * Increase the size of the dynamic string array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param strings
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but the requested length is too large for the buffer.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_fl_string_dynamics_increase_
  extern f_return_status fl_string_dynamics_increase(f_string_dynamics_t *strings);
#endif // _di_fl_string_dynamics_increase_

/**
 * Resize the dynamic string array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param strings
 *   The string array to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but the requested length is too large for the buffer.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_fl_string_dynamics_increase_by_
  extern f_return_status fl_string_dynamics_increase_by(const f_array_length_t amount, f_string_dynamics_t *strings);
#endif // _di_fl_string_dynamics_increase_by_

/**
 * Resize the string lengths array to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_lengths_decrease_
  extern f_return_status fl_string_lengths_decrease(f_string_lengths_t *lengths);
#endif // _di_fl_string_lengths_decrease_

/**
 * Resize the string lengths array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_lengths_decrease_by_
  extern f_return_status fl_string_lengths_decrease_by(const f_array_length_t amount, f_string_lengths_t *lengths);
#endif // _di_fl_string_lengths_decrease_by_

/**
 * Increase the size of the string lengths array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but the requested length is too large for the buffer.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_fl_string_lengths_increase_
  extern f_return_status fl_string_lengths_increase(f_string_lengths_t *lengths);
#endif // _di_fl_string_lengths_increase_

/**
 * Resize the string lengths array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but the requested length is too large for the buffer.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_fl_string_lengths_increase_by_
  extern f_return_status fl_string_lengths_increase_by(const f_array_length_t amount, f_string_lengths_t *lengths);
#endif // _di_fl_string_lengths_increase_by_

/**
 * Resize the string maps array to a smaller size, by 1.
 *
 * This will shrink the size by size - 1.
 * This will not shrink the size to less than 0.
 *
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_maps_decrease_
  extern f_return_status fl_string_maps_decrease(f_string_maps_t *maps);
#endif // _di_fl_string_maps_decrease_

/**
 * Resize the string maps array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_maps_decrease_by_
  extern f_return_status fl_string_maps_decrease_by(const f_array_length_t amount, f_string_maps_t *maps);
#endif // _di_fl_string_maps_decrease_by_

/**
 * Increase the size of the string maps array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but the requested length is too large for the buffer.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_fl_string_maps_increase_
  extern f_return_status fl_string_maps_increase(f_string_maps_t *maps);
#endif // _di_fl_string_maps_increase_

/**
 * Resize the string maps array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param maps
 *   The string maps array to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but the requested length is too large for the buffer.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_fl_string_maps_increase_by_
  extern f_return_status fl_string_maps_increase_by(const f_array_length_t amount, f_string_maps_t *maps);
#endif // _di_fl_string_maps_increase_by_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_mash_
  extern f_return_status fl_string_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_mash_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_mash_nulless_
  extern f_return_status fl_string_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_mash_nulless_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_mish_
  extern f_return_status fl_string_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_mish_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_mish_nulless_
  extern f_return_status fl_string_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_mish_nulless_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_prepend_
  extern f_return_status fl_string_prepend(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_prepend_assure_
  extern f_return_status fl_string_prepend_assure(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_prepend_assure_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_prepend_assure_nulless_
  extern f_return_status fl_string_prepend_assure_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_prepend_assure_nulless_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_prepend_nulless_
  extern f_return_status fl_string_prepend_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_prepend_nulless_

/**
 * Allocate a new string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested length.
 *
 * @param source
 *   The string to rip from.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_rip_
  extern f_return_status fl_string_rip(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_rip_

/**
 * Allocate a new string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested length.
 *
 * Skips over NULL characters from source when ripping.
 *
 * @param source
 *   The string to rip from.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_rip_nulless_
  extern f_return_status fl_string_rip_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_rip_nulless_

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
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_seek_line_to_
  extern f_return_status fl_string_seek_line_to(const f_string_t string, const int8_t seek_to, f_string_range_t *range);
#endif // _di_fl_string_seek_line_to_

/**
 * Seek the string location forward until the character (up to 4-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_data_not_stop if range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *
 * @see f_utf_char_to_character()
 */
#ifndef _di_fl_string_seek_line_to_utf_character_
  extern f_return_status fl_string_seek_line_to_utf_character(const f_string_t string, const f_utf_character_t seek_to, f_string_range_t *range);
#endif // _di_fl_string_seek_line_to_utf_character_

/**
 * Increment string location until a graph character (including UTF-8) or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_data_not_stop if range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_fl_string_seek_line_until_graph_
  extern f_return_status fl_string_seek_line_until_graph(const f_string_t string, const int8_t placeholder, f_string_range_t *range);
#endif // _di_fl_string_seek_line_until_graph_

/**
 * Increment string location until a non-graph character (including UTF-8) or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_seek_line_until_non_graph_
  extern f_return_status fl_string_seek_line_until_non_graph(const f_string_t string, const int8_t placeholder, f_string_range_t *range);
#endif // _di_fl_string_seek_line_until_non_graph_

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
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_seek_to_
  extern f_return_status fl_string_seek_to(const f_string_t string, const int8_t seek_to, f_string_range_t *range);
#endif // _di_fl_string_seek_to_

/**
 * Seek the string location forward until the UTF-8 character (up to 4-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *
 * @see f_utf_char_to_character()
 */
#ifndef _di_fl_string_seek_to_utf_character_
  extern f_return_status fl_string_seek_to_utf_character(const f_string_t string, const f_utf_character_t seek_to, f_string_range_t *range);
#endif // _di_fl_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_string_h
