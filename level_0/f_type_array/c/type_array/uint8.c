#include "../type_array.h"
#include "uint8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_uint8s_adjust_callback_
  f_status_t f_uint8s_adjust_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_uint8s_t * const array = (f_uint8s_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_adjust(0, sizeof(uint8_t), (void **) &array[i].array, &array[i].used, &array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_uint8s_adjust_callback_

#ifndef _di_f_uint8s_resize_callback_
  f_status_t f_uint8s_resize_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_uint8s_t * const array = (f_uint8s_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_resize(0, sizeof(uint8_t), (void **) &array[i].array, &array[i].used, &array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_uint8s_resize_callback_

#ifdef __cplusplus
} // extern "C"
#endif
