#include <level_0/errors.h>
#include <level_3/firewall.h>

int main(f_const f_s_int argc, f_const f_string argv[]) {
  firewall_data data = firewall_data_initialize;

  if (f_error_is_error(firewall_main(argc, argv, &data))) {
    return 1;
  }

  return 0;
}
