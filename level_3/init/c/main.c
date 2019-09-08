#include <level_3/init.h>

int main(const int argc, const f_string *argv) {
  const f_console_arguments arguments = { argc, argv };
  init_argument data = init_argument_initialize;

  return init_main(arguments, &data);
}
