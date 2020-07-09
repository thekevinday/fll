#include <level_2/fss_basic.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_basic_read_
  f_return_status fll_fss_basic_read(f_string_dynamic *buffer, f_string_range *range, f_fss_objects *objects, f_fss_contents *contents, f_fss_quoteds *quoted_objects) {
    #ifndef _di_level_2_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (objects == 0) return F_status_set_error(F_parameter);
      if (contents == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = F_none;
    f_status status2 = F_none;
    f_string_length initial_used = objects->used;

    bool found_data = F_false;

    f_fss_quoted *quoted_object = 0;

    do {
      if (objects->used == objects->size) {
        f_macro_fss_objects_resize(status2, (*objects), objects->used + f_fss_default_allocation_step);
        if (F_status_is_error(status2)) return status2;

        f_macro_fss_contents_resize(status2, (*contents), contents->used + f_fss_default_allocation_step);
        if (F_status_is_error(status2)) return status2;

        if (quoted_objects) {
          f_macro_fss_quoteds_resize(status2, (*quoted_objects), quoted_objects->used + f_fss_default_allocation_step);
          if (F_status_is_error(status2)) return status2;
        }
      }

      do {
        if (quoted_objects) {
          quoted_object = &quoted_objects->array[quoted_objects->used];
        }

        status = fl_fss_basic_object_read(buffer, range, &objects->array[objects->used], quoted_object);

        if (F_status_is_error(status)) {
          return status;
        }

        if (range->start >= range->stop || range->start >= buffer->used) {
          if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {
            objects->used++;

            if (quoted_objects) {
              quoted_objects->used++;
            }

            if (contents->array[contents->used].used == contents->array[contents->used].size) {
              f_macro_fss_content_resize(status2, contents->array[contents->used], contents->array[contents->used].size + f_fss_default_allocation_step);
              if (F_status_is_error(status2)) return status2;
            }

            contents->used++;

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

          status = fl_fss_basic_content_read(buffer, range, &contents->array[contents->used]);
          if (F_status_is_error(status)) return status;

          break;
        }
        else if (status == FL_fss_found_object_content_not) {
          found_data = F_true;

          if (contents->array[contents->used].used == contents->array[contents->used].size) {
            f_macro_fss_content_resize(status2, contents->array[contents->used], contents->array[contents->used].size + f_fss_default_allocation_step);
            if (F_status_is_error(status2)) return status2;
          }

          break;
        }
      } while (status == FL_fss_found_object_not);

      if (status == F_none_eos || status == F_none_stop) {
        contents->array[contents->used].used++;
        objects->used++;
        contents->used++;

        if (quoted_objects) {
          quoted_objects->used++;
        }

        return status;
      }
      else if (status == F_data_not_eos || status == F_data_not_stop) {

        // If at least some valid object was found, then return F_none equivelents.
        if (objects->used > initial_used) {
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
        if (status == FL_fss_found_object || status == FL_fss_found_content || status == FL_fss_found_content_not || status == FL_fss_found_object_content_not) {
          objects->used++;
          contents->used++;

          if (quoted_objects) {
            quoted_objects->used++;
          }
        }

        if (range->start >= buffer->used) {
          return F_none_eos;
        }

        return F_none_stop;
      }

      objects->used++;
      contents->used++;

      if (quoted_objects) {
        quoted_objects->used++;
      }
    } while (range->start < f_string_length_size);

    return F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_basic_read_

#ifndef _di_fll_fss_basic_write_
  f_return_status fll_fss_basic_write(const f_string_static object, const f_string_statics contents, f_string_dynamic *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
      if (contents.used > contents.size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = 0;
    f_array_length current = 0;
    f_string_range range = f_macro_string_range_initialize(object.used);

    status = fl_fss_basic_object_write(object, 0, &range, destination);

    if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
      return status;
    }

    if (status == F_none || status == F_none_stop || status == F_none_eos || status == F_none_eol) {
      if (contents.used > 0) {
        range.start = 0;
        range.stop = contents.array[0].used - 1;
        status = fl_fss_basic_content_write(contents.array[0], &range, destination);

        if (F_status_is_error(status)) {
          return status;
        }
      }
      else {
        if (destination->used == destination->size) {
          f_macro_string_dynamic_resize(status, (*destination), destination->size + f_fss_default_allocation_step_string);
          if (F_status_is_error(status)) return status;
        }

        destination->string[destination->used] = f_string_eol[0];
        destination->used++;
      }
    }

    return F_none;
  }
#endif // _di_fll_fss_basic_write_

#ifdef __cplusplus
} // extern "C"
#endif
