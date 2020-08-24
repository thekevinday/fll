#include "fss_extended_read.h"

int main(const unsigned long argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  fss_extended_read_data data = fss_extended_read_data_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  f_status status = fss_extended_read_main(arguments, &data);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
