/* FLL - Level 1
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  f_return_status fl_fss_basic_list_object_read(f_dynamic_string *buffer, f_string_location *input, f_fss_object *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer       == f_null)       return f_invalid_parameter;
      if (input        == f_null)       return f_invalid_parameter;
      if (found        == f_null)       return f_invalid_parameter;
      if (input->start  < 0)            return f_invalid_parameter;
      if (input->stop   < input->start) return f_invalid_parameter;
      if (buffer->used <= 0)            return f_invalid_parameter;
      if (input->start >= buffer->used) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    fl_macro_fss_skip_past_whitespace((*buffer), (*input))
    fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_no_data_on_eos, f_no_data_on_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders
    if (buffer->string[input->start] == f_eol) {
      input->start++;
      return fl_fss_found_no_object;
    }

    // begin the search
    found->start = input->start;

    // ignore all comment lines
    if (buffer->string[input->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*input), f_no_data_on_eos, f_no_data_on_stop)

      input->start++;
      return fl_fss_found_no_object;
    }

    // identify where the object ends
    while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
      if (buffer->string[input->start] == f_fss_delimit_slash) {
        f_string_length first_slash = input->start;
        f_string_length slash_count = 1;

        input->start++;

        while (input->start < buffer->used && input->start <= input->stop && (buffer->string[input->start] == f_fss_delimit_placeholder || buffer->string[input->start] == f_fss_delimit_slash)) {
          if (buffer->string[input->start] == f_fss_delimit_slash) {
            slash_count++;
          }

          input->start++;
        } // while

        fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_no_data_on_eos, f_no_data_on_stop)

        if (buffer->string[input->start] == f_fss_basic_list_open) {
          f_string_length stop_point = input->start - 1;

          input->start++;

          while (input->start < buffer->used && input->start <= input->stop) {
            if (buffer->string[input->start] == f_eol || isgraph(buffer->string[input->start])) {
              break;
            }

            input->start++;
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_no_data_on_eos, f_no_data_on_stop)

          if (buffer->string[input->start] == f_eol) {
            f_string_length location = input->start;

            input->start = first_slash;

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {
                if (buffer->string[input->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 != 0) {
                    buffer->string[input->start] = f_fss_delimit_placeholder;
                  }

                  slash_count--;
                }

                input->start++;
              } // while

              found->stop = stop_point;
              input->start = location + 1;

              return fl_fss_found_object;
            }

            input->start = location + 1;
            return fl_fss_found_no_object;
          }
        }

        continue;
      } else if (buffer->string[input->start] == f_fss_basic_list_open) {
        f_string_length stop_point = input->start - 1;

        input->start++;

        while (input->start < buffer->used && input->start <= input->stop) {
          if (buffer->string[input->start] == f_eol || isgraph(buffer->string[input->start])) {
            break;
          }

          input->start++;
        } // while

        fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

        if (buffer->string[input->start] == f_eol) {
          found->stop = stop_point;
          input->start++;

          return fl_fss_found_object;
        }

        continue;
      }

      input->start++;
    } // while

    // seek to the end of the line when no valid object is found
    while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
      input->start++;
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_no_data_on_eos, f_no_data_on_stop)

    input->start++;
    return fl_fss_found_no_object;
  }
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  f_return_status fl_fss_basic_list_content_read(f_dynamic_string *buffer, f_string_location *input, f_fss_content *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer       == f_null)       return f_invalid_parameter;
      if (input        == f_null)       return f_invalid_parameter;
      if (found        == f_null)       return f_invalid_parameter;
      if (input->start  < 0)            return f_invalid_parameter;
      if (input->stop   < input->start) return f_invalid_parameter;
      if (buffer->used <= 0)            return f_invalid_parameter;
      if (input->start >= buffer->used) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
    fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

    fl_macro_fss_allocate_content_if_necessary((*found));
    found->array[found->used].start = input->start;

    f_string_length last_newline  = input->start;
    f_bool          found_newline = f_false;

    // identify where the content ends
    while (input->start < buffer->used && input->start <= input->stop) {
      if (buffer->string[input->start] == f_eol) {
        found_newline = f_true;
        last_newline = input->start;
        input->start++;
        continue;
      }

      if (buffer->string[input->start] == f_fss_delimit_slash) {
        f_string_length first_slash = input->start;
        f_string_length slash_count = 1;

        input->start++;

        while (input->start < buffer->used && input->start <= input->stop && (buffer->string[input->start] == f_fss_delimit_placeholder || buffer->string[input->start] == f_fss_delimit_slash)) {
          if (buffer->string[input->start] == f_fss_delimit_slash) {
            slash_count++;
          }

          input->start++;
        } // while

        if (found_newline) {
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
        } else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_no_data_on_eos, f_no_data_on_stop)
        }

        if (buffer->string[input->start] == f_fss_basic_list_open) {
          f_string_length stop_point = input->start - 1;

          input->start++;

          while (input->start < buffer->used && input->start <= input->stop) {
            if (buffer->string[input->start] == f_eol || isgraph(buffer->string[input->start])) {
              break;
            }

            input->start++;
          } // while

          if (found_newline) {
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
          } else {
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_no_data_on_eos, f_no_data_on_stop)
          }

          if (buffer->string[input->start] == f_eol) {
            f_string_length location = input->start;

            input->start = first_slash;

            if (slash_count % 2 == 0) {
              if (found_newline) {
                found->array[found->used].stop = last_newline;
                input->start = last_newline + 1;
                found->used++;

                return fl_fss_found_content;
              }

              return fl_fss_found_no_content;
            }

            while (slash_count > 0) {
              if (buffer->string[input->start] == f_fss_delimit_slash) {
                if (slash_count % 2 != 0) {
                  buffer->string[input->start] = f_fss_delimit_placeholder;
                }

                slash_count--;
              }

              input->start++;
            } // while

            found_newline = f_true;
            input->start = location + 1;
          }
        }

        continue;
      } else if (buffer->string[input->start] == f_fss_basic_list_open) {
        input->start++;

        while (input->start < buffer->used && input->start <= input->stop) {
          if (buffer->string[input->start] == f_eol || isgraph(buffer->string[input->start])) {
            break;
          }

          input->start++;
        } // while

        if (found_newline) {
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
        } else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_no_data_on_eos, f_no_data_on_stop)
        }

        if (buffer->string[input->start] == f_eol) {
          if (found_newline) {
            found->array[found->used].stop = last_newline;
            input->start = last_newline + 1;
            found->used++;

            return fl_fss_found_content;
          }

          return fl_fss_found_no_content;
        }

        continue;
      }

      input->start++;
    } // while

    if (found_newline) {
      found->array[found->used].stop = last_newline - 1;
      input->start = last_newline + 1;
      found->used++;

      fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

      return fl_fss_found_content;
    }

    fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_no_data_on_eos, f_no_data_on_stop)

    return fl_fss_found_no_content;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifdef __cplusplus
} // extern "C"
#endif
