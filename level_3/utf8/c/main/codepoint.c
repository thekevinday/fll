#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_convert_codepoint_
  void utf8_convert_codepoint(utf8_main_t * const main, const f_string_static_t unicode, uint8_t *mode) {

    if (!main) return;

    main->setting.state.status = F_none;

    bool valid_not = F_false;

    if (*mode != utf8_codepoint_mode_end_e) {
      if (main->setting.text.used + unicode.used >= main->setting.text.size) {
        main->setting.state.status = f_string_dynamic_increase_by(utf8_default_allocation_step_d, &main->setting.text);
        if (F_status_is_error(main->setting.state.status)) return;
      }

      for (f_array_length_t i = 0; i < unicode.used; ++i) {
        main->setting.text.string[main->setting.text.used++] = unicode.string[i];
      } // for
    }

    if (*mode == utf8_codepoint_mode_end_e) {
      uint32_t codepoint = 0;

      main->setting.state.status = f_utf_unicode_string_to(main->setting.text.string, main->setting.text.used, &codepoint);

      if (F_status_is_error(main->setting.state.status)) {
        main->setting.state.status = F_status_set_fine(main->setting.state.status);

        if (main->setting.state.status == F_failure || main->setting.state.status == F_utf_not || main->setting.state.status == F_complete_not_utf || main->setting.state.status == F_utf_fragment || main->setting.state.status == F_valid_not) {
          valid_not = F_true;

          utf8_print_data_character_invalid(&main->program.output, unicode);
        }
        else {
          main->setting.state.status = F_status_set_error(main->setting.state.status);

          utf8_print_error_decode(&main->program.error, unicode);

          return;
        }
      }
      else if (!(main->setting.flag & utf8_main_flag_verify_e)) {
        if (main->setting.mode & utf8_mode_to_codepoint_e) {
          utf8_print_data_codepoint(&main->program.output, codepoint);
        }
        else {
          f_char_t byte[4] = { 0, 0, 0, 0 };
          f_string_static_t unicode = macro_f_string_static_t_initialize(byte, 0, 4);

          main->setting.state.status = f_utf_unicode_from(codepoint, 4, &unicode.string);

          if (F_status_is_error(main->setting.state.status)) {
            if (main->setting.mode & utf8_mode_to_bytesequence_e) {
              utf8_print_error_encode(&main->program.error, codepoint);
            }
            else {
              utf8_print_data_combining_or_width_invalid(&main->program.output);
            }
          }
          else if (main->setting.mode & utf8_mode_to_bytesequence_e) {
            main->setting.state.status = F_none;
            unicode.used = macro_f_utf_byte_width(unicode.string[0]);

            utf8_print_data_bytesequence(&main->program.output, unicode);
          }
          else {
            main->setting.state.status = F_none;

            utf8_print_data_combining_or_width(&main->program.output, unicode);
          }
        }
      }
    }
    else if (*mode == utf8_codepoint_mode_bad_end_e) {
      main->setting.state.status = F_none;

      utf8_print_data_character_invalid(&main->program.output, unicode);
    }
    else {
      main->setting.state.status = F_none;

      return;
    }

    *mode = utf8_codepoint_mode_ready_e;
    main->setting.text.used = 0;

    if (valid_not || F_status_is_error(main->setting.state.status)) {
      main->setting.state.status = F_utf_not;
    }
  }
#endif // _di_utf8_convert_codepoint_

