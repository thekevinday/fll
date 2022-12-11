#include "utf8.h"
#include "private-common.h"
#include "private-utf8.h"
#include "private-utf8_bytesequence.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_convert_codepoint_
  f_status_t utf8_convert_codepoint(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t unicode, uint8_t *mode) {

    f_status_t status = F_none;
    bool valid_not = F_false;

    if (*mode != utf8_codepoint_mode_end_e) {
      if (setting->text.used + unicode.used >= setting->text.size) {
        status = f_string_dynamic_increase_by(utf8_default_allocation_step_d, &setting->text);
        if (F_status_is_error(status)) return status;
      }

      for (f_array_length_t i = 0; i < unicode.used; ++i) {
        setting->text.string[setting->text.used++] = unicode.string[i];
      } // for
    }

    if (*mode == utf8_codepoint_mode_end_e) {
      uint32_t codepoint = 0;

      status = f_utf_unicode_string_to(setting->text.string, setting->text.used, &codepoint);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_failure || status == F_utf_not || status == F_complete_not_utf || status == F_utf_fragment || status == F_valid_not) {
          valid_not = F_true;

          utf8_print_character_invalid(setting, main->output, unicode);
        }
        else {
          status = F_status_set_error(status);

          utf8_print_error_decode(setting, main->error, status, unicode);

          return status;
        }
      }
      else if (!(setting->flag & utf8_main_flag_verify_e)) {
        if (setting->mode & utf8_mode_to_codepoint_e) {
          utf8_print_codepoint(setting, main->output, codepoint);
        }
        else {
          f_char_t byte[4] = { 0, 0, 0, 0 };
          f_string_static_t unicode = macro_f_string_static_t_initialize(byte, 0, 4);

          status = f_utf_unicode_from(codepoint, 4, &unicode.string);

          if (F_status_is_error(status)) {
            if (setting->mode & utf8_mode_to_bytesequence_e) {
              utf8_print_error_encode(setting, main->error, status, codepoint);
            }
            else {
              utf8_print_combining_or_width_invalid(setting, main->output);
            }
          }
          else if (setting->mode & utf8_mode_to_bytesequence_e) {
            status = F_none;
            unicode.used = macro_f_utf_byte_width(unicode.string[0]);

            utf8_print_bytesequence(setting, main->output, unicode);
          }
          else {
            status = F_none;

            utf8_print_combining_or_width(setting, main->output, unicode);
          }
        }
      }
    }
    else if (*mode == utf8_codepoint_mode_bad_end_e) {
      status = F_none;

      utf8_print_character_invalid(setting, main->output, unicode);
    }
    else {
      return F_none;
    }

    *mode = utf8_codepoint_mode_ready_e;
    setting->text.used = 0;

    if (valid_not || F_status_is_error(status)) {
      return F_utf_not;
    }

    return status;
  }
#endif // _di_utf8_convert_codepoint_

#ifndef _di_utf8_convert_raw_
  f_status_t utf8_convert_raw(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t hex, uint8_t *mode) {

    f_status_t status = F_none;
    bool valid_not = F_false;

    if (*mode != utf8_codepoint_mode_raw_end_e) {
      if (setting->text.used + hex.used >= setting->text.size) {
        status = f_string_dynamic_increase_by(utf8_default_allocation_step_d, &setting->text);
        if (F_status_is_error(status)) return status;
      }

      for (f_array_length_t i = 0; i < hex.used; ++i) {
        setting->text.string[setting->text.used++] = hex.string[i];
      } // for
    }

    if (*mode == utf8_codepoint_mode_raw_end_e) {
      f_utf_char_t raw = 0;

      {
        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, setting->text, &number);

        raw = (f_utf_char_t) number;
      }

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_number || status == F_utf_not || status == F_complete_not_utf || status == F_utf_fragment || status == F_number_decimal || status == F_number_negative || status == F_number_positive || status == F_number_overflow) {
          valid_not = F_true;

          utf8_print_character_invalid(setting, main->output, hex);
        }
        else {
          status = F_status_set_error(status);

          utf8_print_error_decode(setting, main->error, status, hex);

          return status;
        }
      }
      else if (!(setting->flag & utf8_main_flag_verify_e)) {

        // The width actually includes the leading '0x', which is not part of the width of the digit in binary form.
        uint8_t width = setting->text.used > 1 ? (setting->text.used - 2) / 2 : 0;

        if ((setting->text.used - 2) % 2) {
          ++width;
        }

        if (setting->mode & utf8_mode_to_bytesequence_e) {
          utf8_print_raw_bytesequence(setting, main->output, raw, width);
        }
        else if (setting->mode & utf8_mode_to_codepoint_e) {
          utf8_print_raw_codepoint(setting, main->output, setting->text);
        }
        else {
          utf8_print_raw_combining_or_width(setting, main->output, width);
        }
      }
    }
    else if (*mode == utf8_codepoint_mode_bad_end_e) {
      status = F_none;

      utf8_print_character_invalid(setting, main->output, hex);
    }
    else {
      return F_none;
    }

    *mode = utf8_codepoint_mode_ready_e;
    setting->text.used = 0;

    if (valid_not || F_status_is_error(status)) {
      return F_valid_not;
    }

    return status;
  }
