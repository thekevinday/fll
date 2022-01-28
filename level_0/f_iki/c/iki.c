#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_iki_content_is_
  f_status_t f_iki_content_is(const f_string_static_t content, const uint8_t quote) {
    #ifndef _di_level_0_parameter_checking_
      if (content.used > content.size) return F_status_set_error(F_parameter);
      if (quote != f_iki_syntax_quote_single_s.string[0] && quote != f_iki_syntax_quote_double_s.string[0]) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_string_range_t range = macro_f_string_range_t_initialize(content.used);

    return private_f_iki_content_partial_is(content, range, quote);
  }
#endif // _di_f_iki_content_is_

#ifndef _di_f_iki_content_partial_is_
  f_status_t f_iki_content_partial_is(const f_string_static_t content, const f_string_range_t range, const uint8_t quote) {
    #ifndef _di_level_0_parameter_checking_
      if (content.used > content.size) return F_status_set_error(F_parameter);
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= content.used) return F_status_set_error(F_parameter);
      if (quote != f_iki_syntax_quote_single_s.string[0] && quote != f_iki_syntax_quote_double_s.string[0]) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_content_partial_is(content, range, quote);
  }
#endif // _di_f_iki_content_partial_is_

#ifndef _di_f_iki_object_is_
  f_status_t f_iki_object_is(const f_string_static_t object) {
    #ifndef _di_level_0_parameter_checking_
      if (object.used > object.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_string_range_t range = macro_f_string_range_t_initialize(object.used);

    return private_f_iki_object_partial_is(object, range);
  }
#endif // _di_f_iki_object_is_

#ifndef _di_f_iki_object_partial_is_
  f_status_t f_iki_object_partial_is(const f_string_static_t object, const f_string_range_t range) {
    #ifndef _di_level_0_parameter_checking_
      if (object.used > object.size) return F_status_set_error(F_parameter);
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= object.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_object_partial_is(object, range);
  }
#endif // _di_f_iki_object_partial_is_

#ifndef _di_f_iki_read_
  f_status_t f_iki_read(const f_state_t state, f_string_static_t * const buffer, f_string_range_t *range, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content, f_iki_delimits_t *delimits) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!variable) return F_status_set_error(F_parameter);
      if (!vocabulary) return F_status_set_error(F_parameter);
      if (!content) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer->used) {
      return F_data_not;
    }

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    if (range->start >= buffer->used) {
      return F_data_not_eos;
    }

    f_status_t status = F_none;
    f_array_length_t width_max = 0;

    if (width_max > buffer->used - range->start) {
      width_max = buffer->used - range->start;
    }

    status = private_f_iki_seek_special(*buffer, range);

    if (F_status_is_error(status)) {
      return status;
    }

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    if (range->start >= buffer->used) {
      return F_data_not_eos;
    }

    f_string_range_t found_vocabulary = f_string_range_t_initialize;
    f_array_length_t found_content = 0;
    f_array_length_t vocabulary_slash_first = range->start;
    const f_array_length_t delimits_used = delimits->used;

    uint8_t quote = 0;

    bool vocabulary_delimited = F_false;
    bool find_next = F_false;

    found_vocabulary.start = range->start;

    do {

      // Find the start and end of the vocabulary name.
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

        if (buffer->string[range->start] == f_iki_syntax_separator_s.string[0]) {
          if (range->start == found_vocabulary.start) {
            ++range->start;

            break;
          }

          vocabulary_delimited = F_false;
          found_vocabulary.stop = range->start - 1;

          do {
            status = f_utf_buffer_increment(*buffer, range, 1);
          } while (F_status_is_fine(status) && buffer->string[range->start] == f_iki_syntax_placeholder_s.string[0]);

          if (F_status_is_error(status)) break;

          // Found a valid vocabulary name.
          if (buffer->string[range->start] == f_iki_syntax_quote_single_s.string[0] || buffer->string[range->start] == f_iki_syntax_quote_double_s.string[0]) {
            quote = buffer->string[range->start++];

            break;
          }

          break;
        }

        if (buffer->string[range->start] == f_iki_syntax_slash_s.string[0]) {
          bool separator_found = F_false;

          vocabulary_slash_first = range->start;

          // The slash only needs to be delimited if it were to otherwise be a valid vocabulary name.
          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == f_iki_syntax_placeholder_s.string[0]) {
              ++range->start;

              continue;
            }

            if (separator_found) {
              if (buffer->string[range->start] == f_iki_syntax_quote_single_s.string[0] || buffer->string[range->start] == f_iki_syntax_quote_double_s.string[0]) {
                vocabulary_delimited = F_true;
                quote = buffer->string[range->start++];

                break;
              }
              else {
                find_next = F_true;

                break;
              }
            }
            else if (buffer->string[range->start] == f_iki_syntax_separator_s.string[0]) {
              separator_found = F_true;
            }
            else if (buffer->string[range->start] != f_iki_syntax_slash_s.string[0]) {
              find_next = F_true;

              break;
            }

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          break;
        }

        width_max = (range->stop - range->start) + 1;

        if (width_max > buffer->used - range->start) {
          width_max = buffer->used - range->start;
        }

        status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max, F_false);
        if (F_status_is_error(status)) break;

        // Current word-dash-plus block is not a valid variable name, try again.
        if (status == F_false) {
          status = private_f_iki_seek_special(*buffer, range);
          if (F_status_is_error(status)) break;

          if (range->start > range->stop) {
            delimits->used = delimits_used;

            return F_data_not_stop;
          }

          if (range->start >= buffer->used) {
            delimits->used = delimits_used;

            return F_data_not_eos;
          }

          found_vocabulary.start = range->start;
        }

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) break;
      } // while

      if (F_status_is_error(status)) {
        delimits->used = delimits_used;

        return status;
      }

      // Process potentially valid content.
      if (quote) {
        found_content = range->start;

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

            // This is a valid vocabulary name and content, but if it is delimited, save the delimit and ignore.
            if (vocabulary_delimited) {
              status = f_type_array_lengths_increase(state.step_small, delimits);
              if (F_status_is_error(status)) break;

              delimits->array[delimits->used++] = vocabulary_slash_first;

              find_next = F_true;
              vocabulary_delimited = F_false;
              quote = 0;

              ++range->start;
              break;
            }

            status = f_string_ranges_increase(state.step_small, variable);
            if (F_status_is_error(status)) break;

            status = f_string_ranges_increase(state.step_small, vocabulary);
            if (F_status_is_error(status)) break;

            status = f_string_ranges_increase(state.step_small, content);
            if (F_status_is_error(status)) break;

            variable->array[variable->used].start = found_vocabulary.start;
            variable->array[variable->used++].stop = range->start;

            vocabulary->array[vocabulary->used].start = found_vocabulary.start;
            vocabulary->array[vocabulary->used++].stop = found_vocabulary.stop;

            content->array[content->used].start = found_content;
            content->array[content->used++].stop = range->start - 1;

            if (++range->start > range->stop) {
              return F_none_stop;
            }

            if (range->start >= buffer->used) {
              return F_none_eos;
            }

            return F_none;
          }
          else if (buffer->string[range->start] == f_iki_syntax_slash_s.string[0]) {
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

                status = f_type_array_lengths_increase_by(content_slash_delimits, delimits);
                if (F_status_is_error(status)) break;

                content_range.start = content_slash_first;
                content_range.stop = range->stop;

                while (i < content_slash_delimits) {

                  if (buffer->string[content_range.start] == f_iki_syntax_slash_s.string[0]) {
                    delimits->array[delimits->used++] = content_range.start;
                    ++i;
                  }

                  status = f_utf_buffer_increment(*buffer, (&content_range), 1);
                  if (F_status_is_error(status)) break;
                } // while

                if (F_status_is_error(status)) break;

                // Valid content's ending quote is not delimited, save and return.
                if (content_slash_total % 2 == 0) {

                  // This is a valid vocabulary name and content, but if it is delimited, save the delimit and ignore.
                  if (vocabulary_delimited) {
                    status = f_type_array_lengths_increase(state.step_small, delimits);
                    if (F_status_is_error(status)) break;

                    delimits->array[delimits->used++] = vocabulary_slash_first;

                    vocabulary_delimited = F_false;
                    quote = 0;

                    ++range->start;

                    // Skip past all initial non-word, non-dash, and non-plus.
                    status = private_f_iki_seek_special(*buffer, range);

                    found_vocabulary.start = range->start;
                  }
                  else {
                    status = f_string_ranges_increase(state.step_small, variable);
                    if (F_status_is_error(status)) break;

                    status = f_string_ranges_increase(state.step_small, vocabulary);
                    if (F_status_is_error(status)) break;

                    status = f_string_ranges_increase(state.step_small, content);
                    if (F_status_is_error(status)) break;

                    variable->array[variable->used].start = found_vocabulary.start;
                    variable->array[variable->used++].stop = range->start;

                    vocabulary->array[vocabulary->used].start = found_vocabulary.start;
                    vocabulary->array[vocabulary->used++].stop = found_vocabulary.stop;

                    content->array[content->used].start = found_content;
                    content->array[content->used++].stop = range->start - 1;

                    if (++range->start > range->stop) {
                      return F_none_stop;
                    }

                    if (range->start >= buffer->used) {
                      return F_none_eos;
                    }

                    return F_none;
                  }
                }

                break;
              }

              if (buffer->string[range->start] != f_iki_syntax_slash_s.string[0]) {
                break;
              }

              ++content_slash_total;

              status = f_utf_buffer_increment(*buffer, range, 1);
              if (F_status_is_error(status)) break;
            } // while

            if (F_status_is_error(status)) break;
          }

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) break;
        } // while
      }
      else {
        vocabulary_delimited = F_false;
        find_next = F_true;
      }

      if (F_status_is_error(status)) {
        delimits->used = delimits_used;

        return status;
      }

      if (find_next) {
        status = private_f_iki_seek_special(*buffer, range);

        found_vocabulary.start = range->start;
        find_next = F_false;
      }

    } while (range->start <= range->stop && range->start < buffer->used);

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    return F_data_not_eos;
  }
#endif // _di_f_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif
