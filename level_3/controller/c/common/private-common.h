/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

// These are included in the order of their dependencies.
#include "private-cache.h"
#include "private-execute_set.h"
#include "private-lock.h"
#include "private-rule.h"
#include "private-process.h"
#include "private-entry.h"
#include "private-control.h"
#include "private-setting.h"
#include "private-thread.h"
#include "private-state.h"

/**
 * All special strings used within this program.
 *
 * These are generally the names to match, representing some action or setting.
 */
#ifndef _di_controller_string_s_
  #define CONTROLLER_action_s        "action"
  #define CONTROLLER_actions_s       "actions"
  #define CONTROLLER_affinity_s      "affinity"
  #define CONTROLLER_as_s            "as"
  #define CONTROLLER_asynchronous_s  "asynchronous"
  #define CONTROLLER_bash_s          "bash"
  #define CONTROLLER_batch_s         "batch"
  #define CONTROLLER_capability_s    "capability"
  #define CONTROLLER_cgroup_s        "cgroup"
  #define CONTROLLER_create_s        "create"
  #define CONTROLLER_command_s       "command"
  #define CONTROLLER_consider_s      "consider"
  #define CONTROLLER_control_s       "control"
  #define CONTROLLER_control_group_s "control_group"
  #define CONTROLLER_control_mode_s  "control_mode"
  #define CONTROLLER_control_user_s  "control_user"
  #define CONTROLLER_controller_s    "controller"
  #define CONTROLLER_cpu_s           "cpu"
  #define CONTROLLER_core_s          "core"
  #define CONTROLLER_data_s          "data"
  #define CONTROLLER_deadline_s      "deadline"
  #define CONTROLLER_default_s       "default"
  #define CONTROLLER_define_s        "define"
  #define CONTROLLER_delay_s         "delay"
  #define CONTROLLER_disable_s       "disable"
  #define CONTROLLER_engine_s        "engine"
  #define CONTROLLER_entry_s         "entry"
  #define CONTROLLER_entries_s       "entries"
  #define CONTROLLER_environment_s   "environment"
  #define CONTROLLER_error_s         "error"
  #define CONTROLLER_execute_s       "execute"
  #define CONTROLLER_existing_s      "existing"
  #define CONTROLLER_exit_s          "exit"
  #define CONTROLLER_exits_s         "exits"
  #define CONTROLLER_fail_s          "fail"
  #define CONTROLLER_failsafe_s      "failsafe"
  #define CONTROLLER_failure_s       "failure"
  #define CONTROLLER_fifo_s          "fifo"
  #define CONTROLLER_freeze_s        "freeze"
  #define CONTROLLER_fsize_s         "fsize"
  #define CONTROLLER_full_path_s     "full_path"
  #define CONTROLLER_group_s         "group"
  #define CONTROLLER_groups_s        "groups"
  #define CONTROLLER_helper_s        "helper"
  #define CONTROLLER_how_s           "how"
  #define CONTROLLER_idle_s          "idle"
  #define CONTROLLER_iki_s           "iki"
  #define CONTROLLER_item_s          "item"
  #define CONTROLLER_init_s          "init"
  #define CONTROLLER_kexec_s         "kexec"
  #define CONTROLLER_kill_s          "kill"
  #define CONTROLLER_length_s        "length"
  #define CONTROLLER_limit_s         "limit"
  #define CONTROLLER_locks_s         "locks"
  #define CONTROLLER_main_s          "main"
  #define CONTROLLER_max_s           "max"
  #define CONTROLLER_memlock_s       "memlock"
  #define CONTROLLER_method_s        "method"
  #define CONTROLLER_mode_s          "mode"
  #define CONTROLLER_msgqueue_s      "msgqueue"
  #define CONTROLLER_name_s          "name"
  #define CONTROLLER_need_s          "need"
  #define CONTROLLER_new_s           "new"
  #define CONTROLLER_nice_s          "nice"
  #define CONTROLLER_no_s            "no"
  #define CONTROLLER_nofile_s        "nofile"
  #define CONTROLLER_normal_s        "normal"
  #define CONTROLLER_nproc_s         "nproc"
  #define CONTROLLER_on_s            "on"
  #define CONTROLLER_optional_s      "optional"
  #define CONTROLLER_other_s         "other"
  #define CONTROLLER_parameter_s     "parameter"
  #define CONTROLLER_parameters_s    "parameters"
  #define CONTROLLER_path_s          "path"
  #define CONTROLLER_pause_s         "pause"
  #define CONTROLLER_payload_type_s  "# fss-000e\n"
  #define CONTROLLER_pid_s           "pid"
  #define CONTROLLER_pid_file_s      "pid_file"
  #define CONTROLLER_processor_s     "processor"
  #define CONTROLLER_program_s       "program"
  #define CONTROLLER_ready_s         "ready"
  #define CONTROLLER_reboot_s        "reboot"
  #define CONTROLLER_reload_s        "reload"
  #define CONTROLLER_require_s       "require"
  #define CONTROLLER_required_s      "required"
  #define CONTROLLER_rerun_s         "rerun"
  #define CONTROLLER_reset_s         "reset"
  #define CONTROLLER_restart_s       "restart"
  #define CONTROLLER_resume_s        "resume"
  #define CONTROLLER_round_robin_s   "round_robin"
  #define CONTROLLER_rss_s           "rss"
  #define CONTROLLER_rtprio_s        "rtprio"
  #define CONTROLLER_rttime_s        "rttime"
  #define CONTROLLER_rule_s          "rule"
  #define CONTROLLER_rules_s         "rules"
  #define CONTROLLER_same_s          "same"
  #define CONTROLLER_scheduler_s     "scheduler"
  #define CONTROLLER_script_s        "script"
  #define CONTROLLER_service_s       "service"
  #define CONTROLLER_session_s       "session"
  #define CONTROLLER_session_new_s   "session_new"
  #define CONTROLLER_session_same_s  "session_same"
  #define CONTROLLER_settings_s      "settings"
  #define CONTROLLER_sigpending_s    "sigpending"
  #define CONTROLLER_show_s          "show"
  #define CONTROLLER_shutdown_s      "shutdown"
  #define CONTROLLER_stack_s         "stack"
  #define CONTROLLER_start_s         "start"
  #define CONTROLLER_status_s        "status"
  #define CONTROLLER_stop_s          "stop"
  #define CONTROLLER_succeed_s       "succeed"
  #define CONTROLLER_success_s       "success"
  #define CONTROLLER_synchronous_s   "synchronous"
  #define CONTROLLER_thaw_s          "thaw"
  #define CONTROLLER_timeout_s       "timeout"
  #define CONTROLLER_type_s          "type"
  #define CONTROLLER_use_s           "use"
  #define CONTROLLER_user_s          "user"
  #define CONTROLLER_utility_s       "utility"
  #define CONTROLLER_value_s         "value"
  #define CONTROLLER_wait_s          "wait"
  #define CONTROLLER_want_s          "want"
  #define CONTROLLER_wish_s          "wish"
  #define CONTROLLER_with_s          "with"
  #define CONTROLLER_yes_s           "yes"

  #define CONTROLLER_Entry_s "Entry"
  #define CONTROLLER_Exit_s  "Exit"

  #define CONTROLLER_parameter_map_option_s ":option"
  #define CONTROLLER_parameter_map_value_s  ":value"

  #define CONTROLLER_action_s_length        6
  #define CONTROLLER_actions_s_length       7
  #define CONTROLLER_affinity_s_length      8
  #define CONTROLLER_as_s_length            2
  #define CONTROLLER_asynchronous_s_length  12
  #define CONTROLLER_bash_s_length          4
  #define CONTROLLER_batch_s_length         5
  #define CONTROLLER_capability_s_length    10
  #define CONTROLLER_cgroup_s_length        6
  #define CONTROLLER_create_s_length        6
  #define CONTROLLER_command_s_length       7
  #define CONTROLLER_consider_s_length      8
  #define CONTROLLER_control_s_length       7
  #define CONTROLLER_control_group_s_length 13
  #define CONTROLLER_control_mode_s_length  12
  #define CONTROLLER_control_user_s_length  12
  #define CONTROLLER_controller_s_length    10
  #define CONTROLLER_core_s_length          4
  #define CONTROLLER_cpu_s_length           3
  #define CONTROLLER_data_s_length          4
  #define CONTROLLER_deadline_s_length      8
  #define CONTROLLER_default_s_length       7
  #define CONTROLLER_define_s_length        6
  #define CONTROLLER_delay_s_length         5
  #define CONTROLLER_disable_s_length       7
  #define CONTROLLER_engine_s_length        6
  #define CONTROLLER_entry_s_length         5
  #define CONTROLLER_entries_s_length       7
  #define CONTROLLER_environment_s_length   11
  #define CONTROLLER_error_s_length         5
  #define CONTROLLER_existing_s_length      8
  #define CONTROLLER_execute_s_length       7
  #define CONTROLLER_exit_s_length          4
  #define CONTROLLER_exits_s_length         5
  #define CONTROLLER_fail_s_length          4
  #define CONTROLLER_failure_s_length       7
  #define CONTROLLER_failsafe_s_length      8
  #define CONTROLLER_fifo_s_length          4
  #define CONTROLLER_freeze_s_length        6
  #define CONTROLLER_fsize_s_length         5
  #define CONTROLLER_full_path_s_length     9
  #define CONTROLLER_group_s_length         5
  #define CONTROLLER_groups_s_length        6
  #define CONTROLLER_helper_s_length        6
  #define CONTROLLER_how_s_length           3
  #define CONTROLLER_idle_s_length          4
  #define CONTROLLER_iki_s_length           3
  #define CONTROLLER_init_s_length          4
  #define CONTROLLER_item_s_length          4
  #define CONTROLLER_kexec_s_length         5
  #define CONTROLLER_kill_s_length          4
  #define CONTROLLER_length_s_length        6
  #define CONTROLLER_limit_s_length         5
  #define CONTROLLER_locks_s_length         5
  #define CONTROLLER_main_s_length          4
  #define CONTROLLER_max_s_length           3
  #define CONTROLLER_memlock_s_length       7
  #define CONTROLLER_method_s_length        6
  #define CONTROLLER_mode_s_length          4
  #define CONTROLLER_msgqueue_s_length      8
  #define CONTROLLER_name_s_length          4
  #define CONTROLLER_need_s_length          4
  #define CONTROLLER_new_s_length           3
  #define CONTROLLER_nice_s_length          4
  #define CONTROLLER_no_s_length            2
  #define CONTROLLER_nofile_s_length        6
  #define CONTROLLER_normal_s_length        6
  #define CONTROLLER_nproc_s_length         5
  #define CONTROLLER_on_s_length            2
  #define CONTROLLER_optional_s_length      8
  #define CONTROLLER_other_s_length         5
  #define CONTROLLER_parameter_s_length     9
  #define CONTROLLER_parameters_s_length    10
  #define CONTROLLER_path_s_length          4
  #define CONTROLLER_pause_s_length         5
  #define CONTROLLER_payload_type_s_length  11
  #define CONTROLLER_pid_s_length           3
  #define CONTROLLER_pid_file_s_length      8
  #define CONTROLLER_processor_s_length     9
  #define CONTROLLER_program_s_length       7
  #define CONTROLLER_ready_s_length         5
  #define CONTROLLER_reboot_s_length        6
  #define CONTROLLER_reload_s_length        6
  #define CONTROLLER_require_s_length       7
  #define CONTROLLER_required_s_length      8
  #define CONTROLLER_rerun_s_length         5
  #define CONTROLLER_reset_s_length         5
  #define CONTROLLER_restart_s_length       7
  #define CONTROLLER_resume_s_length        6
  #define CONTROLLER_round_robin_s_length   11
  #define CONTROLLER_rss_s_length           3
  #define CONTROLLER_rtprio_s_length        6
  #define CONTROLLER_rttime_s_length        6
  #define CONTROLLER_rule_s_length          4
  #define CONTROLLER_rules_s_length         5
  #define CONTROLLER_same_s_length          4
  #define CONTROLLER_scheduler_s_length     9
  #define CONTROLLER_script_s_length        6
  #define CONTROLLER_service_s_length       7
  #define CONTROLLER_session_s_length       7
  #define CONTROLLER_session_new_s_length   11
  #define CONTROLLER_session_same_s_length  12
  #define CONTROLLER_settings_s_length      8
  #define CONTROLLER_show_s_length          4
  #define CONTROLLER_shutdown_s_length      8
  #define CONTROLLER_sigpending_s_length    10
  #define CONTROLLER_stack_s_length         5
  #define CONTROLLER_start_s_length         5
  #define CONTROLLER_status_s_length        6
  #define CONTROLLER_stop_s_length          4
  #define CONTROLLER_succeed_s_length       7
  #define CONTROLLER_success_s_length       7
  #define CONTROLLER_synchronous_s_length   11
  #define CONTROLLER_thaw_s_length          4
  #define CONTROLLER_timeout_s_length       7
  #define CONTROLLER_type_s_length          4
  #define CONTROLLER_use_s_length           3
  #define CONTROLLER_user_s_length          4
  #define CONTROLLER_utility_s_length       7
  #define CONTROLLER_value_s_length         5
  #define CONTROLLER_wait_s_length          4
  #define CONTROLLER_want_s_length          4
  #define CONTROLLER_wish_s_length          4
  #define CONTROLLER_with_s_length          4
  #define CONTROLLER_yes_s_length           3

  #define CONTROLLER_Entry_s_length 5
  #define CONTROLLER_Exit_s_length  4

  #define CONTROLLER_parameter_map_option_s_length 7
  #define CONTROLLER_parameter_map_value_s_length  6

  extern const f_string_static_t controller_action_s;
  extern const f_string_static_t controller_actions_s;
  extern const f_string_static_t controller_affinity_s;
  extern const f_string_static_t controller_as_s;
  extern const f_string_static_t controller_asynchronous_s;
  extern const f_string_static_t controller_bash_s;
  extern const f_string_static_t controller_batch_s;
  extern const f_string_static_t controller_capability_s;
  extern const f_string_static_t controller_cgroup_s;
  extern const f_string_static_t controller_create_s;
  extern const f_string_static_t controller_command_s;
  extern const f_string_static_t controller_consider_s;
  extern const f_string_static_t controller_control_s;
  extern const f_string_static_t controller_control_group_s;
  extern const f_string_static_t controller_control_mode_s;
  extern const f_string_static_t controller_control_user_s;
  extern const f_string_static_t controller_controller_s;
  extern const f_string_static_t controller_core_s;
  extern const f_string_static_t controller_cpu_s;
  extern const f_string_static_t controller_data_s;
  extern const f_string_static_t controller_deadline_s;
  extern const f_string_static_t controller_default_s;
  extern const f_string_static_t controller_define_s;
  extern const f_string_static_t controller_delay_s;
  extern const f_string_static_t controller_disable_s;
  extern const f_string_static_t controller_engine_s;
  extern const f_string_static_t controller_entry_s;
  extern const f_string_static_t controller_entries_s;
  extern const f_string_static_t controller_environment_s;
  extern const f_string_static_t controller_error_s;
  extern const f_string_static_t controller_existing_s;
  extern const f_string_static_t controller_execute_s;
  extern const f_string_static_t controller_exit_s;
  extern const f_string_static_t controller_exits_s;
  extern const f_string_static_t controller_fail_s;
  extern const f_string_static_t controller_failsafe_s;
  extern const f_string_static_t controller_failure_s;
  extern const f_string_static_t controller_fifo_s;
  extern const f_string_static_t controller_freeze_s;
  extern const f_string_static_t controller_fsize_s;
  extern const f_string_static_t controller_full_path_s;
  extern const f_string_static_t controller_group_s;
  extern const f_string_static_t controller_groups_s;
  extern const f_string_static_t controller_helper_s;
  extern const f_string_static_t controller_how_s;
  extern const f_string_static_t controller_idle_s;
  extern const f_string_static_t controller_iki_s;
  extern const f_string_static_t controller_init_s;
  extern const f_string_static_t controller_item_s;
  extern const f_string_static_t controller_kexec_s;
  extern const f_string_static_t controller_kill_s;
  extern const f_string_static_t controller_length_s;
  extern const f_string_static_t controller_limit_s;
  extern const f_string_static_t controller_locks_s;
  extern const f_string_static_t controller_main_s;
  extern const f_string_static_t controller_max_s;
  extern const f_string_static_t controller_memlock_s;
  extern const f_string_static_t controller_method_s;
  extern const f_string_static_t controller_mode_s;
  extern const f_string_static_t controller_msgqueue_s;
  extern const f_string_static_t controller_name_s;
  extern const f_string_static_t controller_need_s;
  extern const f_string_static_t controller_new_s;
  extern const f_string_static_t controller_nice_s;
  extern const f_string_static_t controller_no_s;
  extern const f_string_static_t controller_nofile_s;
  extern const f_string_static_t controller_normal_s;
  extern const f_string_static_t controller_nproc_s;
  extern const f_string_static_t controller_on_s;
  extern const f_string_static_t controller_optional_s;
  extern const f_string_static_t controller_other_s;
  extern const f_string_static_t controller_parameter_s;
  extern const f_string_static_t controller_parameters_s;
  extern const f_string_static_t controller_path_s;
  extern const f_string_static_t controller_pause_s;
  extern const f_string_static_t controller_payload_type_s;
  extern const f_string_static_t controller_pid_s;
  extern const f_string_static_t controller_pid_file_s;
  extern const f_string_static_t controller_processor_s;
  extern const f_string_static_t controller_program_s;
  extern const f_string_static_t controller_ready_s;
  extern const f_string_static_t controller_reboot_s;
  extern const f_string_static_t controller_reload_s;
  extern const f_string_static_t controller_require_s;
  extern const f_string_static_t controller_required_s;
  extern const f_string_static_t controller_rerun_s;
  extern const f_string_static_t controller_reset_s;
  extern const f_string_static_t controller_restart_s;
  extern const f_string_static_t controller_resume_s;
  extern const f_string_static_t controller_round_robin_s;
  extern const f_string_static_t controller_rss_s;
  extern const f_string_static_t controller_rtprio_s;
  extern const f_string_static_t controller_rttime_s;
  extern const f_string_static_t controller_rule_s;
  extern const f_string_static_t controller_rules_s;
  extern const f_string_static_t controller_same_s;
  extern const f_string_static_t controller_scheduler_s;
  extern const f_string_static_t controller_script_s;
  extern const f_string_static_t controller_service_s;
  extern const f_string_static_t controller_session_s;
  extern const f_string_static_t controller_session_new_s;
  extern const f_string_static_t controller_session_same_s;
  extern const f_string_static_t controller_settings_s;
  extern const f_string_static_t controller_show_s;
  extern const f_string_static_t controller_shutdown_s;
  extern const f_string_static_t controller_sigpending_s;
  extern const f_string_static_t controller_stack_s;
  extern const f_string_static_t controller_start_s;
  extern const f_string_static_t controller_status_s;
  extern const f_string_static_t controller_stop_s;
  extern const f_string_static_t controller_succeed_s;
  extern const f_string_static_t controller_success_s;
  extern const f_string_static_t controller_synchronous_s;
  extern const f_string_static_t controller_thaw_s;
  extern const f_string_static_t controller_timeout_s;
  extern const f_string_static_t controller_type_s;
  extern const f_string_static_t controller_use_s;
  extern const f_string_static_t controller_user_s;
  extern const f_string_static_t controller_utility_s;
  extern const f_string_static_t controller_value_s;
  extern const f_string_static_t controller_wait_s;
  extern const f_string_static_t controller_want_s;
  extern const f_string_static_t controller_wish_s;
  extern const f_string_static_t controller_with_s;
  extern const f_string_static_t controller_yes_s;

  extern const f_string_static_t controller_Entry_s;
  extern const f_string_static_t controller_Exit_s;

  extern const f_string_static_t controller_parameter_map_option_s;
  extern const f_string_static_t controller_parameter_map_value_s;
