/* FLL - Level 0
 * Project:       Memory
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide means to use memory routines, with error checking.
 *
 * Possible error values on return:
 *   f_warn               - a possible problem, but not an error (warning)
 *   f_critical           - an error
 *   f_unknown            - an unknown error
 *   f_invalid_parameter  - a parameter sent to this function is invalid, error
 *   f_invalid_syntax     - syntax for data sent to this is invalid, error
 *   f_invalid_data       - something is wrong with the data sent to this function, error
 *   f_no_data            - something is wrong with the data sent to this function, warning
 *   f_none               - no errors or warnings
 *   f_allocation_error   - an error during the allocation process
 *   f_reallocation_error - an error during the reallocation process
 *   f_deallocation_error - an error during the deallocation process
 */
#ifndef _F_memory_h
#define _F_memory_h

// libc includes
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// fll includes
#include <level_0/types.h>
#include <level_0/errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _f_memory_FORCE_secure_memory_
  #define f_delete(the_pointer, the_type, the_length) f_destroy(the_pointer, the_type, the_length)
  #define f_resize(the_pointer, the_type, the_old_length, the_new_length) f_adjust(the_pointer, the_type, the_old_length, the_new_length)

  #ifdef _f_memory_FORCE_fast_memory_
    #error You cannot define both _f_memory_FORCE_fast_memory_ and _f_memory_FORCE_secure_memory_ at the same time
  #endif // _f_memory_FORCE_fast_memory_
#endif // _f_memory_FORCE_secure_memory_

#ifdef _f_memory_FORCE_fast_memory_
  #define f_destroy(the_pointer, the_type, the_length) f_delete(the_pointer, the_type, the_length)
  #define f_adjust(the_pointer, the_type, the_old_length, the_new_length) f_resize(the_pointer, the_type, the_old_length, the_new_length)
#endif // _f_memory_FORCE_fast_memory_


#ifndef _di_f_memory_default_allocation_step_
  // Everytime some array needs a single new element, reallocated by this amount
  // Normally, this should be small, but when a large number of singular allocations are made, the overhead can be reduced by not having to reallocate space as often
  // The problem then is that the more space allocated beyond what is initially needed will waste precious memory
  // Change this if you know your application can afford to reduce the allocation overhead at the cost of more memory
  #define f_memory_default_allocation_step 3
#endif // _di_f_memory_default_allocation_step_

#ifndef _di_f_memory_types_
  #define f_memory_size_t f_size_t
  #define f_memory_length f_size_t
#endif // _di_f_memory_types_

