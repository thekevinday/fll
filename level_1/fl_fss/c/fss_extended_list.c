#include "fss_extended_list.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_list_object_read_
  f_return_status fl_fss_extended_list_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!buffer->used) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths_t delimits = f_string_lengths_t_initialize;

    status = f_fss_skip_past_space(*buffer, range);
    if (F_status_is_error(status)) return status;

    // return found nothing if this line only contains whitespace and delimit placeholders.
    if (status == F_none_eol) {
      range->start++;
      return FL_fss_found_object_not;
    }
    else if (status == F_none_eos) {
      return F_data_not_eos;
    }
    else if (status == F_none_stop) {
      return F_data_not_stop;
    }

    // return found nothing if this line only contains whitespace and delimit placeholders.
    if (buffer->string[range->start] == f_string_eol[0]) {
      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      return FL_fss_found_object_not;
    }

    // begin the search.
    found->start = range->start;

    // ignore all comment lines.
    if (buffer->string[range->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*range), delimits, F_data_not_eos, F_data_not_stop)

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      return FL_fss_found_object_not;
    }

    // identify where the object ends.
    while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {

      if (buffer->string[range->start] == f_fss_delimit_slash) {
        f_string_length_t first_slash = range->start;
        f_string_length_t slash_count = 1;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;

        while (range->start < buffer->used && range->start <= range->stop && (buffer->string[range->start] == f_fss_delimit_placeholder || buffer->string[range->start] == f_fss_delimit_slash)) {
          if (buffer->string[range->start] == f_fss_delimit_slash) {
            slash_count++;
          }

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

        if (buffer->string[range->start] == f_fss_extended_list_open) {
          f_string_length_t stop_point = range->start - 1;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start < buffer->used && range->start <= range->stop) {

            if (buffer->string[range->start] == f_string_eol[0] || (status = f_fss_is_graph(*buffer, *range)) == F_true) {
              break;
            }

            if (F_status_is_error(status)) return status;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

          if (buffer->string[range->start] == f_string_eol[0]) {
            f_string_length_t start = range->start;

            range->start = first_slash;

            if (delimits.used + (slash_count / 2) >= delimits.size) {
              f_macro_string_lengths_t_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

              if (F_status_is_error(status)) {
                f_macro_string_lengths_t_delete_simple(delimits);
                return status;
              }
            }

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {

                if (buffer->string[range->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 == 1) {
                    delimits.array[delimits.used] = range->start;
                    delimits.used++;
                  }

                  slash_count--;
                }

                status = f_utf_buffer_increment(*buffer, range, 1);
                if (F_status_is_error(status)) return status;
              } // while

              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              found->stop = stop_point;
              range->start = start + 1;

              return FL_fss_found_object;
            }

            range->start = start + 1;
            return FL_fss_found_object_not;
          }
        }

        continue;
      }
      else if (buffer->string[range->start] == f_fss_extended_list_open) {
        f_string_length_t stop_point = range->start - 1;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;

        while (range->start < buffer->used && range->start <= range->stop) {
          if (buffer->string[range->start] == f_string_eol[0]) break;

          status = f_fss_is_space(*buffer, *range);

          if (F_status_is_error(status)) return status;
          if (status == F_false) break;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

        if (buffer->string[range->start] == f_string_eol[0]) {
          fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

          found->stop = stop_point;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          return FL_fss_found_object;
        }

        continue;
      }

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    // seek to the end of the line when no valid object is found.
    while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

    status = f_utf_buffer_increment(*buffer, range, 1);
    if (F_status_is_error(status)) return status;

    return FL_fss_found_object_not;
  }
#endif // _di_fl_fss_extended_list_object_read_

#ifndef _di_fl_fss_extended_list_content_read_
  f_return_status fl_fss_extended_list_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_nest_t *found) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!buffer->used) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths_t delimits = f_string_lengths_t_initialize;
    f_string_lengths_t positions_start = f_string_lengths_t_initialize;
    f_fss_objects_t objects = f_fss_objects_t_initialize;

    fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));
    fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), positions_start, delimits, objects, F_none_eos, F_none_stop)

    if (found->used + 1 >= found->size) {
      f_macro_fss_nest_t_resize(status, (*found), found->size + f_fss_default_allocation_step + 1);

      if (F_status_is_error(status)) {
        f_macro_string_lengths_t_delete_simple(delimits);
        return status;
      }
    }

    f_array_length_t depth = 0;
    f_string_length_t position_previous = range->start;
    f_string_length_t line_start = range->start;
    f_string_length_t last_newline = range->start;

    f_macro_string_lengths_t_new(status, positions_start, f_fss_default_allocation_step);

    if (F_status_is_error(status)) {
      f_macro_string_lengths_t_delete_simple(delimits);

      return status;
    }

    f_macro_fss_objects_t_new(status, objects, f_fss_default_allocation_step);

    if (F_status_is_error(status)) {
      f_macro_string_lengths_t_delete_simple(positions_start);
      f_macro_string_lengths_t_delete_simple(delimits);

      return status;
    }

    // initialize depth 1 start position.
    // positions_start.used is used as a max depth (such that positions_start.used == max depth + 1).
    positions_start.array[0] = range->start;
    positions_start.used = 1;

    while (range->start < buffer->used && range->start <= range->stop) {

      if (buffer->string[range->start] == f_string_eol[0]) {
        last_newline = range->start;
        position_previous = range->start;
        range->start++;

        if (depth > 0) {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
        }
        else {
          fl_macro_fss_nest_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_none_eos, F_none_stop)
        }

        line_start = range->start;
        continue;
      }

      if (buffer->string[range->start] == f_fss_delimit_slash) {
        f_string_length_t slash_first = range->start;
        f_string_length_t slash_last = range->start;
        f_string_length_t slash_count = 1;

        position_previous = range->start;
        status = f_utf_buffer_increment(*buffer, range, 1);

        if (F_status_is_error(status)) {
          f_macro_string_lengths_t_delete_simple(delimits);
          f_macro_string_lengths_t_delete_simple(positions_start);
          f_macro_fss_objects_t_delete_simple(objects);

          return status;
        }

        while (range->start < buffer->used && range->start <= range->stop && (buffer->string[range->start] == f_fss_delimit_placeholder || buffer->string[range->start] == f_fss_delimit_slash)) {
          position_previous = range->start;

          if (buffer->string[range->start] == f_fss_delimit_slash) {
            slash_last = range->start;
            slash_count++;
          }

          status = f_utf_buffer_increment(*buffer, range, 1);

          if (F_status_is_error(status)) {
            f_macro_string_lengths_t_delete_simple(delimits);
            f_macro_string_lengths_t_delete_simple(positions_start);
            f_macro_fss_objects_t_delete_simple(objects);

            return status;
          }
        } // while

        if (depth > 0) {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
        }
        else {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_data_not_eos, F_data_not_stop)
        }

        // All slashes for an open are delimited (because it could represent a slash in the object name).
        // for example 'object {' = valid open, name 'object', 'object \{' represents 'object {', 'object \\{' = valid open, name 'object \', 'object \\\{' represents 'object \{', etc..
        // Only the first slash before a close is delimited, all others are maintained.
        // for example '}' = valid close, '\}' represents '}', '\\}' represents '\}', '\\\}' represents '\\}', '\\\\}' represents '\\\}', and so on..
        // When slash is odd and a (delimited) valid open/close is found, then save delimited positions and continue.
        if (buffer->string[range->start] == f_string_eol[0]) {
          last_newline = range->start;
          position_previous = range->start;
          range->start++;
          line_start = range->start;
        }
        else if (buffer->string[range->start] == f_fss_extended_list_open || buffer->string[range->start] == f_fss_extended_list_close) {
          f_string_length_t before_list_open = position_previous;
          bool is_open = F_false;

          if (buffer->string[range->start] == f_fss_extended_list_open) {
            is_open = F_true;
          }

          position_previous = range->start;
          range->start++;

          while (range->start < buffer->used && range->start <= range->stop) {

            if (buffer->string[range->start] == f_string_eol[0]) {
              last_newline = range->start;
              line_start = range->start + 1;
              break;
            }

            if (buffer->string[range->start] != f_fss_delimit_placeholder && (status = f_fss_is_space(*buffer, *range)) == F_false) {
              break;
            }

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }

            position_previous = range->start;
            status = f_utf_buffer_increment(*buffer, range, 1);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }
          } // while

          if (depth > 0) {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
          }
          else {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_data_not_eos, F_data_not_stop)
          }

          // this is a valid object open/close that has been delimited, save the slash delimit positions.
          if (buffer->string[range->start] == f_string_eol[0]) {
            last_newline = range->start;
            line_start = range->start + 1;

            if (is_open) {
              bool is_object = F_false;

              if (slash_count % 2 == 0) {
                is_object = F_true;
              }

              range->start = slash_first;

              if (delimits.used + (slash_count / 2) >= delimits.size) {
                f_macro_string_lengths_t_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                if (F_status_is_error(status)) {
                  range->start = last_newline;

                  f_macro_string_lengths_t_delete_simple(delimits);
                  f_macro_string_lengths_t_delete_simple(positions_start);
                  f_macro_fss_objects_t_delete_simple(objects);

                  return status;
                }
              }

              // apply slash delimits, only slashes and placeholders should be present.
              while (slash_count > 0) {

                if (buffer->string[range->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 == 1) {
                    delimits.array[delimits.used] = range->start;
                    delimits.used++;
                  }

                  slash_count--;
                }

                // Delimit slashes and placeholders are required to be in the ASCII range.
                position_previous = range->start;
                range->start++;
              } // while

              // when slashes are even, the object is valid and needs to be processed.
              if (is_object) {
                depth++;

                if (depth > positions_start.size) {
                  f_macro_string_lengths_t_resize(status, positions_start, positions_start.size + f_fss_default_allocation_step);

                  if (F_status_is_error(status)) {
                    range->start = last_newline;

                    f_macro_string_lengths_t_delete_simple(delimits);
                    f_macro_string_lengths_t_delete_simple(positions_start);
                    f_macro_fss_objects_t_delete_simple(objects);

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
                f_macro_string_lengths_t_resize(status, delimits, delimits.size + f_fss_default_allocation_step);

                if (F_status_is_error(status)) {
                  range->start = last_newline;

                  f_macro_string_lengths_t_delete_simple(delimits);
                  f_macro_string_lengths_t_delete_simple(positions_start);
                  f_macro_fss_objects_t_delete_simple(objects);

                  return status;
                }
              }

              delimits.array[delimits.used] = slash_last;
              delimits.used++;
            }

            range->start = last_newline;
          }
        }
      }
      else if (buffer->string[range->start] == f_fss_extended_list_open) {
        f_string_length_t before_list_open = position_previous;

        position_previous = range->start;
        status = f_utf_buffer_increment(*buffer, range, 1);

        if (F_status_is_error(status)) {
          f_macro_string_lengths_t_delete_simple(delimits);
          f_macro_string_lengths_t_delete_simple(positions_start);
          f_macro_fss_objects_t_delete_simple(objects);

          return status;
        }

        while (range->start < buffer->used && range->start <= range->stop) {

          if (buffer->string[range->start] == f_string_eol[0]) {
            break;
          }

          if (buffer->string[range->start] != f_fss_delimit_placeholder && (status = f_fss_is_space(*buffer, *range)) == F_false) {
            break;
          }

          if (F_status_is_error(status)) {
            f_macro_string_lengths_t_delete_simple(delimits);
            f_macro_string_lengths_t_delete_simple(positions_start);
            f_macro_fss_objects_t_delete_simple(objects);

            return status;
          }

          position_previous = range->start;
          status = f_utf_buffer_increment(*buffer, range, 1);

          if (F_status_is_error(status)) {
            f_macro_string_lengths_t_delete_simple(delimits);
            f_macro_string_lengths_t_delete_simple(positions_start);
            f_macro_fss_objects_t_delete_simple(objects);

            return status;
          }
        } // while

        if (depth > 0) {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
        }
        else {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_data_not_eos, F_data_not_stop)
        }

        if (buffer->string[range->start] == f_string_eol[0]) {
          depth++;

          if (depth >= positions_start.size) {
            f_macro_string_lengths_t_resize(status, positions_start, positions_start.size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }

            f_macro_fss_objects_t_resize(status, objects, objects.size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }
          }

          if (positions_start.used <= depth) {
            positions_start.used = depth + 1;
          }

          positions_start.array[depth] = range->start + 1;

          objects.array[depth].start = line_start;
          objects.array[depth].stop = before_list_open;

          last_newline = range->start;
          line_start = range->start + 1;
        }
        // No valid object open found, seek until EOL.
        else {
          while (range->start < buffer->used && range->start <= range->stop) {

            if (buffer->string[range->start] == f_string_eol[0]) {
              last_newline = range->start;
              line_start = range->start + 1;
              break;
            }

            position_previous = range->start;
            status = f_utf_buffer_increment(*buffer, range, 1);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }
          } // while

          if (depth > 0) {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
          }
          else {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_data_not_eos, F_data_not_stop)
          }
        }
      }
      else if (buffer->string[range->start] == f_fss_extended_list_close) {
        while (range->start < buffer->used && range->start <= range->stop) {

          position_previous = range->start;
          status = f_utf_buffer_increment(*buffer, range, 1);

          if (F_status_is_error(status)) {
            f_macro_string_lengths_t_delete_simple(delimits);
            f_macro_string_lengths_t_delete_simple(positions_start);
            f_macro_fss_objects_t_delete_simple(objects);

            return status;
          }

          if (buffer->string[range->start] == f_string_eol[0]) {
            break;
          }

          if (buffer->string[range->start] != f_fss_delimit_placeholder && (status = f_fss_is_space(*buffer, *range)) == F_false) {
            break;
          }

          if (F_status_is_error(status)) {
            f_macro_string_lengths_t_delete_simple(delimits);
            f_macro_string_lengths_t_delete_simple(positions_start);
            f_macro_fss_objects_t_delete_simple(objects);

            return status;
          }
        } // while

        if (depth > 0) {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
        }
        else {
          fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_data_not_eos, F_data_not_stop)
        }

        if (buffer->string[range->start] == f_string_eol[0]) {
          if (depth + 1 >= found->size) {
            f_macro_fss_nest_t_resize(status, (*found), found->size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }
          }

          if (found->depth[depth].used == found->depth[depth].size) {
            f_macro_fss_items_t_resize(status, found->depth[depth], found->depth[depth].size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }
          }

          f_array_length_t position = found->depth[depth].used;

          if (found->depth[depth].array[position].content.size != 1) {
            f_macro_fss_content_t_resize(status, found->depth[depth].array[position].content, 1);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

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

          last_newline = range->start;
          line_start = range->start + 1;

          if (!depth) {
            status = f_utf_buffer_increment(*buffer, range, 1);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }

            fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);
            fl_macro_fss_nest_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_none_eos, F_none_stop)

            f_macro_string_lengths_t_delete_simple(delimits);
            f_macro_string_lengths_t_delete_simple(positions_start);
            f_macro_fss_objects_t_delete_simple(objects);

            return FL_fss_found_content;
          }

          depth--;
        }
        // No valid object close found, seek until EOL.
        else {
          while (range->start < buffer->used && range->start <= range->stop) {

            if (buffer->string[range->start] == f_string_eol[0]) {
              last_newline = range->start;
              line_start = range->start + 1;
              break;
            }

            position_previous = range->start;
            status = f_utf_buffer_increment(*buffer, range, 1);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_t_delete_simple(delimits);
              f_macro_string_lengths_t_delete_simple(positions_start);
              f_macro_fss_objects_t_delete_simple(objects);

              return status;
            }
          } // while

          if (depth > 0) {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_unterminated_nest_eos, F_unterminated_nest_stop)
          }
          else {
            fl_macro_fss_nest_return_on_overflow((*buffer), (*range), (*found), delimits, positions_start, objects, F_data_not_eos, F_data_not_stop)
          }
        }
      }
      else if (buffer->string[range->start] != f_string_eol[0]) {
        position_previous = range->start;
        status = f_utf_buffer_increment(*buffer, range, 1);

        if (F_status_is_error(status)) {
          f_macro_string_lengths_t_delete_simple(delimits);
          f_macro_string_lengths_t_delete_simple(positions_start);
          f_macro_fss_objects_t_delete_simple(objects);

          return status;
        }

        if (range->start >= buffer->used || range->start > range->stop) {
          break;
        }

        continue;
      }

      position_previous = range->start;
      status = f_utf_buffer_increment(*buffer, range, 1);

      if (F_status_is_error(status)) {
        f_macro_string_lengths_t_delete_simple(delimits);
        f_macro_string_lengths_t_delete_simple(positions_start);
        f_macro_fss_objects_t_delete_simple(objects);

        return status;
      }
    } // while

    f_macro_string_lengths_t_delete_simple(delimits);
    f_macro_string_lengths_t_delete_simple(positions_start);
    f_macro_fss_objects_t_delete_simple(objects);

    if (range->start > range->stop) {
      if (!depth) {
        return F_status_set_error(F_unterminated_stop);
      }

      return F_status_set_error(F_unterminated_nest_stop);
    }

    if (!depth) {
      return F_status_set_error(F_unterminated_eos);
    }

    return F_status_set_error(F_unterminated_nest_eos);
  }
