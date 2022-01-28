/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is the Controller program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program provides system service management, much like sysvcontroller and controllerng.
 * This program can be controlled from user-space via the "control" program.
 * This program can be used in an initrd and should be capable of pivot root operations.
 *
 * @todo Implement "exit" files that are the opposite of "entry" files whereas rules specified within are all called via the "stop" action type.
 *       This would then allow for switching modes.
 *       The "exit" would be specified in the "entry", by name and would be found under "exits" directory alongside the "entries" directory.
 *
 * @todo check the return status of unlocks.
 *
 * @todo the read/write locks (and unlocks) needs to be more robust in that they need to attempt to keep going even on failure or need to wait until resolvable.
 *       this is done to help ensure that the controller program always continues onward.
 *
 * @todo just like with the read/write locks, the out of memory cases need to be handled to keep going instead of bailing.
 *       likely these will need to be sleeps on the premise that eventually memory will clear itself up.
 */
#ifndef _controller_h

// include pre-requirements
#define _GNU_SOURCE

// libc includes
#include <sched.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <linux/sched.h>
#include <unistd.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/account.h>
#include <fll/level_0/capability.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/control_group.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/environment.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/file.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/path.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>
#include <fll/level_0/socket.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/control_group.h>
#include <fll/level_1/environment.h>
#include <fll/level_1/fss.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/control_group.h>
#include <fll/level_2/error.h>
#include <fll/level_2/execute.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/fss_basic_list.h>
#include <fll/level_2/fss_extended.h>
#include <fll/level_2/fss_extended_list.h>
#include <fll/level_2/fss_payload.h>
#include <fll/level_2/path.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_version_
  #define CONTROLLER_program_version_major_s F_string_ascii_0_s
  #define CONTROLLER_program_version_minor_s F_string_ascii_5_s
  #define CONTROLLER_program_version_micro_s F_string_ascii_8_s

  #define CONTROLLER_program_version_major_s_length 1
  #define CONTROLLER_program_version_minor_s_length 1
  #define CONTROLLER_program_version_micro_s_length 1

  #ifndef CONTROLLER_program_version_nano_prefix_s
    #define CONTROLLER_program_version_nano_prefix_s

    #define CONTROLLER_program_version_nano_prefix_s_length 0
  #endif

  #ifndef CONTROLLER_program_version_nano_s
    #define CONTROLLER_program_version_nano_s

    #define CONTROLLER_program_version_nano_s_length 0
  #endif

  #define CONTROLLER_program_version_s CONTROLLER_program_version_major_s F_string_ascii_period_s CONTROLLER_program_version_minor_s F_string_ascii_period_s CONTROLLER_program_version_micro_s CONTROLLER_program_version_nano_prefix_s CONTROLLER_program_version_nano_s

  #define CONTROLLER_program_version_s_length CONTROLLER_program_version_major_s_length + F_string_ascii_period_s_length + CONTROLLER_program_version_minor_s_length + F_string_ascii_period_s_length + CONTROLLER_program_version_nano_prefix_s_length + CONTROLLER_program_version_nano_s_length

  extern const f_string_static_t controller_program_version_s;
#endif // _di_controller_program_version_

#ifndef _di_controller_program_name_
  #define CONTROLLER_program_name_s      "controller"
  #define CONTROLLER_program_name_long_s "Controller Program"

  #define CONTROLLER_program_name_init_s      "init"
  #define CONTROLLER_program_name_init_long_s "Init Program"

  #define CONTROLLER_program_name_s_length      7
  #define CONTROLLER_program_name_long_s_length 15

  #define CONTROLLER_program_name_init_s_length      4
  #define CONTROLLER_program_name_init_long_s_length 12

  extern const f_string_static_t controller_program_name_s;
  extern const f_string_static_t controller_program_name_long_s;

  extern const f_string_static_t controller_program_name_init_s;
  extern const f_string_static_t controller_program_name_init_long_s;
#endif // _di_controller_program_name_

#ifndef _di_controller_defines_

  // The pid path is a system-specific path and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_pid_) && defined(_override_controller_path_pid_length_)
    #define CONTROLLER_path_pid_s        _override_controller_path_pid_
    #define CONTROLLER_path_pid_s_length _override_controller_path_pid_length_
  #else
    #define CONTROLLER_path_pid_s        "controller/run"
    #define CONTROLLER_path_pid_s_length 14
  #endif // defined(_override_controller_path_pid_) && defined(_override_controller_path_pid_length_)

  // The init pid path is a system-specific path and needs to be more easily contolled at compile time.
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

  // The pid prefix is a system-specific path part and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_pid_prefix_) && defined(_override_controller_path_pid_prefix_length_)
    #define CONTROLLER_path_pid_prefix_s _override_controller_path_pid_prefix_

    #define CONTROLLER_path_pid_prefix_s_length _override_controller_path_pid_prefix_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_pid_prefix_s "init-"

    #define CONTROLLER_path_pid_prefix_s_length 5
  #else
    #define CONTROLLER_path_pid_prefix_s ""

    #define CONTROLLER_path_pid_prefix_s_length 0
  #endif // defined(_override_controller_name_pid_prefix_) && defined(_override_controller_name_pid_prefix_length_)

  // The socket suffix path is a system-specific path part and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_pid_suffix_) && defined(_override_controller_path_pid_suffix_length_)
    #define CONTROLLER_path_pid_suffix_s _override_controller_path_pid_suffix_

    #define CONTROLLER_path_pid_suffix_s_length _override_controller_path_pid_suffix_length_
  #else
    #define CONTROLLER_path_pid_suffix_s ".pid"

    #define CONTROLLER_path_pid_suffix_s_length 4
  #endif // defined(_override_controller_name_pid_suffix_) && defined(_override_controller_name_pid_suffix_length_)

  // The settings path is a system-specific path part and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_settings_) && defined(_override_controller_path_settings_length_)
    #define CONTROLLER_path_settings_s        _override_controller_path_settings_
    #define CONTROLLER_path_settings_s_length _override_controller_path_settings_length_
  #else
    #define CONTROLLER_path_settings_s "controller"
    #define CONTROLLER_path_settings_s_length 10
  #endif // defined(_override_controller_path_settings_) && defined(_override_controller_path_settings_length_)

  // The init settings path is a system-specific path part and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_settings_init_) && defined(_override_controller_path_settings_init_length_)
    #define CONTROLLER_path_settings_init_s        _override_controller_path_settings_init_
    #define CONTROLLER_path_settings_init_s_length _override_controller_path_settings_init_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_settings_init_s "/etc/init"
    #define CONTROLLER_path_settings_init_s_length 9
  #else
    #define CONTROLLER_path_settings_init_s "/etc/controller"
    #define CONTROLLER_path_settings_init_s_length 15
  #endif // defined(_override_controller_path_settings_init_) && defined(_override_controller_path_settings_init_length_)

  // The socket path is a system-specific path and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)
    #define CONTROLLER_path_socket_s _override_controller_path_socket_

    #define CONTROLLER_path_socket_s_length _override_controller_path_socket_length_
  #else
    #define CONTROLLER_path_socket_s "controller/run"

    #define CONTROLLER_path_socket_s_length 14
  #endif // defined(_override_controller_path_socket_) && defined(_override_controller_path_socket_length_)

  // The socket path is a system-specific path and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_socket_init_) && defined(_override_controller_path_socket_init_length_)
    #define CONTROLLER_path_socket_init_s _override_controller_path_socket_init_

    #define CONTROLLER_path_socket_init_s_length _override_controller_path_socket_init_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_socket_init_s "/var/run/init"

    #define CONTROLLER_path_socket_init_s_length 13
  #else
    #define CONTROLLER_path_socket_init_s "/var/run/controller"

    #define CONTROLLER_path_socket_init_s_length 19
  #endif // defined(_override_controller_path_socket_init_) && defined(_override_controller_path_socket_init_length_)

  // The socket prefix path is a system-specific path part and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)
    #define CONTROLLER_path_socket_prefix_s _override_controller_path_socket_prefix_

    #define CONTROLLER_path_socket_prefix_s_length _override_controller_path_socket_prefix_length_
  #elif defined(_controller_as_init_)
    #define CONTROLLER_path_socket_prefix_s "init-"

    #define CONTROLLER_path_socket_prefix_s_length 5
  #else
    #define CONTROLLER_path_socket_prefix_s ""

    #define CONTROLLER_path_socket_prefix_s_length 0
  #endif // defined(_override_controller_path_socket_prefix_) && defined(_override_controller_path_socket_prefix_length_)

  // The socket suffix path is a system-specific path part and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_socket_suffix_) && defined(_override_controller_path_socket_suffix_length_)
    #define CONTROLLER_path_socket_suffix_s _override_controller_path_socket_suffix_

    #define CONTROLLER_path_socket_suffix_s_length _override_controller_path_socket_suffix_length_
  #else
    #define CONTROLLER_path_socket_suffix_s ".socket"

    #define CONTROLLER_path_socket_suffix_s_length 7
  #endif // defined(_override_controller_path_socket_suffix_) && defined(_override_controller_path_socket_suffix_length_)

  #if defined(_override_controller_default_program_script_) && defined(_override_controller_default_program_script_length_)
    #define CONTROLLER_default_program_script_s _override_controller_default_program_script_

    #define CONTROLLER_default_program_script_s_length _override_controller_default_program_script_length_
  #else
    #define CONTROLLER_default_program_script_s "bash"

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
    controller_parameter_light_e,
    controller_parameter_dark_e,
    controller_parameter_no_color_e,
    controller_parameter_verbosity_quiet_e,
    controller_parameter_verbosity_normal_e,
    controller_parameter_verbosity_verbose_e,
    controller_parameter_verbosity_debug_e,
    controller_parameter_version_e,

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
  };

  #define controller_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(controller_short_cgroup_s.string, controller_long_cgroup_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_daemon_s.string, controller_long_daemon_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_init_s.string, controller_long_init_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_interruptible_s.string, controller_long_interruptible_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_pid_s.string, controller_long_pid_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_settings_s.string, controller_long_settings_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_simulate_s.string, controller_long_simulate_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_socket_s.string, controller_long_socket_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_uninterruptible_s.string, controller_long_uninterruptible_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(controller_short_validate_s.string, controller_long_validate_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define controller_total_parameters_d 19
