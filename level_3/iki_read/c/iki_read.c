#include "iki_read.h"
#include "private-common.h"
#include "private-iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_help_
  f_status_t iki_read_print_help(const f_file_t output, const f_color_context_t context) {

    flockfile(output.stream);

    fll_program_print_help_header(output, context, iki_read_name_long, iki_read_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_character(f_string_eol_s[0], output.stream);

    fll_program_print_help_option(output, context, iki_read_short_at, iki_read_long_at, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Select variable at this numeric index.");
    fll_program_print_help_option(output, context, iki_read_short_line, iki_read_long_line, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print only the variables at the given line within the file.");
    fll_program_print_help_option(output, context, iki_read_short_name, iki_read_long_name, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Select variables with this name.");
    fll_program_print_help_option(output, context, iki_read_short_whole, iki_read_long_whole, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print all of the data instead of just the IKI variable data.");

    f_print_character(f_string_eol_s[0], output.stream);

    fll_program_print_help_option(output, context, iki_read_short_content, iki_read_long_content, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the variable content (default).");
    fll_program_print_help_option(output, context, iki_read_short_literal, iki_read_long_literal, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the entire variable (aka: object, content, and syntax).");
    fll_program_print_help_option(output, context, iki_read_short_object, iki_read_long_object, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the variable name (aka: object).");
    fll_program_print_help_option(output, context, iki_read_short_total, iki_read_long_total, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print the total number of variables.");

    f_print_character(f_string_eol_s[0], output.stream);

    fll_program_print_help_option(output, context, iki_read_short_substitute, iki_read_long_substitute, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Substitute the entire variable for the given name and content value with the given string.");

    fll_program_print_help_usage(output, context, iki_read_name, "filename(s)");

    fl_print_format(" %[Notes:%]%c", output.stream, context.set.important, context.set.important, f_string_eol_s[0]);
    fl_print_format("  This program will find and print variables, vocabularies, or content following the IKI standard, without focusing on any particular vocabulary specification.%c%c", output.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  This %[%s%s%] option, requires 3 additional parameters:", output.stream, context.set.notable, f_console_symbol_long_enable_s, iki_read_long_substitute, context.set.notable);
    fl_print_format(" %[<%]%s%[>%]", output.stream, context.set.notable, context.set.notable, iki_read_substitution_vocabulary, context.set.notable, context.set.notable);
    fl_print_format(" %[<%]%s%[>%]", output.stream, context.set.notable, context.set.notable, iki_read_substitution_replace, context.set.notable, context.set.notable);
    fl_print_format(" %[<%]%s%[>%].%c", output.stream, context.set.notable, context.set.notable, iki_read_substitution_with, context.set.notable, context.set.notable, f_string_eol_s[0]);

    fl_print_format("    %[%s%]: The name of the vocabulary whose content is to be substituted.%c", output.stream, context.set.notable, iki_read_substitution_vocabulary, context.set.notable, f_string_eol_s[0]);
    fl_print_format("    %[%s%]: The content matching this exact string will be substituted.%c", output.stream, context.set.notable, iki_read_substitution_replace, context.set.notable, f_string_eol_s[0]);
    fl_print_format("    %[%s%]: The new string to use as the substitute.%c%c", output.stream, context.set.notable, iki_read_substitution_with, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  The vocabulary and replacement are case-sensitive and must exactly match.%c%c", output.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  The default behavior is to only display content portion of the IKI variable.%c%c", output.stream, f_string_eol_s[0], f_string_eol_s[0]);

    funlockfile(output.stream);

    return F_none;
  }
#endif // _di_iki_read_print_help_

#ifndef _di_iki_read_main_
  f_status_t iki_read_main(const f_console_arguments_t arguments, iki_read_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, iki_read_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { iki_read_parameter_no_color, iki_read_parameter_light, iki_read_parameter_dark };
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
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);

          if (main->error.verbosity == f_console_verbosity_verbose) {
            fll_print_character(f_string_eol_s[0], main->error.to.stream);
          }

          iki_read_main_delete(main);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { iki_read_parameter_verbosity_quiet, iki_read_parameter_verbosity_normal, iki_read_parameter_verbosity_verbose, iki_read_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          iki_read_main_delete(main);
          return status;
        }

        if (choice == iki_read_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
          main->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == iki_read_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
          main->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == iki_read_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
          main->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == iki_read_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
          main->warning.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[iki_read_parameter_help].result == f_console_result_found) {
      iki_read_print_help(main->output, main->context);

      iki_read_main_delete(main);
      return F_none;
    }

    if (main->parameters[iki_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, iki_read_version);

      iki_read_main_delete(main);
      return F_none;
    }

    if (main->remaining.used > 0 || main->process_pipe) {
      if (main->parameters[iki_read_parameter_at].result == f_console_result_found) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_at, main->error.notable);
          fl_print_format("%[' requires a positive number.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[iki_read_parameter_at].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[iki_read_parameter_at].values.array[main->parameters[iki_read_parameter_at].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &number);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, f_console_symbol_long_enable iki_read_long_at, arguments.argv[index]);

          status = F_status_set_error(F_parameter);
        }

        main->at = number;

        if (main->parameters[iki_read_parameter_whole].result == f_console_result_found) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_at, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_whole, main->error.notable);
            fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters[iki_read_parameter_line].result == f_console_result_found) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_line, main->error.notable);
          fl_print_format("%[' requires a positive number.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[iki_read_parameter_line].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[iki_read_parameter_line].values.array[main->parameters[iki_read_parameter_line].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[index]));

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &number);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, f_console_symbol_long_enable iki_read_long_line, arguments.argv[index]);

          status = F_status_set_error(F_parameter);
        }

        main->line = number;
      }

      if (main->parameters[iki_read_parameter_name].result == f_console_result_found) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_name, main->error.notable);
          fl_print_format("%[' requires a string.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }

      if (main->parameters[iki_read_parameter_substitute].result != f_console_result_none) {
        if (main->parameters[iki_read_parameter_substitute].result == f_console_result_found || main->parameters[iki_read_parameter_substitute].values.used % 3 != 0) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_substitute, main->error.notable);
            fl_print_format("%[' requires 3 strings.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters[iki_read_parameter_total].result == f_console_result_found) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_substitute, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_total, main->error.notable);
            fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters[iki_read_parameter_literal].result == f_console_result_found) {
        if (main->parameters[iki_read_parameter_object].result == f_console_result_found) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_literal, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_object, main->error.notable);
            fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters[iki_read_parameter_content].result == f_console_result_found) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_literal, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_content, main->error.notable);
            fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters[iki_read_parameter_total].result == f_console_result_found) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_literal, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_total, main->error.notable);
            fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        main->mode = iki_read_mode_literal;
      }
      else if (main->parameters[iki_read_parameter_object].result == f_console_result_found) {
        if (main->parameters[iki_read_parameter_content].result == f_console_result_found) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_object, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_content, main->error.notable);
            fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters[iki_read_parameter_total].result == f_console_result_found) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_object, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_total, main->error.notable);
            fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        main->mode = iki_read_mode_object;
      }
      else if (main->parameters[iki_read_parameter_total].result == f_console_result_found) {
        main->mode = iki_read_mode_total;
      }
      else {
        // this is the default behavior, so there is no reason to check for the -c/--content parameter.
        main->mode = iki_read_mode_content;
      }

      if (main->parameters[iki_read_parameter_whole].result == f_console_result_found) {
        if (main->parameters[iki_read_parameter_total].result == f_console_result_found) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_whole, main->error.notable);
            fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_total, main->error.notable);
            fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error(status)) {
        if (main->error.verbosity != f_console_verbosity_quiet) {
          fll_print_character(f_string_eol_s[0], main->error.to.stream);
        }

        iki_read_main_delete(main);
        return F_status_set_error(F_parameter);
      }

      if (main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = f_type_descriptor_input;

        status = f_file_read(file, &main->buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read", F_true, "-", "process", fll_error_file_type_file);
        }
        else {
          status = iki_read_process_buffer(arguments, "-", main);
        }

        // Clear buffers before continuing.
        macro_f_string_dynamic_t_delete_simple(main->buffer);
      }

      if (F_status_is_fine(status) && main->remaining.used > 0) {
        f_array_length_t i = 0;
        f_array_length_t total = 0;
        f_file_t file = f_file_t_initialize;

        for (; i < main->remaining.used; ++i) {
          macro_f_file_t_reset(file);
          total = 0;

          status = f_file_open(arguments.argv[main->remaining.array[i]], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_open", F_true, arguments.argv[main->remaining.array[i]], "process", fll_error_file_type_file);
            break;
          }

          status = f_file_size_by_id(file.id, &total);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_size_by_id", F_true, arguments.argv[main->remaining.array[i]], "process", fll_error_file_type_file);

            f_file_stream_close(F_true, &file);
            break;
          }

          // Skip past empty files.
          if (!total) {
            f_file_stream_close(F_true, &file);
            continue;
          }

          status = f_file_read_until(file, total, &main->buffer);

          f_file_stream_close(F_true, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read_until", F_true, arguments.argv[main->remaining.array[i]], "process", fll_error_file_type_file);
            break;
          }

          status = iki_read_process_buffer(arguments, arguments.argv[main->remaining.array[i]], main);
          if (F_status_is_error(status)) break;

          // Clear buffers before repeating the loop.
          macro_f_string_dynamic_t_delete_simple(main->buffer);
        } // for
      }
    }
    else {
      if (main->error.verbosity != f_console_verbosity_quiet) {
        fll_print_format("%c%[%sYou failed to specify one or more files.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context, f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status) || !main->mode) {
        fll_print_character(f_string_eol_s[0], main->error.to.stream);
      }
    }

    iki_read_main_delete(main);
    return status;
  }
#endif // _di_iki_read_main_

#ifndef _di_iki_read_main_delete_
  f_status_t iki_read_main_delete(iki_read_main_t *main) {

    for (f_array_length_t i = 0; i < iki_read_total_parameters; ++i) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);
    macro_f_string_dynamic_t_delete_simple(main->buffer);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_iki_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
