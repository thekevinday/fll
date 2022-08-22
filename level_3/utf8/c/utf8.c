#include "utf8.h"
#include "private-common.h"
#include "private-utf8.h"
#include "private-utf8_bytesequence.h"
#include "private-utf8_codepoint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_main_
  void utf8_main(fll_program_data_t * const main, utf8_setting_t * const setting) {

    if (!main || !setting) {
      utf8_print_line_first(setting, main->error, F_true);
      fll_error_print(main->error, F_parameter, "utf8_main", F_true);
      utf8_print_line_last(setting, main->error, F_true);

      setting->status = F_status_set_error(F_parameter);

      return;
    }

    if (F_status_is_error(setting->status)) return;

    setting->status = F_none;

    if (setting->flag & utf8_main_flag_help_e) {
      utf8_print_help(setting, main->message);

      return;
    }

    if (setting->flag & utf8_main_flag_version_e) {
      fll_program_print_version(main->message, utf8_program_version_s);

      return;
    }

    f_status_t valid = F_true;

    if (main->pipe & fll_program_data_pipe_input_e) {
      const f_file_t file = macro_f_file_t_initialize(F_type_input_d, F_type_descriptor_input_d, F_file_flag_read_only_d, 32768, F_file_default_write_size_d);

      utf8_print_section_header_pipe(main, setting);

      if (setting->mode & utf8_mode_from_bytesequence_e) {
        setting->status = utf8_process_file_bytesequence(main, setting, file);
      }
      else {
        setting->status = utf8_process_file_codepoint(main, setting, file);
      }

      if (F_status_is_error_not(setting->status)) {
        if (setting->mode & utf8_mode_to_bytesequence_e) {
          if (setting->flag & utf8_main_flag_header_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
          }
          else if ((setting->flag & utf8_main_flag_separate_e) && ((setting->flag & utf8_main_flag_file_from_e) || main->parameters.remaining.used)) {
            fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
          }
        }
      }

      if (F_status_is_error(setting->status) && F_status_set_fine(setting->status) != F_utf_fragment && F_status_set_fine(setting->status) != F_complete_not_utf) {
        fll_error_file_print(main->error, F_status_set_fine(setting->status), setting->mode & utf8_mode_from_bytesequence_e ? "utf8_process_file_bytesequence" : "utf8_process_file_codepoint", F_true, f_string_empty_s, f_file_operation_process_s, fll_error_file_type_pipe_e);
      }
    }

    if (F_status_is_error_not(setting->status) && setting->status != F_interrupt && (setting->flag & utf8_main_flag_file_from_e)) {
      f_array_length_t i = 0;
      f_array_length_t index = 0;

      f_file_t file = macro_f_file_t_initialize(0, -1, F_file_flag_read_only_d, 32768, F_file_default_write_size_d);

      f_string_static_t * const args = main->parameters.arguments.array;

      for (; i < main->parameters.array[utf8_parameter_from_file_e].values.used && setting->status != F_interrupt; ++i) {

        if (!((++main->signal_check) % utf8_signal_check_d)) {
          if (fll_program_standard_signal_received(main)) {
            setting->status = F_status_set_error(F_interrupt);

            break;
          }

          main->signal_check = 0;
        }

        index = main->parameters.array[utf8_parameter_from_file_e].values.array[i];

        utf8_print_section_header_file(main, setting, args[index], i);

        setting->status = f_file_stream_open(args[index], f_string_empty_s, &file);

        if (F_status_is_error(setting->status)) {
          fll_error_file_print(main->error, F_status_set_fine(setting->status), "f_file_stream_open", F_true, args[index], f_file_operation_open_s, fll_error_file_type_file_e);

          break;
        }

        if (setting->mode & utf8_mode_from_bytesequence_e) {
          setting->status = utf8_process_file_bytesequence(main, setting, file);
        }
        else {
          setting->status = utf8_process_file_codepoint(main, setting, file);
        }

        f_file_stream_flush(file);
        f_file_stream_close(&file);

        if (setting->flag & utf8_main_flag_verify_e) {
          if (setting->status == F_false) {
            valid = F_false;
          }
        }

        if (F_status_is_error_not(setting->status)) {
          if (setting->mode & utf8_mode_to_bytesequence_e) {
            if (setting->flag & utf8_main_flag_header_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
            }
            else if ((setting->flag & utf8_main_flag_separate_e) && (main->parameters.remaining.used || i + 1 < main->parameters.array[utf8_parameter_from_file_e].values.used)) {
              fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
            }
          }
          else {
            if (!(setting->flag & (utf8_main_flag_file_to_e | utf8_main_flag_header_e | utf8_main_flag_verify_e))) {
              if (!(setting->flag & utf8_main_flag_separate_e)) {
                fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
              }
            }
          }
        }

        if (F_status_is_error(setting->status) && F_status_set_fine(setting->status) != F_utf_fragment && F_status_set_fine(setting->status) != F_complete_not_utf) {
          fll_error_file_print(main->error, F_status_set_fine(setting->status), setting->mode & utf8_mode_from_bytesequence_e ? "utf8_process_file_bytesequence" : "utf8_process_file_codepoint", F_true, args[index], f_file_operation_process_s, fll_error_file_type_file_e);

          break;
        }
      } // for
    }

    if (F_status_is_error_not(setting->status) && setting->status != F_interrupt && main->parameters.remaining.used) {
      for (f_array_length_t i = 0; F_status_is_error_not(setting->status) && i < main->parameters.remaining.used; ++i) {

        if (!((++main->signal_check) % utf8_signal_check_d)) {
          if (fll_program_standard_signal_received(main)) {
            setting->status = F_status_set_error(F_interrupt);

            break;
          }

          main->signal_check = 0;
        }

        utf8_print_section_header_parameter(main, setting, main->parameters.remaining.array[i]);

        setting->status = utf8_process_text(main, setting, main->parameters.arguments.array[main->parameters.remaining.array[i]]);

        if (setting->mode & utf8_mode_to_bytesequence_e) {
          if (setting->flag & utf8_main_flag_header_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
          }
          else if ((setting->flag & utf8_main_flag_separate_e) && i + 1 < main->parameters.remaining.used) {
            fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
          }
        }
        else {
          if (!(setting->flag & (utf8_main_flag_file_to_e | utf8_main_flag_header_e | utf8_main_flag_verify_e))) {
            if (!(setting->flag & utf8_main_flag_separate_e)) {
              fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
            }
          }
        }

        if (setting->flag & utf8_main_flag_verify_e) {
          if (setting->status == F_false) {
            valid = F_false;
          }
        }
      } // for
    }

    if (F_status_is_error(setting->status)) {
      utf8_print_line_last(setting, main->error, F_true);
    }
    else if (setting->status != F_interrupt) {
      utf8_print_line_last(setting, main->message, F_true);
    }

    if (F_status_is_error(setting->status) || setting->status == F_interrupt) return;

    if (setting->flag & utf8_main_flag_verify_e) {
      setting->status = valid;
    }
    else {
      setting->status = F_none;
    }
  }
#endif // _di_utf8_main_

#ifdef __cplusplus
} // extern "C"
#endif
