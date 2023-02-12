/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project path.
 *
 * This is auto-included by path.h and should not need to be explicitly included.
 */
#ifndef _F_path_common_h
#define _F_path_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Standard path defines.
 */
#ifndef _di_f_path_d_
  #define F_path_length_max_d PATH_MAX
#endif // _di_f_path_d_

/**
 * Standard path strings.
 *
 * The path separator, intended to be represented as a single character.
 * The path separator length must be a 1-byte wide character.
 *
 * The "current" path separator "." represents a part of the path that potentially may represent the current path.
 * This is expected to be followed by a separator "/".
 *
 * The path variable separator is intended to represent the path separator used in the PATH environment variable.
 * PATH="/bin:/usr/bin", the path variable separator is ':'.
 * The path variable separator must be a 1-byte wide character.
 *
 * The path extension separator is for the separator that separates the main part of a file path with its extension (which is generally a '.').
 */
#ifndef _di_f_path_s_
  #define F_path_separator_s          F_string_ascii_slash_forward_s
  #define F_path_separator_current_s  F_string_ascii_period_s
  #define F_path_separator_variable_s F_string_ascii_colon_s

  #define F_path_separator_s_length          1
  #define F_path_separator_current_s_length  1
  #define F_path_separator_variable_s_length 1

  #define F_path_extension_separator_s F_string_ascii_period_s

  #define F_path_extension_separator_s_length 1

  #define F_path_environment_s         "PATH"
  #define F_path_home_wildcard_s       F_string_ascii_tilde_s
  #define F_path_present_working_s     "PWD"
  #define F_path_present_working_old_s "OLDPWD"

  #define F_path_environment_s_length         4
  #define F_path_home_wildcard_s_length       F_string_ascii_tilde_s_length
  #define F_path_present_working_s_length     3
  #define F_path_present_working_old_s_length 6

  #ifndef _di_f_path_separator_s_
    extern const f_string_static_t f_path_separator_s;
  #endif // _di_f_path_separator_s_

  #ifndef _di_f_path_separator_current_s_
    extern const f_string_static_t f_path_separator_current_s;
  #endif // _di_f_path_separator_current_s_

  #ifndef _di_f_path_separator_variable_s_
    extern const f_string_static_t f_path_separator_variable_s;
  #endif // _di_f_path_separator_variable_s_

  #ifndef _di_f_path_extension_separator_s_
    extern const f_string_static_t f_path_extension_separator_s;
  #endif // _di_f_path_extension_separator_s_

  #ifndef _di_f_path_environment_s_
    extern const f_string_static_t f_path_environment_s;
  #endif // _di_f_path_environment_s_

  #ifndef _di_f_path_home_wildcard_s_
    extern const f_string_static_t f_path_home_wildcard_s;
  #endif // _di_f_path_home_wildcard_s_

  #ifndef _di_f_path_present_working_s_
    extern const f_string_static_t f_path_present_working_s;
  #endif // _di_f_path_present_working_s_

  #ifndef _di_f_path_present_working_old_s_
    extern const f_string_static_t f_path_present_working_old_s;
  #endif // _di_f_path_present_working_old_s_

  /**
   * Provide Kevux ARCHITECTURE_BITS environment variable handling support.
   *
   * Non-Kevux systems should not need this and enabling this might cause problems.
   *
   * This uses the defines for customizing the architecture bits (and scripts) path:
   *   - _en_kevux_path_architecture_bits_default_name_
   *   - _en_kevux_path_architecture_bits_default_length_
   *   - _en_kevux_path_architecture_bits_scripts_name_
   *   - _en_kevux_path_architecture_bits_scripts_length_
   *
   * The path separator should not be specified for these defines because it is automatically appended.
   * Disable either the default or scripts by setting the length to 0.
   *
   * F_path_*_s:
   *   - architecture_bits:          The architecture bits environment variable (usually is "ARCHITECTURE_BITS").
   *   - architecture_bits_default:  The default architecture bits string with a trailing path separator, such as "x64/".
   *   - architecture_bits_scripts:  The default architecture bits string with a trailing path separator, such as "scripts/".
   */
  #ifdef _en_kevux_path_architecture_bits_
    #define F_path_architecture_bits_s "ARCHITECTURE_BITS"

    #define F_path_architecture_bits_s_length 17

    #if defined(_en_kevux_path_architecture_bits_default_name_) && defined(_en_kevux_path_architecture_bits_default_length_)
      #if _en_kevux_path_architecture_bits_default_length_ == 0
        #define F_path_architecture_bits_default_s F_string_empty_s

        #define F_path_architecture_bits_default_s_length F_string_empty_s_length
      #else
        #define F_path_architecture_bits_default_s _en_kevux_path_architecture_bits_default_name_

        #define F_path_architecture_bits_default_s_length _en_kevux_path_architecture_bits_default_length_ + F_path_separator_s_length
      #endif // _en_kevux_path_architecture_bits_default_length_ == 0
    #else
      #define F_path_architecture_bits_default_s "x64" F_path_separator_s

      #define F_path_architecture_bits_default_s_length 3 + F_path_separator_s_length
    #endif // !defined(_en_kevux_path_architecture_bits_default_name_) || !defined(_en_kevux_path_architecture_bits_default_length_)

    #if defined(_en_kevux_path_architecture_bits_scripts_name_) && defined(_en_kevux_path_architecture_bits_scripts_length_)
      #if _en_kevux_path_architecture_bits_scripts_length_ == 0
        #define F_path_architecture_bits_scripts_s F_string_empty_s

        #define F_path_architecture_bits_scripts_s_length F_string_empty_s_length
      #else
        #define F_path_architecture_bits_scripts_s _en_kevux_path_architecture_bits_scripts_name_

        #define F_path_architecture_bits_scripts_s_length _en_kevux_path_architecture_bits_scripts_length_ + F_path_separator_s_length
      #endif // _en_kevux_path_architecture_bits_scripts_length_ == 0
    #else
      #define F_path_architecture_bits_scripts_s "scripts" F_path_separator_s

      #define F_path_architecture_bits_scripts_s_length 7 + F_path_separator_s_length
    #endif // !defined(_en_kevux_path_architecture_bits_scripts_name_) || !defined(_en_kevux_path_architecture_bits_scripts_length_)

    extern const f_string_static_t f_path_architecture_bits_s;
    extern const f_string_static_t f_path_architecture_bits_default_s;
    extern const f_string_static_t f_path_architecture_bits_scripts_s;
  #endif // _en_kevux_path_architecture_bits_
