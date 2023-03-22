#include "status_code.h"
#include "../main/status_code.h"
#include "print.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  status_code_main_t data = status_code_main_t_initialize;

  data.program.debug.flag |= status_code_print_flag_debug_e;
  data.program.error.flag |= status_code_print_flag_error_e;
  data.program.message.flag |= status_code_print_flag_message_e;
  data.program.warning.flag |= status_code_print_flag_warning_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  data.setting.program_name = &status_code_fss_program_name_s;
  data.setting.program_name_long = &status_code_fss_program_name_long_s;
  data.setting.status_string_from = &fll_fss_status_string_from;
  data.setting.status_string_to = &fll_fss_status_string_to;
  data.setting.status_string_help_detail = &status_code_fss_print_help_detail;

  f_console_parameter_t parameters[] = status_code_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = status_code_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    status_code_setting_load(arguments, &data);
  }

  status_code_main(&data);

  status_code_setting_unload(&data);

  fll_program_data_delete(&data.program);

  fll_program_standard_set_down(&data.program);

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}
