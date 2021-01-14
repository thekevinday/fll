/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines iki common data.
 *
 * This is auto-included by memory.h and should not need to be explicitly included.
 */
#ifndef _F_memory_common_h
#define _F_memory_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check to make sure these two macros are not defined at the same time.
 *
 * If _f_memory_FORCE_secure_memory_ is defined, then all to-be deallocated address spaces are set to 0 before freeing or resizing.
 * If _f_memory_FORCE_fast_memory_ is defined, then all to-be deallocated address spaces remain unchanged before freeing or resizing.
 */
#if defined(_f_memory_FORCE_secure_memory_) && defined(_f_memory_FORCE_fast_memory_)
  #error You cannot define both _f_memory_FORCE_fast_memory_ and _f_memory_FORCE_secure_memory_ at the same time.
#endif // _f_memory_FORCE_secure_memory_

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
 * Reset a generic memory stucture to 0 (clear all values).
 *
 * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
 *
 * structure: the structure to operate on.
 */
#ifndef _di_f_macro_memory_structure_clear_
  #define f_macro_memory_structure_clear(structure) \
    structure.array = 0; \
    structure.size = 0; \
    structure.used = 0;
#endif // _di_f_macro_memory_structure_clear_

/**
 * Resize a generic memory structure.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 * length:    the new size of the array.
 */
