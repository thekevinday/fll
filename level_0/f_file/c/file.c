/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides structures and data types for a file I/O.
 * Provides operations for opening/closing files.
 */
#include <level_0/file.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_open_
  f_return_status f_file_open(f_file *file, const f_string file_name) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    // if file->mode is unset, then this may cause a segfault.
    if (file->mode == 0) return f_status_set_error(f_invalid_parameter);

    file->address = fopen(file_name, file->mode);

    if (file->address == 0) return f_status_set_error(f_file_not_found);
    if (ferror(file->address) != 0) return f_status_set_error(f_file_error_open);

    file->id = fileno(file->address);

    if (file->id == -1) return f_status_set_error(f_file_error_descriptor);

    return f_none;
  }
#endif // _di_f_file_open_

#ifndef _di_f_file_close_
  f_return_status f_file_close(f_file *file) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    // if we were given a file descriptor as well, make sure to flush all changes to the disk that are not flushed by the 'fflush()' command
    if (file->id) {
      // make sure all unfinished data gets completed.
      if (fsync(file->id) != 0) return f_status_set_error(f_file_error_synchronize);
    }

    if (fclose(file->address) == 0) {
      file->address = 0;
      return f_none;
    }

    return f_status_set_error(f_file_error_close);
  }
#endif // _di_f_file_close_

#ifndef _di_f_file_exists_
  f_return_status f_file_exists(const f_string file_name) {
    #ifndef _di_level_0_parameter_checking_
      if (file_name == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (access(file_name, F_OK)) {
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
#endif // _di_f_file_exists_

#ifndef _di_f_file_exists_at_
  f_return_status f_file_exists_at(const int directory_file_descriptor, const f_string file_name, const int flags) {
    #ifndef _di_level_0_parameter_checking_
      if (directory_file_descriptor == 0) return f_status_set_error(f_invalid_parameter);
      if (file_name == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (faccessat(directory_file_descriptor, file_name, F_OK, flags)) {
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

    if (feof(file->address)) {
      return f_none_on_eof;
    }

    return f_none;
  }
#endif // _di_f_file_read_

#ifndef _di_f_file_read_range_
  f_return_status f_file_read_range(f_file *file, f_string_dynamic *buffer, const f_string_length buffer_start, const f_string_length total_elements) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_chunk == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_block == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);
      if (buffer_start < 0) return f_status_set_error(f_invalid_parameter);
      if (total_elements == 0) return f_status_set_error(f_invalid_parameter);

      // when the available buffer size is smaller than the total elements, then there is not enough allocated memory available to read the file.
      if (total_elements > 0) {
        if (buffer_start + total_elements > buffer->size) return f_status_set_error(f_invalid_parameter);
      }
    #endif // _di_level_0_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    int result = 0;

    if (total_elements == 0) {
      result = fread(buffer->string + buffer_start, file->size_chunk, file->size_block, file->address);
    }
    else {
      result = fread(buffer->string + buffer_start, file->size_chunk, total_elements, file->address);
    }

    if (file->address == 0) return f_status_set_error(f_file_error_read);
    if (ferror(file->address) != 0) return f_status_set_error(f_file_error_read);

    f_string_length bytes_total;

    if (file->size_chunk > 1) {
      bytes_total = result * file->size_chunk;
    }
    else {
      bytes_total = result;
    }

    // Save how much of our allocated buffer is actually used.
    if (buffer_start + bytes_total > buffer->used) {
      buffer->used = buffer_start + bytes_total;
    }

    // Append an EOS only when the total elements were set to 0.
    if (total_elements == 0) {
      buffer->string[buffer->used] = f_string_eos;
    }

    // Make sure to communicate that we are done without a problem and the EOF was reached.
    if (feof(file->address)) {
      return f_none_on_eof;
    }

    return f_none;
  }
#endif // _di_f_file_read_range_

#ifndef _di_f_file_read_at_
  f_return_status f_file_read_at(f_file *file, f_string_dynamic *buffer, const f_file_position position) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_chunk == 0) return f_status_set_error(f_invalid_parameter);
      if (file->size_block == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);
      if (position.buffer_start < 0) return f_status_set_error(f_invalid_parameter);
      if (position.file_start < 0) return f_status_set_error(f_invalid_parameter);
      if (position.total_elements < 0) return f_status_set_error(f_invalid_parameter);

      // when the available buffer size is smaller than the total elements, then there is not enough allocated memory available to read the file.
      if (position.total_elements > 0) {
        if (position.buffer_start + position.total_elements > buffer->size) return f_status_set_error(f_invalid_parameter);
      }
    #endif // _di_level_0_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    // first seek to 'where' we need to begin the read.
    unsigned long current_file_position = ftell(file->address);

    if (current_file_position == (unsigned long) -1) return f_status_set_error(f_file_error_seek);

    int result = 0;

    if (current_file_position > position.file_start) {
      result = f_macro_file_seek_to(file->address, file->size_chunk * (0 - (current_file_position - position.file_start)));
    }
    else if (current_file_position < position.file_start) {
      result = f_macro_file_seek_to(file->address, file->size_chunk * (position.file_start - current_file_position));
    }

    if (result != 0) return f_status_set_error(f_file_error_seek);

    // now do the actual read
    if (position.total_elements == 0) {
      result = fread(buffer->string + position.buffer_start, file->size_chunk, file->size_block, file->address);
    }
    else {
      result = fread(buffer->string + position.buffer_start, file->size_chunk, position.total_elements, file->address);
    }

    if (file->address == 0) return f_status_set_error(f_file_error_read);
    if (ferror(file->address) != 0) return f_status_set_error(f_file_error_read);

    f_number_unsigned bytes_total;

    if (file->size_chunk > 1) {
      bytes_total = result * file->size_chunk;
    }
    else {
      bytes_total = result;
    }

    // now save how much of our allocated buffer is actually used.
    // also make sure that we aren't making used space vanish.
    if (position.buffer_start + bytes_total > buffer->used) {
      buffer->used = position.buffer_start + bytes_total;
    }

    // append an EOS only when the total elements were set to 0.
    if (position.total_elements == 0) {
      buffer->string[buffer->used] = f_string_eos;
    }

    if (feof(file->address)) {
      return f_none_on_eof;
    }

    return f_none;
  }
#endif // _di_f_file_read_at_

#ifndef _di_f_file_stat_
  f_return_status f_file_stat(const f_string file_name, struct stat *file_stat) {
    if (stat(file_name, file_stat) < 0) {
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
#endif // _di_f_file_stat_

#ifndef _di_f_file_stat_at_
  f_return_status f_file_stat_at(const int file_id, const f_string file_name, struct stat *file_stat, const int flags) {
    #ifndef _di_level_0_parameter_checking_
      if (file_id <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = fstatat(file_id, file_name, file_stat, flags);
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
