/* FLL - Level 3
 * Project:       Firewall
 * Version:       0.1.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This is the Kevux Operating System Init program.
 * This program utilizes the Featureless Linux Library.
 *
 * This init program is designed to run with certain paths and if they do not exist, it will attemp to create them.
 * This expects the kevux path permissions structure and naming, so a valid /etc/group file should exist.
 *
 * This is designed to have different threads handling the following actions:
 *   Thread Group 1 (Signals and Output)
 *   - (parent process) handles/blocks all signals for init program and handles children accordingly.
 *
 *   Thread Group 2 (Services)
 *   - Handles starting and stopping of individual services.
 *   - New thread created for each user.
 *
 *   Thread Group 3 (Reporting)
 *   - Handles output to the terminal or any other supported devices.
 *   - No child threads.
 *
 *   Thread Group 4 (Commands: Time)
 *   - Handles time based processing.
 *   - This is a cron system.
 *   - 2 Child threads:
 *     1) Cron-style behavior.
 *     2) Anacron-style behavior.
 *
 *   Thread Group 5 (Commands: Socket File)
 *   - If socket file is enabled, then this thread is created to listen on the socket file and process received commands.
 *   - No child threads.
 *
 *   Thread Group 6 (Commands: Socket Port)
 *   - If socket port is enabled, then this thread is created to listen on the socket port and process received commands.
 *   - No child threads.
 *
 *
 * Time based (aka: cron) functionality is being implemented here because cron jobs often need to run as specific users.
 * The init program is already root and can already switch users, so give it control.
 * This avoids having yet another program that must have root privileges.
 *
 * It would be nice to be able to start the init program as a non-root user who has elevated privileges similar to root.
 * - That is, have ability to su to any user (except root).
 * - While this will still be a security concern, not running as root will significantly reduce the potential problems.
 *   - This design would not allow for root-specific cron jobs.
 */
#ifndef _init_h

// libc includes
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <linux/limits.h> // defines PATH_MAX
#include <sys/mount.h>
#include <sys/types.h>
#include <regex.h>
#include <malloc.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_init_version_
  #define init_major_version "0"
  #define init_minor_version "5"
  #define init_micro_version "0"
  #define init_version init_major_version "." init_minor_version "." init_micro_version
#endif // _di_init_version_

#ifndef _di_init_name_
  #define init_name "init"
  #define init_name_long "Kevux Init Program"
#endif // _di_init_name_

#ifndef _di_init_default_allocation_step_
  #define init_default_allocation_step f_memory_default_allocation_step
#endif // _di_init_default_allocation_step_

#ifndef _di_init_paths_
  // @todo: this will eventually be written to use the f_path project.
  #define init_paths_rootfs         "/"
  #define init_paths_devices        "/dev/"
  #define init_paths_devices_pts    "/dev/pts/"
  #define init_paths_system         "/sys/"
  #define init_paths_processes      "/proc/"
  #define init_paths_temporary      "/tmp/"
  #define init_paths_mount          "/mnt/"
  #define init_paths_run            "/run/"
  #define init_paths_init_run       "/run/init/"
  #define init_paths_init_settings  "/etc/init/"
  #define init_paths_init_socket    "/run/init/socket/"
  #define init_paths_init_process   "/run/init/process/"
  #define init_paths_init_log       "/log/init/"
  #define init_paths_log            "/log/"
#endif // _di_init_paths_

#ifndef _di_init_extension_
  #define init_extension_settings  "settings"
  #define init_extension_rule      "rule"
  #define init_extension_socket    "socket"
  #define init_extension_process   "pid"
#endif // _di_init_extension_

#ifndef _di_init_settings_
  #define init_rule_core       "main"
  #define init_rule_core_file  init_paths_init_settings init_rule_core "." init_extension_rule

  #define init_kernel_command_line     init_paths_processes "cmdline"
  #define init_kernel_runlevel         "\\<runlevel=[[:alnum:][:punct:]]*"
  #define init_kernel_runlevel_ignore  9
  #define init_kernel_runlevel_buffer  256
