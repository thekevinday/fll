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

  #define control_signal_check_d 20000

  #define control_allocation_large_d 256
  #define control_allocation_small_d 16
#endif // _di_control_defines_s_

/**
 * A codes repesent different flags associated with a packet.
 *
 * control_packet_flag_*:
 *   - binary:     Designate that the packet is in binary mode (when not set then packet is in string mode).
 *   - endian_big: Designate that the packet is in big endian order (when not set then packet is in little endian order).
 */
#ifndef _di_control_packet_flag_
  #define control_packet_flag_binary_d     0x80
  #define control_packet_flag_endian_big_d 0x40
#endif // _di_control_packet_flag_

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

  #define CONTROL_action_s             "action"
  #define CONTROL_controller_s         "controller"
  #define CONTROL_default_s            "default"
  #define CONTROL_error_s              "error"
  #define CONTROL_kexec_s              "kexec"
  #define CONTROL_init_s               "init"
  #define CONTROL_length_s             "length"
  #define CONTROL_name_socket_s        "name_socket"
  #define CONTROL_path_socket_s        "path_socket"
  #define CONTROL_path_socket_prefix_s "path_socket_prefix"
  #define CONTROL_path_socket_suffix_s "path_socket_suffix"
  #define CONTROL_status_s             "status"
  #define CONTROL_type_s               "type"

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

  #define CONTROL_action_s_length             6
  #define CONTROL_controller_s_length         10
  #define CONTROL_default_s_length            7
  #define CONTROL_error_s_length              5
  #define CONTROL_init_s_length               4
  #define CONTROL_kexec_s_length              5
  #define CONTROL_length_s_length             6
  #define CONTROL_name_socket_s_length        11
  #define CONTROL_path_socket_s_length        11
  #define CONTROL_path_socket_prefix_s_length 18
  #define CONTROL_path_socket_suffix_s_length 18
  #define CONTROL_status_s_length             6
  #define CONTROL_type_s_length               4

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

  extern const f_string_static_t control_action_s;
  extern const f_string_static_t control_controller_s;
  extern const f_string_static_t control_default_s;
  extern const f_string_static_t control_error_s;
  extern const f_string_static_t control_init_s;
  extern const f_string_static_t control_kexec_s;
  extern const f_string_static_t control_length_s;
  extern const f_string_static_t control_name_socket_s;
  extern const f_string_static_t control_path_socket_s;
  extern const f_string_static_t control_path_socket_prefix_s;
  extern const f_string_static_t control_path_socket_suffix_s;
  extern const f_string_static_t control_status_s;
  extern const f_string_static_t control_type_s;

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
 * The control cache.
 *
 * large:  A buffer for storing large sets of data.
 * small:  A buffer for storing small sets of data.
 * packet: A buffer for storing the send packet or the response payload.
 *
 * packet_objects:  The FSS Objects for a packet.
 * packet_contents: The FSS Contents for a packet.
 *
 * header_objects:  The FSS Objects for a packet payload header.
 * header_contents: The FSS Contents for a packet payload header.
 *
 * delimits: The delimits cache.
 */
#ifndef _di_control_cache_t_
  typedef struct {
    f_string_dynamic_t large;
    f_string_dynamic_t small;
    f_string_dynamic_t packet;

    f_fss_objects_t packet_objects;
    f_fss_contents_t packet_contents;

    f_fss_objects_t header_objects;
    f_fss_contents_t header_contents;

    f_fss_delimits_t delimits;
  } control_cache_t;

  #define control_cache_initialize \
    { \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_objects_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_objects_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_delimits_t_initialize, \
    }
#endif // _di_control_cache_t_

/**
 * The control data.
 *
 * action: The action type code.
 * argv:   The argument structure in the progam data parameters for simplifying syntax.
 * cache:  A cache.
 * socket: A socket used to connect to the controller.
 */
#ifndef _di_control_data_t_
  typedef struct {
    uint8_t action;

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
 * The packet payload header data.
 *
 * The FSS-000E (Payload) supports multiple objects, but the Control packet does not support this, yet.
 *
 * action: The action type code, for any valid action (see: control_action_types enumeration).
 * type:   The packet type represented by the payload packet.
 * status: The status code represented by the payload packet.
 * length: The length of the payload content within the payload packet.
 */
#ifndef _di_control_payload_header_t_
  typedef struct {
    uint8_t action;
    uint8_t type;
    f_status_t status;
    uint16_t length;
  } control_payload_header_t;

  #define control_payload_header_t_initialize \
    { \
      0, \
      0, \
      f_status_t_initialize, \
      f_array_length_t_initialize, \
    }
#endif // _di_control_payload_header_t_

/**
 * Deallocate the control data.
 *
 * @param data
 *   The control data.
 */
#ifndef _di_control_data_delete_
  extern void control_data_delete(control_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_control_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
