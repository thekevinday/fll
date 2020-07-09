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
#ifndef _di_f_statuss_
  typedef struct {
    f_status *array;
    f_array_length size;
    f_array_length used;
  } f_statuss;

  #define f_statuss_initialize { 0, 0, 0 }

  #define f_macro_statuss_clear(statuss) f_macro_memory_structure_clear(statuss)

  #define f_macro_statuss_new(status, statuss, length) f_macro_memory_structure_new(status, statuss, f_status, length)

  #define f_macro_statuss_delete(status, statuss)  f_macro_memory_structure_delete(status, statuss, f_status)
  #define f_macro_statuss_destroy(status, statuss) f_macro_memory_structure_destroy(status, statuss, f_status)

  #define f_macro_statuss_delete_simple(statuss)  f_macro_memory_structure_delete_simple(statuss, f_status)
  #define f_macro_statuss_destroy_simple(statuss) f_macro_memory_structure_destroy_simple(statuss, f_status)

  #define f_macro_statuss_resize(status, statuss, new_length) f_macro_memory_structure_resize(status, statuss, f_status, new_length)
  #define f_macro_statuss_adjust(status, statuss, new_length) f_macro_memory_structure_adjust(status, statuss, f_status, new_length)
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

  #define f_macro_statusss_clear(statusss) f_macro_memory_structures_clear(statusss)

  #define f_macro_statusss_new(status, statusss, length) f_macro_memory_structures_new(status, statusss, f_status, f_statuss, length)

  #define f_macro_statusss_delete(status, statusss)  f_macro_memory_structures_delete(status, statusss, f_status, f_statuss)
  #define f_macro_statusss_destroy(status, statusss) f_macro_memory_structures_destroy(status, statusss, f_status, f_statuss)

  #define f_macro_statusss_delete_simple(statusss)  f_macro_memory_structures_delete_simple(statusss, f_status, f_statuss)
  #define f_macro_statusss_destroy_simple(statusss) f_macro_memory_structures_destroy_simple(statusss, f_status, f_statuss)

  #define f_macro_statusss_resize(status, statusss, new_length) f_macro_memory_structures_resize(status, statusss, f_status, f_statuss, new_length, f_array_length)
  #define f_macro_statusss_adjust(status, statusss, new_length) f_macro_memory_structures_adjust(status, statusss, f_status, f_statuss, new_length, f_array_length)
#endif // _di_f_statuss_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_status_array_h
