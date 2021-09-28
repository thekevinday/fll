#include "controller.h"

int main(const int argc, const f_string_t *argv) {

  const f_console_arguments_t arguments = { argc, argv };
  controller_main_t data = controller_main_t_initialize;
  f_status_t status = F_none;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  data.pid = getpid();

  f_signal_set_empty(&data.signal.set);
  f_signal_set_add(F_signal_abort, &data.signal.set);
  f_signal_set_add(F_signal_hangup, &data.signal.set);
  f_signal_set_add(F_signal_interrupt, &data.signal.set);
  f_signal_set_add(F_signal_quit, &data.signal.set);
  f_signal_set_add(F_signal_termination, &data.signal.set);
  f_signal_mask(SIG_BLOCK, &data.signal.set, 0);

  status = f_signal_open(&data.signal);

  // if there is an error opening a signal descriptor, then do not handle signals.
  if (F_status_is_error(status)) {
    f_signal_mask(SIG_UNBLOCK, &data.signal.set, 0);
    f_signal_close(&data.signal);
  }

  // @fixme bad design in POSIX where there is no get umask without setting it.
  data.umask = umask(0);

  // restore umask.
  umask(data.umask);

  // when run as "init" by default, provide the default system-level init path.
  // this change must only exist within this main file so that the change only exists within the program rather than the library.
  #ifdef _controller_as_init_
    data.process_pid = F_false;
    data.program_name = controller_name_init;
    data.program_name_long = controller_name_init_long;
    data.setting_default.string = controller_path_settings_init;
    data.setting_default.used = controller_path_settings_init_length;
    data.path_pid.string = controller_path_pid_init;
    data.path_pid.used = controller_path_pid_init_length;
    data.as_init = F_true;
  #else
    data.program_name = controller_name;
    data.program_name_long = controller_name_long;
    data.path_pid.string = controller_path_pid;
    data.path_pid.used = controller_path_pid_length;
  #endif // _controller_as_init_

  status = controller_main(arguments, &data);

  // flush output pipes before closing.
  fflush(f_type_output);
  fflush(f_type_error);

  // close all open file descriptors.
  close(f_type_descriptor_output);
  close(f_type_descriptor_input);
  close(f_type_descriptor_error);

  f_signal_close(&data.signal);

  if (status == F_child) {
    exit(data.child);
  }

  if (F_status_is_error(status)) {

    // do not return error when interrupt was received.
    if (F_status_set_fine(status) != F_interrupt) {
      return 1;
    }
  }

  return 0;
}
