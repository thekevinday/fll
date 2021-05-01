#include "controller.h"

int main(const int argc, const f_string_t *argv) {
  const f_console_arguments_t arguments = { argc, argv };
  controller_main_t main = controller_main_t_initialize;
  f_status_t status = F_none;

  if (f_pipe_input_exists()) {
    main.process_pipe = F_true;
  }

  main.pid = getpid();

  f_signal_set_empty(&main.signal.set);
  f_signal_set_add(F_signal_abort, &main.signal.set);
  f_signal_set_add(F_signal_hangup, &main.signal.set);
  f_signal_set_add(F_signal_interrupt, &main.signal.set);
  f_signal_set_add(F_signal_quit, &main.signal.set);
  f_signal_set_add(F_signal_termination, &main.signal.set);
  f_signal_mask(SIG_BLOCK, &main.signal.set, 0);

  status = f_signal_open(&main.signal);

  // if there is an error opening a signal descriptor, then do not handle signals.
  if (F_status_is_error(status)) {
    f_signal_mask(SIG_UNBLOCK, &main.signal.set, 0);
    f_signal_close(&main.signal);
  }

  // @fixme: bad design in POSIX where there is no get umask without setting it.
  main.umask = umask(0);

  // restore umask.
  umask(main.umask);

  status = controller_main(arguments, &main);

  // flush output pipes before closing.
  fflush(f_type_output);
  fflush(f_type_error);

  // close all open file descriptors.
  close(f_type_descriptor_output);
  close(f_type_descriptor_input);
  close(f_type_descriptor_error);

  f_signal_close(&main.signal);

  if (status == F_child) {
    exit(main.child);
  }

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
