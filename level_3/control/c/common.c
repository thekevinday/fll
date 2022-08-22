#include "control.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_program_version_
  const f_string_static_t control_program_version_s = macro_f_string_static_t_initialize(CONTROL_program_version_s, 0, CONTROL_program_version_s_length);
#endif // _di_control_program_version_

#ifndef _di_control_program_name_
  const f_string_static_t control_program_name_s = macro_f_string_static_t_initialize(CONTROL_program_name_s, 0, CONTROL_program_name_s_length);
  const f_string_static_t control_program_name_long_s = macro_f_string_static_t_initialize(CONTROL_program_name_long_s, 0, CONTROL_program_name_long_s_length);
#endif // _di_control_program_name_

#ifndef _di_control_parameters_
  const f_string_static_t control_short_name_s = macro_f_string_static_t_initialize(CONTROL_short_name_s, 0, CONTROL_short_name_s_length);
  const f_string_static_t control_short_return_s = macro_f_string_static_t_initialize(CONTROL_short_return_s, 0, CONTROL_short_return_s_length);
  const f_string_static_t control_short_settings_s = macro_f_string_static_t_initialize(CONTROL_short_settings_s, 0, CONTROL_short_settings_s_length);
  const f_string_static_t control_short_socket_s = macro_f_string_static_t_initialize(CONTROL_short_socket_s, 0, CONTROL_short_socket_s_length);

  const f_string_static_t control_long_name_s = macro_f_string_static_t_initialize(CONTROL_long_name_s, 0, CONTROL_long_name_s_length);
  const f_string_static_t control_long_return_s = macro_f_string_static_t_initialize(CONTROL_long_return_s, 0, CONTROL_long_return_s_length);
  const f_string_static_t control_long_settings_s = macro_f_string_static_t_initialize(CONTROL_long_settings_s, 0, CONTROL_long_settings_s_length);
  const f_string_static_t control_long_socket_s = macro_f_string_static_t_initialize(CONTROL_long_socket_s, 0, CONTROL_long_socket_s_length);
#endif // _di_control_parameters_

#ifndef _di_control_action_type_identify_
  uint8_t control_action_type_identify(const f_string_static_t action) {

    if (fl_string_dynamic_compare(action, control_freeze_s) == F_equal_to) {
      return control_action_type_freeze_e;
    }

    if (fl_string_dynamic_compare(action, control_kexec_s) == F_equal_to) {
      return control_action_type_kexec_e;
    }

    if (fl_string_dynamic_compare(action, control_kill_s) == F_equal_to) {
      return control_action_type_kill_e;
    }

    if (fl_string_dynamic_compare(action, control_pause_s) == F_equal_to) {
      return control_action_type_pause_e;
    }

    if (fl_string_dynamic_compare(action, control_reboot_s) == F_equal_to) {
      return control_action_type_reboot_e;
    }

    if (fl_string_dynamic_compare(action, control_reload_s) == F_equal_to) {
      return control_action_type_reload_e;
    }

    if (fl_string_dynamic_compare(action, control_rerun_s) == F_equal_to) {
      return control_action_type_rerun_e;
    }

    if (fl_string_dynamic_compare(action, control_restart_s) == F_equal_to) {
      return control_action_type_restart_e;
    }

    if (fl_string_dynamic_compare(action, control_resume_s) == F_equal_to) {
      return control_action_type_resume_e;
    }

    if (fl_string_dynamic_compare(action, control_shutdown_s) == F_equal_to) {
      return control_action_type_shutdown_e;
    }

    if (fl_string_dynamic_compare(action, control_start_s) == F_equal_to) {
      return control_action_type_start_e;
    }

    if (fl_string_dynamic_compare(action, control_stop_s) == F_equal_to) {
      return control_action_type_stop_e;
    }

    if (fl_string_dynamic_compare(action, control_thaw_s) == F_equal_to) {
      return control_action_type_thaw_e;
    }

    return 0;
  }
