/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
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
  extern f_status_t private_f_thread_attribute_delete(f_thread_attribute_t *attribute) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_attributes_adjust(const f_array_length_t length, f_thread_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_attributes_resize(const f_array_length_t length, f_thread_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
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
  extern f_status_t private_f_thread_barrier_delete(f_thread_barrier_t *barrier) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_barriers_adjust(const f_array_length_t length, f_thread_barriers_t * const barriers) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_barriers_resize(const f_array_length_t length, f_thread_barriers_t * const barriers) F_attribute_visibility_internal_d;
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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
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
  extern f_status_t private_f_thread_barrier_attribute_delete(f_thread_barrier_attribute_t *attribute) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_barrier_attributes_adjust(const f_array_length_t length, f_thread_barrier_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_barrier_attributes_resize(const f_array_length_t length, f_thread_barrier_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
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
  extern f_status_t private_f_thread_condition_attribute_delete(f_thread_condition_attribute_t *attribute) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_condition_attributes_adjust(const f_array_length_t length, f_thread_condition_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_condition_attributes_resize(const f_array_length_t length, f_thread_condition_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_cond_destroy()
 *
 * @see f_thread_condition_delete()
 * @see f_thread_conditions_adjust()
 * @see f_thread_conditions_decimate_by()
 * @see f_thread_conditions_decrease()
 * @see f_thread_conditions_decrease_by()
 * @see f_thread_conditions_increase()
 * @see f_thread_conditions_increase_by()
 * @see f_thread_conditions_resize()
 */
#if !defined(_di_f_thread_condition_delete_) || !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_) || !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_) || !defined(_di_f_thread_conditions_resize_)
  extern f_status_t private_f_thread_condition_delete(f_thread_condition_t *condition) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_condition_delete_) || !defined(_di_f_thread_conditions_adjust_) || !defined(_di_f_thread_conditions_decimate_by_) || !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_) || !defined(_di_f_thread_conditions_resize_)

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
  extern f_status_t private_f_thread_conditions_adjust(const f_array_length_t length, f_thread_conditions_t * const conditions) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_conditions_resize(const f_array_length_t length, f_thread_conditions_t * const conditions) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param ids
 *   The ids to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_ids_adjust()
 * @see f_thread_ids_decimate_by()
 */
#if !defined(_di_f_thread_ids_adjust_) || !defined(_di_f_thread_ids_decimate_by_)
  extern f_status_t private_f_thread_ids_adjust(const f_array_length_t length, f_thread_ids_t * const ids) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_ids_adjust_) || !defined(_di_f_thread_ids_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param ids
 *   The ids to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_ids_decrease_by()
 * @see f_thread_ids_increase()
 * @see f_thread_ids_increase_by()
 */
#if !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_increase_) || !defined(_di_f_thread_ids_increase_by_)
  extern f_status_t private_f_thread_ids_resize(const f_array_length_t length, f_thread_ids_t * const ids) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_increase_) || !defined(_di_f_thread_ids_increase_by_)

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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
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
  extern f_status_t private_f_thread_key_delete(f_thread_key_t *key) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_keys_adjust(const f_array_length_t length, f_thread_keys_t * const keys) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_keys_resize(const f_array_length_t length, f_thread_keys_t * const keys) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)

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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
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
  extern f_status_t private_f_thread_lock_attribute_delete(f_thread_lock_attribute_t *attribute) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_lock_attributes_adjust(const f_array_length_t length, f_thread_lock_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_lock_attributes_resize(const f_array_length_t length, f_thread_lock_attributes_t * const attributes) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_lock_attributes_decrease_by_) || !defined(_di_f_thread_lock_attributes_increase_) || !defined(_di_f_thread_lock_attributes_increase_by_)

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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_rwlock_destroy()
 *
 * @see f_thread_lock_delete()
 * @see f_thread_locks_adjust()
 * @see f_thread_locks_decimate_by()
 * @see f_thread_locks_decrease()
 * @see f_thread_locks_decrease_by()
 * @see f_thread_locks_increase()
 * @see f_thread_locks_increase_by()
 * @see f_thread_locks_resize()
 */
#if !defined(_di_f_thread_lock_delete_) || !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_) || !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_) || !defined(_di_f_thread_locks_resize_)
  extern f_status_t private_f_thread_lock_delete(f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_lock_delete_) || !defined(_di_f_thread_locks_adjust_) || !defined(_di_f_thread_locks_decimate_by_) || !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_) || !defined(_di_f_thread_locks_resize_)

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
  extern f_status_t private_f_thread_locks_adjust(const f_array_length_t length, f_thread_locks_t * const locks) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_locks_resize(const f_array_length_t length, f_thread_locks_t * const locks) F_attribute_visibility_internal_d;
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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
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
  extern f_status_t private_f_thread_mutex_attribute_delete(f_thread_mutex_attribute_t *attribute) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_mutex_attributes_adjust(const f_array_length_t length, f_thread_mutex_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_mutex_attributes_resize(const f_array_length_t length, f_thread_mutex_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see pthread_mutex_destroy()
 *
 * @see f_thread_mutex_delete()
 * @see f_thread_mutexs_adjust()
 * @see f_thread_mutexs_decimate_by()
 * @see f_thread_mutexs_decrease()
 * @see f_thread_mutexs_decrease_by()
 * @see f_thread_mutexs_increase()
 * @see f_thread_mutexs_increase_by()
 * @see f_thread_mutexs_resize()
 */
#if !defined(_di_f_thread_mutex_delete_) || !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_) || !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_) || !defined(_di_f_thread_mutexs_resize_)
  extern f_status_t private_f_thread_mutex_delete(f_thread_mutex_t *mutex) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_mutex_delete_) || !defined(_di_f_thread_mutexs_adjust_) || !defined(_di_f_thread_mutexs_decimate_by_) || !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_) || !defined(_di_f_thread_mutexs_resize_)

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
  extern f_status_t private_f_thread_mutexs_adjust(const f_array_length_t length, f_thread_mutexs_t * const mutexs) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_mutexs_resize(const f_array_length_t length, f_thread_mutexs_t * const mutexs) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param onces
 *   The onces to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_onces_adjust()
 * @see f_thread_onces_decimate_by()
 */
#if !defined(_di_f_thread_onces_adjust_) || !defined(_di_f_thread_onces_decimate_by_)
  extern f_status_t private_f_thread_onces_adjust(const f_array_length_t length, f_thread_onces_t * const onces) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_onces_adjust_) || !defined(_di_f_thread_onces_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param onces
 *   The onces to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_onces_decrease_by()
 * @see f_thread_onces_increase()
 * @see f_thread_onces_increase_by()
 */
#if !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_increase_) || !defined(_di_f_thread_onces_increase_by_)
  extern f_status_t private_f_thread_onces_resize(const f_array_length_t length, f_thread_onces_t * const onces) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_increase_) || !defined(_di_f_thread_onces_increase_by_)

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param semaphore
 *   The semaphores to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see sem_destroy()
 *
 * @see f_thread_semaphores_adjust()
 * @see f_thread_semaphores_decimate_by()
 * @see f_thread_semaphores_decrease()
 * @see f_thread_semaphores_decrease_by()
 * @see f_thread_semaphores_increase()
 * @see f_thread_semaphores_increase_by()
 * @see f_thread_semaphores_resize()
 */
