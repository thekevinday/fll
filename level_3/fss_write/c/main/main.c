#include "fss_write.h"
#include "basic/basic.h"
#include "basic_list/basic_list.h"
#include "extended/extended.h"
#include "extended_list/extended_list.h"
#include "embedded_list/embedded_list.h"
#include "payload/payload.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fll_program_data_t data = fll_program_data_t_initialize;
  fss_write_setting_t setting = fss_write_setting_t_initialize;
  setting.state.data = (void *) &data;

  // Default to Basic.
  setting.process_help = &fss_write_basic_print_help;
  setting.process_pipe = &fss_write_basic_process_pipe;
  setting.process_normal = &fss_write_basic_process_normal;

  f_console_parameter_t parameters[] = fss_write_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = fss_write_total_parameters_d;
  data.environment = envp;

  if (f_pipe_input_exists()) {
    data.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    fss_write_setting_load(arguments, &data, &setting);
  }

  fss_write_main(&data, &setting);

  fss_write_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_set_down(&data);

  return F_status_is_error(setting.status) ? 1 : 0;
}
