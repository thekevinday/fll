/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

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
  #define CONTROLLER_create_s        "create"
  #define CONTROLLER_command_s       "command"
  #define CONTROLLER_consider_s      "consider"
  #define CONTROLLER_control_s       "control"
  #define CONTROLLER_control_group_s "control_group"
  #define CONTROLLER_cpu_s           "cpu"
  #define CONTROLLER_core_s          "core"
  #define CONTROLLER_data_s          "data"
  #define CONTROLLER_deadline_s      "deadline"
  #define CONTROLLER_default_s       "default"
  #define CONTROLLER_define_s        "define"
  #define CONTROLLER_delay_s         "delay"
  #define CONTROLLER_disable_s       "disable"
  #define CONTROLLER_entry_s         "entry"
  #define CONTROLLER_entries_s       "entries"
  #define CONTROLLER_environment_s   "environment"
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
  #define CONTROLLER_how_s           "how"
  #define CONTROLLER_idle_s          "idle"
  #define CONTROLLER_item_s          "item"
  #define CONTROLLER_init_s          "init"
  #define CONTROLLER_kill_s          "kill"
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
  #define CONTROLLER_pid_s           "pid"
  #define CONTROLLER_pid_file_s      "pid_file"
  #define CONTROLLER_processor_s     "processor"
  #define CONTROLLER_program_s       "program"
  #define CONTROLLER_ready_s         "ready"
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
  #define CONTROLLER_setting_s       "setting"
  #define CONTROLLER_sigpending_s    "sigpending"
  #define CONTROLLER_show_s          "show"
  #define CONTROLLER_stack_s         "stack"
  #define CONTROLLER_start_s         "start"
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

  #define controller_action_s_length        6
  #define controller_actions_s_length       7
  #define controller_affinity_s_length      8
  #define controller_as_s_length            2
  #define controller_asynchronous_s_length  12
  #define controller_bash_s_length          4
  #define controller_batch_s_length         5
  #define controller_capability_s_length    10
  #define controller_create_s_length        6
  #define controller_command_s_length       7
  #define controller_consider_s_length      8
  #define controller_control_s_length       7
  #define controller_control_group_s_length 13
  #define controller_core_s_length          4
  #define controller_cpu_s_length           3
  #define controller_data_s_length          4
  #define controller_deadline_s_length      8
  #define controller_default_s_length       7
  #define controller_define_s_length        6
  #define controller_delay_s_length         5
  #define controller_disable_s_length       7
  #define controller_entry_s_length         5
  #define controller_entries_s_length       7
  #define controller_environment_s_length   11
  #define controller_existing_s_length      8
  #define controller_execute_s_length       7
  #define controller_exit_s_length          4
  #define controller_exits_s_length         5
  #define controller_fail_s_length          4
  #define controller_failure_s_length       7
  #define controller_failsafe_s_length      8
  #define controller_fifo_s_length          4
  #define controller_freeze_s_length        6
  #define controller_fsize_s_length         5
  #define controller_full_path_s_length     9
  #define controller_group_s_length         5
  #define controller_groups_s_length        6
  #define controller_how_s_length           3
  #define controller_idle_s_length          4
  #define controller_init_s_length          4
  #define controller_item_s_length          4
  #define controller_kill_s_length          4
  #define controller_limit_s_length         5
  #define controller_locks_s_length         5
  #define controller_main_s_length          4
  #define controller_max_s_length           3
  #define controller_memlock_s_length       7
  #define controller_method_s_length        6
  #define controller_mode_s_length          4
  #define controller_msgqueue_s_length      8
  #define controller_name_s_length          4
  #define controller_need_s_length          4
  #define controller_new_s_length           3
  #define controller_nice_s_length          4
  #define controller_no_s_length            2
  #define controller_nofile_s_length        6
  #define controller_normal_s_length        6
  #define controller_nproc_s_length         5
  #define controller_on_s_length            2
  #define controller_optional_s_length      8
  #define controller_other_s_length         5
  #define controller_parameter_s_length     9
  #define controller_parameters_s_length    10
  #define controller_path_s_length          4
  #define controller_pause_s_length         5
  #define controller_pid_s_length           3
  #define controller_pid_file_s_length      8
  #define controller_processor_s_length     9
  #define controller_program_s_length       7
  #define controller_ready_s_length         5
  #define controller_reload_s_length        6
  #define controller_require_s_length       7
  #define controller_required_s_length      8
  #define controller_rerun_s_length         5
  #define controller_reset_s_length         5
  #define controller_restart_s_length       7
  #define controller_resume_s_length        6
  #define controller_round_robin_s_length   11
  #define controller_rss_s_length           3
  #define controller_rtprio_s_length        6
  #define controller_rttime_s_length        6
  #define controller_rule_s_length          4
  #define controller_rules_s_length         5
  #define controller_same_s_length          4
  #define controller_scheduler_s_length     9
  #define controller_script_s_length        6
  #define controller_service_s_length       7
  #define controller_session_s_length       7
  #define controller_session_new_s_length   11
  #define controller_session_same_s_length  12
  #define controller_setting_s_length       7
  #define controller_show_s_length          4
  #define controller_sigpending_s_length    10
  #define controller_stack_s_length         5
  #define controller_start_s_length         5
  #define controller_stop_s_length          4
  #define controller_succeed_s_length       7
  #define controller_success_s_length       7
  #define controller_synchronous_s_length   11
  #define controller_thaw_s_length          4
  #define controller_timeout_s_length       7
  #define controller_type_s_length          4
  #define controller_use_s_length           3
  #define controller_user_s_length          4
  #define controller_utility_s_length       7
  #define controller_value_s_length         5
  #define controller_wait_s_length          4
  #define controller_want_s_length          4
  #define controller_wish_s_length          4
  #define controller_with_s_length          4
  #define controller_yes_s_length           3

  extern const f_string_t controller_action_s;
  extern const f_string_t controller_actions_s;
  extern const f_string_t controller_affinity_s;
  extern const f_string_t controller_as_s;
  extern const f_string_t controller_asynchronous_s;
  extern const f_string_t controller_bash_s;
  extern const f_string_t controller_batch_s;
  extern const f_string_t controller_capability_s;
  extern const f_string_t controller_create_s;
  extern const f_string_t controller_command_s;
  extern const f_string_t controller_consider_s;
  extern const f_string_t controller_control_s;
  extern const f_string_t controller_control_group_s;
  extern const f_string_t controller_core_s;
  extern const f_string_t controller_cpu_s;
  extern const f_string_t controller_data_s;
  extern const f_string_t controller_deadline_s;
  extern const f_string_t controller_default_s;
  extern const f_string_t controller_define_s;
  extern const f_string_t controller_delay_s;
  extern const f_string_t controller_disable_s;
  extern const f_string_t controller_entry_s;
  extern const f_string_t controller_entries_s;
  extern const f_string_t controller_environment_s;
  extern const f_string_t controller_existing_s;
  extern const f_string_t controller_execute_s;
  extern const f_string_t controller_exit_s;
  extern const f_string_t controller_exits_s;
  extern const f_string_t controller_fail_s;
  extern const f_string_t controller_failsafe_s;
  extern const f_string_t controller_failure_s;
  extern const f_string_t controller_fifo_s;
  extern const f_string_t controller_freeze_s;
  extern const f_string_t controller_fsize_s;
  extern const f_string_t controller_full_path_s;
  extern const f_string_t controller_group_s;
  extern const f_string_t controller_groups_s;
  extern const f_string_t controller_how_s;
  extern const f_string_t controller_idle_s;
  extern const f_string_t controller_init_s;
  extern const f_string_t controller_item_s;
  extern const f_string_t controller_kill_s;
  extern const f_string_t controller_limit_s;
  extern const f_string_t controller_locks_s;
  extern const f_string_t controller_main_s;
  extern const f_string_t controller_max_s;
  extern const f_string_t controller_memlock_s;
  extern const f_string_t controller_method_s;
  extern const f_string_t controller_mode_s;
  extern const f_string_t controller_msgqueue_s;
  extern const f_string_t controller_name_s;
  extern const f_string_t controller_need_s;
  extern const f_string_t controller_new_s;
  extern const f_string_t controller_nice_s;
  extern const f_string_t controller_no_s;
  extern const f_string_t controller_nofile_s;
  extern const f_string_t controller_normal_s;
  extern const f_string_t controller_nproc_s;
  extern const f_string_t controller_on_s;
  extern const f_string_t controller_optional_s;
  extern const f_string_t controller_other_s;
  extern const f_string_t controller_parameter_s;
  extern const f_string_t controller_parameters_s;
  extern const f_string_t controller_path_s;
  extern const f_string_t controller_pause_s;
  extern const f_string_t controller_pid_s;
  extern const f_string_t controller_pid_file_s;
  extern const f_string_t controller_processor_s;
  extern const f_string_t controller_program_s;
  extern const f_string_t controller_ready_s;
  extern const f_string_t controller_reload_s;
  extern const f_string_t controller_require_s;
  extern const f_string_t controller_required_s;
  extern const f_string_t controller_rerun_s;
  extern const f_string_t controller_reset_s;
  extern const f_string_t controller_restart_s;
  extern const f_string_t controller_resume_s;
  extern const f_string_t controller_round_robin_s;
  extern const f_string_t controller_rss_s;
  extern const f_string_t controller_rtprio_s;
  extern const f_string_t controller_rttime_s;
  extern const f_string_t controller_rule_s;
  extern const f_string_t controller_rules_s;
  extern const f_string_t controller_same_s;
  extern const f_string_t controller_scheduler_s;
  extern const f_string_t controller_script_s;
  extern const f_string_t controller_service_s;
  extern const f_string_t controller_session_s;
  extern const f_string_t controller_session_new_s;
  extern const f_string_t controller_session_same_s;
  extern const f_string_t controller_setting_s;
  extern const f_string_t controller_show_s;
  extern const f_string_t controller_sigpending_s;
  extern const f_string_t controller_stack_s;
  extern const f_string_t controller_start_s;
  extern const f_string_t controller_stop_s;
  extern const f_string_t controller_succeed_s;
  extern const f_string_t controller_success_s;
  extern const f_string_t controller_synchronous_s;
  extern const f_string_t controller_thaw_s;
  extern const f_string_t controller_timeout_s;
  extern const f_string_t controller_type_s;
  extern const f_string_t controller_use_s;
  extern const f_string_t controller_user_s;
  extern const f_string_t controller_utility_s;
  extern const f_string_t controller_value_s;
  extern const f_string_t controller_wait_s;
  extern const f_string_t controller_want_s;
  extern const f_string_t controller_wish_s;
  extern const f_string_t controller_with_s;
  extern const f_string_t controller_yes_s;
