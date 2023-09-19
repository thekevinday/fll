/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines status type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_type_status_h
#define _F_type_status_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A status intended to be used as the return value status of some function or operation.
 */
#ifndef _di_f_status_t_
  typedef uint16_t f_status_t;

  #define f_status_t_initialize F_okay
#endif // _di_f_status_t_

/**
 * This holds an array of f_status_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of f_status_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_statuss_t_
  typedef struct {
    f_status_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_statuss_t;

  #define f_statuss_t_initialize { 0, 0, 0 }

  #define macro_f_statuss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_statuss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_statuss_t_

/**
 * This holds an array of f_statuss_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of f_status_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_statusss_t_
  typedef struct {
    f_statuss_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_statusss_t;

  #define f_statusss_t_initialize { 0, 0, 0 }

  #define macro_f_statusss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_statusss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_statusss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_status_h
