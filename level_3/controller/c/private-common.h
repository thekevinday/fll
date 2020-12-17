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
  #define controller_string_asynchronous  "asynchronous"
  #define controller_string_create        "create"
  #define controller_string_command       "command"
  #define controller_string_consider      "consider"
  #define controller_string_control_group "control_group"
  #define controller_string_default       "default"
  #define controller_string_define        "define"
  #define controller_string_entry         "entry"
  #define controller_string_entries       "entries"
  #define controller_string_environment   "environment"
  #define controller_string_fail          "fail"
  #define controller_string_failsafe      "failsafe"
  #define controller_string_group         "group"
  #define controller_string_how           "how"
  #define controller_string_item          "item"
  #define controller_string_kill          "kill"
  #define controller_string_main          "main"
  #define controller_string_method        "method"
  #define controller_string_name          "name"
  #define controller_string_need          "need"
  #define controller_string_no            "no"
  #define controller_string_optional      "optional"
  #define controller_string_parameter     "parameter"
  #define controller_string_path          "path"
  #define controller_string_pid           "pid"
  #define controller_string_ready         "ready"
  #define controller_string_reload        "reload"
  #define controller_string_require       "require"
  #define controller_string_required      "required"
  #define controller_string_restart       "restart"
  #define controller_string_rule          "rule"
  #define controller_string_rules         "rules"
  #define controller_string_script        "script"
  #define controller_string_service       "service"
  #define controller_string_setting       "setting"
  #define controller_string_start         "start"
  #define controller_string_stop          "stop"
  #define controller_string_succeed       "succeed"
  #define controller_string_synchronous   "synchronous"
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
  #define controller_string_asynchronous_length  12
  #define controller_string_create_length        6
  #define controller_string_command_length       7
  #define controller_string_consider_length      8
  #define controller_string_control_group_length 13
  #define controller_string_define_length        6
  #define controller_string_default_length       7
  #define controller_string_entry_length         5
  #define controller_string_entries_length       7
  #define controller_string_environment_length   11
  #define controller_string_fail_length          4
  #define controller_string_failsafe_length      8
  #define controller_string_group_length         5
  #define controller_string_how_length           3
  #define controller_string_item_length          4
  #define controller_string_kill_length          4
  #define controller_string_main_length          4
  #define controller_string_method_length        6
  #define controller_string_name_length          4
  #define controller_string_need_length          4
  #define controller_string_no_length            2
  #define controller_string_optional_length      8
  #define controller_string_parameter_length     9
  #define controller_string_path_length          4
  #define controller_string_pid_length           3
  #define controller_string_ready_length         5
  #define controller_string_reload_length        6
  #define controller_string_require_length       7
  #define controller_string_required_length      8
  #define controller_string_restart_length       7
  #define controller_string_rule_length          4
  #define controller_string_rules_length         5
  #define controller_string_script_length        6
  #define controller_string_service_length       7
  #define controller_string_setting_length       7
  #define controller_string_start_length         5
  #define controller_string_stop_length          4
  #define controller_string_succeed_length       7
  #define controller_string_synchronous_length   11
  #define controller_string_timeout_length       7
  #define controller_string_type_length          4
  #define controller_string_use_length           3
  #define controller_string_user_length          4
  #define controller_string_wait_length          4
  #define controller_string_want_length          4
  #define controller_string_wish_length          4
  #define controller_string_yes_length           3