#endif // _di_controller_string_s_

/**
 * A set of codes for resource limitations.
 *
 * This essentally converts the POSIX standard names into a more verbose format.
 */
#ifndef _di_controller_resource_limit_t_
  enum {
    controller_resource_limit_type_as = RLIMIT_AS,
    controller_resource_limit_type_core = RLIMIT_CORE,
    controller_resource_limit_type_cpu = RLIMIT_CPU,
    controller_resource_limit_type_data = RLIMIT_DATA,
    controller_resource_limit_type_fsize = RLIMIT_FSIZE,
    controller_resource_limit_type_locks = RLIMIT_LOCKS,
    controller_resource_limit_type_memlock = RLIMIT_MEMLOCK,
    controller_resource_limit_type_msgqueue = RLIMIT_MSGQUEUE,
    controller_resource_limit_type_nice = RLIMIT_NICE,
    controller_resource_limit_type_nofile = RLIMIT_NOFILE,
    controller_resource_limit_type_nproc = RLIMIT_NPROC,
    controller_resource_limit_type_rss = RLIMIT_RSS,
    controller_resource_limit_type_rtprio = RLIMIT_RTPRIO,
    controller_resource_limit_type_rttime = RLIMIT_RTTIME,
    controller_resource_limit_type_sigpending = RLIMIT_SIGPENDING,
    controller_resource_limit_type_stack = RLIMIT_STACK,
  };
#endif // _di_controller_resource_limit_t_

/**
 * Provide common/generic definitions.
 *
 * The controller_common_allocation_large_d or controller_common_allocation_small_d must be at least 2 for this project.
 *
 * controller_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_controller_common_
  #define controller_common_allocation_large_d 256
  #define controller_common_allocation_small_d 16
#endif // _di_controller_common_

/**
 * Action related cache.
 *
 * line_action: The line in some file representing an Action.
 * line_item:   The line in some file representing an Item.
 * name_action: A NULL terminated name of some Action.
 * name_file:   A NULL terminated name of some File.
 * name_item:   A NULL terminated name of some Item.
 * generic:     A NULL terminated string for general use.
 */
#ifndef _di_controller_cache_action_t_
  typedef struct {
    f_array_length_t line_action;
    f_array_length_t line_item;

    f_string_dynamic_t name_action;
    f_string_dynamic_t name_file;
    f_string_dynamic_t name_item;

    f_string_dynamic_t generic;
  } controller_cache_action_t;

  #define controller_cache_action_t_initialize { \
    0, \
    0, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
  }

  #define macro_controller_cache_action_t_clear(cache) \
    cache.line_action = 0; \
    cache.line_item = 0; \
    macro_f_string_dynamic_t_clear(cache.name_action) \
    macro_f_string_dynamic_t_clear(cache.name_file) \
    macro_f_string_dynamic_t_clear(cache.name_item) \
    macro_f_string_dynamic_t_clear(cache.generic)
#endif // _di_controller_cache_action_t_

/**
 * A cache intended for re-using memory while loading and processing rules whenever possible.
 *
 * timestamp:       The timestamp.
 * range_action:    The Range for some Action.
 * ats:             Locations.
 * stack:           Locations within a items history used as a history stack for circular recursion prevention.
 * comments:        Comments associated with a buffer string.
 * delimits:        Delimits associated with a buffer string.
 * content_action:  The specific Content for some Action.
 * content_actions: Content for some Action.
 * content_items:   Content for some Item.
 * object_actions:  Objects for some Action.
 * object_items:    Objects for some Item.
 * buffer_file:     A generic file related buffer.
 * buffer_item:     A generic item related buffer.
 * buffer_path:     A generic path related buffer.
 * action:          A cache for some Action, often used by error printing for reporting where an error happened.
 */
#ifndef _di_controller_cache_t_
  typedef struct {
    f_time_spec_t timestamp;

    f_string_range_t range_action;

    f_array_lengths_t ats;
    f_array_lengths_t stack;

    f_fss_comments_t comments;
    f_fss_delimits_t delimits;

    f_fss_content_t content_action;
    f_fss_contents_t content_actions;
    f_fss_contents_t content_items;
    f_fss_objects_t object_actions;
    f_fss_objects_t object_items;

    f_string_dynamic_t buffer_file;
    f_string_dynamic_t buffer_item;
    f_string_dynamic_t buffer_path;

    controller_cache_action_t action;
  } controller_cache_t;

  #define controller_cache_t_initialize { \
    f_time_spec_t_initialize, \
    f_string_range_t_initialize, \
    f_array_lengths_t_initialize, \
    f_array_lengths_t_initialize, \
    f_fss_comments_t_initialize, \
    f_fss_delimits_t_initialize, \
    f_fss_content_t_initialize, \
    f_fss_contents_t_initialize, \
    f_fss_contents_t_initialize, \
    f_fss_objects_t_initialize, \
    f_fss_objects_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    controller_cache_action_t_initialize, \
  }
#endif // _di_controller_cache_t_

/**
 * A structure for passing execution arguments to the execute functions.
 *
 * parameter: All parameters sent to the program on execution.
 * as:        All special properties to apply, such as cpu affinity.
 */
#ifndef _di_controller_execute_set_t_
  typedef struct {
    fl_execute_parameter_t parameter;
    fl_execute_as_t as;
  } controller_execute_set_t;

  #define controller_execute_set_t_initialize { \
    fl_execute_parameter_t_initialize, \
    fl_execute_as_t_initialize \
  }

  #define macro_controller_execute_set_t_initialize(option, wait, environment, signals, main, as) { \
    macro_fl_execute_parameter_t_initialize(option, wait, environment, signals, main), \
    as, \
  }
#endif // _di_controller_execute_set_t_

/**
 * A structure for sharing mutexes globally between different threads.
 *
 * The print lock is intended to lock any activity printing to stdout/stderr.
 * The alert lock is intended for a generic waiting on alerts operations.
 * The process lock is intended to lock any activity on the processs structure.
 * The rule lock is intended to lock any activity on the rules structure.
 *
 * print:           The print mutex lock.
 * alert:           The alert mutex lock for waking up on alerts.
 * process:         The process r/w lock.
 * rule:            The rule r/w lock.
 * alert_condition: The condition used to trigger alerts.
 */
