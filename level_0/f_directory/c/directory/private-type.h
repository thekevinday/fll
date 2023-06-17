/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_directory_type_h
#define _PRIVATE_F_directory_type_h

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
 * @param statuss
 *   The statuss to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: private_f_directory_status_adjust().
 *
 * @see private_f_directory_status_adjust()
 *
 * @see f_directory_statuss_adjust()
 * @see f_directory_statuss_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_directory_statuss_adjust_) || !defined(_di_f_directory_statuss_decimate_by_)
  extern f_status_t private_f_directory_statuss_adjust(const f_number_unsigned_t length, f_directory_statuss_t * const statuss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_directory_statuss_adjust_) || !defined(_di_f_directory_statuss_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param statuss
 *   The statuss to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 *
 * @see f_directory_statuss_decrease_by()
 * @see f_directory_statuss_increase()
 * @see f_directory_statuss_increase_by()
 * @see f_directory_statuss_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_directory_statuss_decrease_by_) || !defined(_di_f_directory_statuss_increase_) || !defined(_di_f_directory_statuss_increase_by_) || !defined(_di_f_directory_statuss_resize_)
  extern f_status_t private_f_directory_statuss_resize(const f_number_unsigned_t length, f_directory_statuss_t * const statuss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_directory_statuss_decrease_by_) || !defined(_di_f_directory_statuss_increase_) || !defined(_di_f_directory_statuss_increase_by_) || !defined(_di_f_directory_statuss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_directory_type_h
