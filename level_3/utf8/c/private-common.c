#include "utf8.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_error_no_from_
  void utf8_print_error_no_from(utf8_main_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet) return;

    fll_print_format("%c%[%sNo from sources are specified, please pipe data, designate a file, or add parameters.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context, f_string_eol_s[0]);
  }
#endif // _di_utf8_print_error_no_from_

#ifndef _di_utf8_print_error_no_value_
  void utf8_print_error_no_value(utf8_main_t * const main, const f_string_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet) return;

    flockfile(main->error.to.stream);

    fl_print_format("%c%[%SThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%s%S%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, parameter, main->context.set.notable);
    fl_print_format("%[' is specified, but no value was given.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

    funlockfile(main->error.to.stream);
  }
#endif // _di_utf8_print_error_no_value_

#ifndef _di_utf8_print_error_parameter_conflict_
  void utf8_print_error_parameter_conflict(utf8_main_t * const main, const f_string_t first, const f_string_t second) {

    if (main->error.verbosity == f_console_verbosity_quiet) return;

    flockfile(main->output.to.stream);

    fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%s%S%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, first, main->error.notable);
    fl_print_format("%[' cannot be used with the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%s%S%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, second, main->error.notable);
    fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

    funlockfile(main->output.to.stream);
  }
#endif // _di_utf8_print_error_parameter_conflict_

#ifndef _di_utf8_print_error_parameter_file_name_empty_
  void utf8_print_error_parameter_file_name_empty(utf8_main_t * const main, const f_array_length_t index) {

    if (main->error.verbosity == f_console_verbosity_quiet) return;

    flockfile(main->error.to.stream);

    fl_print_format("%c%[%SNo file specified at parameter index %]", main->error.to.stream, f_string_eol_s[0], main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%ul%]", main->error.to.stream, main->context.set.notable, index, main->context.set.notable);
    fl_print_format("%[.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

    funlockfile(main->error.to.stream);
  }
#endif // _di_utf8_print_error_parameter_file_name_empty_

#ifndef _di_utf8_print_error_parameter_file_not_found_
  void utf8_print_error_parameter_file_not_found(utf8_main_t * const main, const bool from, const f_string_t name) {

    if (main->error.verbosity == f_console_verbosity_quiet) return;

    flockfile(main->error.to.stream);

    fl_print_format("%c%[%SFailed to find the %s file '%]", main->error.to.stream, f_string_eol_s[0], main->context.set.error, main->error.prefix, from ? utf8_string_from_s : utf8_string_to_s, main->context.set.error);
    fl_print_format("%[%S%]", main->error.to.stream, main->context.set.notable, name, main->context.set.notable);
    fl_print_format("%['.%]%c", main->error.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s[0]);

    funlockfile(main->error.to.stream);
  }
#endif // _di_utf8_print_error_parameter_file_not_found_

#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  void utf8_print_error_parameter_file_to_too_many(utf8_main_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet) return;

    fll_print_format("%c%[%SToo many %s files specified, there may only be one to file.%]%c", main->error.to.stream, f_string_eol_s[0], main->context.set.error, main->error.prefix, utf8_string_to_s, main->context.set.error, f_string_eol_s[0]);
  }
#endif // _di_utf8_print_error_parameter_file_to_too_many_

#ifndef _di_utf8_print_section_header_file_
  void utf8_print_section_header_file(utf8_main_t * const main, const f_string_t name) {

    if (main->output.verbosity == f_console_verbosity_quiet) return;
    if (main->parameters[utf8_parameter_headers].result == f_console_result_none) return;

    flockfile(main->output.to.stream);

    fl_print_format("%c%[File%] ", main->output.to.stream, f_string_eol_s[0], main->output.set->title, main->output.set->title);
    fl_print_format("%[%S%]:%c", main->output.to.stream, main->output.set->notable, name, main->output.set->notable, f_string_eol_s[0]);

    funlockfile(main->output.to.stream);
  }
#endif // _di_utf8_print_section_header_file_

#ifndef _di_utf8_print_section_header_parameter_
  void utf8_print_section_header_parameter(utf8_main_t * const main, const f_array_length_t index) {

    if (main->output.verbosity == f_console_verbosity_quiet) return;
    if (main->parameters[utf8_parameter_headers].result == f_console_result_none) return;

    flockfile(main->output.to.stream);

    fl_print_format("%c%[Parameter%] ", main->output.to.stream, f_string_eol_s[0], main->output.set->title, main->output.set->title);
    fl_print_format("%[%ul%]:%c", main->output.to.stream, main->output.set->notable, index, main->output.set->notable, f_string_eol_s[0]);

    funlockfile(main->output.to.stream);
  }
#endif // _di_utf8_print_section_header_parameter_

#ifndef _di_utf8_print_section_header_pipe_
  void utf8_print_section_header_pipe(utf8_main_t * const main) {

    if (main->output.verbosity == f_console_verbosity_quiet) return;
    if (main->parameters[utf8_parameter_headers].result == f_console_result_none) return;

    fll_print_format("%c%[Pipe%]:%c", main->output.to.stream, f_string_eol_s[0], main->output.set->title, main->output.set->title, f_string_eol_s[0]);
  }
#endif // _di_utf8_print_section_header_pipe_

#ifndef _di_utf8_print_signal_received_
  void utf8_print_signal_received(utf8_main_t * const main, const f_status_t signal) {

    if (main->warning.verbosity != f_console_verbosity_verbose) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%c%c%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s[0], f_string_eol_s[0], main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, signal, main->context.set.notable);
    fl_print_format("%[.%]%c", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s[0]);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_utf8_print_signal_received_

#ifndef _di_utf8_signal_received_
  f_status_t utf8_signal_received(utf8_main_t * const main) {

    if (!main->signal.id) {
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
          utf8_print_signal_received(main, information.ssi_signo);

          return information.ssi_signo;
      }
    }

    return F_false;
  }
#endif // _di_utf8_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif
