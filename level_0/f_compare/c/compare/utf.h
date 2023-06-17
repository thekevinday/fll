/**
 * FLL - Level 0
 *
 * Project: Compare
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides basic UTF-8 string comparison capabilities.
 */
#ifndef _F_compare_utf_h
#define _F_compare_utf_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
#ifndef _di_f_compare_utf_
  extern f_status_t f_compare_utf(const f_utf_string_t string1, const f_utf_string_t string2, const f_number_unsigned_t length1, const f_number_unsigned_t length2);
#endif // _di_f_compare_utf_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 */
#ifndef _di_f_compare_utf_dynamic_
  extern f_status_t f_compare_utf_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2);
#endif // _di_f_compare_utf_dynamic_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
#ifndef _di_f_compare_utf_dynamic_except_
  extern f_status_t f_compare_utf_dynamic_except(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_except_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_except_string_
  extern f_status_t f_compare_utf_dynamic_except_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_except_string_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_except_trim_
  extern f_status_t f_compare_utf_dynamic_except_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_except_trim_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_except_trim_string_
  extern f_status_t f_compare_utf_dynamic_except_trim_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_except_trim_string_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_string_
  extern f_status_t f_compare_utf_dynamic_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1);
#endif // _di_f_compare_utf_dynamic_string_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_trim_
  extern f_status_t f_compare_utf_dynamic_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2);
#endif // _di_f_compare_utf_dynamic_trim_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_trim_string_
  extern f_status_t f_compare_utf_dynamic_trim_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1);
#endif // _di_f_compare_utf_dynamic_trim_string_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given ranges.
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
#ifndef _di_f_compare_utf_dynamic_partial_
  extern f_status_t f_compare_utf_dynamic_partial(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2);
#endif // _di_f_compare_utf_dynamic_partial_

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
#ifndef _di_f_compare_utf_dynamic_partial_dynamic_
  extern f_status_t f_compare_utf_dynamic_partial_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range2);
#endif // _di_f_compare_utf_dynamic_partial_dynamic_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given ranges.
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
#ifndef _di_f_compare_utf_dynamic_partial_except_
  extern f_status_t f_compare_utf_dynamic_partial_except(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_partial_except_

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
#ifndef _di_f_compare_utf_dynamic_partial_except_dynamic_
  extern f_status_t f_compare_utf_dynamic_partial_except_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_partial_except_dynamic_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given range for the second string.
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
#ifndef _di_f_compare_utf_dynamic_partial_except_string_
  extern f_status_t f_compare_utf_dynamic_partial_except_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_partial_except_string_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given ranges.
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_partial_except_trim_
  extern f_status_t f_compare_utf_dynamic_partial_except_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_partial_except_trim_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given range for the second string.
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_partial_except_trim_dynamic_
  extern f_status_t f_compare_utf_dynamic_partial_except_trim_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_partial_except_trim_dynamic_

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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_partial_except_trim_string_
  extern f_status_t f_compare_utf_dynamic_partial_except_trim_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_string_range_t range2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_dynamic_partial_except_trim_string_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given range for the second string.
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
#ifndef _di_f_compare_utf_dynamic_partial_string_
  extern f_status_t f_compare_utf_dynamic_partial_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_string_range_t range2);
#endif // _di_f_compare_utf_dynamic_partial_string_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given ranges.
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_partial_trim_
  extern f_status_t f_compare_utf_dynamic_partial_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2);
#endif // _di_f_compare_utf_dynamic_partial_trim_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given range for the second string.
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_partial_trim_dynamic_
  extern f_status_t f_compare_utf_dynamic_partial_trim_dynamic(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range2);
#endif // _di_f_compare_utf_dynamic_partial_trim_dynamic_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given range for the second string.
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_partial_trim_string_
  extern f_status_t f_compare_utf_dynamic_partial_trim_string(const f_utf_string_t string1, const f_utf_string_static_t string2, const f_number_unsigned_t length1, const f_string_range_t range2);
#endif // _di_f_compare_utf_dynamic_partial_trim_string_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
#ifndef _di_f_compare_utf_except_
  extern f_status_t f_compare_utf_except(const f_utf_string_t string1, const f_utf_string_t string2, const f_number_unsigned_t length1, const f_number_unsigned_t length2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_except_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_except_trim_
  extern f_status_t f_compare_utf_except_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_number_unsigned_t length1, const f_number_unsigned_t length2, const f_number_unsigneds_t except1, const f_number_unsigneds_t except2);
#endif // _di_f_compare_utf_except_trim_

/**
 * Compare two UTF-8 strings, similar to strncmp().
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
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_trim_
  extern f_status_t f_compare_utf_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_number_unsigned_t length1, const f_number_unsigned_t length2);
#endif // _di_f_compare_utf_trim_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_compare_utf_h
