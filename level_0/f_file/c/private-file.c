#include <level_0/file.h>
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_change_mode(const f_string path, const mode_t mode) {

    if (chmod(path, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EIO) return F_status_set_error(F_input_output);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_change_mode_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_change_mode_at(const int at_id, const f_string path, const mode_t mode) {

    if (fchmodat(at_id, path, mode, 0) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EIO) return F_status_set_error(F_input_output);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_change_mode_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_change_owner(const f_string path, const uid_t uid, const gid_t gid, const bool dereference) {
    int result = 0;

    if (dereference) {
      if (uid != -1) {
        result = chown(path, uid, -1);

        if (result < 0 && errno == EPERM) return F_status_set_error(F_access_owner);
      }

      if (result == 0 && gid != -1) {
        result = chown(path, -1, gid);

        if (errno == EPERM) return F_status_set_error(F_access_group);
      }
    }
    else {
      if (uid != -1) {
        result = lchown(path, uid, -1);

        if (result < 0 && errno == EPERM) return F_status_set_error(F_access_owner);
      }

      if (gid != -1) {
        result = lchown(path, -1, gid);

        if (result < 0 && errno == EPERM) return F_status_set_error(F_access_group);
      }
    }

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EIO) return F_status_set_error(F_input_output);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_change_owner_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_change_owner_at(const int at_id, const f_string path, const uid_t uid, const gid_t gid, const int flag) {
    int result = 0;

    if (uid != -1) {
      result = fchownat(at_id, path, uid, -1, flag);

      if (result < 0 && errno == EPERM) return F_status_set_error(F_access_owner);
    }

    if (gid != -1) {
      result = fchownat(at_id, path, -1, gid, flag);

      if (result < 0 && errno == EPERM) return F_status_set_error(F_access_group);
    }

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EIO) return F_status_set_error(F_input_output);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_change_owner_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_close(int *id) {
    if (F_status_is_error(private_f_file_flush(*id))) return F_status_set_error(F_file_synchronize);

    if (close(*id) < 0) {
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);

      return F_status_set_error(F_file_close);
    }

    *id = 0;
    return F_none;
  }
#endif // !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)
  f_return_status private_f_file_copy_content(const f_string source, const f_string destination, const f_number_unsigned size_block) {
    f_file file_source = f_file_initialize;
    f_file file_destination = f_file_initialize;

    file_source.flag = f_file_flag_read_only;
    file_destination.flag = f_file_flag_write_only | f_file_flag_no_follow;

    f_status status = private_f_file_open(source, 0, &file_source);
    if (F_status_is_error(status)) return status;

    status = private_f_file_open(destination, 0, &file_destination);
    if (F_status_is_error(status)) {
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

        return F_status_set_error(F_file_write);
      }
    } // while

    private_f_file_close(&file_destination.id);
    private_f_file_close(&file_source.id);

    if (size_read < 0) return F_status_set_error(F_file_read);

    return F_none;
  }
#endif // !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)

#if !defined(_di_f_file_copy_at_) || !defined(_di_f_file_clone_at_)
  f_return_status private_f_file_copy_content_at(const int at_id, const f_string source, const f_string destination, const f_number_unsigned size_block) {
    f_file file_source = f_file_initialize;
    f_file file_destination = f_file_initialize;

    file_source.flag = f_file_flag_read_only;
    file_destination.flag = f_file_flag_write_only | f_file_flag_no_follow;

    f_status status = private_f_file_open_at(at_id, source, 0, &file_source);
    if (F_status_is_error(status)) return status;

    status = private_f_file_open_at(at_id, destination, 0, &file_destination);
    if (F_status_is_error(status)) {
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

        return F_status_set_error(F_file_write);
      }
    } // while

    private_f_file_close(&file_destination.id);
    private_f_file_close(&file_source.id);

    if (size_read < 0) return F_status_set_error(F_file_read);

    return F_none;
  }
#endif // !defined(_di_f_file_copy_at_) || !defined(_di_f_file_clone_at_)

#if !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_create(const f_string path, const mode_t mode, const bool exclusive) {
    f_file file = f_file_initialize;

    file.flag = f_file_flag_close_execute | f_file_flag_create | f_file_flag_write_only;

    if (exclusive) {
      file.flag |= f_file_flag_exclusive;
    }

    f_status status = private_f_file_open(path, mode, &file);

    if (file.id > 0) {
      return private_f_file_close(&file.id);
    }

    return status;
  }
#endif // !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_create_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_create_at(const int at_id, const f_string path, const mode_t mode, const bool exclusive) {
    f_file file = f_file_initialize;

    file.flag = f_file_flag_close_execute | f_file_flag_create | f_file_flag_write_only;

    if (exclusive) {
      file.flag |= f_file_flag_exclusive;
    }

    f_status status = private_f_file_open_at(at_id, path, mode, &file);

    if (file.id > 0) {
      return private_f_file_close(&file.id);
    }

    return status;
  }
