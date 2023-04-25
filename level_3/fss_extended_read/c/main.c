#include "fss_extended_read.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fss_extended_read_main_t data = fss_extended_read_main_t_initialize;

  data.program.debug.flag |= fss_extended_read_print_flag_debug_e | fss_extended_read_print_flag_out_e;
  data.program.error.flag |= fss_extended_read_print_flag_error_e | fss_extended_read_print_flag_out_e;
  data.program.output.flag |= fss_extended_read_print_flag_out_e;
  data.program.message.flag |= fss_extended_read_print_flag_message_e | fss_extended_read_print_flag_out_e;
  data.program.warning.flag |= fss_extended_read_print_flag_warning_e | fss_extended_read_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  f_console_parameter_t parameters[] = fss_extended_read_console_parameter_t_initialize;
  data.program.parameters.array = parameters;
  data.program.parameters.used = fss_extended_read_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

    fss_extended_read_setting_load(arguments, &data);
  }

  fss_extended_read_main(&data);

  fss_extended_read_setting_unload(&data);

  fll_program_data_delete(&data.program);

  fll_program_standard_set_down(&data.program);

  return F_status_is_error(data.setting.state.status) ? 1 : 0;
}
