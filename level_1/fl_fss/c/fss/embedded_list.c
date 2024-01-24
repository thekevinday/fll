#include "embedded_list.h"
#include "../private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_embedded_list_content_read_
  void fl_fss_embedded_list_content_read(const f_string_static_t buffer, f_range_t * const range, f_fss_nest_t * const found, f_number_unsigneds_t * const delimits, f_ranges_t * const comments, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !found || !delimits || !comments) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    f_fss_skip_past_delimit(buffer, range, state);
    if (F_status_is_error(state->status)) return;
    if (state->status == F_data_not) return;
    if (state->status == F_okay_eos || state->status == F_okay_stop) return;

    state->status = f_memory_array_increase(state->step_small, sizeof(f_fss_nest_t), (void **) &found->depth, &found->used, &found->size);
    if (F_status_is_error(state->status)) return;

    f_number_unsigneds_t positions_start = f_number_unsigneds_t_initialize;

    state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
    if (F_status_is_error(state->status)) return;

    f_ranges_t objects = f_ranges_t_initialize;

    state->status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);

    if (F_status_is_error(state->status)) {
      f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);

      return;
    }

    f_number_unsigneds_t slashes = f_number_unsigneds_t_initialize;

    state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

    if (F_status_is_error(state->status)) {
      f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
      f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);

      return;
    }

    const f_number_unsigned_t delimits_used = delimits->used;
    const f_number_unsigned_t comments_used = comments->used;

    f_number_unsigned_t depth = 0;
    f_number_unsigned_t position = 0;

    f_number_unsigned_t position_previous = range->start;
    f_number_unsigned_t line_start = range->start;
    f_number_unsigned_t newline_last = range->start;
    f_number_unsigned_t comment_delimit = 0;

    f_number_unsigned_t slash_first = 0;
    f_number_unsigned_t slash_last = 0;

    f_number_unsigned_t before_list_open = position_previous;

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

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
        if (graph_first == 0x2) {
          state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
          if (F_status_is_error(state->status)) break;

          delimits->array[delimits->used++] = comment_delimit;
        }

        newline_last = range->start;
        position_previous = range->start++;
        graph_first = 0x1;

        if (depth) {
          if (range->start >= buffer.used || range->start > range->stop) {
            delimits->used = delimits_used;
            comments->used = comments_used;

            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            state->status = (range->start >= buffer.used) ? F_end_not_nest_eos : F_end_not_nest_stop;

            return;
          }
        }
        else {
          if (range->start >= buffer.used || range->start > range->stop) {
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            state->status = (range->start >= buffer.used) ? F_okay_eos : F_okay_stop;

            return;
          }
        }

        line_start = range->start;

        continue;
      }

      if (buffer.string[range->start] == f_fss_slash_s.string[0]) {
        slash_first = range->start;
        slash_last = range->start;
        slashes.array[depth] = 1;

        position_previous = range->start++;

        while (range->start <= range->stop && range->start < buffer.used && (buffer.string[range->start] == f_fss_placeholder_s.string[0] || buffer.string[range->start] == f_fss_slash_s.string[0])) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) break;
          }

          position_previous = range->start;

          if (buffer.string[range->start] == f_fss_slash_s.string[0]) {
            slash_last = range->start++;
            ++slashes.array[depth];
          }
          else {
            state->status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(state->status)) break;
          }
        } // while

        if (F_status_is_error(state->status)) break;

        if (depth) {
          if (range->start >= buffer.used || range->start > range->stop) {
            delimits->used = delimits_used;
            comments->used = comments_used;

            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            state->status = (range->start >= buffer.used) ? F_end_not_nest_eos : F_end_not_nest_stop;

            return;
          }
        }
        else {
          if (range->start >= buffer.used || range->start > range->stop) {
            delimits->used = delimits_used;
            comments->used = comments_used;

            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            state->status = (range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop;

            return;
          }
        }

        // All slashes for an open are delimited (because it could represent a slash in the object name).
        // For example 'object {' = valid open, name 'object', 'object \{' represents 'object {', 'object \\{' = valid open, name 'object \', 'object \\\{' represents 'object \{', etc..
        // Only the first slash before a close is delimited, all others are maintained.
        // For example '}' = valid close, '\}' represents '}', '\\}' represents '\}', '\\\}' represents '\\}', '\\\\}' represents '\\\}', and so on..
        // When slash is odd and a (delimited) valid open/close is found, then save delimited positions and continue.
        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          if (graph_first == 0x2) {
            state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
            if (F_status_is_error(state->status)) break;

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

            if (state->interrupt) {
              state->interrupt((void *) state, 0);
              if (F_status_set_fine(state->status) == F_interrupt) break;
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
              if (graph_first == 0x2) {
                state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
                if (F_status_is_error(state->status)) break;

                delimits->array[delimits->used++] = comment_delimit;
              }

              newline_last = range->start;
              line_start = range->start + 1;
              graph_first = 0x1;

              break;
            }

            if (buffer.string[range->start] != f_fss_placeholder_s.string[0]) {
              if (f_fss_is_space(buffer, *range, state) == F_false) {
                if (F_status_is_error(state->status)) break;

                break;
              }
            }

            position_previous = range->start;

            f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(state->status)) break;
          } // while

          if (F_status_is_error(state->status)) break;

          if (depth) {
            if (range->start >= buffer.used || range->start > range->stop) {
              delimits->used = delimits_used;
              comments->used = comments_used;

              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
              f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

              state->status = (range->start >= buffer.used) ? F_end_not_nest_eos : F_end_not_nest_stop;

              return;
            }
          }
          else {
            if (range->start >= buffer.used || range->start > range->stop) {
              delimits->used = delimits_used;
              comments->used = comments_used;

              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
              f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

              state->status = (range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop;

              return;
            }
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

              state->status = f_memory_array_increase_by((slashes.array[depth] / 2) + 1, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
              if (F_status_is_error(state->status)) break;

              // Apply slash delimits, only slashes and placeholders should be present.
              while (slashes.array[depth]) {

                if (buffer.string[range->start] == f_fss_slash_s.string[0]) {
                  if (slashes.array[depth] % 2 == 1) {
                    delimits->array[delimits->used++] = range->start;
                  }

                  --slashes.array[depth];
                }

                // Delimit slashes and placeholders are required to be in the ASCII range.
                position_previous = range->start++;
              } // while

              if (F_status_is_error(state->status)) break;

              // When slashes are even, the object is valid and needs to be processed.
              if (is_object) {
                if (++depth > positions_start.size) {
                  state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
                  if (F_status_is_error(state->status)) break;

                  state->status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
                  if (F_status_is_error(state->status)) break;

                  state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);
                  if (F_status_is_error(state->status)) break;
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
              state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
              if (F_status_is_error(state->status)) break;

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

        state->status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(state->status)) break;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) break;
          }

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

          if (buffer.string[range->start] != f_fss_placeholder_s.string[0]) {
            if (f_fss_is_space(buffer, *range, state) == F_false) {
              if (F_status_is_error(state->status)) break;

              break;
            }
          }

          position_previous = range->start;

          f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(state->status)) break;
        } // while

        if (F_status_is_error(state->status)) break;

        if (depth) {
          if (range->start >= buffer.used || range->start > range->stop) {
            delimits->used = delimits_used;
            comments->used = comments_used;

            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            state->status = (range->start >= buffer.used) ? F_end_not_nest_eos : F_end_not_nest_stop;

            return;
          }
        }
        else {
          if (range->start >= buffer.used || range->start > range->stop) {
            delimits->used = delimits_used;
            comments->used = comments_used;

            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            state->status = (range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop;

            return;
          }
        }

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          ++depth;

          if (depth >= positions_start.size) {
            state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            if (F_status_is_error(state->status)) break;

            state->status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            if (F_status_is_error(state->status)) break;

            state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);
            if (F_status_is_error(state->status)) break;
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
            state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
            if (F_status_is_error(state->status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          line_start = range->start + 1;
          graph_first = 0x1;
        }
        else {

          // No valid object close found, seek until EOL.
          f_fss_seek_to_eol(buffer, range, state);
          if (F_status_is_error(state->status)) break;

          if (graph_first == 0x2) {
            state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
            if (F_status_is_error(state->status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          line_start = range->start + 1;
          graph_first = 0x1;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (state->interrupt) {
              state->interrupt((void *) state, 0);
              if (F_status_set_fine(state->status) == F_interrupt) break;
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
              newline_last = range->start;
              line_start = range->start + 1;

              break;
            }

            position_previous = range->start;

            state->status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(state->status)) break;
          } // while

          if (F_status_is_error(state->status)) break;

          if (depth) {
            if (range->start >= buffer.used || range->start > range->stop) {
              delimits->used = delimits_used;
              comments->used = comments_used;

              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
              f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

              state->status = (range->start >= buffer.used) ? F_end_not_nest_eos : F_end_not_nest_stop;

              return;
            }
          }
          else {
            if (range->start >= buffer.used || range->start > range->stop) {
              delimits->used = delimits_used;
              comments->used = comments_used;

              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
              f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

              state->status = (range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop;

              return;
            }
          }
        }
      }
      else if (buffer.string[range->start] == f_fss_embedded_list_close_s.string[0]) {
        graph_first = 0x0;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) break;
          }

          position_previous = range->start;

          state->status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(state->status)) break;

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

          if (buffer.string[range->start] != f_fss_placeholder_s.string[0]) {
            if (f_fss_is_space(buffer, *range, state) == F_false) {
              if (F_status_is_error(state->status)) break;

              break;
            }
          }
        } // while

        if (F_status_is_error(state->status)) break;

        if (depth) {
          if (range->start >= buffer.used || range->start > range->stop) {
            delimits->used = delimits_used;
            comments->used = comments_used;

            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            state->status = (range->start >= buffer.used) ? F_end_not_nest_eos : F_end_not_nest_stop;

            return;
          }
        }
        else {
          if (range->start >= buffer.used || range->start > range->stop) {
            delimits->used = delimits_used;
            comments->used = comments_used;

            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            state->status = (range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop;

            return;
          }
        }

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          state->status = f_memory_array_increase(state->step_small, sizeof(f_fss_nest_t), (void **) &found->depth, &found->used, &found->size);
          if (F_status_is_error(state->status)) break;

          if (found->depth[depth].used == found->depth[depth].size) {
            state->status = f_memory_array_increase(state->step_small, sizeof(f_fss_item_t), (void **) &found->depth[depth].array, &found->depth[depth].used, &found->depth[depth].size);
            if (F_status_is_error(state->status)) break;
          }

          position = found->depth[depth].used;

          if (found->depth[depth].array[position].content.size != 1) {
            state->status = f_memory_array_resize(1, sizeof(f_range_t), (void **) &found->depth[depth].array[position].content.array, &found->depth[depth].array[position].content.used, &found->depth[depth].array[position].content.size);
            if (F_status_is_error(state->status)) break;
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
            state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
            if (F_status_is_error(state->status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          line_start = range->start + 1;
          graph_first = 0x1;

          if (!depth) {
            state->status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(state->status)) break;

            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
            f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
            f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

            if (range->start >= buffer.used) {
              state->status = F_okay_eos;
            } else if (range->start > range->stop) {
              state->status = F_okay_stop;
            }
            else {
              state->status = F_fss_found_content;
            }

            return;
          }

          --depth;
        }
        else {

          // No valid object close found, seek until EOL.
          while (range->start <= range->stop && range->start < buffer.used) {

            if (state->interrupt) {
              state->interrupt((void *) state, 0);
              if (F_status_set_fine(state->status) == F_interrupt) break;
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
              if (graph_first == 0x2) {
                state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
                if (F_status_is_error(state->status)) break;

                delimits->array[delimits->used++] = comment_delimit;
              }

              newline_last = range->start;
              line_start = range->start + 1;
              graph_first = 0x1;

              break;
            }

            position_previous = range->start;

            state->status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(state->status)) break;
          } // while

          if (F_status_is_error(state->status)) break;

          if (depth) {
            if (range->start >= buffer.used || range->start > range->stop) {
              delimits->used = delimits_used;
              comments->used = comments_used;

              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
              f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

              state->status = (range->start >= buffer.used) ? F_end_not_nest_eos : F_end_not_nest_stop;

              return;
            }
          }
          else {
            if (range->start >= buffer.used || range->start > range->stop) {
              delimits->used = delimits_used;
              comments->used = comments_used;

              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
              f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
              f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

              state->status = (range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop;

              return;
            }
          }
        }
      }
      else if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment_s.string[0]) {
        position = newline_last + 1;

        f_fss_seek_to_eol(buffer, range, state);
        if (F_status_is_error(state->status)) break;

        state->status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &comments->array, &comments->used, &comments->size);
        if (F_status_is_error(state->status)) break;

        if (range->start > range->stop || range->start >= buffer.used) {
          --range->start;
        }
        else {
          if (graph_first == 0x2) {
            state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
            if (F_status_is_error(state->status)) break;

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
          if (f_fss_is_space(buffer, *range, state) == F_false) {
            if (F_status_is_error(state->status)) break;

            graph_first = 0x0;
          }
        }

        state->status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(state->status)) break;

        if (range->start >= buffer.used || range->start > range->stop) break;

        continue;
      }

      position_previous = range->start;

      state->status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(state->status)) break;
    } // while

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &positions_start.array, &positions_start.used, &positions_start.size);
    f_memory_array_resize(0, sizeof(f_range_t), (void **) &objects.array, &objects.used, &objects.size);
    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &slashes.array, &slashes.used, &slashes.size);

    delimits->used = delimits_used;
    comments->used = comments_used;

    if (F_status_is_error(state->status)) return;

    if (range->start > range->stop) {
      state->status = F_status_set_error(depth ? F_end_not_nest_stop : F_end_not_stop);

      return;
    }

    state->status = F_status_set_error(depth ? F_end_not_nest_eos : F_end_not_eos);
  }
