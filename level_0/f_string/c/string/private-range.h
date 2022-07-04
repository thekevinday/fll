/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_string_range_h
#define _PRIVATE_F_string_range_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param ranges
 *   The ranges to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_ranges_adjust()
 */
#if !defined(_di_f_string_ranges_adjust_) || !defined(_di_f_string_ranges_decimate_by_)
  extern f_status_t private_f_string_ranges_adjust(const f_array_length_t length, f_string_ranges_t * const ranges) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_ranges_adjust_) || !defined(_di_f_string_ranges_decimate_by_)

/**
 * Private implementation for appending.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source ranges to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_string_ranges_append_all()
 * @see f_string_rangess_append()
 * @see f_string_rangess_append_all()
 */
#if !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_)
  extern f_status_t private_f_string_ranges_append_all(const f_string_ranges_t source, f_string_ranges_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_ranges_append_all_) || !defined(_di_f_string_rangess_append_) || !defined(_di_f_string_rangess_append_all_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param ranges
 *   The ranges to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_adjust()
 * @see f_string_ranges_decrease_by()
 * @see f_string_ranges_increase()
 * @see f_string_ranges_increase_by()
 * @see f_string_ranges_terminate()
 * @see f_string_ranges_terminate_after()
 */
#if !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_terminate_) || !defined(_di_f_string_ranges_terminate_after_)
  extern f_status_t private_f_string_ranges_resize(const f_array_length_t length, f_string_ranges_t * const ranges) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_terminate_) || !defined(_di_f_string_ranges_terminate_after_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param rangess
 *   The rangess to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_rangess_adjust()
 */
#if !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)
  extern f_status_t private_f_string_rangess_adjust(const f_array_length_t length, f_string_rangess_t * const rangess) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_rangess_adjust_) || !defined(_di_f_string_rangess_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param rangess
 *   The rangess to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_adjust()
 * @see f_string_rangess_decrease_by()
 * @see f_string_rangess_increase()
 * @see f_string_rangess_increase_by()
 * @see f_string_rangess_terminate()
 * @see f_string_rangess_terminate_after()
 */
#if !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_) || !defined(_di_f_string_rangess_terminate_) || !defined(_di_f_string_rangess_terminate_after_)
  extern f_status_t private_f_string_rangess_resize(const f_array_length_t length, f_string_rangess_t * const rangess) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_string_rangess_decrease_by_) || !defined(_di_f_string_rangess_increase_) || !defined(_di_f_string_rangess_increase_by_) || !defined(_di_f_string_rangess_terminate_) || !defined(_di_f_string_rangess_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_string_range_h
