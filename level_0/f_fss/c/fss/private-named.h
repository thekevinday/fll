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
#ifndef _PRIVATE_F_fss_named_h
#define _PRIVATE_F_fss_named_h

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
 * @param named
 *   The named to adjust.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_arrays_adjust().
 *   Errors (with error bit) from: macro_f_string_ranges_t_adjust().
 *   Errors (with error bit) from: macro_f_string_rangess_t_adjust().
 *
 * @see f_memory_arrays_adjust()
 * @see macro_f_string_ranges_t_adjust()
 * @see macro_f_string_rangess_t_adjust()
 *
 * @see f_fss_nameds_adjust()
 * @see f_fss_nameds_decimate_by()
 */
#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  extern f_status_t private_f_fss_named_adjust(const f_number_unsigned_t length, f_fss_named_t * const named) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param named
 *   The named to resize.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *
 * @see f_memory_arrays_resize()
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 *
 * @see f_fss_nameds_decrease_by()
 * @see f_fss_nameds_resize()
 */
#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_resize_)
  extern f_status_t private_f_fss_named_resize(const f_number_unsigned_t length, f_fss_named_t * const named) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nameds
 *   The nameds to adjust.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 *
 * @see f_fss_nameds_adjust()
 * @see f_fss_nameds_decimate_by()
 */
#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  extern f_status_t private_f_fss_nameds_adjust(const f_number_unsigned_t length, f_fss_nameds_t * const nameds) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nameds
 *   The nameds to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *   Errors (with error bit) from: f_string_rangess_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 *
 * @see f_fss_nameds_decrease_by()
 * @see f_fss_nameds_increase()
 * @see f_fss_nameds_increase_by()
 * @see f_fss_nameds_resize()
 */
#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_named_increase_) || !defined(_di_f_fss_named_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  extern f_status_t private_f_fss_nameds_resize(const f_number_unsigned_t length, f_fss_nameds_t * const nameds) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_named_increase_) || !defined(_di_f_fss_named_increase_by_) || !defined(_di_f_fss_nameds_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_fss_named_h
