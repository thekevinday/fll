#include "control.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_strings_
  const f_string_static_t controller_name_socket_s = macro_f_string_static_t_initialize(CONTROLLER_name_socket_s, 0, CONTROLLER_name_socket_s_length);
  const f_string_static_t controller_path_socket_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_prefix_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_prefix_s, 0, CONTROLLER_path_socket_prefix_s_length);
  const f_string_static_t controller_path_socket_suffix_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_suffix_s, 0, CONTROLLER_path_socket_suffix_s_length);
#endif // _di_controller_strings_

#ifndef _di_control_strings_s_
  const f_string_static_t control_path_settings_s = macro_f_string_static_t_initialize(CONTROL_path_settings_s, 0, CONTROL_path_settings_s_length);

  const f_string_static_t control_action_s = macro_f_string_static_t_initialize(CONTROL_action_s, 0, CONTROL_action_s_length);
  const f_string_static_t control_controller_s = macro_f_string_static_t_initialize(CONTROL_controller_s, 0, CONTROL_controller_s_length);
  const f_string_static_t control_default_s = macro_f_string_static_t_initialize(CONTROL_default_s, 0, CONTROL_default_s_length);
  const f_string_static_t control_error_s = macro_f_string_static_t_initialize(CONTROL_error_s, 0, CONTROL_error_s_length);
  const f_string_static_t control_init_s = macro_f_string_static_t_initialize(CONTROL_init_s, 0, CONTROL_init_s_length);
  const f_string_static_t control_kexec_s = macro_f_string_static_t_initialize(CONTROL_kexec_s, 0, CONTROL_kexec_s_length);
  const f_string_static_t control_length_s = macro_f_string_static_t_initialize(CONTROL_length_s, 0, CONTROL_length_s_length);
  const f_string_static_t control_name_socket_s = macro_f_string_static_t_initialize(CONTROL_name_socket_s, 0, CONTROL_name_socket_s_length);
  const f_string_static_t control_path_socket_s = macro_f_string_static_t_initialize(CONTROL_path_socket_s, 0, CONTROL_path_socket_s_length);
  const f_string_static_t control_path_socket_prefix_s = macro_f_string_static_t_initialize(CONTROL_path_socket_prefix_s, 0, CONTROL_path_socket_prefix_s_length);
  const f_string_static_t control_path_socket_suffix_s = macro_f_string_static_t_initialize(CONTROL_path_socket_suffix_s, 0, CONTROL_path_socket_suffix_s_length);
  const f_string_static_t control_status_s = macro_f_string_static_t_initialize(CONTROL_status_s, 0, CONTROL_status_s_length);
  const f_string_static_t control_type_s = macro_f_string_static_t_initialize(CONTROL_type_s, 0, CONTROL_type_s_length);

  const f_string_static_t control_freeze_s = macro_f_string_static_t_initialize(CONTROL_freeze_s, 0, CONTROL_freeze_s_length);
  const f_string_static_t control_kill_s = macro_f_string_static_t_initialize(CONTROL_kill_s, 0, CONTROL_kill_s_length);
  const f_string_static_t control_pause_s = macro_f_string_static_t_initialize(CONTROL_pause_s, 0, CONTROL_pause_s_length);
  const f_string_static_t control_reboot_s = macro_f_string_static_t_initialize(CONTROL_reboot_s, 0, CONTROL_reboot_s_length);
  const f_string_static_t control_reload_s = macro_f_string_static_t_initialize(CONTROL_reload_s, 0, CONTROL_reload_s_length);
  const f_string_static_t control_rerun_s = macro_f_string_static_t_initialize(CONTROL_rerun_s, 0, CONTROL_rerun_s_length);
  const f_string_static_t control_restart_s = macro_f_string_static_t_initialize(CONTROL_restart_s, 0, CONTROL_restart_s_length);
  const f_string_static_t control_resume_s = macro_f_string_static_t_initialize(CONTROL_resume_s, 0, CONTROL_resume_s_length);
  const f_string_static_t control_shutdown_s = macro_f_string_static_t_initialize(CONTROL_shutdown_s, 0, CONTROL_shutdown_s_length);
  const f_string_static_t control_start_s = macro_f_string_static_t_initialize(CONTROL_start_s, 0, CONTROL_start_s_length);
  const f_string_static_t control_stop_s = macro_f_string_static_t_initialize(CONTROL_stop_s, 0, CONTROL_stop_s_length);
  const f_string_static_t control_thaw_s = macro_f_string_static_t_initialize(CONTROL_thaw_s, 0, CONTROL_thaw_s_length);
#endif // _di_control_strings_s_

#ifndef _di_control_data_delete_
  void control_data_delete(control_data_t * const data) {

    f_string_dynamic_resize(0, &data->cache.large);
    f_string_dynamic_resize(0, &data->cache.small);
    f_string_dynamic_resize(0, &data->cache.packet);

    f_string_ranges_resize(0, &data->cache.packet_objects);
    f_string_rangess_resize(0, &data->cache.packet_contents);

    f_string_ranges_resize(0, &data->cache.header_objects);
    f_string_rangess_resize(0, &data->cache.header_contents);

    f_array_lengths_resize(0, &data->cache.delimits);
  }
#endif // _di_control_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif
