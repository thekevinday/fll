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

#ifndef _di_fll_file_move_
  void fll_file_move(const f_string_static_t source, const f_string_static_t destination, f_directory_recurse_t * const recurse) {
    #ifndef _di_level_2_parameter_checking_
      if (!recurse) return;
    #endif // _di_level_2_parameter_checking_

    if (!source.used || !destination.used) {
      recurse->state.status = F_data_not;

      return;
    }

    recurse->state.status = f_file_rename(source, destination);

    if (F_status_set_fine(recurse->state.status) != F_mount) {
      if (recurse->state.status == F_none && recurse->verbose) {
        recurse->verbose(source, destination, recurse);
      }

      return;
    }

    recurse->state.status = f_file_is(source, F_file_type_directory_d, !(recurse->flag & f_file_stat_flag_reference_e));

    if (recurse->state.status == F_file_found_not) {
      recurse->state.status = F_status_set_error(recurse->state.status);
    }

    if (F_status_is_error(recurse->state.status)) return;

    if (recurse->state.status == F_true) {
      const uint8_t flag_original = recurse->flag;

      recurse->flag = f_directory_recurse_flag_clone_e;

      fl_directory_copy(source, destination, recurse);

      recurse->flag = flag_original;

      if (F_status_is_error(recurse->state.status)) return;

      recurse->state.status = f_directory_remove(source, recurse->max_depth, F_false);

      if (recurse->state.status == F_none && recurse->verbose) {
        recurse->verbose(source, destination, recurse);
      }
    }
    else {
      recurse->state.status = f_file_clone(source, destination, recurse->size_block, recurse->flag);
      if (F_status_is_error(recurse->state.status)) return;

      recurse->state.status = f_file_remove(source);

      if (recurse->state.status == F_none && recurse->verbose) {
        recurse->verbose(source, destination, recurse);
      }
    }
  }
#endif // _di_fll_file_move_

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
