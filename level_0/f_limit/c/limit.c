#include "limit.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_limit_process_
  f_status_t f_limit_process(const pid_t id, const int type, const f_limit_value_t * const value_next, f_limit_value_t * const value_current) {
    #ifndef _di_level_0_parameter_checking_
      if (!value_next && !value_current) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (prlimit(id, type, value_next, value_current) < 0) {
      if (errno == EFAULT) return F_status_set_error(F_address_not);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == ESRCH) return F_status_set_error(F_found_not);

      return F_status_set_error(F_failure);
    }

    return F_okay;
  }
#endif // _di_f_limit_process_

#ifdef __cplusplus
} // extern "C"
#endif
