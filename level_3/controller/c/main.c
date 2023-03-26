#include "controller.h"
#include "main-common.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  controller_main_t data = controller_main_t_initialize;

  data.program.debug.flag |= controller_print_flag_debug_e | controller_print_flag_out_e;
  data.program.error.flag |= controller_print_flag_error_e | controller_print_flag_out_e;
  data.program.output.flag |= controller_print_flag_out_e;
  data.program.message.flag |= controller_print_flag_message_e | controller_print_flag_out_e;
  data.program.warning.flag |= controller_print_flag_warning_e | controller_print_flag_out_e;
  data.program.error.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;

  f_console_parameter_t parameters[] = controller_console_parameter_t_initialize;
  data.program.parameters.array = parameters;
  data.program.parameters.used = controller_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  data.program.pid = getpid();

  fll_program_standard_set_up(&data.program);

  f_file_umask_get(&data.program.umask);

  data.program.default_engine = &controller_default_engine_s;
  data.program.default_path_setting = &controller_path_settings_s;
  data.program.default_path_setting_init = &controller_path_settings_init_s;
  data.program.default_path_pid = &controller_path_pid_s;
  data.program.default_path_pid_init = &controller_path_pid_init_s;
  data.program.default_path_pid_prefix = &controller_path_pid_prefix_s;
  data.program.default_path_pid_suffix = &controller_path_pid_suffix_s;
  data.program.default_path_socket = &controller_path_socket_s;
  data.program.default_path_socket_init = &controller_path_socket_init_s;
  data.program.default_path_socket_prefix = &controller_path_socket_prefix_s;
  data.program.default_path_socket_suffix = &controller_path_socket_suffix_s;
  data.program.program_name = &controller_program_name_s;
  data.program.program_name_long = &controller_program_name_long_s;

  // When run as "init" by default, provide the default system-level init path.
  #ifdef _controller_as_init_
    data.program.as_init = F_true;
  #else
    data.program.as_init = F_false;
  #endif // _controller_as_init_

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    controller_setting_load(arguments, &data);
  }

  controller_main(&data);

  controller_setting_unload(&data);

  controller_main_delete(&data.program);

  fll_program_standard_set_down(&data.program);

  // When the child process exits, it must return the code to the parent so the parent knows how to handle the exit.
  if (status == F_child) {
    exit(data.child);
  }

  return F_status_is_error(data.setting.state.status) ? 1 : 0;
}
