/* FLL - Level 1
 * Project:       FSS
 * Version:       svn
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/fss_extended.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_fss_extended_object_read_
  f_return_status fl_fss_extended_object_read(f_dynamic_string *buffer, f_string_location *input, f_fss_object *found){
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
    fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders
    if (buffer->string[input->start] == f_fss_extended_close){
      input->start++;
      return fl_fss_found_no_object;
    }

    // when handling delimits, the only time they should be applied is when a valid object would exist
    // however, the delimits will appear before a valid object, so remember their positions and only apply them after a would be valid object is confirmed
    f_bool          has_delimit   = f_false;
    f_bool          ignore_quotes = f_false;
    f_string_length location      = f_string_length_initialize;

    // begin the search
    found->start = input->start;

    // ignore all comment lines
    if (buffer->string[input->start] == f_fss_comment){
      fl_macro_fss_object_seek_till_newline((*buffer), (*input), f_error_on_eos, f_error_on_stop)

      input->start++;
      return fl_fss_found_no_object;
    }

    // handle quote support
    f_autochar quoted = f_eos;

    // identify where the object begins
    if (buffer->string[input->start] == f_fss_delimit_slash){
      f_string_length first_slash = input->start;
      input->start++;

      fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
      fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

      // A slash only delimits if a delimit quote would follow the slash (or a slash and a delimit quote follows)
      if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
        location = first_slash;
        has_delimit = f_true;
        quoted = buffer->string[input->start];
        input->start++;
      } else if (buffer->string[input->start] == f_fss_delimit_slash){
        do{
          ++input->start;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

          if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
            location = first_slash;
            has_delimit = f_true;
            quoted = buffer->string[input->start];
            ignore_quotes = f_true;
            input->start++;
          } else if (!isgraph(buffer->string[input->start])) {
            found->stop = input->start - 1;
            input->start++;
            return fl_fss_found_object;
          }
        } while (buffer->string[input->start] == f_fss_delimit_slash);
      }
    } else if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
      quoted = buffer->string[input->start];
      input->start++;
      location = input->start;
    }

    // identify where the object ends
    if (quoted == f_eos){
      while (isgraph(buffer->string[input->start]) || buffer->string[input->start] == f_fss_delimit_placeholder){
        ++input->start;
        fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
      } // while

      if (isspace(buffer->string[input->start])){
        found->stop = input->start - 1;

        if (buffer->string[input->start] == f_eol){
          input->start++;
          return fl_fss_found_object_no_content;
        }

        input->start++;
        return fl_fss_found_object;
      }
    } else {
      // remember the very first space in case a valid object close is not found
      f_string_length pre_space   = f_string_length_initialize;
      f_bool          found_space = f_false;

      // a dynamically populated location of all delimits to apply
      f_string_lengths delimits = f_string_lengths_initialize;

      do{
        fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
        fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

        if (buffer->string[input->start] == f_eol){
          if (found_space){
            found->stop = pre_space;
            input->start = pre_space;
          } else {
            found->stop = input->start - 1;
          }

          input->start++;

          f_status status = f_status_initialize;
          f_delete_string_lengths(status, delimits)

          if (found_space){
            return fl_fss_found_object;
          } else {
            return fl_fss_found_object_no_content;
          }
        } else if (isspace(buffer->string[input->start])) {
          if (!found_space){
            pre_space = input->start - 1;
            found_space = f_true;
          }
        } else if (buffer->string[input->start] == quoted) {
          f_string_length quote_location = input->start;
          ++input->start;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

          if (isspace(buffer->string[input->start])) {
            // this quote is a valid object close quote, so handle appropriately
            if (has_delimit){
              buffer->string[location] = f_fss_delimit_placeholder;

              if (ignore_quotes){
                if (found_space){
                  found->stop = pre_space;
                  input->start = pre_space;
                } else {
                  found->stop = input->start -1;
                }
              } else {
                found->stop = quote_location -1;
              }
            } else {
              found->start = location;
              found->stop  = quote_location - 1;
            }

            if (delimits.used > 0) {
              f_string_length counter = 0;

              for (; counter < delimits.used; counter++) {
                buffer->string[delimits.array[counter]] = f_fss_delimit_placeholder;
              } // for
            }

            f_status status = f_status_initialize;
            f_delete_string_lengths(status, delimits)

            input->start++;
            return fl_fss_found_object;
          } else {
            continue;
          }
        } else if (buffer->string[input->start] == f_fss_delimit_slash) {
          f_string_length first_slash = input->start;
          ++input->start;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

          // A slash only delimits here if whitespace would follow the quote
          if (buffer->string[input->start] == quoted){
            ++input->start;

            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            if (isspace(buffer->string[input->start])){
              if (delimits.used >= delimits.size){
                f_status status = f_status_initialize;

                f_resize_string_lengths(status, delimits, delimits.size + f_fss_default_allocation_step);
                if (f_macro_test_for_allocation_errors(status)) return status;
              }

              delimits.array[delimits.used] = first_slash;
              delimits.used++;
            } else {
              continue;
            }
          } else if (buffer->string[input->start] == f_fss_delimit_slash) {
            ++input->start;

            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            // A slash only delimits here if whitespace would follow the quote
            if (buffer->string[input->start] == quoted){
              ++input->start;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

              if (isspace(buffer->string[input->start])){
                if (delimits.used >= delimits.size){
                  f_status status = f_status_initialize;

                  f_resize_string_lengths(status, delimits, delimits.size + f_fss_default_allocation_step);
                  if (f_macro_test_for_allocation_errors(status)) return status;
                }

                delimits.array[delimits.used] = first_slash;
                delimits.used++;
              } else {
                continue;
              }
            }
          }
        }

        ++input->start;
      } while (f_true);
    }

    // seek to the end of the line
    while(input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol){
      ++input->start;
    }

    input->start++;
    return fl_fss_found_no_object;
  }
#endif // _di_fl_fss_extended_object_read_

#ifndef _di_fl_fss_extended_content_read_
  f_return_status fl_fss_extended_content_read(f_dynamic_string *buffer, f_string_location *input, f_fss_content *found){
    #ifndef _di_level_1_parameter_checking_
      if (buffer       == f_null)       return f_invalid_parameter;
      if (input        == f_null)       return f_invalid_parameter;
      if (found        == f_null)       return f_invalid_parameter;
      if (input->start  < 0)            return f_invalid_parameter;
      if (input->stop   < input->start) return f_invalid_parameter;
      if (buffer->used <= 0)            return f_invalid_parameter;
      if (input->start >= buffer->used) return f_invalid_parameter;
      if (found->used   > found->size)  return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    f_autochar      quoted   = f_eos;
    f_string_length original = found->used;

    fl_macro_fss_allocate_content_if_necessary((*found))
    found->array[found->used].start = input->start;

    while (input->start <= input->stop){
      // get past all leading spaces/tabs (allowed)
      fl_macro_fss_skip_past_whitespace((*buffer), (*input))
      fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

      if (buffer->string[input->start] == f_eol){
        break;
      }

      fl_macro_fss_allocate_content_if_necessary((*found))
      found->array[found->used].start = input->start;

      // this inner loop should read until whitespace is found then mark the end of a specific content field
      do{
        fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
        fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

        // handle delimited quotes, single quotes, and double quotes
        if (buffer->string[input->start] == f_fss_delimit_slash){
          do{
            f_string_length first_slash = input->start;
            ++input->start;

            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            // A slash only delimits if a delimit quote would follow the slash (or a slash and a delimit quote follows)
            if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
              // because the slash properly delimited the quote, the quote then becomes the start of the content
              found->array[found->used].start = input->start;
              buffer->string[first_slash]     = f_fss_delimit_placeholder;
              break;
            } else if (buffer->string[input->start] == f_fss_delimit_slash){
              f_string_length second_slash = input->start;
              ++input->start;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

              if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
                buffer->string[first_slash] = f_fss_delimit_placeholder;

                quoted = buffer->string[input->start];
                input->start++;

                fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
                fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

                found->array[found->used].start = input->start;
                break;
              } else {
                // return to the second slash, this way if there is a third or more, the quote test can be repeated
                input->start = second_slash;
                ++input->start;
              }
            } else {
              break;
            }
          } while (f_true);
        } else if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
          quoted = buffer->string[input->start];
          input->start++;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

          found->array[found->used].start = input->start;
        }

        // when quoted is null, then spaces will end the content, otherwise the quote defined in quoted will end the content (or a newline)
        if (quoted == f_eos){
          do{
            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            if (buffer->string[input->start] == f_fss_extended_close){
              // Save the stop point
              found->array[found->used].stop = input->start - 1;
              found->used++;
              input->start++;
              return fl_fss_found_content;
            }

            if (isspace(buffer->string[input->start])) break;

            ++input->start;
          } while (f_true);
        } else {
          do{
            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            if (buffer->string[input->start] == f_fss_extended_close){
              input->start++;
              return f_unterminated_group;
            }

            // handle delimited quotes
            if (buffer->string[input->start] == f_fss_delimit_slash){
              f_string_length first_slash = input->start;
              ++input->start;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

              // A slash only delimits if a delimit quote would follow the slash (or a slash and a delimit quote follows)
              if (buffer->string[input->start] == quoted){
                buffer->string[first_slash] = f_fss_delimit_placeholder;
                ++input->start;
                continue;
              } else if (buffer->string[input->start] == f_fss_delimit_slash){
                f_string_length second_slash = input->start;
                ++input->start;

                fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
                fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

                if (buffer->string[input->start] == quoted){
                  buffer->string[first_slash] = f_fss_delimit_placeholder;
                  quoted = f_eos;
                  break;
                } else {
                  // return to the second slash, this way if there is a third or more, the quote test can be repeated
                  input->start = second_slash;
                  ++input->start;
                  continue;
                }
              }
            } else if (buffer->string[input->start] == quoted){
              quoted = f_eos;
              break;
            }

            ++input->start;
          } while (f_true);
        }

        // Save the stop point
        found->array[found->used].stop = input->start - 1;
        found->used++;
        break;
      } while (f_true);

      ++input->start;
    }

    // When original is the same as the current found->used, then there was no data found
    if (original == found->used){
      input->start++;
      return fl_fss_found_no_content;
    }

    return fl_fss_found_content;
  }
#endif // _di_fl_fss_extended_content_read_

#ifdef __cplusplus
} // extern "C"
#endif
