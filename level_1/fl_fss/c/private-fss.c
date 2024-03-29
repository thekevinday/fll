#include "fss.h"
#include "private-fss.h"
#include "fss/macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_fss_basic_list_content_write_) || !defined(_di_fl_fss_extended_list_content_write_) || !defined(_di_fl_fss_embedded_list_content_write_)
  f_status_t private_fl_fss_basic_list_write_add_until_end(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {

    f_status_t status = F_none;

    for (; range->start <= range->stop && range->start < buffer.used; ++range->start) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          return F_status_set_error(F_interrupt);
        }
      }

      if (buffer.string[range->start] == f_fss_delimit_placeholder_s.string[0]) continue;
      if (buffer.string[range->start] == f_fss_eol_s.string[0]) break;

      status = f_string_dynamic_increase(state.step_large, destination);
      if (F_status_is_error(status)) break;

      destination->string[destination->used++] = buffer.string[range->start];
    } // for

    return status;
  }
#endif // !defined(_di_fl_fss_basic_list_content_write_) || !defined(_di_fl_fss_extended_list_content_write_) || !defined(_di_fl_fss_embedded_list_content_write_)

#if !defined(_di_fl_fss_basic_list_object_write_) || !defined(_di_fl_fss_extended_list_object_write_)
  f_status_t private_fl_fss_basic_list_write_object_trim(const f_array_length_t used_start, f_state_t state, f_string_dynamic_t * const destination) {

    f_status_t status = F_none;
    f_string_range_t destination_range = macro_f_string_range_t_initialize2(destination->used);
    f_array_length_t i = 0;

    uint8_t width = 0;

    for (; destination_range.start < destination->used; ++destination_range.start) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          return F_status_set_error(F_interrupt);
        }
      }

      if (destination->string[destination_range.start] == f_fss_delimit_placeholder_s.string[0]) continue;

      status = f_fss_is_space(state, *destination, destination_range);

      if (F_status_is_error(status)) {
        destination->used = used_start;

        return status;
      }

      if (status == F_false) break;

      width = macro_f_utf_byte_width(destination->string[destination_range.start]);

      for (i = 0; i < width; ++i) {
        destination->string[destination_range.start + i] = f_fss_delimit_placeholder_s.string[0];
      } // for
    } // for

    for (destination_range.start = destination->used - 1; destination_range.start > 0; --destination_range.start) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          return F_status_set_error(F_interrupt);
        }
      }

      if (destination->string[destination_range.start] == f_fss_delimit_placeholder_s.string[0]) {
        --destination->used;

        continue;
      }

      status = f_fss_is_space(state, *destination, destination_range);

      // When going backwards, getting incomplete UTF-8 sequences is not an error.
      if (F_status_set_fine(status) == F_complete_not_utf) continue;

      if (F_status_is_error(status)) {
        destination->used = used_start;

        return status;
      }

      if (status == F_false) break;

      destination->used -= macro_f_utf_byte_width(destination->string[destination_range.start]);
    } // for

    if (destination_range.start == 0) {
      status = f_fss_is_space(state, *destination, destination_range);

      if (F_status_is_error(status)) {
        destination->used = used_start;

        return status;
      }

      if (status == F_true) {
        destination->used = 0;
      }
    }

    return F_none;
  }
#endif // !defined(_di_fl_fss_basic_list_object_write_) || !defined(_di_fl_fss_extended_list_object_write_)

