/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _controller_common_h
#define _controller_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_controller_program_version_s_
  #define CONTROLLER_program_version_major_s F_string_ascii_0_s
  #define CONTROLLER_program_version_minor_s F_string_ascii_7_s
  #define CONTROLLER_program_version_micro_s F_string_ascii_0_s

  #define CONTROLLER_program_version_major_s_length F_string_ascii_0_s_length
  #define CONTROLLER_program_version_minor_s_length F_string_ascii_7_s_length
  #define CONTROLLER_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(CONTROLLER_program_version_nano_prefix_s) && defined(CONTROLLER_program_version_nano_prefix_s_length))
    #define CONTROLLER_program_version_nano_prefix_s
    #define CONTROLLER_program_version_nano_prefix_s_length 0
  #endif // !(defined(CONTROLLER_program_version_nano_prefix_s) && defined(CONTROLLER_program_version_nano_prefix_s_length))

  #if !(defined(CONTROLLER_program_version_nano_s) && defined(CONTROLLER_program_version_nano_s_length))
    #define CONTROLLER_program_version_nano_s
    #define CONTROLLER_program_version_nano_s_length 0
  #endif // !(defined(CONTROLLER_program_version_nano_s) && defined(CONTROLLER_program_version_nano_s_length))

  #define CONTROLLER_program_version_s CONTROLLER_program_version_major_s F_string_ascii_period_s CONTROLLER_program_version_minor_s F_string_ascii_period_s CONTROLLER_program_version_micro_s CONTROLLER_program_version_nano_prefix_s CONTROLLER_program_version_nano_s

  #define CONTROLLER_program_version_s_length CONTROLLER_program_version_major_s_length + F_string_ascii_period_s_length + CONTROLLER_program_version_minor_s_length + F_string_ascii_period_s_length + CONTROLLER_program_version_micro_s_length + CONTROLLER_program_version_nano_prefix_s_length + CONTROLLER_program_version_nano_s_length

  extern const f_string_static_t controller_program_version_s;
#endif // _di_controller_program_version_s_

/**
 * The main program parameters.
 */
