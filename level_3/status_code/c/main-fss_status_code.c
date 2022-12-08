#include "status_code.h"

// FLL-2 includes.
#include <fll/level_2/fss_status_string.h>

#ifndef _di_status_code_program_name_s_
  const f_string_static_t status_code_program_name_s = macro_f_string_static_t_initialize(STATUS_CODE_program_name_s, 0, STATUS_CODE_program_name_s_length);
  const f_string_static_t status_code_program_name_long_s = macro_f_string_static_t_initialize(STATUS_CODE_program_name_long_s, 0, STATUS_CODE_program_name_long_s_length);
#endif // _di_status_code_program_name_s_

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fll_program_data_t data = fll_program_data_t_initialize;
  status_code_setting_t setting = status_code_setting_t_initialize;

  f_console_parameter_t parameters[] = status_code_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = status_code_total_parameters_d;
  data.environment = envp;

  if (f_pipe_input_exists()) {
    data.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    status_code_setting_load(arguments, &data, &setting);

    setting.status_string_from = &fll_fss_status_string_from;
    setting.status_string_to = &fll_fss_status_string_to;
  }

  status_code_main(&data, &setting);

  status_code_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data);

  return (F_status_is_error(setting.status) || setting.status == F_false) ? 1 : 0;
}
