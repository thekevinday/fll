#include <level_3/fss_basic_read.h>

int main(const f_s_int argc, const f_string argv[]){
  f_status            status = f_status_initialize;
  fss_basic_read_data data   = fss_basic_read_data_initialize;

  status = fss_basic_read_main(argc, argv, &data);

  if (status == f_none) return 0;

  return status;
}
