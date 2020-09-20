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
#include <level_0/memory-structure.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide defines to alter compile time uses of certain memory functions.
 *
 * These are not intended as macros but are instead intended as a tool to automatically replace one function call with another (via the macro).
 *
 * If _f_memory_FORCE_secure_memory_ is defined, then memory operations are all set to be removed address spaces to 0 before freeing or resizing.
 * If _f_memory_FORCE_fast_memory_ is defined, then memory operations are all set to not set to be removed address spaces to 0 before freeing or resizing.
 */
#ifdef _f_memory_FORCE_secure_memory_
  #define f_memory_delete(the_pointer, the_type, the_length) f_memory_destroy(the_pointer, the_type, the_length)
  #define f_memory_resize(the_pointer, the_type, the_old_length, the_new_length) f_memory_adjust(the_pointer, the_type, the_old_length, the_new_length)

  #ifdef _f_memory_FORCE_fast_memory_
    #error You cannot define both _f_memory_FORCE_fast_memory_ and _f_memory_FORCE_secure_memory_ at the same time
  #endif // _f_memory_FORCE_fast_memory_
#endif // _f_memory_FORCE_secure_memory_

#ifdef _f_memory_FORCE_fast_memory_
  #define f_memory_destroy(the_pointer, the_type, the_length) f_memory_delete(the_pointer, the_type, the_length)
  #define f_memory_adjust(the_pointer, the_type, the_old_length, the_new_length) f_memory_resize(the_pointer, the_type, the_old_length, the_new_length)
#endif // _f_memory_FORCE_fast_memory_

/**
 * Default allocation step.
 *
 * Everytime some array needs a single new element, reallocated by this amount.
 *
 * Normally, this should be small, but when a large number of singular allocations are made, the overhead can be reduced by not having to reallocate space as often.
 * The problem then is that the more space allocated beyond what is initially needed will waste precious memory.
 * Change this if you know your application can afford to reduce the allocation overhead at the cost of more memory.
 *
 * Other projects may provide their own values.
 */
#ifndef _di_f_memory_default_allocation_step_
  #define f_memory_default_allocation_step 4
#endif // _di_f_memory_default_allocation_step_

/**
 * Memory types.
 */
#ifndef _di_f_memory_types_
  #define f_memory_size_t size_t
  #define f_memory_length size_t
#endif // _di_f_memory_types_

/**
 * Create some dynamically allocated array of some length.
 *
 * @param pointer
 *   A pointer that will be updated to the address of the newly allocated memory.
 * @param type
 *   The block size, in bytes (type * length = allocated size).
 * @param length
 *   The total number of blocks to be allocated.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see calloc()
 */
#ifndef _di_f_memory_new_
  extern f_return_status f_memory_new(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // _di_f_memory_new_

/**
 * Delete dynamically allocated data.
 *
 * Will not change any of the data to 0 prior to deallocation.
 *
 * Type and length are not normally used by this function but must be provided for the cases when f_memory_delete is swapped with f_memory_destroy (or vice-versa).
 *
 * @param pointer
 *   A pointer to the address that will be freed.
 * @param type
 *   The block size, in bytes (type * length = allocated size).
 * @param length
 *   The total number of blocks to be allocated.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see free()
 */
#if ! ( defined (_di_f_memory_delete_) || defined (_f_memory_FORCE_secure_memory_) )
  extern f_return_status f_memory_delete(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // ! ( defined (_di_f_memory_delete_) || defined (_f_memory_FORCE_secure_memory_) )

/**
 * Securely deletes some dynamically allocated data.
 *
 * Will change all data to 0 prior to deallocation.
 *
 * @param pointer
 *   A pointer to the address that will be freed.
 * @param type
 *   The block size, in bytes (type * length = allocated size).
 * @param length
 *   The total number of blocks to be allocated.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see free()
 * @see memset()
 */
#if ! ( defined (_di_f_memory_destroy_) || defined (_f_memory_FORCE_fast_memory_) )
  extern f_return_status f_memory_destroy(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // ! ( defined (_di_f_memory_destroy_) || defined (_f_memory_FORCE_fast_memory_) )

/**
 * Resize dynamically allocated data.
 *
 * Will not change any of the data prior to deallocation.
 *
 * @param pointer
 *   A pointer to the address that will be resized.
 * @param type
 *   The block size, in bytes (type * length = allocated size).
 * @param old_length
 *   The total number of blocks representing the length to be resized from.
 * @param new_length
 *   The total number of blocks representing the length to be resized to.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see calloc()
 * @see memset()
 * @see realloc()
 */
#if ! ( defined (_di_f_memory_resize_) || defined (_f_memory_FORCE_secure_memory_) )
  extern f_return_status f_memory_resize(void **pointer, const f_memory_size_t type, const f_memory_length old_length, const f_memory_length new_length);
#endif // ! ( defined (_di_f_memory_resize_) || defined (_f_memory_FORCE_secure_memory_) )

/**
 * Securely resize dynamically allocated data.
 *
 * Will change all data to 0 prior to deallocation.
 *
 * @param pointer
 *   A pointer to the address that will be resized.
 * @param type
 *   The block size, in bytes (type * length = allocated size).
 * @param old_length
 *   The total number of blocks representing the length to be resized from.
 * @param new_length
 *   The total number of blocks representing the length to be resized to.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see calloc()
 * @see memset()
 * @see realloc()
 */
#if ! ( defined (_di_f_memory_adjust_) || defined (_f_memory_FORCE_fast_memory_) )
  extern f_return_status f_memory_adjust(void **pointer, const f_memory_size_t type, const f_memory_length old_length, const f_memory_length new_length);
#endif // _di_f_memory_adjust_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_h
