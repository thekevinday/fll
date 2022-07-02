#include "program.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_print_help_header_
  f_status_t fll_program_print_help_header(const f_file_t output, const f_color_context_t context, const f_string_static_t name, const f_string_static_t version) {

    fl_print_format("%r %[%Q%]%r", output.stream, f_string_eol_s, context.set.title, name, context.set.title, f_string_eol_s);
    fl_print_format("  %[Version %Q%]%r", output.stream, context.set.notable, version, context.set.notable, f_string_eol_s);

    fl_print_format("%r %[Available Options:%] ", output.stream, f_string_eol_s, context.set.important, context.set.important);

    return F_none;
  }
#endif // _di_fll_program_print_help_header_

#ifndef _di_fll_program_print_help_option_
  f_status_t fll_program_print_help_option(const f_file_t output, const f_color_context_t context, const f_string_static_t option_short, const f_string_static_t option_long, const f_string_static_t symbol_short, const f_string_static_t symbol_long, const char *description) {

    fl_print_format("%r  %Q%[%Q%]", output.stream, f_string_eol_s, symbol_short, context.set.standout, option_short, context.set.standout);
    fl_print_format(", %Q%[%Q%]  %S", output.stream, symbol_long, context.set.standout, option_long, context.set.standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_

#ifndef _di_fll_program_print_help_option_long_
  f_status_t fll_program_print_help_option_long(const f_file_t output, const f_color_context_t context, const f_string_static_t option_long, const f_string_static_t symbol_long, const char *description) {

    fl_print_format("%r      %Q%[%Q%]  %S", output.stream, f_string_eol_s, symbol_long, context.set.standout, option_long, context.set.standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_long_

#ifndef _di_fll_program_print_help_option_other_
  f_status_t fll_program_print_help_option_other(const f_file_t output, const f_color_context_t context, const f_string_static_t option_other, const char *description) {

    fl_print_format("%r  %[%Q%]  %S", output.stream, f_string_eol_s, context.set.standout, option_other, context.set.standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_other_

#ifndef _di_fll_program_print_help_usage_
  f_status_t fll_program_print_help_usage(const f_file_t output, const f_color_context_t context, const f_string_static_t name, const f_string_static_t parameters) {

    fl_print_format("%r%r %[Usage:%]%r", output.stream, f_string_eol_s, f_string_eol_s, context.set.important, context.set.important, f_string_eol_s);

    fl_print_format("  %[%Q%]", output.stream, context.set.standout, name, context.set.standout);
    fl_print_format(" %[[%] options %[]%]", output.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable);

    if (parameters.used) {
      fl_print_format(" %[[%] %Q %[]%]", output.stream, context.set.notable, context.set.notable, parameters, context.set.notable, context.set.notable);
    }

    fl_print_format("%r%r", output.stream, f_string_eol_s, f_string_eol_s);

    return F_none;
  }
#endif // _di_fll_program_print_help_usage_

#ifndef _di_fll_program_print_version_
  f_status_t fll_program_print_version(const f_file_t output, const f_string_static_t version) {

    f_print_dynamic(version, output.stream);
    f_print_dynamic_raw(f_string_eol_s, output.stream);

    return F_none;
  }
#endif // _di_fll_program_print_version_

#ifndef _di_fll_program_parameter_process_
  f_status_t fll_program_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t * const parameters, const f_console_parameter_ids_t choices, const bool right, f_color_context_t * const context) {

    f_status_t status = F_none;

    status = f_console_parameter_process(arguments, parameters);
    if (F_status_is_error(status)) return status;

    f_console_parameter_id_t decision = choices.id[2];

    if (right) {
      status = f_console_parameter_prioritize_right(*parameters, choices, &decision);
    }
    else {
      status = f_console_parameter_prioritize_left(*parameters, choices, &decision);
    }

    if (F_status_is_error(status)) return status;

    // Load colors unless told not to.
    if (decision == choices.id[0]) {
      context->mode = F_color_mode_no_color_d;
    }
    else {
      f_status_t allocation_status = F_none;

      macro_f_color_context_t_new(allocation_status, (*context));
      if (F_status_is_error(status)) return status;

      status = f_color_load_context(decision == choices.id[1], context);
    }

    return status;
  }
#endif // _di_fll_program_parameter_process_

#ifndef _di_fll_program_parameter_process_empty_
  void fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]) {

    context->set.reset = f_color_set_empty_s;
    context->set.warning = f_color_set_empty_s;
    context->set.error = f_color_set_empty_s;
    context->set.title = f_color_set_empty_s;
    context->set.notable = f_color_set_empty_s;
    context->set.important = f_color_set_empty_s;
    context->set.standout = f_color_set_empty_s;
    context->set.success = f_color_set_empty_s;
    context->set.normal = f_color_set_empty_s;
    context->set.normal_reset = f_color_set_empty_s;

    if (sets) {
      for (f_array_length_t i = 0; sets[i]; ++i) {
        *sets[i] = f_color_set_empty_s;
      }
    }
  }
#endif // _di_fll_program_parameter_process_empty_

#ifndef _di_fll_program_parameter_additional_append_
  f_status_t fll_program_parameter_additional_append(const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamics_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        status = f_string_dynamics_increase(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(status)) break;

        destination->array[destination->used].used = 0;

        status = f_string_dynamic_append(arguments[values.array[i]], &destination->array[destination->used]);
        if (F_status_is_error(status)) break;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          ++destination->used;
        }
      }
    } // for

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_append_

#ifndef _di_fll_program_parameter_additional_mash_
  f_status_t fll_program_parameter_additional_mash(const f_string_static_t glue, const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamic_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        status = f_string_dynamic_mash(glue, arguments[values.array[i]], destination);
        if (F_status_is_error(status)) break;
      }
    } // for

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_mash_

