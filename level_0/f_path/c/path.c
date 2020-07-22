#include <level_0/path.h>
#include "private-path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_path_change_
  f_return_status f_path_change(const f_string path) {

    if (chdir(path) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_path_change_

#ifndef _di_f_path_change_at_
  f_return_status f_path_change_at(const int at_id) {
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
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_path_change_at_

#ifndef _di_f_path_current_
  f_return_status f_path_current(const bool real, f_string_dynamic *path) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    char buffer[f_path_max];

    if (!getcwd(buffer, f_path_max)) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (real) {
      return private_f_path_real(buffer, path);
    }

    const f_string_length length = strnlen(buffer, f_path_max);

    if (length + 1 > path->size) {
      f_status status = F_none;

      f_macro_string_dynamic_new(status, (*path), length + 1);
      if (F_status_is_error(status)) return status;
    }

    memcpy(path->string, buffer, length);

    path->string[length] = 0;
    path->used = length;

    return F_none;
  }
#endif // _di_f_path_current_

#ifndef _di_f_path_real_
  f_return_status f_path_real(const f_string path, f_string_dynamic *real) {
    #ifndef _di_level_0_parameter_checking_
      if (real == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_path_real(path, real);
  }
#endif // _di_f_path_real_

#ifdef __cplusplus
} // extern "C"
#endif
