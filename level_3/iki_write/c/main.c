#include "iki_write.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  iki_write_data_t data = iki_write_data_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  if (F_status_is_error(iki_write_main(arguments, &data))) {
    return 1;
  }

  return 0;
}
