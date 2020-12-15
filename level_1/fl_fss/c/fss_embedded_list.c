#include "fss_embedded_list.h"
#include "private-fss.h"
#include "private-fss_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_embedded_list_object_read_
  f_return_status fl_fss_embedded_list_object_read(const f_string_static_t buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_delimits_t *delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    f_status_t status = f_fss_skip_past_space(buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eol) {

      // move the start position to after the EOL.
      range->start++;

      return FL_fss_found_object_not;
    }

    if (status == F_none_eos) {
      return F_data_not_eos;
    }

    if (status == F_none_stop) {
      return F_data_not_stop;
    }

    // return found nothing if this line only contains whitespace and delimit placeholders.
    if (buffer.string[range->start] == f_fss_eol) {

      // move the start position to after the EOL.
      range->start++;

      return FL_fss_found_object_not;
    }

    // begin the search.
    found->start = range->start;

    // ignore all comment lines.
    if (buffer.string[range->start] == f_fss_comment) {
      status = f_fss_seek_to_eol(buffer, range);

      if (F_status_is_error(status)) {
        delimits->used = delimits_used;
        return status;
      }

      if (status == F_none_eos) {
        return F_data_not_eos;
      }

      if (status == F_none_stop) {
        return F_data_not_stop;
      }

      // move the start position to after the EOL.
      range->start++;

      return FL_fss_found_object_not;
    }

    f_string_length_t start = 0;
    f_string_length_t stop = 0;
    f_string_length_t slash_first = 0;
    f_string_length_t slash_count = 0;

    bool graph_first = F_true;

    // identify where the object ends.
    while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol) {

      if (buffer.string[range->start] == f_fss_delimit_slash) {
        slash_first = range->start;
        slash_count = 1;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;

        while (range->start <= range->stop && range->start < buffer.used && (buffer.string[range->start] == f_fss_delimit_placeholder || buffer.string[range->start] == f_fss_delimit_slash)) {

          if (buffer.string[range->start] == f_fss_delimit_slash) slash_count++;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        private_fl_macro_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

        if (buffer.string[range->start] == f_fss_embedded_list_open) {
          graph_first = F_false;
          stop = range->start - 1;
          range->start++;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (buffer.string[range->start] == f_fss_eol) break;

            status = f_fss_is_graph(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_true) break;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          private_fl_macro_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

          if (buffer.string[range->start] == f_fss_eol) {
            start = range->start;

            range->start = slash_first;

            status = private_fl_fss_delimits_increase_by((slash_count / 2) + 1, delimits);
            if (F_status_is_error(status)) break;

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {

                if (buffer.string[range->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 == 1) {
                    delimits->array[delimits->used] = range->start;
                    delimits->used++;
                  }

                  slash_count--;
                }

                status = f_utf_buffer_increment(buffer, range, 1);
                if (F_status_is_error(status)) break;
              } // while

              if (F_status_is_error(status)) break;

              found->stop = stop;
              range->start = start + 1;

              return FL_fss_found_object;
            }

            range->start = start + 1;
            return FL_fss_found_object_not;
          }
        }
        else if (graph_first && buffer.string[range->start] == f_fss_comment) {
          graph_first = F_false;

          // comments may only have whitespace before the '#', therefore only the first slash needs to be delimited.
          status = private_fl_fss_delimits_increase(delimits);
          if (F_status_is_error(status)) break;

          delimits->array[delimits->used++] = slash_first;
          range->start++;
        }
        else {
          graph_first = F_false;
        }

        continue;
      }
      else if (buffer.string[range->start] == f_fss_embedded_list_open) {
        graph_first = F_false;
        stop = range->start - 1;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (buffer.string[range->start] == f_fss_eol) break;

          status = f_fss_is_space(buffer, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        private_fl_macro_fss_object_return_on_overflow_delimited((buffer), (*range), (*found), F_none_eos, F_none_stop);

        if (buffer.string[range->start] == f_fss_eol) {
          found->stop = stop;

          // move the start position to after the EOL.
          range->start++;

          return FL_fss_found_object;
        }

        continue;
      }
      else if (graph_first) {
        status = f_fss_is_space(buffer, *range);
        if (F_status_is_error(status)) break;

        if (status == F_false) {
          graph_first = F_false;
        }
      }

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) break;
    } // while

    if (F_status_is_error(status)) {
      delimits->used = delimits_used;
      return status;
    }

    // seek to the end of the line when no valid object is found.
    while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol) {

      status = f_utf_buffer_increment(buffer, range, 1);

      if (F_status_is_error(status)) {
        delimits->used = delimits_used;
        return status;
      }
    } // while

    private_fl_macro_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

    status = f_utf_buffer_increment(buffer, range, 1);

    if (F_status_is_error(status)) {
      delimits->used = delimits_used;
      return status;
    }

    return FL_fss_found_object_not;
  }
