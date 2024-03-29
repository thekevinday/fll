#include "utf8.h"
#include "private-common.h"
#include "private-print.h"
#include "private-utf8.h"
#include "private-utf8_bytesequence.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_convert_codepoint_
  f_status_t utf8_convert_codepoint(utf8_data_t * const data, const f_string_static_t unicode, uint8_t *mode) {

    f_status_t status = F_none;
    bool valid_not = F_false;

    if (*mode != utf8_codepoint_mode_end_e) {
      if (data->text.used + unicode.used >= data->text.size) {
        status = f_string_dynamic_increase_by(utf8_default_allocation_step_d, &data->text);
        if (F_status_is_error(status)) return status;
      }

      for (f_array_length_t i = 0; i < unicode.used; ++i) {
        data->text.string[data->text.used++] = unicode.string[i];
      } // for
    }

    if (*mode == utf8_codepoint_mode_end_e) {
      uint32_t codepoint = 0;

      status = f_utf_unicode_string_to(data->text.string, data->text.used, &codepoint);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_failure || status == F_utf_not || status == F_complete_not_utf || status == F_utf_fragment || status == F_valid_not) {
          valid_not = F_true;

          utf8_print_character_invalid(data, unicode);
        }
        else {
          status = F_status_set_error(status);

          utf8_print_error_decode(data, status, unicode);

          return status;
        }
      }
      else if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_none_e) {
        if (data->mode & utf8_mode_to_codepoint_d) {
          utf8_print_codepoint(data, codepoint);
        }
        else {
          f_char_t byte[4] = { 0, 0, 0, 0 };
          f_string_static_t unicode = macro_f_string_static_t_initialize(byte, 0, 4);

          status = f_utf_unicode_from(codepoint, 4, &unicode.string);

          if (F_status_is_error(status)) {
            if (data->mode & utf8_mode_to_bytesequence_d) {
              utf8_print_error_encode(data, status, codepoint);
            }
            else {
              utf8_print_error_combining_or_width(data);
            }
          }
          else if (data->mode & utf8_mode_to_bytesequence_d) {
            status = F_none;
            unicode.used = macro_f_utf_byte_width(unicode.string[0]);

            utf8_print_bytesequence(data, unicode);
          }
          else {
            status = F_none;

            utf8_print_combining_or_width(data, unicode);
          }
        }
      }
    }
    else if (*mode == utf8_codepoint_mode_bad_end_e) {
      status = F_none;

      utf8_print_character_invalid(data, unicode);
    }
    else {
      return F_none;
    }

    *mode = utf8_codepoint_mode_ready_e;
    data->text.used = 0;

    if (valid_not || F_status_is_error(status)) {
      return F_utf_not;
    }

    return status;
  }
#endif // _di_utf8_convert_codepoint_

#ifndef _di_utf8_convert_raw_
  f_status_t utf8_convert_raw(utf8_data_t * const data, const f_string_static_t hex, uint8_t *mode) {

    f_status_t status = F_none;
    bool valid_not = F_false;

    if (*mode != utf8_codepoint_mode_raw_end_e) {
      if (data->text.used + hex.used >= data->text.size) {
        status = f_string_dynamic_increase_by(utf8_default_allocation_step_d, &data->text);
        if (F_status_is_error(status)) return status;
      }

      for (f_array_length_t i = 0; i < hex.used; ++i) {
        data->text.string[data->text.used++] = hex.string[i];
      } // for
    }

    if (*mode == utf8_codepoint_mode_raw_end_e) {
      f_utf_char_t raw = 0;

      {
        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data->text, &number);

        raw = (f_utf_char_t) number;
      }

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_number || status == F_utf_not || status == F_complete_not_utf || status == F_utf_fragment || status == F_number_decimal || status == F_number_negative || status == F_number_positive || status == F_number_overflow) {
          valid_not = F_true;

          utf8_print_character_invalid(data, hex);
        }
        else {
          status = F_status_set_error(status);

          utf8_print_error_decode(data, status, hex);

          return status;
        }
      }
      else if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_none_e) {

        // The width actually includes the leading '0x', which is not part of the width of the digit in binary form.
        uint8_t width = data->text.used > 1 ? (data->text.used - 2) / 2 : 0;

        if ((data->text.used - 2) % 2) {
          ++width;
        }

        if (data->mode & utf8_mode_to_bytesequence_d) {
          utf8_print_raw_bytesequence(data, raw, width);
        }
        else if (data->mode & utf8_mode_to_codepoint_d) {
          utf8_print_raw_codepoint(data, data->text);
        }
        else {
          utf8_print_raw_combining_or_width(data, width);
        }
      }
    }
    else if (*mode == utf8_codepoint_mode_bad_end_e) {
      status = F_none;

      utf8_print_character_invalid(data, hex);
    }
    else {
      return F_none;
    }

    *mode = utf8_codepoint_mode_ready_e;
    data->text.used = 0;

    if (valid_not || F_status_is_error(status)) {
      return F_valid_not;
    }

    return status;
  }
