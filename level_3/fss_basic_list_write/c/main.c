#include <level_3/fss_basic_list_write.h>

int main(f_const f_array_length argc, f_const f_string argv[]) {
  fss_basic_list_write_data data = fss_basic_list_write_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  return fss_basic_list_write_main(argc, argv, &data);
}
