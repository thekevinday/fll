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
  #define macro_f_thread_attribute_t_clear(attribute) attribute.__align = 0;

  #define macro_f_thread_attribute_t_delete_simple(attribute) f_thread_attribute_delete(&attribute);
#endif // _di_f_thread_attribute_t_

/**
 * An array of f_thread_attribute_t.
 *
 * array: The array of f_thread_attribute_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_attributes_t_
  typedef struct {
    f_thread_attribute_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_attributes_t;

  #define f_thread_attributes_t_initialize { 0, 0, 0 }

  #define macro_f_thread_attributes_t_clear(attributes) macro_f_memory_structure_clear(attributes)

  #define macro_f_thread_attributes_t_resize(status, attributes, length) status = f_thread_attributes_resize(length, &attributes);
  #define macro_f_thread_attributes_t_adjust(status, attributes, length) status = f_thread_attributes_adjust(length, &attributes);

  #define macro_f_thread_attributes_t_delete_simple(attributes)  f_thread_attributes_resize(0, &attributes);
  #define macro_f_thread_attributes_t_destroy_simple(attributes) f_thread_attributes_adjust(0, &attributes);

  #define macro_f_thread_attributes_t_increase(status, step, attributes)      status = f_thread_attributes_increase(step, attributes);
  #define macro_f_thread_attributes_t_increase_by(status, attributes, amount) status = f_thread_attributes_increase_by(amount, attributes);
  #define macro_f_thread_attributes_t_decrease_by(status, attributes, amount) status = f_thread_attributes_decrease_by(amount, attributes);
  #define macro_f_thread_attributes_t_decimate_by(status, attributes, amount) status = f_thread_attributes_decimate_by(amount, attributes);
#endif // _di_f_thread_attributes_t_

/**
 * A typedef representing pthread_barrier_t.
 */
#ifndef _di_f_thread_barrier_t_
  typedef pthread_barrier_t f_thread_barrier_t;

  #define f_thread_barrier_t_initialize { 0 }

  #define macro_f_thread_barrier_t_clear(barrier) barrier = 0;

  #define macro_f_thread_barrier_t_delete_simple(barrier) f_thread_barrier_delete(&barrier);
#endif // _di_f_thread_barrier_t_

/**
 * An array of f_thread_barrier_t.
 *
 * array: The array of f_thread_barrier_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_barriers_t_
  typedef struct {
    f_thread_barrier_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_barriers_t;

  #define f_thread_barriers_t_initialize { 0, 0, 0 }

  #define macro_f_thread_barriers_t_clear(barriers) macro_f_memory_structure_clear(barriers)

  #define macro_f_thread_barriers_t_resize(status, barriers, length) status = f_thread_barriers_resize(length, &barriers);
  #define macro_f_thread_barriers_t_adjust(status, barriers, length) status = f_thread_barriers_adjust(length, &barriers);

  #define macro_f_thread_barriers_t_delete_simple(barriers)  f_thread_barriers_resize(0, &barriers);
  #define macro_f_thread_barriers_t_destroy_simple(barriers) f_thread_barriers_adjust(0, &barriers);

  #define macro_f_thread_barriers_t_increase(status, step, barriers)      status = f_thread_barriers_increase(step, barriers);
  #define macro_f_thread_barriers_t_increase_by(status, barriers, amount) status = f_thread_barriers_increase_by(amount, barriers);
  #define macro_f_thread_barriers_t_decrease_by(status, barriers, amount) status = f_thread_barriers_decrease_by(amount, barriers);
  #define macro_f_thread_barriers_t_decimate_by(status, barriers, amount) status = f_thread_barriers_decimate_by(amount, barriers);
#endif // _di_f_thread_barriers_t_

/**
 * A typedef representing pthread_barrierattr_t.
 */
#ifndef _di_f_thread_barrier_attribute_t_
  typedef pthread_barrierattr_t f_thread_barrier_attribute_t;

  #define f_thread_barrier_attribute_t_initialize { 0 }

  // This does not clear the thread.attributes.__size array (may need to memset() against a sizeof(pthread_attr_t)).
  #define macro_f_thread_barrier_attribute_t_clear(attribute) attribute.__align = 0;

  #define macro_f_thread_barrier_attribute_t_delete_simple(attribute) f_thread_barrier_attribute_delete(&attribute);
#endif // _di_f_thread_barrier_attribute_t_

