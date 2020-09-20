/**
 * FLL - Level 0
 *
 * Project: Status
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides status arrays that require memory operations.
 *
 * Because memory requires status.h, this is moved to a separate file to reduce potential circular dependency issues.
 */
#ifndef _F_status_array_h
#define _F_status_array_h

// fll-0 includes
#include <level_0/memory.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of status codes.
 *
 * array: An array of status codes.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_statuss_t_
  typedef struct {
    f_status_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_statuss_t;

  #define f_statuss_t_initialize { 0, 0, 0 }

  #define f_macro_statuss_t_clear(statuss) f_macro_memory_structure_t_clear(statuss)

  #define f_macro_statuss_t_new(status, statuss, length) f_macro_memory_structure_t_new(status, statuss, f_status_t, length)

  #define f_macro_statuss_t_delete(status, statuss)  f_macro_memory_structure_t_delete(status, statuss, f_status_t)
  #define f_macro_statuss_t_destroy(status, statuss) f_macro_memory_structure_t_destroy(status, statuss, f_status_t)

  #define f_macro_statuss_t_delete_simple(statuss)  f_macro_memory_structure_t_delete_simple(statuss, f_status_t)
  #define f_macro_statuss_t_destroy_simple(statuss) f_macro_memory_structure_t_destroy_simple(statuss, f_status_t)

  #define f_macro_statuss_t_resize(status, statuss, new_length) f_macro_memory_structure_t_resize(status, statuss, f_status_t, new_length)
  #define f_macro_statuss_t_adjust(status, statuss, new_length) f_macro_memory_structure_t_adjust(status, statuss, f_status_t, new_length)
#endif // _di_f_statuss_t_

/**
 * An array of an array of status codes.
 *
 * array: the array of an array of status codes.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_statusss_t_
  typedef struct {
    f_statuss_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_statusss_t;

  #define f_statusss_t_initialize { 0, 0, 0 }

  #define f_macro_statusss_t_clear(statusss) f_macro_memory_structures_t_clear(statusss)

  #define f_macro_statusss_t_new(status, statusss, length) f_macro_memory_structures_t_new(status, statusss, f_status_t, f_statuss_t, length)

  #define f_macro_statusss_t_delete(status, statusss)  f_macro_memory_structures_t_delete(status, statusss, f_status_t, f_statuss_t)
  #define f_macro_statusss_t_destroy(status, statusss) f_macro_memory_structures_t_destroy(status, statusss, f_status_t, f_statuss_t)

  #define f_macro_statusss_t_delete_simple(statusss)  f_macro_memory_structures_t_delete_simple(statusss, f_status_t, f_statuss_t)
  #define f_macro_statusss_t_destroy_simple(statusss) f_macro_memory_structures_t_destroy_simple(statusss, f_status_t, f_statuss_t)

  #define f_macro_statusss_t_resize(status, statusss, new_length) f_macro_memory_structures_t_resize(status, statusss, f_status_t, f_statuss_t, new_length, f_array_length_t)
  #define f_macro_statusss_t_adjust(status, statusss, new_length) f_macro_memory_structures_t_adjust(status, statusss, f_status_t, f_statuss_t, new_length, f_array_length_t)
#endif // _di_f_statuss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_status_array_h
