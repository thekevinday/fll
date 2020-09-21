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
 * Reset a generic memory stucture to 0 (clear all values).
 *
 * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
 *
 * structure: the structure to operate on.
 */
#ifndef _di_f_macro_memory_structure_clear_
  #define f_macro_memory_structure_t_clear(structure) \
    structure.array = 0; \
    structure.size = 0; \
    structure.used = 0;
#endif // _di_f_macro_memory_structure_clear_

/**
 * Create a new generic memory structure.
 *
 * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 * length:    the new size of the array.
 */
#ifndef _di_f_macro_memory_structure_new_
  #define f_macro_memory_structure_t_new(status, structure, type, length) \
    f_macro_memory_structure_t_clear(structure) \
    status = f_memory_new((void **) & structure.array, sizeof(type), length); \
    if (status == F_none) { \
      structure.size = length; \
      structure.used = 0; \
    }
#endif // _di_f_macro_memory_structure_new_

/**
 * Delete a generic memory structure.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_delete_
  #define f_macro_memory_structure_t_delete(status, structure, type) \
    status = f_memory_delete((void **) & structure.array, sizeof(type), structure.size); \
    if (status == F_none) { \
      structure.size = 0; \
      structure.used = 0; \
    }
#endif // _di_f_macro_memory_structure_delete_

/**
 * Destroy a generic memory structure.
 *
 * status:    the status to return.
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_destroy_
  #define f_macro_memory_structure_t_destroy(status, structure, type) \
    status = f_memory_destroy((void **) & structure.array, sizeof(type), structure.size); \
    if (status == F_none) { \
      structure.size = 0; \
      structure.used = 0; \
    }
#endif // _di_f_macro_memory_structure_destroy_

/**
 * Delete a generic memory structure.
 *
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_delete_simple_
  #define f_macro_memory_structure_t_delete_simple(structure, type) \
    if (f_memory_delete((void **) & structure.array, sizeof(type), structure.size) == F_none) { \
      structure.size = 0; \
      structure.used = 0; \
    }
#endif // _di_f_macro_memory_structure_delete_simple_

/**
 * Destroy a generic memory structure.
 *
 * structure: the structure to operate on.
 * type:      the structure type.
 */
#ifndef _di_f_macro_memory_structure_destroy_simple_
  #define f_macro_memory_structure_t_destroy_simple(structure, type) \
    if (f_memory_destroy((void **) & structure.array, sizeof(type), structure.size) == F_none) { \
      structure.size = 0; \
      structure.used = 0; \
    }
#endif // _di_f_macro_memory_structure_destroy_simple_

/**
 * Resize a generic memory structure.
 *
 * status:     the status to return.
 * structure:  the structure to operate on.
 * type:       the structure type.
 * new_length: the new size of the array.
 */
#ifndef _di_f_macro_memory_structure_resize_
  #define f_macro_memory_structure_t_resize(status, structure, type, new_length) \
    status = f_memory_resize((void **) & structure.array, sizeof(type), structure.size, new_length); \
    if (status == F_none) { \
      structure.size = new_length; \
      if (structure.used > structure.size) structure.used = new_length; \
    }
#endif // _di_f_macro_memory_structure_resize_

/**
 * Adjust a generic memory structure.
 *
 * status:     the status to return.
 * structure:  the structure to operate on.
 * type:       the structure type.
 * new_length: the new size of the array.
 */
#ifndef _di_f_macro_memory_structure_adjust_
  #define f_macro_memory_structure_t_adjust(status, structure, type, new_length) \
    status = f_memory_adjust((void **) & structure.array, sizeof(type), structure.size, new_length); \
    if (status == F_none) { \
      structure.size = new_length; \
      if (structure.used > structure.size) structure.used = new_length; \
    }
#endif // _di_f_macro_memory_structure_adjust_

/**
 * Reset a generic memory stuctures to 0 (clear all values).
 *
 * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
 *
 * structures: the structures to operate on.
 */
#ifndef _di_f_macro_memory_structures_clear_
  #define f_macro_memory_structures_t_clear(structures) \
    structures.array = 0; \
    structures.size = 0; \
    structures.used = 0;
#endif // _di_f_macro_memory_structures_clear_

/**
 * Create a new generic memory structures.
 *
 * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stuctures: the structure type.
 * new_length:     the new size of the array.
 */
#ifndef _di_f_macro_memory_structures_new_
  #define f_macro_memory_structures_t_new(status, structures, type_structures, new_length) \
    f_macro_memory_structures_t_clear(structures) \
    status = f_memory_new((void **) & structures.array, sizeof(type_structures), new_length); \
    if (status == F_none) { \
      structures.size = new_length; \
      structures.used = 0; \
    }
#endif // _di_f_macro_memory_structures_new_

/**
 * Delete a generic memory structures.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structure type.
 */
#ifndef _di_f_macro_memory_structures_delete_
  #define f_macro_memory_structures_t_delete(status, structures, type_structure, type_structures) \
    status = F_none; \
    structures.used = structures.size; \
    while (structures.used > 0) { \
      structures.used--; \
      f_macro_memory_structure_t_delete(status, structures.array[structures.used], type_structure); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & structures.array, sizeof(type_structures), structures.size); \
    if (status == F_none) structures.size = 0;
