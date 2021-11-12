#include "status_code.h"

int main(const int argc, const f_string_t *argv) {

  const f_console_arguments_t arguments = { argc, argv };
  status_code_main_t data = status_code_main_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  // Handle signals so that program can cleanly exit, deallocating as appropriate.
  {
    f_signal_set_empty(&data.signal.set);
    f_signal_set_add(F_signal_abort, &data.signal.set);
    f_signal_set_add(F_signal_broken_pipe, &data.signal.set);
    f_signal_set_add(F_signal_hangup, &data.signal.set);
    f_signal_set_add(F_signal_interrupt, &data.signal.set);
    f_signal_set_add(F_signal_quit, &data.signal.set);
    f_signal_set_add(F_signal_termination, &data.signal.set);

    f_status_t status = f_signal_mask(SIG_BLOCK, &data.signal.set, 0);

    if (F_status_is_error_not(status)) {
      status = f_signal_open(&data.signal);

      // If there is an error opening a signal descriptor, then do not handle signals.
      if (F_status_is_error(status)) {
        f_signal_mask(SIG_UNBLOCK, &data.signal.set, 0);
        f_signal_close(&data.signal);
      }
    }
  }

  const f_status_t status = status_code_main(&data, &arguments);

  // Flush output pipes before closing.
  fflush(F_type_output_d);
  fflush(F_type_error_d);

  // Close all open file descriptors.
  close(F_type_descriptor_output_d);
  close(F_type_descriptor_input_d);
  close(F_type_descriptor_error_d);

  f_signal_close(&data.signal);

  if (F_status_is_error(status) || status == F_false) {
    return 1;
  }

  return 0;
}
