#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_main_
  void utf8_main(utf8_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & utf8_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & utf8_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_none;

    if (main->setting.flag & (utf8_main_flag_help_e | utf8_main_flag_version_e | utf8_main_flag_copyright_e)) {
      if (main->setting.flag & utf8_main_flag_help_e) {
        utf8_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & utf8_main_flag_version_e) {
        fll_program_print_version(&main->program.message, utf8_program_version_s);
      }
      else if (main->setting.flag & utf8_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & utf8_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    f_status_t valid = F_true;

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      const f_file_t file = macro_f_file_t_initialize(F_type_input_d, F_type_descriptor_input_d, F_file_flag_read_only_d, 32768, F_file_default_write_size_d);

      utf8_print_data_section_header_pipe(&main->program.output);

      if (main->setting.mode & utf8_mode_from_bytesequence_e) {
        utf8_process_file_bytesequence(main, file);
      }
      else {
        utf8_process_file_codepoint(main, file);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        if (main->setting.mode & utf8_mode_to_bytesequence_e) {
          if (main->setting.flag & utf8_main_flag_header_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          }
          else if ((main->setting.flag & (utf8_main_flag_separate_e | utf8_main_flag_file_from_e)) || main->setting.remaining.used) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          }
        }
      }

      if (F_status_is_error(main->setting.state.status) && F_status_set_fine(main->setting.state.status) != F_utf_fragment && F_status_set_fine(main->setting.state.status) != F_complete_not_utf) {
        utf8_print_error_file(&main->program.error, main->setting.mode & utf8_mode_from_bytesequence_e ? macro_utf8_f(utf8_process_file_bytesequence) : macro_utf8_f(utf8_process_file_codepoint), f_string_empty_s, f_file_operation_process_s, fll_error_file_type_pipe_e);
      }
    }

    // Process "from" files.
    if (F_status_is_error_not(main->setting.state.status) && (main->setting.flag & utf8_main_flag_file_from_e)) {
      f_file_t file = macro_f_file_t_initialize(0, -1, F_file_flag_read_only_d, 32768, F_file_default_write_size_d);

      for (f_array_length_t i = 0; i < main->setting.path_files_from.used && F_status_is_error_not(main->setting.state.status); ++i) {

        if (!((++main->program.signal_check) % utf8_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            main->setting.state.status = F_status_set_error(F_interrupt);

            break;
          }

          main->program.signal_check = 0;
        }

        utf8_print_data_section_header_file(&main->program.output, main->setting.path_files_from.array[i], i);

        main->setting.state.status = f_file_stream_open(main->setting.path_files_from.array[i], f_string_empty_s, &file);

        if (F_status_is_error(main->setting.state.status)) {
          utf8_print_error_file(&main->program.error, macro_utf8_f(f_file_stream_open), main->setting.path_files_from.array[i], f_file_operation_open_s, fll_error_file_type_file_e);

          break;
        }

        if (main->setting.mode & utf8_mode_from_bytesequence_e) {
          utf8_process_file_bytesequence(main, file);
        }
        else {
          utf8_process_file_codepoint(main, file);
        }

        f_file_stream_flush(file);
        f_file_stream_close(&file);

        if (main->setting.flag & utf8_main_flag_verify_e) {
          if (main->setting.state.status == F_false) {
            valid = F_false;
          }
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          if (main->setting.mode & utf8_mode_to_bytesequence_e) {
            if (main->setting.flag & utf8_main_flag_header_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
            }
            else if ((main->setting.flag & utf8_main_flag_separate_e) && (main->setting.remaining.used || main->setting.path_files_from.used)) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
            }
          }
          else {
            if (!(main->setting.flag & (utf8_main_flag_file_to_e | utf8_main_flag_header_e | utf8_main_flag_verify_e | utf8_main_flag_separate_e))) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
            }
          }
        }

        if (F_status_is_error(main->setting.state.status) && F_status_set_fine(main->setting.state.status) != F_utf_fragment && F_status_set_fine(main->setting.state.status) != F_complete_not_utf) {
          utf8_print_error_file(
            &main->program.error,
            (main->setting.mode & utf8_mode_from_bytesequence_e)
              ? macro_utf8_f(utf8_process_file_bytesequence)
              : macro_utf8_f(utf8_process_file_codepoint),
            main->setting.path_files_from.array[i],
            f_file_operation_process_s,
            fll_error_file_type_file_e
          );

          break;
        }
      } // for
    }

    // Process remaining parameters.
    if (F_status_is_error_not(main->setting.state.status) && main->setting.remaining.used) {
      for (f_array_length_t i = 0; F_status_is_error_not(main->setting.state.status) && i < main->setting.remaining.used; ++i) {

        if (!((++main->program.signal_check) % utf8_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            main->setting.state.status = F_status_set_error(F_interrupt);

            break;
          }

          main->program.signal_check = 0;
        }

        utf8_print_data_section_header_parameter(&main->program.output, i);

        utf8_process_text(main, main->program.parameters.arguments.array[main->program.parameters.remaining.array[i]]);

        if (main->setting.flag & utf8_main_flag_verify_e) {
          if (main->setting.state.status == F_false) {
            valid = F_false;
          }
        }
      } // for
    }

    if ((main->setting.flag & utf8_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);

      // The last line for data is not printed under certain circumstances, but when last line is printed to screen, print an extra last line.
      if (F_status_is_error_not(main->setting.state.status) && F_status_set_fine(main->setting.state.status) != F_interrupt) {
        if (!(main->setting.flag & (utf8_main_flag_file_to_e | utf8_main_flag_header_e | utf8_main_flag_separate_e))) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }
      }
    }

    if (F_status_set_fine(main->setting.state.status) == F_interrupt) return;
    if (F_status_is_error(main->setting.state.status)) return;

    if (main->setting.flag & utf8_main_flag_verify_e) {
      main->setting.state.status = valid;
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_utf8_main_

#ifdef __cplusplus
} // extern "C"
#endif
