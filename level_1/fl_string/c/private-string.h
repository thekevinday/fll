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
 * Private implementation of fl_string_append().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   Length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source length is 0.
 *   F_memory_allocation (with error bit) on memory allocation error.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_string_dynamic_t_resize().
 *
 * @see memcpy()
 *
 * @see f_macro_string_dynamic_t_resize()
 * @see fl_string_append()
 * @see fl_string_dynamic_append()
 * @see fl_string_dynamic_mash()
 * @see fl_string_mash()
 */
#if !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_) || !defined(_di_fl_string_dynamic_mash_) || !defined(_di_fl_string_mash_)
  extern f_status_t private_fl_string_append(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_) || !defined(_di_fl_string_dynamic_mash_) || !defined(_di_fl_string_mash_)

/**
 * Private implementation of fl_string_append_nulless().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   Length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_string_dynamic_t_resize().
 *
 * @see memcpy()
 *
 * @see f_macro_string_dynamic_t_resize()
 * @see fl_string_append_nulless()
 * @see fl_string_dynamic_append_nulless()
 * @see fl_string_dynamic_mash_nulless()
 * @see fl_string_mash_nulless()
 */
#if !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_) || !defined(_di_fl_string_mash_nulless_)
  extern f_status_t private_fl_string_append_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_) || !defined(_di_fl_string_mash_nulless_)

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
  extern f_status_t private_fl_string_compare(const f_string_t string1, const f_string_t string2, const f_string_length_t offset1, const f_string_length_t offset2, const f_string_length_t stop1, const f_string_length_t stop2) f_gcc_attribute_visibility_internal;
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
  extern f_status_t private_fl_string_compare_except(const f_string_t string1, const f_string_t string2, const f_string_length_t offset1, const f_string_length_t offset2, const f_string_length_t stop1, const f_string_length_t stop2, const f_string_lengths_t except1, const f_string_lengths_t except2) f_gcc_attribute_visibility_internal;
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
  extern f_status_t private_fl_string_compare_except_trim(const f_string_t string1, const f_string_t string2, const f_string_length_t offset1, const f_string_length_t offset2, const f_string_length_t stop1, const f_string_length_t stop2, const f_string_lengths_t except1, const f_string_lengths_t except2) f_gcc_attribute_visibility_internal;
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
  extern f_status_t private_fl_string_compare_trim(const f_string_t string1, const f_string_t string2, const f_string_length_t offset1, const f_string_length_t offset2, const f_string_length_t stop1, const f_string_length_t stop2) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_compare_trim_) || !defined(_di_fl_string_dynamic_compare_trim_) || !defined(_di_fl_string_dynamic_partial_compare_trim_)

/**
 * Private implementation of fl_string_dynamic_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param string
 *   The string to delete.
 *
 * @see fl_string_dynamic_decrease()
 * @see fl_string_dynamic_decrease_by()
 * @see fl_string_dynamic_delete()
 */
#if !defined(_di_fl_string_dynamic_decrease_) || !defined(_di_fl_string_dynamic_decrease_by_) || !defined(_di_fl_string_dynamic_delete_)
  extern void private_fl_string_dynamic_delete(f_string_dynamic_t *string) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_dynamic_decrease_) || !defined(_di_fl_string_dynamic_decrease_by_) || !defined(_di_fl_string_dynamic_delete_)

/**
 * Private implementation of fl_string_dynamic_increase_by().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param string
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_macro_string_dynamic_t_resize().
 *
 * @see memcpy()
 *
 * @see fl_string_append()
 * @see fl_string_append_mash()
 * @see fl_string_append_nulless()
 * @see fl_string_dynamic_append()
 * @see fl_string_dynamic_append_nulless()
 * @see fl_string_dynamic_increase_by()
 * @see fl_string_dynamic_mash()
 * @see fl_string_dynamic_mash_nulless()
 * @see fl_string_dynamic_prepend()
 * @see fl_string_dynamic_prepend_nulless()
 * @see fl_string_mash_nulless()
 * @see fl_string_prepend()
 * @see fl_string_prepend_nulless()
 */
