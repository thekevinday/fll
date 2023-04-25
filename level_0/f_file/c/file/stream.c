#include "../file.h"
#include "stream.h"
#include "../private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_stream_close_
  f_status_t f_file_stream_close(f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file->stream) return F_stream_not;

    if (fclose(file->stream) == EOF) {

      // According to man pages, further access to a stream on error results in undefined behavior.
      file->stream = 0;

      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFBIG) return F_status_set_error(F_file_overflow);
      if (errno == EDEADLK) return F_status_set_error(F_deadlock);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_socket_not);
      if (errno == EDQUOT) return F_status_set_error(F_space_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENOLCK) return F_status_set_error(F_lock);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe_not);

      return F_status_set_error(F_file_close);
    }

    file->stream = 0;

    return F_none;
  }
#endif // _di_f_file_stream_close_

#ifndef _di_f_file_stream_flush_
  f_status_t f_file_stream_flush(const f_file_t file) {

    if (!file.stream) return F_stream_not;

    // Only 0 is considered a success and so any non-zero value could be an error.
    if (fflush(file.stream) != 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_file_synchronize);
    }

    return F_none;
  }
#endif // _di_f_file_stream_flush_

#ifndef _di_f_file_stream_lock_
  f_status_t f_file_stream_lock(const f_file_t file) {

    if (!file.stream) return F_stream_not;

    flockfile(file.stream);

    return F_none;
  }
#endif // _di_f_file_stream_lock_

#ifndef _di_f_file_stream_lock_try_
  f_status_t f_file_stream_lock_try(const f_file_t file) {

    if (!file.stream) return F_stream_not;

    if (ftrylockfile(file.stream)) return F_busy;

    return F_none;
  }
#endif // _di_f_file_stream_lock_try_

#ifndef _di_f_file_stream_open_
  f_status_t f_file_stream_open(const f_string_static_t path, const f_string_static_t mode, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) return F_data_not;

    if (mode.used) {
      file->stream = fopen(path.string, mode.string);
    }
    else {
      file->stream = fopen(path.string, private_f_file_stream_open_mode_determine(file->flag));
    }

    if (!file->stream) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);
      if (errno == EISDIR) return F_status_set_error(F_directory);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_support_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_stream_open_

#ifndef _di_f_file_stream_open_descriptor_
  f_status_t f_file_stream_open_descriptor(const f_string_static_t mode, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file->id == -1) return F_file_descriptor_not;

    if (mode.used) {
      file->stream = fdopen(file->id, private_f_file_stream_open_mode_determine(file->flag));
    }
    else {
      file->stream = fdopen(file->id, mode.string);
    }

    if (!file->stream) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFBIG) return F_status_set_error(F_file_overflow);
      if (errno == EDEADLK) return F_status_set_error(F_deadlock);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_socket_not);
      if (errno == EDQUOT) return F_status_set_error(F_space_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENODEV) return F_status_set_error(F_device_not);
      if (errno == ENOLCK) return F_status_set_error(F_lock);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_stream_open_descriptor_

#ifndef _di_f_file_stream_read_
  f_status_t f_file_stream_read(const f_file_t file, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_read) return F_status_set_error(F_parameter);
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) return F_stream_not;

    flockfile(file.stream);

    if (feof_unlocked(file.stream)) {
      funlockfile(file.stream);

      return F_none_eof;
    }

    if (ferror_unlocked(file.stream)) {
      funlockfile(file.stream);

      return F_status_set_error(F_error);
    }

    f_status_t status = F_none;
    size_t size_read = 0;

    do {
      status = f_string_dynamic_increase_by(file.size_read, buffer);

      if (F_status_is_error(status)) {
        funlockfile(file.stream);

        return status;
      }

      size_read = fread_unlocked(buffer->string + buffer->used, sizeof(f_char_t), file.size_read, file.stream);

      if (ferror_unlocked(file.stream)) {
        funlockfile(file.stream);

        return F_status_set_error(F_file_read);
      }

      buffer->used += size_read;

    } while (size_read == file.size_read && !feof_unlocked(file.stream));

    funlockfile(file.stream);

    return F_none_eof;
  }
