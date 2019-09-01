/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide means to use memory routines, with error checking.
 *
 * Possible error values on return:
 *   f_allocation_error   - an error during the allocation process.
 *   f_critical           - an error.
 *   f_deallocation_error - an error during the deallocation process.
 *   f_invalid_data       - something is wrong with the data sent to this function, error.
 *   f_invalid_parameter  - a parameter sent to this function is invalid, error.
 *   f_invalid_syntax     - syntax for data sent to this is invalid, error.
 *   f_no_data            - something is wrong with the data sent to this function, warning.
 *   f_none               - no errors or warnings.
 *   f_reallocation_error - an error during the reallocation process.
 *   f_unknown            - an unknown error.
 *   f_warn               - a possible problem, but not an error (warning).
 */
#ifndef _F_memory_h
#define _F_memory_h

// libc includes
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

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


#ifndef _di_f_memory_default_allocation_step_
  /**
   * Everytime some array needs a single new element, reallocated by this amount.
   * Normally, this should be small, but when a large number of singular allocations are made, the overhead can be reduced by not having to reallocate space as often.
   * The problem then is that the more space allocated beyond what is initially needed will waste precious memory.
   * Change this if you know your application can afford to reduce the allocation overhead at the cost of more memory.
   */
  #define f_memory_default_allocation_step 3
#endif // _di_f_memory_default_allocation_step_

#ifndef _di_f_memory_types_
  #define f_memory_size_t size_t
  #define f_memory_length size_t
#endif // _di_f_memory_types_

