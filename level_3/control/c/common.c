#include "control.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_program_version_s_
  const f_string_static_t control_program_version_s = macro_f_string_static_t_initialize(CONTROL_program_version_s, 0, CONTROL_program_version_s_length);
#endif // _di_control_program_version_s_

#ifndef _di_control_program_name_s_
  const f_string_static_t control_program_name_s = macro_f_string_static_t_initialize(CONTROL_program_name_s, 0, CONTROL_program_name_s_length);
  const f_string_static_t control_program_name_long_s = macro_f_string_static_t_initialize(CONTROL_program_name_long_s, 0, CONTROL_program_name_long_s_length);
#endif // _di_control_program_name_s_

#ifndef _di_control_parameter_d_
  const f_string_static_t control_short_name_s = macro_f_string_static_t_initialize(CONTROL_short_name_s, 0, CONTROL_short_name_s_length);
  const f_string_static_t control_short_return_s = macro_f_string_static_t_initialize(CONTROL_short_return_s, 0, CONTROL_short_return_s_length);
  const f_string_static_t control_short_settings_s = macro_f_string_static_t_initialize(CONTROL_short_settings_s, 0, CONTROL_short_settings_s_length);
  const f_string_static_t control_short_socket_s = macro_f_string_static_t_initialize(CONTROL_short_socket_s, 0, CONTROL_short_socket_s_length);

  const f_string_static_t control_long_name_s = macro_f_string_static_t_initialize(CONTROL_long_name_s, 0, CONTROL_long_name_s_length);
  const f_string_static_t control_long_return_s = macro_f_string_static_t_initialize(CONTROL_long_return_s, 0, CONTROL_long_return_s_length);
  const f_string_static_t control_long_settings_s = macro_f_string_static_t_initialize(CONTROL_long_settings_s, 0, CONTROL_long_settings_s_length);
  const f_string_static_t control_long_socket_s = macro_f_string_static_t_initialize(CONTROL_long_socket_s, 0, CONTROL_long_socket_s_length);
#endif // _di_control_parameter_d_

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

    if (!main) return;

    setting->state.step_small = control_allocation_console_d;

    f_console_parameter_process(arguments, &main->parameters, &setting->state, 0);

    setting->state.step_small = control_write_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (main->parameters.array[control_parameter_line_first_no_e].result & f_console_result_found_e) {
      setting->flag -= setting->flag & control_main_flag_print_first_e;
    }
    else {
      setting->flag |= control_main_flag_print_first_e;
    }

    if (main->parameters.array[control_parameter_line_last_no_e].result & f_console_result_found_e) {
      setting->flag -= setting->flag & control_main_flag_print_last_e;
    }
    else {
      setting->flag |= control_main_flag_print_last_e;
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
        uint16_t choices_array[3] = { control_parameter_no_color_e, control_parameter_light_e, control_parameter_dark_e };
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
        uint16_t choices_array[5] = { control_parameter_verbosity_quiet_e, control_parameter_verbosity_error_e, control_parameter_verbosity_verbose_e, control_parameter_verbosity_debug_e, control_parameter_verbosity_normal_e };
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

    if (main->parameters.array[control_parameter_help_e].result & f_console_result_found_e) {
      setting->flag |= control_main_flag_help_e;

      return;
    }

    if (main->parameters.array[control_parameter_version_e].result & f_console_result_found_e) {
      setting->flag |= control_main_flag_version_e;

      return;
    }

    if (main->parameters.array[control_parameter_copyright_e].result & f_console_result_found_e) {
      setting->flag |= control_main_flag_copyright_e;

      return;
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[control_parameter_strip_invalid_e].result & f_console_result_found_e) {
      setting->flag |= control_main_flag_strip_invalid_e;
    }
  }
#endif // _di_control_setting_load_

#ifndef _di_control_setting_unload_
  f_status_t control_setting_unload(control_main_t * const main) {

    if (!main) return F_status_set_error(F_parameter);

    control_setting_delete(&control_main_t->setting);

    return F_none;
  }
#endif // _di_control_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
