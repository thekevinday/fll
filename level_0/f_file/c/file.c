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
      if (errno == ENOENT) {
        return f_false;
      }

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
      else if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }

      return f_status_set_error(f_false);
    }

    return f_true;
  }
#endif // _di_f_file_access_

#ifndef _di_f_file_change_owner_
  f_return_status f_file_change_owner(const f_string path, const uid_t uid, const gid_t gid) {
    return private_f_file_change_owner(path, uid, gid);
  }
#endif // _di_f_file_change_owner_

#ifndef _di_f_file_copy_
  f_return_status f_file_copy(const f_string source, const f_string destination, const mode_t mode, const f_number_unsigned size_block, const bool exclusive) {
    #ifndef _di_level_0_parameter_checking_
      if (size_block == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    status = private_f_file_create(destination, mode, exclusive);
    if (f_status_is_error(status)) return status;

    f_file file_source = f_file_initialize;
    f_file file_destination = f_file_initialize;

    file_destination.mode = f_file_write_create;

    status = private_f_file_open(&file_source, source);
    if (f_status_is_error(status)) return status;

    status = private_f_file_open(&file_destination, destination);
    if (f_status_is_error(status)) {
      private_f_file_close(&file_source);
      return status;
    }

    ssize_t size_read = 0;
    ssize_t size_write = 0;
    char *buffer[size_block];

    memset(buffer, 0, size_block);

    while ((size_read = read(file_source.id, buffer, size_block)) > 0) {
      size_write = write(file_destination.id, buffer, size_read);

      if (size_write < 0 || size_write != size_read) {
        private_f_file_close(&file_destination);
        private_f_file_close(&file_source);

        return f_status_set_error(f_file_error_write);
      }
    } // while

    private_f_file_close(&file_destination);
    private_f_file_close(&file_source);

    if (size_read < 0) return f_status_set_error(f_file_error_read);

    return f_none;
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

    status = private_f_file_stat(source, &source_stat);
    if (f_status_is_error(status)) return status;

    status = private_f_file_create(destination, source_stat.st_mode, exclusive);
    if (f_status_is_error(status)) return status;

    // guarantee the file mode is updated (create does not set mode for existing files).
    status = private_f_file_change_mode(destination, source_stat.st_mode);
    if (f_status_is_error(status)) return status;

    if (roles) {
      status = private_f_file_change_owner(destination, source_stat.st_uid, source_stat.st_gid);
      if (f_status_is_error(status)) return status;
    }

    f_file file_source = f_file_initialize;
    f_file file_destination = f_file_initialize;

    file_destination.mode = f_file_write_create;

    status = private_f_file_open(&file_source, source);
    if (f_status_is_error(status)) return status;

    status = private_f_file_open(&file_destination, destination);
    if (f_status_is_error(status)) {
      private_f_file_close(&file_source);
      return status;
    }

    ssize_t size_read = 0;
    ssize_t size_write = 0;
    char *buffer[size_block];

    memset(buffer, 0, size_block);

    while ((size_read = read(file_source.id, buffer, size_block)) > 0) {
      size_write = write(file_destination.id, buffer, size_read);

      if (size_write < 0 || size_write != size_read) {
        private_f_file_close(&file_destination);
        private_f_file_close(&file_source);

        return f_status_set_error(f_file_error_write);
      }
    } // while

    private_f_file_close(&file_destination);
    private_f_file_close(&file_source);

    if (size_read < 0) return f_status_set_error(f_file_error_read);

    return f_none;
  }
#endif // _di_f_file_clone_

#ifndef _di_f_file_close_
  f_return_status f_file_close(f_file *file) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_close(file);
  }
#endif // _di_f_file_close_

#ifndef _di_f_file_create_
  f_return_status f_file_create(f_string path, const mode_t mode, const bool exclusive) {
    return private_f_file_create(path, mode, exclusive);
  }
#endif // _di_f_file_create_

#ifndef _di_f_file_exists_at_
  f_return_status f_file_exists_at(const int directory_file_descriptor, const f_string path, const int flags) {
    #ifndef _di_level_0_parameter_checking_
      if (directory_file_descriptor == 0) return f_status_set_error(f_invalid_parameter);
      if (path == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (faccessat(directory_file_descriptor, path, F_OK, flags)) {
      if (errno == ENOENT) {
        return f_false;
      }

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
      else if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }
      else if (errno == EBADF) {
        return f_status_set_error(f_invalid_descriptor);
      }
      else if (errno == EINVAL) {
        return f_status_set_error(f_invalid_parameter);
      }

      return f_status_set_error(f_false);
    }

    return f_true;
  }
#endif // _di_f_file_exists_at_

#ifndef _di_f_file_flush_
  f_return_status f_file_flush(f_file *file) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    if (fflush(file->address) == 0) return f_none;

    return f_status_set_error(f_file_error_flush);
  }
#endif // _di_f_file_flush_

#ifndef _di_f_file_exists_
  f_return_status f_file_exists(const f_string path) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
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
        return f_false;
      }
      else if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }

      return f_status_set_error(f_file_error_stat);
    }

    return f_true;
  }
#endif // _di_f_file_exists_

#ifndef _di_f_file_is_
  f_return_status f_file_is(const f_string path, const int type) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
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
        return f_file_not_found;
      }
      else if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }

      return f_status_set_error(f_file_error_stat);
    }

    if (f_macro_file_type_get(file_stat.st_mode) == type) return f_true;

    return f_false;
  }
#endif // _di_f_file_is_

