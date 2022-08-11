#include "fss_basic_list_read.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);
  fll_program_data_t data = fll_program_data_t_initialize;

  f_console_parameter_t parameters[] = fss_basic_list_read_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = fss_basic_list_read_total_parameters_d;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  fll_program_standard_set_up(&data.signal);

  const f_status_t status = fss_basic_list_read_main(&data, &arguments);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data.signal);

  if (F_status_is_error(status)) return 1;

  return 0;
}
