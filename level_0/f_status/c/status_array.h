/**
 * FLL - Level 0
 *
 * Project: Status
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides status arrays that require memory operations.
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
#ifndef _di_f_statuss_
  typedef struct {
    f_status *array;
    f_array_length size;
    f_array_length used;
  } f_statuss;

  #define f_statuss_initialize { 0, 0, 0 }

  #define f_macro_statuss_clear(status) f_macro_memory_structure_clear(statuses)

  #define f_macro_statuss_new(status, statuses, length) f_macro_memory_structure_new(status, statuses, f_status, length)

  #define f_macro_statuss_delete(status, statuses)  f_macro_memory_structure_delete(status, statuses, f_status)
  #define f_macro_statuss_destroy(status, statuses) f_macro_memory_structure_destroy(status, statuses, f_status)

  #define f_macro_statuss_delete_simple(statuses)  f_macro_memory_structure_delete_simple(statuses, f_status)
  #define f_macro_statuss_destroy_simple(statuses) f_macro_memory_structure_destroy_simple(statuses, f_status)

  #define f_macro_statuss_resize(status, statuses, new_length) f_macro_memory_structure_resize(status, statuses, f_status, new_length)
  #define f_macro_statuss_adjust(status, statuses, new_length) f_macro_memory_structure_adjust(status, statuses, f_status, new_length)
#endif // _di_f_statuss_

/**
 * An array of an array of status codes.
 *
 * array: the array of an array of status codes.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_statusss_
  typedef struct {
    f_statuss *array;

    f_array_length size;
    f_array_length used;
  } f_statusss;

  #define f_statusss_initialize { 0, 0, 0 }

  #define f_macro_statusss_clear(statuses) f_macro_memory_structures_clear(statuses)

  #define f_macro_statusss_new(status, statuses, length) f_macro_memory_structures_new(status, statuses, f_status, length)

  #define f_macro_statusss_delete(status, statuses)  f_macro_memory_structures_delete(status, statuses, f_status)
  #define f_macro_statusss_destroy(status, statuses) f_macro_memory_structures_destroy(status, statuses, f_status)

  #define f_macro_statusss_delete_simple(statuses)  f_macro_memory_structures_delete_simple(statuses, f_status)
  #define f_macro_statusss_destroy_simple(statuses) f_macro_memory_structures_destroy_simple(statuses, f_status)

  #define f_macro_statusss_resize(status, statuses, new_length) f_macro_memory_structures_resize(status, statuses, f_status, new_length)
  #define f_macro_statusss_adjust(status, statuses, new_length) f_macro_memory_structures_adjust(status, statuses, f_status, new_length)
#endif // _di_f_statuss_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_status_array_h
