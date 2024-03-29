#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_iki_content_is_
  f_status_t f_iki_content_is(const f_string_static_t content, const f_string_static_t quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!quote.used) return F_status_set_error(F_parameter);
      if (quote.string[0] != f_iki_syntax_quote_single_s.string[0] && quote.string[0] != f_iki_syntax_quote_double_s.string[0]) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!content.used) {
      return F_data_not;
    }

    return private_f_iki_content_partial_is(content.string, content.used, quote.string[0]);
  }
#endif // _di_f_iki_content_is_

#ifndef _di_f_iki_content_partial_is_
  f_status_t f_iki_content_partial_is(const f_string_static_t content, const f_string_range_t range, const f_string_static_t quote) {
    #ifndef _di_level_0_parameter_checking_
      if (!quote.used) return F_status_set_error(F_parameter);
      if (quote.string[0] != f_iki_syntax_quote_single_s.string[0] && quote.string[0] != f_iki_syntax_quote_double_s.string[0]) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!content.used) {
      return F_data_not;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (range.start >= content.used) {
      return F_data_not_eos;
    }

    return private_f_iki_content_partial_is(content.string + range.start, (range.stop - range.start) + 1, quote.string[0]);
  }
#endif // _di_f_iki_content_partial_is_

#ifndef _di_f_iki_object_is_
  f_status_t f_iki_object_is(const f_string_static_t object) {

    if (!object.used) {
      return F_data_not;
    }

    return private_f_iki_object_partial_is(object.string, object.used);
  }
#endif // _di_f_iki_object_is_

#ifndef _di_f_iki_object_partial_is_
  f_status_t f_iki_object_partial_is(const f_string_static_t object, const f_string_range_t range) {

    if (!object.used) {
      return F_data_not;
    }

    if (range.start > range.stop) {
      return F_data_not_stop;
    }

    if (range.start >= object.used) {
      return F_data_not_eos;
    }

    return private_f_iki_object_partial_is(object.string + range.start, (range.stop - range.start) + 1);
  }
#endif // _di_f_iki_object_partial_is_