#endif // _di_init_settings_

#ifndef _di_init_socket_
  #define init_socket_control  "control"
#endif // _di_init_settings_

#ifndef _di_init_groups_
  #define init_group_devices          "d_device"
  #define init_group_devices_pts      "d_devpts"
  #define init_group_system           "k_system"
  #define init_group_processes        "k_process"
  #define init_group_temporary        "d_temporary"
  #define init_group_mount            "d_mount"
  #define init_group_run              "d_run"
  #define init_group_init_run         "d_init_run"
  #define init_group_init_settings    "d_init_settings"
  #define init_group_init_socket      "d_init_socket"
  #define init_group_init_process     "d_init_process"
  #define init_group_init_log         "d_log"
  #define init_group_process_null     "p_null"
  #define init_group_process_zero     "p_zero"
  #define init_group_process_console  "p_terminal"
  #define init_group_process_random   "p_random"
  #define init_group_process_urandom  "p_random"
#endif // _di_init_groups_

#ifndef _di_init_defines_
  #define init_parameter_runlevel_short_name    "r"
  #define init_parameter_no_prepare_short_name  "n"

  #define init_parameter_runlevel_long_name    "run_level"
  #define init_parameter_no_prepare_long_name  "no_prepare"

  enum {
    init_parameter_help,
    init_parameter_light,
    init_parameter_no_color,
    init_parameter_version,
    init_parameter_debug,
    init_parameter_runlevel,
    init_parameter_no_prepare,
  };

  #ifdef _en_init_debug_
    #define f_console_parameter_initialize_init \
      { \
        f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, f_false, f_console_type_normal), \
        f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, f_false, f_console_type_inverse), \
        f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, f_false, f_console_type_inverse), \
        f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, f_false, f_console_type_inverse), \
        f_console_parameter_initialize(f_console_standard_short_debug, f_console_standard_long_debug, 0, f_false, f_console_type_inverse), \
        f_console_parameter_initialize(init_parameter_runlevel_short_name, init_parameter_runlevel_long_name, 0, f_true, f_console_type_normal), \
        f_console_parameter_initialize(init_parameter_no_prepare_short_name, init_parameter_no_prepare_long_name, 0, f_true, f_console_type_normal), \
      }

    #define init_total_parameters 7
  #else
    #define f_console_parameter_initialize_init \
      { \
        f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, f_false, f_console_type_normal), \
        f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, f_false, f_console_type_inverse), \
        f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, f_false, f_console_type_inverse), \
        f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, f_false, f_console_type_inverse), \
        f_console_parameter_initialize(init_parameter_runlevel_short_name, init_parameter_runlevel_long_name, 0, f_true, f_console_type_normal), \
        f_console_parameter_initialize(init_parameter_no_prepare_short_name, init_parameter_no_prepare_long_name, 0, f_true, f_console_type_normal), \
      }

    #define init_total_parameters 6
  #endif // _en_init_debug_
#endif // _di_init_defines_

#ifndef _di_init_argument_
  typedef struct {
    f_console_parameter parameters[init_total_parameters];

    fl_color_context context;
  } init_argument;

  #define init_argument_initialize \
    { \
      f_console_parameter_initialize_init, \
      fl_color_context_initialize, \
    }

  #define init_delete_argument(status, argument) \
    memset(&argument.parameters, 0, sizeof(f_console_parameter) * init_total_parameters); \
    fl_delete_color_context(status, argument.context);

  #define init_destroy_argument(status, argument) \
    memset(&argument.parameters, 0, sizeof(f_console_parameter) * init_total_parameters); \
    fl_destroy_color_context(status, argument.context);
#endif // _di_init_argument_

#ifndef _di_init_print_version_
  extern f_return_status init_print_version(const init_argument data);
#endif // _di_init_print_version_

#ifndef _di_init_print_help_
  extern f_return_status init_print_help(const init_argument data);
#endif // _di_init_print_help_

#ifndef _di_init_main_
  extern f_return_status init_main(const f_s_int argc, const f_string argv[], init_argument *data);
#endif // _di_init_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _init_h