#endif // _di_fl_fss_extended_list_content_read_

#ifndef _di_fl_fss_extended_list_object_write_
  f_return_status fl_fss_extended_list_object_write(const f_string_static_t object, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_string_range_t buffer_position = f_string_range_t_initialize;
    f_string_length_t start_position = f_string_t_initialize;
    f_string_length_t size_allocate = 0;
    f_string_length_t start_buffer = 0;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*range))

    if (range->start > range->stop) return F_data_not_stop;
    else if (range->start >= object.used) return F_data_not_eos;

    start_position = range->start;

    // add an additional 2 to ensure that there is room for the slash delimit and the object open character.
    size_allocate = destination->used + (range->stop - range->start) + 2 + f_fss_default_allocation_step_string;

    if (size_allocate > destination->size) {
      f_macro_string_dynamic_t_resize(status, (*destination), size_allocate);

      if (F_status_is_error(status)) return status;
    }

    buffer_position.start = destination->used;
    buffer_position.stop = destination->used;

    while (range->start <= range->stop && range->start < object.used) {

      if (object.string[range->start] == f_fss_comment) {
        // comments are not allowed and this format has no way of "wrapping" a comment.
        return F_status_set_error(FL_fss_found_comment);
      }
      else if ((status = f_fss_is_graph(object, *range)) == F_true) {
        break;
      }
      else if (F_status_is_error(status)) {
        return status;
      }

      if (object.string[range->start] != f_fss_delimit_placeholder) {
        destination->string[buffer_position.stop] = object.string[range->start];
        buffer_position.stop++;
      }

      status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    while (range->start <= range->stop && range->start < object.used) {

      if (object.string[range->start] == f_fss_delimit_slash) {
        f_string_length_t slash_count = 1;

        destination->string[buffer_position.stop] = object.string[range->start];
        buffer_position.stop++;

        status = f_utf_buffer_increment(object, range, 1);
        if (F_status_is_error(status)) return status;

        while (range->start <= range->stop && range->start < object.used) {

          if (object.string[range->start] == f_fss_delimit_placeholder) {
            status = f_utf_buffer_increment(object, range, 1);
            if (F_status_is_error(status)) return status;

            continue;
          } else if (object.string[range->start] != f_fss_delimit_slash) {
            break;
          }

          destination->string[buffer_position.stop] = object.string[range->start];
          buffer_position.stop++;

          status = f_utf_buffer_increment(object, range, 1);
          if (F_status_is_error(status)) return status;

          slash_count++;
        } // while

        if (range->start > range->stop || range->start >= object.used) {
          size_allocate += slash_count;

          if (size_allocate > destination->size) {
            f_macro_string_dynamic_t_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);
            if (F_status_is_error(status)) return status;
          }

          while (slash_count > 0) {
            destination->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
            slash_count--;
          } // while

          break;
        }
      }
      else if (object.string[range->start] == f_string_eol[0]) {
        if (buffer_position.stop == buffer_position.start) return F_data_not_eol;

        break;
      }

      if (object.string[range->start] != f_fss_delimit_placeholder) {
        destination->string[buffer_position.stop] = object.string[range->start];
        buffer_position.stop++;
      }

      status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    destination->string[buffer_position.stop] = f_fss_extended_list_open;
    destination->string[buffer_position.stop + 1] = f_string_eol[0];
    destination->used = buffer_position.stop + 2;

    if (range->start > range->stop) return F_none_stop;
    else if (range->start >= object.used) return F_none_eos;

    return F_none;
  }
