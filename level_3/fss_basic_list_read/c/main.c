#include "fss_basic_list_read.h"

int main(const int argc, const f_string_t *argv) {

  f_console_arguments_t arguments = { argc, argv };
  fss_basic_list_read_main_t data = fss_basic_list_read_main_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  fll_program_standard_setup(&data.signal);

  const f_status_t status = fss_basic_list_read_main(&data, &arguments);

  fll_program_standard_setdown(&data.signal);

  if (F_status_is_error(status)) return 1;

  return 0;
}
