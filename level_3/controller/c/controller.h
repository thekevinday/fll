/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
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
#include <fll/level_2/path.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_version_
  #define controller_program_version_major_s F_string_ascii_0_s
  #define controller_program_version_minor_s F_string_ascii_5_s
  #define controller_program_version_micro_s F_string_ascii_7_s

  #ifndef controller_program_version_nano_prefix_s
    #define controller_program_version_nano_prefix_s
  #endif

  #ifndef controller_program_version_nano_s
    #define controller_program_version_nano_s
  #endif

  #define controller_program_version_s controller_program_version_major_s F_string_ascii_period_s controller_program_version_minor_s F_string_ascii_period_s controller_program_version_micro_s controller_program_version_nano_prefix_s controller_program_version_nano_s
#endif // _di_controller_program_version_

#ifndef _di_controller_program_name_
  #define controller_program_name_s      "controller"
  #define controller_program_name_long_s "Controller Program"

  #define controller_program_name_init_s      "init"
  #define controller_program_name_init_long_s "Init Program"
#endif // _di_controller_program_name_

#ifndef _di_controller_defines_

  // the init pid path is a system-specific path and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_pid_init_) && defined(_override_controller_path_pid_init_length_)
    #define controller_path_pid_init_s         _override_controller_path_pid_init_
    #define controller_path_pid_init_s_length  _override_controller_path_pid_init_length_
  #elif defined(_controller_as_init_)
    #define controller_path_pid_init_s        "/var/run/init/init-"
    #define controller_path_pid_init_s_length 19
  #else
    #define controller_path_pid_init_s        "/var/run/controller/controller-"
    #define controller_path_pid_init_s_length 31
  #endif /* defined(_override_controller_path_pid_init_) && defined(_override_controller_path_pid_init_length_) */

  // the settings path is a system-specific path and needs to be more easily contolled at compile time.
  #if defined(_override_controller_path_settings_init_) && defined(_override_controller_path_settings_init_length_)
    #define controller_path_settings_init_s        _override_controller_path_settings_init_
    #define controller_path_settings_init_s_length _override_controller_path_settings_init_length_
  #elif defined(_controller_as_init_)
    #define controller_path_settings_init_s "/etc/init"
    #define controller_path_settings_init_s_length 9
  #else
    #define controller_path_settings_init_s "/etc/controller"
    #define controller_path_settings_init_s_length 15
  #endif /* defined(_override_controller_path_settings_init_) && defined(_override_controller_path_settings_init_length_) */

  #ifdef _override_controller_default_program_script_
    #define controller_default_program_script_s _override_controller_default_program_script_
  #else
    #define controller_default_program_script_s "bash"
  #endif // _override_controller_default_program_script_

  #define controller_path_pid_s      "controller/run/controller-"
  #define controller_path_settings_s "controller"
  #define controller_path_suffix_s   ".pid"

  #define controller_path_pid_s_length      26
  #define controller_path_settings_s_length 10
  #define controller_path_suffix_s_length   4

  #define controller_short_control_s         "c"
  #define controller_short_daemon_s          "d"
  #define controller_short_init_s            "I"
  #define controller_short_interruptible_s   "i"
  #define controller_short_pid_s             "p"
  #define controller_short_settings_s        "s"
  #define controller_short_simulate_s        "S"
  #define controller_short_uninterruptible_s "U"
  #define controller_short_validate_s        "v"

  #define controller_long_control_s         "control"
  #define controller_long_daemon_s          "daemon"
  #define controller_long_init_s            "init"
  #define controller_long_interruptible_s   "interruptible"
  #define controller_long_pid_s             "pid"
  #define controller_long_settings_s        "settings"
  #define controller_long_simulate_s        "simulate"
  #define controller_long_uninterruptible_s "uninterruptible"
  #define controller_long_validate_s        "validate"

  enum {
    controller_parameter_help,
    controller_parameter_light,
    controller_parameter_dark,
    controller_parameter_no_color,
    controller_parameter_verbosity_quiet,
    controller_parameter_verbosity_normal,
    controller_parameter_verbosity_verbose,
    controller_parameter_verbosity_debug,
    controller_parameter_version,

    controller_parameter_control,
    controller_parameter_daemon,
    controller_parameter_init,
    controller_parameter_interruptible,
    controller_parameter_pid,
    controller_parameter_settings,
    controller_parameter_simulate,
    controller_parameter_uninterruptible,
    controller_parameter_validate,
  };

  #define controller_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help_s, f_console_standard_long_help_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light_s, f_console_standard_long_light_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark_s, f_console_standard_long_dark_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal_s, f_console_standard_long_normal_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug_s, f_console_standard_long_debug_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version_s, f_console_standard_long_version_s, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(controller_short_control_s, controller_long_control_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_daemon_s, controller_long_daemon_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_init_s, controller_long_init_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_interruptible_s, controller_long_interruptible_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_pid_s, controller_long_pid_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_settings_s, controller_long_settings_s, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_simulate_s, controller_long_simulate_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_uninterruptible_s, controller_long_uninterruptible_s, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(controller_short_validate_s, controller_long_validate_s, 0, 0, f_console_type_normal), \
    }

  #define controller_total_parameters_d 18
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

    f_string_t program_name;
    f_string_t program_name_long;
    f_string_static_t setting_default;
    f_string_static_t path_pid;

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
      f_string_t_initialize, \
      f_string_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
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
 * - F_signal_abort
 * - F_signal_broken_pipe
 * - F_signal_hangup
 * - F_signal_interrupt
 * - F_signal_quit
 * - F_signal_termination
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
 * - F_signal_abort
 * - F_signal_broken_pipe
 * - F_signal_hangup
 * - F_signal_interrupt
 * - F_signal_quit
 * - F_signal_termination
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
