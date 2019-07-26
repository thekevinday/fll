#include <level_3/return_code.h>

int main(f_const f_array_length argc, f_const f_string argv[]) {
  return_code_data data = return_code_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  if (f_error_is_error(return_code_main(argc, argv, &data))) {
    return 1;
  }

  return 0;
}
