#include "embedded_list.h"
#include "../private-fss.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_embedded_list_object_read_
  f_status_t fl_fss_embedded_list_object_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_object_t * const found, f_fss_delimits_t * const delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    f_status_t status = f_fss_skip_past_space(buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eol) {

      // Move the start position to after the EOL.
      ++range->start;

      return F_fss_found_object_not;
    }

    if (status == F_none_eos) {
      return F_data_not_eos;
    }

    if (status == F_none_stop) {
      return F_data_not_stop;
    }

    // Return found nothing if this line only contains whitespace and delimit placeholders.
    if (buffer.string[range->start] == f_fss_eol_s.string[0]) {

      // Move the start position to after the EOL.
      ++range->start;

      return F_fss_found_object_not;
    }

    // Begin the search.
    found->start = range->start;

    // Ignore all comment lines.
    if (buffer.string[range->start] == f_fss_comment_s.string[0]) {
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

      // Move the start position to after the EOL.
      ++range->start;

      return F_fss_found_object_not;
    }

    f_array_length_t start = 0;
    f_array_length_t stop = 0;
    f_array_length_t slash_first = 0;
    f_array_length_t slash_count = 0;

    bool graph_first = F_true;

    // Identify where the object ends.
    while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol_s.string[0]) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
        slash_first = range->start;
        slash_count = 1;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;

        while (range->start <= range->stop && range->start < buffer.used && (buffer.string[range->start] == f_fss_delimit_placeholder_s.string[0] || buffer.string[range->start] == f_fss_delimit_slash_s.string[0])) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) slash_count++;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        private_macro_fl_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

        if (buffer.string[range->start] == f_fss_embedded_list_open_s.string[0]) {
          graph_first = F_false;
          stop = range->start++ - 1;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (state.interrupt) {
              status = state.interrupt((void *) &state, 0);

              if (F_status_set_fine(status) == F_interrupt) {
                status = F_status_set_error(F_interrupt);

                break;
              }
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

            status = f_fss_is_graph(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_true) break;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          private_macro_fl_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
            start = range->start;

            range->start = slash_first;

            macro_f_fss_delimits_t_increase_by(status, (*delimits), (slash_count / 2) + 1);
            if (F_status_is_error(status)) break;

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {

                if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
                  if (slash_count % 2 == 1) {
                    delimits->array[delimits->used++] = range->start;
                  }

                  --slash_count;
                }

                status = f_utf_buffer_increment(buffer, range, 1);
                if (F_status_is_error(status)) break;
              } // while

              if (F_status_is_error(status)) break;

              found->stop = stop;
              range->start = start + 1;

              return F_fss_found_object;
            }

            range->start = start + 1;
            return F_fss_found_object_not;
          }
        }
        else if (graph_first && buffer.string[range->start] == f_fss_comment_s.string[0]) {
          graph_first = F_false;

          // Comments may only have whitespace before the '#', therefore only the first slash needs to be delimited.
          macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
          if (F_status_is_error(status)) break;

          delimits->array[delimits->used++] = slash_first;
          ++range->start;
        }
        else {
          graph_first = F_false;
        }

        continue;
      }
      else if (buffer.string[range->start] == f_fss_embedded_list_open_s.string[0]) {
        graph_first = F_false;
        stop = range->start - 1;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

          status = f_fss_is_space(buffer, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        private_macro_fl_fss_object_return_on_overflow_delimited((buffer), (*range), (*found), F_none_eos, F_none_stop);

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          found->stop = stop;

          // Move the start position to after the EOL.
          ++range->start;

          return F_fss_found_object;
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

    // Seek to the end of the line when no valid object is found.
    while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol_s.string[0]) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      status = f_utf_buffer_increment(buffer, range, 1);

      if (F_status_is_error(status)) {
        delimits->used = delimits_used;

        return status;
      }
    } // while

    private_macro_fl_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

    status = f_utf_buffer_increment(buffer, range, 1);

    if (F_status_is_error(status)) {
      delimits->used = delimits_used;

      return status;
    }

    return F_fss_found_object_not;
  }
#endif // _di_fl_fss_embedded_list_object_read_

