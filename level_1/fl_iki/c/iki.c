#include "iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_iki_read_
  void fl_iki_read(f_string_static_t * const buffer, f_string_range_t * const range, f_iki_data_t * const data, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!buffer || !range) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    do {
      f_iki_read(buffer, range, data, state);
      if (F_status_is_error(state->status)) return;

    } while (range->start <= range->stop && range->start < buffer->used);
  }
#endif // _di_fl_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif
