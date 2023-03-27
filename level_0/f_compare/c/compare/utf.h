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
  extern f_status_t f_compare_utf(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t length1, const f_array_length_t length2);
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
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_trim_
  extern f_status_t f_compare_utf_dynamic_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2);
#endif // _di_f_compare_utf_dynamic_trim_

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
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_f_compare_utf_dynamic_partial_trim_
  extern f_status_t f_compare_utf_dynamic_partial_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_string_range_t range1, const f_string_range_t range2);
#endif // _di_f_compare_utf_dynamic_partial_trim_

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
  extern f_status_t f_compare_utf_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t length1, const f_array_length_t length2);
#endif // _di_f_compare_utf_trim_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_compare_utf_h
