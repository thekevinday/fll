/**
 * FLL - Level 1
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides basic string manipulation and processing capabilities.
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
 *   f_equal_to when both strings equal.
 *   f_not_equal_to when both strings do not equal.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_compare()
 * @see fl_string_dynamic_compare()
 * @see fl_string_dynamic_partial_compare()
 */
#if !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)
  extern f_return_status private_fl_string_compare(const f_string string1, const f_string string2, const f_string_length offset1, const f_string_length offset2, const f_string_length stop1, const f_string_length stop2) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_compare_) || !defined(_di_fl_string_dynamic_compare_) || !defined(_di_fl_string_dynamic_partial_compare_)

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
 *   f_equal_to when both strings equal.
 *   f_not_equal_to when both strings do not equal.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_compare_trim()
 * @see fl_string_dynamic_partial_compare_trim()
 */
#if !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)
  extern f_return_status private_fl_string_compare_trim(const f_string string1, const f_string string2, const f_string_length offset1, const f_string_length offset2, const f_string_length stop1, const f_string_length stop2) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)

/**
 * Private implementation of fl_string_mash().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param source_length
 *   Total number of bytes to copy from source string.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   f_none on success.
 *   f_string_max_size (with error bit) if the combined string is too large.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_mash()
 * @see fl_string_dynamic_mash()
 * @see fl_string_dynamic_partial_mash()
 */
#if !defined(_di_fl_string_mash_) || !defined(_di_fl_string_dynamic_mash_) || !defined(_di_fl_string_dynamic_partial_mash_)
  extern f_return_status private_fl_string_mash(const f_string glue, const f_string_length glue_length, const f_string source, const f_string_length source_length, f_string_dynamic *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_mash_) || !defined(_di_fl_string_dynamic_mash_) || !defined(_di_fl_string_dynamic_partial_mash_)

/**
 * Private implementation of fl_string_rip().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to rip from.
 * @param start
 *   Inclusive start point of string to rip.
 * @param stop
 *   Inclusive stop point of string to rip.
 * @param result
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   f_none on success.
 *   f_no_data if nothing to rip, no allocations or reallocations are performed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_rip()
 * @see fl_string_rip()
 */
#if !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_)
  extern f_return_status private_fl_string_rip(const f_string string, const f_string_length start, const f_string_length stop, f_string_dynamic *result) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_)

/**
 * Private implementation of fl_string_rip_trim().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to rip from.
 * @param start
 *   Inclusive start point of string to rip.
 * @param stop
 *   Inclusive stop point of string to rip.
 * @param result
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   f_none on success.
 *   f_no_data if nothing to rip, no allocations or reallocations are performed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_rip()
 * @see fl_string_rip()
 */
#if !defined(_di_fl_string_rip_trim_) || !defined(_di_fl_string_dynamic_rip_trim_)
  extern f_return_status private_fl_string_rip_trim(const f_string string, const f_string_length start, const f_string_length stop, f_string_dynamic *result) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_rip_trim_) || !defined(_di_fl_string_dynamic_rip_trim_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_string_h