#endif // _di_utf8_convert_raw_

#ifndef _di_utf8_detect_codepoint_
  f_status_t utf8_detect_codepoint(utf8_data_t * const data, const f_string_static_t unicode, uint8_t *mode) {

    // Skip past NULL.
    if (!unicode.string[0]) {
      return F_next;
    }

    f_status_t status = F_none;

    if (unicode.string[0] == f_string_ascii_u_s.string[0] || unicode.string[0] == f_string_ascii_U_s.string[0] || unicode.string[0] == f_string_ascii_plus_s.string[0]) {
      // Do nothing.
    }
    else if (unicode.string[0] == f_string_ascii_0_s.string[0] || unicode.string[0] == f_string_ascii_x_s.string[0] || unicode.string[0] == f_string_ascii_X_s.string[0]) {
      // Do nothing.
    }
    else if (unicode.string[0] == f_string_ascii_space_s.string[0]) {
      status = F_space;
    }
    else if (macro_f_utf_byte_width_is(*unicode.string)) {
      status = f_utf_is_whitespace(unicode.string, 4, F_true);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_complete_not_utf || F_status_set_fine(status) == F_utf_fragment) {
          status = F_valid_not;
        }
        else {
          return status;
        }
      }

      if (status == F_true) {
        status = F_space;
      }
      else {
        status = F_valid_not;
      }
    }
    else {
      if (unicode.string[0] < 0x30 || unicode.string[0] > (0x39 && unicode.string[0] < 0x41) || (unicode.string[0] > 0x46 && unicode.string[0] < 0x61) || unicode.string[0] > 0x66) {
        status = f_utf_is_whitespace(unicode.string, 4, F_true);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_complete_not_utf || F_status_set_fine(status) == F_utf_fragment) {
            status = F_valid_not;
          }
          else {
            return status;
          }
        }

        if (status == F_true) {
          status = F_space;
        }
        else {
          status = F_none;
        }
      }
    }

    if (status == F_valid_not) {
      if (*mode != utf8_codepoint_mode_bad_e) {
        if (*mode == utf8_codepoint_mode_bad_begin_e) {
          *mode = utf8_codepoint_mode_bad_e;
        }
        else {
          *mode = utf8_codepoint_mode_bad_begin_e;
        }
      }
    }
    else {
      if (*mode == utf8_codepoint_mode_bad_e) {
        if (status == F_space) {
          *mode = utf8_codepoint_mode_bad_end_e;
        }
      }
      else if (*mode == utf8_codepoint_mode_ready_e) {
        if (status == F_space) {
          status = F_next;
        }
        else if (unicode.string[0] == f_string_ascii_u_s.string[0] || unicode.string[0] == f_string_ascii_U_s.string[0]) {
          *mode = utf8_codepoint_mode_begin_e;
          data->text.used = 0;
        }
        else if (unicode.string[0] == f_string_ascii_0_s.string[0]) {
          *mode = utf8_codepoint_mode_raw_begin_e;
          data->text.used = 0;
        }
        else {
          *mode = utf8_codepoint_mode_bad_e;
        }
      }
      else if (*mode == utf8_codepoint_mode_begin_e) {
        if (unicode.string[0] == f_string_ascii_plus_s.string[0]) {
          *mode = utf8_codepoint_mode_number_e;
        }
        else {
          *mode = utf8_codepoint_mode_bad_e;
        }
      }
      else if (*mode == utf8_codepoint_mode_raw_begin_e) {
        if (unicode.string[0] == f_string_ascii_x_s.string[0] || unicode.string[0] == f_string_ascii_X_s.string[0]) {
          *mode = utf8_codepoint_mode_raw_number_e;
        }
        else {
          *mode = utf8_codepoint_mode_bad_e;
        }
      }
      else if (*mode == utf8_codepoint_mode_raw_number_e) {
        if (status == F_space) {
          *mode = utf8_codepoint_mode_raw_end_e;
        }
      }
      else if (*mode == utf8_codepoint_mode_number_e) {
        if (status == F_space) {
          *mode = utf8_codepoint_mode_end_e;
        }
      }
    }

    return status;
  }
