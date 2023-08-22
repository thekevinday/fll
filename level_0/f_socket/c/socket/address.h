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
#ifndef _F_socket_address_h
#define _F_socket_address_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide a union to simplify using struct sockaddr in arrays.
 *
 * Managing different structures is not as practical.
 * At the cost of resources, use the same space for all of these.
 * This can then easily be used in a generic array that has a mixture of these.
 *
 * All of the properties may or may not be present, but inet4, inet6, and local are generally assumed to exist.
 *
 * Properties:
 *   - arp:   Arp.
 *   - at:    At.
 *   - ax25:  Ax25.
 *   - dl:    Dl.
 *   - eon:   Eon.
 *   - inet4: Ipv4 internet network socket.
 *   - inet6: Ipv6 internet network socket..
 *   - ipx:   Ipx.
 *   - iso:   Iso.
 *   - local: Local (aka: Unix) socket (socket file or localhost).
 *   - ns:    Ns.
 *   - x25:   X25.
 */
#ifndef _di_f_socket_address_t_
  typedef union {
    struct sockaddr_in inet4;
    struct sockaddr_in6 inet6;
    struct sockaddr_un local;

    #ifdef _en_support_socket_address_arp_
      struct sockaddr_inarp arp;
    #endif // _en_support_socket_address_arp_

    #ifdef _en_support_socket_address_at_
      struct sockaddr_at at;
    #endif // _en_support_socket_address_at_

    #ifdef _en_support_socket_address_ax25_
      struct sockaddr_ax25 ax25;
    #endif // _en_support_socket_address_ax25_

    #ifdef _en_support_socket_address_dl_
      struct sockaddr_dl dl;
    #endif // _en_support_socket_address_dl_

    #ifdef _en_support_socket_address_eon_
      struct sockaddr_eon eon;
    #endif // _en_support_socket_address_eon_

    #ifdef _en_support_socket_address_ipx_
      struct sockaddr_ipx ipx;
    #endif // _en_support_socket_address_ipx_

    #ifdef _en_support_socket_address_iso_
      struct sockaddr_iso iso;
    #endif // _en_support_socket_address_iso_

    #ifdef _en_support_socket_address_ns_
      struct sockaddr_ns ns;
    #endif // _en_support_socket_address_ns_

    #ifdef _en_support_socket_address_x25_
      struct sockaddr_x25 x25;
    #endif // _en_support_socket_address_x25_
  } f_socket_address_t;

  #define f_socket_address_t_initialize { 0 }

  #define f_socket_address_initialize_inet4(value_inet4) { .inet4 = value_inet4 }
  #define f_socket_address_initialize_inet6(value_inet6) { .inet6 = value_inet6 }
  #define f_socket_address_initialize_local(value_local) { .local = value_local }
  #define f_socket_address_initialize_arp(value_arp) { .arp = value_arp }
  #define f_socket_address_initialize_at(value_at) { .at = value_at }
  #define f_socket_address_initialize_ax25(value_ax25) { .ax25 = value_ax25 }
  #define f_socket_address_initialize_dl(value_dl) { .dl = value_dl }
  #define f_socket_address_initialize_eon(value_eon) { .local = value_eon }
  #define f_socket_address_initialize_ipx(value_ipx) { .ipx = value_ipx }
  #define f_socket_address_initialize_iso(value_iso) { .iso = value_iso }
  #define f_socket_address_initialize_ns(value_ns) { .ns = value_ns }
  #define f_socket_address_initialize_x25(value_x25) { .x25 = value_x25 }
#endif // _di_f_socket_address_t_

/**
 * An array of f_socket_address_t.
 *
 * Properties:
 *   - array: The array of f_socket_address_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_socket_addresss_t_
  typedef struct {
    f_socket_address_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_socket_addresss_t;

  #define f_socket_addresss_t_initialize { 0, 0, 0 }

  #define macro_f_socket_addresss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_socket_addresss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_socket_addresss_t_

/**
 * This holds an array of an array of f_socket_address_t.
 *
 * Properties:
 *   - array: The array of an array of f_socket_address_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_socket_addressss_t_
  typedef struct {
    f_socket_addresss_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_socket_addressss_t;

  #define f_socket_addressss_t_initialize { 0, 0, 0 }

  #define macro_f_socket_addressss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_socket_addressss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_socket_addressss_t_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_socket_addressss_t structure.
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
#ifndef _di_f_socket_addressss_delete_callback_
  extern f_status_t f_socket_addressss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_socket_addressss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_socket_addressss_t structure.
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
#ifndef _di_f_socket_addressss_destroy_callback_
  extern f_status_t f_socket_addressss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_socket_addressss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_socket_address_h
