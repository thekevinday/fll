#include "../thread.h"
#include "semaphore.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_semaphores_delete_callback_
  f_status_t f_thread_semaphores_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_semaphore_t * const array = (f_thread_semaphore_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        if (sem_destroy(&array[i]) == -1) return (errno == EINVAL) ? F_status_set_error(F_parameter) : F_status_set_error(F_failure);
      } // for
    }

    return F_okay;
  }
#endif // _di_f_thread_semaphores_delete_callback_

#ifndef _di_f_thread_semaphores_destroy_callback_
  f_status_t f_thread_semaphores_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_semaphore_t * const array = (f_thread_semaphore_t *) void_array;

      for (f_number_unsigned_t i = start; i < stop; ++i) {
        if (sem_destroy(&array[i]) == -1) return (errno == EINVAL) ? F_status_set_error(F_parameter) : F_status_set_error(F_failure);
      } // for
    }

    return F_okay;
  }
#endif // _di_f_thread_semaphores_destroy_callback_

#ifndef _di_f_thread_semaphoress_delete_callback_
  f_status_t f_thread_semaphoress_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_semaphores_t * const array = (f_thread_semaphores_t *) void_array;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {
          if (sem_destroy(&array[i].array[j]) == -1) return (errno == EINVAL) ? F_status_set_error(F_parameter) : F_status_set_error(F_failure);
        } // for

        if (array[i].size) {
          const f_status_t status = f_memory_array_resize(0, sizeof(f_thread_semaphore_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_thread_semaphoress_delete_callback_

#ifndef _di_f_thread_semaphoress_destroy_callback_
  f_status_t f_thread_semaphoress_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_thread_semaphores_t * const array = (f_thread_semaphores_t *) void_array;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {
          if (sem_destroy(&array[i].array[j]) == -1) return (errno == EINVAL) ? F_status_set_error(F_parameter) : F_status_set_error(F_failure);
        } // for

        if (array[i].size) {
          const f_status_t status = f_memory_array_resize(0, sizeof(f_thread_semaphore_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_thread_semaphoress_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
