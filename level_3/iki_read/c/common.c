#include "iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_program_version_
  const f_string_static_t iki_read_program_version_s = macro_f_string_static_t_initialize(IKI_READ_program_version_s, 0, IKI_READ_program_version_s_length);
#endif // _di_iki_read_program_version_

#ifndef _di_iki_read_program_name_
  const f_string_static_t iki_read_program_name_s = macro_f_string_static_t_initialize(IKI_READ_program_name_s, 0, IKI_READ_program_name_s_length);
  const f_string_static_t iki_read_program_name_long_s = macro_f_string_static_t_initialize(IKI_READ_program_name_long_s, 0, IKI_READ_program_name_long_s_length);
#endif // _di_iki_read_program_name_

#ifndef _di_iki_read_parameters_
  const f_string_static_t iki_read_short_at_s = macro_f_string_static_t_initialize(IKI_READ_short_at_s, 0, IKI_READ_short_at_s_length);
  const f_string_static_t iki_read_short_content_s = macro_f_string_static_t_initialize(IKI_READ_short_content_s, 0, IKI_READ_short_content_s_length);
  const f_string_static_t iki_read_short_line_s = macro_f_string_static_t_initialize(IKI_READ_short_line_s, 0, IKI_READ_short_line_s_length);
  const f_string_static_t iki_read_short_literal_s = macro_f_string_static_t_initialize(IKI_READ_short_literal_s, 0, IKI_READ_short_literal_s_length);
  const f_string_static_t iki_read_short_name_s = macro_f_string_static_t_initialize(IKI_READ_short_name_s, 0, IKI_READ_short_name_s_length);
  const f_string_static_t iki_read_short_object_s = macro_f_string_static_t_initialize(IKI_READ_short_object_s, 0, IKI_READ_short_object_s_length);
  const f_string_static_t iki_read_short_replace_s = macro_f_string_static_t_initialize(IKI_READ_short_replace_s, 0, IKI_READ_short_replace_s_length);
  const f_string_static_t iki_read_short_substitute_s = macro_f_string_static_t_initialize(IKI_READ_short_substitute_s, 0, IKI_READ_short_substitute_s_length);
  const f_string_static_t iki_read_short_total_s = macro_f_string_static_t_initialize(IKI_READ_short_total_s, 0, IKI_READ_short_total_s_length);
  const f_string_static_t iki_read_short_whole_s = macro_f_string_static_t_initialize(IKI_READ_short_whole_s, 0, IKI_READ_short_whole_s_length);
  const f_string_static_t iki_read_short_wrap_s = macro_f_string_static_t_initialize(IKI_READ_short_wrap_s, 0, IKI_READ_short_wrap_s_length);

  const f_string_static_t iki_read_long_at_s = macro_f_string_static_t_initialize(IKI_READ_long_at_s, 0, IKI_READ_long_at_s_length);
  const f_string_static_t iki_read_long_content_s = macro_f_string_static_t_initialize(IKI_READ_long_content_s, 0, IKI_READ_long_content_s_length);
  const f_string_static_t iki_read_long_line_s = macro_f_string_static_t_initialize(IKI_READ_long_line_s, 0, IKI_READ_long_line_s_length);
  const f_string_static_t iki_read_long_literal_s = macro_f_string_static_t_initialize(IKI_READ_long_literal_s, 0, IKI_READ_long_literal_s_length);
  const f_string_static_t iki_read_long_name_s = macro_f_string_static_t_initialize(IKI_READ_long_name_s, 0, IKI_READ_long_name_s_length);
  const f_string_static_t iki_read_long_object_s = macro_f_string_static_t_initialize(IKI_READ_long_object_s, 0, IKI_READ_long_object_s_length);
  const f_string_static_t iki_read_long_replace_s = macro_f_string_static_t_initialize(IKI_READ_long_replace_s, 0, IKI_READ_long_replace_s_length);
  const f_string_static_t iki_read_long_substitute_s = macro_f_string_static_t_initialize(IKI_READ_long_substitute_s, 0, IKI_READ_long_substitute_s_length);
  const f_string_static_t iki_read_long_total_s = macro_f_string_static_t_initialize(IKI_READ_long_total_s, 0, IKI_READ_long_total_s_length);
  const f_string_static_t iki_read_long_whole_s = macro_f_string_static_t_initialize(IKI_READ_long_whole_s, 0, IKI_READ_long_whole_s_length);
  const f_string_static_t iki_read_long_wrap_s = macro_f_string_static_t_initialize(IKI_READ_long_wrap_s, 0, IKI_READ_long_wrap_s_length);
#endif // _di_iki_read_parameters_

#ifndef _di_iki_read_substitution_t_
  const f_string_static_t iki_read_substitution_after_s = macro_f_string_static_t_initialize(IKI_READ_substitution_after_s, 0, IKI_READ_substitution_after_s_length);
  const f_string_static_t iki_read_substitution_before_s = macro_f_string_static_t_initialize(IKI_READ_substitution_before_s, 0, IKI_READ_substitution_before_s_length);
  const f_string_static_t iki_read_substitution_replace_s = macro_f_string_static_t_initialize(IKI_READ_substitution_replace_s, 0, IKI_READ_substitution_replace_s_length);
  const f_string_static_t iki_read_substitution_vocabulary_s = macro_f_string_static_t_initialize(IKI_READ_substitution_vocabulary_s, 0, IKI_READ_substitution_vocabulary_s_length);
  const f_string_static_t iki_read_substitution_with_s = macro_f_string_static_t_initialize(IKI_READ_substitution_with_s, 0, IKI_READ_substitution_with_s_length);
#endif // _di_iki_read_substitution_t_

#ifndef _di_iki_read_setting_delete_
  f_status_t iki_read_setting_delete(iki_read_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_iki_read_setting_delete_

#ifndef _di_iki_read_setting_load_
  void iki_read_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, iki_read_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(setting->status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { iki_read_parameter_no_color_e, iki_read_parameter_light_e, iki_read_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          iki_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[iki_read_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[iki_read_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { iki_read_parameter_verbosity_quiet_e, iki_read_parameter_verbosity_error_e, iki_read_parameter_verbosity_verbose_e, iki_read_parameter_verbosity_debug_e, iki_read_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          iki_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[iki_read_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= iki_read_main_flag_help_e;

        return;
      }

      if (main->parameters.array[iki_read_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= iki_read_main_flag_version_e;

        return;
      }
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (!(main->parameters.remaining.used || (main->pipe & fll_program_data_pipe_input_e)) {
      setting->status = F_status_set_error(F_parameter);

      iki_read_print_line_first_locked(setting, main->error);
      fll_program_print_error_missing_file(main->error);
      iki_read_print_line_last_locked(setting, main->error);

      return;
    }

    //if (main->parameters.array[iki_read_parameter_strip_invalid_e].result == f_console_result_found_e) {
    //  setting->flag |= iki_read_main_flag_strip_invalid_e;
    //}
  }
#endif // _di_iki_read_setting_load_

#ifndef _di_iki_read_setting_unload_
  f_status_t iki_read_setting_unload(fll_program_data_t * const main, iki_read_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    iki_read_setting_delete(setting);

    return F_none;
  }
#endif // _di_iki_read_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