#endif // _di_control_action_type_identify_

#ifndef _di_control_action_type_name_
  f_string_static_t control_action_type_name(const uint8_t type) {

    switch (type) {
      case control_action_type_freeze_e:
        return control_freeze_s;

      case control_action_type_kexec_e:
        return control_kexec_s;

      case control_action_type_kill_e:
        return control_kill_s;

      case control_action_type_pause_e:
        return control_pause_s;

      case control_action_type_reboot_e:
        return control_reboot_s;

      case control_action_type_reload_e:
        return control_reload_s;

      case control_action_type_rerun_e:
        return control_rerun_s;

      case control_action_type_restart_e:
        return control_restart_s;

      case control_action_type_resume_e:
        return control_resume_s;

      case control_action_type_shutdown_e:
        return control_shutdown_s;

      case control_action_type_start_e:
        return control_start_s;

      case control_action_type_stop_e:
        return control_stop_s;

      case control_action_type_thaw_e:
        return control_thaw_s;
    }

    return f_string_empty_s;
  }
#endif // _di_control_action_type_name_

#ifndef _di_control_payload_type_identify_
  uint8_t control_payload_type_identify(const f_string_static_t payload) {

    if (fl_string_dynamic_compare(payload, control_controller_s) == F_equal_to) {
      return control_payload_type_controller_e;
    }

    if (fl_string_dynamic_compare(payload, control_error_s) == F_equal_to) {
      return control_payload_type_error_e;
    }

    if (fl_string_dynamic_compare(payload, control_init_s) == F_equal_to) {
      return control_payload_type_init_e;
    }

    return 0;
  }
#endif // _di_control_payload_type_identify_

#ifndef _di_control_payload_type_name_
  f_string_static_t control_payload_type_name(const uint8_t type) {

    switch (type) {
      case control_payload_type_controller_e:
        return control_controller_s;

      case control_payload_type_error_e:
        return control_error_s;

      case control_payload_type_init_e:
        return control_init_s;
    }

    return f_string_empty_s;
  }
#endif // _di_control_payload_type_name_

