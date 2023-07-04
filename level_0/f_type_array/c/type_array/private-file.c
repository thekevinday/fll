#include "../type_array.h"
#include "../type_array_file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_files_adjust_) || !defined(_di_f_files_decimate_by_)
  f_status_t private_f_files_adjust(const f_number_unsigned_t length, f_files_t * const files) {

    const f_status_t status = f_memory_adjust(files->size, length, sizeof(f_file_t), (void **) & files->array);
    if (F_status_is_error(status)) return status;

    files->size = length;

    if (files->used > files->size) {
      files->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_files_adjust_) || !defined(_di_f_files_decimate_by_)

#if !defined(_di_f_files_append_) || !defined(_di_f_filess_append_)
  extern f_status_t private_f_files_append(const f_file_t source, f_files_t * const destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_files_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_files_append_) || !defined(_di_f_filess_append_)

#if !defined(_di_f_files_append_) || !defined(_di_f_files_append_all_) || !defined(_di_f_filess_append_all_)
  extern f_status_t private_f_files_append_all(const f_files_t source, f_files_t * const destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_files_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_files_append_) || !defined(_di_f_files_append_all_) || !defined(_di_f_filess_append_all_)

#if !defined(_di_f_files_append_) || !defined(_di_f_files_append_all_) || !defined(_di_f_files_decrease_by_) || !defined(_di_f_files_increase_) || !defined(_di_f_files_increase_by_) || !defined(_di_f_files_resize_) || !defined(_di_f_filess_append_) || !defined(_di_f_filess_append_all_)
  f_status_t private_f_files_resize(const f_number_unsigned_t length, f_files_t * const files) {

    const f_status_t status = f_memory_resize(files->size, length, sizeof(f_file_t), (void **) & files->array);
    if (F_status_is_error(status)) return status;

    files->size = length;

    if (files->used > files->size) {
      files->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_files_append_) || !defined(_di_f_files_append_all_) || !defined(_di_f_files_decrease_by_) || !defined(_di_f_files_increase_) || !defined(_di_f_files_increase_by_) || !defined(_di_f_files_resize_) || !defined(_di_f_filess_append_) || !defined(_di_f_filess_append_all_)

#if !defined(_di_f_filess_adjust_) || !defined(_di_f_filess_decimate_by_)
  f_status_t private_f_filess_adjust(const f_number_unsigned_t length, f_filess_t * const filess) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < filess->size; ++i) {

      status = f_memory_destroy(filess->array[i].size, sizeof(f_files_t), (void **) & filess->array[i].array);
      if (F_status_is_error(status)) return status;

      filess->array[i].size = 0;
      filess->array[i].used = 0;
    } // for

    status = f_memory_adjust(filess->size, length, sizeof(f_files_t), (void **) & filess->array);
    if (F_status_is_error(status)) return status;

    filess->size = length;

    if (filess->used > filess->size) {
      filess->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_filess_adjust_) || !defined(_di_f_filess_decimate_by_)

#if !defined(_di_f_filess_decrease_by_) || !defined(_di_f_filess_increase_) || !defined(_di_f_filess_increase_by_) || !defined(_di_f_filess_resize_)
  f_status_t private_f_filess_resize(const f_number_unsigned_t length, f_filess_t * const filess) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < filess->size; ++i) {

      status = f_memory_delete(filess->array[i].size, sizeof(f_files_t), (void **) & filess->array[i].array);
      if (F_status_is_error(status)) return status;

      filess->array[i].size = 0;
      filess->array[i].used = 0;
    } // for

    status = f_memory_resize(filess->size, length, sizeof(f_files_t), (void **) & filess->array);
    if (F_status_is_error(status)) return status;

    filess->size = length;

    if (filess->used > filess->size) {
      filess->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_filess_decrease_by_) || !defined(_di_f_filess_increase_) || !defined(_di_f_filess_increase_by_) || !defined(_di_f_filess_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