#ifndef _di_f_memory_new_
  // Create some dynamically allocated array of some length
  extern f_return_status f_memory_new(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // _di_f_memory_new_

#if ! ( defined (_di_f_memory_delete_) || defined (_f_memory_FORCE_secure_memory_) )
  /**
   * deletes some dynamically allocated data.
   * f_memory_delete, will not change any of the data to 0 prior to deallocation.
   * type and length are not used by this function normally but must be provided for the cases when f_memory_delete is swapped with f_memory_destroy (or vice-versa).
   */
  extern f_return_status f_memory_delete(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // ! ( defined (_di_f_memory_delete_) || defined (_f_memory_FORCE_secure_memory_) )

#if ! ( defined (_di_f_memory_destroy_) || defined (_f_memory_FORCE_fast_memory_) )
  /**
   * securely deletes some dynamically allocated data.
   * f_memory_destroy, will change all data to 0 prior to deallocation.
   */
  extern f_return_status f_memory_destroy(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // ! ( defined (_di_f_memory_destroy_) || defined (_f_memory_FORCE_fast_memory_) )

#if ! ( defined (_di_f_memory_resize_) || defined (_f_memory_FORCE_secure_memory_) )
  /**
   * resizes some dynamically allocated data.
   * f_memory_resize, will not change any of the data prior to deallocation.
   */
  extern f_return_status f_memory_resize(void **pointer, const f_memory_size_t type, const f_memory_length old_length, const f_memory_length new_length);
#endif // ! ( defined (_di_f_memory_resize_) || defined (_f_memory_FORCE_secure_memory_) )

#if ! ( defined (_di_f_memory_adjust_) || defined (_f_memory_FORCE_fast_memory_) )
  /**
   * securely resizes some dynamically allocated data.
   * f_memory_adjust, will change all data to 0 prior to deallocation.
   */
  extern f_return_status f_memory_adjust(void **pointer, const f_memory_size_t type, const f_memory_length old_length, const f_memory_length new_length);
#endif // _di_f_memory_adjust_


// centralize allocation for all FLL structures that follow the size+used approach.
#ifndef _di_f_macro_memory_structure_clear_
  /**
   * structure: the structure to operate on.
   */
  #define f_macro_memory_structure_clear(structure) \
    structure.array = 0; \
    structure.size = 0; \
    structure.used = 0;
#endif // _di_f_macro_memory_structure_clear_

#ifndef _di_f_macro_memory_structure_new_
  /**
   * status:    the status to return.
   * structure: the structure to operate on.
   * type:      the structure type.
   */
  #define f_macro_memory_structure_new(status, structure, type, length) \
    structure.array = 0; \
    structure.size = 0; \
    structure.used = 0; \
    status = f_memory_new((void **) & structure.array, sizeof(type), length); \
    if (status == f_none) { \
      structure.size = length; \
      structure.used = 0; \
    }
#endif // _di_f_macro_memory_structure_new_

// improper use of these defines can lead to memory leaks and compilation errors
#ifndef _di_f_macro_memory_structure_delete_
  /**
   * status:    the status to return.
   * structure: the structure to operate on.
   * type:      the structure type.
   */
  #define f_macro_memory_structure_delete(status, structure, type) \
    status = f_memory_delete((void **) & structure.array, sizeof(type), structure.size); \
    if (status == f_none) { \
      structure.size = 0; \
      structure.used = 0; \
    }
#endif // _di_f_macro_memory_structure_delete_

#ifndef _di_f_macro_memory_structure_destroy_
  /**
   * status:    the status to return.
   * structure: the structure to operate on.
   * type:      the structure type.
   */
  #define f_macro_memory_structure_destroy(status, structure, type) \
    status = f_memory_destroy((void **) & structure.array, sizeof(type), structure.size); \
    if (status == f_none) { \
      structure.size = 0; \
      structure.used = 0; \
    }
#endif // _di_f_macro_memory_structure_destroy_

#ifndef _di_f_macro_memory_structure_resize_
  /**
   * status:    the status to return.
   * structure: the structure to operate on.
   * type:      the structure type.
   */
  #define f_macro_memory_structure_resize(status, structure, type, new_length) \
    status = f_memory_resize((void **) & structure.array, sizeof(type), structure.size, new_length); \
    if (status == f_none) { \
      structure.size = new_length; \
      if (structure.used > structure.size) structure.used = new_length; \
    }
#endif // _di_f_macro_memory_structure_resize_

#ifndef _di_f_macro_memory_structure_adjust_
  /**
   * status:    the status to return.
   * structure: the structure to operate on.
   * type:      the structure type.
   */
  #define f_macro_memory_structure_adjust(status, structure, type, new_length) \
    status = f_memory_adjust((void **) & structure.array, sizeof(type), structure.size, new_length); \
    if (status == f_none) { \
      structure.size = new_length; \
      if (structure.used > structure.size) structure.used = new_length; \
    }
#endif // _di_f_macro_memory_structure_adjust_

// Structures defines function in the same way that the structure defines do
// however, these hold an array of structure
// improper use of these defines can lead to memory leaks and compilation errors
#ifndef _di_f_macro_memory_structures_clear_
  /**
   * structure: the structure to operate on.
   */
  #define f_macro_memory_structures_clear(structures) \
    structures.array = 0; \
    structures.size = 0; \
    structures.used = 0;
#endif // _di_f_macro_memory_structures_clear_

#ifndef _di_f_macro_memory_structures_new_
  /**
   * status:     the status to return.
   * structures: the structure to operate on.
   * type:       the structure type.
   */
  #define f_macro_memory_structures_new(status, structures, type, new_length) \
    structures.array = 0; \
    structures.size = 0; \
    structures.used = 0; \
    status = f_memory_new((void **) & structures.array, sizeof(type), new_length); \
    if (status == f_none) { \
      structures.size = new_length; \
      structures.used = 0; \
    }
#endif // _di_f_macro_memory_structures_new_

#ifndef _di_f_macro_memory_structures_delete_
  /**
   * status:     the status to return.
   * structures: the structure to operate on.
   * type:       the structure type.
   */
  #define f_macro_memory_structures_delete(status, structures, type) \
    status = f_none; \
    while (structures.size > 0) { \
      --structures.size; \
      f_macro_memory_structure_delete(status, structures.array[structures.size], type); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & structures.array, sizeof(type), structures.size); \
    if (status == f_none) structures.used = 0;
#endif // _di_f_macro_memory_structures_delete_

#ifndef _di_f_macro_memory_structures_destroy_
  /**
   * status:     the status to return.
   * structures: the structure to operate on.
   * type:       the structure type.
   */
  #define f_macro_memory_structures_destroy(status, structures, type) \
    status = f_none; \
    while (structures.size > 0) { \
      --structures.size; \
      f_macro_memory_structure_destroy(status, structures.array[structures.size], type); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_destroy((void **) & structures.array, sizeof(type), structures.size); \
    if (status == f_none) structures.used = 0;
#endif // _di_f_macro_memory_structures_destroy_

#ifndef _di_f_macro_memory_structures_resize_
  /**
   * status:     the status to return.
   * structures: the structure to operate on.
   * type:       the structure type.
   */
  #define f_macro_memory_structures_resize(status, structures, type, new_length, length_variable) \
    status = f_none; \
    if (new_length < structures.size) { \
      length_variable i = structures.size - new_length; \
      for (; i < structures.size; ++i) { \
        f_macro_memory_structure_delete(status, structures.array[i], type); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_resize((void **) & structures.array, sizeof(type), structures.size, new_length); \
    if (status == f_none) { \
      if (new_length > structures.size) { \
        length_variable i = structures.size; \
        for (; i < new_length; ++i) { \
          memset(&structures.array[i], 0, sizeof(type)); \
        } \
      } \
      structures.size = new_length; \
      if (structures.used > structures.size) structures.used = new_length; \
    }
#endif // _di_f_macro_memory_structures_resize_

#ifndef _di_f_macro_memory_structures_adjust_
  /**
   * status:     the status to return.
   * structures: the structure to operate on.
   * type:       the structure type.
   */
  #define f_macro_memory_structures_adjust(status, structures, type, new_length, length_variable) \
    status = f_none; \
    if (new_length < structures.size) { \
      length_variable i = structures.size - new_length; \
      for (; i < structures.size; ++i) { \
        f_macro_memory_structure_destroy(status, structures.array[i], type); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_adjust((void **) & structures.array, sizeof(type), structures.size, new_length); \
    if (status == f_none) { \
      if (new_length > structures.size) { \
        length_variable i = structures.size; \
        for (; i < new_length; ++i) { \
          memset(&structures.array[i], 0, sizeof(type)); \
        } \
      } \
      structures.size = new_length; \
      if (structures.used > structures.size) structures.used = new_length; \
    }
#endif // _di_f_macro_memory_structures_adjust_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_h
