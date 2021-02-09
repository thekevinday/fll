/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_thread_h
#define _PRIVATE_F_thread_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_attr_destroy()
 *
 * @see f_thread_attributes_adjust()
 * @see f_thread_attributes_decimate_by()
 * @see f_thread_attributes_decrease()
 * @see f_thread_attributes_decrease_by()
 * @see f_thread_attributes_increase()
 * @see f_thread_attributes_increase_by()
 * @see f_thread_attributes_resize()
 * @see f_thread_sets_adjust()
 * @see f_thread_sets_decimate_by()
 * @see f_thread_sets_decrease()
 * @see f_thread_sets_decrease_by()
 * @see f_thread_sets_increase()
 * @see f_thread_sets_increase_by()
 * @see f_thread_sets_resize()
 */
#if !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_) || !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_) || !defined(_di_f_thread_attributes_resize_) || !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_) || !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_) || !defined(_di_f_thread_sets_resize_)
  extern f_status_t private_f_thread_attribute_delete(f_thread_attribute_t *attribute) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_) || !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_) || !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_) || !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_attributes_adjust()
 * @see f_thread_attributes_decimate_by()
 */
#if !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_)
  extern f_status_t private_f_thread_attributes_adjust(const f_array_length_t length, f_thread_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_attributes_adjust_) || !defined(_di_f_thread_attributes_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_attributes_decrease_by()
 * @see f_thread_attributes_increase()
 * @see f_thread_attributes_increase_by()
 */
#if !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)
  extern f_status_t private_f_thread_attributes_resize(const f_array_length_t length, f_thread_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param barriers
 *   The barriers to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_attr_destroy()
 *
 * @see f_thread_barriers_adjust()
 * @see f_thread_barriers_decimate_by()
 * @see f_thread_barriers_decrease()
 * @see f_thread_barriers_decrease_by()
 * @see f_thread_barriers_increase()
 * @see f_thread_barriers_increase_by()
 * @see f_thread_barriers_resize()
 */
#if !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_) || !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_) || !defined(_di_f_thread_barriers_resize_)
  extern f_status_t private_f_thread_barrier_delete(f_thread_barrier_t *barrier) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_) || !defined(_di_f_thread_barriers_decrease_) || !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_) || !defined(_di_f_thread_barriers_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param barriers
 *   The barriers to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_barriers_adjust()
 * @see f_thread_barriers_decimate_by()
 */
#if !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_)
  extern f_status_t private_f_thread_barriers_adjust(const f_array_length_t length, f_thread_barriers_t *barriers) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_barriers_adjust_) || !defined(_di_f_thread_barriers_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param barriers
 *   The barriers to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_barriers_decrease_by()
 * @see f_thread_barriers_increase()
 * @see f_thread_barriers_increase_by()
 */
#if !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_)
  extern f_status_t private_f_thread_barriers_resize(const f_array_length_t length, f_thread_barriers_t *barriers) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_barriers_decrease_by_) || !defined(_di_f_thread_barriers_increase_) || !defined(_di_f_thread_barriers_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_attr_destroy()
 *
 * @see f_thread_barrier_attributes_adjust()
 * @see f_thread_barrier_attributes_decimate_by()
 * @see f_thread_barrier_attributes_decrease()
 * @see f_thread_barrier_attributes_decrease_by()
 * @see f_thread_barrier_attributes_increase()
 * @see f_thread_barrier_attributes_increase_by()
 * @see f_thread_barrier_attributes_resize()
 */
#if !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_) || !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_) || !defined(_di_f_thread_barrier_attributes_resize_)
  extern f_status_t private_f_thread_barrier_attribute_delete(f_thread_barrier_attribute_t *attribute) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_) || !defined(_di_f_thread_barrier_attributes_decrease_) || !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_) || !defined(_di_f_thread_barrier_attributes_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_barrier_attributes_adjust()
 * @see f_thread_barrier_attributes_decimate_by()
 */
#if !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_)
  extern f_status_t private_f_thread_barrier_attributes_adjust(const f_array_length_t length, f_thread_barrier_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_barrier_attributes_adjust_) || !defined(_di_f_thread_barrier_attributes_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_barrier_attributes_decrease_by()
 * @see f_thread_barrier_attributes_increase()
 * @see f_thread_barrier_attributes_increase_by()
 */
#if !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_)
  extern f_status_t private_f_thread_barrier_attributes_resize(const f_array_length_t length, f_thread_barrier_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_barrier_attributes_decrease_by_) || !defined(_di_f_thread_barrier_attributes_increase_) || !defined(_di_f_thread_barrier_attributes_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attribute
 *   The attribute to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_condattr_destroy()
 *
 * @see f_thread_condition_attributes_adjust()
 * @see f_thread_condition_attributes_decimate_by()
 * @see f_thread_condition_attributes_decrease()
 * @see f_thread_condition_attributes_decrease_by()
 * @see f_thread_condition_attributes_increase()
 * @see f_thread_condition_attributes_increase_by()
 * @see f_thread_condition_attributes_resize()
 */
#if !defined(_di_f_thread_condition_attributes_adjust_) || !defined(_di_f_thread_condition_attributes_decimate_by_) || !defined(_di_f_thread_condition_attributes_decrease_) || !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_) || !defined(_di_f_thread_condition_attributes_resize_)
  extern f_status_t private_f_thread_condition_attribute_delete(f_thread_condition_attribute_t *attribute) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_condition_attributes_adjust_) || !defined(_di_f_thread_condition_attributes_decimate_by_) || !defined(_di_f_thread_condition_attributes_decrease_) || !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_) || !defined(_di_f_thread_condition_attributes_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_condition_attributes_adjust()
 * @see f_thread_condition_attributes_decimate_by()
 */
#if !defined(_di_f_thread_condition_attributes_adjust_) || !defined(_di_f_thread_condition_attributes_decimate_by_)
  extern f_status_t private_f_thread_condition_attributes_adjust(const f_array_length_t length, f_thread_condition_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_condition_attributes_adjust_) || !defined(_di_f_thread_condition_attributes_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_condition_attributes_decrease_by()
 * @see f_thread_condition_attributes_increase()
 * @see f_thread_condition_attributes_increase_by()
 */
#if !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_)
  extern f_status_t private_f_thread_condition_attributes_resize(const f_array_length_t length, f_thread_condition_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param conditions
 *   The conditions to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_cond_destroy()
 *
 * @see f_thread_conditions_adjust()
 * @see f_thread_conditions_decimate_by()
 * @see f_thread_conditions_decrease()
 * @see f_thread_conditions_decrease_by()
 * @see f_thread_conditions_increase()
 * @see f_thread_conditions_increase_by()
 * @see f_thread_conditions_resize()
 */
#if !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_) || !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_) || !defined(_di_f_thread_conditions_resize_)
  extern f_status_t private_f_thread_condition_delete(f_thread_condition_t *condition) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_) || !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_) || !defined(_di_f_thread_conditions_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param conditions
 *   The conditions to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_conditions_adjust()
 * @see f_thread_conditions_decimate_by()
 */
#if !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_)
  extern f_status_t private_f_thread_conditions_adjust(const f_array_length_t length, f_thread_conditions_t *conditions) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param conditions
 *   The conditions to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_conditions_decrease_by()
 * @see f_thread_conditions_increase()
 * @see f_thread_conditions_increase_by()
 */
#if !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)
  extern f_status_t private_f_thread_conditions_resize(const f_array_length_t length, f_thread_conditions_t *conditions) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param key
 *   The keys to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_key_destroy()
 *
 * @see f_thread_keys_adjust()
 * @see f_thread_keys_decimate_by()
 * @see f_thread_keys_decrease()
 * @see f_thread_keys_decrease_by()
 * @see f_thread_keys_increase()
 * @see f_thread_keys_increase_by()
 * @see f_thread_keys_resize()
 */
#if !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_) || !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_) || !defined(_di_f_thread_keys_resize_)
  extern f_status_t private_f_thread_key_delete(f_thread_key_t *key) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_) || !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_) || !defined(_di_f_thread_keys_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param keys
 *   The keys to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_keys_adjust()
 * @see f_thread_keys_decimate_by()
 */
#if !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_)
  extern f_status_t private_f_thread_keys_adjust(const f_array_length_t length, f_thread_keys_t *keys) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_keys_adjust_) || !defined(_di_f_thread_keys_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param keys
 *   The keys to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_keys_decrease_by()
 * @see f_thread_keys_increase()
 * @see f_thread_keys_increase_by()
 */
#if !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)
  extern f_status_t private_f_thread_keys_resize(const f_array_length_t length, f_thread_keys_t *keys) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param lock
 *   The locks to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_rwlock_destroy()
 *
 * @see f_thread_locks_adjust()
 * @see f_thread_locks_decimate_by()
 * @see f_thread_locks_decrease()
 * @see f_thread_locks_decrease_by()
 * @see f_thread_locks_increase()
 * @see f_thread_locks_increase_by()
 * @see f_thread_locks_resize()
 */
#if !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_) || !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_) || !defined(_di_f_thread_locks_resize_)
  extern f_status_t private_f_thread_lock_delete(f_thread_lock_t *lock) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_) || !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_) || !defined(_di_f_thread_locks_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param locks
 *   The locks to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_locks_adjust()
 * @see f_thread_locks_decimate_by()
 */
#if !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_)
  extern f_status_t private_f_thread_locks_adjust(const f_array_length_t length, f_thread_locks_t *locks) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param locks
 *   The locks to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_locks_decrease_by()
 * @see f_thread_locks_increase()
 * @see f_thread_locks_increase_by()
 */
#if !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)
  extern f_status_t private_f_thread_locks_resize(const f_array_length_t length, f_thread_locks_t *locks) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param attribute
 *   The attribute to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_rwlockattr_destroy()
 *
 * @see f_thread_lock_attributes_adjust()
 * @see f_thread_lock_attributes_decimate_by()
 * @see f_thread_lock_attributes_decrease()
 * @see f_thread_lock_attributes_decrease_by()
 * @see f_thread_lock_attributes_increase()
 * @see f_thread_lock_attributes_increase_by()
 * @see f_thread_lock_attributes_resize()
 */
#if !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_) || !defined(_di_f_thread_lock_attributes_decrease_) || !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_) || !defined(_di_f_thread_lock_attributes_resize_)
  extern f_status_t private_f_thread_lock_attribute_delete(f_thread_lock_attribute_t *attribute) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_) || !defined(_di_f_thread_lock_attributes_decrease_) || !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_) || !defined(_di_f_thread_lock_attributes_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_lock_attributes_adjust()
 * @see f_thread_lock_attributes_decimate_by()
 */
#if !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_)
  extern f_status_t private_f_thread_lock_attributes_adjust(const f_array_length_t length, f_thread_lock_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_lock_attributes_adjust_) || !defined(_di_f_thread_lock_attributes_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_lock_attributes_decrease_by()
 * @see f_thread_lock_attributes_increase()
 * @see f_thread_lock_attributes_increase_by()
 */
#if !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_)
  extern f_status_t private_f_thread_lock_attributes_resize(const f_array_length_t length, f_thread_lock_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param attribute
 *   The attribute to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_mutexattr_destroy()
 *
 * @see f_thread_mutex_attributes_adjust()
 * @see f_thread_mutex_attributes_decimate_by()
 * @see f_thread_mutex_attributes_decrease()
 * @see f_thread_mutex_attributes_decrease_by()
 * @see f_thread_mutex_attributes_increase()
 * @see f_thread_mutex_attributes_increase_by()
 * @see f_thread_mutex_attributes_resize()
 */
#if !defined(_di_f_thread_mutex_attributes_adjust_) || !defined(_di_f_thread_mutex_attributes_decimate_by_) || !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_) || !defined(_di_f_thread_mutex_attributes_resize_)
  extern f_status_t private_f_thread_mutex_attribute_delete(f_thread_mutex_attribute_t *attribute) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutex_attributes_adjust_) || !defined(_di_f_thread_mutex_attributes_decimate_by_) || !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_) || !defined(_di_f_thread_mutex_attributes_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_mutex_attributes_adjust()
 * @see f_thread_mutex_attributes_decimate_by()
 */
#if !defined(_di_f_thread_mutex_attributes_adjust_) || !defined(_di_f_thread_mutex_attributes_decimate_by_)
  extern f_status_t private_f_thread_mutex_attributes_adjust(const f_array_length_t length, f_thread_mutex_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutex_attributes_adjust_) || !defined(_di_f_thread_mutex_attributes_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param attributes
 *   The attributes to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_mutex_attributes_decrease_by()
 * @see f_thread_mutex_attributes_increase()
 * @see f_thread_mutex_attributes_increase_by()
 */
#if !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_)
  extern f_status_t private_f_thread_mutex_attributes_resize(const f_array_length_t length, f_thread_mutex_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param mutex
 *   The mutexs to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_mutex_destroy()
 *
 * @see f_thread_mutexs_adjust()
 * @see f_thread_mutexs_decimate_by()
 * @see f_thread_mutexs_decrease()
 * @see f_thread_mutexs_decrease_by()
 * @see f_thread_mutexs_increase()
 * @see f_thread_mutexs_increase_by()
 * @see f_thread_mutexs_resize()
 */
#if !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_) || !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_) || !defined(_di_f_thread_mutexs_resize_)
  extern f_status_t private_f_thread_mutex_delete(f_thread_mutex_t *mutex) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_) || !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_) || !defined(_di_f_thread_mutexs_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param mutexs
 *   The mutexs to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_mutexs_adjust()
 * @see f_thread_mutexs_decimate_by()
 */
#if !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_)
  extern f_status_t private_f_thread_mutexs_adjust(const f_array_length_t length, f_thread_mutexs_t *mutexs) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param mutexs
 *   The mutexs to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_mutexs_decrease_by()
 * @see f_thread_mutexs_increase()
 * @see f_thread_mutexs_increase_by()
 */
#if !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)
  extern f_status_t private_f_thread_mutexs_resize(const f_array_length_t length, f_thread_mutexs_t *mutexs) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_sets_adjust()
 * @see f_thread_sets_decimate_by()
 */
#if !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_)
  extern f_status_t private_f_thread_sets_adjust(const f_array_length_t length, f_thread_sets_t *sets) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_sets_adjust_) || !defined(_di_f_thread_sets_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_sets_decrease_by()
 * @see f_thread_sets_increase()
 * @see f_thread_sets_increase_by()
 */
#if !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)
  extern f_status_t private_f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t *sets) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param spin
 *   The spins to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
 *
 * @see pthread_spin_destroy()
 *
 * @see f_thread_spins_adjust()
 * @see f_thread_spins_decimate_by()
 * @see f_thread_spins_decrease()
 * @see f_thread_spins_decrease_by()
 * @see f_thread_spins_increase()
 * @see f_thread_spins_increase_by()
 * @see f_thread_spins_resize()
 */
#if !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_) || !defined(_di_f_thread_spins_decrease_) || !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_) || !defined(_di_f_thread_spins_resize_)
  extern f_status_t private_f_thread_spin_delete(f_thread_spin_t *spin) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_) || !defined(_di_f_thread_spins_decrease_) || !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_) || !defined(_di_f_thread_spins_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param spins
 *   The spins to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_spins_adjust()
 * @see f_thread_spins_decimate_by()
 */
#if !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_)
  extern f_status_t private_f_thread_spins_adjust(const f_array_length_t length, f_thread_spins_t *spins) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param spins
 *   The spins to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_spins_decrease_by()
 * @see f_thread_spins_increase()
 * @see f_thread_spins_increase_by()
 */
#if !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_)
  extern f_status_t private_f_thread_spins_resize(const f_array_length_t length, f_thread_spins_t *spins) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_thread_h
