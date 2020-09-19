#include "fss_basic.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_object_read_
  f_return_status fl_fss_basic_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_quoted_t *quoted) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;
    f_string_lengths_t delimits = f_string_lengths_t_initialize;

    status = private_fl_fss_basic_object_read(buffer, range, found, quoted, &delimits);
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
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
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
    for (;;) {
      fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));
      fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

      if (buffer->string[range->start] == f_fss_basic_close) break;

      range->start++;
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
  f_return_status fl_fss_basic_object_write(const f_string_static_t object, const f_fss_quoted_t quoted, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_fss_basic_object_write(object, quoted, range, destination);
  }
#endif // _di_fl_fss_basic_object_write_

#ifndef _di_fl_fss_basic_content_write_
  f_return_status fl_fss_basic_content_write(const f_string_static_t content, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    fl_macro_fss_skip_past_delimit_placeholders(content, (*range));

    if (range->start > range->stop) return F_data_not_stop;
    else if (range->start >= content.used) return F_data_not_eos;

    f_string_range_t input_position = f_string_range_t_initialize;
    f_string_range_t buffer_position = f_string_range_t_initialize;

    // ensure that there is room for the terminating newline.
    f_string_length_t size_allocate = destination->used + content.used + 1 + f_fss_default_allocation_step_string;

    buffer_position.start = destination->used;
    buffer_position.stop = destination->used;

    if (size_allocate > destination->size) {
      f_macro_string_dynamic_t_resize(status, (*destination), size_allocate);
      if (F_status_is_error(status)) return status;
    }

    while (range->start <= range->stop && range->start < content.used) {
      if (content.string[range->start] == f_string_eol[0]) {
        destination->string[buffer_position.stop] = f_string_eol[0];
        destination->used = buffer_position.stop + 1;
        return F_none_eos;
      }

      if (content.string[range->start] != f_fss_delimit_placeholder) {
        destination->string[buffer_position.stop] = content.string[range->start];
        buffer_position.stop++;
      }

      status = f_utf_buffer_increment(content, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    destination->string[buffer_position.stop] = f_string_eol[0];
    destination->used = buffer_position.stop + 1;

    if (range->start > range->stop) return F_none_stop;
    else if (range->start >= content.used) return F_none_eos;

    return F_none;
  }
#endif // _di_fl_fss_basic_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
