#include "status_code.h"
#include "private-common.h"
#include "private-status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_print_help_
  f_status_t status_code_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, status_code_progam_name_long_s, status_code_progam_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, f_console_symbol_short_enable_s.string, f_console_symbol_long_enable_s.string, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, f_console_symbol_short_disable_s.string, f_console_symbol_long_disable_s.string, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, f_console_symbol_short_disable_s.string, f_console_symbol_long_disable_s.string, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, f_console_symbol_short_disable_s.string, f_console_symbol_long_disable_s.string, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, f_console_symbol_short_disable_s.string, f_console_symbol_long_disable_s.string, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, f_console_symbol_short_disable_s.string, f_console_symbol_long_disable_s.string, "  Set verbosity to normal file.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, f_console_symbol_short_disable_s.string, f_console_symbol_long_disable_s.string, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, f_console_symbol_short_disable_s.string, f_console_symbol_long_disable_s.string, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, f_console_symbol_short_disable_s.string, f_console_symbol_long_disable_s.string, " Print only the version number.");

    f_print_dynamic(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, status_code_short_is_fine_s, status_code_long_is_fine_s, f_console_symbol_short_enable_s.string, f_console_symbol_long_enable_s.string, "   Print F_true if the error code is not an error, F_false otherwise.");
    fll_program_print_help_option(file, context, status_code_short_is_warning_s, status_code_long_is_warning_s, f_console_symbol_short_enable_s.string, f_console_symbol_long_enable_s.string, "Print F_true if the error code is a warning, F_false otherwise.");
    fll_program_print_help_option(file, context, status_code_short_is_error_s, status_code_long_is_error_s, f_console_symbol_short_enable_s.string, f_console_symbol_long_enable_s.string, "  Print F_true if the error code is an error, F_false otherwise.");
    fll_program_print_help_option(file, context, status_code_short_number_s, status_code_long_number_s, f_console_symbol_short_enable_s.string, f_console_symbol_long_enable_s.string, "    Convert status code name to number.");

    fll_program_print_help_usage(file, context, status_code_progam_name_s, "status code(s)");

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_status_code_print_help_