/**
 * An array of f_thread_barrier_attribute_t.
 *
 * array: The array of f_thread_barrier_attribute_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_barrier_attributes_t_
  typedef struct {
    f_thread_barrier_attribute_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_barrier_attributes_t;

  #define f_thread_barrier_attributes_t_initialize { 0, 0, 0 }

  #define macro_f_thread_barrier_attributes_t_clear(barrier_attributes) macro_f_memory_structure_clear(barrier_attributes)

  #define macro_f_thread_barrier_attributes_t_resize(status, barrier_attributes, length) status = f_thread_barrier_attributes_resize(length, &barrier_attributes);
  #define macro_f_thread_barrier_attributes_t_adjust(status, barrier_attributes, length) status = f_thread_barrier_attributes_adjust(length, &barrier_attributes);

  #define macro_f_thread_barrier_attributes_t_delete_simple(barrier_attributes)  f_thread_barrier_attributes_resize(0, &barrier_attributes);
  #define macro_f_thread_barrier_attributes_t_destroy_simple(barrier_attributes) f_thread_barrier_attributes_adjust(0, &barrier_attributes);

  #define macro_f_thread_barrier_attributes_t_increase(status, step, barrier_attributes)      status = f_thread_barrier_attributes_increase(step, barrier_attributes);
  #define macro_f_thread_barrier_attributes_t_increase_by(status, barrier_attributes, amount) status = f_thread_barrier_attributes_increase_by(amount, barrier_attributes);
  #define macro_f_thread_barrier_attributes_t_decrease_by(status, barrier_attributes, amount) status = f_thread_barrier_attributes_decrease_by(amount, barrier_attributes);
  #define macro_f_thread_barrier_attributes_t_decimate_by(status, barrier_attributes, amount) status = f_thread_barrier_attributes_decimate_by(amount, barrier_attributes);
#endif // _di_f_thread_barrier_attributes_t_

/**
 * A typedef representing pthread_cond_t.
 *
 * This must be dynamically initialized using f_thread_condition_create().
 * In some cases, they can be utilized statically, in which case only f_thread_condition_t_initialize is needed.
 */
#ifndef _di_f_thread_condition_t_
  typedef pthread_cond_t f_thread_condition_t;

  #define f_thread_condition_t_initialize PTHREAD_COND_INITIALIZER

  #define macro_f_thread_condition_t_delete_simple(condition) f_thread_condition_delete(&condition);
#endif // _di_f_thread_condition_t_

/**
 * An array of thread conditions.
 *
 * array: The array of f_thread_condition_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_conditions_t_
  typedef struct {
    f_thread_condition_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_conditions_t;

  #define f_thread_conditions_t_initialize { 0, 0, 0 }

  #define macro_f_thread_conditions_t_clear(conditions) macro_f_memory_structure_clear(conditions)

  #define macro_f_thread_conditions_t_resize(status, conditions, length) status = f_thread_conditions_resize(length, &conditions);
  #define macro_f_thread_conditions_t_adjust(status, conditions, length) status = f_thread_conditions_adjust(length, &conditions);

  #define macro_f_thread_conditions_t_delete_simple(conditions)  f_thread_conditions_resize(0, &conditions);
  #define macro_f_thread_conditions_t_destroy_simple(conditions) f_thread_conditions_adjust(0, &conditions);

  #define macro_f_thread_conditions_t_increase(status, step, conditions)      status = f_thread_conditions_increase(step, conditions);
  #define macro_f_thread_conditions_t_increase_by(status, conditions, amount) status = f_thread_conditions_increase_by(amount, conditions);
  #define macro_f_thread_conditions_t_decrease_by(status, conditions, amount) status = f_thread_conditions_decrease_by(amount, conditions);
  #define macro_f_thread_conditions_t_decimate_by(status, conditions, amount) status = f_thread_conditions_decimate_by(amount, conditions);
#endif // _di_f_thread_conditions_t_

/**
 * A typedef representing pthread_cond_t.
 */
#ifndef _di_f_thread_condition_attribute_t_
  typedef pthread_condattr_t f_thread_condition_attribute_t;

  #define f_thread_condition_attribute_t_initialize { 0 };

  // This does not clear the thread.attributes.__size array (may need to memset() against a sizeof(pthread_attr_t)).
  #define macro_f_thread_condition_attribute_t_clear(attribute) attribute.__align = 0;

  #define macro_f_thread_condition_attribute_t_delete_simple(attribute) f_thread_condition_attribute_delete(&attribute);
