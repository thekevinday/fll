/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_type_array_poll_h
#define _PRIVATE_F_type_array_poll_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the polls array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param polls
 *   The polls array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *
 * @see f_polls_adjust()
 * @see f_polls_decimate_by()
 */
#if !defined(_di_f_polls_adjust_) || !defined(_di_f_polls_decimate_by_)
  extern f_status_t private_f_polls_adjust(const f_number_unsigned_t length, f_polls_t *polls) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_polls_adjust_) || !defined(_di_f_polls_decimate_by_)

/**
 * Private implementation for appending the poll array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source poll to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_polls_append()
 * @see f_pollss_append()
 */
#if !defined(_di_f_polls_append_) || !defined(_di_f_pollss_append_)
  extern f_status_t private_f_polls_append(const f_poll_t source, f_polls_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_polls_append_) || !defined(_di_f_pollss_append_)

/**
 * Private implementation for appending the poll array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source polls to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 * @see f_polls_append_all()
 * @see f_pollss_append()
 * @see f_pollss_append_all()
 */
#if !defined(_di_f_polls_append_) || !defined(_di_f_polls_append_all_) || !defined(_di_f_pollss_append_all_)
  extern f_status_t private_f_polls_append_all(const f_polls_t source, f_polls_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_polls_append_) || !defined(_di_f_polls_append_all_) || !defined(_di_f_pollss_append_all_)

/**
 * Private implementation for resizing the polls array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param polls
 *   The polls array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_polls_resize()
 * @see f_polls_append()
 * @see f_polls_decrease_by()
 * @see f_pollss_append()
 */
#if !defined(_di_f_polls_resize_) || !defined(_di_f_polls_append_) || !defined(_di_f_polls_decrease_by_) || !defined(_di_f_pollss_append_)
  extern f_status_t private_f_polls_resize(const f_number_unsigned_t length, f_polls_t *polls) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_polls_resize_) || !defined(_di_f_polls_append_) || !defined(_di_f_polls_decrease_by_) || !defined(_di_f_pollss_append_)

/**
 * Private implementation for resizing the pollss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param pollss
 *   The pollss array to adjust.
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
 * @see f_pollss_adjust()
 * @see f_pollss_decimate_by()
 */
#if !defined(_di_f_pollss_adjust_) || !defined(_di_f_pollss_decimate_by_)
  extern f_status_t private_f_pollss_adjust(const f_number_unsigned_t length, f_pollss_t *pollss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_pollss_adjust_) || !defined(_di_f_pollss_decimate_by_)

/**
 * Private implementation for resizing the pollss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param pollss
 *   The pollss array to resize.
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
 * @see f_pollss_decrease_by()
 * @see f_pollss_increase()
 * @see f_pollss_increase_by()
 * @see f_pollss_resize()
 */
#if !defined(_di_f_pollss_decrease_by_) || !defined(_di_f_pollss_increase_) || !defined(_di_f_pollss_increase_by_) || !defined(_di_f_pollss_resize_)
  extern f_status_t private_f_pollss_resize(const f_number_unsigned_t length, f_pollss_t *pollss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_pollss_decrease_by_) || !defined(_di_f_pollss_increase_) || !defined(_di_f_pollss_increase_by_) || !defined(_di_f_pollss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_type_array_poll_h
