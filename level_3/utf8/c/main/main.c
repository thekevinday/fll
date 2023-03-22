#include "utf8.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  utf8_main_t data = utf8_main_t_initialize;

  data.program.debug.flag |= utf8_print_flag_debug_e;
  data.program.error.flag |= utf8_print_flag_error_e;
  data.program.message.flag |= utf8_print_flag_message_e;
  data.program.warning.flag |= utf8_print_flag_warning_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  f_console_parameter_t parameters[] = utf8_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = utf8_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    utf8_setting_load(arguments, &data);
  }

  utf8_main(&data);

  utf8_setting_unload(&data);

  fll_program_data_delete(&data.program);

  fll_program_standard_set_down(&data.program);

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}