#ifndef _di_controller_parameter_d_
  #define CONTROLLER_short_cgroup_s          "c"
  #define CONTROLLER_short_daemon_s          "d"
  #define CONTROLLER_short_init_s            "I"
  #define CONTROLLER_short_interruptible_s   "i"
  #define CONTROLLER_short_pid_s             "p"
  #define CONTROLLER_short_settings_s        "s"
  #define CONTROLLER_short_simulate_s        "S"
  #define CONTROLLER_short_socket_s          "k"
  #define CONTROLLER_short_uninterruptible_s "U"
  #define CONTROLLER_short_validate_s        "v"

  #define CONTROLLER_long_cgroup_s          "cgroup"
  #define CONTROLLER_long_daemon_s          "daemon"
  #define CONTROLLER_long_init_s            "init"
  #define CONTROLLER_long_interruptible_s   "interruptible"
  #define CONTROLLER_long_pid_s             "pid"
  #define CONTROLLER_long_settings_s        "settings"
  #define CONTROLLER_long_simulate_s        "simulate"
  #define CONTROLLER_long_socket_s          "socket"
  #define CONTROLLER_long_uninterruptible_s "uninterruptible"
  #define CONTROLLER_long_validate_s        "validate"

  #define CONTROLLER_short_cgroup_s_length          1
  #define CONTROLLER_short_daemon_s_length          1
  #define CONTROLLER_short_init_s_length            1
  #define CONTROLLER_short_interruptible_s_length   1
  #define CONTROLLER_short_pid_s_length             1
  #define CONTROLLER_short_settings_s_length        1
  #define CONTROLLER_short_simulate_s_length        1
  #define CONTROLLER_short_socket_s_length          1
  #define CONTROLLER_short_uninterruptible_s_length 1
  #define CONTROLLER_short_validate_s_length        1

  #define CONTROLLER_long_cgroup_s_length          6
  #define CONTROLLER_long_daemon_s_length          6
  #define CONTROLLER_long_init_s_length            4
  #define CONTROLLER_long_interruptible_s_length   13
  #define CONTROLLER_long_pid_s_length             3
  #define CONTROLLER_long_settings_s_length        8
  #define CONTROLLER_long_simulate_s_length        8
  #define CONTROLLER_long_socket_s_length          6
  #define CONTROLLER_long_uninterruptible_s_length 15
  #define CONTROLLER_long_validate_s_length        8

  extern const f_string_static_t controller_short_cgroup_s;
  extern const f_string_static_t controller_short_daemon_s;
  extern const f_string_static_t controller_short_init_s;
  extern const f_string_static_t controller_short_interruptible_s;
  extern const f_string_static_t controller_short_pid_s;
  extern const f_string_static_t controller_short_settings_s;
  extern const f_string_static_t controller_short_simulate_s;
  extern const f_string_static_t controller_short_socket_s;
  extern const f_string_static_t controller_short_uninterruptible_s;
  extern const f_string_static_t controller_short_validate_s;

  extern const f_string_static_t controller_long_cgroup_s;
  extern const f_string_static_t controller_long_daemon_s;
  extern const f_string_static_t controller_long_init_s;
  extern const f_string_static_t controller_long_interruptible_s;
  extern const f_string_static_t controller_long_pid_s;
  extern const f_string_static_t controller_long_settings_s;
  extern const f_string_static_t controller_long_simulate_s;
  extern const f_string_static_t controller_long_socket_s;
  extern const f_string_static_t controller_long_uninterruptible_s;
  extern const f_string_static_t controller_long_validate_s;

  enum {
    controller_parameter_help_e,
    controller_parameter_copyright_e,
    controller_parameter_light_e,
    controller_parameter_dark_e,
    controller_parameter_no_color_e,
    controller_parameter_verbosity_quiet_e,
    controller_parameter_verbosity_error_e,
    controller_parameter_verbosity_normal_e,
    controller_parameter_verbosity_verbose_e,
    controller_parameter_verbosity_debug_e,
    controller_parameter_version_e,
    controller_parameter_line_first_no_e,
    controller_parameter_line_last_no_e,

    controller_parameter_cgroup_e,
    controller_parameter_daemon_e,
    controller_parameter_init_e,
    controller_parameter_interruptible_e,
    controller_parameter_pid_e,
    controller_parameter_settings_e,
    controller_parameter_simulate_e,
    controller_parameter_socket_e,
    controller_parameter_uninterruptible_e,
    controller_parameter_validate_e,
  }; // enum

  #define controller_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_copyright_s,     f_console_standard_long_copyright_s,     0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e), \
      \
      macro_f_console_parameter_t_initialize_3(controller_short_cgroup_s,          controller_long_cgroup_s,          1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_daemon_s,          controller_long_daemon_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_init_s,            controller_long_init_s,            0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_interruptible_s,   controller_long_interruptible_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_pid_s,             controller_long_pid_s,             1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_settings_s,        controller_long_settings_s,        1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_simulate_s,        controller_long_simulate_s,        0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_socket_s,          controller_long_socket_s,          1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_uninterruptible_s, controller_long_uninterruptible_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(controller_short_validate_s,        controller_long_validate_s,        0, f_console_flag_normal_e), \
    }

  #define controller_total_parameters_d 23
#endif // _di_controller_parameter_d_

/**
 * The main program data.
 *
 * child:                      Reserved for a child process, often representing the child return status or the child process ID.
 * context:                    The color context.
 * default_engine:             The default scripting engine.
 * default_path_pid:           The default PID file path.
 * default_path_pid_init:      The default PID file path, when run as init.
 * default_path_pid_prefix:    The default PID file path prefix.
 * default_path_pid_suffix:    The default PID file path suffix.
 * default_path_setting:       The default setting path.
 * default_path_setting_init:  The default setting path, when run as init.
 * default_path_socket:        The default socket file path.
 * default_path_socket_init:   The default socket file path, when run as init.
 * default_path_socket_prefix: The default socket file path prefix.
 * default_path_socket_suffix: The default socket file path suffix.
 * error:                      The output file for error printing.
 * as_init:                    Designate whether or not this is running as an init program.
 * output:                     The output file for general printing.
 * parameters:                 The state of pre-defined parameters passed to the program.
 * pid:                        The PID of the program.
 * program_name:               The name of the program.
 * program_name_long:          The long name of the program.
 * signal:                     The process signal management structure.
 * umask:                      The umask settings, needed for avoiding calls to umask() to read the current umask.
 * warning:                    The output file for warning printing.
 */
#ifndef _di_controller_main_t_
  typedef struct {
    f_console_parameters_t parameters;

    bool as_init;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    pid_t pid;
    mode_t umask;
    int child;

    const f_string_static_t *default_engine;
    const f_string_static_t *default_path_pid;
    const f_string_static_t *default_path_pid_init;
    const f_string_static_t *default_path_pid_prefix;
    const f_string_static_t *default_path_pid_suffix;
    const f_string_static_t *default_path_setting;
    const f_string_static_t *default_path_setting_init;
    const f_string_static_t *default_path_socket;
    const f_string_static_t *default_path_socket_init;
    const f_string_static_t *default_path_socket_prefix;
    const f_string_static_t *default_path_socket_suffix;
    const f_string_static_t *program_name;
    const f_string_static_t *program_name_long;

    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;

    f_color_context_t context;
  } controller_main_t;

  #define controller_main_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_controller_main_t_

