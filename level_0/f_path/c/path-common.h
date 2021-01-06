/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgplv2.1
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
#ifndef _di_f_path_defines_
  #define f_path_separator          f_string_ascii_slash_forward
  #define f_path_separator_current  f_string_ascii_period
  #define f_path_separator_variable f_string_ascii_colon

  #define f_path_separator_length          1
  #define f_path_separator_current_length  1
  #define f_path_separator_variable_length 1

  #define f_path_extension_separator f_string_ascii_period

  #define f_path_extension_separator_length 1

  #define f_path_environment         "PATH"
  #define f_path_home_wildcard       f_string_ascii_tilde
  #define f_path_present_working     "PWD"
  #define f_path_present_working_old "OLDPWD"

  #define f_path_environment_length         4
  #define f_path_home_wildcard_length       1
  #define f_path_present_working_length     3
  #define f_path_present_working_old_length 6

  #define f_path_length_max PATH_MAX

  extern const f_string_t f_path_separator_s;
  extern const f_string_t f_path_separator_current_s;
  extern const f_string_t f_path_separator_variable_s;

  extern const f_string_t f_path_extension_separator_s;

  extern const f_string_t f_path_environment_s;
  extern const f_string_t f_path_home_wildcard_s;
  extern const f_string_t f_path_present_working_s;
  extern const f_string_t f_path_present_working_old_s;
#endif // _di_f_path_defines_

/**
 * KFS Filesystem Paths
 * @todo outdated, needs to be updated.
 */
#ifndef _di_path_tree_kevux_standard_

  // disable the FHS default paths
  #define _di_path_tree_hierarchy_standard_

  // KFS Root Level
  #define f_path_tree_devices   f_path_separator "devices"
  #define f_path_tree_external  f_path_separator "external"
  #define f_path_tree_libraries f_path_separator "libraries"
  #define f_path_tree_programs  f_path_separator "programs"
  #define f_path_tree_temporary f_path_separator "temporary"
  #define f_path_tree_home      f_path_separator "home"
  #define f_path_tree_run       f_path_separator "run"
  #define f_path_tree_binary    f_path_separator ".system"

  // Kernel Level
  #define f_path_tree_boot      f_path_devices f_path_separator "boot"
  #define f_path_tree_hardware  f_path_devices f_path_separator "devices"
  #define f_path_tree_processes f_path_devices f_path_separator "processes"
  #define f_path_tree_system    f_path_devices f_path_separator "system"

  // Program Level
  #define f_path_tree_programs_public    f_path_programs f_path_separator "public"
  #define f_path_tree_programs_system    f_path_programs f_path_separator "system"
  #define f_path_tree_programs_remote    f_path_programs f_path_separator "remote"
  #define f_path_tree_programs_services  f_path_programs f_path_separator "targets"
  #define f_path_tree_programs_toolchain f_path_programs f_path_separator "toolchain"
  #define f_path_tree_programs_users     f_path_programs f_path_separator "users"
  #define f_path_tree_programs_susers    f_path_programs f_path_separator "users"
  #define f_path_tree_programs_boot      f_path_boot f_path_separator "programs"
  #define f_path_tree_programs_sboot     f_path_boot f_path_separator "programs"

  // Library Level
  #define f_path_tree_libraries_public    f_path_libraries f_path_separator "public"
  #define f_path_tree_libraries_system    f_path_libraries f_path_separator "system"
  #define f_path_tree_libraries_remote    f_path_libraries f_path_separator "remote"
  #define f_path_tree_libraries_services  f_path_libraries f_path_separator "targets"
  #define f_path_tree_libraries_toolchain f_path_libraries f_path_separator "toolchain"
  #define f_path_tree_libraries_users     f_path_libraries f_path_separator "users"
  #define f_path_tree_libraries_boot      f_path_boot f_path_separator "libraries"

  // Home Level
  #define f_path_tree_home_services f_path_home f_path_separator "services"
  #define f_path_tree_home_share    f_path_home f_path_separator "share"
  #define f_path_tree_home_users    f_path_home f_path_separator "users"
  #define f_path_tree_home_websites f_path_home f_path_separator "websites"

  // System Level
  #define f_path_tree_system_logs      f_path_system f_path_separator "logs"
  #define f_path_tree_system_settings  f_path_system f_path_separator "settings"
  #define f_path_tree_system_data      f_path_system f_path_separator "data"
  #define f_path_tree_system_variables f_path_system f_path_separator "variables" // for backwards FHS support only, use of this directory is considered bad practice for KFS, use f_path_temporary_variables instead

  // Temporary Level
  #define f_path_tree_temporary_public    f_path_temporary f_path_separator "public"
  #define f_path_tree_temporary_services  f_path_temporary f_path_separator "services"
  #define f_path_tree_temporary_users     f_path_temporary f_path_separator "users"
  #define f_path_tree_temporary_variables f_path_temporary f_path_separator "variables"

  // Private User Directories
  #define f_path_tree_user_downloads "downloads"
  #define f_path_tree_user_desktop   "desktop"
  #define f_path_tree_user_private   "private"
  #define f_path_tree_user_settings  "settings"
  #define f_path_tree_user_data      "data"
  #define f_path_tree_user_temporary "temporary"
  #define f_path_tree_user_shared    "shared"
