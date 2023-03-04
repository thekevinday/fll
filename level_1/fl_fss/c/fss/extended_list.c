#include "extended_list.h"
#include "../private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_list_content_read_
  void fl_fss_extended_list_content_read(const f_string_static_t buffer, f_string_range_t * const range, f_fss_content_t * const found, f_fss_delimits_t * const delimits, f_fss_comments_t * const comments, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !found || !delimits || !comments) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;
    const f_array_length_t comments_used = comments->used;

    f_fss_skip_past_delimit(buffer, range, state);
    if (F_status_is_error(state->status)) return;

    if (range->start >= buffer.used || range->start > range->stop) {
      delimits->used = delimits_used;
      comments->used = comments_used;

      if (range->start >= buffer.used) {
        found->array[found->used].stop = buffer.used - 1;
        state->status = F_none_eos;
      }
      else {
        found->array[found->used].stop = range->stop;
        state->status = F_none_stop;
      }

      return;
    }

    state->status = f_string_ranges_increase(state->step_small, found);
    if (F_status_is_error(state->status)) return;

    found->array[found->used].start = range->start;

    f_array_length_t newline_last = range->start;
    f_array_length_t slash_first = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;

    // Identify where the content ends.
    while (range->start <= range->stop && range->start < buffer.used) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      f_fss_skip_past_space(buffer, range, state);
      if (F_status_is_error(state->status)) break;

      if (state->status == F_none_eol) {
        newline_last = range->start++;

        continue;
      }

      if (state->status == F_none_eos || state->status == F_none_stop) break;

      if (buffer.string[range->start] == f_fss_slash_s.string[0]) {
        slash_first = range->start;
        slash_count = 1;

        for (++range->start; range->start <= range->stop && range->start < buffer.used; ++range->start) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) break;
          }

          if (buffer.string[range->start] == f_fss_placeholder_s.string[0]) continue;
          if (buffer.string[range->start] != f_fss_slash_s.string[0]) break;

          ++slash_count;
        } // for

        if (range->start > range->stop || range->start >= buffer.used) break;

        // Only the first slash before a close is delimited, all others are maintained.
        // For example '}' = valid close, '\}' represents '}', '\\}' represents '\}', '\\\}' represents '\\}', '\\\\}' represents '\\\}', and so on..
        // With one or more slashes, even if delimited, this line may never designate a valid content close.
        if (buffer.string[range->start] == f_fss_extended_list_close_s.string[0]) {
          ++range->start;

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

          if (range->start > range->stop || range->start >= buffer.used) break;

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
            state->status = f_array_lengths_increase(state->step_small, delimits);
            if (F_status_is_error(state->status)) break;

            delimits->array[delimits->used++] = slash_first;

            continue;
          }
        }
        else if (buffer.string[range->start] == f_fss_comment_s.string[0]) {
          state->status = f_array_lengths_increase(state->step_small, delimits);
          if (F_status_is_error(state->status)) break;

          delimits->array[delimits->used++] = slash_first;
        }

        f_fss_seek_to_eol(buffer, range, state);
        if (F_status_is_error(state->status)) break;

        continue;
      }

      if (buffer.string[range->start] == f_fss_extended_list_close_s.string[0]) {
        ++range->start;

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

        if (range->start > range->stop || range->start >= buffer.used) break;

        // Found a valid content close, set stop point to last newline.
        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          ++range->start;

          // If the last newline is the entire start, then there is no Content.
          if (newline_last == found->array[found->used].start) {
            found->array[found->used].start = 1;
            found->array[found->used++].stop = 0;

            state->status = F_fss_found_content_not;

            return;
          }

          found->array[found->used++].stop = newline_last;
          state->status = F_fss_found_content;

          return;
        }

        continue;
      }

      if (buffer.string[range->start] == f_fss_comment_s.string[0]) {
        start = newline_last + 1;

        f_fss_seek_to_eol(buffer, range, state);
        if (F_status_is_error(state->status)) break;

        state->status = f_string_ranges_increase(state->step_small, comments);
        if (F_status_is_error(state->status)) break;

        if (range->start > range->stop || range->start >= buffer.used) {
          --range->start;
        }
        else {
          newline_last = range->start;
        }

        comments->array[comments->used].start = start;
        comments->array[comments->used++].stop = range->start++;

        continue;
      }

      // There is no possibility of a valid content close, so seek until newline.
      f_fss_seek_to_eol(buffer, range, state);
      if (F_status_is_error(state->status)) break;
    } // while

    if (F_status_is_error(state->status)) {
      delimits->used = delimits_used;
      comments->used = comments_used;

      return;
    }

    state->status = F_fss_found_content_not;
  }
