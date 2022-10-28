#include "utf.h"
#include "private-utf.h"
#include "private-utf_unassigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_buffer_decrement_
  f_status_t f_utf_buffer_decrement(const f_string_static_t buffer, f_string_range_t *range, const f_array_length_t step) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (step < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t i = 0;
    uint8_t width = 0;

    do {
      width = macro_f_utf_byte_width(buffer.string[range->start - 1]);

      if (width > range->start) {
        if (width > 1 && width > range->start + 1) {
          return F_status_set_error(F_complete_not_utf_eos);
        }

        return F_none_eos;
      }

      ++i;
      range->start -= width;

    } while (i < step);

    return F_none;
  }
#endif // _di_f_utf_buffer_decrement_

#ifndef _di_f_utf_buffer_increment_
  f_status_t f_utf_buffer_increment(const f_string_static_t buffer, f_string_range_t *range, const f_array_length_t step) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (step < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used || range->start > range->stop || range->start >= buffer.used) {
      return F_data_not;
    }

    f_array_length_t i = 0;
    uint8_t width = 0;

    do {
      width = macro_f_utf_byte_width(buffer.string[range->start]);

      if (range->start + width > range->stop) {
        if (width > 1 && range->start + width > range->stop + 1) {
          return F_status_set_error(F_complete_not_utf_stop);
        }

        range->start += width;

        return F_none_stop;
      }
      else if (range->start + width >= buffer.used) {
        if (width > 1 && range->start + width >= buffer.used + 1) {
          return F_status_set_error(F_complete_not_utf_eos);
        }

        range->start += width;

        return F_none_eos;
      }

      ++i;
      range->start += width;

    } while (i < step);

    return F_none;
  }
#endif // _di_f_utf_buffer_increment_

#ifdef __cplusplus
} // extern "C"
#endif
