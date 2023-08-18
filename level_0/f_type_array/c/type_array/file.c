#include "../type_array.h"
#include "../type_array_file.h"
#include "file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_filess_delete_callback_
  f_status_t f_filess_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_files_t * const array = (f_files_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_file_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_filess_delete_callback_

#ifndef _di_f_filess_destroy_callback_
  f_status_t f_filess_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_files_t * const array = (f_files_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_file_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_filess_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