#ifndef _di_utf8_convert_raw_
  void utf8_convert_raw(utf8_main_t * const main, const f_string_static_t hex, uint8_t *mode) {

    if (!main) return;

    main->setting.state.status = F_none;

    bool valid_not = F_false;

    if (*mode != utf8_codepoint_mode_raw_end_e) {
      if (main->setting.text.used + hex.used >= main->setting.text.size) {
        main->setting.state.status = f_string_dynamic_increase_by(utf8_default_allocation_step_d, &main->setting.text);
        if (F_status_is_error(main->setting.state.status)) return;
      }

      for (f_array_length_t i = 0; i < hex.used; ++i) {
        main->setting.text.string[main->setting.text.used++] = hex.string[i];
      } // for
    }

    if (*mode == utf8_codepoint_mode_raw_end_e) {
      f_utf_char_t raw = 0;

      {
        f_number_unsigned_t number = 0;

        main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->setting.text, &number);

        raw = (f_utf_char_t) number;
      }

      if (F_status_is_error(main->setting.state.status)) {
        main->setting.state.status = F_status_set_fine(main->setting.state.status);

        if (main->setting.state.status == F_number || main->setting.state.status == F_utf_not || main->setting.state.status == F_complete_not_utf || main->setting.state.status == F_utf_fragment || main->setting.state.status == F_number_decimal || main->setting.state.status == F_number_negative || main->setting.state.status == F_number_positive || main->setting.state.status == F_number_overflow) {
          valid_not = F_true;

          utf8_print_data_character_invalid(&main->program.output, hex);
        }
        else {
          main->setting.state.status = F_status_set_error(main->setting.state.status);

          utf8_print_error_decode(&main->program.error, hex);

          return;
        }
      }
      else if (!(main->setting.flag & utf8_main_flag_verify_e)) {

        // The width actually includes the leading '0x', which is not part of the width of the digit in binary form.
        uint8_t width = main->setting.text.used > 1 ? (main->setting.text.used - 2) / 2 : 0;

        if ((main->setting.text.used - 2) % 2) {
          ++width;
        }

        if (main->setting.mode & utf8_mode_to_bytesequence_e) {
          utf8_print_data_raw_bytesequence(&main->program.output, raw, width);
        }
        else if (main->setting.mode & utf8_mode_to_codepoint_e) {
          utf8_print_data_raw_codepoint(&main->program.output, main->setting.text);
        }
        else {
          utf8_print_data_raw_combining_or_width(&main->program.output, width);
        }
      }
    }
    else if (*mode == utf8_codepoint_mode_bad_end_e) {
      main->setting.state.status = F_none;

      utf8_print_data_character_invalid(&main->program.output, hex);
    }
    else {
      main->setting.state.status = F_none;

      return;
    }

    *mode = utf8_codepoint_mode_ready_e;
    main->setting.text.used = 0;

    if (valid_not || F_status_is_error(main->setting.state.status)) {
      main->setting.state.status = F_valid_not;
    }
  }
#endif // _di_utf8_convert_raw_

#ifndef _di_utf8_detect_codepoint_
  void utf8_detect_codepoint(utf8_main_t * const main, const f_string_static_t unicode, uint8_t *mode) {

    if (!main) return;

    // Skip past NULL.
    if (!unicode.string[0]) {
      main->setting.state.status = F_next;

      return;
    }

    main->setting.state.status = F_none;

    if (unicode.string[0] == f_string_ascii_u_s.string[0] || unicode.string[0] == f_string_ascii_U_s.string[0] || unicode.string[0] == f_string_ascii_plus_s.string[0]) {
      // Do nothing.
    }
    else if (unicode.string[0] == f_string_ascii_0_s.string[0] || unicode.string[0] == f_string_ascii_x_s.string[0] || unicode.string[0] == f_string_ascii_X_s.string[0]) {
      // Do nothing.
    }
    else if (unicode.string[0] == f_string_ascii_space_s.string[0]) {
      main->setting.state.status = F_space;
    }
    else if (macro_f_utf_byte_width_is(*unicode.string)) {
      main->setting.state.status = f_utf_is_whitespace(unicode.string, 4, F_true);

      if (F_status_is_error(main->setting.state.status)) {
        if (F_status_set_fine(main->setting.state.status) == F_complete_not_utf || F_status_set_fine(main->setting.state.status) == F_utf_fragment) {
          main->setting.state.status = F_valid_not;
        }
        else {
          return;
        }
      }

      main->setting.state.status = (main->setting.state.status == F_true) ? F_space : F_valid_not;
    }
    else {
      if (unicode.string[0] < 0x30 || unicode.string[0] > (0x39 && unicode.string[0] < 0x41) || (unicode.string[0] > 0x46 && unicode.string[0] < 0x61) || unicode.string[0] > 0x66) {
        main->setting.state.status = f_utf_is_whitespace(unicode.string, 4, F_true);

        if (F_status_is_error(main->setting.state.status)) {
          if (F_status_set_fine(main->setting.state.status) == F_complete_not_utf || F_status_set_fine(main->setting.state.status) == F_utf_fragment) {
            main->setting.state.status = F_valid_not;
          }
          else {
            return;
          }
        }

        main->setting.state.status = (main->setting.state.status == F_true) ? F_space : F_none;
      }
    }

    if (main->setting.state.status == F_valid_not) {
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
        if (main->setting.state.status == F_space) {
          *mode = utf8_codepoint_mode_bad_end_e;
        }
      }
      else if (*mode == utf8_codepoint_mode_ready_e) {
        if (main->setting.state.status == F_space) {
          main->setting.state.status = F_next;
        }
        else if (unicode.string[0] == f_string_ascii_u_s.string[0] || unicode.string[0] == f_string_ascii_U_s.string[0]) {
          *mode = utf8_codepoint_mode_begin_e;
          main->setting.text.used = 0;
        }
        else if (unicode.string[0] == f_string_ascii_0_s.string[0]) {
          *mode = utf8_codepoint_mode_raw_begin_e;
          main->setting.text.used = 0;
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
        if (main->setting.state.status == F_space) {
          *mode = utf8_codepoint_mode_raw_end_e;
        }
      }
      else if (*mode == utf8_codepoint_mode_number_e) {
        if (main->setting.state.status == F_space) {
          *mode = utf8_codepoint_mode_end_e;
        }
      }
    }
  }
