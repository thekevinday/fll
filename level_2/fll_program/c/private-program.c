#include "program.h"
#include "private-program.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_program_print_help_option_) || !defined(_di_fll_program_print_help_option_standard_)
  f_status_t private_fll_program_print_help_option(fl_print_t * const print, const f_string_static_t option_short, const f_string_static_t option_long, const f_string_static_t symbol_short, const f_string_static_t symbol_long, const char *description) {

    fl_print_format("  %Q%[%Q%]", print->to, symbol_short, print->set->standout, option_short, print->set->standout);
    fl_print_format(", %Q%[%Q%]  %S%r", print->to, symbol_long, print->set->standout, option_long, print->set->standout, description, f_string_eol_s);

    return F_none;
  }
#endif // !defined(_di_fll_program_print_help_option_) || !defined(_di_fll_program_print_help_option_standard_)

#if !defined(_di_fll_program_standard_signal_received_) || !defined(_di_fll_program_standard_signal_handle_)
  uint32_t private_fll_program_standard_signal_received(fll_program_data_t * const program) {

    if (!program || program->signal.id == -1) return 0;

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    if (f_signal_read(program->signal, 0, &information) == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          program->signal_received = information.ssi_signo;

          return information.ssi_signo;
      }
    }

    return 0;
  }
#endif // !defined(_di_fll_program_standard_signal_received_) || !defined(_di_fll_program_standard_signal_handle_)

#if !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_empty_)
  void private_fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]) {

    context->set.error = f_color_set_empty_s;
    context->set.important = f_color_set_empty_s;
    context->set.normal = f_color_set_empty_s;
    context->set.normal_reset = f_color_set_empty_s;
    context->set.notable = f_color_set_empty_s;
    context->set.reset = f_color_set_empty_s;
    context->set.standout = f_color_set_empty_s;
    context->set.success = f_color_set_empty_s;
    context->set.title = f_color_set_empty_s;
    context->set.warning = f_color_set_empty_s;

    if (sets) {
      for (f_number_unsigned_t i = 0; sets[i]; ++i) {
        *sets[i] = f_color_set_empty_s;
      } // for
    }
  }
#endif // !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_empty_)

#ifdef __cplusplus
} // extern "C"
#endif
