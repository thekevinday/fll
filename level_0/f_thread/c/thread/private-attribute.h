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
#ifndef _PRIVATE_F_thread_attribute_h
#define _PRIVATE_F_thread_attribute_h

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
  extern f_status_t private_f_thread_attributes_adjust(const f_number_unsigned_t length, f_thread_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_attributes_resize(const f_number_unsigned_t length, f_thread_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_barriers_adjust(const f_number_unsigned_t length, f_thread_barriers_t * const barriers) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_barriers_resize(const f_number_unsigned_t length, f_thread_barriers_t * const barriers) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_barrier_attributes_adjust(const f_number_unsigned_t length, f_thread_barrier_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_barrier_attributes_resize(const f_number_unsigned_t length, f_thread_barrier_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_condition_attributes_adjust(const f_number_unsigned_t length, f_thread_condition_attributes_t * const attributes) F_attribute_visibility_internal_d;
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
  extern f_status_t private_f_thread_condition_attributes_resize(const f_number_unsigned_t length, f_thread_condition_attributes_t * const attributes) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_condition_attributes_decrease_by_) || !defined(_di_f_thread_condition_attributes_increase_) || !defined(_di_f_thread_condition_attributes_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_thread_attribute_h
