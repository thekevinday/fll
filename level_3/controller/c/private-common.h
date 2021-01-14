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

#ifndef _di_controller_string_
  #define controller_string_action        "action"
  #define controller_string_actions       "actions"
  #define controller_string_affinity      "affinity"
  #define controller_string_as            "as"
  #define controller_string_asynchronous  "asynchronous"
  #define controller_string_bash          "bash"
  #define controller_string_batch         "batch"
  #define controller_string_capability    "capability"
  #define controller_string_create        "create"
  #define controller_string_command       "command"
  #define controller_string_consider      "consider"
  #define controller_string_control       "control"
  #define controller_string_control_group "control_group"
  #define controller_string_cpu           "cpu"
  #define controller_string_core          "core"
  #define controller_string_data          "data"
  #define controller_string_deadline      "deadline"
  #define controller_string_default       "default"
  #define controller_string_define        "define"
  #define controller_string_entry         "entry"
  #define controller_string_entries       "entries"
  #define controller_string_environment   "environment"
  #define controller_string_existing      "existing"
  #define controller_string_fail          "fail"
  #define controller_string_failsafe      "failsafe"
  #define controller_string_fifo          "fifo"
  #define controller_string_freeze        "freeze"
  #define controller_string_fsize         "fsize"
  #define controller_string_group         "group"
  #define controller_string_groups        "groups"
  #define controller_string_how           "how"
  #define controller_string_idle          "idle"
  #define controller_string_item          "item"
  #define controller_string_kill          "kill"
  #define controller_string_limit         "limit"
  #define controller_string_locks         "locks"
  #define controller_string_main          "main"
  #define controller_string_memlock       "memlock"
  #define controller_string_method        "method"
  #define controller_string_msgqueue      "msgqueue"
  #define controller_string_name          "name"
  #define controller_string_need          "need"
  #define controller_string_new           "new"
  #define controller_string_nice          "nice"
  #define controller_string_no            "no"
  #define controller_string_nofile        "nofile"
  #define controller_string_nproc         "nproc"
  #define controller_string_optional      "optional"
  #define controller_string_other         "other"
  #define controller_string_parameter     "parameter"
  #define controller_string_path          "path"
  #define controller_string_pause         "pause"
  #define controller_string_pid           "pid"
  #define controller_string_processor     "processor"
  #define controller_string_program       "program"
  #define controller_string_ready         "ready"
  #define controller_string_reload        "reload"
  #define controller_string_require       "require"
  #define controller_string_required      "required"
  #define controller_string_restart       "restart"
  #define controller_string_resume        "resume"
  #define controller_string_round_robin   "round_robin"
  #define controller_string_rss           "rss"
  #define controller_string_rtprio        "rtprio"
  #define controller_string_rttime        "rttime"
  #define controller_string_rule          "rule"
  #define controller_string_rules         "rules"
  #define controller_string_scheduler     "scheduler"
  #define controller_string_script        "script"
  #define controller_string_service       "service"
  #define controller_string_setting       "setting"
  #define controller_string_sigpending    "sigpending"
  #define controller_string_stack         "stack"
  #define controller_string_start         "start"
  #define controller_string_stop          "stop"
  #define controller_string_succeed       "succeed"
  #define controller_string_synchronous   "synchronous"
  #define controller_string_thaw          "thaw"
  #define controller_string_timeout       "timeout"
  #define controller_string_type          "type"
  #define controller_string_use           "use"
  #define controller_string_user          "user"
  #define controller_string_wait          "wait"
  #define controller_string_want          "want"
  #define controller_string_wish          "wish"
  #define controller_string_yes           "yes"

  #define controller_string_action_length        6
  #define controller_string_actions_length       7
  #define controller_string_affinity_length      8
  #define controller_string_as_length            2
  #define controller_string_asynchronous_length  12
  #define controller_string_bash_length          4
  #define controller_string_batch_length         5
  #define controller_string_capability_length    10
  #define controller_string_create_length        6
  #define controller_string_command_length       7
  #define controller_string_consider_length      8
  #define controller_string_control_length       7
  #define controller_string_control_group_length 13
  #define controller_string_core_length          4
  #define controller_string_cpu_length           3
  #define controller_string_data_length          4
  #define controller_string_deadline_length      8
  #define controller_string_define_length        6
  #define controller_string_default_length       7
  #define controller_string_entry_length         5
  #define controller_string_entries_length       7
  #define controller_string_environment_length   11
  #define controller_string_existing_length      8
  #define controller_string_fail_length          4
  #define controller_string_failsafe_length      8
  #define controller_string_fifo_length          4
  #define controller_string_freeze_length        6
  #define controller_string_fsize_length         5
  #define controller_string_group_length         5
  #define controller_string_how_length           3
  #define controller_string_idle_length          4
  #define controller_string_item_length          4
  #define controller_string_kill_length          4
  #define controller_string_limit_length         5
  #define controller_string_locks_length         5
  #define controller_string_main_length          4
  #define controller_string_memlock_length       7
  #define controller_string_method_length        6
  #define controller_string_msgqueue_length      8
  #define controller_string_name_length          4
  #define controller_string_need_length          4
  #define controller_string_new_length           3
  #define controller_string_nice_length          4
  #define controller_string_no_length            2
  #define controller_string_nofile_length        6
  #define controller_string_nproc_length         5
  #define controller_string_optional_length      8
  #define controller_string_other_length         5
  #define controller_string_parameter_length     9
  #define controller_string_path_length          4
  #define controller_string_pause_length         5
  #define controller_string_pid_length           3
  #define controller_string_processor_length     9
  #define controller_string_program_length       7
  #define controller_string_ready_length         5
  #define controller_string_reload_length        6
  #define controller_string_require_length       7
  #define controller_string_required_length      8
  #define controller_string_restart_length       7
  #define controller_string_resume_length        6
  #define controller_string_round_robin_length   11
  #define controller_string_rss_length           3
  #define controller_string_rtprio_length        6
  #define controller_string_rttime_length        6
  #define controller_string_rule_length          4
  #define controller_string_rules_length         5
  #define controller_string_scheduler_length     9
  #define controller_string_script_length        6
  #define controller_string_service_length       7
  #define controller_string_setting_length       7
  #define controller_string_sigpending_length    10
  #define controller_string_stack_length         5
  #define controller_string_start_length         5
  #define controller_string_stop_length          4
  #define controller_string_succeed_length       7
  #define controller_string_synchronous_length   11
  #define controller_string_thaw_length          4
  #define controller_string_timeout_length       7
  #define controller_string_type_length          4
  #define controller_string_use_length           3
  #define controller_string_user_length          4
  #define controller_string_wait_length          4
  #define controller_string_want_length          4
  #define controller_string_wish_length          4
  #define controller_string_yes_length           3

  const static f_string_t controller_string_action_s = controller_string_action;
  const static f_string_t controller_string_actions_s = controller_string_actions;
  const static f_string_t controller_string_affinity_s = controller_string_affinity;
  const static f_string_t controller_string_as_s = controller_string_as;
  const static f_string_t controller_string_asynchronous_s = controller_string_asynchronous;
  const static f_string_t controller_string_bash_s = controller_string_bash;
  const static f_string_t controller_string_batch_s = controller_string_batch;
  const static f_string_t controller_string_capability_s = controller_string_capability;
  const static f_string_t controller_string_create_s = controller_string_create;
  const static f_string_t controller_string_command_s = controller_string_command;
  const static f_string_t controller_string_consider_s = controller_string_consider;
  const static f_string_t controller_string_control_s = controller_string_control;
  const static f_string_t controller_string_control_group_s = controller_string_control_group;
  const static f_string_t controller_string_cpu_s = controller_string_cpu;
  const static f_string_t controller_string_core_s = controller_string_core;
  const static f_string_t controller_string_data_s = controller_string_data;
  const static f_string_t controller_string_deadline_s = controller_string_deadline;
  const static f_string_t controller_string_default_s = controller_string_default;
  const static f_string_t controller_string_define_s = controller_string_define;
  const static f_string_t controller_string_entry_s = controller_string_entry;
  const static f_string_t controller_string_entries_s = controller_string_entries;
  const static f_string_t controller_string_environment_s = controller_string_environment;
  const static f_string_t controller_string_existing_s = controller_string_existing;
  const static f_string_t controller_string_fail_s = controller_string_fail;
  const static f_string_t controller_string_failsafe_s = controller_string_failsafe;
  const static f_string_t controller_string_fifo_s = controller_string_fifo;
  const static f_string_t controller_string_freeze_s = controller_string_freeze;
  const static f_string_t controller_string_fsize_s = controller_string_fsize;
  const static f_string_t controller_string_group_s = controller_string_group;
  const static f_string_t controller_string_groups_s = controller_string_groups;
  const static f_string_t controller_string_how_s = controller_string_how;
  const static f_string_t controller_string_idle_s = controller_string_idle;
  const static f_string_t controller_string_item_s = controller_string_item;
  const static f_string_t controller_string_kill_s = controller_string_kill;
  const static f_string_t controller_string_limit_s = controller_string_limit;
  const static f_string_t controller_string_locks_s = controller_string_locks;
  const static f_string_t controller_string_main_s = controller_string_main;
  const static f_string_t controller_string_memlock_s = controller_string_memlock;
  const static f_string_t controller_string_method_s = controller_string_method;
  const static f_string_t controller_string_msgqueue_s = controller_string_msgqueue;
  const static f_string_t controller_string_name_s = controller_string_name;
  const static f_string_t controller_string_need_s = controller_string_need;
  const static f_string_t controller_string_new_s = controller_string_new;
  const static f_string_t controller_string_nice_s = controller_string_nice;
  const static f_string_t controller_string_no_s = controller_string_no;
  const static f_string_t controller_string_nofile_s = controller_string_nofile;
  const static f_string_t controller_string_nproc_s = controller_string_nproc;
  const static f_string_t controller_string_optional_s = controller_string_optional;
  const static f_string_t controller_string_other_s = controller_string_other;
  const static f_string_t controller_string_parameter_s = controller_string_parameter;
  const static f_string_t controller_string_path_s = controller_string_path;
  const static f_string_t controller_string_pause_s = controller_string_pause;
  const static f_string_t controller_string_pid_s = controller_string_pid;
  const static f_string_t controller_string_processor_s = controller_string_processor;
  const static f_string_t controller_string_program_s = controller_string_program;
  const static f_string_t controller_string_ready_s = controller_string_ready;
  const static f_string_t controller_string_reload_s = controller_string_reload;
  const static f_string_t controller_string_require_s = controller_string_require;
  const static f_string_t controller_string_required_s = controller_string_required;
  const static f_string_t controller_string_restart_s = controller_string_restart;
  const static f_string_t controller_string_resume_s = controller_string_resume;
  const static f_string_t controller_string_round_robin_s = controller_string_round_robin;
  const static f_string_t controller_string_rss_s = controller_string_rss;
  const static f_string_t controller_string_rtprio_s = controller_string_rtprio;
  const static f_string_t controller_string_rttime_s = controller_string_rttime;
  const static f_string_t controller_string_rule_s = controller_string_rule;
  const static f_string_t controller_string_rules_s = controller_string_rules;
  const static f_string_t controller_string_scheduler_s = controller_string_scheduler;
  const static f_string_t controller_string_script_s = controller_string_script;
  const static f_string_t controller_string_service_s = controller_string_service;
  const static f_string_t controller_string_setting_s = controller_string_setting;
  const static f_string_t controller_string_sigpending_s = controller_string_sigpending;
  const static f_string_t controller_string_stack_s = controller_string_stack;
  const static f_string_t controller_string_start_s = controller_string_start;
  const static f_string_t controller_string_stop_s = controller_string_stop;
  const static f_string_t controller_string_succeed_s = controller_string_succeed;
  const static f_string_t controller_string_synchronous_s = controller_string_synchronous;
  const static f_string_t controller_string_thaw_s = controller_string_thaw;
  const static f_string_t controller_string_timeout_s = controller_string_timeout;
  const static f_string_t controller_string_type_s = controller_string_type;
  const static f_string_t controller_string_use_s = controller_string_use;
  const static f_string_t controller_string_user_s = controller_string_user;
  const static f_string_t controller_string_wait_s = controller_string_wait;
  const static f_string_t controller_string_want_s = controller_string_want;
  const static f_string_t controller_string_wish_s = controller_string_wish;
  const static f_string_t controller_string_yes_s = controller_string_yes;
