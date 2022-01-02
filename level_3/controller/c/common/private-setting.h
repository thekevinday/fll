/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
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
 *   - program: Run as a program, exiting when finished prrocess entry (and any respective exit).
 *   - service: Run as a service, listening for requests after processing entry.
 *
 * interruptible:      TRUE if the program responds to interrupt signals, FALSE to block/ignore interrupt signals.
 * pid_created:        TRUE if the PID file has been created.
 * ready:              State representing if the settings are all loaded and is ready to run program operations.
 * mode:               Controller setting mode based on the setting mode enumerator.
 * control_group:      Group role of the control socket.
 * control_moode:      Mode role of the control socket.
 * control_readonly:   TRUE if the control is set to readonly, FALSE otherwise.
 * control_socket:     The control socket data.
 * control_user:       User role of the control socket.
 * failsafe_enabled:   TRUE if failsafe execution is enabled, FALSE otherwise.
 * failsafe_item_id:   The Entry Item ID to execute when failsafe execution is enabled.
 * path_cgroup:        Directory path to the cgroup directory.
 * path_control:       File path to the control socket.
 * path_pid:           File path to the PID file.
 * path_setting:       File path to the setting directory.
 * entry:              The Entry settings.
 * rules:              All rules and their respective settings.
 */
#ifndef _di_controller_setting_t
  enum {
    controller_setting_ready_no_e = 0,
    controller_setting_ready_wait_e,
    controller_setting_ready_yes_e,
    controller_setting_ready_done_e,
    controller_setting_ready_fail_e,
    controller_setting_ready_abort_e,
  };

  enum {
    controller_setting_mode_service_e = 0,
    controller_setting_mode_program_e,
  };

  typedef struct {
    bool interruptible;
    bool pid_created;
    uint8_t ready;
    uint8_t mode;

    gid_t control_group;
    mode_t control_mode;
    bool control_readonly;
    f_socket_t control_socket;
    uid_t control_user;

    bool failsafe_enabled;
    f_array_length_t failsafe_item_id;

    f_string_dynamic_t path_cgroup;
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
    0, \
    0, \
    F_false, \
    f_socket_t_initialize, \
    0, \
    F_false, \
    0, \
    f_string_dynamic_t_initialize, \
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_setting_h
