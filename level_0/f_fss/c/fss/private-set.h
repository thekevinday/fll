/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_fss_set_h
#define _PRIVATE_F_fss_set_h

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
 * @param set
 *   The set to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 *
 * @see f_fss_set_adjust()
 * @see f_fss_set_decimate_by()
 */
#if !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_)
  extern f_status_t private_f_fss_set_adjust(const f_number_unsigned_t length, f_fss_set_t * const set) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param set
 *   The set to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *
 * @see f_string_ranges_resize
 * @see f_string_rangess_resize()()
 *
 * @see f_fss_set_decrease_by()
 * @see f_fss_set_resize()
 */
#if !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_resize_)
  extern f_status_t private_f_fss_set_resize(const f_number_unsigned_t length, f_fss_set_t * const set) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets to adjust.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *   Errors (with error bit) from: f_string_rangess_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_ranges_adjust()
 * @see f_string_rangess_adjust()
 *
 * @see f_fss_sets_adjust()
 * @see f_fss_sets_decimate_by()
 */
#if !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_)
  extern f_status_t private_f_fss_sets_adjust(const f_number_unsigned_t length, f_fss_sets_t * const sets) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *
 * @see f_memory_array_resize()
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 *
 * @see f_fss_sets_decrease_by()
 * @see f_fss_sets_resize()
 */
#if !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_resize_)
  extern f_status_t private_f_fss_sets_resize(const f_number_unsigned_t length, f_fss_sets_t * const sets) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_fss_set_h
