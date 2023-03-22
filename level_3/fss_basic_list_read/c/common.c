#include "fss_basic_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_program_version_s_
  const f_string_static_t fss_basic_list_read_program_version_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_program_version_s, 0, FSS_BASIC_LIST_READ_program_version_s_length);
#endif // _di_fss_basic_list_read_program_version_s_

#ifndef _di_fss_basic_list_read_program_name_s_
  const f_string_static_t fss_basic_list_read_program_name_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_program_name_s, 0, FSS_BASIC_LIST_READ_program_name_s_length);
  const f_string_static_t fss_basic_list_read_program_name_long_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_program_name_long_s, 0, FSS_BASIC_LIST_READ_program_name_long_s_length);
#endif // _di_fss_basic_list_read_program_name_s_

#ifndef _di_fss_basic_list_read_pipe_s_
  const f_string_static_t fss_basic_list_read_pipe_name_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_pipe_name_s, 0, FSS_BASIC_LIST_READ_pipe_name_s_length);

  const f_string_static_t fss_basic_list_read_pipe_content_end_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_pipe_content_end_s, 0, FSS_BASIC_LIST_READ_pipe_content_end_s_length);
  const f_string_static_t fss_basic_list_read_pipe_content_ignore_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_pipe_content_ignore_s, 0, FSS_BASIC_LIST_READ_pipe_content_ignore_s_length);
  const f_string_static_t fss_basic_list_read_pipe_content_start_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_pipe_content_start_s, 0, FSS_BASIC_LIST_READ_pipe_content_start_s_length);
#endif // _di_fss_basic_list_read_pipe_s_

#ifndef _di_fss_basic_list_read_parameter_d_
  const f_string_static_t fss_basic_list_read_short_at_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_at_s, 0, FSS_BASIC_LIST_READ_short_at_s_length);
  const f_string_static_t fss_basic_list_read_short_content_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_content_s, 0, FSS_BASIC_LIST_READ_short_content_s_length);
  const f_string_static_t fss_basic_list_read_short_columns_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_columns_s, 0, FSS_BASIC_LIST_READ_short_columns_s_length);
  const f_string_static_t fss_basic_list_read_short_delimit_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_delimit_s, 0, FSS_BASIC_LIST_READ_short_delimit_s_length);
  const f_string_static_t fss_basic_list_read_short_depth_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_depth_s, 0, FSS_BASIC_LIST_READ_short_depth_s_length);
  const f_string_static_t fss_basic_list_read_short_empty_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_empty_s, 0, FSS_BASIC_LIST_READ_short_empty_s_length);
  const f_string_static_t fss_basic_list_read_short_line_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_line_s, 0, FSS_BASIC_LIST_READ_short_line_s_length);
  const f_string_static_t fss_basic_list_read_short_name_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_name_s, 0, FSS_BASIC_LIST_READ_short_name_s_length);
  const f_string_static_t fss_basic_list_read_short_object_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_object_s, 0, FSS_BASIC_LIST_READ_short_object_s_length);
  const f_string_static_t fss_basic_list_read_short_pipe_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_pipe_s, 0, FSS_BASIC_LIST_READ_short_pipe_s_length);
  const f_string_static_t fss_basic_list_read_short_original_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_original_s, 0, FSS_BASIC_LIST_READ_short_original_s_length);
  const f_string_static_t fss_basic_list_read_short_select_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_select_s, 0, FSS_BASIC_LIST_READ_short_select_s_length);
  const f_string_static_t fss_basic_list_read_short_total_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_total_s, 0, FSS_BASIC_LIST_READ_short_total_s_length);
  const f_string_static_t fss_basic_list_read_short_trim_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_short_trim_s, 0, FSS_BASIC_LIST_READ_short_trim_s_length);

  const f_string_static_t fss_basic_list_read_long_at_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_at_s, 0, FSS_BASIC_LIST_READ_long_at_s_length);
  const f_string_static_t fss_basic_list_read_long_content_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_content_s, 0, FSS_BASIC_LIST_READ_long_content_s_length);
  const f_string_static_t fss_basic_list_read_long_columns_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_columns_s, 0, FSS_BASIC_LIST_READ_long_columns_s_length);
  const f_string_static_t fss_basic_list_read_long_delimit_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_delimit_s, 0, FSS_BASIC_LIST_READ_long_delimit_s_length);
  const f_string_static_t fss_basic_list_read_long_depth_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_depth_s, 0, FSS_BASIC_LIST_READ_long_depth_s_length);
  const f_string_static_t fss_basic_list_read_long_empty_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_empty_s, 0, FSS_BASIC_LIST_READ_long_empty_s_length);
  const f_string_static_t fss_basic_list_read_long_line_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_line_s, 0, FSS_BASIC_LIST_READ_long_line_s_length);
  const f_string_static_t fss_basic_list_read_long_name_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_name_s, 0, FSS_BASIC_LIST_READ_long_name_s_length);
  const f_string_static_t fss_basic_list_read_long_object_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_object_s, 0, FSS_BASIC_LIST_READ_long_object_s_length);
  const f_string_static_t fss_basic_list_read_long_pipe_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_pipe_s, 0, FSS_BASIC_LIST_READ_long_pipe_s_length);
  const f_string_static_t fss_basic_list_read_long_original_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_original_s, 0, FSS_BASIC_LIST_READ_long_original_s_length);
  const f_string_static_t fss_basic_list_read_long_select_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_select_s, 0, FSS_BASIC_LIST_READ_long_select_s_length);
  const f_string_static_t fss_basic_list_read_long_total_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_total_s, 0, FSS_BASIC_LIST_READ_long_total_s_length);
  const f_string_static_t fss_basic_list_read_long_trim_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_long_trim_s, 0, FSS_BASIC_LIST_READ_long_trim_s_length);
