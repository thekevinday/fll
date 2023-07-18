/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_memory_array_h
#define _PRIVATE_F_memory_array_h

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
 * @param width
 *   The size of the structure represented by array.
 *   The word "width" is used due to conflicts of already using "length" and "size".
 * @param array
 *   The structure.array to adjust.
 * @param used
 *   The structure.used.
 * @param size
 *   The structure.size.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_array_decimate_by()
 * @see f_memory_adjust()
 */
#if !defined(_di_f_memory_array_adjust_) || !defined(_di_f_memory_array_decimate_by_)
  extern f_status_t private_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_memory_array_adjust_) || !defined(_di_f_memory_array_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param width
 *   The size of the structure represented by array.
 *   The word "width" is used due to conflicts of already using "length" and "size".
 * @param array
 *   The structure.array to resize.
 * @param used
 *   The structure.used.
 * @param size
 *   The structure.size.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_array_decrease_by()
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 * @see f_memory_resize()
 */
#if !defined(_di_f_memory_array_decrease_by_) || !defined(_di_f_memory_array_increase_) || !defined(_di_f_memory_array_increase_by_) || !defined(_di_f_memory_array_resize_)
  extern f_status_t private_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_memory_array_decrease_by_) || !defined(_di_f_memory_array_increase_) || !defined(_di_f_memory_array_increase_by_) || !defined(_di_f_memory_array_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_memory_array_h
