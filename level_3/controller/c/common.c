#include "controller.h"
#include "common/private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_version_s_
  const f_string_static_t controller_program_version_s = macro_f_string_static_t_initialize_1(CONTROLLER_program_version_s, 0, CONTROLLER_program_version_s_length);
#endif // _di_controller_program_version_s_

#ifndef _di_controller_parameter_d_
  const f_string_static_t controller_short_cgroup_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_cgroup_s, 0, CONTROLLER_short_cgroup_s_length);
  const f_string_static_t controller_short_daemon_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_daemon_s, 0, CONTROLLER_short_daemon_s_length);
  const f_string_static_t controller_short_init_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_init_s, 0, CONTROLLER_short_init_s_length);
  const f_string_static_t controller_short_interruptible_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_interruptible_s, 0, CONTROLLER_short_interruptible_s_length);
  const f_string_static_t controller_short_pid_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_pid_s, 0, CONTROLLER_short_pid_s_length);
  const f_string_static_t controller_short_settings_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_settings_s, 0, CONTROLLER_short_settings_s_length);
  const f_string_static_t controller_short_simulate_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_simulate_s, 0, CONTROLLER_short_simulate_s_length);
  const f_string_static_t controller_short_socket_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_socket_s, 0, CONTROLLER_short_socket_s_length);
  const f_string_static_t controller_short_uninterruptible_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_uninterruptible_s, 0, CONTROLLER_short_uninterruptible_s_length);
  const f_string_static_t controller_short_validate_s = macro_f_string_static_t_initialize_1(CONTROLLER_short_validate_s, 0, CONTROLLER_short_validate_s_length);

  const f_string_static_t controller_long_cgroup_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_cgroup_s, 0, CONTROLLER_long_cgroup_s_length);
  const f_string_static_t controller_long_daemon_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_daemon_s, 0, CONTROLLER_long_daemon_s_length);
  const f_string_static_t controller_long_init_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_init_s, 0, CONTROLLER_long_init_s_length);
  const f_string_static_t controller_long_interruptible_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_interruptible_s, 0, CONTROLLER_long_interruptible_s_length);
  const f_string_static_t controller_long_pid_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_pid_s, 0, CONTROLLER_long_pid_s_length);
  const f_string_static_t controller_long_settings_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_settings_s, 0, CONTROLLER_long_settings_s_length);
  const f_string_static_t controller_long_simulate_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_simulate_s, 0, CONTROLLER_long_simulate_s_length);
  const f_string_static_t controller_long_socket_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_socket_s, 0, CONTROLLER_long_socket_s_length);
  const f_string_static_t controller_long_uninterruptible_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_uninterruptible_s, 0, CONTROLLER_long_uninterruptible_s_length);
  const f_string_static_t controller_long_validate_s = macro_f_string_static_t_initialize_1(CONTROLLER_long_validate_s, 0, CONTROLLER_long_validate_s_length);
#endif // _di_controller_parameter_d_

#ifndef _di_controller_main_delete_
  f_status_t controller_main_delete(controller_main_t * const main) {

    if (!main) return F_status_set_error(F_parameter);

    fll_program_data_delete(&main->program);
    controller_setting_delete(&main->setting);

    if (main->process) {
      controller_process_delete(main->process);
    }

    return F_okay;
  }
#endif // _di_controller_main_delete_

#ifndef _di_controller_control_delete_
  f_status_t controller_control_delete(controller_control_t * const control) {

    if (!main) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->cache_1.string, &control->cache_1.used, &control->cache_1.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->cache_2.string, &control->cache_2.used, &control->cache_2.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->cache_3.string, &control->cache_3.used, &control->cache_3.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->input.string, &control->input.used, &control->input.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &control->output.string, &control->output.used, &control->output.size);

    return F_okay;
  }
#endif // _di_controller_control_delete_

