#include <level_3/fss_error_code.h>

int main(const f_array_length argc, const f_string argv[]){
  fss_error_code_data data = fss_error_code_data_initialize;

  /*
  if (f_pipe_exists()){
    data.process_pipe = f_true;
  }
  */

  return fss_error_code_main(argc, argv, &data);
}
