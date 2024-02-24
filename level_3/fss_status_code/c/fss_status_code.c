#include "fss_status_code.h"
#include "private-common.h"
#include "private-fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_print_copyright_
  f_status_t fss_status_code_print_copyright(const f_file_t file, const bool full) {

    flockfile(file.stream);

    fl_print_format("%rCopyright © 2007-2024 Kevin Day.%r", file.stream, f_string_eol_s, f_string_eol_s);

    #ifndef _di_detailed_copyright_
      if (full) {
        fl_print_format("%rThis program comes with ABSOLUTELY NO WARRANTY.%r", file.stream, f_string_eol_s, f_string_eol_s);
        fl_print_format("This is free software, and you are welcome to modify or redistribute in accordance to the license.%r", file.stream, f_string_eol_s);
      }
    #endif // _di_detailed_copyright_

    fl_print_format("%rSource code license lgpl-2.1-or-later.%r", file.stream, f_string_eol_s, f_string_eol_s);
    fl_print_format("Standard and specification license open-standard-license-1.0.%r", file.stream, f_string_eol_s);
    fl_print_format("Documentation license cc-by-sa-4.0.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_status_code_print_copyright_

#ifndef _di_fss_status_code_print_help_
  f_status_t fss_status_code_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, fss_status_code_program_name_long_s, fss_status_code_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_copyright_s, f_console_standard_long_copyright_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Print the copyright.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "     Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Do not print using color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Decrease verbosity, using only error output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Set verbosity to normal.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, fss_status_code_short_fine_s, fss_status_code_long_fine_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Print F_true or F_false if status code is neither an error nor a warning or print number with neither the error code nor the warning code bits set.");
    fll_program_print_help_option(file, context, fss_status_code_short_warning_s, fss_status_code_long_warning_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print F_true or F_false if status code is a warning or print number with warning code bit set.");
    fll_program_print_help_option(file, context, fss_status_code_short_error_s, fss_status_code_long_error_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print F_true or F_false if status code is an error or print number with error code bit set.");
    fll_program_print_help_option(file, context, fss_status_code_short_number_s, fss_status_code_long_number_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Convert status code name to number.");

    fll_program_print_help_usage(file, context, fss_status_code_program_name_s, fss_status_code_program_help_parameters_s);

    fl_print_format("  The FLL programs use a %[16-bit unsigned integer%] to represent the return status of programs and functions.%r%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Programs may print a generic error with one of these codes.%r", file.stream, f_string_eol_s);
    fl_print_format("  This is a tool for converting to or converting from these codes.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[16-bit unsigned integer%] also has the first two high-order bits used to represent flags.%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  These flags are the %[error%] bit and the %[warning%] bit.%r", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  When neither of these flags are set, then the status is considered %[fine%].%r%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This operates identical to the %[status_codes%] program except that this program handles additional codes regarding FSS.%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  These special codes numericaly appear after the %[F_status_code_last%] code.%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  These codes stop at the %[F_fss_status_code_last%] code.%r%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Each code will be printed on its own line.%r", file.stream, f_string_eol_s);
    fl_print_format("  Errors regarding each code may be printed on its own line.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_status_code_print_help_

#ifndef _di_fss_status_code_main_
  f_status_t fss_status_code_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      f_console_parameter_id_t ids[3] = { fss_status_code_parameter_no_color_e, fss_status_code_parameter_light_e, fss_status_code_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = fll_program_parameter_process(*arguments, &main->parameters, choices, F_true, &main->context);

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

      if (F_status_is_error(status)) return status;
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[5] = { fss_status_code_parameter_verbosity_quiet_e, fss_status_code_parameter_verbosity_error_e, fss_status_code_parameter_verbosity_normal_e, fss_status_code_parameter_verbosity_verbose_e, fss_status_code_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == fss_status_code_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == fss_status_code_parameter_verbosity_error_e) {
        main->output.verbosity = f_console_verbosity_error_e;
        main->error.verbosity = f_console_verbosity_error_e;
        main->warning.verbosity = f_console_verbosity_error_e;
      }
      else if (choice == fss_status_code_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == fss_status_code_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == fss_status_code_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    if (main->parameters.array[fss_status_code_parameter_help_e].result == f_console_result_found_e) {
      fss_status_code_print_help(main->output.to, main->context);

      return F_none;
    }

    if (main->parameters.array[fss_status_code_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, fss_status_code_program_version_s);

      return F_none;
    }

    if (main->parameters.array[fss_status_code_parameter_copyright_e].result == f_console_result_found_e) {
      fss_status_code_print_copyright(main->output.to, main->output.verbosity > f_console_verbosity_error_e);

      return F_none;
    }

    status = F_none;

    f_string_static_t * const argv = main->parameters.arguments.array;

    if (main->parameters.array[fss_status_code_parameter_error_e].result == f_console_result_found_e) {
      if (main->parameters.array[fss_status_code_parameter_warning_e].result == f_console_result_found_e) {
        if (main->parameters.array[fss_status_code_parameter_number_e].result == f_console_result_none_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QCannot specify the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_status_code_long_error_s, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_status_code_long_warning_s, main->error.notable);
            fl_print_format("%[' parameter when not also specifying the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_status_code_long_number_s, main->error.notable);
            fl_print_format("%[' parameter.%]%r%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          return F_status_set_error(status);
        }
      }

      if (main->parameters.array[fss_status_code_parameter_fine_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          fll_program_parameter_long_print_cannot_use_with(main->error, fss_status_code_long_error_s, fss_status_code_long_fine_s);
          fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
        }

        return F_status_set_error(status);
      }
    }
    else if (main->parameters.array[fss_status_code_parameter_warning_e].result == f_console_result_found_e && main->parameters.array[fss_status_code_parameter_fine_e].result == f_console_result_found_e) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        fll_program_parameter_long_print_cannot_use_with(main->error, fss_status_code_long_warning_s, fss_status_code_long_fine_s);
        fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
      }

      return F_status_set_error(status);
    }

    if (main->parameters.remaining.used == 0 && !main->process_pipe) {
      fll_print_format("%[You failed to specify an error code.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

      return F_status_set_error(F_parameter);
    }

    f_status_t status2 = F_none;

    if (main->parameters.array[fss_status_code_parameter_number_e].result == f_console_result_found_e) {
      if (main->process_pipe) {
        // @todo call fss_status_code_process_number() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fss_status_code_print_signal_received(main);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_number(main, argv[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }
    else if (main->parameters.array[fss_status_code_parameter_error_e].result == f_console_result_found_e || main->parameters.array[fss_status_code_parameter_warning_e].result == f_console_result_found_e || main->parameters.array[fss_status_code_parameter_fine_e].result == f_console_result_found_e) {
      if (main->process_pipe) {
        // @todo call fss_status_code_process_check() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fss_status_code_print_signal_received(main);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_check(main, argv[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }
    else {
      if (main->process_pipe) {
        // @todo call fss_status_code_process_normal() here for all main from pipe that is space separated.
      }

      if (main->parameters.remaining.used) {
        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % fss_status_code_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              fss_status_code_print_signal_received(main);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          status2 = fss_status_code_process_normal(main, argv[main->parameters.remaining.array[i]]);

          if (F_status_is_error(status2) && status == F_none) {
            status = status2;
          }
        } // for

        funlockfile(main->output.to.stream);
      }
    }

    if (F_status_set_fine(status) == F_interrupt) {
      if (main->output.verbosity != f_console_verbosity_quiet_e) {
        fflush(main->output.to.stream);

        fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
      }
    }

    return status;
  }
#endif // _di_fss_status_code_main_

#ifdef __cplusplus
} // extern "C"
#endif
