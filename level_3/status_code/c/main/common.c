#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_setting_load_
  void status_code_setting_load(const f_console_arguments_t arguments, status_code_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = status_code_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = status_code_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (main->program.parameters.array[status_code_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & status_code_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= status_code_main_flag_print_first_e;
    }

    if (main->program.parameters.array[status_code_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & status_code_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= status_code_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & status_code_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      status_code_print_error(&main->program.error, macro_status_code_f(f_console_parameter_process));

      return;
    }

    {
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { status_code_parameter_no_color_e, status_code_parameter_light_e, status_code_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        main->setting.state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & status_code_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          status_code_print_error(&main->program.error, macro_status_code_f(fll_program_parameter_process_context));

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { status_code_parameter_verbosity_quiet_e, status_code_parameter_verbosity_error_e, status_code_parameter_verbosity_verbose_e, status_code_parameter_verbosity_debug_e, status_code_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        main->setting.state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & status_code_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          status_code_print_error(&main->program.error, macro_status_code_f(fll_program_parameter_process_verbosity));

          return;
        }
      }

      if (main->program.parameters.array[status_code_parameter_help_e].result & f_console_result_found_e) {
        main->setting.flag |= status_code_main_flag_help_e;

        return;
      }

      if (main->program.parameters.array[status_code_parameter_version_e].result & f_console_result_found_e) {
        main->setting.flag |= status_code_main_flag_version_e;

        return;
      }

      if (main->program.parameters.array[status_code_parameter_copyright_e].result & f_console_result_found_e) {
        main->setting.flag |= status_code_main_flag_copyright_e;

        return;
      }
    }

    if (main->program.parameters.array[status_code_parameter_error_e].result & f_console_result_found_e) {
      main->setting.flag |= status_code_main_flag_error_e;
    }

    if (main->program.parameters.array[status_code_parameter_fine_e].result & f_console_result_found_e) {
      main->setting.flag |= status_code_main_flag_fine_e;
    }

    if (main->program.parameters.array[status_code_parameter_warning_e].result & f_console_result_found_e) {
      main->setting.flag |= status_code_main_flag_warning_e;
    }

    if (main->program.parameters.array[status_code_parameter_number_e].result & f_console_result_found_e) {
      main->setting.flag |= status_code_main_flag_number_e;
    }

    if (main->setting.flag & status_code_main_flag_error_e) {
      if (main->setting.flag & status_code_main_flag_warning_e) {
        if (!(main->setting.flag & status_code_main_flag_number_e)) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & status_code_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          status_code_print_error_cannot_error_warning_number(&main->program.error);

          return;
        }
      }

      if (main->setting.flag & status_code_main_flag_fine_e) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & status_code_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, status_code_long_error_s, status_code_long_fine_s);

        return;
      }
    }
    else if (main->setting.flag & status_code_main_flag_warning_e && main->setting.flag & status_code_main_flag_fine_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & status_code_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, status_code_long_warning_s, status_code_long_fine_s);

      return;
    }

    if (main->program.parameters.remaining.used == 0 && !(main->program.pipe & fll_program_data_pipe_input_e)) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & status_code_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      status_code_print_error_no_status_codes(&main->program.error);

      return;
    }
  }
#endif // _di_status_code_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
