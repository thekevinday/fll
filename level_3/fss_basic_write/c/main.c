#include <level_3/fss_basic_write.h>

int main(const unsigned long argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  fss_basic_write_data data = fss_basic_write_data_initialize;

  f_status status = fss_basic_write_main(arguments, &data);

  if (f_status_is_error(status)) {
    return 1;
  }

  return 0;
}
