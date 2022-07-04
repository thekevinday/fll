/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures to be compiled into the main program rather than the library.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_main_common_h
#define _controller_main_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program name.
 */
#ifndef _di_controller_program_name_
  #ifdef _controller_as_init_
    #define CONTROLLER_program_name_s      "init"
    #define CONTROLLER_program_name_long_s "Init Program"

    #define CONTROLLER_program_name_s_length      4
    #define CONTROLLER_program_name_long_s_length 12
  #else
    #define CONTROLLER_program_name_s      "controller"
    #define CONTROLLER_program_name_long_s "Controller Program"

    #define CONTROLLER_program_name_s_length      10
    #define CONTROLLER_program_name_long_s_length 18
  #endif // _controller_as_init_

  extern const f_string_static_t controller_program_name_s;
  extern const f_string_static_t controller_program_name_long_s;
#endif // _di_controller_program_name_

/**
 * The program defines.
 */
#ifndef _di_controller_defines_

  // The pid path is a system-specific path and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_) && defined(_override_controller_path_pid_length_)
    #define CONTROLLER_path_pid_s        _override_controller_path_pid_
    #define CONTROLLER_path_pid_s_length _override_controller_path_pid_length_
  #else
    #define CONTROLLER_path_pid_s        "controller/run"
    #define CONTROLLER_path_pid_s_length 14
  #endif // defined(_override_controller_path_pid_) && defined(_override_controller_path_pid_length_)

  // The init pid path is a system-specific path and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_init_) && defined(_override_controller_path_pid_init_length_)
    #define CONTROLLER_path_pid_init_s        _override_controller_path_pid_init_
    #define CONTROLLER_path_pid_init_s_length _override_controller_path_pid_init_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_pid_init_s        "/var/run/init"
    #define CONTROLLER_path_pid_init_s_length 13
  #else
    #define CONTROLLER_path_pid_init_s        "/var/run/controller"
    #define CONTROLLER_path_pid_init_s_length 19
  #endif // defined(_override_controller_path_pid_init_) && defined(_override_controller_path_pid_init_length_)

  // The pid prefix is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_prefix_) && defined(_override_controller_path_pid_prefix_length_)
    #define CONTROLLER_path_pid_prefix_s _override_controller_path_pid_prefix_

    #define CONTROLLER_path_pid_prefix_s_length _override_controller_path_pid_prefix_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_pid_prefix_s        "init-"
    #define CONTROLLER_path_pid_prefix_s_length 5
  #else
    #define CONTROLLER_path_pid_prefix_s        ""
    #define CONTROLLER_path_pid_prefix_s_length 0
  #endif // defined(_override_controller_name_pid_prefix_) && defined(_override_controller_name_pid_prefix_length_)

  // The socket suffix path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_pid_suffix_) && defined(_override_controller_path_pid_suffix_length_)
    #define CONTROLLER_path_pid_suffix_s        _override_controller_path_pid_suffix_
    #define CONTROLLER_path_pid_suffix_s_length _override_controller_path_pid_suffix_length_
  #else
    #define CONTROLLER_path_pid_suffix_s        ".pid"
    #define CONTROLLER_path_pid_suffix_s_length 4
  #endif // defined(_override_controller_name_pid_suffix_) && defined(_override_controller_name_pid_suffix_length_)

  // The settings path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_settings_) && defined(_override_controller_path_settings_length_)
    #define CONTROLLER_path_settings_s        _override_controller_path_settings_
    #define CONTROLLER_path_settings_s_length _override_controller_path_settings_length_
  #else
    #define CONTROLLER_path_settings_s        "controller"
    #define CONTROLLER_path_settings_s_length 10
  #endif // defined(_override_controller_path_settings_) && defined(_override_controller_path_settings_length_)

  // The init settings path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_settings_init_) && defined(_override_controller_path_settings_init_length_)
    #define CONTROLLER_path_settings_init_s        _override_controller_path_settings_init_
    #define CONTROLLER_path_settings_init_s_length _override_controller_path_settings_init_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_settings_init_s        "/etc/init"
    #define CONTROLLER_path_settings_init_s_length 9
  #else
    #define CONTROLLER_path_settings_init_s        "/etc/controller"
    #define CONTROLLER_path_settings_init_s_length 15
  #endif // defined(_override_controller_path_settings_init_) && defined(_override_controller_path_settings_init_length_)

  // The socket path is a system-specific path and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)
    #define CONTROLLER_path_socket_s        _override_controller_path_socket_
    #define CONTROLLER_path_socket_s_length _override_controller_path_socket_length_
  #else
    #define CONTROLLER_path_socket_s        "controller/run"
    #define CONTROLLER_path_socket_s_length 14
  #endif // defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)

  // The socket path is a system-specific path and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_init_) && defined(_override_controller_path_socket_init_length_)
    #define CONTROLLER_path_socket_init_s        _override_controller_path_socket_init_
    #define CONTROLLER_path_socket_init_s_length _override_controller_path_socket_init_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_socket_init_s        "/var/run/init"
    #define CONTROLLER_path_socket_init_s_length 13
  #else
    #define CONTROLLER_path_socket_init_s        "/var/run/controller"
    #define CONTROLLER_path_socket_init_s_length 19
  #endif // defined(_override_controller_path_socket_init_) && defined(_override_controller_path_socket_init_length_)

  // The socket prefix path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)
    #define CONTROLLER_path_socket_prefix_s        _override_controller_path_socket_prefix_
    #define CONTROLLER_path_socket_prefix_s_length _override_controller_path_socket_prefix_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_socket_prefix_s        "init-"
    #define CONTROLLER_path_socket_prefix_s_length 5
  #else
    #define CONTROLLER_path_socket_prefix_s        ""
    #define CONTROLLER_path_socket_prefix_s_length 0
  #endif // defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)

  // The socket suffix path is a system-specific path part and needs to be more easily controlled at compile time.
  #if defined(_override_controller_path_socket_suffix_) && defined(_override_controller_path_socket_suffix_length_)
    #define CONTROLLER_path_socket_suffix_s        _override_controller_path_socket_suffix_
    #define CONTROLLER_path_socket_suffix_s_length _override_controller_path_socket_suffix_length_
  #else
    #define CONTROLLER_path_socket_suffix_s        ".socket"
    #define CONTROLLER_path_socket_suffix_s_length 7
  #endif // defined(_override_controller_path_socket_suffix_) && defined(_override_controller_path_socket_suffix_length_)

  #if defined(_override_controller_default_program_script_) && defined(_override_controller_default_program_script_length_)
    #define CONTROLLER_default_program_script_s        _override_controller_default_program_script_
    #define CONTROLLER_default_program_script_s_length _override_controller_default_program_script_length_
  #else
    #define CONTROLLER_default_program_script_s        "bash"
    #define CONTROLLER_default_program_script_s_length 4
  #endif // defined(_override_controller_default_program_script_) && defined(_override_controller_default_program_script_length_)

  extern const f_string_static_t controller_default_program_script_s;
  extern const f_string_static_t controller_path_pid_s;
  extern const f_string_static_t controller_path_pid_init_s;
  extern const f_string_static_t controller_path_pid_prefix_s;
  extern const f_string_static_t controller_path_pid_suffix_s;
  extern const f_string_static_t controller_path_settings_s;
  extern const f_string_static_t controller_path_settings_init_s;
  extern const f_string_static_t controller_path_socket_s;
  extern const f_string_static_t controller_path_socket_init_s;
  extern const f_string_static_t controller_path_socket_prefix_s;
  extern const f_string_static_t controller_path_socket_suffix_s;
#endif // _di_controller_defines_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_main_common_h