#endif // _di_fss_basic_list_read_parameter_d_

#ifndef _di_fss_basic_list_read_delimit_mode_s_
  const f_string_static_t fss_basic_list_read_delimit_mode_name_none_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_delimit_mode_name_none_s, 0, FSS_BASIC_LIST_READ_delimit_mode_name_none_s_length);
  const f_string_static_t fss_basic_list_read_delimit_mode_name_all_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_delimit_mode_name_all_s, 0, FSS_BASIC_LIST_READ_delimit_mode_name_all_s_length);
  const f_string_static_t fss_basic_list_read_delimit_mode_name_object_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_delimit_mode_name_object_s, 0, FSS_BASIC_LIST_READ_delimit_mode_name_object_s_length);
  const f_string_static_t fss_basic_list_read_delimit_mode_name_greater_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_delimit_mode_name_greater_s, 0, FSS_BASIC_LIST_READ_delimit_mode_name_greater_s_length);
  const f_string_static_t fss_basic_list_read_delimit_mode_name_lesser_s = macro_f_string_static_t_initialize(FSS_BASIC_LIST_READ_delimit_mode_name_lesser_s, 0, FSS_BASIC_LIST_READ_delimit_mode_name_lesser_s_length);
#endif // _di_fss_basic_list_read_delimit_mode_s_

#ifndef _di_fss_basic_list_read_setting_delete_
  f_status_t fss_basic_list_read_setting_delete(fss_basic_list_read_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_fss_basic_list_read_setting_delete_

#ifndef _di_fss_basic_list_read_setting_load_
  void fss_basic_list_read_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_basic_list_read_setting_t * const setting) {

    if (!main || !setting) return;

    setting->state.step_small = fss_basic_list_read_allocation_console_d;

    f_console_parameter_process(arguments, &main->parameters, &setting->state, 0);

    setting->state.step_small = fss_basic_list_read_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (main->parameters.array[fss_basic_list_read_parameter_line_first_no_e].result & f_console_result_found_e) {
      setting->flag -= setting->flag & fss_basic_list_read_main_flag_print_first_e;
    }
    else {
      setting->flag |= fss_basic_list_read_main_flag_print_first_e;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_line_last_no_e].result & f_console_result_found_e) {
      setting->flag -= setting->flag & fss_basic_list_read_main_flag_print_last_e;
    }
    else {
      setting->flag |= fss_basic_list_read_main_flag_print_last_e;
    }

    if (F_status_is_error(setting->state.status)) {
      fll_error_print(main->error, F_status_set_fine(setting->state.status), "f_console_parameter_process", fll_error_file_flag_fallback_e);

      if (main->error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->error);
      }

      return;
    }

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_basic_list_read_parameter_no_color_e, fss_basic_list_read_parameter_light_e, fss_basic_list_read_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(setting->state.status)) {
          fll_error_print(main->error, F_status_set_fine(setting->state.status), "fll_program_parameter_process_context", fll_error_file_flag_fallback_e);

          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->error);
          }

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_basic_list_read_parameter_verbosity_quiet_e, fss_basic_list_read_parameter_verbosity_error_e, fss_basic_list_read_parameter_verbosity_verbose_e, fss_basic_list_read_parameter_verbosity_debug_e, fss_basic_list_read_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(setting->state.status)) {
          fll_error_print(main->error, F_status_set_fine(setting->state.status), "fll_program_parameter_process_verbosity", fll_error_file_flag_fallback_e);

          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->error);
          }

          return;
        }
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->parameters.array[fss_basic_list_read_parameter_help_e].result & f_console_result_found_e) {
      setting->flag |= fss_basic_list_read_main_flag_help_e;

      return;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_version_e].result & f_console_result_found_e) {
      setting->flag |= fss_basic_list_read_main_flag_version_e;

      return;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_copyright_e].result & f_console_result_found_e) {
      setting->flag |= fss_basic_list_read_main_flag_copyright_e;

      return;
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[fss_basic_list_read_parameter_strip_invalid_e].result & f_console_result_found_e) {
      setting->flag |= fss_basic_list_read_main_flag_strip_invalid_e;
    }
  }
#endif // _di_fss_basic_list_read_setting_load_

#ifndef _di_fss_basic_list_read_setting_unload_
  f_status_t fss_basic_list_read_setting_unload(fss_basic_list_read_main_t * const main) {

    if (!main) return F_status_set_error(F_parameter);

    fss_basic_list_read_setting_delete(&main->setting);

    return F_none;
  }
#endif // _di_fss_basic_list_read_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
