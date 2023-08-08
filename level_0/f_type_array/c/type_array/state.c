#include "../type_array.h"
#include "state.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_states_adjust_callback_
  f_status_t f_states_adjust_callback(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const void_array) {

    {
      f_states_t * const array = (f_states_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < size; ++i) {

        status = f_memory_array_adjust(0, sizeof(f_state_t), (void **) &array[i].array, &array[i].used, &array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_states_adjust_callback_

#ifndef _di_f_states_resize_callback_
  f_status_t f_states_resize_callback(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const void_array) {

    {
      f_states_t * const array = (f_states_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < size; ++i) {

        status = f_memory_array_resize(0, sizeof(f_state_t), (void **) &array[i].array, &array[i].used, &array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_states_resize_callback_

#ifdef __cplusplus
} // extern "C"
#endif