#ifndef _di_controller_lock_t_
  typedef struct {
    f_thread_mutex_t print;
    f_thread_mutex_t alert;

    f_thread_lock_t process;
    f_thread_lock_t rule;

    f_thread_condition_t alert_condition;
  } controller_lock_t;

  #define controller_lock_t_initialize { \
    f_thread_mutex_t_initialize, \
    f_thread_mutex_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_condition_t_initialize, \
  }
#endif // _di_controller_mutex_t_

/**
 * The Rule "rerun" item for controlling re-execution.
 *
 * count: A count of the number of executions.
 * delay: The time to wait before attempting to re-run.
 * max:   The maximum number of times to re-run (with 0 representing re-run infinitely) for executions.
 */
#ifndef _di_controller_rule_rerun_item_t_
  typedef struct {
    bool reset;

    f_number_unsigned_t count;
    f_number_unsigned_t delay;
    f_number_unsigned_t max;
  } controller_rule_rerun_item_t;

  #define controller_rule_rerun_item_initialize { \
    F_false, \
    0, \
    5000, \
    0, \
  }
#endif // _di_controller_rule_rerun_item_t_

/**
 * The Rule "rerun" values for controlling re-execution.
 *
 * controller_rule_rerun_is_*:
 *   - failure:       The success re-run is enabled.
 *   - failure_reset: Reset success counter when failure is returned.
 *   - success:       The success re-run is enabled.
 *   - success_reset: Reset failure counter when success is returned.
 *
 * is:            A bitwise set of options to designate whether rerun is enabled or not and other options.
 * count_failure: A count of the number of failed executions.
 * count_success: A count of the number of successful executions.
 * delay_failure: The time to wait before attempting to "rerun" for failed executions.
 * delay_success: The time to wait before attempting to "rerun" for successful executions.
 * max_failure:   The maximum number of times to "rerun" (with 0 representing "rerun" infinitely) for failed executions.
 * max_success:   The maximum number of times to "rerun" (with 0 representing "rerun" infinitely) for successful executions.
 */
#ifndef _di_controller_rule_rerun_t_
  #define controller_rule_rerun_is_failure_d       0x1
  #define controller_rule_rerun_is_failure_reset_d 0x2
  #define controller_rule_rerun_is_success_d       0x4
  #define controller_rule_rerun_is_success_reset_d 0x8

  typedef struct {
    uint8_t is;

    controller_rule_rerun_item_t failure;
    controller_rule_rerun_item_t success;
  } controller_rule_rerun_t;

  #define controller_rule_rerun_initialize { \
    0, \
    controller_rule_rerun_item_initialize, \
    controller_rule_rerun_item_initialize, \
  }
#endif // _di_controller_rule_rerun_t_

/**
 * A Rule Action.
 *
 * controller_rule_action_method_*:
 *   - extended:      Designate that this Action is represented using FSS Extended.
 *   - extended_list: Designate that this Action is represented using FSS Extended List.
 *
 * controller_rule_action_type_*:
 *   - freeze:   The Freeze execution instructions.
 *   - group:    The Group setting.
 *   - kill:     The Kill execution instructions.
 *   - pause:    The Pause execution instructions.
 *   - pid_file: The PID file setting.
 *   - rerun:    The Re-run execution after success or failure.
 *   - reload:   The Reload execution instructions.
 *   - restart:  The Restart execution instructions.
 *   - resume:   The Resume execution instructions.
 *   - start:    The Start execution instructions.
 *   - stop:     The Stop execution instructions.
 *   - thaw:     The Thaw execution instructions.
 *   - user:     The User setting.
 *   - with:     The With flags.
 *
 * type:       The Rule Action type.
 * line:       The line number where the Rule Action begins.
 * status:     The last execution status of the Rule Action.
 * parameters: All parameters associated with the Rule Action.
 */
#ifndef _di_controller_rule_action_t_
  #define controller_rule_action_method_string_extended_s      "FSS-0001 (Extended)"
  #define controller_rule_action_method_string_extended_list_s "FSS-0003 (Extended List)"

  #define controller_rule_action_method_string_extended_s_length      19
  #define controller_rule_action_method_string_extended_list_s_length 24

  enum {
    controller_rule_action_method_extended = 1,
    controller_rule_action_method_extended_list,
  };

  enum {
    controller_rule_action_type_freeze = 1,
    controller_rule_action_type_group,
    controller_rule_action_type_kill,
    controller_rule_action_type_pause,
    controller_rule_action_type_pid_file,
    controller_rule_action_type_reload,
    controller_rule_action_type_rerun,
    controller_rule_action_type_restart,
    controller_rule_action_type_resume,
    controller_rule_action_type_start,
    controller_rule_action_type_stop,
    controller_rule_action_type_thaw,
    controller_rule_action_type_user,
    controller_rule_action_type_with,

    // designate the largest value in the enum, the '__' is intended.
    controller_rule_action_type__enum_size,
  };

  enum {
    controller_rule_action_type_execute_freeze = 0,
    controller_rule_action_type_execute_kill,
    controller_rule_action_type_execute_pause,
    controller_rule_action_type_execute_reload,
    controller_rule_action_type_execute_restart,
    controller_rule_action_type_execute_resume,
    controller_rule_action_type_execute_start,
    controller_rule_action_type_execute_stop,
    controller_rule_action_type_execute_thaw,

    // designate the largest value in the enum, the '__' is intended.
    controller_rule_action_type_execute__enum_size,
  };

  typedef struct {
    uint8_t type;
    f_array_length_t line;
    f_status_t status;

    f_string_dynamics_t parameters;
  } controller_rule_action_t;

  #define controller_rule_action_t_initialize { \
    0, \
    0, \
    F_known_not, \
    f_string_dynamics_t_initialize, \
  }
#endif // _di_controller_rule_action_t_

/**
 * The Rule Actions.
 *
 * array: An array of Rule Actions.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_rule_actions_t_
  typedef struct {
    controller_rule_action_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rule_actions_t;

  #define controller_rule_actions_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rule_actions_t_

/**
 * A Rule Item.
 *
 * controller_rule_item_type_*:
 *   - command: A Command to execute.
 *   - script:  A Script to execute.
 *   - service: A Service to execute.
 *   - setting: Settings associated with the Rule Item.
 *   - utility: A Utility to execute.
 *
 * type:    The type of the Rule Item.
 * with:    A bitwise number representing execute "with" options.
 * line:    The line number where the Rule Item begins.
 * reruns:  An array designating rerun settings for each execution type available.
 * actions: The actions associated with the Rule Item.
 */
#ifndef _di_controller_rule_item_t_
  enum {
    controller_rule_item_type_command = 1,
    controller_rule_item_type_script,
    controller_rule_item_type_service,
    controller_rule_item_type_setting,
    controller_rule_item_type_utility,
  };

  typedef struct {
    uint8_t type;
    uint8_t with;
    f_array_length_t line;

    f_string_dynamic_t pid_file;
    controller_rule_rerun_t reruns[controller_rule_action_type_execute__enum_size];
    controller_rule_actions_t actions;
  } controller_rule_item_t;

  #define controller_rule_item_t_initialize \
    { \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      { \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
        controller_rule_rerun_t_initialize, \
      }, \
      controller_rule_actions_t_initialize, \
    }
#endif // _di_controller_rule_item_t_

/**
 * The Rule Items.
 *
 * array: An array of Rule Items.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_rule_items_t_
  typedef struct {
    controller_rule_item_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rule_items_t;

  #define controller_rule_items_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rule_items_t_

/**
 * The Rule "on" values for designating dependencies.
 *
 * action: The Rule Action type this "on" dependencies are associated with.
 * need:   The Rule Alias for a required Rule.
 * want:   The Rule Alias for an optional Rule that is required to succeed if found.
 * wish:   The Rule Alias for an optional Rule that is not required.
 */
#ifndef _di_controller_rule_on_t_
  typedef struct {
    uint8_t action;

    f_string_dynamics_t need;
    f_string_dynamics_t want;
    f_string_dynamics_t wish;
  } controller_rule_on_t;

  #define controller_rule_on_initialize { \
    0, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
  }
#endif // _di_controller_rule_on_t_

