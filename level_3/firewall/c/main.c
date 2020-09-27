#include "firewall.h"

int main(const int argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  firewall_data_t data = firewall_data_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  if (F_status_is_error(firewall_main(arguments, &data))) {
    return 1;
  }

  return 0;
}
