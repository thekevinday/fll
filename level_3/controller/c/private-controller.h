/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_controller_h
#define _PRIVATE_controller_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_string_
  #define controller_string_create      "create"
  #define controller_string_command     "command"
  #define controller_string_consider    "consider"
  #define controller_string_default     "default"
  #define controller_string_define      "define"
  #define controller_string_entry       "entry"
  #define controller_string_entries     "entries"
  #define controller_string_environment "environment"
  #define controller_string_failsafe    "failsafe"
  #define controller_string_group       "group"
  #define controller_string_main        "main"
  #define controller_string_name        "name"
  #define controller_string_need        "need"
  #define controller_string_path        "path"
  #define controller_string_pid         "pid"
  #define controller_string_restart     "restart"
  #define controller_string_reload      "reload"
  #define controller_string_rule        "rule"
  #define controller_string_rules       "rules"
  #define controller_string_script      "script"
  #define controller_string_service     "service"
  #define controller_string_settings    "settings"
  #define controller_string_start       "start"
  #define controller_string_stop        "stop"
  #define controller_string_timeout     "timeout"
  #define controller_string_use         "use"
  #define controller_string_user        "user"
  #define controller_string_want        "want"
  #define controller_string_wish        "wish"

  #define controller_string_create_length      6
  #define controller_string_command_length     7
  #define controller_string_consider_length    8
  #define controller_string_define_length      6
  #define controller_string_default_length     7
  #define controller_string_entry_length       5
  #define controller_string_entries_length     7
  #define controller_string_environment_length 11
  #define controller_string_failsafe_length    8
  #define controller_string_group_length       5
  #define controller_string_main_length        4
  #define controller_string_name_length        4
  #define controller_string_need_length        4
  #define controller_string_path_length        4
  #define controller_string_pid_length         3
  #define controller_string_restart_length     7
  #define controller_string_reload_length      6
  #define controller_string_rule_length        4
  #define controller_string_rules_length       5
  #define controller_string_script_length      6
  #define controller_string_service_length     7
  #define controller_string_settings_length    8
  #define controller_string_start_length       5
  #define controller_string_stop_length        4
  #define controller_string_timeout_length     7
  #define controller_string_use_length         3
  #define controller_string_user_length        4
  #define controller_string_want_length        4
  #define controller_string_wish_length        4
#endif // _di_controller_string_

#ifndef _di_controller_rule_action_t_
  enum {
    controller_rule_action_type_extended = 1,
    controller_rule_action_type_extended_list,
  };

  enum {
    controller_rule_action_intent_create = 1,
    controller_rule_action_intent_group,
    controller_rule_action_intent_restart,
    controller_rule_action_intent_reload,
    controller_rule_action_intent_start,
    controller_rule_action_intent_stop,
    controller_rule_action_intent_use,
    controller_rule_action_intent_user,
  };

  typedef struct {
    f_string_length_t line;
    f_string_dynamics_t parameters;
  } controller_rule_action_t;

  #define controller_rule_action_t_initialize \
    { \
      0, \
      f_string_dynamics_t_initialize, \
    }

  #define macro_controller_rule_action_t_delete_simple(action) \
    f_macro_string_dynamics_t_delete_simple(action.parameters)
#endif // _di_controller_rule_action_t_

#ifndef _di_controller_rule_actions_t_
  typedef struct {
    uint8_t type;
    uint8_t intent;

    controller_rule_action_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rule_actions_t;

  #define controller_rule_actions_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      0, \
    }

  #define macro_controller_rule_actions_t_delete_simple(actions) \
    actions.used = actions.size; \
    while (actions.used > 0) { \
      actions.used--; \
      macro_controller_rule_item_t_delete_simple(actions.array[actions.used]); \
      if (!actions.used) { \
        if (f_memory_delete((void **) & actions.array, sizeof(controller_rule_action_t), actions.size)) { \
          actions.size = 0; \
        } \
      } \
    }
