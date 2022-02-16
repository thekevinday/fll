#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_directory_create_
  f_status_t fl_directory_create(const f_string_static_t path, const mode_t mode) {
    #ifndef _di_level_1_parameter_checking_
      if (!path.string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    f_status_t status = f_directory_exists(path);
    if (F_status_is_error(status)) return status;

    if (status == F_true) {
      return F_directory_found;
    }

    {
      f_array_length_t at_tree = 0;
      f_array_length_t at_path = 0;
      f_string_static_t tree = f_string_static_t_initialize;

      char tree_string[path.used + 1];
      tree.string = tree_string;
      tree.used = path.used;
      tree_string[path.used] = 0;

      for (; at_path < path.used; ++at_path) {

        if (at_path && path.string[at_path] == f_path_separator_s.string[0]) {
          memcpy(tree.string, path.string + at_tree, at_path - at_tree);
          tree.string[at_path - at_tree] = 0;

          status = f_directory_exists(tree);
          if (F_status_is_error(status)) return status;

          if (status == F_false) {
            status = f_directory_create(tree, mode);
            if (F_status_is_error(status)) return status;
          }

          at_tree = at_path;
        }
      } // for
    }

    return f_directory_create(path, mode);
  }
#endif // _di_fl_directory_create_

#ifndef _di_fl_directory_clone_
  f_status_t fl_directory_clone(const f_string_static_t source, const f_string_static_t destination, const bool role, const fl_directory_recurse_t recurse) {
    #ifndef _di_level_1_parameter_checking_
      if (!source.string) return F_status_set_error(F_parameter);
      if (!destination.string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used || !destination.used) {
      return F_data_not;
    }

    f_status_t status = f_directory_exists(source);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = f_file_stat(source, F_false, &source_stat);
    if (F_status_is_error(status)) return status;

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;

    if (status == F_true) {
      if (recurse.exclusive) {
        return F_status_set_error(F_directory_found);
      }

      status = f_file_mode_set(destination, source_stat.st_mode);
      if (F_status_is_error(status)) return status;
    }
    else {
      status = f_directory_create(destination, source_stat.st_mode);
      if (F_status_is_error(status)) return status;
    }

    if (role) {
      status = f_file_role_change(destination, source_stat.st_uid, source_stat.st_gid, F_true);
      if (F_status_is_error(status)) return status;
    }

    {
      f_string_static_t static_source = source;
      f_string_static_t static_destination = destination;
      f_array_length_t i = 0;

      // Do not allow null termination or trailing path separators in the string's length calculation.
      for (; i > 0; --i, --static_source.used) {

        if (!source.string[i - 1]) continue;
        if (source.string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for

      i = destination.used;

      for (; i > 0; --i, --static_destination.used) {

        if (!destination.string[i - 1]) continue;
        if (destination.string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for

      if (recurse.depth_max) {
        status = private_fl_directory_clone(static_source, static_destination, role, recurse, 1);
      }
    }

    if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
      recurse.verbose(recurse.output, source, destination);
    }

    return status;
  }
#endif // _di_fl_directory_clone_

#ifndef _di_fl_directory_clone_content_
  f_status_t fl_directory_clone_content(const f_string_static_t source, const f_string_static_t destination, const bool role, const fl_directory_recurse_t recurse) {
    #ifndef _di_level_1_parameter_checking_
      if (!source.string) return F_status_set_error(F_parameter);
      if (!destination.string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used || !destination.used) {
      return F_data_not;
    }

    f_status_t status = f_directory_exists(source);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    f_string_static_t static_source = macro_f_string_static_t_initialize2(source.string, source.used);
    f_string_static_t static_destination = macro_f_string_static_t_initialize2(destination.string, destination.used);

    // Do not allow null termination or trailing path separators in the string's length calculation.
    {
      f_array_length_t i = source.used;

      for (; i > 0; --i, --static_source.used) {

        if (!source.string[i - 1]) continue;
        if (source.string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for

      i = destination.used;

      for (; i > 0; --i, --static_destination.used) {

        if (!destination.string[i - 1]) continue;
        if (destination.string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for
    }

    if (!recurse.depth_max) {
      return status;
    }

    status = private_fl_directory_clone(static_source, static_destination, role, recurse, 1);

    if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
      recurse.verbose(recurse.output, source, destination);
    }

    return status;
  }
#endif // _di_fl_directory_clone_content_

#ifndef _di_fl_directory_copy_
  f_status_t fl_directory_copy(const f_string_static_t source, const f_string_static_t destination, const f_mode_t mode, const fl_directory_recurse_t recurse) {
    #ifndef _di_level_1_parameter_checking_
      if (!source.string) return F_status_set_error(F_parameter);
      if (!destination.string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used || !destination.used) {
      return F_data_not;
    }

    f_status_t status = f_directory_exists(source);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;

    if (status == F_true) {
      if (recurse.exclusive) {
        return F_status_set_error(F_directory_found);
      }

      status = f_file_mode_set(destination, mode.directory);
      if (F_status_is_error(status)) return status;
    }
    else {
      status = f_directory_create(destination, mode.directory);
      if (F_status_is_error(status)) return status;
    }

    f_string_static_t static_source = macro_f_string_static_t_initialize2(source.string, source.used);
    f_string_static_t static_destination = macro_f_string_static_t_initialize2(destination.string, destination.used);

    // Do not allow null termination or trailing path separators in the string's length calculation.
    {
      f_array_length_t i = source.used;

      for (; i > 0; --i, --static_source.used) {

        if (!source.string[i - 1]) continue;
        if (source.string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for

      i = destination.used;

      for (; i > 0; --i, --static_destination.used) {

        if (!destination.string[i - 1]) continue;
        if (destination.string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for
    }

    if (recurse.depth_max) {
      status = private_fl_directory_copy(static_source, static_destination, mode, recurse, 1);
    }

    if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
      recurse.verbose(recurse.output, source, destination);
    }

    return status;
  }
#endif // _di_fl_directory_copy_

#ifndef _di_fl_directory_copy_content_
  f_status_t fl_directory_copy_content(const f_string_static_t source, const f_string_static_t destination, const f_mode_t mode, const fl_directory_recurse_t recurse) {
    #ifndef _di_level_1_parameter_checking_
      if (!source.string) return F_status_set_error(F_parameter);
      if (!destination.string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used || !destination.used) {
      return F_data_not;
    }

    f_status_t status = f_directory_exists(source);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    f_string_static_t static_source = macro_f_string_static_t_initialize2(source.string, source.used);
    f_string_static_t static_destination = macro_f_string_static_t_initialize2(destination.string, destination.used);

    // Do not allow null termination or trailing path separators in the string's length calculation.
    {
      f_array_length_t i = source.used;

      for (; i > 0; --i, --static_source.used) {

        if (!source.string[i - 1]) continue;
        if (source.string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for

      i = destination.used;

      for (; i > 0; --i, --static_destination.used) {

        if (!destination.string[i - 1]) continue;
        if (destination.string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for
    }

    if (recurse.depth_max) {
      status = private_fl_directory_copy(static_source, static_destination, mode, recurse, 1);
    }

    if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
      recurse.verbose(recurse.output, source, destination);
    }

    return status;
  }
#endif // _di_fl_directory_copy_content_

#ifndef _di_fl_directory_list_
  f_status_t fl_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t *listing) {
    #ifndef _di_level_1_parameter_checking_
      if (!path.string) return F_status_set_error(F_parameter);
      if (!listing) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_fl_directory_list(path, filter, sort, dereference, listing);
  }
#endif // _di_fl_directory_list_

#ifndef _di_fl_directory_path_pop_
  f_status_t fl_directory_path_pop(f_string_static_t *path) {
    #ifndef _di_level_1_parameter_checking_
      if (!path->string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!path->used) {
      return F_data_not;
    }

    const bool null_terminated = path->string[path->used] == 0;
    bool first_nulless = F_false;

    f_array_length_t i = path->used - 1;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    for (; i > 0; --i) {

      if (!path->string[i]) continue;

      status = f_utf_is_control(path->string + i, path->used - i);
      if (status == F_true) continue;

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_complete_not_utf) continue;

        return status;
      }

      if (first_nulless) {
        if (path->string[i] == f_path_separator_s.string[0]) {
          if (null_terminated) {
            path->string[i + 1] = 0;
            path->used = i + 2;
          }
          else {
            path->used = i + 1;
          }

          return F_none;
        }
      }
      else {
        first_nulless = F_true;

        for (j = i; j > 0; --j) {
          if (!path->string[j]) continue;

          status = f_utf_is_control(path->string + j, path->used - j);
          if (status == F_true) continue;

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_complete_not_utf) continue;

            return status;
          }

          if (path->string[j] != f_path_separator_s.string[0]) {
            i = j + 1;

            break;
          }
        } // for
      }
    } // for

    path->used = 0;

    return F_none;
  }
#endif // _di_fl_directory_path_pop_

#ifndef _di_fl_directory_path_push_
  f_status_t fl_directory_path_push(const f_string_static_t source, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!source.string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) {
      return F_data_not;
    }

    return private_fl_directory_path_push(source, destination);
  }
#endif // _di_fl_directory_path_push_

#ifdef __cplusplus
} // extern "C"
#endif
