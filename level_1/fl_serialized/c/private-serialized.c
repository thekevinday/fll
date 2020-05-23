#include <level_1/serialized.h>
#include "private-serialized.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_unserialize_simple_find_) || !defined(_di_fl_unserialize_simple_get_)
  f_return_status private_fl_unserialize_simple_find(const f_string_static serialized, const f_array_length index, f_string_range *location) {
    f_status status = F_none;

    f_array_length i = 0;
    f_array_length start = 0;
    f_array_length current = 0;

    unsigned short width = 0;

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

          return F_none;
        }

        start = i + width;
        current++;
      }
      else if (i == serialized.used) {
        if (current == index) {
          location->start = start;
          location->stop = i - 1;
        }

        return F_none_eos;
      }

      if (i + width > serialized.used) {
        return F_status_set_error(F_incomplete_utf_eos);
      }

      i += width;
    } // while

    return F_data_not_eos;
  }
#endif // !defined(_di_fl_unserialize_simple_find_) || !defined(_di_fl_unserialize_simple_get_)

#ifdef __cplusplus
} // extern "C"
#endif
