/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_rule_h
#define _PRIVATE_common_rule_h

#ifdef __cplusplus
extern "C" {
#endif

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
 * type:       The Rule Action type.
 * line:       The line number where the Rule Action begins.
 * status:     The last execution status of the Rule Action.
 * parameters: All parameters associated with the Rule Action.
 */
#ifndef _di_controller_rule_action_t_
  #define CONTROLLER_rule_action_method_string_extended_s      "FSS-0001 (Extended)"
  #define CONTROLLER_rule_action_method_string_extended_list_s "FSS-0003 (Extended List)"

  #define CONTROLLER_rule_action_method_string_extended_s_length      19
  #define CONTROLLER_rule_action_method_string_extended_list_s_length 24

  extern const f_string_static_t controller_rule_action_method_string_extended_s;
  extern const f_string_static_t controller_rule_action_method_string_extended_list_s;

  enum {
    controller_rule_action_method_extended_e = 1,
    controller_rule_action_method_extended_list_e,
  };

  typedef struct {
    uint8_t type;
    f_array_length_t line;
    f_status_t status;

    f_string_dynamics_t parameters;
    f_iki_datas_t ikis;
  } controller_rule_action_t;

  #define controller_rule_action_t_initialize { \
    0, \
    0, \
    F_known_not, \
    f_string_dynamics_t_initialize, \
    f_iki_datas_t_initialize, \
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
  typedef struct {
    uint8_t type;
    uint8_t with;
    f_array_length_t line;

    f_string_dynamic_t pid_file;
    controller_rule_rerun_t reruns[controller_rule_action_execute_type__enum_size_e];
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
 *   - affinity:    Setting type representing a affinity.
 *   - capability:  Setting type representing a capability.
 *   - cgroup:      Setting type representing a control group.
 *   - define:      Setting type representing a define.
 *   - engine:      Setting type representing a engine.
 *   - environment: Setting type representing a environment.
 *   - group:       Setting type representing a group.
 *   - limit:       Setting type representing a limit.
 *   - name:        Setting type representing a name.
 *   - nice:        Setting type representing a nice.
 *   - on:          Setting type representing a on.
 *   - parameter:   Setting type representing a parameter.
 *   - path:        Setting type representing a path.
 *   - scheduler:   Setting type representing a scheduler.
 *   - user:        Setting type representing a user.
 *
 * controller_rule_has_*:
 *   - cgroup:    Has type representing a control group.
 *   - group:     Has type representing a group.
 *   - nice:      Has type representing a nice.
 *   - scheduler: Has type representing a scheduler.
 *   - user:      Has type representing a user.
 *
 * affinity:      The cpu affinity to be used when executing the Rule.
 * alias:         The distinct ID (machine name) of the Rule, such as "service/ssh".
 * capability:    The capability setting if the Rule "has" a capability.
 * cgroup:        The control group setting if the Rule "has" a control group.
 * define:        Any defines (environment variables) made available to the Rule for IKI substitution or just as environment variables.
 * engine:        The program or path to the program of the scripting engine to use when processing scripts in this Rule.
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
 * status:        A set of action-specific success/failure status of the Rule. Each index represents a controller_rule_action_type_* enum value. Index 0 represents a global status.
 * timeout_kill:  The timeout to wait relating to using a kill signal.
 * timeout_start: The timeout to wait relating to starting a process.
 * timeout_stop:  The timeout to wait relating to stopping a process.
 * timestamp:     The timestamp when the Rule was loaded.
 * user:          The User ID if the Rule "has" a user.
 */
#ifndef _di_controller_rule_t_
  enum {
    controller_rule_setting_type_affinity_e = 1,
    controller_rule_setting_type_capability_e,
    controller_rule_setting_type_cgroup_e,
    controller_rule_setting_type_define_e,
    controller_rule_setting_type_engine_e,
    controller_rule_setting_type_environment_e,
    controller_rule_setting_type_group_e,
    controller_rule_setting_type_limit_e,
    controller_rule_setting_type_name_e,
    controller_rule_setting_type_nice_e,
    controller_rule_setting_type_on_e,
    controller_rule_setting_type_parameter_e,
    controller_rule_setting_type_path_e,
    controller_rule_setting_type_scheduler_e,
    controller_rule_setting_type_timeout_e,
    controller_rule_setting_type_user_e,
  };

  // bitwise codes representing properties on controller_rule_t that have been found in the Rule file.
  #define controller_rule_has_cgroup_d 0x1
  #define controller_rule_has_environment_d   0x2
  #define controller_rule_has_group_d         0x4
  #define controller_rule_has_nice_d          0x8
  #define controller_rule_has_scheduler_d     0x10
  #define controller_rule_has_user_d          0x20

  // Designate codes for timeout settings to be used during the loading of the Rule timeout settings.
  #define controller_rule_timeout_code_kill_d  1
  #define controller_rule_timeout_code_start_d 2
  #define controller_rule_timeout_code_stop_d  3

  typedef struct {
    f_status_t status[controller_rule_action_type__enum_size_e];

    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    uint8_t has;
    int nice;
    uid_t user;
    gid_t group;

    f_time_spec_t timestamp;

    f_string_dynamic_t alias;
    f_string_dynamic_t engine;
    f_string_dynamic_t name;
    f_string_dynamic_t path;

    f_string_maps_t define;
    f_string_maps_t parameter;

    f_string_dynamics_t environment;

    f_int32s_t affinity;
    f_capability_t capability;
    f_control_group_t cgroup;
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
 * Fully deallocate all memory for the given Rule Action without caring about return status.
 *
 * @param action
 *   The action to deallocate.
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_controller_rule_action_delete_simple_
  extern void controller_rule_action_delete_simple(controller_rule_action_t * const action) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_action_delete_simple_

/**
 * Fully deallocate all memory for the given Rule Actions without caring about return status.
 *
 * @param actions
 *   The rule_actions to deallocate.
 *
 * @see controller_rule_action_delete_simple()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_actions_delete_simple_
  extern void controller_rule_actions_delete_simple(controller_rule_actions_t * const actions) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_actions_delete_simple_

/**
 * Increase the size of the Rule Actions array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param actions
 *   The actions to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_controller_rule_actions_increase_by_
  extern f_status_t controller_rule_actions_increase_by(const f_array_length_t amount, controller_rule_actions_t * const actions) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_actions_increase_by_

/**
 * Fully deallocate all memory for the given Rule without caring about return status.
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
  extern void controller_rule_delete_simple(controller_rule_t * const rule) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_delete_simple_

/**
 * Fully deallocate all memory for the given Rule Item without caring about return status.
 *
 * @param item
 *   The item to deallocate.
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_rule_item_delete_simple_
  extern void controller_rule_item_delete_simple(controller_rule_item_t * const item) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_item_delete_simple_

/**
 * Fully deallocate all memory for the given Rule Items without caring about return status.
 *
 * @param items
 *   The rule_items to deallocate.
 *
 * @see controller_rule_item_delete_simple()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_items_delete_simple_
  extern void controller_rule_items_delete_simple(controller_rule_items_t * const items) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_items_delete_simple_

/**
 * Fully deallocate all memory for the given Rule Item without caring about return status.
 *
 * @param on
 *   The on to deallocate.
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_rule_on_delete_simple_
  extern void controller_rule_on_delete_simple(controller_rule_on_t * const on) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_on_delete_simple_

/**
 * Fully deallocate all memory for the given Rule Items without caring about return status.
 *
 * @param ons
 *   The rule_ons to deallocate.
 *
 * @see controller_rule_on_delete_simple()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_ons_delete_simple_
  extern void controller_rule_ons_delete_simple(controller_rule_ons_t * const ons) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_ons_delete_simple_

/**
 * Increase the size of the Rule array, but only if necessary.
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
  extern f_status_t controller_rule_ons_increase(controller_rule_ons_t * const ons) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_increase_

/**
 * Resize the Rule array.
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
  extern f_status_t controller_rule_ons_resize(const f_array_length_t length, controller_rule_ons_t * const ons) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_ons_resize_

/**
 * Fully deallocate all memory for the given Rules without caring about return status.
 *
 * @param rules
 *   The rules to deallocate.
 *
 * @see controller_rules_resize()
 */
#ifndef _di_controller_rules_delete_simple_
  extern void controller_rules_delete_simple(controller_rules_t * const rules) F_attribute_visibility_internal_d;
#endif // _di_controller_rules_delete_simple_

/**
 * Increase the size of the Rule array, but only if necessary.
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
  extern f_status_t controller_rules_increase(controller_rules_t * const rules) F_attribute_visibility_internal_d;
#endif // _di_controller_rule_increase_

/**
 * Resize the Rule array.
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
  extern f_status_t controller_rules_resize(const f_array_length_t length, controller_rules_t * const rules) F_attribute_visibility_internal_d;
#endif // _di_controller_rules_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_rule_h
