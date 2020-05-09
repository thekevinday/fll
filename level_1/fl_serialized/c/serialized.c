#include <level_1/serialized.h>
#include "private-serialized.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_serialize_simple_
  f_return_status fl_serialize_simple(const f_string_dynamic value, f_string_dynamic *serialized) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    if (serialized->used + value.used + 1 >= serialized->size) {
      f_macro_string_dynamic_resize(status, (*serialized), serialized->size + value.used + 1);

      if (f_status_is_error(status)) return status;
    }

    if (serialized->used == 0) {
      memcpy(serialized->string + serialized->used, value.string, value.used);
      serialized->used += value.used;
    }
    else {
      memcpy(serialized->string + serialized->used, f_serialized_simple_splitter_string, 1);
      memcpy(serialized->string + serialized->used + 1, value.string, value.used);
      serialized->used += value.used + 1;
    }

    return f_none;
  }
#endif // _di_fl_serialize_simple_

#ifndef _di_fl_unserialize_simple_
  f_return_status fl_unserialize_simple(const f_string_dynamic serialized, f_string_dynamics *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized.used == 0) return f_status_set_error(f_invalid_parameter);
      if (strings == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    f_array_length i = 0;
    f_array_length start = 0;

    uint8_t width = 0;

    while (i < serialized.used) {
      width = f_macro_utf_byte_width(serialized.string[i]);

      if (serialized.string[i] == f_serialized_simple_splitter || i + 1 >= serialized.used) {
        if (strings->used >= strings->size) {
          f_macro_string_dynamics_resize(status, (*strings), strings->size + f_serialized_default_allocation_step);

          if (f_status_is_error(status)) return status;
        }

        if (start == i) {
          strings->array[strings->used].used = 0;
          strings->used++;
        }
        else {
          f_string_length total;

          if (i + 1 >= serialized.used) {
            total = (i - start) + 1;
          }
          else {
            // subtract one from stop point to disclused the f_serialized_simple_splitter character.
            total = ((i - 1) - start) + 1;
          }

          if (total > strings->array[strings->used].size) {
            f_macro_string_dynamic_new(status, strings->array[strings->used], total);

            if (f_status_is_error(status)) return status;

            strings->array[strings->used].size = total;
          }

          memcpy(strings->array[strings->used].string, serialized.string + start, total);

          strings->array[strings->used].used = total;
          strings->used++;
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
#endif // _di_fl_unserialize_simple_

#ifndef _di_fl_unserialize_simple_map_
  f_return_status fl_unserialize_simple_map(const f_string_dynamic serialized, f_string_ranges *locations) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized.used == 0) return f_status_set_error(f_invalid_parameter);
      if (locations == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    f_array_length i = 0;
    f_array_length start = 0;

    uint8_t width = 0;

    while (i < serialized.used) {
      width = f_macro_utf_byte_width(serialized.string[i]);

      if (serialized.string[i] == f_serialized_simple_splitter || i + 1 >= serialized.used) {
        if (locations->used >= locations->size) {
          f_macro_string_ranges_resize(status, (*locations), locations->size + f_serialized_default_allocation_step);

          if (f_status_is_error(status)) return status;
        }

        if (start == i) {
          // provide an invalid start to stop range to communicate that there is no data.
          locations->array[locations->used].start = 1;
          locations->array[locations->used].stop = 0;
        }
        else if (i + 1 >= serialized.used) {
          locations->array[locations->used].start = start;
          locations->array[locations->used].stop = i;
        }
        else {
          // subtract one from stop point to disclused the f_serialized_simple_splitter character.
          locations->array[locations->used].start = start;
          locations->array[locations->used].stop = i - 1;
        }

        locations->used++;

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
  f_return_status fl_unserialize_simple_find(const f_string_dynamic serialized, const f_array_length index, f_string_range *range) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized.used == 0) return f_status_set_error(f_invalid_parameter);
      if (range == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_fl_unserialize_simple_find(serialized, index, range);
  }
#endif // _di_fl_unserialize_simple_find_

#ifndef _di_fl_unserialize_simple_get_
  f_return_status fl_unserialize_simple_get(const f_string_dynamic serialized, const f_array_length index, f_string_dynamic *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (serialized.used == 0) return f_status_set_error(f_invalid_parameter);
      if (dynamic == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_range range = f_string_range_initialize;

    f_status status = private_fl_unserialize_simple_find(serialized, index, &range);

    if (f_status_is_error(status)) return status;

    if (status == f_no_data_on_eos) {
      dynamic->used = 0;
      return status;
    }

    f_string_length total = (range.stop - range.start) + 1;

    if (total >= dynamic->size) {
      f_status status_allocation = f_none;

      f_macro_string_dynamic_resize(status_allocation, (*dynamic), total);

      if (f_status_is_error(status_allocation)) return status_allocation;
    }

    memcpy(dynamic->string, serialized.string + range.start, total);
    dynamic->used = total;

    return status;
  }
#endif // _di_fl_unserialize_simple_get_

#ifdef __cplusplus
} // extern "C"
#endif