#endif // _di_utf8_detect_codepoint_

#ifndef _di_utf8_process_file_codepoint_
  void utf8_process_file_codepoint(utf8_main_t * const main, const f_file_t file) {

    if (!main) return;

    main->setting.state.status = F_none;

    bool valid = F_true;
    bool next = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_char_t block[5] = { 0, 0, 0, 0, 0 };
    f_string_static_t sequence = macro_f_string_static_t_initialize(block, 0, 0);

    do {
      main->setting.state.status = f_file_stream_read_block(file, &main->setting.buffer);

      if (main->setting.state.status == F_none_eof && !main->setting.buffer.used) {

        // Handle complete character, which must be explicitly set to end in this situation.
        if (mode_codepoint == utf8_codepoint_mode_number_e || mode_codepoint == utf8_codepoint_mode_raw_number_e) {
          if (mode_codepoint == utf8_codepoint_mode_number_e) {
            mode_codepoint = utf8_codepoint_mode_end_e;

            utf8_convert_codepoint(main, sequence, &mode_codepoint);
          }
          else if (mode_codepoint == utf8_codepoint_mode_raw_number_e) {
            mode_codepoint = utf8_codepoint_mode_raw_end_e;

            utf8_convert_raw(main, sequence, &mode_codepoint);

            // Raw mode represents an invalid Unicode sequence.
            valid = F_false;
          }

          j = 0;
          next = F_true;
          main->setting.state.status = F_none_eof;
          mode_codepoint = utf8_codepoint_mode_ready_e;
        }

        break;
      }

      for (i = 0; F_status_is_error_not(main->setting.state.status) && i < main->setting.buffer.used; ) {

        if (!((++main->program.signal_check) % utf8_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

            main->setting.state.status = F_status_set_error(F_interrupt);

            break;
          }

          main->program.signal_check = 0;
        }

        main->setting.state.status = F_none;

        // Get the current width only when processing a new block.
        if (next) {
          sequence.used = macro_f_utf_byte_width(main->setting.buffer.string[i]);
          next = F_false;
        }

        for (; j < sequence.used && i < main->setting.buffer.used; ++j, ++i) {
          sequence.string[j] = main->setting.buffer.string[i];
        } // for

        if (j >= sequence.used) {
          if (main->setting.mode & utf8_mode_from_bytesequence_e) {
            utf8_convert_bytesequence(main, sequence);
          }
          else {
            utf8_detect_codepoint(main, sequence, &mode_codepoint);

            if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_next) {
              if (mode_codepoint == utf8_codepoint_mode_raw_begin_e || mode_codepoint == utf8_codepoint_mode_raw_number_e || mode_codepoint == utf8_codepoint_mode_raw_end_e) {
                utf8_convert_raw(main, sequence, &mode_codepoint);

                // Raw mode represents an invalid Unicode sequence.
                valid = F_false;
              }
              else {
                utf8_convert_codepoint(main, sequence, &mode_codepoint);
              }
            }
          }

          if (main->setting.state.status == F_utf_not) {
            valid = F_false;
          }

          j = 0;
          next = F_true;
        }
      } // for

      main->setting.buffer.used = 0;

    } while (F_status_is_error_not(main->setting.state.status));

    // Handle last (incomplete) character when the buffer ended before the character is supposed to end.
    if (F_status_is_error_not(main->setting.state.status) && next == F_false) {
      sequence.used = j;

      if (main->setting.mode & utf8_mode_from_bytesequence_e) {
        utf8_convert_bytesequence(main, sequence);
      }
      else {
        utf8_detect_codepoint(main, sequence, &mode_codepoint);

        if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_next) {
          if (mode_codepoint == utf8_codepoint_mode_raw_begin_e || mode_codepoint == utf8_codepoint_mode_raw_number_e || mode_codepoint == utf8_codepoint_mode_raw_end_e) {
            utf8_convert_raw(main, sequence, &mode_codepoint);

            // Raw mode represents an invalid Unicode sequence.
            valid = F_false;
          }
          else {
            utf8_convert_codepoint(main, sequence, &mode_codepoint);
          }
        }
      }

      if (main->setting.state.status == F_utf_not) {
        valid = F_false;
      }
    }

    main->setting.buffer.used = 0;

    if (F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = valid;
  }
#endif // _di_utf8_process_file_codepoint_

#ifdef __cplusplus
} // extern "C"
#endif
