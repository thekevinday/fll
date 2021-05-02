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
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_compare_
  extern f_status_t fl_string_compare(const f_string_t string1, const f_string_t string2, const f_array_length_t length1, const f_array_length_t length2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_compare_except_
  extern f_status_t fl_string_compare_except(const f_string_t string1, const f_string_t string2, const f_array_length_t length1, const f_array_length_t length2, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_compare_except_trim_
  extern f_status_t fl_string_compare_except_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t length1, const f_array_length_t length2, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_compare_trim_
  extern f_status_t fl_string_compare_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t length1, const f_array_length_t length2);
#endif // _di_fl_string_compare_trim_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_compare_
  extern f_status_t fl_string_dynamic_compare(const f_string_static_t string1, const f_string_static_t string2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_compare_except_
  extern f_status_t fl_string_dynamic_compare_except(const f_string_static_t string1, const f_string_static_t string2, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_except_string_
  extern f_status_t fl_string_dynamic_compare_except_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_except_trim_
  extern f_status_t fl_string_dynamic_compare_except_trim(const f_string_static_t string1, const f_string_static_t string2, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_except_trim_string_
  extern f_status_t fl_string_dynamic_compare_except_trim_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_string_
  extern f_status_t fl_string_dynamic_compare_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_trim_
  extern f_status_t fl_string_dynamic_compare_trim(const f_string_static_t string1, const f_string_static_t string2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_compare_trim_string_
  extern f_status_t fl_string_dynamic_compare_trim_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1);
#endif // _di_fl_string_dynamic_compare_trim_string_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_
  extern f_status_t fl_string_dynamic_partial_compare(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_dynamic_
  extern f_status_t fl_string_dynamic_partial_compare_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_dynamic_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_
  extern f_status_t fl_string_dynamic_partial_compare_except(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_dynamic_
  extern f_status_t fl_string_dynamic_partial_compare_except_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_string_
  extern f_status_t fl_string_dynamic_partial_compare_except_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_string_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_trim_
  extern f_status_t fl_string_dynamic_partial_compare_except_trim(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_trim_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_trim_dynamic_
  extern f_status_t fl_string_dynamic_partial_compare_except_trim_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_except_trim_string_
  extern f_status_t fl_string_dynamic_partial_compare_except_trim_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_string_range_t range2, const f_array_lengths_t except1, const f_array_lengths_t except2);
#endif // _di_fl_string_dynamic_partial_compare_except_trim_string_

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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_partial_compare_string_
  extern f_status_t fl_string_dynamic_partial_compare_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_string_range_t range2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_trim_dynamic_
  extern f_status_t fl_string_dynamic_partial_compare_trim_dynamic(const f_string_static_t string1, const f_string_static_t string2, const f_string_range_t range2);
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_dynamic_partial_compare_trim_string_
  extern f_status_t fl_string_dynamic_partial_compare_trim_string(const f_string_t string1, const f_string_static_t string2, const f_array_length_t length1, const f_string_range_t range2);
#endif // _di_fl_string_dynamic_partial_compare_trim_string_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
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
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_string_dynamic_rip_
  extern f_status_t fl_string_dynamic_rip(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_rip_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
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
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_string_dynamic_rip_nulless_
  extern f_status_t fl_string_dynamic_rip_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_fl_string_dynamic_rip_nulless_

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
 *
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
  extern f_status_t fl_string_dynamic_seek_line_to_utf_character(const f_string_t string, const f_utf_character_t seek_to_this, f_string_range_t *range);
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
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_fl_string_dynamic_seek_line_until_graph_
  extern f_status_t fl_string_dynamic_seek_line_until_graph(const f_string_t string, const uint8_t placeholder, f_string_range_t *range);
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
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_fl_string_dynamic_seek_line_until_graph_non_
  extern f_status_t fl_string_dynamic_seek_line_until_graph_non(const f_string_t string, const uint8_t placeholder, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_line_until_graph_non_

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
 *
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
  extern f_status_t fl_string_dynamic_seek_to_utf_character(const f_string_t string, const f_utf_character_t seek_to_this, f_string_range_t *range);
#endif // _di_fl_string_dynamic_seek_to_utf_character_

/**
 * Allocate a new string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
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
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_rip_
  extern f_status_t fl_string_rip(const f_string_t source, const f_array_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_rip_

/**
 * Allocate a new string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * Ignores leading and trailing NULL characters.
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
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_rip_nulless_
  extern f_status_t fl_string_rip_nulless(const f_string_t source, const f_array_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_string_rip_nulless_

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
 *
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
  extern f_status_t fl_string_seek_line_to_utf_character(const f_string_t string, const f_utf_character_t seek_to, f_string_range_t *range);
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
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_fl_string_seek_line_until_graph_
  extern f_status_t fl_string_seek_line_until_graph(const f_string_t string, const uint8_t placeholder, f_string_range_t *range);
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
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 */
#ifndef _di_fl_string_seek_line_until_graph_non_
  extern f_status_t fl_string_seek_line_until_graph_non(const f_string_t string, const uint8_t placeholder, f_string_range_t *range);
#endif // _di_fl_string_seek_line_until_graph_non_

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
 *
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
  extern f_status_t fl_string_seek_to_utf_character(const f_string_t string, const f_utf_character_t seek_to, f_string_range_t *range);
#endif // _di_fl_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_string_h
