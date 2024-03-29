#include "path.h"
#include "private-path.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_path_current_) || !defined(_di_f_path_real_)
  f_status_t private_f_path_real(const char *path, f_string_dynamic_t * const real) {

    // Use a static array so that realpath() does not call malloc().
    char temporary[PATH_MAX];

    memset(temporary, 0, sizeof(char) * F_path_length_max_d);

    char * const buffer = realpath(path, temporary);

    if (!buffer) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);

      return F_status_set_error(F_failure);
    }

    const f_array_length_t length = strnlen(buffer, F_path_length_max_d);

    {
      real->used = 0;

      const f_status_t status = f_string_dynamic_increase_by(length + 1, real);
      if (F_status_is_error(status)) return status;
    }

    memcpy(real->string, buffer, sizeof(char) * length);

    real->string[length] = 0;
    real->used = length;

    return F_none;
  }
#endif // !defined(_di_f_path_current_) || !defined(_di_f_path_real_)

#ifdef __cplusplus
} // extern "C"
#endif
