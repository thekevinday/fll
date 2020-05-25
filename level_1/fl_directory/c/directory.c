#include <level_1/directory.h>
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_copy_
  f_return_status f_directory_copy(const f_string source, const f_string destination, const mode_t mode, const f_number_unsigned size_block, const bool exclusive) {
    f_status status = F_none;
    /*
@todo
    status = f_directory_exists(source);
    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;

    if (exclusive) {
    }
    else {
    }

    status = private_fl_directory_list(source, 0, 0, listing);*/

    return F_none;
  }
#endif // _di_f_directory_copy_

#ifndef _di_fl_directory_list_
  f_return_status fl_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_directory_listing *listing) {
    #ifndef _di_level_2_parameter_checking_
      if (listing == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fl_directory_list(path, filter, sort, listing);
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

    bool null_terminated = path->string[path->used] == 0;
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
