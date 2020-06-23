#include <level_0/iki.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_iki_read_
  f_return_status f_iki_read(f_string_static *buffer, f_string_range *range, f_iki_variable *variable, f_iki_vocabulary *vocabulary, f_iki_content *content) {
    #ifndef _di_level_0_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (variable == 0) return F_status_set_error(F_parameter);
      if (vocabulary == 0) return F_status_set_error(F_parameter);
      if (content == 0) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range->start > range->stop) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;

    f_string_length width_max = 0;

    if (width_max > buffer->used - range->start) {
      width_max = buffer->used - range->start;
    }

    // skip past all initial non-word, non-dash, and non-plus.
    while (range->start <= range->stop && range->start < buffer->used) {
      if (buffer->string[range->start] == f_iki_syntax_placeholder) {
        range->start++;
        continue;
      }

      f_macro_iki_determine_width_max(buffer, range, width_max);

      status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max);
      if (F_status_is_error(status)) return status;

      if (status == F_true) break;

      f_macro_iki_seek_whitespace(status, buffer, range, width_max, F_true);
      if (F_status_is_error(status)) return status;

      f_macro_iki_seek_whitespace(status, buffer, range, width_max, F_false);
      if (F_status_is_error(status)) return status;
    } // while

    if (range->start > range->stop) {
      return F_data_not_stop;
    }
    else if (range->start >= buffer->used) {
      return F_data_not_eos;
    }

    f_string_range found_vocabulary = f_string_range_initialize;
    f_string_length found_content = 0;

    found_vocabulary.start = range->start;

    f_string_length vocabulary_slash_first = range->start;

    uint8_t quote = 0;

    bool vocabulary_delimited = F_false;
    bool find_next = F_false;

    // delimits must only be applied once a valid object is found.
    f_string_lengths delimits = f_string_lengths_initialize;

    do {
      // find the start and end of the vocabulary name.
      while (range->start <= range->stop && range->start < buffer->used) {
        if (buffer->string[range->start] == f_iki_syntax_placeholder) {
          range->start++;
          continue;
        }

        if (buffer->string[range->start] == f_iki_syntax_separator) {
          if (range->start == found_vocabulary.start) {
            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete(status, delimits);
              return status;
            }

            break;
          }

          vocabulary_delimited = F_false;
          found_vocabulary.stop = range->start - 1;

          do {
            status = f_utf_buffer_increment(*buffer, range, 1);
          } while (F_status_is_fine(status) && buffer->string[range->start] == f_iki_syntax_placeholder);

          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete(status, delimits);
            return status;
          }

          // found a valid vocabulary name.
          if (buffer->string[range->start] == f_iki_syntax_quote_single || buffer->string[range->start] == f_iki_syntax_quote_double) {
            quote = buffer->string[range->start];
            range->start++;
            break;
          }

          // this is not a valid vocabulary name so seek until a whitespace to prepare for the next main loop pass.
          f_macro_iki_seek_whitespace(status, buffer, range, width_max, F_true);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete(status, delimits);
            return status;
          }

          break;
        }
        else if (buffer->string[range->start] == f_iki_syntax_slash) {
          bool separator_found = F_false;

          vocabulary_slash_first = range->start;

          // the slash only needs to be delimited if it were to otherwise be a valid vocabulary name.
          while (range->start <= range->stop && range->start < buffer->used) {

            if (buffer->string[range->start] == f_iki_syntax_placeholder) {
              range->start++;
              continue;
            }

            if (separator_found) {
              if (buffer->string[range->start] == f_iki_syntax_quote_single || buffer->string[range->start] == f_iki_syntax_quote_double) {
                vocabulary_delimited = F_true;

                quote = buffer->string[range->start];
                range->start++;
                break;
              }
              else {
                find_next = F_true;
                break;
              }
            }
            else if (buffer->string[range->start] == f_iki_syntax_separator) {
              separator_found = F_true;
            }
            else if (buffer->string[range->start] != f_iki_syntax_slash) {
              find_next = F_true;
              break;
            }

            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete(status, delimits);
              return status;
            }
          } // while

          break;
        }
        else {
          f_macro_iki_determine_width_max(buffer, range, width_max);

          status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete(status, delimits);
            return status;
          }

          if (status == F_false) {
            status = f_utf_buffer_increment(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete(status, delimits);
              return status;
            }

            find_next = F_true;
            break;
          }
        }

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete(status, delimits);
          return status;
        }
      } // while

      // process potentially valid content.
      if (quote) {
        found_content = range->start;

        while (range->start <= range->stop && range->start < buffer->used) {
          if (buffer->string[range->start] == f_iki_syntax_placeholder) {
            range->start++;
            continue;
          }

          if (buffer->string[range->start] == quote) {

            // this is a valid vocabulary name and content, but if it is delimited, save the delimit and ignore.
            if (vocabulary_delimited) {
              f_macro_iki_allocate_delimits_if_necessary(status, delimits);
              if (F_status_is_error(status)) {
                f_macro_string_lengths_delete(status, delimits);
                return status;
              }

              delimits.array[delimits.used] = vocabulary_slash_first;
              delimits.used++;

              find_next = F_true;
              vocabulary_delimited = F_false;
              quote = 0;

              range->start++;
              break;
            }
            else {
              f_macro_iki_allocate_ranges_if_necessary(status, (*variable));

              if (F_status_is_fine(status)) {
                f_macro_iki_allocate_ranges_if_necessary(status, (*vocabulary));
              }

              if (F_status_is_fine(status)) {
                f_macro_iki_allocate_ranges_if_necessary(status, (*content));
              }

              if (F_status_is_error(status)) {
                f_macro_string_lengths_delete(status, delimits);
                return status;
              }

              variable->array[variable->used].start = found_vocabulary.start;
              variable->array[variable->used].stop = range->start;
              variable->used++;

              vocabulary->array[vocabulary->used].start = found_vocabulary.start;
              vocabulary->array[vocabulary->used].stop = found_vocabulary.stop;
              vocabulary->used++;

              content->array[content->used].start = found_content;
              content->array[content->used].stop = range->start - 1;
              content->used++;

              for (f_array_length i = 0; i < delimits.used; i++) {
                buffer->string[delimits.array[i]] = f_iki_syntax_placeholder;
              } // for

              f_macro_string_lengths_delete(status, delimits);
              if (F_status_is_error(status)) return status;

              range->start++;

              if (range->start > range->stop) {
                return F_none_stop;
              }

              if (range->start >= buffer->used) {
                return F_none_eos;
              }

              return F_none;
            }
          }
          else if (buffer->string[range->start] == f_iki_syntax_slash) {
            f_string_length content_slash_first = range->start;
            f_array_length content_slash_total = 0;

            while (range->start <= range->stop && range->start < buffer->used) {
              if (buffer->string[range->start] == f_iki_syntax_placeholder) {
                range->start++;
                continue;
              }

              if (buffer->string[range->start] == quote) {
                f_array_length content_slash_delimits = content_slash_total / 2;
                f_string_range content_range = f_string_range_initialize;
                f_array_length i = 0;

                if (content_slash_total % 2) {
                  content_slash_delimits++;
                }

                if (delimits.used + content_slash_delimits > delimits.size) {
                  if (delimits.used + content_slash_delimits > f_string_length_size) {
                    status = F_status_set_error(F_string_too_large);
                  }
                  else {
                    f_macro_string_lengths_resize(status, delimits, delimits.used + content_slash_delimits);
                  }

                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete(status, delimits);
                    return status;
                  }
                }

                content_range.start = content_slash_first;
                content_range.stop = range->stop;

                while (i < content_slash_delimits) {
                  if (buffer->string[content_range.start] == f_iki_syntax_slash) {
                    delimits.array[delimits.used] = content_range.start;
                    delimits.used++;

                    i++;
                  }

                  status = f_utf_buffer_increment(*buffer, (&content_range), 1);
                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete(status, delimits);
                    return status;
                  }
                } // while

                // valid content's ending quote is not delimited, save and return.
                if (content_slash_total % 2 == 0) {

                  // this is a valid vocabulary name and content, but if it is delimited, save the delimit and ignore.
                  if (vocabulary_delimited) {
                    f_macro_iki_allocate_delimits_if_necessary(status, delimits);
                    if (F_status_is_error(status)) {
                      f_macro_string_lengths_delete(status, delimits);
                      return status;
                    }

                    delimits.array[delimits.used] = vocabulary_slash_first;
                    delimits.used++;

                    vocabulary_delimited = F_false;
                    quote = 0;

                    range->start++;

                    // skip past all initial non-word, non-dash, and non-plus.
                    while (range->start <= range->stop && range->start < buffer->used) {
                      if (buffer->string[range->start] == f_iki_syntax_placeholder) {
                        range->start++;
                        continue;
                      }

                      f_macro_iki_determine_width_max(buffer, range, width_max);

                      status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max);
                      if (F_status_is_error(status)) {
                        f_macro_string_lengths_delete(status, delimits);
                        return status;
                      }

                      if (status == F_true) break;

                      status = f_utf_buffer_increment(*buffer, range, 1);
                      if (F_status_is_error(status)) {
                        f_macro_string_lengths_delete(status, delimits);
                        return status;
                      }
                    } // while

                    found_vocabulary.start = range->start;
                  }
                  else {
                    f_macro_iki_allocate_ranges_if_necessary(status, (*variable));

                    if (F_status_is_fine(status)) {
                      f_macro_iki_allocate_ranges_if_necessary(status, (*vocabulary));
                    }

                    if (F_status_is_fine(status)) {
                      f_macro_iki_allocate_ranges_if_necessary(status, (*content));
                    }

                    if (F_status_is_error(status)) {
                      f_macro_string_lengths_delete(status, delimits);
                      return status;
                    }

                    variable->array[variable->used].start = found_vocabulary.start;
                    variable->array[variable->used].stop = range->start;
                    variable->used++;

                    vocabulary->array[vocabulary->used].start = found_vocabulary.start;
                    vocabulary->array[vocabulary->used].stop = found_vocabulary.stop;
                    vocabulary->used++;

                    content->array[content->used].start = found_content;
                    content->array[content->used].stop = range->start - 1;
                    content->used++;

                    for (f_array_length i = 0; i < delimits.used; i++) {
                      buffer->string[delimits.array[i]] = f_iki_syntax_placeholder;
                    } // for

                    f_macro_string_lengths_delete(status, delimits);
                    if (F_status_is_error(status)) return status;

                    range->start++;

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
              else if (buffer->string[range->start] != f_iki_syntax_slash) {
                break;
              }

              content_slash_total++;

              status = f_utf_buffer_increment(*buffer, range, 1);
              if (F_status_is_error(status)) {
                f_macro_string_lengths_delete(status, delimits);
                return status;
              }
            } // while
          }

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete(status, delimits);
            return status;
          }
        } // while
      }
      else {

        status = f_utf_buffer_increment(*buffer, range, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete(status, delimits);
          return status;
        }

        vocabulary_delimited = F_false;
        find_next = F_true;
      }

      if (find_next) {

        while (range->start <= range->stop && range->start < buffer->used) {

          f_macro_iki_seek_whitespace(status, buffer, range, width_max, F_true);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete(status, delimits);
            return status;
          }

          f_macro_iki_seek_whitespace(status, buffer, range, width_max, F_false);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete(status, delimits);
            return status;
          }

          f_macro_iki_determine_width_max(buffer, range, width_max);

          status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete(status, delimits);
            return status;
          }

          if (status == F_true) break;

          status = f_utf_buffer_increment(*buffer, range, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete(status, delimits);
            return status;
          }
        } // while

        found_vocabulary.start = range->start;
        find_next = F_false;
      }
    } while (range->start <= range->stop && range->start < buffer->used);

    f_macro_string_lengths_delete(status, delimits);
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
