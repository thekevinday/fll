#include "control.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  control_main_t data = control_main_t_initialize;

  data.program.debug.flag |= control_print_flag_debug_e | control_print_flag_out_e;
  data.program.error.flag |= control_print_flag_error_e | control_print_flag_out_e;
  data.program.output.flag |= control_print_flag_out_e;
  data.program.message.flag |= control_print_flag_message_e | control_print_flag_out_e;
  data.program.warning.flag |= control_print_flag_warning_e | control_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  f_console_parameter_t parameters[] = control_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = control_parameter_total_d;
  data.program.environment = envp;

  data.setting.socket.domain = f_socket_protocol_family_local_e;
  data.setting.socket.type = f_socket_type_stream_e;
  data.setting.socket.length = sizeof(struct sockaddr_un);

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

      control_setting_load(arguments, &data);
    }

    control_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &control_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        control_print_error(&data.program.error, macro_control_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

          control_setting_load(arguments, &data);
        }

        if (!control_signal_check(&data)) {
          control_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  control_main_delete(&data);

  fll_program_standard_set_down(&data.program);

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}