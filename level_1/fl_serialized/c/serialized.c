/* FLL - Level 1
 * Project:       Serialized
 * Version:       0.2.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/serialized.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_serialize_
  f_return_status fl_serialize(const f_u_short strategy, const f_dynamic_string value, f_serialized *serialized) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized == f_null) return f_invalid_parameter;
    #endif // _di_level_0_parameter_checking_

    if (strategy != f_serialized_strategy_simple) {
      return f_unsupported;
    }

    f_status status = f_status_initialize;

    if (serialized->used + value.used + 1 >= serialized->size) {
      f_resize_serialized(status, (*serialized), serialized->size + value.used + f_serialized_default_allocation_step);

      if (f_macro_test_for_allocation_errors(status)) return status;
    }

    memcpy(serialized->string + serialized->used, f_serialized_strategy_simple_splitter, sizeof(f_autochar));
    memcpy(serialized->string + serialized->used + 1, value->string, sizeof(f_autochar) * value.used);
    serialized->used += value.used + 1;

    return f_none;
  }
#endif // _di_fl_serialize_

#ifndef _di_fl_unserialize_
  f_return_status fl_unserialize(const f_u_short strategy, const f_serialized *serialized, f_string_locations *locations) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized == f_null) return f_invalid_parameter;
      if (locations  == f_null) return f_invalid_parameter;
    #endif // _di_level_0_parameter_checking_

    if (strategy != f_serialized_strategy_simple) {
      return f_unsupported;
    }

    f_status status = f_status_initialize;

    f_array_length i       = 0;
    f_array_length current = 0;

    f_string_length start = 1;
    f_string_length stop  = 0;

    while (i < serialized.used) {
      if (current == index) {
        if (start > stop) {
          start = i;
          stop  = i;
        }

        if (serialized.string[i] == f_serialized_strategy_simple_splitter) {
          stop = i - 1;

          if (locations->used + 1 >= locations->size) {
            f_resize_string_locations(status, (*locations), locations->size + f_serialized_default_allocation_step);

            if (f_macro_test_for_allocation_errors(status)) return status;
          }

          locations->array[locations->used].start = start;
          locations->array[locations->used].stop  = stop;
          locations->used++;

          start = 1;
          stop  = 0;
        }
      }
      else if (serialized.string[i] == f_serialized_strategy_simple_splitter) {
        current++;
      }

      i++;
    } // while

    return f_none;
  }
#endif // _di_fl_unserialize_

#ifndef _di_fl_unserialize_get_
  f_return_status fl_unserialize_get(const f_u_short strategy, const f_serialized serialized, const f_array_length index, f_string_location *location) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized == f_null) return f_invalid_parameter;
      if (location   == f_null) return f_invalid_parameter;
    #endif // _di_level_0_parameter_checking_

    if (strategy != f_serialized_strategy_simple) {
      return f_unsupported;
    }

    f_status status = f_status_initialize;

    f_array_length i       = 0;
    f_array_length current = 0;

    location->start = 1;
    location->stop  = 0;

    while (i < serialized.used) {
      if (current == index){
        if (location->start > location->stop){
          location->start = i;
          location->stop  = i;
        }

        if (serialized.string[i] == f_serialized_strategy_simple_splitter) {
          location->stop = i - 1;
          break;
        }
      }
      else if (serialized.string[i] == f_serialized_strategy_simple_splitter) {
        current++;
      }

      i++;
    } // while

    return f_none;
  }
#endif // _di_fl_unserialize_get_

#ifdef __cplusplus
} // extern "C"
#endif
