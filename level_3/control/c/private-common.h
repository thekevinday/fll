/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * General defines used throughout the program.
 *
 * control_default_*:
 *   - buffer_limit_soft_large: The preferred maximum size of buffers intended for large data sets such that sizes exceeding this will be shrunk when operations are complete (aka: a soft limit).
 *   - buffer_limit_soft_small: The preferred maximum size of buffers intended for small data sets such that sizes exceeding this will be shrunk when operations are complete (aka: a soft limit).
 *
 * control_signal_*:
 *   - check: The interval in which callbacks checking signal should actually perform the signal check (significantly improves perfomance).
 *
 * control_allocation_*:
 *   - large: Default allocation buffer size for buffers expected to work with large data sets.
 *   - small: Default allocation buffer size for buffers expected to work with small data sets.
 */
#ifndef _di_control_defines_s_
  #define control_default_buffer_limit_soft_large_d 2048
  #define control_default_buffer_limit_soft_small_d 64

  #define control_signal_check_d 10000

  #define control_allocation_large_d 256
  #define control_allocation_small_d 16
#endif // _di_control_defines_s_

/**
 * Controller defines that the control program utilizes.
 *
 * These are intended to exactly match the relevant controller string defines.
 */
#ifndef _di_controller_strings_

  // The name_socket is a system-specific path and should match the path compiled into the controller program.
  #if defined(_override_controller_name_socket_) && defined(_override_controller_name_socket_length_)
    #define CONTROLLER_name_socket_s _override_controller_name_socket_

    #define CONTROLLER_name_socket_s_length _override_controller_name_socket_length_
  #else
    #define CONTROLLER_name_socket_s "default"

    #define CONTROLLER_name_socket_s_length 7
  #endif // defined(_override_controller_name_socket_) && defined(_override_controller_name_socket_length_)

  // The path_socket is a system-specific path and should match the path compiled into the controller program.
  #if defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)
    #define CONTROLLER_path_socket_s _override_controller_path_socket_

    #define CONTROLLER_path_socket_s_length _override_controller_path_socket_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_socket_s "/var/run/init"

    #define CONTROLLER_path_socket_s_length 13
  #else
    #define CONTROLLER_path_socket_s "/var/run/controller"

    #define CONTROLLER_path_socket_s_length 19
  #endif // defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)

  // The name_socket_prefix is a system-specific path and should match the path compiled into the controller program.
  #if defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)
    #define CONTROLLER_path_socket_prefix_s _override_controller_path_socket_prefix_

    #define CONTROLLER_path_socket_prefix_s_length _override_controller_path_socket_prefix_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_socket_prefix_s "init-"

    #define CONTROLLER_path_socket_prefix_s_length 5
  #else
    #define CONTROLLER_path_socket_prefix_s ""

    #define CONTROLLER_path_socket_prefix_s_length 0
  #endif // defined(_override_controller_name_socket_prefix_) && defined(_override_controller_name_socket_prefix_length_)

  // The name_socket_suffix is a system-specific path and should match the path compiled into the controller program.
  #if defined(_override_controller_path_socket_suffix_) && defined(_override_controller_path_socket_suffix_length_)
    #define CONTROLLER_path_socket_suffix_s _override_controller_path_socket_suffix_

    #define CONTROLLER_path_socket_suffix_s_length _override_controller_path_socket_suffix_length_
  #else
    #define CONTROLLER_path_socket_suffix_s ".socket"

    #define CONTROLLER_path_socket_suffix_s_length 7
  #endif // defined(_override_controller_name_socket_suffix_) && defined(_override_controller_name_socket_suffix_length_)

  extern const f_string_static_t controller_name_socket_s;
  extern const f_string_static_t controller_path_socket_s;
  extern const f_string_static_t controller_path_socket_prefix_s;
  extern const f_string_static_t controller_path_socket_suffix_s;
#endif // _di_controller_strings_

/**
 * All special strings used within this program.
 */
