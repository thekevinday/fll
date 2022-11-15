#include "iki_read.h"
#include "private-common.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_main_
  void iki_read_main(fll_program_data_t * const main, iki_read_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->status)) return;

    setting->status = F_none;

    if (setting->flag & iki_read_main_flag_help_e) {
      iki_read_print_help(setting, main->message);

      return;
    }

    if (setting->flag & iki_read_main_flag_version_e) {
      fll_program_print_version(main->message, iki_read_program_version_s);

      return;
    }

    if (main->pipe & fll_program_data_pipe_input_e) {
      f_file_t file = f_file_t_initialize;

      file.id = F_type_descriptor_input_d;

      setting->buffer.used = 0;

      setting->status = f_file_read(file, &setting->buffer);

      if (F_status_is_error(setting->status)) {
        iki_read_print_error_file(setting, main->error, "f_file_read", f_string_ascii_minus_s, f_file_operation_process_s, fll_error_file_type_file_e);
      }
      else {
        iki_read_process_buffer(main, setting);
        if (F_status_is_error(setting->status)) return;
      }
    }

    if (setting->files.used) {
      f_file_t file = f_file_t_initialize;
      off_t size_block = 0;
      off_t size_file = 0;
      off_t size_read = 0;

      for (f_array_length_t i = 0; i < setting->files.used; ++i) {

        if (!((++main->signal_check) % iki_read_signal_check_d)) {
          if (fll_program_standard_signal_received(main)) {
            fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

            setting->status = F_status_set_error(F_interrupt);

            return;
          }

          main->signal_check = 0;
        }

        file.stream = 0;
        file.id = -1;

        setting->status = f_file_stream_open(setting->files.array[i], f_string_empty_s, &file);

        if (F_status_is_error(setting->status)) {
          iki_read_print_error_file(setting, main->error, "f_file_stream_open", setting->files.array[i], f_file_operation_process_s, fll_error_file_type_file_e);

          return;
        }

        setting->status = f_file_descriptor(&file);

        if (F_status_is_error(setting->status)) {
          iki_read_print_error_file(setting, main->error, "f_file_descriptor", setting->files.array[i], f_file_operation_process_s, fll_error_file_type_file_e);

          return;
        }

        size_file = 0;

        setting->status = f_file_size_by_id(file, &size_file);

        if (F_status_is_error(setting->status)) {
          iki_read_print_error_file(setting, main->error, "f_file_size_by_id", setting->files.array[i], f_file_operation_analyze_s, fll_error_file_type_file_e);

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
        setting->status = f_string_dynamic_increase_by(size_file + 1, &setting->buffer);

        if (F_status_is_error(setting->status)) {
          iki_read_print_error_file(setting, main->error, "f_string_dynamic_increase_by", setting->files.array[i], f_file_operation_process_s, fll_error_file_type_file_e);

          break;
        }

        for (size_read = 0; size_read < size_file; size_read += size_block) {

          // The signal check is always performed on each pass.
          if (size_file > iki_read_block_max && fll_program_standard_signal_received(main)) {
            fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

            setting->status = F_status_set_error(F_interrupt);

            break;
          }

          setting->status = f_file_stream_read_until(file, size_block, &setting->buffer);
          if (F_status_is_error(setting->status)) break;
        } // for

        if (F_status_is_error(setting->status)) {
          if (F_status_set_fine(setting->status) != F_interrupt) {
            iki_read_print_error_file(setting, main->error, "f_file_stream_read_until", setting->files.array[i], f_file_operation_process_s, fll_error_file_type_file_e);
          }

          break;
        }

        f_file_stream_flush(file);
        f_file_stream_close(&file);

        iki_read_process_buffer(main, setting);
        if (F_status_is_error(setting->status)) return;

        setting->buffer.used = 0;
      } // for

      if (F_status_is_error(setting->status)) {
        f_file_stream_flush(file);
        f_file_stream_close(&file);

        return;
      }
    }

    // Ensure a new line is always put at the end of the program execution, unless in quiet mode.
    iki_read_print_line_last_locked(setting, main->message);
  }
#endif // _di_iki_read_main_

#ifdef __cplusplus
} // extern "C"
#endif