#endif // _di_f_file_stream_read_

#ifndef _di_f_file_stream_read_block_
  f_status_t f_file_stream_read_block(const f_file_t file, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_read) return F_status_set_error(F_parameter);
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) return F_stream_not;

    flockfile(file.stream);

    if (feof_unlocked(file.stream)) {
      funlockfile(file.stream);

      return F_none_eof;
    }

    if (ferror_unlocked(file.stream)) {
      funlockfile(file.stream);

      return F_status_set_error(F_error);
    }

    {
      const f_status_t status = f_string_dynamic_increase_by(file.size_read, buffer);

      if (F_status_is_error(status)) {
        funlockfile(file.stream);

        return status;
      }
    }

    const size_t size_read = fread_unlocked(buffer->string + buffer->used, sizeof(f_char_t), file.size_read, file.stream);

    if (ferror_unlocked(file.stream)) {
      funlockfile(file.stream);

      return F_status_set_error(F_file_read);
    }

    if (size_read) {
      buffer->used += size_read;
    }

    if (feof_unlocked(file.stream)) {
      funlockfile(file.stream);

      return F_none_eof;
    }

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_f_file_stream_read_block_

#ifndef _di_f_file_stream_read_until_
  f_status_t f_file_stream_read_until(const f_file_t file, const f_array_length_t total, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_read) return F_status_set_error(F_parameter);
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) return F_stream_not;
    if (!total) return F_data_not;

    flockfile(file.stream);

    if (feof_unlocked(file.stream)) {
      funlockfile(file.stream);

      return F_none_eof;
    }

    if (ferror_unlocked(file.stream)) {
      funlockfile(file.stream);

      return F_status_set_error(F_error);
    }

    {
      const f_status_t status = f_string_dynamic_increase_by(total, buffer);

      if (F_status_is_error(status)) {
        funlockfile(file.stream);

        return F_none_eof;
      }
    }

    f_array_length_t buffer_size = file.size_read;
    f_array_length_t buffer_count = 0;

    size_t size_read = 0;

    for (;;) {

      if (buffer_count + buffer_size > total) {
        buffer_size = total - buffer_count;
      }

      size_read = fread_unlocked(buffer->string + buffer->used, sizeof(f_char_t), buffer_size, file.stream);

      if (ferror_unlocked(file.stream)) {
        funlockfile(file.stream);

        return F_status_set_error(F_file_read);
      }

      buffer->used += size_read;

      if (feof_unlocked(file.stream)) {
        funlockfile(file.stream);

        return F_none_eof;
      }

      buffer_count += size_read;

      if (buffer_count >= total) break;
    } // for

    funlockfile(file.stream);

    return F_none_stop;
  }
#endif // _di_f_file_stream_read_until_

#ifndef _di_f_file_stream_reopen_
  f_status_t f_file_stream_reopen(const f_string_static_t path, const f_string_static_t mode, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used && !mode.used) return F_data_not;

    FILE *result = 0;

    if (mode.used) {
      result = freopen(path.used ? path.string : 0, mode.string, file->stream);
    }
    else {
      result = freopen(path.used ? path.string : 0, private_f_file_stream_open_mode_determine(file->flag), file->stream);
    }

    if (!result) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFBIG) return F_status_set_error(F_file_overflow);
      if (errno == EDEADLK) return F_status_set_error(F_deadlock);
      if (errno == EDESTADDRREQ) return F_status_set_error(F_socket_not);
      if (errno == EDQUOT) return F_status_set_error(F_space_not);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENOLCK) return F_status_set_error(F_lock);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EPIPE) return F_status_set_error(F_pipe_not);

      return F_status_set_error(F_failure);
    }

    file->stream = result;

    return F_none;
  }
#endif // _di_f_file_stream_reopen_

