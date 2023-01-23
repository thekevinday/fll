#include "control.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fll_program_data_t data = fll_program_data_t_initialize;
  control_setting_t setting = control_setting_t_initialize;

  f_console_parameter_t parameters[] = control_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = control_total_parameters_d;
  data.environment = envp;

  if (f_pipe_input_exists()) {
    data.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);
    f_state_t state = f_state_t_initialize;

    control_setting_load(arguments, state, &data, &setting);
  }

  control_main(&data, &setting);

  control_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data);

  return F_status_is_error(status) ? 1 : 0;
}
