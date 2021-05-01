#include "fss_extended_write.h"

int main(const int argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  fss_extended_write_main_t main = fss_extended_write_main_t_initialize;

  if (f_pipe_input_exists()) {
    main.process_pipe = F_true;
  }

  const f_status_t status = fss_extended_write_main(arguments, &main);

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
