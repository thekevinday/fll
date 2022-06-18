#include "utf8.h"
#include "private-common.h"
#include "private-print.h"
#include "private-utf8.h"
#include "private-utf8_bytesequence.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_process_text_
  f_status_t utf8_process_text(utf8_data_t * const data, f_string_static_t text) {

    if (!text.used) return F_true;

    f_status_t status = F_none;
    bool valid = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    utf8_process_text_width(&text);

    flockfile(data->file.stream);

    for (; text.string[0] && F_status_is_error_not(status); ) {

      if (!((++data->main->signal_check) % utf8_signal_check_d)) {
        if (fll_program_standard_signal_received(data->main)) {
          utf8_print_signal_received(data, status);

          status = F_status_set_error(F_interrupt);

          break;
        }

        data->main->signal_check = 0;
      }

      status = F_none;

      if (data->mode & utf8_mode_from_bytesequence_d) {
        status = utf8_convert_bytesequence(data, text);
      }
      else {
        status = utf8_detect_codepoint(data, text, &mode_codepoint);

        if (F_status_is_error(status)) {
          fll_error_print(data->main->error, F_status_set_fine(status), "utf8_detect_codepoint", F_true);

          break;
        }

        if (F_status_is_fine(status) && status != F_next) {
          status = utf8_convert_codepoint(data, text, &mode_codepoint);
        }
      }

      if (status == F_utf_not) {
        valid = F_false;
      }

      text.string += text.used;
      utf8_process_text_width(&text);
    } // for

    if (F_status_is_error_not(status) && !(data->mode & utf8_mode_from_bytesequence_d)) {
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
          status = utf8_convert_raw(data, text, &mode_codepoint);
        }
        else {
          status = utf8_convert_codepoint(data, text, &mode_codepoint);
        }
      }
    }

    if (F_status_is_error(status)) {
      funlockfile(data->file.stream);

      return status;
    }

    if (data->main->parameters.array[utf8_parameter_verify_e].result == f_console_result_none_e) {

      // When headers are printed, they are printed with a newline so only print this newline when separate is used without headers being printed.
      if (data->main->parameters.array[utf8_parameter_headers_e].result == f_console_result_none_e && data->main->parameters.array[utf8_parameter_separate_e].result == f_console_result_found_e) {
        f_print_dynamic_raw(f_string_eol_s, data->file.stream);
      }
    }

    funlockfile(data->file.stream);

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
