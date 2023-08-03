#include "byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_setting_load_
  void byte_dump_setting_load(const f_console_arguments_t arguments, byte_dump_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = byte_dump_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = byte_dump_allocation_small_d;

    // Identify and process first/last parameters.
    if (main->program.parameters.array[f_console_standard_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & byte_dump_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= byte_dump_main_flag_print_first_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & byte_dump_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= byte_dump_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      byte_dump_print_error(&main->program.error, macro_byte_dump_f(f_console_parameter_process));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      byte_dump_print_error(&main->program.error, macro_byte_dump_f(fll_program_parameter_process_context_standard));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      byte_dump_print_error(&main->program.error, macro_byte_dump_f(fll_program_parameter_process_verbosity_standard));

      return;
    }

    {
      f_number_unsigned_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify priority of mode parameters.
      {
        uint16_t choices_array[5] = { byte_dump_parameter_hexidecimal_e, byte_dump_parameter_duodecimal_e, byte_dump_parameter_octal_e, byte_dump_parameter_binary_e, byte_dump_parameter_decimal_e };
        choices.array = choices_array;
        choices.used = 5;
        choice = 0;

        main->setting.state.status = f_console_parameter_prioritize_right(main->program.parameters, choices, &choice);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          byte_dump_print_error(&main->program.error, macro_byte_dump_f(f_console_parameter_prioritize_right));

          return;
        }

        if (choices.array[choice] == byte_dump_parameter_hexidecimal_e) {
          main->setting.mode = byte_dump_mode_hexidecimal_e;
        }
        else if (choices.array[choice] == byte_dump_parameter_duodecimal_e) {
          main->setting.mode = byte_dump_mode_duodecimal_e;
        }
        else if (choices.array[choice] == byte_dump_parameter_octal_e) {
          main->setting.mode = byte_dump_mode_octal_e;
        }
        else if (choices.array[choice] == byte_dump_parameter_binary_e) {
          main->setting.mode = byte_dump_mode_binary_e;
        }
        else if (choices.array[choice] == byte_dump_parameter_decimal_e) {
          main->setting.mode = byte_dump_mode_decimal_e;
        }
      }

      // Identify priority of presentation parameters.
      {
        uint16_t choices_array[3] = { byte_dump_parameter_normal_e, byte_dump_parameter_simple_e, byte_dump_parameter_classic_e };
        choices.array = choices_array;
        choices.used = 3;
        choice = 0;

        main->setting.state.status = f_console_parameter_prioritize_right(main->program.parameters, choices, &choice);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          byte_dump_print_error(&main->program.error, macro_byte_dump_f(f_console_parameter_prioritize_right));

          return;
        }

        if (choices.array[choice] == byte_dump_parameter_normal_e) {
          main->setting.presentation = byte_dump_presentation_normal_e;
        }
        else if (choices.array[choice] == byte_dump_parameter_simple_e) {
          main->setting.presentation = byte_dump_presentation_simple_e;
        }
        else if (choices.array[choice] == byte_dump_parameter_classic_e) {
          main->setting.presentation = byte_dump_presentation_classic_e;
        }
      }

      // Identify priority of narrow and wide parameters.
      {
        uint16_t choices_array[2] = { byte_dump_parameter_narrow_e, byte_dump_parameter_wide_e };
        choices.array = choices_array;
        choices.used = 2;
        choice = 1;

        main->setting.state.status = f_console_parameter_prioritize_right(main->program.parameters, choices, &choice);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          byte_dump_print_error(&main->program.error, macro_byte_dump_f(f_console_parameter_prioritize_right));

          return;
        }

        if (choices.array[choice] == byte_dump_parameter_narrow_e) {
          if (main->setting.flag & byte_dump_main_flag_wide_e) {
            main->setting.flag -= byte_dump_main_flag_wide_e;
          }
        }
        else if (choices.array[choice] == byte_dump_parameter_wide_e) {
          main->setting.flag |= byte_dump_main_flag_wide_e;
        }
      }
    }

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= byte_dump_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= byte_dump_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= byte_dump_main_flag_copyright_e;

      return;
    }

    f_number_unsigned_t index = 0;
    f_number_unsigned_t number = 0;

    if (main->program.parameters.array[byte_dump_parameter_width_e].result & f_console_result_value_e) {
      index = main->program.parameters.array[byte_dump_parameter_width_e].values.array[main->program.parameters.array[byte_dump_parameter_width_e].values.used - 1];

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &number);

      // Negative numbers are not supported.
      if (main->setting.state.status == F_number_negative) {
        main->setting.state.status = F_status_set_error(F_number_negative);
      }

      if (F_status_is_error(main->setting.state.status) || number < 0x1 || number >= 0xfb) {
        if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        byte_dump_print_error_parameter_range_out(&main->program.error, byte_dump_long_width_s, 1, 250, main->program.parameters.arguments.array[index]);

        return;
      }

      main->setting.width = (uint8_t) number;
    }
    else if (main->program.parameters.array[byte_dump_parameter_width_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, byte_dump_long_width_s);

      return;
    }

    {
      const f_number_unsigned_t indexs[] = {
        byte_dump_parameter_first_e,
        byte_dump_parameter_last_e,
      };

      const f_string_static_t names[] = {
        byte_dump_long_first_s,
        byte_dump_long_last_s,
      };

      const uint16_t flags[] = {
        byte_dump_main_flag_first_e,
        byte_dump_main_flag_last_e,
      };

      uint64_t * const values[] = {
        &main->setting.first,
        &main->setting.last,
      };

      for (uint8_t i = 0; i < 2; ++i) {

        if (main->program.parameters.array[indexs[i]].result & f_console_result_value_e) {
          index = main->program.parameters.array[indexs[i]].values.array[main->program.parameters.array[indexs[i]].values.used - 1];

          main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &number);

          // Negative numbers are not supported.
          if (main->setting.state.status == F_number_negative) {
            main->setting.state.status = F_status_set_error(F_number_negative);
          }

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            byte_dump_print_error_parameter_range_out(&main->program.error, names[i], 0, F_number_t_size_unsigned_d, main->program.parameters.arguments.array[index]);

            return;
          }

          *values[i] = number;
          main->setting.flag |= flags[i];
        }
        else if (main->program.parameters.array[indexs[i]].result & f_console_result_found_e) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, names[i]);

          return;
        }
        else {
          main->setting.flag -= flags[i] & main->setting.flag;
        }
      } // for

      if ((main->setting.flag & byte_dump_main_flag_first_e) && (main->setting.flag & byte_dump_main_flag_last_e)) {
        if (main->setting.first > main->setting.last) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_first_greater_than_last(&main->program.error);

          return;
        }

        // Store last position as a relative offset from first instead of an absolute position.
        main->setting.last = (main->setting.last - main->setting.first) + 1;
      }
    }

    if (main->program.parameters.array[byte_dump_parameter_text_e].result & f_console_result_found_e) {
      main->setting.flag |= byte_dump_main_flag_text_e;
    }
    else {
      main->setting.flag -= byte_dump_main_flag_text_e & main->setting.flag;
    }

    if (main->program.parameters.array[byte_dump_parameter_unicode_e].result & f_console_result_found_e) {
      main->setting.flag |= byte_dump_main_flag_unicode_e;
    }
    else {
      main->setting.flag -= byte_dump_main_flag_unicode_e & main->setting.flag;
    }

    if (main->program.parameters.array[byte_dump_parameter_placeholder_e].result & f_console_result_found_e) {
      main->setting.flag |= byte_dump_main_flag_placeholder_e;
    }
    else {
      main->setting.flag -= byte_dump_main_flag_placeholder_e & main->setting.flag;
    }

    if (main->program.parameters.array[byte_dump_parameter_classic_e].result & f_console_result_found_e) {
      main->setting.flag |= byte_dump_main_flag_classic_e;
    }
    else {
      main->setting.flag -= byte_dump_main_flag_classic_e & main->setting.flag;
    }

    if (main->program.parameters.remaining.used) {
      main->setting.state.status = f_string_dynamics_increase_by(main->program.parameters.remaining.used, &main->setting.files);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        byte_dump_print_error(&main->program.error, macro_byte_dump_f(f_string_dynamics_increase_by));

        return;
      }

      f_status_t status_files = F_none;

      for (index = 0; index < main->program.parameters.remaining.used; ++index) {

        if (byte_dump_signal_check(main)) return;

        number = main->program.parameters.remaining.array[index];

        if (!main->program.parameters.arguments.array[number].used) continue;

        // Statically allocate the inner strings.
        main->setting.files.array[main->setting.files.used].string = main->program.parameters.arguments.array[number].string;
        main->setting.files.array[main->setting.files.used].used = main->program.parameters.arguments.array[number].used;
        main->setting.files.array[main->setting.files.used++].size = 0;

        main->setting.state.status = f_file_exists(main->program.parameters.arguments.array[number], F_true);

        if (main->setting.state.status == F_false) {
          main->setting.state.status = F_status_set_error(F_file_found_not);
        }

        if (F_status_is_error(main->setting.state.status)) {
          if (status_files == F_none) {
            if ((main->setting.flag & byte_dump_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            status_files = main->setting.state.status;
          }

          byte_dump_print_error_file(&main->program.error, macro_byte_dump_f(f_file_exists), main->program.parameters.arguments.array[number], f_file_operation_find_s, fll_error_file_type_file_e);
        }
      } // for

      if (status_files != F_none) {
        main->setting.state.status = F_status_set_error(status_files);
      }
    }
  }
#endif // _di_byte_dump_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
