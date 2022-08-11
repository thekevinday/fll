#include "utf8.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_data_delete_
  void utf8_data_delete(utf8_data_t *data) {

    f_string_dynamic_resize(0, &data->buffer);
    f_string_dynamic_resize(0, &data->text);
  }
#endif // _di_utf8_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif
