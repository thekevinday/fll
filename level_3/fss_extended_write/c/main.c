#include <level_3/fss_extended_write.h>

int main(const f_array_length argc, const f_string argv[]) {
  fss_extended_write_data data = fss_extended_write_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  return fss_extended_write_main(argc, argv, &data);
}
