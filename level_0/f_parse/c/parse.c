#include "parse.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_parse_dynamic_seek_line_to_utf_character_
  f_status_t f_parse_dynamic_seek_line_to_utf_character(const f_string_static_t buffer, const f_utf_char_t seek_to_this, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;
    if (range->start >= buffer.used) return F_data_not_eos;

    const unsigned short seek_width = macro_f_utf_char_t_width(seek_to_this);

    f_status_t status = F_okay;

    unsigned short width = 0;
    f_number_unsigned_t width_max = 0;

    while (range->start <= range->stop && range->start < buffer.used) {

      width_max = (range->stop - range->start) + 1;
      width = macro_f_utf_byte_width_is(buffer.string[range->start]);

      if (!width) {
        width = 1;

        if (buffer.string[range->start] == f_string_eol_s.string[0]) return F_okay_eol;
        if (seek_width == width && buffer.string[range->start] == seek_to_this) return F_okay;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
        if (range->start + width >= buffer.used) return F_status_set_error(F_complete_not_utf_eos);

        if (width == seek_width) {
          f_utf_char_t character = 0;

          status = f_utf_char_to_character(buffer.string + range->start, width_max, &character);
          if (F_status_is_error(status)) return status;
          if (character == seek_to_this) return F_okay;
        }
      }

      range->start += width;

      if (range->start >= range->stop) return F_okay_stop;
      if (range->start > buffer.used) return F_okay_eos;
    } // while

    return F_okay_eos;
  }
#endif // _di_f_parse_dynamic_seek_line_to_utf_character_

