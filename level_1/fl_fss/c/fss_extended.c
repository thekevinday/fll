/* FLL - Level 1
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/fss_extended.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_fss_extended_object_read_
  f_return_status fl_fss_extended_object_read(f_dynamic_string *buffer, f_string_location *input, f_fss_object *found) {
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
    if (buffer->string[input->start] == f_fss_extended_close) {
      input->start++;
      return fl_fss_found_no_object;
    }

    // when handling delimits, the only time they should be applied is when a valid object would exist
    // however, the delimits will appear before a valid object, so remember their positions and only apply them after a would be valid object is confirmed
    f_bool          has_delimit = f_false;
    f_string_length location    = f_string_length_initialize;

    // begin the search
    found->start = input->start;

    // ignore all comment lines
    if (buffer->string[input->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*input), f_error_on_eos, f_error_on_stop)

      input->start++;
      return fl_fss_found_no_object;
    }

    // handle quote support
    f_autochar quoted = f_eos;

    // identify where the object begins
    if (buffer->string[input->start] == f_fss_delimit_slash) {
      f_string_length last_slash = input->start;
      input->start++;

      while (input->start <= input->stop && input->start < buffer->used) {
        if (buffer->string[input->start] == f_fss_delimit_placeholder) {
          input->start++;
          continue;
        } else if (!isgraph(buffer->string[input->start])) {
          found->stop = input->start - 1;
          input->start++;
          return fl_fss_found_object;
        } else if (buffer->string[input->start] != f_fss_delimit_slash) {
          break;
        }

        last_slash = input->start;
        input->start++;
      } // while

      fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

      if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote) {
        buffer->string[last_slash] = f_fss_delimit_placeholder;
        input->start++;
      }
    } else if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote) {
      quoted = buffer->string[input->start];
      input->start++;
      found->start = input->start;
    }

    // identify where the object ends
    if (quoted == f_eos) {
      while (isgraph(buffer->string[input->start]) || buffer->string[input->start] == f_fss_delimit_placeholder) {
        input->start++;
        fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
      } // while

      if (isspace(buffer->string[input->start])) {
        found->stop = input->start - 1;

        if (buffer->string[input->start] == f_eol) {
          input->start++;
          return fl_fss_found_object_no_content;
        }

        input->start++;
        return fl_fss_found_object;
      }
    } else {
      while (input->start <= input->stop && input->start < buffer->used) {
        if (buffer->string[input->start] == f_fss_delimit_slash) {
          f_string_length first_slash = input->start;
          f_string_length slash_count = 1;
          input->start++;

          while (input->start <= input->stop && input->start < buffer->used) {
            if (buffer->string[input->start] == f_fss_delimit_placeholder) {
              input->start++;
              continue;
            } else if (buffer->string[input->start] != f_fss_delimit_slash) {
              break;
            }

            slash_count++;
            input->start++;
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

          if (buffer->string[input->start] == quoted) {
            location     = input->start;
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

              input->start = location + 1;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

              if (isgraph(buffer->string[input->start])) {
                while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
                  input->start++;
                } // while

                input->start++;
                return fl_fss_found_no_object;
              } else if (buffer->string[input->start] == f_eol) {
                found->stop = input->start - 1;
                input->start++;

                return fl_fss_found_object_no_content;
              }

              found->stop = input->start - 1;
              input->start++;
              return fl_fss_found_object;
            } else {
              while (slash_count > 0) {
                if (buffer->string[input->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 != 0) {
                    buffer->string[input->start] = f_fss_delimit_placeholder;
                  }

                  slash_count--;
                }

                input->start++;
              } // while

              input->start = location;
            }
          }
        } else if (buffer->string[input->start] == quoted) {
          found->stop = input->start - 1;
          input->start++;

          while (input->start <= input->stop && input->start < buffer->used) {
            if (buffer->string[input->start] == f_eol) {
              input->start++;
              return fl_fss_found_object_no_content;
            } else if (isspace(buffer->string[input->start])) {
              input->start++;
              return fl_fss_found_object;
            } else if (buffer->string[input->start] != f_fss_delimit_placeholder) {
              while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
                input->start++;
              } // while

              input->start++;
              return fl_fss_found_no_object;
            }

            input->start++;
          }

          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
        } else if (buffer->string[input->start] == f_eol) {
          input->start++;
          return fl_fss_found_no_object;
        }

        input->start++;
      } // while

      fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)
    }

    // seek to the end of the line when no valid object is found
    while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
      input->start++;
    }

    input->start++;
    return fl_fss_found_no_object;
  }
#endif // _di_fl_fss_extended_object_read_

#ifndef _di_fl_fss_extended_content_read_
  f_return_status fl_fss_extended_content_read(f_dynamic_string *buffer, f_string_location *input, f_fss_content *found) {
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

    while (input->start <= input->stop) {
      // get past all leading spaces/tabs (allowed)
      fl_macro_fss_skip_past_whitespace((*buffer), (*input))
      fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

      if (buffer->string[input->start] == f_eol) {
        break;
      }

      fl_macro_fss_allocate_content_if_necessary((*found))
      found->array[found->used].start = input->start;

      // this inner loop should read until whitespace is found then mark the end of a specific content field
      do {
        fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
        fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

        // handle delimited quotes, single quotes, and double quotes
        if (buffer->string[input->start] == f_fss_delimit_slash) {
          do {
            f_string_length first_slash = input->start;
            ++input->start;

            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            // A slash only delimits if a delimit quote would follow the slash (or a slash and a delimit quote follows)
            if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote) {
              // because the slash properly delimited the quote, the quote then becomes the start of the content
              found->array[found->used].start = input->start;
              buffer->string[first_slash]     = f_fss_delimit_placeholder;
              break;
            } else if (buffer->string[input->start] == f_fss_delimit_slash) {
              f_string_length second_slash = input->start;
              ++input->start;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

              if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote) {
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
        } else if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote) {
          quoted = buffer->string[input->start];
          input->start++;

          fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

          found->array[found->used].start = input->start;
        }

        // when quoted is null, then spaces will end the content, otherwise the quote defined in quoted will end the content (or a newline)
        if (quoted == f_eos) {
          do {
            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            if (buffer->string[input->start] == f_fss_extended_close) {
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
          do {
            fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

            if (buffer->string[input->start] == f_fss_extended_close) {
              input->start++;
              return f_unterminated_group;
            }

            // handle delimited quotes
            if (buffer->string[input->start] == f_fss_delimit_slash) {
              f_string_length first_slash = input->start;
              ++input->start;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_none_on_eos, f_none_on_stop)

              // A slash only delimits if a delimit quote would follow the slash (or a slash and a delimit quote follows)
              if (buffer->string[input->start] == quoted) {
                buffer->string[first_slash] = f_fss_delimit_placeholder;
                ++input->start;
                continue;
              } else if (buffer->string[input->start] == f_fss_delimit_slash) {
                f_string_length second_slash = input->start;
                ++input->start;

                fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
                fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), f_unterminated_group_on_eos, f_unterminated_group_on_stop)

                if (buffer->string[input->start] == quoted) {
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
            } else if (buffer->string[input->start] == quoted) {
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
    if (original == found->used) {
      input->start++;
      return fl_fss_found_no_content;
    }

    return fl_fss_found_content;
  }
#endif // _di_fl_fss_extended_content_read_

#ifndef _di_fl_fss_extended_object_write_
  f_return_status fl_fss_extended_object_write(const f_dynamic_string buffer, f_string_location *input, f_dynamic_string *object) {
    #ifndef _di_level_1_parameter_checking_
      if (object == f_null) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    f_status status = f_status_initialize;

    f_string_location object_position   = f_string_location_initialize;
    f_string_length   start_position    = f_string_initialize;
    f_string_length   pre_allocate_size = f_string_length_initialize;

    fl_macro_fss_skip_past_delimit_placeholders(buffer, (*input))

    if (input->start > input->stop) {
      return f_no_data_on_stop;
    } else if (input->start >= buffer.used) {
      return f_no_data_on_eos;
    }

    start_position = input->start;

    // add an additional 3 to ensure that there is room for the start and stop quotes or a slash delimit and the object open character.
    pre_allocate_size = object->used + (input->stop - input->start) + 3 + f_fss_default_allocation_step;

    if (pre_allocate_size > object->size) {
      f_resize_dynamic_string(status, (*object), pre_allocate_size);

      if (f_macro_test_for_allocation_errors(status)) return status;
    }

    object_position.start = object->used;
    object_position.stop  = object->used;

    if (buffer.string[input->start] == f_fss_delimit_slash) {
      f_string_length delimit_slash_count = 0;

      while (input->start <= input->stop && input->start < buffer.used) {
        if (buffer.string[input->start] == f_fss_delimit_placeholder) {
          input->start++;
          continue;
        } else if (buffer.string[input->start] != f_fss_delimit_slash) {
          break;
        }

        object->string[object_position.stop] = buffer.string[input->start];
        object_position.stop++;
        delimit_slash_count++;
        input->start++;
      } // while

      if (buffer.string[input->start] == f_fss_delimit_single_quote || buffer.string[input->start] == f_fss_delimit_double_quote) {
        pre_allocate_size += delimit_slash_count + 1;

        if (pre_allocate_size > object->size) {
          f_resize_dynamic_string(status, (*object), pre_allocate_size + f_fss_default_allocation_step);

          if (f_macro_test_for_allocation_errors(status)) return status;
        }

        while (delimit_slash_count > 0) {
          object->string[object_position.stop] = f_fss_delimit_slash;
          object_position.stop++;
          delimit_slash_count--;
        } // while

        object->string[object_position.stop] = buffer.string[input->start];
        object_position.stop++;
        input->start++;
      }
    } else if (buffer.string[input->start] == f_fss_delimit_single_quote || buffer.string[input->start] == f_fss_delimit_double_quote) {
      pre_allocate_size++;

      if (pre_allocate_size > object->size) {
        f_resize_dynamic_string(status, (*object), pre_allocate_size + f_fss_default_allocation_step);

        if (f_macro_test_for_allocation_errors(status)) return status;
      }

      object->string[object_position.stop] = f_fss_delimit_slash;
      object->string[object_position.stop + 1] = buffer.string[input->start];
      object_position.stop += 2;
      input->start++;
    }

    while (input->start <= input->stop && input->start < buffer.used) {
      if (buffer.string[input->start] == f_fss_delimit_placeholder) {
        input->start++;
        continue;
      } else if (isspace(buffer.string[input->start])) {
        f_string_length first_space = input->start;

        input->start++;

        while (input->start <= input->stop && input->start < buffer.used && isspace(buffer.string[input->start])) {
          input->start++;
        } // while

        if (input->start > input->stop || input->start >= buffer.used) {
          object->string[first_space] = f_fss_extended_open;
          object->used = object_position.stop + 1;
          break;
        }

        // restart the loop searching for f_fss_delimit_double_quote.
        input->start = start_position;
        object_position.stop = object_position.start;

        object->string[object_position.stop] = f_fss_delimit_double_quote;
        object_position.stop++;

        while (input->start <= input->stop && input->start < buffer.used) {
          if (buffer.string[input->start] == f_fss_delimit_placeholder) {
            input->start++;
            continue;
          } else if (buffer.string[input->start] == f_fss_delimit_double_quote) {
            pre_allocate_size++;

            if (pre_allocate_size > object->size) {
              f_resize_dynamic_string(status, (*object), pre_allocate_size + f_fss_default_allocation_step);

              if (f_macro_test_for_allocation_errors(status)) return status;
            }

            object->string[object_position.stop] = f_fss_delimit_slash;
            object_position.stop++;
          } else if (buffer.string[input->start] == f_fss_delimit_slash) {
            f_string_length delimit_slash_count = 0;

            do {
              object->string[object_position.stop] = buffer.string[input->start];
              object_position.stop++;
              delimit_slash_count++;
              input->start++;

              fl_macro_fss_skip_past_delimit_placeholders(buffer, (*input));

              if (input->start > input->stop || input->start >= buffer.used) {
                break;
              }

              if (buffer.string[input->start] == f_fss_delimit_double_quote) {
                pre_allocate_size += delimit_slash_count;

                if (pre_allocate_size > object->size) {
                  f_resize_dynamic_string(status, (*object), pre_allocate_size + f_fss_default_allocation_step);

                  if (f_macro_test_for_allocation_errors(status)) return status;
                }

                break;
              } else if (buffer.string[input->start] != f_fss_delimit_slash) {
                delimit_slash_count = 0;
                break;
              }
            } while (f_true);

            while (delimit_slash_count > 0) {
              object->string[object_position.stop] = f_fss_delimit_slash;
              object_position.stop++;
              delimit_slash_count--;
            } // while

            continue;
          }

          object->string[object_position.stop] = buffer.string[input->start];
          input->start++;
          object_position.stop++;
        } // while

        object->string[object_position.stop] = f_fss_delimit_double_quote;
        object->string[object_position.stop + 1] = f_fss_extended_open;
        object->used = object_position.stop + 2;
        break;
      }

      object->string[object_position.stop] = buffer.string[input->start];
      input->start++;
      object_position.stop++;
    } // while

    if (object->used < object_position.stop) {
      object->string[object_position.stop] = f_fss_extended_open;
      object->used = object_position.stop + 1;
    }

    if (input->start > input->stop) {
      return f_none_on_stop;
    } else if (input->start >= buffer.used) {
      return f_none_on_eos;
    }

    return f_none;
  }
#endif // _di_fl_fss_extended_object_write_

#ifdef __cplusplus
} // extern "C"
#endif
