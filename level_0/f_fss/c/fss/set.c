#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_set_delete_
  f_status_t f_fss_set_delete(f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_string_ranges_resize(0, &set->objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_resize(0, &set->contents);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_fss_set_delete_

#ifndef _di_f_fss_set_destroy_
  f_status_t f_fss_set_destroy(f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_string_ranges_adjust(0, &set->objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_adjust(0, &set->contents);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_fss_set_destroy_

#ifndef _di_f_fss_sets_delete_callback_
  f_status_t f_fss_sets_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_set_t * const array = (f_fss_set_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_ranges_resize(0, &array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_resize(0, &array[i].contents);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_sets_delete_callback_

#ifndef _di_f_fss_sets_destroy_callback_
  f_status_t f_fss_sets_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_set_t * const array = (f_fss_set_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_ranges_adjust(0, &array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_adjust(0, &array[i].contents);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_sets_destroy_callback_

#ifndef _di_f_fss_setss_delete_callback_
  f_status_t f_fss_setss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_sets_t * const array = (f_fss_sets_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_ranges_resize(0, &array[i].array[j].objects);
          if (F_status_is_error(status)) return status;

          status = f_string_rangess_resize(0, &array[i].array[j].contents);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_fss_set_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_setss_delete_callback_

#ifndef _di_f_fss_setss_destroy_callback_
  f_status_t f_fss_setss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_sets_t * const array = (f_fss_sets_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_ranges_adjust(0, &array[i].array[j].objects);
          if (F_status_is_error(status)) return status;

          status = f_string_rangess_adjust(0, &array[i].array[j].contents);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_fss_set_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_setss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