#endif // !defined(_di_f_file_create_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_copy_)
  f_return_status private_f_file_create_directory(const f_string path, const mode_t mode) {

    if (mkdir(path, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMLINK) return F_status_set_error(F_directory_link_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_copy_)

#if !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_create_directory_at(const int at_id, const f_string path, const mode_t mode) {

    if (mkdirat(at_id, path, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMLINK) return F_status_set_error(F_directory_link_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_create_fifo_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_create_fifo(const f_string path, const mode_t mode) {

    if (mkfifo(path, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_create_fifo_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_create_fifo_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_create_fifo_at(const int at_id, const f_string path, const mode_t mode) {

    if (mkfifoat(at_id, path, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_create_fifo_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_create_device_) || !defined(_di_f_file_create_node_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_create_node(const f_string path, const mode_t mode, const dev_t device) {

    if (mknod(path, mode, device) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_create_device_) || !defined(_di_f_file_create_node_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_create_device_at_) || !defined(_di_f_file_create_node_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_create_node_at(const int at_id, const f_string path, const mode_t mode, const dev_t device) {

    if (mknodat(at_id, path, mode, device) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_create_device_at_) || !defined(_di_f_file_create_node_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_flush_) || !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_flush(const int id) {

    if (fsync(id) < 0) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EROFS) return F_status_set_error(F_unsupported);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_flush_) || !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_link(const f_string target, const f_string point) {

    if (symlink(target, point) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_link_at(const int at_id, const f_string target, const f_string point) {

    if (symlinkat(target, at_id, point) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_link_read_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_link_read(const f_string path, const struct stat link_stat, f_string_dynamic *target) {
    // create a NULL terminated string based on file stat.
    if (link_stat.st_size + 1 > target->size) {
      if (link_stat.st_size + 1 > f_string_length_size) {
        return F_status_set_error(F_string_too_large);
      }

      f_status status = F_none;

      f_macro_string_dynamic_resize(status, (*target), link_stat.st_size + 1);
      if (F_status_is_error(status)) return status;
    }

    memset(target->string, 0, target->used + 1);

    target->used = link_stat.st_size;

    if (readlink(path, target->string, target->used) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
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
#endif // !defined(_di_f_file_link_read_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_link_read_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_link_read_at(const int at_id, const f_string path, const struct stat link_stat, f_string_dynamic *target) {
    // create a NULL terminated string based on file stat.
    if (link_stat.st_size + 1 > target->size) {
      if (link_stat.st_size + 1 > f_string_length_size) {
        return F_status_set_error(F_string_too_large);
      }

      f_status status = F_none;

      f_macro_string_dynamic_resize(status, (*target), link_stat.st_size + 1);
      if (F_status_is_error(status)) return status;
    }

    memset(target->string, 0, target->used + 1);

    target->used = link_stat.st_size;

    if (readlinkat(at_id, path, target->string, target->used) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
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
#endif // !defined(_di_f_file_link_read_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_open(const f_string path, const mode_t mode, f_file *file) {
    if (mode == 0) {
      file->id = open(path, file->flag);
    }
    else {
      file->id = open(path, file->flag, mode);
    }

    if (file->id < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);
      if (errno == EISDIR) return F_status_set_error(F_directory);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_unsupported);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_open_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_open_at(const int at_id, const f_string path, const mode_t mode, f_file *file) {
    if (mode == 0) {
      file->id = openat(at_id, path, file->flag);
    }
    else {
      file->id = openat(at_id, path, file->flag, mode);
    }

    if (file->id < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);
      if (errno == EISDIR) return F_status_set_error(F_directory);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_unsupported);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_open_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)
  f_return_status private_f_file_stat(const f_string path, const bool dereference, struct stat *file_stat) {

    if ((dereference ? stat(path, file_stat) : lstat(path, file_stat)) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_stat_at_) || !defined(_di_f_file_copy_at_)
  f_return_status private_f_file_stat_at(const int at_id, const f_string path, const int flag, struct stat *file_stat) {

    if (fstatat(at_id, path, file_stat, flag) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);

      return F_status_set_error(F_file_stat);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_stat_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)
  f_return_status private_f_file_stat_by_id(const int id, struct stat *file_stat) {
    int result = fstat(id, file_stat);

    if (result < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)

#if !defined(f_file_write) || !defined(f_file_write_until) || !defined(f_file_write_range)
  f_return_status private_f_file_write_until(const f_file file, const f_string string, const f_string_length total, f_string_length *written) {
    *written = 0;

    f_status status = F_none;
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
      return F_none_stop;
    }

    if (size_write < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(f_file_write) || !defined(f_file_write_until) || !defined(f_file_write_range)

#ifdef __cplusplus
} // extern "C"
#endif
