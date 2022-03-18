#include "control.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_program_version_
  const f_string_static_t control_program_version_s = macro_f_string_static_t_initialize(CONTROL_program_version_s, 0, CONTROL_program_version_s_length);
#endif // _di_control_program_version_

#ifndef _di_control_program_name_
  const f_string_static_t control_program_name_s = macro_f_string_static_t_initialize(CONTROL_program_name_s, 0, CONTROL_program_name_s_length);
  const f_string_static_t control_program_name_long_s = macro_f_string_static_t_initialize(CONTROL_program_name_long_s, 0, CONTROL_program_name_long_s_length);
#endif // _di_control_program_name_

#ifndef _di_control_parameters_
  const f_string_static_t control_short_name_s = macro_f_string_static_t_initialize(CONTROL_short_name_s, 0, CONTROL_short_name_s_length);
  const f_string_static_t control_short_return_s = macro_f_string_static_t_initialize(CONTROL_short_return_s, 0, CONTROL_short_return_s_length);
  const f_string_static_t control_short_settings_s = macro_f_string_static_t_initialize(CONTROL_short_settings_s, 0, CONTROL_short_settings_s_length);
  const f_string_static_t control_short_socket_s = macro_f_string_static_t_initialize(CONTROL_short_socket_s, 0, CONTROL_short_socket_s_length);

  const f_string_static_t control_long_name_s = macro_f_string_static_t_initialize(CONTROL_long_name_s, 0, CONTROL_long_name_s_length);
  const f_string_static_t control_long_return_s = macro_f_string_static_t_initialize(CONTROL_long_return_s, 0, CONTROL_long_return_s_length);
  const f_string_static_t control_long_settings_s = macro_f_string_static_t_initialize(CONTROL_long_settings_s, 0, CONTROL_long_settings_s_length);
  const f_string_static_t control_long_socket_s = macro_f_string_static_t_initialize(CONTROL_long_socket_s, 0, CONTROL_long_socket_s_length);
#endif // _di_control_parameters_

#ifndef _di_control_action_type_name_
  f_string_static_t control_action_type_name(const uint8_t type) {

    switch (type) {
      case control_action_type_freeze_e:
        return control_freeze_s;

      case control_action_type_kill_e:
        return control_kill_s;

      case control_action_type_pause_e:
        return control_pause_s;

      case control_action_type_reboot_e:
        return control_reboot_s;

      case control_action_type_reload_e:
        return control_reload_s;

      case control_action_type_rerun_e:
        return control_rerun_s;

      case control_action_type_restart_e:
        return control_restart_s;

      case control_action_type_resume_e:
        return control_resume_s;

      case control_action_type_shutdown_e:
        return control_shutdown_s;

      case control_action_type_start_e:
        return control_start_s;

      case control_action_type_stop_e:
        return control_stop_s;

      case control_action_type_thaw_e:
        return control_thaw_s;
    }

    return f_string_empty_s;
  }
#endif // _di_control_action_type_name_

#ifndef _di_control_payload_type_name_
  f_string_static_t control_payload_type_name(const uint8_t type) {

    switch (type) {
      case control_payload_type_controller_e:
        return control_controller_s;

      case control_payload_type_error_e:
        return control_error_s;
    }

    return f_string_empty_s;
  }
#endif // _di_control_payload_type_name_

#ifndef _di_control_main_delete_
  f_status_t control_main_delete(fll_program_data_t * const main) {

    return fll_program_data_delete(main);
  }
#endif // _di_control_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
