#include <level_0/fss.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_decrement_buffer_
  f_return_status f_fss_decrement_buffer(const f_string_static buffer, f_string_range *location, const f_string_length step) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer.used <= 0) return F_status_set_error(F_parameter);
      if (location->start < 0) return F_status_set_error(F_parameter);
      if (location->stop < location->start) return F_status_set_error(F_parameter);
      if (location->start >= buffer.used) return F_status_set_error(F_parameter);
      if (step < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (location->start < 1) return F_none_eos;

    f_string_length i = 0;
    unsigned short width = 0;

    do {
      width = f_macro_utf_byte_width(buffer.string[location->start - 1]);

      if (width > location->start) {
        if (width > 1) {
          return F_status_set_error(F_incomplete_utf_eos);
        }

        return F_none_eos;
      }

      i++;
      location->start -= width;
    } while (i < step);

    return F_none;
  }
#endif // _di_f_fss_decrement_buffer_

#ifndef _di_f_fss_increment_buffer_
  f_return_status f_fss_increment_buffer(const f_string_static buffer, f_string_range *location, const f_string_length step) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer.used <= 0) return F_status_set_error(F_parameter);
      if (location->start < 0) return F_status_set_error(F_parameter);
      if (location->stop < location->start) return F_status_set_error(F_parameter);
      if (location->start >= buffer.used) return F_status_set_error(F_parameter);
      if (step < 1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length i = 0;
    unsigned short width = 0;

    do {
      width = f_macro_utf_byte_width(buffer.string[location->start]);

      if (location->start + width > location->stop) {
        if (width > 1) {
          return F_status_set_error(F_incomplete_utf_stop);
        }

        location->start += width;
        return F_none_stop;
      }
      else if (location->start + width >= buffer.used) {
        if (width > 1) {
          return F_status_set_error(F_incomplete_utf_eos);
        }

        location->start += width;
        return F_none_eos;
      }

      i++;
      location->start += width;
    } while (i < step);

    return F_none;
  }
#endif // _di_f_fss_increment_buffer_

#ifndef _di_f_fss_is_graph_
  f_return_status f_fss_is_graph(const f_string_static buffer, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer.used <= 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    return f_utf_is_graph(buffer.string + range.start, width_max);
  }
#endif // _di_f_fss_is_graph_

#ifndef _di_f_fss_is_space_
  f_return_status f_fss_is_space(const f_string_static buffer, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer.used <= 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    return f_utf_is_whitespace(buffer.string + range.start, width_max);
  }
#endif // _di_f_fss_is_space_

#ifndef _di_f_fss_shift_delimiters_
  f_return_status f_fss_shift_delimiters(f_string_dynamic *buffer, const f_string_range range) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer->used <= 0) return F_status_set_error(F_parameter);
      if (range.start < 0) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (range.start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_length position = 0;
    f_string_length distance = 0;
    unsigned short utf_width = 0;
    unsigned short i = 0;

    position = range.start;

    while (position < buffer->used && position <= range.stop) {
      if (buffer->string[position] == f_fss_delimit_placeholder) {
        distance++;
      }

      // do not waste time trying to process what is only going to be replaced with a delimit placeholder
      if (position + distance >= buffer->used || position + distance > range.stop) {
        break;
      }

      utf_width = f_macro_utf_byte_width_is(buffer->string[position]);
      if (utf_width > 1) {
        // not enough space in buffer or in range range to process UTF-8 character.
        if (position + utf_width >= buffer->used || position + utf_width > range.stop) {
          return F_status_set_error(F_utf);
        }

        if (distance > 0) {
          while (utf_width > 0) {
            buffer->string[position] = buffer->string[position + distance];
            utf_width--;
            position++;
          }
        }
      }
      else {
        // shift everything down one for each placeholder found
        if (distance > 0) {
          buffer->string[position] = buffer->string[position + distance];
        }

        position++;
      }
    }

    if (distance > 0) {
      while (position < buffer->used + distance && position <= range.stop) {
        buffer->string[position] = f_fss_delimit_placeholder;
        position++;
      }
    }

    return F_none;
  }
#endif // _di_f_fss_shift_delimiters_

