#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_ensure_quotes_length_
  void fss_read_ensure_quotes_length(fss_read_main_t * const main) {

    if (main->setting.quotes_object.size < main->setting.objects.used) {
      main->setting.state.status = f_uint8s_increase_by(main->setting.objects.used - main->setting.quotes_object.size, &main->setting.quotes_object);
      if (F_status_is_error(main->setting.state.status)) return;
    }

    if (main->setting.quotes_content.size < main->setting.contents.used) {
      main->setting.state.status = f_uint8ss_increase_by(main->setting.contents.used - main->setting.quotes_content.size, &main->setting.quotes_content);
      if (F_status_is_error(main->setting.state.status)) return;
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_ensure_quotes_length_

#ifndef _di_fss_read_setting_load_
  void fss_read_setting_load(const f_console_arguments_t arguments, fss_read_main_t * const main, void (*callback)(const f_console_arguments_t arguments, fss_read_main_t * const main)) {

    if (!main) return;

    f_console_parameters_t * const parameters = &main->program.parameters;

    main->setting.state.step_small = fss_read_allocation_console_d;

    f_console_parameter_process(arguments, parameters, &main->setting.state, 0);

    main->setting.state.step_small = fss_read_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (parameters->array[fss_read_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fss_read_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= fss_read_main_flag_print_first_e;
    }

    if (parameters->array[fss_read_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fss_read_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= fss_read_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fss_read_print_error(&main->program.error, macro_fss_read_f(f_console_parameter_process));

      return;
    }

    {
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_read_parameter_no_color_e, fss_read_parameter_light_e, fss_read_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        main->setting.state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_read_print_error(&main->program.error, macro_fss_read_f(fll_program_parameter_process_context));

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_read_parameter_verbosity_quiet_e, fss_read_parameter_verbosity_error_e, fss_read_parameter_verbosity_verbose_e, fss_read_parameter_verbosity_debug_e, fss_read_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        main->setting.state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_read_print_error(&main->program.error, macro_fss_read_f(fll_program_parameter_process_verbosity));

          return;
        }
      }
    }

    main->program.output.to.id = F_type_descriptor_output_d;
    main->program.output.to.stream = F_type_output_d;
    main->program.output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (parameters->array[fss_read_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_help_e;
    }

    if (parameters->array[fss_read_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_version_e;
    }

    if (parameters->array[fss_read_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_copyright_e;
    }

    if (callback) {
      callback(arguments, main);
      if (F_status_is_error(main->setting.state.status)) return;

      if (main->setting.state.status == F_done) {
        main->setting.state.status = F_none;

        return;
      }
    }

    if (parameters->array[fss_read_parameter_help_e].result & f_console_result_found_e) return;
    if (parameters->array[fss_read_parameter_version_e].result & f_console_result_found_e) return;

    f_array_length_t i = 0;
    f_array_length_t index = 0;

    {
      static const f_array_length_t parameter_code[] = {
        fss_read_parameter_at_e,
        fss_read_parameter_depth_e,
        fss_read_parameter_line_e,
        fss_read_parameter_select_e,
        fss_read_parameter_name_e,
        fss_read_parameter_delimit_e,
      };

      const f_string_static_t parameter_name[] = {
        fss_read_long_at_s,
        fss_read_long_depth_s,
        fss_read_long_line_s,
        fss_read_long_select_s,
        fss_read_long_name_s,
        fss_read_long_delimit_s,
      };

      static const f_string_static_t message_positive_number = macro_f_string_static_t_initialize_1("a positive number", 0, 17);
      static const f_string_static_t message_string = macro_f_string_static_t_initialize_1("a string", 0, 8);
      static const f_string_static_t message_value = macro_f_string_static_t_initialize_1("a value", 0, 7);

      static const f_string_static_t parameter_message[] = {
        message_positive_number,
        message_positive_number,
        message_positive_number,
        message_positive_number,
        message_string,
        message_value,
      };

      static const uint32_t parameter_flag[] = {
        fss_read_main_flag_at_e,
        fss_read_main_flag_depth_e,
        fss_read_main_flag_line_e,
        fss_read_main_flag_select_e,
        fss_read_main_flag_name_e,
        fss_read_main_flag_delimit_e,
      };

      f_number_unsigned_t * const parameter_value_digit[] = {
        0,                     // at
        0,                     // depth
        &main->setting.line,   // line
        &main->setting.select, // select
        0,                     // name
        0,                     // delimit
      };

      for (i = 0; i < 6; ++i) {

        if (parameters->array[parameter_code[i]].result & f_console_result_value_e) {
          main->setting.flag |= parameter_flag[i];

          if (parameter_value_digit[i]) {
            index = parameters->array[parameter_code[i]].values.array[parameters->array[parameter_code[i]].values.used - 1];

            main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, parameters->arguments.array[index], parameter_value_digit[i]);

            if (F_status_is_error(main->setting.state.status)) {
              fll_error_parameter_integer_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(fl_conversion_dynamic_to_unsigned_detect), F_true, parameter_name[i], parameters->arguments.array[index]);

              return;
            }
          }
        }
        else if (parameters->array[parameter_code[i]].result & f_console_result_found_e) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_read_print_error_parameter_requires_message(&main->program.error, f_console_symbol_long_normal_s, parameter_name[i], parameter_message[i]);

          return;
        }
      } // for
    }

    if (parameters->array[fss_read_parameter_columns_e].result & f_console_result_found_e) {
      static const f_array_length_t parameter_code[] = {
        fss_read_parameter_depth_e,
        fss_read_parameter_line_e,
        fss_read_parameter_pipe_e,
        fss_read_parameter_select_e,
        fss_read_parameter_total_e,
      };

      const f_string_static_t parameter_name[] = {
        fss_read_long_depth_s,
        fss_read_long_line_s,
        fss_read_long_pipe_s,
        fss_read_long_select_s,
        fss_read_long_total_s,
      };

      static const uint8_t parameter_match[] = {
        f_console_result_value_e,
        f_console_result_value_e,
        f_console_result_found_e,
        f_console_result_value_e,
        f_console_result_found_e,
      };

      for (i = 0; i < 5; ++i) {

        if (parameters->array[parameter_code[i]].result & parameter_match[i]) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
            if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_read_long_columns_s, parameter_name[i]);
          }

          return;
        }
      } // for

      main->setting.flag |= fss_read_main_flag_columns_e;
    }

    if (parameters->array[fss_read_parameter_pipe_e].result & f_console_result_found_e) {
      if ((parameters->array[fss_read_parameter_total_e].result & f_console_result_found_e) || (parameters->array[fss_read_parameter_total_e].result & f_console_result_found_e)) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_cannot_use_with(
            &main->program.error, f_console_symbol_long_normal_s,
            f_console_symbol_long_normal_s,
            fss_read_long_pipe_s,
            (parameters->array[fss_read_parameter_total_e].result & f_console_result_found_e)
              ? fss_read_long_total_s
              : fss_read_long_line_s
          );
        }

        return;
      }
    }

    if (parameters->array[fss_read_parameter_delimit_e].result & f_console_result_value_e) {
      f_array_length_t length = 0;

      // Set the value to 0 to allow for detecting mode based on what is provided.
      main->setting.delimit_mode = 0;

      for (i = 0; i < parameters->array[fss_read_parameter_delimit_e].values.used; ++i) {

        if (fss_read_signal_check(main)) return;

        index = parameters->array[fss_read_parameter_delimit_e].values.array[i];
        length = parameters->arguments.array[index].used;

        if (!length) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_empty_value(&main->program.error, f_console_symbol_long_normal_s, fss_read_long_delimit_s);

          return;
        }

        if (f_compare_dynamic(fss_read_delimit_mode_name_none_s, parameters->arguments.array[index]) == F_equal_to) {
          main->setting.delimit_mode = fss_read_delimit_mode_none_e;
        }
        else if (f_compare_dynamic(fss_read_delimit_mode_name_all_s, parameters->arguments.array[index]) == F_equal_to) {
          main->setting.delimit_mode = fss_read_delimit_mode_all_e;
        }
        else if (f_compare_dynamic(fss_read_delimit_mode_name_object_s, parameters->arguments.array[index]) == F_equal_to) {
          switch (main->setting.delimit_mode) {
            case fss_read_delimit_mode_auto_e:
              main->setting.delimit_mode = fss_read_delimit_mode_object_e;

              break;

            case fss_read_delimit_mode_none_e:
            case fss_read_delimit_mode_all_e:
            case fss_read_delimit_mode_content_greater_object_e:
            case fss_read_delimit_mode_content_lesser_object_e:
            case fss_read_delimit_mode_object_e:
              break;

            case fss_read_delimit_mode_content_e:
              main->setting.delimit_mode = fss_read_delimit_mode_content_object_e;

              break;

            case fss_read_delimit_mode_content_greater_e:
              main->setting.delimit_mode = fss_read_delimit_mode_content_greater_object_e;

              break;

            case fss_read_delimit_mode_content_lesser_e:
              main->setting.delimit_mode = fss_read_delimit_mode_content_lesser_object_e;

              break;

            default:
              break;
          }
        }
        else {
          if (!main->setting.delimit_mode) {
            main->setting.delimit_mode = fss_read_delimit_mode_content_e;
          }
          else if (main->setting.delimit_mode == fss_read_delimit_mode_object_e) {
            main->setting.delimit_mode = fss_read_delimit_mode_content_object_e;
          }

          if (parameters->arguments.array[index].string[length - 1] == fss_read_delimit_mode_name_greater_s.string[0]) {
            if (!(main->setting.delimit_mode == fss_read_delimit_mode_none_e || main->setting.delimit_mode == fss_read_delimit_mode_all_e)) {
              if (main->setting.delimit_mode == fss_read_delimit_mode_content_object_e) {
                main->setting.delimit_mode = fss_read_delimit_mode_content_greater_object_e;
              }
              else {
                main->setting.delimit_mode = fss_read_delimit_mode_content_greater_e;
              }
            }

            // Shorten the length to better convert the remainder to a number.
            --length;
          }
          else if (parameters->arguments.array[index].string[length - 1] == fss_read_delimit_mode_name_lesser_s.string[0]) {
            if (!(main->setting.delimit_mode == fss_read_delimit_mode_none_e || main->setting.delimit_mode == fss_read_delimit_mode_all_e)) {
              if (main->setting.delimit_mode == fss_read_delimit_mode_content_object_e) {
                main->setting.delimit_mode = fss_read_delimit_mode_content_lesser_object_e;
              }
              else {
                main->setting.delimit_mode = fss_read_delimit_mode_content_lesser_e;
              }
            }

            // Shorten the length to better convert the remainder to a number.
            --length;
          }

          if (length) {
            main->setting.range.start = 0;
            main->setting.range.stop = length - 1;
          }
          else {
            main->setting.range.start = 1;
            main->setting.range.stop = 0;
          }

          // Ignore leading plus sign.
          if (parameters->arguments.array[index].string[0] == f_string_ascii_plus_s.string[0]) {
            ++main->setting.range.start;
          }

          main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, parameters->arguments.array[index], main->setting.range, &main->setting.delimit_depth);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_error_parameter_integer_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(fl_conversion_dynamic_partial_to_unsigned_detect), F_true, fss_read_long_delimit_s, parameters->arguments.array[index]);

            return;
          }

          // There can be nothing smaller than 0, so replace '0-' logic with just '0' logic.
          if (main->setting.delimit_mode == fss_read_delimit_mode_content_lesser_e || main->setting.delimit_mode == fss_read_delimit_mode_content_lesser_object_e) {
            if (!main->setting.delimit_depth) {
              if (main->setting.delimit_mode == fss_read_delimit_mode_content_lesser_e) {
                main->setting.delimit_mode = fss_read_delimit_mode_content_e;
              }
              else {
                main->setting.delimit_mode = fss_read_delimit_mode_content_object_e;
              }
            }
          }
        }
      } // for

      // Guarantee the default value is "all".
      if (!main->setting.delimit_mode) {
        main->setting.delimit_mode = fss_read_delimit_mode_all_e;
      }
    }

    if (parameters->array[fss_read_parameter_content_e].result & f_console_result_found_e) {
      if (parameters->array[fss_read_parameter_object_e].result & f_console_result_found_e) {
        main->setting.flag |= fss_read_main_flag_object_e;
      }

      main->setting.flag |= fss_read_main_flag_content_e;
    }
    else if (parameters->array[fss_read_parameter_object_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_object_e;
    }
    else {

      // Fallback to Content as the default.
      main->setting.flag |= fss_read_main_flag_content_e;
    }

    if (parameters->array[fss_read_parameter_empty_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_empty_e;
    }

    if (parameters->array[fss_read_parameter_original_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_original_e;
    }

    if (parameters->array[fss_read_parameter_pipe_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_pipe_e;
    }

    if (parameters->array[fss_read_parameter_total_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_total_e;
    }

    if (parameters->array[fss_read_parameter_trim_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_trim_e;
    }

    fss_read_setting_load_depth(arguments, main, parameters);
    if (F_status_is_error(main->setting.state.status)) return;

    if (parameters->array[fss_read_parameter_trim_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_trim_e;
    }

    f_file_t file = f_file_t_initialize;

    fss_read_files_resize(((main->program.pipe & fll_program_data_pipe_input_e) ? 1 : 0) + parameters->remaining.used, &main->setting.files);

    if (F_status_is_error(main->setting.state.status)) {
      fss_read_print_error(&main->program.error, macro_fss_read_f(fss_read_files_resize));

      return;
    }

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      file.id = F_type_descriptor_input_d;
      file.stream = F_type_input_d;

      main->setting.files.array[0].range.start = 0;

      while (main->setting.state.status != F_none_eof) {

        if (fss_read_signal_check(main)) break;

        main->setting.state.status = f_file_stream_read_block(file, &main->setting.buffer);
        if (F_status_is_error(main->setting.state.status)) break;
      } // while

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(f_file_stream_read_block), fll_error_file_flag_fallback_e, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);

        return;
      }

      if (main->setting.buffer.used) {
        main->setting.files.array[0].range.stop = main->setting.buffer.used - 1;

        if (main->callback.process_last_line) {
          main->callback.process_last_line((void *) main);
          if (F_status_is_error(main->setting.state.status)) return;
        }

        ++main->setting.files.used;
      }
      else {
        main->setting.files.array[0].range.start = 1;
        main->setting.files.array[0].range.stop = 0;
      }
    }

    if (parameters->remaining.used) {
      off_t size_block = 0;
      off_t size_file = 0;
      off_t size_read = 0;
      fss_read_file_t *file_data = 0;

      for (i = 0; i < parameters->remaining.used; ++i) {

        if (fss_read_signal_check(main)) return;

        index = parameters->remaining.array[i];
        file_data = &main->setting.files.array[main->setting.files.used];
        file_data->name = parameters->arguments.array[index];
        file_data->range.start = main->setting.buffer.used;

        file.id = -1;
        file.stream = 0;

        main->setting.state.status = f_file_stream_open(file_data->name, f_string_empty_s, &file);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(f_file_stream_open), fll_error_file_flag_fallback_e, parameters->arguments.array[index], f_file_operation_open_s, fll_error_file_type_file_e);

          break;
        }

        size_file = 0;

        main->setting.state.status = f_file_size(file_data->name, F_true, &size_file);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(f_file_size), fll_error_file_flag_fallback_e, parameters->arguments.array[index], f_file_operation_read_s, fll_error_file_type_file_e);

          break;
        }

        if (size_file) {

          // Enforce a max block read size to allow for interrupts to be processed between blocks.
          if (size_file > fss_read_allocation_block_max_d) {
            file.size_read = fss_read_allocation_block_read_large_d;
            size_block = fss_read_allocation_block_max_d;
          }
          else {
            file.size_read = fss_read_allocation_block_read_small_d;
            size_block = size_file;
          }

          // Pre-allocate entire file buffer plus space for the terminating NULL.
          f_string_dynamic_increase_by(size_file + 1, &main->setting.buffer);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(f_string_dynamic_increase_by), fll_error_file_flag_fallback_e, parameters->arguments.array[index], f_file_operation_process_s, fll_error_file_type_file_e);

            break;
          }

          for (size_read = 0; size_read < size_file; size_read += size_block) {

            if (size_file > fss_read_allocation_block_max_d && fss_read_signal_check(main)) break;

            main->setting.state.status = f_file_stream_read_until(file, size_block, &main->setting.buffer);
            if (F_status_is_error(main->setting.state.status)) break;
          } // for

          if (F_status_is_error(main->setting.state.status)) {
            if (F_status_set_fine(main->setting.state.status) != F_interrupt) {
              if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(f_file_stream_read_until), fll_error_file_flag_fallback_e, parameters->arguments.array[index], f_file_operation_read_s, fll_error_file_type_file_e);
            }

            break;
          }

          if (main->setting.buffer.used > file_data->range.start) {
            main->setting.files.array[main->setting.files.used++].range.stop = main->setting.buffer.used - 1;

            if (main->callback.process_last_line) {
              main->callback.process_last_line((void *) main);
              if (F_status_is_error(main->setting.state.status)) break;
            }
          }

          f_file_stream_flush(file);
          f_file_stream_close(&file);
        }
        else {
          file_data->range.start = 1;
          file_data->range.stop = 0;
        }
      } // for

      f_file_stream_flush(file);
      f_file_stream_close(&file);
    }
  }