#endif // _di_controller_string_

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
    controller_rule_action_type_group,
    controller_rule_action_type_kill,
    controller_rule_action_type_restart,
    controller_rule_action_type_reload,
    controller_rule_action_type_start,
    controller_rule_action_type_stop,
    controller_rule_action_type_use,
    controller_rule_action_type_user,
  };

  typedef struct {
    uint8_t method;
    uint8_t type;

    f_string_length_t line;

    f_status_t status;

    f_string_dynamics_t parameters;
  } controller_rule_action_t;

  #define controller_rule_action_t_initialize \
    { \
      0, \
      0, \
      0, \
      F_known_not, \
      f_string_dynamics_t_initialize, \
    }

  #define controller_macro_rule_action_t_delete_simple(action) \
    fl_string_dynamics_delete(&action.parameters);
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
    controller_rule_setting_type_control_group = 1,
    controller_rule_setting_type_define,
    controller_rule_setting_type_environment,
    controller_rule_setting_type_name,
    controller_rule_setting_type_need,
    controller_rule_setting_type_parameter,
    controller_rule_setting_type_path,
    controller_rule_setting_type_want,
    controller_rule_setting_type_wish,
  };

  #define controller_rule_option_asynchronous 0x1
  #define controller_rule_option_require      0x2
  #define controller_rule_option_simulate     0x4
  #define controller_rule_option_wait         0x8

  typedef struct {
    f_status_t status;
    f_number_signed_t process; // @todo: for background/threaded support (ideally should hold the process id, but remove if this ends up not being the strategy) (this can also be used by the parent/main process to check to see if the child no longer a child of this process).

    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    f_time_spec_t timestamp;

    f_string_dynamic_t id;
    f_string_dynamic_t name;
    f_string_dynamic_t control_group;
    f_string_dynamic_t path;

    f_string_maps_t define;
    f_string_maps_t parameter;

    f_string_dynamics_t environment;
    f_string_dynamics_t need;
    f_string_dynamics_t want;
    f_string_dynamics_t wish;

    controller_rule_items_t items;
  } controller_rule_t;

  #define controller_rule_t_initialize \
    { \
      F_known_not, \
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
      controller_rule_items_initialize, \
    }

  #define controller_macro_rule_t_delete_simple(rule) \
    fl_string_dynamic_delete(&rule.id); \
    fl_string_dynamic_delete(&rule.name); \
    fl_string_dynamic_delete(&rule.control_group); \
    fl_string_dynamic_delete(&rule.path); \
    f_macro_string_maps_t_delete_simple(rule.define) \
    f_macro_string_maps_t_delete_simple(rule.parameter) \
    fl_string_dynamics_delete(&rule.environment); \
    fl_string_dynamics_delete(&rule.need); \
    fl_string_dynamics_delete(&rule.want); \
    fl_string_dynamics_delete(&rule.wish); \
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
    fl_string_dynamics_delete(&action.parameters);
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
    f_memory_delete((void **) & actions.array, sizeof(controller_entry_action_t), actions.size); \
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
    fl_string_dynamic_delete(&item.name); \
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
      controller_entry_t_initialize, \
      controller_rules_t_initialize, \
    }

  #define controller_macro_setting_t_delete_simple(setting) \
    fl_string_dynamic_delete(&setting.path_pid); \
    fl_string_dynamic_delete(&setting.path_setting); \
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
    }

  #define controller_macro_cache_t_delete_simple(cache) \
    fl_type_array_lengths_delete(&cache.ats); \
    fl_type_array_lengths_delete(&cache.stack); \
    f_macro_fss_comments_t_delete_simple(cache.comments) \
    f_macro_fss_delimits_t_delete_simple(cache.delimits) \
    f_macro_fss_content_t_delete_simple(cache.content_action) \
    f_macro_fss_contents_t_delete_simple(cache.content_actions) \
    f_macro_fss_contents_t_delete_simple(cache.content_items) \
    f_macro_fss_objects_t_delete_simple(cache.object_actions) \
    f_macro_fss_objects_t_delete_simple(cache.object_items) \
    fl_string_dynamic_delete(&cache.buffer_file); \
    fl_string_dynamic_delete(&cache.buffer_item); \
    fl_string_dynamic_delete(&cache.buffer_path); \
    fl_string_dynamic_delete(&cache.name_action); \
    fl_string_dynamic_delete(&cache.name_file); \
    fl_string_dynamic_delete(&cache.name_item);
#endif // _di_controller_cache_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
