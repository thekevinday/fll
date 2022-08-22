#include "fss_payload_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_write_defines_
  const f_string_static_t fss_payload_write_pipe_content_end_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_pipe_content_end_s, 0, FSS_PAYLOAD_WRITE_pipe_content_end_s_length);
  const f_string_static_t fss_payload_write_pipe_content_ignore_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_pipe_content_ignore_s, 0, FSS_PAYLOAD_WRITE_pipe_content_ignore_s_length);
  const f_string_static_t fss_payload_write_pipe_content_start_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_pipe_content_start_s, 0, FSS_PAYLOAD_WRITE_pipe_content_start_s_length);
#endif // _di_fss_payload_write_defines_

#ifndef _di_fss_payload_write_parameters_
  const f_string_static_t fss_payload_write_short_file_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_file_s, 0, FSS_PAYLOAD_WRITE_short_file_s_length);
  const f_string_static_t fss_payload_write_short_content_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_content_s, 0, FSS_PAYLOAD_WRITE_short_content_s_length);
  const f_string_static_t fss_payload_write_short_double_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_double_s, 0, FSS_PAYLOAD_WRITE_short_double_s_length);
  const f_string_static_t fss_payload_write_short_ignore_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_ignore_s, 0, FSS_PAYLOAD_WRITE_short_ignore_s_length);
  const f_string_static_t fss_payload_write_short_object_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_object_s, 0, FSS_PAYLOAD_WRITE_short_object_s_length);
  const f_string_static_t fss_payload_write_short_partial_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_partial_s, 0, FSS_PAYLOAD_WRITE_short_partial_s_length);
  const f_string_static_t fss_payload_write_short_prepend_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_prepend_s, 0, FSS_PAYLOAD_WRITE_short_prepend_s_length);
  const f_string_static_t fss_payload_write_short_single_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_single_s, 0, FSS_PAYLOAD_WRITE_short_single_s_length);
  const f_string_static_t fss_payload_write_short_trim_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_short_trim_s, 0, FSS_PAYLOAD_WRITE_short_trim_s_length);

  const f_string_static_t fss_payload_write_long_file_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_file_s, 0, FSS_PAYLOAD_WRITE_long_file_s_length);
  const f_string_static_t fss_payload_write_long_content_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_content_s, 0, FSS_PAYLOAD_WRITE_long_content_s_length);
  const f_string_static_t fss_payload_write_long_double_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_double_s, 0, FSS_PAYLOAD_WRITE_long_double_s_length);
  const f_string_static_t fss_payload_write_long_ignore_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_ignore_s, 0, FSS_PAYLOAD_WRITE_long_ignore_s_length);
  const f_string_static_t fss_payload_write_long_object_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_object_s, 0, FSS_PAYLOAD_WRITE_long_object_s_length);
  const f_string_static_t fss_payload_write_long_partial_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_partial_s, 0, FSS_PAYLOAD_WRITE_long_partial_s_length);
  const f_string_static_t fss_payload_write_long_prepend_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_prepend_s, 0, FSS_PAYLOAD_WRITE_long_prepend_s_length);
  const f_string_static_t fss_payload_write_long_single_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_single_s, 0, FSS_PAYLOAD_WRITE_long_single_s_length);
  const f_string_static_t fss_payload_write_long_trim_s = macro_f_string_static_t_initialize(FSS_PAYLOAD_WRITE_long_trim_s, 0, FSS_PAYLOAD_WRITE_long_trim_s_length);
#endif // _di_fss_payload_write_parameters_

