#include "status_code.h"
#include "private-status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_print_help_
  f_return_status status_code_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, status_code_name_long, status_code_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    fprintf(output.stream, "%c", f_string_eol[0]);

    fll_program_print_help_option(output, context, status_code_short_is_fine, status_code_long_is_fine, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Print F_true if the error code is not an error, F_false otherwise.");
    fll_program_print_help_option(output, context, status_code_short_is_warning, status_code_long_is_warning, f_console_symbol_short_enable, f_console_symbol_long_enable, "Print F_true if the error code is a warning, F_false otherwise.");
    fll_program_print_help_option(output, context, status_code_short_is_error, status_code_long_is_error, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Print F_true if the error code is an error, F_false otherwise.");
    fll_program_print_help_option(output, context, status_code_short_number, status_code_long_number, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Convert status code name to number.");

    fll_program_print_help_usage(output, context, status_code_name, "status code(s)");

    return F_none;
  }
#endif // _di_status_code_print_help_

#ifndef _di_status_code_main_
  f_return_status status_code_main(const f_console_arguments_t arguments, status_code_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, status_code_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { status_code_parameter_no_color, status_code_parameter_light, status_code_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        data->error.context = data->context.set.error;
        data->error.notable = data->context.set.notable;

        if (F_status_is_error(status)) {
          status_code_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { status_code_parameter_verbosity_quiet, status_code_parameter_verbosity_normal, status_code_parameter_verbosity_verbose, status_code_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          status_code_delete_data(data);
          return status;
        }

        if (choice == status_code_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == status_code_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == status_code_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == status_code_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[status_code_parameter_help].result == f_console_result_found) {
      status_code_print_help(data->output, data->context);

      status_code_delete_data(data);
      return F_none;
    }

    if (data->parameters[status_code_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, status_code_version);

      status_code_delete_data(data);
      return F_none;
    }

    if (data->parameters[status_code_parameter_is_error].result == f_console_result_found) {
      if (data->parameters[status_code_parameter_is_warning].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, status_code_long_is_error);
        fl_color_print(data->error.to.stream, data->context.set.error, "' cannot be used with the parameter ");
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, status_code_long_is_warning);
        fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol[0]);

        status_code_delete_data(data);
        return F_status_set_error(status);
      }
      else if (data->parameters[status_code_parameter_is_fine].result == f_console_result_found) {
        fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, status_code_long_is_error);
        fl_color_print(data->error.to.stream, data->context.set.error, "' cannot be used with the parameter ");
        fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, status_code_long_is_fine);
        fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol[0]);

        status_code_delete_data(data);
        return F_status_set_error(status);
      }
    }
    else if (data->parameters[status_code_parameter_is_warning].result == f_console_result_found && data->parameters[status_code_parameter_is_fine].result == f_console_result_found) {
      fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
      fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, status_code_long_is_warning);
      fl_color_print(data->error.to.stream, data->context.set.error, "' cannot be used with the parameter ");
      fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, status_code_long_is_fine);
      fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol[0]);

      status_code_delete_data(data);
      return F_status_set_error(status);
    }

    if (data->remaining.used == 0 && !data->process_pipe) {
      fl_color_print(data->error.to.stream, data->context.set.error, "%sYou failed to specify a status code.%c", fll_error_print_error, f_string_eol[0]);

      status_code_delete_data(data);
      return F_status_set_error(F_parameter);
    }

    f_status_t status2 = F_none;

    if (data->parameters[status_code_parameter_is_error].result == f_console_result_found || data->parameters[status_code_parameter_is_warning].result == f_console_result_found || data->parameters[status_code_parameter_is_fine].result == f_console_result_found) {
      if (data->process_pipe) {
        // @todo: call status_code_process_check() here for all data from pipe that is space separated.
      }

      if (data->remaining.used > 0) {
        for (f_array_length_t i = 0; i < data->remaining.used; i++) {

          status2 = status_code_process_check(*data, arguments.argv[data->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for
      }
    }
    else if (data->parameters[status_code_parameter_number].result == f_console_result_found) {
      if (data->process_pipe) {
        // @todo: call status_code_process_number() here for all data from pipe that is space separated.
      }

      if (data->remaining.used > 0) {
        for (f_array_length_t i = 0; i < data->remaining.used; i++) {

          status2 = status_code_process_number(*data, arguments.argv[data->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for
      }
    }
    else {
      if (data->process_pipe) {
        // @todo: call status_code_process_normal() here for all data from pipe that is space separated.
      }

      if (data->remaining.used > 0) {
        for (f_array_length_t i = 0; i < data->remaining.used; i++) {

          status2 = status_code_process_normal(*data, arguments.argv[data->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for
      }
    }

    status_code_delete_data(data);
    return status;
  }
#endif // _di_status_code_main_

#ifndef _di_status_code_delete_data_
  f_return_status status_code_delete_data(status_code_data_t *data) {

    for (f_string_length_t i = 0; i < status_code_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);

    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_status_code_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
