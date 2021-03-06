#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_file_mode_set_all_
  f_status_t fll_file_mode_set_all(const f_string_t path, const mode_t mode, const f_number_unsigned_t depth_max) {
    #ifndef _di_level_2_parameter_checking_
      if (!path) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fll_file_mode_set_all(path, mode, depth_max, 0);
  }
#endif // _di_fll_file_mode_set_all_

#ifndef _di_fll_file_move_
  f_status_t fll_file_move(const f_string_t source, const f_string_t destination, const f_array_length_t source_length, const f_array_length_t destination_length, const fl_directory_recurse_t recurse) {
    #ifndef _di_level_2_parameter_checking_
      if (!source) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = f_file_rename(source, destination);

    if (F_status_set_fine(status) != F_mount) {
      if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
        recurse.verbose(recurse.output, source, destination);
      }

      return status;
    }

    status = f_file_is(source, f_file_type_directory, F_false);

    if (status == F_file_found_not) {
      return F_status_set_error(status);
    }

    if (F_status_is_error(status)) {
      return status;
    }

    if (status == F_true) {
      status = fl_directory_clone(source, destination, source_length, destination_length, F_true, recurse);

      if (F_status_is_error(status)) {
        return status;
      }

      status = f_directory_remove(source, recurse.depth_max, F_false);

      if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
        recurse.verbose(recurse.output, source, destination);
      }
    }
    else {
      status = f_file_clone(source, destination, F_true, recurse.size_block, recurse.exclusive);

      if (F_status_is_error(status)) {
        return status;
      }

      status = f_file_remove(source);

      if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
        recurse.verbose(recurse.output, source, destination);
      }
    }

    return status;
  }
#endif // _di_fll_file_move_

#ifndef _di_fll_file_role_change_all_
  f_status_t fll_file_role_change_all(const f_string_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max) {
    #ifndef _di_level_2_parameter_checking_
      if (!path) return F_status_set_error(F_parameter);
      if (uid == -1 && gid == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fll_file_role_change_all(path, uid, gid, dereference, depth_max, 0);
  }
#endif // _di_fll_file_role_change_all_

#ifdef __cplusplus
} // extern "C"
#endif