#if !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_) || !defined(_di_fl_fss_extended_content_read_)
  f_status_t private_fl_fss_basic_or_extended_read(const f_string_static_t buffer, const uint8_t flag, f_state_t state, f_string_range_t * const range, f_fss_object_t * const found, f_fss_quote_t * const quote, f_fss_delimits_t * const delimits) {

    f_status_t status = f_fss_skip_past_space(state, buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eol) {

      // Move the start position to after the EOL.
      ++range->start;

      return F_fss_found_object_not;
    }

    if (status == F_none_eos) return F_data_not_eos;
    if (status == F_none_stop) return F_data_not_stop;
    if (status == F_data_not) return status;

    // Save the delimits used position in case of unterminated quote.
    const f_array_length_t delimits_used = delimits->used;

    // Begin the search.
    const f_array_length_t begin = range->start;
    found->start = range->start;

    // Ignore all comment lines.
    if ((flag & 0x1) && buffer.string[range->start] == f_fss_comment_s.string[0]) {

      while (buffer.string[range->start] != f_fss_eol_s.string[0]) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            return F_status_set_error(F_interrupt);
          }
        }

        ++range->start;

        if (range->start >= buffer.used) {
          return F_data_not_eos;
        }

        if (range->start > range->stop) {
          return F_data_not_stop;
        }
      } // while

      // Move the start position to after the EOL.
      ++range->start;

      return F_fss_found_object_not;
    }

    // Handle quote support.
    f_char_t quote_found = 0;

    if (quote) {
      *quote = f_fss_quote_type_none_e;
    }

    // Identify where the object begins.
    if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
      f_array_length_t first_slash = range->start;

      found->start = range->start;

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) return status;

      while (range->start <= range->stop && range->start < buffer.used) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            status = F_status_set_error(F_interrupt);

            break;
          }
        }

        status = f_fss_is_zero_width(state, buffer, *range);
        if (F_status_is_error(status)) return status;

        if (status == F_true) {
          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) break;

          continue;
        }

        if (buffer.string[range->start] != f_fss_delimit_slash_s.string[0]) {
          status = f_fss_is_space(state, buffer, *range);
          if (F_status_is_error(status)) return status;

          // Found the end of the object while processing the slash for potential delimits.
          if (status == F_true) {
            if (range->start > begin) {
              found->stop = range->start - 1;
            }
            else {
              found->start = 1;
              found->stop = 0;
            }

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) break;

            if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
              return F_fss_found_object_content_not;
            }

            return F_fss_found_object;
          }

          break;
        }

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;
      } // while

      if (F_status_is_error(status)) return status;

      if (range->start >= buffer.used) {
        found->stop = buffer.used - 1;

        return F_none_eos;
      }

      if (range->start > range->stop) {
        found->stop = range->stop;

        return F_none_stop;
      }

      if ((!(flag & 0x2) && (buffer.string[range->start] == f_fss_quote_single_s.string[0] || buffer.string[range->start] == f_fss_quote_double_s.string[0] || buffer.string[range->start] == f_fss_quote_backtick_s.string[0])) || ((flag & 0x1) && buffer.string[range->start] == f_fss_comment_s.string[0])) {

        // Only the first slash before a quote needs to be escaped (or not) as once there is a slash before a quote, this cannot ever be a quote object.
        // This simplifies the number of slashes needed.
        status = f_array_lengths_increase(state.step_small, delimits);
        if (F_status_is_error(status)) return status;

        delimits->array[delimits->used++] = first_slash;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) return status;
      }
    }
    else if (!(flag & 0x2) && (buffer.string[range->start] == f_fss_quote_single_s.string[0] || buffer.string[range->start] == f_fss_delimit_quote_double_s.string[0] || buffer.string[range->start] == f_fss_quote_backtick_s.string[0])) {
      quote_found = buffer.string[range->start];

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) return status;

      found->start = range->start;
    }

    // Identify where the object ends.
    if (quote_found) {
      f_array_length_t first_slash = 0;
      f_array_length_t slash_count = 0;
      f_array_length_t location = 0;

      while (range->start <= range->stop && range->start < buffer.used) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            return F_status_set_error(F_interrupt);
          }
        }

        if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
          first_slash = range->start;
          slash_count = 1;

          status = f_utf_buffer_increment(buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < buffer.used) {

            if (state.interrupt) {
              status = state.interrupt((void *) &state, 0);

              if (F_status_set_fine(status) == F_interrupt) {
                return F_status_set_error(F_interrupt);
              }
            }

            if (buffer.string[range->start] == f_fss_delimit_placeholder_s.string[0]) {
              status = f_utf_buffer_increment(buffer, range, 1);
              if (F_status_is_error(status)) return status;

              continue;
            }
            else if (buffer.string[range->start] != f_fss_delimit_slash_s.string[0]) {
              break;
            }

            ++slash_count;

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (range->start >= buffer.used) {
            found->stop = buffer.used - 1;

            return F_end_not_group_eos;
          }

          if (range->start > range->stop) {
            found->stop = range->stop;

            return F_end_not_group_stop;
          }

          if (buffer.string[range->start] == quote_found) {
            location = range->start;

            // Check to see if there is a whitespace, EOS, or EOL after the quote, if not, then this is not a closing quote and delimits do not apply.
            if (range->start + 1 <= range->stop && range->start + 1 < buffer.used) {
              ++range->start;

              status = f_fss_skip_past_delimit(state, buffer, range);
              if (F_status_is_error(status)) return status;

              if (range->start > range->stop || range->start >= buffer.used) {

                // EOS or EOL was reached, so it is a valid closing quote.
                // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE.)
                status = F_true;
              }
              else {
                status = f_fss_is_space(state, buffer, *range);
                if (F_status_is_error(status)) return status;
              }
            }
            else {

              // EOS or EOL was reached, so it is a valid closing quote.
              // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE.)
              status = F_true;
            }

            if (status == F_true) {
              if (quote) {
                if (quote_found == f_fss_quote_double_s.string[0]) {
                  *quote = f_fss_quote_type_double_e;
                }
                else if (quote_found == f_fss_quote_single_s.string[0]) {
                  *quote = f_fss_quote_type_single_e;
                }
                else if (quote_found == f_fss_quote_backtick_s.string[0]) {
                  *quote = f_fss_quote_type_backtick_e;
                }
                else {
                  *quote = f_fss_quote_type_none_e;
                }
              }

              range->start = first_slash;

              if (slash_count % 2 == 0) {
                status = f_array_lengths_increase_by(slash_count / 2, delimits);
                if (F_status_is_error(status)) return status;

                while (slash_count > 0) {

                  if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
                    if (slash_count % 2 == 1) {
                      delimits->array[delimits->used] = range->start;
                      ++delimits->used;
                    }

                    --slash_count;
                  }

                  status = f_utf_buffer_increment(buffer, range, 1);
                  if (F_status_is_error(status)) return status;
                } // while

                range->start = location + 1;

                while (buffer.string[range->start] == f_fss_delimit_placeholder_s.string[0]) {

                  if (state.interrupt) {
                    status = state.interrupt((void *) &state, 0);

                    if (F_status_set_fine(status) == F_interrupt) {
                      return F_status_set_error(F_interrupt);
                    }
                  }

                  if (++range->start >= buffer.used) return F_none_eos;
                  if (range->start > range->stop) return F_none_stop;
                } // while

                status = f_fss_is_graph(state, buffer, *range);
                if (F_status_is_error(status)) return status;

                if (status == F_true) {

                  while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol_s.string[0]) {

                    if (state.interrupt) {
                      status = state.interrupt((void *) &state, 0);

                      if (F_status_set_fine(status) == F_interrupt) {
                        return F_status_set_error(F_interrupt);
                      }
                    }

                    status = f_utf_buffer_increment(buffer, range, 1);
                    if (F_status_is_error(status)) return status;
                  } // while

                  if (range->start >= buffer.used) {
                    found->stop = buffer.used - 1;

                    return F_data_not_eos;
                  }

                  if (range->start > range->stop) {
                    found->stop = range->stop;

                    return F_data_not_stop;
                  }

                  status = f_utf_buffer_increment(buffer, range, 1);
                  if (F_status_is_error(status)) return status;

                  return F_fss_found_object_not;
                }

                if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
                  found->stop = location - 1;

                  // Move the start position to after the EOL.
                  ++range->start;

                  return F_fss_found_object_content_not;
                }

                found->stop = location - 1;

                status = f_utf_buffer_increment(buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return F_fss_found_object;
              }
              else {
                status = f_array_lengths_increase_by((slash_count / 2) + 1, delimits);
                if (F_status_is_error(status)) return status;

                while (slash_count > 0) {

                  if (buffer.string[range->start] == f_fss_delimit_slash_s.string[0]) {
                    if (slash_count % 2 == 1) {
                      delimits->array[delimits->used++] = range->start;
                    }

                    --slash_count;
                  }

                  status = f_utf_buffer_increment(buffer, range, 1);
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
        else if (buffer.string[range->start] == quote_found) {

          // Check to see if there is a whitespace, EOS, or EOL after the quote, if not, then this is not a closing quote.
          location = range->start;

          if (range->start + 1 <= range->stop && range->start + 1 < buffer.used) {
            ++range->start;

            status = f_fss_skip_past_delimit(state, buffer, range);
            if (F_status_is_error(status)) return status;

            if (range->start > range->stop || range->start >= buffer.used) {

              // EOS or EOL was reached, so it is a valid closing quote.
              // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE.)
              status = F_true;
            }
            else {
              status = f_fss_is_space(state, buffer, *range);
              if (F_status_is_error(status)) return status;
            }
          }
          else {

            // EOS or EOL was reached, so it is a valid closing quote.
            // (for EOL, this is always TRUE, for EOS this could be false but there is no way to know this, so assume TRUE.)
            status = F_true;
          }

          range->start = location;

          if (status == F_true) {
            if (quote) {
              if (quote_found == f_fss_quote_double_s.string[0]) {
                *quote = f_fss_quote_type_double_e;
              }
              else if (quote_found == f_fss_quote_single_s.string[0]) {
                *quote = f_fss_quote_type_single_e;
              }
              else if (quote_found == f_fss_quote_backtick_s.string[0]) {
                *quote = f_fss_quote_type_backtick_e;
              }
              else {
                *quote = f_fss_quote_type_none_e;
              }
            }

            if (range->start > begin) {
              found->stop = range->start - 1;
            }
            else {
              found->start = 1;
              found->stop = 0;
            }

            status = f_utf_buffer_increment(buffer, range, 1);
            if (F_status_is_error(status)) return status;

            while (range->start <= range->stop && range->start < buffer.used) {

              if (state.interrupt) {
                status = state.interrupt((void *) &state, 0);

                if (F_status_set_fine(status) == F_interrupt) {
                  return F_status_set_error(F_interrupt);
                }
              }

              if (buffer.string[range->start] == f_fss_eol_s.string[0]) {

                // Move the start position to after the EOL.
                ++range->start;

                return F_fss_found_object_content_not;
              }

              status = f_fss_is_space(state, buffer, *range);
              if (F_status_is_error(status)) return status;

              if (status == F_true) {
                status = f_utf_buffer_increment(buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return F_fss_found_object;
              }

              if (buffer.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
                while (range->start <= range->stop && range->start < buffer.used && buffer.string[range->start] != f_fss_eol_s.string[0]) {

                  if (state.interrupt) {
                    status = state.interrupt((void *) &state, 0);

                    if (F_status_set_fine(status) == F_interrupt) {
                      return F_status_set_error(F_interrupt);
                    }
                  }

                  status = f_utf_buffer_increment(buffer, range, 1);
                  if (F_status_is_error(status)) return status;
                } // while

                if (range->start >= buffer.used) {
                  found->stop = buffer.used - 1;

                  return F_data_not_eos;
                }

                if (range->start > range->stop) {
                  found->stop = range->stop;

                  return F_data_not_stop;
                }

                status = f_utf_buffer_increment(buffer, range, 1);
                if (F_status_is_error(status)) return status;

                return F_fss_found_object_not;
              }

              status = f_utf_buffer_increment(buffer, range, 1);
              if (F_status_is_error(status)) return status;
            } // while

            if (range->start >= buffer.used) {
              found->stop = buffer.used - 1;

              return F_none_eos;
            }

            if (range->start > range->stop) {
              found->stop = range->stop;

              return F_none_stop;
            }
          }
        }
        else if (buffer.string[range->start] == f_fss_eol_s.string[0]) {
          if (flag & 0x1) {

            // The quote is incomplete, so treat the entire line as the Object as per the specification (including the quotes).
            // The error bit is set to designate that the Object is found in an erroneous state (not having a terminating quote).
            if (found->start > begin && range->start > begin) {
              found->start -= 1;
              found->stop = range->start - 1;
            }
            else {
              found->start = 1;
              found->stop = 0;
            }

            // Move the start position to after the EOL.
            ++range->start;
          }
          else {

            // The quote is incomplete, do not save and reset range->start so that caller can fix the position and re-run with quotes disabled.
            range->start = begin;
          }

          // The delimits cannot be preserved in this case as per specification.
          delimits->used = delimits_used;

          return F_status_set_error(F_fss_found_object_content_not);
        }

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) return status;
      } // while

      if (range->start >= buffer.used) {
        found->stop = buffer.used - 1;

        return F_end_not_group_eos;
      }

      if (range->start > range->stop) {
        found->stop = range->stop;

        return F_end_not_group_stop;
      }
    }
    else {
      status = F_none;

      while (range->start <= range->stop && range->start < buffer.used) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            status = F_status_set_error(F_interrupt);

            break;
          }
        }

        status = f_fss_is_space(state, buffer, *range);
        if (F_status_is_error(status)) return status;

        if (status == F_true) break;

        status = f_utf_buffer_increment(buffer, range, 1);
        if (F_status_is_error(status)) break;
      } // while

      if (F_status_is_error(status)) return status;

      if (range->start > begin) {
        found->stop = range->start - 1;
      }
      else {
        found->start = 1;
        found->stop = 0;
      }

      if (buffer.string[range->start] == f_fss_eol_s.string[0]) {

        // Move the start position to after the EOL.
        ++range->start;

        return F_fss_found_object_content_not;
      }

      status = f_utf_buffer_increment(buffer, range, 1);
      if (F_status_is_error(status)) return status;

      return F_fss_found_object;
    }

    // Seek to the EOL when no valid object is found.
    status = f_fss_seek_to_eol(state, buffer, range);
    if (F_status_is_error(status)) return status;

    // Move the start position to after the EOL.
    ++range->start;

    return F_fss_found_object_not;
  }