/**
 * Codes representing control payload types.
 *
 * controller_control_payload_type_*:
 *   - controller: The item type represents a command operation.
 *   - error:      The item type represents a script operation.
 *   - init:       The item type represents an init operation (Only fo init mode).
 */
#ifndef _di_controller_control_payload_type_e_
  enum {
    controller_control_payload_type_controller_e = 1,
    controller_control_payload_type_error_e,
    controller_control_payload_type_init_e,
  }; // enum
#endif // _di_controller_control_payload_type_e_

/**
 * Codes representing supported actions.
 *
 * controller_entry_action_type_*:
 *   - consider: Perform the consider controller operation.
 *   - execute:  Perform the execute controller operation.
 *   - freeze:   Perform the freeze controller operation..
 *   - item:     Perform the item controller operation.
 *   - kexec:    Perform the kexec controller operation (only for init mode).
 *   - kill:     Perform the kill controller operation.
 *   - pause:    Perform the pause controller operation.
 *   - ready:    Perform the ready controller operation.
 *   - reboot:   Perform the reboot controller operation (only for init mode).
 *   - reload:   Perform the reload controller operation.
 *   - restart:  Perform the restart controller operation.
 *   - resume:   Perform the resume controller operation.
 *   - shutdown: Perform the shutdown controller operation (only for init mode).
 *   - start:    Perform the start controller operation.
 *   - stop:     Perform the stop controller operation.
 *   - timeout:  Perform the timeout controller operation.
 *   - thaw:     Perform the thaw controller operation.
 */
#ifndef _di_controller_entry_action_type_e_
  enum {
    controller_entry_action_type_consider_e = 1,
    controller_entry_action_type_execute_e,
    controller_entry_action_type_failsafe_e,
    controller_entry_action_type_freeze_e,
    controller_entry_action_type_item_e,
    controller_entry_action_type_kexec_e,
    controller_entry_action_type_kill_e,
    controller_entry_action_type_pause_e,
    controller_entry_action_type_ready_e,
    controller_entry_action_type_reboot_e,
    controller_entry_action_type_reload_e,
    controller_entry_action_type_restart_e,
    controller_entry_action_type_resume_e,
    controller_entry_action_type_shutdown_e,
    controller_entry_action_type_start_e,
    controller_entry_action_type_stop_e,
    controller_entry_action_type_timeout_e,
    controller_entry_action_type_thaw_e,
  }; // enum
#endif // _di_controller_entry_action_type_e_

/**
 * Codes representing rule actions.
 *
 * controller_rule_action_type_*:
 *   - freeze:   The Freeze execution instructions.
 *   - group:    The Group setting.
 *   - kill:     The Kill execution instructions.
 *   - pause:    The Pause execution instructions.
 *   - pid_file: The PID file setting.
 *   - rerun:    The Re-run execution after success or failure.
 *   - reload:   The Reload execution instructions.
 *   - restart:  The Restart execution instructions.
 *   - resume:   The Resume execution instructions.
 *   - start:    The Start execution instructions.
 *   - stop:     The Stop execution instructions.
 *   - thaw:     The Thaw execution instructions.
 *   - user:     The User setting.
 *   - with:     The With flags.
 */
#ifndef _di_controller_rule_action_type_e_
  enum {
    controller_rule_action_type_freeze_e = 1,
    controller_rule_action_type_group_e,
    controller_rule_action_type_kill_e,
    controller_rule_action_type_pause_e,
    controller_rule_action_type_pid_file_e,
    controller_rule_action_type_reload_e,
    controller_rule_action_type_rerun_e,
    controller_rule_action_type_restart_e,
    controller_rule_action_type_resume_e,
    controller_rule_action_type_start_e,
    controller_rule_action_type_stop_e,
    controller_rule_action_type_thaw_e,
    controller_rule_action_type_user_e,
    controller_rule_action_type_with_e,

    // Designate the largest value in the enum, the '__' is intended.
    controller_rule_action_type__enum_size_e,
  }; // enum
#endif // _di_controller_rule_action_type_e_

