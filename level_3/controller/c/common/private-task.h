/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_task_h
#define _PRIVATE_common_task_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A Task Action.
 *
 * controller_task_action_method_*:
 *   - extended:      Designate that this Action is represented using FSS Extended.
 *   - extended_list: Designate that this Action is represented using FSS Extended List.
 *
 * help:       The help text associated with this action.
 * line:       The line number where the Task Action begins.
 * parameters: All parameters associated with the Task Action.
 * status:     The last execution status of the Task Action.
 * type:       The Task Action type, this references an index in the controller_task_parameters_t for the parent Task.
 */
#ifndef _di_controller_task_action_t_
  #define controller_task_action_method_string_extended_s      "FSS-0001 (Extended)"
  #define controller_task_action_method_string_extended_list_s "FSS-0003 (Extended List)"

  #define controller_task_action_method_string_extended_s_length      19
  #define controller_task_action_method_string_extended_list_s_length 24

  enum {
    controller_task_action_method_extended_e = 1,
    controller_task_action_method_extended_list_e,
  };

  typedef struct {
    f_status_t status;
    f_array_length_t type;
    f_array_length_t line;

    f_string_dynamic_t help;
    f_string_dynamics_t parameters;
  } controller_task_action_t;

  #define controller_task_action_t_initialize { \
    F_known_not, \
    0, \
    0, \
    f_string_dynamic_t_initialize, \
    f_string_dynamics_t_initialize, \
  }
#endif // _di_controller_task_action_t_

/**
 * The Task Actions.
 *
 * array: An array of Task Actions.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_task_actions_t_
  typedef struct {
    controller_task_action_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_task_actions_t;

  #define controller_task_actions_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_task_actions_t_

/**
 * A Task structure.
 *
 * controller_task_setting_type_*:
 *   - affinity:    Setting type representing a affinity.
 *   - capability:  Setting type representing a capability.
 *   - cgroup:      Setting type representing a cgroup (control group).
 *   - define:      Setting type representing a define.
 *   - environment: Setting type representing a environment.
 *   - group:       Setting type representing a group.
 *   - limit:       Setting type representing a limit.
 *   - name:        Setting type representing a name.
 *   - nice:        Setting type representing a nice.
 *   - parameter:   Setting type representing a parameter.
 *   - path:        Setting type representing a path.
 *   - scheduler:   Setting type representing a scheduler.
 *   - script:      Setting type representing a script.
 *   - user:        Setting type representing a user.
 *
 * controller_task_has_*:
 *   - cgroup:    Has type representing a cgroup (control group).
 *   - group:     Has type representing a group.
 *   - nice:      Has type representing a nice.
 *   - scheduler: Has type representing a scheduler.
 *   - user:      Has type representing a user.
 *
 * affinity:    The cpu affinity to be used when executing the Task.
 * alias:       The distinct ID (machine name) of the Task, such as "service/ssh".
 * arguments:   The arguments (parameters) passed to the Task, which are exposed via the IKI substitution.
 * capability:  The capability setting if the Task "has" a capability.
 * cgroup:      The cgroup (control group) setting if the Task "has" a cgroup (control group).
 * define:      Any defines (environment variables) made available to the Task for IKI substitution or just as environment variables.
 * environment: All environment variables allowed to be exposed to the Task when processing.
 * group:       The group ID if the Task "has" a group.
 * groups:      A set of group IDs to run the process with (first specified group is the primary group).
 * has:         Bitwise set of "has" codes representing what the Task has.
 * limits:      The cpu/resource limits to use when executing the Task.
 * name:        A human name for the Task (does not have to be distinct), such as "Bash Script".
 * nice:        The niceness value if the Task "has" nice.
 * parameter:   Any parameters made available to the Task for IKI substitution.
 * path:        The path to the Task file.
 * scheduler:   The scheduler setting if the Task "has" a scheduler.
 * script:      The program or path to the program of the scripting engine to use when processing scripts in this Task.
 * state:       The current active/inactive state of the Task.
 * status:      The last returned status of the Task.
 * timestamp:   The timestamp when the Task was last updated.
 * user:        The User ID if the Task "has" a user.
 */