#endif // _di_controller_string_

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

#ifndef _di_controller_rule_action_t_
  #define controller_rule_action_method_string_extended      "FSS-0001 (Extended)"
  #define controller_rule_action_method_string_extended_list "FSS-0003 (Extended List)"

  #define controller_rule_action_method_string_extended_length      19
  #define controller_rule_action_method_string_extended_list_length 24

  enum {
    controller_rule_action_method_extended = 1,
    controller_rule_action_method_extended_list,
  };

  enum {
    controller_rule_action_type_create = 1,
    controller_rule_action_type_freeze,
    controller_rule_action_type_group,
    controller_rule_action_type_kill,
    controller_rule_action_type_pause,
    controller_rule_action_type_reload,
    controller_rule_action_type_restart,
    controller_rule_action_type_resume,
    controller_rule_action_type_start,
    controller_rule_action_type_stop,
    controller_rule_action_type_thaw,
    controller_rule_action_type_use,
    controller_rule_action_type_user,
  };

  typedef struct {
    uint8_t type;

    f_string_length_t line;

    f_status_t status;

    f_string_dynamics_t parameters;
  } controller_rule_action_t;

  #define controller_rule_action_t_initialize \
    { \
      0, \
      0, \
      F_known_not, \
      f_string_dynamics_t_initialize, \
    }

  #define controller_macro_rule_action_t_delete_simple(action) \
    f_macro_string_dynamics_t_delete_simple(action.parameters);
