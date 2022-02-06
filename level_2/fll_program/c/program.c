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
  f_status_t fll_program_print_help_option(const f_file_t output, const f_color_context_t context, const f_string_static_t option_short, const f_string_static_t option_long, const f_string_static_t symbol_short, const f_string_static_t symbol_long, const f_string_t description) {

    fl_print_format("%r  %Q%[%Q%]", output.stream, f_string_eol_s, symbol_short, context.set.standout, option_short, context.set.standout);
    fl_print_format(", %Q%[%Q%]  %S", output.stream, symbol_long, context.set.standout, option_long, context.set.standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_

#ifndef _di_fll_program_print_help_option_long_
  f_status_t fll_program_print_help_option_long(const f_file_t output, const f_color_context_t context, const f_string_static_t option_long, const f_string_static_t symbol_long, const f_string_t description) {

    fl_print_format("%r      %Q%[%Q%]  %S", output.stream, f_string_eol_s, symbol_long, context.set.standout, option_long, context.set.standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_long_

#ifndef _di_fll_program_print_help_option_other_
  f_status_t fll_program_print_help_option_other(const f_file_t output, const f_color_context_t context, const f_string_static_t option_other, const f_string_t description) {

    fl_print_format("%r  %[%Q%]  %S", output.stream, f_string_eol_s, context.set.standout, option_other, context.set.standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_other_

#ifndef _di_fll_program_print_help_usage_
  f_status_t fll_program_print_help_usage(const f_file_t output, const f_color_context_t context, const f_string_static_t name, const f_string_static_t parameters) {

    fl_print_format("%r%r %[Usage:%]%r", output.stream, f_string_eol_s, f_string_eol_s, context.set.important, context.set.important, f_string_eol_s);

    fl_print_format("  %[%Q%]", output.stream, context.set.standout, name, context.set.standout);
    fl_print_format(" %[[%] options %[]%]", output.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable);
    fl_print_format(" %[[%] %Q", output.stream, context.set.notable, context.set.notable, parameters);
    fl_print_format(" %[]%]%r%r", output.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

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
  f_status_t fll_program_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t * const parameters, const f_console_parameter_ids_t choices, const bool right, f_color_context_t *context) {

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
  void fll_program_parameter_process_empty(f_color_context_t *context, f_color_set_t *sets[]) {

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
  f_status_t fll_program_parameter_additional_append(const f_string_t *argv, const f_array_lengths_t values, f_string_dynamics_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!argv) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    f_array_length_t length = 0;
    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      length = strnlen(argv[values.array[i]], F_console_parameter_size_d);

      if (length > 0) {
        f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

        status = f_string_append(argv[values.array[i]], length, &ripped);
        if (F_status_is_error(status)) return status;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          macro_f_memory_structure_increment(status, (*destination), 1, F_memory_default_allocation_small_d, macro_f_string_dynamics_t_resize, F_array_too_large);
          if (F_status_is_error(status)) break;

          destination->array[destination->used++] = ripped;
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
  f_status_t fll_program_parameter_additional_mash(const f_string_static_t glue, const f_string_t *argv, const f_array_lengths_t values, f_string_dynamic_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!argv) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    f_array_length_t length = 0;
    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      length = strnlen(argv[values.array[i]], F_console_parameter_size_d);

      if (length > 0) {
        status = f_string_mash(glue.string, glue.used, argv[values.array[i]], length, destination);
        if (F_status_is_error(status)) return F_status_set_error(F_string_too_large);
      }
    } // for

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_mash_

#ifndef _di_fll_program_parameter_additional_rip_
  f_status_t fll_program_parameter_additional_rip(const f_string_t *argv, const f_array_lengths_t values, f_string_dynamics_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!argv) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    f_array_length_t length = 0;
    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      length = strnlen(argv[values.array[i]], F_console_parameter_size_d);

      if (length) {
        f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

        status = fl_string_rip(argv[values.array[i]], length, &ripped);
        if (F_status_is_error(status)) return status;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          macro_f_string_dynamics_t_increase(status, F_memory_default_allocation_small_d, (*destination));
          if (F_status_is_error(status)) return status;

          destination->array[destination->used++] = ripped;
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
  f_status_t fll_program_parameter_additional_rip_mash(const f_string_static_t glue, const f_string_t *argv, const f_array_lengths_t values, f_string_dynamic_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!argv) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;

    f_array_length_t length = 0;
    const f_array_length_t start = destination->used;
    f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      length = strnlen(argv[values.array[i]], F_console_parameter_size_d);

      if (length > 0) {
        status = fl_string_rip(argv[values.array[i]], length, &ripped);

        if (F_status_is_error(status)) {
          f_string_dynamic_resize(0, &ripped);

          return status;
        }

        if (ripped.used > 0) {
          status = f_string_dynamic_mash(glue, ripped, destination);

          if (F_status_is_error(status)) {
            status = f_string_dynamic_resize(0, &ripped);

            return F_status_set_error(F_string_too_large);
          }
        }
      }
    } // for

    if (ripped.size) {
      f_string_dynamic_resize(0, &ripped);
    }

    if (status == F_none && start == destination->used) {
      return F_data_not;
    }

    return status;
  }
#endif // _di_fll_program_parameter_additional_rip_mash_

#ifndef _di_fll_program_standard_setdown_
  f_status_t fll_program_standard_setdown(f_signal_t * const signal) {

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

#ifdef __cplusplus
} // extern "C"
#endif
