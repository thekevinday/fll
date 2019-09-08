#include <level_3/bit_dump.h>

int main(const int argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  bit_dump_data data = bit_dump_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  f_status status = bit_dump_main(arguments, &data);

  if (f_status_is_error(status)) {
    return 1;
  }

  return 0;
}
