#include "controller/controller.h"

int main(const int argc, const f_string_t *argv) {

  const f_console_arguments_t arguments = { argc, argv };
  controller_main_t data = controller_main_t_initialize;

  if (f_pipe_input_exists()) {
    data.process_pipe = F_true;
  }

  data.pid = getpid();

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

  // @fixme bad design in POSIX where there is no get umask without setting it.
  data.umask = umask(0);

  // Restore umask.
  umask(data.umask);

  // when run as "init" by default, provide the default system-level init path.
  // This change must only exist within this main file so that the change only exists within the program rather than the library.
  #ifdef _controller_as_init_
    data.program_name = controller_program_name_init_s;
    data.program_name_long = controller_program_name_init_long_s;
    data.setting_default = controller_path_settings_init_s;
    data.path_pid = controller_path_pid_init_s;
    data.as_init = F_true;
  #else
    data.program_name = controller_program_name_s;
    data.program_name_long = controller_program_name_long_s;
    data.path_pid = controller_path_pid_s;
  #endif // _controller_as_init_

  const f_status_t status = controller_main(&data, &arguments);

  // Flush output pipes before closing.
  fflush(F_type_output_d);
  fflush(F_type_error_d);

  // Close all open file descriptors.
  close(F_type_descriptor_output_d);
  close(F_type_descriptor_input_d);
  close(F_type_descriptor_error_d);

  f_signal_close(&data.signal);

  // When the child process exits, it must return the code to the parent so the parent knows how to handle the exit.
  if (status == F_child) {
    exit(data.child);
  }

  if (F_status_is_error(status)) {
    return 1;
  }

  return 0;
}
