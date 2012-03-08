/* FLL - Level 1
 * Project:       Serialized
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/serialized.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_serialize_simple_
  f_return_status fl_serialize_simple(const f_dynamic_string value, f_dynamic_string *serialized) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized == f_null) return f_invalid_parameter;
    #endif // _di_level_0_parameter_checking_

    f_status status = f_status_initialize;


    if (serialized->used + value.used + 1 >= serialized->size) {
      f_resize_dynamic_string(status, (*serialized), serialized->size + value.used + f_serialized_default_allocation_step);

      if (f_macro_test_for_allocation_errors(status)) return status;
    }

    if (serialized->used == 0) {
      memcpy(serialized->string + serialized->used, value.string, sizeof(f_autochar) * value.used);
      serialized->used += value.used;
    } else {
      memcpy(serialized->string + serialized->used, f_serialized_simple_splitter_string, sizeof(f_autochar));
      memcpy(serialized->string + serialized->used + 1, value.string, sizeof(f_autochar) * value.used);
      serialized->used += value.used + 1;
    }

    return f_none;
  }
#endif // _di_fl_serialize_simple_

#ifndef _di_fl_unserialize_simple_
  f_return_status fl_unserialize_simple(const f_dynamic_string serialized, f_string_locations *locations) {
    #ifndef _di_level_0_parameter_checking_
      if (locations == f_null) return f_invalid_parameter;
    #endif // _di_level_0_parameter_checking_

    f_status status = f_status_initialize;

    f_array_length i     = 0;
    f_array_length start = 0;

    while (i <= serialized.used) {
      if (serialized.string[i] == f_serialized_simple_splitter || i == serialized.used) {
        if (locations->used + 1 >= locations->size) {
          f_resize_string_locations(status, (*locations), locations->size + f_serialized_default_allocation_step);

          if (f_macro_test_for_allocation_errors(status)) return status;
        }

        if (start == i) {
          locations->array[locations->used].start = 1;
          locations->array[locations->used].stop  = 0;
          locations->used++;
        } else {
          locations->array[locations->used].start = start;
          locations->array[locations->used].stop  = i - 1;
          locations->used++;
        }

        start = i + 1;
      }

      i++;
    } // while

    return f_none;
  }
#endif // _di_fl_unserialize_simple_

#ifndef _di_fl_unserialize_simple_get_
  f_return_status fl_unserialize_simple_get(const f_dynamic_string serialized, const f_array_length index, f_string_location *location) {
    #ifndef _di_level_0_parameter_checking_
      if (location == f_null) return f_invalid_parameter;
    #endif // _di_level_0_parameter_checking_

    f_status status = f_status_initialize;

    f_array_length i       = 0;
    f_array_length current = 0;

    location->start = 1;
    location->stop  = 0;

    while (i < serialized.used) {
      if (current == index){
        if (location->start > location->stop) {
          location->start = i;
          location->stop  = i;
        }

        if (serialized.string[i] == f_serialized_simple_splitter) {
          location->stop = i - 1;
          break;
        }
      }
      else if (serialized.string[i] == f_serialized_simple_splitter) {
        current++;
      }

      i++;
    } // while

    return f_none;
  }
#endif // _di_fl_unserialize_simple_get_

#ifdef __cplusplus
} // extern "C"
#endif