#endif // _di_fss_read_setting_load_

#ifndef _di_fss_read_setting_load_depth_
  void fss_read_setting_load_depth(const f_console_arguments_t arguments, void * const void_main, f_console_parameters_t * const parameters) {

    if (!void_main || !parameters) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    f_array_length_t i = 1;

    if (parameters->array[fss_read_parameter_depth_e].result & f_console_result_value_e) {
      i = parameters->array[fss_read_parameter_depth_e].values.used;
    }

    if (i > main->setting.depths.size) {
      main->setting.state.status = fss_read_depths_resize(i, &main->setting.depths);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fss_read_print_error(&main->program.error, macro_fss_read_f(fss_read_depths_resize));

        return;
      }
    }

    main->setting.depths.used = i;

    f_array_length_t position_depth = 0;
    f_array_length_t position_at = 0;
    f_array_length_t position_name = 0;
    fss_read_depth_t *current = 0;

    for (i = 0; i < main->setting.depths.used; ++i) {

      if (fss_read_signal_check(main)) return;

      current = &main->setting.depths.array[i];
      current->depth = 0;
      current->index_at = 0;
      current->index_name = 0;
      current->value_at = 0;
      current->value_name.used = 0;

      if (parameters->array[fss_read_parameter_depth_e].values.used) {
        position_depth = parameters->array[fss_read_parameter_depth_e].values.array[i];

        main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, parameters->arguments.array[position_depth], &current->depth);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_error_parameter_integer_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(fl_conversion_dynamic_to_unsigned_detect), F_true, fss_read_long_depth_s, parameters->arguments.array[position_depth]);

          return;
        }
      }
      else {
        position_depth = 0;
      }

      if (parameters->array[fss_read_parameter_at_e].result & f_console_result_value_e) {
        for (; position_at < parameters->array[fss_read_parameter_at_e].values.used; ++position_at) {

          if (parameters->array[fss_read_parameter_at_e].values.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < main->setting.depths.used && parameters->array[fss_read_parameter_at_e].values.array[position_at] > parameters->array[fss_read_parameter_depth_e].values.array[i + 1]) {
            break;
          }

          current->index_at = parameters->array[fss_read_parameter_at_e].values.array[position_at];

          main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, parameters->arguments.array[current->index_at], &current->value_at);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_error_parameter_integer_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(fl_conversion_dynamic_to_unsigned_detect), F_true, fss_read_long_at_s, parameters->arguments.array[current->index_at]);

            return;
          }
        } // for
      }

      if (parameters->array[fss_read_parameter_name_e].result & f_console_result_value_e) {
        for (; position_name < parameters->array[fss_read_parameter_name_e].values.used; ++position_name) {

          if (parameters->array[fss_read_parameter_name_e].values.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < main->setting.depths.used && parameters->array[fss_read_parameter_name_e].values.array[position_name] > parameters->array[fss_read_parameter_depth_e].values.array[i + 1]) {
            break;
          }

          current->index_name = parameters->array[fss_read_parameter_name_e].values.array[position_name];

          if (parameters->array[fss_read_parameter_trim_e].result & f_console_result_found_e) {
            main->setting.state.status = f_rip_dynamic(parameters->arguments.array[current->index_name], &current->value_name);
          }
          else {
            main->setting.state.status = f_string_dynamic_append(parameters->arguments.array[current->index_name], &current->value_name);
          }

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fss_read_print_error(&main->program.error, (parameters->array[fss_read_parameter_trim_e].result & f_console_result_found_e) ? macro_fss_read_f(f_rip_dynamic) : macro_fss_read_f(f_string_dynamic_append));

            return;
          }
        } // for
      }
    } // for

    f_array_length_t j = 0;

    for (i = 0; i < main->setting.depths.used; ++i) {

      for (j = i + 1; j < main->setting.depths.used; ++j) {

        if (fss_read_signal_check(main)) return;

        current = &main->setting.depths.array[i];

        if (current->depth == main->setting.depths.array[j].depth) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_read_print_error_parameter_value_once_only_number(&main->program.error, f_console_symbol_long_normal_s, fss_read_long_depth_s, current->depth);

          return;
        }

        if (current->depth > main->setting.depths.array[j].depth) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_read_print_error_parameter_value_before_value_number(&main->program.error, f_console_symbol_long_normal_s, fss_read_long_depth_s, current->depth, main->setting.depths.array[j].depth);

          return;
        }
      } // for
    } // for

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_setting_load_depth_

#ifdef __cplusplus
} // extern "C"
#endif
