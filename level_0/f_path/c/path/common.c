#include "../path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_path_defines_
  const f_string_static_t f_path_separator_s = macro_f_string_static_t_initialize(F_string_ascii_slash_forward_s, 0, F_string_ascii_slash_forward_s_length);
  const f_string_static_t f_path_separator_current_s = macro_f_string_static_t_initialize(F_string_ascii_period_s, 0, F_string_ascii_period_s_length);
  const f_string_static_t f_path_separator_variable_s = macro_f_string_static_t_initialize(F_string_ascii_colon_s, 0, F_string_ascii_colon_s_length);

  const f_string_static_t f_path_extension_separator_s = macro_f_string_static_t_initialize(F_string_ascii_period_s, 0, F_string_ascii_period_s_length);

  const f_string_static_t f_path_environment_s = macro_f_string_static_t_initialize(F_path_environment_s, 0, F_path_environment_s_length);
  const f_string_static_t f_path_home_wildcard_s = macro_f_string_static_t_initialize(F_string_ascii_tilde_s, 0, F_string_ascii_tilde_s_length);
  const f_string_static_t f_path_present_working_s = macro_f_string_static_t_initialize(F_path_present_working_s, 0, F_path_present_working_s_length);
  const f_string_static_t f_path_present_working_old_s = macro_f_string_static_t_initialize(F_path_present_working_old_s, 0, F_path_present_working_old_s_length);
#endif // _di_f_path_defines_

