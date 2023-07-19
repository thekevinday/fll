#include "../directory.h"
#include "private-type.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_directory_statuss_adjust_) || !defined(_di_f_directory_statuss_decimate_by_)
  f_status_t private_f_directory_statuss_adjust(const f_number_unsigned_t length, f_directory_statuss_t * const statuss) {

    {
      f_status_t status = F_none;

      for (f_number_unsigned_t i = length; i < statuss->size; ++i) {

        status = f_string_dynamic_adjust(0, &statuss->array[i].path);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_directory_status_t), (void **) &statuss->array, &statuss->used, &statuss->size);
  }
#endif // !defined(_di_f_directory_statuss_adjust_) || !defined(_di_f_directory_statuss_decimate_by_)

#if !defined(_di_f_directory_statuss_decrease_by_) || !defined(_di_f_directory_statuss_resize_)
  f_status_t private_f_directory_statuss_resize(const f_number_unsigned_t length, f_directory_statuss_t * const statuss) {

    {
      f_status_t status = F_none;

      for (f_number_unsigned_t i = length; i < statuss->size; ++i) {

        status = f_string_dynamic_resize(0, &statuss->array[i].path);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_directory_status_t), (void **) &statuss->array, &statuss->used, &statuss->size);
  }
#endif // !defined(_di_f_directory_statuss_decrease_by_) || !defined(_di_f_directory_statuss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
