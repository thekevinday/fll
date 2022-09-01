#include "controller.h"
#include "common/private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_version_
  const f_string_static_t controller_program_version_s = macro_f_string_static_t_initialize(CONTROLLER_program_version_s, 0, CONTROLLER_program_version_s_length);
#endif // _di_controller_program_version_

#ifndef _di_controller_parameters_
  const f_string_static_t controller_short_cgroup_s = macro_f_string_static_t_initialize(CONTROLLER_short_cgroup_s, 0, CONTROLLER_short_cgroup_s_length);
  const f_string_static_t controller_short_daemon_s = macro_f_string_static_t_initialize(CONTROLLER_short_daemon_s, 0, CONTROLLER_short_daemon_s_length);
  const f_string_static_t controller_short_init_s = macro_f_string_static_t_initialize(CONTROLLER_short_init_s, 0, CONTROLLER_short_init_s_length);
  const f_string_static_t controller_short_interruptible_s = macro_f_string_static_t_initialize(CONTROLLER_short_interruptible_s, 0, CONTROLLER_short_interruptible_s_length);
  const f_string_static_t controller_short_pid_s = macro_f_string_static_t_initialize(CONTROLLER_short_pid_s, 0, CONTROLLER_short_pid_s_length);
  const f_string_static_t controller_short_settings_s = macro_f_string_static_t_initialize(CONTROLLER_short_settings_s, 0, CONTROLLER_short_settings_s_length);
  const f_string_static_t controller_short_simulate_s = macro_f_string_static_t_initialize(CONTROLLER_short_simulate_s, 0, CONTROLLER_short_simulate_s_length);
  const f_string_static_t controller_short_socket_s = macro_f_string_static_t_initialize(CONTROLLER_short_socket_s, 0, CONTROLLER_short_socket_s_length);
  const f_string_static_t controller_short_uninterruptible_s = macro_f_string_static_t_initialize(CONTROLLER_short_uninterruptible_s, 0, CONTROLLER_short_uninterruptible_s_length);
  const f_string_static_t controller_short_validate_s = macro_f_string_static_t_initialize(CONTROLLER_short_validate_s, 0, CONTROLLER_short_validate_s_length);

  const f_string_static_t controller_long_cgroup_s = macro_f_string_static_t_initialize(CONTROLLER_long_cgroup_s, 0, CONTROLLER_long_cgroup_s_length);
  const f_string_static_t controller_long_daemon_s = macro_f_string_static_t_initialize(CONTROLLER_long_daemon_s, 0, CONTROLLER_long_daemon_s_length);
  const f_string_static_t controller_long_init_s = macro_f_string_static_t_initialize(CONTROLLER_long_init_s, 0, CONTROLLER_long_init_s_length);
  const f_string_static_t controller_long_interruptible_s = macro_f_string_static_t_initialize(CONTROLLER_long_interruptible_s, 0, CONTROLLER_long_interruptible_s_length);
  const f_string_static_t controller_long_pid_s = macro_f_string_static_t_initialize(CONTROLLER_long_pid_s, 0, CONTROLLER_long_pid_s_length);
  const f_string_static_t controller_long_settings_s = macro_f_string_static_t_initialize(CONTROLLER_long_settings_s, 0, CONTROLLER_long_settings_s_length);
  const f_string_static_t controller_long_simulate_s = macro_f_string_static_t_initialize(CONTROLLER_long_simulate_s, 0, CONTROLLER_long_simulate_s_length);
  const f_string_static_t controller_long_socket_s = macro_f_string_static_t_initialize(CONTROLLER_long_socket_s, 0, CONTROLLER_long_socket_s_length);
  const f_string_static_t controller_long_uninterruptible_s = macro_f_string_static_t_initialize(CONTROLLER_long_uninterruptible_s, 0, CONTROLLER_long_uninterruptible_s_length);
  const f_string_static_t controller_long_validate_s = macro_f_string_static_t_initialize(CONTROLLER_long_validate_s, 0, CONTROLLER_long_validate_s_length);
#endif // _di_controller_parameters_

#ifndef _di_controller_control_payload_type_identify_
  uint8_t controller_control_payload_type_identify(const f_string_static_t payload) {

    if (fl_string_dynamic_compare(payload, controller_controller_s) == F_equal_to) {
      return controller_control_payload_type_controller_e;
    }

    if (fl_string_dynamic_compare(payload, controller_error_s) == F_equal_to) {
      return controller_control_payload_type_error_e;
    }

    if (fl_string_dynamic_compare(payload, controller_init_s) == F_equal_to) {
      return controller_control_payload_type_init_e;
    }

    return 0;
  }
