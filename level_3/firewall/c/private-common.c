#include "firewall.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_data_delete_
  f_status_t firewall_data_delete(firewall_data_t * const data) {

    f_string_dynamics_resize(0, &data->chains);
    f_string_dynamics_resize(0, &data->devices);

    return F_none;
  }
#endif // _di_firewall_data_delete_

void firewall_print_debug_tool(const fl_print_t output, const f_string_static_t tool, const f_string_statics_t arguments) {

  if (output.verbosity != f_console_verbosity_debug_e) return;

  flockfile(output.to.stream);

  fl_print_format("%[%r", output.to.stream, output.context, tool);

  for (f_array_length_t i = 0; i < arguments.used; ++i) {
    fl_print_format(" %Q", output.to.stream, arguments.array[i]);
  } // for

  fl_print_format("%]%r", output.to.stream, output.context, f_string_eol_s);

  funlockfile(output.to.stream);
}

void firewall_print_error_on_allocation_failure(const fl_print_t output) {

  if (output.verbosity == f_console_verbosity_quiet_e) return;

  fll_print_format("%r%[%QUnable to allocate memory.%]%r", output.to.stream, f_string_eol_s, output.context, output.prefix, output.context, f_string_eol_s);
}

void firewall_print_error_on_invalid_parameter(const fl_print_t output, const char *function) {

  if (output.verbosity == f_console_verbosity_quiet_e) return;

  fll_print_format("%r%[%QInvalid parameter when calling %s().%]%r", output.to.stream, f_string_eol_s, output.context, output.prefix, function, output.context, f_string_eol_s);
}

void firewall_print_error_on_invalid_parameter_for_file(const fl_print_t output, const char *function, const f_string_static_t filename) {

  if (output.verbosity == f_console_verbosity_quiet_e) return;

  fll_print_format("%r%[%QInvalid parameter when calling %s() for the file '%Q'.%]%r", output.to.stream, f_string_eol_s, output.context, output.prefix, function, filename, output.context, f_string_eol_s);
}

void firewall_print_error_on_operation(const fl_print_t output, const f_string_static_t tool, const f_string_statics_t arguments) {

  if (output.verbosity == f_console_verbosity_quiet_e) return;

  flockfile(output.to.stream);

  fl_print_format("%r%[%QFailed to perform requested %r operation:%]", output.to.stream, f_string_eol_s, output.context, output.prefix, tool, output.context);
  fl_print_format("%r  %[%r", output.to.stream, f_string_eol_s, output.context, tool);

  for (f_array_length_t i = 0; i < arguments.used; ++i) {
    fl_print_format(" %Q", output.to.stream, arguments.array[i]);
  } // for

  fl_print_format("%]%r", output.to.stream, output.context, f_string_eol_s);

  funlockfile(output.to.stream);
}

void firewall_print_error_on_unhandled(const fl_print_t output, const char *function, const f_status_t status) {

  if (output.verbosity == f_console_verbosity_quiet_e) return;

  fll_print_format("%r%[%QAn unhandled error (%ui) has occurred while calling %s().%]%r", output.to.stream, f_string_eol_s, output.context, output.prefix, status, function, output.context, f_string_eol_s);
}

void firewall_print_error_on_unhandled_for_file(const fl_print_t output, const char *function, const f_status_t status, const f_string_static_t filename) {

  if (output.verbosity == f_console_verbosity_quiet_e) return;

  fll_print_format("%r%[%QAn unhandled error (%ui) has occurred while calling %s() for the file '%Q'.%]%r", output.to.stream, f_string_eol_s, output.context, output.prefix, status, function, filename, output.context, f_string_eol_s);
}

#ifndef _di_firewall_print_signal_received_
  void firewall_print_signal_received(firewall_data_t * const data, const f_status_t signal) {

    if (data->main->warning.verbosity != f_console_verbosity_verbose_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(data->main->warning.to.stream);

    flockfile(data->main->warning.to.stream);

    fl_print_format("%]%r%r%[Received signal code %]", data->main->warning.to.stream, data->main->context.set.reset, f_string_eol_s, f_string_eol_s, data->main->context.set.warning, data->main->context.set.warning);
    fl_print_format("%[%i%]", data->main->warning.to.stream, data->main->context.set.notable, signal, data->main->context.set.notable);
    fl_print_format("%[.%]%r", data->main->warning.to.stream, data->main->context.set.warning, data->main->context.set.warning, f_string_eol_s);

    funlockfile(data->main->warning.to.stream);
  }
#endif // _di_firewall_print_signal_received_

#ifndef _di_firewall_signal_received_
  f_status_t firewall_signal_received(firewall_data_t * const data) {

    if (data->main->signal.id == -1) {
      return F_false;
    }

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    if (f_signal_read(data->main->signal, 0, &information) == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          firewall_print_signal_received(data, information.ssi_signo);

          return information.ssi_signo;
      }
    }

    return F_false;
  }
#endif // _di_firewall_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif
