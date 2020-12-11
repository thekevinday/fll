/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines tuple string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_tuple_h
#define _F_string_tuple_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string tuple consisting of a set of three strings.
 *
 * one: A string representing the first string in the tuple.
 * two: A string representing the second string in the tuple.
 * three: A string representing the third string in the tuple.
 */
#ifndef _di_f_string_tuple_t_
  typedef struct {
    f_string_dynamic_t one;
    f_string_dynamic_t two;
    f_string_dynamic_t three;
  } f_string_tuple_t;

  #define f_string_tuple_t_initialize { f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define f_macro_string_tuple_t_clear(tuple) \
    tuple.one.array = 0; \
    tuple.one.size = 0; \
    tuple.one.used = 0; \
    tuple.two.array = 0; \
    tuple.two.size = 0; \
    tuple.two.used = 0; \
    tuple.three.array = 0; \
    tuple.three.size = 0; \
    tuple.three.used = 0;

  #define f_macro_string_tuple_t_delete(status, tuple) \
    f_macro_string_dynamic_t_delete(status, tuple.one) \
    if (status == F_none) { \
      f_macro_string_dynamic_t_delete(status, tuple.two) \
    } \
    if (status == F_none) { \
      f_macro_string_dynamic_t_delete(status, tuple.three) \
    }

  #define f_macro_string_tuple_t_destroy(status, tuple) \
    f_macro_string_dynamic_t_destroy(status, tuple.one) \
    if (status == F_none) { \
      f_macro_string_dynamic_t_destroy(status, tuple.two) \
    } \
    if (status == F_none) { \
      f_macro_string_dynamic_t_destroy(status, tuple.three) \
    }

  #define f_macro_string_tuple_t_delete_simple(tuple) \
    f_macro_string_dynamic_t_delete_simple(tuple.one) \
    f_macro_string_dynamic_t_delete_simple(tuple.two) \
    f_macro_string_dynamic_t_delete_simple(tuple.three)

  #define f_macro_string_tuple_t_destroy_simple(tuple) \
    f_macro_string_dynamic_t_destroy_simple(tuple.one) \
    f_macro_string_dynamic_t_destroy_simple(tuple.two) \
    f_macro_string_dynamic_t_destroy_simple(tuple.three)
#endif // _di_f_string_tuple_t_

/**
 * An array of string tuples.
 *
 * array: the array of string tuples.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_tuples_t_
  typedef struct {
    f_string_tuple_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_tuples_t;

  #define f_string_tuples_t_initialize f_string_statics_t_initialize

  #define f_macro_string_tuples_t_clear(tuples) \
    tuples.array = 0; \
    tuples.size = 0; \
    tuples.used = 0;

  #define f_macro_string_tuples_t_new(status, tuples, length) \
    f_macro_string_tuples_t_clear(tuples) \
    status = f_memory_new((void **) & tuples.array, sizeof(f_string_tuple_t), length); \
    if (status == F_none) { \
      tuples.size = length; \
      tuples.used = 0; \
    }

  #define f_macro_string_tuples_t_delete(status, tuples) \
    status = F_none; \
    tuples.used = tuples.size; \
    while (tuples.used) { \
      tuples.used--; \
      f_macro_string_tuple_t_delete(status, tuples.array[tuples.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & tuples.array, sizeof(f_string_tuple_t), tuples.size); \
    if (status == F_none) tuples.size = 0;

  #define f_macro_string_tuples_t_destroy(status, tuples) \
    status = F_none; \
    tuples.used = tuples.size; \
    while (tuples.used) { \
      tuples.used--; \
      f_macro_string_tuple_t_destroy(status, tuples.array[tuples.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & tuples.array, sizeof(f_string_tuple_t), tuples.size); \
    if (status == F_none) tuples.size = 0;

  #define f_macro_string_tuples_t_delete_simple(tuples) \
    tuples.used = tuples.size; \
    while (tuples.used) { \
      tuples.used--; \
      f_macro_string_tuple_t_delete_simple(tuples.array[tuples.used]); \
    } \
    f_memory_delete((void **) & tuples.array, sizeof(f_string_tuple_t), tuples.size); \
    tuples.size = 0;

  #define f_macro_string_tuples_t_destroy_simple(tuples) \
    tuples.used = tuples.size; \
    while (tuples.used) { \
      tuples.used--; \
      f_macro_string_tuple_t_destroy_simple(tuples.array[tuples.used]); \
    } \
    f_memory_destroy((void **) & tuples.array, sizeof(f_string_tuple_t), tuples.size); \
    tuples.size = 0;

  #define f_macro_string_tuples_t_resize(status, tuples, new_length) \
    status = F_none; \
    if (new_length < tuples.size) { \
      for (f_array_length_t _macro__i = tuples.size - new_length; _macro__i < tuples.size; _macro__i++) { \
        f_macro_string_tuple_t_delete(status, tuples.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & tuples.array, sizeof(f_string_tuple_t), tuples.size, new_length); \
    if (status == F_none) { \
      if (new_length > tuples.size) { \
        for (f_array_length_t _macro__i = tuples.size; _macro__i < new_length; _macro__i++) { \
          memset(&tuples.array[_macro__i], 0, sizeof(f_string_tuple_t)); \
        } \
      } \
      tuples.size = new_length; \
      if (tuples.used > tuples.size) tuples.used = new_length; \
    }

  #define f_macro_string_tuples_t_adjust(status, tuples, new_length) \
    status = F_none; \
    if (new_length < tuples.size) { \
      for (f_array_length_t _macro__i = tuples.size - new_length; _macro__i < tuples.size; _macro__i++) { \
        f_macro_string_tuple_t_destroy(status, tuples.array[_macro__i], f_string_tuple_t); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & tuples.array, sizeof(f_string_tuple_t), tuples.size, new_length); \
    if (status == F_none) { \
      if (new_length > tuples.size) { \
        for (f_array_length_t _macro__i = tuples.size; _macro__i < new_length; _macro__i++) { \
          memset(&tuples.array[_macro__i], 0, sizeof(f_string_tuple_t)); \
        } \
      } \
      tuples.size = new_length; \
      if (tuples.used > tuples.size) tuples.used = new_length; \
    }
#endif // _di_f_string_tuples_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_tuple_h
