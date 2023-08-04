#include "../control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_program_version_s_
  const f_string_static_t control_program_version_s = macro_f_string_static_t_initialize_1(CONTROL_program_version_s, 0, CONTROL_program_version_s_length);
#endif // _di_control_program_version_s_

#ifndef _di_control_program_name_s_
  const f_string_static_t control_program_name_s = macro_f_string_static_t_initialize_1(CONTROL_program_name_s, 0, CONTROL_program_name_s_length);
  const f_string_static_t control_program_name_long_s = macro_f_string_static_t_initialize_1(CONTROL_program_name_long_s, 0, CONTROL_program_name_long_s_length);
#endif // _di_control_program_name_s_

#ifndef _di_control_parameter_s_
  const f_string_static_t control_short_name_s = macro_f_string_static_t_initialize_1(CONTROL_short_name_s, 0, CONTROL_short_name_s_length);
  const f_string_static_t control_short_return_s = macro_f_string_static_t_initialize_1(CONTROL_short_return_s, 0, CONTROL_short_return_s_length);
  const f_string_static_t control_short_settings_s = macro_f_string_static_t_initialize_1(CONTROL_short_settings_s, 0, CONTROL_short_settings_s_length);
  const f_string_static_t control_short_socket_s = macro_f_string_static_t_initialize_1(CONTROL_short_socket_s, 0, CONTROL_short_socket_s_length);

  const f_string_static_t control_long_name_s = macro_f_string_static_t_initialize_1(CONTROL_long_name_s, 0, CONTROL_long_name_s_length);
  const f_string_static_t control_long_return_s = macro_f_string_static_t_initialize_1(CONTROL_long_return_s, 0, CONTROL_long_return_s_length);
  const f_string_static_t control_long_settings_s = macro_f_string_static_t_initialize_1(CONTROL_long_settings_s, 0, CONTROL_long_settings_s_length);
  const f_string_static_t control_long_socket_s = macro_f_string_static_t_initialize_1(CONTROL_long_socket_s, 0, CONTROL_long_socket_s_length);
#endif // _di_control_parameter_s_

#ifndef _di_control_strings_s_
  const f_string_static_t control_path_settings_s = macro_f_string_static_t_initialize_1(CONTROL_path_settings_s, 0, CONTROL_path_settings_s_length);

  const f_string_static_t control_action_s = macro_f_string_static_t_initialize_1(CONTROL_action_s, 0, CONTROL_action_s_length);
  const f_string_static_t control_at_s = macro_f_string_static_t_initialize_1(CONTROL_at_s, 0, CONTROL_at_s_length);
  const f_string_static_t control_controller_s = macro_f_string_static_t_initialize_1(CONTROL_controller_s, 0, CONTROL_controller_s_length);
  const f_string_static_t control_default_s = macro_f_string_static_t_initialize_1(CONTROL_default_s, 0, CONTROL_default_s_length);
  const f_string_static_t control_error_s = macro_f_string_static_t_initialize_1(CONTROL_error_s, 0, CONTROL_error_s_length);
  const f_string_static_t control_in_s = macro_f_string_static_t_initialize_1(CONTROL_in_s, 0, CONTROL_in_s_length);
  const f_string_static_t control_init_s = macro_f_string_static_t_initialize_1(CONTROL_init_s, 0, CONTROL_init_s_length);
  const f_string_static_t control_kexec_s = macro_f_string_static_t_initialize_1(CONTROL_kexec_s, 0, CONTROL_kexec_s_length);
  const f_string_static_t control_length_s = macro_f_string_static_t_initialize_1(CONTROL_length_s, 0, CONTROL_length_s_length);
  const f_string_static_t control_name_socket_s = macro_f_string_static_t_initialize_1(CONTROL_name_socket_s, 0, CONTROL_name_socket_s_length);
  const f_string_static_t control_now_s = macro_f_string_static_t_initialize_1(CONTROL_now_s, 0, CONTROL_now_s_length);
  const f_string_static_t control_path_socket_s = macro_f_string_static_t_initialize_1(CONTROL_path_socket_s, 0, CONTROL_path_socket_s_length);
  const f_string_static_t control_path_socket_prefix_s = macro_f_string_static_t_initialize_1(CONTROL_path_socket_prefix_s, 0, CONTROL_path_socket_prefix_s_length);
  const f_string_static_t control_path_socket_suffix_s = macro_f_string_static_t_initialize_1(CONTROL_path_socket_suffix_s, 0, CONTROL_path_socket_suffix_s_length);
  const f_string_static_t control_status_s = macro_f_string_static_t_initialize_1(CONTROL_status_s, 0, CONTROL_status_s_length);
  const f_string_static_t control_type_s = macro_f_string_static_t_initialize_1(CONTROL_type_s, 0, CONTROL_type_s_length);

  const f_string_static_t control_freeze_s = macro_f_string_static_t_initialize_1(CONTROL_freeze_s, 0, CONTROL_freeze_s_length);
  const f_string_static_t control_kill_s = macro_f_string_static_t_initialize_1(CONTROL_kill_s, 0, CONTROL_kill_s_length);
  const f_string_static_t control_pause_s = macro_f_string_static_t_initialize_1(CONTROL_pause_s, 0, CONTROL_pause_s_length);
  const f_string_static_t control_reboot_s = macro_f_string_static_t_initialize_1(CONTROL_reboot_s, 0, CONTROL_reboot_s_length);
  const f_string_static_t control_reload_s = macro_f_string_static_t_initialize_1(CONTROL_reload_s, 0, CONTROL_reload_s_length);
  const f_string_static_t control_rerun_s = macro_f_string_static_t_initialize_1(CONTROL_rerun_s, 0, CONTROL_rerun_s_length);
  const f_string_static_t control_restart_s = macro_f_string_static_t_initialize_1(CONTROL_restart_s, 0, CONTROL_restart_s_length);
  const f_string_static_t control_resume_s = macro_f_string_static_t_initialize_1(CONTROL_resume_s, 0, CONTROL_resume_s_length);
  const f_string_static_t control_shutdown_s = macro_f_string_static_t_initialize_1(CONTROL_shutdown_s, 0, CONTROL_shutdown_s_length);
  const f_string_static_t control_start_s = macro_f_string_static_t_initialize_1(CONTROL_start_s, 0, CONTROL_start_s_length);
  const f_string_static_t control_stop_s = macro_f_string_static_t_initialize_1(CONTROL_stop_s, 0, CONTROL_stop_s_length);
  const f_string_static_t control_thaw_s = macro_f_string_static_t_initialize_1(CONTROL_thaw_s, 0, CONTROL_thaw_s_length);
#endif // _di_control_strings_s_

#ifndef _di_controller_strings_s_
  const f_string_static_t controller_name_socket_s = macro_f_string_static_t_initialize_1(CONTROLLER_name_socket_s, 0, CONTROLLER_name_socket_s_length);
  const f_string_static_t controller_path_socket_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_socket_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_prefix_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_socket_prefix_s, 0, CONTROLLER_path_socket_prefix_s_length);
  const f_string_static_t controller_path_socket_suffix_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_socket_suffix_s, 0, CONTROLLER_path_socket_suffix_s_length);
#endif // _di_controller_strings_s_

#ifdef __cplusplus
} // extern "C"
#endif