#endif // _di_controller_control_payload_type_identify_

#ifndef _di_controller_control_payload_type_name_
  f_string_static_t controller_control_payload_type_name(const uint8_t type) {

    switch (type) {
      case controller_control_payload_type_controller_e:
        return controller_controller_s;

      case controller_control_payload_type_error_e:
        return controller_error_s;

      case controller_control_payload_type_init_e:
        return controller_init_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_control_payload_type_name_

#ifndef _di_controller_entry_action_type_identify_
  uint8_t controller_entry_action_type_identify(const f_string_static_t action) {

    if (fl_string_dynamic_compare(action, controller_consider_s) == F_equal_to) {
      return controller_entry_action_type_consider_e;
    }

    if (fl_string_dynamic_compare(action, controller_execute_s) == F_equal_to) {
      return controller_entry_action_type_execute_e;
    }

    if (fl_string_dynamic_compare(action, controller_failsafe_s) == F_equal_to) {
      return controller_entry_action_type_failsafe_e;
    }

    if (fl_string_dynamic_compare(action, controller_freeze_s) == F_equal_to) {
      return controller_entry_action_type_freeze_e;
    }

    if (fl_string_dynamic_compare(action, controller_item_s) == F_equal_to) {
      return controller_entry_action_type_item_e;
    }

    if (fl_string_dynamic_compare(action, controller_kexec_s) == F_equal_to) {
      return controller_entry_action_type_kexec_e;
    }

    if (fl_string_dynamic_compare(action, controller_kill_s) == F_equal_to) {
      return controller_entry_action_type_kill_e;
    }

    if (fl_string_dynamic_compare(action, controller_pause_s) == F_equal_to) {
      return controller_entry_action_type_pause_e;
    }

    if (fl_string_dynamic_compare(action, controller_ready_s) == F_equal_to) {
      return controller_entry_action_type_ready_e;
    }

    if (fl_string_dynamic_compare(action, controller_reboot_s) == F_equal_to) {
      return controller_entry_action_type_reboot_e;
    }

    if (fl_string_dynamic_compare(action, controller_reload_s) == F_equal_to) {
      return controller_entry_action_type_reload_e;
    }

    if (fl_string_dynamic_compare(action, controller_restart_s) == F_equal_to) {
      return controller_entry_action_type_restart_e;
    }

    if (fl_string_dynamic_compare(action, controller_resume_s) == F_equal_to) {
      return controller_entry_action_type_resume_e;
    }

    if (fl_string_dynamic_compare(action, controller_shutdown_s) == F_equal_to) {
      return controller_entry_action_type_shutdown_e;
    }

    if (fl_string_dynamic_compare(action, controller_start_s) == F_equal_to) {
      return controller_entry_action_type_start_e;
    }

    if (fl_string_dynamic_compare(action, controller_stop_s) == F_equal_to) {
      return controller_entry_action_type_stop_e;
    }

    if (fl_string_dynamic_compare(action, controller_thaw_s) == F_equal_to) {
      return controller_entry_action_type_thaw_e;
    }

    if (fl_string_dynamic_compare(action, controller_timeout_s) == F_equal_to) {
      return controller_entry_action_type_timeout_e;
    }

    return 0;
  }
#endif // _di_controller_entry_action_type_identify_

#ifndef _di_controller_entry_action_type_name_
  f_string_static_t controller_entry_action_type_name(const uint8_t type) {

    switch (type) {
      case controller_entry_action_type_consider_e:
        return controller_consider_s;

      case controller_entry_action_type_execute_e:
        return controller_execute_s;

      case controller_entry_action_type_failsafe_e:
        return controller_failsafe_s;

      case controller_entry_action_type_freeze_e:
        return controller_freeze_s;

      case controller_entry_action_type_item_e:
        return controller_item_s;

      case controller_entry_action_type_kexec_e:
        return controller_kexec_s;

      case controller_entry_action_type_kill_e:
        return controller_kill_s;

      case controller_entry_action_type_pause_e:
        return controller_pause_s;

      case controller_entry_action_type_ready_e:
        return controller_ready_s;

      case controller_entry_action_type_reboot_e:
        return controller_reboot_s;

      case controller_entry_action_type_reload_e:
        return controller_reload_s;

      case controller_entry_action_type_restart_e:
        return controller_restart_s;

      case controller_entry_action_type_resume_e:
        return controller_resume_s;

      case controller_entry_action_type_shutdown_e:
        return controller_shutdown_s;

      case controller_entry_action_type_start_e:
        return controller_start_s;

      case controller_entry_action_type_stop_e:
        return controller_stop_s;

      case controller_entry_action_type_thaw_e:
        return controller_thaw_s;

      case controller_entry_action_type_timeout_e:
        return controller_timeout_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_entry_action_type_name_

#ifndef _di_controller_main_delete_
  f_status_t controller_main_delete(controller_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    macro_f_color_context_t_delete_simple(main->context);

    f_string_dynamic_resize(0, &main->path_pid);
    f_string_dynamic_resize(0, &main->path_setting);

    return F_none;
  }
#endif // _di_controller_main_delete_

#ifndef _di_controller_rule_action_type_identify_
  uint8_t controller_rule_action_type_identify(const f_string_static_t action) {

    if (fl_string_dynamic_compare(action, controller_freeze_s) == F_equal_to) {
      return controller_rule_action_type_freeze_e;
    }

    if (fl_string_dynamic_compare(action, controller_group_s) == F_equal_to) {
      return controller_rule_action_type_group_e;
    }

    if (fl_string_dynamic_compare(action, controller_kill_s) == F_equal_to) {
      return controller_rule_action_type_kill_e;
    }

    if (fl_string_dynamic_compare(action, controller_pause_s) == F_equal_to) {
      return controller_rule_action_type_pause_e;
    }

    if (fl_string_dynamic_compare(action, controller_pid_file_s) == F_equal_to) {
      return controller_rule_action_type_pid_file_e;
    }

    if (fl_string_dynamic_compare(action, controller_reload_s) == F_equal_to) {
      return controller_rule_action_type_reload_e;
    }

    if (fl_string_dynamic_compare(action, controller_rerun_s) == F_equal_to) {
      return controller_rule_action_type_rerun_e;
    }

    if (fl_string_dynamic_compare(action, controller_restart_s) == F_equal_to) {
      return controller_rule_action_type_restart_e;
    }

    if (fl_string_dynamic_compare(action, controller_resume_s) == F_equal_to) {
      return controller_rule_action_type_resume_e;
    }

    if (fl_string_dynamic_compare(action, controller_start_s) == F_equal_to) {
      return controller_rule_action_type_start_e;
    }

    if (fl_string_dynamic_compare(action, controller_stop_s) == F_equal_to) {
      return controller_rule_action_type_stop_e;
    }

    if (fl_string_dynamic_compare(action, controller_start_s) == F_equal_to) {
      return controller_rule_action_type_start_e;
    }

    if (fl_string_dynamic_compare(action, controller_thaw_s) == F_equal_to) {
      return controller_rule_action_type_thaw_e;
    }

    if (fl_string_dynamic_compare(action, controller_user_s) == F_equal_to) {
      return controller_rule_action_type_user_e;
    }

    if (fl_string_dynamic_compare(action, controller_with_s) == F_equal_to) {
      return controller_rule_action_type_with_e;
    }

    return 0;
  }
#endif // _di_controller_rule_action_type_identify_

#ifndef _di_controller_rule_action_type_name_
  f_string_static_t controller_rule_action_type_name(const uint8_t type) {

    switch (type) {
      case controller_rule_action_type_freeze_e:
        return controller_freeze_s;

      case controller_rule_action_type_group_e:
        return controller_group_s;

      case controller_rule_action_type_kill_e:
        return controller_kill_s;

      case controller_rule_action_type_pause_e:
        return controller_pause_s;

      case controller_rule_action_type_pid_file_e:
        return controller_pid_file_s;

      case controller_rule_action_type_reload_e:
        return controller_reload_s;

      case controller_rule_action_type_rerun_e:
        return controller_rerun_s;

      case controller_rule_action_type_restart_e:
        return controller_restart_s;

      case controller_rule_action_type_resume_e:
        return controller_resume_s;

      case controller_rule_action_type_start_e:
        return controller_start_s;

      case controller_rule_action_type_stop_e:
        return controller_stop_s;

      case controller_rule_action_type_thaw_e:
        return controller_thaw_s;

      case controller_rule_action_type_user_e:
        return controller_user_s;

      case controller_rule_action_type_with_e:
        return controller_with_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_rule_action_type_name_

#ifndef _di_controller_rule_action_execute_type_identify_
  uint8_t controller_rule_action_execute_type_identify(const f_string_static_t action) {

    if (fl_string_dynamic_compare(action, controller_freeze_s) == F_equal_to) {
      return controller_rule_action_execute_type_freeze_e;
    }

    if (fl_string_dynamic_compare(action, controller_kill_s) == F_equal_to) {
      return controller_rule_action_execute_type_kill_e;
    }

    if (fl_string_dynamic_compare(action, controller_pause_s) == F_equal_to) {
      return controller_rule_action_execute_type_pause_e;
    }

    if (fl_string_dynamic_compare(action, controller_reload_s) == F_equal_to) {
      return controller_rule_action_execute_type_reload_e;
    }

    if (fl_string_dynamic_compare(action, controller_restart_s) == F_equal_to) {
      return controller_rule_action_execute_type_restart_e;
    }

    if (fl_string_dynamic_compare(action, controller_resume_s) == F_equal_to) {
      return controller_rule_action_execute_type_resume_e;
    }

    if (fl_string_dynamic_compare(action, controller_start_s) == F_equal_to) {
      return controller_rule_action_execute_type_start_e;
    }

    if (fl_string_dynamic_compare(action, controller_stop_s) == F_equal_to) {
      return controller_rule_action_execute_type_stop_e;
    }

    if (fl_string_dynamic_compare(action, controller_thaw_s) == F_equal_to) {
      return controller_rule_action_execute_type_thaw_e;
    }

    return controller_rule_action_execute_type__enum_size_e;
  }
#endif // _di_controller_rule_action_execute_type_identify_

#ifndef _di_controller_rule_action_execute_type_name_
  f_string_static_t controller_rule_action_execute_type_name(const uint8_t type) {

    switch (type) {
      case controller_rule_action_execute_type_freeze_e:
        return controller_freeze_s;

      case controller_rule_action_execute_type_kill_e:
        return controller_kill_s;

      case controller_rule_action_execute_type_pause_e:
        return controller_pause_s;

      case controller_rule_action_execute_type_reload_e:
        return controller_reload_s;

      case controller_rule_action_execute_type_restart_e:
        return controller_restart_s;

      case controller_rule_action_execute_type_resume_e:
        return controller_resume_s;

      case controller_rule_action_execute_type_start_e:
        return controller_start_s;

      case controller_rule_action_execute_type_stop_e:
        return controller_stop_s;

      case controller_rule_action_execute_type_thaw_e:
        return controller_thaw_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_rule_action_execute_type_name_

#ifndef _di_controller_rule_item_type_identify_
  uint8_t controller_rule_item_type_identify(const f_string_static_t item) {

    if (fl_string_dynamic_compare(item, controller_command_s) == F_equal_to) {
      return controller_rule_item_type_command_e;
    }

    if (fl_string_dynamic_compare(item, controller_script_s) == F_equal_to) {
      return controller_rule_item_type_script_e;
    }

    if (fl_string_dynamic_compare(item, controller_service_s) == F_equal_to) {
      return controller_rule_item_type_service_e;
    }

    if (fl_string_dynamic_compare(item, controller_settings_s) == F_equal_to) {
      return controller_rule_item_type_settings_e;
    }

    if (fl_string_dynamic_compare(item, controller_utility_s) == F_equal_to) {
      return controller_rule_item_type_utility_e;
    }

    return 0;
  }
#endif // _di_controller_rule_item_type_identify_

#ifndef _di_controller_rule_item_type_name_
  f_string_static_t controller_rule_item_type_name(const uint8_t type) {

    switch (type) {
      case controller_rule_item_type_command_e:
        return controller_command_s;

      case controller_rule_item_type_script_e:
        return controller_script_s;

      case controller_rule_item_type_service_e:
        return controller_service_s;

      case controller_rule_item_type_settings_e:
        return controller_settings_s;

      case controller_rule_item_type_utility_e:
        return controller_utility_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_rule_item_type_name_

#ifndef _di_controller_rule_setting_limit_type_identify_
  uint8_t controller_rule_setting_limit_type_identify(const f_string_static_t limit) {

    if (fl_string_dynamic_compare(limit, controller_as_s) == F_equal_to) {
      return controller_resource_limit_type_as_e;
    }

    if (fl_string_dynamic_compare(limit, controller_core_s) == F_equal_to) {
      return controller_resource_limit_type_core_e;
    }

    if (fl_string_dynamic_compare(limit, controller_cpu_s) == F_equal_to) {
      return controller_resource_limit_type_cpu_e;
    }

    if (fl_string_dynamic_compare(limit, controller_data_s) == F_equal_to) {
      return controller_resource_limit_type_data_e;
    }

    if (fl_string_dynamic_compare(limit, controller_fsize_s) == F_equal_to) {
      return controller_resource_limit_type_fsize_e;
    }

    if (fl_string_dynamic_compare(limit, controller_locks_s) == F_equal_to) {
      return controller_resource_limit_type_locks_e;
    }

    if (fl_string_dynamic_compare(limit, controller_memlock_s) == F_equal_to) {
      return controller_resource_limit_type_memlock_e;
    }

    if (fl_string_dynamic_compare(limit, controller_msgqueue_s) == F_equal_to) {
      return controller_resource_limit_type_msgqueue_e;
    }

    if (fl_string_dynamic_compare(limit, controller_nice_s) == F_equal_to) {
      return controller_resource_limit_type_nice_e;
    }

    if (fl_string_dynamic_compare(limit, controller_nofile_s) == F_equal_to) {
      return controller_resource_limit_type_nofile_e;
    }

    if (fl_string_dynamic_compare(limit, controller_nproc_s) == F_equal_to) {
      return controller_resource_limit_type_nproc_e;
    }

    if (fl_string_dynamic_compare(limit, controller_rss_s) == F_equal_to) {
      return controller_resource_limit_type_rss_e;
    }

    if (fl_string_dynamic_compare(limit, controller_rtprio_s) == F_equal_to) {
      return controller_resource_limit_type_rtprio_e;
    }

    if (fl_string_dynamic_compare(limit, controller_rttime_s) == F_equal_to) {
      return controller_resource_limit_type_rttime_e;
    }

    if (fl_string_dynamic_compare(limit, controller_sigpending_s) == F_equal_to) {
      return controller_resource_limit_type_sigpending_e;
    }

    if (fl_string_dynamic_compare(limit, controller_stack_s) == F_equal_to) {
      return controller_resource_limit_type_stack_e;
    }

    return 0;
  }
#endif // _di_controller_rule_setting_limit_type_identify_

#ifndef _di_controller_rule_setting_limit_type_name_
  f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type) {

    switch (type) {
      case controller_resource_limit_type_as_e:
        return controller_as_s;

      case controller_resource_limit_type_core_e:
        return controller_core_s;

      case controller_resource_limit_type_cpu_e:
        return controller_cpu_s;

      case controller_resource_limit_type_data_e:
        return controller_data_s;

      case controller_resource_limit_type_fsize_e:
        return controller_fsize_s;

      case controller_resource_limit_type_locks_e:
        return controller_locks_s;

      case controller_resource_limit_type_memlock_e:
        return controller_memlock_s;

      case controller_resource_limit_type_msgqueue_e:
        return controller_msgqueue_s;

      case controller_resource_limit_type_nice_e:
        return controller_nice_s;

      case controller_resource_limit_type_nofile_e:
        return controller_nofile_s;

      case controller_resource_limit_type_nproc_e:
        return controller_nproc_s;

      case controller_resource_limit_type_rss_e:
        return controller_rss_s;

      case controller_resource_limit_type_rtprio_e:
        return controller_rtprio_s;

      case controller_resource_limit_type_rttime_e:
        return controller_rttime_s;

      case controller_resource_limit_type_sigpending_e:
        return controller_sigpending_s;

      case controller_resource_limit_type_stack_e:
        return controller_stack_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_rule_setting_limit_type_name_

#ifndef _di_controller_setting_delete_
  f_status_t controller_setting_delete(controller_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_controller_setting_delete_

#ifndef _di_controller_setting_load_
  void controller_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, controller_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(setting->status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { controller_parameter_no_color_e, controller_parameter_light_e, controller_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          controller_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);

          return;
        }
      }

      if (main->parameters.array[controller_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[controller_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { controller_parameter_verbosity_quiet_e, controller_parameter_verbosity_error_e, controller_parameter_verbosity_verbose_e, controller_parameter_verbosity_debug_e, controller_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          controller_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);

          return;
        }
      }

      if (main->parameters.array[controller_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= controller_main_flag_help_e;

        return;
      }

      if (main->parameters.array[controller_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= controller_main_flag_version_e;

        return;
      }
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[controller_parameter_strip_invalid_e].result == f_console_result_found_e) {
      setting->flag |= controller_main_flag_strip_invalid_e;
    }
  }
#endif // _di_controller_setting_load_

#ifndef _di_controller_setting_unload_
  f_status_t controller_setting_unload(fll_program_data_t * const main, controller_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    controller_setting_delete(setting);

    return F_none;
  }
#endif // _di_controller_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