#endif // _di_controller_string_s_

/**
 * Provide common/generic definitions.
 *
 * The controller_common_allocation_large_d or controller_common_allocation_small_d must be at least 2 for this project.
 *
 * controller_common_allocation_*:
 *   - iki_large: An allocation step used for IKI buffers that are anticipated to have large buffers.
 *   - iki_small: An allocation step used for IKI buffers that are anticipated to have small buffers.
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_controller_common_
  #define controller_common_allocation_iki_large_d 128
  #define controller_common_allocation_iki_small_d 8
  #define controller_common_allocation_large_d     256
  #define controller_common_allocation_small_d     16
#endif // _di_controller_common_

/**
 * A set of codes representing different with flags.
 */
#ifndef _di_controller_with_defines_
  #define controller_with_full_path_d    0x1
  #define controller_with_session_new_d  0x2
  #define controller_with_session_same_d 0x4
#endif // _di_controller_with_defines_

/**
 * A wrapper used for passing a common set of all data, particularly for sharing between threads.
 *
 * main:    The main program data.
 * setting: All loaded settings.
 * thread:  All thread related data.
 */
#ifndef _di_controller_main_t_
  typedef struct {
    controller_main_t *main;
    controller_setting_t *setting;
    controller_thread_t *thread;
  } controller_global_t;

  #define controller_global_t_initialize { 0, 0, 0 }

  #define macro_controller_global_t_initialize(main, setting, thread) { \
    main, \
    setting, \
    thread, \
  }
#endif // _di_controller_main_t_

/**
 * A wrapper used for passing a set of entry processing and execution related data.
 *
 * global:  All data globally shared.
 * setting: The setting data.
 */
#ifndef _di_controller_main_entry_t_
  typedef struct {
    controller_global_t *global;
    controller_setting_t *setting;
  } controller_main_entry_t;

  #define controller_main_entry_t_initialize { 0, 0 }

  #define macro_controller_main_entry_t_initialize(global, setting) { \
    global, \
    setting, \
  }
#endif // _di_controller_main_entry_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