#ifndef _di_control_strings_s_
  #if defined(_override_control_path_settings_) && defined(_override_control_path_settings_length_)
    #define CONTROL_path_settings_s _override_control_path_settings_

    #define CONTROL_path_settings_s_length _override_control_path_settings_length_
  #else
    #define CONTROL_path_settings_s "/etc/control/settings"

    #define CONTROL_path_settings_s_length 21
  #endif // defined(_override_control_path_settings_) && defined(_override_control_path_settings_length_)

  #define CONTROL_command_s            "command"
  #define CONTROL_default_s            "default"
  #define CONTROL_name_socket_s        "name_socket"
  #define CONTROL_path_socket_s        "path_socket"
  #define CONTROL_path_socket_prefix_s "path_socket_prefix"
  #define CONTROL_path_socket_suffix_s "path_socket_suffix"

  #define CONTROL_error_s    "error"
  #define CONTROL_freeze_s   "freeze"
  #define CONTROL_kill_s     "kill"
  #define CONTROL_pause_s    "pause"
  #define CONTROL_reboot_s   "reboot"
  #define CONTROL_reload_s   "reload"
  #define CONTROL_rerun_s    "rerun"
  #define CONTROL_restart_s  "restart"
  #define CONTROL_resume_s   "resume"
  #define CONTROL_shutdown_s "shutdown"
  #define CONTROL_start_s    "start"
  #define CONTROL_stop_s     "stop"
  #define CONTROL_thaw_s     "thaw"

  #define CONTROL_command_s_length            7
  #define CONTROL_default_s_length            7
  #define CONTROL_name_socket_s_length        11
  #define CONTROL_path_socket_s_length        11
  #define CONTROL_path_socket_prefix_s_length 18
  #define CONTROL_path_socket_suffix_s_length 18

  #define CONTROL_error_s_length    5
  #define CONTROL_freeze_s_length   6
  #define CONTROL_kill_s_length     4
  #define CONTROL_pause_s_length    5
  #define CONTROL_reboot_s_length   6
  #define CONTROL_reload_s_length   6
  #define CONTROL_rerun_s_length    5
  #define CONTROL_restart_s_length  7
  #define CONTROL_resume_s_length   6
  #define CONTROL_shutdown_s_length 8
  #define CONTROL_start_s_length    5
  #define CONTROL_stop_s_length     4
  #define CONTROL_thaw_s_length     4

  extern const f_string_static_t control_path_settings_s;

  extern const f_string_static_t control_command_s;
  extern const f_string_static_t control_default_s;
  extern const f_string_static_t control_name_socket_s;
  extern const f_string_static_t control_path_socket_s;
  extern const f_string_static_t control_path_socket_prefix_s;
  extern const f_string_static_t control_path_socket_suffix_s;

  extern const f_string_static_t control_error_s;
  extern const f_string_static_t control_freeze_s;
  extern const f_string_static_t control_kill_s;
  extern const f_string_static_t control_pause_s;
  extern const f_string_static_t control_reboot_s;
  extern const f_string_static_t control_reload_s;
  extern const f_string_static_t control_rerun_s;
  extern const f_string_static_t control_restart_s;
  extern const f_string_static_t control_resume_s;
  extern const f_string_static_t control_shutdown_s;
  extern const f_string_static_t control_start_s;
  extern const f_string_static_t control_stop_s;
  extern const f_string_static_t control_thaw_s;
#endif // _di_control_strings_s_

/**
 * Codes representing supported commands.
 *
 * freeze:   Perform the freeze controller operation.
 * kill:     Perform the kill controller operation.
 * pause:    Perform the pause controller operation.
 * reboot:   Perform the reboot controller operation (only for init mode).
 * reload:   Perform the reload controller operation.
 * rerun:    Perform the rerun controller operation.
 * restart:  Perform the restart controller operation.
 * resume:   Perform the resume controller operation.
 * shutdown: Perform the shutdown controller operation (only for init mode).
 * start:    Perform the start controller operation.
 * stop:     Perform the stop controller operation.
 * thaw:     Perform the thaw controller operation.
 */
#ifndef _di_control_command_types_
  enum {
    control_command_type_freeze_e = 1,
    control_command_type_kill_e,
    control_command_type_pause_e,
    control_command_type_reboot_e,
    control_command_type_reload_e,
    control_command_type_rerun_e,
    control_command_type_restart_e,
    control_command_type_resume_e,
    control_command_type_shutdown_e,
    control_command_type_start_e,
    control_command_type_stop_e,
    control_command_type_thaw_e,
  };
#endif // _di_control_command_types_

/**
 * The control cache.
 *
 * buffer_large: A buffer for storing large sets of data.
 * buffer_small: A buffer for storing small sets of data.
 */
#ifndef _di_control_cache_t_
  typedef struct {
    f_string_dynamic_t buffer_large;
    f_string_dynamic_t buffer_small;
  } control_cache_t;

  #define control_cache_initialize \
    { \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_control_cache_t_

/**
 * The control data.
 *
 * argv:    The argument structure in the progam data parameters for simplifying syntax.
 * command: The command type code.
 * cache:   A cache.
 * socket:  A socket used to connect to the controller.
 */
#ifndef _di_control_data_t_
  typedef struct {
    uint8_t command;

    control_cache_t cache;

    f_socket_t socket;

    f_string_static_t *argv;
  } control_data_t;

  #define control_data_t_initialize \
    { \
      0, \
      f_string_dynamic_t_initialize, \
      f_socket_t_initialize, \
      0, \
    }
#endif // _di_control_data_t_

/**
 * Deallocate the control data.
 *
 * @param data
 *   The control data.
 */
#ifndef _di_control_data_delete_
  extern void control_data_delete(control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_data_delete_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_control_signal_received_
  extern f_status_t control_signal_received(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_control_signal_received_

/**
 * Callback passed to FSS functions for checking for interrupts.
 *
 * @param state
 *   The f_state_t data.
 * @param internal
 *   Not used.
 *
 * @return
 *   F_interrupt_not if not interrupted.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 */
#ifndef _di_control_signal_state_interrupt_fss_
  extern f_status_t control_signal_state_interrupt_fss(void * const state, void * const internal) F_attribute_visibility_internal_d;
#endif // _di_control_signal_state_interrupt_fss_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
