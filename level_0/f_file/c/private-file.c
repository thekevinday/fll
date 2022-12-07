#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_file_close_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_stream_close_)
  f_status_t private_f_file_close(const bool flush, int * const id) {

    if (*id == -1) {
      return F_none;
    }

    if (flush) {
      private_f_file_flush(*id);
    }

    if (close(*id) < 0) {

      // According to man pages, retrying close() after another close on error is invalid on Linux because Linux releases the descriptor before stages that cause failures.
      if (errno != EBADF && errno != EINTR) {
        *id = -1;
      }

      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);

      return F_status_set_error(F_file_close);
    }

    *id = -1;

    return F_none;
  }
#endif // !defined(_di_f_file_close_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_stream_close_)

#if !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)
  f_status_t private_f_file_copy_content(const f_string_static_t source, const f_string_static_t destination, const f_number_unsigned_t size_block) {

    f_file_t file_source = f_file_t_initialize;
    f_file_t file_destination = f_file_t_initialize;

    file_source.flag = F_file_flag_read_only_d;
    file_destination.flag = F_file_flag_write_only_d | F_file_flag_no_follow_d;

    f_status_t status = private_f_file_open(source, 0, &file_source);
    if (F_status_is_error(status)) return status;

    status = private_f_file_open(destination, 0, &file_destination);

    if (F_status_is_error(status)) {
      private_f_file_close(F_true, &file_source.id);

      return status;
    }

    ssize_t size_read = 0;
    ssize_t size_write = 0;
    f_char_t buffer[size_block];

    memset(buffer, 0, sizeof(f_char_t) * size_block);

    while ((size_read = read(file_source.id, buffer, size_block)) > 0) {

      size_write = write(file_destination.id, buffer, size_read);

      if (size_write < 0 || size_write != size_read) {
        private_f_file_close(F_true, &file_destination.id);
        private_f_file_close(F_true, &file_source.id);

        return F_status_set_error(F_file_write);
      }
    } // while

    private_f_file_close(F_true, &file_destination.id);
    private_f_file_close(F_true, &file_source.id);

    if (size_read < 0) {
      return F_status_set_error(F_file_read);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)

#if !defined(_di_f_file_copy_at_) || !defined(_di_f_file_clone_at_)
  f_status_t private_f_file_copy_content_at(const int at_id, const f_string_static_t source, const f_string_static_t destination, const f_number_unsigned_t size_block) {

    f_file_t file_source = f_file_t_initialize;
    f_file_t file_destination = f_file_t_initialize;

    file_source.flag = F_file_flag_read_only_d;
    file_destination.flag = F_file_flag_write_only_d | F_file_flag_no_follow_d;

    f_status_t status = private_f_file_open_at(at_id, source, 0, &file_source);
    if (F_status_is_error(status)) return status;

    status = private_f_file_open_at(at_id, destination, 0, &file_destination);

    if (F_status_is_error(status)) {
      private_f_file_close(F_true, &file_source.id);

      return status;
    }

    ssize_t size_read = 0;
    ssize_t size_write = 0;
    f_char_t buffer[size_block];

    memset(buffer, 0, sizeof(f_char_t) * size_block);

    while ((size_read = read(file_source.id, buffer, size_block)) > 0) {

      size_write = write(file_destination.id, buffer, size_read);

      if (size_write < 0 || size_write != size_read) {
        private_f_file_close(F_true, &file_destination.id);
        private_f_file_close(F_true, &file_source.id);

        return F_status_set_error(F_file_write);
      }
    } // while

    private_f_file_close(F_true, &file_destination.id);
    private_f_file_close(F_true, &file_source.id);

    if (size_read < 0) {
      return F_status_set_error(F_file_read);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_copy_at_) || !defined(_di_f_file_clone_at_)

#if !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)
  f_status_t private_f_file_create(const f_string_static_t path, const mode_t mode, const bool exclusive) {

    f_file_t file = f_file_t_initialize;

    file.flag = F_file_flag_close_execute_d | F_file_flag_create_d | F_file_flag_write_only_d;

    if (exclusive) {
      file.flag |= F_file_flag_exclusive_d;
    }

    const f_status_t status = private_f_file_open(path, mode, &file);

    if (file.id != -1) {
      return private_f_file_close(F_true, &file.id);
    }

    return status;
  }
#endif // !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_create_at_) || !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_create_at(const int at_id, const f_string_static_t path, const mode_t mode, const bool exclusive) {

    f_file_t file = f_file_t_initialize;

    file.flag = F_file_flag_close_execute_d | F_file_flag_create_d | F_file_flag_write_only_d;

    if (exclusive) {
      file.flag |= F_file_flag_exclusive_d;
    }

    const f_status_t status = private_f_file_open_at(at_id, path, mode, &file);

    if (file.id != -1) {
      return private_f_file_close(F_true, &file.id);
    }

    return status;
  }
#endif // !defined(_di_f_file_create_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_copy_)
  f_status_t private_f_file_create_directory(const f_string_static_t path, const mode_t mode) {

    if (mkdir(path.string, mode) < 0) {
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
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_copy_)

#if !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_create_directory_at(const int at_id, const f_string_static_t path, const mode_t mode) {

    if (mkdirat(at_id, path.string, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMLINK) return F_status_set_error(F_directory_link_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_create_fifo_) || !defined(_di_f_file_copy_)
  f_status_t private_f_file_create_fifo(const f_string_static_t path, const mode_t mode) {

    if (mkfifo(path.string, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_create_fifo_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_create_fifo_at_) || !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_create_fifo_at(const int at_id, const f_string_static_t path, const mode_t mode) {

    if (mkfifoat(at_id, path.string, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_create_fifo_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_create_device_) || !defined(_di_f_file_create_node_) || !defined(_di_f_file_copy_)
  f_status_t private_f_file_create_node(const f_string_static_t path, const mode_t mode, const dev_t device) {

    if (mknod(path.string, mode, device) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_create_device_) || !defined(_di_f_file_create_node_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_create_device_at_) || !defined(_di_f_file_create_node_at_) || !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_create_node_at(const int at_id, const f_string_static_t path, const mode_t mode, const dev_t device) {

    if (mknodat(at_id, path.string, mode, device) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_create_device_at_) || !defined(_di_f_file_create_node_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_flush_) || !defined(_di_f_file_close_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_stream_close_)
  f_status_t private_f_file_flush(const int id) {

    if (fsync(id) < 0) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EINVAL) return F_status_set_error(F_supported_not);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EROFS) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_file_synchronize);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_flush_) || !defined(_di_f_file_close_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_stream_close_)

#if !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)
  f_status_t private_f_file_link(const f_string_static_t target, const f_string_static_t point) {

    if (symlink(target.string, point.string) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_link_at(const int at_id, const f_string_static_t target, const f_string_static_t point) {

    if (symlinkat(target.string, at_id, point.string) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_link_read_) || !defined(_di_f_file_copy_)
  f_status_t private_f_file_link_read(const f_string_static_t path, const off_t size, f_string_dynamic_t * const target) {

    target->used = 0;

    f_status_t status = f_string_dynamic_increase_by(size + 1, target);
    if (F_status_is_error(status)) return status;

    if (size) {
      if (readlink(path.string, target->string, size) < 0) {
        if (errno == EACCES) return F_status_set_error(F_access_denied);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == ELOOP) return F_status_set_error(F_loop);
        if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
        if (errno == ENOENT) return F_status_set_error(F_file_found_not);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ENOTDIR) return F_status_set_error(F_directory_not);

        return F_status_set_error(F_failure);
      }
    }

    target->used = size;

    status = f_string_dynamic_terminate_after(target);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_file_link_read_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_link_read_at_) || !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_link_read_at(const int at_id, const f_string_static_t path, const off_t size, f_string_dynamic_t * const target) {

    target->used = 0;

    f_status_t status = f_string_dynamic_increase_by(size + 1, target);
    if (F_status_is_error(status)) return status;

    if (size) {
      if (readlinkat(at_id, path.string, target->string, size) < 0) {
        if (errno == EACCES) return F_status_set_error(F_access_denied);
        if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == ELOOP) return F_status_set_error(F_loop);
        if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
        if (errno == ENOENT) return F_status_set_error(F_file_found_not);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);
        if (errno == ENOTDIR) return F_status_set_error(F_directory_not);

        return F_status_set_error(F_failure);
      }
    }

    target->used = size;

    status = f_string_dynamic_terminate_after(target);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // !defined(_di_f_file_link_read_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_mode_set_) || !defined(_di_f_file_copy_)
  f_status_t private_f_file_mode_set(const f_string_static_t path, const mode_t mode) {

    if (chmod(path.string, mode) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_access_mode);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_mode_set_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_mode_set_at_) || !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_mode_set_at(const int at_id, const f_string_static_t path, const mode_t mode) {

    if (fchmodat(at_id, path.string, mode, 0) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EPERM) return F_status_set_error(F_access_mode);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_mode_set_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)
  f_status_t private_f_file_open(const f_string_static_t path, const mode_t mode, f_file_t * const file) {

    file->id = open(path.string, file->flag, mode);

    if (file->id == -1) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EISDIR) return F_status_set_error(F_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_supported_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_copy_at_) || !defined(_di_f_file_clone_at_) || !defined(_di_f_file_open_at_) || !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_open_at(const int at_id, const f_string_static_t path, const mode_t mode, f_file_t * const file) {

    file->id = openat(at_id, path.string, file->flag, mode);

    if (file->id == -1) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EISDIR) return F_status_set_error(F_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_supported_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_copy_at_) || !defined(_di_f_file_clone_at_) || !defined(_di_f_file_open_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_role_change_) || !defined(_di_f_file_copy_)
  f_status_t private_f_file_role_change(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference) {

    int result = 0;

    if (uid != -1) {
      if (dereference) {
        result = chown(path.string, uid, -1);
      }
      else {
        result = lchown(path.string, uid, -1);
      }

      if (result < 0 && errno == EPERM) {
        return F_status_set_error(F_access_owner);
      }
    }

    if (result == 0 && gid != -1) {
      if (dereference) {
        result = chown(path.string, -1, gid);
      }
      else {
        result = lchown(path.string, -1, gid);
      }

      if (result < 0 && errno == EPERM) {
        return F_status_set_error(F_access_group);
      }
    }

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_role_change_) || !defined(_di_f_file_copy_)

#if !defined(_di_f_file_role_change_at_) || !defined(_di_f_file_copy_at_)
  f_status_t private_f_file_role_change_at(const int at_id, const f_string_static_t path, const uid_t uid, const gid_t gid, const int flag) {

    int result = 0;

    if (uid != -1) {
      result = fchownat(at_id, path.string, uid, -1, flag);

      if (result < 0 && errno == EPERM) {
        return F_status_set_error(F_access_owner);
      }
    }

    if (result == 0 && gid != -1) {
      result = fchownat(at_id, path.string, -1, gid, flag);

      if (result < 0 && errno == EPERM) {
        return F_status_set_error(F_access_group);
      }
    }

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_role_change_at_) || !defined(_di_f_file_copy_at_)

#if !defined(_di_f_file_clone_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_exists_) || !defined(_di_f_file_group_read_) || !defined(_di_f_file_is_) || !defined(_di_f_file_link_read_) || !defined(_di_f_file_mode_read_) || !defined(_di_f_file_owner_read_) || !defined(_di_f_file_size_) || !defined(_di_f_file_stat_) || !defined(_di_f_file_touch_) || !defined(_di_f_file_type_)
  f_status_t private_f_file_stat(const f_string_static_t path, const bool dereference, struct stat * const file_stat) {

    if ((dereference ? stat(path.string, file_stat) : lstat(path.string, file_stat)) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_file_stat);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_clone_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_exists_) || !defined(_di_f_file_group_read_) || !defined(_di_f_file_is_) || !defined(_di_f_file_link_read_) || !defined(_di_f_file_mode_read_) || !defined(_di_f_file_owner_read_) || !defined(_di_f_file_size_) || !defined(_di_f_file_stat_) || !defined(_di_f_file_touch_) || !defined(_di_f_file_type_)

#if !defined(_di_f_file_exists_at_) || !defined(_di_f_file_link_read_at_) || !defined(_di_f_file_mode_read_at_) || !defined(_di_f_file_size_at_) || !defined(_di_f_file_stat_at_) || !defined(_di_f_file_touch_at_) || !defined(_di_f_file_type_at_)
  f_status_t private_f_file_stat_at(const int at_id, const f_string_static_t path, const int flag, struct stat * const file_stat) {

    if (fstatat(at_id, path.string, file_stat, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_file_stat);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_exists_at_) || !defined(_di_f_file_link_read_at_) || !defined(_di_f_file_mode_read_at_) || !defined(_di_f_file_size_at_) || !defined(_di_f_file_stat_at_) || !defined(_di_f_file_touch_at_) || !defined(_di_f_file_type_at_)

#if !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)
  f_status_t private_f_file_stat_by_id(const int id, struct stat * const file_stat) {

    if (fstat(id, file_stat) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_file_stat);
    }

    return F_none;
  }
#endif // !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)

#if !defined(_di_f_file_stream_open_descriptor_) || !defined(_di_f_file_stream_open_) || !defined(_di_f_file_stream_reopen_)
  const f_string_t private_f_file_stream_open_mode_determine(const int flag) {

    if (flag & F_file_flag_read_write_d) {
      if (flag & F_file_flag_truncate_d) {
        return f_file_open_mode_read_truncate_s.string;
      }

      if (flag & F_file_flag_append_d) {
        return f_file_open_mode_read_append_s.string;
      }

      // Failsafe to read write prepend.
      return f_file_open_mode_read_write_s.string;
    }
    else if (flag & F_file_flag_write_only_d) {
      if (flag & F_file_flag_truncate_d) {
        return f_file_open_mode_truncate_s.string;
      }

      // Failsafe to append.
      return f_file_open_mode_append_s.string;
    }

    // Failsafe to read only.
    return f_file_open_mode_read_s.string;
  }
#endif // !defined(_di_f_file_stream_open_descriptor_) || !defined(_di_f_file_stream_open_) || !defined(_di_f_file_stream_reopen_)

#if !defined(f_file_stream_write) || !defined(_di_f_file_stream_write_block_) || !defined(f_file_stream_write_until) || !defined(f_file_stream_write_range)
  f_status_t private_f_file_stream_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written) {

    *written = 0;

    f_array_length_t write_amount = 1;
    f_array_length_t write_size = file.size_write;
    f_array_length_t write_max = total;

    ssize_t size_write = 0;

    if (write_max < file.size_write) {
      write_amount = 1;
      write_size = write_max;
    }
    else if (file.size_write > total) {
      write_amount = total / file.size_write;

      if (total % file.size_write) {
        ++write_amount;
      }
    }

    flockfile(file.stream);

    while (*written < write_max) {

      size_write = fwrite_unlocked(buffer.string + *written, write_amount, write_size, file.stream);

      if (ferror_unlocked(file.stream)) {
        funlockfile(file.stream);

        return F_status_set_error(F_file_write);
      }

      *written += size_write * write_amount;

      if (!size_write) {
        funlockfile(file.stream);

        return F_none_stop;
      }
    } // while

    funlockfile(file.stream);

    return F_none;
  }
#endif // !defined(f_file_stream_write) || !defined(_di_f_file_stream_write_block_) || !defined(f_file_stream_write_until) || !defined(f_file_stream_write_range)

#if !defined(f_file_write) || !defined(_di_f_file_write_block_) || !defined(f_file_write_until) || !defined(f_file_write_range)
  f_status_t private_f_file_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written) {

    *written = 0;

    f_array_length_t write_size = file.size_write;
    f_array_length_t write_max = total;

    ssize_t size_write = 0;

    if (write_max < file.size_write) {
      write_size = write_max;
    }

    while (*written < write_max && (size_write = write(file.id, buffer.string + *written, write_size)) > 0) {

      *written += size_write;

      if (*written + write_size > write_max) {
        write_size = write_max - *written;
      }
    } // while

    if (!size_write) {
      return F_none_stop;
    }

    if (size_write < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_file_write);
    }

    return F_none;
  }
#endif // !defined(f_file_write) || !defined(_di_f_file_write_block_) || !defined(f_file_write_until) || !defined(f_file_write_range)

#ifdef __cplusplus
} // extern "C"
#endif
