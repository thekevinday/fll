#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_simple_packet_decode_
  f_status_t f_fss_simple_packet_decode(const f_string_static_t buffer, f_fss_simple_packet_t * const packet) {
    #ifndef _di_level_0_parameter_checking_
      if (!packet) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (buffer.used < F_fss_simple_packet_block_header_size_d) return F_packet_too_small;

    packet->control = (uint8_t) buffer.string[0];

    #ifdef _is_F_endian_little
      // Big Endian.
      if (packet->control & F_fss_simple_packet_endian_d) {
        packet->size = (uint32_t) ((uint8_t) buffer.string[1]);
        packet->size += ((uint32_t) ((uint8_t) buffer.string[2])) << 8;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[3])) << 16;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[4])) << 24;
      }
      // Little Endian.
      else {
        packet->size = ((uint32_t) ((uint8_t) buffer.string[1])) << 24;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[2])) << 16;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[3])) << 8;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[4]));
      }
    #else
      // Big Endian.
      if (packet->control & F_fss_simple_packet_endian_d) {
        packet->size = ((uint32_t) ((uint8_t) buffer.string[1])) << 24;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[2])) << 16;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[3])) << 8;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[4]));
      }
      // Little Endian.
      else {
        packet->size = ((uint32_t) ((uint8_t) buffer.string[1]));
        packet->size += ((uint32_t) ((uint8_t) buffer.string[2])) << 8;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[3])) << 16;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[4])) << 24;
      }
    #endif // _is_F_endian_little

    return F_okay;
  }
#endif // _di_f_fss_simple_packet_decode_

#ifndef _di_f_fss_simple_packet_decode_range_
  f_status_t f_fss_simple_packet_decode_range(const f_string_static_t buffer, f_fss_simple_packet_range_t * const packet) {
    #ifndef _di_f_fss_simple_packet_decode_range_
      if (!packet) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (buffer.used < F_fss_simple_packet_block_header_size_d) return F_packet_too_small;

    packet->control = (uint8_t) buffer.string[0];

    #ifdef _is_F_endian_little
      // Big Endian.
      if (packet->control & F_fss_simple_packet_endian_d) {
        packet->size = ((uint32_t) ((uint8_t) buffer.string[1]));
        packet->size += ((uint32_t) ((uint8_t) buffer.string[2])) << 8;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[3])) << 16;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[4])) << 24;
      }
      // Little Endian.
      else {
        packet->size = ((uint32_t) ((uint8_t) buffer.string[1])) << 24;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[2])) << 16;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[3])) << 8;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[4]));
      }
    #else
      // Big Endian.
      if (packet->control & F_fss_simple_packet_endian_d) {
        packet->size = ((uint32_t) ((uint8_t) buffer.string[1])) << 24;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[2])) << 16;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[3])) << 8;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[4]));
      }
      // Little Endian.
      else {
        packet->size = ((uint32_t) ((uint8_t) buffer.string[1]));
        packet->size += ((uint32_t) ((uint8_t) buffer.string[2])) << 8;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[3])) << 16;
        packet->size += ((uint32_t) ((uint8_t) buffer.string[4])) << 24;
      }
    #endif // _is_F_endian_little

    packet->payload.start = F_fss_simple_packet_block_header_size_d;
    packet->payload.stop = (buffer.used - F_fss_simple_packet_block_header_size_d < F_fss_simple_packet_block_payload_size_d) ? buffer.used - 1 : F_fss_simple_packet_block_payload_size_d - 1;

    return F_okay;
  }
#endif // _di_f_fss_simple_packet_decode_range_

#ifndef _di_f_fss_simple_packet_delete_
  f_status_t f_fss_simple_packet_delete(f_fss_simple_packet_t * const simple_packet) {
    #ifndef _di_level_0_parameter_checking_
      if (!simple_packet) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (simple_packet->payload.size && simple_packet->payload.string) {
      const f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &simple_packet->payload.string, &simple_packet->payload.used, &simple_packet->payload.size);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_fss_simple_packet_delete_

#ifndef _di_f_fss_simple_packet_destroy_
  f_status_t f_fss_simple_packet_destroy(f_fss_simple_packet_t * const simple_packet) {
    #ifndef _di_level_0_parameter_checking_
      if (!simple_packet) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (simple_packet->payload.size && simple_packet->payload.string) {
      const f_status_t status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &simple_packet->payload.string, &simple_packet->payload.used, &simple_packet->payload.size);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_fss_simple_packet_destroy_

#ifndef _di_f_fss_simple_packet_encode_
  f_status_t f_fss_simple_packet_encode(const uint8_t control, const uint32_t size, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_memory_array_increase_by(F_fss_simple_packet_block_header_size_d, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->string[destination->used++] = (uint8_t) control;

    #ifdef _is_F_endian_little
      // Big Endian.
      if (control & F_fss_simple_packet_endian_d) {
        destination->string[destination->used++] = (uint8_t) (size & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 8) & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 16) & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 24) & 0xff);
      }
      // Little Endian.
      else {
        destination->string[destination->used++] = (uint8_t) ((size >> 24) & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 16) & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 8) & 0xff);
        destination->string[destination->used++] = (uint8_t) (size & 0xff);
      }
    #else
      // Big Endian.
      if (control & F_fss_simple_packet_endian_d) {
        destination->string[destination->used++] = (uint8_t) ((size >> 24) & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 16) & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 8) & 0xff);
        destination->string[destination->used++] = (uint8_t) (size & 0xff);
      }
      // Little Endian.
      else {
        destination->string[destination->used++] = (uint8_t) (size & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 8) & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 16) & 0xff);
        destination->string[destination->used++] = (uint8_t) ((size >> 24) & 0xff);
      }
    #endif // _is_F_endian_little

    return F_okay;
  }
#endif // _di_f_fss_simple_packet_encode_

#ifndef _di_f_fss_simple_packets_delete_callback_
  f_status_t f_fss_simple_packets_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_simple_packet_t * const array = (f_fss_simple_packet_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].payload.size && array[i].payload.string) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].payload.string, &array[i].payload.used, &array[i].payload.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_simple_packets_delete_callback_

#ifndef _di_f_fss_simple_packets_destroy_callback_
  f_status_t f_fss_simple_packets_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_simple_packet_t * const array = (f_fss_simple_packet_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].payload.size && array[i].payload.string) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].payload.string, &array[i].payload.used, &array[i].payload.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_simple_packets_destroy_callback_

#ifndef _di_f_fss_simple_packetss_delete_callback_
  f_status_t f_fss_simple_packetss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_simple_packets_t * const array = (f_fss_simple_packets_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          if (array[i].array[j].payload.size && array[i].array[j].payload.string) {
            status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].payload.string, &array[i].array[j].payload.used, &array[i].array[j].payload.size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].array) {
          status = f_memory_array_resize(0, sizeof(f_fss_simple_packet_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_simple_packetss_delete_callback_

#ifndef _di_f_fss_simple_packetss_destroy_callback_
  f_status_t f_fss_simple_packetss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_simple_packets_t * const array = (f_fss_simple_packets_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          if (array[i].array[j].payload.size && array[i].array[j].payload.string) {
            status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].payload.string, &array[i].array[j].payload.used, &array[i].array[j].payload.size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].array) {
          status = f_memory_array_adjust(0, sizeof(f_fss_simple_packet_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_simple_packetss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