#ifndef _di_f_fss_skip_past_space_
  f_return_status f_fss_skip_past_space(const f_string_static buffer, f_string_range *range) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer.used <= 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (range->start < 0) return F_status_set_error(F_parameter);
      if (range->stop < range->start) return F_status_set_error(F_parameter);
      if (range->start >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    unsigned short width = 0;

    f_string_length width_max = (range->stop - range->start) + 1;

    if (width_max > buffer.used - range->start) {
      width_max = buffer.used - range->start;
    }

    for (;;) {
      if (buffer.string[range->start] != f_fss_delimit_placeholder) {
        status = f_utf_is_whitespace(buffer.string + range->start, width_max);

        if (status == F_false) {
          status = f_utf_is_control(buffer.string + range->start, width_max);

          if (status == F_false) {
            status = f_utf_is_zero_width(buffer.string + range->start, width_max);

            if (status == F_true) {
              f_string_length next_width_max = 0;

              for (f_string_length next = range->start + 1; next < buffer.used && next <= range->stop; next += f_macro_utf_byte_width_is(buffer.string[next])) {
                next_width_max = (range->stop - next) + 1;

                status = f_utf_is_whitespace(buffer.string + next, width_max);
                if (status == F_true) {
                  // treat zero-width before a space like a space.
                  break;
                }
                else if (status == F_false) {
                  status = f_utf_is_control(buffer.string + next, width_max);

                  if (status == F_true) {
                    // treat zero-width before a control character like a space.
                    break;
                  }
                  else if (status == F_false) {
                    status = f_utf_is_zero_width(buffer.string + next, width_max);

                    if (status == F_true) {
                      // seek until a non-zero-width is reached.
                      continue;
                    }
                    else if (status == F_false) {
                      // treat zero-width as a non-whitespace non-control character when preceding a non-whitespace non-control character.
                      return F_none;
                    }
                  }
                  else if (F_status_is_error(status)) return status;
                }
                else if (F_status_is_error(status)) return status;
              } // for
            }
            else if (status == F_false) {
              // treat zero-width as a graph when preceding a non-whitespace non-control (that is not a zero-width).
              return F_none;
            }
            else if (F_status_is_error(status)) return status;
          }
          else if (F_status_is_error(status)) return status;
        }
        else if (F_status_is_error(status)) return status;
      }

      if (buffer.string[range->start] == f_string_eol[0]) return F_none_eol;

      width = f_macro_utf_byte_width_is(buffer.string[range->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width >= buffer.used) return F_status_set_error(F_incomplete_utf_eos);
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);
      }

      range->start += width;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_fss_skip_past_space_

#ifndef _di_f_fss_skip_past_non_graph_
  f_return_status f_fss_skip_past_non_graph(const f_string_static buffer, f_string_range *range) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer.used <= 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (range->start < 0) return F_status_set_error(F_parameter);
      if (range->stop < range->start) return F_status_set_error(F_parameter);
      if (range->start >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    unsigned short width = 0;

    f_string_length width_max = (range->stop - range->start) + 1;

    if (width_max > buffer.used - range->start) {
      width_max = buffer.used - range->start;
    }

    for (;;) {
      if (buffer.string[range->start] != f_fss_delimit_placeholder) {
        status = f_utf_is_graph(buffer.string + range->start, width_max);

        if (status == F_true) {
          // stop at a graph.
          break;
        }
        else if (status == F_false) {
          status = f_utf_is_zero_width(buffer.string + range->start, width_max);

          if (status == F_true) {
            f_string_length next_width_max = 0;

            for (f_string_length next = range->start + 1; next < buffer.used && next <= range->stop; next += f_macro_utf_byte_width_is(buffer.string[next])) {
              next_width_max = (range->stop - next) + 1;

              status = f_utf_is_graph(buffer.string + next, width_max);
              if (status == F_true) {
                // treat zero-width as a graph when preceding a graph.
                return F_none;
              }
              else if (status == F_false) {
                status = f_utf_is_zero_width(buffer.string + next, width_max);

                if (status == F_true) {
                  // seek until a non-zero-width is reached.
                  continue;
                }
                else if (status == F_false) {
                  // treat zero-width as a non-graph when preceding a non-graph (that is not a zero-width).
                  break;
                }
                else if (F_status_is_error(status)) return status;
              }
              else if (F_status_is_error(status)) return status;
            } // for
          }
          else if (status == F_false) {
            // continue on when non-graph and non-zero-width.
            break;
          }
          else if (F_status_is_error(status)) return status;
        }
        else if (F_status_is_error(status)) return status;
      }

      if (F_status_is_error(status)) return status;

      width = f_macro_utf_byte_width_is(buffer.string[range->start]);

      if (width == 0) {
        width = 1;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_incomplete_utf);
      }
      else {
        if (range->start + width >= buffer.used) return F_status_set_error(F_incomplete_utf_eos);
        if (range->start + width > range->stop) return F_status_set_error(F_incomplete_utf_stop);
      }

      range->start += width;

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_fss_skip_past_non_graph_

#ifdef __cplusplus
} // extern "C"
#endif
