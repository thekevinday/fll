#include <level_3/status_code.h>

int main(const int argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  status_code_data data = status_code_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  f_status status = status_code_main(arguments, &data);

  if (f_status_is_error(status) || status == f_false) {
    return 1;
  }

  return 0;
}
