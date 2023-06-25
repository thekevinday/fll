#include "fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_setting_load_
  void fss_identify_setting_load(const f_console_arguments_t arguments, fss_identify_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = fss_identify_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = fss_identify_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (main->program.parameters.array[fss_identify_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fss_identify_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= fss_identify_main_flag_print_first_e;
    }

    if (main->program.parameters.array[fss_identify_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fss_identify_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= fss_identify_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fss_identify_print_error(&main->program.error, macro_fss_identify_f(f_console_parameter_process));

      return;
    }

    {
      f_number_unsigned_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_identify_parameter_no_color_e, fss_identify_parameter_light_e, fss_identify_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        static const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        main->setting.state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_identify_print_error(&main->program.error, macro_fss_identify_f(fll_program_parameter_process_context));

          return;
        }
      }
    }

    if (main->program.parameters.array[fss_identify_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_identify_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[fss_identify_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_identify_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[fss_identify_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_identify_main_flag_copyright_e;

      return;
    }

    f_number_unsigned_t index = 0;

    if (main->program.parameters.array[fss_identify_parameter_content_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_identify_main_flag_content_e;
    }
    else {
      main->setting.flag -= main->setting.flag & fss_identify_main_flag_content_e;
    }

    if (main->program.parameters.array[fss_identify_parameter_object_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_identify_main_flag_object_e;
    }
    else {
      main->setting.flag -= main->setting.flag & fss_identify_main_flag_object_e;
    }

    if (main->program.parameters.array[fss_identify_parameter_total_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_identify_main_flag_total_e;
    }
    else {
      main->setting.flag -= main->setting.flag & fss_identify_main_flag_total_e;
    }

    if (main->program.parameters.array[fss_identify_parameter_line_e].result & f_console_result_value_e) {
      index = main->program.parameters.array[fss_identify_parameter_line_e].values.array[main->program.parameters.array[fss_identify_parameter_line_e].values.used - 1];

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &main->setting.line);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_integer_not(&main->program.error, f_console_symbol_long_normal_s, fss_identify_long_line_s, main->program.parameters.arguments.array[index]);

        return;
      }

      main->setting.flag |= fss_identify_main_flag_line_e;
    }
    else if (main->program.parameters.array[fss_identify_parameter_line_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, fss_identify_long_line_s);

      return;
    }
    else {
      main->setting.flag -= main->setting.flag & fss_identify_main_flag_line_e;
    }

    if (main->program.parameters.array[fss_identify_parameter_name_e].result & f_console_result_value_e) {
      main->setting.names.used = 0;

      main->setting.state.status = f_string_dynamics_increase_by(main->program.parameters.array[fss_identify_parameter_name_e].values.used, &main->setting.names);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fss_identify_print_error(&main->program.error, macro_fss_identify_f(f_string_dynamics_increase_by));

        return;
      }

      main->setting.names.used = main->program.parameters.array[fss_identify_parameter_name_e].values.used;

      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;
      f_status_t status = F_none;

      for (; i < main->setting.names.used; ++i) {

        if (fss_identify_signal_check(main)) return;

        index = main->program.parameters.array[fss_identify_parameter_name_e].values.array[i];
        main->setting.names.array[i].used = 0;

        main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[index], &main->setting.names.array[i]);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_identify_print_error(&main->program.error, macro_fss_identify_f(f_string_dynamic_append_nulless));

          break;
        }

        if (main->setting.names.array[i].used) {
          for (j = 0; j < main->setting.names.array[i].used; ++j) {

            if (fss_identify_signal_check(main)) return;

            main->setting.state.status = f_utf_is_word_dash(main->setting.names.array[i].string + j, main->setting.names.array[i].used, F_true);

            if (F_status_is_error(main->setting.state.status)) {
              if (F_status_is_error_not(main->setting.state.status)) {
                if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                  fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                }
              }

              fss_identify_print_error(&main->program.error, macro_fss_identify_f(f_utf_is_word_dash));

              return;
            }

            if (main->setting.state.status == F_false) {
              main->setting.state.status = F_status_set_error(F_parameter);

              if (F_status_is_error_not(main->setting.state.status)) {
                status = F_status_set_error(F_parameter);

                if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                  fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                }
              }

              fss_identify_print_error_parameter_file_name_invalid(&main->program.error, index, main->setting.names.array[i]);

              break;
            }
          } // for
        }
        else {
          if (F_status_is_error_not(main->setting.state.status)) {
            status = F_status_set_error(F_parameter);

            if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }
          }

          fss_identify_print_error_parameter_file_name_empty(&main->program.error, index);
        }
      } // for

      if (F_status_is_error(main->setting.state.status)) return;

      if (F_status_is_error(status)) {
        main->setting.state.status = status;

        return;
      }

      main->setting.flag |= fss_identify_main_flag_name_e;
    }
    else if (main->program.parameters.array[fss_identify_parameter_name_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, fss_identify_long_name_s);

      return;
    }
    else {
      main->setting.flag -= main->setting.flag & fss_identify_parameter_name_e;
    }

    if (main->program.parameters.remaining.used) {
      main->setting.files.used = 0;

      main->setting.state.status = f_string_dynamics_increase_by(main->program.parameters.remaining.used, &main->setting.files);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fss_identify_print_error(&main->program.error, macro_fss_identify_f(f_string_dynamics_increase_by));

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_number_unsigned_t index = 0; main->setting.files.used < main->program.parameters.remaining.used; ) {

        if (fss_identify_signal_check(main)) return;

        index = main->program.parameters.remaining.array[main->setting.files.used];

        main->setting.files.array[main->setting.files.used].string = main->program.parameters.arguments.array[index].string;
        main->setting.files.array[main->setting.files.used].used = main->program.parameters.arguments.array[index].used;
        main->setting.files.array[main->setting.files.used++].size = 0;
      } // for

      main->setting.flag |= fss_identify_main_flag_file_from_e;
    }
    else {
      main->setting.flag -= main->setting.flag & fss_identify_main_flag_file_from_e;
    }

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      main->setting.flag |= fss_identify_main_flag_pipe_e;
    }
    else {
      main->setting.flag -= main->setting.flag & fss_identify_main_flag_pipe_e;
    }

    if (!(main->setting.flag & fss_identify_main_flag_pipe_e | fss_identify_main_flag_file_from_e)) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fss_identify_print_error_no_from(&main->program.error);

      return;
    }

    // Default to both Object and Content when neither are specified.
    if (!(main->setting.flag & (fss_identify_main_flag_object_e | fss_identify_main_flag_content_e | fss_identify_main_flag_total_e))) {
      main->setting.flag |= fss_identify_main_flag_object_e;
      main->setting.flag |= fss_identify_main_flag_content_e;
    }

    if (main->setting.flag & fss_identify_main_flag_total_e) {
      if (main->setting.flag & (fss_identify_main_flag_content_e | fss_identify_main_flag_object_e)) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & fss_identify_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, main->setting.flag & fss_identify_main_flag_content_e ? fss_identify_long_content_s : fss_identify_long_object_s, fss_identify_long_total_s);
        }
      }
    }
  }
#endif // _di_fss_identify_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