#endif // _di_fl_fss_extended_list_content_read_

#ifndef _di_fl_fss_extended_list_content_write_
  void fl_fss_extended_list_content_write(const f_string_static_t content, const uint8_t complete, const f_string_static_t * const prepend, const f_string_ranges_t * const ignore, f_string_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    f_fss_skip_past_delimit(content, range, state);
    if (F_status_is_error(state->status)) return;

    if (state->status == F_none_eos) {
      state->status = F_data_not_eos;
    }
    else if (state->status == F_none_stop) {
      state->status = F_data_not_stop;
    }

    if (range->start > range->stop || range->start >= content.used) {
      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
        {
          const f_status_t status = f_string_dynamic_increase_by(state->step_small + 2, destination);

          if (F_status_is_error(status)) {
            state->status = status;

            return;
          }
        }

        destination->string[destination->used++] = f_fss_extended_list_close_s.string[0];
        destination->string[destination->used++] = f_fss_extended_list_close_end_s.string[0];
      }

      return;
    }

    // Ensure that there is room for a slash delimit and possibly the end of content characters.
    state->status = f_string_dynamic_increase_by(state->step_small + 4, destination);
    if (F_status_is_error(state->status)) return;

    const f_array_length_t destination_used = destination->used;

    bool is_comment = F_false;
    bool ends_on_eol = F_false;
    bool has_graph = F_false;
    bool do_prepend = prepend ? F_true : F_false;

    f_array_length_t i = 0;
    f_array_length_t r = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;

    uint8_t width = 0;

    while (range->start <= range->stop && range->start < content.used) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      if (content.string[range->start] == f_fss_slash_s.string[0] && !is_comment) {
        slash_count = 1;

        if (do_prepend) {
          state->status = f_string_dynamic_increase_by(state->step_small + prepend->used, destination);
          if (F_status_is_error(state->status)) break;

          state->status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(state->status)) break;

          do_prepend = F_false;
        }
        else {
          state->status = f_string_dynamic_increase(state->step_large, destination);
          if (F_status_is_error(state->status)) break;
        }

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

          state->status = f_string_dynamic_increase(state->step_large, destination);

          if (F_status_is_error(state->status)) {
            destination->used = destination_used;

            return;
          }

          destination->string[destination->used++] = f_fss_slash_s.string[0];
          ++slash_count;
        } // for

        if (content.string[range->start] == f_fss_extended_list_close_s.string[0]) {
          start = range->start++;

          f_fss_skip_past_space(content, range, state);
          if (F_status_is_error(state->status)) break;

          if (has_graph) {
            // Do nothing.
          }
          else if (content.string[range->start] == f_fss_eol_s.string[0] || range->start >= content.used || range->start > range->stop) {
            state->status = f_string_dynamic_increase_by(state->step_small + 2, destination);
            if (F_status_is_error(state->status)) break;

            destination->string[destination->used++] = f_fss_slash_s.string[0];
            destination->string[destination->used++] = f_fss_extended_list_close_s.string[0];

            range->start = start + 1;

            private_fl_fss_basic_list_write_add_until_end(content, range, destination, state);
            if (F_status_is_error(state->status)) break;

            if (content.string[range->start] != f_fss_eol_s.string[0]) {
              has_graph = F_true;
            }

            continue;
          }

          // Increase by character at "start" and possible newline.
          state->status = f_string_dynamic_increase_by(state->step_small + 2, destination);
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
      else if (!has_graph && content.string[range->start] == f_fss_extended_list_close_s.string[0] && !is_comment) {
        start = range->start++;

        if (do_prepend) {
          state->status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(state->status)) break;

          do_prepend = F_false;
        }

        has_graph = F_true;

        f_fss_skip_past_space(content, range, state);
        if (F_status_is_error(state->status)) break;

        if (content.string[range->start] == f_fss_eol_s.string[0] || range->start >= content.used || range->start > range->stop) {

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
              state->status = f_string_dynamic_increase(state->step_large, destination);
              if (F_status_is_error(state->status)) break;

              destination->string[destination->used++] = content.string[start];
              range->start = start + 1;

              continue;
            }
          }

          // Increase by slash and extended list close.
          state->status = f_string_dynamic_increase_by(state->step_small + 2, destination);
          if (F_status_is_error(state->status)) break;

          destination->string[destination->used++] = f_fss_slash_s.string[0];
          destination->string[destination->used++] = content.string[start];

          range->start = start + 1;

          private_fl_fss_basic_list_write_add_until_end(content, range, destination, state);
          if (F_status_is_error(state->status)) break;

          continue;
        }

        state->status = f_string_dynamic_increase(state->step_large, destination);
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

        state->status = f_string_dynamic_increase_by(width, destination);
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
      state->status = f_string_dynamic_increase_by(state->step_small + 3, destination);
      if (F_status_is_error(state->status)) {
        destination->used = destination_used;

        return;
      }

      if (!ends_on_eol) {
        destination->string[destination->used++] = f_fss_eol_s.string[0];
      }

      destination->string[destination->used++] = f_fss_extended_list_close_s.string[0];
      destination->string[destination->used++] = f_fss_extended_list_close_end_s.string[0];
    }

    if (range->start > range->stop) {
      state->status = F_none_stop;
    }
    else if (range->start >= content.used) {
      state->status = F_none_eos;
    }
    else {
      state->status = F_none;
    }
  }
