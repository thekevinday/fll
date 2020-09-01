#include "iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_iki_read_
  f_return_status fl_iki_read(f_string_static_t *buffer, f_string_range_t *range, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content) {
    f_status_t status = F_none;

    do {
      status = f_iki_read(buffer, range, variable, vocabulary, content);
      if (F_status_is_error(status)) return status;

      if (status == F_data_not_eos || status == F_data_not_stop) {
        return status;
      }

      if (status == F_none_eos || status == F_none_stop) {
        return status;
      }
    } while (range->start <= range->stop && range->start < buffer->used);

    return F_none;
  }
#endif // _di_fl_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif
