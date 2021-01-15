/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to use memory routines, with error checking.
 *
 * @todo consider adding f_memory_scramble() and f_memory_juggle().
 *       f_memory_scramble() is like f_destroy() but it writes random data instead of 0.
 *       f_memory_juggle() is like f_adjust() but it writes random data instead of 0.
 */
#ifndef _F_memory_h
#define _F_memory_h

// libc includes
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>

// fll-0 memory includes
#include <level_0/memory-common.h>
#include <level_0/memory_structure.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Securely resize dynamically allocated data.
 *
 * Will change all data to 0 prior to deallocation.
 *
 * @param old_length
 *   The total number of blocks representing the length to be resized from.
 * @param new_length
 *   The total number of blocks representing the length to be resized to.
 * @param size
 *   The block size, in bytes (size * length = allocated size).
 * @param pointer
 *   A pointer to the address that will be resized.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there was nothing to do.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see calloc()
 * @see memset()
 * @see realloc()
 */
#ifndef _di_f_memory_adjust_
  extern f_status_t f_memory_adjust(const size_t old_length, const size_t new_length, const size_t size, void **pointer);
#endif // _di_f_memory_adjust_

/**
 * Delete dynamically allocated data.
 *
 * Will not change any of the data to 0 prior to deallocation.
 *
 * Type and length are not normally used by this function but must be provided for the cases when f_memory_delete is swapped with f_memory_destroy (or vice-versa).
 *
 * @param length
 *   The total number of blocks to be allocated.
 *   If length is 0 then no delete is performed.
 * @param size
 *   The block size, in bytes (size * length = allocated size).
 *   If size is 0 then no delete is performed.
 * @param pointer
 *   A pointer to the address that will be freed.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there was nothing to do.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see free()
 */
#ifndef _di_f_memory_delete_
  extern f_status_t f_memory_delete(const size_t length, const size_t size, void **pointer);
#endif // _di_f_memory_delete_

/**
 * Securely deletes some dynamically allocated data.
 *
 * Will change all data to 0 prior to deallocation.
 *
 * @param length
 *   The total number of blocks to be allocated.
 *   If length is 0 then no delete is performed.
 * @param size
 *   The block size, in bytes (size * length = allocated size).
 *   If size is 0 then no delete is performed.
 * @param pointer
 *   A pointer to the address that will be freed.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there was nothing to do.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see free()
 * @see memset()
 */
#ifndef _di_f_memory_destroy_
  extern f_status_t f_memory_destroy(const size_t length, const size_t size, void **pointer);
#endif // _di_f_memory_destroy_

/**
 * Create some dynamically allocated array of some length.
 *
 * @param pointer
 *   A pointer that will be updated to the address of the newly allocated memory.
 * @param size
 *   The block size, in bytes (size * length = allocated size).
 *   Must be greater than 0.
 * @param length
 *   The total number of blocks to be allocated.
 *   Must be greater than 0.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there was nothing to do.
 *
 *   F_memory_not (with error bit) on allocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see calloc()
 * @see memset()
 */
#ifndef _di_f_memory_new_
  extern f_status_t f_memory_new(const size_t length, const size_t size, void **pointer);
#endif // _di_f_memory_new_

/**
 * Create some dynamically allocated array of some length, guaranteeing aligned memory.
 *
 * @param length
 *   The total number of blocks to be allocated.
 *   Must be greater than 0.
 *   Must be a multiple of alignment.
 * @param alignment
 *   The size of the alignment, such as sizeof(void *).
 *   Must be greater than 0.
 * @param pointer
 *   A pointer that will be updated to the address of the newly allocated memory.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there was nothing to do.
 *
 *   F_memory_not (with error bit) on allocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see posix_memalign()
 * @see memset()
 */
#ifndef _di_f_memory_new_aligned_
  extern f_status_t f_memory_new_aligned(const size_t length, const size_t alignment, void **pointer);
#endif // _di_f_memory_new_aligned_

/**
 * Resize dynamically allocated data.
 *
 * Will not change any of the data prior to deallocation.
 *
 * @param old_length
 *   The total number of blocks representing the length to be resized from.
 * @param new_length
 *   The total number of blocks representing the length to be resized to.
 * @param size
 *   The block size, in bytes (size * length = allocated size).
 * @param pointer
 *   A pointer to the address that will be resized.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there was nothing to do.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see calloc()
 * @see memset()
 * @see realloc()
 */
#ifndef _di_f_memory_resize_
  extern f_status_t f_memory_resize(const size_t old_length, const size_t new_length, const size_t size, void **pointer);
#endif // _di_f_memory_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_h
