#include "fss_extended_write.h"
#include "private-fss_extended_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_write_print_help_
  f_return_status fss_extended_write_print_help(const f_file_t file, const f_color_context_t context) {

    fll_program_print_help_header(file, context, fss_extended_write_name_long, fss_extended_write_version);

    fll_program_print_help_option(file, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(file, context, fss_extended_write_short_file, fss_extended_write_long_file, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Specify a file to send output to.");
    fll_program_print_help_option(file, context, fss_extended_write_short_content, fss_extended_write_long_content, f_console_symbol_short_enable, f_console_symbol_long_enable, "The Content to output.");
    fll_program_print_help_option(file, context, fss_extended_write_short_double, fss_extended_write_long_double, f_console_symbol_short_enable, f_console_symbol_long_enable, " Use double quotes (default).");
    fll_program_print_help_option(file, context, fss_extended_write_short_ignore, fss_extended_write_long_ignore, f_console_symbol_short_enable, f_console_symbol_long_enable, " Ignore a given range within a content.");
    fll_program_print_help_option(file, context, fss_extended_write_short_object, fss_extended_write_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, " The Object to output.");
    fll_program_print_help_option(file, context, fss_extended_write_short_partial, fss_extended_write_long_partial, f_console_symbol_short_enable, f_console_symbol_long_enable, "Do not output end of Object/Content character.");
    fll_program_print_help_option(file, context, fss_extended_write_short_prepend, fss_extended_write_long_prepend, f_console_symbol_short_enable, f_console_symbol_long_enable, "Prepend the given whitespace characters to the start of each multi-line Content.");
    fll_program_print_help_option(file, context, fss_extended_write_short_single, fss_extended_write_long_single, f_console_symbol_short_enable, f_console_symbol_long_enable, " Use single quotes.");
    fll_program_print_help_option(file, context, fss_extended_write_short_trim, fss_extended_write_long_trim, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Trim object names.");

    fll_program_print_help_usage(file, context, fss_extended_write_name, "");

    printf("  The pipe uses the Backspace character '");
    fl_color_print(f_type_output, context.set.notable, "\\b");
    printf("' (");
    fl_color_print(f_type_output, context.set.notable, "U+0008");
    printf(") to designate the start of a Content.%c", f_string_eol[0]);

    printf("  The pipe uses the Form Feed character '");
    fl_color_print(f_type_output, context.set.notable, "\\f");
    printf("' (");
    fl_color_print(f_type_output, context.set.notable, "U+000C");
    printf(") to designate the end of the last Content.%c", f_string_eol[0]);

    printf("  The pipe uses the Vertical Line character '");
    fl_color_print(f_type_output, context.set.notable, "\\v");
    printf("' (");
    fl_color_print(f_type_output, context.set.notable, "U+000B");
    printf(") is used to ignore a content range, which does nothing in this program.%c", f_string_eol[0]);

    printf("  For the pipe, an Object is terminated by either a Backspace character '");
    fl_color_print(f_type_output, context.set.notable, "\\b");
    printf("' (");
    fl_color_print(f_type_output, context.set.notable, "U+0008");
    printf(") or a Form Feed character '");
    fl_color_print(f_type_output, context.set.notable, "\\f");
    printf("' (");
    fl_color_print(f_type_output, context.set.notable, "U+000C");
    printf(").%c", f_string_eol[0]);

    printf("  The end of the pipe represents the end of any Object or Content.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  The FSS-0001 (Extended) specification does not support multi-line Content, therefore the parameter '");
    fl_color_print(f_type_output, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_prepend);
    printf("' does nothing.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    printf("  This program does not use the parameter '");
    fl_color_print(f_type_output, context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_ignore);
    printf("', which therefore does nothing.%c", f_string_eol[0]);
    printf("  This parameter requires two values.%c", f_string_eol[0]);

    printf("%c", f_string_eol[0]);

    return F_none;
  }
#endif // _di_fss_extended_write_print_help_

#ifndef _di_fss_extended_write_main_
  f_return_status fss_extended_write_main(const f_console_arguments_t arguments, fss_extended_write_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, fss_extended_write_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_extended_write_parameter_no_color, fss_extended_write_parameter_light, fss_extended_write_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        data->error.context = data->context.set.error;
        data->error.notable = data->context.set.notable;

        if (F_status_is_error(status)) {
          fss_extended_write_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_extended_write_parameter_verbosity_quiet, fss_extended_write_parameter_verbosity_normal, fss_extended_write_parameter_verbosity_verbose, fss_extended_write_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_extended_write_delete_data(data);
          return status;
        }

        if (choice == fss_extended_write_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_extended_write_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_extended_write_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_extended_write_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[fss_extended_write_parameter_help].result == f_console_result_found) {
      fss_extended_write_print_help(data->output, data->context);

      fss_extended_write_delete_data(data);
      return status;
    }

    if (data->parameters[fss_extended_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, fss_extended_write_version);

      fss_extended_write_delete_data(data);
      return status;
    }

    f_file_t output = f_file_t_initialize;

    output.id = f_type_descriptor_output;
    output.stream = f_type_output;
    output.flag = f_file_flag_create | f_file_flag_write_only | f_file_flag_append;

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_extended_write_parameter_file].result == f_console_result_additional) {
        if (data->parameters[fss_extended_write_parameter_file].additional.used > 1) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_file);
            fl_color_print(data->error.to.stream, data->context.set.error, "' may only be specified once.%c", f_string_eol[0]);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_string_length_t location = data->parameters[fss_extended_write_parameter_file].additional.array[0];

          output.id = -1;
          output.stream = 0;
          status = f_file_stream_open(arguments.argv[location], 0, &output);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments.argv[location], "open", fll_error_file_type_file);
          }
        }
      }
      else if (data->parameters[fss_extended_write_parameter_file].result == f_console_result_found) {
        fss_extended_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable, fss_extended_write_long_file);
        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_extended_write_parameter_object].locations.used || data->parameters[fss_extended_write_parameter_content].locations.used) {
        if (data->parameters[fss_extended_write_parameter_object].locations.used) {
          if (data->parameters[fss_extended_write_parameter_object].locations.used != data->parameters[fss_extended_write_parameter_object].additional.used) {
            fss_extended_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable, fss_extended_write_long_object);
            status = F_status_set_error(F_parameter);
          }
          else if (data->parameters[fss_extended_write_parameter_content].locations.used != data->parameters[fss_extended_write_parameter_content].additional.used) {
            fss_extended_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable, fss_extended_write_long_content);
            status = F_status_set_error(F_parameter);
          }
          else if (!data->parameters[fss_extended_write_parameter_content].locations.used && data->parameters[fss_extended_write_parameter_partial].result == f_console_result_none) {
            fss_extended_write_error_parameter_at_least_once(*data);
            status = F_status_set_error(F_parameter);
          }
          else if (data->parameters[fss_extended_write_parameter_content].locations.used && data->parameters[fss_extended_write_parameter_partial].locations.used) {
            if (data->parameters[fss_extended_write_parameter_content].result == f_console_result_additional) {
              if (data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(data->error.to.stream, "%c", f_string_eol[0]);
                fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_partial);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter only allows either the '");
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_object);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter or the '");
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_content);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter, but not both.%c", f_string_eol[0]);
              }

              status = F_status_set_error(F_parameter);
            }
          }

          if (F_status_is_error_not(status)) {
            if (data->parameters[fss_extended_write_parameter_content].result == f_console_result_additional) {
              f_array_length_t location_object = data->parameters[fss_extended_write_parameter_object].locations.array[0];
              f_array_length_t location_content = data->parameters[fss_extended_write_parameter_content].locations.array[0];
              f_array_length_t location_sub_object = data->parameters[fss_extended_write_parameter_object].locations_sub.array[0];
              f_array_length_t location_sub_content = data->parameters[fss_extended_write_parameter_content].locations_sub.array[0];

              if (location_object > location_content || location_object == location_content && location_sub_object > location_sub_content) {
                if (data->error.verbosity != f_console_verbosity_quiet) {
                  fprintf(data->error.to.stream, "%c", f_string_eol[0]);
                  fl_color_print(data->error.to.stream, data->context.set.error, "%sEach ", fll_error_print_error);
                  fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_object);
                  fl_color_print(data->error.to.stream, data->context.set.error, "' parameter must be specified before a '");
                  fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_content);
                  fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol[0]);
                }

                status = F_status_set_error(F_parameter);
              }
              else {
                location_object = data->parameters[fss_extended_write_parameter_object].locations.array[data->parameters[fss_extended_write_parameter_object].locations.used - 1];
                location_content = data->parameters[fss_extended_write_parameter_content].locations.array[data->parameters[fss_extended_write_parameter_content].locations.used - 1];
                location_sub_object = data->parameters[fss_extended_write_parameter_object].locations_sub.array[data->parameters[fss_extended_write_parameter_object].locations_sub.used - 1];
                location_sub_content = data->parameters[fss_extended_write_parameter_content].locations_sub.array[data->parameters[fss_extended_write_parameter_content].locations_sub.used - 1];

                if (location_object > location_content || location_object == location_content && location_sub_object > location_sub_content) {
                  if (data->error.verbosity != f_console_verbosity_quiet) {
                    fprintf(data->error.to.stream, "%c", f_string_eol[0]);
                    fl_color_print(data->error.to.stream, data->context.set.error, "%sEach ", fll_error_print_error);
                    fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_object);
                    fl_color_print(data->error.to.stream, data->context.set.error, "' parameter must have at least one '");
                    fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_content);
                    fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol[0]);
                  }

                  status = F_status_set_error(F_parameter);
                }
              }
            }
          }
        }
        else if (data->parameters[fss_extended_write_parameter_content].locations.used) {
          if (data->parameters[fss_extended_write_parameter_content].locations.used != data->parameters[fss_extended_write_parameter_content].additional.used) {
            fss_extended_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable, fss_extended_write_long_content);
            status = F_status_set_error(F_parameter);
          }
          else if (!data->parameters[fss_extended_write_parameter_partial].locations.used) {
            fss_extended_write_error_parameter_at_least_once(*data);
            status = F_status_set_error(F_parameter);
          }
        }
      }
      else if (!data->process_pipe) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThis requires either piped data or the use of the '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_object);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter with the '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_content);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol[0]);
        }

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && data->process_pipe) {
        if (data->parameters[fss_extended_write_parameter_partial].result == f_console_result_found) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_partial);
            fl_color_print(data->error.to.stream, data->context.set.error, "' parameter cannot be used when processing a pipe.%c", f_string_eol[0]);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_extended_write_parameter_prepend].result == f_console_result_found) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_prepend);
          fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (data->parameters[fss_extended_write_parameter_prepend].result == f_console_result_additional) {
        const f_string_length_t index = data->parameters[fss_extended_write_parameter_prepend].additional.array[data->parameters[fss_extended_write_parameter_prepend].additional.used - 1];
        const f_string_length_t length = strnlen(arguments.argv[index], f_console_length_size);

        // Even though this standard does not utilize this parameter, provide the validation for consistency.
        if (length) {
          f_string_range_t range = f_macro_string_range_t_initialize(length);
          const f_string_static_t prepend = f_macro_string_static_t_initialize(arguments.argv[index], length);

          for (; range.start < length; range.start++) {

            status = f_fss_is_space(prepend, range);
            if (F_status_is_error(status)) break;

            if (status == F_false) {
              if (data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(data->error.to.stream, "%c", f_string_eol[0]);
                fl_color_print(data->error.to.stream, data->context.set.error, "%sThe value for the parameter '", fll_error_print_error);
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_prepend);
                fl_color_print(data->error.to.stream, data->context.set.error, "' must only contain whitespace.%c", f_string_eol[0]);
              }

              status = F_status_set_error(F_parameter);
              break;
            }
          } // for
        }
        else {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe value for the parameter '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_prepend);
            fl_color_print(data->error.to.stream, data->context.set.error, "' must not be an empty string.%c", f_string_eol[0]);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_extended_write_parameter_ignore].result == f_console_result_found) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_ignore);
          fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no values were given.%c", f_string_eol[0]);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (data->parameters[fss_extended_write_parameter_ignore].result == f_console_result_additional) {
        const f_array_length_t total_locations = data->parameters[fss_extended_write_parameter_ignore].locations.used;
        const f_array_length_t total_arguments = data->parameters[fss_extended_write_parameter_ignore].additional.used;

        if (total_locations * 2 > total_arguments) {
          fprintf(data->error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_ignore);
          fl_color_print(data->error.to.stream, data->context.set.error, "' requires two values.%c", f_string_eol[0]);

          status = F_status_set_error(F_parameter);
        }
      }
    }

    f_fss_quote_t quote = f_fss_delimit_quote_double;

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_extended_write_parameter_double].result == f_console_result_found) {
        if (data->parameters[fss_extended_write_parameter_single].result == f_console_result_found) {
          if (data->parameters[fss_extended_write_parameter_double].location < data->parameters[fss_extended_write_parameter_single].location) {
            quote = f_fss_delimit_quote_single;
          }
        }
      }
      else if (data->parameters[fss_extended_write_parameter_single].result == f_console_result_found) {
        quote = f_fss_delimit_quote_single;
      }
    }

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_string_dynamic_t object = f_string_dynamic_t_initialize;
    f_string_dynamics_t contents = f_string_dynamics_t_initialize;

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (data->process_pipe) {
        status = fss_extended_write_process_pipe(*data, output, quote, &buffer);

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sWhile processing the ", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "input pipe");
            fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol[0]);
          }
        }
      }

      if (F_status_is_error_not(status)) {
        if (data->parameters[fss_extended_write_parameter_partial].result == f_console_result_found) {
          if (data->parameters[fss_extended_write_parameter_object].result == f_console_result_additional) {
            contents.used = 0;

            for (f_array_length_t i = 0; i < data->parameters[fss_extended_write_parameter_object].additional.used; i++) {

              object.string = arguments.argv[data->parameters[fss_extended_write_parameter_object].additional.array[i]];
              object.used = strnlen(object.string, f_console_length_size);
              object.size = object.used;

              status = fss_extended_write_process(*data, output, quote, &object, 0, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
          else {
            object.used = 0;

            status = fl_string_dynamics_size_increase(data->parameters[fss_extended_write_parameter_content].additional.used, &contents);

            if (status == F_buffer_too_large) {
              status = F_status_set_error(status);
            }

            if (F_status_is_error(status)) {
              fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamics_size_increase", F_true);
            }
            else {
              f_array_length_t i = 0;

              for (; i < data->parameters[fss_extended_write_parameter_content].additional.used; i++) {

                contents.array[contents.used].string = arguments.argv[data->parameters[fss_extended_write_parameter_content].additional.array[i]];
                contents.array[contents.used].used = strnlen(contents.array[contents.used].string, f_console_length_size);
                contents.array[contents.used].size = contents.array[contents.used].used;
                contents.used++;
              } // for

              status = fss_extended_write_process(*data, output, quote, 0, &contents, &buffer);

              // clear the contents array of the static strings to avoid deallocation attempts on static variables.
              for (; i < data->parameters[fss_extended_write_parameter_content].additional.used; i++) {
                contents.array[contents.used].string = 0;
                contents.array[contents.used].used = 0;
                contents.array[contents.used].size = 0;
              } // for

              contents.used = 0;
              contents.size = 0;
            }
          }
        }
        else {
          f_array_length_t i = 0;
          f_array_length_t j = 0;
          f_array_length_t object_current = 0;
          f_array_length_t object_next = 0;
          f_array_length_t content_current = 0;

          for (; i < data->parameters[fss_extended_write_parameter_object].additional.used; i++) {

            object_current = data->parameters[fss_extended_write_parameter_object].locations.array[i];

            if (i + 1 < data->parameters[fss_extended_write_parameter_object].additional.used) {
              object_next = data->parameters[fss_extended_write_parameter_object].locations.array[i + 1];
            }

            object.string = arguments.argv[data->parameters[fss_extended_write_parameter_object].additional.array[i]];
            object.used = strnlen(object.string, f_console_length_size);
            object.size = object.used;

            contents.used = 0;

            for (; j < data->parameters[fss_extended_write_parameter_content].additional.used; j++) {

              content_current = data->parameters[fss_extended_write_parameter_content].locations.array[j];

              if (i + 1 < data->parameters[fss_extended_write_parameter_object].additional.used) {
                if (content_current < object_current || content_current > object_next) break;
              }

              status = fl_string_dynamics_size_increase(f_fss_default_allocation_step, &contents);

              if (F_status_is_error(status)) {
                fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamics_size_increase", F_true);
                break;
              }

              if (contents.array[contents.used].used) {
                contents.array[contents.used].used = 0;
              }

              status = fl_string_append(arguments.argv[data->parameters[fss_extended_write_parameter_content].additional.array[j]], strnlen(arguments.argv[data->parameters[fss_extended_write_parameter_content].additional.array[j]], f_console_length_size), &contents.array[contents.used]);

              if (F_status_is_error(status)) {
                fll_error_print(data->error, F_status_set_fine(status), "fl_string_append", F_true);
                break;
              }

              contents.used++;
            } // for

            if (F_status_is_error(status)) break;

            status = fss_extended_write_process(*data, output, quote, &object, &contents, &buffer);
            if (F_status_is_error(status)) break;
          } // for
        }

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sWhile processing the ", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "input arguments");
            fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol[0]);
          }
        }
        else if (data->error.verbosity != f_console_verbosity_quiet && data->parameters[fss_extended_write_parameter_file].result == f_console_result_none) {
          // ensure there is always a newline at the end, unless in quiet mode.
          fprintf(f_type_output, "%c", f_string_eol[0]);
        }
      }

      f_macro_string_dynamic_t_delete_simple(escaped);

      // object, though being a "dynamic" type, is being used statically, so clear them up to avoid invalid free().
      object.string = 0;
      object.used = 0;
      object.size = 0;

      // reset contents used, it is dynamically allocated so leave everything else alone.
      contents.used = 0;
    }

    if (data->parameters[fss_extended_write_parameter_file].result == f_console_result_additional) {
      if (output.id != -1) {
        f_file_stream_close(F_true, &output);
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(data->error.to.stream, "%c", f_string_eol[0]);
      }
    }

    f_macro_string_dynamic_t_delete_simple(buffer);
    f_macro_string_dynamic_t_delete_simple(object);
    f_macro_string_dynamics_t_delete_simple(contents);
    fss_extended_write_delete_data(data);
    return status;
  }
#endif // _di_fss_extended_write_main_

#ifndef _di_fss_extended_write_delete_data_
  f_return_status fss_extended_write_delete_data(fss_extended_write_data_t *data) {

    for (f_string_length_t i = 0; i < fss_extended_write_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);

    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_fss_extended_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
