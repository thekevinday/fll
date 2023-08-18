/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_socket_socket_h
#define _PRIVATE_F_socket_socket_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for appending the socket array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source sockets to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 *
 * @see f_sockets_append_all()
 * @see f_socketss_append()
 * @see f_socketss_append_all()
 */
#if !defined(_di_f_sockets_append_all_) || !defined(_di_f_socketss_append_) || !defined(_di_f_socketss_append_all_)
  extern f_status_t private_f_sockets_append_all(const f_sockets_t source, f_sockets_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_sockets_append_all_) || !defined(_di_f_socketss_append_) || !defined(_di_f_socketss_append_all_)

/**
 * Private implementation for resizing the socketss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param socketss
 *   The socketss array to adjust.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 *
 * @see f_socketss_adjust()
 * @see f_socketss_decimate_by()
 */
#if !defined(_di_f_socketss_adjust_) || !defined(_di_f_socketss_decimate_by_)
  extern f_status_t private_f_socketss_adjust(const f_number_unsigned_t length, f_socketss_t * const socketss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_socketss_adjust_) || !defined(_di_f_socketss_decimate_by_)

/**
 * Private implementation for resizing the socketss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param socketss
 *   The socketss array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 *
 * @see f_socketss_decrease_by()
 * @see f_socketss_increase()
 * @see f_socketss_increase_by()
 * @see f_socketss_resize()
 */
#if !defined(_di_f_socketss_decrease_by_) || !defined(_di_f_socketss_increase_) || !defined(_di_f_socketss_increase_by_) || !defined(_di_f_socketss_resize_)
  extern f_status_t private_f_socketss_resize(const f_number_unsigned_t length, f_socketss_t * const socketss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_socketss_decrease_by_) || !defined(_di_f_socketss_increase_) || !defined(_di_f_socketss_increase_by_) || !defined(_di_f_socketss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_socket_socket_h