#ifndef _di_controller_control_payload_type_identify_
  uint8_t controller_control_payload_type_identify(const f_string_static_t payload) {

    if (f_compare_dynamic(payload, controller_controller_s) == F_equal_to) {
      return controller_control_payload_type_controller_e;
    }

    if (f_compare_dynamic(payload, controller_error_s) == F_equal_to) {
      return controller_control_payload_type_error_e;
    }

    if (f_compare_dynamic(payload, controller_init_s) == F_equal_to) {
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

    if (f_compare_dynamic(action, controller_consider_s) == F_equal_to) {
      return controller_entry_action_type_consider_e;
    }

    if (f_compare_dynamic(action, controller_execute_s) == F_equal_to) {
      return controller_entry_action_type_execute_e;
    }

    if (f_compare_dynamic(action, controller_failsafe_s) == F_equal_to) {
      return controller_entry_action_type_failsafe_e;
    }

    if (f_compare_dynamic(action, controller_freeze_s) == F_equal_to) {
      return controller_entry_action_type_freeze_e;
    }

    if (f_compare_dynamic(action, controller_item_s) == F_equal_to) {
      return controller_entry_action_type_item_e;
    }

    if (f_compare_dynamic(action, controller_kexec_s) == F_equal_to) {
      return controller_entry_action_type_kexec_e;
    }

    if (f_compare_dynamic(action, controller_kill_s) == F_equal_to) {
      return controller_entry_action_type_kill_e;
    }

    if (f_compare_dynamic(action, controller_pause_s) == F_equal_to) {
      return controller_entry_action_type_pause_e;
    }

    if (f_compare_dynamic(action, controller_ready_s) == F_equal_to) {
      return controller_entry_action_type_ready_e;
    }

    if (f_compare_dynamic(action, controller_reboot_s) == F_equal_to) {
      return controller_entry_action_type_reboot_e;
    }

    if (f_compare_dynamic(action, controller_reload_s) == F_equal_to) {
      return controller_entry_action_type_reload_e;
    }

    if (f_compare_dynamic(action, controller_restart_s) == F_equal_to) {
      return controller_entry_action_type_restart_e;
    }

    if (f_compare_dynamic(action, controller_resume_s) == F_equal_to) {
      return controller_entry_action_type_resume_e;
    }

    if (f_compare_dynamic(action, controller_shutdown_s) == F_equal_to) {
      return controller_entry_action_type_shutdown_e;
    }

    if (f_compare_dynamic(action, controller_start_s) == F_equal_to) {
      return controller_entry_action_type_start_e;
    }

    if (f_compare_dynamic(action, controller_stop_s) == F_equal_to) {
      return controller_entry_action_type_stop_e;
    }

    if (f_compare_dynamic(action, controller_thaw_s) == F_equal_to) {
      return controller_entry_action_type_thaw_e;
    }

    if (f_compare_dynamic(action, controller_timeout_s) == F_equal_to) {
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

#ifndef _di_controller_process_delete_
  f_status_t controller_process_delete(controller_process_t * const process) {

    if (!process) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->name_entry.string, &process->name_entry.used, &process->name_entry.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_cgroup.string, &process->path_cgroup.used, &process->path_cgroup.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_control.string, &process->path_control.used, &process->path_control.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_current.string, &process->path_current.used, &process->path_current.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_pid.string, &process->path_pid.used, &process->path_pid.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &process->path_setting.string, &process->path_setting.used, &process->path_setting.size);

    controller_control_delete(&process->control);

    status = f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &process->entry.define.array, &process->entry.define.used, &process->entry.define.size, &f_string_maps_delete_callback);
    status = f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &process->entry.parameter.array, &process->entry.parameter.used, &process->entry.parameter.size, &f_string_maps_delete_callback);
    status = f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &process->exit.define.array, &process->exit.define.used, &process->exit.define.size, &f_string_maps_delete_callback);
    status = f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &process->exit.parameter.array, &process->exit.parameter.used, &process->exit.parameter.size, &f_string_maps_delete_callback);

    controller_entry_items_delete(&process->entry.items);
    controller_entry_items_delete(&process->exit.items);

    controller_rules_delete_simple(&process->rules);

    return F_okay;
  }
