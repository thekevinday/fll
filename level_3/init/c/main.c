#include "init.h"

int main(const unsigned long argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  init_data_t data = init_data_initialize;
  f_status_t status = F_none;

  f_signal_set_empty(&data.signal.set);
  f_signal_set_add(F_signal_abort, &data.signal.set);
  f_signal_set_add(F_signal_hangup, &data.signal.set);
  f_signal_set_add(F_signal_interrupt, &data.signal.set);
  f_signal_set_add(F_signal_quit, &data.signal.set);
  f_signal_set_add(F_signal_termination, &data.signal.set);
  f_signal_set_handle(SIG_BLOCK, &data.signal.set);

  // if there is an error opening a signal descriptor, then do not handle signals.
  if (F_status_is_error(f_signal_open(&data.signal))) {
    f_signal_set_handle(SIG_UNBLOCK, &data.signal.set);
    f_signal_close(&data.signal);
  }

  // @fixme: bad design in POSIX where there is no get umask without setting it.
  data.umask = umask(0);

  // restore umask.
  umask(data.umask);

  status = init_main(arguments, &data);

  f_signal_close(&data.signal);

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
