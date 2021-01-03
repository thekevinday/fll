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
 * A typedef representing pthread_attr_t.
 */
#ifndef _di_f_thread_attribute_t_
  typedef pthread_attr_t f_thread_attribute_t;

  #define f_thread_attribute_t_initialize { 0 }

  // This does not clear the thread.attributes.__size array (may need to memset() against a sizeof(pthread_attr_t)).
  #define f_macro_thread_attribute_t_clear(attribute) attribute.__align = 0;
#endif // _di_f_thread_attribute_t_

/**
 * An array of f_thread_attribute_t.
 *
 * array: the array of f_thread_attribute_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_attributes_t_
  typedef struct {
    f_thread_attribute_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_attributes_t;

  #define f_thread_attributes_t_initialize { 0, 0, 0 }

  #define f_macro_thread_attributes_t_clear(attributes) \
    attributes.array = 0; \
    attributes.size = 0; \
    attributes.used = 0;

  #define f_macro_thread_attributes_new(status, attributes, length) \
    f_macro_thread_attributes_t_clear(attributes) \
    status = f_memory_new((void **) & attributes.array, sizeof(f_thread_attribute_t), length); \
    if (status == F_none) { \
      attributes.size = length; \
      attributes.used = 0; \
    }

  #define f_macro_thread_attributes_t_delete(status, attributes) \
    status = f_memory_delete((void **) & attributes.array, sizeof(f_thread_attribute_t), attributes.size); \
    if (status == F_none) { \
      attributes.used = 0; \
      attributes.size = 0; \
    }

  #define f_macro_thread_attributes_t_destroy(status, attributes) \
    status = f_memory_destroy((void **) & attributes.array, sizeof(f_thread_attribute_t), attributes.size); \
    if (status == F_none) { \
      attributes.used = 0; \
      attributes.size = 0; \
    }

  #define f_macro_thread_attributes_t_delete_simple(attributes) \
    f_memory_delete((void **) & attributes.array, sizeof(f_thread_attribute_t), attributes.size); \
    attributes.used = 0; \
    attributes.size = 0;

  #define f_macro_thread_attributes_t_destroy_simple(attributes) \
    f_memory_destroy((void **) & attributes.array, sizeof(f_thread_attribute_t), attributes.size); \
    attributes.used = 0; \
    attributes.size = 0;

  #define f_macro_thread_attributes_t_resize(status, attributes, new_length) \
    status = f_memory_resize((void **) & attributes.array, sizeof(f_thread_attribute_t), attributes.size, new_length); \
    if (status == F_none) { \
      if (new_length > attributes.size) { \
        for (f_array_length_t _macro__i = attributes.size; _macro__i < new_length; _macro__i++) { \
          memset(&attributes.array[_macro__i], 0, sizeof(f_thread_attribute_t)); \
        } \
      } \
      attributes.size = new_length; \
      if (attributes.used > attributes.size) attributes.used = new_length; \
    }

  #define f_macro_thread_attributes_t_adjust(status, attributes, new_length) \
    status = f_memory_adjust((void **) & attributes.array, sizeof(f_thread_attribute_t), attributes.size, new_length); \
    if (status == F_none) { \
      if (new_length > attributes.size) { \
        for (f_array_length_t _macro__i = attributes.size; _macro__i < new_length; _macro__i++) { \
          memset(&attributes.array[_macro__i], 0, sizeof(f_thread_attribute_t)); \
        } \
      } \
      attributes.size = new_length; \
      if (attributes.used > attributes.size) attributes.used = new_length; \
    }
#endif // _di_f_thread_attributes_t_

/**
 * A typedef representing pthread_cond_t.
 */
#ifndef _di_f_thread_condition_t_
  typedef pthread_cond_t f_thread_condition_t;

  #define f_thread_condition_t_initialize 0

  #define f_macro_thread_condition_t_clear(condition) condition = 0;
#endif // _di_f_thread_condition_t_