#endif // _di_f_thread_condition_attribute_t_

/**
 * An array of thread condition attributes.
 *
 * array: The array of f_thread_condition_attribute_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_condition_attributes_t_
  typedef struct {
    f_thread_condition_attribute_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_condition_attributes_t;

  #define f_thread_condition_attributes_t_initialize { 0, 0, 0 }

  #define macro_f_thread_condition_attributes_t_clear(attributes) macro_f_memory_structure_clear(attributes)

  #define macro_f_thread_condition_attributes_t_resize(status, attributes, length) status = f_thread_condition_attributes_resize(length, &attributes);
  #define macro_f_thread_condition_attributes_t_adjust(status, attributes, length) status = f_thread_condition_attributes_adjust(length, &attributes);

  #define macro_f_thread_condition_attributes_t_delete_simple(attributes)  f_thread_condition_attributes_resize(0, &condition_attributes);
  #define macro_f_thread_condition_attributes_t_destroy_simple(attributes) f_thread_condition_attributes_adjust(0, &condition_attributes);

  #define macro_f_thread_condition_attributes_t_increase(status, step, attributes)      status = f_thread_condition_attributes_increase(step, attributes);
  #define macro_f_thread_condition_attributes_t_increase_by(status, attributes, amount) status = f_thread_condition_attributes_increase_by(amount, attributes);
  #define macro_f_thread_condition_attributes_t_decrease_by(status, attributes, amount) status = f_thread_condition_attributes_decrease_by(amount, attributes);
  #define macro_f_thread_condition_attributes_t_decimate_by(status, attributes, amount) status = f_thread_condition_attributes_decimate_by(amount, attributes);
#endif // _di_f_thread_condition_attributes_t_

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
 * array: The array of f_thread_id_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_ids_t_
  typedef struct {
    f_thread_id_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_ids_t;

  #define f_thread_ids_t_initialize { 0, 0, 0 }

  #define macro_f_thread_ids_t_resize(status, ids, length) macro_f_memory_structure_resize(status, ids, f_thread_id_t, length)
  #define macro_f_thread_ids_t_adjust(status, ids, length) macro_f_memory_structure_adjust(status, ids, f_thread_id_t, length)

  #define macro_f_thread_ids_t_delete_simple(ids)  macro_f_memory_structure_delete_simple(ids, f_thread_id_t)
  #define macro_f_thread_ids_t_destroy_simple(ids) macro_f_memory_structure_destroy_simple(ids, f_thread_id_t)

  #define macro_f_thread_ids_t_increase(status, step, ids)      macro_f_memory_structure_increase(status, step, ids, f_thread_id_t)
  #define macro_f_thread_ids_t_increase_by(status, ids, amount) macro_f_memory_structure_increase_by(status, ids, f_thread_id_t, amount)
  #define macro_f_thread_ids_t_decrease_by(status, ids, amount) macro_f_memory_structure_decrease_by(status, ids, f_thread_id_t, amount)
  #define macro_f_thread_ids_t_decimate_by(status, ids, amount) macro_f_memory_structure_decimate_by(status, ids, f_thread_id_t, amount)
#endif // _di_f_thread_ids_t_

/**
 * A typedef representing pthread_key_t.
 */
#ifndef _di_f_thread_key_t_
  typedef pthread_key_t f_thread_key_t;

  #define f_thread_key_t_initialize 0

  #define macro_f_thread_key_t_clear(key) key = 0;

  #define macro_f_thread_key_t_delete_simple(key) f_thread_key_delete(&key);
#endif // _di_f_thread_key_t_

