#include <level_1/utf_file.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_utf_file_read_
  f_return_status fl_utf_file_read(f_file *file, f_utf_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer->used >= buffer->size) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    f_status status = f_none;

    f_string_length i = 0;
    f_string_length total = 0;

    int result = 0;
    const f_number_unsigned bytes_total = file->size_block * file->size_chunk;

    uint8_t width = 0;
    uint8_t buffer_read[bytes_total];
    f_utf_character character = 0;

    for (;;) {
      if (buffer->used + bytes_total >= buffer->used) {
        if (buffer->used + bytes_total > f_utf_string_max_size) return f_status_set_error(f_string_too_large);

        f_macro_string_dynamic_resize(status, (*buffer), buffer->used + bytes_total);

        if (f_status_is_error(status)) return status;
      }

      memset(&buffer_read, 0, bytes_total);

      result = fread(buffer->string + buffer->used, file->size_chunk, file->size_block, file->address);

      if (file->address == 0) return f_status_set_error(f_file_error_read);
      if (ferror(file->address) != 0) return f_status_set_error(f_file_error_read);

      total = result * file->size_chunk;

      for (i = 0; i < total; i += width) {
        width = f_macro_utf_byte_width(buffer_read[i]);

        if (i + width > total) return f_status_set_error(f_incomplete_utf_on_eof);

        character = f_macro_utf_character_from_char_1(buffer_read[i]);

        if (width > 1 && i + 1 < total) {
          character |= f_macro_utf_character_from_char_2(buffer_read[i]);

          if (width > 2 && i + 2 < total) {
          character |= f_macro_utf_character_from_char_3(buffer_read[i]);

            if (width > 3 && i + 3 < total) {
              character |= f_macro_utf_character_from_char_4(buffer_read[i]);
            }
          }
        }

        buffer->string[i] = character;
        buffer->used++;
      } // for

      if (feof(file->address)) return f_none_on_eof;
    } // for

    return status;
  }
#endif // _di_fl_utf_file_read_

#ifndef _di_fl_utf_file_read_position
  f_return_status fl_utf_file_read_position(f_file *file, f_utf_string_dynamic *buffer, const f_file_position position) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    int result = 0;

    // first seek to 'where' we need to begin the read.
    {
      long current_file_position = ftell(file->address);

      if (current_file_position == -1) return f_status_set_error(f_file_error_seek);

      if (current_file_position > position.start) {
        result = f_macro_file_seek_to(file->address, file->size_chunk * (0 - (current_file_position - position.start)));
      }
      else if (current_file_position < position.start) {
        result = f_macro_file_seek_to(file->address, file->size_chunk * (position.start - current_file_position));
      }

      if (result != 0) return f_status_set_error(f_file_error_seek);
    }

    f_status status = f_none;
    bool infinite = f_false;

    f_string_length i = 0;
    f_string_length total = 0;

    f_number_unsigned bytes_total;

    // when total is 0, this means the file read will until EOF is reached.
    if (position.total == 0) {
      infinite = f_true;
      bytes_total = file->size_block * file->size_chunk;
    }
    else {
      bytes_total = position.total * file->size_chunk;
    }

    uint8_t width = 0;
    uint8_t buffer_read[bytes_total];
    f_utf_character character = 0;

    do {
      if (buffer->used + bytes_total > buffer->size) {
        if (buffer->used + bytes_total > f_string_length_size) return f_status_set_error(f_string_too_large);

        f_macro_string_dynamic_resize(status, (*buffer), buffer->used + bytes_total);

        if (f_status_is_error(status)) return status;
      }

      if (position.total == 0) {
        result = fread(buffer->string + buffer->used, file->size_chunk, file->size_block, file->address);
      }
      else {
        result = fread(buffer->string + buffer->used, file->size_chunk, position.total, file->address);
      }

      if (file->address == 0) return f_status_set_error(f_file_error_read);
      if (ferror(file->address) != 0) return f_status_set_error(f_file_error_read);

      total = result * file->size_chunk;

      for (i = 0; i < total; i += width) {
        width = f_macro_utf_byte_width(buffer_read[i]);

        if (i + width > total) return f_status_set_error(f_incomplete_utf_on_eof);

        character = f_macro_utf_character_from_char_1(buffer_read[i]);

        if (width > 1 && i + 1 < total) {
          character |= f_macro_utf_character_from_char_2(buffer_read[i]);

          if (width > 2 && i + 2 < total) {
          character |= f_macro_utf_character_from_char_3(buffer_read[i]);

            if (width > 3 && i + 3 < total) {
              character |= f_macro_utf_character_from_char_4(buffer_read[i]);
            }
          }
        }

        buffer->string[i] = character;
        buffer->used++;
      } // for

      if (feof(file->address)) return f_none_on_eof;
    } while (infinite);

    return status;
  }