#endif // _di_fl_fss_extended_list_content_write_

#ifndef _di_fl_fss_extended_list_object_read_
  void fl_fss_extended_list_object_read(const f_string_static_t buffer, f_string_range_t * const range, f_fss_object_t * const found, f_fss_delimits_t * const delimits, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !found || !delimits) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    f_fss_skip_past_space(buffer, range, state);
    if (F_status_is_error(state->status)) return;

    if (state->status == F_none_eol) {

      // Move the start position to after the EOL.
      ++range->start;
      state->status = F_fss_found_object_not;

      return;
    }

    if (state->status == F_none_eos) {
      state->status = F_data_not_eos;

      return;
    }

    if (state->status == F_none_stop) {
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
    found->start = range->start;

    // Ignore all comment lines.
    if (buffer.string[range->start] == f_fss_comment_s.string[0]) {
      f_fss_seek_to_eol(buffer, range, state);

      if (F_status_is_error(state->status)) {
        delimits->used = delimits_used;

        return;
      }

      if (state->status == F_none_eos) {
        state->status = F_data_not_eos;

        return;
      }

      if (state->status == F_none_stop) {
        state->status = F_data_not_stop;

        return;
      }

      // Move the start position to after the EOL.
      ++range->start;
      state->status = F_fss_found_object_not;

      return;
    }

    f_array_length_t start = 0;
    f_array_length_t stop = 0;
    f_array_length_t slash_first = 0;
    f_array_length_t slash_count = 0;

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

          if (buffer.string[range->start] == f_fss_slash_s.string[0]) ++slash_count;

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

        if (buffer.string[range->start] == f_fss_extended_list_open_s.string[0]) {
          graph_first = F_false;
          stop = range->start++ - 1;

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

            state->status = f_array_lengths_increase_by((slash_count / 2) + 1, delimits);
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

              found->stop = stop;
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
          state->status = f_array_lengths_increase(state->step_small, delimits);
          if (F_status_is_error(state->status)) break;

          delimits->array[delimits->used++] = slash_first;
          ++range->start;
        }
        else {
          graph_first = F_false;
        }

        continue;
      }
      else if (buffer.string[range->start] == f_fss_extended_list_open_s.string[0]) {
        graph_first = F_false;
        stop = range->start - 1;

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
          state->status = F_none_eos;

          return;
        }

        if (range->start > range->stop) {
          found->stop = range->stop;
          state->status = F_none_stop;

          return;
        }

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          found->stop = stop;

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
#endif // _di_fl_fss_extended_list_object_read_

