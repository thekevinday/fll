#include "../thread.h"
#include "key.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_keys_delete_callback_
  f_status_t f_thread_keys_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_key_t * const array = (f_thread_key_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (pthread_key_delete(array[i])) return F_status_set_error(F_failure);

        array[i] = 0;
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_keys_delete_callback_

#ifndef _di_f_thread_keys_destroy_callback_
  f_status_t f_thread_keys_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_key_t * const array = (f_thread_key_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (pthread_key_delete(array[i])) return F_status_set_error(F_failure);

        array[i] = 0;
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_keys_destroy_callback_

#ifndef _di_f_thread_keyss_delete_callback_
  f_status_t f_thread_keyss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_keys_t * const array = (f_thread_keys_t *) void_array;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          if (pthread_key_delete(array[i].array[j])) return F_status_set_error(F_failure);

          array[i].array[j] = 0;
        } // for

        if (array[i].size) {
          const f_status_t status = f_memory_array_resize(0, sizeof(f_thread_key_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_keyss_delete_callback_

#ifndef _di_f_thread_keyss_destroy_callback_
  f_status_t f_thread_keyss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_keys_t * const array = (f_thread_keys_t *) void_array;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          if (pthread_key_delete(array[i].array[j])) return F_status_set_error(F_failure);

          array[i].array[j] = 0;
        } // for

        if (array[i].size) {
          const f_status_t status = f_memory_array_adjust(0, sizeof(f_thread_key_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_keyss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