#ifdef _di_path_tree_s_

  // KFS Root Level.
  const f_string_static_t f_path_tree_devices_s = macro_f_string_static_t_initialize(F_path_tree_devices_s, 0, F_path_tree_devices_s_length);
  const f_string_static_t f_path_tree_external_s = macro_f_string_static_t_initialize(F_path_tree_external_s, 0, F_path_tree_external_s_length);
  const f_string_static_t f_path_tree_libraries_s = macro_f_string_static_t_initialize(F_path_tree_libraries_s, 0, F_path_tree_libraries_s_length);
  const f_string_static_t f_path_tree_programs_s = macro_f_string_static_t_initialize(F_path_tree_programs_s, 0,F_path_tree_programs_s _length);
  const f_string_static_t f_path_tree_temporary_s = macro_f_string_static_t_initialize(F_path_tree_temporary_s, 0, F_path_tree_temporary_s_length);
  const f_string_static_t f_path_tree_home_s = macro_f_string_static_t_initialize(F_path_tree_home_s, 0, F_path_tree_home_s_length);
  const f_string_static_t f_path_tree_run_s = macro_f_string_static_t_initialize(F_path_tree_run_s, 0, F_path_tree_run_s_length);
  const f_string_static_t f_path_tree_binary_s = macro_f_string_static_t_initialize(F_path_tree_binary_s, 0, F_path_tree_binary_s_length);

  // FHS Root Level.
  const f_string_static_t f_path_tree_boot_s = macro_f_string_static_t_initialize(F_path_tree_boot_s, 0, F_path_tree_boot_s_length);
  const f_string_static_t f_path_tree_hardware_s = macro_f_string_static_t_initialize(F_path_tree_hardware_s, 0, F_path_tree_hardware_s_length);
  const f_string_static_t f_path_tree_processes_s = macro_f_string_static_t_initialize(F_path_tree_processes_s, 0, F_path_tree_processes_s_length);
  const f_string_static_t f_path_tree_system_s = macro_f_string_static_t_initialize(F_path_tree_system_s, 0, F_path_tree_system_s_length);

  // Program Level.
  const f_string_static_t f_path_tree_programs_public_s = macro_f_string_static_t_initialize(F_path_tree_programs_public_s, 0, F_path_tree_programs_public_s_length);
  const f_string_static_t f_path_tree_programs_system_s = macro_f_string_static_t_initialize(F_path_tree_programs_system_s, 0, F_path_tree_programs_system_s_length);
  const f_string_static_t f_path_tree_programs_remote_s = macro_f_string_static_t_initialize(F_path_tree_programs_remote_s, 0, F_path_tree_programs_remote_s_length);
  const f_string_static_t f_path_tree_programs_services_s = macro_f_string_static_t_initialize(F_path_tree_programs_services_s, 0, F_path_tree_programs_services_s_length);
  const f_string_static_t f_path_tree_programs_toolchain_s = macro_f_string_static_t_initialize(F_path_tree_programs_toolchain_s, 0, F_path_tree_programs_toolchain_s_length);
  const f_string_static_t f_path_tree_programs_users_s = macro_f_string_static_t_initialize(F_path_tree_programs_users_s, 0, F_path_tree_programs_users_s_length);
  const f_string_static_t f_path_tree_programs_susers_s = macro_f_string_static_t_initialize(F_path_tree_programs_susers_s, 0, F_path_tree_programs_susers_s_length);
  const f_string_static_t f_path_tree_programs_boot_s = macro_f_string_static_t_initialize(F_path_tree_programs_boot_s, 0, F_path_tree_programs_boot_s_length);
  const f_string_static_t f_path_tree_programs_sboot_s = macro_f_string_static_t_initialize(F_path_tree_programs_sboot_s, 0, F_path_tree_programs_sboot_s_length);

  // Library Level.
  const f_string_static_t f_path_tree_libraries_public_s = macro_f_string_static_t_initialize(F_path_tree_libraries_public_s, 0, F_path_tree_libraries_public_s_length);
  const f_string_static_t f_path_tree_libraries_system_s = macro_f_string_static_t_initialize(F_path_tree_libraries_system_s, 0, F_path_tree_libraries_system_s_length);
  const f_string_static_t f_path_tree_libraries_remote_s = macro_f_string_static_t_initialize(F_path_tree_libraries_remote_s, 0, F_path_tree_libraries_remote_s_length);
  const f_string_static_t f_path_tree_libraries_services_s = macro_f_string_static_t_initialize(F_path_tree_libraries_services_s, 0, F_path_tree_libraries_services_s_length);
  const f_string_static_t f_path_tree_libraries_toolchain_s = macro_f_string_static_t_initialize(F_path_tree_libraries_toolchain_s, 0, F_path_tree_libraries_toolchain_s_length);
  const f_string_static_t f_path_tree_libraries_users_s = macro_f_string_static_t_initialize(F_path_tree_libraries_users_s, 0, F_path_tree_libraries_users_s_length);
  const f_string_static_t f_path_tree_libraries_boot_s = macro_f_string_static_t_initialize(F_path_tree_libraries_boot_s, 0, F_path_tree_libraries_boot_s_length);

  // Home Level.
  const f_string_static_t f_path_tree_home_services_s = macro_f_string_static_t_initialize(F_path_tree_home_services_s, 0, F_path_tree_home_services_s_length);
  const f_string_static_t f_path_tree_home_share_s = macro_f_string_static_t_initialize(F_path_tree_home_share_s, 0, F_path_tree_home_share_s_length);
  const f_string_static_t f_path_tree_home_users_s = macro_f_string_static_t_initialize(F_path_tree_home_users_s, 0, F_path_tree_home_users_s_length);
  const f_string_static_t f_path_tree_home_websites_s = macro_f_string_static_t_initialize(F_path_tree_home_websites_s, 0, F_path_tree_home_websites_s_length);

  // System Level.
  const f_string_static_t f_path_tree_system_logs_s = macro_f_string_static_t_initialize(F_path_tree_system_logs_s, 0, F_path_tree_system_logs_s_length);
  const f_string_static_t f_path_tree_system_settings_s = macro_f_string_static_t_initialize(F_path_tree_system_settings_s, 0, F_path_tree_system_settings_s_length);
  const f_string_static_t f_path_tree_system_data_s = macro_f_string_static_t_initialize(F_path_tree_system_data_s, 0, F_path_tree_system_data_s_length);
  const f_string_static_t f_path_tree_system_variables_s = macro_f_string_static_t_initialize(F_path_tree_system_variables_s, 0, F_path_tree_system_variables_s_length);

  // Temporary Level.
  const f_string_static_t f_path_tree_temporary_public_s = macro_f_string_static_t_initialize(F_path_tree_temporary_public_s, 0, F_path_tree_temporary_public_s_length);
  const f_string_static_t f_path_tree_temporary_services_s = macro_f_string_static_t_initialize(F_path_tree_temporary_services_s, 0, F_path_tree_temporary_services_s_length);
  const f_string_static_t f_path_tree_temporary_users_s = macro_f_string_static_t_initialize(F_path_tree_temporary_users_s, 0, F_path_tree_temporary_users_s_length);
  const f_string_static_t f_path_tree_temporary_variables_s = macro_f_string_static_t_initialize(F_path_tree_temporary_variables_s, 0, F_path_tree_temporary_variables_s_length);

  // Private User Directories.
  const f_string_static_t f_path_user_downloads_s = macro_f_string_static_t_initialize(F_path_user_downloads_s, 0, F_path_user_downloads_s_length);
  const f_string_static_t f_path_user_desktop_s = macro_f_string_static_t_initialize(F_path_user_desktop_s, 0, F_path_user_desktop_s_length);
  const f_string_static_t f_path_user_private_s = macro_f_string_static_t_initialize(F_path_user_private_s, 0, F_path_user_private_s_length);
  const f_string_static_t f_path_user_settings_s = macro_f_string_static_t_initialize(F_path_user_settings_s, 0, F_path_user_settings_s_length);
  const f_string_static_t f_path_user_data_s = macro_f_string_static_t_initialize(F_path_user_data_s, 0, F_path_user_data_s_length);
  const f_string_static_t f_path_user_temporary_s = macro_f_string_static_t_initialize(F_path_user_temporary_s, 0, F_path_user_temporary_s_length);
  const f_string_static_t f_path_user_shared_s = macro_f_string_static_t_initialize(F_path_user_shared_s, 0, F_path_user_shared_s_length);
#endif // _di_path_tree_s_

#ifdef __cplusplus
} // extern "C"
#endif