/**
 * An array of thread conditions.
 *
 * array: the array of f_thread_condition_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_conditions_t_
  typedef struct {
    f_thread_condition_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_conditions_t;

  #define f_thread_conditions_t_initialize { 0, 0, 0 }

  #define f_macro_thread_conditions_t_clear(conditions) \
    conditions.array = 0; \
    conditions.size = 0; \
    conditions.used = 0;

  #define f_macro_thread_conditions_new(status, conditions, length) \
    f_macro_thread_conditions_t_clear(conditions) \
    status = f_memory_new((void **) & conditions.array, sizeof(f_thread_condition_t), length); \
    if (status == F_none) { \
      conditions.size = length; \
      conditions.used = 0; \
    }

  #define f_macro_thread_conditions_t_delete(status, conditions) \
    status = f_memory_delete((void **) & conditions.array, sizeof(f_thread_condition_t), conditions.size); \
    if (status == F_none) { \
      conditions.used = 0; \
      conditions.size = 0; \
    }

  #define f_macro_thread_conditions_t_destroy(status, conditions) \
    status = f_memory_destroy((void **) & conditions.array, sizeof(f_thread_condition_t), conditions.size); \
    if (status == F_none) { \
      conditions.used = 0; \
      conditions.size = 0; \
    }

  #define f_macro_thread_conditions_t_delete_simple(conditions) \
    f_memory_delete((void **) & conditions.array, sizeof(f_thread_condition_t), conditions.size); \
    conditions.used = 0; \
    conditions.size = 0;

  #define f_macro_thread_conditions_t_destroy_simple(conditions) \
    f_memory_destroy((void **) & conditions.array, sizeof(f_thread_condition_t), conditions.size); \
    conditions.used = 0; \
    conditions.size = 0;

  #define f_macro_thread_conditions_t_resize(status, conditions, new_length) \
    status = f_memory_resize((void **) & conditions.array, sizeof(f_thread_condition_t), conditions.size, new_length); \
    if (status == F_none) { \
      if (new_length > conditions.size) { \
        for (f_array_length_t _macro__i = conditions.size; _macro__i < new_length; _macro__i++) { \
          memset(&conditions.array[_macro__i], 0, sizeof(f_thread_condition_t)); \
        } \
      } \
      conditions.size = new_length; \
      if (conditions.used > conditions.size) conditions.used = new_length; \
    }

  #define f_macro_thread_conditions_t_adjust(status, conditions, new_length) \
    status = f_memory_adjust((void **) & conditions.array, sizeof(f_thread_condition_t), conditions.size, new_length); \
    if (status == F_none) { \
      if (new_length > conditions.size) { \
        for (f_array_length_t _macro__i = conditions.size; _macro__i < new_length; _macro__i++) { \
          memset(&conditions.array[_macro__i], 0, sizeof(f_thread_condition_t)); \
        } \
      } \
      conditions.size = new_length; \
      if (conditions.used > conditions.size) conditions.used = new_length; \
    }
#endif // _di_f_thread_conditions_t_

/**
 * A typedef representing pthread_t.
 */
#ifndef _di_f_thread_id_t_
  typedef pthread_t f_thread_id_t;

  #define f_thread_id_t_initialize 0

  #define f_macro_thread_id_t_clear(id) id = 0;
#endif // _di_f_thread_id_t_

