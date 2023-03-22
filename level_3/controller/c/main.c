#include "controller.h"
#include "main-common.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  controller_main_t data = controller_main_t_initialize;

  data.program.debug.flag |= controller_print_flag_debug_e;
  data.program.error.flag |= controller_print_flag_error_e;
  data.program.message.flag |= controller_print_flag_message_e;
  data.program.warning.flag |= controller_print_flag_warning_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  f_console_parameter_t parameters[] = controller_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = controller_total_parameters_d;
  data.environment = envp;

  if (f_pipe_input_exists()) {
    data.pipe = fll_program_data_pipe_input_e;
  }

  data.pid = getpid();

  fll_program_standard_set_up(&data);

  f_file_umask_get(&data.umask);

  data.default_engine = &controller_default_engine_s;
  data.default_path_setting = &controller_path_settings_s;
  data.default_path_setting_init = &controller_path_settings_init_s;
  data.default_path_pid = &controller_path_pid_s;
  data.default_path_pid_init = &controller_path_pid_init_s;
  data.default_path_pid_prefix = &controller_path_pid_prefix_s;
  data.default_path_pid_suffix = &controller_path_pid_suffix_s;
  data.default_path_socket = &controller_path_socket_s;
  data.default_path_socket_init = &controller_path_socket_init_s;
  data.default_path_socket_prefix = &controller_path_socket_prefix_s;
  data.default_path_socket_suffix = &controller_path_socket_suffix_s;
  data.program_name = &controller_program_name_s;
  data.program_name_long = &controller_program_name_long_s;

  // When run as "init" by default, provide the default system-level init path.
  #ifdef _controller_as_init_
    data.as_init = F_true;
  #else
    data.as_init = F_false;
  #endif // _controller_as_init_

  {
    const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

    controller_setting_load(arguments, &data, &setting);
  }

  controller_main(&data, &setting);

  controller_setting_unload(&data, &setting);

  controller_main_delete(&data);

  fll_program_standard_set_down(&data);

  // When the child process exits, it must return the code to the parent so the parent knows how to handle the exit.
  if (status == F_child) {
    exit(data.child);
  }

  return F_status_is_error(status) ? 1 : 0;
}
