#include "fss_extended_read.h"

int main(const int argc, const f_string_t *argv) {

  f_console_arguments_t arguments = { argc, argv };
  fss_extended_read_main_t data = fss_extended_read_main_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  const f_status_t status = fss_extended_read_main(&arguments, &data);

  // flush output pipes before closing.
  fflush(F_type_output_d);
  fflush(F_type_error_d);

  // close all open file descriptors.
  close(F_type_descriptor_output_d);
  close(F_type_descriptor_input_d);
  close(F_type_descriptor_error_d);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
