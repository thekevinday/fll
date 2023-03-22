#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_process_text_
  void utf8_process_text(utf8_main_t * const main, f_string_static_t text) {

    if (!main) return;

    if (!text.used) {
      main->setting.state.status = F_true;

      return;
    }

    main->setting.state.status = F_none;

    bool valid = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    utf8_process_text_width(&text);

    f_file_stream_lock(main->program.output.to);

    for (; text.string[0] && F_status_is_error_not(main->setting.state.status); ) {

      if (!((++main->program.signal_check) % utf8_signal_check_d)) {
        if (fll_program_standard_signal_received(&main->program)) {
          fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

          main->setting.state.status = F_status_set_error(F_interrupt);

          break;
        }

        main->program.signal_check = 0;
      }

      main->setting.state.status = F_none;

      if (main->setting.mode & utf8_mode_from_bytesequence_e) {
        utf8_convert_bytesequence(main, text);
      }
      else {
        utf8_detect_codepoint(main, text, &mode_codepoint);

        if (F_status_is_error(main->setting.state.status)) {
          fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_utf8_f(utf8_detect_codepoint), fll_error_file_flag_fallback_e);

          break;
        }

        if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_next) {
          utf8_convert_codepoint(main, text, &mode_codepoint);
        }
      }

      if (main->setting.state.status == F_utf_not) {
        valid = F_false;
      }

      text.string += text.used;
      utf8_process_text_width(&text);
    } // for

    if (F_status_is_error_not(main->setting.state.status) && !(main->setting.mode & utf8_mode_from_bytesequence_e)) {
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
          utf8_convert_raw(main, text, &mode_codepoint);
        }
        else {
          utf8_convert_codepoint(main, text, &mode_codepoint);
        }
      }
    }

    f_file_stream_unlock(main->program.output.to);

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = valid;
    }
  }
#endif // _di_utf8_process_text_

#ifndef _di_utf8_process_text_width_
  void utf8_process_text_width(f_string_static_t *text) {

    if (!text) return;
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
