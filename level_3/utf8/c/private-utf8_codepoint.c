#include "utf8.h"
#include "private-common.h"
#include "private-print.h"
#include "private-utf8.h"
#include "private-utf8_binary.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_convert_codepoint_
  f_status_t utf8_convert_codepoint(utf8_data_t * const data, const f_string_static_t character, uint8_t *mode) {

    f_status_t status = F_none;
    bool valid_not = F_false;

    if (*mode != utf8_codepoint_mode_end) {
      if (data->text.used + character.used >= data->text.size) {
        status = f_string_dynamic_increase_by(utf8_default_allocation_step_d, &data->text);
        if (F_status_is_error(status)) return status;
      }

      for (f_array_length_t i = 0; i < character.used; ++i) {
        data->text.string[data->text.used++] = character.string[i];
      } // for
    }

    if (!(*mode == utf8_codepoint_mode_end || *mode == utf8_codepoint_mode_bad_end)) {
      return F_none;
    }

    if (*mode == utf8_codepoint_mode_end) {
      uint32_t codepoint = 0;

      status = f_utf_unicode_string_to(data->text.string, data->text.used, &codepoint);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_failure || F_status_set_fine(status) == F_utf || F_status_set_fine(status) == F_valid_not) {
          valid_not = F_true;

          if (data->main->parameters[utf8_parameter_strip_invalid].result == f_console_result_none && data->main->parameters[utf8_parameter_verify].result == f_console_result_none) {
            fl_print_format("%s%[%r%]%s", data->file.stream, data->prepend, data->valid_not, data->text, data->valid_not, data->append);
          }
        }
        else {
          if (data->main->parameters[utf8_parameter_strip_invalid].result == f_console_result_none && data->main->parameters[utf8_parameter_verify].result == f_console_result_none) {
            utf8_print_error_decode(data, status, character);
          }

          return status;
        }
      }
      else if (data->main->parameters[utf8_parameter_verify].result == f_console_result_none) {
        if (data->mode & utf8_mode_to_binary_d) {
          char byte[5] = { 0, 0, 0, 0, 0 };
          f_string_static_t text = macro_f_string_static_t_initialize(byte, 5);

          status = f_utf_unicode_from(codepoint, 4, &text.string);

          if (F_status_is_error(status)) {
            utf8_print_error_decode(data, status, character);
          }
          else {
            status = F_none;
            text.used = macro_f_utf_byte_width(text.string[0]);

            fl_print_format("%s%r%s", data->file.stream, data->prepend, text, data->append);
          }
        }
        else {
          fl_print_format(codepoint < 0xffff ? "%sU+%04_U%s" : "%sU+%6_U%s", data->file.stream, data->prepend, codepoint, data->append);
        }
      }
    }
    else {
      status = F_none;

      if (data->main->parameters[utf8_parameter_verify].result == f_console_result_none) {
        fl_print_format("%s%[%r%]%s", data->file.stream, data->prepend, data->valid_not, data->text, data->valid_not, data->append);
      }
    }

    *mode = utf8_codepoint_mode_ready;
    data->text.used = 0;

    if (valid_not || F_status_is_error(status)) {
      return F_utf;
    }

    return status;
  }
#endif // _di_utf8_convert_codepoint_

