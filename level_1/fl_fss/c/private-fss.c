#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)
  f_return_status private_fl_fss_basic_read(const bool object_as, f_string_dynamic_t *buffer, f_string_range_t *range, f_fss_object_t *found, f_fss_quote_t *quote, f_string_lengths_t *delimits) {
    f_status_t status = F_none;

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
    if (object_as && buffer->string[range->start] == f_fss_comment) {
      while (buffer->string[range->start] != f_string_eol[0]) {
        range->start++;

        if (range->start >= buffer->used) return F_data_not_eos;
        if (range->start > range->stop) return F_data_not_stop;
      } // while

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      return FL_fss_found_object_not;
    }

    // delimits must only be applied once a valid object is found->
    const f_string_length_t delimit_initial = delimits->used;

    // handle quoted support.
    int8_t quote_found = 0;

    if (quote) {
      *quote = 0;
    }

    // identify where the object begins.
    if (buffer->string[range->start] == f_fss_delimit_slash) {
      f_string_length_t first_slash = range->start;

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

      if (range->start >= buffer->used) {
        found->stop = buffer->used - 1;
        return F_none_eos;
      }
      else if (range->start > range->stop) {
        found->stop = range->stop;
        return F_none_stop;
      }

      if (buffer->string[range->start] == f_fss_delimit_quote_single || buffer->string[range->start] == f_fss_delimit_quote_double || (object_as && buffer->string[range->start] == f_fss_comment)) {

        // only the first slash before a quoted needs to be escaped (or not) as once there is a slash before a quoted, this cannot ever be a quote object.
        // this simplifies the number of slashes needed.
        if (delimits->used == delimits->size) {
          if (delimits->size + f_fss_default_allocation_step > f_array_length_t_size) {
            if (delimits->size + 1 > f_array_length_t_size) {
              return F_status_set_error(F_buffer_too_large);
            }

            f_macro_string_lengths_t_resize(status, (*delimits), delimits->size + 1);
            if (F_status_is_error(status)) return status;
          }
          else {
            f_macro_string_lengths_t_resize(status, (*delimits), delimits->size + f_fss_default_allocation_step);
            if (F_status_is_error(status)) return status;
          }
        }

        delimits->array[delimits->used] = first_slash;
        delimits->used++;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;
      }
    }
    else if (buffer->string[range->start] == f_fss_delimit_quote_single || buffer->string[range->start] == f_fss_delimit_quote_double) {
      quote_found = buffer->string[range->start];

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      found->start = range->start;
    }

    // identify where the object ends.
    if (!quote_found) {
      status = F_none;

      while (range->start <= range->stop && range->start < buffer->used) {

        status = f_fss_is_space(*buffer, *range);
        if (F_status_is_error(status)) return status;

        if (status == F_true) break;

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;
      } // while

      found->stop = range->start - 1;

      if (buffer->string[range->start] == f_string_eol[0]) {
        range->start++;
        return FL_fss_found_object_content_not;
      }

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      return FL_fss_found_object;
    }
    else {
      f_string_length_t first_slash = 0;
      f_string_length_t slash_count = 0;
      f_string_length_t location = 0;

      while (range->start <= range->stop && range->start < buffer->used) {

        if (buffer->string[range->start] == f_fss_delimit_slash) {
          first_slash = range->start;
          slash_count = 1;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == f_fss_delimit_placeholder) {
              status = f_utf_buffer_increment(*buffer, range, 1);
              if (F_status_is_error(status)) return status;

              continue;
            }
            else if (buffer->string[range->start] != f_fss_delimit_slash) {
              break;
            }

            slash_count++;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (range->start >= buffer->used) {
            found->stop = buffer->used - 1;
            delimits->used = delimit_initial;
            return F_unterminated_group_eos;
          }
          else if (range->start > range->stop) {
            found->stop = range->stop;
            delimits->used = delimit_initial;
            return F_unterminated_group_stop;
          }

          if (buffer->string[range->start] == quote_found) {
            location = range->start;

            // check to see if there is a whitespace, EOS, or EOL after the quoted, if not, then this is not a closing quoted and delimits do not apply.
            if (range->start + 1 <= range->stop && range->start + 1 < buffer->used) {
              range->start++;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));

              if (range->start <= range->stop && range->start < buffer->used) {
                status = f_fss_is_space(*buffer, *range);
                if (F_status_is_error(status)) return status;
              }
              else {
                // EOS or EOL was reached, so it is a valid closing quoted.
                // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE (@todo maybe none on stop?).
                status = F_true;
              }
            }
            else {
              // EOS or EOL was reached, so it is a valid closing quoted.
              // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE (@todo maybe none on stop?).
              status = F_true;
            }

            if (status == F_true) {
              if (quote) {
                if (quote_found == f_fss_delimit_quote_single) {
                  *quote = f_fss_quote_type_single;
                }
                else if (quote_found == f_fss_delimit_quote_double) {
                  *quote = f_fss_quote_type_double;
                }
              }

              range->start = first_slash;

              if (slash_count % 2 == 0) {
                if (delimits->used + (slash_count / 2) >= delimits->size) {
                  if (delimits->used + (slash_count / 2) >= f_array_length_t_size) {
                    return F_status_set_error(F_buffer_too_large);
                  }

                  f_macro_string_lengths_t_resize(status, (*delimits), delimits->size + (slash_count / 2));
                  if (F_status_is_error(status)) return status;
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

                range->start = location + 1;

                while (buffer->string[range->start] == f_fss_delimit_placeholder) {
                  range->start++;

                  if (range->start >= buffer->used) return F_none_eos;
                  if (range->start > range->stop) return F_none_stop;
                } // while

                if ((status = f_fss_is_graph(*buffer, *range)) == F_true) {

                  while (range->start <= range->stop && range->start < buffer->used && buffer->string[range->start] != f_string_eol[0]) {

                    status = f_utf_buffer_increment(*buffer, range, 1);
                    if (F_status_is_error(status)) return status;
                  } // while

                  if (range->start >= buffer->used) {
                    found->stop = buffer->used - 1;
                    return F_data_not_eos;
                  }
                  else if (range->start > range->stop) {
                    found->stop = range->stop;
                    return F_data_not_stop;
                  }

                  status = f_utf_buffer_increment(*buffer, range, 1);
                  if (F_status_is_error(status)) return status;

                  return FL_fss_found_object_not;
                }
                else if (F_status_is_error(status)) {
                  return status;
                }
                else if (buffer->string[range->start] == f_string_eol[0]) {
                  found->stop = location - 1;
                  range->start++;
                  return FL_fss_found_object_content_not;
                }

                found->stop = location - 1;

                status = f_utf_buffer_increment(*buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return FL_fss_found_object;
              }
              else {
                if (delimits->used + (slash_count / 2) >= delimits->size) {
                  if (delimits->used + (slash_count / 2) >= f_array_length_t_size) {
                    return F_status_set_error(F_buffer_too_large);
                  }

                  f_macro_string_lengths_t_resize(status, (*delimits), delimits->size + (slash_count / 2) + 1);
                  if (F_status_is_error(status)) return status;
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

                range->start = location;
              }
            }
            else {
              range->start = location;
            }
          }
        }
        else if (buffer->string[range->start] == quote_found) {
          // check to see if there is a whitespace, EOS, or EOL after the quoted, if not, then this is not a closing quoted.
          {
            location = range->start;

            if (range->start + 1 <= range->stop && range->start + 1 < buffer->used) {
              range->start++;

              fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));

              if (range->start <= range->stop && range->start < buffer->used) {
                status = f_fss_is_space(*buffer, *range);
                if (F_status_is_error(status)) return status;
              }
              else {
                // EOS or EOL was reached, so it is a valid closing quoted.
                // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE (@todo maybe none on stop?).
                status = F_true;
              }
            }
            else {
              // EOS or EOL was reached, so it is a valid closing quoted.
              // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE (@todo maybe none on stop?).
              status = F_true;
            }

            range->start = location;
          }

          if (status == F_true) {
            if (quote) {
              if (quote_found == f_fss_delimit_quote_single) {
                *quote = f_fss_quote_type_single;
              }
              else if (quote_found == f_fss_delimit_quote_double) {
                *quote = f_fss_quote_type_double;
              }
            }

            found->stop = range->start - 1;

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) return status;

            while (range->start <= range->stop && range->start < buffer->used) {

              if (buffer->string[range->start] == f_string_eol[0]) {
                range->start++;
                return FL_fss_found_object_content_not;
              }
              else if ((status = f_fss_is_space(*buffer, *range)) == F_true) {
                status = f_utf_buffer_increment(*buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return FL_fss_found_object;
              }
              else if (F_status_is_error(status)) {
                return status;
              }
              else if (buffer->string[range->start] != f_fss_delimit_placeholder) {

                while (range->start <= range->stop && range->start < buffer->used && buffer->string[range->start] != f_string_eol[0]) {

                  status = f_utf_buffer_increment(*buffer, range, 1);
                  if (F_status_is_error(status)) return status;
                } // while

                if (range->start >= buffer->used) {
                  found->stop = buffer->used - 1;
                  return F_data_not_eos;
                }
                else if (range->start > range->stop) {
                  found->stop = range->stop;
                  return F_data_not_stop;
                }

                status = f_utf_buffer_increment(*buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return FL_fss_found_object_not;
              }

              status = f_utf_buffer_increment(*buffer, range, 1);
              if (F_status_is_error(status)) return status;
            } // while

            if (range->start >= buffer->used) {
              found->stop = buffer->used - 1;
              return F_none_eos;
            }
            else if (range->start > range->stop) {
              found->stop = range->stop;
              return F_none_stop;
            }
          }
        }
        else if (buffer->string[range->start] == f_string_eol[0]) {
          range->start++;
          return FL_fss_found_object_not;
        }

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) return status;
      } // while

      if (range->start >= buffer->used) {
        found->stop = buffer->used - 1;
        delimits->used = delimit_initial;
        return F_unterminated_group_eos;
      }
      else if (range->start > range->stop) {
        found->stop = range->stop;
        delimits->used = delimit_initial;
        return F_unterminated_group_stop;
      }
    }

    // seek to the end of the line when no valid object is found.
    while (range->start <= range->stop && range->start < buffer->used && buffer->string[range->start] != f_string_eol[0]) {

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    if (range->start >= buffer->used) {
      found->stop = buffer->used - 1;
      return F_data_not_eos;
    }
    else if (range->start > range->stop) {
      found->stop = range->stop;
      return F_data_not_stop;
    }

    status = f_utf_buffer_increment(*buffer, range, 1);
    if (F_status_is_error(status)) return status;

    return FL_fss_found_object_not;
  }
