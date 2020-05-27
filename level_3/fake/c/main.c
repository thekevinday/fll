#include <level_3/fake.h>

int main(const unsigned long argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  fake_data data = fake_data_initialize;

  // @fixme: bad design in POSIX where there is no get umask without setting it.
  data.umask = umask(0);

  // restore umask.
  umask(data.umask);

  f_status status = fake_main(arguments, &data);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
