#include <level_3/fss_extended_read.h>

int main(const f_array_length argc, const f_string argv[]){
  f_status               status = f_status_initialize;
  fss_extended_read_data data   = fss_extended_read_data_initialize;

  status = fss_extended_read_main(argc, argv, &data);

  if (status == f_none) return 0;

  return status;
}
