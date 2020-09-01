#include "fss_basic_write.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  fss_basic_write_data data = fss_basic_write_data_initialize;

  f_status_t status = fss_basic_write_main(arguments, &data);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
