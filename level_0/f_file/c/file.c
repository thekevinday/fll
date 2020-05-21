#include <level_0/file.h>
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_access_
  f_return_status f_file_access(const f_string path) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (access(path, F_OK)) {
      if (errno == ENOENT) return f_false;
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ELOOP) return f_status_set_error(f_loop);

      return f_status_set_error(f_false);
    }

    return f_true;
  }
#endif // _di_f_file_access_

#ifndef _di_f_file_change_mode_
  f_return_status f_file_change_mode(const f_string path, const mode_t mode, const bool dereference) {
    return private_f_file_change_mode(path, mode, dereference);
  }
#endif // _di_f_file_change_mode_

#ifndef _di_f_file_change_mode_at_
  f_return_status f_file_change_mode_at(const int at_id, const f_string path, const mode_t mode, const int flags) {
    return private_f_file_change_mode_at(at_id, path, mode, flags);
  }
#endif // _di_f_file_change_mode_at_

#ifndef _di_f_file_change_owner_
  f_return_status f_file_change_owner(const f_string path, const uid_t uid, const gid_t gid, const bool dereference) {
    return private_f_file_change_owner(path, uid, gid, dereference);
  }
#endif // _di_f_file_change_owner_

#ifndef _di_f_file_change_owner_at_
  f_return_status f_file_change_owner_at(const int at_id, const f_string path, const uid_t uid, const gid_t gid, const int flags) {
    return private_f_file_change_owner_at(at_id, path, uid, gid, flags);
  }
#endif // _di_f_file_change_owner_at_

#ifndef _di_f_file_copy_
  f_return_status f_file_copy(const f_string source, const f_string destination, const mode_t mode, const f_number_unsigned size_block, const bool exclusive) {
    #ifndef _di_level_0_parameter_checking_
      if (size_block == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;
    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = private_f_file_stat(source, &source_stat, f_false);
    if (f_status_is_error(status)) return status;

    if (f_macro_file_type_is_file(source_stat.st_mode)) {
      status = private_f_file_create(destination, mode, exclusive, f_false);
      if (f_status_is_error(status)) return status;

      if (!exclusive) {
        status = private_f_file_change_mode(destination, mode, f_false);
        if (f_status_is_error(status)) return status;
      }

      return private_f_file_copy_content(source, destination, size_block);
    }
    else if (f_macro_file_type_is_link(source_stat.st_mode)) {
      status = private_f_file_link(destination, source);
      if (f_status_set_fine(status) == f_file_found) {
        if (exclusive) return status;
      }
      else if (f_status_is_error(status)) {
        return status;
      }

      status = private_f_file_change_mode(destination, mode, f_false);
      if (f_status_is_error(status)) return status;

      return f_none;
    }

    return f_unsupported;
  }
#endif // _di_f_file_copy_

#ifndef _di_f_file_clone_
  f_return_status f_file_clone(const f_string source, const f_string destination, const f_number_unsigned size_block, const bool exclusive, const bool roles) {
    #ifndef _di_level_0_parameter_checking_
      if (size_block == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;
    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = private_f_file_stat(source, &source_stat, f_false);
    if (f_status_is_error(status)) return status;

    if (f_macro_file_type_is_file(source_stat.st_mode)) {
      status = private_f_file_create(destination, source_stat.st_mode, exclusive, f_false);
      if (f_status_is_error(status)) return status;

      if (!exclusive) {
        status = private_f_file_change_mode(destination, source_stat.st_mode, f_false);
        if (f_status_is_error(status)) return status;
      }

      if (roles) {
        status = private_f_file_change_owner(destination, source_stat.st_uid, source_stat.st_gid, f_false);
        if (f_status_is_error(status)) return status;
      }

      return private_f_file_copy_content(source, destination, size_block);
    }
    else if (f_macro_file_type_is_link(source_stat.st_mode)) {
      status = private_f_file_link(destination, source);
      if (f_status_set_fine(status) == f_file_found) {
        if (exclusive) return status;
      }
      else if (f_status_is_error(status)) {
        return status;
      }

      status = private_f_file_change_mode(destination, source_stat.st_mode, f_false);
      if (f_status_is_error(status)) return status;

      if (roles) {
        status = private_f_file_change_owner(destination, source_stat.st_uid, source_stat.st_gid, f_false);
        if (f_status_is_error(status)) return status;
      }

      return f_none;
    }

    return f_unsupported;
  }
#endif // _di_f_file_clone_

#ifndef _di_f_file_close_
  f_return_status f_file_close(int *id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_close(id);
  }
#endif // _di_f_file_close_

#ifndef _di_f_file_create_
  f_return_status f_file_create(const f_string path, const mode_t mode, const bool exclusive, const bool dereference) {
    return private_f_file_create(path, mode, exclusive, dereference);
  }
#endif // _di_f_file_create_

#ifndef _di_f_file_create_at_
  f_return_status f_file_create_at(const int at_id, const f_string path, const mode_t mode, const bool exclusive, const bool dereference) {
    return private_f_file_create_at(at_id, path, mode, exclusive, dereference);
  }
#endif // _di_f_file_create_at_

#ifndef _di_f_file_exists_
  f_return_status f_file_exists(const f_string path) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == ENOENT) return f_false;
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ELOOP) return f_status_set_error(f_loop);

      return f_status_set_error(f_file_error_stat);
    }

    return f_true;
  }
