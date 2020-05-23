#include <level_1/fss_basic.h>
#include <level_0/print.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_list_object_read_
  f_return_status fl_fss_extended_list_object_read(f_string_dynamic *buffer, f_string_range *location, f_fss_object *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (location == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
      if (location->start < 0) return F_status_set_error(F_parameter);
      if (location->stop < location->start) return F_status_set_error(F_parameter);
      if (buffer->used <= 0)  return F_status_set_error(F_parameter);
      if (location->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths delimits = f_string_lengths_initialize;

    fl_fss_skip_past_space(*buffer, location);
    fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, F_data_no_eos, F_data_no_stop)

    // return found nothing if this line only contains whitespace and delimit placeholders.
    if (buffer->string[location->start] == f_string_eol) {
      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (F_status_is_error(status)) return status;

      return FL_fss_found_object_not;
    }

    // begin the search.
    found->start = location->start;

    // ignore all comment lines.
    if (buffer->string[location->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*location), delimits, F_data_no_eos, F_data_no_stop)

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (F_status_is_error(status)) return status;

      return FL_fss_found_object_not;
    }

    // identify where the object ends.
    while (location->start < buffer->used && location->start <= location->stop && buffer->string[location->start] != f_string_eol) {
      if (buffer->string[location->start] == f_fss_delimit_slash) {
        f_string_length first_slash = location->start;
        f_string_length slash_count = 1;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (F_status_is_error(status)) return status;

        while (location->start < buffer->used && location->start <= location->stop && (buffer->string[location->start] == f_fss_delimit_placeholder || buffer->string[location->start] == f_fss_delimit_slash)) {
          if (buffer->string[location->start] == f_fss_delimit_slash) {
            slash_count++;
          }

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (F_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, F_data_no_eos, F_data_no_stop)

        if (buffer->string[location->start] == f_fss_extended_list_open) {
          f_string_length stop_point = location->start - 1;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (F_status_is_error(status)) return status;

          while (location->start < buffer->used && location->start <= location->stop) {
            if (buffer->string[location->start] == f_string_eol || (status = fl_fss_is_graph(*buffer, *location)) == F_true) {
              break;
            }

            if (F_status_is_error(status)) return status;

            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (F_status_is_error(status)) return status;
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, F_data_no_eos, F_data_no_stop)

          if (buffer->string[location->start] == f_string_eol) {
            f_string_length start = location->start;

            location->start = first_slash;

            if (delimits.used + (slash_count / 2) >= delimits.size) {
              f_macro_string_lengths_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

              if (F_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }
            }

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {
                if (buffer->string[location->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 == 1) {
                    delimits.array[delimits.used] = location->start;
                    delimits.used++;
                  }

                  slash_count--;
                }

                status = fl_fss_increment_buffer(*buffer, location, 1);
                if (F_status_is_error(status)) return status;
              } // while

              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              found->stop = stop_point;
              location->start = start + 1;

              return FL_fss_found_object;
            }

            location->start = start + 1;
            return FL_fss_found_object_not;
          }
        }

        continue;
      }
      else if (buffer->string[location->start] == f_fss_extended_list_open) {
        f_string_length stop_point = location->start - 1;

        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (F_status_is_error(status)) return status;

        while (location->start < buffer->used && location->start <= location->stop) {
          if (buffer->string[location->start] == f_string_eol || (status = fl_fss_is_graph(*buffer, *location)) == F_true) {
            break;
          }

          if (F_status_is_error(status)) return status;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (F_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, F_none_eos, F_none_stop)

        if (buffer->string[location->start] == f_string_eol) {
          fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

          found->stop = stop_point;

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (F_status_is_error(status)) return status;

          return FL_fss_found_object;
        }

        continue;
      }

      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (F_status_is_error(status)) return status;
    } // while

    // seek to the end of the line when no valid object is found.
    while (location->start < buffer->used && location->start <= location->stop && buffer->string[location->start] != f_string_eol) {
      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (F_status_is_error(status)) return status;
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*location), (*found), delimits, F_data_no_eos, F_data_no_stop)

    status = fl_fss_increment_buffer(*buffer, location, 1);
    if (F_status_is_error(status)) return status;

    return FL_fss_found_object_not;
  }
#endif // _di_fl_fss_extended_list_object_read_

