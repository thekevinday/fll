#include "fss_identify.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_data_delete_
  void fss_identify_data_delete(fss_identify_data_t *data) {

    if (!data) return;

    f_string_dynamic_resize(0, &data->name);
  }
#endif // _di_fss_identify_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif
