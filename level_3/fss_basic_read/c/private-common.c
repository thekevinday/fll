#include "fss_basic_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_depth_delete_simple_
  void fss_basic_read_depth_delete_simple(fss_basic_read_depth_t *depth) {

    if (!depth) return;

    f_string_dynamic_resize(0, &depth->value_name);
  }
#endif // _di_fss_basic_read_depth_delete_simple_


#ifndef _di_fss_basic_read_depths_resize_
  f_status_t fss_basic_read_depths_resize(const f_array_length_t length, fss_basic_read_depths_t *depths) {

    if (!depths) return F_status_set_error(F_parameter);

    for (f_array_length_t i = length; i < depths->size; ++i) {
      fss_basic_read_depth_delete_simple(&depths->array[i]);
    } // for

    const f_status_t status = f_memory_resize(depths->size, length, sizeof(fss_basic_read_depth_t), (void **) & depths->array);

    if (F_status_is_error_not(status)) {
      depths->size = length;

      if (depths->used > depths->size) {
        depths->used = length;
      }
    }

    return status;
  }
#endif // _di_fss_basic_read_depths_resize_

#ifdef __cplusplus
} // extern "C"
#endif