#ifndef _di_controller_task_t_
  enum {
    controller_task_setting_type_affinity_e = 1,
    controller_task_setting_type_capability_e,
    controller_task_setting_type_cgroup_e,
    controller_task_setting_type_define_e,
    controller_task_setting_type_environment_e,
    controller_task_setting_type_group_e,
    controller_task_setting_type_limit_e,
    controller_task_setting_type_name_e,
    controller_task_setting_type_nice_e,
    controller_task_setting_type_parameter_e,
    controller_task_setting_type_path_e,
    controller_task_setting_type_scheduler_e,
    controller_task_setting_type_script_e,
    controller_task_setting_type_user_e,
  };

  // Bitwise codes representing properties on controller_task_t that have been found in the Task file.
  #define controller_task_has_cgroup_d 0x1
  #define controller_task_has_environment_d   0x2
  #define controller_task_has_group_d         0x4
  #define controller_task_has_nice_d          0x8
  #define controller_task_has_scheduler_d     0x10
  #define controller_task_has_user_d          0x20

  typedef struct {
    f_status_t state;
    f_status_t status;

    uint8_t has;
    int nice;
    uid_t user;
    gid_t group;

    f_time_spec_t timestamp;

    f_string_dynamic_t alias;
    f_string_dynamic_t help;
    f_string_dynamic_t name;
    f_string_dynamic_t path;
    f_string_dynamic_t script;

    f_string_maps_t arguments;
    f_string_maps_t defines;
    f_string_maps_t parameters;

    f_string_dynamics_t environment;

    f_int32s_t affinity;
    f_capability_t capability;
    f_control_group_t cgroup;
    f_int32s_t groups;
    f_limit_sets_t limits;
    f_execute_scheduler_t scheduler;

    controller_task_actions_t actions;
  } controller_task_t;

  #define controller_task_t_initialize { \
    F_none, \
    F_none, \
    0, \
    0, \
    0, \
    0, \
    f_time_spec_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_maps_t_initialize, \
    f_string_maps_t_initialize, \
    f_string_maps_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_int32s_t_initialize, \
    f_capability_t_initialize, \
    f_control_group_t_initialize, \
    f_int32s_t_initialize, \
    f_limit_sets_t_initialize, \
    f_execute_scheduler_t_initialize, \
    controller_task_actions_t_initialize, \
  }
#endif // _di_controller_task_t_

/**
 * The Tasks.
 *
 * array: An array of Tasks.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_controller_tasks_t_
  typedef struct {
    controller_task_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_tasks_t;

  #define controller_tasks_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_tasks_t_

/**
 * Fully deallocate all memory for the given Task Action without caring about return status.
 *
 * @param action
 *   The action to deallocate.
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_controller_task_action_delete_simple_
  extern void controller_task_action_delete_simple(controller_task_action_t * const action) F_attribute_visibility_internal_d;
#endif // _di_controller_task_action_delete_simple_

/**
 * Fully deallocate all memory for the given Task Actions without caring about return status.
 *
 * @param actions
 *   The task_actions to deallocate.
 *
 * @see f_memory_delete()
 *
 * @see controller_task_action_delete_simple()
 */
#ifndef _di_controller_task_actions_delete_simple_
  extern void controller_task_actions_delete_simple(controller_task_actions_t *actions) F_attribute_visibility_internal_d;
#endif // _di_controller_task_actions_delete_simple_

/**
 * Increase the size of the Task Actions array by the specified amount, but only if necessary.
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
#ifndef _di_controller_task_actions_increase_by_
  extern f_status_t controller_task_actions_increase_by(const f_array_length_t amount, controller_task_actions_t * const actions) F_attribute_visibility_internal_d;
#endif // _di_controller_task_actions_increase_by_

/**
 * Fully deallocate all memory for the given Rule without caring about return status.
 *
 * @param task
 *   The task to deallocate.
 *
 * @see macro_f_control_group_t_delete_simple()
 * @see macro_f_int32s_t_delete_simple()
 * @see macro_f_limit_sets_t_delete_simple()
 * @see macro_f_string_dynamics_t_delete_simple()
 * @see macro_f_string_maps_t_delete_simple()
 * @see macro_f_thread_condition_t_delete_simple()
 * @see macro_f_thread_mutex_t_delete_simple()
 *
 * @see f_capability_delete()
 * @see f_string_dynamic_resize()
 *
 * @see controller_task_items_delete_simple()
 */
#ifndef _di_controller_task_delete_simple_
  extern void controller_task_delete_simple(controller_task_t * const task) F_attribute_visibility_internal_d;
#endif // _di_controller_task_delete_simple_

/**
 * Fully deallocate all memory for the given Tasks without caring about return status.
 *
 * @param tasks
 *   The tasks to deallocate.
 *
 * @see controller_tasks_resize()
 */
#ifndef _di_controller_tasks_delete_simple_
  extern void controller_tasks_delete_simple(controller_tasks_t * const tasks) F_attribute_visibility_internal_d;
#endif // _di_controller_tasks_delete_simple_

/**
 * Increase the size of the Task array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param tasks
 *   The task array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_tasks_resize()
 */
#ifndef _di_controller_tasks_increase_
  extern f_status_t controller_tasks_increase(controller_tasks_t * const tasks) F_attribute_visibility_internal_d;
#endif // _di_controller_task_increase_

/**
 * Resize the Task array.
 *
 * @param length
 *   The new size to use.
 * @param tasks
 *   The task array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_tasks_resize_
  extern f_status_t controller_tasks_resize(const f_array_length_t length, controller_tasks_t * const tasks) F_attribute_visibility_internal_d;
#endif // _di_controller_tasks_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_task_h
