/**
 * FLL - Level 0
 *
 * Project: Compare
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_compare_utf_h
#define _PRIVATE_F_compare_utf_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_compare().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param offset1
 *   Offset of string1 to start at.
 * @param offset2
 *   Offset of string2 to start at.
 * @param stop1
 *   Exclusive stop position for string1.
 * @param stop2
 *   Exclusive stop position for string2.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 * @see f_compare_utf()
 * @see f_compare_utf_dynamic()
 * @see f_compare_utf_dynamic_string()
 * @see f_compare_utf_dynamic_partial()
 * @see f_compare_utf_dynamic_partial_dynamic()
 * @see f_compare_utf_dynamic_partial_string()
 */
#if !defined(_di_f_compare_utf_) || !defined(_di_f_compare_utf_dynamic_) || !defined(_di_f_compare_utf_dynamic_string_) || !defined(_di_f_compare_utf_dynamic_partial_) || !defined(_di_f_compare_utf_dynamic_partial_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_string_)
  extern f_status_t private_f_compare_utf(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_compare_utf_) || !defined(_di_f_compare_utf_dynamic_) || !defined(_di_f_compare_utf_dynamic_string_) || !defined(_di_f_compare_utf_dynamic_partial_) || !defined(_di_f_compare_utf_dynamic_partial_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_string_)

/**
 * Private implementation of f_compare_utf_except().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param offset1
 *   Offset of string1 to start at.
 * @param offset2
 *   Offset of string2 to start at.
 * @param stop1
 *   Exclusive stop position for string1.
 * @param stop2
 *   Exclusive stop position for string2.
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
 * @see f_compare_utf_dynamic_except()
 * @see f_compare_utf_dynamic_except_string()
 * @see f_compare_utf_dynamic_partial_except()
 * @see f_compare_utf_dynamic_partial_except_dynamic()
 * @see f_compare_utf_dynamic_partial_except_string()
 * @see f_compare_utf_except_
 */
#if !defined(_di_f_compare_utf_dynamic_except_) || !defined(_di_f_compare_utf_dynamic_except_string_) || !defined(_di_f_compare_utf_dynamic_partial_except_) || !defined(_di_f_compare_utf_dynamic_partial_except_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_except_string_) || !defined(_di_f_compare_utf_except_)
  extern f_status_t private_f_compare_utf_except(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2, const f_array_lengths_t except1, const f_array_lengths_t except2) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_compare_utf_dynamic_except_) || !defined(_di_f_compare_utf_dynamic_except_string_) || !defined(_di_f_compare_utf_dynamic_partial_except_) || !defined(_di_f_compare_utf_dynamic_partial_except_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_except_string_) || !defined(_di_f_compare_utf_except_)

/**
 * Private implementation of f_compare_utf_except_trim().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param offset1
 *   Offset of string1 to start at.
 * @param offset2
 *   Offset of string2 to start at.
 * @param stop1
 *   Exclusive stop position for string1.
 * @param stop2
 *   Exclusive stop position for string2.
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
 *   F_utf_not (with error bit) if a character is not valid UTF-8.
 *
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 *
 * @see f_compare_utf_dynamic_except_trim()
 * @see f_compare_utf_dynamic_except_trim_string()
 * @see f_compare_utf_dynamic_partial_except_trim()
 * @see f_compare_utf_dynamic_partial_except_trim_dynamic()
 * @see f_compare_utf_dynamic_partial_except_trim_string()
 * @see f_compare_utf_except_trim()
 */
#if !defined(_di_f_compare_utf_dynamic_except_trim_) || !defined(_di_f_compare_utf_dynamic_except_trim_string_) || !defined(_di_f_compare_utf_dynamic_partial_except_trim_) || !defined(_di_f_compare_utf_dynamic_partial_except_trim_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_except_trim_string_) || !defined(_di_f_compare_utf_except_trim_)
  extern f_status_t private_f_compare_utf_except_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2, const f_array_lengths_t except1, const f_array_lengths_t except2) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_compare_utf_dynamic_except_trim_) || !defined(_di_f_compare_utf_dynamic_except_trim_string_) || !defined(_di_f_compare_utf_dynamic_partial_except_trim_) || !defined(_di_f_compare_utf_dynamic_partial_except_trim_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_except_trim_string_) || !defined(_di_f_compare_utf_except_trim_)

/**
 * Private implementation of f_compare_utf_trim().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param offset1
 *   Offset of string1 to start at.
 * @param offset2
 *   Offset of string2 to start at.
 * @param stop1
 *   Exclusive stop position for string1.
 * @param stop2
 *   Exclusive stop position for string2.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 *   F_utf_not (with error bit) if a character is not valid UTF-8.
 *
 *   Errors (with error bit) from: f_utf_character_is_combining().
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_combining()
 * @see f_utf_character_is_whitespace()
 *
 * @see f_compare_utf_dynamic_trim()
 * @see f_compare_utf_dynamic_trim_string()
 * @see f_compare_utf_dynamic_partial_trim()
 * @see f_compare_utf_dynamic_partial_trim_dynamic()
 * @see f_compare_utf_dynamic_partial_trim_string()
 * @see f_compare_utf_trim()
 */
#if !defined(_di_f_compare_utf_dynamic_trim_) || !defined(_di_f_compare_utf_dynamic_trim_string_) || !defined(_di_f_compare_utf_dynamic_partial_trim_) || !defined(_di_f_compare_utf_dynamic_partial_trim_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_trim_string_) || !defined(_di_f_compare_utf_trim_)
  extern f_status_t private_f_compare_utf_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_compare_utf_dynamic_trim_) || !defined(_di_f_compare_utf_dynamic_trim_string_) || !defined(_di_f_compare_utf_dynamic_partial_trim_) || !defined(_di_f_compare_utf_dynamic_partial_trim_dynamic_) || !defined(_di_f_compare_utf_dynamic_partial_trim_string_) || !defined(_di_f_compare_utf_trim_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_compare_utf_h
