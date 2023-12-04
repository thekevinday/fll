#include "serialize.h"
#include "private-serialize.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_serialize_from_simple_get_) || !defined(_di_f_serialize_from_simple_select_)
  f_status_t private_f_serialize_from_simple_select(const f_string_static_t source, const f_number_unsigned_t index, f_range_t * const range) {

    f_number_unsigned_t start = 0;
    f_number_unsigned_t current = 0;

    unsigned short width = 0;

    for (f_number_unsigned_t i = 0; i < source.used; i += width) {

      width = macro_f_utf_byte_width(source.string[i]);

      if (source.string[i] == f_serialize_to_simple_splitter_s.string[0]) {
        if (current == index) {
          if (start == i) {
            range->start = 1;
            range->stop = 0;
          }
          else {
            range->start = start;
            range->stop = i - 1;
          }

          return F_okay;
        }

        start = i + width;
        ++current;

        // Handle case when splitter as at the end of the string, creating a new empty string.
        if (start >= source.used && current == index) {
          range->start = 1;
          range->stop = 0;

          return F_okay;
        }
      }
      else if (i == source.used) {
        if (current == index) {
          range->start = start;
          range->stop = i - 1;
        }

        return F_okay_eos;
      }

      if (i + width > source.used) {
        return F_status_set_error(F_complete_not_utf_eos);
      }
    } // for

    return F_data_not_eos;
  }
#endif // !defined(_di_f_serialize_from_simple_get_) || !defined(_di_f_serialize_from_simple_select_)

#ifdef __cplusplus
} // extern "C"
#endif