#endif // _di_fl_fss_embedded_list_content_read_

#ifndef _di_fl_fss_embedded_list_content_write_
  void fl_fss_embedded_list_content_write(const f_string_static_t content, const uint8_t complete, const f_string_static_t * const prepend, const f_ranges_t * const ignore, f_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    f_fss_skip_past_delimit(content, range, state);
    if (F_status_is_error(state->status)) return;
    if (state->status == F_data_not) return;

    if (state->status == F_okay_eos) {
      state->status = F_data_not_eos;
    }
    else if (state->status == F_okay_stop) {
      state->status = F_data_not_stop;
    }

    if (range->start > range->stop || range->start >= content.used) {
      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
        const f_status_t status = f_memory_array_increase_by(state->step_small + 2, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

        if (F_status_is_error(status)) {
          state->status = status;

          return;
        }

        destination->string[destination->used++] = f_fss_embedded_list_close_s.string[0];
        destination->string[destination->used++] = f_fss_embedded_list_close_end_s.string[0];
      }

      return;
    }

    const f_number_unsigned_t destination_used = destination->used;

    bool is_comment = F_false;
    bool ends_on_eol = F_false;
    bool has_graph = F_false;
    bool do_prepend = prepend ? F_true : F_false;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t slash_count = 0;
    f_number_unsigned_t start = 0;

    f_number_unsigned_t r = 0;

    uint8_t width = 0;

    while (range->start <= range->stop && range->start < content.used) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      if (content.string[range->start] == f_fss_slash_s.string[0] && !is_comment) {
        slash_count = 1;

        if (do_prepend) {
          state->status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(state->status)) break;

          do_prepend = F_false;
        }

        state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        if (F_status_is_error(state->status)) break;

        destination->string[destination->used++] = content.string[range->start];

        for (++range->start; range->start <= range->stop && range->start < content.used; ++range->start) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) {
              destination->used = destination_used;

              return;
            }
          }

          if (content.string[range->start] == f_fss_placeholder_s.string[0]) continue;
          if (content.string[range->start] != f_fss_slash_s.string[0]) break;

          state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

          if (F_status_is_error(state->status)) {
            destination->used = destination_used;

            return;
          }

          destination->string[destination->used++] = f_fss_slash_s.string[0];
          ++slash_count;
        } // for

        if (content.string[range->start] == f_fss_embedded_list_open_s.string[0] || content.string[range->start] == f_fss_embedded_list_close_s.string[0]) {
          start = range->start++;

          f_fss_skip_past_space(content, range, state);
          if (F_status_is_error(state->status)) break;

          if (range->start >= content.used || range->start > range->stop || content.string[range->start] == f_fss_eol_s.string[0]) {

            // Increase by total slashes + 1 embedded list open/close.
            state->status = f_memory_array_increase_by(slash_count + 2, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
            if (F_status_is_error(state->status)) break;

            if (content.string[range->start] == f_fss_embedded_list_open_s.string[0]) {
              while (--slash_count) {
                destination->string[destination->used++] = f_fss_slash_s.string[0];
              } // while
            }

            destination->string[destination->used++] = f_fss_slash_s.string[0];
            destination->string[destination->used++] = content.string[start];

            range->start = start + 1;

            private_fl_fss_basic_list_write_add_until_end(content, range, destination, state);
            if (F_status_is_error(state->status)) break;

            if (content.string[range->start] != f_fss_eol_s.string[0]) {
              has_graph = F_true;
            }

            continue;
          }

          // Increase by character at "start" and possible newline.
          state->status = f_memory_array_increase_by(state->step_small + 2, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
          if (F_status_is_error(state->status)) break;

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
          state->status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(state->status)) break;

          do_prepend = F_false;
        }

        has_graph = F_true;

        f_fss_skip_past_space(content, range, state);
        if (F_status_is_error(state->status)) break;

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
              state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
              if (F_status_is_error(state->status)) break;

              destination->string[destination->used++] = content.string[start];
              range->start = start + 1;

              continue;
            }
          }

          // Increase by slash and extended list open and possible newline.
          state->status = f_memory_array_increase_by(state->step_small + 3, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
          if (F_status_is_error(state->status)) break;

          destination->string[destination->used++] = f_fss_slash_s.string[0];
          destination->string[destination->used++] = content.string[start];

          range->start = start + 1;

          private_fl_fss_basic_list_write_add_until_end(content, range, destination, state);
          if (F_status_is_error(state->status)) break;

          continue;
        }

        state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        if (F_status_is_error(state->status)) break;

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
      else if (f_fss_is_graph(content, *range, state) == F_false) {
        if (F_status_is_error(state->status)) break;
      }
      else {
        has_graph = F_true;
      }

      if (content.string[range->start] != f_fss_placeholder_s.string[0]) {
        if (do_prepend) {
          state->status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(state->status)) break;

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

        state->status = f_memory_array_increase_by(width, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        if (F_status_is_error(state->status)) break;

        for (i = 0; i < width; ++i) {
          destination->string[destination->used++] = content.string[range->start + i];
        } // for
      }

      state->status = f_utf_buffer_increment(content, range, 1);
      if (F_status_is_error(state->status)) break;
    } // while

    if (F_status_is_error(state->status)) {
      destination->used = destination_used;

      return;
    }

    if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
      state->status = f_memory_array_increase_by(state->step_small + 3, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
      if (F_status_is_error(state->status)) return;

      if (!ends_on_eol) {
        destination->string[destination->used++] = f_fss_eol_s.string[0];
      }

      destination->string[destination->used++] = f_fss_embedded_list_close_s.string[0];
      destination->string[destination->used++] = f_fss_embedded_list_close_end_s.string[0];
    }

    if (range->start > range->stop) {
      state->status = F_okay_stop;
    }
    else if (range->start >= content.used) {
      state->status = F_okay_eos;
    }
    else {
      state->status = F_okay;
    }
  }
