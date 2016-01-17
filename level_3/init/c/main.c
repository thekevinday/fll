#include <level_3/init.h>

int main(f_const f_s_int argc, f_const f_string argv[]) {
  init_argument data = init_argument_initialize;

  return init_main(argc, argv, &data);
}