#if !defined(_di_fl_string_dynamic_increase_by_) || !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_) || !defined(_di_fl_string_append_mash_) || !defined(_di_fl_string_dynamic_mash_) || !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_mash_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_) || !defined(_di_fl_string_prepend_) || !defined(_di_fl_string_dynamic_prepend_) || !defined(_di_fl_string_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_)
  extern f_status_t private_fl_string_dynamic_increase_by(const f_string_length_t amount, f_string_dynamic_t *string) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_dynamic_increase_by_) || !defined(_di_fl_string_append_) || !defined(_di_fl_string_dynamic_append_) || !defined(_di_fl_string_append_mash_) || !defined(_di_fl_string_dynamic_mash_) || !defined(_di_fl_string_append_nulless_) || !defined(_di_fl_string_dynamic_append_nulless_) || !defined(_di_fl_string_mash_nulless_) || !defined(_di_fl_string_dynamic_mash_nulless_) || !defined(_di_fl_string_prepend_) || !defined(_di_fl_string_dynamic_prepend_) || !defined(_di_fl_string_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param string
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_string_dynamic_t_resize().
 *
 * @see f_macro_string_dynamic_t_resize()
 * @see fl_string_dynamic_decrease()
 * @see fl_string_dynamic_decrease_by()
 * @see fl_string_dynamic_increase()
 * @see fl_string_dynamic_increase_by()
 * @see fl_string_dynamic_terminate()
 * @see fl_string_dynamic_terminate_after()
 */
#if !defined(_di_fl_string_dynamic_decrease_) || !defined(_di_fl_string_dynamic_decrease_by_) || !defined(_di_fl_string_dynamic_increase_) || !defined(_di_fl_string_dynamic_increase_by_) || !defined(_di_fl_string_dynamic_terminate_) || !defined(_di_fl_string_dynamic_terminate_after_)
  extern f_status_t private_fl_string_dynamic_resize(const f_string_length_t length, f_string_dynamic_t *string) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_dynamic_decrease_) || !defined(_di_fl_string_dynamic_decrease_by_) || !defined(_di_fl_string_dynamic_increase_) || !defined(_di_fl_string_dynamic_increase_by_) || !defined(_di_fl_string_dynamic_terminate_) || !defined(_di_fl_string_dynamic_terminate_after_)

/**
 * Private implementation of fl_string_dynamics_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param strings
 *   The strings to delete.
 *
 * @see fl_string_dynamics_decrease()
 * @see fl_string_dynamics_decrease_by()
 * @see fl_string_dynamics_delete()
 */
#if !defined(_di_fl_string_dynamics_decrease_) || !defined(_di_fl_string_dynamics_decrease_by_) || !defined(_di_fl_string_dynamics_delete_)
  extern void private_fl_string_dynamics_delete(f_string_dynamics_t *strings) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_dynamics_decrease_) || !defined(_di_fl_string_dynamics_decrease_by_) || !defined(_di_fl_string_dynamics_delete_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param strings
 *   The strings to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_string_dynamics_t_resize().
 *
 * @see f_macro_string_dynamics_t_resize()
 * @see fl_string_dynamics_decrease()
 * @see fl_string_dynamics_decrease_by()
 * @see fl_string_dynamics_increase()
 * @see fl_string_dynamics_increase_by()
 * @see fl_string_dynamics_terminate()
 * @see fl_string_dynamics_terminate_after()
 */
#if !defined(_di_fl_string_dynamics_decrease_) || !defined(_di_fl_string_dynamics_decrease_by_) || !defined(_di_fl_string_dynamics_increase_) || !defined(_di_fl_string_dynamics_increase_by_) || !defined(_di_fl_string_dynamics_terminate_) || !defined(_di_fl_string_dynamics_terminate_after_)
  extern f_status_t private_fl_string_dynamics_resize(const f_string_length_t length, f_string_dynamics_t *strings) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_dynamics_decrease_) || !defined(_di_fl_string_dynamics_decrease_by_) || !defined(_di_fl_string_dynamics_increase_) || !defined(_di_fl_string_dynamics_increase_by_) || !defined(_di_fl_string_dynamics_terminate_) || !defined(_di_fl_string_dynamics_terminate_after_)

/**
 * Private implementation of fl_string_maps_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param maps
 *   The maps to delete.
 *
 * @see fl_string_maps_decrease()
 * @see fl_string_maps_decrease_by()
 * @see fl_string_maps_delete()
 */
#if !defined(fl_string_maps_decrease) || !defined(fl_string_maps_decrease_by) || !defined(_di_fl_string_maps_delete_)
  extern void private_fl_string_maps_delete(f_string_maps_t *maps) f_gcc_attribute_visibility_internal;
#endif // !defined(fl_string_maps_decrease) || !defined(fl_string_maps_decrease_by) || !defined(_di_fl_string_maps_delete_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param maps
 *   The maps to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_string_maps_t_resize().
 *
 * @see f_macro_string_dynamic_t_resize()
 * @see fl_string_maps_decrease()
 * @see fl_string_maps_decrease_by()
 * @see fl_string_maps_increase()
 * @see fl_string_maps_increase_by()
 * @see fl_string_maps_terminate()
 * @see fl_string_maps_terminate_after()
 */
