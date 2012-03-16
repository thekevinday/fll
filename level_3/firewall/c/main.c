#include <level_3/firewall.h>

int main(const f_s_int argc, const f_string argv[]) {
  firewall_data data = firewall_data_initialize;

  return firewall_main(argc, argv, &data);
}