#endif // _di_fl_fss_embedded_list_content_write_

#ifndef _di_fl_fss_embedded_list_object_read_
  void fl_fss_embedded_list_object_read(const f_string_static_t buffer, f_range_t * const range, f_range_t * const found, f_number_unsigneds_t * const delimits, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !found || !delimits) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    const f_number_unsigned_t delimits_used = delimits->used;

    f_fss_skip_past_space(buffer, range, state);
    if (F_status_is_error(state->status)) return;
    if (state->status == F_data_not) return;

    if (state->status == F_okay_eol) {

      // Move the start position to after the EOL.
      ++range->start;
      state->status = F_fss_found_object_not;

      return;
    }

    if (state->status == F_okay_eos) {
      state->status = F_data_not_eos;

      return;
    }

    if (state->status == F_okay_stop) {
      state->status = F_data_not_stop;

      return;
    }

    // Return found nothing if this line only contains white space and delimit placeholders.
    if (buffer.string[range->start] == f_fss_eol_s.string[0]) {

      // Move the start position to after the EOL.
      ++range->start;
      state->status = F_fss_found_object_not;

      return;
    }

    // Begin the search.
    const f_number_unsigned_t begin = range->start;
    found->start = range->start;

    // Ignore all comment lines.
    if (buffer.string[range->start] == f_fss_comment_s.string[0]) {
      f_fss_seek_to_eol(buffer, range, state);

      if (F_status_is_error(state->status)) {
        delimits->used = delimits_used;

        return;
      }

      if (state->status == F_okay_eos) {
        state->status = F_data_not_eos;

        return;
      }

      if (state->status == F_okay_stop) {
        state->status = F_data_not_stop;

        return;
      }

      // Move the start position to after the EOL.
      ++range->start;
      state->status = F_fss_found_object_not;

      return;
    }

    f_number_unsigned_t start = 0;
    f_number_unsigned_t stop = 0;
    f_number_unsigned_t slash_first = 0;
    f_number_unsigned_t slash_count = 0;

    bool graph_first = F_true;

    // Identify where the object ends.
    while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol_s.string[0]) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      if (buffer.string[range->start] == f_fss_slash_s.string[0]) {
        slash_first = range->start;
        slash_count = 1;

        state->status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(state->status)) break;

        while (range->start <= range->stop && range->start < buffer.used && (buffer.string[range->start] == f_fss_placeholder_s.string[0] || buffer.string[range->start] == f_fss_slash_s.string[0])) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) break;
          }

          if (buffer.string[range->start] == f_fss_slash_s.string[0]) slash_count++;

          state->status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(state->status)) break;
        } // while

        if (F_status_is_error(state->status)) break;

        if (range->start >= buffer.used || range->start > range->stop) {
          delimits->used = delimits_used;

          if (range->start >= buffer.used) {
            found->stop = buffer.used - 1;
            state->status = F_data_not_eos;
          }
          else {
            found->stop = range->stop;
            state->status =  F_data_not_stop;
          }

          return;
        }

        if (buffer.string[range->start] == f_fss_embedded_list_open_s.string[0]) {
          graph_first = F_false;
          stop = range->start++;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (state->interrupt) {
              state->interrupt((void *) state, 0);
              if (F_status_set_fine(state->status) == F_interrupt) break;
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

            if (f_fss_is_graph(buffer, *range, state) == F_false) {
              if (F_status_is_error(state->status)) break;
            }
            else {
              break;
            }

            state->status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(state->status)) break;
          } // while

          if (range->start >= buffer.used || range->start > range->stop) {
            delimits->used = delimits_used;

            if (range->start >= buffer.used) {
              found->stop = buffer.used - 1;
              state->status = F_data_not_eos;
            }
            else {
              found->stop = range->stop;
              state->status =  F_data_not_stop;
            }

            return;
          }

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
            start = range->start;

            range->start = slash_first;

            state->status = f_memory_array_increase_by((slash_count / 2) + 1, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
            if (F_status_is_error(state->status)) break;

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {

                if (buffer.string[range->start] == f_fss_slash_s.string[0]) {
                  if (slash_count % 2 == 1) {
                    delimits->array[delimits->used++] = range->start;
                  }

                  --slash_count;
                }

                state->status = f_utf_buffer_increment(buffer, range, 1);
                if (F_status_is_error(state->status)) break;
              } // while

              if (F_status_is_error(state->status)) break;

              if (stop > begin) {
                found->stop = stop - 1;
              }
              else {
                found->start = 1;
                found->stop = 0;
              }

              range->start = start + 1;
              state->status = F_fss_found_object;

              return;
            }

            range->start = start + 1;
            state->status = F_fss_found_object_not;

            return;
          }
        }
        else if (graph_first && buffer.string[range->start] == f_fss_comment_s.string[0]) {
          graph_first = F_false;

          // Comments may only have white space before the '#', therefore only the first slash needs to be delimited.
          state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &delimits->array, &delimits->used, &delimits->size);
          if (F_status_is_error(state->status)) break;

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
        stop = range->start;

        state->status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(state->status)) break;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) break;
          }

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

          if (f_fss_is_space(buffer, *range, state) == F_false) {
            if (F_status_is_error(state->status)) break;

            break;
          }

          state->status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(state->status)) break;
        } // while

        if (F_status_is_error(state->status)) break;

        if (range->start >= buffer.used) {
          found->stop = buffer.used - 1;
          state->status = F_okay_eos;

          return;
        }

        if (range->start > range->stop) {
          found->stop = range->stop;
          state->status = F_okay_stop;

          return;
        }

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          if (stop > begin) {
            found->stop = stop - 1;
          }
          else {
            found->start = 1;
            found->stop = 0;
          }

          // Move the start position to after the EOL.
          ++range->start;
          state->status = F_fss_found_object;

          return;
        }

        continue;
      }
      else if (graph_first) {
        if (f_fss_is_space(buffer, *range, state) == F_false) {
          if (F_status_is_error(state->status)) break;

          graph_first = F_false;
        }
      }

      state->status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(state->status)) break;
    } // while

    if (F_status_is_error(state->status)) {
      delimits->used = delimits_used;

      return;
    }

    // Seek to the end of the line when no valid object is found.
    while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol_s.string[0]) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      state->status = f_utf_buffer_increment(buffer, range, 1);

      if (F_status_is_error(state->status)) {
        delimits->used = delimits_used;

        return;
      }
    } // while

    if (range->start >= buffer.used || range->start > range->stop) {
      delimits->used = delimits_used;

      if (range->start >= buffer.used) {
        found->stop = buffer.used - 1;
        state->status = F_data_not_eos;
      }
      else {
        found->stop = range->stop;
        state->status =  F_data_not_stop;
      }

      return;
    }

    state->status = f_utf_buffer_increment(buffer, range, 1);

    if (F_status_is_error(state->status)) {
      delimits->used = delimits_used;

      return;
    }

    state->status = F_fss_found_object_not;
  }