#endif // _di_path_tree_kevux_standard_

/**
 * FHS Filesystem Paths
 * @todo outdated, needs to be updated.
 */
#ifndef _di_path_tree_hierarchy_standard_

  // disable the kevux standard default paths
  #define _di_path_tree_kevux_standard_

  // KFS Root Level
  #define f_path_tree_devices   f_path_separator
  #define f_path_tree_external  f_path_separator "mnt"
  #define f_path_tree_libraries f_path_separator
  #define f_path_tree_programs  f_path_separator
  #define f_path_tree_temporary f_path_separator
  #define f_path_tree_home      f_path_separator "home"
  #define f_path_tree_run       f_path_separator "run"
  #define f_path_tree_binary    f_path_separator ".system"

  // FHS Root Level
  #define f_path_tree_boot      f_path_separator "boot"
  #define f_path_tree_hardware  f_path_separator "dev"
  #define f_path_tree_processes f_path_separator "proc"
  #define f_path_tree_system    f_path_separator "sysfs"

  // Program Level
  #define f_path_tree_programs_public    f_path_separator "usr" f_path_separator "bin"
  #define f_path_tree_programs_system    f_path_separator "usr" f_path_separator "sbin"
  #define f_path_tree_programs_remote    f_path_separator "usr" f_path_separator "bin"
  #define f_path_tree_programs_services  f_path_separator "usr" f_path_separator "sbin"
  #define f_path_tree_programs_toolchain f_path_separator "usr" f_path_separator "bin"
  #define f_path_tree_programs_users     f_path_separator "usr" f_path_separator "local" f_path_separator "bin"
  #define f_path_tree_programs_susers    f_path_separator "usr" f_path_separator "local" f_path_separator "sbin"
  #define f_path_tree_programs_boot      f_path_separator "bin"
  #define f_path_tree_programs_sboot     f_path_separator "sbin"

  // Library Level
  #define f_path_tree_libraries_public    f_path_separator "usr" f_path_separator "lib"
  #define f_path_tree_libraries_system    f_path_separator "usr" f_path_separator "lib"
  #define f_path_tree_libraries_remote    f_path_separator "usr" f_path_separator "lib"
  #define f_path_tree_libraries_services  f_path_separator "usr" f_path_separator "lib"
  #define f_path_tree_libraries_toolchain f_path_separator "usr" f_path_separator "lib"
  #define f_path_tree_libraries_users     f_path_separator "usr" f_path_separator "local" f_path_separator "lib"
  #define f_path_tree_libraries_boot      f_path_separator "lib"

  // Home Level
  #define f_path_tree_home_services f_path_separator "srv"
  #define f_path_tree_home_share    f_path_separator ""
  #define f_path_tree_home_users    f_path_home
  #define f_path_tree_home_websites f_path_separator "srv" f_path_separator "www"

  // System Level
  #define f_path_tree_system_logs      f_path_separator "var" f_path_separator "log"
  #define f_path_tree_system_settings  f_path_separator "etc"
  #define f_path_tree_system_data      f_path_separator "usr" f_path_separator "share"
  #define f_path_tree_system_variables f_path_separator "var"

  // Temporary Level
  #define f_path_tree_temporary_public    f_path_separator "tmp"
  #define f_path_tree_temporary_services  f_path_separator "tmp"
  #define f_path_tree_temporary_users     f_path_separator "tmp"
  #define f_path_tree_temporary_variables f_path_separator "var" f_path_separator "tmp"

  // Private User Directories
  #define f_path_tree_user_downloads "downloads"
  #define f_path_tree_user_desktop   "desktop"
  #define f_path_tree_user_private   ""
  #define f_path_tree_user_settings  ""
  #define f_path_tree_user_data      ""
  #define f_path_tree_user_temporary ""
  #define f_path_tree_user_shared    ""
