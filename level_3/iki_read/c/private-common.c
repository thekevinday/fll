#include "iki_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_data_delete_
  f_status_t iki_read_data_delete(fll_program_data_t * const main, status_code_setting_t * const setting, iki_read_data_t * const data) {

    f_string_dynamic_resize(0, &data->buffer);

    return F_none;
  }
#endif // _di_iki_read_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif
