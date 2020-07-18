#include <level_1/fss_extended.h>
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_object_read_
  f_return_status fl_fss_extended_object_read(f_string_dynamic *buffer, f_string_range *range, f_fss_object *found, f_fss_quoted *quoted) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;
    f_string_lengths delimits = f_string_lengths_initialize;

    status = private_fl_fss_basic_object_read(buffer, range, found, quoted, &delimits);
    if (F_status_is_error(status)) {
      f_macro_string_lengths_delete_simple(delimits);
      return status;
    }

    if (status == FL_fss_found_object_not || status == F_data_not || status == F_data_not_eos || status == F_data_not_stop) {
      f_macro_string_lengths_delete_simple(delimits);
      return status;
    }

    fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

    return status;
  }
#endif // _di_fl_fss_extended_object_read_

#ifndef _di_fl_fss_extended_content_read_
  f_return_status fl_fss_extended_content_read(f_string_dynamic *buffer, f_string_range *range, f_fss_content *found, f_fss_quoteds *quoteds) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;
    f_status status_allocate = F_none;

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

    f_string_lengths delimits = f_string_lengths_initialize;

    uint8_t content_found = 0;

    while (range->start <= range->stop && range->start < buffer->used) {
      f_string_range content_partial = f_string_range_initialize;
      f_fss_quoted quoted = 0;

      status = private_fl_fss_basic_object_read(buffer, range, &content_partial, &quoted, &delimits);

      if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {
        if (found->used == found->size) {
          if (found->used + f_fss_default_allocation_step > found->size) {
            if (found->used == f_array_length_size) {
              f_macro_string_lengths_delete_simple(delimits);
              return F_status_set_error(F_buffer_too_large);
            }
            else {
              f_macro_fss_content_resize(status_allocate, (*found), found->size + f_fss_default_allocation_step);
            }
          }
          else {
            f_macro_fss_content_resize(status_allocate, (*found), found->size + f_fss_default_allocation_step);
          }

          if (F_status_is_error(status_allocate)) return status_allocate;

          if (quoteds) {
            f_macro_fss_quoteds_resize(status_allocate, (*quoteds), found->size);
            if (F_status_is_error(status_allocate)) return status_allocate;
          }
        }

        found->array[found->used] = content_partial;
        found->used++;

        if (quoteds) {
          quoteds->array[quoteds->used] = quoted;
          quoteds->used = found->used;
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
        f_macro_string_lengths_delete_simple(delimits);
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
f_return_status fl_fss_extended_object_write(const f_string_static object, const f_fss_quoted quoted, f_string_range *range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_fss_basic_object_write(object, quoted, range, destination);
  }
#endif // _di_fl_fss_extended_object_write_

#ifndef _di_fl_fss_extended_content_write_
  f_return_status fl_fss_extended_content_write(const f_string_static content, const f_fss_quoted quoted, f_string_range *range, f_string_dynamic *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    // this operates exactly like an object, syntax-wise, so just use the object write.
    return private_fl_fss_basic_object_write(content, quoted, range, destination);
  }
#endif // _di_fl_fss_extended_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
