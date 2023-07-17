#include "../fss.h"
#include "private-simple_packet.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_simple_packet_identify_
  f_status_t f_fss_simple_packet_identify(const f_string_static_t buffer, f_fss_simple_packet_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;

    range->control.start = 1;
    range->control.stop = 0;

    range->size.start = 1;
    range->size.stop = 0;

    range->payload.start = 1;
    range->payload.stop = 0;

    if (buffer.used < F_fss_simple_packet_block_control_size_d) return F_partial;

    range->control.start = 0;
    range->control.stop = 0;

    if (buffer.used < F_fss_simple_packet_block_header_size_d) return F_partial;

    range->size.start = 1;
    range->size.stop = F_fss_simple_packet_block_size_size_d;

    // The Payload Block can be NULL and if it is, then all values of the Size Block must be of size F_fss_simple_packet_block_header_size_d.
    if (buffer.used == F_fss_simple_packet_block_size_size_d) {

      // Big endian.
      if (buffer.string[0] & F_fss_simple_packet_endian_d) {
        if (buffer.string[2] || buffer.string[3] || !buffer.string[4]) return F_partial;
        if (buffer.string[1] < F_fss_simple_packet_block_header_size_d) return F_status_set_error(F_valid_not);

        return (buffer.string[1] == F_fss_simple_packet_block_header_size_d) ? F_none : F_partial;
      }

      // Little endian.
      if (!buffer.string[1] || buffer.string[2] || buffer.string[3]) return F_partial;
      if (buffer.string[4] < F_fss_simple_packet_block_header_size_d) return F_status_set_error(F_valid_not);

      return (buffer.string[4] == F_fss_simple_packet_block_header_size_d) ? F_none : F_partial;
    }

    range->payload.start = F_fss_simple_packet_block_header_size_d;
    range->payload.stop = (buffer.used - F_fss_simple_packet_block_header_size_d < F_fss_simple_packet_block_payload_size_d) ? buffer.used - 1 : F_fss_simple_packet_block_payload_size_d - 1;

    return F_none;
  }
#endif // _di_f_fss_simple_packet_identify_

#ifndef _di_f_fss_simple_packet_ranges_adjust_
  f_status_t f_fss_simple_packet_ranges_adjust(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t * const simple_packet_ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!simple_packet_ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packet_ranges_adjust(length, simple_packet_ranges);
  }
#endif // _di_f_fss_simple_packet_ranges_adjust_

#ifndef _di_f_fss_simple_packet_ranges_decimate_by_
  f_status_t f_fss_simple_packet_ranges_decimate_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t * const simple_packet_ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!simple_packet_ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (simple_packet_ranges->size > amount) return private_f_fss_simple_packet_ranges_adjust(simple_packet_ranges->size - amount, simple_packet_ranges);

    return private_f_fss_simple_packet_ranges_adjust(0, simple_packet_ranges);
  }
#endif // _di_f_fss_simple_packet_ranges_decimate_by_

#ifndef _di_f_fss_simple_packet_ranges_decrease_by_
  f_status_t f_fss_simple_packet_ranges_decrease_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t * const simple_packet_ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!simple_packet_ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (simple_packet_ranges->size > amount) return private_f_fss_simple_packet_ranges_resize(simple_packet_ranges->size - amount, simple_packet_ranges);

    return private_f_fss_simple_packet_ranges_resize(0, simple_packet_ranges);
  }
#endif // _di_f_fss_simple_packet_ranges_decrease_by_

#ifndef _di_f_fss_simple_packet_ranges_increase_
  f_status_t f_fss_simple_packet_ranges_increase(const f_number_unsigned_t step, f_fss_simple_packet_ranges_t * const simple_packet_ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!simple_packet_ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && simple_packet_ranges->used + 1 > simple_packet_ranges->size) {
      f_number_unsigned_t size = simple_packet_ranges->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (simple_packet_ranges->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        size = F_number_t_size_unsigned_d;
      }

      return private_f_fss_simple_packet_ranges_resize(size, simple_packet_ranges);
    }

    return F_data_not;
  }
#endif // _di_f_fss_simple_packet_ranges_increase_

#ifndef _di_f_fss_simple_packet_ranges_increase_by_
  f_status_t f_fss_simple_packet_ranges_increase_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t * const simple_packet_ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!simple_packet_ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (simple_packet_ranges->used + amount > simple_packet_ranges->size) {
      if (simple_packet_ranges->used + amount > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      return private_f_fss_simple_packet_ranges_resize(simple_packet_ranges->used + amount, simple_packet_ranges);
    }

    return F_data_not;
  }
#endif // _di_f_fss_simple_packet_ranges_increase_by_

#ifndef _di_f_fss_simple_packet_ranges_resize_
  f_status_t f_fss_simple_packet_ranges_resize(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t * const simple_packet_ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!simple_packet_ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packet_ranges_resize(length, simple_packet_ranges);
  }
#endif // _di_f_fss_simple_packet_ranges_resize_

#ifdef __cplusplus
} // extern "C"
#endif
