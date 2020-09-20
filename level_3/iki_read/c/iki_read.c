#include "iki_read.h"
#include "private-iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_help_
  f_return_status iki_read_print_help(const f_color_context_t context) {

    fll_program_print_help_header(context, iki_read_name_long, iki_read_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, iki_read_short_at, iki_read_long_at, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Select variable at this numeric index.");
    fll_program_print_help_option(context, iki_read_short_line, iki_read_long_line, f_console_symbol_short_enable, f_console_symbol_long_enable, " Print only the variables at the given line.");
    fll_program_print_help_option(context, iki_read_short_name, iki_read_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, " Select variables with this name.");
    fll_program_print_help_option(context, iki_read_short_whole, iki_read_long_whole, f_console_symbol_short_enable, f_console_symbol_long_enable, "Print all of the data instead of just the variable data.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, iki_read_short_content, iki_read_long_content, f_console_symbol_short_enable, f_console_symbol_long_enable, "Print the variable content (default).");
    fll_program_print_help_option(context, iki_read_short_literal, iki_read_long_literal, f_console_symbol_short_enable, f_console_symbol_long_enable, "Print the entire variable (aka: object, content, and syntax).");
    fll_program_print_help_option(context, iki_read_short_object, iki_read_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, " Print the variable name (aka: object).");
    fll_program_print_help_option(context, iki_read_short_total, iki_read_long_total, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Print the total number of variables.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, iki_read_short_substitute, iki_read_long_substitute, f_console_symbol_short_enable, f_console_symbol_long_enable, "Substitute the entire variable for the given name and content value with the given string.");

    fll_program_print_help_usage(context, iki_read_name, "filename(s)");

    fl_color_print(f_type_output, context.set.important, " Notes:");

    printf("%c", f_string_eol[0], f_string_eol[0]);

    printf("  This program will find and print variables, vocabularies, or content following the IKI standard, without focusing on any particular vocabulary specification.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The ");
    fl_color_print(f_type_output, context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_substitute);
    printf(" option, requires 3 additional parameters: ");

    fl_color_print(f_type_output, context.set.notable, "<");
    printf("%s", iki_read_substitution_vocabulary);
    fl_color_print(f_type_output, context.set.notable, ">");
    printf(" ");
    fl_color_print(f_type_output, context.set.notable, "<");
    printf("%s", iki_read_substitution_replace);
    fl_color_print(f_type_output, context.set.notable, ">");
    printf(" ");
    fl_color_print(f_type_output, context.set.notable, "<");
    printf("%s", iki_read_substitution_with);
    fl_color_print(f_type_output, context.set.notable, ">");
    printf(".%c", f_string_eol[0]);

    fl_color_print(f_type_output, context.set.notable, "    %s", iki_read_substitution_vocabulary);
    printf(": The name of the vocabulary whose content is to be substituted.%c", f_string_eol[0]);

    fl_color_print(f_type_output, context.set.notable, "    %s", iki_read_substitution_replace);
    printf(":    The content matching this exact string will be substituted.%c", f_string_eol[0]);

    fl_color_print(f_type_output, context.set.notable, "    %s", iki_read_substitution_with);
    printf(":       The new string to use as the substitute.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The vocabulary and replacement are case-sensitive and must exactly match.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The default behavior is to only display content portion of the IKI variable.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    return F_none;
  }
#endif // _di_iki_read_print_help_

#ifndef _di_iki_read_main_
  f_return_status iki_read_main(const f_console_arguments_t arguments, iki_read_data_t *data) {
    f_status_t status = F_none;

    {
      f_console_parameter_id_t ids[3] = { iki_read_parameter_no_color, iki_read_parameter_light, iki_read_parameter_dark };
      const f_console_parameter_ids_t choices = { ids, 3 };
      const f_console_parameters_t parameters = { data->parameters, iki_read_total_parameters };

      status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

      if (F_status_is_error(status)) {
        iki_read_print_error(data->context, data->verbosity, F_status_set_fine(status), "fll_program_parameter_process", F_true);

        if (data->verbosity == iki_read_verbosity_verbose) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
        }

        iki_read_delete_data(data);
        return F_status_set_error(status);
      }

      status = F_none;
    }

    if (data->parameters[iki_read_parameter_help].result == f_console_result_found) {
      iki_read_print_help(data->context);

      iki_read_delete_data(data);
      return status;
    }
    else if (data->parameters[iki_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(iki_read_version);

      iki_read_delete_data(data);
      return status;
    }

    if (data->parameters[iki_read_parameter_verbose].result == f_console_result_found) {
      if (data->parameters[iki_read_parameter_quiet].result == f_console_result_found) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
        fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, f_console_standard_long_verbose);
        fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
        fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, f_console_standard_long_quiet);
        fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");

        status = F_status_set_error(F_parameter);
      }

      data->verbosity = iki_read_verbosity_verbose;
    }
    else if (data->parameters[iki_read_parameter_quiet].result == f_console_result_found) {
      data->verbosity = iki_read_verbosity_quiet;
    }
    else {
      data->verbosity = iki_read_verbosity_normal;
    }

    if (F_status_is_fine(status)) {
      if (data->remaining.used > 0 || data->process_pipe) {
        if (data->parameters[iki_read_parameter_at].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.set.error, "ERROR: The parameter '");
            fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_at);
            fl_color_print_line(f_type_error, data->context.set.error, "' requires a positive number.");
          }

          status = F_status_set_error(F_parameter);
        }
        else if (data->parameters[iki_read_parameter_at].result == f_console_result_additional) {
          const f_string_length_t index = data->parameters[iki_read_parameter_at].additional.array[data->parameters[iki_read_parameter_at].additional.used - 1];
          const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

          f_number_unsigned_t number = 0;

          status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);

          if (F_status_is_error(status)) {
            iki_read_print_error_number_argument(data->context, data->verbosity, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", iki_read_long_line, arguments.argv[index]);

            status = F_status_set_error(F_parameter);
          }

          data->at = number;

          if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_at);
              fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_total);
              fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");
            }

            status = F_status_set_error(F_parameter);
          }
        }

        if (data->parameters[iki_read_parameter_line].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.set.error, "ERROR: The parameter '");
            fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_line);
            fl_color_print_line(f_type_error, data->context.set.error, "' requires a positive number.");
          }

          status = F_status_set_error(F_parameter);
        }
        else if (data->parameters[iki_read_parameter_line].result == f_console_result_additional) {
          const f_string_length_t index = data->parameters[iki_read_parameter_line].additional.array[data->parameters[iki_read_parameter_line].additional.used - 1];
          const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

          f_number_unsigned_t number = 0;

          status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);

          if (F_status_is_error(status)) {
            iki_read_print_error_number_argument(data->context, data->verbosity, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", iki_read_long_line, arguments.argv[index]);

            status = F_status_set_error(F_parameter);
          }

          data->line = number;
        }

        if (data->parameters[iki_read_parameter_name].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.set.error, "ERROR: The parameter '");
            fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_name);
            fl_color_print_line(f_type_error, data->context.set.error, "' requires a string.");
          }

          status = F_status_set_error(F_parameter);
        }

        if (data->parameters[iki_read_parameter_substitute].result != f_console_result_none) {
          if (data->parameters[iki_read_parameter_substitute].result == f_console_result_found || data->parameters[iki_read_parameter_substitute].additional.used % 3 != 0) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: The parameter '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_substitute);
              fl_color_print_line(f_type_error, data->context.set.error, "' requires 3 strings.");
            }

            status = F_status_set_error(F_parameter);
          }

          if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_substitute);
              fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_total);
              fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");
            }

            status = F_status_set_error(F_parameter);
          }
        }

        if (data->parameters[iki_read_parameter_literal].result == f_console_result_found) {
          if (data->parameters[iki_read_parameter_object].result == f_console_result_found) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_literal);
              fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_object);
              fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");
            }

            status = F_status_set_error(F_parameter);
          }

          if (data->parameters[iki_read_parameter_content].result == f_console_result_found) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_literal);
              fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_content);
              fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");
            }

            status = F_status_set_error(F_parameter);
          }

          if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_literal);
              fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_total);
              fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");
            }

            status = F_status_set_error(F_parameter);
          }

          data->mode = iki_read_mode_literal;
        }
        else if (data->parameters[iki_read_parameter_object].result == f_console_result_found) {
          if (data->parameters[iki_read_parameter_content].result == f_console_result_found) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_object);
              fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_content);
              fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");
            }

            status = F_status_set_error(F_parameter);
          }

          if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_object);
              fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_total);
              fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");
            }

            status = F_status_set_error(F_parameter);
          }

          data->mode = iki_read_mode_object;
        }
        else if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
          data->mode = iki_read_mode_total;
        }
        else {
          // this is the default behavior, so there is no reason to check for the -c/--content parameter.
          data->mode = iki_read_mode_content;
        }

        if (data->parameters[iki_read_parameter_whole].result == f_console_result_found) {
          if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
            if (data->verbosity != iki_read_verbosity_quiet) {
              fprintf(f_type_error, "%c", f_string_eol[0]);
              fl_color_print(f_type_error, data->context.set.error, "ERROR: Cannot specify the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_whole);
              fl_color_print(f_type_error, data->context.set.error, "' parameter with the '");
              fl_color_print(f_type_error, data->context.set.notable, "%s%s", f_console_symbol_long_enable, iki_read_long_total);
              fl_color_print_line(f_type_error, data->context.set.error, "' parameter.");
            }

            status = F_status_set_error(F_parameter);
          }
        }

        if (F_status_is_error(status)) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
          }

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        if (data->process_pipe) {
          f_file_t file = f_file_t_initialize;

          file.id = f_type_descriptor_input;

          status = f_file_read(file, &data->buffer);

          if (F_status_is_error(status)) {
            iki_read_print_error_file(data->context, data->verbosity, F_status_set_fine(status), "f_file_read", "-", "process", F_true, F_true);
          }
          else {
            status = iki_read_process_buffer(arguments, "-", data);
          }

          // Clear buffers before continuing.
          f_macro_string_dynamic_t_delete_simple(data->buffer);
        }

        if (F_status_is_fine(status) && data->remaining.used > 0) {
          f_string_length_t i = 0;
          f_string_length_t total = 0;
          f_file_t file = f_file_t_initialize;

          for (; i < data->remaining.used; i++) {
            f_macro_file_t_reset(file);
            total = 0;

            status = f_file_open(arguments.argv[data->remaining.array[i]], 0, &file);

            if (F_status_is_error(status)) {
              iki_read_print_error_file(data->context, data->verbosity, F_status_set_fine(status), "f_file_open", arguments.argv[data->remaining.array[i]], "process", F_true, F_true);
              break;
            }

            status = f_file_size_by_id(file.id, &total);

            if (F_status_is_error(status)) {
              iki_read_print_error_file(data->context, data->verbosity, F_status_set_fine(status), "f_file_size_by_id", arguments.argv[data->remaining.array[i]], "process", F_true, F_true);

              f_file_close(&file.id);
              break;
            }

            // Skip past empty files.
            if (total == 0) {
              f_file_close(&file.id);
              continue;
            }

            status = f_file_read_until(file, total, &data->buffer);

            f_file_close(&file.id);

            if (F_status_is_error(status)) {
              iki_read_print_error_file(data->context, data->verbosity, F_status_set_fine(status), "f_file_read_until", arguments.argv[data->remaining.array[i]], "process", F_true, F_true);
              break;
            }

            status = iki_read_process_buffer(arguments, arguments.argv[data->remaining.array[i]], data);
            if (F_status_is_error(status)) break;

            // Clear buffers before repeating the loop.
            f_macro_string_dynamic_t_delete_simple(data->buffer);
          } // for
        }
      }
      else {
        if (data->verbosity != iki_read_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print_line(f_type_error, data->context.set.error, "ERROR: you failed to specify one or more files.");
        }

        status = F_status_set_error(F_parameter);
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->verbosity != iki_read_verbosity_quiet) {
      if (F_status_is_error(status) || data->mode == 0) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
      }
    }

    iki_read_delete_data(data);
    return status;
  }
#endif // _di_iki_read_main_

#ifndef _di_iki_read_delete_data_
  f_return_status iki_read_delete_data(iki_read_data_t *data) {
    f_status_t status = F_none;
    f_string_length_t i = 0;

    while (i < iki_read_total_parameters) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_lengths_t_delete_simple(data->remaining);
    f_macro_string_dynamic_t_delete_simple(data->buffer);
    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_iki_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
