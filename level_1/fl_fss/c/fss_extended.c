#include "fss_extended.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_object_read_
  f_return_status fl_fss_extended_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_quote_t *quoted) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!buffer->used) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
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
#endif // _di_fl_fss_extended_object_read_

#ifndef _di_fl_fss_extended_content_read_
  f_return_status fl_fss_extended_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_content_t *found, f_fss_quotes_t *quotes) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!buffer->used) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;
    f_status_t status_allocate = F_none;

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

    f_string_lengths_t delimits = f_string_lengths_t_initialize;

    uint8_t content_found = 0;

    while (range->start <= range->stop && range->start < buffer->used) {
      f_string_range_t content_partial = f_string_range_t_initialize;
      f_fss_quote_t quoted = 0;

      status = private_fl_fss_basic_object_read(buffer, range, &content_partial, &quoted, &delimits);

      if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {
        if (found->used == found->size) {
          if (found->used + f_fss_default_allocation_step > found->size) {
            if (found->used == f_array_length_t_size) {
              f_macro_string_lengths_t_delete_simple(delimits);
              return F_status_set_error(F_buffer_too_large);
            }
            else {
              f_macro_fss_content_t_resize(status_allocate, (*found), found->size + f_fss_default_allocation_step);
            }
          }
          else {
            f_macro_fss_content_t_resize(status_allocate, (*found), found->size + f_fss_default_allocation_step);
          }

          if (F_status_is_error(status_allocate)) return status_allocate;

          if (quotes) {
            f_macro_fss_quotes_t_resize(status_allocate, (*quotes), found->size);
            if (F_status_is_error(status_allocate)) return status_allocate;
          }
        }

        found->array[found->used] = content_partial;
        found->used++;

        if (quotes) {
          quotes->array[quotes->used] = quoted;
          quotes->used = found->used;
        }

        content_found = 1;

        if (status == FL_fss_found_object_content_not) break;
      }
      else if (status == FL_fss_found_object_not) {
        break;
      }
      else if (status == F_data_not_eos) {
        if (content_found) {
          status = F_none_eos;
        }

        content_found = 2;
        break;
      }
      else if (status == F_data_not_stop) {
        if (content_found) {
          status = F_none_stop;
        }

        content_found = 2;
        break;
      }
      else if (status == F_unterminated_group_eos || status == F_unterminated_group_eos) {
        if (content_found) {
          content_found = 2;
        }
        break;
      }
      else if (F_status_is_error(status)) {
        f_macro_string_lengths_t_delete_simple(delimits);
        return status;
      }
    } // while

    if (content_found) {
      fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

      if (content_found == 2) {
        return status;
      }

      return FL_fss_found_content;
    }

    return FL_fss_found_content_not;
  }
#endif // _di_fl_fss_extended_content_read_

#ifndef _di_fl_fss_extended_object_write_
f_return_status fl_fss_extended_object_write(const f_string_static_t object, const f_fss_quote_t quote, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_status_t status = private_fl_fss_basic_object_write(object, quote ? quote : f_fss_delimit_quote_double, range, destination);

    if (status == F_data_not_stop || status == F_data_not_eos) {

      // Objects cannot be empty, so write a quoted empty string.
      const f_status_t status_allocation = private_fl_fss_destination_increase_by(2, destination);
      if (F_status_is_error(status_allocation)) return status_allocation;

      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double;
      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double;

      if (status == F_data_not_stop) {
        return F_none_stop;
      }

      return F_none_eos;
    }

    if (complete == f_fss_complete_partial || complete == f_fss_complete_full) {
      if (status == F_none_stop || status == F_none_eos) {
        const f_status_t status_allocation = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_extended_open;
      }
    }

    return status;
  }
#endif // _di_fl_fss_extended_object_write_

#ifndef _di_fl_fss_extended_content_write_
  f_return_status fl_fss_extended_content_write(const f_string_static_t content, const f_fss_quote_t quote, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    // this operates exactly like an object, syntax-wise.
    const f_status_t status = private_fl_fss_basic_object_write(content, quote ? quote : f_fss_delimit_quote_double, range, destination);

    if (status == F_data_not_stop || status == F_data_not_eos) {
      f_status_t status_allocation = F_none;

      // content should be terminated, even if empty.
      if (complete == f_fss_complete_partial || complete == f_fss_complete_full || complete == f_fss_complete_next) {
        status_allocation = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_extended_next;
      }

      if (complete == f_fss_complete_full || complete == f_fss_complete_end) {
        status_allocation = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_extended_close;
      }

      if (status == F_data_not_stop) {
        return F_none_stop;
      }

      return F_none_eos;
    }

    if (F_status_is_error_not(status)) {
      f_status_t status_allocation = F_none;

      if (complete == f_fss_complete_partial || complete == f_fss_complete_full || complete == f_fss_complete_next) {
        status_allocation = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_extended_next;
      }

      if (complete == f_fss_complete_full || complete == f_fss_complete_end) {
        status_allocation = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_extended_close;
      }
    }

    return status;
  }
#endif // _di_fl_fss_extended_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
