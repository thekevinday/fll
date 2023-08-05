#include "../fss.h"
#include "private-simple_packet.h"

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

#ifndef _di_f_fss_simple_packet_ranges_adjust_
  f_status_t f_fss_simple_packet_ranges_adjust(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_fss_simple_packet_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
  }
#endif // _di_f_fss_simple_packet_ranges_adjust_

#ifndef _di_f_fss_simple_packet_ranges_append_
  f_status_t f_fss_simple_packet_ranges_append(const f_fss_simple_packet_range_t source, f_fss_simple_packet_ranges_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packet_ranges_append(source, destination);
  }
#endif // _di_f_fss_simple_packet_ranges_append_

#ifndef _di_f_fss_simple_packet_ranges_append_all_
  f_status_t f_fss_simple_packet_ranges_append_all(const f_fss_simple_packet_ranges_t source, f_fss_simple_packet_ranges_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_fss_simple_packet_ranges_append_all(source, destination);
  }
#endif // _di_f_fss_simple_packet_ranges_append_all_

#ifndef _di_f_fss_simple_packet_ranges_decimate_by_
  f_status_t f_fss_simple_packet_ranges_decimate_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_fss_simple_packet_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
  }
#endif // _di_f_fss_simple_packet_ranges_decimate_by_

#ifndef _di_f_fss_simple_packet_ranges_decrease_by_
  f_status_t f_fss_simple_packet_ranges_decrease_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_fss_simple_packet_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
  }
#endif // _di_f_fss_simple_packet_ranges_decrease_by_

#ifndef _di_f_fss_simple_packet_ranges_increase_
  f_status_t f_fss_simple_packet_ranges_increase(const f_number_unsigned_t step, f_fss_simple_packet_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_fss_simple_packet_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
  }
#endif // _di_f_fss_simple_packet_ranges_increase_

#ifndef _di_f_fss_simple_packet_ranges_increase_by_
  f_status_t f_fss_simple_packet_ranges_increase_by(const f_number_unsigned_t amount, f_fss_simple_packet_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_fss_simple_packet_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
  }
#endif // _di_f_fss_simple_packet_ranges_increase_by_

#ifndef _di_f_fss_simple_packet_ranges_resize_
  f_status_t f_fss_simple_packet_ranges_resize(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t *ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_fss_simple_packet_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
  }
#endif // _di_f_fss_simple_packet_ranges_resize_

