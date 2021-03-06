/**
 * FLL - Level 1
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FL_string_h
#define _PRIVATE_FL_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fl_string_compare().
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
 * @see fl_string_compare()
 * @see fl_string_dynamic_compare()
 * @see fl_string_dynamic_partial_compare()
 */
#if !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)
  extern f_status_t private_fl_string_compare(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)

/**
 * Private implementation of fl_string_compare_except().
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
 * @see fl_string_compare_except()
 * @see fl_string_dynamic_compare_except()
 * @see fl_string_dynamic_partial_compare_except()
 */
#if !defined(_di_fl_string_compare_except_) || !defined(_di_fl_string_dynamic_compare_except_) || !defined(_di_fl_string_dynamic_partial_compare_except_)
  extern f_status_t private_fl_string_compare_except(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2, const f_array_lengths_t except1, const f_array_lengths_t except2) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_compare_except_) || !defined(_di_fl_string_dynamic_compare_except_) || !defined(_di_fl_string_dynamic_partial_compare_except_)

/**
 * Private implementation of fl_string_compare_except_trim().
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
 *   F_utf (with error bit) if a character is not valid UTF-8.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 * @see fl_string_compare_except_trim()
 * @see fl_string_dynamic_compare_except_trim()
 * @see fl_string_dynamic_partial_compare_except_trim()
 */
#if !defined(_di_fl_string_compare_except_trim_) || !defined(_di_fl_string_dynamic_compare_except_trim_) || !defined(_di_fl_string_dynamic_partial_compare_except_trim_)
  extern f_status_t private_fl_string_compare_except_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2, const f_array_lengths_t except1, const f_array_lengths_t except2) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_compare_except_trim_) || !defined(_di_fl_string_dynamic_compare_except_trim_) || !defined(_di_fl_string_dynamic_partial_compare_except_trim_)

/**
 * Private implementation of fl_string_compare_trim().
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
 *   F_utf (with error bit) if a character is not valid UTF-8.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_whitespace()
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_compare_trim()
 * @see fl_string_dynamic_partial_compare_trim()
 */
#if !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)
  extern f_status_t private_fl_string_compare_trim(const f_string_t string1, const f_string_t string2, const f_array_length_t offset1, const f_array_length_t offset2, const f_array_length_t stop1, const f_array_length_t stop2) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)

/**
 * Private implementation of fl_string_rip(), but only the part for finding the start/stop range.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The string to rip from.
 * @param start
 *   Inclusive start point of string to rip.
 *   Will be updated to reflect the new start range.
 * @param stop
 *   Inclusive stop point of string to rip.
 *   Will be updated to reflect the new stop range.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but only whitespace found.
 *
 *   F_utf (with error bit) if a character is not valid UTF-8.
 *
 *   Errors (with error bit) from: f_utf_is_whitespace().
 *
 * @see fl_string_rip()
 * @see fl_string_rip_nulless()
 * @see fl_string_dynamic_rip()
 * @see fl_string_dynamic_rip_nulless()
 */
#if !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)
  extern f_status_t private_fl_string_rip_find_range(const f_string_t source, f_array_length_t *start, f_array_length_t *stop) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_string_h