#ifndef _di_f_file_stream_unlock_
  f_status_t f_file_stream_unlock(const f_file_t file) {

    if (!file.stream) return F_stream_not;

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_f_file_stream_unlock_

#ifndef _di_f_file_stream_write_
  f_status_t f_file_stream_write(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written) {

    if (!file.stream || !buffer.used || !file.size_write) {
      if (written) {
        *written = 0;
      }

      return file.stream ? F_data_not : F_stream_not;
    }

    f_status_t status = F_none;

    if (written) {
      status = private_f_file_stream_write_until(file, buffer, buffer.used, written);

      if (status == F_none && *written == buffer.used) return F_none_eos;
    }
    else {
      f_array_length_t written_local = 0;

      status = private_f_file_stream_write_until(file, buffer, buffer.used, &written_local);

      if (status == F_none && written_local == buffer.used) return F_none_eos;
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_file_stream_write_

#ifndef _di_f_file_stream_write_block_
  f_status_t f_file_stream_write_block(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written) {

    if (!file.stream || !buffer.used || !file.size_write) {
      if (written) {
        *written = 0;
      }

      return file.stream ? F_data_not : F_stream_not;
    }

    const f_array_length_t write_max = file.size_write > buffer.used ? buffer.used : file.size_write;

    f_status_t status = F_none;

    if (written) {
      status = private_f_file_stream_write_until(file, buffer, write_max, written);

      if (status == F_none) {
        if (*written == buffer.used) return F_none_eos;
        if (*written == write_max) return F_none_stop;
      }
    }
    else {
      f_array_length_t written_local = 0;

      status = private_f_file_stream_write_until(file, buffer, write_max, &written_local);

      if (status == F_none) {
        if (written_local == buffer.used) return F_none_eos;
        if (written_local == write_max) return F_none_stop;
      }
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_file_stream_write_block_

#ifndef _di_f_file_stream_write_until_
  f_status_t f_file_stream_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written) {

    if (!file.stream || !buffer.used || !total || !file.size_write) {
      if (written) {
        *written = 0;
      }

      return file.stream ? F_data_not : F_stream_not;
    }

    const f_array_length_t write_max = total > buffer.used ? buffer.used : total;

    f_status_t status = F_none;

    if (written) {
      status = private_f_file_stream_write_until(file, buffer, write_max, written);

      if (status == F_none) {
        if (*written == buffer.used) return F_none_eos;
        if (*written == write_max) return F_none_stop;
      }
    }
    else {
      f_array_length_t written_local = 0;

      status = private_f_file_stream_write_until(file, buffer, buffer.used, &written_local);

      if (status == F_none) {
        if (written_local == buffer.used) return F_none_eos;
        if (written_local == write_max) return F_none_stop;
      }
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_file_stream_write_until_

#ifndef _di_f_file_stream_write_range_
  f_status_t f_file_stream_write_range(const f_file_t file, const f_string_static_t buffer, const f_string_range_t range, f_array_length_t * const written) {

    if (!file.stream || !buffer.used || range.start > range.stop || range.start >= buffer.used || !file.size_write) {
      if (written) {
        *written = 0;
      }

      return file.stream ? F_data_not : F_stream_not;
    }

    const f_array_length_t write_max = (range.stop - range.start) + 1 > buffer.used ? buffer.used : (range.stop - range.start) + 1;
    const f_string_static_t buffer_adjusted = macro_f_string_static_t_initialize_1(buffer.string + range.start, 0, buffer.used - range.start);

    f_status_t status = F_none;

    if (written) {
      status = private_f_file_stream_write_until(file, buffer_adjusted, write_max, written);

      if (status == F_none) {
        if (range.start + *written == buffer.used) return F_none_eos;
        if (range.start + *written == write_max) return F_none_stop;
      }
    }
    else {
      f_array_length_t written_local = 0;

      status = private_f_file_stream_write_until(file, buffer_adjusted, write_max, &written_local);

      if (status == F_none) {
        if (range.start + written_local == buffer.used) return F_none_eos;
        if (range.start + written_local == write_max) return F_none_stop;
      }
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_file_stream_write_range_

#ifdef __cplusplus
} // extern "C"
#endif