#ifndef _di_status_code_main_
  f_status_t status_code_main(status_code_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, status_code_total_parameters_d);

      {
        f_console_parameter_id_t ids[3] = { status_code_parameter_no_color_e, status_code_parameter_light_e, status_code_parameter_dark_e };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(*arguments, parameters, choices, F_true, &main->remaining, &main->context);

        main->output.set = &main->context.set;
        main->error.set = &main->context.set;
        main->warning.set = &main->context.set;

        if (main->context.set.error.before) {
          main->output.context = f_color_set_empty_s;
          main->output.notable = main->context.set.notable;

          main->error.context = main->context.set.error;
          main->error.notable = main->context.set.notable;

          main->warning.context = main->context.set.warning;
          main->warning.notable = main->context.set.notable;
        }
        else {
          f_color_set_t *sets[] = { &main->output.context, &main->output.notable, &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

          fll_program_parameter_process_empty(&main->context, sets);
        }

        if (F_status_is_error(status)) {
          status_code_main_delete(main);

          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { status_code_parameter_verbosity_quiet_e, status_code_parameter_verbosity_normal_e, status_code_parameter_verbosity_verbose_e, status_code_parameter_verbosity_debug_e };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          status_code_main_delete(main);
          return status;
        }

        if (choice == status_code_parameter_verbosity_quiet_e) {
          main->output.verbosity = f_console_verbosity_quiet_e;
          main->error.verbosity = f_console_verbosity_quiet_e;
          main->warning.verbosity = f_console_verbosity_quiet_e;
        }
        else if (choice == status_code_parameter_verbosity_normal_e) {
          main->output.verbosity = f_console_verbosity_normal_e;
          main->error.verbosity = f_console_verbosity_normal_e;
          main->warning.verbosity = f_console_verbosity_normal_e;
        }
        else if (choice == status_code_parameter_verbosity_verbose_e) {
          main->output.verbosity = f_console_verbosity_verbose_e;
          main->error.verbosity = f_console_verbosity_verbose_e;
          main->warning.verbosity = f_console_verbosity_verbose_e;
        }
        else if (choice == status_code_parameter_verbosity_debug_e) {
          main->output.verbosity = f_console_verbosity_debug_e;
          main->error.verbosity = f_console_verbosity_debug_e;
          main->warning.verbosity = f_console_verbosity_debug_e;
        }
      }

      status = F_none;
    }

    if (main->parameters[status_code_parameter_help_e].result == f_console_result_found_e) {
      status_code_print_help(main->output.to, main->context);

      status_code_main_delete(main);

      return F_none;
    }

    if (main->parameters[status_code_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, status_code_progam_version_s);

      status_code_main_delete(main);

      return F_none;
    }

    if (main->parameters[status_code_parameter_is_error_e].result == f_console_result_found_e) {
      if (main->parameters[status_code_parameter_is_warning_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%q%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%q%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, status_code_long_is_error_s, main->error.notable);
        fl_print_format("%[' cannot be used with the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%q%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, status_code_long_is_warning_s, main->error.notable);
        fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);

        status_code_main_delete(main);

        return F_status_set_error(status);
      }
      else if (main->parameters[status_code_parameter_is_fine_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%q%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%q%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, status_code_long_is_error_s, main->error.notable);
        fl_print_format("%[' cannot be used with the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%q%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, status_code_long_is_fine_s, main->error.notable);
        fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);

        status_code_main_delete(main);

        return F_status_set_error(status);
      }
    }
    else if (main->parameters[status_code_parameter_is_warning_e].result == f_console_result_found_e && main->parameters[status_code_parameter_is_fine_e].result == f_console_result_found_e) {
      flockfile(main->error.to.stream);

      fl_print_format("%q%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
      fl_print_format("%[%q%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, status_code_long_is_warning_s, main->error.notable);
      fl_print_format("%[' cannot be used with the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
      fl_print_format("%[%q%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, status_code_long_is_fine_s, main->error.notable);
      fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

      funlockfile(main->error.to.stream);

      status_code_main_delete(main);

      return F_status_set_error(status);
    }

    if (main->remaining.used == 0 && !main->process_pipe) {
      fll_print_format("%[You failed to specify a status code.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

      status_code_main_delete(main);

      return F_status_set_error(F_parameter);
    }

    f_status_t status2 = F_none;

    if (main->parameters[status_code_parameter_is_error_e].result == f_console_result_found_e || main->parameters[status_code_parameter_is_warning_e].result == f_console_result_found_e || main->parameters[status_code_parameter_is_fine_e].result == f_console_result_found_e) {
      if (main->process_pipe) {
        // @todo call status_code_process_check() here for all main from pipe that is space separated.
      }

      if (main->remaining.used > 0) {
        uint16_t signal_check = 0;

        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->remaining.used; ++i) {

          if (!((++signal_check) % status_code_signal_check_d)) {
            if (status_code_signal_received(main)) {
              status = F_status_set_error(F_signal);
              break;
            }

            signal_check = 0;
          }

          status2 = status_code_process_check(main, arguments->argv[main->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }
    else if (main->parameters[status_code_parameter_number_e].result == f_console_result_found_e) {
      if (main->process_pipe) {
        // @todo call status_code_process_number() here for all main from pipe that is space separated.
      }

      if (main->remaining.used > 0) {
        uint16_t signal_check = 0;

        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->remaining.used; ++i) {

          if (!((++signal_check) % status_code_signal_check_d)) {
            if (status_code_signal_received(main)) {
              status = F_status_set_error(F_signal);
              break;
            }

            signal_check = 0;
          }

          status2 = status_code_process_number(main, arguments->argv[main->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }
    else {
      if (main->process_pipe) {
        // @todo call status_code_process_normal() here for all main from pipe that is space separated.
      }

      if (main->remaining.used > 0) {
        uint16_t signal_check = 0;

        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->remaining.used; ++i) {

          if (!((++signal_check) % status_code_signal_check_d)) {
            if (status_code_signal_received(main)) {
              status = F_status_set_error(F_signal);
              break;
            }

            signal_check = 0;
          }

          status2 = status_code_process_normal(main, arguments->argv[main->remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }

    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        fflush(main->output.to.stream);

        fll_print_dynamic(f_string_eol_s, main->output.to.stream);
      }
    }

    status_code_main_delete(main);

    return status;
  }
#endif // _di_status_code_main_

#ifndef _di_status_code_main_delete_
  f_status_t status_code_main_delete(status_code_main_t * const main) {

    for (f_array_length_t i = 0; i < status_code_total_parameters_d; ++i) {

      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_status_code_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
