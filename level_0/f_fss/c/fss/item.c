#include "../fss.h"
#include "private-item.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_items_adjust_
  f_status_t f_fss_items_adjust(const f_number_unsigned_t length, f_fss_items_t * const items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_items_adjust(length, items);
  }
#endif // _di_f_fss_items_adjust_

#ifndef _di_f_fss_items_decimate_by_
  f_status_t f_fss_items_decimate_by(const f_number_unsigned_t amount, f_fss_items_t * const items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (items->size > amount) return private_f_fss_items_adjust(items->size - amount, items);

    return private_f_fss_items_adjust(0, items);
  }
#endif // _di_f_fss_items_decimate_by_

#ifndef _di_f_fss_items_decrease_by_
  f_status_t f_fss_items_decrease_by(const f_number_unsigned_t amount, f_fss_items_t * const items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;
    if (items->size > amount) return private_f_fss_items_resize(items->size - amount, items);

    return private_f_fss_items_resize(0, items);
  }
#endif // _di_f_fss_items_decrease_by_

#ifndef _di_f_fss_items_increase_
  f_status_t f_fss_items_increase(const f_number_unsigned_t step, f_fss_items_t * const items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && items->used + 1 > items->size) {
      f_number_unsigned_t size = items->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (items->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        size = F_number_t_size_unsigned_d;
      }

      return private_f_fss_items_resize(size, items);
    }

    return F_data_not;
  }
#endif // _di_f_fss_items_increase_

#ifndef _di_f_fss_items_increase_by_
  f_status_t f_fss_items_increase_by(const f_number_unsigned_t amount, f_fss_items_t * const items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (items->used + amount > items->size) {
      if (items->used + amount > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      return private_f_fss_items_resize(items->used + amount, items);
    }

    return F_data_not;
  }
#endif // _di_f_fss_items_increase_by_

#ifndef _di_f_fss_items_resize_
  f_status_t f_fss_items_resize(const f_number_unsigned_t length, f_fss_items_t * const items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_items_resize(length, items);
  }
#endif // _di_f_fss_items_resize_

#ifdef __cplusplus
} // extern "C"
#endif
