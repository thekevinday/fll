#include "fss_payload_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_read_data_delete_simple_
  void fss_payload_read_data_delete_simple(fss_payload_read_data_t *data) {

    if (!data) return;

    // data->files is expected to be statically loaded and cannot be deallocated.

    fss_payload_read_depths_resize(0, &data->depths);

    f_string_dynamic_resize(0, &data->buffer);
    macro_f_fss_contents_t_delete_simple(data->contents);
    macro_f_fss_contents_t_delete_simple(data->contents_header);
    macro_f_fss_objects_t_delete_simple(data->objects);
    macro_f_fss_objects_t_delete_simple(data->objects_header);
    macro_f_uint8s_t_delete_simple(data->quotes_object_header);
    macro_f_uint8ss_t_delete_simple(data->quotes_content_header);
    macro_f_fss_delimits_t_delete_simple(data->delimits_object);
    macro_f_fss_delimits_t_delete_simple(data->delimits_object_header);
    macro_f_fss_delimits_t_delete_simple(data->delimits_content);
    macro_f_fss_delimits_t_delete_simple(data->delimits_content_header);
    macro_f_fss_comments_t_delete_simple(data->comments);
  }
#endif // _di_fss_payload_read_data_delete_simple_

#ifndef _di_fss_payload_read_depth_delete_simple_
  void fss_payload_read_depth_delete_simple(fss_payload_read_depth_t *depth) {

    if (!depth) return;

    f_string_dynamic_resize(0, &depth->value_name);
  }
#endif // _di_fss_payload_read_depth_delete_simple_

#ifndef _di_fss_payload_read_depths_resize_
  f_status_t fss_payload_read_depths_resize(const f_array_length_t length, fss_payload_read_depths_t *depths) {

    if (!depths) {
      return F_status_set_error(F_parameter);
    }

    for (f_array_length_t i = length; i < depths->size; ++i) {
      fss_payload_read_depth_delete_simple(&depths->array[i]);
    } // for

    const f_status_t status = f_memory_resize(depths->size, length, sizeof(fss_payload_read_depth_t), (void **) & depths->array);
    if (F_status_is_error(status)) return status;

    depths->size = length;

    if (depths->used > depths->size) {
      depths->used = length;
    }

    return F_none;
  }
#endif // _di_fss_payload_read_depths_resize_

#ifdef __cplusplus
} // extern "C"
#endif
