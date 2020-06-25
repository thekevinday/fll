#include <level_3/iki_read.h>
#include "private-iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_help_
  f_return_status iki_read_print_help(const fl_color_context context) {
    fll_program_print_help_header(context, iki_read_name_long, iki_read_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, iki_read_short_at, iki_read_long_at, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Select variable at this numeric index.");
    fll_program_print_help_option(context, iki_read_short_line, iki_read_long_line, f_console_symbol_short_enable, f_console_symbol_long_enable, "Print only the variables at the given line.");
    fll_program_print_help_option(context, iki_read_short_name, iki_read_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, "Select variables with this name.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, iki_read_short_literal, iki_read_long_literal, f_console_symbol_short_enable, f_console_symbol_long_enable, "Print the entire variable instead of the content.");
    fll_program_print_help_option(context, iki_read_short_object, iki_read_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, " Print the variable name instead of the variable content.");
    fll_program_print_help_option(context, iki_read_short_raw, iki_read_long_raw, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print the raw data instead of the variable data.");
    fll_program_print_help_option(context, iki_read_short_total, iki_read_long_total, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Print the total number of variables.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, iki_read_short_substitute, iki_read_long_substitute, f_console_symbol_short_enable, f_console_symbol_long_enable,"Substitute the entire variable for the given name and content value with the given string.");
    fll_program_print_help_option(context, iki_read_short_expand, iki_read_long_expand, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Expand all values.");

    fll_program_print_help_usage(context, iki_read_name, "filename(s)");

    fl_color_print(f_type_output, context.important, context.reset, " Notes:");

    printf("%c", f_string_eol[0], f_string_eol[0]);

    printf("  This program will find and print all content following the IKI standard, without focusing on any particular vocabulary specification.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_substitute);
    printf(" option, requires 3 additional parameters: ");

    fl_color_print(f_type_output, context.notable, context.reset, "<");
    printf("%s", iki_read_replacement_vocabulary);
    fl_color_print(f_type_output, context.notable, context.reset, ">");
    printf(" ");
    fl_color_print(f_type_output, context.notable, context.reset, "<");
    printf("%s", iki_read_replacement_replace);
    fl_color_print(f_type_output, context.notable, context.reset, ">");
    printf(" ");
    fl_color_print(f_type_output, context.notable, context.reset, "<");
    printf("%s", iki_read_replacement_with);
    fl_color_print(f_type_output, context.notable, context.reset, ">");
    printf(".%c", f_string_eol[0]);

    fl_color_print(f_type_output, context.notable, context.reset, "    %s", iki_read_replacement_vocabulary);
    printf(": The name of the vocabulary whose content is to be substituted.%c", f_string_eol[0]);

    fl_color_print(f_type_output, context.notable, context.reset, "    %s", iki_read_replacement_replace);
    printf(":    The content matching this exact string will be substituted.%c", f_string_eol[0]);

    fl_color_print(f_type_output, context.notable, context.reset, "    %s", iki_read_replacement_with);
    printf(":       The new string to use as the substitute.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The vocabulary and replacement are case-sensitive and must exactly match.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    return F_none;
  }
#endif // _di_iki_read_print_help_

#ifndef _di_iki_read_main_
  f_return_status iki_read_main(const f_console_arguments arguments, iki_read_data *data) {
    f_status status = F_none;

    {
      f_console_parameters parameters = { data->parameters, iki_read_total_parameters };
      f_console_parameter_id ids[3] = { iki_read_parameter_no_color, iki_read_parameter_light, iki_read_parameter_dark };
      f_console_parameter_ids choices = { ids, 3 };

      status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

      if (F_status_is_error(status)) {
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
        fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, f_console_standard_long_verbose);
        fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
        fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, f_console_standard_long_quiet);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");
        fprintf(f_type_error, "%c", f_string_eol[0]);
      }

      data->verbosity = iki_read_verbosity_verbose;
    }
    else if (data->parameters[iki_read_parameter_quiet].result == f_console_result_found) {
      data->verbosity = iki_read_verbosity_quiet;
    }
    else {
      data->verbosity = iki_read_verbosity_normal;
    }

    if (data->remaining.used > 0 || data->process_pipe) {
      if (data->parameters[iki_read_parameter_at].result == f_console_result_found) {
        if (data->verbosity != iki_read_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_at);
          fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires a positive number.");
          fprintf(f_type_error, "%c", f_string_eol[0]);
        }

        iki_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }

      if (data->parameters[iki_read_parameter_line].result == f_console_result_found) {
        if (data->verbosity != iki_read_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_line);
          fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires a positive number.");
          fprintf(f_type_error, "%c", f_string_eol[0]);
        }

        iki_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }
      else if (data->parameters[iki_read_parameter_line].result == f_console_result_additional) {
        const f_string_length index = data->parameters[iki_read_parameter_line].additional.array[data->parameters[iki_read_parameter_line].additional.used - 1];
        const f_string_range range = f_macro_string_range_initialize(strlen(arguments.argv[index]));

        f_number_unsigned number = 0;

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);
        if (F_status_is_error(status)) {
          iki_read_print_error_number_argument(data->context, data->verbosity, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", iki_read_long_line, arguments.argv[index]);
          fprintf(f_type_error, "%c", f_string_eol[0]);

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        data->line = number;

        // additional @todo
      }

      if (data->parameters[iki_read_parameter_name].result == f_console_result_found) {
        if (data->verbosity != iki_read_verbosity_quiet) {
          fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
          fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_name);
          fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires a string.");
          fprintf(f_type_error, "%c", f_string_eol[0]);
        }

        iki_read_delete_data(data);
        return F_status_set_error(F_parameter);
      }

      if (data->parameters[iki_read_parameter_substitute].result != f_console_result_none) {
        if (data->parameters[iki_read_parameter_substitute].result == f_console_result_found || data->parameters[iki_read_parameter_substitute].additional.used % 3 != 0) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The parameter '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_substitute);
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' requires 3 strings.");
            fprintf(f_type_error, "%c", f_string_eol[0]);
          }

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }
      }

      if (data->parameters[iki_read_parameter_literal].result == f_console_result_found) {
        if (data->parameters[iki_read_parameter_object].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_literal);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_object);
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");
            fprintf(f_type_error, "%c", f_string_eol[0]);
          }

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        if (data->parameters[iki_read_parameter_raw].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_literal);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_raw);
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");
            fprintf(f_type_error, "%c", f_string_eol[0]);
          }

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_literal);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_total);
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");
            fprintf(f_type_error, "%c", f_string_eol[0]);
          }

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        data->mode = iki_read_mode_literal;
      }
      else if (data->parameters[iki_read_parameter_object].result == f_console_result_found) {
        if (data->parameters[iki_read_parameter_raw].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_object);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_raw);
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");
            fprintf(f_type_error, "%c", f_string_eol[0]);
          }

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_object);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_total);
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");
            fprintf(f_type_error, "%c", f_string_eol[0]);
          }

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        data->mode = iki_read_mode_object;
      }
      else if (data->parameters[iki_read_parameter_raw].result == f_console_result_found) {
        if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
          if (data->verbosity != iki_read_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: Cannot specify the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_raw);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "' parameter with the '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s%s", f_console_symbol_long_enable, iki_read_long_total);
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' parameter.");
            fprintf(f_type_error, "%c", f_string_eol[0]);
          }

          iki_read_delete_data(data);
          return F_status_set_error(F_parameter);
        }

        data->mode = iki_read_mode_raw;
      }
      else if (data->parameters[iki_read_parameter_total].result == f_console_result_found) {
        data->mode = iki_read_mode_total;
      }
      else {
        data->mode = iki_read_mode_content;
      }

      if (data->process_pipe) {
        f_file file = f_file_initialize;

        file.id = f_type_descriptor_input;

        status = f_file_read(file, &data->buffer);

        if (F_status_is_error(status)) {
          iki_read_print_error_file(data->context, data->verbosity, F_status_set_fine(status), "f_file_read", "-", "process", F_true, F_true);

          iki_read_delete_data(data);
          return status;
        }

        status = iki_read_main_process_file(arguments, "-", data);
        if (F_status_is_error(status)) {
          iki_read_delete_data(data);
          return status;
        }

        // Clear buffers before continuing.
        f_macro_string_dynamic_delete_simple(data->buffer);
      }

      if (data->remaining.used > 0) {
        f_string_length i = 0;
        f_string_length total = 0;
        f_file file = f_file_initialize;

        for (; i < data->remaining.used; i++) {
          f_macro_file_reset(file);
          total = 0;

          status = f_file_open(arguments.argv[data->remaining.array[i]], 0, &file);
          if (F_status_is_error(status)) {
            iki_read_print_error_file(data->context, data->verbosity, F_status_set_fine(status), "f_file_open", arguments.argv[data->remaining.array[i]], "process", F_true, F_true);

            iki_read_delete_data(data);
            return status;
          }

          status = f_file_size_by_id(file.id, &total);
          if (F_status_is_error(status)) {
            iki_read_print_error_file(data->context, data->verbosity, F_status_set_fine(status), "f_file_size_by_id", arguments.argv[data->remaining.array[i]], "process", F_true, F_true);

            f_file_close(&file.id);

            iki_read_delete_data(data);
            return status;
          }

          // Skip past empty files.
          if (total == 0) {
            f_file_close(&file.id);
            continue;
          }

          status = f_file_read_until(file, &data->buffer, total);

          f_file_close(&file.id);

          if (F_status_is_error(status)) {
            iki_read_print_error_file(data->context, data->verbosity, F_status_set_fine(status), "f_file_read_until", arguments.argv[data->remaining.array[i]], "process", F_true, F_true);

            iki_read_delete_data(data);
            return status;
          }

          status = iki_read_main_process_file(arguments, arguments.argv[data->remaining.array[i]], data);
          if (F_status_is_error(status)) {
            iki_read_delete_data(data);
            return status;
          }

          // Clear buffers before repeating the loop.
          f_macro_string_dynamic_delete_simple(data->buffer);
        } // for
      }
    }
    else {
      if (data->verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: you failed to specify one or more files.");
        fprintf(f_type_error, "%c", f_string_eol[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    iki_read_delete_data(data);
    return status;
  }
#endif // _di_iki_read_main_

#ifndef _di_iki_read_delete_data_
  f_return_status iki_read_delete_data(iki_read_data *data) {
    f_status status = F_none;
    f_string_length i = 0;

    while (i < iki_read_total_parameters) {
      f_macro_string_lengths_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_lengths_delete_simple(data->remaining);
    f_macro_string_dynamic_delete_simple(data->buffer);
    fl_macro_color_context_delete_simple(data->context);

    return F_none;
  }
#endif // _di_iki_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
