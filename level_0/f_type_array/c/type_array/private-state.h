/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_state_h
#define _PRIVATE_F_type_array_state_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the states array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param states
 *   The states array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_states_adjust()
 * @see f_states_decimate_by()
 */
#if !defined(_di_f_states_adjust_) || !defined(_di_f_states_decimate_by_)
  extern f_status_t private_f_states_adjust(const f_array_length_t length, f_states_t *states) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_states_adjust_) || !defined(_di_f_states_decimate_by_)

/**
 * Private implementation for appending the state array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source states to append.
 * @param destination
 *   The destination states the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_states_append()
 * @see f_statess_append()
 */
#if !defined(_di_f_states_append_) || !defined(_di_f_statess_append_)
  extern f_status_t private_f_states_append(const f_states_t source, f_states_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_states_append_) || !defined(_di_f_statess_append_)

/**
 * Private implementation for resizing the states array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param states
 *   The states array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_states_resize()
 * @see f_states_append()
 * @see f_states_decimate_by()
 * @see f_statess_append()
 */
#if !defined(_di_f_states_resize_) || !defined(_di_f_states_append_) || !defined(_di_f_states_decimate_by_) || !defined(_di_f_statess_append_)
  extern f_status_t private_f_states_resize(const f_array_length_t length, f_states_t *states) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_states_resize_) || !defined(_di_f_states_append_) || !defined(_di_f_states_decimate_by_) || !defined(_di_f_statess_append_)

/**
 * Private implementation for resizing the statess array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param statess
 *   The statess array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 *
 * @see f_statess_adjust()
 * @see f_statess_decimate_by()
 */
#if !defined(_di_f_statess_adjust_) || !defined(_di_f_statess_decimate_by_)
  extern f_status_t private_f_statess_adjust(const f_array_length_t length, f_statess_t *statess) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statess_adjust_) || !defined(_di_f_statess_decimate_by_)

/**
 * Private implementation for resizing the statess array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param statess
 *   The statess array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_statess_decrease_by()
 * @see f_statess_increase()
 * @see f_statess_increase_by()
 * @see f_statess_resize()
 */
#if !defined(_di_f_statess_decrease_by_) || !defined(_di_f_statess_increase_) || !defined(_di_f_statess_increase_by_) || !defined(_di_f_statess_resize_)
  extern f_status_t private_f_statess_resize(const f_array_length_t length, f_statess_t *statess) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_statess_decrease_by_) || !defined(_di_f_statess_increase_) || !defined(_di_f_statess_increase_by_) || !defined(_di_f_statess_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_state_h
