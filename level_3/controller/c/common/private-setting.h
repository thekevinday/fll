/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_setting_h
#define _PRIVATE_common_setting_h

#ifdef __cplusplus
extern "C" {
#endif

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
 *   - helper:  Run as a helper, exiting when finished prrocess entry (and any respective exit).
 *   - program: Run as a program, exiting when finished prrocess entry (and any respective exit).
 *   - service: Run as a service, listening for requests after processing entry.
 *
 * controller_setting_flag_*:
 *   - interruptible: When specified, program responds to interrupt signals, otherwise block/ignore interrupt signals.
 *   - pid_created:   When specified, the program responds to interrupt signals, otherwise block/ignore interrupt signals.
 *   - failsafe:      When specified, failsafe mode is enabled, otherwise failsafe mode is disabled.
 *
 * flag:             Flags from controller_setting_flag_*.
 * ready:            State representing if the settings are all loaded and is ready to run program operations.
 * mode:             Controller setting mode based on the setting mode enumerator.
 * control:          The control socket data.
 * failsafe_item_id: The Entry Item ID to execute when failsafe execution is enabled.
 * path_cgroup:      Directory path to the cgroup directory.
 * path_control:     File path to the control socket (used for printing the path).
 * path_pid:         File path to the PID file.
 * path_setting:     File path to the setting directory.
 * entry:            The Entry settings.
 * rules:            All rules and their respective settings.
 */
#ifndef _di_controller_setting_t_
  enum {
    controller_setting_ready_no_e = 0,
    controller_setting_ready_wait_e,
    controller_setting_ready_yes_e,
    controller_setting_ready_done_e,
    controller_setting_ready_fail_e,
    controller_setting_ready_abort_e,
  }; // enum

  enum {
    controller_setting_mode_service_e = 0,
    controller_setting_mode_helper_e,
    controller_setting_mode_program_e,
  }; // enum

  enum {
    controller_setting_flag_interruptible_e = 0x1,
    controller_setting_flag_pid_created_e   = 0x2,
    controller_setting_flag_failsafe_e      = 0x4,
  }; // enum

  typedef struct {
    uint8_t flag;
    uint8_t ready;
    uint8_t mode;

    f_number_unsigned_t failsafe_item_id;

    controller_control_t control;

    f_string_dynamic_t path_cgroup;
    f_string_dynamic_t path_control;
    f_string_dynamic_t path_current;
    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;

    f_string_dynamic_t name_entry;

    controller_entry_t entry;
    controller_entry_t exit;
    controller_rules_t rules;
  } controller_setting_t;

  #define controller_setting_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    controller_control_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    controller_entry_t_initialize, \
    controller_entry_t_initialize, \
    controller_rules_t_initialize, \
  }
#endif // _di_controller_setting_t_

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
  extern void controller_setting_delete_simple(controller_setting_t * const setting) F_attribute_visibility_internal_d;
#endif // _di_controller_setting_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_setting_h
