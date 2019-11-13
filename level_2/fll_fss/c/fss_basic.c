#include <level_2/fss_basic.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_basic_read_
  f_return_status fll_fss_basic_read(f_string_dynamic *buffer, f_string_location *input, f_fss_objects *objects, f_fss_contents *contents) {
    #ifndef _di_level_2_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (objects == 0) return f_status_set_error(f_invalid_parameter);
      if (contents == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = f_none;
    f_string_length initial_used = objects->used;
    bool found_data = f_false;

    do {
      if (objects->used >= objects->size) {
        f_macro_fss_objects_resize(status, (*objects), objects->used + f_fss_default_allocation_step);

        if (f_status_is_error(status)) {
          return status;
        }

        f_macro_fss_contents_resize(status, (*contents), contents->used + f_fss_default_allocation_step);

        if (f_status_is_error(status)) {
          return status;
        }
      }

      do {
        status = fl_fss_basic_object_read(buffer, input, &objects->array[objects->used]);

        if (input->start >= input->stop || input->start >= buffer->used) {
          if (status == fl_fss_found_object || status == fl_fss_found_object_no_content) {
            objects->used++;

            if (contents->array[contents->used].used >= contents->array[contents->used].size) {
              f_status status = f_none;

              f_macro_fss_content_resize(status, contents->array[contents->used], contents->array[contents->used].size + f_fss_default_allocation_step);

              if (f_status_is_error(status)) {
                return status;
              }
            }

            contents->used++;

            return fl_fss_found_object_no_content;
          }

          if (found_data) {
            if (input->start >= buffer->used) {
               return f_none_on_eos;
            }

            return f_none_on_stop;
          }
          else {
            if (input->start >= buffer->used) {
               return f_no_data_on_eos;
            }

            return f_no_data_on_stop;
          }
        }

        if (status == fl_fss_found_object) {
          found_data = f_true;
          status = fl_fss_basic_content_read(buffer, input, &contents->array[contents->used]);

          break;
        }
        else if (status == fl_fss_found_object_no_content) {
          found_data = f_true;

          if (contents->array[contents->used].used >= contents->array[contents->used].size) {
            f_status status = f_none;

            f_macro_fss_content_resize(status, contents->array[contents->used], contents->array[contents->used].size + f_fss_default_allocation_step);

            if (f_status_is_error(status)) {
              return status;
            }
          }

          break;
        }
      } while (status == fl_fss_found_no_object);

      if (status == f_none_on_eos || status == f_none_on_stop) {
        contents->array[contents->used].used++;
        objects->used++;
        contents->used++;
        return status;
      }
      else if (status == f_no_data_on_eos || status == f_no_data_on_stop) {

        // If at least some valid object was found, then return f_none equivelents.
        if (objects->used > initial_used) {
          if (status == f_no_data_on_eos)  return f_none_on_eos;
          if (status == f_no_data_on_stop) return f_none_on_stop;
        }

        return status;
      }
      else if (status != fl_fss_found_object && status != fl_fss_found_content && status != fl_fss_found_no_content && status != fl_fss_found_object_no_content) {
        return status;
      }
      // When content is found, the input->start is incremented, if content is found at input->stop, then input->start will be > input.stop.
      else if (input->start >= input->stop || input->start >= buffer->used) {
        if (status == fl_fss_found_object || status == fl_fss_found_content || status == fl_fss_found_no_content || status == fl_fss_found_object_no_content) {
          objects->used++;
          contents->used++;
        }

        if (input->start >= buffer->used) {
          return f_none_on_eos;
        }

        return f_none_on_stop;
      }

      objects->used++;
      contents->used++;
    } while (input->start < f_string_max_size);

    return f_overflow;
  }
#endif // _di_fll_fss_basic_read_

#ifndef _di_fll_fss_basic_write_
  f_return_status fll_fss_basic_write(const f_string_dynamic object, const f_string_dynamics contents, f_string_dynamic *buffer) {
    #ifndef _di_level_2_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (contents.used > contents.size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = 0;
    f_array_length current = 0;
    f_string_location location = f_string_location_initialize;

    location.start = 0;
    location.stop = object.used - 1;

    status = fl_fss_basic_object_write(buffer, object, &location);

    if (f_status_is_error(status) || status == f_no_data_on_stop || status == f_no_data_on_eos) {
      return status;
    }

    if (status == f_none || status == f_none_on_stop || status == f_none_on_eos || status == f_none_on_eol) {
      if (contents.used > 0) {
        location.start = 0;
        location.stop = contents.array[0].used - 1;
        status = fl_fss_basic_content_write(buffer, contents.array[0], &location);

        if (f_status_is_error(status)) {
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
#endif // _di_fll_fss_basic_write_

#ifdef __cplusplus
} // extern "C"
#endif
