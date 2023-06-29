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
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/string.h>

// FLL-0 network includes.
#include <fll/level_0/network/common.h>

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
  extern f_status_t f_network_from_host_long(const uint32_t from, uint32_t * const to);
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
  extern f_status_t f_network_from_host_short(const uint16_t from, uint16_t * const to);
#endif // _di_f_network_from_host_short_

/**
 * Convert from a IP version 4 or version 6 family integer into a network IP address host entity.
 *
 * This is for the Domain Name and is not for the IP address digit itself.
 *
 * @param from
 *   The IP version 4 or version 6 family integer.
 * @param to
 *   The converted IP host entity.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to convert (to.type is f_network_family_none_e).
 *
 *   F_again (with error bit) Resolver temporarily failed, try again.
 *   F_data_not (with error bit) The requested name is valid, but does not have an IP address.
 *   F_found_not (with error bit) Resolver did not know host.
 *   F_recover_not (with error bit) Resolver failed and cannot recover from the failure, do not try again.
 *   F_failure (with error bit) on any other error.
 *
 * @see gethostbyaddr()
 */
#ifndef _di_f_network_from_ip_address_
  extern f_status_t f_network_from_ip_address(const f_network_family_ip_t from, struct hostent * const to);
#endif // _di_f_network_from_ip_address_

/**
 * Convert from a Domain Name into a network IP address host entity.
 *
 * This is for the Domain Name and is not for the IP address digit itself.
 *
 * @param from
 *   The human-friendly IP Domain Name.
 * @param to
 *   The converted IP host entity.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to convert (from.used is 0).
 *
 *   F_again (with error bit) Resolver temporarily failed, try again.
 *   F_data_not (with error bit) The requested name is valid, but does not have an IP address.
 *   F_found_not (with error bit) Resolver did not know host.
 *   F_recover_not (with error bit) Resolver failed and cannot recover from the failure, do not try again.
 *   F_failure (with error bit) on any other error.
 *
 * @see gethostbyname()
 */
#ifndef _di_f_network_from_ip_name_
  extern f_status_t f_network_from_ip_name(const f_string_static_t from, struct hostent * const to);
#endif // _di_f_network_from_ip_name_

/**
 * Convert from a human-friendly string representing the IP address digit into a network IP address digit.
 *
 * This is for the IP address and is not for the Domain Name.
 *
 * @param from
 *   The human-friendly IP address string.
 * @param to
 *   The converted IP version 4 or version 6 family integer.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to convert (to.type is f_network_family_none_e or from.used is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_space_not (with error bit) if not enough space is available in to.string.
 *   F_support_not (with error bit) if an invalid address family type is passed to inet_pton().
 *   F_failure (with error bit) on any other error.
 *
 * @see inet_pton()
 */
#ifndef _di_f_network_from_ip_string_
  extern f_status_t f_network_from_ip_string(const f_string_static_t from, f_network_family_ip_t * const to);
#endif // _di_f_network_from_ip_string_

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
  extern f_status_t f_network_to_host_long(const uint32_t from, uint32_t * const to);
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
  extern f_status_t f_network_to_host_short(const uint16_t from, uint16_t * const to);
#endif // _di_f_network_to_host_short_

/**
 * Convert from a network IP address digit into a human-friendly string representing the IP address digit.
 *
 * This is for the IP address and is not for the Domain Name.
 *
 * @param from
 *   The IP version 4 or version 6 family integer.
 * @param to
 *   The converted human-friendly IP address string.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success but there is nothing to convert (from.type is f_network_family_none_e).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_space_not (with error bit) if not enough space is available in to.string.
 *   F_support_not (with error bit) if an invalid address family type is passed to inet_ntop().
 *   F_failure (with error bit) on any other error.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by()
 *
 * @see inet_ntop()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_network_to_ip_string_
  extern f_status_t f_network_to_ip_string(const f_network_family_ip_t from, f_string_dynamic_t * const to);
#endif // _di_f_network_to_ip_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_network_h