#endif // _di_fl_fss_embedded_list_object_read_

#ifndef _di_fl_fss_embedded_list_object_write_
  void fl_fss_embedded_list_object_write(const f_string_static_t object, const uint8_t complete, f_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    f_fss_skip_past_delimit(object, range, state);
    if (F_status_is_error(state->status)) return;
    if (state->status == F_data_not) return;

    if (state->status == F_okay_eos) {
      state->status = F_data_not_eos;
    }
    else if (state->status == F_okay_stop) {
      state->status = F_data_not_stop;
    }

    if (state->status == F_data_not_stop || state->status == F_data_not_eos) {
      if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
        {
          const f_status_t status = f_memory_array_increase_by(state->step_small + 2, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

          if (F_status_is_error(status)) {
            state->status = status;

            return;
          }
        }

        destination->string[destination->used++] = f_fss_embedded_list_open_s.string[0];

        if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
          destination->string[destination->used++] = f_fss_embedded_list_open_end_s.string[0];
        }
      }

      return;
    }

    // Ensure that there is room for a slash delimit, the object open character, and the end of line character.
    state->status = f_memory_array_increase_by(state->step_small + 4, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
    if (F_status_is_error(state->status)) return;

    const f_number_unsigned_t destination_used = destination->used;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t slash_count = 0;

    bool ends_on_space = F_false;

    uint8_t width = 0;

    // Find the first graph character.
    while (range->start <= range->stop && range->start < object.used) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      if (object.string[range->start] == f_fss_comment_s.string[0]) {

        // When a comment is found, escape it.
        state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        if (F_status_is_error(state->status)) break;

        destination->string[destination->used++] = f_fss_slash_s.string[0];

        break;
      }

      if (f_fss_is_graph(object, *range, state) == F_false) {
        if (F_status_is_error(state->status)) break;
      }
      else {
        break;
      }

      // Objects will not have leading white spaces, but having this does not result in an invalid object, so just write the provided spaces.
      if (object.string[range->start] != f_fss_placeholder_s.string[0]) {
        if (object.string[range->start] == f_fss_eol_s.string[0]) {
          state->status = F_status_set_error(F_okay_eol);

          break;
        }

        if (f_fss_is_space(object, *range, state) == F_false) {
          if (F_status_is_error(state->status)) break;
        }
        else {
          if (object.string[range->start] == f_fss_eol_s.string[0]) {
            state->status = F_status_set_error(F_okay_eol);

            break;
          }

          width = macro_f_utf_byte_width(object.string[range->start]);

          state->status = f_memory_array_increase_by(width, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
          if (F_status_is_error(state->status)) break;

          for (i = 0; i < width; ++i) {
            destination->string[destination->used++] = object.string[range->start + i];
          } // for
        }
      }

      state->status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(state->status)) break;
    } // while

    if (F_status_is_error(state->status)) {
      destination->used = destination_used;

      return;
    }

    while (range->start <= range->stop && range->start < object.used) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      if (object.string[range->start] == f_fss_slash_s.string[0]) {
        slash_count = 1;

        for (++range->start; range->start <= range->stop && range->start < object.used; ++range->start) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);

            if (F_status_set_fine(state->status) == F_interrupt) {
              destination->used = destination_used;

              return;
            }
          }

          if (object.string[range->start] == f_fss_placeholder_s.string[0]) continue;
          if (object.string[range->start] != f_fss_slash_s.string[0]) break;

          ++slash_count;
        } // for

        if (range->start > range->stop || range->start >= object.used) {

          // Slashes at the end of the object must be delimited to avoid delimiting the object close character.
          slash_count *= 2;
        }

        state->status = f_memory_array_increase_by(slash_count, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        if (F_status_is_error(state->status)) break;

        while (--slash_count) {
          destination->string[destination->used++] = f_fss_slash_s.string[0];
        } // while

        if (range->start > range->stop || range->start >= object.used) {
          ends_on_space = F_false;

          break;
        }
      }

      if (object.string[range->start] != f_fss_placeholder_s.string[0]) {
        if (object.string[range->start] == f_fss_eol_s.string[0]) {
          state->status = F_status_set_error(F_okay_eol);

          break;
        }

        if (f_fss_is_space(object, *range, state) == F_false) {
          if (F_status_is_error(state->status)) break;
        }
        else {
          ends_on_space = F_true;

          if (object.string[range->start] == f_fss_eol_s.string[0]) {
            state->status = F_status_set_error(F_okay_eol);

            break;
          }
        }

        width = macro_f_utf_byte_width(object.string[range->start]);

        state->status = f_memory_array_increase_by(width, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        if (F_status_is_error(state->status)) break;

        for (i = 0; i < width; ++i) {
          destination->string[destination->used++] = object.string[range->start + i];
        } // for
      }

      state->status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(state->status)) break;
    } // while

    if (F_status_is_error(state->status)) {
      destination->used = destination_used;

      return;
    }

    if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_trim_e) {
      if (complete == f_fss_complete_full_trim_e || complete == f_fss_complete_trim_e) {
        private_fl_fss_basic_list_write_object_trim(destination_used, destination, state);

        if (F_status_is_error(state->status)) {
          destination->used = destination_used;

          return;
        }

        // Prevent a space from being added post-trimming.
        ends_on_space = F_true;
      }

      if (complete != f_fss_complete_trim_e) {
        state->status = f_memory_array_increase_by(state->step_small + 3, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

        if (F_status_is_error(state->status)) {
          destination->used = destination_used;

          return;
        }

        if (!ends_on_space) {
          destination->string[destination->used++] = f_fss_space_s.string[0];
        }

        destination->string[destination->used++] = f_fss_embedded_list_open_s.string[0];

        if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
          destination->string[destination->used++] = f_fss_embedded_list_open_end_s.string[0];
        }
      }
    }

    if (range->start > range->stop) {
      state->status = F_okay_stop;
    }
    else if (range->start >= object.used) {
      state->status = F_okay_eos;
    }
    else {
      state->status = F_okay;
    }
  }
#endif // _di_fl_fss_embedded_list_object_write_

#ifdef __cplusplus
} // extern "C"
#endif
