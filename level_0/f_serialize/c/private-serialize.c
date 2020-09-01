#include "serialize.h"
#include "private-serialize.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_serialize_un_simple_find_) || !defined(_di_f_serialize_un_simple_get_)
  f_return_status private_f_serialize_un_simple_find(const f_string_static_t serialize, const f_array_length_t index, f_string_range_t *location) {
    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t start = 0;
    f_array_length_t current = 0;

    unsigned short width = 0;

    while (i < serialize.used) {
      width = f_macro_utf_byte_width(serialize.string[i]);

      if (serialize.string[i] == f_serialize_simple_splitter) {
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
      else if (i == serialize.used) {
        if (current == index) {
          location->start = start;
          location->stop = i - 1;
        }

        return F_none_eos;
      }

      if (i + width > serialize.used) return F_status_set_error(F_incomplete_utf_eos);

      i += width;
    } // while

    return F_data_not_eos;
  }
#endif // !defined(_di_f_serialize_un_simple_find_) || !defined(_di_f_serialize_un_simple_get_)

#ifdef __cplusplus
} // extern "C"
#endif
