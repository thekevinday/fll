#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_directory_create_) || !defined(_di_f_directory_touch_)
  f_return_status private_f_directory_create(const f_string_t path, const mode_t mode) {

    if (mkdir(path, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMLINK) return F_status_set_error(F_directory_link_max);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_directory_create_) || !defined(_di_f_directory_touch_)

#if !defined(_di_f_directory_create_at_) || !defined(_di_f_directory_touch_at_)
  f_return_status private_f_directory_create_at(const int at_id, const f_string_t path, const mode_t mode) {

    if (mkdirat(at_id, path, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMLINK) return F_status_set_error(F_directory_link_max);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_directory_create_at_) || !defined(_di_f_directory_touch_at_)

#if !defined(_di_f_directory_remove_)
  int private_f_directory_remove_recursively(const char *path, const struct stat *file_stat, int type, struct FTW *entity) {
    if (!entity->level) return 0;
    return remove(path);
  }
#endif // !defined(_di_f_directory_remove_)

#ifdef __cplusplus
} // extern "C"
#endif
