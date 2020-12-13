#include "status_code.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  status_code_data_t data = status_code_data_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  const f_status_t status = status_code_main(arguments, &data);

  // close all open file descriptors.
  close(f_type_descriptor_output);
  close(f_type_descriptor_input);
  close(f_type_descriptor_error);

  if (F_status_is_error(status) || status == F_false) {
    return 1;
  }

  return 0;
}
