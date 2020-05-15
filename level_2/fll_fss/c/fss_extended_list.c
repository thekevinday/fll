#include <level_2/fss_extended_list.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_extended_list_read_
  f_return_status fll_fss_extended_list_read(f_string_dynamic *buffer, f_string_range *location, f_fss_nest *nest) {
    #ifndef _di_level_3_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (nest == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_3_parameter_checking_

    f_status status = f_none;
    f_string_length initial_used = 0;
    bool found_data = f_false;

    if (nest->used == 0) {
      f_macro_fss_nest_resize(status, (*nest), f_fss_default_allocation_step);
    }
    else {
      initial_used = nest->depth[0].used;
    }

    do {
      do {
        if (nest->depth[0].used >= nest->depth[0].size) {
          f_macro_fss_items_resize(status, nest->depth[0], nest->depth[0].used + f_fss_default_allocation_step);

          if (f_status_is_error(status)) {
            return status;
          }
        }

        status = fl_fss_extended_list_object_read(buffer, location, &nest->depth[0].array[nest->depth[0].used].object);

        if (f_status_is_error(status)) {
          return status;
        }

        if (location->start >= location->stop || location->start >= buffer->used) {
          if (status == fl_fss_found_object || status == fl_fss_found_object_no_content) {
            // extended list requires content closure, so this could be an error.
            return fl_fss_found_object_no_content;
          }

          if (found_data) {
            if (location->start >= buffer->used) {
              return f_none_on_eos;
            }

            return f_none_on_stop;
          }
          else {
            if (location->start >= buffer->used) {
              return f_no_data_on_eos;
            }

            return f_no_data_on_stop;
          }
        }

        if (status == fl_fss_found_object) {
          found_data = f_true;
          status = fl_fss_extended_list_content_read(buffer, location, nest);

          break;
        }
        else if (status == fl_fss_found_object_no_content) {
          found_data = f_true;
          break;
        }
      } while (status == fl_fss_found_no_object);

      if (status == f_none_on_eos || status == f_none_on_stop) {
        return status;
      }
      else if (status == f_no_data_on_eos || status == f_no_data_on_stop) {
        // If at least some valid object was found, then return f_none equivalents.
        if (nest->depth[0].used > initial_used) {
          if (status == f_no_data_on_eos) return f_none_on_eos;
          if (status == f_no_data_on_stop) return f_none_on_stop;
        }

        return status;
      }
      else if (status == f_unterminated_on_eos || status == f_unterminated_on_stop || status == f_unterminated_nest_on_eos || status == f_unterminated_nest_on_stop) {
        // If at least some valid object was found, then return f_none equivalents.
        if (nest->depth[0].used > initial_used) {
          if (status == f_no_data_on_eos) return f_none_on_eos;
          if (status == f_no_data_on_stop) return f_none_on_stop;
        }

        return status;
      }
      else if (status != fl_fss_found_object && status != fl_fss_found_content && status != fl_fss_found_no_content && status != fl_fss_found_object_no_content) {
        return status;
      }
      // When content is found, the location->start is incremented, if content is found at location->stop, then location->start will be > location.stop.
      else if (location->start >= location->stop || location->start >= buffer->used) {
        if (location->start >= buffer->used) {
          return f_none_on_eos;
        }

        return f_none_on_stop;
      }
    } while (location->start < f_string_max_size);

    return f_status_is_error(f_number_overflow);
  }
#endif // _di_fll_fss_extended_list_read_

/*
#ifndef _di_fll_fss_extended_list_write_
  f_return_status fll_fss_extended_list_write(const f_string_static object, const f_string_statics contents, f_string_dynamic *buffer) {
    #ifndef _di_level_3_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (contents.used > contents.size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_3_parameter_checking_

    f_status status = 0;
    f_array_length current = 0;
    f_string_range range = f_string_range_initialize;

    range.start = 0;
    range.stop = object.used - 1;

    status = fl_fss_extended_list_object_write(object, &range, buffer);

    if (f_status_is_error(status) || status == f_no_data_on_stop || status == f_no_data_on_eos) {
      return status;
    }

    if (status == f_none || status == f_none_on_stop || status == f_none_on_eos || status == f_none_on_eol) {
      if (contents.used > 0) {
        range.start = 0;
        range.stop = contents.array[0].used - 1;
        status = fl_fss_extended_list_content_write(contents.array[0], &range, buffer);

        if (f_status_is_error(status) || status == f_no_data_on_stop || status == f_no_data_on_eos) {
          return status;
        }
      }
      else {
        if (buffer->used >= buffer->size) {
          f_macro_string_dynamic_resize(status, (*buffer), buffer->size + f_fss_default_allocation_step_string);
          if (f_status_is_error(status)) return status;
        }

        buffer->string[buffer->used] = f_string_eol;
        buffer->used++;
      }
    }

    return f_none;
  }
#endif // _di_fll_fss_extended_list_write_
*/

#ifdef __cplusplus
} // extern "C"
#endif
