#include <level_0/status.h>
#include <level_3/firewall.h>

int main(const f_s_int argc, const f_string argv[]) {
  firewall_data data = firewall_data_initialize;

  if (f_status_is_error(firewall_main(argc, argv, &data))) {
    return 1;
  }

  return 0;
}
