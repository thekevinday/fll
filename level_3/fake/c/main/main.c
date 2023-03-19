#include "fake.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fake_main_t data = fake_main_t_initialize;

  data.program.debug.flag |= fake_print_flag_debug_e;
  data.program.error.flag |= fake_print_flag_error_e;
  data.program.message.flag |= fake_print_flag_message_e;
  data.program.warning.flag |= fake_print_flag_warning_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  data.setting.flag |= fake_main_flag_enable_documents_e;
  data.setting.flag |= fake_main_flag_enable_shared_e;
  data.setting.flag |= fake_main_flag_enable_static_e;
  data.setting.state.step_large = fake_allocation_large_d;
  data.setting.state.step_small = fake_allocation_small_d;
  data.setting.state.custom = (void *) &data.program;

  f_console_parameter_t parameters[] = fake_console_parameter_t_initialize;
  data.program.parameters.array = parameters;
  data.program.parameters.used = fake_total_parameters_d;
  data.program.parameters.callback = &fake_setting_load_parameter_callback;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    fake_setting_load(arguments, &data);
  }

  fake_main(&data);

  fake_setting_unload(&data);

  fll_program_data_delete(&data.program);

  fll_program_standard_set_down(&data.program);

  if (data.setting.state.status == F_child) {
    exit(data.program.child);
  }

  return F_status_is_error(data.setting.state.status) ? 1 : 0;
}
