/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_number_unsigned_h
#define _PRIVATE_F_type_array_number_unsigned_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the number array.
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
 * @see f_number_unsigneds_adjust()
 * @see f_number_unsigneds_decimate_by()
 */
#if !defined(_di_f_number_unsigneds_adjust_) || !defined(_di_f_number_unsigneds_decimate_by_)
  extern f_status_t private_f_number_unsigneds_adjust(const f_number_unsigned_t length, f_number_unsigneds_t *lengths) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_number_unsigneds_adjust_) || !defined(_di_f_number_unsigneds_decimate_by_)

/**
 * Private implementation for appending the number array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source number_unsigned to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_number_unsigneds_append()
 * @see f_number_unsignedss_append()
 */
#if !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsignedss_append_)
  extern f_status_t private_f_number_unsigneds_append(const f_number_unsigned_t source, f_number_unsigneds_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsignedss_append_)

/**
 * Private implementation for appending the number array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source number_unsigneds to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_number_unsigneds_append_all()
 * @see f_number_unsignedss_append()
 * @see f_number_unsignedss_append_all()
 */
#if !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsigneds_append_all_) || !defined(_di_f_number_unsignedss_append_all_)
  extern f_status_t private_f_number_unsigneds_append_all(const f_number_unsigneds_t source, f_number_unsigneds_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsigneds_append_all_) || !defined(_di_f_number_unsignedss_append_all_)

/**
 * Private implementation for resizing the number array.
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
 * @see f_number_unsigneds_resize()
 * @see f_number_unsigneds_append()
 * @see f_number_unsigneds_decrease_by()
 * @see f_number_unsignedss_append()
 */
#if !defined(_di_f_number_unsigneds_resize_) || !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsigneds_decrease_by_) || !defined(_di_f_number_unsignedss_append_)
  extern f_status_t private_f_number_unsigneds_resize(const f_number_unsigned_t length, f_number_unsigneds_t *lengths) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_number_unsigneds_resize_) || !defined(_di_f_number_unsigneds_append_) || !defined(_di_f_number_unsigneds_decrease_by_) || !defined(_di_f_number_unsignedss_append_)

/**
 * Private implementation for resizing the number array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param lengthss
 *   The number array to adjust.
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
 * @see f_number_unsignedss_adjust()
 * @see f_number_unsignedss_decimate_by()
 */
#if !defined(_di_f_number_unsignedss_adjust_) || !defined(_di_f_number_unsignedss_decimate_by_)
  extern f_status_t private_f_number_unsignedss_adjust(const f_number_unsigned_t length, f_number_unsignedss_t *lengthss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_number_unsignedss_adjust_) || !defined(_di_f_number_unsignedss_decimate_by_)

/**
 * Private implementation for resizing the number array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param lengthss
 *   The number array to resize.
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
 * @see f_number_unsignedss_decrease_by()
 * @see f_number_unsignedss_increase()
 * @see f_number_unsignedss_increase_by()
 * @see f_number_unsignedss_resize()
 */
#if !defined(_di_f_number_unsignedss_decrease_by_) || !defined(_di_f_number_unsignedss_increase_) || !defined(_di_f_number_unsignedss_increase_by_) || !defined(_di_f_number_unsignedss_resize_)
  extern f_status_t private_f_number_unsignedss_resize(const f_number_unsigned_t length, f_number_unsignedss_t *lengthss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_number_unsignedss_decrease_by_) || !defined(_di_f_number_unsignedss_increase_) || !defined(_di_f_number_unsignedss_increase_by_) || !defined(_di_f_number_unsignedss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_number_unsigned_h