#endif // _di_fl_fss_embedded_list_object_read_

#ifndef _di_fl_fss_embedded_list_content_read_
  f_return_status fl_fss_embedded_list_content_read(const f_string_static_t buffer, f_string_range_t *range, f_fss_nest_t *found, f_fss_delimits_t *delimits, f_fss_comments_t *comments) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
      if (!comments) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t found_used = found->used;

    f_status_t status = f_fss_skip_past_delimit(buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eos || status == F_none_stop) {
      return status;
    }

    status = private_fl_fss_nest_increase(found);
    if (F_status_is_error(status)) return status;

    f_string_lengths_t positions_start = f_string_lengths_t_initialize;

    f_macro_string_lengths_t_new(status, positions_start, f_fss_default_allocation_step);
    if (F_status_is_error(status)) return status;

    f_fss_objects_t objects = f_fss_objects_t_initialize;

    f_macro_fss_objects_t_new(status, objects, f_fss_default_allocation_step);

    if (F_status_is_error(status)) {
      private_fl_fss_string_lengths_delete(&positions_start);

      return status;
    }

    const f_array_length_t delimits_used = delimits->used;
    const f_array_length_t comments_used = comments->used;

    f_array_length_t depth = 0;
    f_array_length_t position = 0;

    f_string_length_t position_previous = range->start;
    f_string_length_t line_start = range->start;
    f_string_length_t newline_last = range->start;
    f_string_length_t comment_delimit = 0;

    f_string_length_t slash_first = 0;
    f_string_length_t slash_last = 0;
    f_string_length_t slash_count = 0;

    f_string_length_t before_list_open = position_previous;

    bool is_open = F_false;

    uint8_t graph_first = 0x0; // 0x0 = false, 0x1 = true, 0x2 = false, but there is a delimited comment, comment_delimit is set.

    // initialize depth 1 start position.
    // positions_start.used is used as a max depth (such that positions_start.used == max depth + 1).
    positions_start.array[0] = range->start;
    positions_start.used = 1;

    while (range->start <= range->stop && range->start < buffer.used) {

      if (buffer.string[range->start] == f_fss_eol) {
        if (graph_first == 0x2) {
          status = private_fl_fss_delimits_increase(delimits);
          if (F_status_is_error(status)) break;

          delimits->array[delimits->used++] = comment_delimit;
        }

        newline_last = range->start;
        position_previous = range->start++;
        graph_first = 0x1;

        if (depth > 0) {
          private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
        }
        else {
          private_fl_macro_fss_nest_return_on_overflow_delimited((buffer), (*range), (*found), positions_start, objects, F_none_eos, F_none_stop);
        }

        line_start = range->start;
        continue;
      }

      if (buffer.string[range->start] == f_fss_delimit_slash) {
        slash_first = range->start;
        slash_last = range->start;
        slash_count = 1;

        position_previous = range->start;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;

        while (range->start <= range->stop && range->start < buffer.used && (buffer.string[range->start] == f_fss_delimit_placeholder || buffer.string[range->start] == f_fss_delimit_slash)) {
          position_previous = range->start;

          if (buffer.string[range->start] == f_fss_delimit_slash) {
            slash_last = range->start++;
          }

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        if (depth > 0) {
          private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
        }
        else {
          private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_data_not_eos, F_data_not_stop);
        }

        // All slashes for an open are delimited (because it could represent a slash in the object name).
        // for example 'object {' = valid open, name 'object', 'object \{' represents 'object {', 'object \\{' = valid open, name 'object \', 'object \\\{' represents 'object \{', etc..
        // Only the first slash before a close is delimited, all others are maintained.
        // for example '}' = valid close, '\}' represents '}', '\\}' represents '\}', '\\\}' represents '\\}', '\\\\}' represents '\\\}', and so on..
        // When slash is odd and a (delimited) valid open/close is found, then save delimited positions and continue.
        if (buffer.string[range->start] == f_fss_eol) {
          if (graph_first == 0x2) {
            status = private_fl_fss_delimits_increase(delimits);
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          position_previous = range->start++;
          line_start = range->start;
          graph_first = 0x1;
        }
        else if (buffer.string[range->start] == f_fss_embedded_list_open || buffer.string[range->start] == f_fss_embedded_list_close) {
          before_list_open = position_previous;
          is_open = F_false;
          graph_first = 0x0;

          if (buffer.string[range->start] == f_fss_embedded_list_open) {
            is_open = F_true;
          }

          position_previous = range->start++;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (buffer.string[range->start] == f_fss_eol) {
              if (graph_first == 0x2) {
                status = private_fl_fss_delimits_increase(delimits);
                if (F_status_is_error(status)) break;

                delimits->array[delimits->used++] = comment_delimit;
              }

              newline_last = range->start;
              line_start = range->start + 1;
              graph_first = 0x1;
              break;
            }

            if (buffer.string[range->start] != f_fss_delimit_placeholder) {
              status = f_fss_is_space(buffer, *range);
              if (F_status_is_error(status)) break;

              if (status == F_false) break;
            }

            position_previous = range->start;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (F_status_is_error(status)) break;

          if (depth > 0) {
            private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
          }
          else {
            private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_data_not_eos, F_data_not_stop);
          }

          // this is a valid object open/close that has been delimited, save the slash delimit positions.
          if (buffer.string[range->start] == f_fss_eol) {
            newline_last = range->start;
            line_start = range->start + 1;
            graph_first = 0x1;

            if (is_open) {
              bool is_object = F_false;

              if (slash_count % 2 == 0) {
                is_object = F_true;
              }

              range->start = slash_first;

              status = private_fl_fss_delimits_increase_by((slash_count / 2) + 1, delimits);
              if (F_status_is_error(status)) break;

              // apply slash delimits, only slashes and placeholders should be present.
              while (slash_count > 0) {

                if (buffer.string[range->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 == 1) {
                    delimits->array[delimits->used++] = range->start;
                  }

                  slash_count--;
                }

                // Delimit slashes and placeholders are required to be in the ASCII range.
                position_previous = range->start++;
              } // while

              if (F_status_is_error(status)) break;

              // when slashes are even, the object is valid and needs to be processed.
              if (is_object) {
                depth++;

                if (depth > positions_start.size) {
                  f_macro_string_lengths_t_resize(status, positions_start, positions_start.size + f_fss_default_allocation_step);
                  if (F_status_is_error(status)) break;
                }

                if (positions_start.used < depth) {
                  positions_start.used = depth;
                }

                positions_start.array[depth] = newline_last + 1;

                objects.array[depth].start = line_start;
                objects.array[depth].stop = before_list_open;
              }
            }
            else {
              status = private_fl_fss_delimits_increase(delimits);
              if (F_status_is_error(status)) break;

              delimits->array[delimits->used++] = slash_last;
            }

            range->start = newline_last;
          }
        }
        else if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment) {
          graph_first = 0x2;
          comment_delimit = slash_first;
        }
        else {
          graph_first = 0x0;
        }
      }
      else if (buffer.string[range->start] == f_fss_embedded_list_open) {
        graph_first = 0x0;
        before_list_open = position_previous;
        position_previous = range->start;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (buffer.string[range->start] == f_fss_eol) break;

          if (buffer.string[range->start] != f_fss_delimit_placeholder) {
            status = f_fss_is_space(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;
          }

          position_previous = range->start;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        if (depth > 0) {
          private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
        }
        else {
          private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_data_not_eos, F_data_not_stop);
        }

        if (buffer.string[range->start] == f_fss_eol) {
          depth++;

          if (depth >= positions_start.size) {
            f_macro_string_lengths_t_resize(status, positions_start, positions_start.size + f_fss_default_allocation_step);
            if (F_status_is_error(status)) break;

            f_macro_fss_objects_t_resize(status, objects, objects.size + f_fss_default_allocation_step);
            if (F_status_is_error(status)) break;
          }

          if (positions_start.used <= depth) {
            positions_start.used = depth + 1;
          }

          positions_start.array[depth] = range->start + 1;

          objects.array[depth].start = line_start;
          objects.array[depth].stop = before_list_open;

          if (graph_first == 0x2) {
            status = private_fl_fss_delimits_increase(delimits);
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          line_start = range->start + 1;
          graph_first = 0x1;
        }
        else {

          // No valid object close found, seek until EOL.
          status = f_fss_seek_to_eol(buffer, range);
          if (F_status_is_error(status)) break;

          if (graph_first == 0x2) {
            status = private_fl_fss_delimits_increase(delimits);
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          line_start = range->start + 1;
          graph_first = 0x1;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (buffer.string[range->start] == f_fss_eol) {
              newline_last = range->start;
              line_start = range->start + 1;
              break;
            }

            position_previous = range->start;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (F_status_is_error(status)) break;

          if (depth > 0) {
            private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
          }
          else {
            private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_data_not_eos, F_data_not_stop);
          }
        }
      }
      else if (buffer.string[range->start] == f_fss_embedded_list_close) {
        graph_first = 0x0;

        while (range->start <= range->stop && range->start < buffer.used) {

          position_previous = range->start;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;

          if (buffer.string[range->start] == f_fss_eol) {
            break;
          }

          if (buffer.string[range->start] != f_fss_delimit_placeholder) {
            status = f_fss_is_space(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) {
              break;
            }
          }
        } // while

        if (F_status_is_error(status)) break;

        if (depth > 0) {
          private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
        }
        else {
          private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_data_not_eos, F_data_not_stop);
        }

        if (buffer.string[range->start] == f_fss_eol) {
          status = private_fl_fss_nest_increase(found);
          if (F_status_is_error(status)) break;

          if (found->depth[depth].used == found->depth[depth].size) {
            f_macro_fss_items_t_resize(status, found->depth[depth], found->depth[depth].size + f_fss_default_allocation_step);
            if (F_status_is_error(status)) break;
          }

          position = found->depth[depth].used;

          if (found->depth[depth].array[position].content.size != 1) {
            f_macro_fss_content_t_resize(status, found->depth[depth].array[position].content, 1);
            if (F_status_is_error(status)) break;
          }

          if (depth) {
            found->depth[depth].array[position].parent = found->depth[depth - 1].used;

            // only assign object positions for nested objects.
            found->depth[depth].array[position].object.start = objects.array[depth].start;
            found->depth[depth].array[position].object.stop = objects.array[depth].stop;
          }

          found->depth[depth].array[position].content.array[0].start = positions_start.array[depth];
          found->depth[depth].array[position].content.array[0].stop = newline_last;
          found->depth[depth].array[position].content.used = 1;

          if (position >= found->depth[depth].used) {
            found->depth[depth].used++;
          }

          if (found->used < depth + 1) {
            found->used = depth + 1;
          }

          if (graph_first == 0x2) {
            status = private_fl_fss_delimits_increase(delimits);
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          line_start = range->start + 1;
          graph_first = 0x1;

          if (!depth) {
            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;

            private_fl_macro_fss_nest_return_on_overflow_delimited((buffer), (*range), (*found), positions_start, objects, F_none_eos, F_none_stop)

            private_fl_fss_string_lengths_delete(&positions_start);
            private_fl_fss_objects_delete(&objects);

            return FL_fss_found_content;
          }

          depth--;
        }
        else {

          // No valid object close found, seek until EOL.
          while (range->start <= range->stop && range->start < buffer.used) {

            if (buffer.string[range->start] == f_fss_eol) {
              if (graph_first == 0x2) {
                status = private_fl_fss_delimits_increase(delimits);
                if (F_status_is_error(status)) break;

                delimits->array[delimits->used++] = comment_delimit;
              }

              newline_last = range->start;
              line_start = range->start + 1;
              graph_first = 0x1;
              break;
            }

            position_previous = range->start;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (F_status_is_error(status)) break;

          if (depth > 0) {
            private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_terminated_not_nest_eos, F_terminated_not_nest_stop)
          }
          else {
            private_fl_macro_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, F_data_not_eos, F_data_not_stop)
          }
        }
      }
      else if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment) {
        position = range->start;

        status = f_fss_seek_to_eol(buffer, range);
        if (F_status_is_error(status)) break;

        status = private_fl_fss_ranges_increase(comments);
        if (F_status_is_error(status)) break;

        if (range->start > range->stop || range->start >= buffer.used) {
          range->start--;
        }
        else {
          if (graph_first == 0x2) {
            status = private_fl_fss_delimits_increase(delimits);
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          graph_first = 0x1;
        }

        comments->array[comments->used].start = position;
        comments->array[comments->used++].stop = range->start++;
        continue;
      }
      else if (buffer.string[range->start] != f_fss_eol) {
        position_previous = range->start;

        if (graph_first == 0x1) {
          status = f_fss_is_space(buffer, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) {
            graph_first = 0x0;
          }
        }

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;

        if (range->start >= buffer.used || range->start > range->stop) {
          break;
        }

        continue;
      }

      position_previous = range->start;

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) break;
    } // while

    private_fl_fss_string_lengths_delete(&positions_start);
    private_fl_fss_objects_delete(&objects);

    delimits->used = delimits_used;
    comments->used = comments_used;

    if (F_status_is_error(status)) {
      return status;
    }

    if (range->start > range->stop) {
      if (!depth) {
        return F_status_set_error(F_terminated_not_stop);
      }

      return F_status_set_error(F_terminated_not_nest_stop);
    }

    if (!depth) {
      return F_status_set_error(F_terminated_not_eos);
    }

    return F_status_set_error(F_terminated_not_nest_eos);
  }