/**
 * Codes representing rule action executes.
 *
 * Execute type starts at 0 because it is intended to be used as an index within a static array.
 *
 * controller_rule_action_execute_type_*:
 *   - freeze:   The Freeze execution instructions.
 *   - kill:     The Kill execution instructions.
 *   - pause:    The Pause execution instructions.
 *   - reload:   The Reload execution instructions.
 *   - restart:  The Restart execution instructions.
 *   - resume:   The Resume execution instructions.
 *   - start:    The Start execution instructions.
 *   - stop:     The Stop execution instructions.
 *   - thaw:     The Thaw execution instructions.
 */
#ifndef _di_controller_rule_action_execute_type_e_
  enum {
    controller_rule_action_execute_type_freeze_e = 0,
    controller_rule_action_execute_type_kill_e,
    controller_rule_action_execute_type_pause_e,
    controller_rule_action_execute_type_reload_e,
    controller_rule_action_execute_type_restart_e,
    controller_rule_action_execute_type_resume_e,
    controller_rule_action_execute_type_start_e,
    controller_rule_action_execute_type_stop_e,
    controller_rule_action_execute_type_thaw_e,

    // Designate the largest value in the enum, the '__' is intended.
    controller_rule_action_execute_type__enum_size_e,
  }; // enum
#endif // _di_controller_rule_action_execute_type_e_

/**
 * Codes representing rule items.
 *
 * controller_rule_item_type_*:
 *   - command:  The item type represents a command operation.
 *   - script:   The item type represents a script operation.
 *   - service:  The item type represents a service operation.
 *   - settings: The item type represents a setting operation.
 *   - utility:  The item type represents a utility operation.
 */
#ifndef _di_controller_rule_item_type_e_
  enum {
    controller_rule_item_type_command_e = 1,
    controller_rule_item_type_script_e,
    controller_rule_item_type_service_e,
    controller_rule_item_type_settings_e,
    controller_rule_item_type_utility_e,
  }; // enum
#endif // _di_controller_rule_item_type_e_

/**
 * A set of codes for resource limitations.
 *
 * This essentally converts the POSIX standard names into a more verbose format.
 */
#ifndef _di_controller_resource_limit_type_d_
  enum {
    controller_resource_limit_type_as_e = RLIMIT_AS,
    controller_resource_limit_type_core_e = RLIMIT_CORE,
    controller_resource_limit_type_cpu_e = RLIMIT_CPU,
    controller_resource_limit_type_data_e = RLIMIT_DATA,
    controller_resource_limit_type_fsize_e = RLIMIT_FSIZE,
    controller_resource_limit_type_locks_e = RLIMIT_LOCKS,
    controller_resource_limit_type_memlock_e = RLIMIT_MEMLOCK,
    controller_resource_limit_type_msgqueue_e = RLIMIT_MSGQUEUE,
    controller_resource_limit_type_nice_e = RLIMIT_NICE,
    controller_resource_limit_type_nofile_e = RLIMIT_NOFILE,
    controller_resource_limit_type_nproc_e = RLIMIT_NPROC,
    controller_resource_limit_type_rss_e = RLIMIT_RSS,
    controller_resource_limit_type_rtprio_e = RLIMIT_RTPRIO,
    controller_resource_limit_type_rttime_e = RLIMIT_RTTIME,
    controller_resource_limit_type_sigpending_e = RLIMIT_SIGPENDING,
    controller_resource_limit_type_stack_e = RLIMIT_STACK,
  }; // enum
#endif // _di_controller_resource_limit_type_d_

/**
 * Flags passed to the main function or program.
 *
 * controller_main_flag_*_e:
 *   - none:          No flags set.
 *   - copyright:     Print copyright.
 *   - file_from:     Using a specified source file.
 *   - file_to:       Using a specified destination file.
 *   - help:          Print help.
 *   - header:        Enable printing of headers.
 *   - separate:      Enable printing of separators.
 *   - strip_invalid: Using strip invalid character mode.
 *   - verify:        Using verify mode.
 *   - version:       Print version.
 */
#ifndef _di_controller_main_flag_e_
  enum {
    controller_main_flag_none_e          = 0x0,
    controller_main_flag_copyright_e     = 0x1,
    controller_main_flag_file_from_e     = 0x2,
    controller_main_flag_file_to_e       = 0x4,
    controller_main_flag_header_e        = 0x8,
    controller_main_flag_help_e          = 0x10,
    controller_main_flag_separate_e      = 0x20,
    controller_main_flag_strip_invalid_e = 0x40,
    controller_main_flag_verify_e        = 0x80,
    controller_main_flag_version_e       = 0x100,
  }; // enum
#endif // _di_controller_main_flag_e_

/**
 * The controller main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status: The main status code, generally used by the load settings and main functions.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 */
