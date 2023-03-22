#include "fss_write.h"
#include "../main/fss_write.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fss_write_main_t data = fss_write_main_t_initialize;

  data.program.debug.flag |= fss_write_print_flag_debug_e;
  data.program.error.flag |= fss_write_print_flag_error_e;
  data.program.message.flag |= fss_write_print_flag_message_e;
  data.program.warning.flag |= fss_write_print_flag_warning_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  setting.state.custom = (void *) &data;
  setting.standard = fss_write_embedded_list_standard_s;
  setting.process_content = &fss_write_embedded_list_process_content;
  setting.process_help = &fss_write_embedded_list_process_help;
  setting.process_normal = &fss_write_process_normal;
  setting.process_object = &fss_write_embedded_list_process_object;
  setting.process_pipe = &fss_write_process_pipe;
  setting.process_set = &fss_write_process_set;
  setting.flag |= fss_write_main_flag_ignore_e;
  setting.flag |= fss_write_main_flag_content_multiple_e;

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

    fss_write_setting_load(arguments, &data, &setting, 0);
  }

  fss_write_main(&data, &setting);

  fss_write_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data);

  return F_status_is_error(setting.state.status) ? 1 : 0;
}
