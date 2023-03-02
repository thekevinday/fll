#include "fss_write.h"
#include "../main/fss_write.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fll_program_data_t data = fll_program_data_t_initialize;
  fss_write_setting_t setting = fss_write_setting_t_initialize;
  setting.state.data = (void *) &data;
  setting.standard = fss_write_extended_standard_s;
  setting.process_content = &fss_write_extended_process_content;
  setting.process_help = &fss_write_extended_process_help;
  setting.process_normal = &fss_write_process_normal;
  setting.process_object = &fss_write_extended_process_object;
  setting.process_pipe = &fss_write_process_pipe;
  setting.process_set = &fss_write_process_set;
  setting.flag |= fss_write_flag_content_multiple_e;

  f_console_parameter_t parameters[] = fss_write_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.array[fss_write_parameter_as_e].flag |= f_console_flag_disable_e;
  data.parameters.used = fss_write_total_parameters_d;
  data.environment = envp;

  if (f_pipe_input_exists()) {
    data.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    fss_write_setting_load(arguments, state, &data, &setting, 0);
  }

  fss_write_main(&data, &setting);

  fss_write_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data);

  return F_status_is_error(setting.status) ? 1 : 0;
}
