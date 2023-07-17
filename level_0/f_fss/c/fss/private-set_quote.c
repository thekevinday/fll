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

    status = f_uint8s_adjust(length, &set_quote->objects_quote);
    if (F_status_is_error(status)) return status;

    status = f_uint8ss_adjust(length, &set_quote->contents_quote);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)

#if !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)
  f_status_t private_f_fss_set_quote_resize(const f_number_unsigned_t length, f_fss_set_quote_t * const set_quote) {

    f_status_t status = f_string_ranges_resize(length, &set_quote->objects);
    if (F_status_is_error(status)) return status;

    status = f_string_rangess_resize(length, &set_quote->contents);
    if (F_status_is_error(status)) return status;

    status = f_uint8s_resize(length, &set_quote->objects_quote);
    if (F_status_is_error(status)) return status;

    status = f_uint8ss_resize(length, &set_quote->contents_quote);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)

#if !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)
  f_status_t private_f_fss_set_quotes_adjust(const f_number_unsigned_t length, f_fss_set_quotes_t * const set_quotes) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < set_quotes->size; ++i) {

      status = f_string_ranges_adjust(0, &set_quotes->array[i].objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_adjust(0, &set_quotes->array[i].contents);
      if (F_status_is_error(status)) return status;

      status = f_uint8s_adjust(0, &set_quotes->array[i].objects_quote);
      if (F_status_is_error(status)) return status;

      status = f_uint8ss_adjust(0, &set_quotes->array[i].contents_quote);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(set_quotes->size, length, sizeof(f_fss_set_quote_t), (void **) & set_quotes->array);
    if (F_status_is_error(status)) return status;

    set_quotes->size = length;

    if (set_quotes->used > set_quotes->size) {
      set_quotes->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)

#if !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)
  f_status_t private_f_fss_set_quotes_resize(const f_number_unsigned_t length, f_fss_set_quotes_t * const set_quotes) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < set_quotes->size; ++i) {

      status = f_string_ranges_resize(0, &set_quotes->array[i].objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_resize(0, &set_quotes->array[i].contents);
      if (F_status_is_error(status)) return status;

      status = f_uint8s_resize(0, &set_quotes->array[i].objects_quote);
      if (F_status_is_error(status)) return status;

      status = f_uint8ss_resize(0, &set_quotes->array[i].contents_quote);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(set_quotes->size, length, sizeof(f_fss_set_quote_t), (void **) & set_quotes->array);
    if (F_status_is_error(status)) return status;

    set_quotes->size = length;

    if (set_quotes->used > set_quotes->size) {
      set_quotes->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
