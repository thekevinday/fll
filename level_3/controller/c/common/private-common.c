#include "../controller/controller.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_string_s_
  const f_string_t controller_action_s = CONTROLLER_action_s;
  const f_string_t controller_actions_s = CONTROLLER_actions_s;
  const f_string_t controller_affinity_s = CONTROLLER_affinity_s;
  const f_string_t controller_as_s = CONTROLLER_as_s;
  const f_string_t controller_asynchronous_s = CONTROLLER_asynchronous_s;
  const f_string_t controller_bash_s = CONTROLLER_bash_s;
  const f_string_t controller_batch_s = CONTROLLER_batch_s;
  const f_string_t controller_capability_s = CONTROLLER_capability_s;
  const f_string_t controller_cgroup_s = CONTROLLER_cgroup_s;
  const f_string_t controller_create_s = CONTROLLER_create_s;
  const f_string_t controller_command_s = CONTROLLER_command_s;
  const f_string_t controller_consider_s = CONTROLLER_consider_s;
  const f_string_t controller_control_s = CONTROLLER_control_s;
  const f_string_t controller_control_group_s = CONTROLLER_control_group_s;
  const f_string_t controller_control_mode_s = CONTROLLER_control_mode_s;
  const f_string_t controller_control_user_s = CONTROLLER_control_user_s;
  const f_string_t controller_cpu_s = CONTROLLER_cpu_s;
  const f_string_t controller_core_s = CONTROLLER_core_s;
  const f_string_t controller_data_s = CONTROLLER_data_s;
  const f_string_t controller_deadline_s = CONTROLLER_deadline_s;
  const f_string_t controller_default_s = CONTROLLER_default_s;
  const f_string_t controller_define_s = CONTROLLER_define_s;
  const f_string_t controller_delay_s = CONTROLLER_delay_s;
  const f_string_t controller_disable_s = CONTROLLER_disable_s;
  const f_string_t controller_entry_s = CONTROLLER_entry_s;
  const f_string_t controller_entries_s = CONTROLLER_entries_s;
  const f_string_t controller_environment_s = CONTROLLER_environment_s;
  const f_string_t controller_error_s = CONTROLLER_error_s;
  const f_string_t controller_execute_s = CONTROLLER_execute_s;
  const f_string_t controller_existing_s = CONTROLLER_existing_s;
  const f_string_t controller_exit_s = CONTROLLER_exit_s;
  const f_string_t controller_exits_s = CONTROLLER_exits_s;
  const f_string_t controller_fail_s = CONTROLLER_fail_s;
  const f_string_t controller_failsafe_s = CONTROLLER_failsafe_s;
  const f_string_t controller_failure_s = CONTROLLER_failure_s;
  const f_string_t controller_fifo_s = CONTROLLER_fifo_s;
  const f_string_t controller_freeze_s = CONTROLLER_freeze_s;
  const f_string_t controller_fsize_s = CONTROLLER_fsize_s;
  const f_string_t controller_full_path_s = CONTROLLER_full_path_s;
  const f_string_t controller_group_s = CONTROLLER_group_s;
  const f_string_t controller_groups_s = CONTROLLER_groups_s;
  const f_string_t controller_how_s = CONTROLLER_how_s;
  const f_string_t controller_idle_s = CONTROLLER_idle_s;
  const f_string_t controller_item_s = CONTROLLER_item_s;
  const f_string_t controller_init_s = CONTROLLER_init_s;
  const f_string_t controller_kill_s = CONTROLLER_kill_s;
  const f_string_t controller_length_s = CONTROLLER_length_s;
  const f_string_t controller_limit_s = CONTROLLER_limit_s;
  const f_string_t controller_locks_s = CONTROLLER_locks_s;
  const f_string_t controller_main_s = CONTROLLER_main_s;
  const f_string_t controller_max_s = CONTROLLER_max_s;
  const f_string_t controller_memlock_s = CONTROLLER_memlock_s;
  const f_string_t controller_method_s = CONTROLLER_method_s;
  const f_string_t controller_mode_s = CONTROLLER_mode_s;
  const f_string_t controller_msgqueue_s = CONTROLLER_msgqueue_s;
  const f_string_t controller_name_s = CONTROLLER_name_s;
  const f_string_t controller_need_s = CONTROLLER_need_s;
  const f_string_t controller_new_s = CONTROLLER_new_s;
  const f_string_t controller_nice_s = CONTROLLER_nice_s;
  const f_string_t controller_no_s = CONTROLLER_no_s;
  const f_string_t controller_nofile_s = CONTROLLER_nofile_s;
  const f_string_t controller_normal_s = CONTROLLER_normal_s;
  const f_string_t controller_nproc_s = CONTROLLER_nproc_s;
  const f_string_t controller_on_s = CONTROLLER_on_s;
  const f_string_t controller_optional_s = CONTROLLER_optional_s;
  const f_string_t controller_other_s = CONTROLLER_other_s;
  const f_string_t controller_parameter_s = CONTROLLER_parameter_s;
  const f_string_t controller_parameters_s = CONTROLLER_parameters_s;
  const f_string_t controller_path_s = CONTROLLER_path_s;
  const f_string_t controller_pause_s = CONTROLLER_pause_s;
  const f_string_t controller_payload_type_s = CONTROLLER_payload_type_s;
  const f_string_t controller_pid_s = CONTROLLER_pid_s;
  const f_string_t controller_pid_file_s = CONTROLLER_pid_file_s;
  const f_string_t controller_processor_s = CONTROLLER_processor_s;
  const f_string_t controller_program_s = CONTROLLER_program_s;
  const f_string_t controller_ready_s = CONTROLLER_ready_s;
  const f_string_t controller_reload_s = CONTROLLER_reload_s;
  const f_string_t controller_require_s = CONTROLLER_require_s;
  const f_string_t controller_required_s = CONTROLLER_required_s;
  const f_string_t controller_rerun_s = CONTROLLER_rerun_s;
  const f_string_t controller_reset_s = CONTROLLER_reset_s;
  const f_string_t controller_restart_s = CONTROLLER_restart_s;
  const f_string_t controller_resume_s = CONTROLLER_resume_s;
  const f_string_t controller_round_robin_s = CONTROLLER_round_robin_s;
  const f_string_t controller_rss_s = CONTROLLER_rss_s;
  const f_string_t controller_rtprio_s = CONTROLLER_rtprio_s;
  const f_string_t controller_rttime_s = CONTROLLER_rttime_s;
  const f_string_t controller_rule_s = CONTROLLER_rule_s;
  const f_string_t controller_rules_s = CONTROLLER_rules_s;
  const f_string_t controller_same_s = CONTROLLER_same_s;
  const f_string_t controller_scheduler_s = CONTROLLER_scheduler_s;
  const f_string_t controller_script_s = CONTROLLER_script_s;
  const f_string_t controller_service_s = CONTROLLER_service_s;
  const f_string_t controller_setting_s = CONTROLLER_setting_s;
  const f_string_t controller_session_s = CONTROLLER_session_s;
  const f_string_t controller_session_new_s = CONTROLLER_session_new_s;
  const f_string_t controller_session_same_s = CONTROLLER_session_same_s;
  const f_string_t controller_show_s = CONTROLLER_show_s;
  const f_string_t controller_sigpending_s = CONTROLLER_sigpending_s;
  const f_string_t controller_stack_s = CONTROLLER_stack_s;
  const f_string_t controller_start_s = CONTROLLER_start_s;
  const f_string_t controller_status_s = CONTROLLER_status_s;
  const f_string_t controller_stop_s = CONTROLLER_stop_s;
  const f_string_t controller_succeed_s = CONTROLLER_succeed_s;
  const f_string_t controller_success_s = CONTROLLER_success_s;
  const f_string_t controller_synchronous_s = CONTROLLER_synchronous_s;
  const f_string_t controller_thaw_s = CONTROLLER_thaw_s;
  const f_string_t controller_timeout_s = CONTROLLER_timeout_s;
  const f_string_t controller_type_s = CONTROLLER_type_s;
  const f_string_t controller_use_s = CONTROLLER_use_s;
  const f_string_t controller_user_s = CONTROLLER_user_s;
  const f_string_t controller_utility_s = CONTROLLER_utility_s;
  const f_string_t controller_value_s = CONTROLLER_value_s;
  const f_string_t controller_wait_s = CONTROLLER_wait_s;
  const f_string_t controller_want_s = CONTROLLER_want_s;
  const f_string_t controller_wish_s = CONTROLLER_wish_s;
  const f_string_t controller_with_s = CONTROLLER_with_s;
  const f_string_t controller_yes_s = CONTROLLER_yes_s;
#endif // _di_controller_string_s_

#ifdef __cplusplus
} // extern "C"
#endif
