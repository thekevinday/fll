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
#ifndef _PRIVATE_F_fss_nest_h
#define _PRIVATE_F_fss_nest_h

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
 * @param nest
 *   The nest to adjust.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_dynamic_adjust()
 *
 * @see f_fss_nests_adjust()
 * @see f_fss_nests_decimate_by()
 */
#if !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)
  extern f_status_t private_f_fss_nest_adjust(const f_number_unsigned_t length, f_fss_nest_t * const nest) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nest
 *   The nest to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_fss_nests_decrease_by()
 * @see f_fss_nests_resize()
 */
#if !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_resize_)
  extern f_status_t private_f_fss_nest_resize(const f_number_unsigned_t length, f_fss_nest_t * const nest) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nests
 *   The nests to adjust.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_dynamic_adjust()
 *
 * @see f_fss_nests_adjust()
 * @see f_fss_nests_decimate_by()
 */
#if !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_)
  extern f_status_t private_f_fss_nests_adjust(const f_number_unsigned_t length, f_fss_nests_t * const nests) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param nests
 *   The nests to resize.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_fss_nests_decrease_by()
 * @see f_fss_nests_increase()
 * @see f_fss_nests_increase_by()
 * @see f_fss_nests_resize()
 */
#if !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)
  extern f_status_t private_f_fss_nests_resize(const f_number_unsigned_t length, f_fss_nests_t * const nests) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_fss_nest_h
