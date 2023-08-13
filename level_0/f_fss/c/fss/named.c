#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_named_delete_
  f_status_t f_fss_named_delete(f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_string_ranges_resize(0, &named->objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_resize(0, &named->contents);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(uint8_t), (void **) &named->quotess.array, &named->quotess.used, &named->quotess.size, &f_uint8ss_delete_callback);
      if (F_status_is_error(status)) return status;
    }

    return F_none;
  }
#endif // _di_f_fss_named_delete_

#ifndef _di_f_fss_named_destroy_
  f_status_t f_fss_named_destroy(f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    named->name.start = 1;
    named->name.stop = 0;

    {
      f_status_t status = f_string_ranges_adjust(0, &named->objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_adjust(0, &named->contents);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(uint8_t), (void **) &named->quotess.array, &named->quotess.used, &named->quotess.size, &f_uint8ss_destroy_callback);
      if (F_status_is_error(status)) return status;
    }

    return F_none;
  }
#endif // _di_f_fss_named_destroy_

#ifndef _di_f_fss_nameds_delete_callback_
  f_status_t f_fss_nameds_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_named_t * const array = (f_fss_named_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_ranges_resize(0, &array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_resize(0, &array[i].contents);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(uint8_t), (void **) &array[i].quotess.array, &array[i].quotess.used, &array[i].quotess.size, &f_uint8ss_delete_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_nameds_delete_callback_

#ifndef _di_f_fss_nameds_destroy_callback_
  f_status_t f_fss_nameds_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_named_t * const array = (f_fss_named_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        array[i].name.start = 1;
        array[i].name.stop = 0;

        status = f_string_ranges_adjust(0, &array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_adjust(0, &array[i].contents);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(uint8_t), (void **) &array[i].quotess.array, &array[i].quotess.used, &array[i].quotess.size, &f_uint8ss_destroy_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_nameds_destroy_callback_

#ifndef _di_f_fss_namedss_delete_callback_
  f_status_t f_fss_namedss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_nameds_t * const array = (f_fss_nameds_t *) void_array;
      f_status_t status = F_none;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_ranges_resize(0, &array[i].array[j].objects);
          if (F_status_is_error(status)) return status;

          status = f_string_rangess_resize(0, &array[i].array[j].contents);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(uint8_t), (void **) &array[i].array[j].quotess.array, &array[i].array[j].quotess.used, &array[i].array[j].quotess.size, &f_uint8ss_delete_callback);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_fss_named_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_namedss_delete_callback_

#ifndef _di_f_fss_namedss_destroy_callback_
  f_status_t f_fss_namedss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_nameds_t * const array = (f_fss_nameds_t *) void_array;
      f_status_t status = F_none;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          array[i].array[j].name.start = 1;
          array[i].array[j].name.stop = 0;

          status = f_string_ranges_adjust(0, &array[i].array[j].objects);
          if (F_status_is_error(status)) return status;

          status = f_string_rangess_adjust(0, &array[i].array[j].contents);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(uint8_t), (void **) &array[i].array[j].quotess.array, &array[i].array[j].quotess.used, &array[i].array[j].quotess.size, &f_uint8ss_destroy_callback);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_fss_named_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_namedss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
