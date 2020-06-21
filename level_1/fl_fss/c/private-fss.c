#include <level_1/fss.h>
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_fss_identify_) || !defined(_di_fl_fss_identify_file_)
  f_return_status private_fl_fss_identify(const f_string_static buffer, f_fss_header *header) {
    register f_string_length i = 0;

    if (buffer.used < 10) {
      // "# fss-0000" is always at least 10 characters.
      return FL_fss_header_not;
    }

    // If this correctly follows the FSS specification, then this should be all that needs to be done (as well as atoh for ascii to hex).
    // All characters used in the identifier are only in the ascii equivalents of the characters, any similarly looking character or number representing in UTF-8 is considered invalid.
    if (buffer.string[i] == f_fss_type_header_open) {
      i++;

      if (buffer.string[i] == f_fss_type_header_part1) {
        i++;

        if (buffer.string[i] == f_fss_type_header_part2) {
          i++;

          if (buffer.string[i] == f_fss_type_header_part3) {
            i++;

            if (buffer.string[i] == f_fss_type_header_part4) {
              i++;

              if (buffer.string[i] == f_fss_type_header_part5) {
                i++;

                if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                  i++;

                  if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                    i++;

                    if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                      i++;

                      if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                        i++;

                        f_string_range range = f_string_range_initialize;

                        range.start = i - 4;
                        range.stop = i;

                        // 1: A possibly valid header type was found, now convert it into its proper format and save the header type.
                        const f_status status = f_conversion_string_to_hexidecimal_unsigned(buffer.string, &header->type, range);
                        if (F_status_is_error(status)) return status;

                        if (status == F_none) {
                          // 2: At this point, we can still know the proper format for the file and still have a invalid header, handle accordingly.
                          if (buffer.string[i] == f_fss_type_header_close) {
                            header->length = i + 1;

                            return F_none;
                          }
                          else {
                            // if "# fss-0000" is there, regardless of whats next, we can guess this to be of fss-0000, even if its fss-00001 (this is a guess afterall).
                            header->length = i + 1;

                            return F_status_set_warning(FL_fss_accepted_invalid);
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      // people can miss spaces, so lets accept in an attempt to interpret the file anyway, but return values at this point are to be flagged as invalid.
      else if (buffer.string[i] == f_fss_type_header_part2) {
        i++;

        if (buffer.string[i] == f_fss_type_header_part3) {
          i++;

          if (buffer.string[i] == f_fss_type_header_part4) {
            i++;

            if (buffer.string[i] == f_fss_type_header_part5) {
              i++;

              if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                i++;

                if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                  i++;

                  if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                    i++;

                    if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                      i++;

                      f_string_range range = f_string_range_initialize;

                      range.start = i - 4;
                      range.stop = i;

                      const f_status status = f_conversion_string_to_hexidecimal_unsigned(buffer.string, &header->type, range);
                      if (F_status_is_error(status)) return status;

                      header->length = i + 1;

                      return F_status_set_warning(FL_fss_accepted_invalid);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    // @todo At some point add checksum and compressions checks here, but the above statements will have to be adjusted accordingly.
    // 3: eventually this will be processing the checksum and 4: will be processing the compression.

    return FL_fss_header_not;
  }
#endif // !defined(_di_fl_fss_identify_) || !defined(_di_fl_fss_identify_file_)

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
            f_string_length length = range->start;

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

              range->start = length + 1;

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

                found->stop = length - 1;
                range->start++;
                return FL_fss_found_object_content_not;
              }

              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              found->stop = length - 1;

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

              range->start = length;
            }
          }
        }
        else if (buffer->string[range->start] == quoted) {
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
