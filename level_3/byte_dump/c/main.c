#include "byte_dump.h"

int main(const int argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  byte_dump_data_t data = byte_dump_data_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  const f_status_t status = byte_dump_main(arguments, &data);

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