/**
 * An array of thread IDs.
 *
 * array: the array of f_thread_id_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_ids_t_
  typedef struct {
    f_thread_id_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_ids_t;

  #define f_thread_ids_t_initialize { 0, 0, 0 }

  #define f_macro_thread_ids_t_clear(ids) \
    ids.array = 0; \
    ids.size = 0; \
    ids.used = 0;

  #define f_macro_thread_ids_new(status, ids, length) \
    f_macro_thread_ids_t_clear(ids) \
    status = f_memory_new((void **) & ids.array, sizeof(f_thread_id_t), length); \
    if (status == F_none) { \
      ids.size = length; \
      ids.used = 0; \
    }

  #define f_macro_thread_ids_t_delete(status, ids) \
    status = f_memory_delete((void **) & ids.array, sizeof(f_thread_id_t), ids.size); \
    if (status == F_none) { \
      ids.used = 0; \
      ids.size = 0; \
    }

  #define f_macro_thread_ids_t_destroy(status, ids) \
    status = f_memory_destroy((void **) & ids.array, sizeof(f_thread_id_t), ids.size); \
    if (status == F_none) { \
      ids.used = 0; \
      ids.size = 0; \
    }

  #define f_macro_thread_ids_t_delete_simple(ids) \
    f_memory_delete((void **) & ids.array, sizeof(f_thread_id_t), ids.size); \
    ids.used = 0; \
    ids.size = 0;

  #define f_macro_thread_ids_t_destroy_simple(ids) \
    f_memory_destroy((void **) & ids.array, sizeof(f_thread_id_t), ids.size); \
    ids.used = 0; \
    ids.size = 0;

  #define f_macro_thread_ids_t_resize(status, ids, new_length) \
    status = f_memory_resize((void **) & ids.array, sizeof(f_thread_id_t), ids.size, new_length); \
    if (status == F_none) { \
      if (new_length > ids.size) { \
        for (f_array_length_t _macro__i = ids.size; _macro__i < new_length; _macro__i++) { \
          memset(&ids.array[_macro__i], 0, sizeof(f_thread_id_t)); \
        } \
      } \
      ids.size = new_length; \
      if (ids.used > ids.size) ids.used = new_length; \
    }

  #define f_macro_thread_ids_t_adjust(status, ids, new_length) \
    status = f_memory_adjust((void **) & ids.array, sizeof(f_thread_id_t), ids.size, new_length); \
    if (status == F_none) { \
      if (new_length > ids.size) { \
        for (f_array_length_t _macro__i = ids.size; _macro__i < new_length; _macro__i++) { \
          memset(&ids.array[_macro__i], 0, sizeof(f_thread_id_t)); \
        } \
      } \
      ids.size = new_length; \
      if (ids.used > ids.size) ids.used = new_length; \
    }
#endif // _di_f_thread_ids_t_

/**
 * A typedef representing pthread_key_t.
 */
#ifndef _di_f_thread_key_t_
  typedef pthread_key_t f_thread_key_t;

  #define f_thread_key_t_initialize 0

  #define f_macro_thread_key_t_clear(key) key = 0;
#endif // _di_f_thread_key_t_

/**
 * An array of thread keys.
 *
 * array: the array of f_thread_key_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_keys_t_
  typedef struct {
    f_thread_key_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_keys_t;

  #define f_thread_keys_t_initialize { 0, 0, 0 }

  #define f_macro_thread_keys_t_clear(keys) \
    keys.array = 0; \
    keys.size = 0; \
    keys.used = 0;

  #define f_macro_thread_keys_new(status, keys, length) \
    f_macro_thread_keys_t_clear(keys) \
    status = f_memory_new((void **) & keys.array, sizeof(f_thread_key_t), length); \
    if (status == F_none) { \
      keys.size = length; \
      keys.used = 0; \
    }

  #define f_macro_thread_keys_t_delete(status, keys) \
    status = f_memory_delete((void **) & keys.array, sizeof(f_thread_key_t), keys.size); \
    if (status == F_none) { \
      keys.used = 0; \
      keys.size = 0; \
    }

  #define f_macro_thread_keys_t_destroy(status, keys) \
    status = f_memory_destroy((void **) & keys.array, sizeof(f_thread_key_t), keys.size); \
    if (status == F_none) { \
      keys.used = 0; \
      keys.size = 0; \
    }

  #define f_macro_thread_keys_t_delete_simple(keys) \
    f_memory_delete((void **) & keys.array, sizeof(f_thread_key_t), keys.size); \
    keys.used = 0; \
    keys.size = 0;

  #define f_macro_thread_keys_t_destroy_simple(keys) \
    f_memory_destroy((void **) & keys.array, sizeof(f_thread_key_t), keys.size); \
    keys.used = 0; \
    keys.size = 0;

  #define f_macro_thread_keys_t_resize(status, keys, new_length) \
    status = f_memory_resize((void **) & keys.array, sizeof(f_thread_key_t), keys.size, new_length); \
    if (status == F_none) { \
      if (new_length > keys.size) { \
        for (f_array_length_t _macro__i = keys.size; _macro__i < new_length; _macro__i++) { \
          memset(&keys.array[_macro__i], 0, sizeof(f_thread_key_t)); \
        } \
      } \
      keys.size = new_length; \
      if (keys.used > keys.size) keys.used = new_length; \
    }

  #define f_macro_thread_keys_t_adjust(status, keys, new_length) \
    status = f_memory_adjust((void **) & keys.array, sizeof(f_thread_key_t), keys.size, new_length); \
    if (status == F_none) { \
      if (new_length > keys.size) { \
        for (f_array_length_t _macro__i = keys.size; _macro__i < new_length; _macro__i++) { \
          memset(&keys.array[_macro__i], 0, sizeof(f_thread_key_t)); \
        } \
      } \
      keys.size = new_length; \
      if (keys.used > keys.size) keys.used = new_length; \
    }
#endif // _di_f_thread_keys_t_

/**
 * A typedef representing pthread_rwlock_t (read/write lock).
 */