#ifndef _di_fss_payload_write_setting_delete_
  f_status_t fss_payload_write_setting_delete(fss_payload_write_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_fss_payload_write_setting_delete_

#ifndef _di_fss_payload_write_setting_load_
  void fss_payload_write_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_payload_write_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(setting->status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_payload_write_parameter_no_color_e, fss_payload_write_parameter_light_e, fss_payload_write_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          fss_payload_write_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);

          return;
        }
      }

      if (main->parameters.array[fss_payload_write_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[fss_payload_write_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_payload_write_parameter_verbosity_quiet_e, fss_payload_write_parameter_verbosity_error_e, fss_payload_write_parameter_verbosity_verbose_e, fss_payload_write_parameter_verbosity_debug_e, fss_payload_write_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          fss_payload_write_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);

          return;
        }
      }

      if (main->parameters.array[fss_payload_write_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= fss_payload_write_main_flag_help_e;

        return;
      }

      if (main->parameters.array[fss_payload_write_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= fss_payload_write_main_flag_version_e;

        return;
      }

      // Identify and prioritize "from" mode parameters.
      {
        uint16_t choices_array[2] = { fss_payload_write_parameter_from_bytesequence_e, fss_payload_write_parameter_from_codepoint_e };
        choices.array = choices_array;
        choices.used = 2;

        setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

        if (F_status_is_error(setting->status)) {
          fss_payload_write_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_prioritize_right", F_true);

          return;
        }

        if (choices.array[choice] == fss_payload_write_parameter_from_bytesequence_e) {
          if (setting->mode & fss_payload_write_mode_from_codepoint_e) {
            setting->mode -= fss_payload_write_mode_from_codepoint_e;
          }

          setting->mode |= fss_payload_write_mode_from_bytesequence_e;
        }
        else if (choices.array[choice] == fss_payload_write_parameter_from_codepoint_e) {
          if (setting->mode & fss_payload_write_mode_from_bytesequence_e) {
            setting->mode -= fss_payload_write_mode_from_bytesequence_e;
          }

          setting->mode |= fss_payload_write_mode_from_codepoint_e;
        }
      }

      // Identify and prioritize "to" mode parameters.
      {
        uint16_t choices_array[4] = { fss_payload_write_parameter_to_bytesequence_e, fss_payload_write_parameter_to_codepoint_e, fss_payload_write_parameter_to_combining_e, fss_payload_write_parameter_to_width_e };
        choices.array = choices_array;
        choices.used = 4;
        choice = 1;

        setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

        if (F_status_is_error(setting->status)) {
          fss_payload_write_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_prioritize_right", F_true);

          return;
        }

        if (choices.array[choice] == fss_payload_write_parameter_to_bytesequence_e) {
          if (setting->mode & fss_payload_write_mode_to_codepoint_e) {
            setting->mode -= fss_payload_write_mode_to_codepoint_e;
          }

          if (setting->mode & fss_payload_write_mode_to_combining_e) {
            setting->mode -= fss_payload_write_mode_to_combining_e;
          }

          if (setting->mode & fss_payload_write_mode_to_width_e) {
            setting->mode -= fss_payload_write_mode_to_width_e;
          }

          setting->mode |= fss_payload_write_mode_to_bytesequence_e;
        }
        else if (choices.array[choice] == fss_payload_write_parameter_to_codepoint_e) {
          if (setting->mode & fss_payload_write_mode_to_bytesequence_e) {
            setting->mode -= fss_payload_write_mode_to_bytesequence_e;
          }

          if (setting->mode & fss_payload_write_mode_to_combining_e) {
            setting->mode -= fss_payload_write_mode_to_combining_e;
          }

          if (setting->mode & fss_payload_write_mode_to_width_e) {
            setting->mode -= fss_payload_write_mode_to_width_e;
          }

          setting->mode |= fss_payload_write_mode_to_codepoint_e;
        }
        else if (choices.array[choice] == fss_payload_write_parameter_to_combining_e) {
          if (setting->mode & fss_payload_write_mode_to_bytesequence_e) {
            setting->mode -= fss_payload_write_mode_to_bytesequence_e;
          }

          if (setting->mode & fss_payload_write_mode_to_codepoint_e) {
            setting->mode -= fss_payload_write_mode_to_codepoint_e;
          }

          // --to_width may be specified with --to_combining.
          if (main->parameters.array[fss_payload_write_parameter_to_width_e].result == f_console_result_found_e) {
            setting->mode |= fss_payload_write_mode_to_width_e;
          }

          setting->mode |= fss_payload_write_mode_to_combining_e;
        }
        else if (choices.array[choice] == fss_payload_write_parameter_to_width_e) {
          if (setting->mode & fss_payload_write_mode_to_bytesequence_e) {
            setting->mode -= fss_payload_write_mode_to_bytesequence_e;
          }

          if (setting->mode & fss_payload_write_mode_to_codepoint_e) {
            setting->mode -= fss_payload_write_mode_to_codepoint_e;
          }

          // --to_width may be specified with --to_combining.
          if (main->parameters.array[fss_payload_write_parameter_to_combining_e].result == f_console_result_found_e) {
            setting->mode |= fss_payload_write_mode_to_combining_e;
          }

          setting->mode |= fss_payload_write_mode_to_width_e;
        }
      }
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[fss_payload_write_parameter_to_file_e].result == f_console_result_additional_e) {
      if (main->parameters.array[fss_payload_write_parameter_to_file_e].values.used > 1) {
        fss_payload_write_print_error_parameter_file_to_too_many(main, setting);

        setting->status = F_status_set_error(F_parameter);

        return;
      }

      if (args[main->parameters.array[fss_payload_write_parameter_to_file_e].values.array[0]].used) {
        setting->path_files_to.used = 0;

        setting->status = f_string_dynamics_increase_by(1, &setting->path_files_to);
        if (F_status_is_error(setting->status)) return;

        setting->path_files_to.array[setting->path_files_to.used].used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[main->parameters.array[fss_payload_write_parameter_to_file_e].values.array[0]], &setting->path_files_to.array[0]);
        if (F_status_is_error(setting->status)) return;

        ++setting->path_files_to.used;

        setting->status = f_file_stream_open(args[main->parameters.array[fss_payload_write_parameter_to_file_e].values.array[0]], f_file_open_mode_append_s, &main->output.to);

        if (F_status_is_error(setting->status)) {
          fll_error_file_print(main->error, F_status_set_fine(setting->status), "f_file_stream_open", F_true, args[main->parameters.array[fss_payload_write_parameter_to_file_e].values.array[0]], f_file_operation_open_s, fll_error_file_type_file_e);

          return;
        }

        setting->flag |= fss_payload_write_main_flag_file_to_e;
      }
      else {
        fss_payload_write_print_error_parameter_file_name_empty(main, setting, main->parameters.array[fss_payload_write_parameter_to_file_e].values.array[0]);

        setting->status = F_status_set_error(F_parameter);

        return;
      }
    }
    else if (main->parameters.array[fss_payload_write_parameter_to_file_e].result == f_console_result_found_e) {
      fss_payload_write_print_error_no_value(main, setting, fss_payload_write_long_to_file_s);

      setting->status = F_status_set_error(F_parameter);

      return;
    }
    else {
      main->output.to = main->message.to;

      if (setting->flag & fss_payload_write_main_flag_file_to_e) {
        setting->flag -= fss_payload_write_main_flag_file_to_e;
      }
    }

    if (main->parameters.array[fss_payload_write_parameter_from_file_e].result == f_console_result_additional_e) {
      setting->path_files_from.used = 0;

      setting->status = f_string_dynamics_increase_by(main->parameters.array[fss_payload_write_parameter_from_file_e].values.used, &setting->path_files_from);
      if (F_status_is_error(setting->status)) return;

      setting->path_files_from.used = main->parameters.array[fss_payload_write_parameter_from_file_e].values.used;

      f_array_length_t i = 0;
      f_array_length_t index = 0;

      for (; i < setting->path_files_from.used; ++i) {

        index = main->parameters.array[fss_payload_write_parameter_from_file_e].values.array[i];
        setting->path_files_from.array[i].used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &setting->path_files_from.array[i]);
        if (F_status_is_error(setting->status)) return;

        if (args[index].used) {
          if (f_file_exists(args[index], F_true) != F_true) {
            fss_payload_write_print_error_parameter_file_not_found(main, setting, F_true, args[index]);

            if (F_status_is_error_not(setting->status)) {
              setting->status = F_status_set_error(F_file_found_not);
            }
          }
        }
        else {
          fss_payload_write_print_error_parameter_file_name_empty(main, setting, index);

          if (F_status_is_error_not(setting->status)) {
            setting->status = F_status_set_error(F_parameter);
          }
        }
      } // for

      if (F_status_is_error(setting->status)) return;

      setting->flag |= fss_payload_write_main_flag_file_from_e;
    }
    else if (main->parameters.array[fss_payload_write_parameter_from_file_e].result == f_console_result_found_e) {
      fss_payload_write_print_error_no_value(main, setting, fss_payload_write_long_from_file_s);

      setting->status = F_status_set_error(F_parameter);

      return;
    }
    else {
      if (setting->flag & fss_payload_write_main_flag_file_from_e) {
        setting->flag -= fss_payload_write_main_flag_file_from_e;
      }
    }

    if (F_status_is_error(setting->status)) return;

    if (main->parameters.array[fss_payload_write_parameter_from_file_e].result == f_console_result_none_e && !((main->pipe & fll_program_data_pipe_input_e) || main->parameters.remaining.used)) {
      fss_payload_write_print_error_no_from(main, setting);

      setting->status = F_status_set_error(F_parameter);
    }

    if (!(setting->mode & fss_payload_write_mode_to_bytesequence_e)) {
      if (main->parameters.array[fss_payload_write_parameter_separate_e].result == f_console_result_found_e || main->parameters.array[fss_payload_write_parameter_headers_e].result == f_console_result_found_e) {
        setting->prepend = fss_payload_write_string_prepend_padding_s;
        setting->append = f_string_eol_s;
      }
      else {
        setting->prepend = f_string_space_s;
      }
    }

    if (main->parameters.array[fss_payload_write_parameter_headers_e].result == f_console_result_found_e) {
      setting->flag |= fss_payload_write_main_flag_header_e;
    }

    if (main->parameters.array[fss_payload_write_parameter_separate_e].result == f_console_result_found_e) {
      setting->flag |= fss_payload_write_main_flag_separate_e;
    }

    if (main->parameters.array[fss_payload_write_parameter_strip_invalid_e].result == f_console_result_found_e) {
      setting->flag |= fss_payload_write_main_flag_strip_invalid_e;
    }

    setting->valid_not = main->message.set->error;
  }
#endif // _di_fss_payload_write_setting_load_

#ifndef _di_fss_payload_write_setting_unload_
  f_status_t fss_payload_write_setting_unload(fll_program_data_t * const main, fss_payload_write_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    fss_payload_write_setting_delete(setting);

    return F_none;
  }
#endif // _di_fss_payload_write_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
