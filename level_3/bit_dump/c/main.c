#include <level_3/bit_dump.h>

int main(const f_array_length argc, const f_string argv[]) {
  bit_dump_data data = bit_dump_data_initialize;

  if (f_pipe_exists()) {
    data.process_pipe = f_true;
  }

  f_status status = bit_dump_main(argc, argv, &data);

  if (f_status_is_error(status)) {
    return 1;
  }

  return 0;
}
