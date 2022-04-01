#include "extended_list.h"
#include "../private-fss.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_list_object_read_
  f_status_t fl_fss_extended_list_object_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_object_t * const found, f_fss_delimits_t * const delimits) {
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

          if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) ++slash_count;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        private_macro_fl_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

        if (buffer.string[range->start] == f_fss_extended_list_open_s.string[0]) {
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
      else if (buffer.string[range->start] == f_fss_extended_list_open_s.string[0]) {
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
#endif // _di_fl_fss_extended_list_object_read_

#ifndef _di_fl_fss_extended_list_content_read_
  f_status_t fl_fss_extended_list_content_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_content_t * const found, f_fss_delimits_t * const delimits, f_fss_comments_t * const comments) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
      if (!comments) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;
    const f_array_length_t comments_used = comments->used;

    f_status_t status = f_fss_skip_past_delimit(buffer, range);
    if (F_status_is_error(status)) return status;

    private_macro_fl_fss_content_with_comments_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, (*comments), comments_used, F_none_eos, F_none_stop);

    status = f_string_ranges_increase(state.step_small, found);
    if (F_status_is_error(status)) return status;

    found->array[found->used].start = range->start;

    f_array_length_t newline_last = range->start;
    f_array_length_t slash_first = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;

    // Identify where the content ends.
    while (range->start <= range->stop && range->start < buffer.used) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      status = f_fss_skip_past_space(buffer, range);
      if (F_status_is_error(status)) break;

      if (status == F_none_eol) {
        newline_last = range->start++;

        continue;
      }

      if (status == F_none_eos || status == F_none_stop) break;

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

        // Only the first slash before a close is delimited, all others are maintained.
        // For example '}' = valid close, '\}' represents '}', '\\}' represents '\}', '\\\}' represents '\\}', '\\\\}' represents '\\\}', and so on..
        // With one or more slashes, even if delimited, this line may never designate a valid content close.
        if (buffer.string[range->start] == f_fss_extended_list_close_s.string[0]) {
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

            status = f_fss_is_space(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (range->start > range->stop || range->start >= buffer.used) break;

          if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
            macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = slash_first;

            continue;
          }
        }
        else if (buffer.string[range->start] == f_fss_comment_s.string[0]) {
          macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
          if (F_status_is_error(status)) break;

          delimits->array[delimits->used++] = slash_first;
        }

        status = f_fss_seek_to_eol(buffer, range);
        if (F_status_is_error(status)) break;

        continue;
      }

      if (buffer.string[range->start] == f_fss_extended_list_close_s.string[0]) {
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

          status = f_fss_is_space(buffer, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        if (range->start > range->stop || range->start >= buffer.used) break;

        // Found a valid content close, set stop point to last newline.
        if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          ++range->start;

          // If the last newline is the entire start, then there is no Content.
          if (newline_last == found->array[found->used].start) {
            found->array[found->used].start = 1;
            found->array[found->used++].stop = 0;

            return F_fss_found_content_not;
          }

          found->array[found->used++].stop = newline_last;

          return F_fss_found_content;
        }

        continue;
      }

      if (buffer.string[range->start] == f_fss_comment_s.string[0]) {
        start = newline_last + 1;

        status = f_fss_seek_to_eol(buffer, range);
        if (F_status_is_error(status)) break;

        macro_f_fss_comments_t_increase(status, state.step_small, (*comments))
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

      // There is no possibility of a valid content close, so seek until newline.
      status = f_fss_seek_to_eol(buffer, range);
      if (F_status_is_error(status)) break;
    } // while

    if (F_status_is_error(status)) {
      delimits->used = delimits_used;
      comments->used = comments_used;

      return status;
    }

    return F_fss_found_content_not;
  }
#endif // _di_fl_fss_extended_list_content_read_

#ifndef _di_fl_fss_extended_list_object_write_
  f_status_t fl_fss_extended_list_object_write(const f_string_static_t object, const uint8_t complete, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
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

        destination->string[destination->used++] = f_fss_extended_list_open_s.string[0];

        if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
          destination->string[destination->used++] = f_fss_extended_list_open_end_s.string[0];
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

      destination->string[destination->used++] = f_fss_extended_list_open_s.string[0];

      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
        destination->string[destination->used++] = f_fss_extended_list_open_end_s.string[0];
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
#endif // _di_fl_fss_extended_list_object_write_

#ifndef _di_fl_fss_extended_list_content_write_
  f_status_t fl_fss_extended_list_content_write(const f_string_static_t content, const uint8_t complete, const f_string_static_t * const prepend, const f_string_ranges_t * const ignore, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
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

        destination->string[destination->used++] = f_fss_extended_list_close_s.string[0];
        destination->string[destination->used++] = f_fss_extended_list_close_end_s.string[0];
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

        if (content.string[range->start] == f_fss_extended_list_close_s.string[0]) {
          start = range->start++;

          status = f_fss_skip_past_space(content, range);
          if (F_status_is_error(status)) break;

          if (has_graph) {
            // Do nothing.
          }
          else if (content.string[range->start] == f_fss_eol_s.string[0] || range->start >= content.used || range->start > range->stop) {

            // increase by total slashes + 1 and extended list close.
            status = f_string_dynamic_increase_by(2, destination);
            if (F_status_is_error(status)) break;

            destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
            destination->string[destination->used++] = f_fss_extended_list_close_s.string[0];

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
      else if (!has_graph && content.string[range->start] == f_fss_extended_list_close_s.string[0] && !is_comment) {
        start = range->start++;

        if (do_prepend) {
          status = f_string_dynamic_append(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        has_graph = F_true;

        status = f_fss_skip_past_space(content, range);
        if (F_status_is_error(status)) break;

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
              status = f_string_dynamic_increase(state.step_large, destination);
              if (F_status_is_error(status)) break;

              destination->string[destination->used++] = content.string[start];
              range->start = start + 1;

              continue;
            }
          }

          // Increase by slash and extended list close.
          status = f_string_dynamic_increase_by(2, destination);
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

      destination->string[destination->used++] = f_fss_extended_list_close_s.string[0];
      destination->string[destination->used++] = f_fss_extended_list_close_end_s.string[0];
    }

    if (range->start > range->stop) {
      return F_none_stop;
    }

    if (range->start >= content.used) {
      return F_none_eos;
    }

    return F_none;
  }
#endif // _di_fl_fss_extended_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
