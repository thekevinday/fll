#include "utf8.h"
#include "private-common.h"
#include "private-utf8.h"
#include "private-utf8_bytesequence.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_process_text_
  f_status_t utf8_process_text(fll_program_data_t * const main, utf8_setting_t * const setting, f_string_static_t text) {

    if (!text.used) return F_true;

    f_status_t status = F_none;
    bool valid = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    utf8_process_text_width(&text);

    f_file_stream_lock(main->output.to);

    for (; text.string[0] && F_status_is_error_not(status); ) {

      if (!((++main->signal_check) % utf8_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

          status = F_status_set_error(F_interrupt);

          break;
        }

        main->signal_check = 0;
      }

      status = F_none;

      if (setting->mode & utf8_mode_from_bytesequence_e) {
        status = utf8_convert_bytesequence(main, setting, text);
      }
      else {
        status = utf8_detect_codepoint(main, setting, text, &mode_codepoint);

        if (F_status_is_error(status)) {
          utf8_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "utf8_detect_codepoint", F_true);

          break;
        }

        if (F_status_is_fine(status) && status != F_next) {
          status = utf8_convert_codepoint(main, setting, text, &mode_codepoint);
        }
      }

      if (status == F_utf_not) {
        valid = F_false;
      }

      text.string += text.used;
      utf8_process_text_width(&text);
    } // for

    if (F_status_is_error_not(status) && !(setting->mode & utf8_mode_from_bytesequence_e)) {
      if (mode_codepoint != utf8_codepoint_mode_ready_e && mode_codepoint != utf8_codepoint_mode_end_e && mode_codepoint != utf8_codepoint_mode_bad_end_e && mode_codepoint != utf8_codepoint_mode_raw_end_e) {
        if (mode_codepoint == utf8_codepoint_mode_number_e) {
          mode_codepoint = utf8_codepoint_mode_end_e;
        }
        else if (mode_codepoint == utf8_codepoint_mode_raw_number_e) {
          mode_codepoint = utf8_codepoint_mode_raw_end_e;
        }
        else {
          mode_codepoint = utf8_codepoint_mode_bad_end_e;
          valid = F_false;
        }

        text.used = 0;

        if (mode_codepoint == utf8_codepoint_mode_raw_number_e) {
          status = utf8_convert_raw(main, setting, text, &mode_codepoint);
        }
        else {
          status = utf8_convert_codepoint(main, setting, text, &mode_codepoint);
        }
      }
    }

    if (F_status_is_error(status)) {
      f_file_stream_unlock(main->output.to);

      return status;
    }

    f_file_stream_unlock(main->output.to);

    return valid;
  }
#endif // _di_utf8_process_text_

#ifndef _di_utf8_process_text_width_
  void utf8_process_text_width(f_string_static_t *text) {

    if (!text->string[0]) return;

    text->used = 0;
    text->size = macro_f_utf_byte_width(text->string[0]);

    if (text->size == 1) {
      text->used = text->string[0] ? 1 : 0;
    }
    else if (text->size == 2) {
      if (!text->string[0]) {
        text->used = 1;
      }
      else {
        text->used = text->string[1] ? 2 : 1;
      }
    }
    else if (text->size == 3) {
      if (!text->string[0]) {
        text->used = 1;
      }
      else if (!text->string[1]) {
        text->used = 2;
      }
      else {
        text->used = text->string[2] ? 3 : 2;
      }
    }
    else {
      if (!text->string[0]) {
        text->used = 1;
      }
      else if (!text->string[1]) {
        text->used = 2;
      }
      else if (!text->string[2]) {
        text->used = 3;
      }
      else {
        text->used = text->string[3] ? 4 : 3;
      }
    }
  }
#endif // _di_utf8_process_text_width_

#ifdef __cplusplus
} // extern "C"
#endif
