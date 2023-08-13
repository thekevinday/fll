#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_simple_packet_delete_
  f_status_t f_fss_simple_packet_delete(f_fss_simple_packet_t * const packet) {
    #ifndef _di_level_0_parameter_checking_
      if (!packet) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_string_dynamic_resize(0, &packet->payload);
  }
#endif // _di_f_fss_simple_packet_delete_

#ifndef _di_f_fss_simple_packet_destroy_
  f_status_t f_fss_simple_packet_destroy(f_fss_simple_packet_t * const packet) {
    #ifndef _di_level_0_parameter_checking_
      if (!packet) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    packet->control = 0;
    packet->size = 0;

    return f_string_dynamic_adjust(0, &packet->payload);
  }
#endif // _di_f_fss_simple_packet_destroy_

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

#ifndef _di_f_fss_simple_packets_delete_callback_
  f_status_t f_fss_simple_packets_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_simple_packet_t * const array = (f_fss_simple_packet_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_dynamic_resize(0, &array[i].payload);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_simple_packets_delete_callback_

#ifndef _di_f_fss_simple_packets_destroy_callback_
  f_status_t f_fss_simple_packets_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_simple_packet_t * const array = (f_fss_simple_packet_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        array[i].control = 0;
        array[i].size = 0;

        status = f_string_dynamic_adjust(0, &array[i].payload);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_simple_packets_destroy_callback_

#ifndef _di_f_fss_simple_packetss_delete_callback_
  f_status_t f_fss_simple_packetss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_simple_packets_t * const array = (f_fss_simple_packets_t *) void_array;
      f_status_t status = F_none;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_dynamic_resize(0, &array[i].array[j].payload);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_fss_simple_packet_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_simple_packetss_delete_callback_

#ifndef _di_f_fss_simple_packetss_destroy_callback_
  f_status_t f_fss_simple_packetss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_simple_packets_t * const array = (f_fss_simple_packets_t *) void_array;
      f_status_t status = F_none;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          array[i].array[j].control = 0;
          array[i].array[j].size = 0;

          status = f_string_dynamic_adjust(0, &array[i].array[j].payload);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_fss_simple_packet_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_simple_packetss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