#ifndef _di_utf8_detect_codepoint_
  f_status_t utf8_detect_codepoint(utf8_data_t * const data, const f_string_static_t character, uint8_t *mode) {

    // Skip past NULL.
    if (!character.string[0]) {
      return F_next;
    }

    f_status_t status = F_none;

    if (character.string[0] == f_string_ascii_u_s[0] || character.string[0] == f_string_ascii_U_s[0] || character.string[0] == f_string_ascii_plus_s[0]) {
      // Do nothing.
    }
    else if (character.string[0] == f_string_ascii_space_s[0]) {
      status = F_space;
    }
    else if (macro_f_utf_byte_width_is(*character.string)) {
      status = f_utf_is_whitespace(character.string, 4);
      if (F_status_is_error(status)) return status;

      if (status == F_true) {
        status = F_space;
      }
      else {
        status = F_valid_not;
      }
    }
    else {
      if (character.string[0] < 0x30 || character.string[0] > 0x39 && character.string[0] < 0x41 || character.string[0] > 0x46 && character.string[0] < 0x61 || character.string[0] > 0x66) {

        status = f_utf_is_whitespace(character.string, 4);
        if (F_status_is_error(status)) return status;

        if (status == F_true) {
          status = F_space;
        }
        else {
          status = F_valid_not;
        }
      }
    }

    if (status == F_valid_not) {
      if (*mode != utf8_codepoint_mode_bad) {
        if (*mode == utf8_codepoint_mode_bad_begin) {
          *mode = utf8_codepoint_mode_bad;
        }
        else {
          *mode = utf8_codepoint_mode_bad_begin;
        }
      }
    }
    else {
      if (*mode == utf8_codepoint_mode_bad) {
        if (status == F_space) {
          *mode = utf8_codepoint_mode_bad_end;
        }
      }
      else if (*mode == utf8_codepoint_mode_ready) {
        if (status == F_space) {
          status = F_next;
        }
        else if (character.string[0] == f_string_ascii_u_s[0] || character.string[0] == f_string_ascii_U_s[0]) {
          *mode = utf8_codepoint_mode_begin;
          data->text.used = 0;
        }
        else {
          *mode = utf8_codepoint_mode_bad;
        }
      }
      else if (*mode == utf8_codepoint_mode_begin) {
        if (character.string[0] == f_string_ascii_plus_s[0]) {
          *mode = utf8_codepoint_mode_number;
        }
        else {
          *mode = utf8_codepoint_mode_bad;
        }
      }
      else if (*mode == utf8_codepoint_mode_number) {
        if (status == F_space) {
          *mode = utf8_codepoint_mode_end;
        }
      }
    }

    return F_none;
  }
#endif // _di_utf8_detect_codepoint_

#ifndef _di_utf8_process_file_codepoint_
  f_status_t utf8_process_file_codepoint(utf8_data_t * const data, const f_file_t file) {

    f_status_t status = F_none;
    bool valid = F_true;
    bool next = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready;
    uint16_t signal_check = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    char block[4] = { 0, 0, 0, 0 };
    f_string_static_t character = macro_f_string_static_t_initialize(block, 4);

    do {
      status = f_file_read_block(file, &data->buffer);

      if (status == F_none_eof && !data->buffer.used) break;

      for (i = 0; F_status_is_fine(status) && i < data->buffer.used; ) {

        if (!((++signal_check) % utf8_signal_check_d)) {
          if (utf8_signal_received(data)) {
            utf8_print_signal_received(data, status);

            status = F_status_set_error(F_signal);
            break;
          }
        }

        status = F_none;

        // Get the current width only when processing a new block.
        if (next) {
          character.used = macro_f_utf_byte_width(data->buffer.string[i]);
          next = F_false;
        }

        for (; j < character.used && i < data->buffer.used; ++j, ++i) {
          character.string[j] = data->buffer.string[i];
        } // for

        if (j == character.used) {
          if (data->mode & utf8_mode_from_binary_d) {
            status = utf8_convert_binary(data, character);
          }
          else {
            status = utf8_detect_codepoint(data, character, &mode_codepoint);

            if (F_status_is_fine(status) && status != F_next) {
              status = utf8_convert_codepoint(data, character, &mode_codepoint);
            }
          }

          if (status == F_utf) {
            valid = F_false;
          }

          j = 0;
          next = F_true;
        }
      } // for

      i = 0;
      data->buffer.used = 0;

    } while (F_status_is_fine(status) && status != F_signal);

    // Handle last (incomplete) character when the buffer ended before the character is supposed to end.
    if (status != F_signal && next == F_false) {
      character.used = j;

      if (data->mode & utf8_mode_from_binary_d) {
        status = utf8_convert_binary(data, character);
      }
      else {
        status = utf8_detect_codepoint(data, character, &mode_codepoint);

        if (F_status_is_fine(status) && status != F_next) {
          status = utf8_convert_codepoint(data, character, &mode_codepoint);
        }
      }

      if (status == F_utf) {
        valid = F_false;
      }
    }

    data->buffer.used = 0;

    if (F_status_is_error(status)) {
      return status;
    }

    return valid;
  }
#endif // _di_utf8_process_file_codepoint_

#ifdef __cplusplus
} // extern "C"
#endif
