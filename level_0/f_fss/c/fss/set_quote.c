#include "../fss.h"
#include "private-set_quote.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_set_quote_adjust_
  f_status_t f_fss_set_quote_adjust(const f_number_unsigned_t length, f_fss_set_quote_t * const set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_quote_adjust(length, set_quote);
  }
#endif // _di_f_fss_set_quote_adjust_

#ifndef _di_f_fss_set_quote_decimate_by_
  f_status_t f_fss_set_quote_decimate_by(const f_number_unsigned_t amount, f_fss_set_quote_t * const set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_set_quote_adjust((set_quote->objects.size - amount > 0) ? set_quote->objects.size - amount : 0, set_quote);
  }
#endif // _di_f_fss_set_quote_decimate_by_

#ifndef _di_f_fss_set_quote_decrease_by_
  f_status_t f_fss_set_quote_decrease_by(const f_number_unsigned_t amount, f_fss_set_quote_t * const set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_set_quote_resize((set_quote->objects.size - amount > 0) ? set_quote->objects.size - amount : 0, set_quote);
  }
#endif // _di_f_fss_set_quote_decrease_by_

#ifndef _di_f_fss_set_quote_increase_
  f_status_t f_fss_set_quote_increase(const f_number_unsigned_t step, f_fss_set_quote_t * const set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && set_quote->objects.used + 1 > set_quote->objects.size) {
      if (set_quote->objects.used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t size = set_quote->objects.used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (set_quote->objects.used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        size = F_number_t_size_unsigned_d;
      }

      return private_f_fss_set_quote_resize(size, set_quote);
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_quote_increase_

#ifndef _di_f_fss_set_quote_increase_by_
  f_status_t f_fss_set_quote_increase_by(const f_number_unsigned_t amount, f_fss_set_quote_t * const set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (set_quote->objects.used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = set_quote->objects.used + amount;

      if (length > set_quote->objects.size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_fss_set_quote_resize(length, set_quote);
      }
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_quote_increase_by_

#ifndef _di_f_fss_set_quote_resize_
  f_status_t f_fss_set_quote_resize(const f_number_unsigned_t length, f_fss_set_quote_t * const set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_quote_resize(length, set_quote);
  }
#endif // _di_f_fss_set_quote_resize_

#ifndef _di_f_fss_set_quotes_adjust_
  f_status_t f_fss_set_quotes_adjust(const f_number_unsigned_t length, f_fss_set_quotes_t * const set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_quotes_adjust(length, set_quotes);
  }
#endif // _di_f_fss_set_quotes_adjust_

#ifndef _di_f_fss_set_quotes_decimate_by_
  f_status_t f_fss_set_quotes_decimate_by(const f_number_unsigned_t amount, f_fss_set_quotes_t * const set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_set_quotes_adjust((set_quotes->size > amount) ? set_quotes->size - amount : 0, set_quotes);
  }
#endif // _di_f_fss_set_quotes_decimate_by_

#ifndef _di_f_fss_set_quotes_decrease_by_
  f_status_t f_fss_set_quotes_decrease_by(const f_number_unsigned_t amount, f_fss_set_quotes_t * const set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_set_quotes_resize((set_quotes->size > amount) ? set_quotes->size - amount : 0, set_quotes);
  }
#endif // _di_f_fss_set_quotes_decrease_by_

#ifndef _di_f_fss_set_quotes_increase_
  f_status_t f_fss_set_quotes_increase(const f_number_unsigned_t step, f_fss_set_quotes_t * const set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_fss_set_quote_t), (void **) &set_quotes->array, &set_quotes->used, &set_quotes->size);
  }
#endif // _di_f_fss_set_quotes_increase_

#ifndef _di_f_fss_set_quotes_increase_by_
  f_status_t f_fss_set_quotes_increase_by(const f_number_unsigned_t amount, f_fss_set_quotes_t * const set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_fss_set_quote_t), (void **) &set_quotes->array, &set_quotes->used, &set_quotes->size);
  }
#endif // _di_f_fss_set_quotes_increase_by_

#ifndef _di_f_fss_set_quotes_resize_
  f_status_t f_fss_set_quotes_resize(const f_number_unsigned_t length, f_fss_set_quotes_t * const set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_quotes_resize(length, set_quotes);
  }
#endif // _di_f_fss_set_quotes_resize_

#ifdef __cplusplus
} // extern "C"
#endif