#endif // _di_fl_fss_embedded_list_content_read_

#ifndef _di_fl_fss_embedded_list_object_write_string_
  f_return_status fl_fss_embedded_list_object_write_string(const f_string_static_t object, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(object, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eos) {
      status = F_data_not_eos;
    }
    else if (status == F_none_stop) {
      status = F_data_not_stop;
    }

    if (status == F_data_not_stop || status == F_data_not_eos) {
      if (complete == f_fss_complete_partial || complete == f_fss_complete_partial_trim || complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
        const f_status_t status_allocation = private_fl_fss_destination_increase_by(2, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_embedded_list_open;

        if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
          destination->string[destination->used++] = f_fss_embedded_list_open_end;
        }
      }

      return status;
    }

    // ensure that there is room for a slash delimit, the object open character, and the end of line character.
    status = private_fl_fss_destination_increase_by(destination->used + (range->stop - range->start) + 3, destination);
    if (F_status_is_error(status)) return status;

    const f_string_length_t input_start = range->start;
    const f_string_length_t used_start = destination->used;

    f_string_length_t i = 0;
    f_string_length_t slash_count = 0;

    f_string_range_t range_next = f_string_range_t_initialize;

    bool ends_on_space = F_false;

    uint8_t width = 0;

    // find the first graph character.
    while (range->start <= range->stop && range->start < object.used) {

      if (object.string[range->start] == f_fss_comment) {

        // when a comment is found, escape it.
        status = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = f_fss_delimit_slash;
        break;
      }

      status = f_fss_is_graph(object, *range);
      if (F_status_is_error(status)) break;

      if (status == F_true) break;

      // objects will not have leading whitespaces, but having this does not result in an invalid object, so just write the provided spaces.
      if (object.string[range->start] != f_fss_delimit_placeholder) {
        if (object.string[range->start] == f_fss_eol) {
          status = F_status_set_error(F_none_eol);
          break;
        }

        status = f_fss_is_space(object, *range);
        if (F_status_is_error(status)) break;

        if (status == F_true) {
          width = f_macro_utf_byte_width(object.string[range->start]);

          status = private_fl_fss_destination_increase_by(width, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < width; i++) {
            destination->string[destination->used++] = object.string[range->start + i];
          } // for
        }
      }

      status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(status)) break;
    } // while

    if (F_status_is_error(status)) {
      destination->used = used_start;
      return status;
    }

    while (range->start <= range->stop && range->start < object.used) {

      if (object.string[range->start] == f_fss_delimit_slash) {
        slash_count = 1;

        for (range->start++; range->start <= range->stop && range->start < object.used; range->start++) {

          if (object.string[range->start] == f_fss_delimit_placeholder) {
            continue;
          } else if (object.string[range->start] != f_fss_delimit_slash) {
            break;
          }

          slash_count++;
        } // for

        if (F_status_is_error(status)) break;

        if (range->start > range->stop || range->start >= object.used) {

          // slashes at the end of the object must be delimited to avoid delimiting the object close character.
          slash_count *= 2;
        }

        status = private_fl_fss_destination_increase_by(slash_count, destination);
        if (F_status_is_error(status)) break;

        while (slash_count--) {
          destination->string[destination->used++] = f_fss_delimit_slash;
        } // while

        if (range->start > range->stop || range->start >= object.used) {
          ends_on_space = F_false;
          break;
        }
      }

      if (object.string[range->start] != f_fss_delimit_placeholder) {
        if (object.string[range->start] == f_fss_eol) {
          status = F_status_set_error(F_none_eol);
          break;
        }

        status = f_fss_is_space(object, *range);
        if (F_status_is_error(status)) break;

        ends_on_space = status == F_true;

        width = f_macro_utf_byte_width(object.string[range->start]);

        status = private_fl_fss_destination_increase_by(width, destination);
        if (F_status_is_error(status)) break;

        for (i = 0; i < width; i++) {
          destination->string[destination->used++] = object.string[range->start + i];
        } // for
      }

      status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(status)) break;
    } // while

    if (F_status_is_error(status)) {
      destination->used = used_start;
      return status;
    }

    if (complete == f_fss_complete_partial || complete == f_fss_complete_partial_trim || complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
      if (complete == f_fss_complete_full_trim) {
        status = private_fl_fss_basic_list_write_object_trim(used_start, destination);

        if (F_status_is_error(status)) {
          destination->used = used_start;
          return status;
        }

        // prevent a space from being added post-trimming.
        ends_on_space = F_true;
      }

      status = private_fl_fss_destination_increase_by(3, destination);

      if (F_status_is_error(status)) {
        destination->used = used_start;
        return status;
      }

      if (!ends_on_space) {
        destination->string[destination->used++] = f_fss_space;
      }

      destination->string[destination->used++] = f_fss_embedded_list_open;

      if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
        destination->string[destination->used++] = f_fss_embedded_list_open_end;
      }
    }

    if (range->start > range->stop) {
      return F_none_stop;
    }

    if (range->start >= object.used) {
      return F_none_eos;
    }

    return F_none;
  }
