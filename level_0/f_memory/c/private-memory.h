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
#ifndef _PRIVATE_F_memory_h
#define _PRIVATE_F_memory_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for adjusting.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length_old
 *   The old size of the structure array.
 *   This is used to determine if and when to call memset().
 * @param length_new
 *   The new size of the structure array.
 *   Setting a length of 0 will result in the deletion (freeing) of the structure.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 * @param pointer
 *   The pointer to the memory to delete.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to do (length_old = length_new).
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 *
 * @see f_memory_adjust()
 * @see f_memory_resize()
 */
#if !defined(_di_f_memory_adjust_) || defined(_f_memory_FORCE_secure_memory_) && !defined(_di_f_memory_resize_) || !defined(_di_f_memory_array_adjust_) || !defined(_di_f_memory_array_decimate_by_)
  extern f_status_t private_f_memory_adjust(const size_t length_old, const size_t length_new, const size_t type_size, void ** const pointer) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_memory_adjust_) || defined(_f_memory_FORCE_secure_memory_) && !defined(_di_f_memory_resize_) || !defined(_di_f_memory_array_adjust_) || !defined(_di_f_memory_array_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length_old
 *   The old size of the structure array.
 *   This is used to determine if and when to call memset().
 * @param length_new
 *   The new size of the structure array.
 *   Setting a length of 0 will result in the deletion (freeing) of the structure.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 * @param pointer
 *   The pointer to the memory to delete.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to do (length_old = length_new).
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 *
 * @see f_memory_adjust()
 * @see f_memory_resize()
 */
#if !defined(_di_f_memory_resize_) || defined(_f_memory_FORCE_fast_memory_) && !defined(_di_f_memory_adjust_) || !defined(_di_f_memory_array_append_) || !defined(_di_f_memory_array_append_all_) || !defined(_di_f_memory_array_decrease_by_) || !defined(_di_f_memory_array_increase_) || !defined(_di_f_memory_array_increase_by_) || !defined(_di_f_memory_array_resize_)
  extern f_status_t private_f_memory_resize(const size_t length_old, const size_t length_new, const size_t type_size, void ** const pointer) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_memory_resize_) || defined(_f_memory_FORCE_fast_memory_) && !defined(_di_f_memory_adjust_) || !defined(_di_f_memory_array_append_) || !defined(_di_f_memory_array_append_all_) || !defined(_di_f_memory_array_decrease_by_) || !defined(_di_f_memory_array_increase_) || !defined(_di_f_memory_array_increase_by_) || !defined(_di_f_memory_array_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_memory_h
