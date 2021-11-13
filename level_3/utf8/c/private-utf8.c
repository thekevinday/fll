#include "utf8.h"
#include "private-common.h"
#include "private-utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_convert_binary_
  f_status_t utf8_convert_binary(utf8_main_t * const main, const f_string_static_t character) {

    f_status_t status = F_none;

    f_string_t prepend = "";
    f_string_t append = "";
    f_color_set_t error = f_color_set_t_initialize;

    if (main->mode & utf8_mode_to_codepoint_d) {
      if (main->parameters[utf8_parameter_verify].result == f_console_result_found) {
        if (main->parameters[utf8_parameter_headers].result == f_console_result_found) {
          prepend = "  ";
        }
        else {
          prepend = " ";
        }

        append = f_string_eol_s;
      }
      else {
        error = main->output.set->error;
        prepend = " ";
      }
    }

    uint32_t codepoint = 0;

    if (character.used) {
      status = f_utf_unicode_to(character.string, character.used, &codepoint);
    }
    else {
      status = F_status_set_error(F_utf);
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_failure || F_status_set_fine(status) == F_utf) {
        if (main->parameters[utf8_parameter_strip_invalid].result == f_console_result_none) {
          if (main->mode & utf8_mode_to_binary_d) {
            fl_print_format("%s%[", main->output.to.stream, prepend, error);

            for (f_array_length_t i = 0; i < character.used; ++i) {
              f_print_character(character.string[i], main->output.to.stream);
            } // for

            fl_print_format("%s%[", main->output.to.stream, error, append);
          }
          else {
            fl_print_format("%s%[0x", main->output.to.stream, prepend, error);

            for (uint8_t i = 0; i < character.used; ++i) {
              fl_print_format("%02_uii", main->output.to.stream, (uint8_t) character.string[i]);
            } // for

            fl_print_format("%]%s", main->output.to.stream, error, append);
          }
        }
      }
      else {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          fl_print_format("%c%[%SFailed to decode character '%]", main->error.to.stream, f_string_eol_s[0], main->context.set.error, main->context.set.error);
          fl_print_format("%[%r%]", main->error.to.stream, main->context.set.notable, character, main->context.set.notable);
          fl_print_format("%[', error status code%] ", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);
          fl_print_format("%[%S%]", main->error.to.stream, main->context.set.notable, F_status_set_fine(status), main->context.set.notable);
          fl_print_format("%[.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);
        }

        return status;
      }
    }
    else if (main->parameters[utf8_parameter_verify].result == f_console_result_none) {
      if (main->mode & utf8_mode_to_binary_d) {
        f_print_terminated(prepend, main->output.to.stream);

        for (f_array_length_t i = 0; i < character.used; ++i) {
          f_print_character(character.string[i], main->output.to.stream);
        } // for

        f_print_terminated(append, main->output.to.stream);
      }
      else {
        if (character.used < 4) {
          fl_print_format("%sU+%04_U%s", main->output.to.stream, prepend, codepoint, append);
        }
        else {
          fl_print_format("%sU+%06_U%s", main->output.to.stream, prepend, codepoint, append);
        }
      }
    }

    if (F_status_is_error(status)) {
      return F_utf;
    }

    return F_none;
  }
#endif // _di_utf8_convert_binary_

#ifndef _di_utf8_convert_codepoint_
  f_status_t utf8_convert_codepoint(utf8_main_t * const main, const f_string_static_t character, uint8_t *mode) {

    f_status_t status = F_none;

    // @todo


    return F_none;
  }
#endif // _di_utf8_convert_codepoint_

#ifndef _di_utf8_process_file_binary_
  f_status_t utf8_process_file_binary(utf8_main_t * const main, const f_file_t file) {

    f_status_t status = F_none;
    bool valid = F_true;
    bool next = F_true;
    uint8_t mode = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    char block_character[4] = { 0, 0, 0, 0 };
    f_string_static_t character = macro_f_string_static_t_initialize(block_character, 4);

    do {
      status = f_file_read_block(file, &main->buffer);

      if (status == F_none_eof && !main->buffer.used) break;

      for (i = 0; F_status_is_fine(status) && i < main->buffer.used; ) {

        status = utf8_signal_received(main);

        if (status) {
          utf8_print_signal_received(main, status);

          status = F_status_set_error(F_signal);
          break;
        }
        else {
          status = F_none;
        }

        // Get the current width only when processing a new block.
        if (next) {
          character.used = macro_f_utf_byte_width(main->buffer.string[i]);
          next = F_false;
        }

        for (; j < character.used && i < main->buffer.used; ++j, ++i) {
          character.string[j] = main->buffer.string[i];
        } // for

        if (j == character.used) {
          if (main->mode & utf8_mode_from_binary_d) {
            status = utf8_convert_binary(main, character);
          }
          else {
            // @todo: check character and determine status.
            /*private_utf8_codepoint_modes_ready = 1,
            private_utf8_codepoint_modes_begin,
            private_utf8_codepoint_modes_number,
            private_utf8_codepoint_modes_end,
            private_utf8_codepoint_modes_bad,*/
            status = utf8_convert_codepoint(main, character, &mode);
          }

          if (status == F_utf) {
            valid = F_false;
          }

          j = 0;
          next = F_true;
        }
      } // for

      i = 0;
      main->buffer.used = 0;

    } while (F_status_is_fine(status) && status != F_signal);

    // Handle last (incomplete) character when the buffer ended before the character is supposed to end.
    if (status != F_signal && next == F_false) {
      character.used = j;

      if (main->mode & utf8_mode_from_binary_d) {
        status = utf8_convert_binary(main, character);
      }
      else {
        // @todo: check character and determine status.
        /*private_utf8_codepoint_modes_ready = 1,
        private_utf8_codepoint_modes_begin,
        private_utf8_codepoint_modes_number,
        private_utf8_codepoint_modes_end,
        private_utf8_codepoint_modes_bad,*/
        status = utf8_convert_codepoint(main, character, &mode);
      }

      if (status == F_utf) {
        valid = F_false;
      }
    }

    main->buffer.used = 0;

    if (F_status_is_error(status)) {
      return status;
    }

    return valid;
  }
