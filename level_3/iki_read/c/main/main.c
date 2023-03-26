#include "iki_read.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  iki_read_main_t data = iki_read_main_t_initialize;

  data.program.debug.flag |= iki_read_print_flag_debug_e | iki_read_print_flag_out_e;
  data.program.error.flag |= iki_read_print_flag_error_e | iki_read_print_flag_out_e;
  data.program.output.flag |= iki_read_print_flag_out_e;
  data.program.message.flag |= iki_read_print_flag_message_e | iki_read_print_flag_out_e;
  data.program.warning.flag |= iki_read_print_flag_warning_e | iki_read_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  data.setting.state.custom = (void *) &data;
  data.setting.state.handle = &fll_program_standard_signal_handle;

  f_console_parameter_t parameters[] = iki_read_console_parameter_t_initialize;
  data.program.parameters.array = parameters;
  data.program.parameters.used = iki_read_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    iki_read_setting_load(arguments, &data);
  }

  iki_read_main(&data);

  iki_read_setting_unload(&data);

  fll_program_data_delete(&data.program);

  fll_program_standard_set_down(&data.program);

  return F_status_is_error(data.setting.state.status) ? 1 : 0;
}
