/* FLL - Level 1
 * Project:       FSS
 * Version:       svn
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  f_return_status fl_fss_basic_list_object_read(f_dynamic_string *buffer, f_string_location *input, f_fss_object *found){
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
    if (buffer->string[input->start] == f_eol){
      input->start++;
      return fl_fss_found_no_object;
    } else if (buffer->string[input->start] == f_fss_basic_list_open){
      fl_macro_fss_object_seek_till_newline((*buffer), (*input), f_error_on_eos, f_error_on_stop)

      input->start++;
      return fl_fss_found_no_object;
    }

    // when handling delimits, the only time they should be applied is when a valid object would exist
    // however, the delimits will appear before a valid object, so remember their positions and only apply them after a would be valid object is confirmed
    f_bool          has_quote_delimit = f_false;
    f_string_length quote_delimit     = f_string_length_initialize;

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
      fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

      // A slash only delimits if a delimit quote would follow the slash (or a slash and a delimit quote follows)
      if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
        // because the slash properly delimited the quote, the quote then becomes the start of the content
        found->start = first_slash + 1;
        quote_delimit = first_slash;
        has_quote_delimit = f_true;
      } else if (buffer->string[input->start] == f_fss_delimit_slash){
        // only apply a slash delimit if the line begins with slashes followed by a quote
        do {
          ++input->start;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

          if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
            found->start = first_slash + 1;
            quote_delimit = first_slash;
            has_quote_delimit = f_true;
            break;
          } else if (!isgraph(buffer->string[input->start])) {
            fl_macro_fss_object_seek_till_newline((*buffer), (*input), f_error_on_eos, f_error_on_stop)

            input->start++;
            return fl_fss_found_no_object;
          }
        } while (buffer->string[input->start] == f_fss_delimit_slash);
      }
    } else if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
      quoted = buffer->string[input->start];
      input->start++;

      fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
      fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

      found->start = input->start;
    } else if (isgraph(buffer->string[input->start])) {
      found->start = input->start;
    }

    // identify where the object ends
    if (quoted == f_eos){
      do{
        fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
        fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

        if (!isgraph(buffer->string[input->start])){
          break;
        } else if (buffer->string[input->start] == f_fss_delimit_slash){
          f_string_length first_slash = input->start;
          ++input->start;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

          // A slash only delimits here if a basic list opener would follow the slash
          if (buffer->string[input->start] == f_fss_basic_list_open){
            ++input->start;

            fl_macro_fss_skip_past_whitespace((*buffer), (*input))
            fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

            // found a would be valid basic list object that has been delimited to not be a valid objecy, so exit
            if (buffer->string[input->start] == f_fss_basic_list_close){
              input->start++;
              return fl_fss_found_no_object;
            } else {
              // otherwise we now know this could never be a valid object so seek to the end of line and return without applying a delimit
              fl_macro_fss_object_seek_till_newline((*buffer), (*input), f_error_on_eos, f_error_on_stop)

              input->start++;
              return fl_fss_found_no_object;
            }
          } else if (buffer->string[input->start] == f_fss_delimit_slash){
            f_string_length second_slash = input->start;
            ++input->start;

            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

            if (buffer->string[input->start] == f_fss_basic_list_open){
              f_string_length open_position = input->start;
              ++input->start;

              fl_macro_fss_skip_past_whitespace((*buffer), (*input))
              fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

              // found a valid basic list object, so apply the delimit
              if (buffer->string[input->start] == f_eol){
                if (has_quote_delimit){
                  buffer->string[quote_delimit] = f_fss_delimit_placeholder;
                }

                buffer->string[first_slash] = f_fss_delimit_placeholder;
                found->stop = open_position - 1;
                input->start++;
                return fl_fss_found_object;
              }
            } else {
              // return to the second slash, this way if there is a third or more, the quote test can be repeated
              input->start = second_slash;
            }
          }
        } else if (buffer->string[input->start] == f_fss_basic_list_open){
          f_string_length open_position = input->start;
          input->start++;

          fl_macro_fss_skip_past_whitespace((*buffer), (*input))
          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

          // found a valid basic list object
          if (buffer->string[input->start] == f_eol){
            if (has_quote_delimit){
              buffer->string[quote_delimit] = f_fss_delimit_placeholder;
            }

            found->stop = open_position - 1;
            input->start++;
            return fl_fss_found_object;
          }
        }

        ++input->start;
      } while (f_true);
    } else {
      f_string_length quote_location = f_string_length_initialize;

      // the quote must end before the opener begins, in this case the colon ':', so a quoted object would look like: "quoted object":\n
      do{
        fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
        fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

        if (buffer->string[input->start] == f_eol){
          input->start++;
          return fl_fss_found_no_object;
        }

        // close quotes do not need to be delimited in this case as a valid quoted object must end with: ":\n
        if (buffer->string[input->start] == quoted){
          // at this point, a valid object will need to be determined
          // if nothing else is between the colon and the newline, then a valid object has been found
          // otherwise restart the loop at this new position, looking for the next proper close quote
          // This allows for an object name like the following to be valid:
          // "My "Weird" Object":
          // Whose object name is seen as: My "Weird" Object
          quote_location = input->start;
          input->start++;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

          if (buffer->string[input->start] == f_fss_basic_list_open){
            input->start++;

            fl_macro_fss_skip_past_whitespace((*buffer), (*input))
            fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

            if (buffer->string[input->start] == f_eol){
              found->stop = quote_location - 1;
              input->start++;
              return fl_fss_found_object;
            } else {
              continue;
            }
          } else {
            continue;
          }
        }

        ++input->start;
      } while (f_true);
    }

    fl_macro_fss_object_seek_till_newline((*buffer), (*input), f_error_on_eos, f_error_on_stop)

    input->start++;
    return fl_fss_found_no_object;
  }
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  f_return_status fl_fss_basic_list_content_read(f_dynamic_string *buffer, f_string_location *input, f_fss_content *found){
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

    fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
    fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

    fl_macro_fss_allocate_content_if_necessary((*found));
    found->array[found->used].start = input->start;

    f_string_length last_newline = input->start;
    f_bool          has_newlines = f_false;

    // when handling delimits, the only time they should be applied is when a valid object would exist
    // however, the delimits will appear before a valid object, so remember their positions and only apply them after a would be valid object is confirmed
    f_bool          has_quote_delimit = f_false;
    f_string_length quote_delimit     = f_string_length_initialize;

    // search until stop point, end of string, or until a valid basic list object is found
    do{
      if (has_quote_delimit){
        has_quote_delimit = f_false;
      }

      fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
      fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

      if (buffer->string[input->start] == f_eol){
        has_newlines = f_true;
        last_newline = input->start;
        ++input->start;
        continue;
      } else if (buffer->string[input->start] == f_fss_basic_list_open){
        // a line that begins with only the basic list opener cannot be a valid list object so skip to next line
        fl_macro_fss_content_seek_till_newline((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

        has_newlines = f_true;
        last_newline = input->start;
        ++input->start;
        continue;
      } else if (buffer->string[input->start] == f_fss_comment){
        // comment lines are not valid objects so skip to next line
        fl_macro_fss_content_seek_till_newline((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

        has_newlines = f_true;
        last_newline = input->start;
        ++input->start;
        continue;
      } else {
        // handle quote support
        f_autochar quoted = f_eos;

        // identify where the object begins
        if (buffer->string[input->start] == f_fss_delimit_slash){
          f_string_length first_slash = input->start;
          input->start++;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

          // A slash only delimits if a delimit quote would follow the slash (or a slash and a delimit quote follows)
          if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
            // because the slash properly delimited the quote, the quote then becomes the start of the content
            quote_delimit = first_slash;
            has_quote_delimit = f_true;
          } else if (buffer->string[input->start] == f_fss_delimit_slash){
            // only apply a slash delimit if the line begins with slashes followed by a quote
            do {
              ++input->start;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

              if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
                quote_delimit = first_slash;
                has_quote_delimit = f_true;
                break;
              } else if (!isgraph(buffer->string[input->start])) {
                fl_macro_fss_content_seek_till_newline((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

                break;
              }
            } while (buffer->string[input->start] == f_fss_delimit_slash);

            // if exited from above loop while at an EOL, then continue the main loop
            if (buffer->string[input->start] == f_eol) {
              continue;
            }
          }
        } else if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote){
          quoted = buffer->string[input->start];
          input->start++;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)
        } else if (!isgraph(buffer->string[input->start])) {
          fl_macro_fss_content_seek_till_newline((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
          continue;
        }

        // identify where the potential object ends
        if (quoted == f_eos){
          do{
            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            if (!isgraph(buffer->string[input->start])){
              while(buffer->string[input->start] != f_eol){
                ++input->start;

                if (input->start >= buffer->used){
                  found->array[found->used].stop = input->stop;
                  found->used++;
                  return f_none_on_eos;
                }

                if (input->start > input->stop){
                  found->array[found->used].stop = input->stop;
                  found->used++;
                  return f_none_on_stop;
                }
              } // while

              has_newlines = f_true;
              last_newline = input->start;
              break;
            } else if (buffer->string[input->start] == f_fss_delimit_slash){
              f_string_length first_slash = input->start;
              ++input->start;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

              // A slash only delimits here if a basic list opener would follow the slash
              if (buffer->string[input->start] == f_fss_basic_list_open){
                f_string_length open_position = input->start;
                ++input->start;

                fl_macro_fss_skip_past_whitespace((*buffer), (*input))

                if (has_newlines){
                  // In this case, assume a valid object was found when eos/eof was reached and reset the start position
                  fl_macro_fss_content_return_on_overflow_reset((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop, last_newline)
                } else {
                  fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
                }

                // found a would be valid basic list object, so apply the delimit
                if (buffer->string[input->start] == f_eol){
                  buffer->string[first_slash] = f_fss_delimit_placeholder;
                  has_newlines = f_true;
                  last_newline = input->start;
                  break;
                } else {
                  input->start = open_position;
                  ++input->start;
                  continue;
                }
              } else if (buffer->string[input->start] == f_fss_delimit_slash){
                f_string_length second_slash = input->start;
                ++input->start;

                fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
                fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

                if (buffer->string[input->start] == f_fss_basic_list_open){
                  f_string_length open_position = input->start;
                  ++input->start;

                  fl_macro_fss_skip_past_whitespace((*buffer), (*input))

                  if (has_newlines){
                    // In this case, assume a valid object was found when eos/eof was reached and reset the start position
                    fl_macro_fss_content_return_on_overflow_reset((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop, last_newline)
                  } else {
                    fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
                  }

                  // found a valid basic list object
                  if (buffer->string[input->start] == f_eol){
                    // the content should not apply delimits for valid objects
                    if (has_newlines){
                      input->start = last_newline;
                      found->array[found->used].stop = input->start - 1;
                      input->start++;
                      found->used++;
                      return fl_fss_found_content;
                    }

                    // when there is no newline and an object was found, then no content was found because the starting line is the next object line!
                    input->start = last_newline;
                    return fl_fss_found_no_content;
                  } else {
                    input->start = open_position;
                    ++input->start;
                    continue;
                  }
                } else {
                  // return to the second slash, this way if there is a third or more, the quote test can be repeated
                  input->start = second_slash;
                  ++input->start;
                  continue;
                }
              }
            } else if (buffer->string[input->start] == f_fss_basic_list_open){
              f_string_length open_position = input->start;
              input->start++;

              fl_macro_fss_skip_past_whitespace((*buffer), (*input))

              if (has_newlines){
                // In this case, assume a valid object was found when eos/eof was reached and reset the start position
                fl_macro_fss_content_return_on_overflow_reset((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop, last_newline)
              } else {
                fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
              }

              // found a valid basic list object
              if (buffer->string[input->start] == f_eol){
                // the content should not apply delimits for valid objects
                if (has_newlines){
                  input->start = last_newline;
                  found->array[found->used].stop = input->start - 1;
                  input->start++;
                  found->used++;
                  return fl_fss_found_content;
                }

                // when there is no newline and an object was found, then no content was found because the starting line is the next object line!
                input->start = last_newline;
                return fl_fss_found_no_content;
              } else {
                input->start = open_position;
              }
            }

            ++input->start;
          } while (f_true);
        } else {
          // the quote must end before the opener begins, in this case the colon ':', so a quoted object would look like: "quoted object":\n
          do{
            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

            if (buffer->string[input->start] == f_eol){
              has_newlines = f_true;
              last_newline = input->start;
              break;
            }

            // close quotes do not need to be delimited in this case as a valid quoted object must end with: ":\n
            if (buffer->string[input->start] == quoted){
              // at this point, a valid object will need to be determined
              // if nothing else is between the colon and the newline, then a valid object has been found
              // otherwise restart the loop at this new position, looking for the next proper close quote
              // This allows for an object name like the following to be valid:
              // "My "Weird" Object":
              // Whose object name is seen as: My "Weird" Object
              input->start++;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

              if (buffer->string[input->start] == f_fss_basic_list_open){
                input->start++;

                fl_macro_fss_skip_past_whitespace((*buffer), (*input))
                fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_error_on_eos, f_error_on_stop)

                if (buffer->string[input->start] == f_eol){
                  if (has_newlines){
                    input->start = last_newline;
                    found->array[found->used].stop = input->start - 1;
                    input->start++;
                    found->used++;
                    return fl_fss_found_content;
                  }

                  // when there is no newline and an object was found, then no content was found because the starting line is the next object line!
                  input->start = last_newline;
                  return fl_fss_found_no_content;
                } else {
                  continue;
                }
              } else {
                continue;
              }
            }

            ++input->start;
          } while (f_true);
        }
      }

      ++input->start;
    } while (f_true);

    // should never get here
    return f_unknown;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifdef __cplusplus
} // extern "C"
#endif