#endif // _di_controller_process_delete_

#ifndef _di_controller_rule_action_type_identify_
  uint8_t controller_rule_action_type_identify(const f_string_static_t action) {

    if (f_compare_dynamic(action, controller_freeze_s) == F_equal_to) {
      return controller_rule_action_type_freeze_e;
    }

    if (f_compare_dynamic(action, controller_group_s) == F_equal_to) {
      return controller_rule_action_type_group_e;
    }

    if (f_compare_dynamic(action, controller_kill_s) == F_equal_to) {
      return controller_rule_action_type_kill_e;
    }

    if (f_compare_dynamic(action, controller_pause_s) == F_equal_to) {
      return controller_rule_action_type_pause_e;
    }

    if (f_compare_dynamic(action, controller_pid_file_s) == F_equal_to) {
      return controller_rule_action_type_pid_file_e;
    }

    if (f_compare_dynamic(action, controller_reload_s) == F_equal_to) {
      return controller_rule_action_type_reload_e;
    }

    if (f_compare_dynamic(action, controller_rerun_s) == F_equal_to) {
      return controller_rule_action_type_rerun_e;
    }

    if (f_compare_dynamic(action, controller_restart_s) == F_equal_to) {
      return controller_rule_action_type_restart_e;
    }

    if (f_compare_dynamic(action, controller_resume_s) == F_equal_to) {
      return controller_rule_action_type_resume_e;
    }

    if (f_compare_dynamic(action, controller_start_s) == F_equal_to) {
      return controller_rule_action_type_start_e;
    }

    if (f_compare_dynamic(action, controller_stop_s) == F_equal_to) {
      return controller_rule_action_type_stop_e;
    }

    if (f_compare_dynamic(action, controller_start_s) == F_equal_to) {
      return controller_rule_action_type_start_e;
    }

    if (f_compare_dynamic(action, controller_thaw_s) == F_equal_to) {
      return controller_rule_action_type_thaw_e;
    }

    if (f_compare_dynamic(action, controller_user_s) == F_equal_to) {
      return controller_rule_action_type_user_e;
    }

    if (f_compare_dynamic(action, controller_with_s) == F_equal_to) {
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

    if (f_compare_dynamic(action, controller_freeze_s) == F_equal_to) {
      return controller_rule_action_execute_type_freeze_e;
    }

    if (f_compare_dynamic(action, controller_kill_s) == F_equal_to) {
      return controller_rule_action_execute_type_kill_e;
    }

    if (f_compare_dynamic(action, controller_pause_s) == F_equal_to) {
      return controller_rule_action_execute_type_pause_e;
    }

    if (f_compare_dynamic(action, controller_reload_s) == F_equal_to) {
      return controller_rule_action_execute_type_reload_e;
    }

    if (f_compare_dynamic(action, controller_restart_s) == F_equal_to) {
      return controller_rule_action_execute_type_restart_e;
    }

    if (f_compare_dynamic(action, controller_resume_s) == F_equal_to) {
      return controller_rule_action_execute_type_resume_e;
    }

    if (f_compare_dynamic(action, controller_start_s) == F_equal_to) {
      return controller_rule_action_execute_type_start_e;
    }

    if (f_compare_dynamic(action, controller_stop_s) == F_equal_to) {
      return controller_rule_action_execute_type_stop_e;
    }

    if (f_compare_dynamic(action, controller_thaw_s) == F_equal_to) {
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

    if (f_compare_dynamic(item, controller_command_s) == F_equal_to) {
      return controller_rule_item_type_command_e;
    }

    if (f_compare_dynamic(item, controller_script_s) == F_equal_to) {
      return controller_rule_item_type_script_e;
    }

    if (f_compare_dynamic(item, controller_service_s) == F_equal_to) {
      return controller_rule_item_type_service_e;
    }

    if (f_compare_dynamic(item, controller_settings_s) == F_equal_to) {
      return controller_rule_item_type_settings_e;
    }

    if (f_compare_dynamic(item, controller_utility_s) == F_equal_to) {
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

    if (f_compare_dynamic(limit, controller_as_s) == F_equal_to) {
      return controller_resource_limit_type_as_e;
    }

    if (f_compare_dynamic(limit, controller_core_s) == F_equal_to) {
      return controller_resource_limit_type_core_e;
    }

    if (f_compare_dynamic(limit, controller_cpu_s) == F_equal_to) {
      return controller_resource_limit_type_cpu_e;
    }

    if (f_compare_dynamic(limit, controller_data_s) == F_equal_to) {
      return controller_resource_limit_type_data_e;
    }

    if (f_compare_dynamic(limit, controller_fsize_s) == F_equal_to) {
      return controller_resource_limit_type_fsize_e;
    }

    if (f_compare_dynamic(limit, controller_locks_s) == F_equal_to) {
      return controller_resource_limit_type_locks_e;
    }

    if (f_compare_dynamic(limit, controller_memlock_s) == F_equal_to) {
      return controller_resource_limit_type_memlock_e;
    }

    if (f_compare_dynamic(limit, controller_msgqueue_s) == F_equal_to) {
      return controller_resource_limit_type_msgqueue_e;
    }

    if (f_compare_dynamic(limit, controller_nice_s) == F_equal_to) {
      return controller_resource_limit_type_nice_e;
    }

    if (f_compare_dynamic(limit, controller_nofile_s) == F_equal_to) {
      return controller_resource_limit_type_nofile_e;
    }

    if (f_compare_dynamic(limit, controller_nproc_s) == F_equal_to) {
      return controller_resource_limit_type_nproc_e;
    }

    if (f_compare_dynamic(limit, controller_rss_s) == F_equal_to) {
      return controller_resource_limit_type_rss_e;
    }

    if (f_compare_dynamic(limit, controller_rtprio_s) == F_equal_to) {
      return controller_resource_limit_type_rtprio_e;
    }

    if (f_compare_dynamic(limit, controller_rttime_s) == F_equal_to) {
      return controller_resource_limit_type_rttime_e;
    }

    if (f_compare_dynamic(limit, controller_sigpending_s) == F_equal_to) {
      return controller_resource_limit_type_sigpending_e;
    }

    if (f_compare_dynamic(limit, controller_stack_s) == F_equal_to) {
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

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_pid.string, &setting->path_pid.used, &setting->path_pid.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->path_setting.string, &setting->path_setting.used, &setting->path_setting.size);

    return F_okay;
  }
#endif // _di_controller_setting_delete_

#ifndef _di_controller_setting_load_
  f_status_t controller_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main) {

    if (!main) return F_status_set_error(F_parameter);

    main->setting.state.step_small = controller_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = controller_allocation_small_d;

    if (main->program.parameters.array[f_console_standard_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~controller_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= controller_main_flag_print_first_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag &= ~controller_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= controller_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "f_console_parameter_process", fll_error_file_flag_fallback_e);

      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.error);
      }

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "fll_program_parameter_process_context_standard", fll_error_file_flag_fallback_e);

      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.error);
      }

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "fll_program_parameter_process_verbosity_standard", fll_error_file_flag_fallback_e);

      if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.error);
      }

      return;
    }

    main->program.output.to.id = F_type_descriptor_output_d;
    main->program.output.to.stream = F_type_output_d;
    main->program.output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_help_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_version_e;

      return;
    }

    if (main->program.parameters.array[f_console_standard_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_copyright_e;

      return;
    }

    f_string_static_t * const args = main->program.parameters.arguments.array;

    if (main->program.parameters.array[controller_parameter_strip_invalid_e].result & f_console_result_found_e) {
      main->setting.flag |= controller_main_flag_strip_invalid_e;
    }

    return F_okay;
  }
