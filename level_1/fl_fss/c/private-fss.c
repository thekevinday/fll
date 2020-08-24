#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)
  f_return_status private_fl_fss_basic_object_read(f_string_dynamic *buffer, f_string_range *range, f_fss_object *found, f_fss_quoted *quoted, f_string_lengths *delimits) {
    f_status status = F_none;

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
    const f_string_length delimit_initial = delimits->used;

    // handle quoted support.
    int8_t quote = 0;

    if (quoted) {
      *quoted = 0;
    }

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

      if (range->start >= buffer->used) {
        found->stop = buffer->used - 1;
        return F_none_eos;
      }
      else if (range->start > range->stop) {
        found->stop = range->stop;
        return F_none_stop;
      }

      if (buffer->string[range->start] == f_fss_delimit_quote_single || buffer->string[range->start] == f_fss_delimit_quote_double) {

        // only the first slash before a quoted needs to be escaped (or not) as once there is a slash before a quoted, this cannot ever be a quote object.
        // this simplifies the number of slashes needed.
        if (delimits->used == delimits->size) {
          if (delimits->size + f_fss_default_allocation_step > f_array_length_size) {
            if (delimits->size + 1 > f_array_length_size) {
              return F_status_set_error(F_buffer_too_large);
            }

            f_macro_string_lengths_resize(status, (*delimits), delimits->size + 1);
            if (F_status_is_error(status)) return status;
          }
          else {
            f_macro_string_lengths_resize(status, (*delimits), delimits->size + f_fss_default_allocation_step);
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
      quote = buffer->string[range->start];

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      found->start = range->start;
    }

    // identify where the object ends.
    if (quote == 0) {
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
      while (range->start <= range->stop && range->start < buffer->used) {

        if (buffer->string[range->start] == f_fss_delimit_slash) {
          f_string_length first_slash = range->start;
          f_string_length slash_count = 1;

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

          if (buffer->string[range->start] == quote) {
            f_string_length location = range->start;

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
              if (quoted) {
                if (quote == f_fss_delimit_quote_single) {
                  *quoted = f_fss_quoted_type_single;
                }
                else if (quote == f_fss_delimit_quote_double) {
                  *quoted = f_fss_quoted_type_double;
                }
              }

              range->start = first_slash;

              if (slash_count % 2 == 0) {
                if (delimits->used + (slash_count / 2) >= delimits->size) {
                  if (delimits->used + (slash_count / 2) >= f_array_length_size) {
                    return F_status_set_error(F_buffer_too_large);
                  }

                  f_macro_string_lengths_resize(status, (*delimits), delimits->size + (slash_count / 2));
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

                  while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {
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
                  if (delimits->used + (slash_count / 2) >= f_array_length_size) {
                    return F_status_set_error(F_buffer_too_large);
                  }

                  f_macro_string_lengths_resize(status, (*delimits), delimits->size + (slash_count / 2) + 1);
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
        else if (buffer->string[range->start] == quote) {
          // check to see if there is a whitespace, EOS, or EOL after the quoted, if not, then this is not a closing quoted.
          {
            f_string_length location = range->start;

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
            if (quoted) {
              if (quote == f_fss_delimit_quote_single) {
                *quoted = f_fss_quoted_type_single;
              }
              else if (quote == f_fss_delimit_quote_double) {
                *quoted = f_fss_quoted_type_double;
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

                while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {
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

    // seek to the end of the line when no valid object is found->
    while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {
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

#if !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_)
  f_return_status private_fl_fss_basic_object_write(const f_string_static object, const f_fss_quoted quoted, f_string_range *range, f_string_dynamic *destination) {
    f_status status = F_none;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*range));

    if (range->start > range->stop) return F_data_not_stop;
    else if (range->start >= object.used) return F_data_not_eos;

    // ensure that there is room for the start and stop quotes or a slash delimit and the object open character.
    f_string_length size_allocate = destination->used + (range->stop - range->start) + 3 + f_fss_default_allocation_step_string;

    if (size_allocate > destination->size) {
      f_macro_string_dynamic_resize(status, (*destination), size_allocate);
      if (F_status_is_error(status)) return status;
    }

    const f_string_length position_start = range->start;

    f_string_range destination_position = f_string_range_initialize;

    destination_position.start = destination->used;
    destination_position.stop  = destination->used;

    bool quote = quoted ? F_true : F_false;

    if (quote) {
      if (quoted == f_fss_quoted_type_single) {
        destination->string[destination_position.start] = f_fss_delimit_quote_single;
      }
      else {
        destination->string[destination_position.start] = f_fss_delimit_quote_double;
      }

      destination_position.stop++;
    }

    // @todo: if the string starts with a single or double quoted, it needs to be escaped, but if quotes are detected later on, be sure to re-evaluate escaping.

    if (object.string[range->start] == f_fss_delimit_slash) {
      while (range->start <= range->stop && range->start < object.used) {
        if (object.string[range->start] == f_fss_delimit_placeholder) {
          status = f_utf_buffer_increment(object, range, 1);
          if (F_status_is_error(status)) return status;

          continue;
        }
        else if (object.string[range->start] != f_fss_delimit_slash) {
          break;
        }

        destination->string[destination_position.stop] = object.string[range->start];
        destination_position.stop++;

        status = f_utf_buffer_increment(object, range, 1);
        if (F_status_is_error(status)) return status;
      } // while

      if (range->start <= range->stop && range->start < object.used) {
        if ((quoted == f_fss_quoted_type_single && object.string[range->start] == f_fss_delimit_quote_single) || (quoted == f_fss_quoted_type_double && object.string[range->start] == f_fss_delimit_quote_double)) {
          size_allocate++;

          if (size_allocate > destination->size) {
            f_macro_string_dynamic_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);
            if (F_status_is_error(status)) return status;
          }

          destination->string[destination_position.stop] = f_fss_delimit_slash;
          destination->string[destination_position.stop + 1] = object.string[range->start];
          destination_position.stop += 2;

          status = f_utf_buffer_increment(object, range, 1);
          if (F_status_is_error(status)) return status;
        }
      }
    }
    else if ((quoted == f_fss_quoted_type_single && object.string[range->start] == f_fss_delimit_quote_single) || (quoted == f_fss_quoted_type_double && object.string[range->start] == f_fss_delimit_quote_double)) {
      size_allocate++;

      if (size_allocate > destination->size) {
        f_macro_string_dynamic_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);

        if (F_status_is_error(status)) return status;
      }

      destination->string[destination_position.stop] = f_fss_delimit_slash;
      destination->string[destination_position.stop + 1] = object.string[range->start];
      destination_position.stop += 2;

      status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(status)) return status;
    }

    while (range->start <= range->stop && range->start < object.used) {
      if (object.string[range->start] == f_fss_delimit_placeholder) {
        status = f_utf_buffer_increment(object, range, 1);
        if (F_status_is_error(status)) return status;

        continue;
      }

      if (object.string[range->start] == f_string_eol[0]) {
        if (quote) {
          destination->string[destination_position.stop] = destination->string[destination_position.start];
          destination_position.stop++;
        }

        destination->string[destination_position.stop] = f_fss_basic_open;
        destination->used = destination_position.stop + 1;

        return F_none_eol;
      }

      if (quote) {
        if (object.string[range->start] == f_fss_delimit_slash) {
          f_string_range next = *range;
          f_string_length slashes = 1;

          bool must_delimit = F_false;

          while (next.start <= next.stop && next.start < object.used) {
            if (object.string[next.start] == f_fss_delimit_placeholder) {
              status = f_utf_buffer_increment(object, &next, 1);
              if (F_status_is_error(status)) return status;

              continue;
            }
            else if (object.string[next.start] != f_fss_delimit_slash) {
              break;
            }

            slashes++;

            status = f_utf_buffer_increment(object, &next, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (next.start <= next.stop && next.start < object.used) {
            // identify if quoted exists and could be considered a valid closing quoted.
            if (object.string[next.start] == destination->string[destination_position.start]) {
              fl_macro_fss_skip_past_delimit_placeholders(object, next);

              if (next.start <= next.stop && next.start < object.used) {
                status = f_fss_is_space(*destination, next);

                if (status == F_true) {
                  must_delimit = F_true;
                }
                else if (F_status_is_error(status)) {
                  return status;
                }
              }
              else {
                must_delimit = F_true;
              }
            }
          }
          else {
            // ensure that the slashes before the closing quoted to not delimit the closing quoted.
            must_delimit = F_true;
          }

          if (must_delimit) {
            for (f_string_length i = 0; i < slashes; i++) {
              destination->string[destination_position.stop] = f_fss_delimit_slash;
              destination_position.stop++;
            } // for

            if (slashes % 2) {
              size_allocate++;

              if (size_allocate > destination->size) {
                f_macro_string_dynamic_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);
                if (F_status_is_error(status)) return status;
              }

              destination->string[destination_position.stop] = f_fss_delimit_slash;
              destination_position.stop++;
            }
          }
        }
        else if (object.string[range->start] == destination->string[destination_position.start]) {
          f_string_range next = *range;
          bool must_delimit = F_false;

          status = f_utf_buffer_increment(object, &next, 1);
          if (F_status_is_error(status)) return status;

          fl_macro_fss_skip_past_delimit_placeholders(object, next);

          if (next.start > range->stop || next.start >= object.used) {
            must_delimit = F_true;
          }
          else {
            status = f_fss_is_space(object, next);

            if (status == F_true) {
              must_delimit = F_true;
            }
            else if (F_status_is_error(status)) {
              return status;
            }
          }

          if (must_delimit) {
            size_allocate++;

            if (size_allocate > destination->size) {
              f_macro_string_dynamic_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);
              if (F_status_is_error(status)) return status;
            }

            destination->string[destination_position.stop] = f_fss_delimit_slash;
            destination_position.stop++;
          }
        }
      }
      else {
        status = f_fss_is_space(object, *range);

        if (status == F_true) {
          size_allocate++;

          if (size_allocate > destination->size) {
            f_macro_string_dynamic_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);
            if (F_status_is_error(status)) return status;
          }

          // restart the loop then search for delimit slash or quoted and escape as appropriate.
          range->start = position_start;
          destination_position.stop = destination_position.start;

          destination->string[destination_position.stop] = f_fss_delimit_quote_double;
          destination_position.stop++;

          quote = F_true;

          if (object.string[range->start] == f_fss_delimit_slash) {
            while (range->start <= range->stop && range->start < object.used) {
              if (object.string[range->start] == f_fss_delimit_placeholder) {
                status = f_utf_buffer_increment(object, range, 1);
                if (F_status_is_error(status)) return status;

                continue;
              }
              else if (object.string[range->start] != f_fss_delimit_slash) {
                break;
              }

              destination->string[destination_position.stop] = object.string[range->start];
              destination_position.stop++;

              status = f_utf_buffer_increment(object, range, 1);
              if (F_status_is_error(status)) return status;
            } // while

            if (range->start > range->stop || range->start >= object.used) break;

            if (object.string[range->start] == f_fss_delimit_quote_double) {
              size_allocate++;

              if (size_allocate > destination->size) {
                f_macro_string_dynamic_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);
                if (F_status_is_error(status)) return status;
              }

              destination->string[destination_position.stop] = f_fss_delimit_slash;
              destination_position.stop++;
            }
          }
          else if (object.string[range->start] == f_fss_delimit_quote_double) {
            size_allocate++;

            if (size_allocate > destination->size) {
              f_macro_string_dynamic_resize(status, (*destination), size_allocate + f_fss_default_allocation_step_string);
              if (F_status_is_error(status)) return status;
            }

            destination->string[destination_position.stop] = f_fss_delimit_slash;
            destination_position.stop++;
          }
        }
        else if (F_status_is_error(status)) {
          return status;
        }
      }

      destination->string[destination_position.stop] = object.string[range->start];

      status = f_utf_buffer_increment(object, range, 1);
      if (F_status_is_error(status)) return status;

      destination_position.stop++;
    } // while

    if (quote) {
      destination->string[destination_position.stop] = destination->string[destination_position.start];
      destination_position.stop++;
    }

    destination->string[destination_position.stop] = f_fss_basic_open;
    destination->used = destination_position.stop + 1;

    if (range->start > range->stop) return F_none_stop;
    else if (range->start >= object.used) return F_none_eos;

    return F_none;
  }
#endif // !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_)

#ifdef __cplusplus
} // extern "C"
#endif