#ifndef _di_f_iki_read_
  f_status_t f_iki_read(const f_state_t state, f_string_static_t * const buffer, f_string_range_t * const range, f_iki_data_t * const data) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!data) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer->used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;
    if (range->start >= buffer->used) return F_data_not_eos;

    f_status_t status = F_none;
    f_array_length_t width_max = 0;

    if (width_max > buffer->used - range->start) {
      width_max = buffer->used - range->start;
    }

    f_string_range_t found_vocabulary = f_string_range_t_initialize;
    f_array_length_t found_content = 0;
    f_array_length_t vocabulary_slash_first = 0;
    const f_array_length_t delimits_used = data->delimits.used;

    uint8_t quote = 0;
    uint8_t wrapped = F_false; // 0x0 (false) = not wapped, 0x1 (true) = wrapped, 0x2 = valid wrapped.

    do {

      // Find the start of the vocabulary name.
      while (range->start <= range->stop && range->start < buffer->used) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            status = F_status_set_error(F_interrupt);

            break;
          }
        }

        width_max = buffer->used - range->start;

        status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max, F_false);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_utf_fragment || F_status_set_fine(status) == F_complete_not_utf) {
            if (state.flag & f_iki_state_flag_utf_fail_on_valid_not_e) break;

            status = F_false;
          }
          else {
            break;
          }
        }

        if (status == F_true) {
          if (!wrapped) {
            found_vocabulary.start = range->start;
            found_vocabulary.stop = range->start;
          }

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) break;

          status = F_true;

          break;
        }

        // Wrapped must be followed by a valid vocabulary name.
        if (buffer->string[range->start] == f_iki_syntax_wrap_open_s.string[0]) {
          found_vocabulary.start = range->start;
          found_vocabulary.stop = range->start;

          wrapped = F_true;
        }
        else if (wrapped) {
          wrapped = F_false;
        }

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) break;
      } // while

      // Find the end of the vocabulary name.
      while (F_status_is_error_not(status) && range->start <= range->stop && range->start < buffer->used) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            status = F_status_set_error(F_interrupt);

            break;
          }
        }

        if (buffer->string[range->start] == f_iki_syntax_placeholder_s.string[0]) {
          ++range->start;

          continue;
        }

        if (buffer->string[range->start] == f_iki_syntax_separator_s.string[0]) {

          // Wrapped must close in a wrap close before the seperator.
          if (wrapped == F_true) {
            status = F_next;

            break;
          }

          do {
            status = f_utf_buffer_increment(*buffer, range, 1);
          } while (F_status_is_fine(status) && buffer->string[range->start] == f_iki_syntax_placeholder_s.string[0] && range->start <= range->stop && range->start < buffer->used);

          if (F_status_is_error(status) || range->start > range->stop || range->start >= buffer->used) break;

          // Found a valid vocabulary name.
          if (buffer->string[range->start] == f_iki_syntax_quote_single_s.string[0] || buffer->string[range->start] == f_iki_syntax_quote_double_s.string[0]) {
            status = F_true;
            quote = buffer->string[range->start];
          }
          else {
            status = F_next;
          }

          break;
        }

        if (buffer->string[range->start] == f_iki_syntax_slash_s.string[0]) {
          bool separator_found = F_false;

          vocabulary_slash_first = range->start;

          // The slash only needs to be delimited if it were to otherwise be a valid vocabulary name.
          while (range->start <= range->stop && range->start < buffer->used) {

            if (state.interrupt) {
              status = state.interrupt((void *) &state, 0);

              if (F_status_set_fine(status) == F_interrupt) {
                status = F_status_set_error(F_interrupt);

                break;
              }
            }

            if (buffer->string[range->start] == f_iki_syntax_placeholder_s.string[0]) {
              ++range->start;

              continue;
            }

            if (separator_found) {

              // Save delimit for a would-be valid IKI that is now delimited.
              if (buffer->string[range->start] == f_iki_syntax_quote_single_s.string[0] || buffer->string[range->start] == f_iki_syntax_quote_double_s.string[0]) {
                status = f_array_lengths_increase(state.step_small, &data->delimits);
                if (F_status_is_error(status)) break;

                data->delimits.array[data->delimits.used++] = vocabulary_slash_first;

                ++range->start;
              }

              status = F_next;

              break;
            }

            if (buffer->string[range->start] == f_iki_syntax_separator_s.string[0]) {
              separator_found = F_true;
            }
            else if (buffer->string[range->start] != f_iki_syntax_slash_s.string[0]) {
              status = F_next;

              break;
            }

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          if (status == F_true) break;
          if (F_status_is_error(status) || range->start > range->stop || range->start >= buffer->used || status == F_next) break;
        }
        else if (buffer->string[range->start] == f_iki_syntax_wrap_open_s.string[0]) {
          status = F_next;

          break;
        }
        else if (wrapped == F_true && buffer->string[range->start] == f_iki_syntax_wrap_close_s.string[0]) {
          wrapped = 0x2;
          found_vocabulary.stop = range->start;
        }
        else if (wrapped == 0x2) {

          // Wrapped close must be immediately before a separator (ignoring any placeholders in between).
          status = F_next;

          break;
        }
        else {
          width_max = buffer->used - range->start;

          status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max, F_false);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_utf_fragment || F_status_set_fine(status) == F_complete_not_utf) {
              if (state.flag & f_iki_state_flag_utf_fail_on_valid_not_e) break;

              status = F_false;
            }
            else {
              break;
            }
          }

          if (status == F_true) {
            found_vocabulary.stop = range->start;
          }
          else {

            // Not a valid IKI vocabulary name.
            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) break;

            status = F_next;

            break;
          }
        }

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) break;
      } // while

      if (F_status_is_error(status) || range->start > range->stop || range->start >= buffer->used) break;

      if (status == F_next) {
        quote = 0;
        wrapped = F_false;

        continue;
      }

      // Process potentially valid content.
      if (quote) {
        found_content = ++range->start;

        while (range->start <= range->stop && range->start < buffer->used) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (buffer->string[range->start] == f_iki_syntax_placeholder_s.string[0]) {
            ++range->start;

            continue;
          }

          if (buffer->string[range->start] == quote) {
            status = f_string_ranges_increase(state.step_small, &data->variable);
            if (F_status_is_error(status)) break;

            status = f_string_ranges_increase(state.step_small, &data->vocabulary);
            if (F_status_is_error(status)) break;

            status = f_string_ranges_increase(state.step_small, &data->content);
            if (F_status_is_error(status)) break;

            data->variable.array[data->variable.used].start = found_vocabulary.start;
            data->variable.array[data->variable.used++].stop = range->start;

            data->vocabulary.array[data->vocabulary.used].start = wrapped ? found_vocabulary.start + f_iki_syntax_wrap_open_s.used : found_vocabulary.start;
            data->vocabulary.array[data->vocabulary.used++].stop = wrapped ? found_vocabulary.stop - f_iki_syntax_wrap_close_s.used : found_vocabulary.stop;

            data->content.array[data->content.used].start = found_content;
            data->content.array[data->content.used++].stop = range->start - 1;

            if (++range->start > range->stop) return F_none_stop;
            if (range->start >= buffer->used) return F_none_eos;

            return F_none;
          }

          if (buffer->string[range->start] == f_iki_syntax_slash_s.string[0]) {
            f_array_length_t content_slash_first = range->start;
            f_array_length_t content_slash_total = 0;

            while (range->start <= range->stop && range->start < buffer->used) {

              if (buffer->string[range->start] == f_iki_syntax_placeholder_s.string[0]) {
                ++range->start;

                continue;
              }

              if (buffer->string[range->start] == quote) {
                f_array_length_t content_slash_delimits = content_slash_total / 2;
                f_string_range_t content_range = f_string_range_t_initialize;
                f_array_length_t i = 0;

                if (content_slash_total % 2) {
                  ++content_slash_delimits;
                }

                status = f_array_lengths_increase_by(content_slash_delimits, &data->delimits);
                if (F_status_is_error(status)) break;

                content_range.start = content_slash_first;
                content_range.stop = range->stop;

                while (i < content_slash_delimits) {

                  if (buffer->string[content_range.start] == f_iki_syntax_slash_s.string[0]) {
                    data->delimits.array[data->delimits.used++] = content_range.start;
                    ++i;
                  }

                  status = f_utf_buffer_increment(*buffer, (&content_range), 1);
                  if (F_status_is_error(status)) break;
                } // while

                if (F_status_is_error(status)) break;

                // Valid content's ending quote is not delimited, save and return.
                if (content_slash_total % 2 == 0) {
                  status = f_string_ranges_increase(state.step_small, &data->variable);
                  if (F_status_is_error(status)) break;

                  status = f_string_ranges_increase(state.step_small, &data->vocabulary);
                  if (F_status_is_error(status)) break;

                  status = f_string_ranges_increase(state.step_small, &data->content);
                  if (F_status_is_error(status)) break;

                  data->variable.array[data->variable.used].start = found_vocabulary.start;
                  data->variable.array[data->variable.used++].stop = range->start;

                  data->vocabulary.array[data->vocabulary.used].start = wrapped ? found_vocabulary.start + f_iki_syntax_wrap_open_s.used : found_vocabulary.start;
                  data->vocabulary.array[data->vocabulary.used++].stop = wrapped ? found_vocabulary.stop - f_iki_syntax_wrap_close_s.used : found_vocabulary.stop;

                  data->content.array[data->content.used].start = found_content;
                  data->content.array[data->content.used++].stop = range->start - 1;

                  if (++range->start > range->stop) return F_none_stop;
                  if (range->start >= buffer->used) return F_none_eos;

                  return F_none;
                }

                break;
              }

              if (buffer->string[range->start] != f_iki_syntax_slash_s.string[0]) break;

              ++content_slash_total;

              status = f_utf_buffer_increment(*buffer, range, 1);
              if (F_status_is_error(status)) break;
            } // while

            if (F_status_is_error(status)) break;
          }

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while

        quote = 0;
        wrapped = F_false;
      }

      if (F_status_is_error(status) || range->start > range->stop || range->start >= buffer->used) break;

      status = f_utf_buffer_increment(*buffer, range, 1);
      if (F_status_is_error(status)) break;

    } while (range->start <= range->stop && range->start < buffer->used);

    if (F_status_set_fine(status) == F_complete_not_utf_eos || F_status_set_fine(status) == F_complete_not_utf_stop) {
      if (!(state.flag & f_iki_state_flag_utf_fail_on_valid_not_e)) {
        status = F_status_set_fine(status);
      }
    }

    if (F_status_is_error(status)) {
      data->delimits.used = delimits_used;

      return status;
    }

    if (range->start > range->stop) return F_data_not_stop;

    return F_data_not_eos;
  }
#endif // _di_f_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif
