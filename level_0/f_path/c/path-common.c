#include "path.h"
#include "private-path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_path_defines_
  const f_string_t f_path_separator_s = F_string_ascii_slash_forward_s;
  const f_string_t f_path_separator_current_s = F_string_ascii_period_s;
  const f_string_t f_path_separator_variable_s = F_string_ascii_colon_s;

  const f_string_t f_path_extension_separator_s = F_string_ascii_period_s;

  const f_string_t f_path_environment_s = F_path_environment_s;
  const f_string_t f_path_home_wildcard_s = F_string_ascii_tilde_s;
  const f_string_t f_path_present_working_s = F_path_present_working_s;
  const f_string_t f_path_present_working_old_s = F_path_present_working_old_s;
#endif // _di_f_path_defines_

#ifdef _di_path_tree_s_

  // KFS Root Level
  extern const f_string_t f_path_tree_devices_s = F_path_tree_devices_s;
  extern const f_string_t f_path_tree_external_s = F_path_tree_external_s;
  extern const f_string_t f_path_tree_libraries_s = F_path_tree_libraries_s;
  extern const f_string_t f_path_tree_programs_s = F_path_tree_programs_s;
  extern const f_string_t f_path_tree_temporary_s = F_path_tree_temporary_s;
  extern const f_string_t f_path_tree_home_s = F_path_tree_home_s;
  extern const f_string_t f_path_tree_run_s = F_path_tree_run_s;
  extern const f_string_t f_path_tree_binary_s = F_path_tree_binary_s;

  // FHS Root Level
  extern const f_string_t f_path_tree_boot_s = F_path_tree_boot_s;
  extern const f_string_t f_path_tree_hardware_s = F_path_tree_hardware_s;
  extern const f_string_t f_path_tree_processes_s = F_path_tree_processes_s;
  extern const f_string_t f_path_tree_system_s = F_path_tree_system_s;

  // Program Level
  extern const f_string_t f_path_tree_programs_public_s = F_path_tree_programs_public_s;
  extern const f_string_t f_path_tree_programs_system_s = F_path_tree_programs_system_s;
  extern const f_string_t f_path_tree_programs_remote_s = F_path_tree_programs_remote_s;
  extern const f_string_t f_path_tree_programs_services_s = F_path_tree_programs_services_s;
  extern const f_string_t f_path_tree_programs_toolchain_s = F_path_tree_programs_toolchain_s;
  extern const f_string_t f_path_tree_programs_users_s = F_path_tree_programs_users_s;
  extern const f_string_t f_path_tree_programs_susers_s = F_path_tree_programs_susers_s;
  extern const f_string_t f_path_tree_programs_boot_s = F_path_tree_programs_boot_s;
  extern const f_string_t f_path_tree_programs_sboot_s = F_path_tree_programs_sboot_s;

  // Library Level
  extern const f_string_t f_path_tree_libraries_public_s = F_path_tree_libraries_public_s;
  extern const f_string_t f_path_tree_libraries_system_s = F_path_tree_libraries_system_s;
  extern const f_string_t f_path_tree_libraries_remote_s = F_path_tree_libraries_remote_s;
  extern const f_string_t f_path_tree_libraries_services_s = F_path_tree_libraries_services_s;
  extern const f_string_t f_path_tree_libraries_toolchain_s = F_path_tree_libraries_toolchain_s;
  extern const f_string_t f_path_tree_libraries_users_s = F_path_tree_libraries_users_s;
  extern const f_string_t f_path_tree_libraries_boot_s = F_path_tree_libraries_boot_s;

  // Home Level
  extern const f_string_t f_path_tree_home_services_s = F_path_tree_home_services_s;
  extern const f_string_t f_path_tree_home_share_s = F_path_tree_home_share_s;
  extern const f_string_t f_path_tree_home_users_s = F_path_tree_home_users_s;
  extern const f_string_t f_path_tree_home_websites_s = F_path_tree_home_websites_s;

  // System Level
  extern const f_string_t f_path_tree_system_logs_s = F_path_tree_system_logs_s;
  extern const f_string_t f_path_tree_system_settings_s = F_path_tree_system_settings_s;
  extern const f_string_t f_path_tree_system_data_s = F_path_tree_system_data_s;
  extern const f_string_t f_path_tree_system_variables_s = F_path_tree_system_variables_s;

  // Temporary Level
  extern const f_string_t f_path_tree_temporary_public_s = F_path_tree_temporary_public_s;
  extern const f_string_t f_path_tree_temporary_services_s = F_path_tree_temporary_services_s;
  extern const f_string_t f_path_tree_temporary_users_s = F_path_tree_temporary_users_s;
  extern const f_string_t f_path_tree_temporary_variables_s = F_path_tree_temporary_variables_s;

  // Private User Directories
  extern const f_string_t f_path_user_downloads_s = F_path_user_downloads_s;
  extern const f_string_t f_path_user_desktop_s = F_path_user_desktop_s;
  extern const f_string_t f_path_user_private_s = F_path_user_private_s;
  extern const f_string_t f_path_user_settings_s = F_path_user_settings_s;
  extern const f_string_t f_path_user_data_s = F_path_user_data_s;
  extern const f_string_t f_path_user_temporary_s = F_path_user_temporary_s;
  extern const f_string_t f_path_user_shared_s = F_path_user_shared_s;
#endif // _di_path_tree_s_

#ifdef __cplusplus
} // extern "C"
#endif
