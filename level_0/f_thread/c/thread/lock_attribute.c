#include "../thread.h"
#include "lock_attribute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_lock_attributes_delete_callback_
  f_status_t f_thread_lock_attributes_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_lock_attribute_t * const array = (f_thread_lock_attribute_t *) void_array;
      int error = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        error = pthread_rwlockattr_destroy(&array[i]);

        if (error) {
          if (error == EBUSY) return F_status_set_error(F_busy);
          if (error == EINVAL) return F_status_set_error(F_parameter);

          return F_status_set_error(F_failure);
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_lock_attributes_delete_callback_

#ifndef _di_f_thread_lock_attributes_destroy_callback_
  f_status_t f_thread_lock_attributes_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_lock_attribute_t * const array = (f_thread_lock_attribute_t *) void_array;
      int error = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        error = pthread_rwlockattr_destroy(&array[i]);

        if (error) {
          if (error == EBUSY) return F_status_set_error(F_busy);
          if (error == EINVAL) return F_status_set_error(F_parameter);

          return F_status_set_error(F_failure);
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_lock_attributes_destroy_callback_

#ifndef _di_f_thread_lock_attributess_delete_callback_
  f_status_t f_thread_lock_attributess_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_lock_attributes_t * const array = (f_thread_lock_attributes_t *) void_array;
      int error = 0;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          error = pthread_rwlockattr_destroy(&array[i].array[j]);

          if (error) {
            if (error == EBUSY) return F_status_set_error(F_busy);
            if (error == EINVAL) return F_status_set_error(F_parameter);

            return F_status_set_error(F_failure);
          }
        } // for

        if (array[i].size) {
          const f_status_t status = f_memory_array_resize(0, sizeof(f_thread_lock_attribute_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_lock_attributess_delete_callback_

#ifndef _di_f_thread_lock_attributess_destroy_callback_
  f_status_t f_thread_lock_attributess_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_lock_attributes_t * const array = (f_thread_lock_attributes_t *) void_array;
      int error = 0;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          error = pthread_rwlockattr_destroy(&array[i].array[j]);

          if (error) {
            if (error == EBUSY) return F_status_set_error(F_busy);
            if (error == EINVAL) return F_status_set_error(F_parameter);

            return F_status_set_error(F_failure);
          }
        } // for

        if (array[i].size) {
          const f_status_t status = f_memory_array_adjust(0, sizeof(f_thread_lock_attribute_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_thread_lock_attributess_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
