#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_version_
  const f_string_static_t controller_program_version_s = macro_f_string_static_t_initialize(CONTROLLER_program_version_s, 0, CONTROLLER_program_version_s_length);
#endif // _di_controller_program_version_

#ifndef _di_controller_program_name_
  const f_string_static_t controller_program_name_s = macro_f_string_static_t_initialize(CONTROLLER_program_name_s, 0, CONTROLLER_program_name_s_length);
  const f_string_static_t controller_program_name_long_s = macro_f_string_static_t_initialize(CONTROLLER_program_name_long_s, 0, CONTROLLER_program_name_long_s_length);

  const f_string_static_t controller_program_name_init_s = macro_f_string_static_t_initialize(CONTROLLER_program_name_init_s, 0, CONTROLLER_program_name_init_s_length);
  const f_string_static_t controller_program_name_init_long_s = macro_f_string_static_t_initialize(CONTROLLER_program_name_init_long_s, 0, CONTROLLER_program_name_init_long_s_length);
#endif // _di_controller_program_name_

#ifndef _di_controller_defines_
  const f_string_static_t controller_default_program_script_s = macro_f_string_static_t_initialize(CONTROLLER_default_program_script_s, 0, CONTROLLER_default_program_script_s_length);
  const f_string_static_t controller_path_pid_s = macro_f_string_static_t_initialize(CONTROLLER_path_pid_s, 0, CONTROLLER_path_pid_s_length);
  const f_string_static_t controller_path_pid_init_s = macro_f_string_static_t_initialize(CONTROLLER_path_pid_init_s, 0, CONTROLLER_path_pid_init_s_length);
  const f_string_static_t controller_path_pid_prefix_s = macro_f_string_static_t_initialize(CONTROLLER_path_pid_prefix_s, 0, CONTROLLER_path_pid_prefix_s_length);
  const f_string_static_t controller_path_pid_suffix_s = macro_f_string_static_t_initialize(CONTROLLER_path_pid_suffix_s, 0, CONTROLLER_path_pid_suffix_s_length);
  const f_string_static_t controller_path_settings_s = macro_f_string_static_t_initialize(CONTROLLER_path_settings_s, 0, CONTROLLER_path_settings_s_length);
  const f_string_static_t controller_path_settings_init_s = macro_f_string_static_t_initialize(CONTROLLER_path_settings_init_s, 0, CONTROLLER_path_settings_init_s_length);
  const f_string_static_t controller_path_socket_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_init_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_init_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_prefix_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_prefix_s, 0, CONTROLLER_path_socket_prefix_s_length);
  const f_string_static_t controller_path_socket_suffix_s = macro_f_string_static_t_initialize(CONTROLLER_path_socket_suffix_s, 0, CONTROLLER_path_socket_suffix_s_length);

  const f_string_static_t controller_short_cgroup_s = macro_f_string_static_t_initialize(CONTROLLER_short_cgroup_s, 0, CONTROLLER_short_cgroup_s_length);
  const f_string_static_t controller_short_daemon_s = macro_f_string_static_t_initialize(CONTROLLER_short_daemon_s, 0, CONTROLLER_short_daemon_s_length);
  const f_string_static_t controller_short_init_s = macro_f_string_static_t_initialize(CONTROLLER_short_init_s, 0, CONTROLLER_short_init_s_length);
  const f_string_static_t controller_short_interruptible_s = macro_f_string_static_t_initialize(CONTROLLER_short_interruptible_s, 0, CONTROLLER_short_interruptible_s_length);
  const f_string_static_t controller_short_pid_s = macro_f_string_static_t_initialize(CONTROLLER_short_pid_s, 0, CONTROLLER_short_pid_s_length);
  const f_string_static_t controller_short_settings_s = macro_f_string_static_t_initialize(CONTROLLER_short_settings_s, 0, CONTROLLER_short_settings_s_length);
  const f_string_static_t controller_short_simulate_s = macro_f_string_static_t_initialize(CONTROLLER_short_simulate_s, 0, CONTROLLER_short_simulate_s_length);
  const f_string_static_t controller_short_socket_s = macro_f_string_static_t_initialize(CONTROLLER_short_socket_s, 0, CONTROLLER_short_socket_s_length);
  const f_string_static_t controller_short_uninterruptible_s = macro_f_string_static_t_initialize(CONTROLLER_short_uninterruptible_s, 0, CONTROLLER_short_uninterruptible_s_length);
  const f_string_static_t controller_short_validate_s = macro_f_string_static_t_initialize(CONTROLLER_short_validate_s, 0, CONTROLLER_short_validate_s_length);

  const f_string_static_t controller_long_cgroup_s = macro_f_string_static_t_initialize(CONTROLLER_long_cgroup_s, 0, CONTROLLER_long_cgroup_s_length);
  const f_string_static_t controller_long_daemon_s = macro_f_string_static_t_initialize(CONTROLLER_long_daemon_s, 0, CONTROLLER_long_daemon_s_length);
  const f_string_static_t controller_long_init_s = macro_f_string_static_t_initialize(CONTROLLER_long_init_s, 0, CONTROLLER_long_init_s_length);
  const f_string_static_t controller_long_interruptible_s = macro_f_string_static_t_initialize(CONTROLLER_long_interruptible_s, 0, CONTROLLER_long_interruptible_s_length);
  const f_string_static_t controller_long_pid_s = macro_f_string_static_t_initialize(CONTROLLER_long_pid_s, 0, CONTROLLER_long_pid_s_length);
  const f_string_static_t controller_long_settings_s = macro_f_string_static_t_initialize(CONTROLLER_long_settings_s, 0, CONTROLLER_long_settings_s_length);
  const f_string_static_t controller_long_simulate_s = macro_f_string_static_t_initialize(CONTROLLER_long_simulate_s, 0, CONTROLLER_long_simulate_s_length);
  const f_string_static_t controller_long_socket_s = macro_f_string_static_t_initialize(CONTROLLER_long_socket_s, 0, CONTROLLER_long_socket_s_length);
  const f_string_static_t controller_long_uninterruptible_s = macro_f_string_static_t_initialize(CONTROLLER_long_uninterruptible_s, 0, CONTROLLER_long_uninterruptible_s_length);
  const f_string_static_t controller_long_validate_s = macro_f_string_static_t_initialize(CONTROLLER_long_validate_s, 0, CONTROLLER_long_validate_s_length);
#endif // _di_controller_defines_

#ifndef _di_controller_main_delete_
  f_status_t controller_main_delete(controller_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    f_type_array_lengths_resize(0, &main->remaining);
    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_controller_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
