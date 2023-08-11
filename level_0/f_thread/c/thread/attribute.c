#include "../thread.h"
#include "attribute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_attributes_adjust_callback_
  f_status_t f_thread_attributes_adjust_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_attributes_t * const array = (f_thread_attributes_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        if (pthread_attr_destroy(&array->array[i])) return F_status_set_error(F_failure);
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_attributes_adjust_callback_

#ifndef _di_f_thread_attributes_resize_callback_
  f_status_t f_thread_attributes_resize_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_attributes_t * const array = (f_thread_attributes_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        if (pthread_attr_destroy(&array->array[i])) return F_status_set_error(F_failure);
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_attributes_resize_callback_

#ifdef __cplusplus
} // extern "C"
#endif
