/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_entry_h
#define _PRIVATE_common_entry_h

#ifdef __cplusplus
extern "C" {
#endif

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
    controller_entry_action_type_consider_e = 1,
    controller_entry_action_type_execute_e,
    controller_entry_action_type_failsafe_e,
    controller_entry_action_type_freeze_e,
    controller_entry_action_type_item_e,
    controller_entry_action_type_kill_e,
    controller_entry_action_type_pause_e,
    controller_entry_action_type_ready_e,
    controller_entry_action_type_reload_e,
    controller_entry_action_type_restart_e,
    controller_entry_action_type_resume_e,
    controller_entry_action_type_start_e,
    controller_entry_action_type_stop_e,
    controller_entry_action_type_timeout_e,
    controller_entry_action_type_thaw_e,
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
    controller_entry_pid_disable_e = 0,
    controller_entry_pid_require_e,
    controller_entry_pid_ready_e,
  };

  enum {
    controller_entry_show_normal_e = 0,
    controller_entry_show_init_e,
  };

  enum {
    controller_entry_session_none_e = 0,
    controller_entry_session_new_e,
    controller_entry_session_same_e,
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
    controller_entry_pid_require_e, \
    controller_entry_session_none_e, \
    controller_entry_show_normal_e, \
    0, \
    0, \
    0, \
    controller_entry_items_t_initialize, \
  }
#endif // _di_controller_entry_t_

/**
 * Fully deallocate all memory for the given entry action without caring about return status.
 *
 * @param action
 *   The action to deallocate.
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_controller_entry_action_delete_simple_
  extern void controller_entry_action_delete_simple(controller_entry_action_t * const action) F_attribute_visibility_internal_d;
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
  extern void controller_entry_actions_delete_simple(controller_entry_actions_t * const actions) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_actions_delete_simple_

/**
 * Increase the size of the entry item actions array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param actions
 *   The entry item actions to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_entry_actions_increase_by_
  extern f_status_t controller_entry_actions_increase_by(const f_array_length_t amount, controller_entry_actions_t * const actions) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_actions_increase_by_

/**
 * Fully deallocate all memory for the given entry item without caring about return status.
 *
 * @param item
 *   The item to deallocate.
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_controller_entry_item_delete_simple_
  extern void controller_entry_item_delete_simple(controller_entry_item_t * const item) F_attribute_visibility_internal_d;
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
  extern void controller_entry_items_delete_simple(controller_entry_items_t * const items) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_items_delete_simple_

/**
 * Increase the size of the entry items array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param items
 *   The entry items to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_entry_items_increase_by_
  extern f_status_t controller_entry_items_increase_by(const f_array_length_t amount, controller_entry_items_t * const items) F_attribute_visibility_internal_d;
#endif // _di_controller_entry_items_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_entry_h