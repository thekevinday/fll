#include "network.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_network_from_host_long_
  f_status_t f_network_from_host_long(const uint32_t from, uint32_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = htonl(from);

    return F_none;
  }
#endif // _di_f_network_from_host_long_

#ifndef _di_f_network_from_host_short_
  f_status_t f_network_from_host_short(const uint16_t from, uint16_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = htons(from);

    return F_none;
  }
#endif // _di_f_network_from_host_short_

#ifndef _di_f_network_from_ip_string_
  f_status_t f_network_from_ip_string(const f_string_static_t from, f_network_family_ip_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!from.used || to->type == f_network_family_none_e) return F_data_not;

    if (inet_pton(to->type == f_network_family_ip_4_e ? AF_INET : AF_INET6, from.string, (void *) & to->address) == -1) {
      if (errno == EAFNOSUPPORT) return F_status_set_error(F_support_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_network_from_ip_string_

#ifndef _di_f_network_to_host_long_
  f_status_t f_network_to_host_long(const uint32_t from, uint32_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = ntohl(from);

    return F_none;
  }
#endif // _di_f_network_to_host_long_

#ifndef _di_f_network_to_host_short_
  f_status_t f_network_to_host_short(const uint16_t from, uint16_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = ntohs(from);

    return F_none;
  }
#endif // _di_f_network_to_host_short_

#ifndef _di_f_network_to_ip_string_
  f_status_t f_network_to_ip_string(const f_network_family_ip_t from, f_string_dynamic_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!(from.type == f_network_family_ip_4_e || from.type == f_network_family_ip_6_e)) return F_data_not;

    {
      const f_status_t status = f_string_dynamic_increase_by((from.type == f_network_family_ip_4_e ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN) + 1, to);
      if (F_status_is_error(status)) return status;
    }

    if (!inet_ntop(from.type == f_network_family_ip_4_e ? AF_INET : AF_INET6, (void *) & from.address, to->string + to->used, from.type == f_network_family_ip_4_e ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN)) {
      if (errno == EAFNOSUPPORT) return F_status_set_error(F_support_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);

      return F_status_set_error(F_failure);
    }

    while (to->used < to->size && to->string[to->used]) {
      ++to->used;
    } // while

    // The string should be NULL terminated, but in case it is not, ensure one always exists.
    to->string[to->used] = 0;

    return F_none;
  }
#endif // _di_f_network_to_ip_string_

#ifdef __cplusplus
} // extern "C"
#endif
