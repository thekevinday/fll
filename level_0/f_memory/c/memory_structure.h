/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines memory structure data.
 *
 * This is auto-included by memory.h and should not need to be explicitly included.
 */
#ifndef _F_memory_structure_h
#define _F_memory_structure_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the structure.
 *
 * Memory being deleted will be wiped.
 *
 * @param length_new
 *   The new size of the structure array.
 *   Setting a length of 0 will result in the deletion (freeing) of the structure.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 *   Must be greater than 0.
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_adjust_
  extern f_status_t f_memory_structure_adjust(const size_t length_new, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_adjust_

/**
 * Resize the structure to a smaller size, by the given amount.
 *
 * This will not shrink the size to less than 0.
 * Memory being deleted will be wiped.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 *   Must be greater than 0.
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but amount is 0 so there is nothing to do.
 *
 *   F_memory_not (with error bit) on out of memory.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_decimate_by_
  extern f_status_t f_memory_structure_decimate_by(const f_array_length_t amount, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_decimate_by_

/**
 * Resize the structure to a smaller size, by the given amount.
 *
 * This will not shrink the size to less than 0.
 * Memory being deleted will not be wiped.
 *
 * @param amount
 *   A positive number representing how much to decrease by.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 *   Must be greater than 0.
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but amount is 0 so there is nothing to do.
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_decrease_by_
  extern f_status_t f_memory_structure_decrease_by(const f_array_length_t amount, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_decrease_by_

/**
 * Delete the structure.
 *
 * Memory being deleted will not be wiped.
 *
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 *   Must be greater than 0.
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but amount is 0 so there is nothing to do.
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_delete_
  extern f_status_t f_memory_structure_delete(const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_delete_

/**
 * Destroy the structure.
 *
 * Memory being deleted will be wiped.
 *
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 *   Must be greater than 0.
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but amount is 0 so there is nothing to do.
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_destroy_
  extern f_status_t f_memory_structure_destroy(const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_destroy_

/**
 * Increase the size of the structure, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 *   Must be greater than 0.
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_increase_
  extern f_status_t f_memory_structure_increase(const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_increase_

/**
 * Resize the structure to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 *   Must be greater than 0.
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but amount is 0 so there is nothing to do.
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_increase_by_
  extern f_status_t f_memory_structure_increase_by(const f_array_length_t amount, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_increase_by_

/**
 * Initialize a new structure.
 *
 * The structure will be cleared before making changes.
 * Be sure any existing data is deallocation as necessary.
 *
 * @param length_new
 *   The new size of the structure array.
 *   Must be greater than 0.
 * @param type_size
 *   The size of the structure type (such as: sizeof(structure_size)).
 *   Must be greater than 0.
 * @param structure
 *   The structure to delete.
 * @param used
 *   The amount of data used by the structure.
 * @param size
 *   The amount of data allocated to the structure.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_new_
  extern f_status_t f_memory_structure_new(const size_t length_new, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_new_

/**
 * Resize the structure.
 *
 * Memory being deleted will not be wiped.
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
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on allocation error.
 *
 * @see calloc()
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_structure_resize_
  extern f_status_t f_memory_structure_resize(const size_t length_new, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size);
#endif // _di_f_memory_structure_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_structure_h
