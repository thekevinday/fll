/* FLL - Level 2
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_2/fss_extended.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fll_fss_extended_read_
  f_return_status fll_fss_extended_read(f_dynamic_string *buffer, f_string_location *input, f_fss_objects *objects, f_fss_contents *contents) {
    #ifndef _di_level_2_parameter_checking_
      if (buffer   == f_null) return f_invalid_parameter;
      if (objects  == f_null) return f_invalid_parameter;
      if (contents == f_null) return f_invalid_parameter;
    #endif // _di_level_2_parameter_checking_

    f_status        status       = f_status_initialize;
    f_string_length initial_used = objects->used;
    f_bool          found_data   = f_false;

    do {
      if (objects->used >= objects->size) {
        f_resize_fss_objects(status, (*objects), objects->used + f_fss_default_allocation_step);

        if (f_macro_test_for_allocation_errors(status)) {
          return status;
        }

        f_resize_fss_contents(status, (*contents), contents->used + f_fss_default_allocation_step);

        if (f_macro_test_for_allocation_errors(status)) {
          return status;
        }
      }

      do {
        status = fl_fss_extended_object_read(buffer, input, &objects->array[objects->used]);

        if (input->start >= input->stop || input->start >= buffer->used) {
          if (status == fl_fss_found_object || status == fl_fss_found_object_no_content) {
            objects->used++;

            fl_macro_fss_allocate_content_if_necessary(contents->array[contents->used]);

            contents->used++;

            return fl_fss_found_object_no_content;
          }

          if (found_data) {
            if (input->start >= buffer->used) {
               return f_none_on_eos;
            }

            return f_none_on_stop;
          } else {
            if (input->start >= buffer->used) {
               return f_no_data_on_eos;
            }

            return f_no_data_on_stop;
          }
        }

        if (status == fl_fss_found_object) {
          found_data = f_true;
          status     = fl_fss_extended_content_read(buffer, input, &contents->array[contents->used]);

          break;
        } else if (status == fl_fss_found_object_no_content) {
          found_data = f_true;

          fl_macro_fss_allocate_content_if_necessary(contents->array[contents->used]);

          break;
        }
      } while (status == fl_fss_found_no_object);

      if (status == f_none_on_eos || status == f_none_on_stop) {
        contents->array[contents->used].used++;
        objects->used++;
        contents->used++;
        return status;
      } else if (status == f_no_data_on_eos || status == f_no_data_on_stop) {

        // if at least some valid object was found, then return f_none equivelents
        if (objects->used > initial_used) {
          if (status == f_no_data_on_eos)  return f_none_on_eos;
          if (status == f_no_data_on_stop) return f_none_on_stop;
        }

        return status;
      } else if (status != fl_fss_found_object && status != fl_fss_found_content && status != fl_fss_found_no_content && status != fl_fss_found_object_no_content) {
        return status;
      // when content is found, the input->start is incremented, if content is found at input->stop, then input->start will be > input.stop
      } else if (input->start >= input->stop || input->start >= buffer->used) {
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
    } while (f_true);

    return f_unknown;
  }
#endif // _di_fll_fss_extended_read_

#ifdef __cplusplus
} // extern "C"
#endif
