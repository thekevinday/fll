#include "limit.h"
#include "private-limit.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_limit_sets_decrease_) || !defined(_di_f_limit_sets_decrease_by_) || !defined(_di_f_limit_sets_delete_)
  f_return_status private_f_limit_sets_delete(f_limit_sets_t *sets) {
    f_status_t status = F_none;

    f_macro_limit_sets_t_delete(status, (*sets));

    return status;
  }
#endif // !defined(_di_f_limit_sets_decrease_) || !defined(_di_f_limit_sets_decrease_by_) || !defined(_di_f_limit_sets_delete_)

#if !defined(_di_f_limit_sets_decrease_) || !defined(_di_f_limit_sets_decrease_by_) || !defined(_di_f_limit_sets_increase_) || !defined(_di_f_limit_sets_increase_by_)
  f_return_status private_f_limit_sets_resize(const f_array_length_t length, f_limit_sets_t *sets) {
    f_status_t status = F_none;

    f_macro_limit_sets_t_resize(status, (*sets), length);

    return status;
  }
#endif // !defined(_di_f_limit_sets_decrease_) || !defined(_di_f_limit_sets_decrease_by_) || !defined(_di_f_limit_sets_increase_) || !defined(_di_f_limit_sets_increase_by_)

#if !defined(_di_f_limit_values_decrease_) || !defined(_di_f_limit_values_decrease_by_) || !defined(_di_f_limit_values_delete_)
  f_return_status private_f_limit_values_delete(f_limit_values_t *values) {
    f_status_t status = F_none;

    f_macro_limit_values_t_delete(status, (*values));

    return status;
  }
#endif // !defined(_di_f_limit_values_decrease_) || !defined(_di_f_limit_values_decrease_by_) || !defined(_di_f_limit_values_delete_)

#if !defined(_di_f_limit_values_decrease_) || !defined(_di_f_limit_values_decrease_by_) || !defined(_di_f_limit_values_increase_) || !defined(_di_f_limit_values_increase_by_)
  f_return_status private_f_limit_values_resize(const f_array_length_t length, f_limit_values_t *values) {
    f_status_t status = F_none;

    f_macro_limit_values_t_resize(status, (*values), length);

    return status;
  }
#endif // !defined(_di_f_limit_values_decrease_) || !defined(_di_f_limit_values_decrease_by_) || !defined(_di_f_limit_values_increase_) || !defined(_di_f_limit_values_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif
