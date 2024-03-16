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
 * The program defines.
 *
 * controller_*_d:
 *   - allocation_console: An allocation step used for small buffers specifically for console parameter.
 *   - allocation_large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - allocation_small:   An allocation step used for buffers that are anticipated to have small buffers.
 *   - signal_check:       Number of iterations before performing signal check in non-threaded signal handling.
 */
#ifndef _di_controller_d_
  #define controller_allocation_console_d 4
  #define controller_allocation_large_d   256
  #define controller_allocation_small_d   16
  #define controller_signal_check_d       20000
#endif // _di_controller_d_

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
    controller_parameter_cgroup_e = f_console_standard_parameter_last_e,
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
      macro_fll_program_console_parameter_standard_initialize, \
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

  #define controller_parameter_total_d (f_console_parameter_state_type_total_d + 10)
#endif // _di_controller_parameter_d_

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
 *   - none:                   No flags set.
 *   - copyright:              Print copyright.
 *   - file_from:              Using a specified source file.
 *   - file_to:                Using a specified destination file.
 *   - header:                 Enable printing of headers.
 *   - help:                   Print help.
 *   - init:                   Operate as an "init" program.
 *   - print_first:            When set, print new line to message output on program begin after loading settings.
 *   - print_last:             When set, print new line to message output on program end.
 *   - separate:               Enable printing of separators.
 *   - strip_invalid:          Using strip invalid character mode.
 *   - verify:                 Using verify mode.
 *   - version:                Print version.
 *   - version_copyright_help: A helper flag representing version, copyright, and help flag bits being set.
 */
#ifndef _di_controller_main_flag_e_
  enum {
    controller_main_flag_none_e                   = 0x0,
    controller_main_flag_copyright_e              = 0x1,
    controller_main_flag_file_from_e              = 0x2,
    controller_main_flag_file_to_e                = 0x4,
    controller_main_flag_header_e                 = 0x8,
    controller_main_flag_help_e                   = 0x10,
    controller_main_flag_init_e                   = 0x20,
    controller_main_flag_print_first_e            = 0x40,
    controller_main_flag_print_last_e             = 0x80,
    controller_main_flag_separate_e               = 0x100,
    controller_main_flag_strip_invalid_e          = 0x200,
    controller_main_flag_verify_e                 = 0x400,
    controller_main_flag_version_e                = 0x800,
    controller_main_flag_version_copyright_help_e = 0x811,
  }; // enum
#endif // _di_controller_main_flag_e_

/**
 * Flags for fine-tuned print control.
 *
 * controller_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_controller_print_flag_e_
  enum {
    controller_print_flag_none_e    = 0x0,
    controller_print_flag_debug_e   = 0x1,
    controller_print_flag_error_e   = 0x2,
    controller_print_flag_file_e    = 0x4,
    controller_print_flag_in_e      = 0x8,
    controller_print_flag_out_e     = 0x10,
    controller_print_flag_message_e = 0x20,
    controller_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_controller_print_flag_e_

/**
 * The controller main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag:    Flags passed to the main function.
 * as_init: Designate whether or not this is running as an init program.
 *
 * state: The state information.
 *
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
 *
 * program_name:      The short program name.
 * program_name_long: The long program name.
 *
 * path_pid:     The name of the program.
 * path_setting: The long name of the program.
 */
#ifndef _di_controller_setting_t_
  typedef struct {
    uint16_t flag;

    f_state_t state;

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

    f_string_static_t program_name;
    f_string_static_t program_name_long;

    f_string_dynamic_t path_pid;
    f_string_dynamic_t path_setting;
  } controller_setting_t;

  #define controller_setting_t_initialize \
    { \
      controller_main_flag_none_e, \
      f_state_t_initialize, \
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
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_controller_setting_t_

/**
 * Provide default control settings.
 *
 * controller_control_default:
 *   - socket_backlog:     The amount of waiting client connections to support while handling a socket connection.
 *   - socket_buffer:      The preferred max size of the buffer such that if the buffer exceeds this then it is reallocated to this size at the end of processing.
 *   - socket_buffer_max:  The max size allowed in the buffer (this value must not be set smaller than the packet headers).
 *   - socket_cache:       The preferred max size of the control cache such that if the cache exceeds this then it is reallocated to this size at the end of processing.
 *   - socket_header:      The minimum size in bytes of the packet header to read to be able to process the size information.
 *   - socket_linger:      The number of seconds to linger the connection before closing.
 *   - socket_timeout:     The number of microseconds to wait.
 *   - socket_payload_max: The max size allowed for the "payload" part of a packet and must be smaller than socket_buffer_max (this is smaller than socket_buffer_max to allow for enough room to afford a header).
 */
#ifndef _di_controller_control_defaults_
  #define controller_control_default_socket_backlog_d     64
  #define controller_control_default_socket_buffer_d      2048
  #define controller_control_default_socket_buffer_max_d  4294967296
  #define controller_control_default_socket_cache_d       128
  #define controller_control_default_socket_header_d      5
  #define controller_control_default_socket_linger_d      2
  #define controller_control_default_socket_timeout_d     10000 // 0.01 seconds.
  #define controller_control_default_socket_payload_max_d 4294965248
#endif // _di_controller_defaults_

/**
 * The control data.
 *
 * controller_control_flag_*:
 *   - readonly:  Control is set to read-only mode.
 *   - has_user:  A user is manually specified.
 *   - has_group: A group is manually specified.
 *   - has_mode:  A file mode is manually specified.
 *
 * flag:    Flags from controller_control_flag_*.
 * user:    The user ID, if specified.
 * group:   The group ID, if specified.
 * mode:    The file mode, if specified.
 * server:  The server socket connection.
 * client:  The client socket connection.
 * cache_1: A generic buffer used for caching control related data.
 * cache_2: A generic buffer used for caching control related data.
 * cache_3: A generic buffer used for caching control related data.
 * input:   A buffer used for receiving data from the client.
 * output:  A buffer used for transmitting data to the client.
 * address: The socket address structure.
 */
#ifndef _di_controller_control_t_
  enum {
    controller_control_flag_readonly_e  = 0x1,
    controller_control_flag_has_user_e  = 0x2,
    controller_control_flag_has_group_e = 0x4,
    controller_control_flag_has_mode_e  = 0x8,
  };

  typedef struct {
    uint8_t flag;

    uid_t user;
    gid_t group;
    mode_t mode;

    f_socket_t server;
    f_socket_t client;

    f_string_dynamic_t cache_1;
    f_string_dynamic_t cache_2;
    f_string_dynamic_t cache_3;

    f_string_dynamic_t input;
    f_string_dynamic_t output;

    struct sockaddr_un address;
  } controller_control_t;

  #define controller_control_t_initialize { \
    0, \
    -1, \
    -1, \
    0, \
    f_socket_t_initialize, \
    f_socket_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    { }, \
  }
#endif // _di_controller_control_t_

/**
 * A codes repesent different flags associated with a packet.
 *
 * controller_control_packet_flag_*:
 *   - binary:     Designate that the packet is in binary mode (when not set then packet is in string mode).
 *   - endian_big: Designate that the packet is in big endian order (when not set then packet is in little endian order).
 */
#ifndef _di_controller_control_packet_flag_
  #define controller_control_packet_flag_binary_d     0x10000000
  #define controller_control_packet_flag_endian_big_d 0x01000000
#endif // _di_controller_control_packet_flag_

/**
 * An Entry Item Action.
 *
 * controller_entry_action_flag_*:
 *   - undefined: The given type and code are designated as undefined.
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
 * controller_entry_timeout_code_*:
 *   - exit:  The timeout Action represents an exit timeout.
 *   - kill:  The timeout Action represents a kill timeout.
 *   - start: The timeout Action represents a start timeout.
 *   - stop:  The timeout Action represents a stop timeout.
 *
 * type:       The type of Action.
 * code:       A single code or sub-type associated with the Action.
 * flag:       A set of flags to describe special behavior for the given type and code (flags may be different per type and code).
 * line:       The line number where the Entry Item begins.
 * number:     The unsigned number that some types use instead of the "parameters".
 * status:     The overall status.
 * parameters: The values associated with the Action.
 */
#ifndef _di_controller_entry_action_t_
  #define controller_entry_rule_code_asynchronous_d 0x1
  #define controller_entry_rule_code_require_d      0x2
  #define controller_entry_rule_code_wait_d         0x4

  #define controller_entry_timeout_code_exit_d  0x1
  #define controller_entry_timeout_code_kill_d  0x2
  #define controller_entry_timeout_code_start_d 0x4
  #define controller_entry_timeout_code_stop_d  0x8

  enum {
    controller_entry_action_flag_none_e      = 0x0,
    controller_entry_action_flag_undefined_e = 0x1,
  };

  typedef struct {
    uint8_t type;
    uint8_t code;
    uint8_t flag;

    f_number_unsigned_t line;
    f_number_unsigned_t number;

    f_status_t status;

    f_string_dynamics_t parameters;
  } controller_entry_action_t;

  #define controller_entry_action_t_initialize { \
    0, \
    0, \
    0, \
    controller_entry_action_flag_none_e, \
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

    f_number_unsigned_t size;
    f_number_unsigned_t used;
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
    f_number_unsigned_t line;
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

    f_number_unsigned_t size;
    f_number_unsigned_t used;
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
 * controller_entry_flag_*:
 *   - none_e:             No flags are set.
 *   - timeout_exit_no_e:  The exit timeout is disabled.
 *   - timeout_kill_no_e:  The kill timeout is disabled for Rules by default.
 *   - timeout_start_no_e: The start timeout is disabled for Rules by default.
 *   - timeout_stop_no_e:  The stop timeout is disabled for Rules by default.
 *
 * controller_entry_session_*:
 *   - none: No special session configuration specified, use built in defaults.
 *   - new:  Designate the default to use a new session, ignoring built in defaults (passing FL_execute_parameter_option_session_d to the execute functions).
 *   - same: Designate the default to use a same session, ignoring built in defaults.
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
 * define:        Any defines (environment variables) made available to all Rules in this entry for IKI substitution or just as environment variables.
 * flag:          A set of flags, primarily used to designate that timeouts are disabled.
 * items:         The array of entry items.
 * parameter:     Any parameters made available to all Rules in this entry for IKI substitution.
 * pid:           The PID file generation setting.
 * session:       The default session settings (when NULL, no default is specified).
 * show:          The show setting for controlling what to show when executing entry items and rules.
 * status:        The overall status.
 * timeout_exit:  The timeout to wait when exiting the Controller program after sending the terminate signal to send the kill signal.
 * timeout_kill:  The timeout to wait relating to using a kill signal.
 * timeout_start: The timeout to wait relating to starting a process.
 * timeout_stop:  The timeout to wait relating to stopping a process.
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

  enum {
    controller_entry_flag_none_e             = 0x0,
    controller_entry_flag_timeout_exit_no_e  = 0x1,
    controller_entry_flag_timeout_kill_no_e  = 0x2,
    controller_entry_flag_timeout_start_no_e = 0x4,
    controller_entry_flag_timeout_stop_no_e  = 0x8,
  };

  typedef struct {
    f_status_t status;

    uint8_t pid;
    uint8_t session;
    uint8_t show;
    uint8_t flag;

    f_number_unsigned_t timeout_exit;
    f_number_unsigned_t timeout_kill;
    f_number_unsigned_t timeout_start;
    f_number_unsigned_t timeout_stop;

    f_string_maps_t define;
    f_string_maps_t parameter;

    controller_entry_items_t items;
  } controller_entry_t;

  #define controller_entry_t_initialize { \
    F_known_not, \
    controller_entry_pid_require_e, \
    controller_entry_session_none_e, \
    controller_entry_show_normal_e, \
    0, \
    controller_thread_exit_timeout_d, \
    0, \
    0, \
    0, \
    f_string_maps_t_initialize, \
    f_string_maps_t_initialize, \
    controller_entry_items_t_initialize, \
  }
#endif // _di_controller_entry_t_

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

  #define macro_controller_rule_rerun_item_initialize(item) { \
    item.reset = F_false; \
    item.count = 0; \
    item.delay = 5000; \
    item.max = 0; \
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
    f_number_unsigned_t line;
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

    f_number_unsigned_t size;
    f_number_unsigned_t used;
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
    f_number_unsigned_t line;

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

    f_number_unsigned_t size;
    f_number_unsigned_t used;
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

    f_number_unsigned_t size;
    f_number_unsigned_t used;
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
 *   - affinity:         Setting type representing a affinity.
 *   - capability:       Setting type representing a capability.
 *   - cgroup:           Setting type representing a control group.
 *   - define:           Setting type representing a define.
 *   - engine:           Setting type representing a engine.
 *   - engine_arguments: Setting type representing a engine.
 *   - environment:      Setting type representing a environment.
 *   - group:            Setting type representing a group.
 *   - limit:            Setting type representing a limit.
 *   - name:             Setting type representing a name.
 *   - nice:             Setting type representing a nice.
 *   - on:               Setting type representing a on.
 *   - parameter:        Setting type representing a parameter.
 *   - path:             Setting type representing a path.
 *   - scheduler:        Setting type representing a scheduler.
 *   - user:             Setting type representing a user.
 *
 * controller_rule_has_*:
 *   - cgroup:    Has type representing a control group.
 *   - group:     Has type representing a group.
 *   - nice:      Has type representing a nice.
 *   - scheduler: Has type representing a scheduler.
 *   - user:      Has type representing a user.
 *
 * affinity:         The cpu affinity to be used when executing the Rule.
 * alias:            The distinct ID (machine name) of the Rule, such as "service/ssh".
 * capability:       The capability setting if the Rule "has" a capability.
 * cgroup:           The control group setting if the Rule "has" a control group.
 * define:           Any defines (environment variables) made available to the Rule for IKI substitution or just as environment variables.
 * engine:           The program or path to the program of the scripting engine to use when processing scripts in this Rule.
 * engine_arguments: Any arguments to pass to the engine program.
 * environment:      All environment variables allowed to be exposed to the Rule when processing.
 * group:            The group ID if the Rule "has" a group.
 * groups:           A set of group IDs to run the process with (first specified group is the primary group).
 * has:              Bitwise set of "has" codes representing what the Rule has.
 * items:            All items associated with the Rule.
 * limits:           The cpu/resource limits to use when executing the Rule.
 * name:             A human name for the Rule (does not have to be distinct), such as "Bash Script".
 * nice:             The niceness value if the Rule "has" nice.
 * on:               A set of parameters for defining dependencies and how they are needed, wanted, or wished for.
 * parameter:        Any parameters made available to the Rule for IKI substitution.
 * path:             The path to the Rule file.
 * scheduler:        The scheduler setting if the Rule "has" a scheduler.
 * status:           A set of action-specific success/failure status of the Rule. Each index represents a controller_rule_action_type_* enum value. Index 0 represents a global status.
 * timeout_exit:     The timeout to wait when exiting the Controller program after sending the terminate signal to send the kill signal.
 * timeout_kill:     The timeout to wait relating to using a kill signal.
 * timeout_start:    The timeout to wait relating to starting a process.
 * timeout_stop:     The timeout to wait relating to stopping a process.
 * timestamp:        The timestamp when the Rule was loaded.
 * user:             The User ID if the Rule "has" a user.
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

    f_string_dynamics_t engine_arguments;
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

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } controller_rules_t;

  #define controller_rules_t_initialize { \
    0, \
    0, \
    0, \
  }
#endif // _di_controller_rules_t_

/**
 * The process specific settings.
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
#ifndef _di_controller_process_t_
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
  } controller_process_t;

  #define controller_process_t_initialize { \
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
#endif // _di_controller_process_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 *
 * process: The active process information.
 */
#ifndef _di_controller_main_t_
  typedef struct {
    fll_program_data_t program;
    controller_setting_t setting;

    controller_process_t *process;
  } controller_main_t;

  #define controller_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      controller_setting_t_initialize, \
      0, \
    }
#endif // _di_controller_main_t_

/**
 * Deallocate main program data.
 *
 * @param main
 *   The main program data.
 *
 *   This does not alter main.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_controller_main_delete_
  extern f_status_t controller_main_delete(controller_main_t * const main);
#endif // _di_controller_main_delete_

/**
 * Delete the controller control data.
 *
 * @param control
 *   The controller control data.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_controller_control_delete_
  extern f_status_t controller_control_delete(controller_control_t * const control);
#endif // _di_controller_control_delete_

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
 * Delete the controller process data.
 *
 * @param process
 *   The controller process data.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_controller_process_delete_
  extern f_status_t controller_process_delete(controller_process_t * const process);
#endif // _di_controller_process_delete_

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
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_okay on success.
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
 * @param main
 *   The main program data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_controller_setting_load_
  extern void controller_setting_load(const f_console_arguments_t arguments, controller_main_t * const main);
#endif // _di_controller_setting_load_

/**
 * Fully deallocate all memory for the given entry action without caring about return status.
 *
 * @param action
 *   The action to deallocate.
 *
 * @see f_memory_arrays_resize()
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_controller_entry_action_delete_
  extern f_status_t controller_entry_action_delete(controller_entry_action_t * const action);
#endif // _di_controller_entry_action_delete_

/**
 * Fully deallocate all memory for the given entry actions without caring about return status.
 *
 * @param actions
 *   The entry_actions to deallocate.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_entry_action_delete()
 * @see f_memory_delete()
 */
#ifndef _di_controller_entry_actions_delete_
  extern f_status_t controller_entry_actions_delete(controller_entry_actions_t * const actions);
#endif // _di_controller_entry_actions_delete_

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
 *   F_okay on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_entry_actions_increase_by_
  extern f_status_t controller_entry_actions_increase_by(const f_number_unsigned_t amount, controller_entry_actions_t * const actions);
#endif // _di_controller_entry_actions_increase_by_

/**
 * Fully deallocate all memory for the given entry item without caring about return status.
 *
 * @param item
 *   The item to deallocate.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_entry_item_delete_
  extern f_status_t controller_entry_item_delete(controller_entry_item_t * const item);
#endif // _di_controller_entry_item_delete_

/**
 * Fully deallocate all memory for the given entry items without caring about return status.
 *
 * @param items
 *   The entry_items to deallocate.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_entry_item_delete()
 * @see f_memory_delete()
 */
#ifndef _di_controller_entry_items_delete_
  extern f_status_t controller_entry_items_delete(controller_entry_items_t * const items);
#endif // _di_controller_entry_items_delete_

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
 *   F_okay on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_entry_items_increase_by_
  extern f_status_t controller_entry_items_increase_by(const f_number_unsigned_t amount, controller_entry_items_t * const items);
#endif // _di_controller_entry_items_increase_by_

/**
 * Fully deallocate all memory for the given Rule Action without caring about return status.
 *
 * @param action
 *   The action to deallocate.
 *
 * @see f_memory_arrays_resize()
 */
#ifndef _di_controller_rule_action_delete_
  extern void controller_rule_action_delete(controller_rule_action_t * const action);
#endif // _di_controller_rule_action_delete_

/**
 * Fully deallocate all memory for the given Rule Actions without caring about return status.
 *
 * @param actions
 *   The rule_actions to deallocate.
 *
 * @see controller_rule_action_delete()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_actions_delete_
  extern void controller_rule_actions_delete(controller_rule_actions_t * const actions);
#endif // _di_controller_rule_actions_delete_

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
 *   F_okay on success.
 *   F_array_too_large (with error bit) if the resulting new size is bigger than the max array length.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_controller_rule_actions_increase_by_
  extern f_status_t controller_rule_actions_increase_by(const f_number_unsigned_t amount, controller_rule_actions_t * const actions);
#endif // _di_controller_rule_actions_increase_by_

/**
 * Fully deallocate all memory for the given Rule without caring about return status.
 *
 * @param rule
 *   The rule to deallocate.
 *
 * @see controller_rule_items_delete()
 * @see f_capability_delete()
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_controller_rule_delete_
  extern void controller_rule_delete(controller_rule_t * const rule);
#endif // _di_controller_rule_delete_

/**
 * Fully deallocate all memory for the given Rule Item without caring about return status.
 *
 * @param item
 *   The item to deallocate.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_rule_item_delete_
  extern void controller_rule_item_delete(controller_rule_item_t * const item);
#endif // _di_controller_rule_item_delete_

/**
 * Fully deallocate all memory for the given Rule Items without caring about return status.
 *
 * @param items
 *   The rule_items to deallocate.
 *
 * @see controller_rule_item_delete()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_items_delete_
  extern void controller_rule_items_delete(controller_rule_items_t * const items);
#endif // _di_controller_rule_items_delete_

/**
 * Fully deallocate all memory for the given Rule Item without caring about return status.
 *
 * @param on
 *   The on to deallocate.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_rule_on_delete_
  extern void controller_rule_on_delete(controller_rule_on_t * const on);
#endif // _di_controller_rule_on_delete_

/**
 * Fully deallocate all memory for the given Rule Items without caring about return status.
 *
 * @param ons
 *   The rule_ons to deallocate.
 *
 * @see controller_rule_on_delete()
 * @see f_memory_delete()
 */
#ifndef _di_controller_rule_ons_delete_
  extern void controller_rule_ons_delete(controller_rule_ons_t * const ons);
#endif // _di_controller_rule_ons_delete_

/**
 * Increase the size of the Rule array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param ons
 *   The on array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_rule_ons_resize()
 */
#ifndef _di_controller_rule_ons_increase_
  extern f_status_t controller_rule_ons_increase(controller_rule_ons_t * const ons);
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
 *   F_okay on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_rule_ons_resize_
  extern f_status_t controller_rule_ons_resize(const f_number_unsigned_t length, controller_rule_ons_t * const ons);
#endif // _di_controller_rule_ons_resize_

/**
 * Fully deallocate all memory for the given Rules without caring about return status.
 *
 * @param rules
 *   The rules to deallocate.
 *
 * @see controller_rules_resize()
 */
#ifndef _di_controller_rules_delete_
  extern void controller_rules_delete(controller_rules_t * const rules);
#endif // _di_controller_rules_delete_

/**
 * Increase the size of the Rule array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param rules
 *   The rule array to resize.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is no reason to increase size (used + controller_common_allocation_small_d <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see controller_rules_resize()
 */
#ifndef _di_controller_rules_increase_
  extern f_status_t controller_rules_increase(controller_rules_t * const rules);
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
 *   F_okay on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_rules_resize_
  extern f_status_t controller_rules_resize(const f_number_unsigned_t length, controller_rules_t * const rules);
#endif // _di_controller_rules_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_common_h
