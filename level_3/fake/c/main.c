#include "fake.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  fake_data_t data = fake_data_t_initialize;

  // @fixme: bad design in POSIX where there is no get umask without setting it.
  data.umask = umask(0);

  // restore umask.
  umask(data.umask);

  f_status_t status = fake_main(arguments, &data);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
