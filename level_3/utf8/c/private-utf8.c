#include "utf8.h"
#include "private-common.h"
#include "private-print.h"
#include "private-utf8.h"
#include "private-utf8_binary.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_data_delete_
  void utf8_data_delete(utf8_data_t *data) {

    if (data->file.stream != data->main->output.to.stream) {
      f_file_stream_close(F_true, &data->file);
    }

    macro_f_string_dynamic_t_delete_simple(data->buffer);
    macro_f_string_dynamic_t_delete_simple(data->text);
  }
#endif // _di_utf8_data_delete_

#ifndef _di_utf8_process_text_
  f_status_t utf8_process_text(utf8_data_t * const data, const f_string_t text) {

    if (!text) {
      return F_true;
    }

    f_status_t status = F_none;
    bool valid = F_true;
    uint8_t mode_codepoint = utf8_codepoint_mode_ready;

    f_string_static_t character = macro_f_string_static_t_initialize(text, 4);

    flockfile(data->file.stream);

    for (uint16_t signal_check = 0; *character.string && F_status_is_error_not(status); ) {

      if (!((++signal_check) % utf8_signal_check_d)) {
        if (utf8_signal_received(data)) {
          utf8_print_signal_received(data, status);

          status = F_status_set_error(F_signal);
          break;
        }
      }

      status = F_none;
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

      if (data->mode & utf8_mode_from_binary_d) {
        status = utf8_convert_binary(data, character);
      }
      else {
        status = utf8_detect_codepoint(data, character, &mode_codepoint);

        if (F_status_is_fine(status) && status != F_next) {
          status = utf8_convert_codepoint(data, character, &mode_codepoint);
        }
      }

      character.string += character.used;

      if (status == F_utf) {
        valid = F_false;
      }
    } // for

    if (F_status_is_error_not(status) && !(data->mode & utf8_mode_from_binary_d)) {
      if (mode_codepoint != utf8_codepoint_mode_ready && mode_codepoint != utf8_codepoint_mode_end && mode_codepoint != utf8_codepoint_mode_bad_end) {
        if (mode_codepoint == utf8_codepoint_mode_number) {
          mode_codepoint = utf8_codepoint_mode_end;
        }
        else {
          mode_codepoint = utf8_codepoint_mode_bad_end;
          valid = F_false;
        }

        character.used = 0;

        status = utf8_convert_codepoint(data, character, &mode_codepoint);
      }
    }

    if (F_status_is_error(status)) {
      funlockfile(data->file.stream);

      return status;
    }

    if (data->main->parameters[utf8_parameter_verify].result == f_console_result_none) {

      // When headers are printed, they are printed with a newline so only print this newline when separate is used without headers being printed.
      if (data->main->parameters[utf8_parameter_headers].result == f_console_result_none && data->main->parameters[utf8_parameter_separate].result == f_console_result_found) {
        f_print_terminated(f_string_eol_s, data->file.stream);
      }
    }

    funlockfile(data->file.stream);

    return valid;
  }
#endif // _di_utf8_process_text_

#ifdef __cplusplus
} // extern "C"
#endif
