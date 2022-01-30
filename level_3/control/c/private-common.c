#include "control.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_strings_
  const f_string_static_t controller_name_socket_s = macro_f_string_static_t_initialize2(CONTROLLER_name_socket_s, 0, CONTROLLER_name_socket_s_length);
  const f_string_static_t controller_path_socket_s = macro_f_string_static_t_initialize2(CONTROLLER_path_socket_s, 0, CONTROLLER_path_socket_s_length);
  const f_string_static_t controller_path_socket_prefix_s = macro_f_string_static_t_initialize2(CONTROLLER_path_socket_prefix_s, 0, CONTROLLER_path_socket_prefix_s_length);
  const f_string_static_t controller_path_socket_suffix_s = macro_f_string_static_t_initialize2(CONTROLLER_path_socket_suffix_s, 0, CONTROLLER_path_socket_suffix_s_length);
#endif // _di_controller_strings_

#ifndef _di_control_strings_s_
  const f_string_static_t control_path_settings_s = macro_f_string_static_t_initialize2(CONTROL_path_settings_s, 0, CONTROL_path_settings_s_length);

  const f_string_static_t control_command_s = macro_f_string_static_t_initialize2(CONTROL_command_s, 0, CONTROL_command_s_length);
  const f_string_static_t control_default_s = macro_f_string_static_t_initialize2(CONTROL_default_s, 0, CONTROL_default_s_length);
  const f_string_static_t control_name_socket_s = macro_f_string_static_t_initialize2(CONTROL_name_socket_s, 0, CONTROL_name_socket_s_length);
  const f_string_static_t control_path_socket_s = macro_f_string_static_t_initialize2(CONTROL_path_socket_s, 0, CONTROL_path_socket_s_length);
  const f_string_static_t control_path_socket_prefix_s = macro_f_string_static_t_initialize2(CONTROL_path_socket_prefix_s, 0, CONTROL_path_socket_prefix_s_length);
  const f_string_static_t control_path_socket_suffix_s = macro_f_string_static_t_initialize2(CONTROL_path_socket_suffix_s, 0, CONTROL_path_socket_suffix_s_length);

  const f_string_static_t control_error_s = macro_f_string_static_t_initialize2(CONTROL_error_s, 0, CONTROL_error_s_length);
  const f_string_static_t control_freeze_s = macro_f_string_static_t_initialize2(CONTROL_freeze_s, 0, CONTROL_freeze_s_length);
  const f_string_static_t control_kill_s = macro_f_string_static_t_initialize2(CONTROL_kill_s, 0, CONTROL_kill_s_length);
  const f_string_static_t control_pause_s = macro_f_string_static_t_initialize2(CONTROL_pause_s, 0, CONTROL_pause_s_length);
  const f_string_static_t control_reboot_s = macro_f_string_static_t_initialize2(CONTROL_reboot_s, 0, CONTROL_reboot_s_length);
  const f_string_static_t control_reload_s = macro_f_string_static_t_initialize2(CONTROL_reload_s, 0, CONTROL_reload_s_length);
  const f_string_static_t control_rerun_s = macro_f_string_static_t_initialize2(CONTROL_rerun_s, 0, CONTROL_rerun_s_length);
  const f_string_static_t control_restart_s = macro_f_string_static_t_initialize2(CONTROL_restart_s, 0, CONTROL_restart_s_length);
  const f_string_static_t control_resume_s = macro_f_string_static_t_initialize2(CONTROL_resume_s, 0, CONTROL_resume_s_length);
  const f_string_static_t control_shutdown_s = macro_f_string_static_t_initialize2(CONTROL_shutdown_s, 0, CONTROL_shutdown_s_length);
  const f_string_static_t control_start_s = macro_f_string_static_t_initialize2(CONTROL_start_s, 0, CONTROL_start_s_length);
  const f_string_static_t control_stop_s = macro_f_string_static_t_initialize2(CONTROL_stop_s, 0, CONTROL_stop_s_length);
  const f_string_static_t control_thaw_s = macro_f_string_static_t_initialize2(CONTROL_thaw_s, 0, CONTROL_thaw_s_length);
#endif // _di_control_strings_s_

#ifndef _di_control_data_delete_
  void control_data_delete(control_data_t * const data) {

    f_string_dynamic_resize(0, &data->cache.buffer_large);
    f_string_dynamic_resize(0, &data->cache.buffer_small);
  }
#endif // _di_control_data_delete_

#ifndef _di_control_signal_received_
  f_status_t control_signal_received(control_main_t * const main) {

    if (main->signal.id == -1) {
      return F_false;
    }

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    if (f_signal_read(main->signal, 0, &information) == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          control_print_signal_received(main, information.ssi_signo);

          return information.ssi_signo;
      }
    }

    return F_false;
  }
#endif // _di_control_signal_received_

#ifndef _di_control_signal_state_interrupt_fss_
  f_status_t control_signal_state_interrupt_fss(void *state, void *internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t * const state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    control_main_t * const main = (control_main_t *) state_ptr->custom;

    if (!((++main->signal_check) % control_signal_check_d)) {
      if (control_signal_received(main)) {
        return F_status_set_error(F_interrupt);
      }

      main->signal_check = 0;
    }

    return F_interrupt_not;
  }
#endif // _di_control_signal_state_interrupt_fss_

#ifdef __cplusplus
} // extern "C"
#endif
