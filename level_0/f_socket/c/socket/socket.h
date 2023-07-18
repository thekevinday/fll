/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines socket type related functionality.
 *
 * This is auto-included by socket.h and should not need to be explicitly included.
 */
#ifndef _F_socket_socket_h
#define _F_socket_socket_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize the string sockets array.
 *
 * @param length
 *   The new size to use.
 * @param sockets
 *   The string sockets array to resize.
 *
 * @return
 *   Success from f_memory_array_adjust().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_sockets_adjust_
  extern f_status_t f_sockets_adjust(const f_number_unsigned_t length, f_sockets_t * const sockets);
#endif // _di_f_sockets_adjust_

/**
 * Append the single source socket onto the destination.
 *
 * @param source
 *   The source socket to append.
 * @param destination
 *   The destination sockets the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 */
#ifndef _di_f_sockets_append_
  extern f_status_t f_sockets_append(const f_socket_t source, f_sockets_t * const destination);
#endif // _di_f_sockets_append_

/**
 * Append the source sockets onto the destination.
 *
 * @param source
 *   The source sockets to append.
 * @param destination
 *   The destination sockets the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 */
#ifndef _di_f_sockets_append_all_
  extern f_status_t f_sockets_append_all(const f_sockets_t source, f_sockets_t * const destination);
#endif // _di_f_sockets_append_all_

/**
 * Resize the string sockets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param sockets
 *   The string sockets array to resize.
 *
 * @return
 *   Success from f_memory_array_decimate_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decimate_by().
 *
 * @see f_memory_array_decimate_by()
 */
#ifndef _di_f_sockets_decimate_by_
  extern f_status_t f_sockets_decimate_by(const f_number_unsigned_t amount, f_sockets_t * const sockets);
#endif // _di_f_sockets_decimate_by_

/**
 * Resize the string sockets array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param sockets
 *   The string sockets array to resize.
 *
 * @return
 *   Success from f_memory_array_decrease_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decrease_by().
 *
 * @see f_memory_array_decrease_by()
 */
#ifndef _di_f_sockets_decrease_by_
  extern f_status_t f_sockets_decrease_by(const f_number_unsigned_t amount, f_sockets_t * const sockets);
#endif // _di_f_sockets_decrease_by_

/**
 * Increase the size of the string sockets array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param sockets
 *   The string sockets array to resize.
 *
 * @return
 *   Success from f_memory_array_increase().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 */
#ifndef _di_f_sockets_increase_
  extern f_status_t f_sockets_increase(const f_number_unsigned_t step, f_sockets_t * const sockets);
#endif // _di_f_sockets_increase_

/**
 * Resize the string sockets array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param sockets
 *   The string sockets array to resize.
 *
 * @return
 *   Success from f_memory_array_increase_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_sockets_increase_by_
  extern f_status_t f_sockets_increase_by(const f_number_unsigned_t amount, f_sockets_t * const sockets);
#endif // _di_f_sockets_increase_by_

/**
 * Resize the string sockets array.
 *
 * @param length
 *   The new size to use.
 * @param sockets
 *   The string sockets array to adjust.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_sockets_resize_
  extern f_status_t f_sockets_resize(const f_number_unsigned_t length, f_sockets_t * const sockets);
#endif // _di_f_sockets_resize_

/**
 * Resize the string socketss array.
 *
 * @param length
 *   The new size to use.
 * @param socketss
 *   The string socketss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_memory_destroy().
 */
#ifndef _di_f_socketss_adjust_
  extern f_status_t f_socketss_adjust(const f_number_unsigned_t length, f_socketss_t * const socketss);
#endif // _di_f_socketss_adjust_

/**
 * Append the single source sockets onto the destination.
 *
 * @param source
 *   The source sockets to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 */
#ifndef _di_f_socketss_append_
  extern f_status_t f_socketss_append(const f_sockets_t source, f_socketss_t * const destination);
#endif // _di_f_socketss_append_

/**
 * Append the source socketss onto the destination.
 *
 * @param source
 *   The source socketss to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 */
#ifndef _di_f_socketss_append_all_
  extern f_status_t f_socketss_append_all(const f_socketss_t source, f_socketss_t * const destination);
#endif // _di_f_socketss_append_all_

/**
 * Resize the string socketss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param socketss
 *   The string socketss array to resize.
 *
 * @return
 *   F_data_not on success, but the amount to decrease by is 0.
 *
 *   Success from f_memory_array_decimate_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decimate_by().
 *
 * @see f_memory_array_decimate_by()
 */
#ifndef _di_f_socketss_decimate_by_
  extern f_status_t f_socketss_decimate_by(const f_number_unsigned_t amount, f_socketss_t * const socketss);
#endif // _di_f_socketss_decimate_by_

/**
 * Resize the string socketss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param socketss
 *   The string socketss array to resize.
 *
 * @return
 *   F_data_not on success, but the amount to decrease by is 0.
 *
 *   Success from f_memory_array_decrease_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_decrease_by().
 *
 * @see f_memory_array_decrease_by()
 */
#ifndef _di_f_socketss_decrease_by_
  extern f_status_t f_socketss_decrease_by(const f_number_unsigned_t amount, f_socketss_t * const socketss);
#endif // _di_f_socketss_decrease_by_

/**
 * Increase the size of the string socketss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param socketss
 *   The string socketss array to resize.
 *
 * @return
 *   Success from f_memory_array_increase().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase().
 *
 * @see f_memory_array_increase()
 */
#ifndef _di_f_socketss_increase_
  extern f_status_t f_socketss_increase(const f_number_unsigned_t step, f_socketss_t * const socketss);
#endif // _di_f_socketss_increase_

/**
 * Resize the string socketss array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param socketss
 *   The string socketss array to resize.
 *
 * @return
 *   Success from f_memory_array_increase_by().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_socketss_increase_by_
  extern f_status_t f_socketss_increase_by(const f_number_unsigned_t amount, f_socketss_t * const socketss);
#endif // _di_f_socketss_increase_by_

/**
 * Resize the string socketss array.
 *
 * @param length
 *   The new size to use.
 * @param socketss
 *   The string socketss array to adjust.
 *
 * @return
 *   Success from f_memory_array_resize().
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_socketss_resize_
  extern f_status_t f_socketss_resize(const f_number_unsigned_t length, f_socketss_t * const socketss);
#endif // _di_f_socketss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_socket_h
