#include "fss_payload_read.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fss_payload_read_main_t data = fss_payload_read_main_t_initialize;

  data.program.debug.flag |= fss_payload_read_print_flag_debug_e;
  data.program.error.flag |= fss_payload_read_print_flag_error_e;
  data.program.message.flag |= fss_payload_read_print_flag_message_e;
  data.program.warning.flag |= fss_payload_read_print_flag_warning_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  f_console_parameter_t parameters[] = fss_payload_read_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = fss_payload_read_total_parameters_d;
  data.environment = envp;

  if (f_pipe_input_exists()) {
    data.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    fss_payload_read_setting_load(arguments, &data, &setting);
  }

  fss_payload_read_main(&data, &setting);

  fss_payload_read_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data);

  return F_status_is_error(status) ? 1 : 0;
}
