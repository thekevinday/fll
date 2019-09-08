#include <level_0/status.h>
#include <level_3/firewall.h>

int main(const int argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  firewall_data data = firewall_data_initialize;

  if (f_status_is_error(firewall_main(arguments, &data))) {
    return 1;
  }

  return 0;
}
