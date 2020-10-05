#include "fss_basic_write.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  fss_basic_write_data_t data = fss_basic_write_data_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  if (F_status_is_error(fss_basic_write_main(arguments, &data))) {
    return 1;
  }

  return 0;
}
