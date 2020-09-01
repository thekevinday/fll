#include "path.h"
#include "private-path.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_path_current_) || !defined(_di_f_path_real_)
  f_return_status private_f_path_real(const f_string_t path, f_string_dynamic_t *real) {
    char buffer[f_path_max];

    if (!realpath(path, buffer)) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);

      return F_status_set_error(F_failure);
    }

    const f_string_length_t length = strnlen(buffer, f_path_max);

    if (length + 1 > real->size) {
      f_status_t status = F_none;

      f_macro_string_dynamic_t_resize(status, (*real), length + 1);
      if (F_status_is_error(status)) return status;
    }

    memcpy(real->string, buffer, length);

    real->string[length] = 0;
    real->used = length;

    return F_none;
  }
#endif // !defined(_di_f_path_current_) || !defined(_di_f_path_real_)

#ifdef __cplusplus
} // extern "C"
#endif