#ifndef _di_fl_fss_embedded_list_content_read_
  f_status_t fl_fss_embedded_list_content_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_nest_t * const found, f_fss_delimits_t * const delimits, f_fss_comments_t * const comments) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
      if (!comments) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eos || status == F_none_stop) {
      return status;
    }

    macro_f_fss_nest_t_increase(status, state.step_small, (*found));
    if (F_status_is_error(status)) return status;

    f_array_lengths_t positions_start = f_array_lengths_t_initialize;

    macro_f_array_lengths_t_resize(status, positions_start, state.step_small)
    if (F_status_is_error(status)) return status;

    f_fss_objects_t objects = f_fss_objects_t_initialize;

    macro_f_fss_objects_t_resize(status, objects, state.step_small)

    if (F_status_is_error(status)) {
      f_array_lengths_resize(0, &positions_start);

      return status;
    }

    f_array_lengths_t slashes = f_array_lengths_t_initialize;

    macro_f_array_lengths_t_resize(status, slashes, state.step_small)

    if (F_status_is_error(status)) {
      f_array_lengths_resize(0, &positions_start);
      macro_f_fss_objects_t_delete_simple(objects);

      return status;
    }

    const f_array_length_t delimits_used = delimits->used;
    const f_array_length_t comments_used = comments->used;

    f_array_length_t depth = 0;
    f_array_length_t position = 0;

    f_array_length_t position_previous = range->start;
    f_array_length_t line_start = range->start;
    f_array_length_t newline_last = range->start;
    f_array_length_t comment_delimit = 0;

    f_array_length_t slash_first = 0;
    f_array_length_t slash_last = 0;

    f_array_length_t before_list_open = position_previous;

    bool is_open = F_false;

    // 0x0 = false, 0x1 = true, 0x2 = false, but there is a delimited comment, comment_delimit is set.
    uint8_t graph_first = 0x0;

    // Initialize depth 1 start position.
    // Positions_start.used is used as a max depth (such that positions_start.used == max depth + 1).
    positions_start.array[0] = range->start;
    positions_start.used = 1;

    slashes.array[0] = 0;
    slashes.used = 1;

    while (range->start <= range->stop && range->start < buffer.used) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
        if (graph_first == 0x2) {
          macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
          if (F_status_is_error(status)) break;

          delimits->array[delimits->used++] = comment_delimit;
        }

        newline_last = range->start;
        position_previous = range->start++;
        graph_first = 0x1;

        if (depth) {
          private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
        }
        else {
          private_macro_fl_fss_nest_return_on_overflow_delimited((buffer), (*range), (*found), positions_start, objects, slashes, F_none_eos, F_none_stop);
        }

        line_start = range->start;

        continue;
      }

      if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
        slash_first = range->start;
        slash_last = range->start;
        slashes.array[depth] = 1;

        position_previous = range->start++;

        while (range->start <= range->stop && range->start < buffer.used && (buffer.string[range->start] == f_fss_delimit_placeholder_s.string[0] || buffer.string[range->start] == f_fss_delimit_slash_s.string[0])) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          position_previous = range->start;

          if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
            slash_last = range->start++;
            ++slashes.array[depth];
          }
          else {
            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          }
        } // while

        if (F_status_is_error(status)) break;

        if (depth) {
          private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
        }
        else {
          private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_data_not_eos, F_data_not_stop);
        }

        // All slashes for an open are delimited (because it could represent a slash in the object name).
        // For example 'object {' = valid open, name 'object', 'object \{' represents 'object {', 'object \\{' = valid open, name 'object \', 'object \\\{' represents 'object \{', etc..
        // Only the first slash before a close is delimited, all others are maintained.
        // For example '}' = valid close, '\}' represents '}', '\\}' represents '\}', '\\\}' represents '\\}', '\\\\}' represents '\\\}', and so on..
        // When slash is odd and a (delimited) valid open/close is found, then save delimited positions and continue.
        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          if (graph_first == 0x2) {
            macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          position_previous = range->start++;
          line_start = range->start;
          graph_first = 0x1;
        }
        else if (buffer.string[range->start] == f_fss_embedded_list_open_s.string[0] || buffer.string[range->start] == f_fss_embedded_list_close_s.string[0]) {
          before_list_open = position_previous;
          is_open = F_false;
          graph_first = 0x0;

          if (buffer.string[range->start] == f_fss_embedded_list_open_s.string[0]) {
            is_open = F_true;
          }

          position_previous = range->start++;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (state.interrupt) {
              status = state.interrupt((void *) &state, 0);

              if (F_status_set_fine(status) == F_interrupt) {
                status = F_status_set_error(F_interrupt);

                break;
              }
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
              if (graph_first == 0x2) {
                macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
                if (F_status_is_error(status)) break;

                delimits->array[delimits->used++] = comment_delimit;
              }

              newline_last = range->start;
              line_start = range->start + 1;
              graph_first = 0x1;

              break;
            }

            if (buffer.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
              status = f_fss_is_space(buffer, *range);
              if (F_status_is_error(status)) break;

              if (status == F_false) break;
            }

            position_previous = range->start;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (F_status_is_error(status)) break;

          if (depth) {
            private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
          }
          else {
            private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_data_not_eos, F_data_not_stop);
          }

          // This is a valid object open/close that has been delimited, save the slash delimit positions.
          if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
            newline_last = range->start;
            line_start = range->start + 1;
            graph_first = 0x1;

            if (is_open) {
              bool is_object = F_false;

              if (slashes.array[depth] % 2 == 0) {
                is_object = F_true;
              }

              range->start = slash_first;

              macro_f_fss_delimits_t_increase_by(status, (*delimits), (slashes.array[depth] / 2) + 1);
              if (F_status_is_error(status)) break;

              // Apply slash delimits, only slashes and placeholders should be present.
              while (slashes.array[depth]) {

                if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
                  if (slashes.array[depth] % 2 == 1) {
                    delimits->array[delimits->used++] = range->start;
                  }

                  --slashes.array[depth];
                }

                // Delimit slashes and placeholders are required to be in the ASCII range.
                position_previous = range->start++;
              } // while

              if (F_status_is_error(status)) break;

              // When slashes are even, the object is valid and needs to be processed.
              if (is_object) {
                if (++depth > positions_start.size) {
                  macro_f_array_lengths_t_resize(status, positions_start, positions_start.size + state.step_small);
                  if (F_status_is_error(status)) break;

                  macro_f_fss_objects_t_resize(status, objects, objects.size + state.step_small);
                  if (F_status_is_error(status)) break;

                  macro_f_array_lengths_t_resize(status, slashes, slashes.size + state.step_small);
                  if (F_status_is_error(status)) break;
                }

                if (positions_start.used < depth) {
                  positions_start.used = depth;
                  slashes.used = depth;
                }

                positions_start.array[depth] = newline_last + 1;

                objects.array[depth].start = line_start;
                objects.array[depth].stop = before_list_open;

                slashes.array[depth] = 0;
              }
            }
            else {
              macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
              if (F_status_is_error(status)) break;

              delimits->array[delimits->used++] = slash_last;
            }

            range->start = newline_last;
          }
        }
        else if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment_s.string[0]) {
          graph_first = 0x2;
          comment_delimit = slash_first;
        }
        else {
          graph_first = 0x0;
        }
      }
      else if (buffer.string[range->start] == f_fss_embedded_list_open_s.string[0]) {
        graph_first = 0x0;
        before_list_open = position_previous;
        position_previous = range->start;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

          if (buffer.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
            status = f_fss_is_space(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;
          }

          position_previous = range->start;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        if (depth) {
          private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
        }
        else {
          private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_data_not_eos, F_data_not_stop);
        }

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          ++depth;

          if (depth >= positions_start.size) {
            macro_f_array_lengths_t_resize(status, positions_start, positions_start.size + state.step_small);
            if (F_status_is_error(status)) break;

            macro_f_fss_objects_t_resize(status, objects, objects.size + state.step_small);
            if (F_status_is_error(status)) break;

            macro_f_array_lengths_t_resize(status, slashes, slashes.size + state.step_small);
            if (F_status_is_error(status)) break;
          }

          if (positions_start.used <= depth) {
            positions_start.used = depth + 1;
            slashes.used = depth + 1;
          }

          positions_start.array[depth] = range->start + 1;

          objects.array[depth].start = line_start;
          objects.array[depth].stop = before_list_open;

          slashes.array[depth] = 0;

          if (graph_first == 0x2) {
            macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
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
            macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          line_start = range->start + 1;
          graph_first = 0x1;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (state.interrupt) {
              status = state.interrupt((void *) &state, 0);

              if (F_status_set_fine(status) == F_interrupt) {
                status = F_status_set_error(F_interrupt);

                break;
              }
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
              newline_last = range->start;
              line_start = range->start + 1;

              break;
            }

            position_previous = range->start;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (F_status_is_error(status)) break;

          if (depth) {
            private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
          }
          else {
            private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_data_not_eos, F_data_not_stop);
          }
        }
      }
      else if (buffer.string[range->start] == f_fss_embedded_list_close_s.string[0]) {
        graph_first = 0x0;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          position_previous = range->start;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

          if (buffer.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
            status = f_fss_is_space(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;
          }
        } // while

        if (F_status_is_error(status)) break;

        if (depth) {
          private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_terminated_not_nest_eos, F_terminated_not_nest_stop);
        }
        else {
          private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_data_not_eos, F_data_not_stop);
        }

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          macro_f_fss_nest_t_increase(status, state.step_small, (*found));
          if (F_status_is_error(status)) break;

          if (found->depth[depth].used == found->depth[depth].size) {
            macro_f_fss_items_t_resize(status, found->depth[depth], found->depth[depth].size + state.step_small);
            if (F_status_is_error(status)) break;
          }

          position = found->depth[depth].used;

          if (found->depth[depth].array[position].content.size != 1) {
            macro_f_fss_content_t_resize(status, found->depth[depth].array[position].content, 1);
            if (F_status_is_error(status)) break;
          }

          if (depth) {
            found->depth[depth].array[position].parent = found->depth[depth - 1].used;

            // Only assign object positions for nested objects.
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
            macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          line_start = range->start + 1;
          graph_first = 0x1;

          if (!depth) {
            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;

            private_macro_fl_fss_nest_return_on_overflow_delimited((buffer), (*range), (*found), positions_start, objects, slashes, F_none_eos, F_none_stop)

            f_array_lengths_resize(0, &positions_start);
            macro_f_fss_objects_t_delete_simple(objects);
            f_array_lengths_resize(0, &slashes);

            return F_fss_found_content;
          }

          --depth;
        }
        else {

          // No valid object close found, seek until EOL.
          while (range->start <= range->stop && range->start < buffer.used) {

            if (state.interrupt) {
              status = state.interrupt((void *) &state, 0);

              if (F_status_set_fine(status) == F_interrupt) {
                status = F_status_set_error(F_interrupt);

                break;
              }
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
              if (graph_first == 0x2) {
                macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
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

          if (depth) {
            private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_terminated_not_nest_eos, F_terminated_not_nest_stop)
          }
          else {
            private_macro_fl_fss_nest_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, positions_start, objects, slashes, F_data_not_eos, F_data_not_stop)
          }
        }
      }
      else if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment_s.string[0]) {
        position = newline_last + 1;

        status = f_fss_seek_to_eol(buffer, range);
        if (F_status_is_error(status)) break;

        macro_f_fss_comments_t_increase(status, state.step_small, (*comments))
        if (F_status_is_error(status)) break;

        if (range->start > range->stop || range->start >= buffer.used) {
          --range->start;
        }
        else {
          if (graph_first == 0x2) {
            macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
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
      else if (buffer.string[range->start] != f_fss_eol_s.string[0]) {
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

        if (range->start >= buffer.used || range->start > range->stop) break;

        continue;
      }

      position_previous = range->start;

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) break;
    } // while

    f_array_lengths_resize(0, &positions_start);
    macro_f_fss_objects_t_delete_simple(objects);
    f_array_lengths_resize(0, &slashes);

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

#ifndef _di_fl_fss_embedded_list_object_write_
  f_status_t fl_fss_embedded_list_object_write(const f_string_static_t object, const uint8_t complete, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
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
      if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
        const f_status_t status_allocation = f_string_dynamic_increase_by(2, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_embedded_list_open_s.string[0];

        if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
          destination->string[destination->used++] = f_fss_embedded_list_open_end_s.string[0];
        }
      }

      return status;
    }

    // Ensure that there is room for a slash delimit, the object open character, and the end of line character.
    status = f_string_dynamic_increase_by(4, destination);
    if (F_status_is_error(status)) return status;

    const f_array_length_t used_start = destination->used;

    f_array_length_t i = 0;
    f_array_length_t slash_count = 0;

    bool ends_on_space = F_false;

    uint8_t width = 0;

    // Find the first graph character.
    while (range->start <= range->stop && range->start < object.used) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      if (object.string[range->start] == f_fss_comment_s.string[0]) {

        // When a comment is found, escape it.
        status = f_string_dynamic_increase(state.step_large, destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];

        break;
      }

      status = f_fss_is_graph(object, *range);
      if (F_status_is_error(status)) break;

      if (status == F_true) break;

      // Objects will not have leading whitespaces, but having this does not result in an invalid object, so just write the provided spaces.
      if (object.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
        if (object.string[range->start] == f_fss_eol_s.string[0]) {
          status = F_status_set_error(F_none_eol);

          break;
        }

        status = f_fss_is_space(object, *range);
        if (F_status_is_error(status)) break;

        if (status == F_true) {
          width = macro_f_utf_byte_width(object.string[range->start]);

          status = f_string_dynamic_increase_by(width, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < width; ++i) {
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

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      if (object.string[range->start] == f_fss_delimit_slash_s.string[0]) {
        slash_count = 1;

        for (++range->start; range->start <= range->stop && range->start < object.used; ++range->start) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (object.string[range->start] == f_fss_delimit_placeholder_s.string[0]) continue;
          if (object.string[range->start] != f_fss_delimit_slash_s.string[0]) break;

          ++slash_count;
        } // for

        if (F_status_is_error(status)) break;

        if (range->start > range->stop || range->start >= object.used) {

          // Slashes at the end of the object must be delimited to avoid delimiting the object close character.
          slash_count *= 2;
        }

        status = f_string_dynamic_increase_by(slash_count, destination);
        if (F_status_is_error(status)) break;

        while (--slash_count) {
          destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
        } // while

        if (range->start > range->stop || range->start >= object.used) {
          ends_on_space = F_false;

          break;
        }
      }

      if (object.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
        if (object.string[range->start] == f_fss_eol_s.string[0]) {
          status = F_status_set_error(F_none_eol);

          break;
        }

        status = f_fss_is_space(object, *range);
        if (F_status_is_error(status)) break;

        ends_on_space = status == F_true;

        width = macro_f_utf_byte_width(object.string[range->start]);

        status = f_string_dynamic_increase_by(width, destination);
        if (F_status_is_error(status)) break;

        for (i = 0; i < width; ++i) {
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

    if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
      if (complete == f_fss_complete_full_trim_e) {
        status = private_fl_fss_basic_list_write_object_trim(used_start, state, destination);

        if (F_status_is_error(status)) {
          destination->used = used_start;

          return status;
        }

        // Prevent a space from being added post-trimming.
        ends_on_space = F_true;
      }

      status = f_string_dynamic_increase_by(3, destination);

      if (F_status_is_error(status)) {
        destination->used = used_start;

        return status;
      }

      if (!ends_on_space) {
        destination->string[destination->used++] = f_fss_space_s.string[0];
      }

      destination->string[destination->used++] = f_fss_embedded_list_open_s.string[0];

      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
        destination->string[destination->used++] = f_fss_embedded_list_open_end_s.string[0];
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
#endif // _di_fl_fss_embedded_list_object_write_

#ifndef _di_fl_fss_embedded_list_content_write_
  f_status_t fl_fss_embedded_list_content_write(const f_string_static_t content, const uint8_t complete, const f_string_static_t * const prepend, const f_string_ranges_t * const ignore, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
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
      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
        const f_status_t status_allocation = f_string_dynamic_increase_by(2, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_embedded_list_close_s.string[0];
        destination->string[destination->used++] = f_fss_embedded_list_close_end_s.string[0];
      }

      return status;
    }

    // Ensure that there is room for a slash delimit and possibly the end of content characters.
    status = f_string_dynamic_increase_by(4, destination);
    if (F_status_is_error(status)) return status;

    const f_array_length_t used_start = destination->used;

    bool is_comment = F_false;
    bool ends_on_eol = F_false;
    bool has_graph = F_false;
    bool do_prepend = prepend ? F_true : F_false;

    f_array_length_t i = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;

    f_array_length_t r = 0;

    uint8_t width = 0;

    while (range->start <= range->stop && range->start < content.used) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      if (content.string[range->start] == f_fss_delimit_slash_s.string[0] && !is_comment) {
        slash_count = 1;

        if (do_prepend) {
          status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        destination->string[destination->used++] = content.string[range->start];

        for (++range->start; range->start <= range->stop && range->start < content.used; ++range->start) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (content.string[range->start] == f_fss_delimit_placeholder_s.string[0]) continue;
          if (content.string[range->start] != f_fss_delimit_slash_s.string[0]) break;

          destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          ++slash_count;
        } // for

        if (content.string[range->start] == f_fss_embedded_list_open_s.string[0] || content.string[range->start] == f_fss_embedded_list_close_s.string[0]) {
          start = range->start++;

          status = f_fss_skip_past_space(content, range);
          if (F_status_is_error(status)) break;

          if (range->start >= content.used || range->start > range->stop || content.string[range->start] == f_fss_eol_s.string[0]) {

            // Increase by total slashes + 1 embedded list open/close.
            status = f_string_dynamic_increase_by(slash_count + 2, destination);
            if (F_status_is_error(status)) break;

            if (content.string[range->start] == f_fss_embedded_list_open_s.string[0]) {
              while (--slash_count) {
                destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
              } // while
            }

            destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
            destination->string[destination->used++] = content.string[start];

            range->start = start + 1;

            status = private_fl_fss_basic_list_write_add_until_end(content, state, range, destination);
            if (F_status_is_error(status)) break;

            if (content.string[range->start] != f_fss_eol_s.string[0]) {
              has_graph = F_true;
            }

            continue;
          }

          // Increase by character at "start" and possible newline.
          status = f_string_dynamic_increase_by(2, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = content.string[start];

          if (content.string[range->start] == f_fss_eol_s.string[0]) {
            destination->string[destination->used++] = f_fss_eol_s.string[0];
            ends_on_eol = F_true;
          }
          else {
            ends_on_eol = F_false;
          }

          range->start = start + 1;
          continue;
        }
      }
      else if ((content.string[range->start] == f_fss_embedded_list_open_s.string[0] || (!has_graph && content.string[range->start] == f_fss_embedded_list_close_s.string[0])) && !is_comment) {
        start = range->start++;

        if (do_prepend) {
          status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        has_graph = F_true;

        status = f_fss_skip_past_space(content, range);
        if (F_status_is_error(status)) break;

        if (range->start >= content.used || range->start > range->stop || content.string[range->start] == f_fss_eol_s.string[0]) {

          if (content.string[range->start] == f_fss_eol_s.string[0] && prepend) {
            do_prepend = F_true;
            ends_on_eol = F_true;
          }
          else {
            ends_on_eol = F_false;
          }

          if (ignore && ignore->used) {

            for (r = 0; r < ignore->used; ++r) {
              if (start >= ignore->array[r].start && start <= ignore->array[r].stop) break;
            } // for

            if (r < ignore->used) {
              status = f_string_dynamic_increase(state.step_large, destination);
              if (F_status_is_error(status)) break;

              destination->string[destination->used++] = content.string[start];
              range->start = start + 1;
              continue;
            }
          }

          // Increase by slash and extended list open and possible newline.
          status = f_string_dynamic_increase_by(3, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          destination->string[destination->used++] = content.string[start];

          range->start = start + 1;

          status = private_fl_fss_basic_list_write_add_until_end(content, state, range, destination);
          if (F_status_is_error(status)) break;

          continue;
        }

        status = f_string_dynamic_increase(state.step_large, destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = content.string[start];
        range->start = start + 1;
        continue;
      }
      else if (content.string[range->start] == f_fss_comment_s.string[0] && !has_graph) {
        is_comment = F_true;
      }
      else if (content.string[range->start] == f_fss_eol_s.string[0]) {
        has_graph = F_false;
        is_comment = F_false;
      }
      else if ((status = f_fss_is_graph(content, *range)) == F_true) {
        has_graph = F_true;
      }
      else if (F_status_is_error(status)) {
        break;
      }

      if (content.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
        if (do_prepend) {
          status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        if (content.string[range->start] == f_fss_eol_s.string[0] && prepend) {
          do_prepend = F_true;
          ends_on_eol = F_true;
        }
        else {
          ends_on_eol = F_false;
        }

        width = macro_f_utf_byte_width(content.string[range->start]);

        status = f_string_dynamic_increase_by(width, destination);
        if (F_status_is_error(status)) break;

        for (i = 0; i < width; ++i) {
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

    if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
      status = f_string_dynamic_increase_by(3, destination);
      if (F_status_is_error(status)) return status;

      if (!ends_on_eol) {
        destination->string[destination->used++] = f_fss_eol_s.string[0];
      }

      destination->string[destination->used++] = f_fss_embedded_list_close_s.string[0];
      destination->string[destination->used++] = f_fss_embedded_list_close_end_s.string[0];
    }

    if (range->start > range->stop) {
      return F_none_stop;
    }

    if (range->start >= content.used) {
      return F_none_eos;
    }

    return F_none;
  }
#endif // _di_fl_fss_embedded_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