#endif // _di_controller_defines_

#ifndef _di_controller_main_t_
  typedef struct {
    f_console_parameter_t parameters[controller_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;
    bool as_init;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    pid_t pid;
    mode_t umask;
    int child;

    const f_string_static_t *program_name;
    const f_string_static_t *program_name_long;
    const f_string_static_t *default_path_setting;
    const f_string_static_t *default_path_pid;
    const f_string_static_t *default_path_socket;

    f_color_context_t context;
  } controller_main_t;

  #define controller_main_t_initialize \
    { \
      controller_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
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
      f_color_context_t_initialize, \
    }
#endif // _di_controller_main_t_

/**
 * Print help.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_controller_print_help_
  extern f_status_t controller_print_help(controller_main_t * const main);
#endif // _di_controller_print_help_

/**
 * Execute main program.
 *
 * Be sure to call controller_main_delete() after executing this.
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
 * @param arguments
 *   The parameters passed to the process.
 *
 * @return
 *   F_none on success.
 *   F_child if this is a child process returning.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see controller_main_delete()
 */
#ifndef _di_controller_main_
  extern f_status_t controller_main(controller_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_controller_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing controller_main().
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
 *
 * @see controller_main()
 */
#ifndef _di_controller_main_delete_
  extern f_status_t controller_main_delete(controller_main_t * const main);
#endif // _di_controller_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_h
