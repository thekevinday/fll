#include "path.h"
#include "private-path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_path_defines_
  const f_string_t f_path_separator_s = f_string_ascii_slash_forward;
  const f_string_t f_path_separator_current_s = f_string_ascii_period;
  const f_string_t f_path_separator_variable_s = f_string_ascii_colon;

  const f_string_t f_path_extension_separator_s = f_string_ascii_period;

  const f_string_t f_path_environment_s = f_path_environment;
  const f_string_t f_path_home_wildcard_s = f_string_ascii_tilde;
  const f_string_t f_path_present_working_s = f_path_present_working;
  const f_string_t f_path_present_working_old_s = f_path_present_working_old;
#endif // _di_f_path_defines_

#ifdef _di_path_tree_s_

  // KFS Root Level
  extern const f_string_t f_path_tree_devices_s = f_path_tree_devices;
  extern const f_string_t f_path_tree_external_s = f_path_tree_external;
  extern const f_string_t f_path_tree_libraries_s = f_path_tree_libraries;
  extern const f_string_t f_path_tree_programs_s = f_path_tree_programs;
  extern const f_string_t f_path_tree_temporary_s = f_path_tree_temporary;
  extern const f_string_t f_path_tree_home_s = f_path_tree_home;
  extern const f_string_t f_path_tree_run_s = f_path_tree_run;
  extern const f_string_t f_path_tree_binary_s = f_path_tree_binary;

  // FHS Root Level
  extern const f_string_t f_path_tree_boot_s = f_path_tree_boot;
  extern const f_string_t f_path_tree_hardware_s = f_path_tree_hardware;
  extern const f_string_t f_path_tree_processes_s = f_path_tree_processes;
  extern const f_string_t f_path_tree_system_s = f_path_tree_system;

  // Program Level
  extern const f_string_t f_path_tree_programs_public_s = f_path_tree_programs_public;
  extern const f_string_t f_path_tree_programs_system_s = f_path_tree_programs_system;
  extern const f_string_t f_path_tree_programs_remote_s = f_path_tree_programs_remote;
  extern const f_string_t f_path_tree_programs_services_s = f_path_tree_programs_services;
  extern const f_string_t f_path_tree_programs_toolchain_s = f_path_tree_programs_toolchain;
  extern const f_string_t f_path_tree_programs_users_s = f_path_tree_programs_users;
  extern const f_string_t f_path_tree_programs_susers_s = f_path_tree_programs_susers;
  extern const f_string_t f_path_tree_programs_boot_s = f_path_tree_programs_boot;
  extern const f_string_t f_path_tree_programs_sboot_s = f_path_tree_programs_sboot;

  // Library Level
  extern const f_string_t f_path_tree_libraries_public_s = f_path_tree_libraries_public;
  extern const f_string_t f_path_tree_libraries_system_s = f_path_tree_libraries_system;
  extern const f_string_t f_path_tree_libraries_remote_s = f_path_tree_libraries_remote;
  extern const f_string_t f_path_tree_libraries_services_s = f_path_tree_libraries_services;
  extern const f_string_t f_path_tree_libraries_toolchain_s = f_path_tree_libraries_toolchain;
  extern const f_string_t f_path_tree_libraries_users_s = f_path_tree_libraries_users;
  extern const f_string_t f_path_tree_libraries_boot_s = f_path_tree_libraries_boot;

  // Home Level
  extern const f_string_t f_path_tree_home_services_s = f_path_tree_home_services;
  extern const f_string_t f_path_tree_home_share_s = f_path_tree_home_share;
  extern const f_string_t f_path_tree_home_users_s = f_path_tree_home_users;
  extern const f_string_t f_path_tree_home_websites_s = f_path_tree_home_websites;

  // System Level
  extern const f_string_t f_path_tree_system_logs_s = f_path_tree_system_logs;
  extern const f_string_t f_path_tree_system_settings_s = f_path_tree_system_settings;
  extern const f_string_t f_path_tree_system_data_s = f_path_tree_system_data;
  extern const f_string_t f_path_tree_system_variables_s = f_path_tree_system_variables;

  // Temporary Level
  extern const f_string_t f_path_tree_temporary_public_s = f_path_tree_temporary_public;
  extern const f_string_t f_path_tree_temporary_services_s = f_path_tree_temporary_services;
  extern const f_string_t f_path_tree_temporary_users_s = f_path_tree_temporary_users;
  extern const f_string_t f_path_tree_temporary_variables_s = f_path_tree_temporary_variables;

  // Private User Directories
  extern const f_string_t f_path_user_downloads_s = f_path_user_downloads;
  extern const f_string_t f_path_user_desktop_s = f_path_user_desktop;
  extern const f_string_t f_path_user_private_s = f_path_user_private;
  extern const f_string_t f_path_user_settings_s = f_path_user_settings;
  extern const f_string_t f_path_user_data_s = f_path_user_data;
  extern const f_string_t f_path_user_temporary_s = f_path_user_temporary;
  extern const f_string_t f_path_user_shared_s = f_path_user_shared;
#endif // _di_path_tree_s_

#ifdef __cplusplus
} // extern "C"
#endif
