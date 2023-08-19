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
      const f_status_t status = f_string_dynamic_resize(0, &directory_status->path);
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
      const f_status_t status = f_string_dynamic_adjust(0, &directory_status->path);
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

        status = f_string_dynamic_resize(0, &array[i].path);
        if (F_status_is_error(status)) return status;
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

        status = f_string_dynamic_adjust(0, &array[i].path);
        if (F_status_is_error(status)) return status;
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

          status = f_string_dynamic_resize(0, &array[i].array[j].path);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
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

          status = f_string_dynamic_adjust(0, &array[i].array[j].path);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
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