#endif // _di_fl_utf_file_read_position

#ifndef _di_fl_utf_file_write_
  f_return_status fl_utf_file_write(f_file *file, const f_utf_string_static buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file->address == 0) return f_status_set_error(f_file_not_open);

    f_string_length total = 0;
    f_string_length last = 0;
    f_string_length used = 0;
    f_string_length i = 0;

    size_t written = 0;
    uint8_t buffer_write[f_file_default_write_size];
    uint8_t width = 0;

    do {
      memset(&buffer_write[f_file_default_write_size], 0, f_file_default_write_size);

      for (i = 0; used < f_file_default_write_size && total + i < buffer.used; i++, used += width) {
        width = f_macro_utf_character_width(buffer.string[total + i]);

        buffer_write[used] = f_macro_utf_character_to_char_1(buffer.string[total + i]);

        if (width > 1) {
          buffer_write[used + 1] = f_macro_utf_character_to_char_2(buffer.string[total + i]);

          if (width > 2) {
            buffer_write[used + 2] = f_macro_utf_character_to_char_3(buffer.string[total + i]);

            if (width > 3) {
              buffer_write[used + 3] = f_macro_utf_character_to_char_4(buffer.string[total + i]);
            }
          }
        }
      } // for

      written = fwrite(buffer.string + last, file->size_chunk, used, file->address);

      if (written < i * file->size_chunk) return f_status_set_error(f_file_error_write);

      total += i;
      last += used;
    } while (total < buffer.used);

    return f_none;
  }
#endif // _di_fl_utf_file_write_

#ifndef _di_fl_utf_file_write_position_
  f_return_status fl_utf_file_write_position(f_file *file, const f_utf_string_static buffer, const f_utf_string_range position) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (position.start < position.stop) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (file->address == 0) return f_file_not_open;

    f_string_length total = 0;
    f_string_length last = position.start;
    f_string_length used = 0;
    f_string_length i = 0;

    size_t written = 0;
    uint8_t buffer_write[f_file_default_write_size];
    uint8_t width = 0;

    const f_string_length max = buffer.used - (position.stop - position.start + 1);

    do {
      memset(&buffer_write[f_file_default_write_size], 0, f_file_default_write_size);

      for (i = 0; used < f_file_default_write_size && total + i < max; i++, used += width) {
        width = f_macro_utf_character_width(buffer.string[total + i]);

        buffer_write[used] = f_macro_utf_character_to_char_1(buffer.string[total + i]);

        if (width > 1) {
          buffer_write[used + 1] = f_macro_utf_character_to_char_2(buffer.string[total + i]);

          if (width > 2) {
            buffer_write[used + 2] = f_macro_utf_character_to_char_3(buffer.string[total + i]);

            if (width > 3) {
              buffer_write[used + 3] = f_macro_utf_character_to_char_4(buffer.string[total + i]);
            }
          }
        }
      } // for

      written = fwrite(buffer.string + last, file->size_chunk, used, file->address);

      if (written < i * file->size_chunk) return f_status_set_error(f_file_error_write);

      total += i;
      last += used;
    } while (total < max);

    return f_none;
  }
#endif // _di_fl_utf_file_write_position_

#ifdef __cplusplus
} // extern "C"
#endif
