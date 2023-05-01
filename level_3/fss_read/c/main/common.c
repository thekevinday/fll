#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_setting_load_
  void fss_read_setting_load(const f_console_arguments_t arguments, fss_read_main_t * const main, void (*callback)(const f_console_arguments_t arguments, fss_read_main_t * const main)) {

    if (!main) return;

    main->setting.state.step_small = fss_read_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = fss_read_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (main->program.parameters.array[fss_read_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fss_read_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= fss_read_main_flag_print_first_e;
    }

    if (main->program.parameters.array[fss_read_parameter_line_last_no_e].result & f_console_result_found_e) {
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

    if (main->program.parameters.array[fss_read_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_help_e;
    }

    if (main->program.parameters.array[fss_read_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_version_e;
    }

    if (main->program.parameters.array[fss_read_parameter_copyright_e].result & f_console_result_found_e) {
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

    if (main->program.parameters.array[fss_read_parameter_help_e].result & f_console_result_found_e) return;
    if (main->program.parameters.array[fss_read_parameter_version_e].result & f_console_result_found_e) return;

    f_array_length_t i = 0;

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

      static const f_string_t message_positive_number = "a positive number";
      static const f_string_t message_string = "a string";
      static const f_string_t message_value = "a value";

      static const f_string_t parameter_message[] = {
        message_positive_number,
        message_positive_number,
        message_positive_number,
        message_positive_number,
        message_string,
        message_value,
      };

      for (i = 0; i < 6; ++i) {

        if (main->program.parameters.array[parameter_code[i]].result & f_console_result_found_e)) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_read_print_error_parameter_requires_message(&main->error, f_console_symbol_long_normal_s, parameter_name[i], parameter_message[i]);

          return;
        }
      } // for
    }

    if (main->parameters.array[fss_read_parameter_columns_e].result & f_console_result_found_e) {
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

      const uint8_t parameter_match[] = {
        f_console_result_value_e,
        f_console_result_value_e,
        f_console_result_found_e,
        f_console_result_value_e,
        f_console_result_found_e,
      };

      for (i = 0; i < 5; ++i) {

        if (main->parameters.array[parameter_code[i]].result == parameter_match[i]) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_cannot_use_with(&main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_read_long_columns_s, parameter_name[i]);
          }

          return;
        }
      } // for
    }

    if (main->parameters.array[fss_read_parameter_pipe_e].result & f_console_result_found_e) {
      if ((main->parameters.array[fss_read_parameter_total_e].result & f_console_result_found_e) || (main->parameters.array[fss_read_parameter_total_e].result & f_console_result_found_e)) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_cannot_use_with(
            &main->error, f_console_symbol_long_normal_s,
            f_console_symbol_long_normal_s,
            fss_read_long_pipe_s,
            (main->parameters.array[fss_read_parameter_total_e].result & f_console_result_found_e)
              ? fss_read_long_total_s
              : fss_read_long_line_s
          );
        }

        return;
      }
    }

    if (main->parameters.array[fss_read_parameter_delimit_e].result & f_console_result_value_e) {
      f_array_length_t index = 0;
      f_array_length_t length = 0;

      // Set the value to 0 to allow for detecting mode based on what is provided.
      main->setting.delimit_mode = 0;

      for (i = 0; i < main->parameters.array[fss_read_parameter_delimit_e].values.used; ++i) {

        if (!((++main->signal_check) % fss_read_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            fll_program_print_signal_received(main->warning, main->signal_received);

            main->setting.state.status = F_status_set_error(F_interrupt);

            return;
          }

          main->signal_check = 0;
        }

        index = main->parameters.array[fss_read_parameter_delimit_e].values.array[i];
        length = main->program.parameters.arguments.array[index].used;

        if (!length) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_empty_value(&main->program.error, f_console_symbol_long_normal_s, fss_read_long_file_s);

          return;
        }

        if (f_compare_dynamic(fss_read_delimit_mode_name_none_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
          main->setting.delimit_mode = fss_read_delimit_mode_none_e;
        }
        else if (f_compare_dynamic(fss_read_delimit_mode_name_all_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
          main->setting.delimit_mode = fss_read_delimit_mode_all_e;
        }
        else if (f_compare_dynamic(fss_read_delimit_mode_name_object_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
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

          if (main->program.parameters.arguments.array[index].string[length - 1] == fss_read_delimit_mode_name_greater_s.string[0]) {
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
          else if (main->program.parameters.arguments.array[index].string[length - 1] == fss_read_delimit_mode_name_lesser_s.string[0]) {
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
          if (main->program.parameters.arguments.array[index].string[0] == f_string_ascii_plus_s.string[0]) {
            ++main->setting.range.start;
          }

          main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], main->setting.range, &main->setting.delimit_depth);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_error_parameter_integer_print(&main->error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(fl_conversion_dynamic_partial_to_unsigned_detect), F_true, fss_read_long_delimit_s, main->program.parameters.arguments.array[index]);

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

    main->setting.state.status = fss_read_depth_process(main, &data);

    if (F_status_is_error(main->setting.state.status) {
      if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fss_read_print_error(&main->program.error, macro_fss_read_f(fss_read_depth_process));

      return;
    }

    // @todo: Some standards do not support nesting, so any depth greater than 0 can be predicted without processing the file, this check needs to happen in the program specific settings processing function.
    // if (data.depths.array[0].depth) { ...

    if (main->parameters.array[fss_read_parameter_select_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_integer_not_positive(&main->error, f_console_symbol_long_normal_s, fss_read_long_select_s);

      return;
    }

    if (main->program.parameters.array[fss_read_parameter_trim_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_read_main_flag_trim_e;
    }

    // @fixme this is from fss_write, but doing some sort of file check, such as no pipe and no files may be a good idea here. Replace this with such logic if deemed desirable.
    if (!(main->setting.flag & (fll_program_data_pipe_input_e | fss_read_main_flag_content_e | fss_read_parameter_object_e))) {
      main->setting.state.status = F_data_not;
    }
  }
#endif // _di_fss_read_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
