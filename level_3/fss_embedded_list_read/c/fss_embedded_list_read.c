#include "fss_embedded_list_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_read_main_
  f_status_t fss_embedded_list_read_main(fll_program_data_t * const main, fss_embedded_list_read_setting_t * const setting) {

    f_status_t status = F_none;

    // Load parameters.
    status = f_console_parameter_process(arguments, &main->parameters, 0);
    if (F_status_is_error(status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_embedded_list_read_parameter_no_color_e, fss_embedded_list_read_parameter_light_e, fss_embedded_list_read_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(status)) {
          fss_embedded_list_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_context", F_true);
          fss_embedded_list_read_print_line_last_locked(setting, main->error);

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_embedded_list_read_parameter_verbosity_quiet_e, fss_embedded_list_read_parameter_verbosity_error_e, fss_embedded_list_read_parameter_verbosity_verbose_e, fss_embedded_list_read_parameter_verbosity_debug_e, fss_embedded_list_read_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(status)) {
          fss_embedded_list_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process_verbosity", F_true);
          fss_embedded_list_read_print_line_last_locked(setting, main->error);

          return;
        }
      }
    }

    fss_embedded_list_read_data_t data = fss_embedded_list_read_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[fss_embedded_list_read_parameter_help_e].result & f_console_result_found_e) {
      fss_embedded_list_read_print_help(setting, main->message);

      fss_embedded_list_read_data_delete(&data);

      return F_none;
    }

    if (main->parameters.array[fss_embedded_list_read_parameter_version_e].result & f_console_result_found_e) {
      fll_program_print_version(main->message, fss_embedded_list_read_program_version_s);

      fss_embedded_list_read_data_delete(&data);

      return F_none;
    }

    if (F_status_is_error_not(status) && (main->parameters.array[fss_embedded_list_read_parameter_total_e].result & f_console_result_found_e)) {
      if (main->parameters.array[fss_embedded_list_read_parameter_columns_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_embedded_list_read_long_columns_s, fss_embedded_list_read_long_total_s);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (main->parameters.remaining.used > 0 || (main->pipe & fll_program_data_pipe_input_e)) {
      if (main->parameters.array[fss_embedded_list_read_parameter_at_e].result & f_console_result_found_e) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_embedded_list_read_long_at_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && (main->parameters.array[fss_embedded_list_read_parameter_depth_e].result & f_console_result_found_e)) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_embedded_list_read_long_depth_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->parameters.array[fss_embedded_list_read_parameter_line_e].result & f_console_result_value_e) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_embedded_list_read_long_line_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && (main->parameters.array[fss_embedded_list_read_parameter_name_e].result & f_console_result_found_e)) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_embedded_list_read_long_name_s, main->error.notable);
        fl_print_format("%[' requires a string.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && (main->parameters.array[fss_embedded_list_read_parameter_select_e].result & f_console_result_found_e)) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_embedded_list_read_long_select_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }

      if (main->parameters.array[fss_embedded_list_read_parameter_line_e].result & f_console_result_value_e) {
        if (F_status_is_error_not(status) && (main->parameters.array[fss_embedded_list_read_parameter_total_e].result & f_console_result_found_e)) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_embedded_list_read_long_line_s, fss_embedded_list_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters.array[fss_embedded_list_read_parameter_pipe_e].result & f_console_result_found_e) {
        if (F_status_is_error_not(status) && (main->parameters.array[fss_embedded_list_read_parameter_total_e].result & f_console_result_found_e)) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_embedded_list_read_long_pipe_s, fss_embedded_list_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status)) {
        if (main->parameters.array[fss_embedded_list_read_parameter_delimit_e].result & f_console_result_found_e) {
          f_file_stream_lock(main->error.to);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_embedded_list_read_long_delimit_s, main->error.notable);
          fl_print_format("%[' requires a value.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          f_file_stream_unlock(main->error.to);

          status = F_status_set_error(F_parameter);
        }
        else if (main->parameters.array[fss_embedded_list_read_parameter_delimit_e].result & f_console_result_value_e) {
          const f_array_length_t index = main->parameters.array[fss_embedded_list_read_parameter_delimit_e].values.array[0];
          f_array_length_t length = data.argv[index].used;

          if (!length) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_embedded_list_read_long_delimit_s, main->error.notable);
            fl_print_format("%[' must not be empty.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);

            status = F_status_set_error(F_parameter);
          }
          else if (fl_string_dynamic_compare_string(fss_embedded_list_read_delimit_mode_name_none_s.string, data.argv[index], fss_embedded_list_read_delimit_mode_name_none_s.used) == F_equal_to) {
            data.delimit_mode = fss_embedded_list_read_delimit_mode_none_e;
          }
          else if (fl_string_dynamic_compare_string(fss_embedded_list_read_delimit_mode_name_all_s.string, data.argv[index], fss_embedded_list_read_delimit_mode_name_all_s.used) == F_equal_to) {
            data.delimit_mode = fss_embedded_list_read_delimit_mode_all_e;
          }
          else {
            data.delimit_mode = fss_embedded_list_read_delimit_mode_depth_e;

            if (data.argv[index].string[length - 1] == fss_embedded_list_read_delimit_mode_name_greater_s.string[0]) {
              data.delimit_mode = fss_embedded_list_read_delimit_mode_depth_greater_e;

              // Shorten the length to better convert the remainder to a number.
              --length;
            }
            else if (data.argv[index].string[length - 1] == fss_embedded_list_read_delimit_mode_name_lesser_s.string[0]) {
              data.delimit_mode = fss_embedded_list_read_delimit_mode_depth_lesser_e;

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
              fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_partial_to_unsigned_detect", F_true, fss_embedded_list_read_long_delimit_s, data.argv[index]);
            }
          }
        }
      }

      fss_embedded_list_read_depths_t depths = fss_embedded_list_read_depths_t_initialize;

      f_fss_delimits_t objects_delimits = f_fss_delimits_t_initialize;
      f_fss_delimits_t contents_delimits = f_fss_delimits_t_initialize;
      f_fss_comments_t comments = f_fss_comments_t_initialize;

      if (F_status_is_error_not(status)) {
        status = fss_embedded_list_read_main_preprocess_depth(&data, &depths);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fss_embedded_list_read_main_preprocess_depth", F_true);
        }
      }

      if (F_status_is_error_not(status) && (main->parameters.array[fss_embedded_list_read_parameter_select_e].result & f_console_result_found_e)) {
        f_file_stream_lock(main->error.to);

        fl_print_format("%r%[%QThe '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_embedded_list_read_long_select_s, main->error.notable);
        fl_print_format("%[' parameter requires a positive number.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

        f_file_stream_unlock(main->error.to);

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && (main->pipe & fll_program_data_pipe_input_e)) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;

        status = f_file_read(file, &data.buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read", F_true, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
        }
        else {
          status = fss_embedded_list_read_main_process_file(&data, f_string_ascii_minus_s, depths, &objects_delimits, &contents_delimits, &comments);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "fss_embedded_list_read_main_process_file", F_true, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
          }
        }

        // Clear buffers before continuing.
        f_fss_nest_resize(0, &data.nest);
        f_string_dynamic_resize(0, &data.buffer);
      }

      if (F_status_is_error_not(status) && main->parameters.remaining.used > 0) {
        f_file_t file = f_file_t_initialize;
        off_t size_block = 0;
        off_t size_file = 0;
        off_t size_read = 0;

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_embedded_list_read_signal_check_d)) {
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
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_open_s, fll_error_file_type_file_e);

            break;
          }

          size_file = 0;

          status = f_file_size_by_id(file.id, &size_file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_size_by_id", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_read_s, fll_error_file_type_file_e);

            f_file_stream_flush(file);
            f_file_stream_close(&file);

            break;
          }

          // Skip past empty files.
          if (!size_file) {
            if (main->parameters.array[fss_embedded_list_read_parameter_total_e].result & f_console_result_found_e) {
              fll_print_format("%r%r", main->output.to, f_string_ascii_0_s, f_string_eol_s);
            }

            f_file_stream_flush(file);
            f_file_stream_close(&file);

            continue;
          }

          // Enforce a max block read size to allow for interrupts to be processed between blocks.
          if (size_file > fss_embedded_list_read_block_max) {
            file.size_read = fss_embedded_list_read_block_read_large;
            size_block = fss_embedded_list_read_block_max;

            // Pre-allocate entire file buffer plus space for the terminating NULL.
            f_string_dynamic_increase_by(size_file + (size_block - (size_file % size_block)) + 1, &data.buffer);
          }
          else {
            file.size_read = fss_embedded_list_read_block_read_small;
            size_block = size_file;

            // Pre-allocate entire file buffer plus space for the terminating NULL.
            f_string_dynamic_increase_by(size_file + 1, &data.buffer);
          }

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);

            f_file_stream_flush(file);
            f_file_stream_close(&file);

            break;
          }

          for (size_read = 0; size_read < size_file; size_read += size_block) {

            // The signal check is always performed on each pass.
            if (size_file > fss_embedded_list_read_block_max && fll_program_standard_signal_received(main)) {
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
              fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read_until", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_read_s, fll_error_file_type_file_e);
            }

            break;
          }

          status = fss_embedded_list_read_main_process_file(&data, data.argv[main->parameters.remaining.array[i]], depths, &objects_delimits, &contents_delimits, &comments);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "fss_embedded_list_read_main_process_file", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_read_s, fll_error_file_type_file_e);

            break;
          }

          // Clear buffers before repeating the loop.
          f_fss_nest_resize(0, &data.nest);
          data.buffer.used = 0;
        } // for
      }

      f_fss_nest_resize(0, &data.nest);
      f_string_dynamic_resize(0, &data.buffer);
      fss_embedded_list_read_depths_resize(0, &depths);
      f_array_lengths_resize(0, &objects_delimits);
      f_array_lengths_resize(0, &contents_delimits);
      f_string_ranges_resize(0, &comments);
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

    fss_embedded_list_read_data_delete(&data);

    return status;
  }
#endif // _di_fss_embedded_list_read_main_

#ifdef __cplusplus
} // extern "C"
#endif
