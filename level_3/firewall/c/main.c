#include <level_0/status.h>
#include <level_3/firewall.h>

int main(const f_s_int argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  firewall_data data = firewall_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  f_status status = firewall_main(arguments, &data);

  if (f_status_is_error(status)) {
    return 1;
  }

  return 0;
}
