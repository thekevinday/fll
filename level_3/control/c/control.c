#include "control.h"
#include "private-control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_help_
  f_return_status control_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, control_name_long, control_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    fll_program_print_help_usage(output, context, control_name, f_string_empty_s);

    return F_none;
  }
#endif // _di_control_print_help_

#ifndef _di_control_main_
  f_return_status control_main(const f_console_arguments_t arguments, control_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, control_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { control_parameter_no_color, control_parameter_light, control_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        if (data->context.set.error.before) {
          data->error.context = data->context.set.error;
          data->error.notable = data->context.set.notable;

          data->warning.context = data->context.set.warning;
          data->warning.notable = data->context.set.notable;
        }
        else {
          data->context.set.warning.before = &f_color_set_string_null_s;
          data->context.set.warning.after = &f_color_set_string_null_s;
          data->context.set.error.before = &f_color_set_string_null_s;
          data->context.set.error.after = &f_color_set_string_null_s;
          data->context.set.title.before = &f_color_set_string_null_s;
          data->context.set.title.after = &f_color_set_string_null_s;
          data->context.set.notable.before = &f_color_set_string_null_s;
          data->context.set.notable.after = &f_color_set_string_null_s;
          data->context.set.important.before = &f_color_set_string_null_s;
          data->context.set.important.after = &f_color_set_string_null_s;
          data->context.set.standout.before = &f_color_set_string_null_s;
          data->context.set.standout.after = &f_color_set_string_null_s;
          data->context.set.normal.before = &f_color_set_string_null_s;
          data->context.set.normal.after = &f_color_set_string_null_s;
          data->context.set.normal_reset.before = &f_color_set_string_null_s;
          data->context.set.normal_reset.after = &f_color_set_string_null_s;

          data->error.context.before = &f_color_set_string_null_s;
          data->error.context.after = &f_color_set_string_null_s;
          data->error.notable.before = &f_color_set_string_null_s;
          data->error.notable.after = &f_color_set_string_null_s;

          data->warning.context.before = &f_color_set_string_null_s;
          data->warning.context.after = &f_color_set_string_null_s;
          data->warning.notable.before = &f_color_set_string_null_s;
          data->warning.notable.after = &f_color_set_string_null_s;
        }

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(data->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
            fprintf(data->error.to.stream, "%c", f_string_eol[0]);
          }

          control_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { control_parameter_verbosity_quiet, control_parameter_verbosity_normal, control_parameter_verbosity_verbose, control_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          control_delete_data(data);
          return status;
        }

        if (choice == control_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == control_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == control_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == control_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[control_parameter_help].result == f_console_result_found) {
      control_print_help(data->output, data->context);

      control_delete_data(data);
      return F_none;
    }

    if (data->parameters[control_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, control_version);

      control_delete_data(data);
      return F_none;
    }

    // @todo

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(data->error.to.stream, "%c", f_string_eol[0]);
      }
    }

    control_delete_data(data);
    return status;
  }
#endif // _di_control_main_

#ifndef _di_control_delete_data_
  f_return_status control_delete_data(control_data_t *data) {

    for (f_string_length_t i = 0; i < control_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].values);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);

    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_control_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
