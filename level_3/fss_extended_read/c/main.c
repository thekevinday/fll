#include <level_3/fss_extended_read.h>

int main(f_const f_array_length argc, f_const f_string argv[]) {
  fss_extended_read_data data = fss_extended_read_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  if (f_error_is_error(fss_extended_read_main(argc, argv, &data))) {
    return 1;
  }

  return 0;
}
