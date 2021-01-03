/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines 3-tuple of string data called a triple (which is an ordered list of 3 strings).
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_triple_h
#define _F_string_triple_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string triple consisting of a set of three strings.
 *
 * one: A string representing the first string in the triple.
 * two: A string representing the second string in the triple.
 * three: A string representing the third string in the triple.
 */
#ifndef _di_f_string_triple_t_
  typedef struct {
    f_string_dynamic_t one;
    f_string_dynamic_t two;
    f_string_dynamic_t three;
  } f_string_triple_t;

  #define f_string_triple_t_initialize { f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define f_macro_string_triple_t_clear(triple) \
    triple.one.array = 0; \
    triple.one.size = 0; \
    triple.one.used = 0; \
    triple.two.array = 0; \
    triple.two.size = 0; \
    triple.two.used = 0; \
    triple.three.array = 0; \
    triple.three.size = 0; \
    triple.three.used = 0;

  #define f_macro_string_triple_t_delete(status, triple) \
    f_macro_string_dynamic_t_delete(status, triple.one) \
    if (status == F_none) { \
      f_macro_string_dynamic_t_delete(status, triple.two) \
    } \
    if (status == F_none) { \
      f_macro_string_dynamic_t_delete(status, triple.three) \
    }

  #define f_macro_string_triple_t_destroy(status, triple) \
    f_macro_string_dynamic_t_destroy(status, triple.one) \
    if (status == F_none) { \
      f_macro_string_dynamic_t_destroy(status, triple.two) \
    } \
    if (status == F_none) { \
      f_macro_string_dynamic_t_destroy(status, triple.three) \
    }

  #define f_macro_string_triple_t_delete_simple(triple) \
    f_macro_string_dynamic_t_delete_simple(triple.one) \
    f_macro_string_dynamic_t_delete_simple(triple.two) \
    f_macro_string_dynamic_t_delete_simple(triple.three)

  #define f_macro_string_triple_t_destroy_simple(triple) \
    f_macro_string_dynamic_t_destroy_simple(triple.one) \
    f_macro_string_dynamic_t_destroy_simple(triple.two) \
    f_macro_string_dynamic_t_destroy_simple(triple.three)
#endif // _di_f_string_triple_t_

/**
 * An array of string triples.
 *
 * array: the array of string triples.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_triples_t_
  typedef struct {
    f_string_triple_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_triples_t;

  #define f_string_triples_t_initialize f_string_statics_t_initialize

  #define f_macro_string_triples_t_clear(triples) \
    triples.array = 0; \
    triples.size = 0; \
    triples.used = 0;

  #define f_macro_string_triples_t_new(status, triples, length) \
    f_macro_string_triples_t_clear(triples) \
    status = f_memory_new((void **) & triples.array, sizeof(f_string_triple_t), length); \
    if (status == F_none) { \
      triples.size = length; \
      triples.used = 0; \
    }

  #define f_macro_string_triples_t_delete(status, triples) \
    status = F_none; \
    triples.used = triples.size; \
    while (triples.used) { \
      triples.used--; \
      f_macro_string_triple_t_delete(status, triples.array[triples.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & triples.array, sizeof(f_string_triple_t), triples.size); \
    if (status == F_none) triples.size = 0;

  #define f_macro_string_triples_t_destroy(status, triples) \
    status = F_none; \
    triples.used = triples.size; \
    while (triples.used) { \
      triples.used--; \
      f_macro_string_triple_t_destroy(status, triples.array[triples.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & triples.array, sizeof(f_string_triple_t), triples.size); \
    if (status == F_none) triples.size = 0;

  #define f_macro_string_triples_t_delete_simple(triples) \
    triples.used = triples.size; \
    while (triples.used) { \
      triples.used--; \
      f_macro_string_triple_t_delete_simple(triples.array[triples.used]); \
    } \
    f_memory_delete((void **) & triples.array, sizeof(f_string_triple_t), triples.size); \
    triples.size = 0;

  #define f_macro_string_triples_t_destroy_simple(triples) \
    triples.used = triples.size; \
    while (triples.used) { \
      triples.used--; \
      f_macro_string_triple_t_destroy_simple(triples.array[triples.used]); \
    } \
    f_memory_destroy((void **) & triples.array, sizeof(f_string_triple_t), triples.size); \
    triples.size = 0;

  #define f_macro_string_triples_t_resize(status, triples, new_length) \
    status = F_none; \
    if (new_length < triples.size) { \
      for (f_array_length_t _macro__i = triples.size - new_length; _macro__i < triples.size; _macro__i++) { \
        f_macro_string_triple_t_delete(status, triples.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & triples.array, sizeof(f_string_triple_t), triples.size, new_length); \
    if (status == F_none) { \
      triples.size = new_length; \
      if (triples.used > triples.size) triples.used = new_length; \
    }

  #define f_macro_string_triples_t_adjust(status, triples, new_length) \
    status = F_none; \
    if (new_length < triples.size) { \
      for (f_array_length_t _macro__i = triples.size - new_length; _macro__i < triples.size; _macro__i++) { \
        f_macro_string_triple_t_destroy(status, triples.array[_macro__i], f_string_triple_t); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & triples.array, sizeof(f_string_triple_t), triples.size, new_length); \
    if (status == F_none) { \
      triples.size = new_length; \
      if (triples.used > triples.size) triples.used = new_length; \
    }
#endif // _di_f_string_triples_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_triple_h