#ifndef _di_f_thread_lock_t_
  typedef pthread_rwlock_t f_thread_lock_t;

  #define f_thread_lock_t_initialize 0

  #define f_macro_thread_lock_t_clear(lock) lock = 0;
#endif // _di_f_thread_lock_t_

/**
 * An array of thread locks.
 *
 * array: the array of f_thread_lock_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_locks_t_
  typedef struct {
    f_thread_lock_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_locks_t;

  #define f_thread_locks_t_initialize { 0, 0, 0 }

  #define f_macro_thread_locks_t_clear(locks) \
    locks.array = 0; \
    locks.size = 0; \
    locks.used = 0;

  #define f_macro_thread_locks_new(status, locks, length) \
    f_macro_thread_locks_t_clear(locks) \
    status = f_memory_new((void **) & locks.array, sizeof(f_thread_lock_t), length); \
    if (status == F_none) { \
      locks.size = length; \
      locks.used = 0; \
    }

  #define f_macro_thread_locks_t_delete(status, locks) \
    status = f_memory_delete((void **) & locks.array, sizeof(f_thread_lock_t), locks.size); \
    if (status == F_none) { \
      locks.used = 0; \
      locks.size = 0; \
    }

  #define f_macro_thread_locks_t_destroy(status, locks) \
    status = f_memory_destroy((void **) & locks.array, sizeof(f_thread_lock_t), locks.size); \
    if (status == F_none) { \
      locks.used = 0; \
      locks.size = 0; \
    }

  #define f_macro_thread_locks_t_delete_simple(locks) \
    f_memory_delete((void **) & locks.array, sizeof(f_thread_lock_t), locks.size); \
    locks.used = 0; \
    locks.size = 0;

  #define f_macro_thread_locks_t_destroy_simple(locks) \
    f_memory_destroy((void **) & locks.array, sizeof(f_thread_lock_t), locks.size); \
    locks.used = 0; \
    locks.size = 0;

  #define f_macro_thread_locks_t_resize(status, locks, new_length) \
    status = f_memory_resize((void **) & locks.array, sizeof(f_thread_lock_t), locks.size, new_length); \
    if (status == F_none) { \
      if (new_length > locks.size) { \
        for (f_array_length_t _macro__i = locks.size; _macro__i < new_length; _macro__i++) { \
          memset(&locks.array[_macro__i], 0, sizeof(f_thread_lock_t)); \
        } \
      } \
      locks.size = new_length; \
      if (locks.used > locks.size) locks.used = new_length; \
    }

  #define f_macro_thread_locks_t_adjust(status, locks, new_length) \
    status = f_memory_adjust((void **) & locks.array, sizeof(f_thread_lock_t), locks.size, new_length); \
    if (status == F_none) { \
      if (new_length > locks.size) { \
        for (f_array_length_t _macro__i = locks.size; _macro__i < new_length; _macro__i++) { \
          memset(&locks.array[_macro__i], 0, sizeof(f_thread_lock_t)); \
        } \
      } \
      locks.size = new_length; \
      if (locks.used > locks.size) locks.used = new_length; \
    }
#endif // _di_f_thread_locks_t_

/**
 * A typedef representing pthread_mutex_t.
 */
