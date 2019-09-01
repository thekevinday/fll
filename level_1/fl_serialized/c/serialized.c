#include <level_1/serialized.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_serialize_simple_
  f_return_status fl_serialize_simple(const f_dynamic_string value, f_dynamic_string *serialized) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    if (serialized->used + value.used + 1 >= serialized->size) {
      f_macro_string_dynamic_resize(status, (*serialized), serialized->size + value.used + 1);

      if (f_status_is_error(status)) return status;
    }

    if (serialized->used == 0) {
      memcpy(serialized->string + serialized->used, value.string, sizeof(char) * value.used);
      serialized->used += value.used;
    }
    else {
      memcpy(serialized->string + serialized->used, f_serialized_simple_splitter_string, sizeof(char));
      memcpy(serialized->string + serialized->used + 1, value.string, sizeof(char) * value.used);
      serialized->used += value.used + 1;
    }

    return f_none;
  }
#endif // _di_fl_serialize_simple_

#ifndef _di_fl_unserialize_simple_map_
  f_return_status fl_unserialize_simple_map(const f_dynamic_string serialized, f_string_locations *locations) {
    #ifndef _di_level_0_parameter_checking_
      if (locations == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    f_array_length i = 0;
    f_array_length start = 0;

    f_u_short width = 0;

    while (i < serialized.used) {
      width = f_macro_utf_byte_width(serialized.string[i]);

      if (serialized.string[i] == f_serialized_simple_splitter || i == serialized.used) {
        if (locations->used + width >= locations->size) {
          f_macro_strings_string_locations_resize(status, (*locations), locations->size + f_serialized_default_allocation_step);

          if (f_status_is_error(status)) return status;
        }

        if (start == i) {
          // provide an invalid start to stop range to communicate that there is no data.
          locations->array[locations->used].start = 1;
          locations->array[locations->used].stop = 0;
          locations->used++;
        }
        else {
          locations->array[locations->used].start = start;
          locations->array[locations->used].stop = i - 1;
          locations->used++;
        }

        if (i + width > serialized.used) {
          return f_status_set_error(f_incomplete_utf_on_eos);
        }

        start = i + width;
      }
      else if (i + width > serialized.used) {
        return f_status_set_error(f_incomplete_utf_on_eos);
      }

      i += width;
    } // while

    return f_none;
  }
#endif // _di_fl_unserialize_simple_map_

#ifndef _di_fl_unserialize_simple_find_
  f_return_status fl_unserialize_simple_find(const f_dynamic_string serialized, const f_array_length index, f_string_location *location) {
    #ifndef _di_level_0_parameter_checking_
      if (location == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    f_array_length i = 0;
    f_array_length start = 0;
    f_array_length current = 0;

    f_u_short width = 0;

    while (i < serialized.used) {
      width = f_macro_utf_byte_width(serialized.string[i]);

      if (serialized.string[i] == f_serialized_simple_splitter) {
        if (current == index) {
          if (start == i) {
            // provide an invalid start to stop range to communicate that there is no data.
            location->start = 1;
            location->stop = 0;
          }
          else {
            location->start = start;
            location->stop = i - 1;
          }

          return f_none;
        }

        start = i + width;
        current++;
      }
      else if (i == serialized.used) {
        if (current == index) {
          location->start = start;
          location->stop = i - 1;
        }

        return f_none_on_eos;
      }

      if (i + width > serialized.used) {
        return f_status_set_error(f_incomplete_utf_on_eos);
      }

      i += width;
    } // while

    return f_no_data_on_eos;
  }
#endif // _di_fl_unserialize_simple_find_

#ifdef __cplusplus
} // extern "C"
#endif
