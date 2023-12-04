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

    return F_okay;
  }
#endif // _di_f_network_from_host_long_

#ifndef _di_f_network_from_host_short_
  f_status_t f_network_from_host_short(const uint16_t from, uint16_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = htons(from);

    return F_okay;
  }
#endif // _di_f_network_from_host_short_

#ifndef _di_f_network_from_ip_address_
  f_status_t f_network_from_ip_address(const f_network_family_ip_t from, struct hostent * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!(from.type == f_network_family_ip_4_e || from.type == f_network_family_ip_6_e)) return F_data_not;

    h_errno = 0;

    struct hostent * const result = from.type == f_network_family_ip_4_e
      ? gethostbyaddr((void *) &from.address.v4, INET_ADDRSTRLEN, AF_INET)
      : gethostbyaddr((void *) &from.address.v6, INET6_ADDRSTRLEN, AF_INET6);

    if (!result) {
      if (h_errno == HOST_NOT_FOUND) return F_status_set_error(F_found_not);
      if (h_errno == NO_DATA || h_errno == NO_ADDRESS) return F_status_set_error(F_data_not);
      if (h_errno == NO_RECOVERY) return F_status_set_error(F_recover_not);
      if (h_errno == TRY_AGAIN) return F_status_set_error(F_again);

      return F_status_set_error(F_failure);
    }

    memcpy((void *) to, (void *) result, sizeof(struct hostent));

    return F_okay;
  }
#endif // _di_f_network_from_ip_address_

#ifndef _di_f_network_from_ip_name_
  f_status_t f_network_from_ip_name(const f_string_static_t from, struct hostent * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!from.used) return F_data_not;

    h_errno = 0;

    struct hostent * const result = gethostbyname(from.string);

    if (!result) {
      if (h_errno == HOST_NOT_FOUND) return F_status_set_error(F_found_not);
      if (h_errno == NO_DATA || h_errno == NO_ADDRESS) return F_status_set_error(F_data_not);
      if (h_errno == NO_RECOVERY) return F_status_set_error(F_recover_not);
      if (h_errno == TRY_AGAIN) return F_status_set_error(F_again);

      return F_status_set_error(F_failure);
    }

    memcpy((void *) to, (void *) result, sizeof(struct hostent));

    return F_okay;
  }
#endif // _di_f_network_from_ip_name_

#ifndef _di_f_network_from_ip_string_
  f_status_t f_network_from_ip_string(const f_string_static_t from, f_network_family_ip_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!from.used || to->type == f_network_family_none_e) return F_data_not;

    {
      const int result = (to->type == f_network_family_ip_4_e)
        ? inet_pton(AF_INET, from.string, (void *) & to->address.v4)
        : inet_pton(AF_INET6, from.string, (void *) & to->address.v6);

      if (result == -1) {
        if (errno == EAFNOSUPPORT) return F_status_set_error(F_support_not);

        return F_status_set_error(F_failure);
      }
      else if (result) {
        return F_okay;
      }
    }

    return F_status_set_error(F_address_not);
  }
#endif // _di_f_network_from_ip_string_