/**
 * An array of thread keys.
 *
 * array: The array of f_thread_key_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_keys_t_
  typedef struct {
    f_thread_key_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_keys_t;

  #define f_thread_keys_t_initialize { 0, 0, 0 }

  #define macro_f_thread_keys_t_clear(keys) macro_f_memory_structure_clear(keys)

  #define macro_f_thread_keys_t_resize(status, keys, length) status = f_thread_keys_resize(length, &keys);
  #define macro_f_thread_keys_t_adjust(status, keys, length) status = f_thread_keys_adjust(length, &keys);

  #define macro_f_thread_keys_t_delete_simple(keys)  f_thread_keys_resize(0, &keys);
  #define macro_f_thread_keys_t_destroy_simple(keys) f_thread_keys_adjust(0, &keys);

  #define macro_f_thread_keys_t_increase(status, step, keys)      status = f_thread_keys_increase(step, keys);
  #define macro_f_thread_keys_t_increase_by(status, keys, amount) status = f_thread_keys_increase_by(amount, keys);
  #define macro_f_thread_keys_t_decrease_by(status, keys, amount) status = f_thread_keys_decrease_by(amount, keys);
  #define macro_f_thread_keys_t_decimate_by(status, keys, amount) status = f_thread_keys_decimate_by(amount, keys);
#endif // _di_f_thread_keys_t_

/**
 * A typedef representing pthread_rwlock_t (read/write lock).
 *
 * This must be dynamically initialized using f_thread_lock_create().
 * In some cases, they can be utilized statically, in which case only f_thread_lock_t_initialize is needed.
 */
#ifndef _di_f_thread_lock_t_
  typedef pthread_rwlock_t f_thread_lock_t;

  #define f_thread_lock_t_initialize PTHREAD_RWLOCK_INITIALIZER

  #define macro_f_thread_lock_t_delete_simple(lock) f_thread_lock_delete(&lock);
#endif // _di_f_thread_lock_t_

/**
 * An array of thread locks.
 *
 * array: The array of f_thread_lock_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_locks_t_
  typedef struct {
    f_thread_lock_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_locks_t;

  #define f_thread_locks_t_initialize { 0, 0, 0 }

  #define macro_f_thread_locks_t_resize(status, locks, length) macro_f_memory_structure_resize(status, locks, f_thread_lock_t, length)
  #define macro_f_thread_locks_t_adjust(status, locks, length) macro_f_memory_structure_adjust(status, locks, f_thread_lock_t, length)

  #define macro_f_thread_locks_t_delete_simple(locks)  macro_f_memory_structure_delete_simple(locks, f_thread_lock_t)
  #define macro_f_thread_locks_t_destroy_simple(locks) macro_f_memory_structure_destroy_simple(locks, f_thread_lock_t)

  #define macro_f_thread_locks_t_increase(status, step, locks)      macro_f_memory_structure_increase(status, step, locks, f_thread_lock_t)
  #define macro_f_thread_locks_t_increase_by(status, locks, amount) macro_f_memory_structure_increase_by(status, locks, f_thread_lock_t, amount)
  #define macro_f_thread_locks_t_decrease_by(status, locks, amount) macro_f_memory_structure_decrease_by(status, locks, f_thread_lock_t, amount)
  #define macro_f_thread_locks_t_decimate_by(status, locks, amount) macro_f_memory_structure_decimate_by(status, locks, f_thread_lock_t, amount)
#endif // _di_f_thread_locks_t_

/**
 * A typedef representing pthread_rwlockattr_t.
 */
#ifndef _di_f_thread_lock_attribute_t_
  typedef pthread_rwlockattr_t f_thread_lock_attribute_t;

  #define f_thread_lock_attribute_t_initialize { 0 }

  // This does not clear the thread.attributes.__size array (may need to memset() against a sizeof(pthread_attr_t)).
  #define macro_f_thread_lock_attribute_t_clear(attribute) attribute.__align = 0;

  #define macro_f_thread_lock_attribute_t_delete_simple(attribute) f_thread_lock_attribute_delete(&attribute);
#endif // _di_f_thread_lock_attribute_t_

/**
 * An array of read/write lock attributees.
 *
 * array: The array of f_thread_lock_attribute_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_lock_attributes_t_
  typedef struct {
    f_thread_lock_attribute_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_lock_attributes_t;

  #define f_thread_lock_attributes_t_initialize { 0, 0, 0 }

  #define macro_f_thread_lock_attributes_t_clear(attributes) macro_f_memory_structure_clear(attributes)

  #define macro_f_thread_lock_attributes_t_resize(status, attributes, length) status = f_thread_lock_attributes_resize(length, &attributes);
  #define macro_f_thread_lock_attributes_t_adjust(status, attributes, length) status = f_thread_lock_attributes_adjust(length, &attributes);

  #define macro_f_thread_lock_attributes_t_delete_simple(attributes)  f_thread_lock_attributes_resize(0, &attributes);
  #define macro_f_thread_lock_attributes_t_destroy_simple(attributes) f_thread_lock_attributes_adjust(0, &attributes);

  #define macro_f_thread_lock_attributes_t_increase(status, step, attributes)      status = f_thread_lock_attributes_increase(step, attributes);
  #define macro_f_thread_lock_attributes_t_increase_by(status, attributes, amount) status = f_thread_lock_attributes_increase_by(amount, attributes);
  #define macro_f_thread_lock_attributes_t_decrease_by(status, attributes, amount) status = f_thread_lock_attributes_decrease_by(amount, attributes);
  #define macro_f_thread_lock_attributes_t_decimate_by(status, attributes, amount) status = f_thread_lock_attributes_decimate_by(amount, attributes);
#endif // _di_f_thread_lock_attributes_t_

/**
 * A typedef representing pthread_mutex_t.
 *
 * This variable cannot be cleared by setting value to 0, so there is no clear macro provided.
 *
 * This must be dynamically initialized using f_thread_mutex_create().
 * In some cases, they can be utilized statically, in which case only f_thread_mutex_t_initialize is needed.
 */
