#include "network.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_network_from_host_long_
  f_status_t f_network_from_host_long(const uint32_t from, uint32_t *to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = htonl(from);

    return F_none;
  }
#endif // _di_f_network_from_host_long_

#ifndef _di_f_network_from_host_short_
  f_status_t f_network_from_host_short(const uint16_t from, uint16_t *to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = htons(from);

    return F_none;
  }
#endif // _di_f_network_from_host_short_

#ifndef _di_f_network_to_host_long_
  f_status_t f_network_to_host_long(const uint32_t from, uint32_t *to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = ntohl(from);

    return F_none;
  }
#endif // _di_f_network_to_host_long_

#ifndef _di_f_network_to_host_short_
  f_status_t f_network_to_host_short(const uint16_t from, uint16_t *to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = ntohs(from);

    return F_none;
  }
#endif // _di_f_network_to_host_short_

#ifdef __cplusplus
} // extern "C"
#endif