#ifndef _di_f_macro_memory_structure_resize_
  #define f_macro_memory_structure_resize(status, structure, type, length) \
    status = f_memory_structure_resize(length, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_resize_

/**
 * Adjust a generic memory structure.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 * length:    the new size of the array.
 */
#ifndef _di_f_macro_memory_structure_adjust_
  #define f_macro_memory_structure_adjust(status, structure, type, length) \
    status = f_memory_structure_adjust(length, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_adjust_

/**
 * Delete a generic memory structure.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_delete_
  #define f_macro_memory_structure_delete(status, structure, type) \
    status = f_memory_structure_resize(0, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_delete_

/**
 * Destroy a generic memory structure.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_destroy_
  #define f_macro_memory_structure_destroy(status, structure, type) \
    status = f_memory_structure_adjust(0, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_destroy_

/**
 * Delete a generic memory structure.
 *
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_delete_simple_
  #define f_macro_memory_structure_delete_simple(structure, type) \
    f_memory_structure_resize(0, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_delete_simple_

/**
 * Destroy a generic memory structure.
 *
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_destroy_simple_
  #define f_macro_memory_structure_destroy_simple(structure, type) \
    f_memory_structure_adjust(0, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_destroy_simple_

/**
 * Increase a generic memory structure.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_increase_
  #define f_macro_memory_structure_increase(status, structure, type) \
    status = f_memory_structure_increase(sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_increase_

/**
 * Increase a generic memory structure by some amount.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 * amount:    the amount to increase the size of the array by.
 */
#ifndef _di_f_macro_memory_structure_increase_by_
  #define f_macro_memory_structure_increase_by(status, structure, type, amount) \
    status = f_memory_structure_increase_by(amount, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_increase_by_

/**
 * Decrease a generic memory structure by some amount.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 * amount:    the amount to decrease the size of the array by.
 */
#ifndef _di_f_macro_memory_structure_decrease_by_
  #define f_macro_memory_structure_decrease_by(status, structure, type, amount) \
    status = f_memory_structure_decrease_by(amount, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_decrease_by_

/**
 * Decimate a generic memory structure by some amount.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 * amount:    the amount to decimate the size of the array by.
 */
#ifndef _di_f_macro_memory_structure_decimate_by_
  #define f_macro_memory_structure_decimate_by(status, structure, type, amount) \
    status = f_memory_structure_decimate_by(amount, sizeof(type), (void **) &structure.array, &structure.used, &structure.size);
#endif // _di_f_macro_memory_structure_decimate_by_

/**
 * Reset a generic memory stuctures to 0 (clear all values).
 *
 * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
 *
 * structures: the structures to operate on.
 */
#ifndef _di_f_macro_memory_structures_clear_
  #define f_macro_memory_structures_clear(structures) \
    structures.array = 0; \
    structures.size = 0; \
    structures.used = 0;
#endif // _di_f_macro_memory_structures_clear_

/**
 * Resize a generic memory structures.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structures type.
 * length:         the new size of the array.
 * type_length:    the data type of the length variable type.
 */
#ifndef _di_f_macro_memory_structures_resize_
  #define f_macro_memory_structures_resize(status, structures, type_structure, type_structures, length, type_length) \
    status = F_none; \
    if (length < structures.size) { \
      for (register type_length _macro__i = structures.size - length; _macro__i < structures.size; ++_macro__i) { \
        status = f_memory_structure_resize(0, sizeof(type_structure), (void **) &structures.array[_macro__i].array, &structures.array[_macro__i].used, &structures.array[_macro__i].size); \
        if (F_status_is_error(status)) break; \
      } \
    } \
    if (F_status_is_error_not(status)) status = f_memory_structure_resize(0, sizeof(type_structures), (void **) &structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_resize_

/**
 * Adjust a generic memory structures.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structures type.
 * length:         the new size of the array.
 * type_length:    the data type of the length variable type.
 */
#ifndef _di_f_macro_memory_structures_adjust_
  #define f_macro_memory_structures_adjust(status, structures, type_structure, type_structures, length, type_length) \
    status = F_none; \
    if (length < structures.size) { \
      for (register type_length _macro__i = structures.size - length; _macro__i < structures.size; ++_macro__i) { \
        status = f_memory_structure_adjust(0, sizeof(type_structure), (void **) &structures.array[_macro__i].array, &structures.array[_macro__i].used, &structures.array[_macro__i].size); \
        if (F_status_is_error(status)) break; \
      } \
    } \
    if (F_status_is_error_not(status)) status = f_memory_structure_adjust(0, sizeof(type_structures), (void **) &structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_adjust_

/**
 * Delete a generic memory structures.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structures type.
 */
#ifndef _di_f_macro_memory_structures_delete_
  #define f_macro_memory_structures_delete(status, structures, type_structure, type_structures) \
    structures.used = structures.size; \
    while (structures.used) { \
      structures.used--; \
      status = f_memory_structure_resize(0, sizeof(type_structure), (void **) &structures.array[structures.used].array, &structures.array[structures.used].used, &structures.array[structures.used].size); \
      if (F_status_is_error(status)) break; \
    } \
    if (F_status_is_error_not(status)) status = f_memory_structure_resize(0, sizeof(type_structures), (void **) & structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_delete_

/**
 * Destroy a generic memory structures.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structures type.
 */
#ifndef _di_f_macro_memory_structures_destroy_
  #define f_macro_memory_structures_destroy(status, structures, type_structure, type_structures) \
    structures.used = structures.size; \
    while (structures.used) { \
      structures.used--; \
      status = f_memory_structure_adjust(0, sizeof(type_structure), (void **) &structures.array[structures.used].array, &structures.array[structures.used].used, &structures.array[structures.used].size); \
      if (F_status_is_error(status)) break; \
    } \
    if (F_status_is_error_not(status)) status = f_memory_structure_adjust(0, sizeof(type_structures), (void **) & structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_destroy_

/**
 * Delete a generic memory structures.
 *
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structures type.
 */
#ifndef _di_f_macro_memory_structures_delete_simple_
  #define f_macro_memory_structures_delete_simple(structures, type_structure, type_structures) \
    structures.used = structures.size; \
    while (structures.used) { \
      structures.used--; \
      f_memory_structure_resize(0, sizeof(type_structure), (void **) &structures.array[structures.used].array, &structures.array[structures.used].used, &structures.array[structures.used].size); \
    } \
    f_memory_structure_resize(0, sizeof(type_structures), (void **) & structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_delete_simple_

/**
 * Destroy a generic memory structures.
 *
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structures type.
 */
#ifndef _di_f_macro_memory_structures_destroy_simple_
  #define f_macro_memory_structures_destroy_simple(structures, type_structure, type_structures) \
    structures.used = structures.size; \
    while (structures.used) { \
      structures.used--; \
      f_memory_structure_adjust(0, sizeof(type_structure), (void **) &structures.array[structures.used].array, &structures.array[structures.used].used, &structures.array[structures.used].size); \
    } \
    f_memory_structure_adjust(0, sizeof(type_structures), (void **) & structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_destroy_simple_

/**
 * Increase a generic memory structures by 1.
 *
 * This only increases if the structure.used + 1 is greater than structure.size.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stuctures: the structures type.
 * type_length:    the data type of the length variable type.
 */
#ifndef _di_f_macro_memory_structures_increase_
  #define f_macro_memory_structures_increase(status, structures, type_structures, type_length) \
    status = f_memory_structure_increase(sizeof(type_structures), (void **) &structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_increase_

/**
 * Increase a generic memory structures by the given amount.
 *
 * This only increases if the structure.used + amount is greater than structure.size.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stuctures: the structures type.
 * type_length:    the data type of the length variable type.
 * amount:         the amount to increase by.
 */
#ifndef _di_f_macro_memory_structures_increase_by_
  #define f_macro_memory_structures_increase_by(status, structures, type_structures, type_length, amount) \
    status = f_memory_structure_increase_by(amount, sizeof(type_structures), (void **) &structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_increase_by_

/**
 * Decrease a generic memory structures by the given amount.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structures type.
 * type_length:    the data type of the length variable type.
 * amount:         the amount to decrease by.
 */
#ifndef _di_f_macro_memory_structures_decrease_by_
  #define f_macro_memory_structures_decrease_by(status, structures, type_structure, type_structures, type_length, amount) \
    if (amount && structures.size) { \
      f_macro_memory_structures_resize(status, structures, type_structure, type_structures, (amount < structures.size ? structures.size - amount : 0), type_length); \
    } \
    status = f_memory_structure_decrease_by(amount, sizeof(type_structures), (void **) &structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_decrease_by_

/**
 * Decimate a generic memory structures by the given amount.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structures type.
 * type_length:    the data type of the length variable type.
 * amount:         the amount to decimate by.
 */
#ifndef _di_f_macro_memory_structures_decimate_by_
  #define f_macro_memory_structures_decimate_by(status, structures, type_structure, type_structures, type_length, amount) \
    if (amount && structures.size) { \
      f_macro_memory_structures_adjust(status, structures, type_structure, type_structures, (amount < structures.size ? structures.size - amount : 0), type_length); \
    } \
    status = f_memory_structure_decimate_by(amount, sizeof(type_structures), (void **) &structures.array, &structures.used, &structures.size);
#endif // _di_f_macro_memory_structures_decimate_by_

/**
 * Provide a macro for calling other macros for incrementing a buffer.
 *
 * If the used + step is greater than size, then increase by step_default.
 * If step_default exceeds f_array_length_t_size, then attempt to increment by step.
 * If step exceeds f_array_length_t_size, set status to error_too_large.
 *
 * Be sure to check size for error after calling this.
 *
 * status:          the status to return.
 * structures:      the structures to operate on.
 * step:            the step to increase by, must be less than or equal to step_default.
 * step_default:    the default step to increase by if memory allows.
 * macro_resize:    the resize structure macro to call that excepts the exact arguments: (status, structure, length).
 * error_too_large: the error status to return when f_array_length_t_size would be exceeded.
 */
#ifndef _di_f_macro_memory_structure_macro_increment_
  #define f_macro_memory_structure_macro_increment(status, structure, step, step_default, macro_resize, error_too_large) \
    if (structure.used + step > structure.size) { \
      if (structure.used + step_default > f_array_length_t_size) { \
        if (structure.used + step > f_array_length_t_size) { \
          status = F_status_set_error(error_too_large); \
        } \
        else { \
          macro_resize(status, structure, structure.used + step); \
        } \
      } \
      else { \
        macro_resize(status, structure, structure.size + step_default); \
      } \
    }
#endif // _di_f_macro_memory_structure_macro_increment_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_memory_common_h