#ifndef _di_fl_fss_extended_list_content_read_
  f_return_status fl_fss_extended_list_content_read(f_string_dynamic *buffer, f_string_range *location, f_fss_nest *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (location == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
      if (location->start < 0) return F_status_set_error(F_parameter);
      if (location->stop < location->start) return F_status_set_error(F_parameter);
      if (buffer->used <= 0)  return F_status_set_error(F_parameter);
      if (location->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths delimits = f_string_lengths_initialize;
    f_string_lengths positions_start = f_string_lengths_initialize;
    f_fss_objects objects = f_fss_objects_initialize;

    fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*location))
    fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), positions_start, delimits, objects, F_none_eos, F_none_stop)

    if (found->used + 1 >= found->size) {
      f_macro_fss_nest_resize(status, (*found), found->size + f_fss_default_allocation_step + 1);

      if (F_status_is_error(status)) {
        f_macro_string_lengths_delete_simple(delimits);
        return status;
      }
    }

    f_array_length depth = 0;
    f_string_length position_previous = location->start;
    f_string_length line_start = location->start;
    f_string_length last_newline = location->start;

    f_macro_string_lengths_new(status, positions_start, f_fss_default_allocation_step);
    if (F_status_is_error(status)) {
      f_macro_string_lengths_delete_simple(delimits);

      return status;
    }

    f_macro_fss_objects_new(status, objects, f_fss_default_allocation_step);
    if (F_status_is_error(status)) {
      f_macro_string_lengths_delete_simple(positions_start);
      f_macro_string_lengths_delete_simple(delimits);

      return status;
    }

    // initialize depth 1 start position.
    // positions_start.used is used as a max depth (such that positions_start.used == max depth + 1).
    positions_start.array[0] = location->start;
    positions_start.used = 1;

    while (location->start < buffer->used && location->start <= location->stop) {
      if (buffer->string[location->start] == f_string_eol) {
        last_newline = location->start;
        position_previous = location->start;
        location->start++;

        if (depth > 0) {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
        }
        else {
          fl_macro_fss_nest_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_none_eos, F_none_stop)
        }

        line_start = location->start;
        continue;
      }

      if (buffer->string[location->start] == f_fss_delimit_slash) {
        f_string_length slash_first = location->start;
        f_string_length slash_last = location->start;
        f_string_length slash_count = 1;

        position_previous = location->start;
        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          f_macro_string_lengths_delete_simple(positions_start);
          f_macro_fss_objects_delete_simple(objects);

          return status;
        }

        while (location->start < buffer->used && location->start <= location->stop && (buffer->string[location->start] == f_fss_delimit_placeholder || buffer->string[location->start] == f_fss_delimit_slash)) {
          position_previous = location->start;

          if (buffer->string[location->start] == f_fss_delimit_slash) {
            slash_last = location->start;
            slash_count++;
          }

          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            f_macro_string_lengths_delete_simple(positions_start);
            f_macro_fss_objects_delete_simple(objects);

            return status;
          }
        } // while

        if (depth > 0) {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
        }
        else {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_data_no_eos, F_data_no_stop)
        }

        // All slashes for an open are delimited (because it could represent a slash in the object name).
        // for example 'object {' = valid open, name 'object', 'object \{' represents 'object {', 'object \\{' = valid open, name 'object \', 'object \\\{' represents 'object \{', etc..
        // Only the first slash before a close is delimited, all others are maintained.
        // for example '}' = valid close, '\}' represents '}', '\\}' represents '\}', '\\\}' represents '\\}', '\\\\}' represents '\\\}', and so on..
        // When slash is odd and a (delimited) valid open/close is found, then save delimited positions and continue.
        if (buffer->string[location->start] == f_string_eol) {
          last_newline = location->start;
          position_previous = location->start;
          location->start++;
          line_start = location->start;
        }
        else if (buffer->string[location->start] == f_fss_extended_list_open || buffer->string[location->start] == f_fss_extended_list_close) {
          f_string_length before_list_open = position_previous;
          bool is_open = F_false;

          if (buffer->string[location->start] == f_fss_extended_list_open) {
            is_open = F_true;
          }

          position_previous = location->start;
          location->start++;

          while (location->start < buffer->used && location->start <= location->stop) {
            if (buffer->string[location->start] == f_string_eol) {
              last_newline = location->start;
              line_start = location->start + 1;
              break;
            }

            if (buffer->string[location->start] != f_fss_delimit_placeholder && (status = fl_fss_is_space(*buffer, *location)) == F_false) {
              break;
            }

            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }

            position_previous = location->start;
            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }
          } // while

          if (depth > 0) {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
          }
          else {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_data_no_eos, F_data_no_stop)
          }

          // this is a valid object open/close that has been delimited, save the slash delimit positions.
          if (buffer->string[location->start] == f_string_eol) {
            last_newline = location->start;
            line_start = location->start + 1;

            if (is_open) {
              bool is_object = F_false;

              if (slash_count % 2 == 0) {
                is_object = F_true;
              }

              location->start = slash_first;

              if (delimits.used + (slash_count / 2) >= delimits.size) {
                f_macro_string_lengths_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                if (F_status_is_error(status)) {
                  location->start = last_newline;

                  f_macro_string_lengths_delete_simple(delimits);
                  f_macro_string_lengths_delete_simple(positions_start);
                  f_macro_fss_objects_delete_simple(objects);

                  return status;
                }
              }

              // apply slash delimits, only slashes and placeholders should be present.
              while (slash_count > 0) {
                if (buffer->string[location->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 == 1) {
                    delimits.array[delimits.used] = location->start;
                    delimits.used++;
                  }

                  slash_count--;
                }

                // Delimit slashes and placeholders are required to be in the ASCII range.
                position_previous = location->start;
                location->start++;
              } // while

              // when slashes are even, the object is valid and needs to be processed.
              if (is_object) {
                depth++;

                if (depth > positions_start.size) {
                  f_macro_string_lengths_resize(status, positions_start, positions_start.size + f_fss_default_allocation_step);

                  if (F_status_is_error(status)) {
                    location->start = last_newline;

                    f_macro_string_lengths_delete_simple(delimits);
                    f_macro_string_lengths_delete_simple(positions_start);
                    f_macro_fss_objects_delete_simple(objects);

                    return status;
                  }
                }

                if (positions_start.used < depth) {
                  positions_start.used = depth;
                }

                positions_start.array[depth] = last_newline + 1;

                objects.array[depth].start = line_start;
                objects.array[depth].stop = before_list_open;
              }
            }
            else {
              if (delimits.used + 1 >= delimits.size) {
                f_macro_string_lengths_resize(status, delimits, delimits.size + f_fss_default_allocation_step);

                if (F_status_is_error(status)) {
                  location->start = last_newline;

                  f_macro_string_lengths_delete_simple(delimits);
                  f_macro_string_lengths_delete_simple(positions_start);
                  f_macro_fss_objects_delete_simple(objects);

                  return status;
                }
              }

              delimits.array[delimits.used] = slash_last;
              delimits.used++;
            }

            location->start = last_newline;
          }
        }
      }
      else if (buffer->string[location->start] == f_fss_extended_list_open) {
        f_string_length before_list_open = position_previous;

        position_previous = location->start;
        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          f_macro_string_lengths_delete_simple(positions_start);
          f_macro_fss_objects_delete_simple(objects);

          return status;
        }

        while (location->start < buffer->used && location->start <= location->stop) {

          if (buffer->string[location->start] == f_string_eol) {
            break;
          }

          if (buffer->string[location->start] != f_fss_delimit_placeholder && (status = fl_fss_is_space(*buffer, *location)) == F_false) {
            break;
          }

          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            f_macro_string_lengths_delete_simple(positions_start);
            f_macro_fss_objects_delete_simple(objects);

            return status;
          }

          position_previous = location->start;
          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            f_macro_string_lengths_delete_simple(positions_start);
            f_macro_fss_objects_delete_simple(objects);

            return status;
          }
        } // while

        if (depth > 0) {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
        }
        else {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_data_no_eos, F_data_no_stop)
        }

        if (buffer->string[location->start] == f_string_eol) {
          depth++;

          if (depth >= positions_start.size) {
            f_macro_string_lengths_resize(status, positions_start, positions_start.size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }

            f_macro_fss_objects_resize(status, objects, objects.size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }
          }

          if (positions_start.used <= depth) {
            positions_start.used = depth + 1;
          }

          positions_start.array[depth] = location->start + 1;

          objects.array[depth].start = line_start;
          objects.array[depth].stop = before_list_open;

          last_newline = location->start;
          line_start = location->start + 1;
        }
        // No valid object open found, seek until EOL.
        else {
          while (location->start < buffer->used && location->start <= location->stop) {
            if (buffer->string[location->start] == f_string_eol) {
              last_newline = location->start;
              line_start = location->start + 1;
              break;
            }

            position_previous = location->start;
            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }
          } // while

          if (depth > 0) {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
          }
          else {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_data_no_eos, F_data_no_stop)
          }
        }
      }
      else if (buffer->string[location->start] == f_fss_extended_list_close) {
        while (location->start < buffer->used && location->start <= location->stop) {
          position_previous = location->start;
          status = fl_fss_increment_buffer(*buffer, location, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            f_macro_string_lengths_delete_simple(positions_start);
            f_macro_fss_objects_delete_simple(objects);

            return status;
          }

          if (buffer->string[location->start] == f_string_eol) {
            break;
          }

          if (buffer->string[location->start] != f_fss_delimit_placeholder && (status = fl_fss_is_space(*buffer, *location)) == F_false) {
            break;
          }

          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            f_macro_string_lengths_delete_simple(positions_start);
            f_macro_fss_objects_delete_simple(objects);

            return status;
          }
        } // while

        if (depth > 0) {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
        }
        else {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_data_no_eos, F_data_no_stop)
        }

        if (buffer->string[location->start] == f_string_eol) {
          if (depth + 1 >= found->size) {
            f_macro_fss_nest_resize(status, (*found), found->size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }
          }

          if (found->depth[depth].used >= found->depth[depth].size) {
            f_macro_fss_items_resize(status, found->depth[depth], found->depth[depth].size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }
          }

          f_array_length position = found->depth[depth].used;

          if (found->depth[depth].array[position].content.size != 1) {
            f_macro_fss_content_resize(status, found->depth[depth].array[position].content, 1);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }
          }

          // only assign object positions for nested objects.
          if (depth > 0) {
            found->depth[depth].array[position].object.start = objects.array[depth].start;
            found->depth[depth].array[position].object.stop = objects.array[depth].stop;
          }

          found->depth[depth].array[position].content.array[0].start = positions_start.array[depth];
          found->depth[depth].array[position].content.array[0].stop = last_newline;
          found->depth[depth].array[position].content.used = 1;

          if (position >= found->depth[depth].used) {
            found->depth[depth].used++;
          }

          if (found->used < depth + 1) {
            found->used = depth + 1;
          }

          last_newline = location->start;
          line_start = location->start + 1;

          if (depth == 0) {
            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }

            fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);
            fl_macro_fss_nest_delimited_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_none_eos, F_none_stop)

            f_macro_string_lengths_delete_simple(delimits);
            f_macro_string_lengths_delete_simple(positions_start);
            f_macro_fss_objects_delete_simple(objects);

            return FL_fss_found_content;
          }

          depth--;
        }
        // No valid object close found, seek until EOL.
        else {
          while (location->start < buffer->used && location->start <= location->stop) {
            if (buffer->string[location->start] == f_string_eol) {
              last_newline = location->start;
              line_start = location->start + 1;
              break;
            }

            position_previous = location->start;
            status = fl_fss_increment_buffer(*buffer, location, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              f_macro_string_lengths_delete_simple(positions_start);
              f_macro_fss_objects_delete_simple(objects);

              return status;
            }
          } // while

          if (depth > 0) {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
          }
          else {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*location), (*found), delimits, positions_start, objects, F_data_no_eos, F_data_no_stop)
          }
        }
      }
      else if (buffer->string[location->start] != f_string_eol) {
        position_previous = location->start;
        status = fl_fss_increment_buffer(*buffer, location, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          f_macro_string_lengths_delete_simple(positions_start);
          f_macro_fss_objects_delete_simple(objects);

          return status;
        }

        if (location->start >= buffer->used || location->start > location->stop) {
          break;
        }

        continue;
      }

      position_previous = location->start;
      status = fl_fss_increment_buffer(*buffer, location, 1);
      if (F_status_is_error(status)) {
        f_macro_string_lengths_delete_simple(delimits);
        f_macro_string_lengths_delete_simple(positions_start);
        f_macro_fss_objects_delete_simple(objects);

        return status;
      }
    } // while

    f_macro_string_lengths_delete_simple(delimits);
    f_macro_string_lengths_delete_simple(positions_start);
    f_macro_fss_objects_delete_simple(objects);

    if (location->start > location->stop) {
      if (depth == 0) {
        return F_status_set_error(F_unterminated_stop);
      }

      return F_status_set_error(F_unterminated_nest_stop);
    }

    if (depth == 0) {
      return F_status_set_error(F_unterminated_eos);
    }

    return F_status_set_error(F_unterminated_nest_eos);
  }
