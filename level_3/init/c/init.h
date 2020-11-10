/**
 * FLL - Level 3
 *
 * Project: Init
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the Init program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program performs the basic system boot operations.
 *
 * This program does the following:
 * 1) perform all initial filesystem setup tasks (creating directories, mounting, setting permissions, populated device files, etc..).
 * 2) finding the desired/wanted boot partition, mounting it (and any other mount points).
 * 3) booting into target partition using a given target program (controller, bash, etc..).
 * 4) falling back into a failsafe environment on error (such as bash).
 */
#ifndef _init_h

// libc includes
#include <sys/mount.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/console.h>
#include <level_0/directory.h>
#include <level_0/file.h>
#include <level_0/iki.h>
#include <level_0/print.h>
#include <level_0/signal.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/iki.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/error.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_init_version_
  #define init_major_version "0"
  #define init_minor_version "5"
  #define init_micro_version "2"
  #define init_version init_major_version "." init_minor_version "." init_micro_version
#endif // _di_init_version_

#ifndef _di_init_name_
  #define init_name "init"
  #define init_name_long "Init Program"
#endif // _di_init_name_

#ifndef _di_init_defines_
  #define init_string_classic       "classic"
  #define init_string_color         "color" // for specifying color mode.
  #define init_string_custom        "custom"
  #define init_string_dark          "dark"
  #define init_string_debug         "debug"
  #define init_string_failsafe      "failsafe" // default to /bin/bash if provided failsafe is invalid, or prompt for valid??.
  #define init_string_light         "light"
  #define init_string_maintenance   "maintenance"
  #define init_string_mode          "mode"
  #define init_string_no            "no"
  #define init_string_normal        "normal"
  #define init_string_quiet         "quiet"
  #define init_string_root          "root"
  #define init_string_root_group    "root_group" // floating root group id (such as d_root).
  #define init_string_root_mode     "root_mode"  // floating root mode (such as 2751).
  #define init_string_root_size     "root_size"
  #define init_string_root_sub      "root_sub" // was "subroot".
  #define init_string_run           "run"
  #define init_string_settings      "settings"
  #define init_string_settings_name "settings_name"
  #define init_string_squash        "squash"
  #define init_string_squish        "squish"
  #define init_string_verbose       "verbose"
  #define init_string_verbosity     "verbosity" // quite, normal, verbose, debug
  #define init_string_yes           "yes"

  #define init_string_classic_length       7
  #define init_string_color_length         5
  #define init_string_custom_length        6
  #define init_string_dark_length          4
  #define init_string_debug_length         5
  #define init_string_failsafe_length      8
  #define init_string_light_length         5
  #define init_string_maintenance_length   11
  #define init_string_mode_length          4
  #define init_string_no_length            2
  #define init_string_normal_length        6
  #define init_string_quiet_length         5
  #define init_string_root_length          4
  #define init_string_root_group_length    10
  #define init_string_root_mode_length     9
  #define init_string_root_size_length     9
  #define init_string_root_sub_length      8
  #define init_string_run_length           3
  #define init_string_settings_length      8
  #define init_string_settings_name_length 13
  #define init_string_squash_length        6
  #define init_string_squish_length        6
  #define init_string_verbose_length       7
  #define init_string_verbosity_length     9
  #define init_string_yes_length           3

  #define init_path_proc         "/proc"
  #define init_path_proc_cmdline "/proc/cmdline"
  #define init_path_settings_0   "settings"
  #define init_path_settings_1   ".settings"

  #define init_path_proc_lenght         5
  #define init_path_proc_cmdline_length 13
  #define init_path_settings_0_length   8
  #define init_path_settings_1_length   9

  #define init_path_extension_device ".device"
  #define init_path_extension_lock   ".lock"
  #define init_path_extension_squash ".sfs"

  #define init_path_extension_device_length 7
  #define init_path_extension_lock_length   5
  #define init_path_extension_squash_length 3

  #define init_device_by_device    "device"   // such as: "pci-0000:00:1.0-ata-1"
  #define init_device_by_id        "id"       // such as: "ata-WIN_SSD_1234567890123"
  #define init_device_by_label     "label"    // such as: "my_usb" from LABEL="my_usb"
  #define init_device_by_path      "path"     // such as: "sda1"
  #define init_device_by_type      "type"     // such as: "ext4"
  #define init_device_by_uuid      "uuid"     // such as: "80a2a094-8536-46d9-aa54-cd34c142422b" from UUID="80a2a094-8536-46d9-aa54-cd34c142422b"
  #define init_device_by_uuid_part "partuuid" // such as: "0abcdef1-23" from PARTUUID="0abcdef1-34"

  #define init_device_by_device_length    6
  #define init_device_by_id_length        2
  #define init_device_by_label_length     5
  #define init_device_by_path_length      4
  #define init_device_by_type_length      4
  #define init_device_by_uuid_length      4
  #define init_device_by_uuid_part_length 8

  enum {
    init_mode_classic = 1,
    init_mode_custom,
    init_mode_maintenance,
    init_mode_normal,
    init_mode_squash,
    init_mode_squish,
  };

  enum {
    init_parameter_help,
    init_parameter_light,
    init_parameter_dark,
    init_parameter_no_color,
    init_parameter_version,
  };

  #define init_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_console_type_inverse), \
    }

  #define init_total_parameters 5
#endif // _di_init_defines_

#ifndef _di_init_setting_kernel_t_
  typedef struct {
    bool failsafe;

    bool lock_color;
    bool lock_devices;
    bool lock_failsafe;
    bool lock_mode;
    bool lock_root;
    bool lock_root_group;
    bool lock_root_mode;
    bool lock_root_size;
    bool lock_root_sub;
    bool lock_run;
    bool lock_settings;
    bool lock_settings_name;
    bool lock_verbosity;

    uint8_t color;
    uint8_t mode;
    uint8_t root_mode;
    uint8_t verbosity;

    f_number_unsigned_t root_size;

    f_string_dynamic_t root;
    f_string_dynamic_t root_group;
    f_string_dynamic_t root_sub;
    f_string_dynamic_t run;
    f_string_dynamic_t settings;
    f_string_dynamic_t settings_name;
  } init_setting_kernel_t;

  #define init_setting_kernel_t_initialize \
    { \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      F_false, \
      0, \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_init_setting_kernel_

#ifndef _di_init_data_t_
  typedef struct {
    f_console_parameter_t parameters[init_total_parameters];

    f_string_lengths_t remaining;

    f_file_t output;
    fll_error_print_t error;

    mode_t umask;
    f_signal_t signal;

    init_setting_kernel_t setting_kernel;

    f_color_context_t context;
  } init_data_t;

  #define init_data_initialize \
    { \
      init_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      f_macro_file_t_initialize(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      0, \
      f_signal_t_initialize, \
      init_setting_kernel_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_init_data_t_

/**
 * Print help.
 *
 * @param output
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_init_print_help_
  extern f_return_status init_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_init_print_help_

/**
 * Execute main program.
 *
 * Be sure to call init_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see init_delete_data()
 */
#ifndef _di_init_main_
  extern f_return_status init_main(const f_console_arguments_t arguments, init_data_t *data);
#endif // _di_init_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing init_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see init_main()
 */
#ifndef _di_init_delete_data_
  extern f_return_status init_delete_data(init_data_t *data);
#endif // _di_init_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _init_h