#endif // _di_f_file_exists_

#ifndef _di_f_file_exists_at_
  f_return_status f_file_exists_at(const int at_id, const f_string path, const bool follow) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path, &file_stat, follow ? 0 : AT_SYMLINK_NOFOLLOW) < 0) {
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

    return f_true;
  }
#endif // _di_f_file_exists_at_

#ifndef _di_f_file_flush_
  f_return_status f_file_flush(const int id) {
    return private_f_file_flush(id);
  }
#endif // _di_f_file_flush_

#ifndef _di_f_file_link_
  f_return_status f_file_link(const f_string target, const f_string point) {
    return private_f_file_link(target, point);
  }
#endif // _di_f_file_link_

#ifndef _di_f_file_link_at_
  f_return_status f_file_link_at(const int at_id, const f_string target, const f_string point) {
    return private_f_file_link_at(at_id, target, point);
  }
#endif // _di_f_file_link_at_

#ifndef _di_f_file_link_hard_
  f_return_status f_file_link_hard(const f_string target, const f_string point) {

    if (link(target, point) < 0) {
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
#endif // _di_f_file_link_hard_

#ifndef _di_f_file_link_hard_at_
  f_return_status f_file_link_hard_at(const int at_id_target, const int at_id_point, const f_string target, const f_string point, const int flags) {

    if (linkat(at_id_target, target, at_id_point, point, flags) < 0) {
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
#endif // _di_f_file_link_hard_at_

#ifndef _di_f_file_is_
  f_return_status f_file_is(const f_string path, const int type) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
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

    if (f_macro_file_type_get(file_stat.st_mode) == type) return f_true;

    return f_false;
  }
#endif // _di_f_file_is_

#ifndef _di_f_file_is_at_
  f_return_status f_file_is_at(const int at_id, const f_string path, const int type, const bool follow) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path, &file_stat, follow ? 0 : AT_SYMLINK_NOFOLLOW) < 0) {
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

    if (file_stat.st_mode == (S_IFMT & S_IFDIR)) return f_true;

    return f_false;
  }
#endif // _di_f_file_is_at_

#ifndef _di_f_file_open_
  f_return_status f_file_open(const f_string path, const int flags, const mode_t mode, f_file *file) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_open(path, mode, flags, file);
  }
#endif // _di_f_file_open_

#ifndef _di_f_file_open_at_
  f_return_status f_file_open_at(const int at_id, const f_string path, const int flags, const mode_t mode, f_file *file) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_open_at(at_id, path, flags, mode, file);
  }
#endif // _di_f_file_open_at_

