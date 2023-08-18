#include "../fss.h"
#include "private-set_quote.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)
  f_status_t private_f_fss_set_quote_adjust(const f_number_unsigned_t length, f_fss_set_quote_t * const set_quote) {

    f_status_t status = f_string_ranges_adjust(length, &set_quote->objects);
    if (F_status_is_error(status)) return status;

    status = f_string_rangess_adjust(length, &set_quote->contents);
    if (F_status_is_error(status)) return status;

    status = f_memory_array_adjust(length, sizeof(uint8_t), (void **) &set_quote->objects_quote.array, &set_quote->objects_quote.used, &set_quote->objects_quote.size);
    if (F_status_is_error(status)) return status;

    status = f_memory_arrays_adjust(length, sizeof(f_uint8s_t), (void **) &set_quote->contents_quote.array, &set_quote->contents_quote.used, &set_quote->contents_quote.size, &f_uint8s_delete_callback);
    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)

#if !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)
  f_status_t private_f_fss_set_quote_resize(const f_number_unsigned_t length, f_fss_set_quote_t * const set_quote) {

    f_status_t status = f_string_ranges_resize(length, &set_quote->objects);
    if (F_status_is_error(status)) return status;

    status = f_string_rangess_resize(length, &set_quote->contents);
    if (F_status_is_error(status)) return status;

    status = f_memory_array_resize(length, sizeof(uint8_t), (void **) &set_quote->objects_quote.array, &set_quote->objects_quote.used, &set_quote->objects_quote.size);
    if (F_status_is_error(status)) return status;

    status = f_memory_arrays_resize(length, sizeof(f_uint8s_t), (void **) &set_quote->contents_quote.array, &set_quote->contents_quote.used, &set_quote->contents_quote.size, &f_uint8s_delete_callback);
    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)

#if !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)
  f_status_t private_f_fss_set_quotes_adjust(const f_number_unsigned_t length, f_fss_set_quotes_t * const set_quotes) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < set_quotes->size; ++i) {

        status = f_string_ranges_adjust(0, &set_quotes->array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_adjust(0, &set_quotes->array[i].contents);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_adjust(0, sizeof(uint8_t), (void **) &set_quotes->array[i].objects_quote.array, &set_quotes->array[i].objects_quote.used, &set_quotes->array[i].objects_quote.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_uint8s_t), (void **) &set_quotes->array[i].contents_quote.array, &set_quotes->array[i].contents_quote.used, &set_quotes->array[i].contents_quote.size, &f_uint8s_delete_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_fss_set_quote_t), (void **) &set_quotes->array, &set_quotes->used, &set_quotes->size);
  }
#endif // !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)

#if !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_resize_)
  f_status_t private_f_fss_set_quotes_resize(const f_number_unsigned_t length, f_fss_set_quotes_t * const set_quotes) {

    {
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = length; i < set_quotes->size; ++i) {

        status = f_string_ranges_resize(0, &set_quotes->array[i].objects);
        if (F_status_is_error(status)) return status;

        status = f_string_rangess_resize(0, &set_quotes->array[i].contents);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_resize(0, sizeof(uint8_t), (void **) &set_quotes->array[i].objects_quote.array, &set_quotes->array[i].objects_quote.used, &set_quotes->array[i].objects_quote.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_uint8s_t), (void **) &set_quotes->array[i].contents_quote.array, &set_quotes->array[i].contents_quote.used, &set_quotes->array[i].contents_quote.size, &f_uint8s_delete_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_fss_set_quote_t), (void **) &set_quotes->array, &set_quotes->used, &set_quotes->size);
  }
#endif // !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