#ifndef _di_controller_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status;

    f_string_static_t line_first;
    f_string_static_t line_last;
  } controller_setting_t;

  #define controller_setting_t_initialize \
    { \
      controller_main_flag_none_e, \
      F_none, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
    }
#endif // _di_controller_setting_t_

/**
 * Identify the payload code the given name represents.
 *
 * @param payload
 *   The string representing a payload.
 *
 * @return
 *   The payload type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_controller_control_payload_type_identify_
  extern uint8_t controller_control_payload_type_identify(const f_string_static_t payload);
#endif // _di_controller_control_payload_type_identify_

/**
 * Get a string representing the payload type.
 *
 * @param type
 *   The payload type id.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_control_payload_type_name_
  extern f_string_static_t controller_control_payload_type_name(const uint8_t type);
#endif // _di_controller_control_payload_type_name_

/**
 * Identify the entry action code the given name represents.
 *
 * @param action
 *   The string representing an entry action.
 *
 * @return
 *   The entry action type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_controller_entry_action_type_identify_
  extern uint8_t controller_entry_action_type_identify(const f_string_static_t action);
#endif // _di_controller_entry_action_type_identify_

/**
 * Get a string representing the entry action type.
 *
 * @param type
 *   The entry action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_entry_action_type_name_
  extern f_string_static_t controller_entry_action_type_name(const uint8_t type);
#endif // _di_controller_entry_action_type_name_

/**
 * Deallocate main.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_controller_main_delete_
  extern f_status_t controller_main_delete(controller_main_t * const main);
#endif // _di_controller_main_delete_

/**
 * Identify the rule action code the given name represents.
 *
 * @param action
 *   The string representing an rule action.
 *
 * @return
 *   The rule action type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_controller_rule_action_type_identify_
  extern uint8_t controller_rule_action_type_identify(const f_string_static_t action);
#endif // _di_controller_rule_action_type_identify_

/**
 * Get a string representing the rule action type.
 *
 * @param type
 *   The rule action type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_action_type_name_
  extern f_string_static_t controller_rule_action_type_name(const uint8_t type);
#endif // _di_controller_rule_action_type_name_

/**
 * Identify the rule action execute code the given name represents.
 *
 * @param action
 *   The string representing an rule action execute.
 *
 * @return
 *   The rule action execute type code on success.
 *   controller_rule_action_execute_type__enum_size_e if name is unknown.
 */
#ifndef _di_controller_rule_action_execute_type_identify_
  extern uint8_t controller_rule_action_execute_type_identify(const f_string_static_t action);
#endif // _di_controller_rule_action_execute_type_identify_

/**
 * Get a string representing the rule action execute type.
 *
 * @param type
 *   The rule action type execute code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_action_execute_type_name_
  extern f_string_static_t controller_rule_action_execute_type_name(const uint8_t type);
#endif // _di_controller_rule_action_execute_type_name_

/**
 * Identify the rule item code the given name represents.
 *
 * @param item
 *   The string representing an rule action.
 *
 * @return
 *   The rule item type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_controller_rule_item_type_identify_
  extern uint8_t controller_rule_item_type_identify(const f_string_static_t item);
#endif // _di_controller_rule_item_type_identify_

/**
 * Get a string representing the rule item type.
 *
 * @param type
 *   The rule item type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_item_type_name_
  extern f_string_static_t controller_rule_item_type_name(const uint8_t type);
#endif // _di_controller_rule_item_type_name_

/**
 * Identify the rule item code the given name represents.
 *
 * @param item
 *   The string representing an rule action.
 *
 * @return
 *   The rule item type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_controller_rule_setting_limit_type_identify_
  extern uint8_t controller_rule_setting_limit_type_identify(const f_string_static_t item);
#endif // _di_controller_rule_setting_limit_type_identify_

/**
 * Get a string representing the rule setting limit type.
 *
 * @param type
 *   The rule setting limit type code.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_controller_rule_setting_limit_type_name_
  extern f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type);
#endif // di_controller_rule_setting_limit_type_name_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_controller_setting_delete_
  extern f_status_t controller_setting_delete(controller_setting_t * const setting);
#endif // _di_controller_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_controller_setting_load_
  extern void controller_setting_load(const f_console_arguments_t arguments, f_state_t state, fll_program_data_t * const main, controller_setting_t * const setting);
#endif // _di_controller_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: utf8_setting_delete().
 *
 * @see utf8_setting_delete()
 */
#ifndef _di_controller_setting_unload_
  extern f_status_t controller_setting_unload(fll_program_data_t * const main, controller_setting_t * const setting);
#endif // _di_controller_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_common_h