#ifndef _di_f_file_read_
  f_return_status f_file_read(f_file *file, f_string_dynamic *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_chunk == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_block == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file->id <= 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;
    ssize_t size_read = 0;

    // use a custom buffer so that memory is allocated post-read instead of pre-read.
    const f_string_length buffer_size = file->size_chunk * file->size_block;
    char buffer_read[buffer_size];

    memset(&buffer_read, 0, sizeof(buffer_size));

    while ((size_read = read(file->id, buffer_read, buffer_size)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return f_status_set_error(f_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (f_status_is_error(status)) return status;
      }

      memcpy(buffer->string + buffer->used, buffer_read, buffer_size);
      buffer->used += size_read;
    } // while

    if (size_read == 0) {
      return f_none_on_eof;
    }

    if (size_read < 0) {
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
#endif // _di_f_file_read_

#ifndef _di_f_file_read_block_
  f_return_status f_file_read_block(f_file *file, f_string_dynamic *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_chunk == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_block == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file->id <= 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;
    ssize_t size_read = 0;

    const f_string_length buffer_size = file->size_chunk * file->size_block;
    char buffer_read[buffer_size];

    memset(&buffer_read, 0, sizeof(buffer_size));

    if ((size_read = read(file->id, buffer_read, buffer_size)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return f_status_set_error(f_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (f_status_is_error(status)) return status;
      }

      memcpy(buffer->string + buffer->used, buffer_read, buffer_size);
      buffer->used += size_read;
    }

    if (size_read == 0) {
      return f_none_on_eof;
    }

    if (size_read < 0) {
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
#endif // _di_f_file_read_block_

#ifndef _di_f_file_read_until_
  f_return_status f_file_read_until(f_file *file, f_string_dynamic *buffer, const f_string_length total) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_chunk == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_block == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file->id <= 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;
    ssize_t size_read = 0;

    f_string_length buffer_size = file->size_chunk * file->size_block;
    f_string_length buffer_count = 0;

    if (total < buffer_size) {
      buffer_size = total;
    }

    char buffer_read[buffer_size];

    memset(&buffer_read, 0, sizeof(buffer_size));

    if ((size_read = read(file->id, buffer_read, buffer_size)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return f_status_set_error(f_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (f_status_is_error(status)) return status;
      }

      memcpy(buffer->string + buffer->used, buffer_read, buffer_size);
      buffer->used += size_read;
      buffer_count += size_read;
    }

    if (size_read == 0) {
      return f_none_on_eof;
    }

    if (size_read < 0) {
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
#endif // _di_f_file_read_until_

#ifndef _di_f_file_remove_
  f_return_status f_file_remove(const f_string path) {

    if (unlink(path) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EBUSY) return f_status_set_error(f_busy);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == EISDIR) return f_status_set_error(f_file_is_type_directory);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_file_remove_

#ifndef _di_f_file_remove_at_
  f_return_status f_file_remove_at(const int at_id, const f_string path, const int flags) {

    if (unlinkat(at_id, path, flags) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EBUSY) return f_status_set_error(f_busy);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == EISDIR) return f_status_set_error(f_file_is_type_directory);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_file_remove_at_

#ifndef _di_f_file_seek_
  f_return_status f_file_seek(const int id, const int whence, const f_string_length offset, f_string_length *seeked) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return f_status_set_error(f_invalid_parameter);
      if (whence < 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    *seeked = lseek(id, offset, whence);

    if (*seeked < 0) {
      if (errno == EBADF) return f_status_set_error(f_file_error_descriptor);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == ENXIO) return f_status_set_error(f_out_of_bound);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ESPIPE) return f_status_set_error(f_file_is_type_pipe);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_file_seek_

#ifndef _di_f_file_size_
  f_return_status f_file_size(const f_string path, const bool dereference, f_string_length *size) {
    #ifndef _di_level_0_parameter_checking_
      if (size == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    f_status status = private_f_file_stat(path, dereference, &file_stat);

    if (f_status_is_error(status)) return status;

    *size = file_stat.st_size;

    return f_none;
  }
#endif // _di_f_file_size_

#ifndef _di_f_file_size_at_
  f_return_status f_file_size_at(const int at_id, const f_string path, const bool dereference, f_string_length *size) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return f_status_set_error(f_invalid_parameter);
      if (size == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    f_status status = private_f_file_stat_at(at_id, path, dereference, &file_stat);

    if (f_status_is_error(status)) return status;

    *size = file_stat.st_size;

    return f_none;
  }
#endif // _di_f_file_size_at_

#ifndef _di_f_file_size_by_id_
  f_return_status f_file_size_by_id(const int id, f_string_length *size) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return f_status_set_error(f_invalid_parameter);
      if (size == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    f_status status = private_f_file_stat_by_id(id, &file_stat);

    if (f_status_is_error(status)) return status;

    *size = file_stat.st_size;

    return f_none;
  }
#endif // _di_f_file_size_by_id_

#ifndef _di_f_file_stat_
  f_return_status f_file_stat(const f_string path, const bool dereference, struct stat *file_stat) {
    #ifndef _di_level_0_parameter_checking_
      if (file_stat == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_stat(path, dereference, file_stat);
  }
#endif // _di_f_file_stat_

#ifndef _di_f_file_stat_at_
  f_return_status f_file_stat_at(const int at_id, const f_string path, const int flags, struct stat *file_stat) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return f_status_set_error(f_invalid_parameter);
      if (file_stat == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_stat_at(at_id, path, flags, file_stat);
  }
#endif // _di_f_file_stat_at_

#ifndef _di_f_file_stat_by_id_
  f_return_status f_file_stat_by_id(const int id, struct stat *file_stat) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return f_status_set_error(f_invalid_parameter);
      if (file_stat == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_stat_by_id(id, file_stat);
  }
#endif // _di_f_file_stat_by_id_

#ifdef __cplusplus
} // extern "C"
#endif
