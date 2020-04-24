#include <level_1/fss.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_decrement_buffer_
  f_return_status fl_fss_decrement_buffer(const f_string_dynamic buffer, f_string_location *location, const f_string_length step) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
      if (step < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (location->start < 1) return f_none_on_eos;

    f_string_length i = 0;
    unsigned short width = 0;

    do {
      width = f_macro_utf_byte_width(buffer.string[location->start - 1]);

      if (width > location->start) {
        if (width > 1) {
          return f_status_set_error(f_incomplete_utf_on_eos);
        }

        return f_none_on_eos;
      }

      i++;
      location->start -= width;
    } while (i < step);

    return f_none;
  }
#endif // _di_fl_fss_decrement_buffer_

#ifndef _di_fl_fss_identify_
  f_return_status fl_fss_identify(const f_string_dynamic buffer, f_fss_header *header) {
    #ifndef _di_level_1_parameter_checking_
      if (header == 0) return f_status_set_error(f_invalid_parameter);
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    register f_string_length i = 0;

    if (buffer.used < 10) {
      // "# fss-0000" is always 10 characters.
      return fl_fss_no_header;
    }

    // If this correctly follows the FSS specification, then this should be all that needs to be done (as well as atoh for ascii to hex).
    // All characters used in the identifier are only in the ascii equivalents of the characters, any similarly looking character or number representing in UTF-8 is considered invalid.
    if (buffer.string[i] == f_fss_type_header_open) {
      i++;

      if (buffer.string[i] == f_fss_type_header_part1) {
        i++;

        if (buffer.string[i] == f_fss_type_header_part2) {
          i++;

          if (buffer.string[i] == f_fss_type_header_part3) {
            i++;

            if (buffer.string[i] == f_fss_type_header_part4) {
              i++;

              if (buffer.string[i] == f_fss_type_header_part5) {
                i++;

                if (f_conversion_character_is_hexidecimal(buffer.string[i]) == f_true) {
                  i++;

                  if (f_conversion_character_is_hexidecimal(buffer.string[i]) == f_true) {
                    i++;

                    if (f_conversion_character_is_hexidecimal(buffer.string[i]) == f_true) {
                      i++;

                      if (f_conversion_character_is_hexidecimal(buffer.string[i]) == f_true) {
                        i++;

                        f_string_location length = f_string_location_initialize;

                        length.start = i - 4;
                        length.stop = i;

                        // 1: A possibly valid header type was found, now convert it into its proper format and save the header type
                        f_conversion_string_to_hexidecimal_unsigned(buffer.string, &header->type, length);

                        // 2: At this point, we can still know the proper format for the file and still have a invalid header, handle accordingly
                        if (buffer.string[i] == f_fss_type_header_close) {
                          i++;
                          header->length = i;

                          return f_none;
                        }
                        else {
                          // if "# fss-0000" is there, regardless of whats next, we can guess this to be of fss-0000, even if its fss-00001 (this is a guess afterall)
                          i++;
                          header->length = i;

                          return f_status_is_warning(fl_fss_invalid_but_accepted);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      // people can miss spaces, so lets accept in an attempt to interpret the file anyway, but return values at this point are to be flagged as invalid
      else if (buffer.string[i] == f_fss_type_header_part2) {
        i++;

        if (buffer.string[i] == f_fss_type_header_part3) {
          i++;

          if (buffer.string[i] == f_fss_type_header_part4) {
            i++;

            if (buffer.string[i] == f_fss_type_header_part5) {
              i++;

              if (f_conversion_character_is_hexidecimal(buffer.string[i]) == f_true) {
                i++;

                if (f_conversion_character_is_hexidecimal(buffer.string[i]) == f_true) {
                  i++;

                  if (f_conversion_character_is_hexidecimal(buffer.string[i]) == f_true) {
                    i++;

                    if (f_conversion_character_is_hexidecimal(buffer.string[i]) == f_true) {
                      i++;

                      f_string_location length = f_string_location_initialize;

                      length.start = i - 4;
                      length.stop = i;

                      f_conversion_string_to_hexidecimal_unsigned(buffer.string, &header->type, length);

                      header->length = i + 1;

                      return f_status_is_warning(fl_fss_invalid_but_accepted);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    // TODO: At some point add checksum and compressions checks here, but the above statements will have to be adjusted accordingly
    // 3: eventually this will be processing the checksum and 4: will be processing the compression

    return fl_fss_no_header;
  }
#endif // _di_fl_fss_identify_

#ifndef _di_fl_fss_identify_file_
  f_return_status fl_fss_identify_file(f_file *file, f_fss_header *header) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (header == 0) return f_status_set_error(f_invalid_parameter);
      if (file->address == 0) return f_status_set_error(f_file_not_open);
      if (ferror(file->address) != 0) return f_status_set_error(f_file_error);
    #endif // _di_level_1_parameter_checking_

    clearerr(file->address);

    f_status         status = f_none;
    f_string_dynamic buffer = f_string_dynamic_initialize;
    f_file_position  length = f_file_position_initialize;

    // make sure we are in the proper length in the file
    {
      int seek_result = f_macro_file_seek_begin(file->address, 0);

      if (seek_result != 0) return f_status_set_error(f_file_error_seek);
    }

    // 1: Prepare the buffer to handle a size of f_fss_max_header_length
    length.total_elements = f_fss_max_header_length;

    f_macro_string_dynamic_adjust(status, buffer, length.total_elements + 1);

    if (f_status_is_error(status)) {
      return status;
    }

    // 2: buffer the file
    status = f_file_read_at(file, &buffer, length);

    if (f_status_is_error(status)) {
      return status;
    }

    // 3: Now attempt to process the file for the header
    status = fl_fss_identify(buffer, header);

    return status;
  }
#endif // _di_fl_fss_identify_file_

#ifndef _di_fl_fss_increment_buffer_
  f_return_status fl_fss_increment_buffer(const f_string_dynamic buffer, f_string_location *location, const f_string_length step) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
      if (step < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length i = 0;
    unsigned short width = 0;

    do {
      width = f_macro_utf_byte_width(buffer.string[location->start]);

      if (location->start + width > location->stop) {
        if (width > 1) {
          return f_status_set_error(f_incomplete_utf_on_stop);
        }

        location->start += width;
        return f_none_on_stop;
      }
      else if (location->start + width >= buffer.used) {
        if (width > 1) {
          return f_status_set_error(f_incomplete_utf_on_eos);
        }

        location->start += width;
        return f_none_on_eos;
      }

      i++;
      location->start += width;
    } while (i < step);

    return f_none;
  }
#endif // _di_fl_fss_increment_buffer_

#ifndef _di_fl_fss_is_graph_
  f_return_status fl_fss_is_graph(const f_string_dynamic buffer, const f_string_location location) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (location.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length max_width = (location.stop - location.start) + 1;

    if (max_width > buffer.used - location.start) {
      max_width = buffer.used - location.start;
    }

    return f_utf_is_graph(buffer.string + location.start, max_width);
  }
#endif // _di_fl_fss_is_graph_

#ifndef _di_fl_fss_is_space_
  f_return_status fl_fss_is_space(const f_string_dynamic buffer, const f_string_location location) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (location.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length max_width = (location.stop - location.start) + 1;

    if (max_width > buffer.used - location.start) {
      max_width = buffer.used - location.start;
    }

    return f_utf_is_whitespace(buffer.string + location.start, max_width);
  }
#endif // _di_fl_fss_is_space_

#ifndef _di_fl_fss_skip_past_space_
  f_return_status fl_fss_skip_past_space(const f_string_dynamic buffer, f_string_location *location) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length max_width = (location->stop - location->start) + 1;

    if (max_width > buffer.used - location->start) {
      max_width = buffer.used - location->start;
    }

    while (buffer.string[location->start] == f_string_eos || (status = f_utf_is_whitespace(buffer.string + location->start, max_width)) == f_true || (status = f_utf_is_control(buffer.string + location->start, max_width)) == f_true) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (buffer.string[location->start] == f_string_eol) return f_none_on_eol;

      width = f_macro_utf_byte_width_is(buffer.string[location->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width >= buffer.used) return f_status_set_error(f_incomplete_utf_on_eos);
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);
      }

      location->start += width;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;

      max_width = (location->stop - location->start) + 1;

      if (max_width > buffer.used - location->start) {
        max_width = buffer.used - location->start;
      }
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_fss_skip_past_space_

#ifndef _di_fl_fss_skip_past_non_graph_
  f_return_status fl_fss_skip_past_non_graph(const f_string_dynamic buffer, f_string_location *location) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length max_width = (location->stop - location->start) + 1;

    if (max_width > buffer.used - location->start) {
      max_width = buffer.used - location->start;
    }

    while (buffer.string[location->start] == f_string_eos || ((status = f_utf_is_graph(buffer.string + location->start, max_width)) == f_false && (status = f_utf_is_zero_width(buffer.string + location->start, max_width)) == f_false)) {
      if (f_status_is_error(status)) return status;

      width = f_macro_utf_byte_width_is(buffer.string[location->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (location->start + width >= buffer.used) return f_status_set_error(f_incomplete_utf_on_eos);
        if (location->start + width > location->stop) return f_status_set_error(f_incomplete_utf_on_stop);
      }

      location->start += width;

      if (location->start >= buffer.used) return f_none_on_eos;
      if (location->start > location->stop) return f_none_on_stop;

      max_width = (location->stop - location->start) + 1;

      if (max_width > buffer.used - location->start) {
        max_width = buffer.used - location->start;
      }
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_fss_skip_past_non_graph_

#ifndef _di_fl_fss_shift_delimiters_
  f_return_status fl_fss_shift_delimiters(f_string_dynamic *buffer, const f_string_location location) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer->used <= 0) return f_status_set_error(f_invalid_parameter);
      if (location.start < 0) return f_status_set_error(f_invalid_parameter);
      if (location.stop < location.start) return f_status_set_error(f_invalid_parameter);
      if (location.start >= buffer->used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length position = 0;
    f_string_length distance = 0;
    unsigned short utf_width = 0;
    unsigned short i = 0;

    position = location.start;

    while (position < buffer->used && position <= location.stop) {
      if (buffer->string[position] == f_fss_delimit_placeholder) {
        distance++;
      }

      // do not waste time trying to process what is only going to be replaced with a delimit placeholder
      if (position + distance >= buffer->used || position + distance > location.stop) {
        break;
      }

      utf_width = f_macro_utf_byte_width_is(buffer->string[position]);
      if (utf_width > 1) {
        // not enough space in buffer or in location range to process UTF-8 character.
        if (position + utf_width >= buffer->used || position + utf_width > location.stop) {
          return f_status_set_error(f_invalid_utf);
        }

        if (distance > 0) {
          while (utf_width > 0) {
            buffer->string[position] = buffer->string[position + distance];
            utf_width--;
            position++;
          }
        }
      }
      else {
        // shift everything down one for each placeholder found
        if (distance > 0) {
          buffer->string[position] = buffer->string[position + distance];
        }

        position++;
      }
    }

    if (distance > 0) {
      while (position < buffer->used + distance && position <= location.stop) {
        buffer->string[position] = f_fss_delimit_placeholder;
        position++;
      }
    }

    return f_none;
  }
#endif // _di_fl_fss_shift_delimiters_

#ifdef __cplusplus
} // extern "C"
#endif
