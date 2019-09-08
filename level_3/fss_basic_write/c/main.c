#include <level_3/fss_basic_write.h>

int main(const int argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  fss_basic_write_data data = fss_basic_write_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  if (f_status_is_error(fss_basic_write_main(arguments, &data))) {
    return 1;
  }

  return 0;
}
