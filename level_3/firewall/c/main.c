#include "firewall.h"

int main(const int argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  firewall_data data = firewall_data_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  f_status status = firewall_main(arguments, &data);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
