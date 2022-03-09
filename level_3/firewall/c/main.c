#include "firewall.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);
  firewall_main_t data = firewall_main_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  fll_program_standard_setup(&data.signal);

  const f_status_t status = firewall_main(&data, &arguments);

  fll_program_standard_setdown(&data.signal);

  if (status == F_child) {
    exit(data.child);
  }

  if (F_status_is_error(status)) return 1;

  return 0;
}
