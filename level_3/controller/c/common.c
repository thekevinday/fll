#include "controller.h"
#include "common/private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_version_
  const f_string_static_t controller_program_version_s = macro_f_string_static_t_initialize(CONTROLLER_program_version_s, 0, CONTROLLER_program_version_s_length);
#endif // _di_controller_program_version_

#ifndef _di_controller_program_name_
  const f_string_static_t controller_program_name_s = macro_f_string_static_t_initialize(CONTROLLER_program_name_s, 0, CONTROLLER_program_name_s_length);
  const f_string_static_t controller_program_name_long_s = macro_f_string_static_t_initialize(CONTROLLER_program_name_long_s, 0, CONTROLLER_program_name_long_s_length);

  const f_string_static_t controller_program_name_init_s = macro_f_string_static_t_initialize(CONTROLLER_program_name_init_s, 0, CONTROLLER_program_name_init_s_length);
  const f_string_static_t controller_program_name_init_long_s = macro_f_string_static_t_initialize(CONTROLLER_program_name_init_long_s, 0, CONTROLLER_program_name_init_long_s_length);
#endif // _di_controller_program_name_

#ifndef _di_controller_defines_
  const f_string_static_t controller_default_program_script_s = macro_f_string_static_t_initialize(CONTROLLER_default_program_script_s, 0, CONTROLLER_default_program_script_s_length);
  const f_string_static_t controller_path_pid_s = macro_f_string_static_t_initialize(CONTROLLER_path_pid_s, 0, CONTROLLER_path_pid_s_length);
  const f_string_static_t controller_path_pid_init_s = macro_f_string_static_t_initialize(CONTROLLER_path_pid_init_s, 0, CONTROLLER_path_pid_init_s_length);
  const f_string_static_t controller_path_pid_prefix_s = macro_f_string_static_t_initialize(CONTROLLER_path_pid_prefix_s, 0, CONTROLLER_path_pid_prefix_s_length);
  const f_string_static_t controller_path_pid_suffix_s = macro_f_string_static_t_initialize(CONTROLLER_path_pid_suffix_s, 0, CONTROLLER_path_pid_suffix_s_length);
  const f_string_static_t controller_path_settings_s = macro_f_string_static_t_initialize(CONTROLLER_path_settings_s, 0, CONTROLLER_path_settings_s_length);
  const f_string_static_t controller_path_settings_init_s = macro_f_string_static_t_initialize(CONTROLLER_path_settings_init_s, 0, CONTROLLER_path_settings_init_s_length);
  const f_string_static_t controller_path_socket_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_init_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_init_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_prefix_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_prefix_s, 0, CONTROLLER_path_socket_prefix_s_length);
  const f_string_static_t controller_path_socket_suffix_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_suffix_s, 0, CONTROLLER_path_socket_suffix_s_length);
#endif // _di_controller_defines_

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

      case controller_entry_action_type_kill_e:
        return controller_kill_s;

      case controller_entry_action_type_pause_e:
        return controller_pause_s;

      case controller_entry_action_type_ready_e:
        return controller_ready_s;

      case controller_entry_action_type_reload_e:
        return controller_reload_s;

      case controller_entry_action_type_restart_e:
        return controller_restart_s;

      case controller_entry_action_type_resume_e:
        return controller_resume_s;

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

    return F_none;
  }
#endif // _di_controller_main_delete_

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

      case controller_rule_action_type_rerun_e:
        return controller_rerun_s;

      case controller_rule_action_type_reload_e:
        return controller_reload_s;

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

#ifndef _di_controller_rule_action_type_execute_name_
  f_string_static_t controller_rule_action_type_execute_name(const uint8_t type) {

    switch (type) {
      case controller_rule_action_type_execute_freeze_e:
        return controller_freeze_s;

      case controller_rule_action_type_execute_kill_e:
        return controller_kill_s;

      case controller_rule_action_type_execute_pause_e:
        return controller_pause_s;

      case controller_rule_action_type_execute_reload_e:
        return controller_reload_s;

      case controller_rule_action_type_execute_restart_e:
        return controller_restart_s;

      case controller_rule_action_type_execute_resume_e:
        return controller_resume_s;

      case controller_rule_action_type_execute_start_e:
        return controller_start_s;

      case controller_rule_action_type_execute_stop_e:
        return controller_stop_s;

      case controller_rule_action_type_execute_thaw_e:
        return controller_thaw_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_rule_action_type_execute_name_

#ifndef _di_controller_rule_item_type_name_
  f_string_static_t controller_rule_item_type_name(const uint8_t type) {

    switch (type) {
      case controller_rule_item_type_command_e:
        return controller_command_s;

      case controller_rule_item_type_script_e:
        return controller_script_s;

      case controller_rule_item_type_service_e:
        return controller_service_s;

      case controller_rule_item_type_setting_e:
        return controller_setting_s;

      case controller_rule_item_type_utility_e:
        return controller_utility_s;
    }

    return f_string_empty_s;
  }
#endif // _di_controller_rule_item_type_name_

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

#ifdef __cplusplus
} // extern "C"
#endif