#endif // _di_f_macro_memory_structures_delete_

/**
 * Destroy a generic memory structures.
 *
 * status:         the status to return.
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structure type.
 */
#ifndef _di_f_macro_memory_structures_destroy_
  #define f_macro_memory_structures_t_destroy(status, structures, type_structure, type_structures) \
    status = F_none; \
    structures.used = structures.size; \
    while (structures.used > 0) { \
      structures.used--; \
      f_macro_memory_structure_t_destroy(status, structures.array[structures.used], type_structure); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & structures.array, sizeof(type_structures), structures.size); \
    if (status == F_none) structures.size = 0;
#endif // _di_f_macro_memory_structures_destroy_

/**
 * Delete a generic memory structures.
 *
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structure type.
 */
#ifndef _di_f_macro_memory_structures_delete_simple_
  #define f_macro_memory_structures_t_delete_simple(structures, type_structure, type_structures) \
    structures.used = structures.size; \
    while (structures.used > 0) { \
      structures.used--; \
      f_macro_memory_structure_t_delete_simple(structures.array[structures.used], type_structure); \
    } \
    if (!structures.used) { \
      if (f_memory_delete((void **) & structures.array, sizeof(type_structures), structures.size)) { \
        structures.size = 0; \
      } \
    }
#endif // _di_f_macro_memory_structures_delete_simple_

/**
 * Destroy a generic memory structures.
 *
 * structures:     the structures to operate on.
 * type_stucture:  the structure type.
 * type_stuctures: the structure type.
 */
#ifndef _di_f_macro_memory_structures_destroy_simple_
  #define f_macro_memory_structures_t_destroy_simple(structures, type_structure, type_structures) \
    structures.used = structures.size; \
    while (structures.used > 0) { \
      structures.used--; \
      f_macro_memory_structure_t_destroy_simple(structures.array[structures.used], type_structure); \
    } \
    if (!structures.used) { \
      if (f_memory_destroy((void **) & structures.array, sizeof(type_structures), structures.size)) { \
        structures.size = 0; \
      } \
    }
#endif // _di_f_macro_memory_structures_destroy_simple_

/**
 * Resize a generic memory structures.
 *
 * status:          the status to return.
 * structures:      the structures to operate on.
 * type_stucture:   the structure type.
 * type_stuctures:  the structure type.
 * new_length:      the new size of the array.
 * length_variable: the data type of the length variable.
 */
#ifndef _di_f_macro_memory_structures_resize_
  #define f_macro_memory_structures_t_resize(status, structures, type_structure, type_structures, new_length, length_variable) \
    status = F_none; \
    if (new_length < structures.size) { \
      for (length_variable _macro__i = structures.size - new_length; _macro__i < structures.size; _macro__i++) { \
        f_macro_memory_structure_t_delete(status, structures.array[_macro__i], type_structure); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & structures.array, sizeof(type_structures), structures.size, new_length); \
    if (status == F_none) { \
      if (new_length > structures.size) { \
        for (length_variable _macro__i = structures.size; _macro__i < new_length; _macro__i++) { \
          memset(&structures.array[_macro__i], 0, sizeof(type_structures)); \
        } \
      } \
      structures.size = new_length; \
      if (structures.used > structures.size) structures.used = new_length; \
    }
#endif // _di_f_macro_memory_structures_resize_

/**
 * Adjust a generic memory structures.
 *
 * status:          the status to return.
 * structures:      the structures to operate on.
 * type_stucture:   the structure type.
 * type_stuctures:  the structure type.
 * new_length:      the new size of the array.
 * length_variable: the data type of the length variable.
 */
#ifndef _di_f_macro_memory_structures_adjust_
  #define f_macro_memory_structures_t_adjust(status, structures, type_structure, type_structures, new_length, length_variable) \
    status = F_none; \
    if (new_length < structures.size) { \
      for (length_variable _macro__i = structures.size - new_length; _macro__i < structures.size; _macro__i++) { \
        f_macro_memory_structure_t_destroy(status, structures.array[_macro__i], type_structure); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & structures.array, sizeof(type_structures), structures.size, new_length); \
    if (status == F_none) { \
      if (new_length > structures.size) { \
        for (length_variable _macro__i = structures.size; _macro__i < new_length; _macro__i++) { \
          memset(&structures.array[_macro__i], 0, sizeof(type_structures)); \
        } \
      } \
      structures.size = new_length; \
      if (structures.used > structures.size) structures.used = new_length; \
    }
#endif // _di_f_macro_memory_structures_adjust_

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
 * macro_resize:    the resize structure macro to call that excepts the exact arguments: (status, structure, new_length).
 * error_too_large: the error status to return when f_array_length_t_size would be exceeded.
 */
#ifndef _di_f_macro_memory_structure_macro_increment_
  #define f_macro_memory_structure_macro_increment(status, structure, step, step_default, macro_resize, error_too_large) \
    if (structure.used + step > structure.size) { \
      if (structure.used + step_default > f_array_length_t_size) { \
        if (structure.used + step > structure.size > f_array_length_t_size) { \
          status = F_status_set_error(error_too_large); \
        } \
        else { \
          macro_resize(status, structure, structure.size + step); \
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

#endif // _F_memory_structure_h
