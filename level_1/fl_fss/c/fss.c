/* FLL - Level 1
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 */
#include <level_1/fss.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_fss_identify_
  f_return_status fl_fss_identify(const f_dynamic_string buffer, f_fss_header *header) {
    #ifndef _di_level_1_parameter_checking_
      if (header      == f_null) return f_invalid_parameter;
      if (buffer.used <= 0)      return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    register f_string_length i = 0;

    // If this correctly follows the FSS specification, then this should be all that needs to be done (as well as atoh for ascii to hex)
    if                   (buffer.string[i] == f_fss_type_header_open) {  i++;
      if                 (buffer.string[i] == f_fss_type_header_part1) { i++;
        if               (buffer.string[i] == f_fss_type_header_part2) { i++;
          if             (buffer.string[i] == f_fss_type_header_part3) { i++;
            if           (buffer.string[i] == f_fss_type_header_part4) { i++;
              if         (buffer.string[i] == f_fss_type_header_part5) { i++;
                if       (f_is_hexdigit(buffer.string[i]) == f_true) {   i++;
                  if     (f_is_hexdigit(buffer.string[i]) == f_true) {   i++;
                    if   (f_is_hexdigit(buffer.string[i]) == f_true) {   i++;
                      if (f_is_hexdigit(buffer.string[i]) == f_true) {   i++;

                        f_string_location location = f_string_location_initialize;

                        location.start = i - 4;
                        location.stop  = i;

                        // 1: A possibly valid header type was found, now convert it into its proper format and save the header type
                        f_string_to_hexdigit(buffer.string, &header->type, location);

                        // 2: At this point, we can still know the proper format for the file and still have a invalid header, handle accordingly
                        if (buffer.string[i] == f_fss_type_header_close) {
                          i++;
                          header->length = i;

                          return f_none;
                        } else {
                          // if "# fss-0000" is there, regardless of whats next, we can guess this to be of fss-0000, even if its fss-00001 (this is a guess afterall)
                          i++;
                          header->length = i;

                          return fl_fss_accepted_but_invalid;
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
      } else if        (buffer.string[i] == f_fss_type_header_part2) { i++;
        if             (buffer.string[i] == f_fss_type_header_part3) { i++;
          if           (buffer.string[i] == f_fss_type_header_part4) { i++;
            if         (buffer.string[i] == f_fss_type_header_part5) { i++;
              if       (f_is_hexdigit(buffer.string[i]) == f_true) {   i++;
                if     (f_is_hexdigit(buffer.string[i]) == f_true) {   i++;
                  if   (f_is_hexdigit(buffer.string[i]) == f_true) {   i++;
                    if (f_is_hexdigit(buffer.string[i]) == f_true) {   i++;

                      f_string_location location = f_string_location_initialize;

                      location.start = i - 4;
                      location.stop  = i;

                      f_string_to_hexdigit(buffer.string, &header->type, location);

                      header->length = i + 1;

                      return fl_fss_accepted_but_invalid;
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
  f_return_status fl_fss_identify_file(f_file *file_information, f_fss_header *header) {
    #ifndef _di_level_1_parameter_checking_
      if (file_information               == f_null) return f_invalid_parameter;
      if (header                         == f_null) return f_invalid_parameter;
      if (file_information->file         == 0)      return f_file_not_open;
      if (ferror(file_information->file) != 0)      return f_file_error;
    #endif // _di_level_1_parameter_checking_

    clearerr(file_information->file);

    f_status          status   = f_status_initialize;
    f_dynamic_string  buffer   = f_dynamic_string_initialize;
    f_file_position   location = f_file_position_initialize;

    // make sure we are in the proper location in the file
    {
      f_s_int seek_result = f_file_seek_from_beginning(file_information->file, 0);

      if (seek_result != 0) return f_file_seek_error;
    }

    // 1: Prepare the buffer to handle a size of f_fss_max_header_length
    location.total_elements = f_fss_max_header_length;

    f_adjust_dynamic_string(status, buffer, location.total_elements + 1);

    if (f_macro_test_for_allocation_errors(status)) {
      return status;
    }

    // 2: buffer the file
    status = f_file_read(file_information, &buffer, location);

    if (f_macro_test_for_basic_errors(status) || f_macro_test_for_file_errors(status)) {
      return status;
    }

    // 3: Now attempt to process the file for the header
    status = fl_fss_identify(buffer, header);

    return status;
  }
#endif // _di_fl_fss_identify_file_

#ifndef _di_fl_fss_shift_delimiters_
f_return_status fl_fss_shift_delimiters(f_dynamic_string *buffer, const f_string_location location) {
  #ifndef _di_level_1_parameter_checking_
    if (buffer->used   <= 0)              return f_invalid_parameter;
    if (location.start  < 0)              return f_invalid_parameter;
    if (location.stop   < location.start) return f_invalid_parameter;
    if (location.start >= buffer->used)   return f_invalid_parameter;
  #endif // _di_level_1_parameter_checking_

  f_string_length position = f_string_length_initialize;
  f_string_length distance = f_string_length_initialize;

  position = location.start;

  while (position < buffer->used && position <= location.stop) {
    if (buffer->string[position] == f_fss_delimit_placeholder) {
      distance++;
    }

    // do not waste time trying to process what is only going to be replaced with a delimit placeholder
    if (position + distance >= buffer->used || position + distance > location.stop) {
      break;
    }

    // shift everything down one for each placeholder found
    if (distance > 0) {
      buffer->string[position] = buffer->string[position + distance];
    }

    ++position;
  }

  if (distance > 0) {
    while (position < buffer->used + distance && position <= location.stop) {
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
