#include "fss_extended_write.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  fss_extended_write_data_t data = fss_extended_write_data_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  f_status_t status = fss_extended_write_main(arguments, &data);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
