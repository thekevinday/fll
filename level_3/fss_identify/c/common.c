#include "fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_program_version_
  const f_string_static_t fss_identify_program_version_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_program_version_s, 0, FSS_IDENTIFY_program_version_s_length);
#endif // _di_fss_identify_program_version_

#ifndef _di_fss_identify_program_name_
  const f_string_static_t fss_identify_program_name_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_program_name_s, 0, FSS_IDENTIFY_program_name_s_length);
  const f_string_static_t fss_identify_program_name_long_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_program_name_long_s, 0, FSS_IDENTIFY_program_name_long_s_length);
#endif // _di_fss_identify_program_name_

#ifndef _di_fss_identify_parameters_
  const f_string_static_t fss_identify_short_content_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_short_content_s, 0, FSS_IDENTIFY_short_content_s_length);
  const f_string_static_t fss_identify_short_line_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_short_line_s, 0, FSS_IDENTIFY_short_line_s_length);
  const f_string_static_t fss_identify_short_name_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_short_name_s, 0, FSS_IDENTIFY_short_name_s_length);
  const f_string_static_t fss_identify_short_object_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_short_object_s, 0, FSS_IDENTIFY_short_object_s_length);
  const f_string_static_t fss_identify_short_total_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_short_total_s, 0, FSS_IDENTIFY_short_total_s_length);

  const f_string_static_t fss_identify_long_content_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_long_content_s, 0, FSS_IDENTIFY_long_content_s_length);
  const f_string_static_t fss_identify_long_line_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_long_line_s, 0, FSS_IDENTIFY_long_line_s_length);
  const f_string_static_t fss_identify_long_name_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_long_name_s, 0, FSS_IDENTIFY_long_name_s_length);
  const f_string_static_t fss_identify_long_object_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_long_object_s, 0, FSS_IDENTIFY_long_object_s_length);
  const f_string_static_t fss_identify_long_total_s = macro_f_string_static_t_initialize(FSS_IDENTIFY_long_total_s, 0, FSS_IDENTIFY_long_total_s_length);
#endif // _di_fss_identify_parameters_

#ifndef _di_fss_identify_setting_delete_
  f_status_t fss_identify_setting_delete(fss_identify_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_fss_identify_setting_delete_

#ifndef _di_fss_identify_setting_load_
  void fss_identify_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_identify_setting_t * const setting) {

    if (!main || !setting) return;

    setting->flag = 0;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);

    if (F_status_is_error(setting->status)) {
      fss_identify_print_line_first_locked(setting, main->error);
      fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_process", F_true);
      fss_identify_print_line_last_locked(setting, main->error);

      return;
    }

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_identify_parameter_no_color_e, fss_identify_parameter_light_e, fss_identify_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          fss_identify_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);
          fss_identify_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[fss_identify_parameter_line_first_no_e].result & f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[fss_identify_parameter_line_last_no_e].result & f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_identify_parameter_verbosity_quiet_e, fss_identify_parameter_verbosity_error_e, fss_identify_parameter_verbosity_verbose_e, fss_identify_parameter_verbosity_debug_e, fss_identify_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          fss_identify_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);
          fss_identify_print_line_last_locked(setting, main->error);

          return;
        }
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->parameters.array[fss_identify_parameter_help_e].result & f_console_result_found_e) {
      setting->flag |= fss_identify_main_flag_help_e;

      return;
    }

    if (main->parameters.array[fss_identify_parameter_version_e].result & f_console_result_found_e) {
      setting->flag |= fss_identify_main_flag_version_e;

      return;
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[fss_identify_parameter_strip_invalid_e].result & f_console_result_found_e) {
      setting->flag |= fss_identify_main_flag_strip_invalid_e;
    }
  }
#endif // _di_fss_identify_setting_load_

#ifndef _di_fss_identify_setting_unload_
  f_status_t fss_identify_setting_unload(fll_program_data_t * const main, fss_identify_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    fss_identify_setting_delete(setting);

    return F_none;
  }
#endif // _di_fss_identify_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