#endif // _di_controller_setting_load_

#ifndef _di_controller_entry_action_delete_
  f_status_t controller_entry_action_delete(controller_entry_action_t * const action) {

    if (!action) return F_status_set_error(F_parameter);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size, &f_string_dynamics_delete_callback);

    return F_okay;
  }
#endif // _di_controller_entry_action_delete_

#ifndef _di_controller_entry_actions_delete_
  f_status_t controller_entry_actions_delete(controller_entry_actions_t * const actions) {

    if (!actions) return F_status_set_error(F_parameter);

    // @todo Determine if this should be replaced with a resize callback strategy.
    actions->used = actions->size;

    while (actions->used) {
      controller_entry_action_delete(&actions->array[--actions->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_entry_action_t), (void **) &actions->array, &actions->used, &actions->size);

    return F_okay;
  }
#endif // _di_controller_entry_actions_delete_

#ifndef _di_controller_entry_actions_increase_by_
  f_status_t controller_entry_actions_increase_by(const f_number_unsigned_t amount, controller_entry_actions_t * const actions) {

    if (!actions) return F_status_set_error(F_parameter);

    if (amount) {
      if (actions->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = actions->used + amount;

      if (length > actions->size) {
        const f_status_t status = f_memory_resize(actions->size, length, sizeof(controller_entry_action_t), (void **) & actions->array);

        if (F_status_is_error_not(status)) {
          actions->size = actions->used + amount;
        }

        return status;
      }
    }

    return F_data_not;
  }
#endif // _di_controller_entry_actions_increase_by_

#ifndef _di_controller_entry_item_delete_
  f_status_t controller_entry_item_delete(controller_entry_item_t * const item) {

    if (!item) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &item->name.string, &item->name.used, &item->name.size);

    controller_entry_actions_delete(&item->actions);

    return F_okay;
  }
#endif // _di_controller_entry_item_delete_

#ifndef _di_controller_entry_items_delete_
  f_status_t controller_entry_items_delete(controller_entry_items_t * const items) {

    if (!items) return F_status_set_error(F_parameter);

    // @todo Determine if this should be replaced with a resize callback strategy.
    items->used = items->size;

    while (items->used) {
      controller_entry_item_delete(&items->array[--items->used]);
    } // while

    f_memory_array_resize(0, sizeof(controller_entry_item_t), (void **) &items->array, &items->used, &items->size);

    return F_okay;
  }
#endif // _di_controller_entry_items_delete_

#ifndef _di_controller_entry_items_increase_by_
  f_status_t controller_entry_items_increase_by(const f_number_unsigned_t amount, controller_entry_items_t * const items) {

    if (!items) return F_status_set_error(F_parameter);

    if (amount) {
      if (items->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = items->used + amount;

      if (length > items->size) {
        const f_status_t status = f_memory_resize(items->size, length, sizeof(controller_entry_item_t), (void **) & items->array);

        if (F_status_is_error_not(status)) {
          items->size = items->used + amount;
        }

        return status;
      }
    }

    return F_data_not;
  }
#endif // _di_controller_entry_items_increase_by_

#ifndef _di_controller_rule_action_t_
  const f_string_static_t controller_rule_action_method_string_extended_s = macro_f_string_static_t_initialize_1(CONTROLLER_rule_action_method_string_extended_s, 0, CONTROLLER_rule_action_method_string_extended_s_length);
  const f_string_static_t controller_rule_action_method_string_extended_list_s = macro_f_string_static_t_initialize_1(CONTROLLER_rule_action_method_string_extended_list_s, 0, CONTROLLER_rule_action_method_string_extended_list_s_length);
#endif // _di_controller_rule_action_t_

#ifndef _di_controller_rule_action_delete_simple_
  f_status_t controller_rule_action_delete_simple(controller_rule_action_t * const action) {

    if (!action) return F_status_set_error(F_parameter);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);

    return F_okay;
  }
#endif // _di_controller_rule_action_delete_simple_

#ifndef _di_controller_rule_actions_delete_simple_
  f_status_t controller_rule_actions_delete_simple(controller_rule_actions_t * const actions) {

    if (!actions) return F_status_set_error(F_parameter);

    actions->used = actions->size;

    while (actions->used) {
      controller_rule_action_delete_simple(&actions->array[--actions->used]);
    } // while

    f_memory_delete(actions->size, sizeof(controller_rule_action_t), (void **) & actions->array);
    actions->size = 0;

    return F_okay;
  }
#endif // _di_controller_rule_actions_delete_simple_

#ifndef _di_controller_rule_actions_increase_by_
  f_status_t controller_rule_actions_increase_by(const f_number_unsigned_t amount, controller_rule_actions_t * const actions) {

    if (!actions) return F_status_set_error(F_parameter);

    if (amount) {
      if (actions->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = actions->used + amount;

      if (length > actions->size) {
        const f_status_t status = f_memory_resize(actions->size, length, sizeof(controller_rule_action_t), (void **) & actions->array);

        if (F_status_is_error_not(status)) {
          actions->size = actions->used + amount;
        }

        return status;
      }
    }

    return F_data_not;
  }
#endif // _di_controller_rule_actions_increase_by_

#ifndef _di_controller_rule_delete_
  f_status_t controller_rule_delete(controller_rule_t * const rule) {

    if (!rule) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->engine.string, &rule->engine.used, &rule->engine.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->name.string, &rule->name.used, &rule->name.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->path.string, &rule->path.used, &rule->path.size);

    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &rule->define.array, &rule->define.used, &rule->define.size, &f_string_maps_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &rule->parameter.array, &rule->parameter.used, &rule->parameter.size, &f_string_maps_delete_callback);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->engine_arguments.array, &rule->engine_arguments.used, &rule->engine_arguments.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->environment.array, &rule->environment.used, &rule->environment.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(int32_t), (void **) &rule->affinity.array, &rule->affinity.used, &rule->affinity.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &rule->cgroup.path.string, &rule->cgroup.path.used, &rule->cgroup.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &rule->cgroup.groups.array, &rule->cgroup.groups.used, &rule->cgroup.groups.size, &f_string_dynamics_delete_callback);
    f_memory_array_resize(0, sizeof(int32_t), (void **) &rule->groups.array, &rule->groups.used, &rule->groups.size);
    f_memory_array_resize(0, sizeof(f_limit_set_t), (void **) &rule->limits.array, &rule->limits.used, &rule->limits.size);

    if (rule->capability) {
      f_capability_delete(&rule->capability);
    }

    controller_rule_ons_delete(&rule->ons);
    controller_rule_items_delete(&rule->items);

    return F_okay;
  }
