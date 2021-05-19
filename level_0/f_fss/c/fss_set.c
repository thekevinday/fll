#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_set_adjust_
  f_status_t f_fss_set_adjust(const f_array_length_t length, f_fss_set_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_adjust(length, set);
  }
#endif // _di_f_fss_set_adjust_

#ifndef _di_f_fss_set_decimate_by_
  f_status_t f_fss_set_decimate_by(const f_array_length_t amount, f_fss_set_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set->objects.size - amount > 0) {
      return private_f_fss_set_adjust(set->objects.size - amount, set);
    }

    return private_f_fss_set_adjust(0, set);
  }
#endif // _di_f_fss_set_decimate_by_

#ifndef _di_f_fss_set_decrease_by_
  f_status_t f_fss_set_decrease_by(const f_array_length_t amount, f_fss_set_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set->objects.size - amount > 0) {
      return private_f_fss_set_resize(set->objects.size - amount, set);
    }

    return private_f_fss_set_resize(0, set);
  }
#endif // _di_f_fss_set_decrease_by_

#ifndef _di_f_fss_set_increase_
  f_status_t f_fss_set_increase(const uint16_t step, f_fss_set_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set->objects.used + 1 > set->objects.size) {
      f_array_length_t size = set->objects.used + step;

      if (size > f_array_length_t_size) {
        if (set->objects.used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_set_resize(size, set);
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_increase_

#ifndef _di_f_fss_set_increase_by_
  f_status_t f_fss_set_increase_by(const f_array_length_t amount, f_fss_set_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set->objects.used + amount > set->objects.size) {
      if (set->objects.used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_set_resize(set->objects.used + amount, set);
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_increase_by_

#ifndef _di_f_fss_set_resize_
  f_status_t f_fss_set_resize(const f_array_length_t length, f_fss_set_t *set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_resize(length, set);
  }
#endif // _di_f_fss_set_resize_

#ifndef _di_f_fss_set_quote_adjust_
  f_status_t f_fss_set_quote_adjust(const f_array_length_t length, f_fss_set_quote_t *set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_quote_adjust(length, set_quote);
  }
#endif // _di_f_fss_set_quote_adjust_

#ifndef _di_f_fss_set_quote_decimate_by_
  f_status_t f_fss_set_quote_decimate_by(const f_array_length_t amount, f_fss_set_quote_t *set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set_quote->objects.size - amount > 0) {
      return private_f_fss_set_quote_adjust(set_quote->objects.size - amount, set_quote);
    }

    return private_f_fss_set_quote_adjust(0, set_quote);
  }
#endif // _di_f_fss_set_quote_decimate_by_

#ifndef _di_f_fss_set_quote_decrease_by_
  f_status_t f_fss_set_quote_decrease_by(const f_array_length_t amount, f_fss_set_quote_t *set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set_quote->objects.size - amount > 0) {
      return private_f_fss_set_quote_resize(set_quote->objects.size - amount, set_quote);
    }

    return private_f_fss_set_quote_resize(0, set_quote);
  }
#endif // _di_f_fss_set_quote_decrease_by_

#ifndef _di_f_fss_set_quote_increase_
  f_status_t f_fss_set_quote_increase(const uint16_t step, f_fss_set_quote_t *set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set_quote->objects.used + 1 > set_quote->objects.size) {
      f_array_length_t size = set_quote->objects.used + step;

      if (size > f_array_length_t_size) {
        if (set_quote->objects.used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_set_quote_resize(size, set_quote);
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_quote_increase_

#ifndef _di_f_fss_set_quote_increase_by_
  f_status_t f_fss_set_quote_increase_by(const f_array_length_t amount, f_fss_set_quote_t *set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set_quote->objects.used + amount > set_quote->objects.size) {
      if (set_quote->objects.used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_set_quote_resize(set_quote->objects.used + amount, set_quote);
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_quote_increase_by_

#ifndef _di_f_fss_set_quote_resize_
  f_status_t f_fss_set_quote_resize(const f_array_length_t length, f_fss_set_quote_t *set_quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quote) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_quote_resize(length, set_quote);
  }
#endif // _di_f_fss_set_quote_resize_

#ifndef _di_f_fss_set_quotes_adjust_
  f_status_t f_fss_set_quotes_adjust(const f_array_length_t length, f_fss_set_quotes_t *set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_quotes_adjust(length, set_quotes);
  }
#endif // _di_f_fss_set_quotes_adjust_

#ifndef _di_f_fss_set_quotes_decimate_by_
  f_status_t f_fss_set_quotes_decimate_by(const f_array_length_t amount, f_fss_set_quotes_t *set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set_quotes->size - amount > 0) {
      return private_f_fss_set_quotes_adjust(set_quotes->size - amount, set_quotes);
    }

    return private_f_fss_set_quotes_adjust(0, set_quotes);
  }
#endif // _di_f_fss_set_quotes_decimate_by_

#ifndef _di_f_fss_set_quotes_decrease_by_
  f_status_t f_fss_set_quotes_decrease_by(const f_array_length_t amount, f_fss_set_quotes_t *set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set_quotes->size - amount > 0) {
      return private_f_fss_set_quotes_resize(set_quotes->size - amount, set_quotes);
    }

    return private_f_fss_set_quotes_resize(0, set_quotes);
  }
#endif // _di_f_fss_set_quotes_decrease_by_

#ifndef _di_f_fss_set_quotes_increase_
  f_status_t f_fss_set_quotes_increase(const uint16_t step, f_fss_set_quotes_t *set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set_quotes->used + 1 > set_quotes->size) {
      f_array_length_t size = set_quotes->used + step;

      if (size > f_array_length_t_size) {
        if (set_quotes->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_set_quotes_resize(size, set_quotes);
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_quotes_increase_

#ifndef _di_f_fss_set_quotes_increase_by_
  f_status_t f_fss_set_quotes_increase_by(const f_array_length_t amount, f_fss_set_quotes_t *set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (set_quotes->used + amount > set_quotes->size) {
      if (set_quotes->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_set_quotes_resize(set_quotes->used + amount, set_quotes);
    }

    return F_data_not;
  }
#endif // _di_f_fss_set_quotes_increase_by_

#ifndef _di_f_fss_set_quotes_resize_
  f_status_t f_fss_set_quotes_resize(const f_array_length_t length, f_fss_set_quotes_t *set_quotes) {
    #ifndef _di_level_0_parameter_checking_
      if (!set_quotes) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_set_quotes_resize(length, set_quotes);
  }
#endif // _di_f_fss_set_quotes_resize_

#ifndef _di_f_fss_sets_adjust_
  f_status_t f_fss_sets_adjust(const f_array_length_t length, f_fss_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_sets_adjust(length, sets);
  }
#endif // _di_f_fss_sets_adjust_

#ifndef _di_f_fss_sets_decimate_by_
  f_status_t f_fss_sets_decimate_by(const f_array_length_t amount, f_fss_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->size - amount > 0) {
      return private_f_fss_sets_adjust(sets->size - amount, sets);
    }

    return private_f_fss_sets_adjust(0, sets);
  }
#endif // _di_f_fss_sets_decimate_by_

#ifndef _di_f_fss_sets_decrease_by_
  f_status_t f_fss_sets_decrease_by(const f_array_length_t amount, f_fss_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->size - amount > 0) {
      return private_f_fss_sets_resize(sets->size - amount, sets);
    }

    return private_f_fss_sets_resize(0, sets);
  }
#endif // _di_f_fss_sets_decrease_by_

#ifndef _di_f_fss_sets_increase_
  f_status_t f_fss_sets_increase(const uint16_t step, f_fss_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->used + 1 > sets->size) {
      f_array_length_t size = sets->used + step;

      if (size > f_array_length_t_size) {
        if (sets->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_sets_resize(size, sets);
    }

    return F_data_not;
  }
#endif // _di_f_fss_sets_increase_

#ifndef _di_f_fss_sets_increase_by_
  f_status_t f_fss_sets_increase_by(const f_array_length_t amount, f_fss_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (sets->used + amount > sets->size) {
      if (sets->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_sets_resize(sets->used + amount, sets);
    }

    return F_data_not;
  }
#endif // _di_f_fss_sets_increase_by_

#ifndef _di_f_fss_sets_resize_
  f_status_t f_fss_sets_resize(const f_array_length_t length, f_fss_sets_t *sets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_sets_resize(length, sets);
  }
#endif // _di_f_fss_sets_resize_

#ifdef __cplusplus
} // extern "C"
#endif
