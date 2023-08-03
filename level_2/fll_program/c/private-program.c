#include "program.h"
#include "private-program.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_context_standard_)
  f_status_t private_fll_program_parameter_process_context(const f_uint16s_t choices, const uint8_t modes[], const bool right, fll_program_data_t * const main) {

    {
      if (choices.used) {
        f_status_t status = F_none;
        f_number_unsigned_t choice = 0;

        if (right) {
          status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);
        }
        else {
          status = f_console_parameter_prioritize_left(main->parameters, choices, &choice);
        }

        if (F_status_is_error(status)) return status;

        if (status == F_data_not) {
          main->context.mode = modes[choices.used - 1];
        }
        else {
          main->context.mode = modes[choice];
        }

        if (main->context.mode == f_color_mode_dark_e || main->context.mode == f_color_mode_light_e) {
          status = f_color_load_context(main->context.mode, &main->context);
          if (F_status_is_error(status)) return status;
        }
      }
      else {
        main->context.mode = f_color_mode_not_e;
      }
    }

    main->message.set =
      main->output.set =
      main->error.set =
      main->warning.set = &main->context.set;

    if (main->context.set.error.before) {
      main->message.context = f_color_set_empty_s;
      main->message.notable = main->context.set.notable;

      main->output.context = f_color_set_empty_s;
      main->output.notable = main->context.set.notable;

      main->error.context = main->context.set.error;
      main->error.notable = main->context.set.notable;

      main->warning.context = main->context.set.warning;
      main->warning.notable = main->context.set.notable;
    }
    else {
      f_color_set_t * const sets[] = { &main->message.context, &main->message.notable, &main->output.context, &main->output.notable, &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

      private_fll_program_parameter_process_empty(&main->context, sets);
    }

    return F_none;
  }
#endif // !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_context_standard_)

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

#if !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_context_standard_) || !defined(_di_fll_program_parameter_process_empty_)
  void private_fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]) {

    context->set.error =
      context->set.important =
      context->set.normal =
      context->set.normal_reset =
      context->set.notable =
      context->set.reset =
      context->set.standout =
      context->set.success =
      context->set.title =
      context->set.warning = f_color_set_empty_s;

    if (sets) {
      for (f_number_unsigned_t i = 0; sets[i]; ++i) {
        *sets[i] = f_color_set_empty_s;
      } // for
    }
  }
#endif // !defined(_di_fll_program_parameter_process_context_) || !defined(_di_fll_program_parameter_process_context_standard_) || !defined(_di_fll_program_parameter_process_empty_)

#ifdef __cplusplus
} // extern "C"
#endif