#endif // _di_controller_rule_actions_t_

#ifndef _di_controller_rule_item_t_
  enum {
    controller_rule_item_type_command = 1,
    controller_rule_item_type_script,
    controller_rule_item_type_service,
    controller_rule_item_type_settings,
  };

  typedef struct {
    uint8_t type;
    f_string_length_t line;

    controller_rule_actions_t create;
    controller_rule_actions_t group;
    controller_rule_actions_t restart;
    controller_rule_actions_t reload;
    controller_rule_actions_t start;
    controller_rule_actions_t stop;
    controller_rule_actions_t use;
    controller_rule_actions_t user;
  } controller_rule_item_t;

  #define controller_rule_item_t_initialize \
    { \
      0, \
      0, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
    }

  #define macro_controller_rule_item_t_delete_simple(item) \
    macro_controller_rule_actions_t_delete_simple(item.create) \
    macro_controller_rule_actions_t_delete_simple(item.group) \
    macro_controller_rule_actions_t_delete_simple(item.restart) \
    macro_controller_rule_actions_t_delete_simple(item.reload) \
    macro_controller_rule_actions_t_delete_simple(item.start) \
    macro_controller_rule_actions_t_delete_simple(item.stop) \
    macro_controller_rule_actions_t_delete_simple(item.use) \
    macro_controller_rule_actions_t_delete_simple(item.user)
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

  #define macro_controller_rule_items_t_delete_simple(items) \
    items.used = items.size; \
    while (items.used > 0) { \
      items.used--; \
      macro_controller_rule_item_t_delete_simple(items.array[items.used]); \
      if (!items.used) { \
        if (f_memory_delete((void **) & items.array, sizeof(controller_rule_item_t), items.size)) { \
          items.size = 0; \
        } \
      } \
    }
#endif // _di_controller_rule_items_t_

#ifndef _di_controller_rule_t_
  typedef struct {
    f_status_t status;

    f_string_dynamic_t id;
    f_string_dynamic_t name;
    f_string_dynamic_t control_group;
    f_string_dynamic_t path;
    f_string_dynamic_t pid;

    f_string_maps_t defines;

    f_string_dynamics_t environment;
    f_string_dynamics_t need;
    f_string_dynamics_t want;
    f_string_dynamics_t wish;

    controller_rule_items_t items;
  } controller_rule_t;

  #define controller_rule_t_initialize \
    { \
      F_unknown, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_maps_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      controller_rule_items_initialize, \
    }

  #define macro_controller_rule_t_delete_simple(setting) \
    f_string_dynamic_t_delete_simple(setting.id) \
    f_string_dynamic_t_delete_simple(setting.name) \
    f_string_dynamic_t_delete_simple(setting.control_group) \
    f_string_dynamic_t_delete_simple(setting.path) \
    f_string_dynamic_t_delete_simple(setting.pid) \
    f_string_maps_t_delete_simple(setting.defines) \
    f_string_dynamics_t_delete_simple(setting.environments) \
    f_string_dynamics_t_delete_simple(setting.need) \
    f_string_dynamics_t_delete_simple(setting.want) \
    f_string_dynamics_t_delete_simple(setting.wish) \
    macro_controller_rule_item_t_delete_simple(setting.items)
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

  #define macro_controller_rules_t_delete_simple(rules) \
    rules.used = rules.size; \
    while (rules.used > 0) { \
      rules.used--; \
      macro_controller_rule_t_delete_simple(rules.array[rules.used]); \
      if (!rules.used) { \
        if (f_memory_delete((void **) & rules.array, sizeof(controller_rule_t), rules.size)) { \
          rules.size = 0; \
        } \
      } \
    }
#endif // _di_controller_rules_t_

#ifndef _di_controller_entry_item_t_
  enum {
    controller_entry_item_type_consider = 1,
    controller_entry_item_type_failsafe,
    controller_entry_item_type_group,
    controller_entry_item_type_rule,
    controller_entry_item_type_timeout,
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
    f_number_unsigned_t timeout;

    f_string_dynamic_t id;
  } controller_entry_item_t;

  #define controller_entry_item_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }

  #define macro_controller_entry_item_t_delete_simple(item) \
    f_macro_string_dynamics_t_delete_simple(item.id)
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

  #define macro_controller_entry_items_t_delete_simple(items) \
    items.used = items.size; \
    while (items.used > 0) { \
      items.used--; \
      macro_controller_rule_t_delete_simple(items.array[items.used]); \
      if (!items.used) { \
        if (f_memory_delete((void **) & items.array, sizeof(controller_entry_item_t), items.size)) { \
          items.size = 0; \
        } \
      } \
    }
#endif // _di_controller_entry_items_t_

#ifndef _di_controller_entry_list_t_
  typedef struct {
    f_string_length_t line;
    f_string_dynamic_t name;
    controller_entry_items_t items;
  } controller_entry_list_t;

  #define controller_entry_list_t_initialize \
    { \
      0, \
      f_string_dynamic_t_initialize, \
      controller_entry_items_t_initialize, \
    }

  #define macro_controller_entry_list_t_delete_simple(list) \
    f_macro_string_dynamic_t_delete_simple(list.name) \
    macro_controller_entry_items_t_delete_simple(list.items)
#endif // _di_controller_entry_list_t_

#ifndef _di_controller_entry_lists_t_
  typedef struct {
    controller_entry_list_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_entry_lists_t;

  #define controller_entry_lists_t_initialize \
    { \
      0, \
      0, \
      0, \
    }

  #define macro_controller_entry_lists_t_delete_simple(lists) \
    lists.used = lists.size; \
    while (lists.used > 0) { \
      lists.used--; \
      macro_controller_rule_t_delete_simple(lists.array[lists.used]); \
      if (!lists.used) { \
        if (f_memory_delete((void **) & lists.array, sizeof(controller_entry_list_t), lists.size)) { \
          lists.size = 0; \
        } \
      } \
    }
#endif // _di_controller_entry_lists_t_

#ifndef _di_controller_setting_t
  typedef struct {
    bool interruptable;

    f_string_dynamic_t path_setting;

    controller_entry_lists_t entry_lists;
    controller_rules_t rules;
  } controller_setting_t;

  #define controller_setting_t_initialize \
    { \
      F_false, \
      f_string_dynamic_t_initialize, \
      controller_rules_t_initialize, \
    }

  #define macro_controller_setting_t_delete_simple(setting) \
    f_macro_string_dynamic_t_delete_simple(setting.path_setting) \
    macro_controller_entry_lists_t_delete_simple(entry_lists) \
    f_macro_string_dynamic_t_delete_simple(setting.rules)
#endif // _di_controller_setting_t

/**
 * Validate that the given string is a valid environment variable name.
 *
 * A valid environment variable name must begin with an alpha-character or an underscore.
 * Every character after that may be alphanumeric or underscore.
 * All other characters, including Unicode characters, are invalid.
 *
 * @param name
 *   The string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_none if there is no string to validate (used = 0).
 *
 *   Errors (with error bit) from: f_utf_is_alpha().
 *   Errors (with error bit) from: f_utf_is_alpha_digit().
 *
 * @see f_utf_is_alpha()
 * @see f_utf_is_alpha_digit()
 */
#ifndef _di_controller_validate_define_name_
  extern f_return_status controller_validate_environment_name(const f_string_static_t name) f_gcc_attribute_visibility_internal;
#endif // _di_controller_validate_define_name_

/**
 * Validate that the given string has at least one graph character.
 *
 * @param name
 *   The string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_none if there is no string to validate (used = 0).
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_controller_validate_has_graph_
  extern f_return_status controller_validate_has_graph(const f_string_static_t name) f_gcc_attribute_visibility_internal;
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_controller_h