#ifndef _di_f_parse_dynamic_seek_line_until_graph_
  f_status_t f_parse_dynamic_seek_line_until_graph(const f_string_static_t buffer, const uint8_t placeholder, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;
    if (range->start >= buffer.used) return F_data_not_eos;

    f_status_t status = F_okay;
    unsigned short width = 0;

    f_number_unsigned_t width_max = (range->stop - range->start) + 1;

    while (buffer.string[range->start] == placeholder || (status = f_utf_is_graph(buffer.string + range->start, width_max)) == F_false) {

      if (F_status_is_error(status)) return status;
      if (buffer.string[range->start] == f_string_eol_s.string[0]) return F_okay_eol;

      width = macro_f_utf_byte_width_is(buffer.string[range->start]);

      if (!width) {
        width = 1;
      }
      else if (width == 1) {

        // Do not operate on UTF-8 fragments that are not the first byte of the character.
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
        if (range->start + width >= buffer.used) return F_status_set_error(F_complete_not_utf_eos);
      }

      range->start += width;

      if (range->start > range->stop) return F_okay_stop;
      if (range->start >= buffer.used) return F_okay_eos;

      width_max = (range->stop - range->start) + 1;
    } // while

    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_f_parse_dynamic_seek_line_until_graph_

#ifndef _di_f_parse_dynamic_seek_line_until_graph_non_
  f_status_t f_parse_dynamic_seek_line_until_graph_non(const f_string_static_t buffer, const uint8_t placeholder, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (range->start > range->stop) return F_data_not_stop;
    if (range->start >= buffer.used) return F_data_not_eos;

    f_status_t status = F_okay;
    unsigned short width = 0;

    f_number_unsigned_t width_max = (range->stop - range->start) + 1;

    while (buffer.string[range->start] == placeholder || (status = f_utf_is_whitespace(buffer.string + range->start, width_max, F_false)) == F_false) {

      if (F_status_is_error(status)) return status;
      if (buffer.string[range->start] == f_string_eol_s.string[0]) return F_okay_eol;

      width = macro_f_utf_byte_width_is(buffer.string[range->start]);

      if (!width) {
        width = 1;
      }
      else if (width == 1) {

        // Do not operate on UTF-8 fragments that are not the first byte of the character.
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
        if (range->start + width >= buffer.used) return F_status_set_error(F_complete_not_utf_eos);
      }

      range->start += width;

      if (range->start > range->stop) return F_okay_stop;
      if (range->start >= buffer.used) return F_okay_eos;

      width_max = (range->stop - range->start) + 1;
    } // while

    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_f_parse_dynamic_seek_line_until_graph_non_

#ifndef _di_f_parse_dynamic_seek_to_utf_character_
  f_status_t f_parse_dynamic_seek_to_utf_character(const f_string_static_t buffer, const f_utf_char_t seek_to_this, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!buffer.used) return F_data_not;

    if (range->start > range->stop) return F_data_not_stop;
    if (range->start > buffer.used) return F_data_not_eos;

    const unsigned short seek_width = macro_f_utf_char_t_width(seek_to_this);

    f_status_t status = F_okay;

    unsigned short width = 0;

    f_number_unsigned_t width_max = 0;

    while (range->start <= range->stop && range->start < buffer.used) {

      width_max = (range->stop - range->start) + 1;
      width = macro_f_utf_byte_width_is(buffer.string[range->start]);

      if (!width) {
        width = 1;

        if (seek_width == width) {
          if (buffer.string[range->start] == seek_to_this) return F_okay;
        }
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
        if (range->start + width >= buffer.used) return F_status_set_error(F_complete_not_utf_eos);

        if (width == seek_width) {
          f_utf_char_t character = 0;

          status = f_utf_char_to_character(buffer.string + range->start, width_max, &character);
          if (F_status_is_error(status)) return status;
          if (character == seek_to_this) return F_okay;
        }
      }

      range->start += width;
    } // while

    if (range->start >= range->stop) return F_okay_stop;

    return F_okay_eos;
  }
#endif // _di_f_parse_dynamic_seek_to_utf_character_

#ifndef _di_f_parse_dynamic_partial_fll_identify_
  f_status_t f_parse_dynamic_partial_fll_identify(const f_string_static_t buffer, f_string_range_t * const range, f_fll_id_t * const id) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (id) {
      id->type = 0;
      id->used = 0;
    }

    // Skip past all leading NULLs.
    for (; range->start <= range->stop && range->start < buffer.used; ++range->start) {
      if (buffer.string[range->start]) break;
    } // for

    if (range->start > range->stop) {
      return F_data_not;
    }

    // The FLL Identifier is always at least 6 characters ("X-0000").
    if (range->stop - range->start < 5) {

      // Increment until stop, while taking into consideration UTF-8 character widths.
      for (; range->start <= range->stop && range->start < buffer.used; ) {

        if (buffer.string[range->start] == f_string_eol_s.string[0]) {
          ++range->start;

          break;
        }

        range->start += macro_f_utf_byte_width(buffer.string[range->start]);
      } // for

      return F_found_not;
    }

    f_status_t status = F_okay;

    for (; range->start <= range->stop && range->start < buffer.used; ) {

      status = f_utf_is_whitespace(buffer.string + range->start, (range->stop - range->start) + 1, F_false);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_maybe) return F_status_set_error(F_complete_not_utf);

        return status;
      }

      if (status == F_false) {
        if (!buffer.string[range->start]) {
          ++range->start;

          continue;
        }

        break;
      }

      if (buffer.string[range->start] == f_string_eol_s.string[0]) {
        ++range->start;

        return F_found_not;
      }

      range->start += macro_f_utf_byte_width(buffer.string[range->start]);
    } // for

    if (range->start > range->stop || range->start > buffer.used) return F_found_not;

    if (range->stop - range->start < 5) {

      // Increment until stop, while taking into consideration UTF-8 character widths.
      for (; range->start <= range->stop && range->start < buffer.used; ) {

        if (buffer.string[range->start] == f_string_eol_s.string[0]) {
          ++range->start;

          break;
        }

        range->start += macro_f_utf_byte_width(buffer.string[range->start]);
      } // for

      return F_found_not;
    }

    f_number_unsigned_t i = range->start;

    for (; range->start <= range->stop && range->start < buffer.used; ) {

      status = f_utf_is_word(buffer.string + range->start, (range->stop - range->start) + 1, F_true);
      if (F_status_is_error(status)) return status;

      if (status == F_false) {
        if (!buffer.string[range->start]) {
          ++range->start;

          continue;
        }

        break;
      }

      range->start += macro_f_utf_byte_width(buffer.string[range->start]);
    } // for

    if (range->start > range->stop || range->start >= buffer.used || buffer.string[range->start] != f_string_ascii_minus_s.string[0]) {

      // Increment until stop, while taking into consideration UTF-8 character widths.
      for (; range->start <= range->stop && range->start < buffer.used; ) {

        if (buffer.string[range->start] == f_string_eol_s.string[0]) {
          ++range->start;

          break;
        }

        range->start += macro_f_utf_byte_width(buffer.string[range->start]);
      } // for

      return F_found_not;
    }

    {
      f_number_unsigned_t j = 0;
      f_char_t number[5] = { 0, 0, 0, 0, 0 };

      for (++range->start; range->start <= range->stop && range->start < buffer.used && j < 4; ++range->start, ++j) {

        // The hexidecimal representing the number may only be ASCII.
        if (macro_f_utf_byte_width_is(buffer.string[range->start])) {

          // Increment until stop, while taking into consideration UTF-8 character widths.
          for (; range->start <= range->stop && range->start < buffer.used; ) {

            if (buffer.string[range->start] == f_string_eol_s.string[0]) {
              ++range->start;

              break;
            }

            range->start += macro_f_utf_byte_width(buffer.string[range->start]);
          } // for

          if (id) {
            id->type = 0;
          }

          return F_found_not;
        }

        if (isxdigit(buffer.string[range->start])) {
          number[j] = buffer.string[range->start];
        }
        else {
          if (!buffer.string[range->start]) continue;

          break;
        }
      } // for

      if (j == 4) {
        if (id) {
          id->type = strtol(number, 0, 16);
        }
      }
      else {

        // Increment until stop, while taking into consideration UTF-8 character widths.
        for (; range->start <= range->stop && range->start < buffer.used; ) {

          if (buffer.string[range->start] == f_string_eol_s.string[0]) {
            ++range->start;

            break;
          }

          range->start += macro_f_utf_byte_width(buffer.string[range->start]);
        } // for

        if (id) {
          id->type = 0;
        }

        return F_found_not;
      }
    }

    // Skip past all NULLs.
    for (; range->start <= range->stop && range->start < buffer.used; ++range->start) {
      if (buffer.string[range->start]) break;
    } // for

    // The end of line, whitespace, or range stop point are the only valid stop points.
    if (range->start <= range->stop) {
      status = f_utf_is_whitespace(buffer.string + range->start, (range->stop - range->start) + 1, F_false);

      if (F_status_is_error(status)) {
        if (id) {
          id->type = 0;
        }

        return status;
      }

      if (status == F_false) {

        // Increment until stop, while taking into consideration UTF-8 character widths.
        for (; range->start <= range->stop && range->start < buffer.used; ) {

          if (buffer.string[range->start] == f_string_eol_s.string[0]) {
            ++range->start;

            break;
          }

          range->start += macro_f_utf_byte_width(buffer.string[range->start]);
        } // for

        if (id) {
          id->type = 0;
        }

        return F_found_not;
      }
    }

    if (buffer.string[range->start] == f_string_eol_s.string[0]) {
      ++range->start;
    }

    if (id) {
      for (f_number_unsigned_t j = i, i = 0; j <= range->stop && j < buffer.used; ++j) {

        if (!buffer.string[j]) continue;
        if (buffer.string[j] == f_string_ascii_minus_s.string[0]) break;

        id->name[i++] = buffer.string[j];
      } // for

      id->used = i + 1;

      if (id->used < 64) {
        id->name[id->used] = 0;
      }
    }

    return F_found;
  }
