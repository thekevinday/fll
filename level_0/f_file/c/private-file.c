#include <level_0/file.h>
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_change_mode(const f_string path, const mode_t mode, const bool dereference) {

    if ((dereference ? chmod(path, mode) : lchmod(path, mode)) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == EIO) return f_status_set_error(f_error_input_output);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_change_mode_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_change_mode_at(const int at_id, const f_string path, const mode_t mode, const int flags) {

    if (fchmodat(at_id, path, mode, flags) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == EIO) return f_status_set_error(f_error_input_output);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_change_mode_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_change_owner(const f_string path, const uid_t uid, const gid_t gid, const bool dereference) {

    if ((dereference ? chown(path, uid, gid) : lchown(path, uid, gid)) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == EIO) return f_status_set_error(f_error_input_output);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_change_owner_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_change_owner_at(const int at_id, const f_string path, const uid_t uid, const gid_t gid, const int flags) {

    if (fchownat(at_id, path, uid, gid, flags) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == EIO) return f_status_set_error(f_error_input_output);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_change_owner_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_close(int *id) {
    if (f_status_is_error(private_f_file_flush(*id))) return f_status_set_error(f_file_error_synchronize);

    if (close(*id) < 0) {
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == ENOSPC) return f_status_set_error(f_no_space);
      if (errno == EDQUOT) return f_status_set_error(f_filesystem_quota_blocks);

      return f_status_set_error(f_file_error_close);
    }

    *id = 0;
    return f_none;
  }
#endif // !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)
  f_return_status private_f_file_copy_content(const f_string source, const f_string destination, const f_number_unsigned size_block) {
    f_file file_source = f_file_initialize;
    f_file file_destination = f_file_initialize;

    f_status status = private_f_file_open(source, f_file_flag_read_only, 0, &file_source);
    if (f_status_is_error(status)) return status;

    status = private_f_file_open(destination, f_file_flag_write_only | f_file_flag_no_follow, 0, &file_destination);
    if (f_status_is_error(status)) {
      private_f_file_close(&file_source.id);
      return status;
    }

    ssize_t size_read = 0;
    ssize_t size_write = 0;
    char *buffer[size_block];

    memset(buffer, 0, size_block);

    while ((size_read = read(file_source.id, buffer, size_block)) > 0) {
      size_write = write(file_destination.id, buffer, size_read);

      if (size_write < 0 || size_write != size_read) {
        private_f_file_close(&file_destination.id);
        private_f_file_close(&file_source.id);

        return f_status_set_error(f_file_error_write);
      }
    } // while

    private_f_file_close(&file_destination.id);
    private_f_file_close(&file_source.id);

    if (size_read < 0) return f_status_set_error(f_file_error_read);

    return f_none;
  }
#endif // !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)

#if !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_create(const f_string path, const mode_t mode, const bool exclusive, const bool dereference) {
    int flags = O_CLOEXEC | O_CREAT | O_WRONLY;

    if (exclusive) {
      flags |= O_EXCL;
    }

    if (!dereference) {
      flags |= O_NOFOLLOW;
    }

    f_file file = f_file_initialize;
    f_status status = private_f_file_open(path, mode, flags, &file);

    if (file.id > 0) {
      return private_f_file_close(&file.id);
    }

    return status;
  }
#endif // !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_create_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_create_at(const int at_id, const f_string path, const mode_t mode, const bool exclusive, const bool dereference) {
    int flags = O_CLOEXEC | O_CREAT | O_WRONLY;

    if (exclusive) {
      flags |= O_EXCL;
    }

    if (!dereference) {
      flags |= O_NOFOLLOW;
    }

    f_file file = f_file_initialize;
    f_status status = private_f_file_open_at(at_id, path, flags, mode, &file);

    if (file.id > 0) {
      return private_f_file_close(&file.id);
    }

    return status;
  }
#endif // !defined(_di_f_file_create_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_flush_) || !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_flush(const int id) {

    if (fsync(id) < 0) {
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == ENOSPC) return f_status_set_error(f_no_space);
      if (errno == EROFS) return f_status_set_error(f_unsupported);
      if (errno == EDQUOT) return f_status_set_error(f_filesystem_quota_blocks);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_flush_) || !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_link(const f_string target, const f_string point) {

    if (symlink(target, point) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EDQUOT) return f_status_set_error(f_filesystem_quota_blocks);
      if (errno == EEXIST) return f_status_set_error(f_file_found);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOSPC) return f_status_set_error(f_no_space);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == ETXTBSY) return f_status_set_error(f_busy);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_link_at(const int at_id, const f_string target, const f_string point) {

    if (symlinkat(target, at_id, point) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EDQUOT) return f_status_set_error(f_filesystem_quota_blocks);
      if (errno == EEXIST) return f_status_set_error(f_file_found);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOSPC) return f_status_set_error(f_no_space);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == ETXTBSY) return f_status_set_error(f_busy);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_open(const f_string path, const int flags, const mode_t mode, f_file *file) {
    if (mode == 0) {
      file->id = open(path, flags);
    }
    else {
      file->id = open(path, flags, mode);
    }

    if (file->id < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EDQUOT) return f_status_set_error(f_filesystem_quota_blocks);
      if (errno == EEXIST) return f_status_set_error(f_file_found);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENFILE) return f_status_set_error(f_file_max_open);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOSPC) return f_status_set_error(f_no_space);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == ETXTBSY) return f_status_set_error(f_busy);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_open_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_open_at(const int at_id, const f_string path, const int flags, const mode_t mode, f_file *file) {
    if (mode == 0) {
      file->id = openat(at_id, path, flags);
    }
    else {
      file->id = openat(at_id, path, flags, mode);
    }

    if (file->id < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EDQUOT) return f_status_set_error(f_filesystem_quota_blocks);
      if (errno == EEXIST) return f_status_set_error(f_file_found);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENFILE) return f_status_set_error(f_file_max_open);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOSPC) return f_status_set_error(f_no_space);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == ETXTBSY) return f_status_set_error(f_busy);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_open_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_stat(const f_string path, const bool dereference, struct stat *file_stat) {

    if ((dereference ? stat(path, file_stat) : lstat(path, file_stat)) < 0) {
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ELOOP) return f_status_set_error(f_loop);

      return f_status_set_error(f_file_error_stat);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_stat_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_stat_at(const int at_id, const f_string path, const int flags, struct stat *file_stat) {

    if (fstatat(at_id, path, file_stat, flags) < 0) {
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);

      return f_status_set_error(f_file_error_stat);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_stat_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)
  f_return_status private_f_file_stat_by_id(const int id, struct stat *file_stat) {
    int result = fstat(id, file_stat);

    if (result < 0) {
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == ENOENT) return f_file_not_found;
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ELOOP) return f_status_set_error(f_loop);

      return f_status_set_error(f_file_error_stat);
    }

    return f_none;
  }
#endif // !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)

#if !defined(f_file_write) || !defined(f_file_write_until) || !defined(f_file_write_range)
  f_return_status private_f_file_write_until(const f_file file, const f_string string, const f_string_length total, f_string_length *written) {
    *written = 0;

    f_status status = f_none;
    f_string_length write_size = file.size_write;
    f_string_length write_max = total;

    ssize_t size_write = 0;

    if (write_max < write_size) {
      write_size = write_max;
    }

    while (*written < write_max && (size_write = write(file.id, string + *written, write_size)) > 0) {
      *written += size_write;

      if (*written + write_size > write_max) {
        write_size = write_max - *written;
      }
    } // while

    if (size_write == 0) {
      return f_none_on_stop;
    }

    if (size_write < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return f_status_set_error(f_block);
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EINTR) return f_status_set_error(f_interrupted);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == EISDIR) return f_status_set_error(f_file_is_type_directory);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // !defined(f_file_write) || !defined(f_file_write_until) || !defined(f_file_write_range)

#ifdef __cplusplus
} // extern "C"
#endif