#ifndef _di_control_setting_delete_
  f_status_t control_setting_delete(control_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_control_setting_delete_

#ifndef _di_control_setting_load_
  void control_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, control_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(setting->status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { control_parameter_no_color_e, control_parameter_light_e, control_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          control_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);

          return;
        }
      }

      if (main->parameters.array[control_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[control_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { control_parameter_verbosity_quiet_e, control_parameter_verbosity_error_e, control_parameter_verbosity_verbose_e, control_parameter_verbosity_debug_e, control_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          control_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);

          return;
        }
      }

      if (main->parameters.array[control_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= control_main_flag_help_e;

        return;
      }

      if (main->parameters.array[control_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= control_main_flag_version_e;

        return;
      }

      // Identify and prioritize "from" mode parameters.
      {
        uint16_t choices_array[2] = { control_parameter_from_bytesequence_e, control_parameter_from_codepoint_e };
        choices.array = choices_array;
        choices.used = 2;

        setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

        if (F_status_is_error(setting->status)) {
          control_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_prioritize_right", F_true);

          return;
        }

        if (choices.array[choice] == control_parameter_from_bytesequence_e) {
          if (setting->mode & control_mode_from_codepoint_e) {
            setting->mode -= control_mode_from_codepoint_e;
          }

          setting->mode |= control_mode_from_bytesequence_e;
        }
        else if (choices.array[choice] == control_parameter_from_codepoint_e) {
          if (setting->mode & control_mode_from_bytesequence_e) {
            setting->mode -= control_mode_from_bytesequence_e;
          }

          setting->mode |= control_mode_from_codepoint_e;
        }
      }

      // Identify and prioritize "to" mode parameters.
      {
        uint16_t choices_array[4] = { control_parameter_to_bytesequence_e, control_parameter_to_codepoint_e, control_parameter_to_combining_e, control_parameter_to_width_e };
        choices.array = choices_array;
        choices.used = 4;
        choice = 1;

        setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

        if (F_status_is_error(setting->status)) {
          control_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_prioritize_right", F_true);

          return;
        }

        if (choices.array[choice] == control_parameter_to_bytesequence_e) {
          if (setting->mode & control_mode_to_codepoint_e) {
            setting->mode -= control_mode_to_codepoint_e;
          }

          if (setting->mode & control_mode_to_combining_e) {
            setting->mode -= control_mode_to_combining_e;
          }

          if (setting->mode & control_mode_to_width_e) {
            setting->mode -= control_mode_to_width_e;
          }

          setting->mode |= control_mode_to_bytesequence_e;
        }
        else if (choices.array[choice] == control_parameter_to_codepoint_e) {
          if (setting->mode & control_mode_to_bytesequence_e) {
            setting->mode -= control_mode_to_bytesequence_e;
          }

          if (setting->mode & control_mode_to_combining_e) {
            setting->mode -= control_mode_to_combining_e;
          }

          if (setting->mode & control_mode_to_width_e) {
            setting->mode -= control_mode_to_width_e;
          }

          setting->mode |= control_mode_to_codepoint_e;
        }
        else if (choices.array[choice] == control_parameter_to_combining_e) {
          if (setting->mode & control_mode_to_bytesequence_e) {
            setting->mode -= control_mode_to_bytesequence_e;
          }

          if (setting->mode & control_mode_to_codepoint_e) {
            setting->mode -= control_mode_to_codepoint_e;
          }

          // --to_width may be specified with --to_combining.
          if (main->parameters.array[control_parameter_to_width_e].result == f_console_result_found_e) {
            setting->mode |= control_mode_to_width_e;
          }

          setting->mode |= control_mode_to_combining_e;
        }
        else if (choices.array[choice] == control_parameter_to_width_e) {
          if (setting->mode & control_mode_to_bytesequence_e) {
            setting->mode -= control_mode_to_bytesequence_e;
          }

          if (setting->mode & control_mode_to_codepoint_e) {
            setting->mode -= control_mode_to_codepoint_e;
          }

          // --to_width may be specified with --to_combining.
          if (main->parameters.array[control_parameter_to_combining_e].result == f_console_result_found_e) {
            setting->mode |= control_mode_to_combining_e;
          }

          setting->mode |= control_mode_to_width_e;
        }
      }
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[control_parameter_to_file_e].result == f_console_result_additional_e) {
      if (main->parameters.array[control_parameter_to_file_e].values.used > 1) {
        control_print_error_parameter_file_to_too_many(main, setting);

        setting->status = F_status_set_error(F_parameter);

        return;
      }

      if (args[main->parameters.array[control_parameter_to_file_e].values.array[0]].used) {
        setting->path_files_to.used = 0;

        setting->status = f_string_dynamics_increase_by(1, &setting->path_files_to);
        if (F_status_is_error(setting->status)) return;

        setting->path_files_to.array[setting->path_files_to.used].used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[main->parameters.array[control_parameter_to_file_e].values.array[0]], &setting->path_files_to.array[0]);
        if (F_status_is_error(setting->status)) return;

        ++setting->path_files_to.used;

        setting->status = f_file_stream_open(args[main->parameters.array[control_parameter_to_file_e].values.array[0]], f_file_open_mode_append_s, &main->output.to);

        if (F_status_is_error(setting->status)) {
          fll_error_file_print(main->error, F_status_set_fine(setting->status), "f_file_stream_open", F_true, args[main->parameters.array[control_parameter_to_file_e].values.array[0]], f_file_operation_open_s, fll_error_file_type_file_e);

          return;
        }

        setting->flag |= control_main_flag_file_to_e;
      }
      else {
        control_print_error_parameter_file_name_empty(main, setting, main->parameters.array[control_parameter_to_file_e].values.array[0]);

        setting->status = F_status_set_error(F_parameter);

        return;
      }
    }
    else if (main->parameters.array[control_parameter_to_file_e].result == f_console_result_found_e) {
      control_print_error_no_value(main, setting, control_long_to_file_s);

      setting->status = F_status_set_error(F_parameter);

      return;
    }
    else {
      main->output.to = main->message.to;

      if (setting->flag & control_main_flag_file_to_e) {
        setting->flag -= control_main_flag_file_to_e;
      }
    }

    if (main->parameters.array[control_parameter_from_file_e].result == f_console_result_additional_e) {
      setting->path_files_from.used = 0;

      setting->status = f_string_dynamics_increase_by(main->parameters.array[control_parameter_from_file_e].values.used, &setting->path_files_from);
      if (F_status_is_error(setting->status)) return;

      setting->path_files_from.used = main->parameters.array[control_parameter_from_file_e].values.used;

      f_array_length_t i = 0;
      f_array_length_t index = 0;

      for (; i < setting->path_files_from.used; ++i) {

        index = main->parameters.array[control_parameter_from_file_e].values.array[i];
        setting->path_files_from.array[i].used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &setting->path_files_from.array[i]);
        if (F_status_is_error(setting->status)) return;

        if (args[index].used) {
          if (f_file_exists(args[index], F_true) != F_true) {
            control_print_error_parameter_file_not_found(main, setting, F_true, args[index]);

            if (F_status_is_error_not(setting->status)) {
              setting->status = F_status_set_error(F_file_found_not);
            }
          }
        }
        else {
          control_print_error_parameter_file_name_empty(main, setting, index);

          if (F_status_is_error_not(setting->status)) {
            setting->status = F_status_set_error(F_parameter);
          }
        }
      } // for

      if (F_status_is_error(setting->status)) return;

      setting->flag |= control_main_flag_file_from_e;
    }
    else if (main->parameters.array[control_parameter_from_file_e].result == f_console_result_found_e) {
      control_print_error_no_value(main, setting, control_long_from_file_s);

      setting->status = F_status_set_error(F_parameter);

      return;
    }
    else {
      if (setting->flag & control_main_flag_file_from_e) {
        setting->flag -= control_main_flag_file_from_e;
      }
    }

    if (F_status_is_error(setting->status)) return;

    if (main->parameters.array[control_parameter_from_file_e].result == f_console_result_none_e && !((main->pipe & fll_program_data_pipe_input_e) || main->parameters.remaining.used)) {
      control_print_error_no_from(main, setting);

      setting->status = F_status_set_error(F_parameter);
    }

    if (!(setting->mode & control_mode_to_bytesequence_e)) {
      if (main->parameters.array[control_parameter_separate_e].result == f_console_result_found_e || main->parameters.array[control_parameter_headers_e].result == f_console_result_found_e) {
        setting->prepend = control_string_prepend_padding_s;
        setting->append = f_string_eol_s;
      }
      else {
        setting->prepend = f_string_space_s;
      }
    }

    if (main->parameters.array[control_parameter_headers_e].result == f_console_result_found_e) {
      setting->flag |= control_main_flag_header_e;
    }

    if (main->parameters.array[control_parameter_separate_e].result == f_console_result_found_e) {
      setting->flag |= control_main_flag_separate_e;
    }

    if (main->parameters.array[control_parameter_strip_invalid_e].result == f_console_result_found_e) {
      setting->flag |= control_main_flag_strip_invalid_e;
    }

    setting->valid_not = main->message.set->error;
  }
#endif // _di_control_setting_load_

#ifndef _di_control_setting_unload_
  f_status_t control_setting_unload(fll_program_data_t * const main, control_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    control_setting_delete(setting);

    return F_none;
  }
#endif // _di_control_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