#endif // _di_f_path_s_

/**
 * KFS Filesystem Paths
 */
#ifndef _di_f_path_tree_kevux_standard_d_

  // Disable the FHS default paths.
  #define _di_f_path_tree_hierarchy_standard_d_

  // KFS Root Level.
  #define F_path_tree_devices_s   F_path_separator_s "devices"
  #define F_path_tree_external_s  F_path_separator_s "external"
  #define F_path_tree_libraries_s F_path_separator_s "libraries"
  #define F_path_tree_programs_s  F_path_separator_s "programs"
  #define F_path_tree_temporary_s F_path_separator_s "temporary"
  #define F_path_tree_home_s      F_path_separator_s "home"
  #define F_path_tree_run_s       F_path_separator_s "run"
  #define F_path_tree_binary_s    F_path_separator_s ".system"

  #define F_path_tree_devices_s_length   F_path_separator_s_length + 7
  #define F_path_tree_external_s_length  F_path_separator_s_length + 8
  #define F_path_tree_libraries_s_length F_path_separator_s_length + 9
  #define F_path_tree_programs_s_length  F_path_separator_s_length + 8
  #define F_path_tree_temporary_s_length F_path_separator_s_length + 9
  #define F_path_tree_home_s_length      F_path_separator_s_length + 4
  #define F_path_tree_run_s_length       F_path_separator_s_length + 3
  #define F_path_tree_binary_s_length    F_path_separator_s_length + 7

  // Kernel Level.
  #define F_path_tree_boot_s      f_path_devices_s F_path_separator_s "boot"
  #define F_path_tree_hardware_s  f_path_devices_s F_path_separator_s "devices"
  #define F_path_tree_processes_s f_path_devices_s F_path_separator_s "processes"
  #define F_path_tree_system_s    f_path_devices_s F_path_separator_s "system"

  #define F_path_tree_boot_s_length      F_path_separator_s_length + 4
  #define F_path_tree_hardware_s_length  F_path_separator_s_length + 7
  #define F_path_tree_processes_s_length F_path_separator_s_length + 9
  #define F_path_tree_system_s_length    F_path_separator_s_length + 6

  // Program Level.
  #define F_path_tree_programs_public_s    f_path_programs F_path_separator_s "public"
  #define F_path_tree_programs_system_s    f_path_programs F_path_separator_s "system"
  #define F_path_tree_programs_remote_s    f_path_programs F_path_separator_s "remote"
  #define F_path_tree_programs_services_s  f_path_programs F_path_separator_s "targets"
  #define F_path_tree_programs_toolchain_s f_path_programs F_path_separator_s "toolchain"
  #define F_path_tree_programs_users_s     f_path_programs F_path_separator_s "users"
  #define F_path_tree_programs_susers_s    f_path_programs F_path_separator_s "users"
  #define F_path_tree_programs_boot_s      f_path_boot F_path_separator_s "programs"
  #define F_path_tree_programs_sboot_s     f_path_boot F_path_separator_s "programs"

  #define F_path_tree_programs_public_s_length    f_path_programs_s_length + F_path_separator_s_length + 6
  #define F_path_tree_programs_system_s_length    f_path_programs_s_length + F_path_separator_s_length + 6
  #define F_path_tree_programs_remote_s_length    f_path_programs_s_length + F_path_separator_s_length + 6
  #define F_path_tree_programs_services_s_length  f_path_programs_s_length + F_path_separator_s_length + 7
  #define F_path_tree_programs_toolchain_s_length f_path_programs_s_length + F_path_separator_s_length + 9
  #define F_path_tree_programs_users_s_length     f_path_programs_s_length + F_path_separator_s_length + 5
  #define F_path_tree_programs_susers_s_length    f_path_programs_s_length + F_path_separator_s_length + 5
  #define F_path_tree_programs_boot_s_length      f_path_programs_s_length + F_path_separator_s_length + 8
  #define F_path_tree_programs_sboot_s_length     f_path_programs_s_length + F_path_separator_s_length + 8

  // Library Level.
  #define F_path_tree_libraries_public_s    f_path_libraries_s F_path_separator_s "public"
  #define F_path_tree_libraries_system_s    f_path_libraries_s F_path_separator_s "system"
  #define F_path_tree_libraries_remote_s    f_path_libraries_s F_path_separator_s "remote"
  #define F_path_tree_libraries_services_s  f_path_libraries_s F_path_separator_s "targets"
  #define F_path_tree_libraries_toolchain_s f_path_libraries_s F_path_separator_s "toolchain"
  #define F_path_tree_libraries_users_s     f_path_libraries_s F_path_separator_s "users"
  #define F_path_tree_libraries_boot_s      f_path_boot_s F_path_separator_s "libraries"

  #define F_path_tree_libraries_public_s_length    f_path_libraries_s_length + F_path_separator_s_length + 6
  #define F_path_tree_libraries_system_s_length    f_path_libraries_s_length + F_path_separator_s_length + 6
  #define F_path_tree_libraries_remote_s_length    f_path_libraries_s_length + F_path_separator_s_length + 6
  #define F_path_tree_libraries_services_s_length  f_path_libraries_s_length + F_path_separator_s_length + 7
  #define F_path_tree_libraries_toolchain_s_length f_path_libraries_s_length + F_path_separator_s_length + 9
  #define F_path_tree_libraries_users_s_length     f_path_libraries_s_length + F_path_separator_s_length + 5
  #define F_path_tree_libraries_boot_s_length      f_path_boot_s_length + F_path_separator_s_length + 9

  // Home Level.
  #define F_path_tree_home_services_s f_path_home_s F_path_separator_s "services"
  #define F_path_tree_home_share_s    f_path_home_s F_path_separator_s "share"
  #define F_path_tree_home_users_s    f_path_home_s F_path_separator_s "users"
  #define F_path_tree_home_websites_s f_path_home_s F_path_separator_s "websites"

  #define F_path_tree_home_services_s_length f_path_home_s_length + F_path_separator_s_length + 8
  #define F_path_tree_home_share_s_length    f_path_home_s_length + F_path_separator_s_length + 5
  #define F_path_tree_home_users_s_length    f_path_home_s_length + F_path_separator_s_length + 5
  #define F_path_tree_home_websites_s_length f_path_home_s_length + F_path_separator_s_length + 8

  // System Level.
  #define F_path_tree_system_logs_s      f_path_system_s F_path_separator_s "logs"
  #define F_path_tree_system_settings_s  f_path_system_s F_path_separator_s "settings"
  #define F_path_tree_system_data_s      f_path_system_s F_path_separator_s "data"
  #define F_path_tree_system_variables_s f_path_system_s F_path_separator_s "variables" // for backwards FHS support only, use of this directory is considered bad practice for KFS, use f_path_temporary_variables instead.

  #define F_path_tree_system_logs_s_length      f_path_system_s_length + F_path_separator_s_length + 4
  #define F_path_tree_system_settings_s_length  f_path_system_s_length + F_path_separator_s_length + 8
  #define F_path_tree_system_data_s_length      f_path_system_s_length + F_path_separator_s_length + 4
  #define F_path_tree_system_variables_s_length f_path_system_s_length + F_path_separator_s_length

  // Temporary Level.
  #define F_path_tree_temporary_public_s    f_path_temporary_s F_path_separator_s "public"
  #define F_path_tree_temporary_services_s  f_path_temporary_s F_path_separator_s "services"
  #define F_path_tree_temporary_users_s     f_path_temporary_s F_path_separator_s "users"
  #define F_path_tree_temporary_variables_s f_path_temporary_s F_path_separator_s "variables"

  #define F_path_tree_temporary_public_s_length    f_path_temporary_s_length + F_path_separator_s_length + 6
  #define F_path_tree_temporary_services_s_length  f_path_temporary_s_length + F_path_separator_s_length + 8
  #define F_path_tree_temporary_users_s_length     f_path_temporary_s_length + F_path_separator_s_length + 5
  #define F_path_tree_temporary_variables_s_length f_path_temporary_s_length + F_path_separator_s_length + 9

  // Private User Directories.
  #define F_path_tree_user_downloads_s "downloads"
  #define F_path_tree_user_desktop_s   "desktop"
  #define F_path_tree_user_private_s   "private"
  #define F_path_tree_user_settings_s  "settings"
  #define F_path_tree_user_data_s      "data"
  #define F_path_tree_user_temporary_s "temporary"
  #define F_path_tree_user_shared_s    "shared"

  #define F_path_tree_user_downloads_s_length 9
  #define F_path_tree_user_desktop_s_length   7
  #define F_path_tree_user_private_s_length   7
  #define F_path_tree_user_settings_s_length  8
  #define F_path_tree_user_data_s_length      4
  #define F_path_tree_user_temporary_s_length 9
  #define F_path_tree_user_shared_s_length    6
