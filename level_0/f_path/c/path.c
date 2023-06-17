#include "path.h"
#include "private-path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_path_change_
  f_status_t f_path_change(const f_string_static_t path) {

    if (chdir(path.string) < 0) {
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
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
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
#endif // _di_f_path_change_at_

#ifndef _di_f_path_current_
  f_status_t f_path_current(const bool real, f_string_dynamic_t * const path) {
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

    const f_number_unsigned_t length = strnlen(buffer, F_path_length_max_d);

    {
      path->used = 0;

      const f_status_t status = f_string_dynamic_increase_by(length + 1, path);
      if (F_status_is_error(status)) return status;
    }

    memcpy(path->string, buffer, sizeof(char) * length);

    path->string[length] = 0;
    path->used = length;

    return F_none;
  }
#endif // _di_f_path_current_

#ifndef _f_path_directory_cleanup_
  f_status_t f_path_directory_cleanup(const f_string_static_t argument, f_string_dynamic_t * const directory) {
    #ifndef _di_level_0_parameter_checking_
      if (!directory) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    directory->used = 0;

    if (!argument.used) {
      return F_none;
    }

    // Ensure enough space is available for terminating slash and terminating NULL.
    if (argument.string[argument.used - 1] == f_path_separator_s.string[0]) {
      const f_status_t status = f_string_dynamic_increase_by(argument.used + 1, directory);
      if (F_status_is_error(status)) return status;
    }
    else {
      const f_status_t status = f_string_dynamic_increase_by(argument.used + 2, directory);
      if (F_status_is_error(status)) return status;
    }

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    while (i < argument.used) {

      if (argument.string[i] == f_path_separator_s.string[0]) {
        directory->string[directory->used++] = f_path_separator_s.string[0];

        do {
          ++i;
        } while (i < argument.used && (argument.string[i] == f_path_separator_s.string[0] || !argument.string[i]));
      }
      else {
        j = i + 1;

        while (j < argument.used && argument.string[j] != f_path_separator_s.string[0]) {
          ++j;
        } // while

        // Use memcpy() to take advantage of its optimized copy behaviors.
        memcpy(directory->string + directory->used, argument.string + i, sizeof(f_char_t) * (j - i));

        directory->used += j - i;
        i = j;
      }
    } // while

    if (directory->string[directory->used - 1] != f_path_separator_s.string[0]) {
      directory->string[directory->used++] = f_path_separator_s.string[0];
    }

    directory->string[directory->used] = 0;

    return F_none;
  }
#endif // _f_path_directory_cleanup_

#ifndef _di_f_path_is_
  f_status_t f_path_is(const f_string_static_t path) {

    if (!path.used || !path.string) {
      return F_data_not;
    }

    for (f_number_unsigned_t i = 0; i < path.used; ++i) {
      if (path.string[i] == f_path_separator_s.string[0]) return true;
    } // for

    return F_false;
  }
#endif // _di_f_path_is_

#ifndef _di_f_path_is_absolute_
  f_status_t f_path_is_absolute(const f_string_static_t path) {

    if (!path.used || !path.string) {
      return F_data_not;
    }

    f_number_unsigned_t i = 0;

    for (; i < path.used; ++i) {
      if (path.string[i]) break;
    } // for

    if (i == path.used) return F_data_not;
    if (path.string[i] == f_path_separator_s.string[0]) return F_true;

    return F_false;
  }
#endif // _di_f_path_is_absolute_

#ifndef _di_f_path_is_relative_
  f_status_t f_path_is_relative(const f_string_static_t path) {

    if (!path.used || !path.string) {
      return F_data_not;
    }

    f_number_unsigned_t i = 0;

    for (; i < path.used; ++i) {
      if (path.string[i]) break;
    } // for

    if (i == path.used) return F_data_not;
    if (path.string[i] == f_path_separator_s.string[0]) return F_false;

    return F_true;
  }
#endif // _di_f_path_is_relative_

#ifndef _di_f_path_is_relative_current_
  f_status_t f_path_is_relative_current(const f_string_static_t path) {

    if (!path.used || !path.string) {
      return F_data_not;
    }

    f_number_unsigned_t i = 0;

    for (; i < path.used; ++i) {
      if (path.string[i]) break;
    } // for

    if (i == path.used) return F_data_not;
    if (path.string[i] == f_path_separator_s.string[0]) return F_false;

    if (path.string[i] == f_path_separator_current_s.string[0]) {
      for (++i; i < path.used; ++i) {
        if (path.string[i]) break;
      } // for

      if (i == path.used) return F_false;
      if (path.string[i] == f_path_separator_s.string[0]) return F_true;

      if (path.string[i] == f_path_separator_current_s.string[0]) {
        for (++i; i < path.used; ++i) {
          if (path.string[i]) break;
        } // for

        if (i == path.used) return F_false;
        if (path.string[i] == f_path_separator_s.string[0]) return F_true;
      }
    }

    return F_false;
  }
#endif // _di_f_path_is_relative_current_

#ifndef _di_f_path_real_
  f_status_t f_path_real(const f_string_static_t path, f_string_dynamic_t * const real) {
    #ifndef _di_level_0_parameter_checking_
      if (!real) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_path_real(path.string, real);
  }
#endif // _di_f_path_real_

#ifdef __cplusplus
} // extern "C"
#endif
