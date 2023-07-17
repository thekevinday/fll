#include "../fss.h"
#include "private-simple_packet.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_simple_packet_ranges_adjust_) || !defined(_di_f_fss_simple_packet_ranges_decimate_by_)
  f_status_t private_f_fss_simple_packet_ranges_adjust(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t * const simple_packet_ranges) {

    const f_status_t status = f_memory_adjust(simple_packet_ranges->size, length, sizeof(f_fss_simple_packet_range_t), (void **) & simple_packet_ranges->array);
    if (F_status_is_error(status)) return status;

    simple_packet_ranges->size = length;

    if (simple_packet_ranges->used > simple_packet_ranges->size) {
      simple_packet_ranges->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_simple_packet_ranges_adjust_) || !defined(_di_f_fss_simple_packet_ranges_decimate_by_)

#if !defined(_di_f_fss_simple_packet_ranges_decrease_by_) || !defined(_di_f_fss_simple_packet_ranges_increase_) || !defined(_di_f_fss_simple_packet_ranges_increase_by_) || !defined(_di_f_fss_simple_packet_ranges_resize_)
  f_status_t private_f_fss_simple_packet_ranges_resize(const f_number_unsigned_t length, f_fss_simple_packet_ranges_t * const simple_packet_ranges) {

    const f_status_t status = f_memory_resize(simple_packet_ranges->size, length, sizeof(f_fss_simple_packet_range_t), (void **) & simple_packet_ranges->array);
    if (F_status_is_error(status)) return status;

    simple_packet_ranges->size = length;

    if (simple_packet_ranges->used > simple_packet_ranges->size) {
      simple_packet_ranges->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_simple_packet_ranges_decrease_by_) || !defined(_di_f_fss_simple_packet_ranges_increase_) || !defined(_di_f_fss_simple_packet_ranges_increase_by_) || !defined(_di_f_fss_simple_packet_ranges_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
