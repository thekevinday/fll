#include "iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_iki_read_
  f_status_t fl_iki_read(const f_state_t state, f_string_static_t * const buffer, f_string_range_t * const range, f_iki_data_t * const data) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    do {
      status = f_iki_read(state, buffer, range, data);
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
