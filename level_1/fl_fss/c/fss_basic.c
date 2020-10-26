#include "fss_basic.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_object_read_
  f_return_status fl_fss_basic_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_quote_t *quote, f_fss_delimits_t *delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    f_status_t status = private_fl_fss_basic_read(F_true, buffer, range, found, quote, delimits);

    if (F_status_is_error(status)) {
      delimits->used = delimits_used;
      return status;
    }

    return status;
  }
#endif // _di_fl_fss_basic_object_read_

#ifndef _di_fl_fss_basic_content_read_
  f_return_status fl_fss_basic_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_content_t *found, f_fss_delimits_t *delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_space(*buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eol) {
      range->start++;
      return FL_fss_found_content_not;
    }

    if (status == F_none_eos) {
      return F_data_not_eos;
    }

    if (status == F_none_stop) {
      return F_data_not_stop;
    }

    status = private_fl_fss_ranges_increase(found);
    if (F_status_is_error(status)) return status;

    found->array[found->used].start = range->start;

    for (;; range->start++) {

      status = f_fss_skip_past_delimit(*buffer, range);
      if (F_status_is_error(status)) return status;

      if (status == F_none_eos || status == F_none_stop) {
        return status;
      }

      if (buffer->string[range->start] == f_fss_basic_close) break;
    } // for

    found->array[found->used++].stop = range->start - 1;

    status = f_utf_buffer_increment(*buffer, range, 1);
    if (F_status_is_error(status)) return status;

    return FL_fss_found_content;
  }
#endif // _di_fl_fss_basic_content_read_

#ifndef _di_fl_fss_basic_object_write_string_
  f_return_status fl_fss_basic_object_write_string(const f_string_static_t object, const f_fss_quote_t quote, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_string_length_t destination_used = destination->used;

    f_status_t status = private_fl_fss_basic_write(F_true, object, quote ? quote : f_fss_delimit_quote_double, range, destination);

    if (status == F_data_not_stop || status == F_data_not_eos) {

      // Objects cannot be empty, so write a quoted empty string.
      const f_status_t status_allocation = private_fl_fss_destination_increase_by(2, destination);

      if (F_status_is_error(status_allocation)) {
        destination->used = destination_used;
        return status_allocation;
      }

      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double;
      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double;
    }

    if (complete == f_fss_complete_partial || complete == f_fss_complete_partial_trim || complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
      if (status == F_none_stop || status == F_none_eos || status == F_data_not_stop || status == F_data_not_eos) {
        f_status_t status2 = F_none;

        if (complete == f_fss_complete_full_trim) {
          status2 = private_fl_fss_basic_write_object_trim(quote ? quote : f_fss_delimit_quote_double, destination_used, destination);

          if (F_status_is_error(status2)) {
            destination->used = destination_used;
            return status2;
          }
        }

        status2 = private_fl_fss_destination_increase(destination);

        if (F_status_is_error(status2)) {
          destination->used = destination_used;
          return status2;
        }

        destination->string[destination->used++] = f_fss_basic_open;
      }
    }

    if (F_status_is_error(status)) {
      destination->used = destination_used;
    }

    return status;
  }
#endif // _di_fl_fss_basic_object_write_string_

#ifndef _di_fl_fss_basic_content_write_string_
  f_return_status fl_fss_basic_content_write_string(const f_string_static_t content, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    status = f_fss_skip_past_delimit(content, range);
    if (F_status_is_error(status)) return status;

    if (range->start > range->stop || range->start >= content.used) {

      // content should be terminated, even if empty.
      if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim || complete == f_fss_complete_end) {
        status = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status)) return status;

        destination->string[destination->used++] = f_fss_basic_close;
      }

      if (range->start > range->stop) {
        return F_data_not_stop;
      }

      return F_data_not_eos;
    }

    // ensure that there is room for the potential terminating newline.
    status = private_fl_fss_destination_increase_by(destination->used + (range->stop - range->start) + 1, destination);
    if (F_status_is_error(status)) return status;

    const f_string_length_t destination_used = destination->used;

    for (; range->start <= range->stop && range->start < content.used; range->start++) {

      if (content.string[range->start] == f_fss_eol) {
        destination->used = destination_used;
        return F_status_set_error(F_none_eol);
      }

      if (content.string[range->start] == f_fss_delimit_placeholder) {
        continue;
      }

      destination->string[destination->used++] = content.string[range->start];
    } // for

    if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim || complete == f_fss_complete_end) {
      destination->string[destination->used++] = f_fss_basic_close;
    }

    if (range->start > range->stop) {
      return F_none_stop;
    }

    return F_none_eos;
  }
#endif // _di_fl_fss_basic_content_write_string_

#ifdef __cplusplus
} // extern "C"
#endif
