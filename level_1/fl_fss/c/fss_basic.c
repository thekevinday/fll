#include "fss_basic.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_object_read_
  f_return_status fl_fss_basic_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_quote_t *quote) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!buffer->used ) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;
    f_string_lengths_t delimits = f_string_lengths_t_initialize;

    status = private_fl_fss_basic_read(F_true, buffer, range, found, quote, &delimits);

    if (F_status_is_error(status)) {
      f_macro_string_lengths_t_delete_simple(delimits);
      return status;
    }

    if (status == FL_fss_found_object_not || status == F_data_not || status == F_data_not_eos || status == F_data_not_stop) {
      f_macro_string_lengths_t_delete_simple(delimits);
      return status;
    }

    fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

    return status;
  }
#endif // _di_fl_fss_basic_object_read_

#ifndef _di_fl_fss_basic_content_read_
  f_return_status fl_fss_basic_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_content_t *found) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!buffer->used ) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths_t delimits = f_string_lengths_t_initialize;

    status = f_fss_skip_past_space(*buffer, range);
    if (F_status_is_error(status)) return status;

    // return found nothing if this line only contains whitespace and delimit placeholders.
    if (status == F_none_eol) {
      range->start++;
      return FL_fss_found_content_not;
    }
    else if (status == F_none_eos) {
      return F_data_not_eos;
    }
    else if (status == F_none_stop) {
      return F_data_not_stop;
    }

    fl_macro_fss_allocate_content_if_necessary((*found), delimits);
    found->array[found->used].start = range->start;

    // search for valid content.
    for (;; range->start++) {

      fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));
      fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

      if (buffer->string[range->start] == f_fss_basic_close) break;
    } // for

    // Save the stop length/
    found->array[found->used].stop = range->start - 1;
    found->used++;

    status = f_utf_buffer_increment(*buffer, range, 1);
    if (F_status_is_error(status)) return status;

    return FL_fss_found_content;
  }
#endif // _di_fl_fss_basic_content_read_

#ifndef _di_fl_fss_basic_object_write_
  f_return_status fl_fss_basic_object_write(const f_string_static_t object, const f_fss_quote_t quote, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = private_fl_fss_basic_write(F_true, object, quote ? quote : f_fss_delimit_quote_double, range, destination);

    if (status == F_data_not_stop || status == F_data_not_eos) {

      // Objects cannot be empty, so write a quoted empty string.
      const f_status_t status_allocation = private_fl_fss_destination_increase_by(2, destination);
      if (F_status_is_error(status_allocation)) return status_allocation;

      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double;
      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double;
    }

    if (complete == f_fss_complete_partial || complete == f_fss_complete_full) {
      if (status == F_none_stop || status == F_none_eos || status == F_data_not_stop || status == F_data_not_eos) {
        const f_status_t status_allocation = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_basic_open;
      }
    }

    return status;
  }
#endif // _di_fl_fss_basic_object_write_

#ifndef _di_fl_fss_basic_content_write_
  f_return_status fl_fss_basic_content_write(const f_string_static_t content, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    fl_macro_fss_skip_past_delimit_placeholders(content, (*range));

    if (range->start > range->stop || range->start >= content.used) {

      // content should be terminated, even if empty.
      if (complete == f_fss_complete_full || complete == f_fss_complete_end) {
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

    const f_string_length_t used_start = destination->used;

    for (; range->start <= range->stop && range->start < content.used; range->start++) {

      if (content.string[range->start] == f_fss_eol) {
        destination->used = used_start;
        return F_status_set_error(F_none_eol);
      }

      if (content.string[range->start] == f_fss_delimit_placeholder) {
        continue;
      }

      destination->string[destination->used++] = content.string[range->start];
    } // while

    if (complete == f_fss_complete_full || complete == f_fss_complete_end) {
      destination->string[destination->used++] = f_fss_basic_close;
    }

    if (range->start > range->stop) {
      return F_none_stop;
    }

    return F_none_eos;
  }
#endif // _di_fl_fss_basic_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
