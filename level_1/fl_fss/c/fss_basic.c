#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_object_read_
  f_return_status fl_fss_basic_object_read(f_string_dynamic *buffer, f_string_location *location, f_fss_object *found) {
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

    fl_fss_skip_past_whitespace(*buffer, location);
    fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders
    if (buffer->string[location->start] == f_fss_basic_close) {
      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;

      return fl_fss_found_no_object;
    }

    // when handling delimits, the only time they should be applied is when a valid object would exist
    // however, the delimits will appear before a valid object, so remember their positions and only apply them after a would be valid object is confirmed
    f_bool has_delimit = f_false;

    // begin the search
    found->start = location->start;

    // ignore all comment lines
    if (buffer->string[location->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*location), delimits, f_no_data_on_eos, f_no_data_on_stop)

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;

      return fl_fss_found_no_object;
    }

    // handle quote support
    int8_t quoted = f_string_eos;

    // identify where the object begins
    if (buffer->string[location->start] == f_fss_delimit_slash) {
      f_string_length last_slash = location->start;

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;


      while (location->start <= location->stop && location->start < buffer->used) {
        if (buffer->string[location->start] == f_fss_delimit_placeholder) {

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          continue;
        }
        else {
          status = fl_fss_is_graph(*buffer, *location);
          if (status == f_false) {
            found->stop = location->start - 1;

            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (f_status_is_error(status)) return status;

            return fl_fss_found_object;
          }
          else if (f_status_is_error(status)) {
            return status;
          }
          else if (buffer->string[location->start] != f_fss_delimit_slash) {
            break;
          }
        }

        last_slash = location->start;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;
      } // while

      fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)

      if (buffer->string[location->start] == f_fss_delimit_single_quote || buffer->string[location->start] == f_fss_delimit_double_quote) {
        if (delimits.used >= delimits.size) {
          f_status allocation_status = f_none;

           f_macro_string_lengths_resize(allocation_status, delimits, delimits.size + f_fss_default_allocation_step);

          if (f_status_is_error(allocation_status)) {
            f_macro_string_lengths_delete(allocation_status, delimits);
            return allocation_status;
          }
        }

        delimits.array[delimits.used] = last_slash;
        delimits.used++;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;
      }
    }
    else if (buffer->string[location->start] == f_fss_delimit_single_quote || buffer->string[location->start] == f_fss_delimit_double_quote) {
      quoted = buffer->string[location->start];

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;

      found->start = location->start;
    }

    // identify where the object ends
    if (quoted == f_string_eos) {
      status = f_none;
      while (buffer->string[location->start] == f_fss_delimit_placeholder || (status = fl_fss_is_graph(*buffer, *location)) == f_true) {
        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;

        fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)
      } // while

      if (f_status_is_error(status)) return status;

      status = fl_fss_is_space(*buffer, *location);
      if (status == f_true) {
        found->stop = location->start - 1;

        fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

        if (buffer->string[location->start] == f_string_eol) {
          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          return fl_fss_found_object_no_content;
        }

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;

        return fl_fss_found_object;
      }
      else if (f_status_is_error(status)) {
        return status;
      }
    }
    else {
      while (location->start <= location->stop && location->start < buffer->used) {
        if (buffer->string[location->start] == f_fss_delimit_slash) {
          f_string_length first_slash = location->start;
          f_string_length slash_count = 1;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;


          while (location->start <= location->stop && location->start < buffer->used) {
            if (buffer->string[location->start] == f_fss_delimit_placeholder) {

              status = fl_fss_increment_buffer(*buffer, location, 1);
              if (f_status_is_error(status)) return status;

              continue;
            }
            else if (buffer->string[location->start] != f_fss_delimit_slash) {
              break;
            }

            slash_count++;

            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (f_status_is_error(status)) return status;
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_status_is_warning(f_unterminated_group_on_eos), f_status_is_warning(f_unterminated_group_on_stop))

          if (buffer->string[location->start] == quoted) {
            f_string_length length = location->start;

            location->start = first_slash;

            if (slash_count % 2 == 0) {
              if (delimits.used + (slash_count / 2) >= delimits.size) {
                f_status allocation_status = f_none;

                f_macro_string_lengths_resize(allocation_status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                if (f_status_is_error(allocation_status)) {
                  f_macro_string_lengths_delete(allocation_status, delimits);
                  return allocation_status;
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

              location->start = length + 1;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*location))
              fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)

              if ((status = fl_fss_is_graph(*buffer, *location)) == f_true) {
                while (location->start < buffer->used && location->start <= location->stop && buffer->string[location->start] != f_string_eol) {
                  status = fl_fss_increment_buffer(*buffer, location, 1);
                  if (f_status_is_error(status)) return status;
                } // while

                fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

                {
                  f_status allocation_status = f_none;

                  f_macro_string_lengths_delete(allocation_status, delimits);
                }

                status = fl_fss_increment_buffer(*buffer, location, 1);
                if (f_status_is_error(status)) return status;

                return fl_fss_found_no_object;
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
              else if (buffer->string[location->start] == f_string_eol) {
                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                found->stop = length - 1;

                status = fl_fss_increment_buffer(*buffer, location, 1);
                if (f_status_is_error(status)) return status;


                return fl_fss_found_object_no_content;
              }

              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              found->stop = length - 1;

              status = fl_fss_increment_buffer(*buffer, location, 1);
              if (f_status_is_error(status)) return status;

              return fl_fss_found_object;
            }
            else {
              if (delimits.used + (slash_count / 2) >= delimits.size) {
                f_status allocation_status = f_none;

                f_macro_string_lengths_resize(allocation_status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                if (f_status_is_error(allocation_status)) {
                  f_macro_string_lengths_delete(allocation_status, delimits);
                  return allocation_status;
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

              location->start = length;
            }
          }
        }
        else if (buffer->string[location->start] == quoted) {
          found->stop = location->start - 1;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          while (location->start <= location->stop && location->start < buffer->used) {
            if (buffer->string[location->start] == f_string_eol) {
              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              status = fl_fss_increment_buffer(*buffer, location, 1);
              if (f_status_is_error(status)) return status;

              return fl_fss_found_object_no_content;
            }
            else if ((status = fl_fss_is_space(*buffer, *location)) == f_true) {
              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              status = fl_fss_increment_buffer(*buffer, location, 1);
              if (f_status_is_error(status)) return status;

              return fl_fss_found_object;
            }
            else if (f_status_is_error(status)) {
              return status;
            }
            else if (buffer->string[location->start] != f_fss_delimit_placeholder) {
              while (location->start < buffer->used && location->start <= location->stop && buffer->string[location->start] != f_string_eol) {

                status = fl_fss_increment_buffer(*buffer, location, 1);
                if (f_status_is_error(status)) return status;

              } // while

              fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

              {
                f_status allocation_status = f_none;

                f_macro_string_lengths_delete(allocation_status, delimits);
              }

              status = fl_fss_increment_buffer(*buffer, location, 1);
              if (f_status_is_error(status)) return status;

              return fl_fss_found_no_object;
            }


            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (f_status_is_error(status)) return status;
          } // while

          fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)
        }
        else if (buffer->string[location->start] == f_string_eol) {
          {
            f_status allocation_status = f_none;

            f_macro_string_lengths_delete(allocation_status, delimits);
          }

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          return fl_fss_found_no_object;
        }


        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;
      } // while

      fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_status_is_warning(f_unterminated_group_on_eos), f_status_is_warning(f_unterminated_group_on_stop))
    }

    // seek to the end of the line when no valid object is found
    while (location->start < buffer->used && location->start <= location->stop && buffer->string[location->start] != f_string_eol) {
      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, f_no_data_on_eos, f_no_data_on_stop)

    {
      f_status allocation_status = f_none;

      f_macro_string_lengths_delete(allocation_status, delimits);
    }


    status = fl_fss_increment_buffer(*buffer, location, 1);
    if (f_status_is_error(status)) return status;

    return fl_fss_found_no_object;
  }
#endif // _di_fl_fss_basic_object_read_

#ifndef _di_fl_fss_basic_content_read_
  f_return_status fl_fss_basic_content_read(f_string_dynamic *buffer, f_string_location *location, f_fss_content *found) {
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

    fl_fss_skip_past_whitespace(*buffer, location);
    fl_macro_fss_content_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders
    if (buffer->string[location->start] == f_string_eol) {
      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;

      return fl_fss_found_no_content;
    }

    fl_macro_fss_allocate_content_if_necessary((*found), delimits);
    found->array[found->used].start = location->start;

    // search for valid content
    do {
      fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*location))
      fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, f_none_on_eos, f_none_on_stop)

      if (buffer->string[location->start] == f_fss_basic_close) break;

      ++location->start;
    } while (f_true);

    // Save the stop length
    found->array[found->used].stop = location->start - 1;
    found->used++;

    status = fl_fss_increment_buffer(*buffer, location, 1);
    if (f_status_is_error(status)) return status;

    return fl_fss_found_content;
  }