#ifndef _di_f_network_is_ip_address_
  void f_network_is_ip_address(const f_string_static_t address, f_string_range_double_t * const where, f_state_t * const state) {

    if (!state) return;

    if (!address.used) {
      state->status = F_data_not;

      return;
    }

    f_number_unsigned_t i = 0;
    uint8_t flag = 0x0; // 0x1 == is IPv6.
    uint8_t set = 0;
    uint8_t count = 0;
    f_string_range_double_t at = f_string_range_double_t_initialize;

    for (; i < address.used; ++i) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) return;
      }

      if (!address.string[i]) continue;

      if (isxdigit(address.string[i])) {
        if (address.string[i] < f_string_ascii_0_s.string[0] || address.string[i] > f_string_ascii_9_s.string[0]) {
          flag |= 0x1;
        }

        if (!where) {
          if (at.start_1 > at.stop_1) {
            at.start_1 = at.stop_1 = i;
          }
        }

        ++count;

        continue;
      }

      if (address.string[i] == f_string_ascii_period_s.string[0]) {

        // An IPv4 looking address with a hexidecimal letter.
        if (flag & 0x1) {
          state->status = F_network_version_four_not;

          return;
        }

        break;
      }

      if (address.string[i] == f_string_ascii_colon_s.string[0]) {
        flag = 0x1;

        break;
      }

      if (address.string[i] == f_string_ascii_bracket_open_s.string[0]) {
        if (flag) {
          state->status = F_false;

          return;
        }

        flag |= 0x3;

        break;
      }

      state->status = F_false;

      return;
    } // for

    if (i >= address.used) {
      state->status = F_false;

      return;
    }

    at.start_1 = i;

    if (flag & 0x1) {

      // IPv6 flag additions: 0x2 == has bracket open, 0x4 == has forward slash, 0x8 = has double-colon, 0x10 = has no leading digit and no bracket open.
      if (flag & 0x2) {
        ++i;
      }

      state->status = F_network_version_six_not;

      if (count > 4 || i == address.used) return;

      if (!count) {

        // Skip past NULL characters.
        for (; i < address.used && !address.string[i]; ++i) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) return;

            // Restore status in case the interrupt callback changed it.
            state->status = F_network_version_six_not;
          }
        } // for

        if (i == address.used) return;
        if (!(flag & 0x2)) flag |= 0x10;

        at.start_1 = i;
      }

      // Process address, counting all sets.
      for (; i < address.used; ++i) {

        if (state->interrupt) {
          state->interrupt((void *) state, 0);
          if (F_status_set_fine(state->status) == F_interrupt) return;

          // Restore status in case the interrupt callback changed it.
          state->status = F_network_version_six_not;
        }

        if (!address.string[i]) continue;

        if (isxdigit(address.string[i])) {
          if (++count > 4) return;

          if (flag & 0x4) {
            if (address.string[i] < f_string_ascii_0_s.string[0] || address.string[i] > f_string_ascii_9_s.string[0] || count > 3) return;
          }
        }
        else if (address.string[i] == f_string_ascii_colon_s.string[0]) {
          if (flag & 0x4) return;

          at.stop_1 = i;
          at.start_2 = i + 1;

          if (at.start_2 < address.used) {

            // Skip past NULL characters.
            for (; at.start_2 < address.used && !address.string[at.start_2]; ++at.start_2) {

              if (state->interrupt) {
                state->interrupt((void *) state, 0);
                if (F_status_set_fine(state->status) == F_interrupt) return;

                // Restore status in case the interrupt callback changed it.
                state->status = F_network_version_six_not;
              }
            } // for

            if (at.start_2 == address.used) return;

            if (address.string[at.start_2] == f_string_ascii_colon_s.string[0]) {
              if (flag & 0x8) return;

              flag |= 0x8;

              // Skip past NULL characters.
              for (; at.start_2 < address.used && !address.string[at.start_2]; ++at.start_2) {

                if (state->interrupt) {
                  state->interrupt((void *) state, 0);
                  if (F_status_set_fine(state->status) == F_interrupt) return;

                  // Restore status in case the interrupt callback changed it.
                  state->status = F_network_version_six_not;
                }
              } // for

              // Must not end on a double-colon.
              if (at.start_2 == address.used) return;
            }

            // Colons must be followed by a hexidecimal digit.
            if (!isxdigit(address.string[at.start_2])) return;

            i = at.stop_1 = at.start_2;
          }
          else {

            // Must not end on a colon.
            return;
          }

          if (++set > 7) return;

          count = 0;
        }
        else if (address.string[i] == f_string_ascii_slash_forward_s.string[0]) {
          if (flag & 0x4) return;

          flag |= 0x4;
        }
        else if (address.string[i] == f_string_ascii_bracket_close_s.string[0]) {
          if (!(flag & 0x2)) return;

          if (!where) {
            at.stop_1 = i - 1;
          }

          // Skip past NULL characters.
          for (at.start_2 = i + 1; at.start_2 < address.used && !address.string[at.start_2]; ++at.start_2) {

            if (state->interrupt) {
              state->interrupt((void *) state, 0);
              if (F_status_set_fine(state->status) == F_interrupt) return;

              // Restore status in case the interrupt callback changed it.
              state->status = F_network_version_six_not;
            }
          } // for

          if (at.start_2 < address.used) {
            if (address.string[at.start_2] == f_string_ascii_colon_s.string[0]) {

              // Skip past NULL characters.
              while (++at.start_2 < address.used && !address.string[at.start_2]) {

                if (state->interrupt) {
                  state->interrupt((void *) state, 0);
                  if (F_status_set_fine(state->status) == F_interrupt) return;

                  // Restore status in case the interrupt callback changed it.
                  state->status = F_network_version_six_not;
                }
              } // while

              // The colon used to designate the port number must be followed by a (base-10) number.
              for (at.stop_2 = at.start_2; at.stop_2 < address.used; ++at.stop_2) {

                if (state->interrupt) {
                  state->interrupt((void *) state, 0);
                  if (F_status_set_fine(state->status) == F_interrupt) return;

                  // Restore status in case the interrupt callback changed it.
                  state->status = F_network_version_six_not;
                }

                if (!address.string[at.stop_2]) continue;
                if (!isdigit(address.string[at.stop_2])) return;
              } // for

              // The double colon either must exist when set is smaller than 7 or the double colon must not exist at all.
              if (set < 7 && !(flag & 0x8) || set == 7 && (flag & 0x8)) return;

              state->status = F_network_version_six;
            }
            else {

              // Only a colon (and port number) may follow a valid close bracket.
              return;
            }
          }
          else if (count || set) {

            // The double colon either must exist when set is smaller than 7 or the double colon must not exist at all.
            if (set < 7 && !(flag & 0x8) || set == 7 && (flag & 0x8)) return;

            state->status = F_network_version_six;

            at.start_2 = 1;
            at.stop_2 = 0;

            if (where) {
              *where = at;
            }
          }

          return;
        }
        else {
          return;
        }
      } // for

      // The double colon either must exist when set is smaller than 7 or the double colon must not exist at all.
      if (set < 7 && !(flag & 0x8) || set == 7 && (flag & 0x8)) return;

      // A close bracket must exist if there is an open bracket.
      if (flag & 0x2) return;

      if (!(flag & 0x10) || set || count) {
        state->status = F_network_version_six;

        at.start_2 = 1;
        at.stop_2 = 0;

        if (where) {
          *where = at;
        }
      }

      return;
    }

    // IPv4 flag additions: 0x2 == has port number (and all 4 proper sets), 0x4 == has forward slash, 0x8 = finished forward slash.
    state->status = F_network_version_four_not;

    if (count > 3) return;

    for (; i < address.used; ++i) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) return;

        // Restore status in case the interrupt callback changed it.
        state->status = F_network_version_four_not;
      }

      if (!address.string[i]) continue;

      if (isdigit(address.string[i])) {
        if (flag & 0x4) {
          if (!(flag & 0x8) && ++count > 3) return;

          if (flag & 0x2) {
            at.stop_2 = i;
          }
        }
        else if (flag & 0x2) {
          at.stop_2 = i;
        }
        else {
          if (++count > 3) return;
        }
      }
      else if (address.string[i] == f_string_ascii_period_s.string[0]) {
        if ((flag & 0x6) || !count || ++set > 3) return;

        count = 0;
      }
      else if (address.string[i] == f_string_ascii_colon_s.string[0]) {
        if (set != 3 || (flag & 0x2)) return;

        if (flag & 0x4) {
          flag |= 0x8;
        }

        for (; i < address.used && !address.string[i]; ++i) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) return;

            // Restore status in case the interrupt callback changed it.
            state->status = F_network_version_four_not;
          }
        } // for

        if (i == address.used) return;

        flag |= 0x2;
        at.start_2 = i + 1; // Save the position that might represent the start of the port number.
      }
      else if (address.string[i] == f_string_ascii_slash_forward_s.string[0]) {
        if ((flag & 0x4) || set != 3) return;

        flag |= 0x4;
        count = 0;
      }
      else {
        return;
      }
    } // for

    if (set == 3) {
      if (where) {
        *where = at;
      }

      state->status = F_network_version_four;
    }
    else {
      state->status = F_network_version_four_not;
    }
  }
