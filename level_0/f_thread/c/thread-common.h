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

  #define f_macro_thread_attributes_t_clear(attributes) f_macro_memory_structure_t_clear(attributes)

  #define f_macro_thread_attributes_t_new(status, attributes, length) f_macro_memory_structure_t_new(status, attributes, f_thread_attribute_t, length)

  #define f_macro_thread_attributes_t_delete(status, attributes)  f_macro_memory_structure_t_delete(status, attributes, f_thread_attribute_t)
  #define f_macro_thread_attributes_t_destroy(status, attributes) f_macro_memory_structure_t_destroy(status, attributes, f_thread_attribute_t)

  #define f_macro_thread_attributes_t_delete_simple(attributes)  f_macro_memory_structure_t_delete_simple(attributes, f_thread_attribute_t)
  #define f_macro_thread_attributes_t_destroy_simple(attributes) f_macro_memory_structure_t_destroy_simple(attributes, f_thread_attribute_t)

  #define f_macro_thread_attributes_t_resize(status, attributes, new_length) f_macro_memory_structure_t_resize(status, attributes, f_thread_attribute_t, new_length)
  #define f_macro_thread_attributes_t_adjust(status, attributes, new_length) f_macro_memory_structure_t_adjust(status, attributes, f_thread_attribute_t, new_length)
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

  #define f_macro_thread_conditions_t_clear(conditions) f_macro_memory_structure_t_clear(conditions)

  #define f_macro_thread_conditions_t_new(status, conditions, length) f_macro_memory_structure_t_new(status, conditions, f_thread_condition_t, length)

  #define f_macro_thread_conditions_t_delete(status, conditions)  f_macro_memory_structure_t_delete(status, conditions, f_thread_condition_t)
  #define f_macro_thread_conditions_t_destroy(status, conditions) f_macro_memory_structure_t_destroy(status, conditions, f_thread_condition_t)

  #define f_macro_thread_conditions_t_delete_simple(conditions)  f_macro_memory_structure_t_delete_simple(conditions, f_thread_condition_t)
  #define f_macro_thread_conditions_t_destroy_simple(conditions) f_macro_memory_structure_t_destroy_simple(conditions, f_thread_condition_t)

  #define f_macro_thread_conditions_t_resize(status, conditions, new_length) f_macro_memory_structure_t_resize(status, conditions, f_thread_condition_t, new_length)
  #define f_macro_thread_conditions_t_adjust(status, conditions, new_length) f_macro_memory_structure_t_adjust(status, conditions, f_thread_condition_t, new_length)
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

  #define f_macro_thread_ids_t_clear(ids) f_macro_memory_structure_t_clear(ids)

  #define f_macro_thread_ids_t_new(status, ids, length) f_macro_memory_structure_t_new(status, ids, f_thread_ids_t, length)

  #define f_macro_thread_ids_t_delete(status, ids)  f_macro_memory_structure_t_delete(status, ids, f_thread_ids_t)
  #define f_macro_thread_ids_t_destroy(status, ids) f_macro_memory_structure_t_destroy(status, ids, f_thread_ids_t)

  #define f_macro_thread_ids_t_delete_simple(ids)  f_macro_memory_structure_t_delete_simple(ids, f_thread_ids_t)
  #define f_macro_thread_ids_t_destroy_simple(ids) f_macro_memory_structure_t_destroy_simple(ids, f_thread_ids_t)

  #define f_macro_thread_ids_t_resize(status, ids, new_length) f_macro_memory_structure_t_resize(status, ids, f_thread_ids_t, new_length)
  #define f_macro_thread_ids_t_adjust(status, ids, new_length) f_macro_memory_structure_t_adjust(status, ids, f_thread_ids_t, new_length)
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

  #define f_macro_thread_keys_t_clear(keys) f_macro_memory_structure_t_clear(keys)

  #define f_macro_thread_keys_t_new(status, keys, length) f_macro_memory_structure_t_new(status, keys, f_thread_key_t, length)

  #define f_macro_thread_keys_t_delete(status, keys)  f_macro_memory_structure_t_delete(status, keys, f_thread_key_t)
  #define f_macro_thread_keys_t_destroy(status, keys) f_macro_memory_structure_t_destroy(status, keys, f_thread_key_t)

  #define f_macro_thread_keys_t_delete_simple(keys)  f_macro_memory_structure_t_delete_simple(keys, f_thread_key_t)
  #define f_macro_thread_keys_t_destroy_simple(keys) f_macro_memory_structure_t_destroy_simple(keys, f_thread_key_t)

  #define f_macro_thread_keys_t_resize(status, keys, new_length) f_macro_memory_structure_t_resize(status, keys, f_thread_key_t, new_length)
  #define f_macro_thread_keys_t_adjust(status, keys, new_length) f_macro_memory_structure_t_adjust(status, keys, f_thread_key_t, new_length)
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

  #define f_macro_thread_locks_t_clear(locks) f_macro_memory_structure_t_clear(locks)

  #define f_macro_thread_locks_t_new(status, locks, length) f_macro_memory_structure_t_new(status, locks, f_thread_lock_t, length)

  #define f_macro_thread_locks_t_delete(status, locks)  f_macro_memory_structure_t_delete(status, locks, f_thread_lock_t)
  #define f_macro_thread_locks_t_destroy(status, locks) f_macro_memory_structure_t_destroy(status, locks, f_thread_lock_t)

  #define f_macro_thread_locks_t_delete_simple(locks)  f_macro_memory_structure_t_delete_simple(locks, f_thread_lock_t)
  #define f_macro_thread_locks_t_destroy_simple(locks) f_macro_memory_structure_t_destroy_simple(locks, f_thread_lock_t)

  #define f_macro_thread_locks_t_resize(status, locks, new_length) f_macro_memory_structure_t_resize(status, locks, f_thread_lock_t, new_length)
  #define f_macro_thread_locks_t_adjust(status, locks, new_length) f_macro_memory_structure_t_adjust(status, locks, f_thread_lock_t, new_length)
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

  #define f_macro_thread_mutexs_t_clear(mutexs) f_macro_memory_structure_t_clear(mutexs)

  #define f_macro_thread_mutexs_t_new(status, mutexs, length) f_macro_memory_structure_t_new(status, mutexs, f_thread_mutex_t, length)

  #define f_macro_thread_mutexs_t_delete(status, mutexs)  f_macro_memory_structure_t_delete(status, mutexs, f_thread_mutex_t)
  #define f_macro_thread_mutexs_t_destroy(status, mutexs) f_macro_memory_structure_t_destroy(status, mutexs, f_thread_mutex_t)

  #define f_macro_thread_mutexs_t_delete_simple(mutexs)  f_macro_memory_structure_t_delete_simple(mutexs, f_thread_mutex_t)
  #define f_macro_thread_mutexs_t_destroy_simple(mutexs) f_macro_memory_structure_t_destroy_simple(mutexs, f_thread_mutex_t)

  #define f_macro_thread_mutexs_t_resize(status, mutexs, new_length) f_macro_memory_structure_t_resize(status, mutexs, f_thread_mutex_t, new_length)
  #define f_macro_thread_mutexs_t_adjust(status, mutexs, new_length) f_macro_memory_structure_t_adjust(status, mutexs, f_thread_mutex_t, new_length)
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

  #define f_macro_thread_mutex_attributes_t_clear(mutex_attributes) f_macro_memory_structure_t_clear(mutex_attributes)

  #define f_macro_thread_mutex_attributes_t_new(status, mutex_attributes, length) f_macro_memory_structure_t_new(status, mutex_attributes, f_thread_mutex_attribute_t, length)

  #define f_macro_thread_mutex_attributes_t_delete(status, mutex_attributes)  f_macro_memory_structure_t_delete(status, mutex_attributes, f_thread_mutex_attribute_t)
  #define f_macro_thread_mutex_attributes_t_destroy(status, mutex_attributes) f_macro_memory_structure_t_destroy(status, mutex_attributes, f_thread_mutex_attribute_t)

  #define f_macro_thread_mutex_attributes_t_delete_simple(mutex_attributes)  f_macro_memory_structure_t_delete_simple(mutex_attributes, f_thread_mutex_attribute_t)
  #define f_macro_thread_mutex_attributes_t_destroy_simple(mutex_attributes) f_macro_memory_structure_t_destroy_simple(mutex_attributes, f_thread_mutex_attribute_t)

  #define f_macro_thread_mutex_attributes_t_resize(status, mutex_attributes, new_length) f_macro_memory_structure_t_resize(status, mutex_attributes, f_thread_mutex_attribute_t, new_length)
  #define f_macro_thread_mutex_attributes_t_adjust(status, mutex_attributes, new_length) f_macro_memory_structure_t_adjust(status, mutex_attributes, f_thread_mutex_attribute_t, new_length)
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

  #define f_macro_thread_onces_t_clear(onces) f_macro_memory_structure_t_clear(onces)

  #define f_macro_thread_onces_t_new(status, onces, length) f_macro_memory_structure_t_new(status, onces, f_thread_once_t, length)

  #define f_macro_thread_onces_t_delete(status, onces)  f_macro_memory_structure_t_delete(status, onces, f_thread_once_t)
  #define f_macro_thread_onces_t_destroy(status, onces) f_macro_memory_structure_t_destroy(status, onces, f_thread_once_t)

  #define f_macro_thread_onces_t_delete_simple(onces)  f_macro_memory_structure_t_delete_simple(onces, f_thread_once_t)
  #define f_macro_thread_onces_t_destroy_simple(onces) f_macro_memory_structure_t_destroy_simple(onces, f_thread_once_t)

  #define f_macro_thread_onces_t_resize(status, onces, new_length) f_macro_memory_structure_t_resize(status, onces, f_thread_once_t, new_length)
  #define f_macro_thread_onces_t_adjust(status, onces, new_length) f_macro_memory_structure_t_adjust(status, onces, f_thread_once_t, new_length)
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

  #define f_macro_thread_sets_t_clear(sets) f_macro_memory_structure_t_clear(sets)

  #define f_macro_thread_sets_t_new(status, sets, length) f_macro_memory_structure_t_new(status, sets, f_thread_set_t, length)

  #define f_macro_thread_sets_t_delete(status, sets)  f_macro_memory_structure_t_delete(status, sets, f_thread_set_t)
  #define f_macro_thread_sets_t_destroy(status, sets) f_macro_memory_structure_t_destroy(status, sets, f_thread_set_t)

  #define f_macro_thread_sets_t_delete_simple(sets)  f_macro_memory_structure_t_delete_simple(sets, f_thread_set_t)
  #define f_macro_thread_sets_t_destroy_simple(sets) f_macro_memory_structure_t_destroy_simple(sets, f_thread_set_t)

  #define f_macro_thread_sets_t_resize(status, sets, new_length) f_macro_memory_structure_t_resize(status, sets, f_thread_set_t, new_length)
  #define f_macro_thread_sets_t_adjust(status, sets, new_length) f_macro_memory_structure_t_adjust(status, sets, f_thread_set_t, new_length)
#endif // _di_f_thread_sets_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_common_h
