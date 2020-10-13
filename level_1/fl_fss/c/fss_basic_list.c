#include "fss_basic.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  f_return_status fl_fss_basic_list_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found) {
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

    // begin the search.
    found->start = range->start;

    // ignore all comment lines.
    if (buffer->string[range->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*range), delimits, F_data_not_eos, F_data_not_stop);

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      return FL_fss_found_object_not;
    }

    f_string_length_t first_slash = 0;
    f_string_length_t slash_count = 0;
    f_string_length_t start = 0;
    f_string_length_t stop = 0;

    // identify where the object ends.
    while (range->start <= range->stop && range->start < buffer->used && buffer->string[range->start] != f_string_eol[0]) {

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

        fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

        if (buffer->string[range->start] == f_fss_basic_list_open) {
          stop = range->start - 1;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == f_string_eol[0]) {
              break;
            }

            status = f_fss_is_space(*buffer, *range);
            if (F_status_is_error(status)) return status;

            if (status == F_false) break;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

          if (buffer->string[range->start] == f_string_eol[0]) {
            start = range->start;

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
        if (F_status_is_error(status)) return status;

        while (range->start <= range->stop && range->start < buffer->used) {

          if (buffer->string[range->start] == f_string_eol[0]) {
            break;
          }

          status = f_fss_is_space(*buffer, *range);
          if (F_status_is_error(status)) return status;

          if (status == F_false) break;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;
        } // while

        fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

        if (buffer->string[range->start] == f_string_eol[0]) {
          fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

          found->stop = stop;

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
    while (range->start <= range->stop && range->start < buffer->used && buffer->string[range->start] != f_string_eol[0]) {
      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

    status = f_utf_buffer_increment(*buffer, range, 1);
    if (F_status_is_error(status)) return status;

    return FL_fss_found_object_not;
  }
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  f_return_status fl_fss_basic_list_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_content_t *found) {
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

    fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));
    fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

    fl_macro_fss_allocate_content_if_necessary((*found), delimits);
    found->array[found->used].start = range->start;

    f_string_length_t last_newline = range->start;
    f_string_length_t first_slash = 0;
    f_string_length_t slash_count = 0;
    f_string_length_t start = 0;

    bool found_newline = F_false;

    // identify where the content ends.
    while (range->start <= range->stop && range->start < buffer->used) {

      if (buffer->string[range->start] == f_string_eol[0]) {
        found_newline = F_true;
        last_newline = range->start;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;

        fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

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
          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);
        }

        if (buffer->string[range->start] == f_fss_basic_list_open) {
          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == f_string_eol[0]) {
              break;
            }

            status = f_fss_is_space(*buffer, *range);

            if (F_status_is_error(status)) return status;
            if (status == F_false) break;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (found_newline) {
            fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);
          }
          else {
            fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);
          }

          if (buffer->string[range->start] == f_string_eol[0]) {
            start = range->start;

            range->start = first_slash;

            if (slash_count % 2 == 0) {
              if (found_newline) {
                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                found->array[found->used].stop = last_newline;
                range->start = last_newline + 1;
                found->used++;

                return FL_fss_found_content;
              }

              return FL_fss_found_content_not;
            }

            if (delimits.used + (slash_count / 2) >= delimits.size) {
              f_macro_string_lengths_t_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

              if (F_status_is_error(status)) {
                f_macro_string_lengths_t_delete_simple(delimits);
                return status;
              }
            }

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

          if (buffer->string[range->start] == f_string_eol[0]) {
            break;
          }

          status = f_fss_is_space(*buffer, *range);

          if (F_status_is_error(status)) return status;
          if (status == F_false) break;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;
        } // while

        if (found_newline) {
          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);
        }

        if (buffer->string[range->start] == f_string_eol[0]) {
          if (found_newline) {
            fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

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
      fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

      found->array[found->used++].stop = last_newline;
      range->start = last_newline + 1;

      fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

      return FL_fss_found_content;
    }

    fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

    return FL_fss_found_content_not;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifndef _di_fl_fss_basic_list_object_write_
  f_return_status fl_fss_basic_list_object_write(const f_string_static_t object, const uint8_t complete, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*range));

    if (range->start > range->stop) {
      status = F_data_not_stop;
    }
    else if (range->start >= object.used) {
      status = F_data_not_eos;
    }

    if (status == F_data_not_stop || status == F_data_not_eos) {
      if (complete == f_fss_complete_partial || complete == f_fss_complete_partial_trim || complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
        const f_status_t status_allocation = private_fl_fss_destination_increase_by(2, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;

        destination->string[destination->used++] = f_fss_basic_list_open;

        if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim) {
          destination->string[destination->used++] = f_fss_basic_list_open_end;
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
#endif // _di_fl_fss_basic_list_object_write_

#ifndef _di_fl_fss_basic_list_content_write_
  f_return_status fl_fss_basic_list_content_write(const f_string_static_t content, const uint8_t complete, const f_string_static_t prepend, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    fl_macro_fss_skip_past_delimit_placeholders(content, (*range));

    if (range->start > range->stop || range->start >= content.used) {
      if (complete == f_fss_complete_full || complete == f_fss_complete_full_trim || complete == f_fss_complete_end) {
        status = private_fl_fss_destination_increase(destination);
        if (F_status_is_error(status)) return status;

        destination->string[destination->used++] = f_fss_basic_list_close;
      }

      if (range->start > range->stop) {
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

        status = f_utf_buffer_increment(content, range, 1);
        if (F_status_is_error(status)) break;

        for (; range->start <= range->stop && range->start < content.used; range->start++) {

          if (content.string[range->start] == f_fss_delimit_placeholder) {
            continue;
          }
          else if (content.string[range->start] != f_fss_delimit_slash) {
            break;
          }

          destination->string[destination->used++] = f_fss_delimit_slash;
          slash_count++;
        } // for

        if (content.string[range->start] == f_fss_basic_list_open) {
          start = range->start;

          status = f_utf_buffer_increment(content, range, 1);
          if (F_status_is_error(status)) break;

          while (range->start < content.used && range->start <= range->stop) {

            if (content.string[range->start] == f_fss_eol) {
              do_prepend = F_true;
              break;
            }

            status = f_fss_is_space(content, *range);
            if (F_status_is_error(status)) break;

            if (status == F_false) break;

            status = f_utf_buffer_increment(content, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (F_status_is_error(status)) break;

          if (content.string[range->start] == f_fss_eol || range->start >= content.used || range->start > range->stop) {

            // increase by total slashes + 1, along with the basic list open and possible newline.
            status = private_fl_fss_destination_increase_by(slash_count + 3, destination);
            if (F_status_is_error(status)) break;

            while (slash_count--) {
              destination->string[destination->used++] = f_fss_delimit_slash;
            } // while

            destination->string[destination->used++] = f_fss_delimit_slash;
            has_graph = F_false;
            is_comment = F_false;
          }
          else {
            status = private_fl_fss_destination_increase(destination);
            if (F_status_is_error(status)) break;
          }

          destination->string[destination->used++] = f_fss_basic_list_open;

          if (content.string[range->start] == f_fss_eol) {
            destination->string[destination->used++] = f_fss_eol;
          }

          range->start = start + 1;
          continue;
        }
      }
      else if (content.string[range->start] == f_fss_basic_list_open && !is_comment) {
        start = range->start++;
        has_graph = F_true;

        while (range->start < content.used && range->start <= range->stop) {

          if (content.string[range->start] == f_fss_eol) break;

          status = f_fss_is_space(content, *range);
          if (F_status_is_error(status)) break;

          if (status == F_false) break;

          status = f_utf_buffer_increment(content, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        if (F_status_is_error(status)) break;

        if (do_prepend) {
          status = private_fl_fss_destination_prepend(prepend, destination);
          if (F_status_is_error(status)) break;

          do_prepend = F_false;
        }

        if (content.string[range->start] == f_fss_eol || range->start >= content.used || range->start > range->stop) {
          if (content.string[range->start] == f_fss_eol) {
            do_prepend = F_true;
          }

          // increase by slash and basic list open and possible newline.
          status = private_fl_fss_destination_increase_by(3, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = f_fss_delimit_slash;
          has_graph = F_false;
          is_comment = F_false;
        }
        else {
          status = private_fl_fss_destination_increase(destination);
          if (F_status_is_error(status)) break;
        }

        destination->string[destination->used++] = f_fss_basic_list_open;

        if (content.string[range->start] == f_fss_eol) {
          destination->string[destination->used++] = f_fss_eol;
        }

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
#endif // _di_fl_fss_basic_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
