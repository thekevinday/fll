#include "controller.h"
#include "main-common.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);
  controller_main_t data = controller_main_t_initialize;

  f_console_parameter_t parameters[] = controller_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = controller_total_parameters_d;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  data.pid = getpid();

  fll_program_standard_setup(&data.signal);

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

  const f_status_t status = controller_main(&data, &arguments);

  controller_main_delete(&data);

  fll_program_standard_setdown(&data.signal);

  // When the child process exits, it must return the code to the parent so the parent knows how to handle the exit.
  if (status == F_child) {
    exit(data.child);
  }

  if (F_status_is_error(status)) return 1;

  return 0;
}
