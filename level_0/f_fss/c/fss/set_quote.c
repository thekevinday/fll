#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_set_quote_delete_
  f_status_t f_fss_set_quote_delete(f_fss_set_quote_t * const set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_string_ranges_resize(0, &set_quote->objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_resize(0, &set_quote->contents);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(uint8_t), (void **) &set_quote->objects_quote.array, &set_quote->objects_quote.used, &set_quote->objects_quote.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(uint8_t), (void **) &set_quote->contents_quote.array, &set_quote->contents_quote.used, &set_quote->contents_quote.size, &f_uint8ss_delete_callback);
      if (F_status_is_error(status)) return status;
    }

    return F_none;
  }
#endif // _di_f_fss_set_quote_delete_

#ifndef _di_f_fss_set_quote_destroy_
  f_status_t f_fss_set_quote_destroy(f_fss_set_quote_t * const set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_string_ranges_adjust(0, &set_quote->objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_adjust(0, &set_quote->contents);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(uint8_t), (void **) &set_quote->objects_quote.array, &set_quote->objects_quote.used, &set_quote->objects_quote.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(uint8_t), (void **) &set_quote->contents_quote.array, &set_quote->contents_quote.used, &set_quote->contents_quote.size, &f_uint8ss_destroy_callback);
      if (F_status_is_error(status)) return status;
    }

    return F_none;
  }
#endif // _di_f_fss_set_quote_destroy_

#ifndef _di_f_fss_set_quotes_delete_callback_
  f_status_t f_fss_set_quotes_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_set_quote_t * const array = (f_fss_set_quote_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_ranges_resize(0, &array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_resize(0, &array[i].contents);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_resize(0, sizeof(uint8_t), (void **) &array[i].objects_quote.array, &array[i].objects_quote.used, &array[i].objects_quote.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(uint8_t), (void **) &array[i].contents_quote.array, &array[i].contents_quote.used, &array[i].contents_quote.size, &f_uint8ss_delete_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_set_quotes_delete_callback_

#ifndef _di_f_fss_set_quotes_destroy_callback_
  f_status_t f_fss_set_quotes_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_set_quote_t * const array = (f_fss_set_quote_t *) void_array;
      f_status_t status = F_none;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_ranges_adjust(0, &array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_adjust(0, &array[i].contents);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_adjust(0, sizeof(uint8_t), (void **) &array[i].objects_quote.array, &array[i].objects_quote.used, &array[i].objects_quote.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(uint8_t), (void **) &array[i].contents_quote.array, &array[i].contents_quote.used, &array[i].contents_quote.size, &f_uint8ss_destroy_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_set_quotes_destroy_callback_

#ifndef _di_f_fss_set_quotess_delete_callback_
  f_status_t f_fss_set_quotess_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_set_quotes_t * const array = (f_fss_set_quotes_t *) void_array;
      f_status_t status = F_none;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_ranges_resize(0, &array[i].array[j].objects);
          if (F_status_is_error(status)) return status;

          status = f_string_rangess_resize(0, &array[i].array[j].contents);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_resize(0, sizeof(uint8_t), (void **) &array[i].array[j].objects_quote.array, &array[i].array[j].objects_quote.used, &array[i].array[j].objects_quote.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(uint8_t), (void **) &array[i].array[j].contents_quote.array, &array[i].array[j].contents_quote.used, &array[i].array[j].contents_quote.size, &f_uint8ss_delete_callback);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_fss_set_quote_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_set_quotess_delete_callback_

#ifndef _di_f_fss_set_quotess_destroy_callback_
  f_status_t f_fss_set_quotess_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_set_quotes_t * const array = (f_fss_set_quotes_t *) void_array;
      f_status_t status = F_none;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_ranges_adjust(0, &array[i].array[j].objects);
          if (F_status_is_error(status)) return status;

          status = f_string_rangess_adjust(0, &array[i].array[j].contents);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_adjust(0, sizeof(uint8_t), (void **) &array[i].array[j].objects_quote.array, &array[i].array[j].objects_quote.used, &array[i].array[j].objects_quote.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(uint8_t), (void **) &array[i].array[j].contents_quote.array, &array[i].array[j].contents_quote.used, &array[i].array[j].contents_quote.size, &f_uint8ss_destroy_callback);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_fss_set_quote_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_f_fss_set_quotess_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