#ifndef _di_f_new_
  // Create some dynamically allocated array of some length
  #define f_new(pointer,type) f_new_array(pointer, type, 1)
  extern f_return_status f_new_array(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // _di_f_new_

#if ! ( defined (_di_f_delete_) || defined (_f_memory_FORCE_secure_memory_) )
  // deletes some dynamically allocated data
  // f_delete, will not change any of the data to 0 prior to deallocation
  // type and length are not used by this function normally but must be provided for the cases when f_delete is swapped with f_destroy (or vice-versa)
  extern f_return_status f_delete(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // ! ( defined (_di_f_delete_) || defined (_f_memory_FORCE_secure_memory_) )

#if ! ( defined (_di_f_destroy_) || defined (_f_memory_FORCE_fast_memory_) )
  // securely deletes some dynamically allocated data
  // f_destroy, will change all data to 0 prior to deallocation
  extern f_return_status f_destroy(void **pointer, const f_memory_size_t type, const f_memory_length length);
#endif // ! ( defined (_di_f_destroy_) || defined (_f_memory_FORCE_fast_memory_) )

#if ! ( defined (_di_f_resize_) || defined (_f_memory_FORCE_secure_memory_) )
  // resizes some dynamically allocated data
  // f_resize, will not change any of the data prior to deallocation
  extern f_return_status f_resize(void **pointer, const f_memory_size_t type, const f_memory_length old_length, const f_memory_length new_length);
#endif // ! ( defined (_di_f_resize_) || defined (_f_memory_FORCE_secure_memory_) )

#if ! ( defined (_di_f_adjust_) || defined (_f_memory_FORCE_fast_memory_) )
  // securely resizes some dynamically allocated data
  // f_adjust, will change all data to 0 prior to deallocation
  extern f_return_status f_adjust(void **pointer, const f_memory_size_t type, const f_memory_length old_length, const f_memory_length new_length);
#endif // _di_f_adjust_


// the delete, destroy, resize, and adjust structure defines are mean to centralize allocation for all FLL structures that follow the size+used approach.
// improper use of these defines can lead to memory leaks and compilation errors
#ifndef _di_f_delete_structure_
  // status:     the status to return
  // structure:  the structure to operate on
  // type:       the structure type
  #define f_delete_structure(status, structure, type) \
    status = f_delete((void **) & structure.array, sizeof(type), structure.size); \
    if (status == f_none) { \
      structure.size = 0; \
      structure.used = 0; \
    }
#endif // _di_f_delete_structure_

#ifndef _di_f_destroy_structure_
  // status:     the status to return
  // structure:  the structure to operate on
  // type:       the structure type
  #define f_destroy_structure(status, structure, type) \
    status = f_destroy((void **) & structure.array, sizeof(type), structure.size); \
    if (status == f_none) { \
      structure.size = 0; \
      structure.used = 0; \
    }
#endif // _di_f_destroy_structure_

#ifndef _di_f_resize_structure_
  // status:     the status to return
  // structure:  the structure to operate on
  // type:       the structure type
  #define f_resize_structure(status, structure, type, new_length) \
    status = f_resize((void **) & structure.array, sizeof(type), structure.size, new_length); \
    if (status == f_none) { \
      structure.size = new_length; \
      if (structure.used > structure.size) structure.used = new_length; \
    }
#endif // _di_f_resize_structure_

#ifndef _di_f_adjust_structure_
  // status:     the status to return
  // structure:  the structure to operate on
  // type:       the structure type
  #define f_adjust_structure(status, structure, type, new_length) \
    status = f_adjust((void **) & structure.array, sizeof(type), structure.size, new_length); \
    if (status == f_none) { \
      structure.size = new_length; \
      if (structure.used > structure.size) structure.used = new_length; \
    }
#endif // _di_f_adjust_structure_

// the delete, destroy, resize, and adjust structures defines function in the same way that the delete, destroy, resize, and adjust structure defines do
// however, these hold an array of structure
// improper use of these defines can lead to memory leaks and compilation errors
#ifndef _di_f_delete_structures_
  // status:     the status to return
  // structures: the structure to operate on
  // type:       the structure type
  #define f_delete_structures(status, structures, type) \
    status = f_none; \
    while (structures.size > 0) { \
      --structures.size; \
      f_delete_structure(status, structures.array[structures.size], type); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_delete((void **) & structures.array, sizeof(type), structures.size); \
    if (status == f_none) structures.used = 0;
#endif // _di_f_delete_structures_

#ifndef _di_f_destroy_structures_
  // status:     the status to return
  // structures: the structure to operate on
  // type:       the structure type
  #define f_destroy_structures(status, structures, type) \
    status = f_none; \
    while (structures.size > 0) { \
      --structures.size; \
      f_destroy_structure(status, structures.array[structures.size], type); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_destroy((void **) & structures.array, sizeof(type), structures.size); \
    if (status == f_none) structures.used = 0;
#endif // _di_f_destroy_structures_

#ifndef _di_f_resize_structures_
  // status:     the status to return
  // structures: the structure to operate on
  // type:       the structure type
  #define f_resize_structures(status, structures, type, new_length, length_variable) \
    status = f_none; \
    if (new_length < structures.size) { \
      length_variable i = structures.size - new_length; \
      for (; i < structures.size; ++i) { \
        f_delete_structure(status, structures.array[i], type); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_resize((void **) & structures.array, sizeof(type), structures.size, new_length); \
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
#endif // _di_f_resize_structures_

#ifndef _di_f_adjust_structures_
  // status:     the status to return
  // structures: the structure to operate on
  // type:       the structure type
  #define f_adjust_structures(status, structures, type, new_length, length_variable) \
    status = f_none; \
    if (new_length < structures.size) { \
      length_variable i = structures.size - new_length; \
      for (; i < structures.size; ++i) { \
        f_destroy_structure(status, structures.array[i], type); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_adjust((void **) & structures.array, sizeof(type), structures.size, new_length); \
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
#endif // _di_f_adjust_structures_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_h
