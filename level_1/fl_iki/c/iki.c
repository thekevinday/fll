#include <level_1/iki.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_iki_read_
  f_return_status fl_iki_read(f_string_static *buffer, f_string_range *range, f_iki_variable *variable, f_iki_vocabulary *vocabulary, f_iki_content *content) {
    f_status status = F_none;

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
