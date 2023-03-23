#include "iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_main_
  void iki_read_main(iki_read_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & iki_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_none;

    if (main->setting.flag & (iki_read_main_flag_help_e | iki_read_main_flag_version_e | iki_read_main_flag_copyright_e)) {
      if (main->setting.flag & iki_read_main_flag_help_e) {
        iki_read_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & iki_read_main_flag_version_e) {
        fll_program_print_version(&main->program.message, iki_read_program_version_s);
      }
      else if (main->setting.flag & iki_read_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & iki_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      f_file_t file = f_file_t_initialize;

      file.id = F_type_descriptor_input_d;

      main->setting.buffer.used = 0;

      main->setting.state.status = f_file_read(file, &main->setting.buffer);

      if (F_status_is_error(main->setting.state.status)) {
        iki_read_print_error_file(&main->program.error, macro_iki_read_f(f_file_read), f_string_ascii_minus_s, f_file_operation_process_s, fll_error_file_type_file_e);
      }
      else {
        iki_read_process_buffer(main);
      }
    }

    if (F_status_is_error_not(main->setting.state.status) && main->setting.files.used) {
      f_file_t file = f_file_t_initialize;
      off_t size_block = 0;
      off_t size_file = 0;
      off_t size_read = 0;

      for (f_array_length_t i = 0; i < main->setting.files.used; ++i) {

        if (!((++main->program.signal_check) % iki_read_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

            main->setting.state.status = F_status_set_error(F_interrupt);

            break;
          }

          main->program.signal_check = 0;
        }

        file.stream = 0;
        file.id = -1;

        main->setting.state.status = f_file_stream_open(main->setting.files.array[i], f_string_empty_s, &file);

        if (F_status_is_error(main->setting.state.status)) {
          iki_read_print_error_file(&main->program.error, macro_iki_read_f(f_file_stream_open), main->setting.files.array[i], f_file_operation_process_s, fll_error_file_type_file_e);

          break;
        }

        main->setting.state.status = f_file_descriptor(&file);

        if (F_status_is_error(main->setting.state.status)) {
          iki_read_print_error_file(&main->program.error, macro_iki_read_f(f_file_descriptor), main->setting.files.array[i], f_file_operation_process_s, fll_error_file_type_file_e);

          break;
        }

        size_file = 0;

        main->setting.state.status = f_file_size_by_id(file, &size_file);

        if (F_status_is_error(main->setting.state.status)) {
          iki_read_print_error_file(&main->program.error, macro_iki_read_f(f_file_size_by_id), main->setting.files.array[i], f_file_operation_analyze_s, fll_error_file_type_file_e);

          break;
        }

        // Skip past empty files.
        if (!size_file) {
          f_file_stream_flush(file);
          f_file_stream_close(&file);

          continue;
        }

        // Enforce a max block read size to allow for interrupts to be processed between blocks.
        if (size_file > iki_read_block_max) {
          file.size_read = iki_read_block_read_large;
          size_block = iki_read_block_max;
        }
        else {
          file.size_read = iki_read_block_read_small;
          size_block = size_file;
        }

        // Pre-allocate entire file buffer plus space for the terminating NULL.
        main->setting.state.status = f_string_dynamic_increase_by(size_file + 1, &main->setting.buffer);

        if (F_status_is_error(main->setting.state.status)) {
          iki_read_print_error_file(&main->program.error, macro_iki_read_f(f_string_dynamic_increase_by), main->setting.files.array[i], f_file_operation_process_s, fll_error_file_type_file_e);

          break;
        }

        for (size_read = 0; size_read < size_file; size_read += size_block) {

          // The signal check is always performed on each pass.
          if (size_file > iki_read_block_max && fll_program_standard_signal_received(&main->program)) {
            fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

            main->setting.state.status = F_status_set_error(F_interrupt);

            break;
          }

          main->setting.state.status = f_file_stream_read_until(file, size_block, &main->setting.buffer);
          if (F_status_is_error(main->setting.state.status)) break;
        } // for

        if (F_status_is_error(main->setting.state.status)) {
          if (F_status_set_fine(main->setting.state.status) != F_interrupt) {
            iki_read_print_error_file(&main->program.error, macro_iki_read_f(f_file_stream_read_until), main->setting.files.array[i], f_file_operation_process_s, fll_error_file_type_file_e);
          }

          break;
        }

        f_file_stream_flush(file);
        f_file_stream_close(&file);

        iki_read_process_buffer(main);
        if (F_status_is_error(main->setting.state.status)) break;

        main->setting.buffer.used = 0;
      } // for

      if (F_status_is_error(main->setting.state.status)) {
        f_file_stream_flush(file);
        f_file_stream_close(&file);
      }
    }

    if ((main->setting.flag & iki_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_iki_read_main_

#ifdef __cplusplus
} // extern "C"
#endif
