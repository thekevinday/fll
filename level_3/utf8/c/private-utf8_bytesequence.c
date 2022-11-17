#include "utf8.h"
#include "private-common.h"
#include "private-utf8.h"
#include "private-utf8_bytesequence.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_convert_bytesequence_
  f_status_t utf8_convert_bytesequence(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t sequence) {

    f_status_t status = F_none;
    bool valid_not = F_false;

    uint32_t codepoint = 0;

    if (sequence.used) {
      status = f_utf_unicode_to(sequence.string, sequence.used, &codepoint);
    }
    else {
      status = F_status_set_error(F_utf_not);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_failure || status == F_utf_not || status == F_complete_not_utf || status == F_utf_fragment || status == F_valid_not) {
        valid_not = F_true;

        utf8_print_character_invalid(setting, main->output, sequence);
      }
      else {
        status = F_status_set_error(status);

        utf8_print_error_decode(setting, main->error, status, sequence);

        return status;
      }
    }
    else if (!(setting->flag & utf8_main_flag_verify_e)) {
      if (setting->mode & utf8_mode_to_bytesequence_e) {
        utf8_print_bytesequence(setting, main->output, sequence);
      }
      else if (setting->mode & utf8_mode_to_codepoint_e) {
        utf8_print_codepoint(setting, main->output, codepoint);
      }
      else {
        utf8_print_combining_or_width(setting, main->output, sequence);
      }
    }

    if (valid_not || F_status_is_error(status)) return F_utf_not;

    return F_none;
  }
#endif // _di_utf8_convert_bytesequence_

#ifndef _di_utf8_process_file_bytesequence_
  f_status_t utf8_process_file_bytesequence(fll_program_data_t * const main, utf8_setting_t * const setting, const f_file_t file) {

    f_status_t status = F_none;

    bool valid = F_true;
    bool next = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_char_t block[4] = { 0, 0, 0, 0 };
    f_string_static_t sequence = macro_f_string_static_t_initialize(block, 0, 4);

    do {
      status = f_file_stream_read_block(file, &setting->buffer);

      if (status == F_none_eof && !setting->buffer.used) break;

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

        if (j == sequence.used) {
          if (setting->mode & utf8_mode_from_bytesequence_e) {
            status = utf8_convert_bytesequence(main, setting, sequence);
          }
          else {
            status = utf8_detect_codepoint(main, setting, sequence, &mode_codepoint);

            if (F_status_is_fine(status) && status != F_next) {
              status = utf8_convert_codepoint(main, setting, sequence, &mode_codepoint);
            }
          }

          if (status == F_utf_not) {
            valid = F_false;
          }

          j = 0;
          next = F_true;
        }
      } // for

      i = 0;
      setting->buffer.used = 0;

    } while (F_status_is_fine(status) && status != F_interrupt);

    // Handle last (incomplete) sequence when the buffer ended before the sequence is supposed to end.
    if (F_status_is_error_not(status) && status != F_interrupt && next == F_false) {
      sequence.used = j;

      if (setting->mode & utf8_mode_from_bytesequence_e) {
        status = utf8_convert_bytesequence(main, setting, sequence);
      }
      else {
        status = utf8_detect_codepoint(main, setting, sequence, &mode_codepoint);

        if (F_status_is_fine(status) && status != F_next) {
          status = utf8_convert_codepoint(main, setting, sequence, &mode_codepoint);
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
#endif // _di_utf8_process_file_bytesequence_

#ifdef __cplusplus
} // extern "C"
#endif
