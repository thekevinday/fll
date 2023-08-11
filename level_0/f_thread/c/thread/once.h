/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by POSIX thread related functionality.
 *
 * This is auto-included by thread.h and should not need to be explicitly included.
 */
#ifndef _F_thread_once_h
#define _F_thread_once_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A typedef representing pthread_once_t.
 *
 * There are no delete functions and therefore no delete macros.
 */
#ifndef _di_f_thread_once_t_
  typedef pthread_once_t f_thread_once_t;

  #define f_thread_once_t_initialize PTHREAD_ONCE_INIT

  #define macro_f_thread_once_t_initialize_1(once) once
#endif // _di_f_thread_once_t_

/**
 * An array of thread onces.
 *
 * Properties:
 *   - array: The array of f_thread_once_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_onces_t_
  typedef struct {
    f_thread_once_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_thread_onces_t;

  #define f_thread_onces_t_initialize { 0, 0, 0 }

  #define macro_f_thread_onces_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_thread_onces_t_initialize_2(array, length) { array, length, length }

  #define macro_f_thread_onces_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_thread_onces_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_thread_onces_t_


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_once_h
