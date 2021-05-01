#include "fss_status_code.h"
#include "private-common.h"
#include "private-fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_print_help_
  f_status_t fss_status_code_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, fss_status_code_name_long, fss_status_code_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fll_program_print_help_option(output, context, fss_status_code_short_is_fine, fss_status_code_long_is_fine, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Print F_true if the error code is not an error, F_false otherwise.");
    fll_program_print_help_option(output, context, fss_status_code_short_is_warning, fss_status_code_long_is_warning, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print F_true if the error code is a warning, F_false otherwise.");
    fll_program_print_help_option(output, context, fss_status_code_short_is_error, fss_status_code_long_is_error, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print F_true if the error code is an error, F_false otherwise.");
    fll_program_print_help_option(output, context, fss_status_code_short_number, fss_status_code_long_number, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Convert status code name to number.");

    fll_program_print_help_usage(output, context, fss_status_code_name, "status code(s)");

    return F_none;
  }
#endif // _di_fss_status_code_print_help_

#ifndef _di_fss_status_code_main_
  f_status_t fss_status_code_main(const f_console_arguments_t arguments, fss_status_code_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, fss_status_code_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_status_code_parameter_no_color, fss_status_code_parameter_light, fss_status_code_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &main->remaining, &main->context);

        if (main->context.set.error.before) {
          main->error.context = main->context.set.error;
          main->error.notable = main->context.set.notable;
        }
        else {
          f_color_set_t *sets[] = { &main->error.context, &main->error.notable, 0 };

          fll_program_parameter_process_empty(&main->context, sets);
        }

        if (F_status_is_error(status)) {
          fss_status_code_main_delete(main);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_status_code_parameter_verbosity_quiet, fss_status_code_parameter_verbosity_normal, fss_status_code_parameter_verbosity_verbose, fss_status_code_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_status_code_main_delete(main);
          return status;
        }

        if (choice == fss_status_code_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_status_code_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_status_code_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_status_code_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[fss_status_code_parameter_help].result == f_console_result_found) {
      fss_status_code_print_help(main->output, main->context);

      fss_status_code_main_delete(main);
      return F_none;
    }

    if (main->parameters[fss_status_code_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, fss_status_code_version);

      fss_status_code_main_delete(main);
      return F_none;
    }

    if (main->parameters[fss_status_code_parameter_is_error].result == f_console_result_found) {
      if (main->parameters[fss_status_code_parameter_is_warning].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_status_code_long_is_error);
        f_color_print(main->error.to.stream, main->context.set.error, "' cannot be used with the parameter ");
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_status_code_long_is_warning);
        f_color_print(main->error.to.stream, main->context.set.error, ".%c", f_string_eol_s[0]);

        fss_status_code_main_delete(main);
        return F_status_set_error(status);
      }
      else if (main->parameters[fss_status_code_parameter_is_fine].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_status_code_long_is_error);
        f_color_print(main->error.to.stream, main->context.set.error, "' cannot be used with the parameter ");
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_status_code_long_is_fine);
        f_color_print(main->error.to.stream, main->context.set.error, ".%c", f_string_eol_s[0]);

        fss_status_code_main_delete(main);
        return F_status_set_error(status);
      }
    }
    else if (main->parameters[fss_status_code_parameter_is_warning].result == f_console_result_found && main->parameters[fss_status_code_parameter_is_fine].result == f_console_result_found) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter '", fll_error_print_error);
      f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_status_code_long_is_warning);
      f_color_print(main->error.to.stream, main->context.set.error, "' cannot be used with the parameter ");
      f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_status_code_long_is_fine);
      f_color_print(main->error.to.stream, main->context.set.error, ".%c", f_string_eol_s[0]);

      fss_status_code_main_delete(main);
      return F_status_set_error(status);
    }

    if (main->remaining.used == 0 && !main->process_pipe) {
      f_color_print(main->error.to.stream, main->context.set.error, "%sYou failed to specify an error code.%c", fll_error_print_error, f_string_eol_s[0]);

      fss_status_code_main_delete(main);
      return F_status_set_error(F_parameter);
    }

    f_status_t status2 = F_none;

    if (main->parameters[fss_status_code_parameter_is_error].result == f_console_result_found || main->parameters[fss_status_code_parameter_is_warning].result == f_console_result_found || main->parameters[fss_status_code_parameter_is_fine].result == f_console_result_found) {
      if (main->process_pipe) {
        // @todo: call fss_status_code_process_check() here for all main from pipe that is space separated.
      }

      if (main->remaining.used > 0) {
        for (f_array_length_t i = 0; i < main->remaining.used; i++) {

          status2 = fss_status_code_process_check(*main, arguments.argv[main->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for
      }
    }
    else if (main->parameters[fss_status_code_parameter_number].result == f_console_result_found) {
      if (main->process_pipe) {
        // @todo: call fss_status_code_process_number() here for all main from pipe that is space separated.
      }

      if (main->remaining.used > 0) {
        for (f_array_length_t i = 0; i < main->remaining.used; i++) {

          status2 = fss_status_code_process_number(*main, arguments.argv[main->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for
      }
    }
    else {
      if (main->process_pipe) {
        // @todo: call fss_status_code_process_normal() here for all main from pipe that is space separated.
      }

      if (main->remaining.used > 0) {
        for (f_array_length_t i = 0; i < main->remaining.used; i++) {
          status2 = fss_status_code_process_normal(*main, arguments.argv[main->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for
      }
    }

    fss_status_code_main_delete(main);
    return status;
  }
#endif // _di_fss_status_code_main_

#ifndef _di_fss_status_code_main_delete_
  f_status_t fss_status_code_main_delete(fss_status_code_main_t *main) {

    for (f_array_length_t i = 0; i < fss_status_code_total_parameters; i++) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fss_status_code_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