#endif // _di_controller_rule_action_t_

#ifndef _di_controller_rule_actions_t_
  typedef struct {
    controller_rule_action_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rule_actions_t;

  #define controller_rule_actions_t_initialize \
    { \
      0, \
      0, \
      0, \
    }

  #define controller_macro_rule_actions_t_delete_simple(actions) \
    actions.used = actions.size; \
    while (actions.used) { \
      actions.used--; \
      controller_macro_rule_action_t_delete_simple(actions.array[actions.used]); \
    } \
    f_memory_delete((void **) & actions.array, sizeof(controller_rule_action_t), actions.size); \
    actions.size = 0;
#endif // _di_controller_rule_actions_t_

#ifndef _di_controller_rule_item_t_
  enum {
    controller_rule_item_type_command = 1,
    controller_rule_item_type_script,
    controller_rule_item_type_service,
    controller_rule_item_type_setting,
  };

  typedef struct {
    uint8_t type;
    f_string_length_t line;

    controller_rule_actions_t actions;
  } controller_rule_item_t;

  #define controller_rule_item_t_initialize \
    { \
      0, \
      0, \
      controller_rule_actions_t_initialize, \
    }

  #define controller_macro_rule_item_t_delete_simple(item) \
    controller_macro_rule_actions_t_delete_simple(item.actions)
#endif // _di_controller_rule_item_t_

#ifndef _di_controller_rule_items_t_
  typedef struct {
    controller_rule_item_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rule_items_t;

  #define controller_rule_items_initialize \
    { \
      0, \
      0, \
      0, \
    }

  #define controller_macro_rule_items_t_delete_simple(items) \
    items.used = items.size; \
    while (items.used) { \
      items.used--; \
      controller_macro_rule_item_t_delete_simple(items.array[items.used]); \
    } \
    f_memory_delete((void **) & items.array, sizeof(controller_rule_item_t), items.size); \
    items.size = 0;
#endif // _di_controller_rule_items_t_

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
    controller_rule_setting_type_need,
    controller_rule_setting_type_nice,
    controller_rule_setting_type_parameter,
    controller_rule_setting_type_path,
    controller_rule_setting_type_scheduler,
    controller_rule_setting_type_script,
    controller_rule_setting_type_user,
    controller_rule_setting_type_want,
    controller_rule_setting_type_wish,
  };

  #define controller_rule_option_asynchronous 0x1
  #define controller_rule_option_require      0x2
  #define controller_rule_option_simulate     0x4
  #define controller_rule_option_validate     0x8
  #define controller_rule_option_wait         0x10

  // bitwise codes representing properties on controller_rule_t that have been found in the rule file.
  #define controller_rule_has_control_group 0x1
  #define controller_rule_has_group         0x2
  #define controller_rule_has_nice          0x4
  #define controller_rule_has_scheduler     0x8
  #define controller_rule_has_user          0x10

  typedef struct {
    f_status_t status;
    f_number_signed_t process; // @todo: for background/threaded support (ideally should hold the process id, but remove if this ends up not being the strategy) (this can also be used by the parent/main process to check to see if the child no longer a child of this process).

    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    uint8_t has;
    int nice;
    uid_t user;
    gid_t group;

    f_time_spec_t timestamp;

    f_string_dynamic_t id;
    f_string_dynamic_t name;
    f_string_dynamic_t path;
    f_string_dynamic_t script;

    f_string_maps_t define;
    f_string_maps_t parameter;

    f_string_dynamics_t environment;
    f_string_dynamics_t need;
    f_string_dynamics_t want;
    f_string_dynamics_t wish;

    f_int32s_t affinity;
    f_capability_t capability;
    f_control_group_t control_group;
    f_int32s_t groups;
    f_limit_sets_t limits;
    f_execute_scheduler_t scheduler;

    controller_rule_items_t items;
  } controller_rule_t;

  #define controller_rule_t_initialize \
    { \
      F_known_not, \
      0, \
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
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_int32s_t_initialize, \
      f_capability_t_initialize, \
      f_control_group_t_initialize, \
      f_int32s_t_initialize, \
      f_limit_sets_t_initialize, \
      f_execute_scheduler_t_initialize, \
      controller_rule_items_initialize, \
    }

  #define controller_macro_rule_t_delete_simple(rule) \
    f_macro_string_dynamic_t_delete_simple(rule.id) \
    f_macro_string_dynamic_t_delete_simple(rule.name) \
    f_macro_string_dynamic_t_delete_simple(rule.path) \
    f_macro_string_dynamic_t_delete_simple(rule.script) \
    f_macro_string_maps_t_delete_simple(rule.define) \
    f_macro_string_maps_t_delete_simple(rule.parameter) \
    f_macro_string_dynamics_t_delete_simple(rule.environment) \
    f_macro_string_dynamics_t_delete_simple(rule.need) \
    f_macro_string_dynamics_t_delete_simple(rule.want) \
    f_macro_string_dynamics_t_delete_simple(rule.wish) \
    f_macro_int32s_t_delete_simple(rule.affinity) \
    f_capability_delete(&rule.capability); \
    f_macro_control_group_t_delete_simple(rule.control_group) \
    f_macro_int32s_t_delete_simple(rule.groups) \
    f_macro_limit_sets_t_delete_simple(rule.limits) \
    controller_macro_rule_items_t_delete_simple(rule.items)
#endif // _di_controller_rule_t_

#ifndef _di_controller_rules_t_
  typedef struct {
    controller_rule_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rules_t;

  #define controller_rules_t_initialize \
    { \
      0, \
      0, \
      0, \
    }

  #define controller_macro_rules_t_delete_simple(rules) \
    rules.used = rules.size; \
    while (rules.used) { \
      rules.used--; \
      controller_macro_rule_t_delete_simple(rules.array[rules.used]); \
    } \
    f_memory_delete((void **) & rules.array, sizeof(controller_rule_t), rules.size); \
    rules.size = 0;
#endif // _di_controller_rules_t_

#ifndef _di_controller_entry_action_t_
  enum {
    controller_entry_action_type_consider = 1,
    controller_entry_action_type_failsafe,
    controller_entry_action_type_item,
    controller_entry_action_type_ready,
    controller_entry_action_type_rule,
    controller_entry_action_type_timeout,
  };

  #define controller_entry_rule_code_asynchronous 0x1
  #define controller_entry_rule_code_require      0x2
  #define controller_entry_rule_code_wait         0x4

  #define controller_entry_timeout_code_kill  0x1
  #define controller_entry_timeout_code_start 0x2
  #define controller_entry_timeout_code_stop  0x4

  typedef struct {
    uint8_t type;
    uint8_t code;

    f_string_length_t line;
    f_number_unsigned_t number;

    f_status_t status;

    f_string_dynamics_t parameters;
  } controller_entry_action_t;

  #define controller_entry_action_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      F_known_not, \
      f_string_dynamics_t_initialize, \
    }

  #define controller_macro_entry_action_t_delete_simple(action) \
    f_macro_string_dynamics_t_delete_simple(action.parameters);
#endif // _di_controller_entry_action_t_

#ifndef _di_controller_entry_actions_t_
  typedef struct {
    controller_entry_action_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_entry_actions_t;

  #define controller_entry_actions_t_initialize \
    { \
      0, \
      0, \
      0, \
    }

  #define controller_macro_entry_actions_t_delete_simple(actions) \
    actions.used = actions.size; \
    while (actions.used) { \
      actions.used--; \
      controller_macro_entry_action_t_delete_simple(actions.array[actions.used]); \
    } \
    f_memory_resize((void **) & actions.array, sizeof(controller_entry_action_t), actions.size, 0); \
    actions.size = 0;
#endif // _di_controller_entry_actions_t_

#ifndef _di_controller_entry_item_t_
  typedef struct {
    f_string_length_t line;

    f_string_dynamic_t name;
    controller_entry_actions_t actions;
  } controller_entry_item_t;

  #define controller_entry_item_t_initialize \
    { \
      0, \
      f_string_dynamic_t_initialize, \
      controller_entry_actions_t_initialize, \
    }

  #define controller_macro_entry_item_t_delete_simple(item) \
    f_macro_string_dynamic_t_delete_simple(item.name); \
    controller_macro_entry_actions_t_delete_simple(item.actions)
#endif // _di_controller_entry_item_t_

#ifndef _di_controller_entry_items_t_
  typedef struct {
    controller_entry_item_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_entry_items_t;

  #define controller_entry_items_t_initialize \
    { \
      0, \
      0, \
      0, \
    }

  #define controller_macro_entry_items_t_delete_simple(items) \
    items.used = items.size; \
    while (items.used) { \
      items.used--; \
      controller_macro_entry_item_t_delete_simple(items.array[items.used]); \
    } \
    f_memory_delete((void **) & items.array, sizeof(controller_entry_item_t), items.size); \
    items.size = 0;
#endif // _di_controller_entry_items_t_

#ifndef _di_controller_entry_t_
  typedef struct {
    f_status_t status;
    controller_entry_items_t items;
  } controller_entry_t;

  #define controller_entry_t_initialize \
    { \
      F_known_not, \
      controller_entry_items_t_initialize, \
    }

  #define controller_macro_entry_t_delete_simple(entry) \
    controller_macro_entry_items_t_delete_simple(entry.items)
#endif // _di_controller_entry_t_

#ifndef _di_controller_setting_t
  enum {
    controller_setting_ready_no = 0,
    controller_setting_ready_wait,
    controller_setting_ready_yes,
    controller_setting_ready_done,
    controller_setting_ready_fail,
    controller_setting_ready_abort,
  };

  typedef struct {
    bool interruptable;
    bool lock; // @todo: this is intended for mutex write locking of this setting for thread safety, remove this if another approach is used.
    uint8_t ready;

    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    bool failsafe_enabled;
    f_array_length_t failsafe_rule_id;

    f_string_dynamic_t path_control;
    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;

    controller_entry_t entry;
    controller_rules_t rules;
  } controller_setting_t;

  #define controller_setting_t_initialize \
    { \
      F_false, \
      F_false, \
      0, \
      3, \
      3, \
      3, \
      F_false, \
      0, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      controller_entry_t_initialize, \
      controller_rules_t_initialize, \
    }

  #define controller_macro_setting_t_delete_simple(setting) \
    f_macro_string_dynamic_t_delete_simple(setting.path_control) \
    f_macro_string_dynamic_t_delete_simple(setting.path_pid) \
    f_macro_string_dynamic_t_delete_simple(setting.path_setting) \
    controller_macro_entry_t_delete_simple(setting.entry) \
    controller_macro_rules_t_delete_simple(setting.rules)
#endif // _di_controller_setting_t

#ifndef _di_controller_cache_t_
  typedef struct {
    f_string_length_t line_action;
    f_string_length_t line_item;

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
    f_string_dynamic_t buffer_other;
    f_string_dynamic_t buffer_path;

    f_string_dynamic_t name_action;
    f_string_dynamic_t name_file;
    f_string_dynamic_t name_item;
  } controller_cache_t;

  #define controller_cache_t_initialize \
    { \
      0, \
      0, \
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
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }

  #define controller_macro_cache_t_delete_simple(cache) \
    f_macro_array_lengths_t_delete_simple(cache.ats) \
    f_macro_array_lengths_t_delete_simple(cache.stack) \
    f_macro_fss_comments_t_delete_simple(cache.comments) \
    f_macro_fss_delimits_t_delete_simple(cache.delimits) \
    f_macro_fss_content_t_delete_simple(cache.content_action) \
    f_macro_fss_contents_t_delete_simple(cache.content_actions) \
    f_macro_fss_contents_t_delete_simple(cache.content_items) \
    f_macro_fss_objects_t_delete_simple(cache.object_actions) \
    f_macro_fss_objects_t_delete_simple(cache.object_items) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_file) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_item) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_other) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_path) \
    f_macro_string_dynamic_t_delete_simple(cache.name_action) \
    f_macro_string_dynamic_t_delete_simple(cache.name_file) \
    f_macro_string_dynamic_t_delete_simple(cache.name_item)
#endif // _di_controller_cache_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
