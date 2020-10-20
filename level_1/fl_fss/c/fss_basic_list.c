#include "fss_basic.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  f_return_status fl_fss_basic_list_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_delimits_t *delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    f_status_t status = f_fss_skip_past_space(*buffer, range);
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

    // begin the search.
    found->start = range->start;

    // ignore all comment lines.
    if (buffer->string[range->start] == f_fss_comment) {

      status = f_fss_seek_to_eol(*buffer, range);
      if (F_status_is_error(status)) return status;

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

    f_string_length_t first_slash = 0;
    f_string_length_t slash_count = 0;
    f_string_length_t start = 0;
    f_string_length_t stop = 0;

    // identify where the object ends.
    while (range->start <= range->stop && range->start < buffer->used && buffer->string[range->start] != f_fss_eol) {

      if (buffer->string[range->start] == f_fss_delimit_slash) {
        first_slash = range->start;
        slash_count = 1;

        for (range->start++; range->start <= range->stop && range->start < buffer->used; range->start++) {

          if (buffer->string[range->start] == f_fss_delimit_placeholder) {
            continue;
          } else if (buffer->string[range->start] != f_fss_delimit_slash) {
            break;
          }

          slash_count++;
        } // for

        fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

        if (buffer->string[range->start] == f_fss_basic_list_open) {
          stop = range->start - 1;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == f_fss_eol) {
              break;
            }

            status = f_fss_is_space(*buffer, *range);

            if (F_status_is_error(status)) {
              delimits->used = delimits_used;
              return status;
            }

            if (status == F_false) break;

            status = f_utf_buffer_increment(*buffer, range, 1);

            if (F_status_is_error(status)) {
              delimits->used = delimits_used;
              return status;
            }
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

          if (buffer->string[range->start] == f_fss_eol) {
            start = range->start;

            range->start = first_slash;

            status = private_fl_fss_delimits_increase_by((slash_count / 2) + 1, delimits);

            if (F_status_is_error(status)) {
              delimits->used = delimits_used;
              return status;
            }

            if (slash_count % 2 == 0) {
              while (slash_count > 0) {

                if (buffer->string[range->start] == f_fss_delimit_slash) {
                  if (slash_count % 2 == 1) {
                    delimits->array[delimits->used] = range->start;
                    delimits->used++;
                  }

                  slash_count--;
                }

                status = f_utf_buffer_increment(*buffer, range, 1);

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

        continue;
      }
      else if (buffer->string[range->start] == f_fss_basic_list_open) {
        stop = range->start - 1;

        status = f_utf_buffer_increment(*buffer, range, 1);

        if (F_status_is_error(status)) {
          delimits->used = delimits_used;
          return status;
        }

        while (range->start <= range->stop && range->start < buffer->used) {

          if (buffer->string[range->start] == f_fss_eol) {
            break;
          }

          status = f_fss_is_space(*buffer, *range);

          if (F_status_is_error(status)) {
            delimits->used = delimits_used;
            return status;
          }

          if (status == F_false) break;

          status = f_utf_buffer_increment(*buffer, range, 1);

          if (F_status_is_error(status)) {
            delimits->used = delimits_used;
            return status;
          }
        } // while

        fl_macro_fss_object_return_on_overflow_delimited((*buffer), (*range), (*found), F_none_eos, F_none_stop);

        if (buffer->string[range->start] == f_fss_eol) {
          found->stop = stop;

          status = f_utf_buffer_increment(*buffer, range, 1);

          if (F_status_is_error(status)) {
            delimits->used = delimits_used;
            return status;
          }

          return FL_fss_found_object;
        }

        continue;
      }

      status = f_utf_buffer_increment(*buffer, range, 1);

      if (F_status_is_error(status)) {
        delimits->used = delimits_used;
        return status;
      }
    } // while

    // seek to the end of the line when no valid object is found.
    status = f_fss_seek_to_eol(*buffer, range);

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
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  f_return_status fl_fss_basic_list_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_content_t *found, f_fss_delimits_t *delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    f_status_t status = f_fss_skip_past_delimit(*buffer, range);
    if (F_status_is_error(status)) return status;

    fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), (*delimits), delimits_used, F_none_eos, F_none_stop);

    status = private_fl_fss_ranges_increase(found);
    if (F_status_is_error(status)) return status;

    found->array[found->used].start = range->start;

    f_string_length_t last_newline = range->start;
    f_string_length_t first_slash = 0;
    f_string_length_t slash_count = 0;
    f_string_length_t start = 0;

    bool found_newline = F_false;

    // identify where the content ends.
    while (range->start <= range->stop && range->start < buffer->used) {

      if (buffer->string[range->start] == f_fss_eol) {
        found_newline = F_true;
        last_newline = range->start;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;

        fl_macro_fss_content_return_on_overflow_delimited((*buffer), (*range), (*found), F_none_eos, F_none_stop);

        continue;
      }

      if (buffer->string[range->start] == f_fss_delimit_slash) {
        first_slash = range->start;
        slash_count = 1;

        for (range->start++; range->start <= range->stop && range->start < buffer->used; range->start++) {

          if (buffer->string[range->start] == f_fss_delimit_placeholder) {
            continue;
          } else if (buffer->string[range->start] != f_fss_delimit_slash) {
            break;
          }

          slash_count++;
        } // for

        if (found_newline) {
          fl_macro_fss_content_return_on_overflow_delimited((*buffer), (*range), (*found), F_none_eos, F_none_stop);
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);
        }

        if (buffer->string[range->start] == f_fss_basic_list_open) {
          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == f_fss_eol) {
              break;
            }

            status = f_fss_is_space(*buffer, *range);

            if (F_status_is_error(status)) return status;
            if (status == F_false) break;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (found_newline) {
            fl_macro_fss_content_return_on_overflow_delimited((*buffer), (*range), (*found), F_none_eos, F_none_stop);
          }
          else {
            fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);
          }

          if (buffer->string[range->start] == f_fss_eol) {
            start = range->start;

            range->start = first_slash;

            if (slash_count % 2 == 0) {
              if (found_newline) {
                found->array[found->used].stop = last_newline;
                range->start = last_newline + 1;
                found->used++;

                return FL_fss_found_content;
              }

              return FL_fss_found_content_not;
            }

            status = private_fl_fss_delimits_increase_by(slash_count / 2, delimits);

            if (F_status_is_error(status)) {
              delimits->used = delimits_used;
              return status;
            }

            while (slash_count > 0) {

              if (buffer->string[range->start] == f_fss_delimit_slash) {
                if (slash_count % 2 == 1) {
                  delimits->array[delimits->used] = range->start;
                  delimits->used++;
                }

                slash_count--;
              }

              status = f_utf_buffer_increment(*buffer, range, 1);
              if (F_status_is_error(status)) return status;
            } // while

            found_newline = F_true;
            range->start = start + 1;
          }
        }

        continue;
      }
      else if (buffer->string[range->start] == f_fss_basic_list_open) {
        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;

        while (range->start <= range->stop && range->start < buffer->used) {

          if (buffer->string[range->start] == f_fss_eol) {
            break;
          }

          status = f_fss_is_space(*buffer, *range);

          if (F_status_is_error(status)) return status;
          if (status == F_false) break;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;
        } // while

        if (found_newline) {
          fl_macro_fss_content_return_on_overflow_delimited((*buffer), (*range), (*found), F_none_eos, F_none_stop);
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);
        }

        if (buffer->string[range->start] == f_fss_eol) {
          if (found_newline) {
            found->array[found->used++].stop = last_newline;
            range->start = last_newline + 1;

            return FL_fss_found_content;
          }

          if (!found_newline) {
            range->start = last_newline;
          }

          return FL_fss_found_content_not;
        }

        continue;
      }

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    if (found_newline) {
      found->array[found->used++].stop = last_newline;
      range->start = last_newline + 1;

      fl_macro_fss_content_return_on_overflow_delimited((*buffer), (*range), (*found), F_none_eos, F_none_stop);

      return FL_fss_found_content;
    }

    fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), (*delimits), delimits_used, F_data_not_eos, F_data_not_stop);

    return FL_fss_found_content_not;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifndef _di_fl_fss_basic_list_object_write_string_
  f_return_status fl_fss_basic_list_object_write_string(const f_string_static_t object, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(object, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_stop || status == F_none_eos) {
      if (complete == f_fss_complete_partial || complete == f_fss_complete_partial_trim || complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
        const f_status_t status_allocation = private_fl_fss_destination_increase_by(2, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_basic_list_open;

        if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
          destination->string[destination->used++] = f_fss_basic_list_open_end;
        }
      }

      if (status == F_none_stop) {
        return F_data_not_stop;
      }

      return F_data_not_eos;
    }

    // ensure that there is room for a slash delimit, the object open character, and the end of line character.
    status = private_fl_fss_destination_increase_by(destination->used + (range->stop - range->start) + 3, destination);
    if (F_status_is_error(status)) return status;

    const f_string_length_t input_start = range->start;
    const f_string_length_t used_start = destination->used;

    f_string_length_t i = 0;
    f_string_length_t slash_count = 0;

    f_string_range_t range_next = f_string_range_t_initialize;

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
          break;
        }
      }

      if (object.string[range->start] != f_fss_delimit_placeholder) {
        if (object.string[range->start] == f_fss_eol) {
          status = F_status_set_error(F_none_eol);
          break;
        }

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
      }

      status = private_fl_fss_destination_increase_by(2, destination);

      if (F_status_is_error(status)) {
        destination->used = used_start;
        return status;
      }

      destination->string[destination->used++] = f_fss_basic_list_open;

      if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
        destination->string[destination->used++] = f_fss_basic_list_open_end;
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
  f_return_status fl_fss_basic_list_content_write_string(const f_string_static_t content, const uint8_t complete, const f_string_static_t *prepend, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_delimit(content, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_stop || status == F_none_eos) {
      if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim || complete == f_fss_complete_end) {
        const f_status_t status_allocation = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_basic_list_close;
      }

      if (status == F_none_stop) {
        return F_data_not_stop;
      }

      return F_data_not_eos;
    }

    // ensure that there is room for a slash delimit and possibly the end of content character.
    status = private_fl_fss_destination_increase_by(destination->used + (range->stop - range->start) + 2, destination);
    if (F_status_is_error(status)) return status;

    const f_string_length_t input_start = range->start;
    const f_string_length_t used_start = destination->used;

    bool is_comment = F_false;
    bool has_graph = F_false;
    bool do_prepend = F_true;

    f_string_length_t i = 0;
    f_string_length_t slash_count = 0;
    f_string_length_t start = 0;

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
        has_graph = F_true;

        for (range->start++; range->start <= range->stop && range->start < content.used; range->start++) {

          if (content.string[range->start] == f_fss_delimit_placeholder) continue;
          if (content.string[range->start] != f_fss_delimit_slash) break;

          destination->string[destination->used++] = f_fss_delimit_slash;
          slash_count++;
        } // for

        if (content.string[range->start] == f_fss_basic_list_open) {
          start = range->start++;

          status = f_fss_skip_past_space(content, range);
          if (F_status_is_error(status)) break;

          if (content.string[range->start] == f_fss_eol || range->start >= content.used || range->start > range->stop) {

            // increase by total slashes + 1, along with the basic list open and possible newline.
            status = private_fl_fss_destination_increase_by(slash_count + 3, destination);
            if (F_status_is_error(status)) break;

            while (slash_count--) {
              destination->string[destination->used++] = f_fss_delimit_slash;
            } // while

            destination->string[destination->used++] = f_fss_delimit_slash;
            destination->string[destination->used++] = f_fss_basic_list_open;

            range->start = start + 1;

            status = private_fl_fss_basic_list_write_add_until_end(content, range, destination);
            if (F_status_is_error(status)) break;

            continue;
          }

          status = private_fl_fss_destination_increase(destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = f_fss_basic_list_open;
          range->start = start + 1;
          continue;
        }
      }
      else if (content.string[range->start] == f_fss_basic_list_open && !is_comment) {
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

          // increase by slash and basic list open and possible newline.
          status = private_fl_fss_destination_increase_by(3, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = f_fss_delimit_slash;
          destination->string[destination->used++] = f_fss_basic_list_open;

          range->start = start + 1;

          status = private_fl_fss_basic_list_write_add_until_end(content, range, destination);
          if (F_status_is_error(status)) break;

          continue;
        }

        status = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = f_fss_basic_list_open;
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
      else {
        status = f_fss_is_graph(content, *range);

        if (status == F_true) {
          has_graph = F_true;
        }
        else if (F_status_is_error(status)) {
          break;
        }
      }

      if (content.string[range->start] != f_fss_delimit_placeholder) {
        if (do_prepend) {
          status = private_fl_fss_destination_prepend(prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        if (content.string[range->start] == f_fss_eol) {
          do_prepend = F_true;
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
      status = private_fl_fss_destination_increase(destination);
      if (F_status_is_error(status)) return status;

      destination->string[destination->used++] = f_fss_basic_list_close;
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
