/**
 * FLL - Level 1
 *
 * Project: String
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
 * Private implementation of f_thread_attributes_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param attributes
 *   The attributes to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_attributes_t_delete().
 *
 * @see f_macro_thread_attributes_t_delete()
 * @see f_thread_attributes_decrease()
 * @see f_thread_attributes_decrease_by()
 * @see f_thread_attributes_delete()
 */
#if !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_delete_)
  extern f_return_status private_f_thread_attributes_delete(f_thread_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_delete_)

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
 *   Errors (with error bit) from: f_macro_thread_attributes_t_resize().
 *
 * @see f_macro_thread_attributes_t_resize()
 * @see f_thread_attributes_decrease()
 * @see f_thread_attributes_decrease_by()
 * @see f_thread_attributes_increase()
 * @see f_thread_attributes_increase_by()
 */
#if !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)
  extern f_return_status private_f_thread_attributes_resize(const f_array_length_t length, f_thread_attributes_t *attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)

/**
 * Private implementation of f_thread_conditions_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param conditions
 *   The conditions to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_conditions_t_delete().
 *
 * @see f_macro_thread_conditions_t_delete()
 * @see f_thread_conditions_decrease()
 * @see f_thread_conditions_decrease_by()
 * @see f_thread_conditions_delete()
 */
#if !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_delete_)
  extern f_return_status private_f_thread_conditions_delete(f_thread_conditions_t *conditions) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_delete_)

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
 *   Errors (with error bit) from: f_macro_thread_conditions_t_resize().
 *
 * @see f_macro_thread_conditions_t_resize()
 * @see f_thread_conditions_decrease()
 * @see f_thread_conditions_decrease_by()
 * @see f_thread_conditions_increase()
 * @see f_thread_conditions_increase_by()
 */
#if !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)
  extern f_return_status private_f_thread_conditions_resize(const f_array_length_t length, f_thread_conditions_t *conditions) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)

/**
 * Private implementation of f_thread_ids_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param ids
 *   The ids to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_ids_t_delete().
 *
 * @see f_macro_thread_ids_t_delete()
 * @see f_thread_ids_decrease()
 * @see f_thread_ids_decrease_by()
 * @see f_thread_ids_delete()
 */
#if !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_delete_)
  extern f_return_status private_f_thread_ids_delete(f_thread_ids_t *ids) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_delete_)

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
 *   Errors (with error bit) from: f_macro_thread_ids_t_resize().
 *
 * @see f_macro_thread_ids_t_resize()
 * @see f_thread_ids_decrease()
 * @see f_thread_ids_decrease_by()
 * @see f_thread_ids_increase()
 * @see f_thread_ids_increase_by()
 */
#if !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_increase_) || !defined(_di_f_thread_ids_increase_by_)
  extern f_return_status private_f_thread_ids_resize(const f_array_length_t length, f_thread_ids_t *ids) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_increase_) || !defined(_di_f_thread_ids_increase_by_)

/**
 * Private implementation of f_thread_keys_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param keys
 *   The keys to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_keys_t_delete().
 *
 * @see f_macro_thread_keys_t_delete()
 * @see f_thread_keys_decrease()
 * @see f_thread_keys_decrease_by()
 * @see f_thread_keys_delete()
 */
#if !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_delete_)
  extern f_return_status private_f_thread_keys_delete(f_thread_keys_t *keys) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_delete_)

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
 *   Errors (with error bit) from: f_macro_thread_keys_t_resize().
 *
 * @see f_macro_thread_keys_t_resize()
 * @see f_thread_keys_decrease()
 * @see f_thread_keys_decrease_by()
 * @see f_thread_keys_increase()
 * @see f_thread_keys_increase_by()
 */
#if !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)
  extern f_return_status private_f_thread_keys_resize(const f_array_length_t length, f_thread_keys_t *keys) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)

/**
 * Private implementation of f_thread_locks_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param locks
 *   The locks to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_locks_t_delete().
 *
 * @see f_macro_thread_locks_t_delete()
 * @see f_thread_locks_decrease()
 * @see f_thread_locks_decrease_by()
 * @see f_thread_locks_delete()
 */
