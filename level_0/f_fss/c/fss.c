#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_apply_delimit_
  f_status_t fl_fss_apply_delimit(const f_fss_delimits_t delimits, f_string_static_t *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    for (f_array_length_t i = 0; i < delimits.used; ++i) {

      if (delimits.array[i] < buffer->used) {
        buffer->string[delimits.array[i]] = f_fss_delimit_placeholder;
      }
    } // for

    return F_none;
  }
#endif // _di_fl_fss_apply_delimit_

#ifndef _di_fl_fss_apply_delimit_between_
  f_status_t fl_fss_apply_delimit_between(const f_fss_delimits_t delimits, const f_string_range_t range, f_string_static_t *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    for (f_array_length_t i = 0; i < delimits.used; ++i) {

      if (delimits.array[i] < buffer->used && delimits.array[i] >= range.start && delimits.array[i] <= range.stop) {
        buffer->string[delimits.array[i]] = f_fss_delimit_placeholder;
      }
    } // for

    return F_none;
  }
#endif // _di_fl_fss_apply_delimit_between_

#ifndef _di_f_fss_count_lines_
  f_status_t f_fss_count_lines(const f_string_static_t buffer, const f_array_length_t before, f_array_length_t *line) {
    #ifndef _di_level_0_parameter_checking_
      if (!line) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (before >= buffer.used) {
      return F_none;
    }

    for (f_array_length_t i = before; i > 0; --i) {

      if (buffer.string[i] == f_fss_eol) {
        ++(*line);
      }
    } // for

    if (buffer.string[0] == f_fss_eol) {
      ++(*line);
    }

    return F_none;
  }
#endif // _di_f_fss_count_lines_

#ifndef _di_f_fss_count_lines_range_
  f_status_t f_fss_count_lines_range(const f_string_static_t buffer, const f_string_range_t range, const f_array_length_t before, f_array_length_t *line) {
    #ifndef _di_level_0_parameter_checking_
      if (!line) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range.stop < range.start || range.start >= buffer.used || !buffer.used || before >= buffer.used || before > range.stop) {
      return F_none;
    }

    for (f_array_length_t i = before; i > range.start; --i) {

      if (buffer.string[i] == f_fss_eol) {
        ++(*line);
      }
    } // for

    if (buffer.string[range.start] == f_fss_eol) {
      ++(*line);
    }

    return F_none;
  }
#endif // _di_f_fss_count_lines_range_

#ifndef _di_f_fss_is_graph_
  f_status_t f_fss_is_graph(const f_string_static_t buffer, const f_string_range_t range) {

    if (range.stop < range.start || range.start >= buffer.used || !buffer.used) {
      return F_false;
    }

    f_array_length_t width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    return f_utf_is_graph(buffer.string + range.start, width_max);
  }
#endif // _di_f_fss_is_graph_

#ifndef _di_f_fss_is_space_
  f_status_t f_fss_is_space(const f_string_static_t buffer, const f_string_range_t range) {

    if (range.stop < range.start || range.start >= buffer.used || !buffer.used) {
      return F_false;
    }

    f_array_length_t width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    f_status_t status = f_utf_is_zero_width(buffer.string + range.start, width_max);

    if (status != F_false) {
      if (status == F_true) {
        return F_false;
      }

      return status;
    }

    status = f_utf_is_whitespace(buffer.string + range.start, width_max);

    if (status == F_false) {
      return f_utf_is_control(buffer.string + range.start, width_max);
    }

    return status;
  }
#endif // _di_f_fss_is_space_

#ifndef _di_f_fss_is_zero_width_
  f_status_t f_fss_is_zero_width(const f_string_static_t buffer, const f_string_range_t range) {

    if (range.stop < range.start || range.start >= buffer.used || !buffer.used) {
      return F_false;
    }

    f_array_length_t width_max = (range.stop - range.start) + 1;

    if (width_max > buffer.used - range.start) {
      width_max = buffer.used - range.start;
    }

    return f_utf_is_zero_width(buffer.string + range.start, width_max);
  }
#endif // _di_f_fss_is_zero_width_

#ifndef _di_f_fss_seek_to_eol_
  f_status_t f_fss_seek_to_eol(const f_string_dynamic_t buffer, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    for (;; ++range->start) {

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
      if (buffer.string[range->start] == f_fss_eol) break;
    } // for

    return F_none;
  }
#endif // _di_f_fss_seek_to_eol_