#endif // _di_f_path_tree_kevux_standard_d_

/**
 * FHS Filesystem Paths
 */
#ifndef _di_f_path_tree_hierarchy_standard_d_

  // Disable the kevux standard default paths.
  #define _di_f_path_tree_kevux_standard_d_

  // KFS Root Level.
  #define F_path_tree_devices_s   F_path_separator_s
  #define F_path_tree_external_s  F_path_separator_s "mnt"
  #define F_path_tree_libraries_s F_path_separator_s
  #define F_path_tree_programs_s  F_path_separator_s
  #define F_path_tree_temporary_s F_path_separator_s
  #define F_path_tree_home_s      F_path_separator_s "home"
  #define F_path_tree_run_s       F_path_separator_s "run"
  #define F_path_tree_binary_s    F_path_separator_s ".system"

  #define F_path_tree_devices_s_length   F_path_separator_s_length
  #define F_path_tree_external_s_length  F_path_separator_s_length + 3
  #define F_path_tree_libraries_s_length F_path_separator_s_length
  #define F_path_tree_programs_s_length  F_path_separator_s_length
  #define F_path_tree_temporary_s_length F_path_separator_s_length
  #define F_path_tree_home_s_length      F_path_separator_s_length + 4
  #define F_path_tree_run_s_length       F_path_separator_s_length + 3
  #define F_path_tree_binary_s_length    F_path_separator_s_length + 7

  // FHS Root Level.
  #define F_path_tree_boot_s      F_path_separator_s "boot"
  #define F_path_tree_hardware_s  F_path_separator_s "dev"
  #define F_path_tree_processes_s F_path_separator_s "proc"
  #define F_path_tree_system_s    F_path_separator_s "sysfs"

  #define F_path_tree_boot_s_length      F_path_separator_s_length + 4
  #define F_path_tree_hardware_s_length  F_path_separator_s_length + 3
  #define F_path_tree_processes_s_length F_path_separator_s_length + 4
  #define F_path_tree_system_s_length    F_path_separator_s_length + 5

  // Program Level.
  #define F_path_tree_programs_public_s    F_path_separator_s "usr" F_path_separator_s "bin"
  #define F_path_tree_programs_system_s    F_path_separator_s "usr" F_path_separator_s "sbin"
  #define F_path_tree_programs_remote_s    F_path_separator_s "usr" F_path_separator_s "bin"
  #define F_path_tree_programs_services_s  F_path_separator_s "usr" F_path_separator_s "sbin"
  #define F_path_tree_programs_toolchain_s F_path_separator_s "usr" F_path_separator_s "bin"
  #define F_path_tree_programs_users_s     F_path_separator_s "usr" F_path_separator_s "local" F_path_separator_s "bin"
  #define F_path_tree_programs_susers_s    F_path_separator_s "usr" F_path_separator_s "local" F_path_separator_s "sbin"
  #define F_path_tree_programs_boot_s      F_path_separator_s "bin"
  #define F_path_tree_programs_sboot_s     F_path_separator_s "sbin"

  #define F_path_tree_programs_public_s_length    F_path_separator_s_length + F_path_separator_s_length + 6
  #define F_path_tree_programs_system_s_length    F_path_separator_s_length + F_path_separator_s_length + 7
  #define F_path_tree_programs_remote_s_length    F_path_separator_s_length + F_path_separator_s_length + 6
  #define F_path_tree_programs_services_s_length  F_path_separator_s_length + F_path_separator_s_length + 7
  #define F_path_tree_programs_toolchain_s_length F_path_separator_s_length + F_path_separator_s_length + 9
  #define F_path_tree_programs_users_s_length     F_path_separator_s_length + F_path_separator_s_length + 5
  #define F_path_tree_programs_susers_s_length    F_path_separator_s_length + F_path_separator_s_length + 5
  #define F_path_tree_programs_boot_s_length      F_path_separator_s_length + F_path_separator_s_length + 8
  #define F_path_tree_programs_sboot_s_length     F_path_separator_s_length + F_path_separator_s_length + 8

  // Library Level.
  #define F_path_tree_libraries_public_s    F_path_separator_s "usr" F_path_separator_s "lib"
  #define F_path_tree_libraries_system_s    F_path_separator_s "usr" F_path_separator_s "lib"
  #define F_path_tree_libraries_remote_s    F_path_separator_s "usr" F_path_separator_s "lib"
  #define F_path_tree_libraries_services_s  F_path_separator_s "usr" F_path_separator_s "lib"
  #define F_path_tree_libraries_toolchain_s F_path_separator_s "usr" F_path_separator_s "lib"
  #define F_path_tree_libraries_users_s     F_path_separator_s "usr" F_path_separator_s "local" F_path_separator_s "lib"
  #define F_path_tree_libraries_boot_s      F_path_separator_s "lib"

  #define F_path_tree_libraries_public_s_length    F_path_separator_s_length + F_path_separator_s_length + 6
  #define F_path_tree_libraries_system_s_length    F_path_separator_s_length + F_path_separator_s_length + 6
  #define F_path_tree_libraries_remote_s_length    F_path_separator_s_length + F_path_separator_s_length + 6
  #define F_path_tree_libraries_services_s_length  F_path_separator_s_length + F_path_separator_s_length + 6
  #define F_path_tree_libraries_toolchain_s_length F_path_separator_s_length + F_path_separator_s_length + 6
  #define F_path_tree_libraries_users_s_length     F_path_separator_s_length + F_path_separator_s_length + F_path_separator_s_length + 11
  #define F_path_tree_libraries_boot_s_length      F_path_separator_s_length + 3

  // Home Level.
  #define F_path_tree_home_services_s F_path_separator_s "srv"
  #define F_path_tree_home_share_s    F_path_separator_s
  #define F_path_tree_home_users_s    f_path_home_s
  #define F_path_tree_home_websites_s F_path_separator_s "srv" F_path_separator_s "www"

  #define F_path_tree_home_services_s_length F_path_separator_s_length + 3
  #define F_path_tree_home_share_s_length    F_path_separator_s_length
  #define F_path_tree_home_users_s_length    f_path_home_s_length
  #define F_path_tree_home_websites_s_length F_path_separator_s_length + F_path_separator_s_length + 6

  // System Level.
  #define F_path_tree_system_logs_s      F_path_separator_s "var" F_path_separator_s "log"
  #define F_path_tree_system_settings_s  F_path_separator_s "etc"
  #define F_path_tree_system_data_s      F_path_separator_s "usr" F_path_separator_s "share"
  #define F_path_tree_system_variables_s F_path_separator_s "var"

  #define F_path_tree_system_logs_s_length      F_path_separator_s_length + F_path_separator_s_length + 6
  #define F_path_tree_system_settings_s_length  F_path_separator_s_length + 3
  #define F_path_tree_system_data_s_length      F_path_separator_s_length + F_path_separator_s_length + 8
  #define F_path_tree_system_variables_s_length F_path_separator_s_length + 3

  // Temporary Level.
  #define F_path_tree_temporary_public_s    F_path_separator_s "tmp"
  #define F_path_tree_temporary_services_s  F_path_separator_s "tmp"
  #define F_path_tree_temporary_users_s     F_path_separator_s "tmp"
  #define F_path_tree_temporary_variables_s F_path_separator_s "var" F_path_separator_s "tmp"

  #define F_path_tree_temporary_public_s_length    F_path_separator_s_length 3
  #define F_path_tree_temporary_services_s_length  F_path_separator_s_length 3
  #define F_path_tree_temporary_users_s_length     F_path_separator_s_length 3
  #define F_path_tree_temporary_variables_s_length F_path_separator_s_length + F_path_separator_s_length + 6

  // Private User Directories.
  #define F_path_tree_user_downloads_s "downloads"
  #define F_path_tree_user_desktop_s   "desktop"
  #define F_path_tree_user_private_s   ""
  #define F_path_tree_user_settings_s  ""
  #define F_path_tree_user_data_s      ""
  #define F_path_tree_user_temporary_s ""
  #define F_path_tree_user_shared_s    ""

  #define F_path_tree_user_downloads_s_length 9
  #define F_path_tree_user_desktop_s_length   7
  #define F_path_tree_user_private_s_length   0
  #define F_path_tree_user_settings_s_length  0
  #define F_path_tree_user_data_s_length      0
  #define F_path_tree_user_temporary_s_length 0
  #define F_path_tree_user_shared_s_length    0
