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
#ifndef _F_thread_id_h
#define _F_thread_id_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A typedef representing pthread_t.
 */
#ifndef _di_f_thread_id_t_
  typedef pthread_t f_thread_id_t;

  #define f_thread_id_t_initialize 0

  #define macro_f_thread_id_t_clear(id) id = 0;
#endif // _di_f_thread_id_t_

/**
 * An array of thread IDs.
 *
 * Properties:
 *   - array: The array of f_thread_id_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_ids_t_
  typedef struct {
    f_thread_id_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_thread_ids_t;

  #define f_thread_ids_t_initialize { 0, 0, 0 }

  #define macro_f_thread_ids_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_thread_ids_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_thread_ids_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_id_h
