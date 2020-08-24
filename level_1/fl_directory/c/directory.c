#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_directory_clone_
  f_return_status fl_directory_clone(const f_string source, const f_string destination, const f_string_length source_length, const f_string_length destination_length, const bool role, const f_number_unsigned size_block, const bool exclusive, FILE *verbose, f_directory_statuss *failures) {
    #ifndef _di_level_1_parameter_checking_
      if (source) return F_status_set_error(F_parameter);
      if (destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_directory_exists(source);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = f_file_stat(source, F_false, &source_stat);
    if (F_status_is_error(status)) return status;

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;

    if (status == F_true) {
      if (exclusive) {
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

    if (verbose) {
      fprintf(verbose, "Cloned '%s' to '%s'.%c", source, destination, f_string_eol[0]);
    }

    f_string_static static_source = { source, source_length, source_length };
    f_string_static static_destination = { destination, destination_length, destination_length };

    // do not allow null termination or trailing path separators in the string's length calculation.
    {
      f_string_length i = source_length;

      for (; i > 0; i--, static_source.used--) {
        if (source[i - 1] == 0) continue;
        if (source[i - 1] == f_path_separator[0]) continue;
        break;
      } // for

      i = destination_length;

      for (; i > 0; i--, static_destination.used--) {
        if (destination[i - 1] == 0) continue;
        if (destination[i - 1] == f_path_separator[0]) continue;
        break;
      } // for
    }

    return private_fl_directory_clone(static_source, static_destination, role, size_block, exclusive, verbose, failures);
  }
#endif // _di_fl_directory_clone_

#ifndef _di_fl_directory_clone_content_
  f_return_status fl_directory_clone_content(const f_string source, const f_string destination, const f_string_length source_length, const f_string_length destination_length, const bool role, const f_number_unsigned size_block, const bool exclusive, FILE *verbose, f_directory_statuss *failures) {
    #ifndef _di_level_1_parameter_checking_
      if (source) return F_status_set_error(F_parameter);
      if (destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_directory_exists(source);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    f_string_static static_source = { source, source_length, source_length };
    f_string_static static_destination = { destination, destination_length, destination_length };

    // do not allow null termination or trailing path separators in the string's length calculation.
    {
      f_string_length i = source_length;

      for (; i > 0; i--, static_source.used--) {
        if (source[i - 1] == 0) continue;
        if (source[i - 1] == f_path_separator[0]) continue;
        break;
      } // for

      i = destination_length;

      for (; i > 0; i--, static_destination.used--) {
        if (destination[i - 1] == 0) continue;
        if (destination[i - 1] == f_path_separator[0]) continue;
        break;
      } // for
    }

    return private_fl_directory_clone(static_source, static_destination, role, size_block, exclusive, verbose, failures);
  }
#endif // _di_fl_directory_clone_content_

#ifndef _di_fl_directory_copy_
  f_return_status fl_directory_copy(const f_string source, const f_string destination, const f_string_length source_length, const f_string_length destination_length, const f_mode mode, const f_number_unsigned size_block, const bool exclusive, FILE *verbose, f_directory_statuss *failures) {
    #ifndef _di_level_1_parameter_checking_
      if (source) return F_status_set_error(F_parameter);
      if (destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_directory_exists(source);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;

    if (status == F_true) {
      if (exclusive) {
        return F_status_set_error(F_directory_found);
      }

      status = f_file_mode_set(destination, mode.directory);
      if (F_status_is_error(status)) return status;
    }
    else {
      status = f_directory_create(destination, mode.directory);
      if (F_status_is_error(status)) return status;
    }

    if (verbose) {
      fprintf(verbose, "Copied '%s' to '%s'.%c", source, destination, f_string_eol[0]);
    }

    f_string_static static_source = { source, source_length, source_length };
    f_string_static static_destination = { destination, destination_length, destination_length };

    // do not allow null termination or trailing path separators in the string's length calculation.
    {
      f_string_length i = source_length;

      for (; i > 0; i--, static_source.used--) {
        if (source[i - 1] == 0) continue;
        if (source[i - 1] == f_path_separator[0]) continue;
        break;
      } // for

      i = destination_length;

      for (; i > 0; i--, static_destination.used--) {
        if (destination[i - 1] == 0) continue;
        if (destination[i - 1] == f_path_separator[0]) continue;
        break;
      } // for
    }

    return private_fl_directory_copy(static_source, static_destination, mode, size_block, exclusive, verbose, failures);
  }
#endif // _di_fl_directory_copy_

#ifndef _di_fl_directory_copy_content_
  f_return_status fl_directory_copy_content(const f_string source, const f_string destination, const f_string_length source_length, const f_string_length destination_length, const f_mode mode, const f_number_unsigned size_block, const bool exclusive, FILE *verbose, f_directory_statuss *failures) {
    #ifndef _di_level_1_parameter_checking_
      if (source) return F_status_set_error(F_parameter);
      if (destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_directory_exists(source);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    f_string_static static_source = { source, source_length, source_length };
    f_string_static static_destination = { destination, destination_length, destination_length };

    // do not allow null termination or trailing path separators in the string's length calculation.
    {
      f_string_length i = source_length;

      for (; i > 0; i--, static_source.used--) {
        if (source[i - 1] == 0) continue;
        if (source[i - 1] == f_path_separator[0]) continue;
        break;
      } // for

      i = destination_length;

      for (; i > 0; i--, static_destination.used--) {
        if (destination[i - 1] == 0) continue;
        if (destination[i - 1] == f_path_separator[0]) continue;
        break;
      } // for
    }

    return private_fl_directory_copy(static_source, static_destination, mode, size_block, exclusive, verbose, failures);
  }
#endif // _di_fl_directory_copy_content_

#ifndef _di_fl_directory_list_
  f_return_status fl_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing *listing) {
    #ifndef _di_level_1_parameter_checking_
      if (path) return F_status_set_error(F_parameter);
      if (listing == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_directory_list(path, filter, sort, dereference, listing);
  }
#endif // _di_fl_directory_list_

#ifndef _di_fl_directory_path_pop_
  f_return_status fl_directory_path_pop(f_string_static *path) {
    #ifndef _di_level_0_parameter_checking_
      if (path->used > path->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (path->used == 0) {
      return F_data_not;
    }

    const bool null_terminated = path->string[path->used] == 0;
    bool first_nulless = F_false;

    f_string_length i = path->used - 1;
    f_string_length j = 0;

    f_status status = F_none;

    for (; i > 0; i--) {
      if (path->string[i] == 0) continue;

      status = f_utf_is_control(path->string + i, path->used - i);
      if (status == F_true) continue;

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_incomplete_utf) continue;

        return status;
      }

      if (first_nulless) {
        if (path->string[i] == f_path_separator[0]) {
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

        for (j = i; j > 0; j--) {
          if (path->string[j] == 0) continue;

          status = f_utf_is_control(path->string + j, path->used - j);
          if (status == F_true) continue;

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_incomplete_utf) continue;

            return status;
          }

          if (path->string[j] != f_path_separator[0]) {
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
  f_return_status fl_directory_path_push(const f_string source, f_string_length length, f_string_dynamic *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (length == 0) {
      return F_data_not;
    }

    return private_fl_directory_path_push(source, length, destination);
  }
#endif // _di_fl_directory_path_push_

#ifndef _di_fl_directory_path_push_dynamic_
  f_return_status fl_directory_path_push_dynamic(const f_string_static source, f_string_dynamic *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (source.used > source.size) return F_status_set_error(F_parameter);
      if (destination->used > destination->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (source.used == 0) {
      return F_data_not;
    }

    return private_fl_directory_path_push(source.string, source.used, destination);
  }
#endif // _di_fl_directory_path_push_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif
