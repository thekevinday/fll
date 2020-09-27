#include "init.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  init_data_t data = init_data_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  if (F_status_is_error(init_main(arguments, &data))) {
    return 1;
  }

  return 0;
}
