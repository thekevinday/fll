#include <level_3/fss_return_code.h>

int main(const f_array_length argc, const f_string argv[]) {
  fss_return_code_data data = fss_return_code_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  if (f_error_is_error(fss_return_code_main(argc, argv, &data))) {
    return 1;
  }

  return 0;
}
