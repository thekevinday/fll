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
 * @param mutexs
 *   The mutexs to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on error.
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_thread_h