#ifndef _di_f_thread_mutex_t_
  typedef pthread_mutex_t f_thread_mutex_t;

  #define f_thread_mutex_t_initialize 0

  #define f_macro_thread_mutex_t_clear(mutex) mutex = 0;
#endif // _di_f_thread_mutex_t_

/**
 * An array of thread mutexes.
 *
 * array: the array of f_thread_mutex_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_mutexs_t_
  typedef struct {
    f_thread_mutex_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_mutexs_t;

  #define f_thread_mutexs_t_initialize { 0, 0, 0 }

  #define f_macro_thread_mutexs_t_clear(mutexs) \
    mutexs.array = 0; \
    mutexs.size = 0; \
    mutexs.used = 0;

  #define f_macro_thread_mutexs_new(status, mutexs, length) \
    f_macro_thread_mutexs_t_clear(mutexs) \
    status = f_memory_new((void **) & mutexs.array, sizeof(f_thread_mutex_t), length); \
    if (status == F_none) { \
      mutexs.size = length; \
      mutexs.used = 0; \
    }

  #define f_macro_thread_mutexs_t_delete(status, mutexs) \
    status = f_memory_delete((void **) & mutexs.array, sizeof(f_thread_mutex_t), mutexs.size); \
    if (status == F_none) { \
      mutexs.used = 0; \
      mutexs.size = 0; \
    }

  #define f_macro_thread_mutexs_t_destroy(status, mutexs) \
    status = f_memory_destroy((void **) & mutexs.array, sizeof(f_thread_mutex_t), mutexs.size); \
    if (status == F_none) { \
      mutexs.used = 0; \
      mutexs.size = 0; \
    }

  #define f_macro_thread_mutexs_t_delete_simple(mutexs) \
    f_memory_delete((void **) & mutexs.array, sizeof(f_thread_mutex_t), mutexs.size); \
    mutexs.used = 0; \
    mutexs.size = 0;

  #define f_macro_thread_mutexs_t_destroy_simple(mutexs) \
    f_memory_destroy((void **) & mutexs.array, sizeof(f_thread_mutex_t), mutexs.size); \
    mutexs.used = 0; \
    mutexs.size = 0;

  #define f_macro_thread_mutexs_t_resize(status, mutexs, new_length) \
    status = f_memory_resize((void **) & mutexs.array, sizeof(f_thread_mutex_t), mutexs.size, new_length); \
    if (status == F_none) { \
      if (new_length > mutexs.size) { \
        for (f_array_length_t _macro__i = mutexs.size; _macro__i < new_length; _macro__i++) { \
          memset(&mutexs.array[_macro__i], 0, sizeof(f_thread_mutex_t)); \
        } \
      } \
      mutexs.size = new_length; \
      if (mutexs.used > mutexs.size) mutexs.used = new_length; \
    }

  #define f_macro_thread_mutexs_t_adjust(status, mutexs, new_length) \
    status = f_memory_adjust((void **) & mutexs.array, sizeof(f_thread_mutex_t), mutexs.size, new_length); \
    if (status == F_none) { \
      if (new_length > mutexs.size) { \
        for (f_array_length_t _macro__i = mutexs.size; _macro__i < new_length; _macro__i++) { \
          memset(&mutexs.array[_macro__i], 0, sizeof(f_thread_mutex_t)); \
        } \
      } \
      mutexs.size = new_length; \
      if (mutexs.used > mutexs.size) mutexs.used = new_length; \
    }
#endif // _di_f_thread_mutexs_t_

/**
 * A typedef representing pthread_mutex_attribute_t.
 */
