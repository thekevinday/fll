#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_file_mode_set_all_
  f_status_t fll_file_mode_set_all(const f_string_static_t path, const mode_t mode, const f_number_unsigned_t depth_max) {
    #ifndef _di_level_2_parameter_checking_
      if (!path.string) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_fll_file_mode_set_all(path, mode, depth_max, 0);
  }
#endif // _di_fll_file_mode_set_all_

#ifndef _di_fll_file_move_
  f_status_t fll_file_move(const f_string_static_t source, const f_string_static_t destination, const fl_directory_recurse_t recurse) {
    #ifndef _di_level_2_parameter_checking_
      if (!source.string) return F_status_set_error(F_parameter);
      if (!destination.string) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!source.used || !destination.string) {
      return F_data_not;
    }

    f_status_t status = f_file_rename(source, destination);

    if (F_status_set_fine(status) != F_mount) {
      if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
        recurse.verbose(recurse.output, source.string, destination.string);
      }

      return status;
    }

    status = f_file_is(source, F_file_type_directory_d, F_false);

    if (status == F_file_found_not) {
      return F_status_set_error(status);
    }

    if (F_status_is_error(status)) {
      return status;
    }

    if (status == F_true) {
      status = fl_directory_clone(source, destination, F_true, recurse);
      if (F_status_is_error(status)) return status;

      status = f_directory_remove(source, recurse.depth_max, F_false);

      if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
        recurse.verbose(recurse.output, source.string, destination.string);
      }
    }
    else {
      status = f_file_clone(source, destination, F_true, recurse.size_block, recurse.exclusive);
      if (F_status_is_error(status)) return status;

      status = f_file_remove(source);

      if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
        recurse.verbose(recurse.output, source.string, destination.string);
      }
    }

    return status;
  }
#endif // _di_fll_file_move_

#ifndef _di_fll_file_role_change_all_
  f_status_t fll_file_role_change_all(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max) {
    #ifndef _di_level_2_parameter_checking_
      if (!path.string) return F_status_set_error(F_parameter);
      if (uid == -1 && gid == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!path.string) {
      return F_data_not;
    }

    return private_fll_file_role_change_all(path, uid, gid, dereference, depth_max, 0);
  }
#endif // _di_fll_file_role_change_all_

#ifdef __cplusplus
} // extern "C"
#endif
