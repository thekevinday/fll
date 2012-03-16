#include <level_3/return_code.h>

int main(const f_array_length argc, const f_string argv[]) {
  return_code_data data = return_code_data_initialize;

  /*
  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }
  */

  return return_code_main(argc, argv, &data);
}
