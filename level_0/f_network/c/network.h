/**
 * FLL - Level 0
 *
 * Project: Network
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides network related functionality.
 */
#ifndef _F_network_h
#define _F_network_h

// Libc includes.
#include <arpa/inet.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>

// FLL-0 network includes.

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert from host byte order to network byte order for an unsigned long integer.
 *
 * @param from
 *   The long integer in host byte order.
 * @param to
 *   The converted long integer in network byte order.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see htonl()
 */
#ifndef _di_f_network_from_host_long_
  extern f_status_t f_network_from_host_long(const uint32_t from, uint32_t *to);
#endif // _di_f_network_from_host_long_

/**
 * Convert from host byte order to network byte order for an unsigned short integer.
 *
 * @param from
 *   The short integer in host byte order.
 * @param to
 *   The converted short integer in network byte order.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see htons()
 */
#ifndef _di_f_network_from_host_short_
  extern f_status_t f_network_from_host_short(const uint16_t from, uint16_t *to);
#endif // _di_f_network_from_host_short_

/**
 * Convert from network byte order to host byte order for an unsigned long integer.
 *
 * @param from
 *   The long integer in network byte order.
 * @param to
 *   The converted long integer in host byte order.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see ntohl()
 */
#ifndef _di_f_network_to_host_long_
  extern f_status_t f_network_to_host_long(const uint32_t from, uint32_t *to);
#endif // _di_f_network_to_host_long_

/**
 * Convert from network byte order to host byte order for an unsigned short integer.
 *
 * @param from
 *   The short integer in network byte order.
 * @param to
 *   The converted short integer in host byte order.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see ntohs()
 */
#ifndef _di_f_network_to_host_short_
  extern f_status_t f_network_to_host_short(const uint16_t from, uint16_t *to);
#endif // _di_f_network_to_host_short_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_network_h
