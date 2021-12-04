/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
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
 * rlim_cur: The soft limit.
 * rlim_max: The hard limit.
 */
#ifndef _di_f_limit_value_t_
  typedef struct rlimit f_limit_value_t;

  #define f_limit_value_t_initialize { 0, 0 }

  #define macro_f_limit_value_t_clear(value) \
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

  #define macro_f_limit_values_t_clear(values) macro_f_memory_structure_clear(values)

  #define macro_f_limit_values_t_resize(status, values, length) macro_f_memory_structure_resize(status, values, f_limit_value_t, length)
  #define macro_f_limit_values_t_adjust(status, values, length) macro_f_memory_structure_adjust(status, values, f_limit_value_t, length)

  #define macro_f_limit_values_t_delete_simple(values)  macro_f_memory_structure_delete_simple(values, f_limit_value_t)
  #define macro_f_limit_values_t_destroy_simple(values) macro_f_memory_structure_destroy_simple(values, f_limit_value_t)

  #define macro_f_limit_values_t_increase(status, step, values)      macro_f_memory_structure_increase(status, step, values, f_limit_value_t)
  #define macro_f_limit_values_t_increase_by(status, values, amount) macro_f_memory_structure_increase_by(status, values, f_limit_value_t, amount)
  #define macro_f_limit_values_t_decrease_by(status, values, amount) macro_f_memory_structure_decrease_by(status, values, f_limit_value_t, amount)
  #define macro_f_limit_values_t_decimate_by(status, values, amount) macro_f_memory_structure_decimate_by(status, values, f_limit_value_t, amount)
#endif // _di_f_limit_values_t_

/**
 * A limit value structure.
 *
 * type:  The limit resource type code.
 * value: The limit value containing the soft and hard limit.
 */
#ifndef _di_f_limit_set_t_
  typedef struct {
    int type;
    f_limit_value_t value;
  } f_limit_set_t;

  #define f_limit_set_t_initialize { 0, 0 }

  #define macro_f_limit_set_t_clear(set) \
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

  #define macro_f_limit_sets_t_clear(sets) macro_f_memory_structure_clear(sets)

  #define macro_f_limit_sets_t_resize(status, sets, length) macro_f_memory_structure_resize(status, sets, f_limit_set_t, length)
  #define macro_f_limit_sets_t_adjust(status, sets, length) macro_f_memory_structure_adjust(status, sets, f_limit_set_t, length)

  #define macro_f_limit_sets_t_delete_simple(sets)  macro_f_memory_structure_delete_simple(sets, f_limit_set_t)
  #define macro_f_limit_sets_t_destroy_simple(sets) macro_f_memory_structure_destroy_simple(sets, f_limit_set_t)

  #define macro_f_limit_sets_t_increase(status, step, sets)      macro_f_memory_structure_increase(status, step, sets, f_limit_set_t)
  #define macro_f_limit_sets_t_increase_by(status, sets, amount) macro_f_memory_structure_increase_by(status, sets, f_limit_set_t, amount)
  #define macro_f_limit_sets_t_decrease_by(status, sets, amount) macro_f_memory_structure_decrease_by(status, sets, f_limit_set_t, amount)
  #define macro_f_limit_sets_t_decimate_by(status, sets, amount) macro_f_memory_structure_decimate_by(status, sets, f_limit_set_t, amount)
#endif // _di_f_limit_sets_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_limit_common_h
