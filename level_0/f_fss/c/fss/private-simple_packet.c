#include "../fss.h"
#include "private-simple_packet.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_simple_packet_ranges_append_) || !defined(_di_f_fss_simple_packet_rangess_append_)
  extern f_status_t private_f_fss_simple_packet_ranges_append(const f_fss_simple_packet_range_t source, f_fss_simple_packet_ranges_t *destination) {

    const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_fss_simple_packet_range_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    destination->array[destination->used++] = source;

    return F_okay;
  }
#endif // !defined(_di_f_fss_simple_packet_ranges_append_) || !defined(_di_f_fss_simple_packet_rangess_append_)

#if !defined(_di_f_fss_simple_packet_ranges_append_) || !defined(_di_f_fss_simple_packet_ranges_append_all_) || !defined(_di_f_fss_simple_packet_rangess_append_all_)
  extern f_status_t private_f_fss_simple_packet_ranges_append_all(const f_fss_simple_packet_ranges_t source, f_fss_simple_packet_ranges_t *destination) {

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_fss_simple_packet_range_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_okay;
  }
#endif // !defined(_di_f_fss_simple_packet_ranges_append_) || !defined(_di_f_fss_simple_packet_ranges_append_all_) || !defined(_di_f_fss_simple_packet_rangess_append_all_)

#if !defined(_di_f_fss_simple_packet_rangess_adjust_) || !defined(_di_f_fss_simple_packet_rangess_decimate_by_)
  f_status_t private_f_fss_simple_packet_rangess_adjust(const f_number_unsigned_t length, f_fss_simple_packet_rangess_t *rangess) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < rangess->size; ++i) {

        status = f_memory_array_adjust(0, sizeof(f_fss_simple_packet_range_t), (void **) &rangess->array[i].array, &rangess->array[i].used, &rangess->array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_fss_simple_packet_ranges_t), (void **) &rangess->array, &rangess->used, &rangess->size);
  }
#endif // !defined(_di_f_fss_simple_packet_rangess_adjust_) || !defined(_di_f_fss_simple_packet_rangess_decimate_by_)

#if !defined(_di_f_fss_simple_packet_rangess_decrease_by_) || !defined(_di_f_fss_simple_packet_rangess_resize_)
  f_status_t private_f_fss_simple_packet_rangess_resize(const f_number_unsigned_t length, f_fss_simple_packet_rangess_t *rangess) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < rangess->size; ++i) {

        status = f_memory_array_resize(0, sizeof(f_fss_simple_packet_range_t), (void **) &rangess->array[i].array, &rangess->array[i].used, &rangess->array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_fss_simple_packet_ranges_t), (void **) &rangess->array, &rangess->used, &rangess->size);
  }
#endif // !defined(_di_f_fss_simple_packet_rangess_decrease_by_) || !defined(_di_f_fss_simple_packet_rangess_resize_)

#if !defined(_di_f_fss_simple_packets_adjust_) || !defined(_di_f_fss_simple_packets_decimate_by_)
  f_status_t private_f_fss_simple_packets_adjust(const f_number_unsigned_t length, f_fss_simple_packets_t *packets) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < packets->size; ++i) {

        status = f_string_dynamic_adjust(0, &packets->array[i].payload);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_fss_simple_packet_t), (void **) &packets->array, &packets->used, &packets->size);
  }
#endif // !defined(_di_f_fss_simple_packets_adjust_) || !defined(_di_f_fss_simple_packets_decimate_by_)

#if !defined(_di_f_fss_simple_packets_append_) || !defined(_di_f_fss_simple_packetss_append_)
  extern f_status_t private_f_fss_simple_packets_append(const f_fss_simple_packet_t source, f_fss_simple_packets_t *destination) {

    const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_fss_simple_packet_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    destination->array[destination->used++] = source;

    return F_okay;
  }
#endif // !defined(_di_f_fss_simple_packets_append_) || !defined(_di_f_fss_simple_packetss_append_)

#if !defined(_di_f_fss_simple_packets_append_) || !defined(_di_f_fss_simple_packets_append_all_) || !defined(_di_f_fss_simple_packetss_append_all_)
  extern f_status_t private_f_fss_simple_packets_append_all(const f_fss_simple_packets_t source, f_fss_simple_packets_t *destination) {

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_fss_simple_packet_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_okay;
  }
#endif // !defined(_di_f_fss_simple_packets_append_) || !defined(_di_f_fss_simple_packets_append_all_) || !defined(_di_f_fss_simple_packetss_append_all_)

#if !defined(_di_f_fss_simple_packets_decrease_by_) || !defined(_di_f_fss_simple_packets_resize_)
  f_status_t private_f_fss_simple_packets_resize(const f_number_unsigned_t length, f_fss_simple_packets_t *packets) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < packets->size; ++i) {

        status = f_memory_array(0, sizeof(f_char_t), (void **) &packets->array[i].payload.string, &packets->array[i].payload.used, &packets->array[i].payload.size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_fss_simple_packet_t), (void **) &packets->array, &packets->used, &packets->size);
  }
#endif // !defined(_di_f_fss_simple_packets_decrease_by_) || !defined(_di_f_fss_simple_packets_resize_)

#if !defined(_di_f_fss_simple_packetss_adjust_) || !defined(_di_f_fss_simple_packetss_decimate_by_)
  f_status_t private_f_fss_simple_packetss_adjust(const f_number_unsigned_t length, f_fss_simple_packetss_t *packetss) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < packetss->size; ++i) {

        status = f_memory_array_adjust(0, sizeof(f_fss_simple_packet_t), (void **) &packetss->array[i].array, &packetss->array[i].used, &packetss->array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_fss_simple_packets_t), (void **) &packetss->array, &packetss->used, &packetss->size);
  }
#endif // !defined(_di_f_fss_simple_packetss_adjust_) || !defined(_di_f_fss_simple_packetss_decimate_by_)

#if !defined(_di_f_fss_simple_packetss_decrease_by_) || !defined(_di_f_fss_simple_packetss_resize_)
  f_status_t private_f_fss_simple_packetss_resize(const f_number_unsigned_t length, f_fss_simple_packetss_t *packetss) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < packetss->size; ++i) {

        status = f_memory_array_resize(0, sizeof(f_fss_simple_packet_t), (void **) &packetss->array[i].array, &packetss->array[i].used, &packetss->array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_fss_simple_packets_t), (void **) &packetss->array, &packetss->used, &packetss->size);
  }
#endif // !defined(_di_f_fss_simple_packetss_decrease_by_) || !defined(_di_f_fss_simple_packetss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
