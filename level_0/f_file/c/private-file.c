#include <level_0/file.h>
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_change_owner(const f_string path, const uid_t uid, const gid_t gid) {
    if (chown(path, uid, gid) < 0) {
      if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_status_set_error(f_invalid_name);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }
      else if (errno == ENOENT) {
        return f_status_set_error(f_file_not_found);
      }
      else if (errno == ENOMEM) {
        return f_status_set_error(f_out_of_memory);
      }
      else if (errno == ENOTDIR) {
        return f_status_set_error(f_invalid_directory);
      }
      else if (errno == EPERM) {
        return f_status_set_error(f_prohibited);
      }
      else if (errno == EROFS) {
        return f_status_set_error(f_read_only);
      }
      else if (errno == EIO) {
        return f_status_set_error(f_error_input_output);
      }

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_change_mode(const f_string path, const mode_t mode) {
    if (chmod(path, mode) < 0) {
      if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_status_set_error(f_invalid_name);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }
      else if (errno == ENOENT) {
        return f_status_set_error(f_file_not_found);
      }
      else if (errno == ENOMEM) {
        return f_status_set_error(f_out_of_memory);
      }
      else if (errno == ENOTDIR) {
        return f_status_set_error(f_invalid_directory);
      }
      else if (errno == EPERM) {
        return f_status_set_error(f_prohibited);
      }
      else if (errno == EROFS) {
        return f_status_set_error(f_read_only);
      }
      else if (errno == EIO) {
        return f_status_set_error(f_error_input_output);
      }

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_close(f_file *file) {
    if (file->address == 0) return f_status_set_error(f_file_not_open);

    // if given a file descriptor, flush all changes to the disk that are not flushed by the 'fflush()' command.
    if (file->id) {
      if (fsync(file->id) != 0) return f_status_set_error(f_file_error_synchronize);
    }

    if (fclose(file->address) == 0) {
      file->address = 0;
      return f_none;
    }

    return f_status_set_error(f_file_error_close);
  }
#endif // !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_create(f_string path, const mode_t mode, const bool exclusive) {
    int flags = O_CLOEXEC | O_CREAT | O_WRONLY;

    if (exclusive) {
      flags |= O_EXCL;
    }

    int result = open(path, flags, mode);

    if (result < 0) {
      if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == EDQUOT) {
        return f_status_set_error(f_filesystem_quota_blocks);
      }
      else if (errno == EEXIST) {
        return f_status_set_error(f_file_found);
      }
      else if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_status_set_error(f_invalid_name);
      }
      else if (errno == EFBIG || errno == EOVERFLOW) {
        return f_status_set_error(f_number_overflow);
      }
      else if (errno == EINTR) {
        return f_status_set_error(f_interrupted);
      }
      else if (errno == EINVAL) {
        return f_status_set_error(f_invalid_parameter);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }
      else if (errno == ENFILE) {
        return f_status_set_error(f_file_max_open);
      }
      else if (errno == ENOENT || errno == ENOTDIR) {
        return f_status_set_error(f_invalid_directory);
      }
      else if (errno == ENOMEM) {
        return f_status_set_error(f_out_of_memory);
      }
      else if (errno == ENOSPC) {
        return f_status_set_error(f_filesystem_quota_reached);
      }
      else if (errno == EPERM) {
        return f_status_set_error(f_prohibited);
      }
      else if (errno == EROFS) {
        return f_status_set_error(f_read_only);
      }
      else if (errno == ETXTBSY) {
        return f_status_set_error(f_busy);
      }

      return f_status_set_error(f_failure);
    }

    close(result);

    return f_none;
  }
#endif // !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_open(f_file *file, const f_string path) {
    // if file->mode is unset, then this may cause a segfault.
    if (file->mode == 0) return f_status_set_error(f_invalid_parameter);

    file->address = fopen(path, file->mode);

    if (file->address == 0) return f_status_set_error(f_file_not_found);
    if (ferror(file->address) != 0) return f_status_set_error(f_file_error_open);

    file->id = fileno(file->address);

    if (file->id == -1) return f_status_set_error(f_file_error_descriptor);

    return f_none;
  }
#endif // !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_stat(const f_string path, struct stat *file_stat) {
    if (stat(path, file_stat) < 0) {
      if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_status_set_error(f_invalid_name);
      }
      else if (errno == ENOMEM) {
        return f_status_set_error(f_out_of_memory);
      }
      else if (errno == EOVERFLOW) {
        return f_status_set_error(f_number_overflow);
      }
      else if (errno == ENOTDIR) {
        return f_status_set_error(f_invalid_directory);
      }
      else if (errno == ENOENT) {
        return f_status_set_error(f_file_not_found);
      }
      else if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }

      return f_status_set_error(f_file_error_stat);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)

#ifdef __cplusplus
} // extern "C"
#endif
