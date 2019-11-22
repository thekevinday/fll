#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  f_return_status fl_fss_basic_list_object_read(f_string_dynamic *buffer, f_string_location *location, f_fss_object *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (found == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer->used <= 0)  return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer->used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths delimits = f_string_lengths_initialize;

    fl_fss_skip_past_whitespace(*buffer, location);
    fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders.
    if (buffer->string[location->start] == f_string_eol) {
      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;

      return fl_fss_found_no_object;
    }

    // begin the search.
    found->start = location->start;

    // ignore all comment lines.
    if (buffer->string[location->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*location), delimits, f_no_data_on_eos, f_no_data_on_stop)

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;

      return fl_fss_found_no_object;
    }

    // identify where the object ends.
    while (location->start < buffer->used && location->start <= location->stop && buffer->string[location->start] != f_string_eol) {
      if (buffer->string[location->start] == f_fss_delimit_slash) {
        f_string_length first_slash = location->start;
        f_string_length slash_count = 1;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;

        while (location->start < buffer->used && location->start <= location->stop && (buffer->string[location->start] == f_fss_delimit_placeholder || buffer->string[location->start] == f_fss_delimit_slash)) {
          if (buffer->string[location->start] == f_fss_delimit_slash) {
            slash_count++;
          }

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

        if (buffer->string[location->start] == f_fss_basic_list_open) {
          f_string_length stop_point = location->start - 1;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          while (location->start < buffer->used && location->start <= location->stop) {
            if (buffer->string[location->start] == f_string_eol || (status = fl_fss_is_graph(*buffer, *location)) == f_true) {
              break;
            }

            if (f_status_is_error(status)) return status;

            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (f_status_is_error(status)) return status;
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

          if (buffer->string[location->start] == f_string_eol) {
            f_string_length start = location->start;

            location->start = first_slash;

            if (delimits.used + (slash_count / 2) >= delimits.size) {
              f_macro_string_lengths_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

              if (f_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }
            }

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {
                if (buffer->string[location->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 != 0) {
                    delimits.array[delimits.used] = location->start;
                    delimits.used++;
                  }

                  slash_count--;
                }

                status = fl_fss_increment_buffer(*buffer, location, 1);
                if (f_status_is_error(status)) return status;
              } // while

              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              found->stop = stop_point;
              location->start = start + 1;

              return fl_fss_found_object;
            }

            location->start = start + 1;
            return fl_fss_found_no_object;
          }
        }

        continue;
      }
      else if (buffer->string[location->start] == f_fss_basic_list_open) {
        f_string_length stop_point = location->start - 1;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;

        while (location->start < buffer->used && location->start <= location->stop) {
          if (buffer->string[location->start] == f_string_eol || (status = fl_fss_is_graph(*buffer, *location)) == f_true) {
            break;
          }

          if (f_status_is_error(status)) return status;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)

        if (buffer->string[location->start] == f_string_eol) {
          fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

          found->stop = stop_point;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          return fl_fss_found_object;
        }

        continue;
      }

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;
    } // while

    // seek to the end of the line when no valid object is found.
    while (location->start < buffer->used && location->start <= location->stop && buffer->string[location->start] != f_string_eol) {
      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    status = fl_fss_increment_buffer(*buffer, location, 1);
    if (f_status_is_error(status)) return status;

    return fl_fss_found_no_object;
  }
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  f_return_status fl_fss_basic_list_content_read(f_string_dynamic *buffer, f_string_location *location, f_fss_content *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (location == 0) return f_status_set_error(f_invalid_parameter);
      if (found == 0) return f_status_set_error(f_invalid_parameter);
      if (location->start < 0) return f_status_set_error(f_invalid_parameter);
      if (location->stop < location->start) return f_status_set_error(f_invalid_parameter);
      if (buffer->used <= 0)  return f_status_set_error(f_invalid_parameter);
      if (location->start >= buffer->used) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    // delimits must only be applied once a valid object is found
    f_string_lengths delimits = f_string_lengths_initialize;

    fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*location))
    fl_macro_fss_content_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)

    fl_macro_fss_allocate_content_if_necessary((*found), delimits);
    found->array[found->used].start = location->start;

    f_string_length last_newline = location->start;
    bool found_newline = f_false;

    // identify where the content ends
    while (location->start < buffer->used && location->start <= location->stop) {
      if (buffer->string[location->start] == f_string_eol) {
        found_newline = f_true;
        last_newline = location->start;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;

        fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)

        continue;
      }

      if (buffer->string[location->start] == f_fss_delimit_slash) {
        f_string_length first_slash = location->start;
        f_string_length slash_count = 1;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;

        while (location->start < buffer->used && location->start <= location->stop && (buffer->string[location->start] == f_fss_delimit_placeholder || buffer->string[location->start] == f_fss_delimit_slash)) {
          if (buffer->string[location->start] == f_fss_delimit_slash) {
            slash_count++;
          }

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;
        } // while

        if (found_newline) {
          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)
        }

        if (buffer->string[location->start] == f_fss_basic_list_open) {
          f_string_length stop_point = location->start - 1;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          while (location->start < buffer->used && location->start <= location->stop) {
            if (buffer->string[location->start] == f_string_eol || (status = fl_fss_is_graph(*buffer, *location)) == f_true) {
              break;
            }

            if (f_status_is_error(status)) return status;

            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (f_status_is_error(status)) return status;
          } // while

          if (found_newline) {
            fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)
          }
          else {
            fl_macro_fss_content_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)
          }

          if (buffer->string[location->start] == f_string_eol) {
            f_string_length start = location->start;

            location->start = first_slash;

            if (slash_count % 2 == 0) {
              if (found_newline) {
                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                found->array[found->used].stop = last_newline;
                location->start = last_newline + 1;
                found->used++;

                return fl_fss_found_content;
              }

              return fl_fss_found_no_content;
            }

            if (delimits.used + (slash_count / 2) >= delimits.size) {
              f_macro_string_lengths_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

              if (f_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }
            }

            while (slash_count > 0) {
              if (buffer->string[location->start] == f_fss_delimit_slash) {
                if (slash_count % 2 != 0) {
                  delimits.array[delimits.used] = location->start;
                  delimits.used++;
                }

                slash_count--;
              }

              status = fl_fss_increment_buffer(*buffer, location, 1);
              if (f_status_is_error(status)) return status;
            } // while

            found_newline = f_true;
            location->start = start + 1;
          }
        }

        continue;
      }
      else if (buffer->string[location->start] == f_fss_basic_list_open) {
        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;

        while (location->start < buffer->used && location->start <= location->stop) {
          if (buffer->string[location->start] == f_string_eol || (status = fl_fss_is_graph(*buffer, *location)) == f_true) {
            break;
          }

          if (f_status_is_error(status)) return status;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;
        } // while

        if (found_newline) {
          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)
        }

        if (buffer->string[location->start] == f_string_eol) {
          if (found_newline) {
            fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

            found->array[found->used].stop = last_newline;
            location->start = last_newline + 1;
            found->used++;

            return fl_fss_found_content;
          }

          if (!found_newline) {
            location->start = last_newline;
          }

          return fl_fss_found_no_content;
        }

        continue;
      }

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;
    } // while

    if (found_newline) {
      fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

      found->array[found->used].stop = last_newline - 1;
      location->start = last_newline + 1;
      found->used++;

      fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)

      return fl_fss_found_content;
    }

    fl_macro_fss_content_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    return fl_fss_found_no_content;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifndef _di_fl_fss_basic_list_object_write_
  f_return_status fl_fss_basic_list_object_write(const f_string_dynamic object, f_string_location *location, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    f_string_location buffer_position = f_string_location_initialize;
    f_string_length start_position = f_string_initialize;
    f_string_length pre_allocate_size = 0;
    f_string_length start_buffer = 0;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*location))

    if (location->start > location->stop) {
      return f_no_data_on_stop;
    }
    else if (location->start >= object.used) {
      return f_no_data_on_eos;
    }

    start_position = location->start;

    // add an additional 2 to ensure that there is room for the slash delimit and the object open character.
    pre_allocate_size = buffer->used + (location->stop - location->start) + 2 + f_fss_default_allocation_step_string;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);

      if (f_status_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop = buffer->used;

    while (location->start <= location->stop && location->start < object.used) {
      if (object.string[location->start] == f_fss_comment) {
        // comments are not allowed and this format has no way of "wrapping" a comment.
        return f_status_set_error(fl_fss_found_comment);
      }
      else if ((status = fl_fss_is_graph(object, *location)) == f_true) {
        break;
      }
      else if (f_status_is_error(status)) {
        return status;
      }

      if (object.string[location->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = object.string[location->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(object, location, 1);
      if (f_status_is_error(status)) return status;
    } // while

    while (location->start <= location->stop && location->start < object.used) {
      if (object.string[location->start] == f_fss_delimit_slash) {
        f_string_length slash_count = 1;

        buffer->string[buffer_position.stop] = object.string[location->start];
        buffer_position.stop++;

        status = fl_fss_increment_buffer(object, location, 1);
        if (f_status_is_error(status)) return status;

        while (location->start <= location->stop && location->start < object.used) {
          if (object.string[location->start] == f_fss_delimit_placeholder) {
            status = fl_fss_increment_buffer(object, location, 1);
            if (f_status_is_error(status)) return status;

            continue;
          } else if (object.string[location->start] != f_fss_delimit_slash) {
            break;
          }

          buffer->string[buffer_position.stop] = object.string[location->start];
          buffer_position.stop++;

          status = fl_fss_increment_buffer(object, location, 1);
          if (f_status_is_error(status)) return status;

          slash_count++;
        } // while

        if (location->start > location->stop || location->start >= object.used) {
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
      else if (object.string[location->start] == f_string_eol) {
        if (buffer_position.stop == buffer_position.start) {
          return f_no_data_on_eol;
        }

        break;
      }

      if (object.string[location->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = object.string[location->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(object, location, 1);
      if (f_status_is_error(status)) return status;
    } // while

    buffer->string[buffer_position.stop] = f_fss_basic_list_open;
    buffer->string[buffer_position.stop + 1] = f_string_eol;
    buffer->used = buffer_position.stop + 2;

    if (location->start > location->stop) {
      return f_none_on_stop;
    }
    else if (location->start >= object.used) {
      return f_none_on_eos;
    }

    return f_none;
  }
#endif // _di_fl_fss_basic_list_object_write_

#ifndef _di_fl_fss_basic_list_content_write_
  f_return_status fl_fss_basic_list_content_write(const f_string_dynamic content, f_string_location *location, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    bool is_comment = f_false;
    bool has_graph = f_false;

    f_string_location buffer_position = f_string_location_initialize;
    f_string_length start_position = f_string_initialize;
    f_string_length pre_allocate_size = 0;

    fl_macro_fss_skip_past_delimit_placeholders(content, (*location))

    if (location->start > location->stop) {
      return f_no_data_on_stop;
    }
    else if (location->start >= content.used) {
      return f_no_data_on_eos;
    }

    start_position = location->start;

    // add an additional 2 to ensure that there is room for the slash delimit and the content open character.
    pre_allocate_size = buffer->used + (location->stop - location->start) + 2 + f_fss_default_allocation_step_string;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);

      if (f_status_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop = buffer->used;

    while (location->start <= location->stop && location->start < content.used) {
      if (content.string[location->start] == f_fss_delimit_slash && !is_comment) {
        f_string_length slash_count = 1;

        buffer->string[buffer_position.stop] = content.string[location->start];
        buffer_position.stop++;

        has_graph = f_true;
        status = fl_fss_increment_buffer(content, location, 1);
        if (f_status_is_error(status)) return status;

        while (location->start <= location->stop && location->start < content.used) {
          if (content.string[location->start] == f_fss_delimit_placeholder) {
            status = fl_fss_increment_buffer(content, location, 1);
            if (f_status_is_error(status)) return status;

            continue;
          }
          else if (content.string[location->start] != f_fss_delimit_slash) {
            break;
          }

          buffer->string[buffer_position.stop] = content.string[location->start];
          buffer_position.stop++;

          status = fl_fss_increment_buffer(content, location, 1);
          if (f_status_is_error(status)) return status;

          slash_count++;
        } // while

        if (content.string[location->start] == f_fss_basic_list_open) {
          f_string_length start = location->start;

          status = fl_fss_increment_buffer(content, location, 1);
          if (f_status_is_error(status)) return status;

          while (location->start < content.used && location->start <= location->stop) {
            if (content.string[location->start] == f_string_eol || (status = fl_fss_is_graph(content, *location)) == f_true) {
              break;
            }

            if (f_status_is_error(status)) return status;

            status = fl_fss_increment_buffer(content, location, 1);
            if (f_status_is_error(status)) return status;
          } // while

          if (content.string[location->start] == f_string_eol || location->start >= content.used || location->start > location->stop) {
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
          location->start = start + 1;
          continue;
        }
      }
      else if (content.string[location->start] == f_fss_basic_list_open && !is_comment) {
        f_string_length start = location->start;

        has_graph = f_true;

        status = fl_fss_increment_buffer(content, location, 1);
        if (f_status_is_error(status)) return status;

        while (location->start < content.used && location->start <= location->stop) {
          if (content.string[location->start] == f_string_eol || (status = fl_fss_is_graph(content, *location)) == f_true) {
            break;
          }

          if (f_status_is_error(status)) return status;

          status = fl_fss_increment_buffer(content, location, 1);
          if (f_status_is_error(status)) return status;
        } // while

        if (content.string[location->start] == f_string_eol || location->start >= content.used || location->start > location->stop) {
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
        location->start = start + 1;
        continue;
      }
      else if (content.string[location->start] == f_fss_comment && !has_graph) {
        is_comment = f_true;
      }
      else if (content.string[location->start] == f_string_eol) {
        has_graph = f_false;
        is_comment = f_false;
      }
      else if ((status = fl_fss_is_graph(content, *location)) == f_true) {
        has_graph = f_true;
      }
      else if (f_status_is_error(status)) {
        f_status status2 = f_status_set_fine(status);

        if (status2 == f_failure) {
          return f_status_set_error(f_invalid_utf);
        }

        if (status2 == f_failure) {
          return f_status_set_error(f_incomplete_utf);
        }

        return status;
      }

      if (content.string[location->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = content.string[location->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(content, location, 1);
      if (f_status_is_error(status)) return status;
    } // while

    buffer->string[buffer_position.stop] = f_string_eol;
    buffer->used = buffer_position.stop + 1;

    if (location->start > location->stop) {
      return f_none_on_stop;
    }
    else if (location->start >= content.used) {
      return f_none_on_eos;
    }

    return f_none;
  }
#endif // _di_fl_fss_basic_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
