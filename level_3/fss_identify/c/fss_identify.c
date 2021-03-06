#include "fss_identify.h"
#include "private-common.h"
#include "private-fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_print_help_
  f_status_t fss_identify_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, fss_identify_name_long, fss_identify_version);

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

    fll_program_print_help_option(output, context, fss_identify_short_content, fss_identify_long_content, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the Identifier content (the 4-digit hexidecimal type code).");
    fll_program_print_help_option(output, context, fss_identify_short_object, fss_identify_long_object, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the Identifier object (the name).");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fll_program_print_help_option(output, context, fss_identify_short_line, fss_identify_long_line, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print only the Identifier at the given line.");
    fll_program_print_help_option(output, context, fss_identify_short_name, fss_identify_long_name, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Select Object with this name.");
    fll_program_print_help_option(output, context, fss_identify_short_total, fss_identify_long_total, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the total Identifiers found.");

    fll_program_print_help_usage(output, context, fss_identify_name, "filename(s)");

    fprintf(output.stream, "  The ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_line);
    fprintf(output.stream, " parameter refers to the output lines and not the lines in a given file.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  If neither the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_object);
    fprintf(output.stream, " nor ", f_string_eol_s[0]);
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_content);
    fprintf(output.stream, " are specified, then the default behavior is to print both.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  When specifying the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_total);
    fprintf(output.stream, " parameter, neither the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_object);
    fprintf(output.stream, " nor the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_content);
    fprintf(output.stream, " parameter may be specified.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  An FSS file is identified by the following format: '");
    f_color_print(output.stream, context.set.notable, "# Object-Content");
    fprintf(output.stream, "' where the Object, is a machine-name representing the name and may only consist of \"word\" characters and the Content is a 4-digit hexidecimal number representing a particular variant of the Object.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  This identifier, if provided, must exist on the first line in a file and must begin with the pound character: '#'.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  Whitespace must follow this pound character.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  There may be multiple Object and Content pairs, separated by whitspace, such as: \"# fss-0002 fss-0000 iki-0002\".%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_fss_identify_print_help_

#ifndef _di_fss_identify_main_
  f_status_t fss_identify_main(const f_console_arguments_t arguments, fss_identify_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, fss_identify_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_identify_parameter_no_color, fss_identify_parameter_light, fss_identify_parameter_dark };
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

          fss_identify_main_delete(main);

          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_identify_parameter_verbosity_quiet, fss_identify_parameter_verbosity_normal, fss_identify_parameter_verbosity_verbose, fss_identify_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_identify_main_delete(main);

          return status;
        }

        if (choice == fss_identify_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_identify_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_identify_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_identify_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[fss_identify_parameter_help].result == f_console_result_found) {
      fss_identify_print_help(main->output, main->context);

      fss_identify_main_delete(main);

      return F_none;
    }

    if (main->parameters[fss_identify_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, fss_identify_version);

      fss_identify_main_delete(main);

      return F_none;
    }

    fss_identify_data_t data = fss_identify_data_t_initialize;

    if (F_status_is_error_not(status)) {
      if (main->parameters[fss_identify_parameter_line].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter ", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_line);
        f_color_print(main->error.to.stream, main->context.set.error, " requires a positive number.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[fss_identify_parameter_line].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[fss_identify_parameter_line].values.array[main->parameters[fss_identify_parameter_line].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strnlen(arguments.argv[index], f_console_parameter_size));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &data.line);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_identify_long_line, arguments.argv[index]);
        }
      }
    }

    if (F_status_is_error_not(status) && main->parameters[fss_identify_parameter_total].result == f_console_result_found) {
      if (main->parameters[fss_identify_parameter_object].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sCannot specify the ", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_object);
        f_color_print(main->error.to.stream, main->context.set.error, " parameter with the ");
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_total);
        f_color_print(main->error.to.stream, main->context.set.error, " parameter.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[fss_identify_parameter_content].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sCannot specify the ", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_content);
        f_color_print(main->error.to.stream, main->context.set.error, " parameter with the ");
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_total);
        f_color_print(main->error.to.stream, main->context.set.error, " parameter.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters[fss_identify_parameter_name].result == f_console_result_found) {
        f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter ", fll_error_print_error);
        f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_name);
        f_color_print(main->error.to.stream, main->context.set.error, " requires a string.%c", f_string_eol_s[0]);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[fss_identify_parameter_name].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[fss_identify_parameter_name].values.array[main->parameters[fss_identify_parameter_name].values.used - 1];
        const f_array_length_t length = strnlen(arguments.argv[index], f_console_parameter_size);
        const f_string_range_t range = macro_f_string_range_t_initialize(length);

        if (length == 0) {
          f_color_print(main->error.to.stream, main->context.set.error, "%sThe parameter ", fll_error_print_error);
          f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_name);
          f_color_print(main->error.to.stream, main->context.set.error, " does not allow zero length strings.%c", f_string_eol_s[0]);

          status = F_status_set_error(F_parameter);
        }
        else {
          status = f_string_dynamic_resize(length, &data.name);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word", F_true);
          }
        }

        if (F_status_is_error_not(status)) {

          for (f_array_length_t i = range.start; i <= range.stop; ++i) {

            status = f_utf_is_word(arguments.argv[index] + i, length, F_true);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word", F_true);

              break;
            }
            else if (status == F_false) {
              f_color_print(main->error.to.stream, main->context.set.error, "%sThe value '", fll_error_print_error);
              f_color_print(main->error.to.stream, main->context.set.notable, "%s", arguments.argv[index]);
              f_color_print(main->error.to.stream, main->context.set.error, "' for the parameter ", fll_error_print_error);
              f_color_print(main->error.to.stream, main->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_identify_long_name);
              f_color_print(main->error.to.stream, main->context.set.error, " may only contain word characters.%c", f_string_eol_s[0]);

              status = F_status_set_error(F_parameter);

              break;
            }

            data.name.string[data.name.used++] = arguments.argv[index][i];
          } // for
        }
      }
    }

    f_string_range_t range = f_string_range_t_initialize;
    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_file_t file = f_file_t_initialize;

    if (F_status_is_error_not(status) && main->process_pipe) {
      file.id = f_type_descriptor_input;
      file.stream = f_type_input;
      file.size_read = 512;

      status = fss_identify_load_line(*main, file, "-", &buffer, &range);

      if (F_status_is_error_not(status)) {
        status = fss_identify_process(*main, "-", buffer, &range, &data);
      }
    }

    if (F_status_is_error_not(status)) {

      for (f_array_length_t i = 0; i < main->remaining.used; ++i) {

        if (main->parameters[fss_identify_parameter_line].result == f_console_result_additional) {
          if (data.current > data.line) break;
        }

        macro_f_file_t_reset(file);

        file.size_read = 512;

        status = f_file_stream_open(arguments.argv[main->remaining.array[i]], 0, &file);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments.argv[main->remaining.array[i]], "open", fll_error_file_type_file);
        }
        else {
          status = fss_identify_load_line(*main, file, arguments.argv[main->remaining.array[i]], &buffer, &range);

          if (F_status_is_error_not(status)) {
            status = fss_identify_process(*main, arguments.argv[main->remaining.array[i]], buffer, &range, &data);
          }
        }

        f_file_stream_close(F_true, &file);

        if (F_status_is_error(status)) break;
      } // for
    }

    f_string_dynamic_resize(0, &buffer);

    if (F_status_is_error_not(status)) {
      if (main->parameters[fss_identify_parameter_total].result == f_console_result_found) {
        fprintf(main->output.stream, "%llu%c", data.total, f_string_eol_s[0]);
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(main->error.to.stream, "%c", f_string_eol_s[0]);
      }
    }

    fss_identify_data_delete(&data);
    fss_identify_main_delete(main);

    return status;
  }
#endif // _di_fss_identify_main_

#ifndef _di_fss_identify_main_delete_
  f_status_t fss_identify_main_delete(fss_identify_main_t *main) {

    for (f_array_length_t i = 0; i < fss_identify_total_parameters; ++i) {

      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fss_identify_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