#if !defined(_di_fl_string_maps_decrease_) || !defined(_di_fl_string_maps_decrease_by_) || !defined(_di_fl_string_maps_increase_) || !defined(_di_fl_string_maps_increase_by_) || !defined(_di_fl_string_maps_terminate_) || !defined(_di_fl_string_maps_terminate_after_)
  extern f_status_t private_fl_string_maps_resize(const f_string_length_t length, f_string_maps_t *maps) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_maps_decrease_) || !defined(_di_fl_string_maps_decrease_by_) || !defined(_di_fl_string_maps_increase_) || !defined(_di_fl_string_maps_increase_by_) || !defined(_di_fl_string_maps_terminate_) || !defined(_di_fl_string_maps_terminate_after_)

/**
 * Private implementation of fl_string_prepend().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   Length of source to append.
 * @param destination
 *   The destination string the source and glue are prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_macro_string_dynamic_t_resize().
 *
 * @see memcopy()
 * @see memmove()
 *
 * @see fl_string_dynamic_mish()
 * @see fl_string_dynamic_partial_mish()
 * @see fl_string_dynamic_partial_prepend_assure()
 * @see fl_string_dynamic_partial_prepend()
 * @see fl_string_dynamic_prepend_assure()
 * @see fl_string_dynamic_prepend()
 * @see fl_string_mish()
 * @see fl_string_prepend_assure()
 * @see fl_string_prepend()
 */
#if !defined(_di_fl_string_dynamic_mish_) || !defined(_di_fl_string_dynamic_partial_mish_) || !defined(_di_fl_string_dynamic_partial_prepend_assure_) || !defined(_di_fl_string_dynamic_partial_prepend_) || !defined(_di_fl_string_dynamic_prepend_assure_) || !defined(_di_fl_string_dynamic_prepend_) || !defined(_di_fl_string_mish_) || !defined(_di_fl_string_prepend_assure_) || !defined(_di_fl_string_prepend_)
  extern f_status_t private_fl_string_prepend(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_dynamic_mish_) || !defined(_di_fl_string_dynamic_partial_mish_) || !defined(_di_fl_string_dynamic_partial_prepend_assure_) || !defined(_di_fl_string_dynamic_partial_prepend_) || !defined(_di_fl_string_dynamic_prepend_assure_) || !defined(_di_fl_string_dynamic_prepend_) || !defined(_di_fl_string_mish_) || !defined(_di_fl_string_prepend_assure_) || !defined(_di_fl_string_prepend_)

/**
 * Private implementation of fl_string_prepend_nulless().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   Length of source to append.
 * @param destination
 *   The destination string the source and glue are prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_macro_string_dynamic_t_resize().
 *
 * @see memcopy()
 * @see memmove()
 *
 * @see fl_string_dynamic_mish_nulless()
 * @see fl_string_dynamic_partial_mish_nulless()
 * @see fl_string_dynamic_partial_prepend_assure_nulless()
 * @see fl_string_dynamic_partial_prepend_nulless()
 * @see fl_string_dynamic_prepend_assure_nulless()
 * @see fl_string_dynamic_prepend_nulless()
 * @see fl_string_mish_nulless()
 * @see fl_string_prepend_assure_nulless()
 * @see fl_string_prepend_nulless()
 */
#if !defined(_di_fl_string_dynamic_mish_nulless_) || !defined(_di_fl_string_dynamic_partial_mish_nulless_) || !defined(_di_fl_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_fl_string_dynamic_partial_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_assure_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_) || !defined(_di_fl_string_mish_nulless_) || !defined(_di_fl_string_prepend_assure_nulless_) || !defined(_di_fl_string_prepend_nulless_)
  extern f_status_t private_fl_string_prepend_nulless(const f_string_t source, f_string_length_t length, f_string_dynamic_t *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_dynamic_mish_nulless_) || !defined(_di_fl_string_dynamic_partial_mish_nulless_) || !defined(_di_fl_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_fl_string_dynamic_partial_prepend_nulless_) || !defined(_di_fl_string_dynamic_prepend_assure_nulless_) || !defined(_di_fl_string_dynamic_prepend_nulless_) || !defined(_di_fl_string_mish_nulless_) || !defined(_di_fl_string_prepend_assure_nulless_) || !defined(_di_fl_string_prepend_nulless_)

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
 * @see fl_string_dynamic_rip()
 * @see fl_string_rip()
 * @see fl_string_rip_nulless()
 * @see fl_string_dynamic_rip_nulless()
 */
#if !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)
  extern f_status_t private_fl_string_rip_find_range(const f_string_t source, f_string_length_t *start, f_string_length_t *stop) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_string_rip_) || !defined(_di_fl_string_dynamic_rip_) || !defined(_di_fl_string_rip_nulless_) || !defined(_di_fl_string_dynamic_rip_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_string_h