/**
 * The Rule "on" array.
 *
 * array: An array of Rule "on" values.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_rule_ons_t_
  typedef struct {
    controller_rule_on_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rule_ons_t;

  #define controller_rule_ons_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rule_ons_t_

/**
 * A Rule.
 *
 * controller_rule_setting_type_*:
 *   - affinity:      Setting type representing a affinity.
 *   - capability:    Setting type representing a capability.
 *   - control_group: Setting type representing a control group.
 *   - define:        Setting type representing a define.
 *   - environment:   Setting type representing a environment.
 *   - group:         Setting type representing a group.
 *   - limit:         Setting type representing a limit.
 *   - name:          Setting type representing a name.
 *   - nice:          Setting type representing a nice.
 *   - on:            Setting type representing a on.
 *   - parameter:     Setting type representing a parameter.
 *   - path:          Setting type representing a path.
 *   - scheduler:     Setting type representing a scheduler.
 *   - script:        Setting type representing a script.
 *   - user:          Setting type representing a user.
 *
 * controller_rule_has_*:
 *   - control_group: Has type representing a control group.
 *   - group:         Has type representing a group.
 *   - nice:          Has type representing a nice.
 *   - scheduler:     Has type representing a scheduler.
 *   - user:          Has type representing a user.
 *
 * affinity:      The cpu affinity to be used when executing the Rule.
 * alias:         The distinct ID (machine name) of the rule, such as "service/ssh".
 * capability:    The capability setting if the Rule "has" a capability.
 * control_group: The control group setting if the Rule "has" a control group.
 * define:        Any defines (environment variables) made available to the Rule for IKI substitution or just as environment variables.
 * environment:   All environment variables allowed to be exposed to the Rule when processing.
 * group:         The group ID if the Rule "has" a group.
 * groups:        A set of group IDs to run the process with (first specified group is the primary group).
 * has:           Bitwise set of "has" codes representing what the Rule has.
 * items:         All items associated with the Rule.
 * limits:        The cpu/resource limits to use when executing the Rule.
 * name:          A human name for the Rule (does not have to be distinct), such as "Bash Script".
 * nice:          The niceness value if the Rule "has" nice.
 * on:            A set of parameters for defining dependencies and how they are needed, wanted, or wished for.
 * parameter:     Any parameters made available to the Rule for IKI substitution.
 * path:          The path to the Rule file.
 * scheduler:     The scheduler setting if the Rule "has" a scheduler.
 * script:        The program or path to the program of the scripting engine to use when processing scripts in this Rule.
 * status:        A set of action-specific success/failure status of the Rule. Each index represents a controller_rule_action_type_* enum value. Index 0 represents a global status.
 * timeout_kill:  The timeout to wait relating to using a kill signal.
 * timeout_start: The timeout to wait relating to starting a process.
 * timeout_stop:  The timeout to wait relating to stopping a process.
 * timestamp:     The timestamp when the Rule was loaded.
 * user:          The User ID if the Rule "has" a user.
 */
#ifndef _di_controller_rule_t_
  enum {
    controller_rule_setting_type_affinity = 1,
    controller_rule_setting_type_capability,
    controller_rule_setting_type_control_group,
    controller_rule_setting_type_define,
    controller_rule_setting_type_environment,
    controller_rule_setting_type_group,
    controller_rule_setting_type_limit,
    controller_rule_setting_type_name,
    controller_rule_setting_type_nice,
    controller_rule_setting_type_on,
    controller_rule_setting_type_parameter,
    controller_rule_setting_type_path,
    controller_rule_setting_type_scheduler,
    controller_rule_setting_type_script,
    controller_rule_setting_type_timeout,
    controller_rule_setting_type_user,
  };

  // bitwise codes representing properties on controller_rule_t that have been found in the rule file.
  #define controller_rule_has_control_group_d 0x1
  #define controller_rule_has_environment_d   0x2
  #define controller_rule_has_group_d         0x4
  #define controller_rule_has_nice_d          0x8
  #define controller_rule_has_scheduler_d     0x10
  #define controller_rule_has_user_d          0x20

  // Designate codes for timeout settings to be used during the loading of the rule timeout settings.
  #define controller_rule_timeout_code_kill_d  1
  #define controller_rule_timeout_code_start_d 2
  #define controller_rule_timeout_code_stop_d  3

  typedef struct {
    f_status_t status[controller_rule_action_type__enum_size];

    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    uint8_t has;
    int nice;
    uid_t user;
    gid_t group;

    f_time_spec_t timestamp;

    f_string_dynamic_t alias;
    f_string_dynamic_t name;
    f_string_dynamic_t path;
    f_string_dynamic_t script;

    f_string_maps_t define;
    f_string_maps_t parameter;

    f_string_dynamics_t environment;

    f_int32s_t affinity;
    f_capability_t capability;
    f_control_group_t control_group;
    f_int32s_t groups;
    f_limit_sets_t limits;
    f_execute_scheduler_t scheduler;

    controller_rule_ons_t ons;
    controller_rule_items_t items;
  } controller_rule_t;

  #define controller_rule_t_initialize { \
      { \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
        F_known_not, \
      }, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    f_time_spec_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_maps_t_initialize, \
    f_string_maps_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_int32s_t_initialize, \
    f_capability_t_initialize, \
    f_control_group_t_initialize, \
    f_int32s_t_initialize, \
    f_limit_sets_t_initialize, \
    f_execute_scheduler_t_initialize, \
    controller_rule_ons_initialize, \
    controller_rule_items_initialize, \
  }
#endif // _di_controller_rule_t_

/**
 * The Rules.
 *
 * array: An array of Rules.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_rules_t_
  typedef struct {
    controller_rule_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rules_t;

  #define controller_rules_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rules_t_

/**
 * A set of codes representing different with flags.
 */
#ifndef _di_controller_with_defines_
  #define controller_with_full_path_d    0x1
  #define controller_with_session_new_d  0x2
  #define controller_with_session_same_d 0x4
#endif // _di_controller_with_defines_

/**
 * An array of PIDs.
 *
 * array: An array of rule PIDs.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_pids_t_
  typedef struct {
    pid_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_pids_t;

  #define controller_pids_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_pids_t_

/**
 * A Rule Process.
 *
 * This refers to "process" as in the processing of a single rule for the given Rule ID and does not refer to "process" as in a CPU Process.
 *
 * The "cache" should only be used by the function processing/executing the process and as such should not require a write lock on the "process".
 * There should only be a single thread running any given Rule process at a time, guaranteeing the cache to not need read/write locks.
 *
 * Process States:
 * - idle:   No process is running for this rule.
 * - busy:   A process is actively using this, and is running synchronously.
 * - active: A process is actively using this, and is running asynchronously.
 * - done:   A process has finished running on this and there is a thread that needs to be cleaned up.
 *
 * Process Types:
 * - entry:   The process is started from an entry.
 * - exit:    The process is started from an exit.
 * - control: The process is started from a control operation.
 *
 * id:           The ID of this process relative to the processes array.
 * result:       The last return code from an execution of a process.
 * status:       The last execution status of the process.
 * state:        The state of the process.
 * action:       The action being performed.
 * options:      Configuration options for this asynchronous thread.
 * child:        The process id of a child process, if one is running (when forking to execute a child process).
 * id_thread:    The thread id, a valid ID when state is "active", and an invalid ID when the state is "busy".
 * lock:         A read/write lock on the structure.
 * active:       A read/write lock representing that something is currently using this (read locks = in use, write lock = begin deleting).
 * wait:         A thread condition to tell a process waiting process that the rule has is done being processed.
 * wait_lock:    A mutex lock for working with "wait".
 * cache:        The cache used in this process.
 * stack:        A stack used to represent dependencies as Rule ID's to avoid circular rule dependencies (If Rule A waits on Rule B, then Rule B must not wait on Rule A).
 * rule:         A copy of the rule actively being executed.
 * main_data:    Used for passing the controller_main_t data to the process thread (to populate controller_global_t).
 * main_setting: Used for passing the controller_setting_t data to the process thread (to populate controller_global_t).
 * main_thread:  Used for passing the controller_thread_t data to the process thread (to populate controller_global_t).
 */
