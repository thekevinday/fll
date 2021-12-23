#include "firewall.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

void firewall_print_debug_tool(const fl_print_t output, const f_string_t tool, const f_string_dynamics_t arguments) {

  if (output.verbosity != f_console_verbosity_debug) return;

  flockfile(output.to.stream);

  fl_print_format("%[%s", output.to.stream, output.context, tool);

  for (f_array_length_t i = 0; i < arguments.used; ++i) {
    fl_print_format(" %Q", output.to.stream, arguments.array[i]);
  } // for

  fl_print_format("%]%c", output.to.stream, output.context, f_string_eol_s[0]);

  funlockfile(output.to.stream);
}

void firewall_print_error_on_allocation_failure(const fl_print_t output) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sUnable to allocate memory.%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, output.context, f_string_eol_s[0]);
}

void firewall_print_error_on_invalid_parameter(const fl_print_t output, const f_string_t function) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sInvalid parameter when calling %S().%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, function, output.context, f_string_eol_s[0]);
}

void firewall_print_error_on_invalid_parameter_for_file(const fl_print_t output, const f_string_t function, const f_string_t filename) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sInvalid parameter when calling %S() for the file '%S'.%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, function, filename, output.context, f_string_eol_s[0]);
}

void firewall_print_error_on_operation(const fl_print_t output, const f_string_t tool, const f_string_dynamics_t arguments) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  flockfile(output.to.stream);

  fl_print_format("%c%[%sFailed to perform requested %s operation:%]", output.to.stream, f_string_eol_s[0], output.context, output.prefix, tool, output.context);
  fl_print_format("%c  %[%s", output.to.stream, f_string_eol_s[0], output.context, tool);

  for (f_array_length_t i = 0; i < arguments.used; ++i) {
    fl_print_format(" %Q", output.to.stream, arguments.array[i]);
  } // for

  fl_print_format("%]%c", output.to.stream, output.context, f_string_eol_s[0]);

  funlockfile(output.to.stream);
}

void firewall_print_error_on_unhandled(const fl_print_t output, const f_string_t function, const f_status_t status) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sAn unhandled error (%ui) has occurred while calling %S().%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, status, function, output.context, f_string_eol_s[0]);
}

void firewall_print_error_on_unhandled_for_file(const fl_print_t output, const f_string_t function, const f_status_t status, const f_string_t filename) {

  if (output.verbosity == f_console_verbosity_quiet) return;

  fll_print_format("%c%[%sAn unhandled error (%ui) has occurred while calling %S() for the file '%S'.%]%c", output.to.stream, f_string_eol_s[0], output.context, output.prefix, status, function, filename, output.context, f_string_eol_s[0]);
}

#ifndef _di_firewall_print_signal_received_
  void firewall_print_signal_received(firewall_main_t * const main, const f_status_t signal) {

    if (main->warning.verbosity != f_console_verbosity_verbose) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%c%c%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s[0], f_string_eol_s[0], main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, signal, main->context.set.notable);
    fl_print_format("%[.%]%c", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s[0]);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_firewall_print_signal_received_

#ifndef _di_firewall_signal_received_
  f_status_t firewall_signal_received(firewall_main_t * const main) {

    if (main->signal.id == -1) {
      return F_false;
    }

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    if (f_signal_read(main->signal, 0, &information) == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          firewall_print_signal_received(main, information.ssi_signo);

          return information.ssi_signo;
      }
    }

    return F_false;
  }
#endif // _di_firewall_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif
