#include "utf8.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

  fll_program_data_t data = fll_program_data_t_initialize;
  utf8_main_setting_t setting = utf8_main_setting_t_initialize;

  f_console_parameter_t parameters[] = utf8_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = utf8_total_parameters_d;

  if (f_pipe_input_exists()) {
    data.pipe |= fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.signal);

  f_status_t status = utf8_main_setting_load(arguments, data, &setting);

  if (F_status_is_error_not(status)) {
    status = utf8_main(&data, &setting);
  }

  if (data.message.stream != data.output.stream) {
    f_file_stream_flush(&data->output);
    f_file_stream_close(&data->output);
  }

  utf8_main_setting_unload(data, &setting);

  utf8_main_setting_delete(&setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data.signal);

  return F_status_is_error(status) ? 1 : 0;
}
