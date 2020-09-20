#include "fss_extended_list.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_extended_list_read_
  f_return_status fll_fss_extended_list_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_nest_t *nest) {
    #ifndef _di_level_3_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (nest == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_3_parameter_checking_

    f_status_t status = F_none;
    f_status_t status2 = F_none;
    f_string_length_t initial_used = 0;
    bool found_data = F_false;

    if (nest->used == 0) {
      f_macro_fss_nest_t_resize(status2, (*nest), f_fss_default_allocation_step);
      if (F_status_is_error(status2)) return status2;
    }
    else {
      initial_used = nest->depth[0].used;
    }

    do {
      do {
        if (nest->depth[0].used == nest->depth[0].size) {
          f_macro_fss_items_t_resize(status2, nest->depth[0], nest->depth[0].used + f_fss_default_allocation_step);
          if (F_status_is_error(status)) return status;
        }

        status = fl_fss_extended_list_object_read(buffer, range, &nest->depth[0].array[nest->depth[0].used].object);
        if (F_status_is_error(status)) return status;

        if (range->start >= range->stop || range->start >= buffer->used) {
          if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {

            // extended list requires content closure, so this could be an error.
            return FL_fss_found_object_content_not;
          }

          if (found_data) {
            if (range->start >= buffer->used) {
              return F_none_eos;
            }

            return F_none_stop;
          }
          else {
            if (range->start >= buffer->used) {
              return F_data_not_eos;
            }

            return F_data_not_stop;
          }
        }

        if (status == FL_fss_found_object) {
          found_data = F_true;

          status = fl_fss_extended_list_content_read(buffer, range, nest);

          break;
        }
        else if (status == FL_fss_found_object_content_not) {
          found_data = F_true;
          break;
        }
      } while (status == FL_fss_found_object_not);

      if (status == F_none_eos || status == F_none_stop) {
        return status;
      }
      else if (status == F_data_not_eos || status == F_data_not_stop) {

        // If at least some valid object was found, then return F_none equivalents.
        if (nest->depth[0].used > initial_used) {
          if (status == F_data_not_eos) return F_none_eos;
          if (status == F_data_not_stop) return F_none_stop;
        }

        return status;
      }
      else if (status == F_unterminated_eos || status == F_unterminated_stop || status == F_unterminated_nest_eos || status == F_unterminated_nest_stop) {

        // If at least some valid object was found, then return F_none equivalents.
        if (nest->depth[0].used > initial_used) {
          if (status == F_data_not_eos) return F_none_eos;
          if (status == F_data_not_stop) return F_none_stop;
        }

        return status;
      }
      else if (status != FL_fss_found_object && status != FL_fss_found_content && status != FL_fss_found_content_not && status != FL_fss_found_object_content_not) {
        return status;
      }
      // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
      else if (range->start >= range->stop || range->start >= buffer->used) {
        if (range->start >= buffer->used) {
          return F_none_eos;
        }

        return F_none_stop;
      }
    } while (range->start < f_string_length_t_size);

    return F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_extended_list_read_

/*
#ifndef _di_fll_fss_extended_list_write_
  f_return_status fll_fss_extended_list_write(const f_string_static_t object, const f_string_statics_t contents, f_string_dynamic_t *buffer) {
    #ifndef _di_level_3_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (contents.used > contents.size) return F_status_set_error(F_parameter);
    #endif // _di_level_3_parameter_checking_

    f_status_t status = 0;
    f_array_length_t current = 0;
    f_string_range_t range = f_string_range_t_initialize;

    range.start = 0;
    range.stop = object.used - 1;

    status = fl_fss_extended_list_object_write(object, &range, buffer);

    if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
      return status;
    }

    if (status == F_none || status == F_none_stop || status == F_none_eos || status == F_none_eol) {
      if (contents.used > 0) {
        range.start = 0;
        range.stop = contents.array[0].used - 1;

        status = fl_fss_extended_list_content_write(contents.array[0], &range, buffer);

        if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
          return status;
        }
      }
      else {
        if (buffer->used == buffer->size) {
          status = fl_string_dynamic_size_increase(f_fss_default_allocation_step_string, buffer);
          if (F_status_is_error(status)) return status;
        }

        buffer->string[buffer->used] = f_string_eol[0];
        buffer->used++;
      }
    }

    return F_none;
  }
#endif // _di_fll_fss_extended_list_write_
*/

#ifdef __cplusplus
} // extern "C"
#endif