#ifndef _di_controller_process_t_
  #define controller_process_option_asynchronous_d 0x1
  #define controller_process_option_require_d      0x2
  #define controller_process_option_simulate_d     0x4
  #define controller_process_option_validate_d     0x8
  #define controller_process_option_wait_d         0x10

  enum {
    controller_process_state_idle = 1,
    controller_process_state_busy,
    controller_process_state_active,
    controller_process_state_done,
  };

  enum {
    controller_process_type_entry = 1,
    controller_process_type_exit,
    controller_process_type_control,
  };

  typedef struct {
    f_array_length_t id;

    uint8_t state;
    uint8_t action;
    uint8_t options;
    uint8_t type;

    int result;

    f_thread_id_t id_thread;
    f_thread_lock_t lock;
    f_thread_lock_t active;
    f_thread_condition_t wait;
    f_thread_mutex_t wait_lock;

    controller_cache_t cache;
    f_array_lengths_t stack;

    f_string_dynamics_t path_pids;

    controller_pids_t childs;
    controller_rule_t rule;

    void *main_data;
    void *main_setting;
    void *main_thread;
  } controller_process_t;

  #define controller_process_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    f_thread_id_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_lock_t_initialize, \
    f_thread_condition_t_initialize, \
    controller_cache_t_initialize, \
    f_array_lengths_t_initialize, \
    f_string_dynamics_t_initialize, \
    controller_pids_t_initialize, \
    controller_rule_t_initialize, \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_process_t_

/**
 * The Rule Processes.
 *
 * Each process is a pointer of a process, to preserve memory locations that may ultimately change due to the resizing the array.
 *
 * array: An array of rule processes.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_processs_t_
  typedef struct {
    controller_process_t **array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_processs_t;

  #define controller_processs_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_processs_t_

/**
 * An Entry Item Action.
 *
 * controller_entry_action_type_*:
 *   - consider: Designate a rule to be pre-loaded.
 *   - execute:  Execute into another program.
 *   - failsafe: Designate a failsafe "item".
 *   - freeze:   A Rule Action for freezing.
 *   - item:     A named set of Rules.
 *   - kill:     A Rule Action for killing.
 *   - pause:    A Rule Action for pausing.
 *   - ready:    Designate readiness for special processing for Entry or Exit.
 *   - reload:   A Rule Action for reloading.
 *   - restart:  A Rule Action for restarting.
 *   - resume:   A Rule Action for resuming.
 *   - start:    A Rule Action for starting.
 *   - stop:     A Rule Action for stopping.
 *   - timeout:  Inline timeout settings.
 *   - thaw:     A Rule Action for unfreezing.
 *
 * controller_entry_rule_code_*:
 *   - asynchronous: Process Rule asynchronously.
 *   - require:      Require Rule operations to succeed or the Entry/Exit will fail.
 *   - wait:         Wait for all existing asynchronous processes to finish before operating Rule.
 *
 * type:       The type of Action.
 * code:       A single code or sub-type associated with the Action.
 * line:       The line number where the Entry Item begins.
 * number:     The unsigned number that some types use instead of the "parameters".
 * status:     The overall status.
 * parameters: The values associated with the Action.
 */
#ifndef _di_controller_entry_action_t_
  enum {
    controller_entry_action_type_consider = 1,
    controller_entry_action_type_execute,
    controller_entry_action_type_failsafe,
    controller_entry_action_type_freeze,
    controller_entry_action_type_item,
    controller_entry_action_type_kill,
    controller_entry_action_type_pause,
    controller_entry_action_type_ready,
    controller_entry_action_type_reload,
    controller_entry_action_type_restart,
    controller_entry_action_type_resume,
    controller_entry_action_type_start,
    controller_entry_action_type_stop,
    controller_entry_action_type_timeout,
    controller_entry_action_type_thaw,
  };

  #define controller_entry_rule_code_asynchronous_d 0x1
  #define controller_entry_rule_code_require_d      0x2
  #define controller_entry_rule_code_wait_d         0x4

  #define controller_entry_timeout_code_kill_d  0x1
  #define controller_entry_timeout_code_start_d 0x2
  #define controller_entry_timeout_code_stop_d  0x4

  typedef struct {
    uint8_t type;
    uint8_t code;

    f_array_length_t line;
    f_number_unsigned_t number;

    f_status_t status;

    f_string_dynamics_t parameters;
  } controller_entry_action_t;

  #define controller_entry_action_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    F_known_not, \
    f_string_dynamics_t_initialize, \
  }
#endif // _di_controller_entry_action_t_

/**
 * The Entry Item Actions.
 *
 * array: An array of Entry Item Actions.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_entry_actions_t_
  typedef struct {
    controller_entry_action_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_entry_actions_t;

  #define controller_entry_actions_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_entry_actions_t_

/**
 * An Entry Item.
 *
 * line:    The line number where the Entry Item begins.
 * name:    The name of the Entry Item.
 * actions: The Actions associated with the Entry Item.
 */
#ifndef _di_controller_entry_item_t_
  typedef struct {
    f_array_length_t line;
    f_string_dynamic_t name;

    controller_entry_actions_t actions;
  } controller_entry_item_t;

  #define controller_entry_item_t_initialize \
    { \
      0, \
      f_string_dynamic_t_initialize, \
      controller_entry_actions_t_initialize, \
    }
#endif // _di_controller_entry_item_t_

/**
 * An Entry Items.
 *
 * array: An array of Entry Items.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_entry_items_t_
  typedef struct {
    controller_entry_item_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_entry_items_t;

  #define controller_entry_items_t_initialize { \
    0, \
    0, \
    0, \
  }

  #define macro_controller_entry_items_t_clear(items) \
    items.array = 0; \
    items.size = 0; \
    items.used = 0;
#endif // _di_controller_entry_items_t_

/**
 * The Entry or Exit.
 *
 * Entry and Exit files are essentially the same structure with minor differences in settings and behavior.
 * The structure is identical and due to lacking any particularly good name to represent both "entry" or "exit", the name "entry" is being used for both.
 *
 * controller_entry_pid_*:
 *   - disable: Do not check for or create a PID file to represent the entry execution.
 *   - require: Check to see if the PID file exists for an entry at startup and then when "ready" create a pid file, display error on pid file already exists or on failure and then fail.
 *   - ready:   When "ready" create a pid file, display error on failure and then fail (does not check if PID file exists).
 *
 * controller_entry_show_*:
 *   - normal: Do not print anything other than warnings and errors, but allow executed programs and scripts to output however they like.
 *   - init:   Print like an init program, printing status of entry and rules as they are being started, stopped, etc...
 *
 * controller_entry_session_*:
 *   - none: No special session configuration specified, use built in defaults.
 *   - new:  Designate the default to use a new session, ignoring built in defaults (passing FL_execute_parameter_option_session_d to the execute functions).
 *   - same: Designate the default to use a same session, ignoring built in defaults.
 *
 * status:        The overall status.
 * pid:           The PID file generation setting.
 * session:       The default session settings (when NULL, no default is specified).
 * show:          The show setting for controlling what to show when executing entry items and rules.
 * timeout_kill:  The timeout to wait relating to using a kill signal.
 * timeout_start: The timeout to wait relating to starting a process.
 * timeout_stop:  The timeout to wait relating to stopping a process.
 * items:         The array of entry items.
 */
#ifndef _di_controller_entry_t_
  enum {
    controller_entry_pid_disable = 0,
    controller_entry_pid_require,
    controller_entry_pid_ready,
  };

  enum {
    controller_entry_show_normal = 0,
    controller_entry_show_init,
  };

  enum {
    controller_entry_session_none = 0,
    controller_entry_session_new,
    controller_entry_session_same,
  };

  typedef struct {
    f_status_t status;

    uint8_t pid;
    uint8_t session;
    uint8_t show;

    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    controller_entry_items_t items;
  } controller_entry_t;

  #define controller_entry_t_initialize { \
    F_known_not, \
    controller_entry_pid_require, \
    controller_entry_session_none, \
    controller_entry_show_normal, \
    0, \
    0, \
    0, \
    controller_entry_items_t_initialize, \
  }
#endif // _di_controller_entry_t_

/**
 * All setting data.
 *
 * controller_setting_ready_*:
 *   - no:    Entry/Exit is not ready.
 *   - wait:  Entry/Exit has "ready" somewhere in the file but is not yet ready.
 *   - yes:   Entry/Exit is now ready (Entry/Exit is still being processed).
 *   - done:  Entry/Exit is ready and processing is complete.
 *   - fail:  Entry/Exit processing failed.
 *   - abort: Abort received before finished processing Entry/Exit.
 *
 * controller_setting_mode_*:
 *   - program: Run as a program, exiting when finished prrocess entry (and any respective exit).
 *   - service: Run as a service, listening for requests after processing entry.
 *
 * interruptible:    TRUE if the program responds to interrupt signals, FALSE to block/ignore interrupt signals.
 * ready:            State representing if the settings are all loaded and is ready to run program operations.
 * failsafe_enabled: TRUE if failsafe execution is enabled, FALSE otherwise.
 * failsafe_item_id: The Entry Item ID to execute when failsafe execution is enabled.
 * path_control:     File path to the control socket.
 * path_pid:         File path to the PID file.
 * path_setting:     File path to the setting directory.
 * entry:            The Entry settings.
 * rules:            All rules and their respective settings.
 */
