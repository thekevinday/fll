#include <level_3/fss_basic_read.h>

int main(const f_array_length argc, const f_string argv[]){
  fss_basic_read_data data = fss_basic_read_data_initialize;

  if (f_pipe_exists()){
    data.process_pipe = f_true;
  }

  return fss_basic_read_main(argc, argv, &data);
}