#endif // _di_fl_fss_extended_list_object_write_

#ifndef _di_fl_fss_extended_list_content_write_
  f_return_status fl_fss_extended_list_content_write(const f_string_static_t content, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    // @todo
    /*
    f_status_t status = F_none;
    bool is_comment = F_false;
    bool has_graph = F_false;

    f_string_range_t buffer_position = f_string_range_t_initialize;
    f_string_length_t start_position = f_string_t_initialize;
    f_string_length_t size_allocate = 0;

    fl_macro_fss_skip_past_delimit_placeholders(content, (*range))

    if (range->start > range->stop) return F_data_not_stop;
    else if (range->start >= content.used) return F_data_not_eos;

    start_position = range->start;

    // add an additional 2 to ensure that there is room for the slash delimit and the content open character.
    size_allocate = destination->used + (range->stop - range->start) + 2 + f_fss_default_allocation_step_string;

    if (size_allocate > destination->size) {
      f_macro_string_dynamic_t_resize(status, (*destination), size_allocate);
      if (F_status_is_error(status)) return status;
    }

    buffer_position.start = destination->used;
    buffer_position.stop = destination->used;

    while (range->start <= range->stop && range->start < content.used) {

      if (content.string[range->start] == f_fss_delimit_slash && !is_comment) {
        f_string_length_t slash_count = 1;

        destination->string[buffer_position.stop] = content.string[range->start];
        buffer_position.stop++;

        has_graph = F_true;
        status = f_utf_buffer_increment(content, range, 1);
        if (F_status_is_error(status)) return status;

        while (range->start <= range->stop && range->start < content.used) {

          if (content.string[range->start] == f_fss_delimit_placeholder) {
            status = f_utf_buffer_increment(content, range, 1);
            if (F_status_is_error(status)) return status;

            continue;
          }
          else if (content.string[range->start] != f_fss_delimit_slash) {
            break;
          }

          destination->string[buffer_position.stop] = content.string[range->start];
          buffer_position.stop++;

          status = f_utf_buffer_increment(content, range, 1);
          if (F_status_is_error(status)) return status;

          slash_count++;
        } // while

        if (content.string[range->start] == f_fss_extended_list_open) {
          f_string_length_t start = range->start;

          status = f_utf_buffer_increment(content, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start < content.used && range->start <= range->stop) {

            if (content.string[range->start] == f_string_eol[0] || (status = f_fss_is_graph(content, *range)) == F_true) {
              break;
            }

            if (F_status_is_error(status)) return status;

            status = f_utf_buffer_increment(content, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (content.string[range->start] == f_string_eol[0] || range->start >= content.used || range->start > range->stop) {
            size_allocate += slash_count + 1;

            if (size_allocate > destination->size) {
              f_macro_string_dynamic_t_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);
              if (F_status_is_error(status)) return status;
            }

            while (slash_count > 0) {
              destination->string[buffer_position.stop] = f_fss_delimit_slash;
              buffer_position.stop++;
              slash_count--;
            } // while

            destination->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
            has_graph = F_false;
            is_comment = F_false;
          }

          destination->string[buffer_position.stop] = f_fss_extended_list_open;
          buffer_position.stop++;
          range->start = start + 1;
          continue;
        }
      }
      else if (content.string[range->start] == f_fss_extended_list_open && !is_comment) {
        f_string_length_t start = range->start;

        has_graph = F_true;

        status = f_utf_buffer_increment(content, range, 1);
        if (F_status_is_error(status)) return status;

        while (range->start < content.used && range->start <= range->stop) {

          if (content.string[range->start] == f_string_eol[0] || (status = f_fss_is_graph(content, *range)) == F_true) {
            break;
          }

          if (F_status_is_error(status)) return status;

          status = f_utf_buffer_increment(content, range, 1);
          if (F_status_is_error(status)) return status;
        } // while

        if (content.string[range->start] == f_string_eol[0] || range->start >= content.used || range->start > range->stop) {
          size_allocate++;

          if (size_allocate > destination->size) {
            f_macro_string_dynamic_t_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);

            if (F_status_is_error(status)) return status;
          }

          destination->string[buffer_position.stop] = f_fss_delimit_slash;
          buffer_position.stop++;
          has_graph = F_false;
          is_comment = F_false;
        }

        destination->string[buffer_position.stop] = f_fss_extended_list_open;
        buffer_position.stop++;
        range->start = start + 1;
        continue;
      }
      else if (content.string[range->start] == f_fss_comment && !has_graph) {
        is_comment = F_true;
      }
      else if (content.string[range->start] == f_string_eol[0]) {
        has_graph = F_false;
        is_comment = F_false;
      }
      else if ((status = f_fss_is_graph(content, *range)) == F_true) {
        has_graph = F_true;
      }
      else if (F_status_is_error(status)) {
        return status;
      }

      if (content.string[range->start] != f_fss_delimit_placeholder) {
        destination->string[buffer_position.stop] = content.string[range->start];
        buffer_position.stop++;
      }

      status = f_utf_buffer_increment(content, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    destination->string[buffer_position.stop] = f_string_eol[0];
    destination->used = buffer_position.stop + 1;

    if (range->start > range->stop) return F_none_stop;
    else if (range->start >= content.used) return F_none_eos;
    */

    return F_none;
  }
#endif // _di_fl_fss_extended_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
