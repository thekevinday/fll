#include "fss_embedded_list_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_write_program_version_
  const f_string_static_t fss_embedded_list_write_program_version_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_program_version_s, 0, FSS_EMBEDDED_LIST_WRITE_program_version_s_length);
#endif // _di_fss_embedded_list_write_program_version_

#ifndef _di_fss_embedded_list_write_program_name_
  const f_string_static_t fss_embedded_list_write_program_name_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_program_name_s, 0, FSS_EMBEDDED_LIST_WRITE_program_name_s_length);
  const f_string_static_t fss_embedded_list_write_program_name_long_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_program_name_long_s, 0, FSS_EMBEDDED_LIST_WRITE_program_name_long_s_length);
#endif // _di_fss_embedded_list_write_program_name_

#ifndef _di_fss_embedded_list_write_defines_
  const f_string_static_t fss_embedded_list_write_pipe_name_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_pipe_name_s, 0, FSS_EMBEDDED_LIST_WRITE_pipe_name_s_length);
  const f_string_static_t fss_embedded_list_write_pipe_content_end_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_pipe_content_end_s, 0, FSS_EMBEDDED_LIST_WRITE_pipe_content_end_s_length);
  const f_string_static_t fss_embedded_list_write_pipe_content_ignore_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_pipe_content_ignore_s, 0, FSS_EMBEDDED_LIST_WRITE_pipe_content_ignore_s_length);
  const f_string_static_t fss_embedded_list_write_pipe_content_start_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_pipe_content_start_s, 0, FSS_EMBEDDED_LIST_WRITE_pipe_content_start_s_length);
#endif // _di_fss_embedded_list_write_defines_

#ifndef _di_fss_embedded_list_write_parameters_
  const f_string_static_t fss_embedded_list_write_short_file_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_file_s, 0, FSS_EMBEDDED_LIST_WRITE_short_file_s_length);
  const f_string_static_t fss_embedded_list_write_short_content_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_content_s, 0, FSS_EMBEDDED_LIST_WRITE_short_content_s_length);
  const f_string_static_t fss_embedded_list_write_short_double_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_double_s, 0, FSS_EMBEDDED_LIST_WRITE_short_double_s_length);
  const f_string_static_t fss_embedded_list_write_short_ignore_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_ignore_s, 0, FSS_EMBEDDED_LIST_WRITE_short_ignore_s_length);
  const f_string_static_t fss_embedded_list_write_short_object_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_object_s, 0, FSS_EMBEDDED_LIST_WRITE_short_object_s_length);
  const f_string_static_t fss_embedded_list_write_short_partial_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_partial_s, 0, FSS_EMBEDDED_LIST_WRITE_short_partial_s_length);
  const f_string_static_t fss_embedded_list_write_short_prepend_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_prepend_s, 0, FSS_EMBEDDED_LIST_WRITE_short_prepend_s_length);
  const f_string_static_t fss_embedded_list_write_short_single_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_single_s, 0, FSS_EMBEDDED_LIST_WRITE_short_single_s_length);
  const f_string_static_t fss_embedded_list_write_short_trim_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_short_trim_s, 0, FSS_EMBEDDED_LIST_WRITE_short_trim_s_length);

  const f_string_static_t fss_embedded_list_write_long_file_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_file_s, 0, FSS_EMBEDDED_LIST_WRITE_long_file_s_length);
  const f_string_static_t fss_embedded_list_write_long_content_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_content_s, 0, FSS_EMBEDDED_LIST_WRITE_long_content_s_length);
  const f_string_static_t fss_embedded_list_write_long_double_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_double_s, 0, FSS_EMBEDDED_LIST_WRITE_long_double_s_length);
  const f_string_static_t fss_embedded_list_write_long_ignore_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_ignore_s, 0, FSS_EMBEDDED_LIST_WRITE_long_ignore_s_length);
  const f_string_static_t fss_embedded_list_write_long_object_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_object_s, 0, FSS_EMBEDDED_LIST_WRITE_long_object_s_length);
  const f_string_static_t fss_embedded_list_write_long_partial_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_partial_s, 0, FSS_EMBEDDED_LIST_WRITE_long_partial_s_length);
  const f_string_static_t fss_embedded_list_write_long_prepend_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_prepend_s, 0, FSS_EMBEDDED_LIST_WRITE_long_prepend_s_length);
  const f_string_static_t fss_embedded_list_write_long_single_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_single_s, 0, FSS_EMBEDDED_LIST_WRITE_long_single_s_length);
  const f_string_static_t fss_embedded_list_write_long_trim_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_long_trim_s, 0, FSS_EMBEDDED_LIST_WRITE_long_trim_s_length);
#endif // _di_fss_embedded_list_write_parameters_

#ifndef _di_fss_embedded_list_write_setting_delete_
  f_status_t fss_embedded_list_write_setting_delete(fss_embedded_list_write_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_fss_embedded_list_write_setting_delete_

#ifndef _di_fss_embedded_list_write_setting_load_
  void fss_embedded_list_write_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_embedded_list_write_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(setting->status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_embedded_list_write_parameter_no_color_e, fss_embedded_list_write_parameter_light_e, fss_embedded_list_write_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          fss_embedded_list_write_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);

          return;
        }
      }

      if (main->parameters.array[fss_embedded_list_write_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[fss_embedded_list_write_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_embedded_list_write_parameter_verbosity_quiet_e, fss_embedded_list_write_parameter_verbosity_error_e, fss_embedded_list_write_parameter_verbosity_verbose_e, fss_embedded_list_write_parameter_verbosity_debug_e, fss_embedded_list_write_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          fss_embedded_list_write_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);

          return;
        }
      }

      if (main->parameters.array[fss_embedded_list_write_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= fss_embedded_list_write_main_flag_help_e;

        return;
      }

      if (main->parameters.array[fss_embedded_list_write_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= fss_embedded_list_write_main_flag_version_e;

        return;
      }
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[fss_embedded_list_write_parameter_strip_invalid_e].result == f_console_result_found_e) {
      setting->flag |= fss_embedded_list_write_main_flag_strip_invalid_e;
    }
  }
#endif // _di_fss_embedded_list_write_setting_load_

#ifndef _di_fss_embedded_list_write_setting_unload_
  f_status_t fss_embedded_list_write_setting_unload(fll_program_data_t * const main, fss_embedded_list_write_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    fss_embedded_list_write_setting_delete(setting);

    return F_none;
  }
#endif // _di_fss_embedded_list_write_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
