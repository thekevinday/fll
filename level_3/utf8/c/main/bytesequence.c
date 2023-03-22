#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_convert_bytesequence_
  void utf8_convert_bytesequence(utf8_main_t * const main, const f_string_static_t sequence) {

    if (!main) return;

    bool valid_not = F_false;

    uint32_t codepoint = 0;

    if (sequence.used) {
      main->setting.state.status = f_utf_unicode_to(sequence.string, sequence.used, &codepoint);
    }
    else {
      main->setting.state.status = F_status_set_error(F_utf_not);
    }

    if (F_status_is_error(main->setting.state.status)) {
      main->setting.state.status = F_status_set_fine(main->setting.state.status);

      if (main->setting.state.status == F_failure || main->setting.state.status == F_utf_not || main->setting.state.status == F_complete_not_utf || main->setting.state.status == F_utf_fragment || main->setting.state.status == F_valid_not) {
        valid_not = F_true;

        utf8_print_data_character_invalid(&main->program.output, sequence);
      }
      else {
        main->setting.state.status = F_status_set_error(main->setting.state.status);

        utf8_print_error_decode(&main->program.error, sequence);

        return;
      }
    }
    else if (!(main->setting.flag & utf8_main_flag_verify_e)) {
      if (main->setting.mode & utf8_mode_to_bytesequence_e) {
        utf8_print_data_bytesequence(&main->program.output, sequence);
      }
      else if (main->setting.mode & utf8_mode_to_codepoint_e) {
        utf8_print_data_codepoint(&main->program.output, codepoint);
      }
      else {
        utf8_print_data_combining_or_width(&main->program.output, sequence);
      }
    }

    if (valid_not || F_status_is_error(main->setting.state.status)) {
      main->setting.state.status = F_utf_not;
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_utf8_convert_bytesequence_

#ifndef _di_utf8_process_file_bytesequence_
  void utf8_process_file_bytesequence(utf8_main_t * const main, const f_file_t file) {

    if (!main) return;

    bool valid = F_true;
    bool next = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready_e;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_char_t block[4] = { 0, 0, 0, 0 };
    f_string_static_t sequence = macro_f_string_static_t_initialize(block, 0, 4);

    do {
      main->setting.state.status = f_file_stream_read_block(file, &main->setting.buffer);

      if (main->setting.state.status == F_none_eof && !main->setting.buffer.used) break;

      for (i = 0; F_status_is_error_not(main->setting.state.status) && i < main->setting.buffer.used; ) {

        if (!((++main->program.signal_check) % utf8_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            fll_program_print_signal_received(main->program.warning, main->program.signal_received);

            main->setting.state.status = F_interrupt;

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

        if (j == sequence.used) {
          if (main->setting.mode & utf8_mode_from_bytesequence_e) {
            utf8_convert_bytesequence(main, sequence);
          }
          else {
            utf8_detect_codepoint(main, sequence, &mode_codepoint);

            if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_next) {
              utf8_convert_codepoint(main, sequence, &mode_codepoint);
            }
          }

          if (main->setting.state.status == F_utf_not) {
            valid = F_false;
          }

          j = 0;
          next = F_true;
        }
      } // for

      i = 0;
      main->setting.buffer.used = 0;

    } while (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_interrupt);

    // Handle last (incomplete) sequence when the buffer ended before the sequence is supposed to end.
    if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_interrupt && next == F_false) {
      sequence.used = j;

      if (main->setting.mode & utf8_mode_from_bytesequence_e) {
        utf8_convert_bytesequence(main, sequence);
      }
      else {
        utf8_detect_codepoint(main, sequence, &mode_codepoint);

        if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_next) {
          utf8_convert_codepoint(main, sequence, &mode_codepoint);
        }
      }

      if (main->setting.state.status == F_utf_not) {
        valid = F_false;
      }
    }

    main->setting.buffer.used = 0;

    if (F_status_is_error(main->setting.state.status) || main->setting.state.status == F_interrupt) return;

    main->setting.state.status = valid;
  }
#endif // _di_utf8_process_file_bytesequence_

#ifdef __cplusplus
} // extern "C"
#endif
