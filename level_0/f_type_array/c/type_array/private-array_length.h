/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_array_length_h
#define _PRIVATE_F_type_array_array_length_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the array_lengths array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param lengths
 *   The lengths array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_type_array_lengths_adjust()
 * @see f_type_array_lengths_decimate_by()
 */
#if !defined(_di_f_type_array_lengths_adjust_) || !defined(_di_f_type_array_lengths_decimate_by_)
  extern f_status_t private_f_type_array_lengths_adjust(const f_array_length_t length, f_array_lengths_t *lengths) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengths_adjust_) || !defined(_di_f_type_array_lengths_decimate_by_)

/**
 * Private implementation for appending the array_length array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source array_lengths to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_array_lengths_append()
 * @see f_type_array_lengthss_append()
 */
#if !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengthss_append_)
  extern f_status_t private_f_type_array_lengths_append(const f_array_lengths_t source, f_array_lengths_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengthss_append_)

/**
 * Private implementation for resizing the array_lengths array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param lengths
 *   The lengths array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_array_lengths_resize()
 * @see f_type_array_lengths_append()
 * @see f_type_array_lengths_decimate_by()
 * @see f_type_array_lengthss_append()
 */
#if !defined(_di_f_type_array_lengths_resize_) || !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengths_decimate_by_) || !defined(_di_f_type_array_lengthss_append_)
  extern f_status_t private_f_type_array_lengths_resize(const f_array_length_t length, f_array_lengths_t *lengths) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengths_resize_) || !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengths_decimate_by_) || !defined(_di_f_type_array_lengthss_append_)

/**
 * Private implementation for resizing the lengthss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param lengthss
 *   The lengthss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 *
 * @see f_type_array_lengthss_adjust()
 * @see f_type_array_lengthss_decimate_by()
 */
#if !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)
  extern f_status_t private_f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)

/**
 * Private implementation for resizing the lengthss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param lengthss
 *   The lengthss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_type_array_lengthss_decrease_by()
 * @see f_type_array_lengthss_increase()
 * @see f_type_array_lengthss_increase_by()
 * @see f_type_array_lengthss_resize()
 */
#if !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_) || !defined(_di_f_type_array_lengthss_resize_)
  extern f_status_t private_f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_) || !defined(_di_f_type_array_lengthss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_array_length_h
