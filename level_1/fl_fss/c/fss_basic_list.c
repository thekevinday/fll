#include "fss_basic.h"
#include "private-fss.h"
#include "private-fss_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  f_status_t fl_fss_basic_list_object_read(const f_string_static_t buffer, f_state_t state, f_string_range_t *range, f_fss_object_t *found, f_fss_delimits_t *delimits) {
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
      ++range->start;

      return FL_fss_found_object_not;
    }

    if (status == F_none_eos) {
      return F_data_not_eos;
    }

    if (status == F_none_stop) {
      return F_data_not_stop;
    }

    // begin the search.
    found->start = range->start;

    // ignore all comment lines.
    if (buffer.string[range->start] == f_fss_comment_s[0]) {

      status = f_fss_seek_to_eol(buffer, range);
      if (F_status_is_error(status)) return status;

      if (status == F_none_eos) {
        return F_data_not_eos;
      }

      if (status == F_none_stop) {
        return F_data_not_stop;
      }

      // move the start position to after the EOL.
      ++range->start;

      return FL_fss_found_object_not;
    }

    f_array_length_t slash_first = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;
    f_array_length_t stop = 0;

    bool graph_first = F_true;

    // identify where the object ends.
    while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol_s[0]) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);
          break;
        }
      }

      if (buffer.string[range->start] == F_fss_delimit_slash_s) {
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

          if (buffer.string[range->start] == F_fss_delimit_placeholder_s) {
            continue;
          } else if (buffer.string[range->start] != F_fss_delimit_slash_s) {
            break;
          }

          ++slash_count;
        } // for

        private_macro_fl_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

        if (buffer.string[range->start] == f_fss_basic_list_open_s[0]) {
          graph_first = F_false;
          stop = range->start - 1;

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

            if (buffer.string[range->start] == f_fss_eol_s[0]) break;

            status = f_fss_is_space(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          private_macro_fl_fss_object_return_on_overflow((buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

          if (buffer.string[range->start] == f_fss_eol_s[0]) {
            start = range->start;

            range->start = slash_first;

            macro_f_fss_delimits_t_increase_by(status, (*delimits), (slash_count / 2) + 1);
            if (F_status_is_error(status)) break;

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {

                if (buffer.string[range->start] == F_fss_delimit_slash_s) {
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

              found->stop = stop;
              range->start = start + 1;

              return FL_fss_found_object;
            }

            range->start = start + 1;

            return FL_fss_found_object_not;
          }
        }
        else if (graph_first && buffer.string[range->start] == f_fss_comment_s[0]) {
          graph_first = F_false;

          // comments may only have whitespace before the '#', therefore only the first slash needs to be delimited.
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
      else if (buffer.string[range->start] == f_fss_basic_list_open_s[0]) {
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

          if (buffer.string[range->start] == f_fss_eol_s[0]) break;

          status = f_fss_is_space(buffer, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        private_macro_fl_fss_object_return_on_overflow_delimited((buffer), (*range), (*found), F_none_eos, F_none_stop);

        if (buffer.string[range->start] == f_fss_eol_s[0]) {
          found->stop = stop;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;

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

    if (status == F_none_eos) {
      return F_data_not_eos;
    }

    if (status == F_none_stop) {
      return F_data_not_stop;
    }

    // seek to the end of the line when no valid object is found.
    status = f_fss_seek_to_eol(buffer, range);

    // move the start position to after the EOL.
    ++range->start;

    return FL_fss_found_object_not;
  }
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  f_status_t fl_fss_basic_list_content_read(const f_string_static_t buffer, f_state_t state, f_string_range_t *range, f_fss_content_t *found, f_fss_delimits_t *delimits, f_fss_comments_t *comments) {
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

    macro_f_fss_content_t_increase(status, state.step_small, (*found))
    if (F_status_is_error(status)) return status;

    found->array[found->used].start = range->start;

    f_array_length_t newline_last = range->start;
    f_array_length_t slash_first = 0;
    f_array_length_t slash_count = 0;
    f_array_length_t start = 0;
    f_array_length_t comment_delimit = 0;

    uint8_t graph_first = 0x1; // 0x0 = false, 0x1 = true, 0x2 = false, but there is a delimited comment, comment_delimit is set.

    // identify where the content ends.
    while (range->start <= range->stop && range->start < buffer.used) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);
          break;
        }
      }

      if (buffer.string[range->start] == f_fss_eol_s[0]) {
        if (graph_first == 0x2) {
          macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
          if (F_status_is_error(status)) break;

          delimits->array[delimits->used++] = comment_delimit;
        }

        newline_last = range->start;
        graph_first = 0x1;
        ++range->start;

        continue;
      }

      if (buffer.string[range->start] == F_fss_delimit_slash_s) {
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

          if (buffer.string[range->start] == F_fss_delimit_placeholder_s) {
            continue;
          } else if (buffer.string[range->start] != F_fss_delimit_slash_s) {
            break;
          }

          ++slash_count;
        } // for

        if (range->start > range->stop || range->start >= buffer.used) break;

        if (buffer.string[range->start] == f_fss_basic_list_open_s[0]) {
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

            if (buffer.string[range->start] == f_fss_eol_s[0]) break;

            status = f_fss_is_space(buffer, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (range->start > range->stop || range->start >= buffer.used) break;

          if (buffer.string[range->start] == f_fss_eol_s[0]) {
            start = range->start;
            range->start = slash_first;

            if (slash_count % 2 == 0) {
              found->array[found->used++].stop = newline_last;
              range->start = newline_last + 1;

              return FL_fss_found_content;
            }

            macro_f_fss_delimits_t_increase_by(status, (*delimits), (slash_count / 2) + 1);
            if (F_status_is_error(status)) break;

            while (slash_count > 0) {

              if (buffer.string[range->start] == F_fss_delimit_slash_s) {
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
              macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
              if (F_status_is_error(status)) break;

              delimits->array[delimits->used++] = comment_delimit;
            }

            graph_first = 0x1;
            range->start = start + 1;
          }
        }
        else if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment_s[0]) {
          graph_first = 0x2;
          comment_delimit = slash_first;
          ++range->start;
        }

        continue;
      }

      if (buffer.string[range->start] == f_fss_basic_list_open_s[0]) {
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

          if (buffer.string[range->start] == f_fss_eol_s[0]) break;

          status = f_fss_is_space(buffer, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        if (range->start > range->stop || range->start >= buffer.used) break;

        // found a valid object, set stop point to last newline.
        if (buffer.string[range->start] == f_fss_eol_s[0]) {

          if (newline_last == found->array[found->used].start && buffer.string[found->array[found->used].start] != f_fss_eol_s[0]) {
            range->start = newline_last;
            return FL_fss_found_content_not;
          }
          else {
            range->start = newline_last + 1;
            found->array[found->used++].stop = newline_last;
          }

          return FL_fss_found_content;
        }

        if (buffer.string[range->start] == f_fss_eol_s[0]) {
          if (graph_first == 0x2) {
            macro_f_fss_delimits_t_increase(status, state.step_small, (*delimits));
            if (F_status_is_error(status)) break;

            delimits->array[delimits->used++] = comment_delimit;
          }

          newline_last = range->start;
          graph_first = 0x1;
        }

        continue;
      }

      if (graph_first == 0x1 && buffer.string[range->start] == f_fss_comment_s[0]) {
        start = range->start;

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

      if (graph_first == 0x1) {
        status = f_fss_is_space(buffer, *range);
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

    found->array[found->used++].stop = range->start - 1;

    private_macro_fl_fss_content_return_on_overflow_delimited((buffer), (*range), (*found), F_none_eos, F_none_stop);

    return FL_fss_found_content;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifndef _di_fl_fss_basic_list_object_write_string_
  f_status_t fl_fss_basic_list_object_write_string(const f_string_static_t object, const uint8_t complete, f_state_t state, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(object, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_stop || status == F_none_eos) {
      if (complete == f_fss_complete_partial || complete == f_fss_complete_partial_trim || complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
        const f_status_t status_allocation = f_string_dynamic_increase_by(2, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_basic_list_open_s[0];

        if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
          destination->string[destination->used++] = f_fss_basic_list_open_end_s[0];
        }
      }

      if (status == F_none_stop) {
        return F_data_not_stop;
      }

      return F_data_not_eos;
    }

    // ensure that there is room for a slash delimit, the object open character, and the end of line character.
    status = f_string_dynamic_increase_by(destination->used + (range->stop - range->start) + 3, destination);
    if (F_status_is_error(status)) return status;

    const f_array_length_t used_start = destination->used;

    f_array_length_t i = 0;
    f_array_length_t slash_count = 0;

    uint8_t width = 0;

    // find the first graph character.
    while (range->start <= range->stop && range->start < object.used) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);
          break;
        }
      }

      if (object.string[range->start] == f_fss_comment_s[0]) {

        // when a comment is found, escape it.
        status = f_string_dynamic_increase(state.step_large, destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = F_fss_delimit_slash_s;
        break;
      }

      status = f_fss_is_graph(object, *range);
      if (F_status_is_error(status)) break;

      if (status == F_true) break;

      // objects will not have leading whitespaces, but having this does not result in an invalid object, so just write the provided spaces.
      if (object.string[range->start] != F_fss_delimit_placeholder_s) {
        if (object.string[range->start] == f_fss_eol_s[0]) {
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

      if (object.string[range->start] == F_fss_delimit_slash_s) {
        slash_count = 1;

        for (++range->start; range->start <= range->stop && range->start < object.used; ++range->start) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);
              break;
            }
          }

          if (object.string[range->start] == F_fss_delimit_placeholder_s) {
            continue;
          } else if (object.string[range->start] != F_fss_delimit_slash_s) {
            break;
          }

          ++slash_count;
        } // for

        if (F_status_is_error(status)) break;

        if (range->start > range->stop || range->start >= object.used) {

          // slashes at the end of the object must be delimited to avoid delimiting the object close character.
          slash_count *= 2;
        }

        status = f_string_dynamic_increase_by(slash_count, destination);
        if (F_status_is_error(status)) break;

        while (--slash_count) {
          destination->string[destination->used++] = F_fss_delimit_slash_s;
        } // while

        if (range->start > range->stop || range->start >= object.used) {
          break;
        }
      }

      if (object.string[range->start] != F_fss_delimit_placeholder_s) {
        if (object.string[range->start] == f_fss_eol_s[0]) {
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
      destination->used = used_start;

      return status;
    }

    if (complete == f_fss_complete_partial || complete == f_fss_complete_partial_trim || complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
      if (complete == f_fss_complete_full_trim) {
        status = private_fl_fss_basic_list_write_object_trim(used_start, state, destination);

        if (F_status_is_error(status)) {
          destination->used = used_start;

          return status;
        }
      }

      status = f_string_dynamic_increase_by(2, destination);

      if (F_status_is_error(status)) {
        destination->used = used_start;

        return status;
      }

      destination->string[destination->used++] = f_fss_basic_list_open_s[0];

      if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
        destination->string[destination->used++] = f_fss_basic_list_open_end_s[0];
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
#endif // _di_fl_fss_basic_list_object_write_string_

#ifndef _di_fl_fss_basic_list_content_write_string_
  f_status_t fl_fss_basic_list_content_write_string(const f_string_static_t content, const uint8_t complete, const f_string_static_t *prepend, f_state_t state, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(content, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_stop || status == F_none_eos) {
      if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim || complete == f_fss_complete_end) {
        const f_status_t status_allocation = f_string_dynamic_increase(state.step_large, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_basic_list_close_s[0];
      }

      if (status == F_none_stop) {
        return F_data_not_stop;
      }

      return F_data_not_eos;
    }

    // ensure that there is room for a slash delimit and possibly the end of content character.
    status = f_string_dynamic_increase_by(destination->used + (range->stop - range->start) + 2, destination);
    if (F_status_is_error(status)) return status;

    const f_array_length_t used_start = destination->used;

    bool is_comment = F_false;
    bool has_graph = F_false;
    bool do_prepend = F_true;

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

      if (content.string[range->start] == F_fss_delimit_slash_s && !is_comment) {
        slash_count = 1;

        if (do_prepend) {
          status = f_string_dynamic_prepend(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        destination->string[destination->used++] = content.string[range->start];
        has_graph = F_true;

        for (++range->start; range->start <= range->stop && range->start < content.used; ++range->start) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);
              break;
            }
          }

          if (content.string[range->start] == F_fss_delimit_placeholder_s) continue;
          if (content.string[range->start] != F_fss_delimit_slash_s) break;

          destination->string[destination->used++] = F_fss_delimit_slash_s;
          ++slash_count;
        } // for

        if (content.string[range->start] == f_fss_basic_list_open_s[0]) {
          start = range->start++;

          status = f_fss_skip_past_space(content, range);
          if (F_status_is_error(status)) break;

          if (content.string[range->start] == f_fss_eol_s[0] || range->start >= content.used || range->start > range->stop) {

            // increase by total slashes + 1, along with the basic list open and possible newline.
            status = f_string_dynamic_increase_by(slash_count + 3, destination);
            if (F_status_is_error(status)) break;

            while (--slash_count) {
              destination->string[destination->used++] = F_fss_delimit_slash_s;
            } // while

            destination->string[destination->used++] = F_fss_delimit_slash_s;
            destination->string[destination->used++] = f_fss_basic_list_open_s[0];

            range->start = start + 1;

            status = private_fl_fss_basic_list_write_add_until_end(content, state, range, destination);
            if (F_status_is_error(status)) break;

            continue;
          }

          status = f_string_dynamic_increase(state.step_large, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = f_fss_basic_list_open_s[0];
          range->start = start + 1;
          continue;
        }
      }
      else if (content.string[range->start] == f_fss_basic_list_open_s[0] && !is_comment) {
        start = range->start++;

        if (do_prepend) {
          status = f_string_dynamic_prepend(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        has_graph = F_true;

        status = f_fss_skip_past_space(content, range);
        if (F_status_is_error(status)) break;

        if (content.string[range->start] == f_fss_eol_s[0] || range->start >= content.used || range->start > range->stop) {

          // increase by slash and basic list open and possible newline.
          status = f_string_dynamic_increase_by(3, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = F_fss_delimit_slash_s;
          destination->string[destination->used++] = f_fss_basic_list_open_s[0];

          range->start = start + 1;

          status = private_fl_fss_basic_list_write_add_until_end(content, state, range, destination);
          if (F_status_is_error(status)) break;

          continue;
        }

        status = f_string_dynamic_increase(state.step_large, destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = f_fss_basic_list_open_s[0];
        range->start = start + 1;
        continue;
      }
      else if (content.string[range->start] == f_fss_comment_s[0] && !has_graph) {
        is_comment = F_true;
      }
      else if (content.string[range->start] == f_fss_eol_s[0]) {
        has_graph = F_false;
        is_comment = F_false;
      }
      else {
        status = f_fss_is_graph(content, *range);

        if (status == F_true) {
          has_graph = F_true;
        }
        else if (F_status_is_error(status)) {
          break;
        }
      }

      if (content.string[range->start] != F_fss_delimit_placeholder_s) {
        if (do_prepend) {
          status = f_string_dynamic_prepend(*prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        if (content.string[range->start] == f_fss_eol_s[0]) {
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
      destination->used = used_start;

      return status;
    }

    if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim || complete == f_fss_complete_end) {
      status = f_string_dynamic_increase(state.step_large, destination);
      if (F_status_is_error(status)) return status;

      // check to see if a newline exists, at the end.
      if (destination->used) {
        for (i = destination->used - 1; i > 0; --i) {
          if (destination->string[i] != F_fss_delimit_placeholder_s) break;
        } // for
      }

      if (!destination->used || destination->string[i] != f_fss_eol_s[0]) {
        destination->string[destination->used++] = f_fss_basic_list_close_s[0];
      }
    }

    if (range->start > range->stop) {
      return F_none_stop;
    }

    if (range->start >= content.used) {
      return F_none_eos;
    }

    return F_none;
  }
#endif // _di_fl_fss_basic_list_content_write_string_

#ifdef __cplusplus
} // extern "C"
#endif