#endif // _di_fl_fss_basic_content_read_

#ifndef _di_fl_fss_basic_object_write_
  f_return_status fl_fss_basic_object_write(f_string_dynamic *buffer, const f_string_dynamic object, f_string_location *location) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    f_bool quoted = f_false;

    f_string_location buffer_position = f_string_location_initialize;
    f_string_length start_position = f_string_initialize;
    f_string_length pre_allocate_size = 0;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*location))

    if (location->start > location->stop) {
      return f_no_data_on_stop;
    }
    else if (location->start >= object.used) {
      return f_no_data_on_eos;
    }

    start_position = location->start;

    // add an additional 3 to ensure that there is room for the start and stop quotes or a slash delimit and the object open character.
    pre_allocate_size = buffer->used + (location->stop - location->start) + 3 + f_fss_default_allocation_step_string;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);

      if (f_status_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop  = buffer->used;

    if (object.string[location->start] == f_fss_delimit_slash) {
      while (location->start <= location->stop && location->start < object.used) {
        if (object.string[location->start] == f_fss_delimit_placeholder) {
          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          continue;
        }
        else if (object.string[location->start] != f_fss_delimit_slash) {
          break;
        }

        buffer->string[buffer_position.stop] = object.string[location->start];
        buffer_position.stop++;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;
      } // while

      if (object.string[location->start] == f_fss_delimit_single_quote || object.string[location->start] == f_fss_delimit_double_quote) {
        pre_allocate_size++;

        if (pre_allocate_size > buffer->size) {
          f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

          if (f_status_is_error(status)) return status;
        }

        buffer->string[buffer_position.stop] = f_fss_delimit_slash;
        buffer->string[buffer_position.stop + 1] = object.string[location->start];
        buffer_position.stop += 2;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;
      }
    }
    else if (object.string[location->start] == f_fss_delimit_single_quote || object.string[location->start] == f_fss_delimit_double_quote) {
      pre_allocate_size++;

      if (pre_allocate_size > buffer->size) {
        f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

        if (f_status_is_error(status)) return status;
      }

      buffer->string[buffer_position.stop] = f_fss_delimit_slash;
      buffer->string[buffer_position.stop + 1] = object.string[location->start];
      buffer_position.stop += 2;

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;
    }
    else if (object.string[location->start] == f_fss_comment) {
      quoted = f_true;
    }

    while (location->start <= location->stop && location->start < object.used) {
      if (object.string[location->start] == f_fss_delimit_placeholder) {
        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (f_status_is_error(status)) return status;

        continue;
      }
      else if (object.string[location->start] == f_string_eol) {
        if (quoted) {
          buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
          buffer_position.stop++;
        }

        buffer->string[buffer_position.stop] = f_fss_basic_open;
        buffer->used = buffer_position.stop + 1;

        return f_none_on_eol;
      }
      else if ((status = fl_fss_is_space(*buffer, *location)) == f_true || quoted) {
        pre_allocate_size++;

        if (pre_allocate_size > buffer->size) {
          f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

          if (f_status_is_error(status)) return status;
        }

        // restart the loop searching for f_fss_delimit_double_quote.
        location->start = start_position;
        buffer_position.stop = buffer_position.start;

        buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
        buffer_position.stop++;

        while (location->start <= location->stop && location->start < object.used) {
          if (object.string[location->start] == f_fss_delimit_placeholder) {
            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (f_status_is_error(status)) return status;

            continue;
          }
          else if (object.string[location->start] == f_fss_delimit_double_quote) {
            pre_allocate_size++;

            if (pre_allocate_size > buffer->size) {
              f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

              if (f_status_is_error(status)) return status;
            }

            buffer->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
          }
          else if (object.string[location->start] == f_fss_delimit_slash) {
            f_string_length slash_count = 0;

            do {
              buffer->string[buffer_position.stop] = object.string[location->start];
              buffer_position.stop++;
              slash_count++;

              status = fl_fss_increment_buffer(*buffer, location, 1);
              if (f_status_is_error(status)) return status;


              fl_macro_fss_skip_past_delimit_placeholders(object, (*location));

              if (location->start > location->stop || location->start >= object.used) {
                break;
              }

              if (object.string[location->start] == f_fss_delimit_double_quote) {
                pre_allocate_size += slash_count;

                if (pre_allocate_size > buffer->size) {
                  f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

                  if (f_status_is_error(status)) return status;
                }

                break;
              }
              else if (object.string[location->start] != f_fss_delimit_slash) {
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
          }
          else if (object.string[location->start] == f_string_eol) {
            buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
            buffer_position.stop++;

            buffer->string[buffer_position.stop] = f_fss_basic_open;
            buffer->used = buffer_position.stop + 1;

            return f_none_on_eol;
          }

          buffer->string[buffer_position.stop] = object.string[location->start];

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (f_status_is_error(status)) return status;

          buffer_position.stop++;
        } // while

        buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
        buffer->string[buffer_position.stop + 1] = f_fss_basic_open;
        buffer->used = buffer_position.stop + 2;
        break;
      }
      else if (f_status_is_error(status)) {
        return status;
      }

      buffer->string[buffer_position.stop] = object.string[location->start];

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (f_status_is_error(status)) return status;

      buffer_position.stop++;
    } // while

    if (buffer->used < buffer_position.stop) {
      buffer->string[buffer_position.stop] = f_fss_basic_open;
      buffer->used = buffer_position.stop + 1;
    }

    if (location->start > location->stop) {
      return f_none_on_stop;
    }
    else if (location->start >= object.used) {
      return f_none_on_eos;
    }

    return f_none;
  }
#endif // _di_fl_fss_basic_object_write_

#ifndef _di_fl_fss_basic_content_write_
  f_return_status fl_fss_basic_content_write(f_string_dynamic *buffer, const f_string_dynamic content, f_string_location *location) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    f_string_location input_position = f_string_location_initialize;
    f_string_location buffer_position = f_string_location_initialize;
    f_string_length pre_allocate_size = 0;

    // add an additional 1 to ensure that there is room for the terminating newline.
    pre_allocate_size = buffer->used + (content.used) + 1 + f_fss_default_allocation_step_string;

    buffer_position.start = buffer->used;
    buffer_position.stop = buffer->used;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);

      if (f_status_is_error(status)) return status;
    }

    while (location->start <= location->stop && location->start < content.used) {
      if (content.string[location->start] == f_string_eol){
        buffer->string[buffer_position.stop] = f_string_eol;
        buffer->used = buffer_position.stop + 1;
        return f_none_on_eos;
      }

      if (content.string[location->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = content.string[location->start];
        buffer_position.stop++;
      }

      fl_fss_increment_buffer(*buffer, location, 1);
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
#endif // _di_fl_fss_basic_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
