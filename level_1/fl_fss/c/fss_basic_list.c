#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  f_return_status fl_fss_basic_list_object_read(f_dynamic_string *buffer, f_string_location *input, f_fss_object *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (input == 0) return f_status_set_error(f_invalid_parameter);
      if (found == 0) return f_status_set_error(f_invalid_parameter);
      if (input->start < 0) return f_status_set_error(f_invalid_parameter);
      if (input->stop < input->start) return f_status_set_error(f_invalid_parameter);
      if (buffer->used <= 0)  return f_status_set_error(f_invalid_parameter);
      if (input->start >= buffer->used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    // delimits must only be applied once a valid object is found
    f_string_lengths delimits = f_string_lengths_initialize;

    fl_fss_skip_past_whitespace(*buffer, input);
    fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders
    if (buffer->string[input->start] == f_eol) {
      status = fl_fss_increment_buffer(*buffer, input, 1);
      if (f_status_is_error(status)) return status;

      return fl_fss_found_no_object;
    }

    // begin the search
    found->start = input->start;

    // ignore all comment lines
    if (buffer->string[input->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*input), delimits, f_no_data_on_eos, f_no_data_on_stop)

      status = fl_fss_increment_buffer(*buffer, input, 1);
      if (f_status_is_error(status)) return status;

      return fl_fss_found_no_object;
    }

    // identify where the object ends
    while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
      if (buffer->string[input->start] == f_fss_delimit_slash) {
        f_string_length first_slash = input->start;
        f_string_length slash_count = 1;

        status = fl_fss_increment_buffer(*buffer, input, 1);
        if (f_status_is_error(status)) return status;

        while (input->start < buffer->used && input->start <= input->stop && (buffer->string[input->start] == f_fss_delimit_placeholder || buffer->string[input->start] == f_fss_delimit_slash)) {
          if (buffer->string[input->start] == f_fss_delimit_slash) {
            slash_count++;
          }

          status = fl_fss_increment_buffer(*buffer, input, 1);
          if (f_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

        if (buffer->string[input->start] == f_fss_basic_list_open) {
          f_string_length stop_point = input->start - 1;

          status = fl_fss_increment_buffer(*buffer, input, 1);
          if (f_status_is_error(status)) return status;

          while (input->start < buffer->used && input->start <= input->stop) {
            if (buffer->string[input->start] == f_eol || (status = fl_fss_is_graph(*buffer, *input)) == f_true) {
              break;
            }

            if (f_status_is_error(status)) return status;

            status = fl_fss_increment_buffer(*buffer, input, 1);
            if (f_status_is_error(status)) return status;
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

          if (buffer->string[input->start] == f_eol) {
            f_string_length location = input->start;

            input->start = first_slash;

            if (delimits.used + (slash_count / 2) >= delimits.size) {
              f_status allocation_status = f_none;

              f_macro_strings_string_lengths_resize(allocation_status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

              if (f_status_is_error(allocation_status)) {
                f_macro_strings_string_lengths_delete(allocation_status, delimits);
                return allocation_status;
              }
            }

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {
                if (buffer->string[input->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 != 0) {
                    delimits.array[delimits.used] = input->start;
                    delimits.used++;
                  }

                  slash_count--;
                }

                status = fl_fss_increment_buffer(*buffer, input, 1);
                if (f_status_is_error(status)) return status;
              } // while

              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              found->stop = stop_point;
              input->start = location + 1;

              return fl_fss_found_object;
            }

            input->start = location + 1;
            return fl_fss_found_no_object;
          }
        }

        continue;
      }
      else if (buffer->string[input->start] == f_fss_basic_list_open) {
        f_string_length stop_point = input->start - 1;

        status = fl_fss_increment_buffer(*buffer, input, 1);
        if (f_status_is_error(status)) return status;

        while (input->start < buffer->used && input->start <= input->stop) {
          if (buffer->string[input->start] == f_eol || (status = fl_fss_is_graph(*buffer, *input)) == f_true) {
            break;
          }

          if (f_status_is_error(status)) return status;

          status = fl_fss_increment_buffer(*buffer, input, 1);
          if (f_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)

        if (buffer->string[input->start] == f_eol) {
          fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

          found->stop = stop_point;

          status = fl_fss_increment_buffer(*buffer, input, 1);
          if (f_status_is_error(status)) return status;

          return fl_fss_found_object;
        }

        continue;
      }

      status = fl_fss_increment_buffer(*buffer, input, 1);
      if (f_status_is_error(status)) return status;
    } // while

    // seek to the end of the line when no valid object is found
    while (input->start < buffer->used && input->start <= input->stop && buffer->string[input->start] != f_eol) {
      status = fl_fss_increment_buffer(*buffer, input, 1);
      if (f_status_is_error(status)) return status;
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    status = fl_fss_increment_buffer(*buffer, input, 1);
    if (f_status_is_error(status)) return status;

    return fl_fss_found_no_object;
  }
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  f_return_status fl_fss_basic_list_content_read(f_dynamic_string *buffer, f_string_location *input, f_fss_content *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (input == 0) return f_status_set_error(f_invalid_parameter);
      if (found == 0) return f_status_set_error(f_invalid_parameter);
      if (input->start < 0) return f_status_set_error(f_invalid_parameter);
      if (input->stop < input->start) return f_status_set_error(f_invalid_parameter);
      if (buffer->used <= 0)  return f_status_set_error(f_invalid_parameter);
      if (input->start >= buffer->used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    // delimits must only be applied once a valid object is found
    f_string_lengths delimits = f_string_lengths_initialize;

    fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*input))
    fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)

    fl_macro_fss_allocate_content_if_necessary((*found), delimits);
    found->array[found->used].start = input->start;

    f_string_length last_newline = input->start;
    f_bool found_newline = f_false;

    // identify where the content ends
    while (input->start < buffer->used && input->start <= input->stop) {
      if (buffer->string[input->start] == f_eol) {
        found_newline = f_true;
        last_newline = input->start;

        status = fl_fss_increment_buffer(*buffer, input, 1);
        if (f_status_is_error(status)) return status;

        fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)

        continue;
      }

      if (buffer->string[input->start] == f_fss_delimit_slash) {
        f_string_length first_slash = input->start;
        f_string_length slash_count = 1;

        status = fl_fss_increment_buffer(*buffer, input, 1);
        if (f_status_is_error(status)) return status;

        while (input->start < buffer->used && input->start <= input->stop && (buffer->string[input->start] == f_fss_delimit_placeholder || buffer->string[input->start] == f_fss_delimit_slash)) {
          if (buffer->string[input->start] == f_fss_delimit_slash) {
            slash_count++;
          }

          status = fl_fss_increment_buffer(*buffer, input, 1);
          if (f_status_is_error(status)) return status;
        } // while

        if (found_newline) {
          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)
        }

        if (buffer->string[input->start] == f_fss_basic_list_open) {
          f_string_length stop_point = input->start - 1;

          status = fl_fss_increment_buffer(*buffer, input, 1);
          if (f_status_is_error(status)) return status;

          while (input->start < buffer->used && input->start <= input->stop) {
            if (buffer->string[input->start] == f_eol || (status = fl_fss_is_graph(*buffer, *input)) == f_true) {
              break;
            }

            if (f_status_is_error(status)) return status;

            status = fl_fss_increment_buffer(*buffer, input, 1);
            if (f_status_is_error(status)) return status;
          } // while

          if (found_newline) {
            fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)
          }
          else {
            fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)
          }

          if (buffer->string[input->start] == f_eol) {
            f_string_length location = input->start;

            input->start = first_slash;

            if (slash_count % 2 == 0) {
              // FIXME: apply delimits??
              if (found_newline) {
                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                found->array[found->used].stop = last_newline;
                input->start = last_newline + 1;
                found->used++;

                return fl_fss_found_content;
              }

              return fl_fss_found_no_content;
            }

            if (delimits.used + (slash_count / 2) >= delimits.size) {
              f_status allocation_status = f_none;

              f_macro_strings_string_lengths_resize(allocation_status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

              if (f_status_is_error(allocation_status)) {
                f_macro_strings_string_lengths_delete(allocation_status, delimits);
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

              status = fl_fss_increment_buffer(*buffer, input, 1);
              if (f_status_is_error(status)) return status;
            } // while

            found_newline = f_true;
            input->start = location + 1;
          }
        }

        continue;
      }
      else if (buffer->string[input->start] == f_fss_basic_list_open) {
        status = fl_fss_increment_buffer(*buffer, input, 1);
        if (f_status_is_error(status)) return status;

        while (input->start < buffer->used && input->start <= input->stop) {
          if (buffer->string[input->start] == f_eol || (status = fl_fss_is_graph(*buffer, *input)) == f_true) {
            break;
          }

          if (f_status_is_error(status)) return status;

          status = fl_fss_increment_buffer(*buffer, input, 1);
          if (f_status_is_error(status)) return status;
        } // while

        if (found_newline) {
          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)
        }

        if (buffer->string[input->start] == f_eol) {
          if (found_newline) {
            fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

            found->array[found->used].stop = last_newline;
            input->start = last_newline + 1;
            found->used++;

            return fl_fss_found_content;
          }

          if (!found_newline) {
            input->start = last_newline;
          }

          return fl_fss_found_no_content;
        }

        continue;
      }

      status = fl_fss_increment_buffer(*buffer, input, 1);
      if (f_status_is_error(status)) return status;
    } // while

    if (found_newline) {
      fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

      found->array[found->used].stop = last_newline - 1;
      input->start = last_newline + 1;
      found->used++;

      fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*input), (*found), delimits, f_none_on_eos, f_none_on_stop)

      return fl_fss_found_content;
    }

    fl_macro_fss_content_return_on_overflow((*buffer), (*input), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    return fl_fss_found_no_content;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifndef _di_fl_fss_basic_list_object_write_
  f_return_status fl_fss_basic_list_object_write(const f_dynamic_string object, f_string_location *input, f_dynamic_string *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    f_string_location buffer_position = f_string_location_initialize;
    f_string_length start_position = f_string_initialize;
    f_string_length pre_allocate_size = 0;
    f_string_length start_buffer = 0;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*input))

    if (input->start > input->stop) {
      return f_no_data_on_stop;
    }
    else if (input->start >= object.used) {
      return f_no_data_on_eos;
    }

    start_position = input->start;

    // add an additional 2 to ensure that there is room for the slash delimit and the object open character.
    pre_allocate_size = buffer->used + (input->stop - input->start) + 2 + f_fss_default_allocation_step_string;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);

      if (f_status_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop = buffer->used;

    while (input->start <= input->stop && input->start < object.used) {
      if (object.string[input->start] == f_fss_comment) {
        // comments are not allowed and this format has no way of "wrapping" a comment.
        return f_invalid_data;
      }
      else if ((status = fl_fss_is_graph(object, *input)) == f_true) {
        break;
      }
      else if (f_status_is_error(status)) {
        return status;
      }

      if (object.string[input->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = object.string[input->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(object, input, 1);
      if (f_status_is_error(status)) return status;
    } // while

    while (input->start <= input->stop && input->start < object.used) {
      if (object.string[input->start] == f_fss_delimit_slash) {
        f_string_length slash_count = 1;

        buffer->string[buffer_position.stop] = object.string[input->start];
        buffer_position.stop++;

        status = fl_fss_increment_buffer(object, input, 1);
        if (f_status_is_error(status)) return status;

        while (input->start <= input->stop && input->start < object.used) {
          if (object.string[input->start] == f_fss_delimit_placeholder) {
            status = fl_fss_increment_buffer(object, input, 1);
            if (f_status_is_error(status)) return status;

            continue;
          } else if (object.string[input->start] != f_fss_delimit_slash) {
            break;
          }

          buffer->string[buffer_position.stop] = object.string[input->start];
          buffer_position.stop++;

          status = fl_fss_increment_buffer(object, input, 1);
          if (f_status_is_error(status)) return status;

          slash_count++;
        } // while

        if (input->start > input->stop || input->start >= object.used) {
          pre_allocate_size += slash_count;

          if (pre_allocate_size > buffer->size) {
            f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

            if (f_status_is_error(status)) return status;
          }

          while (slash_count > 0) {
            buffer->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
            slash_count--;
          } // while

          break;
        }
      }
      else if (object.string[input->start] == f_eol) {
        if (buffer_position.stop == buffer_position.start) {
          return f_no_data_on_eol;
        }

        break;
      }

      if (object.string[input->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = object.string[input->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(object, input, 1);
      if (f_status_is_error(status)) return status;
    } // while

    buffer->string[buffer_position.stop] = f_fss_basic_list_open;
    buffer->string[buffer_position.stop + 1] = f_eol;
    buffer->used = buffer_position.stop + 2;

    if (input->start > input->stop) {
      return f_none_on_stop;
    }
    else if (input->start >= object.used) {
      return f_none_on_eos;
    }

    return f_none;
  }
#endif // _di_fl_fss_basic_list_object_write_

#ifndef _di_fl_fss_basic_list_content_write_
  f_return_status fl_fss_basic_list_content_write(const f_dynamic_string content, f_string_location *input, f_dynamic_string *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    f_bool is_comment = f_false;
    f_bool has_graph = f_false;

    f_string_location buffer_position = f_string_location_initialize;
    f_string_length start_position = f_string_initialize;
    f_string_length pre_allocate_size = 0;

    fl_macro_fss_skip_past_delimit_placeholders(content, (*input))

    if (input->start > input->stop) {
      return f_no_data_on_stop;
    }
    else if (input->start >= content.used) {
      return f_no_data_on_eos;
    }

    start_position = input->start;

    // add an additional 2 to ensure that there is room for the slash delimit and the content open character.
    pre_allocate_size = buffer->used + (input->stop - input->start) + 2 + f_fss_default_allocation_step_string;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);

      if (f_status_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop = buffer->used;

    while (input->start <= input->stop && input->start < content.used) {
      if (content.string[input->start] == f_fss_delimit_slash && !is_comment) {
        f_string_length slash_count = 1;

        buffer->string[buffer_position.stop] = content.string[input->start];
        buffer_position.stop++;

        has_graph = f_true;
        status = fl_fss_increment_buffer(content, input, 1);
        if (f_status_is_error(status)) return status;

        while (input->start <= input->stop && input->start < content.used) {
          if (content.string[input->start] == f_fss_delimit_placeholder) {
            status = fl_fss_increment_buffer(content, input, 1);
            if (f_status_is_error(status)) return status;

            continue;
          }
          else if (content.string[input->start] != f_fss_delimit_slash) {
            break;
          }

          buffer->string[buffer_position.stop] = content.string[input->start];
          buffer_position.stop++;

          status = fl_fss_increment_buffer(content, input, 1);
          if (f_status_is_error(status)) return status;

          slash_count++;
        } // while

        if (content.string[input->start] == f_fss_basic_list_open) {
          f_string_length location = input->start;

          status = fl_fss_increment_buffer(content, input, 1);
          if (f_status_is_error(status)) return status;

          while (input->start < content.used && input->start <= input->stop) {
            if (content.string[input->start] == f_eol || (status = fl_fss_is_graph(content, *input)) == f_true) {
              break;
            }

            if (f_status_is_error(status)) return status;

            status = fl_fss_increment_buffer(content, input, 1);
            if (f_status_is_error(status)) return status;
          } // while

          if (content.string[input->start] == f_eol || input->start >= content.used || input->start > input->stop) {
            pre_allocate_size += slash_count + 1;

            if (pre_allocate_size > buffer->size) {
              f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

              if (f_status_is_error(status)) return status;
            }

            while (slash_count > 0) {
              buffer->string[buffer_position.stop] = f_fss_delimit_slash;
              buffer_position.stop++;
              slash_count--;
            } // while

            buffer->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
            has_graph = f_false;
            is_comment = f_false;
          }

          buffer->string[buffer_position.stop] = f_fss_basic_list_open;
          buffer_position.stop++;
          input->start = location + 1;
          continue;
        }
      }
      else if (content.string[input->start] == f_fss_basic_list_open && !is_comment) {
        f_string_length location = input->start;

        has_graph = f_true;

        status = fl_fss_increment_buffer(content, input, 1);
        if (f_status_is_error(status)) return status;

        while (input->start < content.used && input->start <= input->stop) {
          if (content.string[input->start] == f_eol || (status = fl_fss_is_graph(content, *input)) == f_true) {
            break;
          }

          if (f_status_is_error(status)) return status;

          status = fl_fss_increment_buffer(content, input, 1);
          if (f_status_is_error(status)) return status;
        } // while

        if (content.string[input->start] == f_eol || input->start >= content.used || input->start > input->stop) {
          pre_allocate_size++;

          if (pre_allocate_size > buffer->size) {
            f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

            if (f_status_is_error(status)) return status;
          }

          buffer->string[buffer_position.stop] = f_fss_delimit_slash;
          buffer_position.stop++;
          has_graph = f_false;
          is_comment = f_false;
        }

        buffer->string[buffer_position.stop] = f_fss_basic_list_open;
        buffer_position.stop++;
        input->start = location + 1;
        continue;
      }
      else if (content.string[input->start] == f_fss_comment && !has_graph) {
        is_comment = f_true;
      }
      else if (content.string[input->start] == f_eol) {
        has_graph = f_false;
        is_comment = f_false;
      }
      else if ((status = fl_fss_is_graph(content, *input)) == f_true) {
        has_graph = f_true;
      }
      else if (f_status_is_error(status)) {
        return status;
      }

      if (content.string[input->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = content.string[input->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(content, input, 1);
      if (f_status_is_error(status)) return status;
    } // while

    buffer->string[buffer_position.stop] = f_eol;
    buffer->used = buffer_position.stop + 1;

    if (input->start > input->stop) {
      return f_none_on_stop;
    }
    else if (input->start >= content.used) {
      return f_none_on_eos;
    }

    return f_none;
  }
#endif // _di_fl_fss_basic_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
