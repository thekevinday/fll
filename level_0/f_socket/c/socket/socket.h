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
 * Commonly used socket related properties, loosely based off of f_file_t.
 *
 * Properties:
 *   - id:       Socket file descriptor, used for binding and listening.
 *   - id_data:  Data file descriptor, used for reading and writing data from or to the socket.
 *   - domain:   The socket domain (protocol family, such as f_socket_protocol_family_local_e).
 *   - protocol: The socket protocol (such as f_socket_protocol_tcp_e).
 *   - type:     The socket type (address family, such as f_socket_address_family_local_e).
 *   - form:     The form of the socket address type, such as f_socket_address_form_inet4_e for sockaddr_in.
 *
 *   - size_read:  The default number of 1-byte characters to read at a time and is often used for the read buffer size.
 *   - size_write: The default number of 1-byte characters to read at a time and is often used for the write buffer size.
 *
 *   - address: The socket address.
 *   - length:  The length of the socket.
 *
 *   - name: The name of the socket, if a name is given (for UNIX sockets this represents the path) (Must be a NULL terminated string).
 *
 * The clear and reset macros do not clear or reset the address (type f_socket_address_t) because the struct sockaddr is defined outside of the FLL project.
 */
#ifndef _di_f_socket_t_
  typedef struct {
    int id;
    int id_data;
    int domain;
    int protocol;
    int type;
    uint16_t form;

    size_t size_read;
    size_t size_write;

    f_socket_address_t address;
    socklen_t length;

    f_string_static_t name;
  } f_socket_t;

  #define f_socket_t_initialize { -1, -1, 0, 0, 0, f_socket_address_form_generic_e, F_socket_default_read_size_d, F_socket_default_write_size_d, f_socket_address_t_initialize, 0, f_string_static_t_initialize }

  #define macro_f_socket_t_initialize_1(form, address, length) { \
    -1, \
    -1, \
    0, \
    0, \
    0, \
    form, \
    F_socket_default_read_size_d, \
    F_socket_default_write_size_d, \
    address, \
    length, \
    f_string_empty_s \
  }

  #define macro_f_socket_t_initialize_2(form, address, length, name) { \
    -1, \
    -1, \
    0, \
    0, \
    0, \
    form, \
    F_socket_default_read_size_d, \
    F_socket_default_write_size_d, \
    address, \
    length, \
    name \
  }

  #define macro_f_socket_t_initialize_3(id, domain, protocol, type, form, address, length, name) { \
    id, \
    -1, \
    domain, \
    protocol, \
    type, \
    form, \
    F_socket_default_read_size_d, \
    F_socket_default_write_size_d, \
    address, \
    length, \
    name \
  }

  #define macro_f_socket_t_initialize_4(id, domain, protocol, type, form, size_read, size_write, address, length, name) { \
    id, \
    -1, \
    domain, \
    protocol, \
    type, \
    form, \
    size_read, \
    size_write, \
    address, \
    length, \
    name \
  }

  #define macro_f_socket_t_initialize_5(id, id_data, domain, protocol, type, form, size_read, size_write, address, length, name) { \
    id, \
    id_data, \
    domain, \
    protocol, \
    type, \
    form, \
    size_read, \
    size_write, \
    address, \
    length, \
    name \
  }

  #define macro_f_socket_t_clear(file) \
    file.id = -1; \
    file.id_data = -1; \
    file.domain = 0; \
    file.protocol = 0; \
    file.type = 0; \
    file.form = 0; \
    file.size_read = 0; \
    file.size_write = 0; \
    file.length = 0; \
    macro_f_string_static_t_clear(file);

  #define macro_f_socket_t_reset(file) \
    file.id = -1; \
    file.id_data = -1; \
    file.domain = 0; \
    file.protocol = 0; \
    file.type = 0; \
    file.form = f_socket_address_form_generic_e; \
    file.size_read = F_socket_default_read_size_d; \
    file.size_write = F_socket_default_write_size_d; \
    file.length = 0; \
    macro_f_string_static_t_clear(file);
#endif // _di_f_socket_t_

/**
 * An array of f_socket_t.
 *
 * Properties:
 *   - array: The array of f_socket_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_sockets_t_
  typedef struct {
    f_socket_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_sockets_t;

  #define f_sockets_t_initialize { 0, 0, 0 }

  #define macro_f_sockets_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_sockets_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_sockets_t_

/**
 * This holds an array of f_sockets_t.
 *
 * Properties:
 *   - array: The array of f_socket_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_socketss_t_
  typedef struct {
    f_sockets_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_socketss_t;

  #define f_socketss_t_initialize { 0, 0, 0 }

  #define macro_f_socketss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_socketss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_socketss_t_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_socketss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_socketss_delete_callback_
  extern f_status_t f_socketss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_socketss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_socketss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_socketss_destroy_callback_
  extern f_status_t f_socketss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_socketss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_socket_h
