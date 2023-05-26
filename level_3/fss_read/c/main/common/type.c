#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_depth_delete_
  void fss_read_depth_delete(fss_read_depth_t * const depth) {

    if (!depth) return;

    f_string_dynamic_resize(0, &depth->value_name);
  }
#endif // _di_fss_read_depth_delete_

#ifndef _di_fss_read_depths_resize_
  f_status_t fss_read_depths_resize(const f_array_length_t length, fss_read_depths_t * const depths) {

    if (!depths) return F_status_set_error(F_parameter);
    if (depths->used + length > F_array_length_t_size_d) return F_status_set_error(F_array_too_large);

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < depths->size; ++i) {
      fss_read_depth_delete(&depths->array[i]);
    } // for

    status = f_memory_resize(depths->size, length, sizeof(fss_read_file_t), (void **) & depths->array);
    if (F_status_is_error(status)) return status;

    depths->size = length;

    if (depths->used > depths->size) {
      depths->used = length;
    }

    return F_none;
  }
#endif // _di_fss_read_depths_resize_

#ifndef _di_fss_read_files_resize_
  f_status_t fss_read_files_resize(const f_array_length_t length, fss_read_files_t * const files) {

    if (!files) return F_status_set_error(F_parameter);
    if (files->used + length > F_array_length_t_size_d) return F_status_set_error(F_array_too_large);

    const f_status_t status = f_memory_adjust(files->size, length, sizeof(fss_read_file_t), (void **) & files->array);
    if (F_status_is_error(status)) return status;

    files->size = length;

    if (files->used > files->size) {
      files->used = length;
    }

    return F_none;
  }
#endif // _di_fss_read_files_resize_

#ifndef _di_fss_read_main_data_delete_
  void fss_read_main_delete(fss_read_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    fss_read_setting_delete(&main->setting);
  }
#endif // _di_fss_read_main_data_delete_

#ifndef _di_fss_read_setting_delete_
  f_status_t fss_read_setting_delete(fss_read_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    fss_read_files_resize(0, &setting->files);
    fss_read_depths_resize(0, &setting->depths);

    f_string_dynamic_resize(0, &setting->buffer);

    f_string_ranges_resize(0, &setting->objects);
    f_string_ranges_resize(0, &setting->comments);
    f_string_rangess_resize(0, &setting->contents);

    f_fss_nest_resize(0, &setting->nest);

    f_array_lengths_resize(0, &setting->delimits_object);
    f_array_lengths_resize(0, &setting->delimits_content);

    f_uint8s_resize(0, &setting->quotes_object);
    f_uint8ss_resize(0, &setting->quotes_content);

    return F_none;
  }
#endif // _di_fss_read_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
