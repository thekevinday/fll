#include <level_0/serialize.h>
#include "private-serialize.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_serialize_simple_
  f_return_status f_serialize_simple(const f_string_static value, f_string_dynamic *serialize) {
    #ifndef _di_level_0_parameter_checking_
      if (serialize == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;

    if (serialize->used + value.used + 1 >= serialize->size) {
      f_macro_string_dynamic_resize(status, (*serialize), serialize->size + value.used + 1);
      if (F_status_is_error(status)) return status;
    }

    if (serialize->used == 0) {
      memcpy(serialize->string + serialize->used, value.string, value.used);
      serialize->used += value.used;
    }
    else {
      memcpy(serialize->string + serialize->used, f_serialize_simple_splitter_string, 1);
      memcpy(serialize->string + serialize->used + 1, value.string, value.used);
      serialize->used += value.used + 1;
    }

    return F_none;
  }
#endif // _di_f_serialize_simple_

#ifndef _di_f_serialize_un_simple_
  f_return_status f_serialize_un_simple(const f_string_static serialize, f_string_dynamics *strings) {
    #ifndef _di_level_0_parameter_checking_
      if (serialize.used == 0) return F_status_set_error(F_parameter);
      if (strings == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;

    f_array_length i = 0;
    f_array_length start = 0;

    uint8_t width = 0;

    while (i < serialize.used) {
      width = f_macro_utf_byte_width(serialize.string[i]);

      if (serialize.string[i] == f_serialize_simple_splitter || i + 1 >= serialize.used) {
        f_macro_memory_structure_macro_increment(status, (*strings), 1, f_serialize_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
        if (F_status_is_error(status)) return status;

        if (start == i) {
          strings->array[strings->used].used = 0;
          strings->used++;
        }
        else {
          f_string_length total;

          if (i + 1 >= serialize.used) {
            total = (i - start) + 1;
          }
          else {
            // subtract one from stop point to disclused the f_serialize_simple_splitter character.
            total = ((i - 1) - start) + 1;
          }

          if (total > strings->array[strings->used].size) {
            f_macro_string_dynamic_new(status, strings->array[strings->used], total);
            if (F_status_is_error(status)) return status;

            strings->array[strings->used].size = total;
          }

          memcpy(strings->array[strings->used].string, serialize.string + start, total);

          strings->array[strings->used].used = total;
          strings->used++;
        }

        if (i + width > serialize.used) {
          return F_status_set_error(F_incomplete_utf_eos);
        }

        start = i + width;
      }
      else if (i + width > serialize.used) {
        return F_status_set_error(F_incomplete_utf_eos);
      }

      i += width;
    } // while

    return F_none;
  }
#endif // _di_f_serialize_un_simple_

#ifndef _di_f_serialize_un_simple_map_
  f_return_status f_serialize_un_simple_map(const f_string_static serialize, f_string_ranges *locations) {
    #ifndef _di_level_0_parameter_checking_
      if (serialize.used == 0) return F_status_set_error(F_parameter);
      if (locations == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;

    f_array_length i = 0;
    f_array_length start = 0;

    uint8_t width = 0;

    while (i < serialize.used) {
      width = f_macro_utf_byte_width(serialize.string[i]);

      if (serialize.string[i] == f_serialize_simple_splitter || i + 1 >= serialize.used) {
        f_macro_memory_structure_macro_increment(status, (*locations), 1, f_serialize_default_allocation_step, f_macro_string_ranges_resize, F_buffer_too_large);
        if (F_status_is_error(status)) return status;

        if (start == i) {
          // provide an invalid start to stop range to communicate that there is no data.
          locations->array[locations->used].start = 1;
          locations->array[locations->used].stop = 0;
        }
        else if (i + 1 >= serialize.used) {
          locations->array[locations->used].start = start;
          locations->array[locations->used].stop = i;
        }
        else {
          // subtract one from stop point to disclused the f_serialize_simple_splitter character.
          locations->array[locations->used].start = start;
          locations->array[locations->used].stop = i - 1;
        }

        locations->used++;

        if (i + width > serialize.used) return F_status_set_error(F_incomplete_utf_eos);

        start = i + width;
      }
      else if (i + width > serialize.used) {
        return F_status_set_error(F_incomplete_utf_eos);
      }

      i += width;
    } // while

    return F_none;
  }
#endif // _di_f_serialize_un_simple_map_

#ifndef _di_f_serialize_un_simple_find_
  f_return_status f_serialize_un_simple_find(const f_string_static serialize, const f_array_length index, f_string_range *range) {
    #ifndef _di_level_0_parameter_checking_
      if (serialize.used == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_serialize_un_simple_find(serialize, index, range);
  }
#endif // _di_f_serialize_un_simple_find_

#ifndef _di_f_serialize_un_simple_get_
  f_return_status f_serialize_un_simple_get(const f_string_static serialize, const f_array_length index, f_string_dynamic *dynamic) {
    #ifndef _di_level_0_parameter_checking_
      if (serialize.used == 0) return F_status_set_error(F_parameter);
      if (dynamic == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_range range = f_string_range_initialize;

    f_status status = private_f_serialize_un_simple_find(serialize, index, &range);
    if (F_status_is_error(status)) return status;

    if (status == F_data_not_eos) {
      dynamic->used = 0;
      return status;
    }

    f_string_length total = (range.stop - range.start) + 1;

    if (total >= dynamic->size) {
      f_status status_allocation = F_none;

      f_macro_string_dynamic_resize(status_allocation, (*dynamic), total);
      if (F_status_is_error(status_allocation)) return status_allocation;
    }

    memcpy(dynamic->string, serialize.string + range.start, total);
    dynamic->used = total;

    return status;
  }
#endif // _di_f_serialize_un_simple_get_

#ifdef __cplusplus
} // extern "C"
#endif