#if !defined(_di_f_thread_semaphores_adjust_) || !defined(_di_f_thread_semaphores_decimate_by_) || !defined(_di_f_thread_semaphores_decrease_) || !defined(_di_f_thread_semaphores_decrease_by_) || !defined(_di_f_thread_semaphores_increase_) || !defined(_di_f_thread_semaphores_increase_by_) || !defined(_di_f_thread_semaphores_resize_)
  extern f_status_t private_f_thread_semaphore_delete(f_thread_semaphore_t *semaphore) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_semaphores_adjust_) || !defined(_di_f_thread_semaphores_decimate_by_) || !defined(_di_f_thread_semaphores_decrease_) || !defined(_di_f_thread_semaphores_decrease_by_) || !defined(_di_f_thread_semaphores_increase_) || !defined(_di_f_thread_semaphores_increase_by_) || !defined(_di_f_thread_semaphores_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param semaphores
 *   The semaphores to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_memory_adjust()
 * @see f_thread_semaphores_adjust()
 * @see f_thread_semaphores_decimate_by()
 */
#if !defined(_di_f_thread_semaphores_adjust_) || !defined(_di_f_thread_semaphores_decimate_by_)
  extern f_status_t private_f_thread_semaphores_adjust(const f_array_length_t length, f_thread_semaphores_t * const semaphores) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_semaphores_adjust_) || !defined(_di_f_thread_semaphores_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param semaphores
 *   The semaphores to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_thread_semaphores_decrease_by()
 * @see f_thread_semaphores_increase()
 * @see f_thread_semaphores_increase_by()
 */
#if !defined(_di_f_thread_semaphores_decrease_by_) || !defined(_di_f_thread_semaphores_increase_) || !defined(_di_f_thread_semaphores_increase_by_)
  extern f_status_t private_f_thread_semaphores_resize(const f_array_length_t length, f_thread_semaphores_t * const semaphores) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_semaphores_decrease_by_) || !defined(_di_f_thread_semaphores_increase_) || !defined(_di_f_thread_semaphores_increase_by_)

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
  extern f_status_t private_f_thread_sets_adjust(const f_array_length_t length, f_thread_sets_t * const sets) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t * const sets) F_attribute_visibility_internal_d;
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
 *   F_busy (with error bit) if the lock is busy.
 *   F_failure (with error bit) on error.
 *   F_parameter (with error bit) if a parameter is invalid.
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
  extern f_status_t private_f_thread_spin_delete(f_thread_spin_t *spin) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_spins_adjust(const f_array_length_t length, f_thread_spins_t * const spins) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_spins_resize(const f_array_length_t length, f_thread_spins_t * const spins) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_thread_h
