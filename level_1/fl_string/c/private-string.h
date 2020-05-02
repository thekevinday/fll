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
 * Private implementation of fl_string_append().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to append.
 * @param start
 *   Inclusive start point of string to append.
 * @param stop
 *   Inclusive stop point of string to append.
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
 * @see fl_string_append()
 * @see fl_string_mash()
 * @see fl_string_dynamic_append()
 * @see fl_string_dynamic_mash()
 */
#if !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_) || !defined(_di_fl_string_append_mash_) || !defined(_di_fl_string_dynamic_mash_)
  extern f_return_status private_fl_string_append(const f_string source, const f_string_length start, const f_string_length stop, f_string_dynamic *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_) || !defined(_di_fl_string_append_mash_) || !defined(_di_fl_string_dynamic_mash_)

/**
 * Private implementation of fl_string_append_nulless().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to append.
 * @param start
 *   Inclusive start point of string to append.
 * @param stop
 *   Inclusive stop point of string to append.
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
 * @see fl_string_append_nulless()
 * @see fl_string_mash_nulless()
 * @see fl_string_dynamic_append_nulless()
 * @see fl_string_dynamic_mash_nulless()
 */
#if !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_mash_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_)
  extern f_return_status private_fl_string_append_nulless(const f_string source, const f_string_length start, const f_string_length stop, f_string_dynamic *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_mash_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_)

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
 * Private implementation of fl_string_prepend().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to prepend.
 * @param start
 *   Inclusive start point of string to append.
 * @param stop
 *   Inclusive stop point of string to append.
 * @param destination
 *   The destination string the source and glue are prepended onto.
 *
 * @return
 *   f_none on success.
 *   f_string_max_size (with error bit) if the combined string is too large.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_prepend()
 * @see fl_string_dynamic_prepend()
 */
#if !defined(_di_fl_string_prepend_) || !defined(_di_fl_string_dynamic_prepend_) || !defined(_di_fl_string_append_mish_) || !defined(_di_fl_string_dynamic_mish_)
  extern f_return_status private_fl_string_prepend(const f_string source, const f_string_length start, const f_string_length stop, f_string_dynamic *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_prepend_) || !defined(_di_fl_string_dynamic_prepend_) || !defined(_di_fl_string_append_mish_) || !defined(_di_fl_string_dynamic_mish_)

/**
 * Private implementation of fl_string_prepend_nulless().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to prepend.
 * @param start
 *   Inclusive start point of string to append.
 * @param stop
 *   Inclusive stop point of string to append.
 * @param destination
 *   The destination string the source and glue are prepended onto.
 *
 * @return
 *   f_none on success.
 *   f_string_max_size (with error bit) if the combined string is too large.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_prepend_nulless()
 * @see fl_string_dynamic_prepend_nulless()
 */
#if !defined(_di_fl_string_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_) || !defined(_di_fl_string_append_mish_) || !defined(_di_fl_string_dynamic_mish_)
  extern f_return_status private_fl_string_prepend_nulless(const f_string source, f_string_length start, const f_string_length stop, f_string_dynamic *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_) || !defined(_di_fl_string_append_mish_) || !defined(_di_fl_string_dynamic_mish_)

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
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_rip()
 * @see fl_string_rip()
 */
#if !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)
  extern f_return_status private_fl_string_rip_find_range(const f_string source, f_string_length *start, f_string_length *stop) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_string_h
