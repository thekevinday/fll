#include "fake.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fll_program_data_t data = fll_program_data_t_initialize;
  fake_setting_t setting = fake_setting_t_initialize;

  f_console_parameter_t parameters[] = fake_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = fake_total_parameters_d;
  data.environment = envp;

  if (f_pipe_input_exists()) {
    data.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data);

  f_file_umask_get(&data.umask);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    fake_setting_load(arguments, &data, &setting);
  }

  fake_main(&data, &setting);

  fake_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data);

  if (setting.status == F_child) {
    exit(data.child);
  }

  return F_status_is_error(setting.status) ? 1 : 0;
}