#endif // _di_f_parse_dynamic_partial_fll_identify_

#ifndef _di_f_parse_seek_line_to_utf_character_
  f_status_t f_parse_seek_line_to_utf_character(const f_string_t string, const f_utf_char_t seek_to, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = macro_f_utf_char_t_width(seek_to);

    f_status_t status = F_okay;

    unsigned short width = 0;
    f_number_unsigned_t width_max = (range->stop - range->start) + 1;

    for (; range->start <= range->stop; range->start += width) {

      width_max = (range->stop - range->start) + 1;

      width = macro_f_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;

        if (string[range->start] == f_string_eol_s.string[0]) return F_okay_eol;
        if (seek_width == width && string[range->start] == seek_to) return F_okay;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_eos);

        if (width == seek_width) {
          f_utf_char_t character = 0;

          status = f_utf_char_to_character(string + range->start, width_max, &character);
          if (F_status_is_error(status)) return status;
          if (character == seek_to) return F_okay;
        }
      }
    } // for

    return F_okay_stop;
  }
#endif // _di_f_parse_seek_line_to_utf_character_

#ifndef _di_f_parse_seek_line_until_graph_
  f_status_t f_parse_seek_line_until_graph(const f_string_t string, const uint8_t placeholder, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_okay;
    unsigned short width = 0;

    f_number_unsigned_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_graph(string + range->start, width_max)) == F_false) {

      if (F_status_is_error(status)) return status;
      if (string[range->start] == f_string_eol_s.string[0]) return F_okay_eol;

      width = macro_f_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;
      }
      else if (width == 1) {

        // Do not operate on UTF-8 fragments that are not the first byte of the character.
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
      }

      range->start += width;

      if (range->start > range->stop) return F_okay_stop;

      width_max = (range->stop - range->start) + 1;
    } // while

    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_f_parse_seek_line_until_graph_