#endif // _di_controller_rule_delete_

#ifndef _di_controller_rule_item_delete_
  f_status_t controller_rule_item_delete(controller_rule_item_t * const item) {

    if (!item) return F_status_set_error(F_parameter);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &item->pid_file.string, &item->pid_file.used, &item->pid_file.size);

    controller_rule_actions_delete(&item->actions);

    return F_okay;
  }
#endif // _di_controller_rule_item_delete_

#ifndef _di_controller_rule_items_delete_
  f_status_t controller_rule_items_delete(controller_rule_items_t * const items) {

    if (!items) return F_status_set_error(F_parameter);

    items->used = items->size;

    while (items->used) {
      controller_rule_item_delete(&items->array[--items->used]);
    } // while

    f_memory_delete(items->size, sizeof(controller_rule_item_t), (void **) & items->array);
    items->size = 0;

    return F_okay;
  }
#endif // _di_controller_rule_items_delete_

#ifndef _di_controller_rule_on_delete_
  f_status_t controller_rule_on_delete(controller_rule_on_t * const on) {

    if (!on) return F_status_set_error(F_parameter);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->need.array, &on->need.used, &on->need.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->want.array, &on->want.used, &on->want.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &on->wish.array, &on->wish.used, &on->wish.size, &f_string_dynamics_delete_callback);

    return F_okay;
  }