#endif // _di_path_tree_hierarchy_standard_

#ifdef _di_path_tree_s_

  // KFS Root Level
  extern const f_string_t f_path_tree_devices;
  extern const f_string_t f_path_tree_external;
  extern const f_string_t f_path_tree_libraries;
  extern const f_string_t f_path_tree_programs;
  extern const f_string_t f_path_tree_temporary;
  extern const f_string_t f_path_tree_home;
  extern const f_string_t f_path_tree_run;
  extern const f_string_t f_path_tree_binary;

  // FHS Root Level
  extern const f_string_t f_path_tree_boot;
  extern const f_string_t f_path_tree_hardware;
  extern const f_string_t f_path_tree_processes;
  extern const f_string_t f_path_tree_system;

  // Program Level
  extern const f_string_t f_path_tree_programs_public;
  extern const f_string_t f_path_tree_programs_system;
  extern const f_string_t f_path_tree_programs_remote;
  extern const f_string_t f_path_tree_programs_services;
  extern const f_string_t f_path_tree_programs_toolchain;
  extern const f_string_t f_path_tree_programs_users;
  extern const f_string_t f_path_tree_programs_susers;
  extern const f_string_t f_path_tree_programs_boot;
  extern const f_string_t f_path_tree_programs_sboot;

  // Library Level
  extern const f_string_t f_path_tree_libraries_public;
  extern const f_string_t f_path_tree_libraries_system;
  extern const f_string_t f_path_tree_libraries_remote;
  extern const f_string_t f_path_tree_libraries_services;
  extern const f_string_t f_path_tree_libraries_toolchain;
  extern const f_string_t f_path_tree_libraries_users;
  extern const f_string_t f_path_tree_libraries_boot;

  // Home Level
  extern const f_string_t f_path_tree_home_services;
  extern const f_string_t f_path_tree_home_share;
  extern const f_string_t f_path_tree_home_users;
  extern const f_string_t f_path_tree_home_websites;

  // System Level
  extern const f_string_t f_path_tree_system_logs;
  extern const f_string_t f_path_tree_system_settings;
  extern const f_string_t f_path_tree_system_data;
  extern const f_string_t f_path_tree_system_variables;

  // Temporary Level
  extern const f_string_t f_path_tree_temporary_public;
  extern const f_string_t f_path_tree_temporary_services;
  extern const f_string_t f_path_tree_temporary_users;
  extern const f_string_t f_path_tree_temporary_variables;

  // Private User Directories
  extern const f_string_t f_path_user_downloads;
  extern const f_string_t f_path_user_desktop;
  extern const f_string_t f_path_user_private;
  extern const f_string_t f_path_user_settings;
  extern const f_string_t f_path_user_data;
  extern const f_string_t f_path_user_temporary;
  extern const f_string_t f_path_user_shared;
#endif // _di_path_tree_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_path_common_h
