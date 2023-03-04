#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_setting_delete_
  f_status_t status_code_setting_delete(status_code_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_status_code_setting_delete_

#ifndef _di_status_code_setting_load_
  void status_code_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, status_code_setting_t * const setting) {

    if (!main || !setting) return;

    setting->state.step_small = status_code_allocation_console_d;

    f_console_parameter_process(arguments, &main->parameters, &setting->state, 0);

    setting->state.step_small = status_code_allocation_small_d;

    if (F_status_is_error(setting->state.status)) {
      status_code_print_error(setting, main->error, macro_status_code_f(f_console_parameter_process));

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

        setting->state.status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->state.status)) {
          status_code_print_error(setting, main->error, macro_status_code_f(fll_program_parameter_process_context));

          return;
        }
      }

      if (main->parameters.array[status_code_parameter_line_first_no_e].result & f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[status_code_parameter_line_last_no_e].result & f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { status_code_parameter_verbosity_quiet_e, status_code_parameter_verbosity_error_e, status_code_parameter_verbosity_verbose_e, status_code_parameter_verbosity_debug_e, status_code_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->state.status)) {
          status_code_print_error(setting, main->error, macro_status_code_f(fll_program_parameter_process_verbosity));

          return;
        }
      }

      if (main->parameters.array[status_code_parameter_help_e].result & f_console_result_found_e) {
        setting->flag |= status_code_main_flag_help_e;

        return;
      }

      if (main->parameters.array[status_code_parameter_version_e].result & f_console_result_found_e) {
        setting->flag |= status_code_main_flag_version_e;

        return;
      }

      if (main->parameters.array[status_code_parameter_copyright_e].result & f_console_result_found_e) {
        setting->flag |= status_code_main_flag_copyright_e;

        return;
      }
    }

    if (main->parameters.array[status_code_parameter_error_e].result & f_console_result_found_e) {
      setting->flag |= status_code_main_flag_error_e;
    }

    if (main->parameters.array[status_code_parameter_fine_e].result & f_console_result_found_e) {
      setting->flag |= status_code_main_flag_fine_e;
    }

    if (main->parameters.array[status_code_parameter_warning_e].result & f_console_result_found_e) {
      setting->flag |= status_code_main_flag_warning_e;
    }

    if (main->parameters.array[status_code_parameter_number_e].result & f_console_result_found_e) {
      setting->flag |= status_code_main_flag_number_e;
    }

    if (setting->flag & status_code_main_flag_error_e) {
      if (setting->flag & status_code_main_flag_warning_e) {
        if (!(setting->flag & status_code_main_flag_number_e)) {
          setting->state.status = F_status_set_error(F_parameter);

          status_code_print_line_first(setting, main->message);
          status_code_print_error_cannot_error_warning_number(setting, main->error);

          return;
        }
      }

      if (setting->flag & status_code_main_flag_fine_e) {
        setting->state.status = F_status_set_error(F_parameter);

        status_code_print_line_first(setting, main->message);
        fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, status_code_long_error_s, status_code_long_fine_s);

        return;
      }
    }
    else if (setting->flag & status_code_main_flag_warning_e && setting->flag & status_code_main_flag_fine_e) {
      setting->state.status = F_status_set_error(F_parameter);

      status_code_print_line_first(setting, main->message);
      fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, status_code_long_warning_s, status_code_long_fine_s);

      return;
    }

    if (main->parameters.remaining.used == 0 && !(main->pipe & fll_program_data_pipe_input_e)) {
      setting->state.status = F_status_set_error(F_parameter);

      status_code_print_line_first(setting, main->message);
      status_code_print_error_no_status_codes(setting, main->error);

      return;
    }
  }
#endif // _di_status_code_setting_load_

#ifndef _di_status_code_setting_unload_
  f_status_t status_code_setting_unload(fll_program_data_t * const main, status_code_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    status_code_setting_delete(setting);

    return F_none;
  }
#endif // _di_status_code_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