#endif // !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_)

#if !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)
  f_status_t private_fl_fss_basic_write(const uint8_t flag, const f_string_static_t object, const f_fss_quote_t quote, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {

    f_status_t status = f_fss_skip_past_space(state, object, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eos) return F_data_not_eos;
    if (status == F_none_stop) return F_data_not_stop;
    if (status == F_none_eol) return F_status_set_error(F_none_eol);
    if (status == F_data_not) return status;

    // Ensure that there is room for the potential start and stop quotes, a potential delimit at start, and the potential object open character.
    status = f_string_dynamic_increase_by(state.step_small + 5, destination);
    if (F_status_is_error(status)) return status;

    const f_array_length_t input_start = range->start;
    const f_array_length_t used_start = destination->used;

    bool quote_is = F_false;
    bool commented = F_false;

    f_array_length_t item_first = 0;
    f_array_length_t item_total = 0;
    f_array_length_t i = 0;

    const f_char_t quote_char = quote == f_fss_quote_type_double_e ? f_string_ascii_quote_double_s.string[0] : f_string_ascii_quote_single_s.string[0];

    // Use placeholders for potential quote and potential delimited quote to avoid doing things such as memmove().
    destination->string[destination->used++] = f_fss_delimit_placeholder_s.string[0];
    destination->string[destination->used++] = f_fss_delimit_placeholder_s.string[0];

    // If there is an initial quote, then this must be quote and the existing quote must be delimited.
    if (object.string[input_start] == quote_char) {
      quote_is = F_true;
    }
    else if ((flag & 0x1) && object.string[input_start] == f_fss_comment_s.string[0]) {
      commented = F_true;
    }

    uint8_t width = 0;

    for (; range->start <= range->stop && range->start < object.used; ) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      if (object.string[range->start] == f_fss_delimit_slash_s.string[0]) {
        item_first = range->start++;
        item_total = 1;

        for (; range->start <= range->stop && range->start < object.used; ++range->start) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              status = F_status_set_error(F_interrupt);

              break;
            }
          }

          if (object.string[range->start] == f_fss_delimit_slash_s.string[0]) {
            ++item_total;
          }
          else if (object.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
            break;
          }
        } // for

        if (range->start > range->stop || range->start >= object.used) {

          // Slashes before the final quote must be escaped when quote, add the delimit slashes.
          if (quote_is) {

            // If this is the first quote, then only a single delimit slash is needed.
            if (item_first == input_start) {
              status = f_string_dynamic_increase(state.step_large, destination);
              if (F_status_is_error(status)) break;

              destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
            }
            else {
              status = f_string_dynamic_increase_by(item_total, destination);
              if (F_status_is_error(status)) break;

              for (i = 0; i < item_total; ++i) {
                destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
              } // for
            }
          }

          status = f_string_dynamic_increase_by(item_total, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < item_total; ++i) {
            destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          } // for

          break;
        }

        if (object.string[range->start] == f_fss_eol_s.string[0]) {
          status = F_status_set_error(F_none_eol);

          break;
        }

        if (object.string[range->start] == quote_char) {
          item_first = range->start++;

          status = f_fss_skip_past_delimit(state, object, range);
          if (F_status_is_error(status)) break;

          if (range->start > range->stop || range->start >= object.used) {

            status = f_string_dynamic_increase_by(item_total + 1, destination);
            if (F_status_is_error(status)) break;

            for (i = 0; i < item_total; ++i) {
              destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
            } // for

            destination->string[destination->used++] = quote_char;

            break;
          }

          // if any space is found after a quote after a slash, then this must be delimited and quote.
          status = f_fss_is_space(state, object, *range);
          if (F_status_is_error(status)) break;

          if (status == F_true) {
            if (object.string[range->start] == f_fss_eol_s.string[0]) {
              status = F_status_set_error(F_none_eol);

              break;
            }

            quote_is = F_true;

            status = f_string_dynamic_increase_by(item_total + 1, destination);
            if (F_status_is_error(status)) break;

            // Add the slashes that delimit the slashes.
            if (item_first == input_start) {
              destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
            }
            else {
              for (i = 0; i < item_total; ++i) {
                destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
              } // for
            }
          }

          width = macro_f_utf_byte_width(object.string[range->start]);

          status = f_string_dynamic_increase_by(item_total + width + 1, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < item_total; ++i) {
            destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          } // for

          destination->string[destination->used++] = quote_char;

          for (i = 0; i < width; ++i) {
            destination->string[destination->used++] = object.string[range->start + i];
          } // for
        }
        else if ((flag & 0x1) && object.string[range->start] == f_fss_comment_s.string[0]) {

          // Only the first slash needs to be escaped for a comment, and then only if not quote.
          if (item_first == input_start) {
            commented = F_true;
          }

          status = f_string_dynamic_increase_by(item_total + 1, destination);
          if (F_status_is_error(status)) break;

          for (i = 0; i < item_total; ++i) {
            destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          } // for

          destination->string[destination->used++] = object.string[range->start++];

          continue;
        }
        else {

          // If any space is found, then this must be quote.
          status = f_fss_is_space(state, object, *range);
          if (F_status_is_error(status)) break;

          if (status == F_true) {
            if (object.string[range->start] == f_fss_eol_s.string[0]) {
              status = F_status_set_error(F_none_eol);

              break;
            }

            quote_is = F_true;
          }

          width = macro_f_utf_byte_width(object.string[range->start]);

          status = f_string_dynamic_increase_by(item_total + width, destination);
          if (F_status_is_error(status)) break;

          // There is nothing to delimit, so all slashes should be printed as is.
          for (i = 0; i < item_total; ++i) {
            destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          } // for

          for (i = 0; i < width; ++i) {
            destination->string[destination->used++] = object.string[range->start + i];
          } // for
        }
      }
      else if (object.string[range->start] == quote_char) {
        item_first = range->start++;

        // The very first quote, must be escaped, when quoting is disabled.
        if (item_first == input_start) {
          status = f_string_dynamic_increase(state.step_large, destination);
          if (F_status_is_error(status)) break;

          destination->string[used_start + 1] = f_fss_delimit_slash_s.string[0];
        }

        status = f_fss_skip_past_delimit(state, object, range);
        if (F_status_is_error(status)) return status;

        if (range->start > range->stop || range->start >= object.used) {

          status = f_string_dynamic_increase(state.step_large, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = quote_char;

          break;
        }

        if (object.string[range->start] == quote_char) {
          status = f_string_dynamic_increase(state.step_large, destination);
          if (F_status_is_error(status)) break;

          destination->string[destination->used++] = quote_char;

          // The next quote must also be checked, so do not increment.
          continue;
        }

        // If any space is found, then this must be quote.
        status = f_fss_is_space(state, object, *range);
        if (F_status_is_error(status)) break;

        if (status == F_true) {
          if (object.string[range->start] == f_fss_eol_s.string[0]) {
            status = F_status_set_error(F_none_eol);

            break;
          }

          if (item_first != input_start) {
            status = f_string_dynamic_increase(state.step_large, destination);
            if (F_status_is_error(status)) break;

            destination->string[destination->used++] = f_fss_delimit_slash_s.string[0];
          }

          quote_is = F_true;
        }

        width = macro_f_utf_byte_width(object.string[range->start]);

        status = f_string_dynamic_increase_by(width + 1, destination);
        if (F_status_is_error(status)) break;

        destination->string[destination->used++] = quote_char;

        for (i = 0; i < width; ++i) {
          destination->string[destination->used++] = object.string[range->start + i];
        } // for
      }
      else if (object.string[range->start] == f_fss_eol_s.string[0]) {
        status = F_status_set_error(F_none_eol);

        break;
      }
      else if (object.string[range->start] != f_fss_delimit_placeholder_s.string[0]) {
        if (!quote_is) {
          status = f_fss_is_space(state, object, *range);
          if (F_status_is_error(status)) break;

          if (status == F_true) {
            quote_is = F_true;
          }
        }

        width = macro_f_utf_byte_width(object.string[range->start]);

        status = f_string_dynamic_increase_by(width, destination);
        if (F_status_is_error(status)) break;

        for (i = 0; i < width; ++i) {
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

    if (quote_is) {
      status = f_string_dynamic_increase_by(state.step_small + 2, destination);

      if (F_status_is_error(status)) {
        destination->used = used_start;

        return status;
      }

      destination->string[used_start] = quote_char;
      destination->string[destination->used++] = quote_char;

      // The start quote may or may not need to be delimited in this case.
      if (destination->string[input_start] == quote_char) {

        for (i = input_start + macro_f_utf_byte_width(object.string[input_start]); i <= range->stop && i < object.used; i += macro_f_utf_byte_width(object.string[i])) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              destination->used = used_start;

              return F_status_set_error(F_interrupt);
            }
          }

          if (object.string[i] != f_fss_delimit_placeholder_s.string[0]) break;
        } // for

        // Only when followed by a space must the start quote be delimited.
        if (i <= range->stop && i < object.used) {
          f_string_range_t range_i = *range;

          range_i.start = i;

          status = f_fss_is_space(state, object, range_i);

          if (F_status_is_error(status)) {
            destination->used = used_start;

            return status;
          }

          if (status == F_true) {
            if (object.string[i] == f_fss_eol_s.string[0]) {
              destination->used = used_start;

              return F_status_set_error(F_none_eol);
            }
          }
          else {
            destination->string[used_start + 1] = f_fss_delimit_placeholder_s.string[0];
          }
        }
      }
    }
    else if (commented) {
      destination->string[used_start] = f_fss_delimit_slash_s.string[0];
    }

    return range->start > range->stop ? F_none_stop : F_none_eos;
  }