#ifndef _di_f_thread_mutex_t_
  typedef pthread_mutex_t f_thread_mutex_t;

  #define f_thread_mutex_t_initialize PTHREAD_MUTEX_INITIALIZER

  #define macro_f_thread_mutex_t_delete_simple(mutex) f_thread_mutex_delete(&mutex);
#endif // _di_f_thread_mutex_t_

/**
 * An array of thread mutexes.
 *
 * array: The array of f_thread_mutex_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_mutexs_t_
  typedef struct {
    f_thread_mutex_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_mutexs_t;

  #define f_thread_mutexs_t_initialize { 0, 0, 0 }

  #define macro_f_thread_mutexs_t_clear(mutexs) macro_f_memory_structure_clear(mutexs)

  #define macro_f_thread_mutexs_t_resize(status, mutexs, length) status = f_thread_mutexs_resize(length, &mutexs);
  #define macro_f_thread_mutexs_t_adjust(status, mutexs, length) status = f_thread_mutexs_adjust(length, &mutexs);

  #define macro_f_thread_mutexs_t_delete_simple(mutexs)  f_thread_mutexs_resize(0, &mutexs);
  #define macro_f_thread_mutexs_t_destroy_simple(mutexs) f_thread_mutexs_adjust(0, &mutexs);

  #define macro_f_thread_mutexs_t_increase(status, step, mutexs)      status = f_thread_mutexs_increase(step, mutexs);
  #define macro_f_thread_mutexs_t_increase_by(status, mutexs, amount) status = f_thread_mutexs_increase_by(amount, mutexs);
  #define macro_f_thread_mutexs_t_decrease_by(status, mutexs, amount) status = f_thread_mutexs_decrease_by(amount, mutexs);
  #define macro_f_thread_mutexs_t_decimate_by(status, mutexs, amount) status = f_thread_mutexs_decimate_by(amount, mutexs);
#endif // _di_f_thread_mutexs_t_

/**
 * A typedef representing pthread_mutex_attribute_t.
 */
#ifndef _di_f_thread_mutex_attribute_t_
  typedef pthread_mutexattr_t f_thread_mutex_attribute_t;

  #define f_thread_mutex_attribute_t_initialize { 0 }

  // This does not clear the thread.attributes.__size array (may need to memset() against a sizeof(pthread_attr_t)).
  #define macro_f_thread_mutex_attribute_t_clear(attribute) attribute.__align = 0;

  #define macro_f_thread_mutex_attribute_t_delete_simple(attribute) f_thread_mutex_attribute_delete(&attribute);
#endif // _di_f_thread_mutex_attribute_t_

/**
 * An array of thread mutex_attributees.
 *
 * array: The array of f_thread_mutex_attribute_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_mutex_attributes_t_
  typedef struct {
    f_thread_mutex_attribute_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_mutex_attributes_t;

  #define f_thread_mutex_attributes_t_initialize { 0, 0, 0 }

  #define macro_f_thread_mutex_attributes_t_clear(attributes) macro_f_memory_structure_clear(attributes)

  #define macro_f_thread_mutex_attributes_t_resize(status, attributes, length) status = f_thread_mutex_attributes_resize(length, &attributes);
  #define macro_f_thread_mutex_attributes_t_adjust(status, attributes, length) status = f_thread_mutex_attributes_adjust(length, &attributes);

  #define macro_f_thread_mutex_attributes_t_delete_simple(attributes)  f_thread_mutex_attributes_resize(0, &attributes);
  #define macro_f_thread_mutex_attributes_t_destroy_simple(attributes) f_thread_mutex_attributes_adjust(0, &attributes);

  #define macro_f_thread_mutex_attributes_t_increase(status, step, attributes)      status = f_thread_mutex_attributes_increase(step, attributes);
  #define macro_f_thread_mutex_attributes_t_increase_by(status, attributes, amount) status = f_thread_mutex_attributes_increase_by(amount, attributes);
  #define macro_f_thread_mutex_attributes_t_decrease_by(status, attributes, amount) status = f_thread_mutex_attributes_decrease_by(amount, attributes);
  #define macro_f_thread_mutex_attributes_t_decimate_by(status, attributes, amount) status = f_thread_mutex_attributes_decimate_by(amount, attributes);
#endif // _di_f_thread_mutex_attributes_t_

/**
 * A typedef representing pthread_once_t.
 *
 * There are no delete functions and therefore no delete macros.
 */
