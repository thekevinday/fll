#include "../directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_status_delete_
  f_status_t f_directory_status_delete(f_directory_status_t * const directory_status) {
    #ifndef _di_level_0_parameter_checking_
      if (!directory_status) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &directory_status->path.string, &directory_status->path.used, &directory_status->path.size);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_directory_status_delete_

#ifndef _di_f_directory_status_destroy_
  f_status_t f_directory_status_destroy(f_directory_status_t * const directory_status) {
    #ifndef _di_level_0_parameter_checking_
      if (!directory_status) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &directory_status->path.string, &directory_status->path.used, &directory_status->path.size);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_directory_status_destroy_

#ifndef _di_f_directory_statuss_delete_callback_
  f_status_t f_directory_statuss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_status_t * const array = (f_directory_status_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].path.size && array[i].path.string) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].path.string, &array[i].path.used, &array[i].path.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_statuss_delete_callback_

#ifndef _di_f_directory_statuss_destroy_callback_
  f_status_t f_directory_statuss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_status_t * const array = (f_directory_status_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].path.size && array[i].path.string) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].path.string, &array[i].path.used, &array[i].path.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_statuss_destroy_callback_

#ifndef _di_f_directory_statusss_delete_callback_
  f_status_t f_directory_statusss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_statuss_t * const array = (f_directory_statuss_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          if (array[i].array[j].path.size && array[i].array[j].path.string) {
            status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].path.string, &array[i].array[j].path.used, &array[i].array[j].path.size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].array) {
          status = f_memory_array_resize(0, sizeof(f_directory_status_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_statusss_delete_callback_

#ifndef _di_f_directory_statusss_destroy_callback_
  f_status_t f_directory_statusss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_statuss_t * const array = (f_directory_statuss_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          if (array[i].array[j].path.size && array[i].array[j].path.string) {
            status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].path.string, &array[i].array[j].path.used, &array[i].array[j].path.size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].array) {
          status = f_memory_array_adjust(0, sizeof(f_directory_status_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_statusss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
