/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by limit related functionality.
 *
 * This is auto-included by limit.h and should not need to be explicitly included.
 */
#ifndef _F_limit_common_h
#define _F_limit_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A limit value structure.
 *
 * rlim_cur: the soft limit.
 * rlim_max: the hard limit.
 */
#ifndef _di_f_limit_value_t_
  typedef struct rlimit f_limit_value_t;

  #define f_limit_value_t_initialize { 0, 0 }

  #define f_macro_limit_value_t_clear(value) \
    value.rlim_cur = 0; \
    value.rlim_max = 0;
#endif // _di_f_limit_value_t_

/**
 * An array of limit values.
 *
 * array: An array of limit values.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_limit_values_t_
  typedef struct {
    f_limit_value_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_limit_values_t;

  #define f_limit_values_t_initialize { 0, 0, 0 }

  #define f_macro_limit_values_t_clear(values) f_macro_memory_structure_t_clear(values)

  #define f_macro_limit_values_t_new(status, values, length) f_macro_memory_structure_t_new(status, values, f_limit_value_t, length)

  #define f_macro_limit_values_t_delete(status, values)  f_macro_memory_structure_t_delete(status, values, f_limit_value_t)
  #define f_macro_limit_values_t_destroy(status, values) f_macro_memory_structure_t_destroy(status, values, f_limit_value_t)

  #define f_macro_limit_values_t_delete_simple(values)  f_macro_memory_structure_t_delete_simple(values, f_limit_value_t)
  #define f_macro_limit_values_t_destroy_simple(values) f_macro_memory_structure_t_destroy_simple(values, f_limit_value_t)

  #define f_macro_limit_values_t_resize(status, values, new_length) f_macro_memory_structure_t_resize(status, values, f_limit_value_t, new_length)
  #define f_macro_limit_values_t_adjust(status, values, new_length) f_macro_memory_structure_t_adjust(status, values, f_limit_value_t, new_length)
#endif // _di_f_limit_values_t_

/**
 * A limit value structure.
 *
 * type:  the limit resource type code.
 * value: the limit value containing the soft and hard limit.
 */
#ifndef _di_f_limit_set_t_
  typedef struct {
    int type;
    f_limit_value_t value;
  } f_limit_set_t;

  #define f_limit_set_t_initialize { 0, 0 }

  #define f_macro_limit_set_t_clear(set) \
    set.type = 0; \
    set.value = 0;
#endif // _di_f_limit_set_t_

/**
 * An array of limit sets.
 *
 * array: An array of limit sets.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_limit_sets_t_
  typedef struct {
    f_limit_set_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_limit_sets_t;

  #define f_limit_sets_t_initialize { 0, 0, 0 }

  #define f_macro_limit_sets_t_clear(sets) f_macro_memory_structure_t_clear(sets)

  #define f_macro_limit_sets_t_new(status, sets, length) f_macro_memory_structure_t_new(status, sets, f_limit_set_t, length)

  #define f_macro_limit_sets_t_delete(status, sets)  f_macro_memory_structure_t_delete(status, sets, f_limit_set_t)
  #define f_macro_limit_sets_t_destroy(status, sets) f_macro_memory_structure_t_destroy(status, sets, f_limit_set_t)

  #define f_macro_limit_sets_t_delete_simple(sets)  f_macro_memory_structure_t_delete_simple(sets, f_limit_set_t)
  #define f_macro_limit_sets_t_destroy_simple(sets) f_macro_memory_structure_t_destroy_simple(sets, f_limit_set_t)

  #define f_macro_limit_sets_t_resize(status, sets, new_length) f_macro_memory_structure_t_resize(status, sets, f_limit_set_t, new_length)
  #define f_macro_limit_sets_t_adjust(status, sets, new_length) f_macro_memory_structure_t_adjust(status, sets, f_limit_set_t, new_length)
#endif // _di_f_limit_sets_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_limit_common_h