#ifndef _di_f_thread_once_t_
  typedef pthread_once_t f_thread_once_t;

  #define f_thread_once_t_initialize PTHREAD_ONCE_INIT
#endif // _di_f_thread_once_t_

/**
 * An array of thread onces.
 *
 * array: The array of f_thread_once_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_onces_t_
  typedef struct {
    f_thread_once_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_onces_t;

  #define f_thread_onces_t_initialize { 0, 0, 0 }

  #define macro_f_thread_onces_t_resize(status, onces, length) macro_f_memory_structure_resize(status, onces, f_thread_once_t, length)
  #define macro_f_thread_onces_t_adjust(status, onces, length) macro_f_memory_structure_adjust(status, onces, f_thread_once_t, length)

  #define macro_f_thread_onces_t_delete_simple(onces)  macro_f_memory_structure_delete_simple(onces, f_thread_once_t)
  #define macro_f_thread_onces_t_destroy_simple(onces) macro_f_memory_structure_destroy_simple(onces, f_thread_once_t)

  #define macro_f_thread_onces_t_increase(status, step, onces)      macro_f_memory_structure_increase(status, step, onces, f_thread_once_t)
  #define macro_f_thread_onces_t_increase_by(status, onces, amount) macro_f_memory_structure_increase_by(status, onces, f_thread_once_t, amount)
  #define macro_f_thread_onces_t_decrease_by(status, onces, amount) macro_f_memory_structure_decrease_by(status, onces, f_thread_once_t, amount)
  #define macro_f_thread_onces_t_decimate_by(status, onces, amount) macro_f_memory_structure_decimate_by(status, onces, f_thread_once_t, amount)
#endif // _di_f_thread_onces_t_

/**
 * A typedef representing sem_t.
 *
 * This variable cannot be cleared by setting value to 0, so there is no clear macro provided.
 *
 * This must be dynamically initialized using f_thread_semaphore_create().
 */
#ifndef _di_f_thread_semaphore_t_
  typedef sem_t f_thread_semaphore_t;

  #define f_thread_semaphore_t_initialize 0

  #define macro_f_thread_semaphore_t_delete_simple(semaphore) f_thread_semaphore_delete(&semaphore);
#endif // _di_f_thread_semaphore_t_

/**
 * An array of thread semaphorees.
 *
 * array: The array of f_thread_semaphore_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_semaphores_t_
  typedef struct {
    f_thread_semaphore_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_semaphores_t;

  #define f_thread_semaphores_t_initialize { 0, 0, 0 }

  #define macro_f_thread_semaphores_t_clear(semaphores) macro_f_memory_structure_clear(semaphores)

  #define macro_f_thread_semaphores_t_resize(status, semaphores, length) status = f_thread_semaphores_resize(length, &semaphores);
  #define macro_f_thread_semaphores_t_adjust(status, semaphores, length) status = f_thread_semaphores_adjust(length, &semaphores);

  #define macro_f_thread_semaphores_t_delete_simple(semaphores)  f_thread_semaphores_resize(0, &semaphores);
  #define macro_f_thread_semaphores_t_destroy_simple(semaphores) f_thread_semaphores_adjust(0, &semaphores);

  #define macro_f_thread_semaphores_t_increase(status, step, semaphores)      status = f_thread_semaphores_increase(step, semaphores);
  #define macro_f_thread_semaphores_t_increase_by(status, semaphores, amount) status = f_thread_semaphores_increase_by(amount, semaphores);
  #define macro_f_thread_semaphores_t_decrease_by(status, semaphores, amount) status = f_thread_semaphores_decrease_by(amount, semaphores);
  #define macro_f_thread_semaphores_t_decimate_by(status, semaphores, amount) status = f_thread_semaphores_decimate_by(amount, semaphores);
#endif // _di_f_thread_semaphores_t_

/**
 * A structure containing basic thread information.
 *
 * attribute: The thread attributes (which is a union).
 * id:        The thread identifier.
 * result:    The result of the thread on exit.
 */
