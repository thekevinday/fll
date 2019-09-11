#include <level_1/fss.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_decrement_buffer_
  f_return_status fl_fss_decrement_buffer(const f_string_dynamic buffer, f_string_location *input, const f_string_length step) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (input->start < 0) return f_status_set_error(f_invalid_parameter);
      if (input->stop < input->start) return f_status_set_error(f_invalid_parameter);
      if (input->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
      if (step < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (input->start < 1) return f_none_on_eos;

    f_string_length i = 0;
    unsigned short width = 0;

    do {
      width = f_macro_utf_byte_width(buffer.string[input->start - 1]);

      if (width > input->start) {
        if (width > 1) {
          return f_status_set_error(f_incomplete_utf_on_eos);
        }

        return f_none_on_eos;
      }

      i++;
      input->start -= width;
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

    // A single UTF-8 BOM is allowed to exist before the valid FSS identifier.
    if (buffer.used > 3) {
      f_status status = f_utf_is_bom(buffer.string, 4);

      if (f_status_is_error(status)) {
        return f_status_set_error(fl_fss_no_header);
      }

      if (status == f_true) {
        i = f_utf_bom_length;

        if (buffer.used < 10 + f_utf_bom_length) {
          return fl_fss_no_header;
        }
      }
      else if (buffer.used < 10) {
        // "# fss-0000" without UTF-8 BOM is always 10 characters.
        return fl_fss_no_header;
      }
    }
    else {
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

                if (f_is_hexidecimal(buffer.string[i]) == f_true) {
                  i++;

                  if (f_is_hexidecimal(buffer.string[i]) == f_true) {
                    i++;

                    if (f_is_hexidecimal(buffer.string[i]) == f_true) {
                      i++;

                      if (f_is_hexidecimal(buffer.string[i]) == f_true) {
                        i++;

                        f_string_location location = f_string_location_initialize;

                        location.start = i - 4;
                        location.stop = i;

                        // 1: A possibly valid header type was found, now convert it into its proper format and save the header type
                        f_string_to_hexidecimal(buffer.string, &header->type, location);

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

                          return f_status_is_warning(fl_fss_accepted_but_invalid);
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

              if (f_is_hexidecimal(buffer.string[i]) == f_true) {
                i++;

                if (f_is_hexidecimal(buffer.string[i]) == f_true) {
                  i++;

                  if (f_is_hexidecimal(buffer.string[i]) == f_true) {
                    i++;

                    if (f_is_hexidecimal(buffer.string[i]) == f_true) {
                      i++;

                      f_string_location location = f_string_location_initialize;

                      location.start = i - 4;
                      location.stop = i;

                      f_string_to_hexidecimal(buffer.string, &header->type, location);

                      header->length = i + 1;

                      return f_status_is_warning(fl_fss_accepted_but_invalid);
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
    f_file_position  location = f_file_position_initialize;

    // make sure we are in the proper location in the file
    {
      int seek_result = f_macro_file_seek_begin(file->address, 0);

      if (seek_result != 0) return f_status_set_error(f_file_seek_error);
    }

    // 1: Prepare the buffer to handle a size of f_fss_max_header_length
    location.total_elements = f_fss_max_header_length;

    f_macro_string_dynamic_adjust(status, buffer, location.total_elements + 1);

    if (f_status_is_error(status)) {
      return status;
    }

    // 2: buffer the file
    status = f_file_read_at(file, &buffer, location);

    if (f_status_is_error(status)) {
      return status;
    }

    // 3: Now attempt to process the file for the header
    status = fl_fss_identify(buffer, header);

    return status;
  }
#endif // _di_fl_fss_identify_file_

#ifndef _di_fl_fss_increment_buffer_
  f_return_status fl_fss_increment_buffer(const f_string_dynamic buffer, f_string_location *input, const f_string_length step) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (input->start < 0) return f_status_set_error(f_invalid_parameter);
      if (input->stop < input->start) return f_status_set_error(f_invalid_parameter);
      if (input->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
      if (step < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length i = 0;
    unsigned short width = 0;

    do {
      width = f_macro_utf_byte_width(buffer.string[input->start]);

      if (input->start + width > input->stop) {
        if (width > 1) {
          return f_status_set_error(f_incomplete_utf_on_stop);
        }

        input->start += width;
        return f_none_on_stop;
      }
      else if (input->start + width >= buffer.used) {
        if (width > 1) {
          return f_status_set_error(f_incomplete_utf_on_eos);
        }

        input->start += width;
        return f_none_on_eos;
      }

      i++;
      input->start += width;
    } while (i < step);

    return f_none;
  }
#endif // _di_fl_fss_increment_buffer_

#ifndef _di_fl_fss_is_graph_
  f_return_status fl_fss_is_graph(const f_string_dynamic buffer, const f_string_location input) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (input.start < 0) return f_status_set_error(f_invalid_parameter);
      if (input.stop < input.start) return f_status_set_error(f_invalid_parameter);
      if (input.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length max_width = (input.stop - input.start) + 1;

    if (max_width > buffer.used - input.start) {
      max_width = buffer.used - input.start;
    }

    return f_utf_is_graph(buffer.string + input.start, max_width);
  }
#endif // _di_fl_fss_is_graph_

#ifndef _di_fl_fss_is_space_
  f_return_status fl_fss_is_space(const f_string_dynamic buffer, const f_string_location input) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (input.start < 0) return f_status_set_error(f_invalid_parameter);
      if (input.stop < input.start) return f_status_set_error(f_invalid_parameter);
      if (input.start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length max_width = (input.stop - input.start) + 1;

    if (max_width > buffer.used - input.start) {
      max_width = buffer.used - input.start;
    }

    return f_utf_is_space(buffer.string + input.start, max_width);
  }
#endif // _di_fl_fss_is_space_

#ifndef _di_fl_fss_skip_past_whitespace_
  f_return_status fl_fss_skip_past_whitespace(const f_string_dynamic buffer, f_string_location *input) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (input == 0) return f_status_set_error(f_invalid_parameter);
      if (input->start < 0) return f_status_set_error(f_invalid_parameter);
      if (input->stop < input->start) return f_status_set_error(f_invalid_parameter);
      if (input->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length max_width = (input->stop - input->start) + 1;

    if (max_width > buffer.used - input->start) {
      max_width = buffer.used - input->start;
    }

    while (buffer.string[input->start] == f_string_eos || (status = f_utf_is_graph(buffer.string + input->start, max_width)) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      if (buffer.string[input->start] == f_string_eol) return f_none_on_eol;

      width = f_macro_utf_byte_width_is(buffer.string[input->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (input->start + width >= buffer.used) return f_status_set_error(f_incomplete_utf_on_eos);
        if (input->start + width > input->stop) return f_status_set_error(f_incomplete_utf_on_stop);
      }

      input->start += width;

      if (input->start >= buffer.used) return f_none_on_eos;
      if (input->start > input->stop) return f_none_on_stop;

      max_width = (input->stop - input->start) + 1;

      if (max_width > buffer.used - input->start) {
        max_width = buffer.used - input->start;
      }
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_fss_skip_past_whitespace_

#ifndef _di_fl_fss_skip_past_all_whitespace_
  f_return_status fl_fss_skip_past_all_whitespace(const f_string_dynamic buffer, f_string_location *input) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer.used <= 0) return f_status_set_error(f_invalid_parameter);
      if (input == 0) return f_status_set_error(f_invalid_parameter);
      if (input->start < 0) return f_status_set_error(f_invalid_parameter);
      if (input->stop < input->start) return f_status_set_error(f_invalid_parameter);
      if (input->start >= buffer.used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    unsigned short width = 0;

    f_string_length max_width = (input->stop - input->start) + 1;

    if (max_width > buffer.used - input->start) {
      max_width = buffer.used - input->start;
    }

    while (buffer.string[input->start] == f_string_eos || (status = f_utf_is_graph(buffer.string + input->start, max_width)) == f_false) {
      if (f_status_is_error(status)) {
        return status;
      }

      width = f_macro_utf_byte_width_is(buffer.string[input->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return f_status_set_error(f_incomplete_utf);
      }
      else {
        if (input->start + width >= buffer.used) return f_status_set_error(f_incomplete_utf_on_eos);
        if (input->start + width > input->stop) return f_status_set_error(f_incomplete_utf_on_stop);
      }

      input->start += width;

      if (input->start >= buffer.used) return f_none_on_eos;
      if (input->start > input->stop) return f_none_on_stop;

      max_width = (input->stop - input->start) + 1;

      if (max_width > buffer.used - input->start) {
        max_width = buffer.used - input->start;
      }
    } // while

    if (f_status_is_error(status)) {
      return status;
    }

    return f_none;
  }
#endif // _di_fl_fss_skip_past_all_whitespace_

#ifndef _di_fl_fss_shift_delimiters_
  f_return_status fl_fss_shift_delimiters(f_string_dynamic *buffer, const f_string_location input) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer->used <= 0) return f_status_set_error(f_invalid_parameter);
      if (input.start < 0) return f_status_set_error(f_invalid_parameter);
      if (input.stop < input.start) return f_status_set_error(f_invalid_parameter);
      if (input.start >= buffer->used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length position = 0;
    f_string_length distance = 0;
    unsigned short utf_width = 0;
    unsigned short i = 0;

    position = input.start;

    while (position < buffer->used && position <= input.stop) {
      if (buffer->string[position] == f_fss_delimit_placeholder) {
        distance++;
      }

      // do not waste time trying to process what is only going to be replaced with a delimit placeholder
      if (position + distance >= buffer->used || position + distance > input.stop) {
        break;
      }

      utf_width = f_macro_utf_byte_width_is(buffer->string[position]);
      if (utf_width > 1) {
        // not enough space in buffer or in input range to process UTF-8 character.
        if (position + utf_width >= buffer->used || position + utf_width > input.stop) {
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
      while (position < buffer->used + distance && position <= input.stop) {
        buffer->string[position] = f_fss_delimit_placeholder;
        ++position;
      }
    }

    return f_none;
  }
#endif // _di_fl_fss_shift_delimiters_

#ifdef __cplusplus
} // extern "C"
#endif
