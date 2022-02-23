#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_iki_datas_adjust_) || !defined(_di_f_iki_datas_decimate_by_)
  f_status_t private_f_iki_datas_adjust(const f_array_length_t length, f_iki_datas_t *datas) {

    if (datas->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < datas->size; ++i) {

      status = f_string_ranges_adjust(0, &datas->array[i].content);
      if (F_status_is_error(status)) return status;

      status = f_array_lengths_adjust(0, &datas->array[i].delimits);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_adjust(0, &datas->array[i].variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_adjust(0, &datas->array[i].vocabulary);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(datas->size, length, sizeof(f_iki_data_t), (void **) & datas->array);

    if (F_status_is_error_not(status)) {
      datas->size = length;

      if (datas->used > datas->size) {
        datas->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_iki_datas_adjust_) || !defined(_di_f_iki_datas_decimate_by_)

#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_decrease_by_) || !defined(_di_f_iki_datas_increase_) || !defined(_di_f_iki_datas_increase_by_) || !defined(_di_f_iki_datas_resize_)
  f_status_t private_f_iki_datas_resize(const f_array_length_t length, f_iki_datas_t *datas) {

    if (datas->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < datas->size; ++i) {

      status = f_string_ranges_resize(0, &datas->array[i].content);
      if (F_status_is_error(status)) return status;

      status = f_array_lengths_resize(0, &datas->array[i].delimits);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_resize(0, &datas->array[i].variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_resize(0, &datas->array[i].vocabulary);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(datas->size, length, sizeof(f_iki_data_t), (void **) & datas->array);

    if (F_status_is_error_not(status)) {
      datas->size = length;

      if (datas->used > datas->size) {
        datas->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_decrease_by_) || !defined(_di_f_iki_datas_increase_) || !defined(_di_f_iki_datas_increase_by_) || !defined(_di_f_iki_datas_resize_)

#if !defined(_di_f_iki_read_)
  f_status_t private_f_iki_seek_special(const f_string_static_t buffer, f_string_range_t * const range) {

    f_status_t status = F_none;
    f_array_length_t width_max = 0;

    while (range->start <= range->stop && range->start < buffer.used) {

      if (buffer.string[range->start] == f_iki_syntax_separator_s.string[0]) {
        break;
      }

      if (buffer.string[range->start] == f_iki_syntax_quote_double_s.string[0]) {
        break;
      }

      if (buffer.string[range->start] == f_iki_syntax_quote_single_s.string[0]) {
        break;
      }

      if (buffer.string[range->start] == f_iki_syntax_slash_s.string[0]) {
        break;
      }

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }

      status = f_utf_is_word_dash_plus(buffer.string + range->start, width_max, F_false);
      if (F_status_is_error(status)) return status;
      if (status == F_true) return status;

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    return F_false;
  }
#endif // !defined(_di_f_iki_read_)

#if !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)
  f_status_t private_f_iki_content_partial_is(const f_string_static_t buffer, const f_string_range_t range, const char quote) {

    f_array_length_t delimits = 0;

    for (f_array_length_t i = 0; i < buffer.used; ++i) {

      if (buffer.string[i] == quote) {
        if (delimits && delimits % 2) {
          delimits = 0;

          continue;
        }

        return F_false;
      }
      else if (buffer.string[i] == f_iki_syntax_slash_s.string[0]) {
        ++delimits;
      }
      else {
        delimits = 0;
      }
    } // for

    return F_true;
  }
#endif // !defined(_di_f_iki_content_is_) || !defined(_di_f_iki_content_partial_is_)

#if !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)
  f_status_t private_f_iki_object_partial_is(const f_string_static_t buffer, const f_string_range_t range) {

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < buffer.used; ++i) {

      status = f_utf_is_word(buffer.string + i, buffer.used - i, F_false);
      if (F_status_is_error(status)) return status;

      if (status == F_false) return F_false;
    } // for

    return F_true;
  }
#endif // !defined(_di_f_iki_object_is_) || !defined(_di_f_iki_object_partial_is_)

#ifdef __cplusplus
} // extern "C"
#endif
