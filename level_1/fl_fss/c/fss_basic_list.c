#include "fss_basic.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  f_return_status fl_fss_basic_list_object_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
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

        if (buffer->string[range->start] == f_fss_basic_list_open) {
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
      else if (buffer->string[range->start] == f_fss_basic_list_open) {
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
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  f_return_status fl_fss_basic_list_content_read(f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_content_t *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths_t delimits = f_string_lengths_t_initialize;

    fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));
    fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)

    fl_macro_fss_allocate_content_if_necessary((*found), delimits);
    found->array[found->used].start = range->start;

    f_string_length_t last_newline = range->start;
    bool found_newline = F_false;

    // identify where the content ends.
    while (range->start < buffer->used && range->start <= range->stop) {
      if (buffer->string[range->start] == f_string_eol[0]) {
        found_newline = F_true;
        last_newline = range->start;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;

        fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)

        continue;
      }

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

        if (found_newline) {
          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop)
        }

        if (buffer->string[range->start] == f_fss_basic_list_open) {
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

          if (found_newline) {
            fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)
          }
          else {
            fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop)
          }

          if (buffer->string[range->start] == f_string_eol[0]) {
            f_string_length_t start = range->start;

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

        while (range->start < buffer->used && range->start <= range->stop) {
          if (buffer->string[range->start] == f_string_eol[0]) break;

          status = f_fss_is_space(*buffer, *range);

          if (F_status_is_error(status)) return status;
          if (status == F_false) break;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;
        } // while

        if (found_newline) {
          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)
        }
        else {
          fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop)
        }

        if (buffer->string[range->start] == f_string_eol[0]) {
          if (found_newline) {
            fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

            found->array[found->used].stop = last_newline;
            range->start = last_newline + 1;
            found->used++;

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

      found->array[found->used].stop = last_newline - 1;
      range->start = last_newline + 1;
      found->used++;

      fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)

      return FL_fss_found_content;
    }

    fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop)

    return FL_fss_found_content_not;
  }
#endif // _di_fl_fss_basic_list_content_read_

#ifndef _di_fl_fss_basic_list_object_write_
  f_return_status fl_fss_basic_list_object_write(const f_string_static_t object, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_string_range_t buffer_position = f_string_range_initialize;
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
        if (buffer_position.stop == buffer_position.start) {
          return F_data_not_eol;
        }

        break;
      }

      if (object.string[range->start] != f_fss_delimit_placeholder) {
        destination->string[buffer_position.stop] = object.string[range->start];
        buffer_position.stop++;
      }

      status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    destination->string[buffer_position.stop] = f_fss_basic_list_open;
    destination->string[buffer_position.stop + 1] = f_string_eol[0];
    destination->used = buffer_position.stop + 2;

    if (range->start > range->stop) return F_none_stop;
    else if (range->start >= object.used) return F_none_eos;

    return F_none;
  }
#endif // _di_fl_fss_basic_list_object_write_

#ifndef _di_fl_fss_basic_list_content_write_
  f_return_status fl_fss_basic_list_content_write(const f_string_static_t content, f_string_range_t *range, f_string_dynamic_t *destination) {
    #ifndef _di_level_1_parameter_checking_
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;
    bool is_comment = F_false;
    bool has_graph = F_false;

    f_string_range_t buffer_position = f_string_range_initialize;
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

        if (content.string[range->start] == f_fss_basic_list_open) {
          f_string_length_t start = range->start;

          status = f_utf_buffer_increment(content, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start < content.used && range->start <= range->stop) {
            if (content.string[range->start] == f_string_eol[0]) break;

            status = f_fss_is_space(content, *range);

            if (F_status_is_error(status)) return status;
            if (status == F_false) break;

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

          destination->string[buffer_position.stop] = f_fss_basic_list_open;
          buffer_position.stop++;
          range->start = start + 1;
          continue;
        }
      }
      else if (content.string[range->start] == f_fss_basic_list_open && !is_comment) {
        f_string_length_t start = range->start;

        has_graph = F_true;

        status = f_utf_buffer_increment(content, range, 1);
        if (F_status_is_error(status)) return status;

        while (range->start < content.used && range->start <= range->stop) {
          if (content.string[range->start] == f_string_eol[0]) break;

          status = f_fss_is_space(content, *range);

          if (F_status_is_error(status)) return status;
          if (status == F_false) break;

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

        destination->string[buffer_position.stop] = f_fss_basic_list_open;
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

    return F_none;
  }
#endif // _di_fl_fss_basic_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