#endif // _di_f_path_tree_hierarchy_standard_d_

#if defined(_di_f_path_tree_s_) && !defined(_di_f_path_tree_hierarchy_standard_d_) && !defined(_di_f_path_tree_kevux_standard_d_)

  // KFS Root Level.
  #ifndef _di_f_path_tree_devices_s_
    extern const f_string_static_t f_path_tree_devices_s;
  #endif // _di_f_path_tree_devices_s_

  #ifndef _di_f_path_tree_external_s_
    extern const f_string_static_t f_path_tree_external_s;
  #endif // _di_f_path_tree_external_s_

  #ifndef _di_f_path_tree_libraries_s_
    extern const f_string_static_t f_path_tree_libraries_s;
  #endif // _di_f_path_tree_libraries_s_

  #ifndef _di_f_path_tree_programs_s_
    extern const f_string_static_t f_path_tree_programs_s;
  #endif // _di_f_path_tree_programs_s_

  #ifndef _di_f_path_tree_temporary_s_
    extern const f_string_static_t f_path_tree_temporary_s;
  #endif // _di_f_path_tree_temporary_s_

  #ifndef _di_f_path_tree_home_s_
    extern const f_string_static_t f_path_tree_home_s;
  #endif // _di_f_path_tree_home_s_

  #ifndef _di_f_path_tree_run_s_
    extern const f_string_static_t f_path_tree_run_s;
  #endif // _di_f_path_tree_run_s_

  #ifndef _di_f_path_tree_binary_s_
    extern const f_string_static_t f_path_tree_binary_s;
  #endif // _di_f_path_tree_binary_s_

  // FHS Root Level.
  #ifndef _di_f_path_tree_boot_s_
    extern const f_string_static_t f_path_tree_boot_s;
  #endif // _di_f_path_tree_boot_s_

  #ifndef _di_f_path_tree_hardware_s_
    extern const f_string_static_t f_path_tree_hardware_s;
  #endif // _di_f_path_tree_hardware_s_

  #ifndef _di_f_path_tree_processes_s_
    extern const f_string_static_t f_path_tree_processes_s;
  #endif // _di_f_path_tree_processes_s_

  #ifndef _di_f_path_tree_system_s_
    extern const f_string_static_t f_path_tree_system_s;
  #endif // _di_f_path_tree_system_s_

  // Program Level.
  #ifndef _di_f_path_tree_programs_public_s_
    extern const f_string_static_t f_path_tree_programs_public_s;
  #endif // _di_f_path_tree_programs_public_s_

  #ifndef _di_f_path_tree_programs_system_s_
    extern const f_string_static_t f_path_tree_programs_system_s;
  #endif // _di_f_path_tree_programs_system_s_

  #ifndef _di_f_path_tree_programs_remote_s_
    extern const f_string_static_t f_path_tree_programs_remote_s;
  #endif // _di_f_path_tree_programs_remote_s_

  #ifndef _di_f_path_tree_programs_services_s_
    extern const f_string_static_t f_path_tree_programs_services_s;
  #endif // _di_f_path_tree_programs_services_s_

  #ifndef _di_f_path_tree_programs_toolchain_s_
    extern const f_string_static_t f_path_tree_programs_toolchain_s;
  #endif // _di_f_path_tree_programs_toolchain_s_

  #ifndef _di_f_path_tree_programs_users_s_
    extern const f_string_static_t f_path_tree_programs_users_s;
  #endif // _di_f_path_tree_programs_users_s_

  #ifndef _di_f_path_tree_programs_susers_s_
    extern const f_string_static_t f_path_tree_programs_susers_s;
  #endif // _di_f_path_tree_programs_susers_s_

  #ifndef _di_f_path_tree_programs_boot_s_
    extern const f_string_static_t f_path_tree_programs_boot_s;
  #endif // _di_f_path_tree_programs_boot_s_

  #ifndef _di_f_path_tree_programs_sboot_s_
    extern const f_string_static_t f_path_tree_programs_sboot_s;
  #endif // _di_f_path_tree_programs_sboot_s_

  // Library Level.
  #ifndef _di_f_path_tree_libraries_public_s_
    extern const f_string_static_t f_path_tree_libraries_public_s;
  #endif // _di_f_path_tree_libraries_public_s_

  #ifndef _di_f_path_tree_libraries_system_s_
    extern const f_string_static_t f_path_tree_libraries_system_s;
  #endif // _di_f_path_tree_libraries_system_s_

  #ifndef _di_f_path_tree_libraries_remote_s_
    extern const f_string_static_t f_path_tree_libraries_remote_s;
  #endif // _di_f_path_tree_libraries_remote_s_

  #ifndef _di_f_path_tree_libraries_services_s_
    extern const f_string_static_t f_path_tree_libraries_services_s;
  #endif // _di_f_path_tree_libraries_services_s_

  #ifndef _di_f_path_tree_libraries_toolchain_s_
    extern const f_string_static_t f_path_tree_libraries_toolchain_s;
  #endif // _di_f_path_tree_libraries_toolchain_s_

  #ifndef _di_f_path_tree_libraries_users_s_
    extern const f_string_static_t f_path_tree_libraries_users_s;
  #endif // _di_f_path_tree_libraries_users_s_

  #ifndef _di_f_path_tree_libraries_boot_s_
    extern const f_string_static_t f_path_tree_libraries_boot_s;
  #endif // _di_f_path_tree_libraries_boot_s_

  // Home Level.
  #ifndef _di_f_path_tree_home_services_s_
    extern const f_string_static_t f_path_tree_home_services_s;
  #endif // _di_f_path_tree_home_services_s_

  #ifndef _di_f_path_tree_home_share_s_
    extern const f_string_static_t f_path_tree_home_share_s;
  #endif // _di_f_path_tree_home_share_s_

  #ifndef _di_f_path_tree_home_users_s_
    extern const f_string_static_t f_path_tree_home_users_s;
  #endif // _di_f_path_tree_home_users_s_

  #ifndef _di_f_path_tree_home_websites_s_
    extern const f_string_static_t f_path_tree_home_websites_s;
  #endif // _di_f_path_tree_home_websites_s_

  // System Level.
  #ifndef _di_f_path_tree_system_logs_s_
    extern const f_string_static_t f_path_tree_system_logs_s;
  #endif // _di_f_path_tree_system_logs_s_

  #ifndef _di_f_path_tree_system_settings_s_
    extern const f_string_static_t f_path_tree_system_settings_s;
  #endif // _di_f_path_tree_system_settings_s_

  #ifndef _di_f_path_tree_system_data_s_
    extern const f_string_static_t f_path_tree_system_data_s;
  #endif // _di_f_path_tree_system_data_s_

  #ifndef _di_f_path_tree_system_variables_s_
    extern const f_string_static_t f_path_tree_system_variables_s;
  #endif // _di_f_path_tree_system_variables_s_

  // Temporary Level.
  #ifndef _di_f_path_tree_temporary_public_s_
    extern const f_string_static_t f_path_tree_temporary_public_s;
  #endif // _di_f_path_tree_temporary_public_s_

  #ifndef _di_f_path_tree_temporary_services_s_
    extern const f_string_static_t f_path_tree_temporary_services_s;
  #endif // _di_f_path_tree_temporary_services_s_

  #ifndef _di_f_path_tree_temporary_users_s_
    extern const f_string_static_t f_path_tree_temporary_users_s;
  #endif // _di_f_path_tree_temporary_users_s_

  #ifndef _di_f_path_tree_temporary_variables_s_
    extern const f_string_static_t f_path_tree_temporary_variables_s;
  #endif // _di_f_path_tree_temporary_variables_s_

  // Private User Directories.
  #ifndef _di_f_path_user_downloads_s_
    extern const f_string_static_t f_path_user_downloads_s;
  #endif // _di_f_path_user_downloads_s_

  #ifndef _di_f_path_user_desktop_s_
    extern const f_string_static_t f_path_user_desktop_s;
  #endif // _di_f_path_user_desktop_s_

  #ifndef _di_f_path_user_private_s_
    extern const f_string_static_t f_path_user_private_s;
  #endif // _di_f_path_user_private_s_

  #ifndef _di_f_path_user_settings_s_
    extern const f_string_static_t f_path_user_settings_s;
  #endif // _di_f_path_user_settings_s_

  #ifndef _di_f_path_user_data_s_
    extern const f_string_static_t f_path_user_data_s;
  #endif // _di_f_path_user_data_s_

  #ifndef _di_f_path_user_temporary_s_
    extern const f_string_static_t f_path_user_temporary_s;
  #endif // _di_f_path_user_temporary_s_

  #ifndef _di_f_path_user_shared_s_
    extern const f_string_static_t f_path_user_shared_s;
  #endif // _di_f_path_user_shared_s_
#endif // defined(_di_f_path_tree_s_) && !defined(_di_f_path_tree_hierarchy_standard_d_) && !defined(_di_f_path_tree_kevux_standard_d_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_path_common_h