#endif // _di_utf8_detect_codepoint_

#ifndef _di_utf8_process_file_codepoint_
  f_status_t utf8_process_file_codepoint(utf8_data_t * const data, const f_file_t file) {

    f_status_t status = F_none;
    bool valid = F_true;
    bool next = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_char_t block[5] = { 0, 0, 0, 0, 0 };
    f_string_static_t sequence = macro_f_string_static_t_initialize(block, 0, 0);

    do {
      status = f_file_stream_read_block(file, &data->buffer);

      if (status == F_none_eof && !data->buffer.used) {

        // Handle complete character, which must be explicitly set to end in this situation.
        if (mode_codepoint == utf8_codepoint_mode_number_e || mode_codepoint == utf8_codepoint_mode_raw_number_e) {
          if (mode_codepoint == utf8_codepoint_mode_number_e) {
            mode_codepoint = utf8_codepoint_mode_end_e;

            status = utf8_convert_codepoint(data, sequence, &mode_codepoint);
          }
          else if (mode_codepoint == utf8_codepoint_mode_raw_number_e) {
            mode_codepoint = utf8_codepoint_mode_raw_end_e;

            status = utf8_convert_raw(data, sequence, &mode_codepoint);

            // Raw mode represents an invalid Unicode sequence.
            valid = F_false;
          }

          j = 0;
          next = F_true;
          status = F_none_eof;
          mode_codepoint = utf8_codepoint_mode_ready_e;
        }

        break;
      }

      for (i = 0; F_status_is_fine(status) && i < data->buffer.used; ) {

        if (!((++data->main->signal_check) % utf8_signal_check_d)) {
          if (fll_program_standard_signal_received(data->main)) {
            utf8_print_signal_received(data, status);

            status = F_interrupt;

            break;
          }

          data->main->signal_check = 0;
        }

        status = F_none;

        // Get the current width only when processing a new block.
        if (next) {
          sequence.used = macro_f_utf_byte_width(data->buffer.string[i]);
          next = F_false;
        }

        for (; j < sequence.used && i < data->buffer.used; ++j, ++i) {
          sequence.string[j] = data->buffer.string[i];
        } // for

        if (j >= sequence.used) {
          if (data->mode & utf8_mode_from_bytesequence_d) {
            status = utf8_convert_bytesequence(data, sequence);
          }
          else {
            status = utf8_detect_codepoint(data, sequence, &mode_codepoint);

            if (F_status_is_fine(status) && status != F_next) {
              if (mode_codepoint == utf8_codepoint_mode_raw_begin_e || mode_codepoint == utf8_codepoint_mode_raw_number_e || mode_codepoint == utf8_codepoint_mode_raw_end_e) {
                status = utf8_convert_raw(data, sequence, &mode_codepoint);

                // Raw mode represents an invalid Unicode sequence.
                valid = F_false;
              }
              else {
                status = utf8_convert_codepoint(data, sequence, &mode_codepoint);
              }
            }
          }

          if (status == F_utf_not) {
            valid = F_false;
          }

          j = 0;
          next = F_true;
        }
      } // for

      data->buffer.used = 0;

    } while (F_status_is_fine(status) && status != F_interrupt);

    // Handle last (incomplete) character when the buffer ended before the character is supposed to end.
    if (F_status_is_error_not(status) && status != F_interrupt && next == F_false) {
      sequence.used = j;

      if (data->mode & utf8_mode_from_bytesequence_d) {
        status = utf8_convert_bytesequence(data, sequence);
      }
      else {
        status = utf8_detect_codepoint(data, sequence, &mode_codepoint);

        if (F_status_is_fine(status) && status != F_next) {
          if (mode_codepoint == utf8_codepoint_mode_raw_begin_e || mode_codepoint == utf8_codepoint_mode_raw_number_e || mode_codepoint == utf8_codepoint_mode_raw_end_e) {
            status = utf8_convert_raw(data, sequence, &mode_codepoint);

            // Raw mode represents an invalid Unicode sequence.
            valid = F_false;
          }
          else {
            status = utf8_convert_codepoint(data, sequence, &mode_codepoint);
          }
        }
      }

      if (status == F_utf_not) {
        valid = F_false;
      }
    }

    data->buffer.used = 0;

    if (F_status_is_error(status) || status == F_interrupt) {
      return status;
    }

    return valid;
  }
#endif // _di_utf8_process_file_codepoint_

#ifdef __cplusplus
} // extern "C"
#endif