#ifndef _di_f_file_is_at_
  f_return_status f_file_is_at(const int file_id, const f_string path, const int type, const bool follow) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(file_id, path, &file_stat, follow ? 0 : AT_SYMLINK_NOFOLLOW) < 0) {
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
        return f_file_not_found;
      }
      else if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }

      return f_status_set_error(f_file_error_stat);
    }

    if (file_stat.st_mode == (S_IFMT & S_IFDIR)) return f_true;

    return f_false;
  }
#endif // _di_f_file_is_at_

#ifndef _di_f_file_open_
  f_return_status f_file_open(f_file *file, const f_string path) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_open(file, path);
  }
#endif // _di_f_file_open_

#ifndef _di_f_file_read_
  f_return_status f_file_read(f_file *file, f_string_dynamic *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_chunk == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_block == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    int result = fread(buffer->string + buffer->used, file->size_chunk, file->size_block, file->address);

    if (file->address == 0) return f_status_set_error(f_file_error_read);
    if (ferror(file->address) != 0) return f_status_set_error(f_file_error_read);

    if (file->size_chunk > 1) {
      buffer->used += result * file->size_chunk;
    }
    else {
      buffer->used += result;
    }

    if (feof(file->address)) return f_none_on_eof;

    return f_none;
  }
#endif // _di_f_file_read_

#ifndef _di_f_file_read_at_
  f_return_status f_file_read_at(f_file *file, f_string_dynamic *buffer, const f_file_position position) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_chunk == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_block == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);

      // when the available buffer size is smaller than the total elements, then there is not enough allocated memory available to read the file.
      if (position.total > 0) {
        if (buffer->used + position.total > buffer->size) return f_status_set_error(f_invalid_parameter);
      }
      else {
        if (buffer->used + (file->size_chunk * file->size_block) > buffer->size) return f_status_set_error(f_invalid_parameter);
      }
    #endif // _di_level_0_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    // first seek to 'where' we need to begin the read.
    long current_file_position = ftell(file->address);

    if (current_file_position == -1) return f_status_set_error(f_file_error_seek);

    int result = 0;

    if (current_file_position > position.start) {
      result = f_macro_file_seek_to(file->address, file->size_chunk * (0 - (current_file_position - position.start)));
    }
    else if (current_file_position < position.start) {
      result = f_macro_file_seek_to(file->address, file->size_chunk * (position.start - current_file_position));
    }

    if (result != 0) return f_status_set_error(f_file_error_seek);

    // now do the actual read
    if (position.total == 0) {
      result = fread(buffer->string + buffer->used, file->size_chunk, file->size_block, file->address);
    }
    else {
      result = fread(buffer->string + buffer->used, file->size_chunk, position.total, file->address);
    }

    if (file->address == 0) return f_status_set_error(f_file_error_read);
    if (ferror(file->address) != 0) return f_status_set_error(f_file_error_read);

    f_number_unsigned bytes_total;

    if (file->size_chunk > 1) {
      buffer->used += result * file->size_chunk;
    }
    else {
      buffer->used += result;
    }

    if (feof(file->address)) return f_none_on_eof;

    return f_none;
  }
#endif // _di_f_file_read_at_

#ifndef _di_f_file_read_until_
  f_return_status f_file_read_until(f_file *file, f_string_dynamic *buffer, const f_string_length total) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_chunk == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_block == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);

      // when the available buffer size is smaller than the total elements, then there is not enough allocated memory available to read the file.
      if (total > 0) {
        if (buffer->used + total > buffer->size) return f_status_set_error(f_invalid_parameter);
      }
      else {
        if (buffer->used + (file->size_chunk * file->size_block) > buffer->size) return f_status_set_error(f_invalid_parameter);
      }
    #endif // _di_level_0_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    int result;

    if (total == 0) {
      result = fread(buffer->string + buffer->used, file->size_chunk, file->size_block, file->address);
    }
    else {
      result = fread(buffer->string + buffer->used, file->size_chunk, total, file->address);
    }

    if (file->address == 0) return f_status_set_error(f_file_error_read);
    if (ferror(file->address) != 0) return f_status_set_error(f_file_error_read);

    if (file->size_chunk > 1) {
      buffer->used += result * file->size_chunk;
    }
    else {
      buffer->used += result;
    }

    if (feof(file->address)) return f_none_on_eof;

    return f_none;
  }
#endif // _di_f_file_read_until_

#ifndef _di_f_file_remove_
  f_return_status f_file_remove(const f_string path) {
    if (unlink(path) < 0) {
      if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == EBUSY) {
        return f_status_set_error(f_busy);
      }
      else if (errno == EIO) {
        return f_status_set_error(f_error_input_output);
      }
      else if (errno == EISDIR) {
        return f_status_set_error(f_file_is_type_directory);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }
      else if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_status_set_error(f_invalid_name);
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

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_file_remove_

#ifndef _di_f_file_stat_
  f_return_status f_file_stat(const f_string path, struct stat *file_stat) {
    return private_f_file_stat(path, file_stat);
  }
#endif // _di_f_file_stat_

#ifndef _di_f_file_stat_at_
  f_return_status f_file_stat_at(const int file_id, const f_string path, struct stat *file_stat, const int flags) {
    #ifndef _di_level_0_parameter_checking_
      if (file_id <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (fstatat(file_id, path, file_stat, flags) < 0) {
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
        return f_file_not_found;
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
#endif // _di_f_file_stat_by_at_

#ifndef _di_f_file_stat_by_id_
  f_return_status f_file_stat_by_id(const int file_id, struct stat *file_stat) {
    #ifndef _di_level_0_parameter_checking_
      if (file_id <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = fstat(file_id, file_stat);

    if (result < 0) {
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
        return f_file_not_found;
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
#endif // _di_f_file_stat_by_id_

#ifdef __cplusplus
} // extern "C"
#endif
