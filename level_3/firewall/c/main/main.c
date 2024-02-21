#include "firewall.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  firewall_main_t data = firewall_main_t_initialize;

  data.program.debug.flag |= firewall_print_flag_debug_e | firewall_print_flag_out_e;
  data.program.error.flag |= firewall_print_flag_error_e | firewall_print_flag_out_e;
  data.program.output.flag |= firewall_print_flag_out_e;
  data.program.message.flag |= firewall_print_flag_message_e | firewall_print_flag_out_e;
  data.program.warning.flag |= firewall_print_flag_warning_e | firewall_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  f_console_parameter_t parameters[] = firewall_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = firewall_parameter_total_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

      firewall_setting_load(arguments, &data);
    }

    firewall_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &firewall_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        firewall_print_error(&data.program.error, macro_firewall_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

          firewall_setting_load(arguments, &data);
        }

        if (!firewall_signal_check(&data)) {
          firewall_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  firewall_main_delete(&data);

  fll_program_standard_set_down(&data.program);

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}