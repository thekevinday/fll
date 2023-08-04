/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_common_string_h
#define _control_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_control_program_version_s_
  #define CONTROL_program_version_major_s F_string_ascii_0_s
  #define CONTROL_program_version_minor_s F_string_ascii_7_s
  #define CONTROL_program_version_micro_s F_string_ascii_0_s

  #define CONTROL_program_version_major_s_length F_string_ascii_0_s_length
  #define CONTROL_program_version_minor_s_length F_string_ascii_7_s_length
  #define CONTROL_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(CONTROL_program_version_nano_prefix_s) && defined(CONTROL_program_version_nano_prefix_s_length))
    #define CONTROL_program_version_nano_prefix_s
    #define CONTROL_program_version_nano_prefix_s_length 0
  #endif // !(defined(CONTROL_program_version_nano_prefix_s) && defined(CONTROL_program_version_nano_prefix_s_length))

  #if !(defined(CONTROL_program_version_nano_s) && defined(CONTROL_program_version_nano_s_length))
    #define CONTROL_program_version_nano_s
    #define CONTROL_program_version_nano_s_length 0
  #endif // !(defined(CONTROL_program_version_nano_s) && defined(CONTROL_program_version_nano_s_length))

  #define CONTROL_program_version_s CONTROL_program_version_major_s F_string_ascii_period_s CONTROL_program_version_minor_s F_string_ascii_period_s CONTROL_program_version_micro_s CONTROL_program_version_nano_prefix_s CONTROL_program_version_nano_s

  #define CONTROL_program_version_s_length CONTROL_program_version_major_s_length + F_string_ascii_period_s_length + CONTROL_program_version_minor_s_length + F_string_ascii_period_s_length + CONTROL_program_version_micro_s_length + CONTROL_program_version_nano_prefix_s_length + CONTROL_program_version_nano_s_length

  extern const f_string_static_t control_program_version_s;
#endif // _di_control_program_version_s_

/**
 * The program name.
 */
#ifndef _di_control_program_name_s_
  #define CONTROL_program_name_s      "control"
  #define CONTROL_program_name_long_s "Control Program"

  #define CONTROL_program_name_s_length      7
  #define CONTROL_program_name_long_s_length 15

  extern const f_string_static_t control_program_name_s;
  extern const f_string_static_t control_program_name_long_s;
#endif // _di_control_program_name_s_

/**
 * The main program parameters.
 */
#ifndef _di_control_parameter_s_
  #define CONTROL_short_name_s     "n"
  #define CONTROL_short_return_s   "R"
  #define CONTROL_short_settings_s "s"
  #define CONTROL_short_socket_s   "k"

  #define CONTROL_long_name_s     "name"
  #define CONTROL_long_return_s   "return"
  #define CONTROL_long_settings_s "settings"
  #define CONTROL_long_socket_s   "socket"

  #define CONTROL_short_name_s_length     1
  #define CONTROL_short_return_s_length   1
  #define CONTROL_short_settings_s_length 1
  #define CONTROL_short_socket_s_length   1

  #define CONTROL_long_name_s_length     4
  #define CONTROL_long_return_s_length   6
  #define CONTROL_long_settings_s_length 8
  #define CONTROL_long_socket_s_length   6

  extern const f_string_static_t control_short_name_s;
  extern const f_string_static_t control_short_return_s;
  extern const f_string_static_t control_short_settings_s;
  extern const f_string_static_t control_short_socket_s;

  extern const f_string_static_t control_long_name_s;
  extern const f_string_static_t control_long_return_s;
  extern const f_string_static_t control_long_settings_s;
  extern const f_string_static_t control_long_socket_s;
#endif // _di_control_parameter_s_

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
  #define CONTROL_at_s                 "at"
  #define CONTROL_controller_s         "controller"
  #define CONTROL_default_s            "default"
  #define CONTROL_error_s              "error"
  #define CONTROL_kexec_s              "kexec"
  #define CONTROL_in_s                 "in"
  #define CONTROL_init_s               "init"
  #define CONTROL_length_s             "length"
  #define CONTROL_name_socket_s        "name_socket"
  #define CONTROL_now_s                "now"
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
  #define CONTROL_at_s_length                 2
  #define CONTROL_controller_s_length         10
  #define CONTROL_default_s_length            7
  #define CONTROL_error_s_length              5
  #define CONTROL_in_s_length                 2
  #define CONTROL_init_s_length               4
  #define CONTROL_kexec_s_length              5
  #define CONTROL_length_s_length             6
  #define CONTROL_name_socket_s_length        11
  #define CONTROL_now_s_length                3
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
  extern const f_string_static_t control_at_s;
  extern const f_string_static_t control_controller_s;
  extern const f_string_static_t control_default_s;
  extern const f_string_static_t control_error_s;
  extern const f_string_static_t control_in_s;
  extern const f_string_static_t control_init_s;
  extern const f_string_static_t control_kexec_s;
  extern const f_string_static_t control_length_s;
  extern const f_string_static_t control_name_socket_s;
  extern const f_string_static_t control_now_s;
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
 * Controller defines that the control program utilizes.
 *
 * These are intended to exactly match the relevant controller string defines.
 */
#ifndef _di_controller_strings_s_

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
#endif // _di_controller_strings_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_common_string_h