#ifndef _di_fll_program_parameter_additional_rip_
  f_status_t fll_program_parameter_additional_rip(const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamics_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        status = f_string_dynamics_increase(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(status)) break;

        destination->array[destination->used].used = 0;

        status = fl_string_dynamic_rip(arguments[values.array[i]], &destination->array[destination->used]);
        if (F_status_is_error(status)) break;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          ++destination->used;
        }
      }
    } // for

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_rip_

#ifndef _di_fll_program_parameter_additional_rip_mash_
  f_status_t fll_program_parameter_additional_rip_mash(const f_string_static_t glue, const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamic_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    const f_array_length_t start = destination->used;
    f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        ripped.used = 0;

        status = fl_string_dynamic_rip(arguments[values.array[i]], &ripped);
        if (F_status_is_error(status)) break;

        if (ripped.used) {
          status = f_string_dynamic_mash(glue, ripped, destination);
          if (F_status_is_error(status)) break;
        }
      }
    } // for

    f_string_dynamic_resize(0, &ripped);

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_rip_mash_

#ifndef _di_fll_program_parameter_long_print_cannot_use_with_
  f_status_t fll_program_parameter_long_print_cannot_use_with(const fl_print_t print, const f_string_static_t first, const f_string_static_t second) {

    flockfile(print.to.stream);

    fl_print_format("%r%[%QCannot specify the '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%r%r%]", print.to.stream, print.notable, f_console_symbol_long_enable_s, first, print.notable);
    fl_print_format("%[' parameter with the '%]", print.to.stream, print.context, print.context);
    fl_print_format("%[%r%r%]", print.to.stream, print.notable, f_console_symbol_long_enable_s, second, print.notable);
    fl_print_format("%[' parameter.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

    funlockfile(print.to.stream);

    return F_none;
  }
#endif // _di_fll_program_parameter_long_print_cannot_use_with_

#ifndef _di_fll_program_standard_setdown_
  f_status_t fll_program_standard_setdown(f_signal_t * const signal) {
    #ifndef _di_level_2_parameter_checking_
      if (!signal) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_


    // Flush output pipes before closing.
    fflush(F_type_output_d);
    fflush(F_type_error_d);

    // Close all open file descriptors.
    close(F_type_descriptor_output_d);
    close(F_type_descriptor_input_d);
    close(F_type_descriptor_error_d);

    const f_status_t status = f_signal_close(signal);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_program_standard_setdown_

#ifndef _di_fll_program_standard_setup_
  f_status_t fll_program_standard_setup(f_signal_t * const signal) {
    #ifndef _di_level_2_parameter_checking_
      if (!signal) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_signal_set_empty(&signal->set);
    f_signal_set_add(F_signal_abort, &signal->set);
    f_signal_set_add(F_signal_broken_pipe, &signal->set);
    f_signal_set_add(F_signal_hangup, &signal->set);
    f_signal_set_add(F_signal_interrupt, &signal->set);
    f_signal_set_add(F_signal_quit, &signal->set);
    f_signal_set_add(F_signal_termination, &signal->set);

    f_status_t status = f_signal_mask(SIG_BLOCK, &signal->set, 0);

    if (F_status_is_error_not(status)) {
      status = f_signal_open(signal);

      // If there is an error opening a signal descriptor, then do not handle signals.
      if (F_status_is_error(status)) {
        f_signal_mask(SIG_UNBLOCK, &signal->set, 0);
        f_signal_close(signal);
      }
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_program_standard_setup_

#ifndef _di_fll_program_standard_signal_received_
  f_status_t fll_program_standard_signal_received(fll_program_data_t * const main) {

    if (!main || main->signal.id == -1) {
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
          main->signal_received = information.ssi_signo;

          return information.ssi_signo;
      }
    }

    return F_false;
  }
#endif // _di_fss_basic_read_signal_received_

#ifndef _di_fll_program_standard_signal_state_
  f_status_t fll_program_standard_signal_state(void * const state, void * const internal) {

    if (!state) {
      return F_interrupt_not;
    }

    f_state_t *state_ptr = (f_state_t *) state;

    if (!state_ptr->custom) {
      return F_interrupt_not;
    }

    fll_program_data_t *custom = (fll_program_data_t *) state_ptr->custom;

    custom->signal_received = fll_program_standard_signal_received(custom);

    if (custom->signal_received == F_signal_abort || custom->signal_received == F_signal_broken_pipe || custom->signal_received == F_signal_hangup || custom->signal_received == F_signal_interrupt || custom->signal_received == F_signal_quit || custom->signal_received == F_signal_termination) {
      return F_status_set_error(F_interrupt);
    }

    return F_interrupt_not;
  }
#endif // _di_fll_program_standard_signal_state_

#ifdef __cplusplus
} // extern "C"
#endif
