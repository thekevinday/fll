#include "utf8.h"
#include "private-common.h"
#include "private-print.h"
#include "private-utf8.h"
#include "private-utf8_bytecode.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_convert_bytecode_
  f_status_t utf8_convert_bytecode(utf8_data_t * const data, const f_string_static_t character) {

    f_status_t status = F_none;
    bool valid_not = F_false;

    uint32_t codepoint = 0;

    if (character.used) {
      status = f_utf_unicode_to(character.string, character.used, &codepoint);
    }
    else {
      status = F_status_set_error(F_utf);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_failure || status == F_utf || status == F_complete_not_utf || status == F_utf_fragment || status == F_valid_not) {
        valid_not = F_true;

        utf8_print_character_invalid(data, character);
      }
      else {
        status = F_status_set_error(status);

        utf8_print_error_decode(data, status, character);

        return status;
      }
    }
    else if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_none_e) {
      if (data->mode & utf8_mode_to_bytecode_d) {
        utf8_print_bytecode(data, character);
      }
      else if (data->mode & utf8_mode_to_codepoint_d) {
        utf8_print_codepoint(data, codepoint);
      }
      else {
        utf8_print_combining_or_width(data, character);
      }
    }

    if (valid_not || F_status_is_error(status)) {
      return F_utf;
    }

    return F_none;
  }
#endif // _di_utf8_convert_bytecode_

#ifndef _di_utf8_process_file_bytecode_
  f_status_t utf8_process_file_bytecode(utf8_data_t * const data, const f_file_t file) {

    f_status_t status = F_none;

    bool valid = F_true;
    bool next = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_char_t block_character[4] = { 0, 0, 0, 0 };
    f_string_static_t character = macro_f_string_static_t_initialize2(block_character, 4);

    do {
      status = f_file_read_block(file, &data->buffer);

      if (status == F_none_eof && !data->buffer.used) break;

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
          character.used = macro_f_utf_byte_width(data->buffer.string[i]);
          next = F_false;
        }

        for (; j < character.used && i < data->buffer.used; ++j, ++i) {
          character.string[j] = data->buffer.string[i];
        } // for

        if (j == character.used) {
          if (data->mode & utf8_mode_from_bytecode_d) {
            status = utf8_convert_bytecode(data, character);
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

    } while (F_status_is_fine(status) && status != F_interrupt);

    // Handle last (incomplete) character when the buffer ended before the character is supposed to end.
    if (F_status_is_error_not(status) && status != F_interrupt && next == F_false) {
      character.used = j;

      if (data->mode & utf8_mode_from_bytecode_d) {
        status = utf8_convert_bytecode(data, character);
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

    if (F_status_is_error(status) || status == F_interrupt) {
      return status;
    }

    return valid;
  }
#endif // _di_utf8_process_file_bytecode_

#ifdef __cplusplus
} // extern "C"
#endif
