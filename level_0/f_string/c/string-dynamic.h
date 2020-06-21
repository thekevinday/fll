/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines dynamic (and static) string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_dynamic_h
#define _F_string_dynamic_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string that is analogous to f_string_dynamic but intended for static-only uses.
 *
 * The f_string_static type should never be directly allocated or deallocated.
 *
 * A special f_macro_string_static_initialize() is provided for the special purpose of easily initialize a static string.
 *
 * string: the string.
 * size: total amount of space available.
 * used: total number of space used.
 */
#ifndef _di_f_string_static_
  typedef struct {
    f_string string;

    f_string_length size;
    f_string_length used;
  } f_string_static;

  #define f_string_static_initialize { 0, 0, 0 }

  #define f_macro_string_static_clear(string_static) \
    string_static.string = 0; \
    string_static.size = 0; \
    string_static.used = 0;

  #define f_macro_string_static_initialize(string, length) { string, length, length }
#endif // _di_f_string_static_

/**
 * A string that supports contains a size attribute to handle dynamic allocations and deallocations.
 *
 * Save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * This is a sub-type of f_string_static, allowing it to be passed into any f_string_static type.
 * It is recommended that f_string_static are not otherwise casted into f_string_dynamic to avoid potential memory allocation issues.
 *
 * string: the string.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamic_
  typedef f_string_static f_string_dynamic;

  #define f_string_dynamic_initialize f_string_static_initialize

  #define f_macro_string_dynamic_clear(dynamic) f_macro_string_static_clear(dynamic)

  #define f_macro_string_dynamic_new(status, dynamic, new_length) \
    f_macro_string_dynamic_clear(dynamic) \
    status = f_memory_new((void **) & dynamic.string, sizeof(f_string), new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_delete(status, dynamic) \
    status = f_memory_delete((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    if (status == F_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_destroy(status, dynamic) \
    status = f_memory_destroy((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    if (status == F_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_delete_simple(dynamic) \
    f_memory_delete((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_string_dynamic_destroy_simple(dynamic) \
    f_memory_destroy((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_string_dynamic_resize(status, dynamic, new_length) \
    status = f_memory_resize((void **) & dynamic.string, sizeof(f_string), dynamic.size, new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }

  #define f_macro_string_dynamic_adjust(status, dynamic, new_length) \
    status = f_memory_adjust((void **) & dynamic.string, sizeof(f_string), dynamic.size, new_length); \
    if (status == F_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }
#endif // _di_f_string_dynamic_

/**
 * An array of static strings.
 *
 * array: the array of static strings.
 * size: total amount of space available.
 * used: total number of space used.
 */
#ifndef _di_f_string_statics_
  typedef struct {
    f_string_static *array;

    f_array_length size;
    f_array_length used;
  } f_string_statics;

  #define f_string_statics_initialize { 0, 0, 0 }

  #define f_macro_string_statics_clear(statics) \
    statics.array = 0; \
    statics.size = 0; \
    statics.used = 0;
#endif // _di_f_string_statics_

/**
 * An array of dynamic strings.
 *
 * array: the array of dynamic strings.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamics_
  typedef f_string_statics f_string_dynamics;

  #define f_string_dynamics_initialize f_string_statics_initialize

  #define f_macro_string_dynamics_clear(dynamics) f_macro_string_statics_clear(dynamics)

  #define f_macro_string_dynamics_new(status, dynamics, length) \
    f_macro_string_dynamics_clear(dynamics) \
    status = f_memory_new((void **) & dynamics.array, sizeof(f_string_dynamic), length); \
    if (status == F_none) { \
      dynamics.size = length; \
      dynamics.used = 0; \
    }

  #define f_macro_string_dynamics_delete(status, dynamics) \
    status = F_none; \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_delete(status, dynamics.array[dynamics.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size); \
    if (status == F_none) dynamics.size = 0;

  #define f_macro_string_dynamics_destroy(status, dynamics) \
    status = F_none; \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_destroy(status, dynamics.array[dynamics.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size); \
    if (status == F_none) dynamics.size = 0;

  #define f_macro_string_dynamics_delete_simple(dynamics) \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_delete_simple(dynamics.array[dynamics.used]); \
      if (dynamics.used == 0) { \
        if (f_memory_delete((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size)) { \
          dynamics.size = 0; \
        } \
      } \
    }

  #define f_macro_string_dynamics_destroy_simple(dynamics) \
    dynamics.used = dynamics.size; \
    while (dynamics.used > 0) { \
      dynamics.used--; \
      f_macro_string_dynamic_destroy_simple(dynamics.array[dynamics.used]); \
      if (dynamics.used == 0) { \
        if (f_memory_destroy((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size)) { \
          dynamics.size = 0; \
        } \
      } \
    }

  #define f_macro_string_dynamics_resize(status, dynamics, new_length) \
    status = F_none; \
    if (new_length < dynamics.size) { \
      f_array_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; i++) { \
        f_macro_string_dynamic_delete(status, dynamics.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size, new_length); \
    if (status == F_none) { \
      if (new_length > dynamics.size) { \
        f_array_length i = dynamics.size; \
        for (; i < new_length; i++) { \
          memset(&dynamics.array[i], 0, sizeof(f_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }

  #define f_macro_string_dynamics_adjust(status, dynamics, new_length) \
    status = F_none; \
    if (new_length < dynamics.size) { \
      f_array_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; i++) { \
        f_macro_string_dynamic_destroy(status, dynamics.array[i], f_string_dynamic); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size, new_length); \
    if (status == F_none) { \
      if (new_length > dynamics.size) { \
        f_array_length i = dynamics.size; \
        for (; i < new_length; i++) { \
          memset(&dynamics.array[i], 0, sizeof(f_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }
#endif // _di_f_string_dynamics_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_dynamic_h