#ifndef _di_controller_setting_t
  enum {
    controller_setting_ready_no = 0,
    controller_setting_ready_wait,
    controller_setting_ready_yes,
    controller_setting_ready_done,
    controller_setting_ready_fail,
    controller_setting_ready_abort,
  };

  enum {
    controller_setting_mode_service = 0,
    controller_setting_mode_program,
  };

  typedef struct {
    bool interruptible;
    bool pid_created;
    uint8_t ready;
    uint8_t mode;

    bool failsafe_enabled;
    f_array_length_t failsafe_item_id;

    f_string_dynamic_t path_control;
    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;

    f_string_dynamic_t name_entry;

    controller_entry_t entry;
    controller_entry_t exit;
    controller_rules_t rules;
  } controller_setting_t;

  #define controller_setting_t_initialize { \
    F_false, \
    F_false, \
    0, \
    0, \
    F_false, \
    0, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    controller_entry_t_initialize, \
    controller_entry_t_initialize, \
    controller_rules_t_initialize, \
  }
#endif // _di_controller_setting_t

/**
 * A structure for managing threads.
 *
 * This is essentially data shared globally between threads, about threads.
 *
 * The "enabled" and "signal" utilize the lock: lock.process.
 *
 * enabled:    TRUE when threads are active, FALSE when inactive and the program is essentially shutting down, no new threads should be started when FALSE.
 * signal:     The code of any signal received.
 * status:     A status used by the main entry/rule processing thread for synchronous operations.
 * id_cleanup: The thread ID representing the Cleanup Process.
 * id_control: The thread ID representing the Control Process.
 * id_entry:   The thread ID representing the Entry or Exit Process.
 * id_rule:    The thread ID representing the Rule Process.
 * id_signal:  The thread ID representing the Signal Process.
 * lock:       A r/w lock for operating on this structure.
 * processs:   All Rule Process thread data.
 * cache:      A cache used by the main entry/rule processing thread for synchronous operations.
 */
#ifndef _di_controller_thread_t_
  #define controller_thread_cleanup_interval_long_d     3600      // 1 hour in seconds.
  #define controller_thread_cleanup_interval_short_d    180       // 3 minutes in seconds.
  #define controller_thread_exit_process_cancel_wait_d  600000000 // 0.6 seconds in nanoseconds.
  #define controller_thread_exit_process_cancel_total_d 150       // 90 seconds in multiples of wait.
  #define controller_thread_simulation_timeout_d        200       // 0.2 seconds in milliseconds.

  #define controller_thread_signal_wait_timeout_seconds_d     70
  #define controller_thread_signal_wait_timeout_nanoseconds_d 0

  #define controller_thread_lock_read_timeout_seconds_d      3
  #define controller_thread_lock_read_timeout_nanoseconds_d  0
  #define controller_thread_lock_write_timeout_seconds_d     3
  #define controller_thread_lock_write_timeout_nanoseconds_d 0

  #define controller_thread_wait_timeout_1_before_d 4
  #define controller_thread_wait_timeout_2_before_d 12
  #define controller_thread_wait_timeout_3_before_d 28

  #define controller_thread_wait_timeout_1_seconds_d     0
  #define controller_thread_wait_timeout_1_nanoseconds_d 20000000  // 0.02 seconds in nanoseconds.
  #define controller_thread_wait_timeout_2_seconds_d     0
  #define controller_thread_wait_timeout_2_nanoseconds_d 200000000 // 0.2 seconds in nanoseconds.
  #define controller_thread_wait_timeout_3_seconds_d     2
  #define controller_thread_wait_timeout_3_nanoseconds_d 0
  #define controller_thread_wait_timeout_4_seconds_d     20
  #define controller_thread_wait_timeout_4_nanoseconds_d 0

  #define controller_thread_exit_ready_timeout_seconds_d     0
  #define controller_thread_exit_ready_timeout_nanoseconds_d 500000000 // 0.5 seconds in nanoseconds.

  /**
   * States for enabled, designating how to stop the process.
   *
   * controller_thread_*:
   *   - enabled_not:          The controller is no longer enabled, shut down and abort all work.
   *   - enabled:              The controller is operating normally.
   *   - enabled_execute:      The controller is executing another process, all running operations must terminate.
   *   - enabled_exit:         The controller is shutting down, only process exit rules.
   *   - enabled_exit_execute: The controller is executing another process while in failsafe mode, all running operations must terminate.
   *   - enabled_exit_ready:   The controller is shutting down, only process exit rules, and now ready to send termination signals.
   *
   * controller_thread_cancel_*:
   *   - signal:       Cancellation is triggered by a signal.
   *   - call:         Cancellation is explicitly called.
   *   - execute:      Cancellation is explicitly called due to an "execute" Item Action, when not during Exit.
   *   - exit:         Cancellation is explicitly called during Exit.
   *   - exit_execute: Cancellation is explicitly called due to an "execute" Item Action during Exit.
   */
  enum {
    controller_thread_enabled_not = 0,
    controller_thread_enabled,
    controller_thread_enabled_execute,
    controller_thread_enabled_exit,
    controller_thread_enabled_exit_execute,
    controller_thread_enabled_exit_ready,
  };

  enum {
    controller_thread_cancel_signal = 0,
    controller_thread_cancel_call,
    controller_thread_cancel_execute,
    controller_thread_cancel_exit,
    controller_thread_cancel_exit_execute,
  };

  typedef struct {
    uint8_t enabled;
    int signal;
    f_status_t status;

    f_thread_id_t id_cleanup;
    f_thread_id_t id_control;
    f_thread_id_t id_entry;
    f_thread_id_t id_rule;
    f_thread_id_t id_signal;

    controller_lock_t lock;
    controller_processs_t processs;
    controller_cache_t cache;
  } controller_thread_t;

  #define controller_thread_t_initialize { \
    controller_thread_enabled, \
    0, \
    F_none, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    f_thread_id_t_initialize, \
    controller_lock_t_initialize, \
    controller_processs_t_initialize, \
    controller_cache_t_initialize, \
  }
#endif // _di_controller_thread_t_

/**
 * A structure for passing data to the interrupt state function.
 *
 * is_normal: Boolean designating if this is operating in a normal state.
 * thread:    The thread data.
 */
#ifndef _di_controller_state_interrupt_t_
  typedef struct {
    bool is_normal;
    controller_thread_t *thread;
  } controller_state_interrupt_t;

  #define controller_state_interrupt_t_initialize { \
    F_true, \
    0, \
  }

  #define macro_controller_state_interrupt_t_initialize(is_normal, thread) { \
    is_normal, \
    thread, \
  }
#endif // _di_controller_state_interrupt_t_

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

/**
 * Fully deallocate all memory for the given cache without caring about return status.
 *
 * @param cache
 *   The cache to deallocate.
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_cache_action_delete_simple_
  extern void controller_cache_action_delete_simple(controller_cache_action_t *cache) F_attribute_visibility_internal_d;
#endif // _di_controller_cache_action_delete_simple_

/**
 * Fully deallocate all memory for the given cache without caring about return status.
 *
 * @param cache
 *   The cache to deallocate.
 *
 * @see macro_f_array_lengths_t_delete_simple()
 * @see macro_f_fss_delimits_t_delete_simple()
 *
 * @see controller_cache_action_delete_simple()
 * @see f_string_dynamic_resize()
 * @see f_string_ranges_resize()
 * @see f_string_rangess_resize()
 */
#ifndef _di_controller_cache_delete_simple_
  extern void controller_cache_delete_simple(controller_cache_t *cache) F_attribute_visibility_internal_d;
#endif // _di_controller_cache_delete_simple_

/**
 * Fully deallocate all memory for the given entry action without caring about return status.
 *
 * @param action
 *   The action to deallocate.
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_controller_entry_action_delete_simple_
  extern void controller_entry_action_delete_simple(controller_entry_action_t *action) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_action_delete_simple_

/**
 * Fully deallocate all memory for the given entry actions without caring about return status.
 *
 * @param actions
 *   The entry_actions to deallocate.
 *
 * @see controller_entry_action_delete_simple()
 * @see f_memory_delete()
 */
