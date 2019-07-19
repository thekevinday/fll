/* FLL - Level 1
 * Project:       FSS
 * Version:       0.4.3
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_fss_basic_object_read_
  f_return_status fl_fss_basic_object_read(f_dynamic_string *buffer, f_string_location *input, f_fss_object *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == f_null) return f_error_set_error(f_invalid_parameter);
      if (input == f_null) return f_error_set_error(f_invalid_parameter);
      if (found == f_null) return f_error_set_error(f_invalid_parameter);
      if (input->start < 0) return f_error_set_error(f_invalid_parameter);
      if (input->stop < input->start) return f_error_set_error(f_invalid_parameter);
      if (buffer->used <= 0)  return f_error_set_error(f_invalid_parameter);
      if (input->start >= buffer->used) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    // delimits must only be applied once a valid object is found
    f_string_lengths delimits = f_string_lengths_initialize;

    fl_macro_fss_skip_past_whitespace((*buffer), (*input))
    fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders
    if (buffer->string[input->start] == f_fss_basic_close) {
      input->start++;
      return fl_fss_found_no_object;
    }

    // when handling delimits, the only time they should be applied is when a valid object would exist
    // however, the delimits will appear before a valid object, so remember their positions and only apply them after a would be valid object is confirmed
    f_bool has_delimit = f_false;

    // begin the search
    found->start = input->start;

    // ignore all comment lines
    if (buffer->string[input->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*input), delimits, f_no_data_on_eos, f_no_data_on_stop)

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

      fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)

      if (buffer->string[input->start] == f_fss_delimit_single_quote || buffer->string[input->start] == f_fss_delimit_double_quote) {
        if (delimits.used >= delimits.size) {
          f_status allocation_status = f_none;

           f_resize_string_lengths(allocation_status, delimits, delimits.size + f_fss_default_allocation_step);

          if (f_error_is_error(allocation_status)) {
            f_delete_string_lengths(allocation_status, delimits);
            return allocation_status;
          }
        }

        delimits.array[delimits.used] = last_slash;
        delimits.used++;
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
        fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)
      } // while

      if (isspace(buffer->string[input->start])) {
        found->stop = input->start - 1;

        fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

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

          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_error_is_warning(f_unterminated_group_on_eos), f_error_is_warning(f_unterminated_group_on_stop))

          if (buffer->string[input->start] == quoted) {
            f_string_length location = input->start;

            input->start = first_slash;

            if (slash_count % 2 == 0) {
              if (delimits.used + (slash_count / 2) >= delimits.size) {
                f_status allocation_status = f_none;

                f_resize_string_lengths(allocation_status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                if (f_error_is_error(allocation_status)) {
                  f_delete_string_lengths(allocation_status, delimits);
                  return allocation_status;
                }
              }

              while (slash_count > 0) {
                if (buffer->string[input->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 != 0) {
                    delimits.array[delimits.used] = input->start;
                    delimits.used++;
                  }

                  slash_count--;
                }

                input->start++;
              } // while

              input->start = location + 1;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
              fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)

              if (isgraph(buffer->string[input->start])) {
                while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
                  input->start++;
                } // while

                fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

                {
                  f_status allocation_status = f_none;

                  f_delete_string_lengths(allocation_status, delimits);
                }

                input->start++;
                return fl_fss_found_no_object;
              } else if (buffer->string[input->start] == f_eol) {
                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                found->stop = location - 1;
                input->start++;

                return fl_fss_found_object_no_content;
              }

              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              found->stop = location - 1;
              input->start++;
              return fl_fss_found_object;
            } else {
              if (delimits.used + (slash_count / 2) >= delimits.size) {
                f_status allocation_status = f_none;

                f_resize_string_lengths(allocation_status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                if (f_error_is_error(allocation_status)) {
                  f_delete_string_lengths(allocation_status, delimits);
                  return allocation_status;
                }
              }

              while (slash_count > 0) {
                if (buffer->string[input->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 != 0) {
                    delimits.array[delimits.used] = input->start;
                    delimits.used++;
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
              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);
              input->start++;
              return fl_fss_found_object_no_content;
            } else if (isspace(buffer->string[input->start])) {
              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);
              input->start++;
              return fl_fss_found_object;
            } else if (buffer->string[input->start] != f_fss_delimit_placeholder) {
              while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
                input->start++;
              } // while

              fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

              {
                f_status allocation_status = f_none;

                f_delete_string_lengths(allocation_status, delimits);
              }

              input->start++;
              return fl_fss_found_no_object;
            }

            input->start++;
          } // while

          fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)
        } else if (buffer->string[input->start] == f_eol) {
          {
            f_status allocation_status = f_none;

            f_delete_string_lengths(allocation_status, delimits);
          }

          input->start++;
          return fl_fss_found_no_object;
        }

        input->start++;
      } // while

      fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_error_is_warning(f_unterminated_group_on_eos), f_error_is_warning(f_unterminated_group_on_stop))
    }

    // seek to the end of the line when no valid object is found
    while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
      input->start++;
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    {
      f_status allocation_status = f_none;

      f_delete_string_lengths(allocation_status, delimits);
    }

    input->start++;
    return fl_fss_found_no_object;
  }
#endif // _di_fl_fss_basic_object_read_

#ifndef _di_fl_fss_basic_content_read_
  f_return_status fl_fss_basic_content_read(f_dynamic_string *buffer, f_string_location *input, f_fss_content *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == f_null) return f_error_set_error(f_invalid_parameter);
      if (input == f_null) return f_error_set_error(f_invalid_parameter);
      if (found == f_null) return f_error_set_error(f_invalid_parameter);
      if (input->start < 0) return f_error_set_error(f_invalid_parameter);
      if (input->stop < input->start) return f_error_set_error(f_invalid_parameter);
      if (buffer->used <= 0)  return f_error_set_error(f_invalid_parameter);
      if (input->start >= buffer->used) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    // delimits must only be applied once a valid object is found
    f_string_lengths delimits = f_string_lengths_initialize;

    fl_macro_fss_skip_past_whitespace((*buffer), (*input))
    fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders
    if (buffer->string[input->start] == f_eol) {
      input->start++;
      return fl_fss_found_no_content;
    }

    fl_macro_fss_allocate_content_if_necessary((*found), delimits);
    found->array[found->used].start = input->start;

    // search for valid content
    do {
      fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
      fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)

      if (buffer->string[input->start] == f_fss_basic_close) break;

      ++input->start;
    } while (f_true);

    // Save the stop point
    found->array[found->used].stop = input->start - 1;
    found->used++;
    input->start++;
    return fl_fss_found_content;
  }
#endif // _di_fl_fss_basic_content_read_

#ifndef _di_fl_fss_basic_object_write_
  f_return_status fl_fss_basic_object_write(const f_dynamic_string object, f_string_location *input, f_dynamic_string *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == f_null) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    f_bool   quoted = f_false;

    f_string_location buffer_position   = f_string_location_initialize;
    f_string_length   start_position    = f_string_initialize;
    f_string_length   pre_allocate_size = 0;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*input))

    if (input->start > input->stop) {
      return f_no_data_on_stop;
    } else if (input->start >= object.used) {
      return f_no_data_on_eos;
    }

    start_position = input->start;

    // add an additional 3 to ensure that there is room for the start and stop quotes or a slash delimit and the object open character.
    pre_allocate_size = buffer->used + (input->stop - input->start) + 3 + f_fss_default_allocation_step;

    if (pre_allocate_size > buffer->size) {
      f_resize_dynamic_string(status, (*buffer), pre_allocate_size);

      if (f_error_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop  = buffer->used;

    if (object.string[input->start] == f_fss_delimit_slash) {
      while (input->start <= input->stop && input->start < object.used) {
        if (object.string[input->start] == f_fss_delimit_placeholder) {
          input->start++;
          continue;
        } else if (object.string[input->start] != f_fss_delimit_slash) {
          break;
        }

        buffer->string[buffer_position.stop] = object.string[input->start];
        buffer_position.stop++;
        input->start++;
      } // while

      if (object.string[input->start] == f_fss_delimit_single_quote || object.string[input->start] == f_fss_delimit_double_quote) {
        pre_allocate_size++;

        if (pre_allocate_size > buffer->size) {
          f_resize_dynamic_string(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step);

          if (f_error_is_error(status)) return status;
        }

        buffer->string[buffer_position.stop] = f_fss_delimit_slash;
        buffer->string[buffer_position.stop + 1] = object.string[input->start];
        buffer_position.stop += 2;
        input->start++;
      }
    } else if (object.string[input->start] == f_fss_delimit_single_quote || object.string[input->start] == f_fss_delimit_double_quote) {
      pre_allocate_size++;

      if (pre_allocate_size > buffer->size) {
        f_resize_dynamic_string(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step);

        if (f_error_is_error(status)) return status;
      }

      buffer->string[buffer_position.stop] = f_fss_delimit_slash;
      buffer->string[buffer_position.stop + 1] = object.string[input->start];
      buffer_position.stop += 2;
      input->start++;
    } else if (object.string[input->start] == f_fss_comment) {
      quoted = f_true;
    }

    while (input->start <= input->stop && input->start < object.used) {
      if (object.string[input->start] == f_fss_delimit_placeholder) {
        input->start++;
        continue;
      } else if (object.string[input->start] == f_eol) {
        if (quoted) {
          buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
          buffer_position.stop++;
        }

        buffer->string[buffer_position.stop] = f_fss_basic_open;
        buffer->used = buffer_position.stop + 1;

        return f_none_on_eol;
      } else if (isspace(object.string[input->start]) || quoted) {
        pre_allocate_size++;

        if (pre_allocate_size > buffer->size) {
          f_resize_dynamic_string(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step);

          if (f_error_is_error(status)) return status;
        }

        // restart the loop searching for f_fss_delimit_double_quote.
        input->start = start_position;
        buffer_position.stop = buffer_position.start;

        buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
        buffer_position.stop++;

        while (input->start <= input->stop && input->start < object.used) {
          if (object.string[input->start] == f_fss_delimit_placeholder) {
            input->start++;
            continue;
          } else if (object.string[input->start] == f_fss_delimit_double_quote) {
            pre_allocate_size++;

            if (pre_allocate_size > buffer->size) {
              f_resize_dynamic_string(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step);

              if (f_error_is_error(status)) return status;
            }

            buffer->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
          } else if (object.string[input->start] == f_fss_delimit_slash) {
            f_string_length slash_count = 0;

            do {
              buffer->string[buffer_position.stop] = object.string[input->start];
              buffer_position.stop++;
              slash_count++;
              input->start++;

              fl_macro_fss_skip_past_delimit_placeholders(object, (*input));

              if (input->start > input->stop || input->start >= object.used) {
                break;
              }

              if (object.string[input->start] == f_fss_delimit_double_quote) {
                pre_allocate_size += slash_count;

                if (pre_allocate_size > buffer->size) {
                  f_resize_dynamic_string(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step);

                  if (f_error_is_error(status)) return status;
                }

                break;
              } else if (object.string[input->start] != f_fss_delimit_slash) {
                slash_count = 0;
                break;
              }
            } while (f_true);

            while (slash_count > 0) {
              buffer->string[buffer_position.stop] = f_fss_delimit_slash;
              buffer_position.stop++;
              slash_count--;
            } // while

            continue;
          } else if (object.string[input->start] == f_eol) {
            buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
            buffer_position.stop++;

            buffer->string[buffer_position.stop] = f_fss_basic_open;
            buffer->used = buffer_position.stop + 1;

            return f_none_on_eol;
          }

          buffer->string[buffer_position.stop] = object.string[input->start];
          input->start++;
          buffer_position.stop++;
        } // while

        buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
        buffer->string[buffer_position.stop + 1] = f_fss_basic_open;
        buffer->used = buffer_position.stop + 2;
        break;
      }

      buffer->string[buffer_position.stop] = object.string[input->start];
      input->start++;
      buffer_position.stop++;
    } // while

    if (buffer->used < buffer_position.stop) {
      buffer->string[buffer_position.stop] = f_fss_basic_open;
      buffer->used = buffer_position.stop + 1;
    }

    if (input->start > input->stop) {
      return f_none_on_stop;
    } else if (input->start >= object.used) {
      return f_none_on_eos;
    }

    return f_none;
  }
#endif // _di_fl_fss_basic_object_write_

#ifndef _di_fl_fss_basic_content_write_
  f_return_status fl_fss_basic_content_write(const f_dynamic_string content, f_string_location *input, f_dynamic_string *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == f_null) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    f_string_location input_position    = f_string_location_initialize;
    f_string_location buffer_position   = f_string_location_initialize;
    f_string_length   pre_allocate_size = 0;

    // add an additional 1 to ensure that there is room for the terminating newline.
    pre_allocate_size = buffer->used + (content.used) + 1 + f_fss_default_allocation_step;

    buffer_position.start = buffer->used;
    buffer_position.stop  = buffer->used;

    if (pre_allocate_size > buffer->size) {
      f_resize_dynamic_string(status, (*buffer), pre_allocate_size);

      if (f_error_is_error(status)) return status;
    }

    while (input->start <= input->stop && input->start < content.used) {
      if (content.string[input->start] == f_eol){
        buffer->string[buffer_position.stop] = f_eol;
        buffer->used = buffer_position.stop + 1;
        return f_none_on_eos;
      }

      if (content.string[input->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = content.string[input->start];
        buffer_position.stop++;
      }

      input->start++;
    } // while

    buffer->string[buffer_position.stop] = f_eol;
    buffer->used = buffer_position.stop + 1;

    if (input->start > input->stop) {
      return f_none_on_stop;
    } else if (input->start >= content.used) {
      return f_none_on_eos;
    }

    return f_none;
  }
#endif // _di_fl_fss_basic_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