#endif // _di_utf8_convert_raw_

#ifndef _di_utf8_detect_codepoint_
  f_status_t utf8_detect_codepoint(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t unicode, uint8_t *mode) {

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
          setting->text.used = 0;
        }
        else if (unicode.string[0] == f_string_ascii_0_s.string[0]) {
          *mode = utf8_codepoint_mode_raw_begin_e;
          setting->text.used = 0;
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
  f_status_t utf8_process_file_codepoint(fll_program_data_t * const main, utf8_setting_t * const setting, const f_file_t file) {

    f_status_t status = F_none;
    bool valid = F_true;
    bool next = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_char_t block[5] = { 0, 0, 0, 0, 0 };
    f_string_static_t sequence = macro_f_string_static_t_initialize(block, 0, 0);

    do {
      status = f_file_stream_read_block(file, &setting->buffer);

      if (status == F_none_eof && !setting->buffer.used) {

        // Handle complete character, which must be explicitly set to end in this situation.
        if (mode_codepoint == utf8_codepoint_mode_number_e || mode_codepoint == utf8_codepoint_mode_raw_number_e) {
          if (mode_codepoint == utf8_codepoint_mode_number_e) {
            mode_codepoint = utf8_codepoint_mode_end_e;

            status = utf8_convert_codepoint(main, setting, sequence, &mode_codepoint);
          }
          else if (mode_codepoint == utf8_codepoint_mode_raw_number_e) {
            mode_codepoint = utf8_codepoint_mode_raw_end_e;

            status = utf8_convert_raw(main, setting, sequence, &mode_codepoint);

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

      for (i = 0; F_status_is_fine(status) && i < setting->buffer.used; ) {

        if (!((++main->signal_check) % utf8_signal_check_d)) {
          if (fll_program_standard_signal_received(main)) {
            fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

            status = F_interrupt;

            break;
          }

          main->signal_check = 0;
        }

        status = F_none;

        // Get the current width only when processing a new block.
        if (next) {
          sequence.used = macro_f_utf_byte_width(setting->buffer.string[i]);
          next = F_false;
        }

        for (; j < sequence.used && i < setting->buffer.used; ++j, ++i) {
          sequence.string[j] = setting->buffer.string[i];
        } // for

        if (j >= sequence.used) {
          if (setting->mode & utf8_mode_from_bytesequence_e) {
            status = utf8_convert_bytesequence(main, setting, sequence);
          }
          else {
            status = utf8_detect_codepoint(main, setting, sequence, &mode_codepoint);

            if (F_status_is_fine(status) && status != F_next) {
              if (mode_codepoint == utf8_codepoint_mode_raw_begin_e || mode_codepoint == utf8_codepoint_mode_raw_number_e || mode_codepoint == utf8_codepoint_mode_raw_end_e) {
                status = utf8_convert_raw(main, setting, sequence, &mode_codepoint);

                // Raw mode represents an invalid Unicode sequence.
                valid = F_false;
              }
              else {
                status = utf8_convert_codepoint(main, setting, sequence, &mode_codepoint);
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

      setting->buffer.used = 0;

    } while (F_status_is_fine(status) && status != F_interrupt);

    // Handle last (incomplete) character when the buffer ended before the character is supposed to end.
    if (F_status_is_error_not(status) && status != F_interrupt && next == F_false) {
      sequence.used = j;

      if (setting->mode & utf8_mode_from_bytesequence_e) {
        status = utf8_convert_bytesequence(main, setting, sequence);
      }
      else {
        status = utf8_detect_codepoint(main, setting, sequence, &mode_codepoint);

        if (F_status_is_fine(status) && status != F_next) {
          if (mode_codepoint == utf8_codepoint_mode_raw_begin_e || mode_codepoint == utf8_codepoint_mode_raw_number_e || mode_codepoint == utf8_codepoint_mode_raw_end_e) {
            status = utf8_convert_raw(main, setting, sequence, &mode_codepoint);

            // Raw mode represents an invalid Unicode sequence.
            valid = F_false;
          }
          else {
            status = utf8_convert_codepoint(main, setting, sequence, &mode_codepoint);
          }
        }
      }

      if (status == F_utf_not) {
        valid = F_false;
      }
    }

    setting->buffer.used = 0;

    if (F_status_is_error(status) || status == F_interrupt) return status;

    return valid;
  }
#endif // _di_utf8_process_file_codepoint_

#ifdef __cplusplus
} // extern "C"
#endif
