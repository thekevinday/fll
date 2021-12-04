/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
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
 *   F_none on success.
 *   F_data_not on success, but there is nothing to do (length_old = length_new).
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 *
 * @see f_memory_structure_adjust()
 * @see f_memory_structure_decimate_by()
 */
#if !defined(_di_f_memory_structure_adjust_) || !defined(_di_f_memory_structure_decimate_by_)
  extern f_status_t private_f_memory_adjust(const size_t length_old, const size_t length_new, const size_t type_size, void **pointer) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_memory_structure_adjust_) || !defined(_di_f_memory_structure_decimate_by_)

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
 *   F_none on success.
 *   F_data_not on success, but there is nothing to do (length_old = length_new).
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 *
 * @see f_memory_structure_decrease_by()
 * @see f_memory_structure_increase()
 * @see f_memory_structure_increase_by()
 * @see f_memory_structure_resize()
 *
 * @see private_f_memory_structure_resize()
 */
#if !defined(_di_memory_structure_decrease_by_) || !defined(_di_memory_structure_increase_) || !defined(_di_memory_structure_increase_by_) || !defined(_di_f_memory_structure_resize_)
  extern f_status_t private_f_memory_resize(const size_t length_old, const size_t length_new, const size_t type_size, void **pointer) F_attribute_visibility_internal_d;
#endif // !defined(_di_memory_structure_decrease_by_) || !defined(_di_memory_structure_increase_) || !defined(_di_memory_structure_increase_by_) || !defined(_di_f_memory_structure_resize_)

/**
 * Private implementation for resizing a structure.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length_new
 *   The new size of the structure array.
 *   Setting a length of 0 will result in the deletion (freeing) of the structure.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   Return from: private_f_memory_adjust().
 *
 *   Errors (with error bit) from: private_f_memory_adjust().
 *
 * @see f_memory_structure_adjust()
 * @see f_memory_structure_decimate_by()
 *
 * @see private_f_memory_adjust()
 */
#if !defined(_di_f_memory_structure_adjust_) || !defined(_di_f_memory_structure_decimate_by_)
  f_status_t private_f_memory_structure_adjust(const size_t length_new, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_memory_structure_adjust_) || !defined(_di_f_memory_structure_decimate_by_)

/**
 * Private implementation for resizing a structure.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length_new
 *   The new size of the structure array.
 *   Setting a length of 0 will result in the deletion (freeing) of the structure.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   Return from: private_f_memory_resize().
 *
 *   Errors (with error bit) from: private_f_memory_structure_resize().
 *
 * @see f_memory_structure_decrease_by()
 * @see f_memory_structure_increase()
 * @see f_memory_structure_increase_by()
 * @see f_memory_structure_resize()
 *
 * @see private_f_memory_resize()
 */
#if !defined(_di_memory_structure_decrease_by_) || !defined(_di_memory_structure_increase_) || !defined(_di_memory_structure_increase_by_) || !defined(_di_f_memory_structure_resize_)
  f_status_t private_f_memory_structure_resize(const size_t length_new, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size) F_attribute_visibility_internal_d;
#endif // !defined(_di_memory_structure_decrease_by_) || !defined(_di_memory_structure_increase_) || !defined(_di_memory_structure_increase_by_) || !defined(_di_f_memory_structure_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_memory_h