#ifndef _di_fl_fss_extended_list_object_write_
  void fl_fss_extended_list_object_write(const f_string_static_t object, const uint8_t complete, f_string_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    f_fss_skip_past_delimit(object, range, state);
    if (F_status_is_error(state->status)) return;

    if (state->status == F_none_eos) {
      state->status = F_data_not_eos;
    }
    else if (state->status == F_none_stop) {
      state->status = F_data_not_stop;
    }

    if (state->status == F_data_not_stop || state->status == F_data_not_eos) {
      if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
        {
          const f_status_t status = f_string_dynamic_increase_by(state->step_small + 2, destination);

          if (F_status_is_error(status)) {
            state->status = status;

            return;
          }
        }

        destination->string[destination->used++] = f_fss_extended_list_open_s.string[0];

        if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
          destination->string[destination->used++] = f_fss_extended_list_open_end_s.string[0];
        }
      }

      return;
    }

    // Ensure that there is room for a slash delimit, the object open character, and the end of line character.
    state->status = f_string_dynamic_increase_by(state->step_small + 4, destination);
    if (F_status_is_error(state->status)) return;

    const f_array_length_t destination_used = destination->used;

    f_array_length_t i = 0;
    f_array_length_t slash_count = 0;

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
        state->status = f_string_dynamic_increase(state->step_large, destination);
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
          state->status = F_status_set_error(F_none_eol);

          break;
        }

        if (f_fss_is_space(object, *range, state) == F_false) {
          if (F_status_is_error(state->status)) break;
        }
        else {
          if (object.string[range->start] == f_fss_eol_s.string[0]) {
            state->status = F_status_set_error(F_none_eol);

            break;
          }

          width = macro_f_utf_byte_width(object.string[range->start]);

          state->status = f_string_dynamic_increase_by(width, destination);
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

        state->status = f_string_dynamic_increase_by(slash_count, destination);
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
          state->status = F_status_set_error(F_none_eol);

          break;
        }

        if (f_fss_is_space(object, *range, state) == F_false) {
          if (F_status_is_error(state->status)) break;
        }
        else {
          ends_on_space = F_true;

          if (object.string[range->start] == f_fss_eol_s.string[0]) {
            state->status = F_status_set_error(F_none_eol);

            break;
          }
        }

        width = macro_f_utf_byte_width(object.string[range->start]);

        state->status = f_string_dynamic_increase_by(width, destination);
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
        state->status = f_string_dynamic_increase_by(state->step_small + 3, destination);

        if (F_status_is_error(state->status)) {
          destination->used = destination_used;

          return;
        }

        if (!ends_on_space) {
          destination->string[destination->used++] = f_fss_space_s.string[0];
        }

        destination->string[destination->used++] = f_fss_extended_list_open_s.string[0];

        if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
          destination->string[destination->used++] = f_fss_extended_list_open_end_s.string[0];
        }
      }
    }

    if (range->start > range->stop) {
      state->status = F_none_stop;
    }
    else if (range->start >= object.used) {
      state->status = F_none_eos;
    }
    else {
      state->status = F_none;
    }
  }
#endif // _di_fl_fss_extended_list_object_write_

#ifdef __cplusplus
} // extern "C"
#endif