#ifndef _di_f_fss_shift_delimit_
  f_status_t f_fss_shift_delimit(const f_string_range_t range, f_string_dynamic_t *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range.stop < range.start || range.start >= buffer->used || !buffer->used) {
      return F_none;
    }

    f_array_length_t position = 0;
    f_array_length_t distance = 0;

    uint8_t utf_width = 0;

    position = range.start;

    while (position < buffer->used && position <= range.stop) {

      if (buffer->string[position] == f_fss_delimit_placeholder) {
        ++distance;
      }

      // do not waste time trying to process what is only going to be replaced with a delimit placeholder.
      if (position + distance >= buffer->used || position + distance > range.stop) {
        break;
      }

      utf_width = macro_f_utf_byte_width_is(buffer->string[position]);

      if (utf_width > 1) {

        // not enough space in buffer or in range range to process UTF-8 character.
        if (position + utf_width >= buffer->used || position + utf_width > range.stop) {
          return F_status_set_error(F_utf);
        }

        if (distance > 0) {
          while (utf_width) {

            buffer->string[position] = buffer->string[position + distance];
            --utf_width;
            ++position;
          } // while
        }
      }
      else {

        // shift everything down one for each delimit placeholder found.
        if (distance > 0) {
          buffer->string[position] = buffer->string[position + distance];
        }

        ++position;
      }
    }

    if (distance > 0) {
      while (position < buffer->used + distance && position <= range.stop) {

        buffer->string[position] = f_fss_delimit_placeholder;
        ++position;
      }
    }

    return F_none;
  }
#endif // _di_f_fss_shift_delimit_

#ifndef _di_f_fss_skip_past_delimit_
  f_status_t f_fss_skip_past_delimit(const f_string_static_t buffer, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    for (;; ++range->start) {

      if (range->start >= buffer.used) return F_none_eos;
      if (range->start > range->stop) return F_none_stop;
      if (buffer.string[range->start] != f_fss_delimit_placeholder) break;
    } // for

    return F_none;
  }
#endif // _di_f_fss_skip_past_delimit_

#ifndef _di_f_fss_skip_past_space_
  f_status_t f_fss_skip_past_space(const f_string_static_t buffer, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) {
      return F_none_stop;
    }

    if (range->start >= buffer.used || !buffer.used) {
      return F_none_eos;
    }

    f_status_t status = F_none;
    uint8_t width = 0;

    f_array_length_t width_max = (range->stop - range->start) + 1;

    if (width_max > buffer.used - range->start) {
      width_max = buffer.used - range->start;
    }

    for (;;) {

      if (buffer.string[range->start] == f_fss_eol) {
        return F_none_eol;
      }

      if (buffer.string[range->start] == f_fss_delimit_placeholder) {
        ++range->start;

        if (range->start >= buffer.used) {
          return F_none_eos;
        }

        if (range->start > range->stop) {
          return F_none_stop;
        }

        continue;
      }

      status = f_utf_is_whitespace(buffer.string + range->start, width_max);
      if (F_status_is_error(status)) return status;

      if (status == F_false) {
        status = f_utf_is_zero_width(buffer.string + range->start, width_max);
        if (F_status_is_error(status)) return status;

        if (status == F_false) {
          return F_none;
        }
      }

      width = macro_f_utf_byte_width_is(buffer.string[range->start]);

      if (!width) {
        width = 1;
      }
      else if (width == 1) {

        // Do not operate on UTF-8 fragments that are not the first byte of the character.
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width >= buffer.used) {
          return F_status_set_error(F_complete_not_utf_eos);
        }

        if (range->start + width > range->stop) {
          return F_status_set_error(F_complete_not_utf_stop);
        }
      }

      range->start += width;

      if (range->start >= buffer.used) {
        return F_none_eos;
      }

      if (range->start > range->stop) {
        return F_none_stop;
      }

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }
    } // for

    return F_none;
  }
#endif // _di_f_fss_skip_past_space_

#ifndef _di_f_fss_skip_past_non_graph_
  f_status_t f_fss_skip_past_non_graph(const f_string_static_t buffer, f_string_range_t *range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) {
      return F_none_stop;
    }

    if (range->start >= buffer.used || !buffer.used) {
      return F_none_eos;
    }

    f_status_t status = F_none;
    uint8_t width = 0;

    f_array_length_t width_max = (range->stop - range->start) + 1;
    f_array_length_t next = 0;

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
            next = range->start + 1;

            for (; next < buffer.used && next <= range->stop; next += macro_f_utf_byte_width_is(buffer.string[next])) {

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
                else if (F_status_is_error(status)) {
                  return status;
                }
              }
              else if (F_status_is_error(status)) {
                return status;
              }
            } // for
          }
          else if (status == F_false) {

            // continue on when non-graph and non-zero-width.
            break;
          }
          else if (F_status_is_error(status)) {
            return status;
          }
        }
        else if (F_status_is_error(status)) {
          return status;
        }
      }

      width = macro_f_utf_byte_width_is(buffer.string[range->start]);

      if (!width) {
        width = 1;
      }
      else if (width == 1) {

        // Do not operate on UTF-8 fragments that are not the first byte of the character.
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width >= buffer.used) {
          return F_status_set_error(F_complete_not_utf_eos);
        }

        if (range->start + width > range->stop) {
          return F_status_set_error(F_complete_not_utf_stop);
        }
      }

      range->start += width;

      if (range->start >= buffer.used) {
        return F_none_eos;
      }

      if (range->start > range->stop) {
        return F_none_stop;
      }

      width_max = (range->stop - range->start) + 1;

      if (width_max > buffer.used - range->start) {
        width_max = buffer.used - range->start;
      }
    } // for

    if (F_status_is_error(status)) {
      return status;
    }

    return F_none;
  }
#endif // _di_f_fss_skip_past_non_graph_

#ifdef __cplusplus
} // extern "C"
#endif
