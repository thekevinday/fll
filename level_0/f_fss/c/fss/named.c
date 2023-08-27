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
      f_status_t status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &named->objects.array, &named->objects.used, &named->objects.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_ranges_t), (void **) &named->contents.array, &named->contents.used, &named->contents.size, &f_string_rangess_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_uint8s_t), (void **) &named->quotess.array, &named->quotess.used, &named->quotess.size, &f_uint8ss_delete_callback);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_fss_named_delete_

#ifndef _di_f_fss_named_destroy_
  f_status_t f_fss_named_destroy(f_fss_named_t * const named) {
    #ifndef _di_level_0_parameter_checking_
      if (!named) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &named->objects.array, &named->objects.used, &named->objects.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_ranges_t), (void **) &named->contents.array, &named->contents.used, &named->contents.size, &f_string_rangess_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_uint8s_t), (void **) &named->quotess.array, &named->quotess.used, &named->quotess.size, &f_uint8ss_destroy_callback);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_fss_named_destroy_

#ifndef _di_f_fss_nameds_delete_callback_
  f_status_t f_fss_nameds_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_named_t * const array = (f_fss_named_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &array[i].objects.array, &array[i].objects.used, &array[i].objects.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_ranges_t), (void **) &array[i].contents.array, &array[i].contents.used, &array[i].contents.size, &f_string_rangess_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_uint8s_t), (void **) &array[i].quotess.array, &array[i].quotess.used, &array[i].quotess.size, &f_uint8ss_delete_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_nameds_delete_callback_

#ifndef _di_f_fss_nameds_destroy_callback_
  f_status_t f_fss_nameds_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_named_t * const array = (f_fss_named_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &array[i].objects.array, &array[i].objects.used, &array[i].objects.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_ranges_t), (void **) &array[i].contents.array, &array[i].contents.used, &array[i].contents.size, &f_string_rangess_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_uint8s_t), (void **) &array[i].quotess.array, &array[i].quotess.used, &array[i].quotess.size, &f_uint8ss_destroy_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_nameds_destroy_callback_

#ifndef _di_f_fss_namedss_delete_callback_
  f_status_t f_fss_namedss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_nameds_t * const array = (f_fss_nameds_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &array[i].array[j].objects.array, &array[i].array[j].objects.used, &array[i].array[j].objects.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_ranges_t), (void **) &array[i].array[j].contents.array, &array[i].array[j].contents.used, &array[i].array[j].contents.size, &f_string_rangess_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_uint8s_t), (void **) &array[i].array[j].quotess.array, &array[i].array[j].quotess.used, &array[i].array[j].quotess.size, &f_uint8ss_delete_callback);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_fss_named_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_namedss_delete_callback_

#ifndef _di_f_fss_namedss_destroy_callback_
  f_status_t f_fss_namedss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_nameds_t * const array = (f_fss_nameds_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &array[i].array[j].objects.array, &array[i].array[j].objects.used, &array[i].array[j].objects.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_ranges_t), (void **) &array[i].array[j].contents.array, &array[i].array[j].contents.used, &array[i].array[j].contents.size, &f_string_rangess_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_uint8s_t), (void **) &array[i].array[j].quotess.array, &array[i].array[j].quotess.used, &array[i].array[j].quotess.size, &f_uint8ss_destroy_callback);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_fss_named_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_namedss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
