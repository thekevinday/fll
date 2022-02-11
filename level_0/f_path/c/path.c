#include "path.h"
#include "private-path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_path_change_
  f_status_t f_path_change(const f_string_t path) {

    if (chdir(path) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_path_change_

#ifndef _di_f_path_change_at_
  f_status_t f_path_change_at(const int at_id) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (fchdir(at_id) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_path_change_at_

#ifndef _di_f_path_current_
  f_status_t f_path_current(const bool real, f_string_dynamic_t *path) {
    #ifndef _di_level_0_parameter_checking_
      if (!path) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    char buffer[F_path_length_max_d];

    if (!getcwd(buffer, F_path_length_max_d)) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (real) {
      return private_f_path_real(buffer, path);
    }

    const f_array_length_t length = strnlen(buffer, F_path_length_max_d);

    if (length + 1 > path->size) {
      f_status_t status = F_none;

      macro_f_string_dynamic_t_clear((*path))
      macro_f_string_dynamic_t_resize(status, (*path), length + 1)
      if (F_status_is_error(status)) return status;
    }

    memcpy(path->string, buffer, length);

    path->string[length] = 0;
    path->used = length;

    return F_none;
  }
#endif // _di_f_path_current_

#ifndef _f_path_directory_cleanup_
  f_status_t f_path_directory_cleanup(const f_string_static_t argument, f_string_dynamic_t *directory) {
    #ifndef _di_level_0_parameter_checking_
      if (!directory) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_array_length_t used_original = argument.used;

    directory->used = 0;

    if (!used_original) {
      return F_none;
    }

    // Ensure enough space is available for termiting slash and terminating NULL.
    if (argument.string[argument.used - 1] == f_path_separator_s.string[0]) {
      const f_status_t status = f_string_dynamic_increase_by(used_original + 1, directory);
      if (F_status_is_error(status)) return status;
    }
    else {
      const f_status_t status = f_string_dynamic_increase_by(used_original + 2, directory);
      if (F_status_is_error(status)) return status;
    }

    if (used_original == 1) {
      directory->string[0] = argument.string[0];

      return F_none;
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    do {
      if (argument.string[i] == f_path_separator_s.string[0]) {
        directory->string[directory->used++] = f_path_separator_s.string[0];

        do {
          ++i;
        } while (i < used_original && (argument.string[i] == f_path_separator_s.string[0] || !argument.string[i]));
      }
      else {
        j = i + 1;

        while (j < used_original && argument.string[j] != f_path_separator_s.string[0]) {
          ++j;
        } // while

        // Use memcpy() to take advantage of its optimized copy behaviors whenever possible.
        memcpy(directory->string + directory->used, argument.string + i, j - i);

        directory->used += j - i;
        i = j;
      }

    } while (i < used_original);

    if (directory->string[directory->used - 1] != f_path_separator_s.string[0]) {
      directory->string[directory->used++] = f_path_separator_s.string[0];
    }

    directory->string[directory->used++] = 0;

    return F_none;
  }
#endif // _f_path_directory_cleanup_

#ifndef _di_f_path_is_
  f_status_t f_path_is(const f_string_t path, const f_array_length_t length) {

    if (!path || !length) {
      return F_data_not;
    }

    for (f_array_length_t i = 0; i < length; ++i) {

      if (path[i] == f_path_separator_s.string[0]) {
        return F_true;
      }
    } // for

    return F_false;
  }
#endif // _di_f_path_is_

#ifndef _di_f_path_is_relative_
  f_status_t f_path_is_relative(const f_string_t path, const f_array_length_t length) {

    if (!path || !length) {
      return F_data_not;
    }

    f_array_length_t i = 0;

    for (; i < length; ++i) {
      if (path[i]) break;
    } // for

    if (path[i] == f_path_separator_s.string[0]) {
      return F_false;
    }

    return F_true;
  }
#endif // _di_f_path_is_relative_

#ifndef _di_f_path_is_relative_current_
  f_status_t f_path_is_relative_current(const f_string_t path, const f_array_length_t length) {

    if (!path || !length) {
      return F_data_not;
    }

    f_array_length_t i = 0;

    for (; i < length; ++i) {
      if (path[i]) break;
    } // for

    if (path[i] == f_path_separator_s.string[0]) {
      return F_false;
    }

    if (path[i] == f_path_separator_current_s.string[0]) {
      for (; i < length; ++i) {
        if (path[i]) break;
      } // for

      if (path[i] == f_path_separator_s.string[0]) {
        return F_true;
      }

      if (path[i] == f_path_separator_current_s.string[0]) {
        for (; i < length; ++i) {
          if (path[i]) break;
        } // for

        if (path[i] == f_path_separator_s.string[0]) {
          return F_true;
        }
      }
    }

    return F_false;
  }
#endif // _di_f_path_is_relative_current_

#ifndef _di_f_path_real_
  f_status_t f_path_real(const f_string_t path, f_string_dynamic_t *real) {
    #ifndef _di_level_0_parameter_checking_
      if (!real) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_path_real(path, real);
  }
#endif // _di_f_path_real_

#ifdef __cplusplus
} // extern "C"
#endif