#endif // !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_) || !defined(_di_fl_fss_extended_content_write_)

#if !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_)
  f_status_t private_fl_fss_basic_write_object_trim(const f_fss_quote_t quote, const f_array_length_t used_start, f_state_t state, f_string_dynamic_t * const destination) {

    f_status_t status = F_none;
    f_string_range_t destination_range = macro_f_string_range_t_initialize2(destination->used);
    f_array_length_t i = 0;

    uint8_t width = 0;
    const f_char_t quote_char = quote == f_fss_quote_type_double_e ? f_string_ascii_quote_double_s.string[0] : f_string_ascii_quote_single_s.string[0];

    // If there are any spaces, then this will be quote so find the first non-placeholder character.
    for (; destination_range.start < destination->used; ++destination_range.start) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          destination->used = used_start;

          return F_status_set_error(F_interrupt);
        }
      }

      if (destination->string[destination_range.start] != f_fss_delimit_placeholder_s.string[0]) break;
    } // for

    if (destination->string[destination_range.start] == quote_char) {
      const f_array_length_t front = destination_range.start;

      for (++destination_range.start; destination_range.start < destination->used; ++destination_range.start) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            destination->used = used_start;

            return F_status_set_error(F_interrupt);
          }
        }

        if (destination->string[destination_range.start] == f_fss_delimit_placeholder_s.string[0]) continue;

        status = f_fss_is_space(state, *destination, destination_range);

        if (F_status_is_error(status)) {
          destination->used = used_start;

          return status;
        }

        if (status == F_false) break;

        width = macro_f_utf_byte_width(destination->string[destination_range.start]);

        for (i = 0; i < width; ++i) {
          destination->string[destination_range.start + i] = f_fss_delimit_placeholder_s.string[0];
        } // for
      } // for

      // Find the last quote.
      for (destination_range.start = destination->used - 1; destination_range.start > front; --destination_range.start) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            destination->used = used_start;

            return F_status_set_error(F_interrupt);
          }
        }

        if (destination->string[destination_range.start] == quote_char) {
          --destination_range.start;

          break;
        }
      } // for

      const f_array_length_t rear = destination_range.start + 1;

      for (; destination_range.start > front; --destination_range.start) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            destination->used = used_start;

            return F_status_set_error(F_interrupt);
          }
        }

        if (destination->string[destination_range.start] == f_fss_delimit_placeholder_s.string[0]) continue;

        status = f_fss_is_space(state, *destination, destination_range);

        // When going backwards, getting incomplete UTF-8 sequences is not an error.
        if (F_status_set_fine(status) == F_complete_not_utf) continue;

        if (F_status_is_error(status)) {
          destination->used = used_start;

          return status;
        }

        if (status == F_false) break;

        width = macro_f_utf_byte_width(destination->string[destination_range.start]);

        for (i = 0; i < width; ++i) {
          destination->string[destination_range.start + i] = f_fss_delimit_placeholder_s.string[0];
        } // for
      } // for

      // If there is no whitespace between the quotes, post-trimming, then remove the quotes.
      for (destination_range.start = front; destination_range.start < rear; ++destination_range.start) {

        if (state.interrupt) {
          status = state.interrupt((void *) &state, 0);

          if (F_status_set_fine(status) == F_interrupt) {
            destination->used = used_start;

            return F_status_set_error(F_interrupt);
          }
        }

        status = f_fss_is_space(state, *destination, destination_range);

        if (F_status_is_error(status)) {
          destination->used = used_start;

          return status;
        }

        if (status == F_true) break;
      } // for

      if (destination_range.start == rear) {
        destination->string[front] = f_fss_delimit_placeholder_s.string[0];
        destination->string[rear] = f_fss_delimit_placeholder_s.string[0];
      }
    }

    return F_none;
  }
#endif // !defined(_di_fl_fss_basic_object_write_) || !defined(_di_fl_fss_extended_object_write_)

#ifdef __cplusplus
} // extern "C"
#endif
