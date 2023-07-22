#include "../fss.h"
#include "private-item.h"
#include "private-nest.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_nest_adjust_
  f_status_t f_fss_nest_adjust(const f_number_unsigned_t length, f_fss_nest_t * const nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nest_adjust(length, nest);
  }
#endif // _di_f_fss_nest_adjust_

#ifndef _di_f_fss_nest_decimate_by_
  f_status_t f_fss_nest_decimate_by(const f_number_unsigned_t amount, f_fss_nest_t * const nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_nest_adjust((nest->size > amount) ? nest->size - amount : 0, nest);
  }
#endif // _di_f_fss_nest_decimate_by_

#ifndef _di_f_fss_nest_decrease_by_
  f_status_t f_fss_nest_decrease_by(const f_number_unsigned_t amount, f_fss_nest_t * const nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_nest_resize((nest->size > amount) ? nest->size - amount : 0, nest);
  }
#endif // _di_f_fss_nest_decrease_by_

#ifndef _di_f_fss_nest_increase_
  f_status_t f_fss_nest_increase(const f_number_unsigned_t step, f_fss_nest_t * const nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && nest->used + 1 > nest->size) {
      if (nest->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t length = nest->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (nest->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_fss_nest_resize(length, nest);
    }

    return F_data_not;
  }
#endif // _di_f_fss_nest_increase_

#ifndef _di_f_fss_nest_increase_by_
  f_status_t f_fss_nest_increase_by(const f_number_unsigned_t amount, f_fss_nest_t * const nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (nest->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = nest->used + amount;

      if (length > nest->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_fss_nest_resize(length, nest);
      }
    }

    return F_data_not;
  }
#endif // _di_f_fss_nest_increase_by_

#ifndef _di_f_fss_nest_resize_
  f_status_t f_fss_nest_resize(const f_number_unsigned_t length, f_fss_nest_t * const nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nest_resize(length, nest);
  }
#endif // _di_f_fss_nest_resize_

#ifndef _di_f_fss_nests_adjust_
  f_status_t f_fss_nests_adjust(const f_number_unsigned_t length, f_fss_nests_t * const nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nests_adjust(length, nests);
  }
#endif // _di_f_fss_nests_adjust_

#ifndef _di_f_fss_nests_decimate_by_
  f_status_t f_fss_nests_decimate_by(const f_number_unsigned_t amount, f_fss_nests_t * const nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_nests_adjust((nests->size > amount) ? nests->size - amount : 0, nests);
  }
#endif // _di_f_fss_nests_decimate_by_

#ifndef _di_f_fss_nests_decrease_by_
  f_status_t f_fss_nests_decrease_by(const f_number_unsigned_t amount, f_fss_nests_t * const nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_fss_nests_resize((nests->size > amount) ? nests->size - amount : 0, nests);
  }
#endif // _di_f_fss_nests_decrease_by_

#ifndef _di_f_fss_nests_increase_
  f_status_t f_fss_nests_increase(const f_number_unsigned_t step, f_fss_nests_t * const nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && nests->used + 1 > nests->size) {
      if (nests->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t length = nests->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (nests->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_fss_nests_resize(length, nests);
    }

    return F_data_not;
  }
#endif // _di_f_fss_nests_increase_

#ifndef _di_f_fss_nests_increase_by_
  f_status_t f_fss_nests_increase_by(const f_number_unsigned_t amount, f_fss_nests_t * const nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (nests->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = nests->used + amount;

      if (length > nests->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_fss_nests_resize(length, nests);
      }
    }

    return F_data_not;
  }
#endif // _di_f_fss_nests_increase_by_

#ifndef _di_f_fss_nests_resize_
  f_status_t f_fss_nests_resize(const f_number_unsigned_t length, f_fss_nests_t * const nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nests_resize(length, nests);
  }
#endif // _di_f_fss_nests_resize_

#ifdef __cplusplus
} // extern "C"
#endif
