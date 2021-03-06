#include "control.h"
#include "private-common.h"
#include "private-control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_help_
  f_status_t control_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, control_name_long, control_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    fll_program_print_help_usage(output, context, control_name, f_string_empty_s);

    return F_none;
  }
#endif // _di_control_print_help_

#ifndef _di_control_main_
  f_status_t control_main(const f_console_arguments_t arguments, control_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, control_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { control_parameter_no_color, control_parameter_light, control_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &main->remaining, &main->context);

        if (main->context.set.error.before) {
          main->error.context = main->context.set.error;
          main->error.notable = main->context.set.notable;

          main->warning.context = main->context.set.warning;
          main->warning.notable = main->context.set.notable;
        }
        else {
          f_color_set_t *sets[] = { &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

          fll_program_parameter_process_empty(&main->context, sets);
        }

        if (F_status_is_error(status)) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
            fprintf(main->error.to.stream, "%c", f_string_eol_s[0]);
          }

          control_main_delete(main);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { control_parameter_verbosity_quiet, control_parameter_verbosity_normal, control_parameter_verbosity_verbose, control_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          control_main_delete(main);
          return status;
        }

        if (choice == control_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == control_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == control_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == control_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[control_parameter_help].result == f_console_result_found) {
      control_print_help(main->output, main->context);

      control_main_delete(main);
      return F_none;
    }

    if (main->parameters[control_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, control_version);

      control_main_delete(main);
      return F_none;
    }

    // @todo

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(main->error.to.stream, "%c", f_string_eol_s[0]);
      }
    }

    control_main_delete(main);
    return status;
  }
#endif // _di_control_main_

#ifndef _di_control_main_delete_
  f_status_t control_main_delete(control_main_t *main) {

    for (f_array_length_t i = 0; i < control_total_parameters; ++i) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_control_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
