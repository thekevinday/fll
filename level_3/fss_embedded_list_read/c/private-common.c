#include "fss_embedded_list_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_read_data_delete_
  f_status_t fss_embedded_list_read_data_delete(fss_embedded_list_read_data_t * const data) {

    f_fss_nest_resize(0, &data->nest);
    f_string_dynamic_resize(0, &data->buffer);

    return F_none;
  }
#endif // _di_fss_embedded_list_read_data_delete_

#ifndef _di_fss_embedded_list_read_data_delete_
  f_status_t fss_embedded_list_read_depth_delete(fss_embedded_list_read_depth_t * const depth) {

    f_string_dynamic_resize(0, &depth->value_name);

    return F_none;
  }
#endif // _di_fss_embedded_list_read_data_delete_

#ifndef _di_fss_embedded_list_read_depths_resize_
  f_status_t fss_embedded_list_read_depths_resize(const f_number_unsigned_t length, fss_embedded_list_read_depths_t *depths) {

    if (!depths) {
      return F_status_set_error(F_parameter);
    }

    for (f_number_unsigned_t i = length; i < depths->size; ++i) {
      fss_embedded_list_read_depth_delete(&depths->array[i]);
    } // for

    const f_status_t status = f_memory_resize(depths->size, length, sizeof(fss_embedded_list_read_depth_t), (void **) & depths->array);
    if (F_status_is_error(status)) return status;

    depths->size = length;

    if (depths->used > depths->size) {
      depths->used = length;
    }

    return F_none;
  }
#endif // _di_fss_embedded_list_read_depths_resize_

#ifdef __cplusplus
} // extern "C"
#endif
