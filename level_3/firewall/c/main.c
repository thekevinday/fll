#include "firewall.h"

int main(const int argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  firewall_main_t main = firewall_main_t_initialize;

  if (f_pipe_input_exists()) {
    main.process_pipe = F_true;
  }

  if (F_status_is_error(firewall_main(arguments, &main))) {
    return 1;
  }

  return 0;
}
