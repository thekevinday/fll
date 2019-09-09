#include <level_3/init.h>

int main(const unsigned long argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  init_argument data = init_argument_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  f_status status = init_main(arguments, &data);

  if (f_status_is_error(status)) {
    return 1;
  }

  return 0;
}