#if !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_delete_)
  extern f_return_status private_f_thread_locks_delete(f_thread_locks_t *locks) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_delete_)

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
 *   Errors (with error bit) from: f_macro_thread_locks_t_resize().
 *
 * @see f_macro_thread_locks_t_resize()
 * @see f_thread_locks_decrease()
 * @see f_thread_locks_decrease_by()
 * @see f_thread_locks_increase()
 * @see f_thread_locks_increase_by()
 */
#if !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)
  extern f_return_status private_f_thread_locks_resize(const f_array_length_t length, f_thread_locks_t *locks) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)

/**
 * Private implementation of f_thread_mutexs_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param mutexs
 *   The mutexs to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_mutexs_t_delete().
 *
 * @see f_macro_thread_mutexs_t_delete()
 * @see f_thread_mutexs_decrease()
 * @see f_thread_mutexs_decrease_by()
 * @see f_thread_mutexs_delete()
 */
#if !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_delete_)
  extern f_return_status private_f_thread_mutexs_delete(f_thread_mutexs_t *mutexs) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_delete_)

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
 *   Errors (with error bit) from: f_macro_thread_mutexs_t_resize().
 *
 * @see f_macro_thread_mutexs_t_resize()
 * @see f_thread_mutexs_decrease()
 * @see f_thread_mutexs_decrease_by()
 * @see f_thread_mutexs_increase()
 * @see f_thread_mutexs_increase_by()
 */
#if !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)
  extern f_return_status private_f_thread_mutexs_resize(const f_array_length_t length, f_thread_mutexs_t *mutexs) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)

/**
 * Private implementation of f_thread_mutex_attributes_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param mutex_attributes
 *   The mutex_attributes to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_mutex_attributes_t_delete().
 *
 * @see f_macro_thread_mutex_attributes_t_delete()
 * @see f_thread_mutex_attributes_decrease()
 * @see f_thread_mutex_attributes_decrease_by()
 * @see f_thread_mutex_attributes_delete()
 */
#if !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_delete_)
  extern f_return_status private_f_thread_mutex_attributes_delete(f_thread_mutex_attributes_t *mutex_attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_delete_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param mutex_attributes
 *   The mutex_attributes to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_mutex_attributes_t_resize().
 *
 * @see f_macro_thread_mutex_attributes_t_resize()
 * @see f_thread_mutex_attributes_decrease()
 * @see f_thread_mutex_attributes_decrease_by()
 * @see f_thread_mutex_attributes_increase()
 * @see f_thread_mutex_attributes_increase_by()
 */
#if !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_)
  extern f_return_status private_f_thread_mutex_attributes_resize(const f_array_length_t length, f_thread_mutex_attributes_t *mutex_attributes) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_)

/**
 * Private implementation of f_thread_onces_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param onces
 *   The onces to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_onces_t_delete().
 *
 * @see f_macro_thread_onces_t_delete()
 * @see f_thread_onces_decrease()
 * @see f_thread_onces_decrease_by()
 * @see f_thread_onces_delete()
 */
#if !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_delete_)
  extern f_return_status private_f_thread_onces_delete(f_thread_onces_t *onces) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_delete_)

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
 *   Errors (with error bit) from: f_macro_thread_onces_t_resize().
 *
 * @see f_macro_thread_onces_t_resize()
 * @see f_thread_onces_decrease()
 * @see f_thread_onces_decrease_by()
 * @see f_thread_onces_increase()
 * @see f_thread_onces_increase_by()
 */
#if !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_increase_) || !defined(_di_f_thread_onces_increase_by_)
  extern f_return_status private_f_thread_onces_resize(const f_array_length_t length, f_thread_onces_t *onces) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_increase_) || !defined(_di_f_thread_onces_increase_by_)

/**
 * Private implementation of f_thread_sets_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param sets
 *   The sets to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_thread_sets_t_delete().
 *
 * @see f_macro_thread_sets_t_delete()
 * @see f_thread_sets_decrease()
 * @see f_thread_sets_decrease_by()
 * @see f_thread_sets_delete()
 */
#if !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_delete_)
  extern f_return_status private_f_thread_sets_delete(f_thread_sets_t *sets) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_delete_)

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
 *   Errors (with error bit) from: f_macro_thread_sets_t_resize().
 *
 * @see f_macro_thread_sets_t_resize()
 * @see f_thread_sets_decrease()
 * @see f_thread_sets_decrease_by()
 * @see f_thread_sets_increase()
 * @see f_thread_sets_increase_by()
 */
#if !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)
  extern f_return_status private_f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t *sets) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_thread_h