#ifndef _di_f_thread_set_t_
  typedef struct {
    f_thread_attribute_t attribute;
    f_thread_id_t id;
    int result;
  } f_thread_set_t;

  #define f_thread_set_t_initialize { f_thread_attribute_t_initialize, f_thread_id_t_initialize, 0 }

  #define macro_f_thread_set_t_clear(thread) \
    macro_f_thread_attribute_t_clear(thread.attribute) \
    macro_f_thread_id_t_clear(thread.id)

  #define macro_f_thread_set_t_delete_simple(set) macro_f_thread_attribute_t_delete_simple(set.attribute)
#endif // _di_f_thread_set_t_

/**
 * An array of f_thread_set_t.
 *
 * array: The array of f_thread_set_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_sets_t_
  typedef struct {
    f_thread_set_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_sets_t;

  #define f_thread_sets_t_initialize { 0, 0, 0 }

  #define macro_f_thread_sets_t_clear(sets) macro_f_memory_structure_clear(sets)

  #define macro_f_thread_sets_t_resize(status, sets, length) status = f_thread_sets_resize(length, &sets);
  #define macro_f_thread_sets_t_adjust(status, sets, length) status = f_thread_sets_adjust(length, &sets);

  #define macro_f_thread_sets_t_delete_simple(sets)  f_thread_sets_resize(0, &sets);
  #define macro_f_thread_sets_t_destroy_simple(sets) f_thread_sets_adjust(0, &sets);

  #define macro_f_thread_sets_t_increase(status, step, sets)      status = f_thread_sets_increase(step, sets);
  #define macro_f_thread_sets_t_increase_by(status, sets, amount) status = f_thread_sets_increase_by(amount, sets);
  #define macro_f_thread_sets_t_decrease_by(status, sets, amount) status = f_thread_sets_decrease_by(amount, sets);
  #define macro_f_thread_sets_t_decimate_by(status, sets, amount) status = f_thread_sets_decimate_by(amount, sets);
#endif // _di_f_thread_sets_t_

/**
 * A typedef representing pthread_spinlock_t.
 *
 * Note: There appears to be no pthread init macro for spinlock, so initialize manually similarly to how the other inits work.
 */
#ifndef _di_f_thread_spin_t_
  typedef pthread_spinlock_t f_thread_spin_t;

  #define f_thread_spin_t_initialize ((pthread_spinlock_t) 0xFFFFFFFF)

  #define macro_f_thread_spin_t_delete_simple(spin) f_thread_spin_delete(&spin);
#endif // _di_f_thread_spin_t_

/**
 * An array of thread spins.
 *
 * array: The array of f_thread_spin_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_thread_spins_t_
  typedef struct {
    f_thread_spin_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_thread_spins_t;

  #define f_thread_spins_t_initialize { 0, 0, 0 }

  #define macro_f_thread_spins_t_clear(spins) macro_f_memory_structure_clear(spins)

  #define macro_f_thread_spins_t_resize(status, spins, length) status = f_thread_spins_resize(length, &spins);
  #define macro_f_thread_spins_t_adjust(status, spins, length) status = f_thread_spins_adjust(length, &spins);

  #define macro_f_thread_spins_t_delete_simple(spins)  f_thread_spins_resize(0, &spins);
  #define macro_f_thread_spins_t_destroy_simple(spins) f_thread_spins_adjust(0, &spins);

  #define macro_f_thread_spins_t_increase(status, step, spins)      status = f_thread_spins_increase(step, spins);
  #define macro_f_thread_spins_t_increase_by(status, spins, amount) status = f_thread_spins_increase_by(amount, spins);
  #define macro_f_thread_spins_t_decrease_by(status, spins, amount) status = f_thread_spins_decrease_by(amount, spins);
  #define macro_f_thread_spins_t_decimate_by(status, spins, amount) status = f_thread_spins_decimate_by(amount, spins);
#endif // _di_f_thread_spins_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_thread_common_h
