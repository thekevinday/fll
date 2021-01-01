/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by POSIX thread related functionality.
 *
 * This is auto-included by thread.h and should not need to be explicitly included.
 */
#ifndef _F_thread_common_h
#define _F_thread_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure containing basic thread information.
 *
 * attributes: The thread attributes (which is a union).
 * id:         The thread identifier.
 * result:     The result of the thread on exit.
 */
#ifndef _di_f_thread_set_t_
  typedef struct {
    pthread_attr_t attributes;
    pthread_t id;
    int result;
  } f_thread_set_t;

  #define f_thread_set_t_initialize { { 0 }, 0, 0 }

  // This does not clear the thread.attributes.__size array (may need to memset() against a sizeof(pthread_attr_t)).
  #define f_macro_thread_set_t_clear(thread) \
    thread.attributes.__align = 0; \
    thread.id = 0;
#endif // _di_f_thread_set_t_

/**
 * An array of f_thread_set_t.
 *
 * array: the array of f_thread_set_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_sets_t_
  typedef struct {
    f_thread_set_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_sets_t;

  #define f_thread_sets_t_initialize { 0, 0, 0 }

  #define f_macro_thread_sets_t_clear(threads) \
    threads.array = 0; \
    threads.size = 0; \
    threads.used = 0;

  #define f_macro_threads_new(status, threads, length) \
    f_macro_thread_sets_t_clear(threads) \
    status = f_memory_new((void **) & threads.array, sizeof(f_thread_set_t), length); \
    if (status == F_none) { \
      threads.size = length; \
      threads.used = 0; \
    }

  #define f_macro_thread_sets_t_delete(status, threads) \
    status = f_memory_delete((void **) & threads.array, sizeof(f_thread_set_t), threads.size); \
    if (status == F_none) { \
      threads.used = 0; \
      threads.size = 0; \
    }

  #define f_macro_thread_sets_t_destroy(status, threads) \
    status = f_memory_destroy((void **) & threads.array, sizeof(f_thread_set_t), threads.size); \
    if (status == F_none) { \
      threads.used = 0; \
      threads.size = 0; \
    }

  #define f_macro_thread_sets_t_delete_simple(threads) \
    f_memory_delete((void **) & threads.array, sizeof(f_thread_set_t), threads.size); \
    threads.used = 0; \
    threads.size = 0;

  #define f_macro_thread_sets_t_destroy_simple(threads) \
    f_memory_destroy((void **) & threads.array, sizeof(f_thread_set_t), threads.size); \
    threads.used = 0; \
    threads.size = 0;

  #define f_macro_thread_sets_t_resize(status, threads, new_length) \
    status = f_memory_resize((void **) & threads.array, sizeof(f_thread_set_t), threads.size, new_length); \
    if (status == F_none) { \
      if (new_length > threads.size) { \
        for (f_array_length_t _macro__i = threads.size; _macro__i < new_length; _macro__i++) { \
          memset(&threads.array[_macro__i], 0, sizeof(f_thread_set_t)); \
        } \
      } \
      threads.size = new_length; \
      if (threads.used > threads.size) threads.used = new_length; \
    }

  #define f_macro_thread_sets_t_adjust(status, threads, new_length) \
    status = f_memory_adjust((void **) & threads.array, sizeof(f_thread_set_t), threads.size, new_length); \
    if (status == F_none) { \
      if (new_length > threads.size) { \
        for (f_array_length_t _macro__i = threads.size; _macro__i < new_length; _macro__i++) { \
          memset(&threads.array[_macro__i], 0, sizeof(f_thread_set_t)); \
        } \
      } \
      threads.size = new_length; \
      if (threads.used > threads.size) threads.used = new_length; \
    }
#endif // _di_f_thread_sets_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_common_h