#endif // _di_controller_rule_on_delete_

#ifndef _di_controller_rule_ons_delete_
  f_status_t controller_rule_ons_delete(controller_rule_ons_t * const ons) {

    if (!ons) return F_status_set_error(F_parameter);

    ons->used = ons->size;

    while (ons->used) {
      controller_rule_on_delete(&ons->array[--ons->used]);
    } // while

    f_memory_delete(ons->size, sizeof(controller_rule_on_t), (void **) & ons->array);
    ons->size = 0;

    return F_okay;
  }
#endif // _di_controller_rule_ons_delete_

#ifndef _di_controller_rule_ons_increase_
  f_status_t controller_rule_ons_increase(controller_rule_ons_t * const ons) {

    if (!ons) return F_status_set_error(F_parameter);

    if (ons->used + 1 > ons->size) {
      f_number_unsigned_t length = ons->used + controller_common_allocation_small_d;

      if (length > F_number_t_size_unsigned_d) {
        if (ons->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        length = F_number_t_size_unsigned_d;
      }

      return controller_rule_ons_resize(length, ons);
    }

    return F_data_not;
  }
#endif // _di_controller_rule_ons_increase_

#ifndef _di_controller_rule_ons_resize_
  f_status_t controller_rule_ons_resize(const f_number_unsigned_t length, controller_rule_ons_t * const ons) {

    if (!ons) return F_status_set_error(F_parameter);

    for (f_number_unsigned_t i = length; i < ons->size; ++i) {
      controller_rule_on_delete(&ons->array[i]);
    } // for

    const f_status_t status = f_memory_resize(ons->size, length, sizeof(controller_rule_on_t), (void **) & ons->array);
    if (F_status_is_error(status)) return status;

    ons->size = length;

    if (ons->used > ons->size) {
      ons->used = length;
    }

    return F_okay;
  }
#endif // _di_controller_rule_ons_resize_

#ifndef _di_controller_rules_delete_
  f_status_t controller_rules_delete(controller_rules_t * const rules) {

    if (!rules) return F_status_set_error(F_parameter);

    controller_rules_resize(0, rules);

    return F_okay;
  }
#endif // _di_controller_rules_delete_

#ifndef _di_controller_rules_increase_
  f_status_t controller_rules_increase(controller_rules_t * const rules) {

    if (!rules) return F_status_set_error(F_parameter);

    if (rules->used + 1 > rules->size) {
      f_number_unsigned_t length = rules->used + controller_common_allocation_small_d;

      if (length > F_number_t_size_unsigned_d) {
        if (rules->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        length = F_number_t_size_unsigned_d;
      }

      return controller_rules_resize(length, rules);
    }

    return F_data_not;
  }
#endif // _di_controller_rules_increase_

#ifndef _di_controller_rules_resize_
  f_status_t controller_rules_resize(const f_number_unsigned_t length, controller_rules_t * const rules) {

    if (!rules) return F_status_set_error(F_parameter);

    for (f_number_unsigned_t i = length; i < rules->size; ++i) {
      controller_rule_delete(&rules->array[i]);
    } // for

    const f_status_t status = f_memory_resize(rules->size, length, sizeof(controller_rule_t), (void **) & rules->array);
    if (F_status_is_error(status)) return status;

    rules->size = length;

    if (rules->used > rules->size) {
      rules->used = length;
    }

    return F_okay;
  }
#endif // _di_controller_rules_resize_

#ifdef __cplusplus
} // extern "C"
#endif
