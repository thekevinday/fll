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
#ifndef _PRIVATE_F_thread_spin_h
#define _PRIVATE_F_thread_spin_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for deleting (and destroying).
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param structure
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
  extern f_status_t private_f_thread_spin_delete(f_thread_spin_t *structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_) || !defined(_di_f_thread_spins_decrease_) || !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_) || !defined(_di_f_thread_spins_resize_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The spins to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_thread_spins_adjust()
 * @see f_thread_spins_decimate_by()
 */
#if !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_)
  extern f_status_t private_f_thread_spins_adjust(const f_number_unsigned_t length, f_thread_spins_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_spins_adjust_) || !defined(_di_f_thread_spins_decimate_by_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param structure
 *   The spins to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_thread_spins_decrease_by()
 * @see f_thread_spins_increase()
 * @see f_thread_spins_increase_by()
 */
#if !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_)
  extern f_status_t private_f_thread_spins_resize(const f_number_unsigned_t length, f_thread_spins_t * const structure) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_thread_spins_decrease_by_) || !defined(_di_f_thread_spins_increase_) || !defined(_di_f_thread_spins_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_thread_spin_h