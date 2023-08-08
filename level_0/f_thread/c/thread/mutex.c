#include "../thread.h"
#include "mutex.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_thread_mutexs_adjust_
  f_status_t f_thread_mutexs_adjust(const f_number_unsigned_t length, f_thread_mutexs_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      int error = 0;

      for (f_number_unsigned_t i = length; i < structure->size; ++i) {

        error = pthread_mutex_destroy(&structure->array[i]);

        if (error) {
          if (error == EBUSY) return F_status_set_error(F_busy);
          if (error == EINVAL) return F_status_set_error(F_parameter);

          return F_status_set_error(F_failure);
        }
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_thread_mutex_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_mutexs_adjust_

#ifndef _di_f_thread_mutexs_decimate_by_
  f_status_t f_thread_mutexs_decimate_by(const f_number_unsigned_t amount, f_thread_mutexs_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    const f_number_unsigned_t length = (structure->size > amount) ? structure->size - amount : 0;

    {
      int error = 0;

      for (f_number_unsigned_t i = length; i < structure->size; ++i) {

        error = pthread_mutex_destroy(&structure->array[i]);

        if (error) {
          if (error == EBUSY) return F_status_set_error(F_busy);
          if (error == EINVAL) return F_status_set_error(F_parameter);

          return F_status_set_error(F_failure);
        }
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_thread_mutex_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_mutexs_decimate_by_

#ifndef _di_f_thread_mutexs_decrease_by_
  f_status_t f_thread_mutexs_decrease_by(const f_number_unsigned_t amount, f_thread_mutexs_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    const f_number_unsigned_t length = (structure->size > amount) ? structure->size - amount : 0;

    {
      int error = 0;

      for (f_number_unsigned_t i = length; i < structure->size; ++i) {

        error = pthread_mutex_destroy(&structure->array[i]);

        if (error) {
          if (error == EBUSY) return F_status_set_error(F_busy);
          if (error == EINVAL) return F_status_set_error(F_parameter);

          return F_status_set_error(F_failure);
        }
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_thread_mutex_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_mutexs_decrease_by_

#ifndef _di_f_thread_mutexs_increase_
  f_status_t f_thread_mutexs_increase(const f_number_unsigned_t step, f_thread_mutexs_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      {
        int error = 0;

        for (f_number_unsigned_t i = length; i < structure->size; ++i) {

          error = pthread_mutex_destroy(&structure->array[i]);

          if (error) {
            if (error == EBUSY) return F_status_set_error(F_busy);
            if (error == EINVAL) return F_status_set_error(F_parameter);

            return F_status_set_error(F_failure);
          }
        } // for
      }

      return f_memory_array_resize(length, sizeof(f_thread_mutex_t), (void **) &structure->array, &structure->used, &structure->size);
    }

    return F_data_not;
  }
#endif // _di_f_thread_mutexs_increase_

#ifndef _di_f_thread_mutexs_increase_by_
  f_status_t f_thread_mutexs_increase_by(const f_number_unsigned_t amount, f_thread_mutexs_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        {
          int error = 0;

          for (f_number_unsigned_t i = length; i < structure->size; ++i) {

            error = pthread_mutex_destroy(&structure->array[i]);

            if (error) {
              if (error == EBUSY) return F_status_set_error(F_busy);
              if (error == EINVAL) return F_status_set_error(F_parameter);

              return F_status_set_error(F_failure);
            }
          } // for
        }

        return f_memory_array_resize(length, sizeof(f_thread_mutex_t), (void **) &structure->array, &structure->used, &structure->size);
      }
    }

    return F_data_not;
  }
#endif // _di_f_thread_mutexs_increase_by_

#ifndef _di_f_thread_mutexs_resize_
  f_status_t f_thread_mutexs_resize(const f_number_unsigned_t length, f_thread_mutexs_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      int error = 0;

      for (f_number_unsigned_t i = length; i < structure->size; ++i) {

        error = pthread_mutex_destroy(&structure->array[i]);

        if (error) {
          if (error == EBUSY) return F_status_set_error(F_busy);
          if (error == EINVAL) return F_status_set_error(F_parameter);

          return F_status_set_error(F_failure);
        }
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_thread_mutex_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_thread_mutexs_resize_

#ifdef __cplusplus
} // extern "C"
#endif