#ifndef _di_controller_entry_actions_delete_simple_
  extern void controller_entry_actions_delete_simple(controller_entry_actions_t *actions) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_actions_delete_simple_

/**
 * Fully deallocate all memory for the given entry item without caring about return status.
 *
 * @param item
 *   The item to deallocate.
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_entry_item_delete_simple_
  extern void controller_entry_item_delete_simple(controller_entry_item_t *item) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_item_delete_simple_

/**
 * Fully deallocate all memory for the given entry items without caring about return status.
 *
 * @param items
 *   The entry_items to deallocate.
 *
 * @see controller_entry_item_delete_simple()
 * @see f_memory_delete()
 */
#ifndef _di_controller_entry_items_delete_simple_
  extern void controller_entry_items_delete_simple(controller_entry_items_t *items) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_items_delete_simple_

/**
 * Print the file error, locking the print mutex during the print.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 * @param thread
 *   (optional) The thread data.
 *   Set to NULL to disable locking on the thread (this should be done only if the lock is already in place).
 *
 * @see fll_error_file_print()
 */
#ifndef _di_controller_error_file_print_
  extern void controller_error_file_print(const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback, const f_string_t name, const f_string_t operation, const uint8_t type, controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_error_file_print_

/**
 * Print the error, locking the print mutex during the print.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param fallback
 *   Set to F_true to print the fallback error message for unknown errors.
 * @param thread
 *   (optional) The thread data.
 *   Set to NULL to disable locking on the thread (this should be done only if the lock is already in place).
 *
 * @see fll_error_print()
 */
#ifndef _di_controller_error_print_
  extern void controller_error_print(const fl_print_t print, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_error_print_

/**
 * Perform the initial, required, allocation for the lock.
 *
 * @param lock
 *   The lock to allocate.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_thread_lock_delete().
 *   Errors (with error bit) from: f_thread_mutex_delete().
 *
 * @see f_thread_lock_delete()
 * @see f_thread_mutex_delete()
 */
#ifndef _di_controller_lock_create_
  extern f_status_t controller_lock_create(controller_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_create_

/**
 * Delete the mutex lock and if the mutex lock is busy, forcibly unlock it and then delete it.
 *
 * @param mutex
 *   The mutex lock to delete.
 *   Will be set to NULLif delete succeeded.
 */
#ifndef _di_controller_lock_delete_mutex_
  extern void controller_lock_delete_mutex(f_thread_mutex_t *mutex) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_delete_mutex_

/**
 * Delete the r/w lock and if the r/w lock is busy, forcibly unlock it and then delete it.
 *
 * @param lock
 *   The r/w lock to delete.
 *   Will be set to NULL if delete succeeded.
 */
#ifndef _di_controller_lock_delete_rw_
  extern void controller_lock_delete_rw(f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_delete_rw_

/**
 * Fully deallocate all memory for the given lock without caring about return status.
 *
 * @param lock
 *   The lock to deallocate.
 *
 * @see f_thread_lock_delete()
 * @see f_thread_mutex_delete()
 */
#ifndef _di_controller_lock_delete_simple_
  extern void controller_lock_delete_simple(controller_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_delete_simple_

/**
 * Print a r/w lock related error message, locking the print mutex during the print.
 *
 * This will ignore F_signal and not print any messages, if passed.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param read
 *   If TRUE, then this is for a read lock.
 *   If FALSE, then this is for a write lock.
 * @param thread
 *   The thread data.
 *
 * @see fll_error_print()
 * @see controller_entry_error_print_cache()
 */
#ifndef _di_controller_lock_error_critical_print_
  extern void controller_lock_error_critical_print(const fl_print_t print, const f_status_t status, const bool read, controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_error_critical_print_

/**
 * Wait to get a read lock.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 * @return
 *   F_none on success.
 *   F_signal on (exit) signal received, lock will not be set when this is returned.
 *   F_status if main thread is disabled and write lock was never achieved.
 *
 *   Status from: f_thread_lock_read_timed().
 *
 *   Errors (with error bit) from: f_thread_lock_read_timed().
 *
 * @see f_thread_lock_read_timed()
 */
#ifndef _di_controller_lock_read_
  extern f_status_t controller_lock_read(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_read_

/**
 * Wait to get a read lock for some process.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param process
 *   The process to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 * @return
 *
 *   Status from: controller_lock_read().
 *
 *   Errors (with error bit) from: controller_lock_read().
 *
 * @see controller_lock_read()
 */
#ifndef _di_controller_lock_read_process_
  extern f_status_t controller_lock_read_process(controller_process_t * const process, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_read_process_

/**
 * Wait to get a read lock for some process type.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a read lock on.
 *
 * @return
 *
 *   Status from: controller_lock_read().
 *
 *   Errors (with error bit) from: controller_lock_read().
 *
 * @see controller_lock_read()
 */
#ifndef _di_controller_lock_read_process_type_
  extern f_status_t controller_lock_read_process_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_read_process_type_

/**
 * Wait to get a write lock.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param is_normal
 *   If TRUE, then process as if this operates during a normal operation (entry and control).
 *   If FALSE, then process as if this operates during a an exit operation.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 * @return
 *   F_none on success.
 *   F_signal on (exit) signal received, lock will not be set when this is returned.
 *   F_status if main thread is disabled and write lock was never achieved.
 *
 *   Status from: f_thread_lock_write_timed().
 *
 *   Errors (with error bit) from: f_thread_lock_write_timed().
 *
 * @see f_thread_lock_write_timed()
 */
#ifndef _di_controller_lock_write_
  extern f_status_t controller_lock_write(const bool is_normal, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_write_

/**
 * Wait to get a write lock for some process.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param process
 *   The process to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 * @return
 *
 *   Status from: controller_lock_write_process_type().
 *
 *   Errors (with error bit) from: controller_lock_write_process_type().
 *
 * @see controller_lock_write_process_type()
 */
#ifndef _di_controller_lock_write_process_
  extern f_status_t controller_lock_write_process(controller_process_t * const process, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_write_process_

/**
 * Wait to get a write lock for some process type.
 *
 * Given a r/w lock, periodically check to see if main thread is disabled while waiting.
 *
 * @param type
 *   The process type to use when checking if thread is enabled.
 * @param thread
 *   The thread data used to determine if the main thread is disabled or not.
 * @param lock
 *   The r/w lock to obtain a write lock on.
 *
 * @return
 *
 *   Status from: controller_lock_write().
 *
 *   Errors (with error bit) from: controller_lock_write().
 *
 * @see controller_lock_write()
 */
#ifndef _di_controller_lock_write_process_type_
  extern f_status_t controller_lock_write_process_type(const uint8_t type, controller_thread_t * const thread, f_thread_lock_t *lock) F_attribute_visibility_internal_d;
#endif // _di_controller_lock_write_process_type_

/**
 * Increase the size of the pid array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param pids
 *   The pid array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_pids_resize()
 */
#ifndef _di_controller_pids_increase_
  extern f_status_t controller_pids_increase(controller_pids_t *pids) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_increase_

/**
 * Resize the pid array.
 *
 * @param length
 *   The new size to use.
 * @param pids
 *   The pid array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_pids_resize_
  extern f_status_t controller_pids_resize(const f_array_length_t length, controller_pids_t *pids) F_attribute_visibility_internal_d;
#endif // _di_controller_pids_resize_

/**
 * Lock the mutex and the stream.
 *
 * This is implemented as a compliment to controller_print_unlock_flush() for consistency reasons.
 *
 * @param to
 *   The file stream to lock.
 * @param thread
 *   The thread containing the print mutex to lock.
 *
 * @see flockfile()
 *
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_print_lock_
  extern void controller_print_lock(const f_file_t to, controller_thread_t * const thread) F_attribute_visibility_internal_d;
#endif // _di_controller_print_lock_

/**
 * Flush the stream buffer and then unlock the mutex.
 *
 * This unlocks both the stream and the mutex locks.
 *
 * Weird behavior was observed when piping data from this program.
 * The behavior appears related to how this handles locks in addition to the file streams own locking mechanisms.
 *
 * As a work-around, this performs a flush immediately before unlocking the print mutex.
 *
 * @param to
 *   The file stream to unlock and flush.
 * @param thread
 *   The thread containing the print mutex to unlock.
 *
 * @see funlockfile()
 *
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_print_unlock_flush_
  void controller_print_unlock_flush(const f_file_t to, controller_thread_t * const thread) F_attribute_visibility_internal_d;
#endif // _di_controller_print_unlock_flush_

/**
 * Fully deallocate all memory for the given process without caring about return status.
 *
 * @param process
 *   The process to deallocate.
 *
 * @see f_string_dynamic_resize()
 * @see f_thread_condition_delete()
 * @see f_thread_mutex_delete()
 */
#ifndef _di_controller_process_delete_simple_
  extern void controller_process_delete_simple(controller_process_t *process) F_attribute_visibility_internal_d;
#endif // _di_controller_process_delete_simple_

/***
 * Safely wait for a process, periodically checking to see if process completed or check if exiting.
 *
 * @param global
 *   The global data.
 * @param process
 *   The process to wait on.
 *
 * @return
 *   F_none on success.
 *   F_signal on success and signal found.
 *
 *   Success from: f_thread_condition_wait_timed().
 *
 *   Errors (with error bit) from: f_thread_condition_wait_timed().
 *
 * @see f_thread_condition_wait_timed()
 */
#ifndef _di_controller_process_wait_
  extern f_status_t controller_process_wait(const controller_global_t global, controller_process_t *process) F_attribute_visibility_internal_d;
#endif // _di_controller_process_wait_

/**
 * Fully deallocate all memory for the given processs without caring about return status.
 *
 * @param processs
 *   The process array to deallocate.
 *
 * @see controller_processs_resize()
 */
#ifndef _di_controller_processs_delete_simple_
  extern void controller_processs_delete_simple(controller_processs_t *processs) F_attribute_visibility_internal_d;
#endif // _di_controller_processs_delete_simple_

/**
 * Increase the size of the rule array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param processs
 *   The process array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_processs_resize()
 */
#ifndef _di_controller_processs_increase_
  extern f_status_t controller_processs_increase(controller_processs_t *processs) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_increase_

/**
 * Resize the rule array.
 *
 * @param length
 *   The new size to use.
 * @param processs
 *   The process array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: controller_process_delete_simple().
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_thread_condition_create().
 *   Errors (with error bit) from: f_thread_lock_create().
 *
 * @see controller_process_delete_simple()
 * @see f_memory_resize()
 * @see f_thread_condition_create()
 * @see f_thread_lock_create()
 */
#ifndef _di_controller_processs_resize_
  extern f_status_t controller_processs_resize(const f_array_length_t length, controller_processs_t *processs) F_attribute_visibility_internal_d;
#endif // _di_controller_processs_resize_

/**
 * Fully deallocate all memory for the given rule action without caring about return status.
 *
 * @param action
 *   The action to deallocate.
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_controller_rule_action_delete_simple_
  extern void controller_rule_action_delete_simple(controller_rule_action_t *action) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_action_delete_simple_

/**
 * Fully deallocate all memory for the given rule actions without caring about return status.
 *
 * @param actions
 *   The rule_actions to deallocate.
 *
 * @see controller_rule_action_delete_simple()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_actions_delete_simple_
  extern void controller_rule_actions_delete_simple(controller_rule_actions_t *actions) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_actions_delete_simple_

/**
 * Fully deallocate all memory for the given rule without caring about return status.
 *
 * @param rule
 *   The rule to deallocate.
 *
 * @see macro_f_control_group_t_delete_simple()
 * @see macro_f_int32s_t_delete_simple()
 * @see macro_f_limit_sets_t_delete_simple()
 * @see macro_f_string_dynamics_t_delete_simple()
 * @see macro_f_string_maps_t_delete_simple()
 * @see macro_f_thread_condition_t_delete_simple()
 * @see macro_f_thread_mutex_t_delete_simple()
 *
 * @see controller_rule_items_delete_simple()
 * @see f_capability_delete()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_rule_delete_simple_
  extern void controller_rule_delete_simple(controller_rule_t *rule) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_delete_simple_

/**
 * Fully deallocate all memory for the given rule item without caring about return status.
 *
 * @param item
 *   The item to deallocate.
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_rule_item_delete_simple_
  extern void controller_rule_item_delete_simple(controller_rule_item_t *item) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_item_delete_simple_

/**
 * Fully deallocate all memory for the given rule items without caring about return status.
 *
 * @param items
 *   The rule_items to deallocate.
 *
 * @see controller_rule_item_delete_simple()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_items_delete_simple_
  extern void controller_rule_items_delete_simple(controller_rule_items_t *items) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_items_delete_simple_

/**
 * Fully deallocate all memory for the given rule item without caring about return status.
 *
 * @param on
 *   The on to deallocate.
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_rule_on_delete_simple_
  extern void controller_rule_on_delete_simple(controller_rule_on_t *on) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_on_delete_simple_

/**
 * Fully deallocate all memory for the given rule items without caring about return status.
 *
 * @param ons
 *   The rule_ons to deallocate.
 *
 * @see controller_rule_on_delete_simple()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_ons_delete_simple_
  extern void controller_rule_ons_delete_simple(controller_rule_ons_t *ons) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_ons_delete_simple_

/**
 * Increase the size of the rule array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param ons
 *   The on array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_rule_ons_resize()
 */
#ifndef _di_controller_rule_ons_increase_
  extern f_status_t controller_rule_ons_increase(controller_rule_ons_t *ons) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_increase_

/**
 * Resize the rule array.
 *
 * @param length
 *   The new size to use.
 * @param ons
 *   The on array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_rule_ons_resize_
  extern f_status_t controller_rule_ons_resize(const f_array_length_t length, controller_rule_ons_t *ons) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_ons_resize_

/**
 * Fully deallocate all memory for the given rules without caring about return status.
 *
 * @param rules
 *   The rules to deallocate.
 *
 * @see controller_rules_resize()
 */
#ifndef _di_controller_rules_delete_simple_
  extern void controller_rules_delete_simple(controller_rules_t *rules) F_attribute_visibility_internal_d;
#endif // _di_controller_rules_delete_simple_

/**
 * Increase the size of the rule array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param rules
 *   The rule array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_rules_resize()
 */
#ifndef _di_controller_rules_increase_
  extern f_status_t controller_rules_increase(controller_rules_t *rules) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_increase_

/**
 * Resize the rule array.
 *
 * @param length
 *   The new size to use.
 * @param rules
 *   The rule array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_rules_resize_
  extern f_status_t controller_rules_resize(const f_array_length_t length, controller_rules_t *rules) F_attribute_visibility_internal_d;
#endif // _di_controller_rules_resize_

/**
 * Fully deallocate all memory for the given setting without caring about return status.
 *
 * @param setting
 *   The setting to deallocate.
 *
 * @see controller_entry_delete_simple()
 * @see controller_rules_delete_simple()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_setting_delete_simple_
  extern void controller_setting_delete_simple(controller_setting_t *setting) F_attribute_visibility_internal_d;
#endif // _di_controller_setting_delete_simple_

/**
 * Fully deallocate all memory for the given setting without caring about return status.
 *
 * @param thread
 *   The thread to deallocate.
 *
 * @see controller_asynchronouss_resize()
 * @see f_thread_mutex_unlock()
 */
#ifndef _di_controller_thread_delete_simple_
  extern void controller_thread_delete_simple(controller_thread_t *thread) F_attribute_visibility_internal_d;
#endif // _di_controller_thread_delete_simple_

/**
 * Get the current time, plus the given offset.
 *
 * @todo this is basic enough that there needs to be an f_time class with this function f_time_now(), f_time_future(), f_time_past().
 *       "struct timespec" -> f_time_nano_t, "struct timeval" -> f_time_micro_t.
 *
 * @param seconds
 *   The seconds to add to current time.
 * @param nanoseconds
 *   The nanoseconds to add to current time.
 * @param time
 *   The resulting current time.
 */
#ifndef _di_controller_time_
  void controller_time(const time_t seconds, const long nanoseconds, struct timespec *time) F_attribute_visibility_internal_d;
#endif // _di_controller_time_

/**
 * Convert milliseconds to nanoseconds.
 *
 * @param milliseconds
 *   The number of milliseconds.
 *
 * @return
 *   A time structure suitable for passing to nanosleep() and similar functions.
 */
#ifndef _di_controller_time_milliseconds_
  extern struct timespec controller_time_milliseconds(const f_number_unsigned_t milliseconds) F_attribute_visibility_internal_d;
#endif // _di_controller_time_milliseconds_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