#endif // _di_fl_fss_embedded_list_object_write_string_

#ifndef _di_fl_fss_embedded_list_content_write_string_
  f_return_status fl_fss_embedded_list_content_write_string(const f_string_static_t content, const uint8_t complete, const f_string_static_t *prepend, const f_string_ranges_t *ignore, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(content, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eos) {
      status = F_data_not_eos;
    }
    else if (status == F_none_stop) {
      status = F_data_not_stop;
    }

    if (range->start > range->stop || range->start >= content.used) {
      if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim || complete == f_fss_complete_end) {
        const f_status_t status_allocation = private_fl_fss_destination_increase_by(2, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_embedded_list_close;
        destination->string[destination->used++] = f_fss_embedded_list_close_end;
      }

      return status;
    }

    // ensure that there is room for a slash delimit and possibly the end of content characters.
    status = private_fl_fss_destination_increase_by(destination->used + (range->stop - range->start) + 3, destination);
    if (F_status_is_error(status)) return status;

    const f_string_length_t input_start = range->start;
    const f_string_length_t used_start = destination->used;

    bool is_comment = F_false;
    bool ends_on_eol = F_false;
    bool has_graph = F_false;
    bool do_prepend = F_true;

    f_string_length_t i = 0;
    f_string_length_t slash_count = 0;
    f_string_length_t start = 0;

    f_array_length_t r = 0;

    uint8_t width = 0;

    while (range->start <= range->stop && range->start < content.used) {

      if (content.string[range->start] == f_fss_delimit_slash && !is_comment) {
        slash_count = 1;

        if (do_prepend) {
          status = private_fl_fss_destination_prepend(prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        destination->string[destination->used++] = content.string[range->start];

        for (range->start++; range->start <= range->stop && range->start < content.used; range->start++) {

          if (content.string[range->start] == f_fss_delimit_placeholder) continue;
          if (content.string[range->start] != f_fss_delimit_slash) break;

          destination->string[destination->used++] = f_fss_delimit_slash;
          slash_count++;
        } // for

        if (content.string[range->start] == f_fss_embedded_list_open || content.string[range->start] == f_fss_embedded_list_close) {
          start = range->start++;

          status = f_fss_skip_past_space(content, range);
          if (F_status_is_error(status)) break;

          if (has_graph && content.string[range->start] == f_fss_embedded_list_close) {
            // do nothing.
          }
          else if (content.string[range->start] == f_fss_eol || range->start >= content.used || range->start > range->stop) {

            // increase by total slashes + 1 embedded list open/close.
            status = private_fl_fss_destination_increase_by(slash_count + 2, destination);
            if (F_status_is_error(status)) break;

            if (content.string[range->start] == f_fss_embedded_list_open) {
              while (slash_count--) {
                destination->string[destination->used++] = f_fss_delimit_slash;
              } // while
            }

            destination->string[destination->used++] = f_fss_delimit_slash;
            destination->string[destination->used++] = content.string[start];

            range->start = start + 1;

            status = private_fl_fss_basic_list_write_add_until_end(content, range, destination);
            if (F_status_is_error(status)) break;

            if (content.string[range->start] != f_fss_eol) {
              has_graph = F_true;
            }

            continue;
          }

          // increase by character at "start" and possible newline.
          status = private_fl_fss_destination_increase_by(2, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = content.string[start];

          if (content.string[range->start] == f_fss_eol) {
            destination->string[destination->used++] = f_fss_eol;
            ends_on_eol = F_true;
          }
          else {
            ends_on_eol = F_false;
          }

          range->start = start + 1;
          continue;
        }
      }
      else if ((content.string[range->start] == f_fss_embedded_list_open || (!has_graph && content.string[range->start] == f_fss_embedded_list_close)) && !is_comment) {
        start = range->start++;

        if (do_prepend) {
          status = private_fl_fss_destination_prepend(prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        has_graph = F_true;

        status = f_fss_skip_past_space(content, range);
        if (F_status_is_error(status)) break;

        if (content.string[range->start] == f_fss_eol || range->start >= content.used || range->start > range->stop) {

          if (content.string[range->start] == f_fss_eol) {
            do_prepend = F_true;
            ends_on_eol = F_true;
          }
          else {
            ends_on_eol = F_false;
          }

          if (ignore && ignore->used) {

            for (r = 0; r < ignore->used; r++) {
              if (start >= ignore->array[r].start && start <= ignore->array[r].stop) break;
            } // for

            if (r < ignore->used) {
              status = private_fl_fss_destination_increase(destination);
              if (F_status_is_error(status)) break;

              destination->string[destination->used++] = content.string[start];
              range->start = start + 1;
              continue;
            }
          }

          // increase by slash and extended list open and possible newline.
          status = private_fl_fss_destination_increase_by(3, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = f_fss_delimit_slash;
          destination->string[destination->used++] = content.string[start];

          range->start = start + 1;

          status = private_fl_fss_basic_list_write_add_until_end(content, range, destination);
          if (F_status_is_error(status)) break;

          continue;
        }

        status = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = content.string[start];
        range->start = start + 1;
        continue;
      }
      else if (content.string[range->start] == f_fss_comment && !has_graph) {
        is_comment = F_true;
      }
      else if (content.string[range->start] == f_fss_eol) {
        has_graph = F_false;
        is_comment = F_false;
      }
      else if ((status = f_fss_is_graph(content, *range)) == F_true) {
        has_graph = F_true;
      }
      else if (F_status_is_error(status)) {
        break;
      }

      if (content.string[range->start] != f_fss_delimit_placeholder) {
        if (do_prepend) {
          status = private_fl_fss_destination_prepend(prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        if (content.string[range->start] == f_fss_eol) {
          do_prepend = F_true;
          ends_on_eol = F_true;
        }
        else {
          ends_on_eol = F_false;
        }

        width = f_macro_utf_byte_width(content.string[range->start]);

        status = private_fl_fss_destination_increase_by(width, destination);
        if (F_status_is_error(status)) break;

        for (i = 0; i < width; i++) {
          destination->string[destination->used++] = content.string[range->start + i];
        } // for
      }

      status = f_utf_buffer_increment(content, range, 1);
      if (F_status_is_error(status)) break;
    } // while

    if (F_status_is_error(status)) {
      destination->used = used_start;
      return status;
    }

    if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim || complete == f_fss_complete_end) {
      status = private_fl_fss_destination_increase_by(3, destination);
      if (F_status_is_error(status)) return status;

      if (!ends_on_eol) {
        destination->string[destination->used++] = f_fss_eol;
      }

      destination->string[destination->used++] = f_fss_embedded_list_close;
      destination->string[destination->used++] = f_fss_embedded_list_close_end;
    }

    if (range->start > range->stop) {
      return F_none_stop;
    }

    if (range->start >= content.used) {
      return F_none_eos;
    }

    return F_none;
  }
#endif // _di_fl_fss_embedded_list_content_write_string_

#ifdef __cplusplus
} // extern "C"
#endif