#ifndef _di_f_thread_mutex_attribute_t_
  typedef pthread_mutexattr_t f_thread_mutex_attribute_t;

  #define f_thread_mutex_attribute_t_initialize 0

  #define f_macro_thread_mutex_attribute_t_clear(mutex_attribute) mutex_attribute = 0;
#endif // _di_f_thread_mutex_attribute_t_

/**
 * An array of thread mutex_attributees.
 *
 * array: the array of f_thread_mutex_attribute_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_mutex_attributes_t_
  typedef struct {
    f_thread_mutex_attribute_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_mutex_attributes_t;

  #define f_thread_mutex_attributes_t_initialize { 0, 0, 0 }

  #define f_macro_thread_mutex_attributes_t_clear(mutex_attributes) \
    mutex_attributes.array = 0; \
    mutex_attributes.size = 0; \
    mutex_attributes.used = 0;

  #define f_macro_thread_mutex_attributes_new(status, mutex_attributes, length) \
    f_macro_thread_mutex_attributes_t_clear(mutex_attributes) \
    status = f_memory_new((void **) & mutex_attributes.array, sizeof(f_thread_mutex_attribute_t), length); \
    if (status == F_none) { \
      mutex_attributes.size = length; \
      mutex_attributes.used = 0; \
    }

  #define f_macro_thread_mutex_attributes_t_delete(status, mutex_attributes) \
    status = f_memory_delete((void **) & mutex_attributes.array, sizeof(f_thread_mutex_attribute_t), mutex_attributes.size); \
    if (status == F_none) { \
      mutex_attributes.used = 0; \
      mutex_attributes.size = 0; \
    }

  #define f_macro_thread_mutex_attributes_t_destroy(status, mutex_attributes) \
    status = f_memory_destroy((void **) & mutex_attributes.array, sizeof(f_thread_mutex_attribute_t), mutex_attributes.size); \
    if (status == F_none) { \
      mutex_attributes.used = 0; \
      mutex_attributes.size = 0; \
    }

  #define f_macro_thread_mutex_attributes_t_delete_simple(mutex_attributes) \
    f_memory_delete((void **) & mutex_attributes.array, sizeof(f_thread_mutex_attribute_t), mutex_attributes.size); \
    mutex_attributes.used = 0; \
    mutex_attributes.size = 0;

  #define f_macro_thread_mutex_attributes_t_destroy_simple(mutex_attributes) \
    f_memory_destroy((void **) & mutex_attributes.array, sizeof(f_thread_mutex_attribute_t), mutex_attributes.size); \
    mutex_attributes.used = 0; \
    mutex_attributes.size = 0;

  #define f_macro_thread_mutex_attributes_t_resize(status, mutex_attributes, new_length) \
    status = f_memory_resize((void **) & mutex_attributes.array, sizeof(f_thread_mutex_attribute_t), mutex_attributes.size, new_length); \
    if (status == F_none) { \
      if (new_length > mutex_attributes.size) { \
        for (f_array_length_t _macro__i = mutex_attributes.size; _macro__i < new_length; _macro__i++) { \
          memset(&mutex_attributes.array[_macro__i], 0, sizeof(f_thread_mutex_attribute_t)); \
        } \
      } \
      mutex_attributes.size = new_length; \
      if (mutex_attributes.used > mutex_attributes.size) mutex_attributes.used = new_length; \
    }

  #define f_macro_thread_mutex_attributes_t_adjust(status, mutex_attributes, new_length) \
    status = f_memory_adjust((void **) & mutex_attributes.array, sizeof(f_thread_mutex_attribute_t), mutex_attributes.size, new_length); \
    if (status == F_none) { \
      if (new_length > mutex_attributes.size) { \
        for (f_array_length_t _macro__i = mutex_attributes.size; _macro__i < new_length; _macro__i++) { \
          memset(&mutex_attributes.array[_macro__i], 0, sizeof(f_thread_mutex_attribute_t)); \
        } \
      } \
      mutex_attributes.size = new_length; \
      if (mutex_attributes.used > mutex_attributes.size) mutex_attributes.used = new_length; \
    }
#endif // _di_f_thread_mutex_attributes_t_

/**
 * A typedef representing pthread_once_t.
 */
