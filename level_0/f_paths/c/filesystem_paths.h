/* FLL - Level 0
 * Project:       Paths
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide locations to all filesystem paths, for low level hardcoding
 *
 * FIXME: this is very outdated due to numerous structural changes while I was developing turtle kevux
 */
#ifndef _F_filesystem_paths_h
#define _F_filesystem_paths_h

#ifdef __cplusplus
extern "C" {
#endif

// KFS Filesystem Paths
#ifdef _di_kevux_standard_paths_
  // disable the FHS default paths
  #define _di_filesystem_hierarch_standard_paths_

  // KFS Root Level
  #define f_path_devices    "/devices"
  #define f_path_external   "/external"
  #define f_path_libraries  "/libraries"
  #define f_path_programs   "/programs"
  #define f_path_temporary  "/temporary"
  #define f_path_home       "/home"
  #define f_path_run        "/run"
  #define f_path_binary     "/.system"

  // Kernel Level
  #define f_path_boot       f_path_devices"/boot"
  #define f_path_hardware   f_path_devices"/devices"
  #define f_path_processes  f_path_devices"/processes"
  #define f_path_system     f_path_devices"/system"

  // Program Level
  #define f_path_programs_public     f_path_programs"/public"
  #define f_path_programs_system     f_path_programs"/system"
  #define f_path_programs_remote     f_path_programs"/remote"
  #define f_path_programs_services   f_path_programs"/targets"
  #define f_path_programs_toolchain  f_path_programs"/toolchain"
  #define f_path_programs_users      f_path_programs"/users"
  #define f_path_programs_susers     f_path_programs"/users"
  #define f_path_programs_boot       f_path_boot"/programs"
  #define f_path_programs_sboot      f_path_boot"/programs"

  // Library Level
  #define f_path_libraries_public     f_path_libraries"/public"
  #define f_path_libraries_system     f_path_libraries"/system"
  #define f_path_libraries_remote     f_path_libraries"/remote"
  #define f_path_libraries_services   f_path_libraries"/targets"
  #define f_path_libraries_toolchain  f_path_libraries"/toolchain"
  #define f_path_libraries_users      f_path_libraries"/users"
  #define f_path_libraries_boot       f_path_boot"/libraries"

  // Home Level
  #define f_path_home_services  f_path_home"/services"
  #define f_path_home_share     f_path_home"/share"
  #define f_path_home_users     f_path_home"/users"
  #define f_path_home_websites  f_path_home"/websites"

  // System Level
  #define f_path_system_logs       f_path_system"/logs"
  #define f_path_system_settings   f_path_system"/settings"
  #define f_path_system_data       f_path_system"/data"
  #define f_path_system_variables  f_path_system"/variables" // for backwards FHS support only, use of this directory is considered bad practice for KFS, use f_path_temporary_variables instead

  // Temporary Level
  #define f_path_temporary_public     f_path_temporary"/public"
  #define f_path_temporary_services   f_path_temporary"/services"
  #define f_path_temporary_users      f_path_temporary"/users"
  #define f_path_temporary_variables  f_path_temporary"/variables"

  // Private User Directories
  #define f_path_user_downloads  "downloads"
  #define f_path_user_desktop    "desktop"
  #define f_path_user_private    "private"
  #define f_path_user_settings   "settings"
  #define f_path_user_data       "data"
  #define f_path_user_temporary  "temporary"
  #define f_path_user_shared     "shared"
#endif // _di_kevux_standard_paths_

// FHS Filesystem Paths
#ifndef _di_filesystem_hierarch_standard_paths_
  // disable the kevux standard default paths
  #define _di_kevux_standard_paths_

  // KFS Root Level
  #define f_path_devices    "/"
  #define f_path_external   "/mnt"
  #define f_path_libraries  "/"
  #define f_path_programs   "/"
  #define f_path_temporary  "/"
  #define f_path_home       "/home"
  #define f_path_run        "/run"
  #define f_path_binary     "/.system"

  // FHS Root Level
  #define f_path_boot       "/boot"
  #define f_path_hardware   "/dev"
  #define f_path_processes  "/proc"
  #define f_path_system     "/sysfs"

  // Program Level
  #define f_path_programs_public     "/usr/bin"
  #define f_path_programs_system     "/usr/sbin"
  #define f_path_programs_remote     "/usr/bin"
  #define f_path_programs_services   "/usr/sbin"
  #define f_path_programs_toolchain  "/usr/bin"
  #define f_path_programs_users      "/usr/local/bin"
  #define f_path_programs_susers     "/usr/local/sbin"
  #define f_path_programs_boot       "/bin"
  #define f_path_programs_sboot      "/sbin"

  // Library Level
  #define f_path_libraries_public     "/usr/lib"
  #define f_path_libraries_system     "/usr/lib"
  #define f_path_libraries_remote     "/usr/lib"
  #define f_path_libraries_services   "/usr/lib"
  #define f_path_libraries_toolchain  "/usr/lib"
  #define f_path_libraries_users      "/usr/local/lib"
  #define f_path_libraries_boot       "/lib"

  // Home Level
  #define f_path_home_services  "/srv"
  #define f_path_home_share     "/"
  #define f_path_home_users     f_path_home
  #define f_path_home_websites  "/srv/www"

  // System Level
  #define f_path_system_logs       "/var/log"
  #define f_path_system_settings   "/etc"
  #define f_path_system_data       "/usr/share"
  #define f_path_system_variables  "/var"

  // Temporary Level
  #define f_path_temporary_public     "/tmp"
  #define f_path_temporary_services   "/tmp"
  #define f_path_temporary_users      "/tmp"
  #define f_path_temporary_variables  "/var/tmp"

  // Private User Directories
  #define f_path_user_downloads  "downloads"
  #define f_path_user_desktop    "desktop"
  #define f_path_user_private    ""
  #define f_path_user_settings   ""
  #define f_path_user_data       ""
  #define f_path_user_temporary  ""
  #define f_path_user_shared     ""
#endif // _di_filesystem_hierarch_standard_paths_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_filesystem_paths_h
