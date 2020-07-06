#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_)
  f_return_status private_fl_fss_basic_object_read(const bool is_basic, f_string_dynamic *buffer, f_string_range *range, f_fss_object *found) {
    f_status status = F_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths delimits = f_string_lengths_initialize;

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

    // when handling delimits, the only time they should be applied is when a valid object would exist.
    // however, the delimits will appear before a valid object, so remember their positions and only apply them after a would be valid object is confirmed.
    bool has_delimit = F_false;

    // begin the search.
    found->start = range->start;

    // ignore all comment lines.
    if (buffer->string[range->start] == f_fss_comment) {
      fl_macro_fss_object_seek_till_newline((*buffer), (*range), delimits, F_data_not_eos, F_data_not_stop);

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      return FL_fss_found_object_not;
    }

    // handle quote support.
    int8_t quoted = 0;

    // identify where the object begins.
    if (buffer->string[range->start] == f_fss_delimit_slash) {
      f_string_length first_slash = range->start;

      found->start = range->start;

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      while (range->start <= range->stop && range->start < buffer->used) {
        status = f_fss_is_zero_width(*buffer, *range);
        if (F_status_is_error(status)) return status;

        if (status == F_true) {
          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          continue;
        }

        if (buffer->string[range->start] != f_fss_delimit_slash) {
          status = f_fss_is_space(*buffer, *range);

          // found the end of the object while processing the slash for potential delimits.
          if (status == F_true) {
            found->stop = range->start - 1;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) return status;

            if (buffer->string[range->start] == f_string_eol[0]) {
              return FL_fss_found_object_content_not;
            }

            return FL_fss_found_object;
          }
          else if (F_status_is_error(status)) {
            return status;
          }

          break;
        }

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) {
          return status;
        }
      } // while

      fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

      if (buffer->string[range->start] == f_fss_delimit_single_quote || buffer->string[range->start] == f_fss_delimit_double_quote) {

        // only the first slash before a quote needs to be escaped (or not) as once there is a slash before a quote, this cannot ever be a quoted object.
        // this simplifies the number of slashes needed.
        if (delimits.used + 1 > delimits.size) {
          f_macro_string_lengths_resize(status, delimits, delimits.size + 1);
          if (F_status_is_error(status)) return status;
        }

        delimits.array[delimits.used] = first_slash;
        delimits.used++;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          return status;
        }
      }
    }
    else if (buffer->string[range->start] == f_fss_delimit_single_quote || buffer->string[range->start] == f_fss_delimit_double_quote) {
      quoted = buffer->string[range->start];

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      found->start = range->start;
    }

    // identify where the object ends.
    if (quoted == 0) {
      status = F_none;

      while (range->start <= range->stop && range->start < buffer->used) {
        status = f_fss_is_space(*buffer, *range);

        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          return status;
        }

        if (status == F_true) break;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          return status;
        }
      } // while

      found->stop = range->start - 1;

      fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

      if (buffer->string[range->start] == f_string_eol[0]) {
        range->start++;
        return FL_fss_found_object_content_not;
      }

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) {
        f_macro_string_lengths_delete_simple(delimits);
        return status;
      }

      return FL_fss_found_object;
    }
    else {

      while (range->start <= range->stop && range->start < buffer->used) {

        if (buffer->string[range->start] == f_fss_delimit_slash) {
          f_string_length first_slash = range->start;
          f_string_length slash_count = 1;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            return status;
          }

          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == f_fss_delimit_placeholder) {
              status = f_utf_buffer_increment(*buffer, range, 1);
              if (F_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }

              continue;
            }
            else if (buffer->string[range->start] != f_fss_delimit_slash) {
              break;
            }

            slash_count++;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              return status;
            }
          } // while

          fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_status_set_warning(F_unterminated_group_eos), F_status_set_warning(F_unterminated_group_stop));

          if (buffer->string[range->start] == quoted) {
            f_string_length location = range->start;

            // check to see if there is a whitespace, EOS, or EOL after the quote, if not, then this is not a closing quote and delimits do not apply.
            if (range->start + 1 <= range->stop && range->start + 1 < buffer->used) {
              range->start++;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));

              if (range->start <= range->stop && range->start < buffer->used) {
                status = f_fss_is_space(*buffer, *range);
                if (F_status_is_error(status)) {
                  return status;
                }
              }
              else {
                // EOS or EOL was reached, so it is a valid closing quote.
                // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE (@todo maybe none on stop?).
                status = F_true;
              }
            }
            else {
              // EOS or EOL was reached, so it is a valid closing quote.
              // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE (@todo maybe none on stop?).
              status = F_true;
            }

            if (status == F_true) {
              range->start = first_slash;

              if (slash_count % 2 == 0) {
                if (delimits.used + (slash_count / 2) >= delimits.size) {
                  f_macro_string_lengths_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
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
                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }
                } // while

                range->start = location + 1;

                fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));
                fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);

                if ((status = f_fss_is_graph(*buffer, *range)) == F_true) {

                  while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {
                    status = f_utf_buffer_increment(*buffer, range, 1);
                    if (F_status_is_error(status)) {
                      f_macro_string_lengths_delete_simple(delimits);
                      return status;
                    }
                  } // while

                  fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

                  f_macro_string_lengths_delete_simple(delimits);

                  status = f_utf_buffer_increment(*buffer, range, 1);
                  if (F_status_is_error(status)) return status;

                  return FL_fss_found_object_not;
                }
                else if (F_status_is_error(status)) {
                  f_macro_string_lengths_delete_simple(delimits);
                  return status;
                }
                else if (buffer->string[range->start] == f_string_eol[0]) {
                  fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                  found->stop = location - 1;
                  range->start++;
                  return FL_fss_found_object_content_not;
                }

                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                found->stop = location - 1;

                status = f_utf_buffer_increment(*buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return FL_fss_found_object;
              }
              else {
                if (delimits.used + (slash_count / 2) >= delimits.size) {
                  f_macro_string_lengths_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
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
                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }
                } // while

                range->start = location;
              }
            }
            else {
              range->start = location;
            }
          }
        }
        else if (buffer->string[range->start] == quoted) {
          // check to see if there is a whitespace, EOS, or EOL after the quote, if not, then this is not a closing quote.
          {
            f_string_length location = range->start;

            if (range->start + 1 <= range->stop && range->start + 1 < buffer->used) {
              range->start++;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));

              if (range->start <= range->stop && range->start < buffer->used) {
                status = f_fss_is_space(*buffer, *range);
                if (F_status_is_error(status)) {
                  return status;
                }
              }
              else {
                // EOS or EOL was reached, so it is a valid closing quote.
                // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE (@todo maybe none on stop?).
                status = F_true;
              }
            }
            else {
              // EOS or EOL was reached, so it is a valid closing quote.
                // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE (@todo maybe none on stop?).
              status = F_true;
            }

            range->start = location;
          }

          if (status == F_true) {
            found->stop = range->start - 1;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              return status;
            }

            while (range->start <= range->stop && range->start < buffer->used) {
              if (buffer->string[range->start] == f_string_eol[0]) {
                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                range->start++;
                return FL_fss_found_object_content_not;
              }
              else if ((status = f_fss_is_space(*buffer, *range)) == F_true) {
                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                status = f_utf_buffer_increment(*buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return FL_fss_found_object;
              }
              else if (F_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }
              else if (buffer->string[range->start] != f_fss_delimit_placeholder) {

                while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {
                  status = f_utf_buffer_increment(*buffer, range, 1);
                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }

                } // while

                fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

                f_macro_string_lengths_delete_simple(delimits);

                status = f_utf_buffer_increment(*buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return FL_fss_found_object_not;
              }

              status = f_utf_buffer_increment(*buffer, range, 1);
              if (F_status_is_error(status)) return status;
            } // while

            fl_macro_fss_object_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop);
          }
        }
        else if (buffer->string[range->start] == f_string_eol[0]) {
          f_macro_string_lengths_delete_simple(delimits);

          range->start++;
          return FL_fss_found_object_not;
        }

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          return status;
        }
      } // while

      fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_status_set_warning(F_unterminated_group_eos), F_status_set_warning(F_unterminated_group_stop));
    }

    // seek to the end of the line when no valid object is found
    while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {
      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) {
        f_macro_string_lengths_delete_simple(delimits);
        return status;
      }
    } // while

    fl_macro_fss_object_return_on_overflow((*buffer), (*range), (*found), delimits, F_data_not_eos, F_data_not_stop);

    f_macro_string_lengths_delete_simple(delimits);

    status = f_utf_buffer_increment(*buffer, range, 1);
    if (F_status_is_error(status)) return status;

    return FL_fss_found_object_not;
  }
#endif // !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_)

#ifdef __cplusplus
} // extern "C"
#endif
