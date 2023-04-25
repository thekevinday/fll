#include "controller.h"
#include "main-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_program_name_
  const f_string_static_t controller_program_name_s = macro_f_string_static_t_initialize_1(CONTROLLER_program_name_s, 0, CONTROLLER_program_name_s_length);
  const f_string_static_t controller_program_name_long_s = macro_f_string_static_t_initialize_1(CONTROLLER_program_name_long_s, 0, CONTROLLER_program_name_long_s_length);
#endif // _di_controller_program_name_

#ifndef _di_controller_defines_
  const f_string_static_t controller_default_engine_s = macro_f_string_static_t_initialize_1(CONTROLLER_default_engine_s, 0, CONTROLLER_default_engine_s_length);
  const f_string_static_t controller_path_pid_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_pid_s, 0, CONTROLLER_path_pid_s_length);
  const f_string_static_t controller_path_pid_init_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_pid_init_s, 0, CONTROLLER_path_pid_init_s_length);
  const f_string_static_t controller_path_pid_prefix_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_pid_prefix_s, 0, CONTROLLER_path_pid_prefix_s_length);
  const f_string_static_t controller_path_pid_suffix_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_pid_suffix_s, 0, CONTROLLER_path_pid_suffix_s_length);
  const f_string_static_t controller_path_settings_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_settings_s, 0, CONTROLLER_path_settings_s_length);
  const f_string_static_t controller_path_settings_init_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_settings_init_s, 0, CONTROLLER_path_settings_init_s_length);
  const f_string_static_t controller_path_socket_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_socket_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_init_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_socket_init_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_prefix_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_socket_prefix_s, 0, CONTROLLER_path_socket_prefix_s_length);
  const f_string_static_t controller_path_socket_suffix_s = macro_f_string_static_t_initialize_1(CONTROLLER_path_socket_suffix_s, 0, CONTROLLER_path_socket_suffix_s_length);
#endif // _di_controller_defines_

#ifdef __cplusplus
} // extern "C"
#endif
