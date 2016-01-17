/* FLL - Level 0
 * Project:       File
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 *  Provides structures and data types for a file I/O.
 *  Provides operations for opening/closing files
 */
#include <level_0/file.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_open_
  f_return_status f_file_open(f_file *file_information, f_const f_string filename) {
    #ifndef _di_level_0_parameter_checking_
      if (file_information == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    // if file->mode is unset, then this may cause a segfault, depending on whether or not the libc will handle this appropriately
    if (file_information->mode == 0) return f_error_set_error(f_invalid_parameter);

    file_information->file = fopen(filename, file_information->mode);

    if (file_information->file == 0) return f_error_set_error(f_file_not_found);
    if (ferror(file_information->file) != 0) return f_error_set_error(f_file_open_error);

    file_information->id = fileno(file_information->file);

    if (file_information->id == -1) return f_error_set_error(f_file_descriptor_error);

    return f_none;
  }
#endif // _di_f_file_open_

#ifndef _di_f_file_close_
  f_return_status f_file_close(f_file *file_information) {
    #ifndef _di_level_0_parameter_checking_
      if (file_information == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file_information->file == 0) return f_error_set_error(f_file_not_open);

    // if we were given a file descriptor as well, make sure to flush all changes to the disk that are not flushed by the 'fflush()' command
    if (file_information->id != 0) {
      // make sure all unfinished data gets completed
      if (fsync(file_information->id) != 0) return f_error_set_error(f_file_synchronize_error);
    }

    if (fclose(file_information->file) == 0) {
      file_information->file = 0;
      return f_none;
    }
    else return f_error_set_error(f_file_close_error);
  }
#endif // _di_f_file_close_

#ifndef _di_f_file_flush_
  f_return_status f_file_flush(f_file *file_information) {
    #ifndef _di_level_0_parameter_checking_
      if (file_information == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file_information->file == 0) return f_error_set_error(f_file_not_open);

    if (fflush(file_information->file) == 0) return f_none;
    else return f_error_set_error(f_file_flush_error);
  }
#endif // _di_f_file_flush_

#ifndef _di_f_file_read_
  f_return_status f_file_read(f_file *file_information, f_dynamic_string *buffer, f_const f_file_position location) {
    #ifndef _di_level_0_parameter_checking_
      if (file_information == 0) return f_error_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_error_set_error(f_invalid_parameter);

      if (location.buffer_start < 0) return f_error_set_error(f_invalid_parameter);
      if (location.file_start < 0) return f_error_set_error(f_invalid_parameter);
      if (location.total_elements < 0) return f_error_set_error(f_invalid_parameter);

      // when the available buffer size is smaller than the total elements, then there is not enough allocated memory available to read the file
      if (location.total_elements > 0) {
        if (buffer->size - location.buffer_start < location.total_elements) return f_error_set_error(f_invalid_parameter);
      }
    #endif // _di_level_0_parameter_checking_

    if (file_information->file == 0) return f_error_set_error(f_file_not_open);

    // first seek to 'where' we need to begin the read
    f_u_long current_file_position = ftell(file_information->file);
    if (current_file_position == (f_u_long) -1) return f_error_set_error(f_file_seek_error);

    f_s_int result = 0;

    if (current_file_position > location.file_start) {
      result = f_file_seek_from_current(file_information->file, file_information->byte_size * (0 - (current_file_position - location.file_start)));
    } else if (current_file_position < location.file_start) {
      result = f_file_seek_from_current(file_information->file, file_information->byte_size * (location.file_start - current_file_position));
    }

    if (result != 0) return f_error_set_error(f_file_seek_error);

    // now do the actual read
    if (location.total_elements == 0) {
      result = fread(buffer->string + location.buffer_start, file_information->byte_size, buffer->size - buffer->used - 1, file_information->file);
    } else {
      result = fread(buffer->string + location.buffer_start, file_information->byte_size, location.total_elements, file_information->file);
    }

    if (file_information->file == 0) return f_error_set_error(f_file_read_error);
    if (ferror(file_information->file) != 0) return f_error_set_error(f_file_read_error);

    // now save how much of our allocated buffer is actually used
    // also make sure that we aren't making used space vanish
    if (location.buffer_start + result > buffer->used) {
      buffer->used = location.buffer_start + (result / file_information->byte_size);
    }

    // append an EOS only when the total elements were set to 0
    if (location.total_elements == 0) {
      buffer->string[buffer->used] = f_eos;
    }

    // make sure to communicate that we are done without a problem and the eof was reached
    if (feof(file_information->file)) {
      return f_none_on_eof;
    }

    return f_none;
  }
#endif // _di_f_file_read_

#ifndef _di_f_file_read_fifo_
  f_return_status f_file_read_fifo(f_file *file_information, f_dynamic_string *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (file_information == 0) return f_error_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file_information->file == 0) return f_error_set_error(f_file_not_open);

    f_s_int result = 0;

    // now do the actual read
    result = fread(buffer->string + buffer->used, file_information->byte_size, buffer->size - buffer->used - 1, file_information->file);

    if (file_information->file == 0) return f_error_set_error(f_file_read_error);
    if (ferror(file_information->file) != 0) return f_error_set_error(f_file_read_error);

    buffer->used += (result / file_information->byte_size);

    // make sure to communicate that we are done without a problem and the eof was reached
    if (feof(file_information->file)) {
      return f_none_on_eof;
    }

    return f_none;
  }
#endif // _di_f_file_read_fifo_

#ifndef _di_f_file_stat_
  f_return_status f_file_stat(f_const f_string file, f_stat *stat) {
    if (stat != 0) {
      return f_none;
    }

    f_int result = 0;

    result = stat(file, stat);
    if (result < 0) {
      if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_error_set_error(f_invalid_parameter);
      }
      else if (errno == ENOMEM) {
        return f_error_set_error(f_out_of_memory);
      }
      else if (errno == EOVERFLOW) {
        return f_error_set_error(f_overflow);
      }
      else if (errno == ENOTDIR) {
        return f_error_set_error(f_invalid_directory);
      }
      else if (errno == ENOENT) {
        return f_file_not_found;
      }
      else if (errno == EACCESS) {
        return f_error_set_error(f_access_denied);
      }
      else if (errno == ELOOP) {
        return f_error_set_error(f_loop);
      }

      return f_error_set_error(f_file_stat_error);
    }

    return f_none;
  }
#endif // _di_f_file_stat_

#ifndef _di_f_file_stat_by_id_
  f_return_status f_file_stat_by_id(f_const f_s_int file_id, f_stat *stat) {
    #ifndef _di_level_0_parameter_checking_
      if (file_id <= 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (stat != 0) {
      return f_none;
    }

    f_int result = 0;

    result = stat(file, stat);
    if (result < 0) {
      if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_error_set_error(f_invalid_parameter);
      }
      else if (errno == ENOMEM) {
        return f_error_set_error(f_out_of_memory);
      }
      else if (errno == EOVERFLOW) {
        return f_error_set_error(f_overflow);
      }
      else if (errno == ENOTDIR) {
        return f_error_set_error(f_invalid_directory);
      }
      else if (errno == ENOENT) {
        return f_file_not_found;
      }
      else if (errno == EACCESS) {
        return f_error_set_error(f_access_denied);
      }
      else if (errno == ELOOP) {
        return f_error_set_error(f_loop);
      }

      return f_error_set_error(f_file_stat_error);
    }

    return f_none;
  }
#endif // _di_f_file_stat_by_id_

#ifdef __cplusplus
} // extern "C"
#endif
