#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_iki_content_is_
  f_status_t f_iki_content_is(const f_string_static_t content, const uint8_t quote) {
    #ifndef _di_level_0_parameter_checking_
      if (content.used > content.size) return F_status_set_error(F_parameter);
      if (quote != F_iki_syntax_quote_single_s && quote != F_iki_syntax_quote_double_s) return F_status_set_error(F_parameter);
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
      if (quote != F_iki_syntax_quote_single_s && quote != F_iki_syntax_quote_double_s) return F_status_set_error(F_parameter);
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
  f_status_t f_iki_read(f_state_t state, f_string_static_t *buffer, f_string_range_t *range, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!range) return F_status_set_error(F_parameter);
      if (!variable) return F_status_set_error(F_parameter);
      if (!vocabulary) return F_status_set_error(F_parameter);
      if (!content) return F_status_set_error(F_parameter);
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

    // skip past all initial non-word, non-dash, and non-plus.
    macro_f_iki_seek_word_dash_plus(status, buffer, range, width_max, F_true);

    if (F_status_is_error(status)) {
      return status;
    }
    else if (range->start > range->stop) {
      return F_data_not_stop;
    }
    else if (range->start >= buffer->used) {
      return F_data_not_eos;
    }

    f_string_range_t found_vocabulary = f_string_range_t_initialize;
    f_array_length_t found_content = 0;

    found_vocabulary.start = range->start;

    f_array_length_t vocabulary_slash_first = range->start;

    uint8_t quote = 0;

    bool vocabulary_delimited = F_false;
    bool find_next = F_false;

    // delimits must only be applied once a valid object is found.
    f_array_lengths_t delimits = f_array_lengths_t_initialize;

    do {

      // find the start and end of the vocabulary name.
      while (range->start <= range->stop && range->start < buffer->used) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            status = F_status_set_error(F_interrupt);
            break;
          }
        }

        if (buffer->string[range->start] == F_iki_syntax_placeholder_s) {
          ++range->start;
          continue;
        }

        if (buffer->string[range->start] == F_iki_syntax_separator_s) {
          if (range->start == found_vocabulary.start) {
            status = f_utf_buffer_increment(*buffer, range, 1);

            break;
          }

          vocabulary_delimited = F_false;
          found_vocabulary.stop = range->start - 1;

          do {
            status = f_utf_buffer_increment(*buffer, range, 1);
          } while (F_status_is_fine(status) && buffer->string[range->start] == F_iki_syntax_placeholder_s);

          if (F_status_is_error(status)) break;

          // found a valid vocabulary name.
          if (buffer->string[range->start] == F_iki_syntax_quote_single_s || buffer->string[range->start] == F_iki_syntax_quote_double_s) {
            quote = buffer->string[range->start];
            ++range->start;

            break;
          }

          // this is not a valid vocabulary name so seek until a non-word, non-dash, or non-plus character.
          macro_f_iki_seek_word_dash_plus(status, buffer, range, width_max, F_false);
          if (F_status_is_error(status)) break;

          break;
        }
        else if (buffer->string[range->start] == F_iki_syntax_slash_s) {
          bool separator_found = F_false;

          vocabulary_slash_first = range->start;

          // the slash only needs to be delimited if it were to otherwise be a valid vocabulary name.
          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == F_iki_syntax_placeholder_s) {
              ++range->start;
              continue;
            }

            if (separator_found) {
              if (buffer->string[range->start] == F_iki_syntax_quote_single_s || buffer->string[range->start] == F_iki_syntax_quote_double_s) {
                vocabulary_delimited = F_true;

                quote = buffer->string[range->start];
                ++range->start;
                break;
              }
              else {
                find_next = F_true;
                break;
              }
            }
            else if (buffer->string[range->start] == F_iki_syntax_separator_s) {
              separator_found = F_true;
            }
            else if (buffer->string[range->start] != F_iki_syntax_slash_s) {
              find_next = F_true;
              break;
            }

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) break;
          } // while

          break;
        }
        else {
          macro_f_iki_determine_width_max(buffer, range, width_max);

          status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max, F_false);
          if (F_status_is_error(status)) break;

          // current word-dash-plus block is not a valid variable name, try again.
          if (status == F_false) {
            macro_f_iki_seek_word_dash_plus(status, buffer, range, width_max, F_true);

            if (F_status_is_error(status)) {
              break;
            }
            else if (range->start > range->stop) {
              macro_f_array_lengths_t_delete_simple(delimits);

              return F_data_not_stop;
            }
            else if (range->start >= buffer->used) {
              macro_f_array_lengths_t_delete_simple(delimits);

              return F_data_not_eos;
            }

            found_vocabulary.start = range->start;
          }
        }

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) break;
      } // while

      if (F_status_is_error(status)) {
        macro_f_array_lengths_t_delete_simple(delimits);

        return status;
      }

      // process potentially valid content.
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

          if (buffer->string[range->start] == F_iki_syntax_placeholder_s) {
            ++range->start;

            continue;
          }

          if (buffer->string[range->start] == quote) {

            // this is a valid vocabulary name and content, but if it is delimited, save the delimit and ignore.
            if (vocabulary_delimited) {
              macro_f_iki_allocate_delimits_if_necessary(state, status, delimits);
              if (F_status_is_error(status)) break;

              delimits.array[delimits.used] = vocabulary_slash_first;
              ++delimits.used;

              find_next = F_true;
              vocabulary_delimited = F_false;
              quote = 0;

              ++range->start;
              break;
            }
            else {
              macro_f_iki_allocate_ranges_if_necessary(state, status, (*variable));

              if (F_status_is_fine(status)) {
                macro_f_iki_allocate_ranges_if_necessary(state, status, (*vocabulary));
              }

              if (F_status_is_fine(status)) {
                macro_f_iki_allocate_ranges_if_necessary(state, status, (*content));
              }

              if (F_status_is_error(status)) break;

              variable->array[variable->used].start = found_vocabulary.start;
              variable->array[variable->used].stop = range->start;
              ++variable->used;

              vocabulary->array[vocabulary->used].start = found_vocabulary.start;
              vocabulary->array[vocabulary->used].stop = found_vocabulary.stop;
              ++vocabulary->used;

              content->array[content->used].start = found_content;
              content->array[content->used].stop = range->start - 1;
              ++content->used;

              for (f_array_length_t i = 0; i < delimits.used; ++i) {
                buffer->string[delimits.array[i]] = F_iki_syntax_placeholder_s;
              } // for

              macro_f_array_lengths_t_delete_simple(delimits);
              if (F_status_is_error(status)) return status;

              ++range->start;

              if (range->start > range->stop) {
                return F_none_stop;
              }

              if (range->start >= buffer->used) {
                return F_none_eos;
              }

              return F_none;
            }
          }
          else if (buffer->string[range->start] == F_iki_syntax_slash_s) {
            f_array_length_t content_slash_first = range->start;
            f_array_length_t content_slash_total = 0;

            while (range->start <= range->stop && range->start < buffer->used) {

              if (buffer->string[range->start] == F_iki_syntax_placeholder_s) {
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

                if (delimits.used + content_slash_delimits > delimits.size) {
                  if (delimits.used + content_slash_delimits > F_array_length_t_size_d) {
                    status = F_status_set_error(F_string_too_large);
                  }
                  else {
                    macro_f_array_lengths_t_resize(status, delimits, delimits.used + content_slash_delimits);
                  }

                  if (F_status_is_error(status)) break;
                }

                content_range.start = content_slash_first;
                content_range.stop = range->stop;

                while (i < content_slash_delimits) {

                  if (buffer->string[content_range.start] == F_iki_syntax_slash_s) {
                    delimits.array[delimits.used] = content_range.start;
                    ++delimits.used;

                    ++i;
                  }

                  status = f_utf_buffer_increment(*buffer, (&content_range), 1);
                  if (F_status_is_error(status)) break;
                } // while

                if (F_status_is_error(status)) break;

                // valid content's ending quote is not delimited, save and return.
                if (content_slash_total % 2 == 0) {

                  // this is a valid vocabulary name and content, but if it is delimited, save the delimit and ignore.
                  if (vocabulary_delimited) {
                    macro_f_iki_allocate_delimits_if_necessary(state, status, delimits);
                    if (F_status_is_error(status)) break;

                    delimits.array[delimits.used] = vocabulary_slash_first;
                    ++delimits.used;

                    vocabulary_delimited = F_false;
                    quote = 0;

                    ++range->start;

                    // skip past all initial non-word, non-dash, and non-plus.
                    macro_f_iki_seek_word_dash_plus(status, buffer, range, width_max, F_true);

                    found_vocabulary.start = range->start;
                  }
                  else {
                    macro_f_iki_allocate_ranges_if_necessary(state, status, (*variable));

                    if (F_status_is_fine(status)) {
                      macro_f_iki_allocate_ranges_if_necessary(state, status, (*vocabulary));
                    }

                    if (F_status_is_fine(status)) {
                      macro_f_iki_allocate_ranges_if_necessary(state, status, (*content));
                    }

                    if (F_status_is_error(status)) break;

                    variable->array[variable->used].start = found_vocabulary.start;
                    variable->array[variable->used].stop = range->start;
                    ++variable->used;

                    vocabulary->array[vocabulary->used].start = found_vocabulary.start;
                    vocabulary->array[vocabulary->used].stop = found_vocabulary.stop;
                    ++vocabulary->used;

                    content->array[content->used].start = found_content;
                    content->array[content->used].stop = range->start - 1;
                    ++content->used;

                    for (f_array_length_t i = 0; i < delimits.used; ++i) {
                      buffer->string[delimits.array[i]] = F_iki_syntax_placeholder_s;
                    } // for

                    macro_f_array_lengths_t_delete_simple(delimits);
                    if (F_status_is_error(status)) return status;

                    ++range->start;

                    if (range->start > range->stop) {
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
              else if (buffer->string[range->start] != F_iki_syntax_slash_s) {
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
        macro_f_array_lengths_t_delete_simple(delimits);

        return status;
      }

      if (find_next) {
        macro_f_iki_seek_word_dash_plus(status, buffer, range, width_max, F_true);

        found_vocabulary.start = range->start;
        find_next = F_false;
      }

    } while (range->start <= range->stop && range->start < buffer->used);

    for (f_array_length_t i = 0; i < delimits.used; ++i) {
      buffer->string[delimits.array[i]] = F_iki_syntax_placeholder_s;
    } // for

    macro_f_array_lengths_t_delete_simple(delimits);
    if (F_status_is_error(status)) return status;

    if (range->start > range->stop) {
      return F_data_not_stop;
    }

    return F_data_not_eos;
  }
#endif // _di_f_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif
