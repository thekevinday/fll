#include "fss_basic_read.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  fss_basic_read_data_t data = fss_basic_read_data_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  const f_status_t status = fss_basic_read_main(arguments, &data);

  // flush output pipes before closing.
  fflush(f_type_output);
  fflush(f_type_error);

  // close all open file descriptors.
  close(f_type_descriptor_output);
  close(f_type_descriptor_input);
  close(f_type_descriptor_error);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