#endif // !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_)

#if !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)
  f_return_status private_fl_fss_basic_write(const bool object_as, const f_string_static_t object, const f_fss_quote_t quote, f_string_range_t *range, f_string_dynamic_t *destination) {
    f_status_t status = F_none;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*range));

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    if (range->start >= object.used) {
      return F_data_not_eos;
    }

    // ensure that there is room for the potential start and stop quotes, a potential delimit at start, and the potential object open character.
    status = private_fl_fss_destination_increase_by(destination->used + (range->stop - range->start) + 4, destination);
    if (F_status_is_error(status)) return status;

    const f_string_length_t input_start = range->start;
    const f_string_length_t used_start = destination->used;

    bool quoted = F_false;
    bool commented = F_false;

    f_string_length_t item_first = 0;
    f_string_length_t item_total = 0;
    f_string_length_t quote_start = 0;
    f_string_length_t i = 0;

    // use placeholders for potential quote and potential delimited quote to avoid doing things such as memmove().
    destination->string[destination->used++] = f_fss_delimit_placeholder;
    destination->string[destination->used++] = f_fss_delimit_placeholder;

    // if there is an initial quote, then this must be quoted and the existing quote must be delimited.
    if (object.string[input_start] == quote) {
      quoted = F_true;
    }
    else if (object_as && object.string[input_start] == f_fss_comment) {
      commented = F_true;
    }

    uint8_t width = 0;

    for (; range->start <= range->stop && range->start < object.used; ) {

      if (object.string[range->start] == f_fss_delimit_slash) {
        item_first = range->start++;
        item_total = 1;

        for (; range->start <= range->stop && range->start < object.used; range->start++) {

          if (object.string[range->start] == f_fss_delimit_slash) {
            item_total++;
          }
          else if (object.string[range->start] != f_fss_delimit_placeholder) {
            break;
          }
        } // for

        if (range->start > range->stop || range->start >= object.used) {

          // slashes before the final quote must be escaped when quoted, add the delimit slashes.
          if (quoted) {

            // if this is the first quote, then only a single delimit slash is needed.
            if (item_first == input_start) {
              status = private_fl_fss_destination_increase(destination);
              if (F_status_is_error(status)) break;

              destination->string[destination->used++] = f_fss_delimit_slash;
            }
            else {
              status = private_fl_fss_destination_increase_by(item_total, destination);
              if (F_status_is_error(status)) break;

              for (i = 0; i < item_total; i++) {
                destination->string[destination->used++] = f_fss_delimit_slash;
              } // for
            }
          }

          status = private_fl_fss_destination_increase_by(item_total, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < item_total; i++) {
            destination->string[destination->used++] = f_fss_delimit_slash;
          } // for

          break;
        }
        else if (object.string[range->start] == f_fss_eol) {
          status = F_status_set_error(F_none_eol);
          break;
        }

        if (object.string[range->start] == quote) {
          item_first = range->start++;

          fl_macro_fss_skip_past_delimit_placeholders(object, (*range));

          if (range->start > range->stop || range->start >= object.used) {
            status = private_fl_fss_destination_increase_by(item_total + 1, destination);
            if (F_status_is_error(status)) break;

            for (i = 0; i < item_total; i++) {
              destination->string[destination->used++] = f_fss_delimit_slash;
            } // for

            destination->string[destination->used++] = quote;

            break;
          }

          // if any space is found after a quote after a slash, then this must be delimited and quoted.
          status = f_fss_is_space(object, *range);
          if (F_status_is_error(status)) break;

          if (status == F_true) {
            quoted = F_true;

            status = private_fl_fss_destination_increase_by(item_total, destination);
            if (F_status_is_error(status)) break;

            // add the slashes that delimit the slashes.
            if (item_first == input_start) {
              status = private_fl_fss_destination_increase(destination);
              if (F_status_is_error(status)) break;

              destination->string[destination->used++] = f_fss_delimit_slash;
            }
            else {
              status = private_fl_fss_destination_increase_by(item_total, destination);
              if (F_status_is_error(status)) break;

              for (i = 0; i < item_total; i++) {
                destination->string[destination->used++] = f_fss_delimit_slash;
              } // for
            }
          }

          width = f_macro_utf_byte_width(object.string[range->start]);

          status = private_fl_fss_destination_increase_by(item_total + width + 1, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < item_total; i++) {
            destination->string[destination->used++] = f_fss_delimit_slash;
          } // for

          destination->string[destination->used++] = quote;

          for (i = 0; i < width; i++) {
            destination->string[destination->used++] = object.string[range->start + i];
          } // for
        }
        else if (object_as && object.string[range->start] == f_fss_comment) {

          // only the first slash needs to be escaped for a comment, and then only if not quoted.
          if (item_first == input_start) {
            commented = F_true;
          }

          status = private_fl_fss_destination_increase_by(item_total + 1, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < item_total; i++) {
            destination->string[destination->used++] = f_fss_delimit_slash;
          } // for

          destination->string[destination->used++] = object.string[range->start];
          range->start++;
          continue;
        }
        else {

          // if any space is found, then this must be quoted.
          status = f_fss_is_space(object, *range);
          if (F_status_is_error(status)) break;

          if (status == F_true) {
            quoted = F_true;
          }

          width = f_macro_utf_byte_width(object.string[range->start]);

          status = private_fl_fss_destination_increase_by(item_total + width, destination);
          if (F_status_is_error(status)) break;

          // there is nothing to delimit, so all slashes should be printed as is.
          for (i = 0; i < item_total; i++) {
            destination->string[destination->used++] = f_fss_delimit_slash;
          } // for

          status = private_fl_fss_destination_increase_by(width, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < width; i++) {
            destination->string[destination->used++] = object.string[range->start + i];
          } // for
        }
      }
      else if (object.string[range->start] == quote) {
        item_first = range->start++;

        // the very first quote, must be escaped, when quoting is disabled.
        if (item_first == input_start) {
          status = private_fl_fss_destination_increase(destination);
          if (F_status_is_error(status)) break;

          destination->string[used_start + 1] = f_fss_delimit_slash;
        }

        fl_macro_fss_skip_past_delimit_placeholders(object, (*range));

        if (range->start > range->stop || range->start >= object.used) {
          status = private_fl_fss_destination_increase(destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = quote;
          break;
        }

        if (object.string[range->start] == quote) {
          status = private_fl_fss_destination_increase(destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = quote;

          // the next quote must also be checked, so do not increment.
          continue;
        }

        // if any space is found, then this must be quoted.
        status = f_fss_is_space(object, *range);
        if (F_status_is_error(status)) break;

        if (status == F_true) {
          if (item_first != input_start) {
            status = private_fl_fss_destination_increase(destination);
            if (F_status_is_error(status)) break;

            destination->string[destination->used++] = f_fss_delimit_slash;
          }

          quoted = F_true;
        }

        width = f_macro_utf_byte_width(object.string[range->start]);

        status = private_fl_fss_destination_increase_by(1 + width, destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = quote;

        for (i = 0; i < width; i++) {
          destination->string[destination->used++] = object.string[range->start + i];
        } // for
      }
      else if (object.string[range->start] == f_fss_eol) {
        status = F_status_set_error(F_none_eol);
        break;
      }
      else if (object.string[range->start] != f_fss_delimit_placeholder) {
        if (!quoted) {
          status = f_fss_is_space(object, *range);
          if (F_status_is_error(status)) break;

          if (status == F_true) {
            quoted = F_true;
          }
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
    } // for

    if (F_status_is_error(status)) {
      destination->used = used_start;
      return status;
    }

    if (quoted) {
      status = private_fl_fss_destination_increase(destination);

      if (F_status_is_error(status)) {
        destination->used = used_start;
        return status;
      }

      destination->string[used_start] = quote;
      destination->string[destination->used++] = quote;

      // The start quote may or may not need to be delimited in this case.
      if (destination->string[input_start] == quote) {
        for (i = input_start + 1; i <= range->stop && i < object.used; i++) {
          if (object.string[i] != f_fss_delimit_placeholder) break;
        } // for

        // only when followed by a space must the start quote be delimited.
        if (i <= range->stop && i < object.used) {
          f_string_range_t range_i = *range;

          range_i.start = i;

          status = f_fss_is_space(object, range_i);

          if (F_status_is_error(status)) {
            destination->used = used_start;
            return status;
          }

          if (status == F_false) {
            destination->string[used_start + 1] = f_fss_delimit_placeholder;
          }
        }
      }
    }
    else if (commented) {
      destination->string[used_start] = f_fss_delimit_slash;
    }

    if (range->start > range->stop) {
      return F_none_stop;
    }

    return F_none_eos;
  }
#endif // !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)

#if !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_basic_content_write_) || !defined(_di_fl_fss_basic_list_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)
  f_return_status private_fl_fss_destination_increase(f_string_dynamic_t *destination) {
    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      if (destination->size + f_fss_default_allocation_step > f_string_length_t_size) {
        if (destination->size + 1 > f_string_length_t_size) {
          return F_status_set_error(F_string_too_large);
        }

        f_macro_string_dynamic_t_resize(status, (*destination), destination->size + 1);
      }
      else {
        f_macro_string_dynamic_t_resize(status, (*destination), destination->size + f_fss_default_allocation_step);
      }
    }

    return status;
  }
#endif // !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_basic_content_write_) || !defined(_di_fl_fss_basic_list_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)

#if !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_basic_content_write_) || !defined(_di_fl_fss_basic_list_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)
  f_return_status private_fl_fss_destination_increase_by(const f_string_length_t amount, f_string_dynamic_t *destination) {
    f_status_t status = F_none;

    if (destination->used + amount > destination->size) {
      if (destination->size + amount > f_string_length_t_size) {
        return F_status_set_error(F_string_too_large);
      }

      f_macro_string_dynamic_t_resize(status, (*destination), destination->size + amount);
    }

    return status;
  }
#endif // !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_basic_content_write_) || !defined(_di_fl_fss_basic_list_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)

#ifdef __cplusplus
} // extern "C"
#endif
