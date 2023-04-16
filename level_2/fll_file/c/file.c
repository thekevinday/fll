#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_file_mode_set_all_
  f_status_t fll_file_mode_set_all(const f_string_static_t path, const bool dereference, const mode_t mode, const f_number_unsigned_t depth_max) {

    if (!path.used) return F_data_not;

    return private_fll_file_mode_set_all(path, dereference, mode, depth_max, 0);
  }
#endif // _di_fll_file_mode_set_all_

#ifndef _di_fll_file_role_change_all_
  f_status_t fll_file_role_change_all(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max) {
    #ifndef _di_level_2_parameter_checking_
      if (uid == -1 && gid == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!path.string) return F_data_not;

    return private_fll_file_role_change_all(path, uid, gid, dereference, depth_max, 0);
  }
#endif // _di_fll_file_role_change_all_

#ifdef __cplusplus
} // extern "C"
#endif
