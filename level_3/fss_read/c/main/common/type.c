#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_depth_delete_
  void fss_read_depth_delete(fss_read_depth_t * const depth) {

    if (!depth) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &depth->value_name.string, &depth->value_name.used, &depth->value_name.size);
  }
#endif // _di_fss_read_depth_delete_

#ifndef _di_fss_read_depths_resize_
  f_status_t fss_read_depths_resize(const f_number_unsigned_t length, fss_read_depths_t * const depths) {

    if (!depths) return F_status_set_error(F_parameter);
    if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);
    if (depths->used + length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    for (f_number_unsigned_t i = length; i < depths->size; ++i) {
      fss_read_depth_delete(&depths->array[i]);
    } // for

    const f_status_t status = f_memory_resize(depths->size, length, sizeof(fss_read_depth_t), (void **) & depths->array);
    if (F_status_is_error(status)) return status;

    depths->size = length;

    if (depths->used > depths->size) {
      depths->used = length;
    }

    return F_okay;
  }
#endif // _di_fss_read_depths_resize_

#ifndef _di_fss_read_files_resize_
  f_status_t fss_read_files_resize(const f_number_unsigned_t length, fss_read_files_t * const files) {

    if (!files) return F_status_set_error(F_parameter);
    if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);
    if (files->used + length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    const f_status_t status = f_memory_adjust(files->size, length, sizeof(fss_read_file_t), (void **) & files->array);
    if (F_status_is_error(status)) return status;

    files->size = length;

    if (files->used > files->size) {
      files->used = length;
    }

    return F_okay;
  }
#endif // _di_fss_read_files_resize_

#ifndef _di_fss_read_main_delete_
  void fss_read_main_delete(fss_read_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    fss_read_setting_delete(&main->setting);
  }
#endif // _di_fss_read_main_delete_

#ifndef _di_fss_read_setting_delete_
  void fss_read_setting_delete(fss_read_setting_t * const setting) {

    if (!setting) return;

    fss_read_files_resize(0, &setting->files);
    fss_read_depths_resize(0, &setting->depths);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->buffer.string, &setting->buffer.used, &setting->buffer.size);

    f_memory_array_resize(0, sizeof(f_range_t), (void **) &setting->objects.array, &setting->objects.used, &setting->objects.size);
    f_memory_array_resize(0, sizeof(f_range_t), (void **) &setting->comments.array, &setting->comments.used, &setting->comments.size);
    f_memory_arrays_resize(0, sizeof(f_ranges_t), (void **) &setting->contents.array, &setting->contents.used, &setting->contents.size, &f_rangess_delete_callback);

    f_fss_nest_delete(&setting->nest);

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &setting->delimits_object.array, &setting->delimits_object.used, &setting->delimits_object.size);
    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &setting->delimits_content.array, &setting->delimits_content.used, &setting->delimits_content.size);

    f_memory_array_resize(0, sizeof(uint8_t), (void **) &setting->quotes_object.array, &setting->quotes_object.used, &setting->quotes_object.size);
    f_memory_arrays_resize(0, sizeof(f_uint8s_t), (void **) &setting->quotes_content.array, &setting->quotes_content.used, &setting->quotes_content.size, &f_uint8ss_delete_callback);
  }
#endif // _di_fss_read_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