#endif // _di_f_network_is_ip_address_

#ifndef _di_f_network_to_host_long_
  f_status_t f_network_to_host_long(const uint32_t from, uint32_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = ntohl(from);

    return F_okay;
  }
#endif // _di_f_network_to_host_long_

#ifndef _di_f_network_to_host_short_
  f_status_t f_network_to_host_short(const uint16_t from, uint16_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *to = ntohs(from);

    return F_okay;
  }
#endif // _di_f_network_to_host_short_

#ifndef _di_f_network_to_ip_string_
  f_status_t f_network_to_ip_string(const f_network_family_ip_t from, f_string_dynamic_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!(from.type == f_network_family_ip_4_e || from.type == f_network_family_ip_6_e)) return F_data_not;

    {
      const f_status_t status = f_memory_array_increase_by((from.type == f_network_family_ip_4_e ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN) + 1, sizeof(f_char_t), (void **) &to->string, &to->used, &to->size);
      if (F_status_is_error(status)) return status;
    }

    {
      const char * const result = (from.type == f_network_family_ip_4_e)
        ? inet_ntop(AF_INET, (void *) & from.address.v4, to->string + to->used, INET_ADDRSTRLEN)
        : inet_ntop(AF_INET6, (void *) & from.address.v6, to->string + to->used, INET6_ADDRSTRLEN);

      if (!result) {
        if (errno == EAFNOSUPPORT) return F_status_set_error(F_support_not);
        if (errno == ENOSPC) return F_status_set_error(F_space_not);

        return F_status_set_error(F_failure);
      }
    }

    while (to->used < to->size && to->string[to->used]) {
      ++to->used;
    } // while

    // The string should be NULL terminated, but in case it is not, ensure one always exists.
    to->string[to->used] = 0;

    return F_okay;
  }
#endif // _di_f_network_to_ip_string_

#ifdef __cplusplus
} // extern "C"
#endif
