#include "basic_list.h"
#include "../private-fss.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_list_content_read_
  f_status_t fl_fss_basic_list_content_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_content_t * const found, f_fss_delimits_t * const delimits, f_fss_comments_t * const comments) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
      if (!comments) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;
    const f_array_length_t comments_used = comments->used;

    f_status_t status = f_fss_skip_past_delimit(state, buffer, range);
    if (F_status_is_error(status)) return status;

    private_macro_fl_fss_content_with_comments_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, F_none_eos, F_none_stop);

    status = f_string_ranges_increase(state.step_small, found);
    if (F_status_is_error(status)) return status;

    const f_number_unsigned_t begin = range->start;
    found->array[found->used].start = range->start;

    f_array_length_t newline_last = range->start;
    f_array_length_t slash_first = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;
    f_array_length_t comment_delimit = 0;

    uint8_t graph_first = 0x1; // 0x0 = false, 0x1 = true, 0x2 = false, but there is a delimited comment, comment_delimit is set.

    // Identify where the content ends.
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
          status = f_array_lengths_increase(state.step_small, delimits);
          if (F_status_is_error(status)) break;

          delimits->array[delimits->used++] = comment_delimit;
        }

        newline_last = range->start;
        graph_first = 0x1;
        ++range->start;

        continue;
      }

      if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
        slash_first = range->start;
        slash_count = 1;

        for (++range->start; range->start <= range->stop && range->start < buffer.used; ++range->start) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (buffer.string[range->start] == f_fss_delimit_placeholder_s.string[0]) continue;
          if (buffer.string[range->start] != f_fss_delimit_slash_s.string[0]) break;

          ++slash_count;
        } // for

        if (range->start > range->stop || range->start >= buffer.used) break;

        if (buffer.string[range->start] == f_fss_basic_list_open_s.string[0]) {
          graph_first = 0x0;
          ++range->start;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (state.interrupt) {
              status = state.interrupt((void *) &state, 0);

              if (F_status_set_fine(status) == F_interrupt) {
                status = F_status_set_error(F_interrupt);

                break;
              }
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

            status = f_fss_is_space(state, buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (range->start > range->stop || range->start >= buffer.used) break;

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
            start = range->start;
            range->start = slash_first;

            if (slash_count % 2 == 0) {
              found->array[found->used++].stop = newline_last;
              range->start = newline_last + 1;

              return F_fss_found_content;
            }

            status = f_array_lengths_increase_by((slash_count / 2) + 1, delimits);
            if (F_status_is_error(status)) break;

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

            if (graph_first == 0x2) {
              status = f_array_lengths_increase(state.step_small, delimits);
              if (F_status_is_error(status)) break;

              delimits->array[delimits->used++] = comment_delimit;
            }

            graph_first = 0x1;
            range->start = start + 1;
          }
        }
        else if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment_s.string[0]) {
          graph_first = 0x2;
          comment_delimit = slash_first;
          ++range->start;
        }

        continue;
      }

      if (buffer.string[range->start] == f_fss_basic_list_open_s.string[0]) {
        ++range->start;
        graph_first = 0x0;

        while (range->start <= range->stop && range->start < buffer.used) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

          status = f_fss_is_space(state, buffer, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        if (range->start > range->stop || range->start >= buffer.used) break;

        // Found a valid object, set stop point to last newline.
        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {

          if (newline_last == found->array[found->used].start && buffer.string[found->array[found->used].start] != f_fss_eol_s.string[0]) {
            range->start = newline_last;

            return F_fss_found_content_not;
          }
          else {
            range->start = newline_last + 1;
            found->array[found->used++].stop = newline_last;
          }

          return F_fss_found_content;
        }

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          if (graph_first == 0x2) {
            status = f_array_lengths_increase(state.step_small, delimits);
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          graph_first = 0x1;
        }

        continue;
      }

      if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment_s.string[0]) {

        // The newline_last is initialized to the range->start, which may not actually be a new line.
        if (buffer.string[newline_last] == f_string_eol_s.string[0]) {
          start = newline_last + 1;
        }
        else {
          start = newline_last;
        }

        status = f_fss_seek_to_eol(state, buffer, range);
        if (F_status_is_error(status)) break;

        status = f_string_ranges_increase(state.step_small, comments);
        if (F_status_is_error(status)) break;

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

      if (graph_first == 0x1) {
        status = f_fss_is_space(state, buffer, *range);
        if (F_status_is_error(status)) break;

        if (status == F_false) {
          graph_first = 0x0;
        }
      }

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) break;
    } // while

    if (F_status_is_error(status)) {
      delimits->used = delimits_used;
      comments->used = comments_used;

      return status;
    }

    if (range->start >= buffer.used) {
      found->array[found->used].stop = buffer.used - 1;

      return F_none_eos;
    }

    if (range->start > range->stop) {
      found->array[found->used].stop = range->stop;

      return F_none_stop;
    }

    if (range->start > begin) {
      found->array[found->used++].stop = range->start - 1;
    }
    else {
      found->array[found->used].start = 1;
      found->array[found->used++].stop = 0;
    }

    return F_fss_found_content;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifndef _di_fl_fss_basic_list_content_write_
  f_status_t fl_fss_basic_list_content_write(const f_string_static_t content, const uint8_t complete, const f_string_static_t *prepend, f_state_t state, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(state, content, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_stop || status == F_none_eos) {
      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
        const f_status_t status_allocation = f_string_dynamic_increase(state.step_large, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_basic_list_close_s.string[0];
      }

      if (status == F_none_stop) return F_data_not_stop;

      return F_data_not_eos;
    }

    // Ensure that there is room for a slash delimit and possibly the end of content character.
    status = f_string_dynamic_increase_by(state.step_small + 3, destination);
    if (F_status_is_error(status)) return status;

    const f_array_length_t destination_used = destination->used;

    bool is_comment = F_false;
    bool has_graph = F_false;
    bool do_prepend = prepend ? F_true : F_false;

    f_array_length_t i = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;

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
        has_graph = F_true;

        for (++range->start; range->start <= range->stop && range->start < content.used; ++range->start) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              destination->used = destination_used;

              return F_status_set_error(F_interrupt);
            }
          }

          if (content.string[range->start] == f_fss_delimit_placeholder_s.string[0]) continue;
          if (content.string[range->start] != f_fss_delimit_slash_s.string[0]) break;

          status = f_string_dynamic_increase(state.step_large, destination);

          if (F_status_is_error(status)) {
            destination->used = destination_used;

            return status;
          }

          destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          ++slash_count;
        } // for

        if (content.string[range->start] == f_fss_basic_list_open_s.string[0]) {
          start = range->start++;

          status = f_fss_skip_past_space(state, content, range);
          if (F_status_is_error(status)) break;

          if (content.string[range->start] == f_fss_eol_s.string[0] || range->start >= content.used || range->start > range->stop) {

            // Increase by total slashes + 1, along with the basic list open and possible newline.
            status = f_string_dynamic_increase_by(slash_count + 3, destination);
            if (F_status_is_error(status)) break;

            while (--slash_count) {
              destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
            } // while

            destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
            destination->string[destination->used++] = f_fss_basic_list_open_s.string[0];

            range->start = start + 1;

            status = private_fl_fss_basic_list_write_add_until_end(content, state, range, destination);
            if (F_status_is_error(status)) break;

            continue;
          }

          status = f_string_dynamic_increase(state.step_large, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = f_fss_basic_list_open_s.string[0];
          range->start = start + 1;

          continue;
        }
      }
      else if (content.string[range->start] == f_fss_basic_list_open_s.string[0] && !is_comment) {
        start = range->start++;

        if (do_prepend) {
          status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        has_graph = F_true;

        status = f_fss_skip_past_space(state, content, range);
        if (F_status_is_error(status)) break;

        if (content.string[range->start] == f_fss_eol_s.string[0] || range->start >= content.used || range->start > range->stop) {

          // Increase by slash and basic list open and possible newline.
          status = f_string_dynamic_increase_by(state.step_small + 3, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          destination->string[destination->used++] = f_fss_basic_list_open_s.string[0];

          range->start = start + 1;

          status = private_fl_fss_basic_list_write_add_until_end(content, state, range, destination);
          if (F_status_is_error(status)) break;

          continue;
        }

        status = f_string_dynamic_increase(state.step_large, destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = f_fss_basic_list_open_s.string[0];
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
      else {
        status = f_fss_is_graph(state, content, *range);

        if (status == F_true) {
          has_graph = F_true;
        }
        else if (F_status_is_error(status)) {
          break;
        }
      }

      if (content.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
        if (do_prepend) {
          status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        if (content.string[range->start] == f_fss_eol_s.string[0] && prepend) {
          do_prepend = F_true;
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
      destination->used = destination_used;

      return status;
    }

    if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
      status = f_string_dynamic_increase(state.step_large, destination);

      if (F_status_is_error(status)) {
        destination->used = destination_used;

        return status;
      }

      // Check to see if a newline exists, at the end.
      if (destination->used) {
        for (i = destination->used - 1; i > 0; --i) {
          if (destination->string[i] != f_fss_delimit_placeholder_s.string[0]) break;
        } // for
      }

      if (!destination->used || destination->string[i] != f_fss_eol_s.string[0]) {
        destination->string[destination->used++] = f_fss_basic_list_close_s.string[0];
      }
    }

    if (range->start > range->stop) return F_none_stop;
    if (range->start >= content.used) return F_none_eos;

    return F_none;
  }
#endif // _di_fl_fss_basic_list_content_write_

#ifndef _di_fl_fss_basic_list_object_read_
  f_status_t fl_fss_basic_list_object_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_object_t * const found, f_fss_delimits_t * const delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    f_status_t status = f_fss_skip_past_space(state, buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eol) {

      // Move the start position to after the EOL.
      ++range->start;

      return F_fss_found_object_not;
    }

    if (status == F_none_eos) return F_data_not_eos;
    if (status == F_none_stop) return F_data_not_stop;

    // Begin the search.
    const f_number_unsigned_t begin = range->start;
    found->start = range->start;

    // Ignore all comment lines.
    if (buffer.string[range->start] == f_fss_comment_s.string[0]) {

      status = f_fss_seek_to_eol(state, buffer, range);
      if (F_status_is_error(status)) return status;

      if (status == F_none_eos) return F_data_not_eos;
      if (status == F_none_stop) return F_data_not_stop;

      // Move the start position to after the EOL.
      ++range->start;

      return F_fss_found_object_not;
    }

    f_array_length_t slash_first = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;
    f_array_length_t stop = 0;

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

        for (++range->start; range->start <= range->stop && range->start < buffer.used; ++range->start) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (buffer.string[range->start] == f_fss_delimit_placeholder_s.string[0]) {
            continue;
          } else if (buffer.string[range->start] != f_fss_delimit_slash_s.string[0]) {
            break;
          }

          ++slash_count;
        } // for

        private_macro_fl_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

        if (buffer.string[range->start] == f_fss_basic_list_open_s.string[0]) {
          graph_first = F_false;
          stop = range->start;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (state.interrupt) {
              status = state.interrupt((void *) &state, 0);

              if (F_status_set_fine(status) == F_interrupt) {
                status = F_status_set_error(F_interrupt);

                break;
              }
            }

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

            status = f_fss_is_space(state, buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          private_macro_fl_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
            start = range->start;

            range->start = slash_first;

            status = f_array_lengths_increase_by((slash_count / 2) + 1, delimits);
            if (F_status_is_error(status)) break;

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {

                if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
                  if (slash_count % 2 == 1) {
                    delimits->array[delimits->used] = range->start;
                    ++delimits->used;
                  }

                  --slash_count;
                }

                status = f_utf_buffer_increment(buffer, range, 1);

                if (F_status_is_error(status)) {
                  delimits->used = delimits_used;

                  return status;
                }
              } // while

              if (stop > begin) {
                found->stop = stop - 1;
              }
              else {
                found->start = 1;
                found->stop = 0;
              }

              range->start = start + 1;

              return F_fss_found_object;
            }

            range->start = start + 1;

            return F_fss_found_object_not;
          }
        }
        else if (graph_first && buffer.string[range->start] == f_fss_comment_s.string[0]) {
          graph_first = F_false;

          // Comments may only have white space before the '#', therefore only the first slash needs to be delimited.
          status = f_array_lengths_increase(state.step_small, delimits);
          if (F_status_is_error(status)) break;

          delimits->array[delimits->used++] = slash_first;
          ++range->start;
        }
        else {
          graph_first = F_false;
        }

        continue;
      }

      if (buffer.string[range->start] == f_fss_basic_list_open_s.string[0]) {
        graph_first = F_false;
        stop = range->start;

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

          status = f_fss_is_space(state, buffer, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        private_macro_fl_fss_object_return_on_overflow_delimited((buffer), (*range), (*found), F_none_eos, F_none_stop);

        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          if (stop > begin) {
            found->stop = stop - 1;
          }
          else {
            found->start = 1;
            found->stop = 0;
          }

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;

          return F_fss_found_object;
        }

        continue;
      }
      else if (graph_first) {
        status = f_fss_is_space(state, buffer, *range);
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

    if (status == F_none_eos) return F_data_not_eos;
    if (status == F_none_stop) return F_data_not_stop;

    // seek to the end of the line when no valid object is found.
    status = f_fss_seek_to_eol(state, buffer, range);

    // move the start position to after the EOL.
    ++range->start;

    return F_fss_found_object_not;
  }
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_object_write_
  f_status_t fl_fss_basic_list_object_write(const f_string_static_t object, const uint8_t complete, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(state, object, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_stop || status == F_none_eos) {
      if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
        {
          const f_status_t status_allocation = f_string_dynamic_increase_by(state.step_small + 2, destination);
          if (F_status_is_error(status_allocation)) return status_allocation;
        }

        destination->string[destination->used++] = f_fss_basic_list_open_s.string[0];

        if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
          destination->string[destination->used++] = f_fss_basic_list_open_end_s.string[0];
        }
      }

      if (status == F_none_stop) return F_data_not_stop;

      return F_data_not_eos;
    }

    const f_array_length_t destination_used = destination->used;

    f_array_length_t i = 0;
    f_array_length_t slash_count = 0;

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

      status = f_fss_is_graph(state, object, *range);
      if (F_status_is_error(status)) break;

      if (status == F_true) break;

      // Objects will not have leading white spaces, but having this does not result in an invalid object, so just write the provided spaces.
      if (object.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
        if (object.string[range->start] == f_fss_eol_s.string[0]) {
          status = F_status_set_error(F_none_eol);

          break;
        }

        status = f_fss_is_space(state, object, *range);
        if (F_status_is_error(status)) break;

        if (status == F_true) {
          if (object.string[range->start] == f_fss_eol_s.string[0]) {
            status = F_status_set_error(F_none_eol);

            break;
          }

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
      destination->used = destination_used;

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

        if (range->start > range->stop || range->start >= object.used) break;
      }

      if (object.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
        if (object.string[range->start] == f_fss_eol_s.string[0]) {
          status = F_status_set_error(F_none_eol);

          break;
        }

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
      destination->used = destination_used;

      return status;
    }

    if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
      if (complete == f_fss_complete_full_trim_e) {
        status = private_fl_fss_basic_list_write_object_trim(destination_used, state, destination);

        if (F_status_is_error(status)) {
          destination->used = destination_used;

          return status;
        }
      }

      status = f_string_dynamic_increase(state.step_small + 2, destination);

      if (F_status_is_error(status)) {
        destination->used = destination_used;

        return status;
      }

      destination->string[destination->used++] = f_fss_basic_list_open_s.string[0];

      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
        destination->string[destination->used++] = f_fss_basic_list_open_end_s.string[0];
      }
    }

    if (range->start > range->stop) return F_none_stop;
    if (range->start >= object.used) return F_none_eos;

    return F_none;
  }
#endif // _di_fl_fss_basic_list_object_write_

#ifdef __cplusplus
} // extern "C"
#endif