#endif // _di_utf8_process_file_binary_

#ifndef _di_utf8_process_file_codepoint_
  f_status_t utf8_process_file_codepoint(utf8_main_t * const main, const f_file_t file) {

    f_status_t status = F_none;
    bool valid = F_true;
    bool next = F_true;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    char block[4] = { 0, 0, 0, 0 };
    f_string_static_t character = macro_f_string_static_t_initialize(block, 4);

    do {
      status = f_file_read_block(file, &main->buffer);

      if (status == F_none_eof && !main->buffer.used) break;

      for (i = 0; F_status_is_fine(status) && i < main->buffer.used; ) {

        status = utf8_signal_received(main);

        if (status) {
          utf8_print_signal_received(main, status);

          status = F_status_set_error(F_signal);
          break;
        }
        else {
          status = F_none;
        }

        // Get the current width only when processing a new block.
        if (next) {
          character.used = macro_f_utf_byte_width(main->buffer.string[i]);
          next = F_false;
        }

        for (; j < character.used && i < main->buffer.used; ++j, ++i) {
          character.string[j] = main->buffer.string[i];
        } // for

        if (j == character.used) {
          status = utf8_convert_binary(main, character);

          if (status == F_utf) {
            valid = F_false;
          }

          j = 0;
          next = F_true;
        }
      } // for

      i = 0;
      main->buffer.used = 0;

    } while (F_status_is_fine(status) && status != F_signal);

    // Handle last (incomplete) character when the buffer ended before the character is supposed to end.
    if (status != F_signal && next == F_false) {
      character.used = j;

      status = utf8_convert_binary(main, character);

      if (status == F_utf) {
        valid = F_false;
      }
    }

    main->buffer.used = 0;

    if (F_status_is_error(status)) {
      return status;
    }

    return valid;
  }
#endif // _di_utf8_process_file_codepoint_

#ifndef _di_utf8_process_text_
  f_status_t utf8_process_text(utf8_main_t * const main, const f_string_t text) {

    if (!text) {
      return F_true;
    }

    f_status_t status = F_none;
    bool valid = F_true;
    uint8_t mode = 0;

    f_string_static_t character = macro_f_string_static_t_initialize(text, 4);

    flockfile(main->output.to.stream);

    while (*character.string && F_status_is_error_not(status)) {

      status = utf8_signal_received(main);

      if (status) {
        utf8_print_signal_received(main, status);

        status = F_status_set_error(F_signal);
        break;
      }
      else {
        status = F_none;
      }

      character.used = macro_f_utf_byte_width(*character.string);

      // Re-adjust used if buffer ended before the character is supposed to end.
      if (character.string[0]) {
        if (character.used > 1) {
          if (character.string[1]) {
            if (character.used > 2) {
              if (character.string[2]) {
                if (character.used > 3) {
                  if (character.string[3]) {
                    character.used = 4;
                  }
                  else {
                    character.used = 3;
                  }
                }
              }
              else {
                character.used = 2;
              }
            }
          }
          else {
            character.used = 1;
          }
        }
      }
      else {
        character.used = 0;
      }

      if (main->mode & utf8_mode_from_binary_d) {
        status = utf8_convert_binary(main, character);
      }
      else {
        // @todo: check character and determine status.
        /*private_utf8_codepoint_modes_ready = 1,
        private_utf8_codepoint_modes_begin,
        private_utf8_codepoint_modes_number,
        private_utf8_codepoint_modes_end,
        private_utf8_codepoint_modes_bad,*/
        status = utf8_convert_codepoint(main, character, &mode);
      }

      character.string += character.used;

      if (status == F_utf) {
        valid = F_false;
      }
    } // while

    if (F_status_is_error(status)) {
      funlockfile(main->output.to.stream);

      return status;
    }

    if (main->parameters[utf8_parameter_verify].result == f_console_result_none) {
      f_print_character(f_string_eol_s[0], main->output.to.stream);
    }

    funlockfile(main->output.to.stream);

    return valid;
  }
#endif // _di_utf8_process_text_

#ifdef __cplusplus
} // extern "C"
#endif
