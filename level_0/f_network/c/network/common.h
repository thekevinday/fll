/**
 * FLL - Level 0
 *
 * Project: Network
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines network common data.
 *
 * This is auto-included by network.h and should not need to be explicitly included.
 */
#ifndef _F_network_common_h
#define _F_network_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Designate an ip address family.
 *
 * f_network_family_*_e:
 *   - none: Represents address family is not set.
 *   - ip_4: Represents IP address family version 4, similar to AF_INET.
 *   - ip_6: Represents IP address family version 6, similar to AF_INET6.
 */
#ifndef _di_f_network_family_e_
  enum {
    f_network_family_none_e = 0,
    f_network_family_ip_4_e,
    f_network_family_ip_6_e,
  }; // enum
#endif // _di_f_network_family_e_

/**
 * A union for representing either an IP version 4 or IP version 6 structure.
 *
 * v4: The IP version 4.
 * v6: The IP version 6.
 *
 * macro_f_network_family_ip_4_or_6_t_*:
 *   - initialize_1: Specifically initialize the IP address version 4.
 *   - initialize_2: Specifically initialize the IP address version 6.
 *   - clear:        Clear the union values.
 */
#ifndef _di_f_network_family_ip_4_or_6_t_
  typedef union {
    struct in_addr v4;
    struct in6_addr v6;
  } f_network_family_ip_4_or_6_t;

  #define f_network_family_ip_4_or_6_t_initialize { 0 }

  #define macro_f_network_family_ip_4_or_6_t_initialize_1(v4) { .v4 = v4 }
  #define macro_f_network_family_ip_4_or_6_t_initialize_2(v6) { .v6 = v6 }

  #define f_network_family_ip_4_or_6_t_clear(family_ip_4_or_6) \
    family_ip_4_or_6.v4 = 0; \
    family_ip_4_or_6.v6 = 0;
#endif // _di_f_network_family_ip_4_or_6_t_

/**
 * A structure for managing an IP address version 4 or 6.
 *
 * type:    The type, usually either one of f_network_family_ip_4_e or f_network_family_ip_6_e.
 * address: The address data.
 *
 * macro_f_network_family_ip_4_or_6_t_*:
 *   - initialize_1: Specifically initialize the IP address version 4.
 *   - initialize_2: Specifically initialize the IP address version 6.
 *   - clear:        Clear the union values.
 */
#ifndef _di_f_network_family_ip_t_
  typedef struct {
    uint8_t type;
    f_network_family_ip_4_or_6_t address;
  } f_network_family_ip_t;

  #define f_network_family_ip_t_initialize { 0 }

  #define macro_f_network_family_ip_t_initialize_1(v4) { f_network_family_ip_4_e, macro_f_network_family_ip_4_or_6_t_initialize_1(v4) }
  #define macro_f_network_family_ip_t_initialize_2(v6) { f_network_family_ip_6_e, macro_f_network_family_ip_4_or_6_t_initialize_2(v6) }

  #define f_network_family_ip_t_clear(family_ip) \
    family_ip.type = f_network_family_none_e; \
    f_network_family_ip_t_clear(family_ip.address)
#endif // _di_f_network_family_ip_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_network_common_h
