#include <level_3/init.h>

int main(const f_s_int argc, const f_string argv[]) {
  init_argument data = init_argument_initialize;

  return init_main(argc, argv, &data);
}
