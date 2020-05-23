#include <level_3/fss_status_code.h>

int main(const unsigned long argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  fss_status_code_data data = fss_status_code_data_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  f_status status = fss_status_code_main(arguments, &data);

  if (F_status_is_error(status) || status == F_false) {
    return 1;
  }

  return 0;
}