#ifndef _di_f_fss_simple_packet_rangess_adjust_
  f_status_t f_fss_simple_packet_rangess_adjust(const f_number_unsigned_t length, f_fss_simple_packet_rangess_t *rangess) {
    #ifndef _di_level_0_parameter_checking_
      if (!rangess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packet_rangess_adjust(length, rangess);
  }
#endif // _di_f_fss_simple_packet_rangess_adjust_

#ifndef _di_f_fss_simple_packet_rangess_append_
  f_status_t f_fss_simple_packet_rangess_append(const f_fss_simple_packet_ranges_t source, f_fss_simple_packet_rangess_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_fss_simple_packet_ranges_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_fss_simple_packet_ranges_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_fss_simple_packet_rangess_append_

#ifndef _di_f_fss_simple_packet_rangess_append_all_
  f_status_t f_fss_simple_packet_rangess_append_all(const f_fss_simple_packet_rangess_t source, f_fss_simple_packet_rangess_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_fss_simple_packet_ranges_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_fss_simple_packet_ranges_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_fss_simple_packet_rangess_append_all_

#ifndef _di_f_fss_simple_packet_rangess_decimate_by_
  f_status_t f_fss_simple_packet_rangess_decimate_by(const f_number_unsigned_t amount, f_fss_simple_packet_rangess_t *rangess) {
    #ifndef _di_level_0_parameter_checking_
      if (!rangess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_simple_packet_rangess_adjust((rangess->size > amount) ? rangess->size - amount : 0, rangess);
  }
#endif // _di_f_fss_simple_packet_rangess_decimate_by_

#ifndef _di_f_fss_simple_packet_rangess_decrease_by_
  f_status_t f_fss_simple_packet_rangess_decrease_by(const f_number_unsigned_t amount, f_fss_simple_packet_rangess_t *rangess) {
    #ifndef _di_level_0_parameter_checking_
      if (!rangess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_simple_packet_rangess_resize((rangess->size > amount) ? rangess->size - amount : 0, rangess);
  }
#endif // _di_f_fss_simple_packet_rangess_decrease_by_

#ifndef _di_f_fss_simple_packet_rangess_increase_
  f_status_t f_fss_simple_packet_rangess_increase(const f_number_unsigned_t step, f_fss_simple_packet_rangess_t *rangess) {
    #ifndef _di_level_0_parameter_checking_
      if (!rangess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_fss_simple_packet_ranges_t), (void **) &rangess->array, &rangess->used, &rangess->size);
  }
#endif // _di_f_fss_simple_packet_rangess_increase_

#ifndef _di_f_fss_simple_packet_rangess_increase_by_
  f_status_t f_fss_simple_packet_rangess_increase_by(const f_number_unsigned_t amount, f_fss_simple_packet_rangess_t *rangess) {
    #ifndef _di_level_0_parameter_checking_
      if (!rangess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_fss_simple_packet_ranges_t), (void **) &rangess->array, &rangess->used, &rangess->size);
  }
#endif // _di_f_fss_simple_packet_rangess_increase_by_

#ifndef _di_f_fss_simple_packet_rangess_resize_
  f_status_t f_fss_simple_packet_rangess_resize(const f_number_unsigned_t length, f_fss_simple_packet_rangess_t *rangess) {
    #ifndef _di_level_0_parameter_checking_
      if (!rangess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packet_rangess_resize(length, rangess);
  }
#endif // _di_f_fss_simple_packet_rangess_resize_

#ifndef _di_f_fss_simple_packets_adjust_
  f_status_t f_fss_simple_packets_adjust(const f_number_unsigned_t length, f_fss_simple_packets_t *packets) {
    #ifndef _di_level_0_parameter_checking_
      if (!packets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packets_adjust(length, packets);
  }
#endif // _di_f_fss_simple_packets_adjust_

#ifndef _di_f_fss_simple_packets_append_
  f_status_t f_fss_simple_packets_append(const f_fss_simple_packet_t source, f_fss_simple_packets_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packets_append(source, destination);
  }
#endif // _di_f_fss_simple_packets_append_

#ifndef _di_f_fss_simple_packets_append_all_
  f_status_t f_fss_simple_packets_append_all(const f_fss_simple_packets_t source, f_fss_simple_packets_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_fss_simple_packets_append_all(source, destination);
  }
#endif // _di_f_fss_simple_packets_append_all_

#ifndef _di_f_fss_simple_packets_decimate_by_
  f_status_t f_fss_simple_packets_decimate_by(const f_number_unsigned_t amount, f_fss_simple_packets_t *packets) {
    #ifndef _di_level_0_parameter_checking_
      if (!packets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_fss_simple_packet_t), (void **) &packets->array, &packets->used, &packets->size);
  }
#endif // _di_f_fss_simple_packets_decimate_by_

#ifndef _di_f_fss_simple_packets_decrease_by_
  f_status_t f_fss_simple_packets_decrease_by(const f_number_unsigned_t amount, f_fss_simple_packets_t *packets) {
    #ifndef _di_level_0_parameter_checking_
      if (!packets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_fss_simple_packet_t), (void **) &packets->array, &packets->used, &packets->size);
  }
#endif // _di_f_fss_simple_packets_decrease_by_

#ifndef _di_f_fss_simple_packets_increase_
  f_status_t f_fss_simple_packets_increase(const f_number_unsigned_t step, f_fss_simple_packets_t *packets) {
    #ifndef _di_level_0_parameter_checking_
      if (!packets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_fss_simple_packet_t), (void **) &packets->array, &packets->used, &packets->size);
  }
#endif // _di_f_fss_simple_packets_increase_

#ifndef _di_f_fss_simple_packets_increase_by_
  f_status_t f_fss_simple_packets_increase_by(const f_number_unsigned_t amount, f_fss_simple_packets_t *packets) {
    #ifndef _di_level_0_parameter_checking_
      if (!packets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_fss_simple_packet_t), (void **) &packets->array, &packets->used, &packets->size);
  }
#endif // _di_f_fss_simple_packets_increase_by_

#ifndef _di_f_fss_simple_packets_resize_
  f_status_t f_fss_simple_packets_resize(const f_number_unsigned_t length, f_fss_simple_packets_t *packets) {
    #ifndef _di_level_0_parameter_checking_
      if (!packets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packets_resize(length, packets);
  }
#endif // _di_f_fss_simple_packets_resize_

#ifndef _di_f_fss_simple_packetss_adjust_
  f_status_t f_fss_simple_packetss_adjust(const f_number_unsigned_t length, f_fss_simple_packetss_t *packetss) {
    #ifndef _di_level_0_parameter_checking_
      if (!packetss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packetss_adjust(length, packetss);
  }
#endif // _di_f_fss_simple_packetss_adjust_

#ifndef _di_f_fss_simple_packetss_append_
  f_status_t f_fss_simple_packetss_append(const f_fss_simple_packets_t source, f_fss_simple_packetss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_fss_simple_packets_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_fss_simple_packets_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_fss_simple_packetss_append_

#ifndef _di_f_fss_simple_packetss_append_all_
  f_status_t f_fss_simple_packetss_append_all(const f_fss_simple_packetss_t source, f_fss_simple_packetss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_fss_simple_packets_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_fss_simple_packets_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_fss_simple_packetss_append_all_

#ifndef _di_f_fss_simple_packetss_decimate_by_
  f_status_t f_fss_simple_packetss_decimate_by(const f_number_unsigned_t amount, f_fss_simple_packetss_t *packetss) {
    #ifndef _di_level_0_parameter_checking_
      if (!packetss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_simple_packetss_adjust((packetss->size > amount) ? packetss->size - amount : 0, packetss);
  }
#endif // _di_f_fss_simple_packetss_decimate_by_

#ifndef _di_f_fss_simple_packetss_decrease_by_
  f_status_t f_fss_simple_packetss_decrease_by(const f_number_unsigned_t amount, f_fss_simple_packetss_t *packetss) {
    #ifndef _di_level_0_parameter_checking_
      if (!packetss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_simple_packetss_resize((packetss->size > amount) ? packetss->size - amount : 0, packetss);
  }
#endif // _di_f_fss_simple_packetss_decrease_by_

#ifndef _di_f_fss_simple_packetss_increase_
  f_status_t f_fss_simple_packetss_increase(const f_number_unsigned_t step, f_fss_simple_packetss_t *packetss) {
    #ifndef _di_level_0_parameter_checking_
      if (!packetss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_fss_simple_packets_t), (void **) &packetss->array, &packetss->used, &packetss->size);
  }
#endif // _di_f_fss_simple_packetss_increase_

#ifndef _di_f_fss_simple_packetss_increase_by_
  f_status_t f_fss_simple_packetss_increase_by(const f_number_unsigned_t amount, f_fss_simple_packetss_t *packetss) {
    #ifndef _di_level_0_parameter_checking_
      if (!packetss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_fss_simple_packets_t), (void **) &packetss->array, &packetss->used, &packetss->size);
  }
#endif // _di_f_fss_simple_packetss_increase_by_

#ifndef _di_f_fss_simple_packetss_resize_
  f_status_t f_fss_simple_packetss_resize(const f_number_unsigned_t length, f_fss_simple_packetss_t *packetss) {
    #ifndef _di_level_0_parameter_checking_
      if (!packetss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_simple_packetss_resize(length, packetss);
  }
#endif // _di_f_fss_simple_packetss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
