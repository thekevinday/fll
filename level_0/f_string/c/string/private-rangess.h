/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_string_rangess_h
#define _PRIVATE_F_string_rangess_h

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

#endif // _PRIVATE_F_string_rangess_h