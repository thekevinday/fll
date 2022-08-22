#include "iki_read.h"
#include "private-common.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_main_
  f_status_t iki_read_main(fll_program_data_t * const main, iki_read_setting_t * const setting) {

    f_status_t status = F_none;

    // Load parameters.
    status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { iki_read_parameter_no_color_e, iki_read_parameter_light_e, iki_read_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", F_true);

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { iki_read_parameter_verbosity_quiet_e, iki_read_parameter_verbosity_error_e, iki_read_parameter_verbosity_verbose_e, iki_read_parameter_verbosity_debug_e, iki_read_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", F_true);

          return;
        }
      }
    }

    iki_read_data_t data = iki_read_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[iki_read_parameter_help_e].result == f_console_result_found_e) {
      iki_read_print_help(setting, main->message);

      iki_read_data_delete(&data);

      return F_none;
    }

    if (main->parameters.array[iki_read_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->message, iki_read_program_version_s);

      iki_read_data_delete(&data);

      return F_none;
    }

    if (main->parameters.remaining.used > 0 || (main->pipe & fll_program_data_pipe_input_e)) {
      if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_at_s, main->error.notable);
          fl_print_format("%[' requires a positive number.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[iki_read_parameter_at_e].values.array[main->parameters.array[iki_read_parameter_at_e].values.used - 1];

        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &number);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_unsigned_detect", F_true, iki_read_long_at_s, data.argv[index]);

          status = F_status_set_error(F_parameter);
        }

        data.at = number;

        if (main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_at_s, iki_read_long_whole_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters.array[iki_read_parameter_line_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_line_s, main->error.notable);
          fl_print_format("%[' requires a positive number.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[iki_read_parameter_line_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[iki_read_parameter_line_e].values.array[main->parameters.array[iki_read_parameter_line_e].values.used - 1];

        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], &number);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_unsigned_detect", F_true, iki_read_long_line_s, data.argv[index]);

          status = F_status_set_error(F_parameter);
        }

        data.line = number;
      }

      if (main->parameters.array[iki_read_parameter_name_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_name_s, main->error.notable);
          fl_print_format("%[' requires a string.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }

      if (main->parameters.array[iki_read_parameter_replace_e].result != f_console_result_none_e) {
        if (main->parameters.array[iki_read_parameter_replace_e].result == f_console_result_found_e || main->parameters.array[iki_read_parameter_replace_e].values.used % 2 != 0) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_replace_s, main->error.notable);
            fl_print_format("%[' requires 2 strings.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_replace_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters.array[iki_read_parameter_substitute_e].result != f_console_result_none_e) {
        if (main->parameters.array[iki_read_parameter_substitute_e].result == f_console_result_found_e || main->parameters.array[iki_read_parameter_substitute_e].values.used % 3 != 0) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_substitute_s, main->error.notable);
            fl_print_format("%[' requires 3 strings.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_substitute_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters.array[iki_read_parameter_literal_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_read_parameter_object_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_literal_s, iki_read_long_object_s);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_content_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_literal_s, iki_read_long_content_s);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_literal_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }

        data.mode = iki_read_mode_literal_e;
      }
      else if (main->parameters.array[iki_read_parameter_object_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_read_parameter_content_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_object_s, iki_read_long_content_s);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_object_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }

        data.mode = iki_read_mode_object_e;
      }
      else if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
        data.mode = iki_read_mode_total_e;
      }
      else {

        // This is the default behavior, so there is no reason to check for the -c/--content parameter.
        data.mode = iki_read_mode_content_e;
      }

      if (main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_whole_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error(status)) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
        }

        iki_read_data_delete(&data);

        return F_status_set_error(F_parameter);
      }

      if (main->pipe & fll_program_data_pipe_input_e) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;

        status = f_file_read(file, &data.buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read", F_true, f_string_ascii_minus_s, f_file_operation_process_s, fll_error_file_type_file_e);
        }
        else {
          status = iki_read_process_buffer(&data);
        }

        // Clear buffers before continuing.
        f_string_dynamic_resize(0, &data.buffer);
      }

      if (F_status_is_fine(status) && main->parameters.remaining.used > 0) {
        f_file_t file = f_file_t_initialize;
        off_t size_block = 0;
        off_t size_file = 0;
        off_t size_read = 0;

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % iki_read_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          file.stream = 0;
          file.id = -1;

          status = f_file_stream_open(data.argv[main->parameters.remaining.array[i]], f_string_empty_s, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);

            break;
          }

          size_file = 0;

          status = f_file_size_by_id(file.id, &size_file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_size_by_id", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);

            f_file_stream_flush(file);
            f_file_stream_close(&file);

            break;
          }

          // Skip past empty files.
          if (!size_file) {
            f_file_stream_flush(file);
            f_file_stream_close(&file);

            continue;
          }

          // Enforce a max block read size to allow for interrupts to be processed beteween blocks.
          if (size_file > iki_read_block_max) {
            file.size_read = iki_read_block_read_large;
            size_block = iki_read_block_max;
          }
          else {
            file.size_read = iki_read_block_read_small;
            size_block = size_file;
          }

          // Pre-allocate entire file buffer plus space for the terminating NULL.
          f_string_dynamic_increase_by(size_file + 1, &data.buffer);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);

            f_file_stream_flush(file);
            f_file_stream_close(&file);

            break;
          }

          for (size_read = 0; size_read < size_file; size_read += size_block) {

            // The signal check is always performed on each pass.
            if (size_file > iki_read_block_max && fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              status = F_status_set_error(F_interrupt);

              break;
            }

            status = f_file_stream_read_until(file, size_block, &data.buffer);
            if (F_status_is_error(status)) break;
          } // for

          f_file_stream_flush(file);
          f_file_stream_close(&file);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) != F_interrupt) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read_until", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);
            }

            break;
          }

          status = iki_read_process_buffer(&data);
          if (F_status_is_error(status)) break;

          // Clear buffers before repeating the loop.
          f_string_dynamic_resize(0, &data.buffer);
        } // for
      }
    }
    else {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        fll_print_format("%r%[%QYou failed to specify one or more files.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
      }

      status = F_status_set_error(F_parameter);
    }

    // Ensure a new line is always put at the end of the program execution, unless in quiet mode.
    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        fflush(main->output.to.stream);
      }

      fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
    }

    iki_read_data_delete(&data);

    return status;
  }
#endif // _di_iki_read_main_

#ifdef __cplusplus
} // extern "C"
#endif
