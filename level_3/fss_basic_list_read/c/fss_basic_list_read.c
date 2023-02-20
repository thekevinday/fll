#include "fss_basic_list_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_main_
  f_status_t fss_basic_list_read_main(fll_program_data_t * const main, fss_basic_list_read_setting_t * const setting) {

    f_status_t status = F_none;

    // Load parameters.
    status = f_console_parameter_process(arguments, &main->parameters, 0);
    if (F_status_is_error(status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_basic_list_read_parameter_no_color_e, fss_basic_list_read_parameter_light_e, fss_basic_list_read_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(status)) {
          fss_basic_list_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", fll_error_file_flag_fallback_e);
          fss_basic_list_read_print_line_last_locked(setting, main->error);

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_basic_list_read_parameter_verbosity_quiet_e, fss_basic_list_read_parameter_verbosity_error_e, fss_basic_list_read_parameter_verbosity_verbose_e, fss_basic_list_read_parameter_verbosity_debug_e, fss_basic_list_read_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(status)) {
          fss_basic_list_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", fll_error_file_flag_fallback_e);
          fss_basic_list_read_print_line_last_locked(setting, main->error);

          return;
        }
      }
    }

    if (main->parameters.array[fss_basic_list_read_parameter_help_e].result & f_console_result_found_e) {
      fss_basic_list_read_print_help(setting, main->message);

      return F_none;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_version_e].result & f_console_result_found_e) {
      fll_program_print_version(main->message, (setting->line_first.used ? 0x1 : 0x0) | (setting->line_last.used ? 0x2 : 0x0), fss_basic_list_read_program_version_s);

      return F_none;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_copyright_e].result & f_console_result_found_e) {
      fll_program_print_copyright(main->message, (setting->line_first.used ? 0x1 : 0x0) | (setting->line_last.used ? 0x2 : 0x0));

      return F_none;
    }

    status = F_none;

    // Provide a range designating where within the buffer a particular file exists, using a statically allocated array.
    fss_basic_list_read_file_t files_array[main->parameters.remaining.used + 1];
    fss_basic_list_read_data_t data = fss_basic_list_read_data_t_initialize;

    data.argv = main->parameters.arguments.array;
    data.files.array = files_array;
    data.files.used = 1;
    data.files.size = main->parameters.remaining.used + 1;
    data.files.array[0].name = fss_basic_list_read_pipe_name_s;
    data.files.array[0].range.start = 1;
    data.files.array[0].range.stop = 0;

    if (main->parameters.remaining.used || (main->pipe & fll_program_data_pipe_input_e)) {
      {
        const f_array_length_t parameter_code[] = {
          fss_basic_list_read_parameter_at_e,
          fss_basic_list_read_parameter_depth_e,
          fss_basic_list_read_parameter_line_e,
          fss_basic_list_read_parameter_select_e,
          fss_basic_list_read_parameter_name_e,
          fss_basic_list_read_parameter_delimit_e,
        };

        const f_string_static_t parameter_name[] = {
          fss_basic_list_read_long_at_s,
          fss_basic_list_read_long_depth_s,
          fss_basic_list_read_long_line_s,
          fss_basic_list_read_long_select_s,
          fss_basic_list_read_long_name_s,
          fss_basic_list_read_long_delimit_s,
        };

        const f_string_t message_positive_number = "positive number";
        const f_string_t message_string = "string";
        const f_string_t message_value = "value";

        const f_string_t parameter_message[] = {
          message_positive_number,
          message_positive_number,
          message_positive_number,
          message_positive_number,
          message_string,
          message_value,
        };

        for (f_array_length_t i = 0; i < 6; ++i) {

          if (main->parameters.array[parameter_code[i]].result & f_console_result_found_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, parameter_name[i], main->error.notable);
            fl_print_format("%[' requires a %s.%]%r", main->error.to, main->error.context, parameter_message[i], main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);

            status = F_status_set_error(F_parameter);

            break;
          }
        } // for
      }

      if (F_status_is_error_not(status) && (main->parameters.array[fss_basic_list_read_parameter_columns_e].result & f_console_result_found_e)) {
        const f_array_length_t parameter_code[] = {
          fss_basic_list_read_parameter_depth_e,
          fss_basic_list_read_parameter_line_e,
          fss_basic_list_read_parameter_pipe_e,
          fss_basic_list_read_parameter_select_e,
          fss_basic_list_read_parameter_total_e,
        };

        const f_string_static_t parameter_name[] = {
          fss_basic_list_read_long_depth_s,
          fss_basic_list_read_long_line_s,
          fss_basic_list_read_long_pipe_s,
          fss_basic_list_read_long_select_s,
          fss_basic_list_read_long_total_s,
        };

        const uint8_t parameter_match[] = {
          f_console_result_value_e,
          f_console_result_value_e,
          f_console_result_found_e,
          f_console_result_value_e,
          f_console_result_found_e,
        };

        for (f_array_length_t i = 0; i < 5; ++i) {

          if (main->parameters.array[parameter_code[i]].result == parameter_match[i]) {
            if (main->error.verbosity > f_console_verbosity_quiet_e) {
              fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_basic_list_read_long_columns_s, parameter_name[i]);
            }

            status = F_status_set_error(F_parameter);

            break;
          }
        } // for
      }

      if (F_status_is_error_not(status) && (main->parameters.array[fss_basic_list_read_parameter_pipe_e].result & f_console_result_found_e)) {
        if (main->parameters.array[fss_basic_list_read_parameter_total_e].result & f_console_result_found_e) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_basic_list_read_long_pipe_s, fss_basic_list_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }
        else if (main->parameters.array[fss_basic_list_read_parameter_line_e].result & f_console_result_value_e) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_basic_list_read_long_pipe_s, fss_basic_list_read_long_line_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status) && main->parameters.array[fss_basic_list_read_parameter_delimit_e].result & f_console_result_value_e) {
        f_array_length_t index = 0;
        f_array_length_t length = 0;

        // Set the value to 0 to allow for detecting mode based on what is provided.
        data.delimit_mode = 0;

        for (f_array_length_t i = 0; i < main->parameters.array[fss_basic_list_read_parameter_delimit_e].values.used; ++i) {

          if (!((++main->signal_check) % fss_basic_list_read_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          index = main->parameters.array[fss_basic_list_read_parameter_delimit_e].values.array[i];
          length = data.argv[index].used;

          if (!length) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_list_read_long_delimit_s, main->error.notable);
            fl_print_format("%[' must not be empty.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);

            status = F_status_set_error(F_parameter);

            break;
          }
          else if (fl_string_dynamic_compare_string(fss_basic_list_read_delimit_mode_name_none_s.string, data.argv[index], fss_basic_list_read_delimit_mode_name_none_s.used) == F_equal_to) {
            data.delimit_mode = fss_basic_list_read_delimit_mode_none_e;
          }
          else if (fl_string_dynamic_compare_string(fss_basic_list_read_delimit_mode_name_all_s.string, data.argv[index], fss_basic_list_read_delimit_mode_name_all_s.used) == F_equal_to) {
            data.delimit_mode = fss_basic_list_read_delimit_mode_all_e;
          }
          else if (fl_string_dynamic_compare_string(fss_basic_list_read_delimit_mode_name_object_s.string, data.argv[index], fss_basic_list_read_delimit_mode_name_object_s.used) == F_equal_to) {
            switch (data.delimit_mode) {
              case 0:
                data.delimit_mode = fss_basic_list_read_delimit_mode_object_e;
                break;

              case fss_basic_list_read_delimit_mode_none_e:
              case fss_basic_list_read_delimit_mode_all_e:
              case fss_basic_list_read_delimit_mode_content_greater_object_e:
              case fss_basic_list_read_delimit_mode_content_lesser_object_e:
              case fss_basic_list_read_delimit_mode_object_e:
                break;

              case fss_basic_list_read_delimit_mode_content_e:
                data.delimit_mode = fss_basic_list_read_delimit_mode_content_object_e;
                break;

              case fss_basic_list_read_delimit_mode_content_greater_e:
                data.delimit_mode = fss_basic_list_read_delimit_mode_content_greater_object_e;
                break;

              case fss_basic_list_read_delimit_mode_content_lesser_e:
                data.delimit_mode = fss_basic_list_read_delimit_mode_content_lesser_object_e;
                break;

              default:
                break;
            }
          }
          else {
            if (!data.delimit_mode) {
              data.delimit_mode = fss_basic_list_read_delimit_mode_content_e;
            }
            else if (data.delimit_mode == fss_basic_list_read_delimit_mode_object_e) {
              data.delimit_mode = fss_basic_list_read_delimit_mode_content_object_e;
            }

            if (data.argv[index].string[length - 1] == fss_basic_list_read_delimit_mode_name_greater_s.string[0]) {
              if (!(data.delimit_mode == fss_basic_list_read_delimit_mode_none_e || data.delimit_mode == fss_basic_list_read_delimit_mode_all_e)) {
                if (data.delimit_mode == fss_basic_list_read_delimit_mode_content_object_e) {
                  data.delimit_mode = fss_basic_list_read_delimit_mode_content_greater_object_e;
                }
                else {
                  data.delimit_mode = fss_basic_list_read_delimit_mode_content_greater_e;
                }
              }

              // Shorten the length to better convert the remainder to a number.
              --length;
            }
            else if (data.argv[index].string[length - 1] == fss_basic_list_read_delimit_mode_name_lesser_s.string[0]) {
              if (!(data.delimit_mode == fss_basic_list_read_delimit_mode_none_e || data.delimit_mode == fss_basic_list_read_delimit_mode_all_e)) {
                if (data.delimit_mode == fss_basic_list_read_delimit_mode_content_object_e) {
                  data.delimit_mode = fss_basic_list_read_delimit_mode_content_lesser_object_e;
                }
                else {
                  data.delimit_mode = fss_basic_list_read_delimit_mode_content_lesser_e;
                }
              }

              // Shorten the length to better convert the remainder to a number.
              --length;
            }

            f_string_range_t range = macro_f_string_range_t_initialize2(length);

            // Ignore leading plus sign.
            if (data.argv[index].string[0] == f_string_ascii_plus_s.string[0]) {
              ++range.start;
            }

            status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, data.argv[index], range, &data.delimit_depth);

            if (F_status_is_error(status)) {
              fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_partial_to_unsigned_detect", F_true, fss_basic_list_read_long_delimit_s, data.argv[index]);

              break;
            }

            // There can be nothing smaller than 0, so replace '0-' logic with just '0' logic.
            if (data.delimit_mode == fss_basic_list_read_delimit_mode_content_lesser_e || data.delimit_mode == fss_basic_list_read_delimit_mode_content_lesser_object_e) {
              if (!data.delimit_depth) {
                if (data.delimit_mode == fss_basic_list_read_delimit_mode_content_lesser_e) {
                  data.delimit_mode = fss_basic_list_read_delimit_mode_content_e;
                }
                else {
                  data.delimit_mode = fss_basic_list_read_delimit_mode_content_object_e;
                }
              }
            }
          }
        } // for

        // Guarantee the default value is "all".
        if (F_status_is_error_not(status) && !data.delimit_mode) {
          data.delimit_mode = fss_basic_list_read_delimit_mode_all_e;
        }
      }

      if (F_status_is_error_not(status)) {
        status = fss_basic_list_read_depth_process(main, &data);
      }

      // This standard does not support nesting, so any depth greater than 0 can be predicted without processing the file.
      if (F_status_is_error_not(status) && data.depths.array[0].depth) {
        if (main->parameters.array[fss_basic_list_read_parameter_total_e].result & f_console_result_found_e) {
          fss_basic_list_read_print_zero(main);
        }

        fss_basic_list_read_data_delete_simple(&data);

        return F_none;
      }

      if (F_status_is_error_not(status) && (main->parameters.array[fss_basic_list_read_parameter_select_e].result & f_console_result_found_e)) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_list_read_long_select_s, main->error.notable);
        fl_print_format("%[' parameter requires a positive number.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && (main->pipe & fll_program_data_pipe_input_e)) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;
        file.stream = F_type_input_d;

        data.files.array[0].range.start = 0;

        status = f_file_stream_read(file, &data.buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read", fll_error_file_flag_fallback_e, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
        }
        else if (data.buffer.used) {
          data.files.array[0].range.stop = data.buffer.used - 1;

          // This standard is newline sensitive, when appending files to the buffer if the file lacks a final newline then this could break the format for files appended thereafter.
          // Guarantee that a newline exists at the end of the buffer.
          status = f_string_dynamic_append_assure(f_string_eol_s, &data.buffer);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_assure", fll_error_file_flag_fallback_e, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
          }
        }
        else {
          data.files.array[0].range.start = 1;
        }
      }

      if (F_status_is_error_not(status) && main->parameters.remaining.used) {
        f_file_t file = f_file_t_initialize;
        off_t size_block = 0;
        off_t size_file = 0;
        off_t size_read = 0;

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_basic_list_read_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          data.files.array[data.files.used].name = data.argv[main->parameters.remaining.array[i]];
          data.files.array[data.files.used].range.start = data.buffer.used;
          file.stream = 0;
          file.id = -1;

          status = f_file_stream_open(data.files.array[data.files.used].name, f_string_empty_s, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", fll_error_file_flag_fallback_e, data.argv[main->parameters.remaining.array[i]], f_file_operation_open_s, fll_error_file_type_file_e);

            break;
          }

          size_file = 0;

          status = f_file_size_by_id(file.id, &size_file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_size_by_id", fll_error_file_flag_fallback_e, data.argv[main->parameters.remaining.array[i]], f_file_operation_read_s, fll_error_file_type_file_e);

            f_file_stream_flush(file);
            f_file_stream_close(&file);

            break;
          }

          if (size_file) {

            // Enforce a max block read size to allow for interrupts to be processed between blocks.
            if (size_file > fss_basic_list_read_block_max) {
              file.size_read = fss_basic_list_read_block_read_large;
              size_block = fss_basic_list_read_block_max;

              // Pre-allocate entire file buffer plus space for the terminating NULL.
              f_string_dynamic_increase_by(size_file + (size_block - (size_file % size_block)) + 1, &data.buffer);
            }
            else {
              file.size_read = fss_basic_list_read_block_read_small;
              size_block = size_file;

              // Pre-allocate entire file buffer plus space for the terminating NULL.
              f_string_dynamic_increase_by(size_file + 1, &data.buffer);
            }

            if (F_status_is_error(status)) {
              fll_error_file_print(main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", fll_error_file_flag_fallback_e, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);

              f_file_stream_flush(file);
              f_file_stream_close(&file);

              break;
            }

            for (size_read = 0; size_read < size_file; size_read += size_block) {

              // The signal check is always performed on each pass.
              if (size_file > fss_basic_list_read_block_max && fll_program_standard_signal_received(main)) {
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
                fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read_until", fll_error_file_flag_fallback_e, data.argv[main->parameters.remaining.array[i]], f_file_operation_read_s, fll_error_file_type_file_e);
              }

              break;
            }

            if (data.buffer.used > data.files.array[data.files.used].range.start) {
              data.files.array[data.files.used++].range.stop = data.buffer.used - 1;

              // This standard is newline sensitive, when appending files to the buffer if the file lacks a final newline then this could break the format for files appended thereafter.
              // Guarantee that a newline exists at the end of the buffer.
              status = f_string_dynamic_append_assure(f_string_eol_s, &data.buffer);

              if (F_status_is_error(status)) {
                fll_error_file_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_assure", fll_error_file_flag_fallback_e, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
              }
            }
          }
          else {
            data.files.array[data.files.used].range.start = 1;
            data.files.array[data.files.used].range.stop = 1;
          }
        } // for

        f_file_stream_flush(file);
        f_file_stream_close(&file);
      }

      if (F_status_is_error_not(status)) {
        status = fss_basic_list_read_process(main, &data);
      }

      fss_basic_list_read_data_delete_simple(&data);
    }
    else {
      fll_print_format("%r%[%QYou failed to specify one or more files.%]%r", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
      status = F_status_set_error(F_parameter);
    }

    if (main->error.verbosity > f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        f_file_stream_flush(main->output.to);

        fll_print_dynamic_raw(f_string_eol_s, main->output.to);
      }
    }

    fss_basic_list_read_data_delete_simple(&data);

    return status;
  }
#endif // _di_fss_basic_list_read_main_

#ifdef __cplusplus
} // extern "C"
#endif