#ifndef _di_f_parse_seek_line_until_graph_non_
  f_status_t f_parse_seek_line_until_graph_non(const f_string_t string, const uint8_t placeholder, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    f_status_t status = F_okay;
    unsigned short width = 0;

    f_number_unsigned_t width_max = (range->stop - range->start) + 1;

    while (string[range->start] == placeholder || (status = f_utf_is_whitespace(string + range->start, width_max, F_false)) == F_false) {

      if (F_status_is_error(status)) return status;

      if (string[range->start] == f_string_eol_s.string[0]) return F_okay_eol;

      width = macro_f_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;
      }
      else if (width == 1) {

        // Do not operate on UTF-8 fragments that are not the first byte of the character.
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);
      }

      range->start += width;

      if (range->start > range->stop) return F_okay_stop;

      width_max = (range->stop - range->start) + 1;
    } // while

    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_f_parse_seek_line_until_graph_non_

#ifndef _di_f_parse_seek_to_utf_character_
  f_status_t f_parse_seek_to_utf_character(const f_string_t string, const f_utf_char_t seek_to, f_string_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (range->start > range->stop) return F_data_not_stop;

    const unsigned short seek_width = macro_f_utf_char_t_width(seek_to);

    f_status_t status = F_okay;

    unsigned short width = 0;
    f_number_unsigned_t width_max = 0;

    for (; range->start <= range->stop; range->start += width) {

      width_max = (range->stop - range->start) + 1;

      width = macro_f_utf_byte_width_is(string[range->start]);

      if (!width) {
        width = 1;

        if (seek_width == width && string[range->start] == seek_to) return F_okay;
      }
      // Do not operate on UTF-8 fragments that are not the first byte of the character.
      else if (width == 1) {
        return F_status_set_error(F_complete_not_utf);
      }
      else {
        if (range->start + width > range->stop) return F_status_set_error(F_complete_not_utf_stop);

        if (width == seek_width) {
          f_utf_char_t character = 0;

          status = f_utf_char_to_character(string + range->start, width_max, &character);
          if (F_status_is_error(status)) return status;
          if (character == seek_to) return F_okay;
        }
      }
    } // for

    return F_okay_stop;
  }
#endif // _di_f_parse_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif
