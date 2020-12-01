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
  #define controller_string_failsafe      "failsafe"
  #define controller_string_group         "group"
  #define controller_string_item          "item"
  #define controller_string_kill          "kill"
  #define controller_string_main          "main"
  #define controller_string_name          "name"
  #define controller_string_need          "need"
  #define controller_string_parameter     "parameter"
  #define controller_string_path          "path"
  #define controller_string_pid           "pid"
  #define controller_string_ready         "ready"
  #define controller_string_reload        "reload"
  #define controller_string_require       "require"
  #define controller_string_restart       "restart"
  #define controller_string_rule          "rule"
  #define controller_string_rules         "rules"
  #define controller_string_script        "script"
  #define controller_string_service       "service"
  #define controller_string_settings      "settings"
  #define controller_string_start         "start"
  #define controller_string_stop          "stop"
  #define controller_string_timeout       "timeout"
  #define controller_string_use           "use"
  #define controller_string_user          "user"
  #define controller_string_wait          "wait"
  #define controller_string_want          "want"
  #define controller_string_wish          "wish"

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
  #define controller_string_failsafe_length      8
  #define controller_string_group_length         5
  #define controller_string_item_length          4
  #define controller_string_kill_length          4
  #define controller_string_main_length          4
  #define controller_string_name_length          4
  #define controller_string_need_length          4
  #define controller_string_parameter_length     9
  #define controller_string_path_length          4
  #define controller_string_pid_length           3
  #define controller_string_ready_length         5
  #define controller_string_reload_length        6
  #define controller_string_require_length       7
  #define controller_string_restart_length       7
  #define controller_string_rule_length          4
  #define controller_string_rules_length         5
  #define controller_string_script_length        6
  #define controller_string_service_length       7
  #define controller_string_settings_length      8
  #define controller_string_start_length         5
  #define controller_string_stop_length          4
  #define controller_string_timeout_length       7
  #define controller_string_use_length           3
  #define controller_string_user_length          4
  #define controller_string_wait_length          4
  #define controller_string_want_length          4
  #define controller_string_wish_length          4
#endif // _di_controller_string_

#ifndef _di_controller_rule_action_t_
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
    f_string_length_t line;

    f_status_t status;

    f_string_dynamics_t parameters;
  } controller_rule_action_t;

  #define controller_rule_action_t_initialize \
    { \
      0, \
      F_known_not, \
      f_string_dynamics_t_initialize, \
    }

  #define macro_controller_rule_action_t_delete_simple(action) \
    f_macro_string_dynamics_t_delete_simple(action.parameters)
#endif // _di_controller_rule_action_t_

#ifndef _di_controller_rule_actions_t_
  typedef struct {
    uint8_t method;
    uint8_t type;

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
      macro_controller_rule_action_t_delete_simple(actions.array[actions.used]); \
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

    controller_rule_actions_t actions;
  } controller_rule_item_t;

  #define controller_rule_item_t_initialize \
    { \
      0, \
      0, \
      controller_rule_actions_t_initialize, \
    }

  #define macro_controller_rule_item_t_delete_simple(item) \
    macro_controller_rule_actions_t_delete_simple(item.actions)
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

  typedef struct {
    f_status_t status;

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

  #define macro_controller_rule_t_delete_simple(rule) \
    f_macro_string_dynamic_t_delete_simple(rule.id) \
    f_macro_string_dynamic_t_delete_simple(rule.name) \
    f_macro_string_dynamic_t_delete_simple(rule.control_group) \
    f_macro_string_dynamic_t_delete_simple(rule.path) \
    f_macro_string_maps_t_delete_simple(rule.define) \
    f_macro_string_maps_t_delete_simple(rule.parameter) \
    f_macro_string_dynamics_t_delete_simple(rule.environment) \
    f_macro_string_dynamics_t_delete_simple(rule.need) \
    f_macro_string_dynamics_t_delete_simple(rule.want) \
    f_macro_string_dynamics_t_delete_simple(rule.wish) \
    macro_controller_rule_items_t_delete_simple(rule.items)
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
    f_number_unsigned_t timeout;

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

  #define macro_controller_entry_action_t_delete_simple(action) \
    f_macro_string_dynamics_t_delete_simple(action.parameters)
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

  #define macro_controller_entry_actions_t_delete_simple(actions) \
    actions.used = actions.size; \
    while (actions.used > 0) { \
      actions.used--; \
      macro_controller_entry_action_t_delete_simple(actions.array[actions.used]); \
      if (!actions.used) { \
        if (f_memory_delete((void **) & actions.array, sizeof(controller_entry_action_t), actions.size)) { \
          actions.size = 0; \
        } \
      } \
    }
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

  #define macro_controller_entry_item_t_delete_simple(item) \
    f_macro_string_dynamic_t_delete_simple(item.name) \
    macro_controller_entry_actions_t_delete_simple(item.actions)
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
      macro_controller_entry_item_t_delete_simple(items.array[items.used]); \
      if (!items.used) { \
        if (f_memory_delete((void **) & items.array, sizeof(controller_entry_item_t), items.size)) { \
          items.size = 0; \
        } \
      } \
    }
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

  #define macro_controller_entry_t_delete_simple(entry) \
    macro_controller_entry_items_t_delete_simple(entry.items)
#endif // _di_controller_entry_t_

#ifndef _di_controller_setting_t
  typedef struct {
    bool interruptable;
    bool ready;

    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;

    controller_entry_t entry;
    controller_rules_t rules;
  } controller_setting_t;

  #define controller_setting_t_initialize \
    { \
      F_false, \
      F_false, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      controller_entry_t_initialize, \
      controller_rules_t_initialize, \
    }

  #define macro_controller_setting_t_delete_simple(setting) \
    f_macro_string_dynamic_t_delete_simple(setting.path_pid) \
    f_macro_string_dynamic_t_delete_simple(setting.path_setting) \
    macro_controller_entry_t_delete_simple(setting.entry) \
    macro_controller_rules_t_delete_simple(setting.rules)
#endif // _di_controller_setting_t

/**
 * Load a file from the controller settings directory.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param path_prefix
 *   The path prefix, such as 'entries' from '/etc/controller/entries/default.entry'.
 * @param path_name
 *   The path name, such as 'default' from '/etc/controller/entries/default.entry'.
 * @param path_suffix
 *   The path suffix, such as 'entry' from '/etc/controller/entries/default.entry'.
 * @param path_prefix_length
 *   The length of the prefix path.
 * @param path_suffix_length
 *   The length of the suffix path.
 * @param path_file
 *   This is updated with a partial path to the given file.
 * @param buffer
 *   The buffer to load the file into.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *
 * @see f_file_stream_open()
 * @see f_file_stream_read()
 */
#ifndef _di_controller_file_load_
  extern f_return_status controller_file_load(const controller_data_t data, const controller_setting_t setting, const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_string_length_t path_prefix_length, const f_string_length_t path_suffix_length, f_string_dynamic_t *path_file, f_string_dynamic_t *buffer) f_gcc_attribute_visibility_internal;
#endif // _di_controller_file_load_

/**
 * Create the pid file, if possible.
 *
 * @param data
 *   The program data.
 * @param path_pid
 *   The file path to the pid file to create.
 *
 * @return
 *   F_none on success.
 *   F_access_denied if pid file is not created due to access denied errors.
 *   F_directory_not if pid file is not created due to a parent directory is unavailable or invalid.
 *
 *   Errors (with error bit) from: f_directory_exists().
 *   Errors (with error bit) from: f_file_name_directory().
 *   Errors (with error bit) from: f_file_stream_open().
 *
 * @see f_directory_exists()
 * @see f_file_name_directory()
 * @see f_file_stream_open()
 */
#ifndef _di_controller_file_pid_create_
  f_return_status controller_file_pid_create(const controller_data_t data, const f_string_static_t path_pid) f_gcc_attribute_visibility_internal;
#endif // _di_controller_file_pid_create_

/**
 * Delete the pid file, if exists and is valid.
 *
 * This is meant to be called on exit and avoids checking status codes, returning void.
 *
 * @param data
 *   The program data.
 * @param path_pid
 *   The file path to the pid file to create.
 */
#ifndef _di_controller_file_pid_delete_
  void controller_file_pid_delete(const controller_data_t data, const f_string_static_t path_pid) f_gcc_attribute_visibility_internal;
#endif // _di_controller_file_pid_delete_

/**
 * Given a wide range of status codes, simplify them down to a small subset.
 *
 * @param status
 *   The status code (without the error bit set) to simplify.
 *
 * @return
 *   A subset of status codes with error bit set.
 */
#ifndef _di_controller_status_simplify_
  extern f_return_status controller_status_simplify(const f_status_t status) f_gcc_attribute_visibility_internal;
#endif // _di_controller_status_simplify_

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