#ifndef _di_f_thread_once_t_
  typedef pthread_once_t f_thread_once_t;

  #define f_thread_once_t_initialize 0

  #define f_macro_thread_once_t_clear(once) once = 0;
#endif // _di_f_thread_once_t_

/**
 * An array of thread onces.
 *
 * array: the array of f_thread_once_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_thread_onces_t_
  typedef struct {
    f_thread_once_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_onces_t;

  #define f_thread_onces_t_initialize { 0, 0, 0 }

  #define f_macro_thread_onces_t_clear(onces) \
    onces.array = 0; \
    onces.size = 0; \
    onces.used = 0;

  #define f_macro_thread_onces_new(status, onces, length) \
    f_macro_thread_onces_t_clear(onces) \
    status = f_memory_new((void **) & onces.array, sizeof(f_thread_once_t), length); \
    if (status == F_none) { \
      onces.size = length; \
      onces.used = 0; \
    }

  #define f_macro_thread_onces_t_delete(status, onces) \
    status = f_memory_delete((void **) & onces.array, sizeof(f_thread_once_t), onces.size); \
    if (status == F_none) { \
      onces.used = 0; \
      onces.size = 0; \
    }

  #define f_macro_thread_onces_t_destroy(status, onces) \
    status = f_memory_destroy((void **) & onces.array, sizeof(f_thread_once_t), onces.size); \
    if (status == F_none) { \
      onces.used = 0; \
      onces.size = 0; \
    }

  #define f_macro_thread_onces_t_delete_simple(onces) \
    f_memory_delete((void **) & onces.array, sizeof(f_thread_once_t), onces.size); \
    onces.used = 0; \
    onces.size = 0;

  #define f_macro_thread_onces_t_destroy_simple(onces) \
    f_memory_destroy((void **) & onces.array, sizeof(f_thread_once_t), onces.size); \
    onces.used = 0; \
    onces.size = 0;

  #define f_macro_thread_onces_t_resize(status, onces, new_length) \
    status = f_memory_resize((void **) & onces.array, sizeof(f_thread_once_t), onces.size, new_length); \
    if (status == F_none) { \
      if (new_length > onces.size) { \
        for (f_array_length_t _macro__i = onces.size; _macro__i < new_length; _macro__i++) { \
          memset(&onces.array[_macro__i], 0, sizeof(f_thread_once_t)); \
        } \
      } \
      onces.size = new_length; \
      if (onces.used > onces.size) onces.used = new_length; \
    }

  #define f_macro_thread_onces_t_adjust(status, onces, new_length) \
    status = f_memory_adjust((void **) & onces.array, sizeof(f_thread_once_t), onces.size, new_length); \
    if (status == F_none) { \
      if (new_length > onces.size) { \
        for (f_array_length_t _macro__i = onces.size; _macro__i < new_length; _macro__i++) { \
          memset(&onces.array[_macro__i], 0, sizeof(f_thread_once_t)); \
        } \
      } \
      onces.size = new_length; \
      if (onces.used > onces.size) onces.used = new_length; \
    }
#endif // _di_f_thread_onces_t_

/**
 * A structure containing basic thread information.
 *
 * attributes: The thread attributes (which is a union).
 * id:         The thread identifier.
 * result:     The result of the thread on exit.
 */
#ifndef _di_f_thread_set_t_
  typedef struct {
    f_thread_attribute_t attributes;
    f_thread_id_t id;
    int result;
  } f_thread_set_t;

  #define f_thread_set_t_initialize { f_thread_attribute_t_initialize, f_thread_id_t_initialize, 0 }


  #define f_macro_thread_set_t_clear(thread) \
    f_macro_thread_attribute_t_clear(thread.attributes) \
    f_macro_thread_id_t_clear(thread.id)
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

  #define f_macro_thread_sets_new(status, threads, length) \
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