#endif // _di_fl_fss_extended_list_content_read_

#ifndef _di_fl_fss_extended_list_object_write_
  f_return_status fl_fss_extended_list_object_write(const f_string_static object, f_string_range *location, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;

    f_string_range buffer_position = f_string_range_initialize;
    f_string_length start_position = f_string_initialize;
    f_string_length pre_allocate_size = 0;
    f_string_length start_buffer = 0;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*location))

    if (location->start > location->stop) {
      return F_data_no_stop;
    }
    else if (location->start >= object.used) {
      return F_data_no_eos;
    }

    start_position = location->start;

    // add an additional 2 to ensure that there is room for the slash delimit and the object open character.
    pre_allocate_size = buffer->used + (location->stop - location->start) + 2 + f_fss_default_allocation_step_string;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);

      if (F_status_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop = buffer->used;

    while (location->start <= location->stop && location->start < object.used) {
      if (object.string[location->start] == f_fss_comment) {
        // comments are not allowed and this format has no way of "wrapping" a comment.
        return F_status_set_error(FL_fss_found_comment);
      }
      else if ((status = fl_fss_is_graph(object, *location)) == F_true) {
        break;
      }
      else if (F_status_is_error(status)) {
        f_status status2 = F_status_set_fine(status);

        if (status2 == F_failure) {
          return F_status_set_error(F_utf);
        }

        if (status2 == F_failure) {
          return F_status_set_error(F_incomplete_utf);
        }

        return status;
      }

      if (object.string[location->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = object.string[location->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(object, location, 1);
      if (F_status_is_error(status)) return status;
    } // while

    while (location->start <= location->stop && location->start < object.used) {
      if (object.string[location->start] == f_fss_delimit_slash) {
        f_string_length slash_count = 1;

        buffer->string[buffer_position.stop] = object.string[location->start];
        buffer_position.stop++;

        status = fl_fss_increment_buffer(object, location, 1);
        if (F_status_is_error(status)) return status;

        while (location->start <= location->stop && location->start < object.used) {
          if (object.string[location->start] == f_fss_delimit_placeholder) {
            status = fl_fss_increment_buffer(object, location, 1);
            if (F_status_is_error(status)) return status;

            continue;
          } else if (object.string[location->start] != f_fss_delimit_slash) {
            break;
          }

          buffer->string[buffer_position.stop] = object.string[location->start];
          buffer_position.stop++;

          status = fl_fss_increment_buffer(object, location, 1);
          if (F_status_is_error(status)) return status;

          slash_count++;
        } // while

        if (location->start > location->stop || location->start >= object.used) {
          pre_allocate_size += slash_count;

          if (pre_allocate_size > buffer->size) {
            f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

            if (F_status_is_error(status)) return status;
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
          return F_data_no_eol;
        }

        break;
      }

      if (object.string[location->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = object.string[location->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(object, location, 1);
      if (F_status_is_error(status)) return status;
    } // while

    buffer->string[buffer_position.stop] = f_fss_extended_list_open;
    buffer->string[buffer_position.stop + 1] = f_string_eol;
    buffer->used = buffer_position.stop + 2;

    if (location->start > location->stop) {
      return F_none_stop;
    }
    else if (location->start >= object.used) {
      return F_none_eos;
    }

    return F_none;
  }
#endif // _di_fl_fss_extended_list_object_write_

#ifndef _di_fl_fss_extended_list_content_write_
  f_return_status fl_fss_extended_list_content_write(const f_string_static content, f_string_range *location, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    // @todo
    /*
    f_status status = F_none;
    bool is_comment = F_false;
    bool has_graph = F_false;

    f_string_range buffer_position = f_string_range_initialize;
    f_string_length start_position = f_string_initialize;
    f_string_length pre_allocate_size = 0;

    fl_macro_fss_skip_past_delimit_placeholders(content, (*location))

    if (location->start > location->stop) {
      return F_data_no_stop;
    }
    else if (location->start >= content.used) {
      return F_data_no_eos;
    }

    start_position = location->start;

    // add an additional 2 to ensure that there is room for the slash delimit and the content open character.
    pre_allocate_size = buffer->used + (location->stop - location->start) + 2 + f_fss_default_allocation_step_string;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);

      if (F_status_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop = buffer->used;

    while (location->start <= location->stop && location->start < content.used) {
      if (content.string[location->start] == f_fss_delimit_slash && !is_comment) {
        f_string_length slash_count = 1;

        buffer->string[buffer_position.stop] = content.string[location->start];
        buffer_position.stop++;

        has_graph = F_true;
        status = fl_fss_increment_buffer(content, location, 1);
        if (F_status_is_error(status)) return status;

        while (location->start <= location->stop && location->start < content.used) {
          if (content.string[location->start] == f_fss_delimit_placeholder) {
            status = fl_fss_increment_buffer(content, location, 1);
            if (F_status_is_error(status)) return status;

            continue;
          }
          else if (content.string[location->start] != f_fss_delimit_slash) {
            break;
          }

          buffer->string[buffer_position.stop] = content.string[location->start];
          buffer_position.stop++;

          status = fl_fss_increment_buffer(content, location, 1);
          if (F_status_is_error(status)) return status;

          slash_count++;
        } // while

        if (content.string[location->start] == f_fss_extended_list_open) {
          f_string_length start = location->start;

          status = fl_fss_increment_buffer(content, location, 1);
          if (F_status_is_error(status)) return status;

          while (location->start < content.used && location->start <= location->stop) {
            if (content.string[location->start] == f_string_eol || (status = fl_fss_is_graph(content, *location)) == F_true) {
              break;
            }

            if (F_status_is_error(status)) return status;

            status = fl_fss_increment_buffer(content, location, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (content.string[location->start] == f_string_eol || location->start >= content.used || location->start > location->stop) {
            pre_allocate_size += slash_count + 1;

            if (pre_allocate_size > buffer->size) {
              f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

              if (F_status_is_error(status)) return status;
            }

            while (slash_count > 0) {
              buffer->string[buffer_position.stop] = f_fss_delimit_slash;
              buffer_position.stop++;
              slash_count--;
            } // while

            buffer->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
            has_graph = F_false;
            is_comment = F_false;
          }

          buffer->string[buffer_position.stop] = f_fss_extended_list_open;
          buffer_position.stop++;
          location->start = start + 1;
          continue;
        }
      }
      else if (content.string[location->start] == f_fss_extended_list_open && !is_comment) {
        f_string_length start = location->start;

        has_graph = F_true;

        status = fl_fss_increment_buffer(content, location, 1);
        if (F_status_is_error(status)) return status;

        while (location->start < content.used && location->start <= location->stop) {
          if (content.string[location->start] == f_string_eol || (status = fl_fss_is_graph(content, *location)) == F_true) {
            break;
          }

          if (F_status_is_error(status)) return status;

          status = fl_fss_increment_buffer(content, location, 1);
          if (F_status_is_error(status)) return status;
        } // while

        if (content.string[location->start] == f_string_eol || location->start >= content.used || location->start > location->stop) {
          pre_allocate_size++;

          if (pre_allocate_size > buffer->size) {
            f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

            if (F_status_is_error(status)) return status;
          }

          buffer->string[buffer_position.stop] = f_fss_delimit_slash;
          buffer_position.stop++;
          has_graph = F_false;
          is_comment = F_false;
        }

        buffer->string[buffer_position.stop] = f_fss_extended_list_open;
        buffer_position.stop++;
        location->start = start + 1;
        continue;
      }
      else if (content.string[location->start] == f_fss_comment && !has_graph) {
        is_comment = F_true;
      }
      else if (content.string[location->start] == f_string_eol) {
        has_graph = F_false;
        is_comment = F_false;
      }
      else if ((status = fl_fss_is_graph(content, *location)) == F_true) {
        has_graph = F_true;
      }
      else if (F_status_is_error(status)) {
        f_status status2 = F_status_set_fine(status);

        if (status2 == F_failure) {
          return F_status_set_error(F_utf);
        }

        if (status2 == F_failure) {
          return F_status_set_error(F_incomplete_utf);
        }

        return status;
      }

      if (content.string[location->start] != f_fss_delimit_placeholder) {
        buffer->string[buffer_position.stop] = content.string[location->start];
        buffer_position.stop++;
      }

      status = fl_fss_increment_buffer(content, location, 1);
      if (F_status_is_error(status)) return status;
    } // while

    buffer->string[buffer_position.stop] = f_string_eol;
    buffer->used = buffer_position.stop + 1;

    if (location->start > location->stop) {
      return F_none_stop;
    }
    else if (location->start >= content.used) {
      return F_none_eos;
    }
    */

    return F_none;
  }
#endif // _di_fl_fss_extended_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
