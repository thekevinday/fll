#include "../thread.h"
#include "set.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_sets_adjust_callback_
  f_status_t f_thread_sets_adjust_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_sets_t * const array = (f_thread_sets_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        if (pthread_attr_destroy(&array->array[i].attribute)) return F_status_set_error(F_failure);
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_sets_adjust_callback_

#ifndef _di_f_thread_sets_resize_callback_
  f_status_t f_thread_sets_resize_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_sets_t * const array = (f_thread_sets_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        if (pthread_attr_destroy(&array->array[i].attribute)) return F_status_set_error(F_failure);
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_sets_resize_callback_

#ifdef __cplusplus
} // extern "C"
#endif
