#include "firewall.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  firewall_main_t data = firewall_main_t_initialize;

  data.program.debug.flag |= firewall_read_print_flag_debug_e;
  data.program.error.flag |= firewall_read_print_flag_error_e;
  data.program.message.flag |= firewall_read_print_flag_message_e;
  data.program.warning.flag |= firewall_read_print_flag_warning_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  f_console_parameter_t parameters[] = firewall_console_parameter_t_initialize;
  data.program.parameters.array = parameters;
  data.program.parameters.used = firewall_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    firewall_setting_load(arguments, &data);
  }

  firewall_main(&data);

  firewall_setting_unload(&data);

  fll_program_data_delete(&data.program);

  fll_program_standard_set_down(&data.program);

  if (status == F_child) {
    exit(data.child);
  }

  return F_status_is_error(data.setting.state.status) ? 1 : 0;
}
