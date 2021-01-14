#include "fss_basic_list_write.h"
#include "private-fss_basic_list_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_write_print_help_
  f_status_t fss_basic_list_write_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, fss_basic_list_write_name_long, fss_basic_list_write_version);

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

    fll_program_print_help_option(output, context, fss_basic_list_write_short_file, fss_basic_list_write_long_file, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send output to.");
    fll_program_print_help_option(output, context, fss_basic_list_write_short_content, fss_basic_list_write_long_content, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The Content to output.");
    fll_program_print_help_option(output, context, fss_basic_list_write_short_double, fss_basic_list_write_long_double, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(output, context, fss_basic_list_write_short_ignore, fss_basic_list_write_long_ignore, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Ignore a given range within a content.");
    fll_program_print_help_option(output, context, fss_basic_list_write_short_object, fss_basic_list_write_long_object, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The Object to output.");
    fll_program_print_help_option(output, context, fss_basic_list_write_short_partial, fss_basic_list_write_long_partial, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Do not output end of Object/Content character.");
    fll_program_print_help_option(output, context, fss_basic_list_write_short_prepend, fss_basic_list_write_long_prepend, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Prepend the given whitespace characters to the start of each multi-line Content.");
    fll_program_print_help_option(output, context, fss_basic_list_write_short_single, fss_basic_list_write_long_single, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");
    fll_program_print_help_option(output, context, fss_basic_list_write_short_trim, fss_basic_list_write_long_trim, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Trim object names.");

    fll_program_print_help_usage(output, context, fss_basic_list_write_name, f_string_empty_s);

    fprintf(output.stream, "  The pipe uses the Backspace character '");
    fl_color_print(output.stream, context.set.notable, "\\b");
    fprintf(output.stream, "' (");
    fl_color_print(output.stream, context.set.notable, "U+0008");
    fprintf(output.stream, ") to designate the start of a Content.%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The pipe uses the Form Feed character '");
    fl_color_print(output.stream, context.set.notable, "\\f");
    fprintf(output.stream, "' (");
    fl_color_print(output.stream, context.set.notable, "U+000C");
    fprintf(output.stream, ") to designate the end of the last Content.%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The pipe uses the Vertical Line character '");
    fl_color_print(output.stream, context.set.notable, "\\v");
    fprintf(output.stream, "' (");
    fl_color_print(output.stream, context.set.notable, "U+000B");
    fprintf(output.stream, ") is used to ignore a content range, which does nothing in this program.%c", f_string_eol_s[0]);

    fprintf(output.stream, "  For the pipe, an Object is terminated by either a Backspace character '");
    fl_color_print(output.stream, context.set.notable, "\\b");
    fprintf(output.stream, "' (");
    fl_color_print(output.stream, context.set.notable, "U+0008");
    fprintf(output.stream, ") or a Form Feed character '");
    fl_color_print(output.stream, context.set.notable, "\\f");
    fprintf(output.stream, "' (");
    fl_color_print(output.stream, context.set.notable, "U+000C");
    fprintf(output.stream, ").%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The end of the pipe represents the end of any Object or Content.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  The FSS-0002 (Basic List) specification does not support quoted names, therefore the parameters '");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_single);
    fprintf(output.stream, "' and '");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_double);
    fprintf(output.stream, "' do nothing.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fprintf(output.stream, "  This program does not use the parameter '");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_ignore);
    fprintf(output.stream, "', which therefore does nothing.%c", f_string_eol_s[0]);
    fprintf(output.stream, "  This parameter requires two values.%c", f_string_eol_s[0]);

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_fss_basic_list_write_print_help_

#ifndef _di_fss_basic_list_write_main_
  f_status_t fss_basic_list_write_main(const f_console_arguments_t arguments, fss_basic_list_write_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, fss_basic_list_write_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_basic_list_write_parameter_no_color, fss_basic_list_write_parameter_light, fss_basic_list_write_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        if (data->context.set.error.before) {
          data->error.context = data->context.set.error;
          data->error.notable = data->context.set.notable;
        }
        else {
          data->context.set.warning = f_color_set_empty_s;
          data->context.set.error = f_color_set_empty_s;
          data->context.set.title = f_color_set_empty_s;
          data->context.set.notable = f_color_set_empty_s;
          data->context.set.important = f_color_set_empty_s;
          data->context.set.standout = f_color_set_empty_s;
          data->context.set.normal = f_color_set_empty_s;
          data->context.set.normal_reset = f_color_set_empty_s;

          data->error.context = f_color_set_empty_s;
          data->error.notable = f_color_set_empty_s;
        }

        if (F_status_is_error(status)) {
          fss_basic_list_write_delete_data(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_basic_list_write_parameter_verbosity_quiet, fss_basic_list_write_parameter_verbosity_normal, fss_basic_list_write_parameter_verbosity_verbose, fss_basic_list_write_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_basic_list_write_delete_data(data);
          return status;
        }

        if (choice == fss_basic_list_write_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_basic_list_write_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_basic_list_write_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_basic_list_write_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[fss_basic_list_write_parameter_help].result == f_console_result_found) {
      fss_basic_list_write_print_help(data->output, data->context);

      fss_basic_list_write_delete_data(data);
      return status;
    }

    if (data->parameters[fss_basic_list_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, fss_basic_list_write_version);

      fss_basic_list_write_delete_data(data);
      return status;
    }

    f_file_t output = f_file_t_initialize;

    output.id = f_type_descriptor_output;
    output.stream = data->output.stream;
    output.flag = f_file_flag_create | f_file_flag_write_only | f_file_flag_append;

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_additional) {
        if (data->parameters[fss_basic_list_write_parameter_file].values.used > 1) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_file);
            fl_color_print(data->error.to.stream, data->context.set.error, "' may only be specified once.%c", f_string_eol_s[0]);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_string_length_t location = data->parameters[fss_basic_list_write_parameter_file].values.array[0];

          output.id = -1;
          output.stream = 0;
          status = f_file_stream_open(arguments.argv[location], 0, &output);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments.argv[location], "open", fll_error_file_type_file);
          }
        }
      }
      else if (data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_found) {
        fss_basic_list_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable_s, fss_basic_list_write_long_file);
        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_basic_list_write_parameter_object].locations.used || data->parameters[fss_basic_list_write_parameter_content].locations.used) {
        if (data->parameters[fss_basic_list_write_parameter_object].locations.used) {
          if (data->parameters[fss_basic_list_write_parameter_object].locations.used != data->parameters[fss_basic_list_write_parameter_object].values.used) {
            fss_basic_list_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable_s, fss_basic_list_write_long_object);
            status = F_status_set_error(F_parameter);
          }
          else if (data->parameters[fss_basic_list_write_parameter_content].locations.used != data->parameters[fss_basic_list_write_parameter_content].values.used) {
            fss_basic_list_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable_s, fss_basic_list_write_long_content);
            status = F_status_set_error(F_parameter);
          }
          else if (data->parameters[fss_basic_list_write_parameter_object].locations.used != data->parameters[fss_basic_list_write_parameter_content].locations.used && data->parameters[fss_basic_list_write_parameter_partial].result == f_console_result_none) {
            fss_basic_list_write_error_parameter_same_times_print(*data);
            status = F_status_set_error(F_parameter);
          }
          else if (data->parameters[fss_basic_list_write_parameter_content].locations.used && data->parameters[fss_basic_list_write_parameter_partial].locations.used) {
            if (data->parameters[fss_basic_list_write_parameter_content].result == f_console_result_additional) {
              if (data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
                fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_partial);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter only allows either the '");
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_object);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter or the '");
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_content);
                fl_color_print(data->error.to.stream, data->context.set.error, "' parameter, but not both.%c", f_string_eol_s[0]);
              }

              status = F_status_set_error(F_parameter);
            }
          }

          if (F_status_is_error_not(status)) {
            if (data->parameters[fss_basic_list_write_parameter_content].result == f_console_result_additional) {
              f_array_length_t location_object = 0;
              f_array_length_t location_content = 0;
              f_array_length_t location_sub_object = 0;
              f_array_length_t location_sub_content = 0;

              for (f_array_length_t i = 0; i < data->parameters[fss_basic_list_write_parameter_object].locations.used; i++) {
                location_object = data->parameters[fss_basic_list_write_parameter_object].locations.array[i];
                location_content = data->parameters[fss_basic_list_write_parameter_content].locations.array[i];
                location_sub_object = data->parameters[fss_basic_list_write_parameter_object].locations_sub.array[i];
                location_sub_content = data->parameters[fss_basic_list_write_parameter_content].locations_sub.array[i];

                if (location_object > location_content || location_object == location_content && location_sub_object > location_sub_content) {
                  if (data->error.verbosity != f_console_verbosity_quiet) {
                    fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
                    fl_color_print(data->error.to.stream, data->context.set.error, "%sEach ", fll_error_print_error);
                    fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_object);
                    fl_color_print(data->error.to.stream, data->context.set.error, "' parameter must be specified before a '");
                    fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_content);
                    fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol_s[0]);
                  }

                  status = F_status_set_error(F_parameter);
                  break;
                }
              } // for
            }
          }
        }
        else if (data->parameters[fss_basic_list_write_parameter_content].locations.used) {
          if (data->parameters[fss_basic_list_write_parameter_content].locations.used != data->parameters[fss_basic_list_write_parameter_content].values.used) {
            fss_basic_list_write_error_parameter_value_missing_print(*data, f_console_symbol_long_enable_s, fss_basic_list_write_long_content);
            status = F_status_set_error(F_parameter);
          }
          else if (!data->parameters[fss_basic_list_write_parameter_partial].locations.used) {
            fss_basic_list_write_error_parameter_same_times_print(*data);
            status = F_status_set_error(F_parameter);
          }
        }
      }
      else if (!data->process_pipe) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThis requires either piped data or the use of the '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_object);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter with the '");
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_content);
          fl_color_print(data->error.to.stream, data->context.set.error, "' parameter.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && data->process_pipe) {
        if (data->parameters[fss_basic_list_write_parameter_partial].result == f_console_result_found) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_partial);
            fl_color_print(data->error.to.stream, data->context.set.error, "' parameter cannot be used when processing a pipe.%c", f_string_eol_s[0]);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_basic_list_write_parameter_prepend].result == f_console_result_found) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_prepend);
          fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (data->parameters[fss_basic_list_write_parameter_prepend].result == f_console_result_additional) {
        const f_string_length_t index = data->parameters[fss_basic_list_write_parameter_prepend].values.array[data->parameters[fss_basic_list_write_parameter_prepend].values.used - 1];
        const f_string_length_t length = strnlen(arguments.argv[index], f_console_length_size);

        if (length) {
          f_string_range_t range = f_macro_string_range_t_initialize(length);

          data->prepend.string = arguments.argv[index];
          data->prepend.used = length;
          data->prepend.size = length;

          for (; range.start < length; range.start++) {

            status = f_fss_is_space(data->prepend, range);
            if (F_status_is_error(status)) break;

            if (status == F_false) {
              if (data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
                fl_color_print(data->error.to.stream, data->context.set.error, "%sThe value for the parameter '", fll_error_print_error);
                fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_prepend);
                fl_color_print(data->error.to.stream, data->context.set.error, "' must only contain whitespace.%c", f_string_eol_s[0]);
              }

              status = F_status_set_error(F_parameter);
              break;
            }
          } // for
        }
        else {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sThe value for the parameter '", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_prepend);
            fl_color_print(data->error.to.stream, data->context.set.error, "' must not be an empty string.%c", f_string_eol_s[0]);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_basic_list_write_parameter_ignore].result == f_console_result_found) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_ignore);
          fl_color_print(data->error.to.stream, data->context.set.error, "' was specified, but no values were given.%c", f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (data->parameters[fss_basic_list_write_parameter_ignore].result == f_console_result_additional) {
        const f_array_length_t total_locations = data->parameters[fss_basic_list_write_parameter_ignore].locations.used;
        const f_array_length_t total_arguments = data->parameters[fss_basic_list_write_parameter_ignore].values.used;

        if (total_locations * 2 > total_arguments) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fl_color_print(data->error.to.stream, data->context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data->error.to.stream, data->context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_list_write_long_ignore);
          fl_color_print(data->error.to.stream, data->context.set.error, "' requires two values.%c", f_string_eol_s[0]);

          status = F_status_set_error(F_parameter);
        }
      }
    }

    f_fss_quote_t quote = f_fss_delimit_quote_double;

    if (F_status_is_error_not(status)) {
      if (data->parameters[fss_basic_list_write_parameter_double].result == f_console_result_found) {
        if (data->parameters[fss_basic_list_write_parameter_single].result == f_console_result_found) {
          if (data->parameters[fss_basic_list_write_parameter_double].location < data->parameters[fss_basic_list_write_parameter_single].location) {
            quote = f_fss_delimit_quote_single;
          }
        }
      }
      else if (data->parameters[fss_basic_list_write_parameter_single].result == f_console_result_found) {
        quote = f_fss_delimit_quote_single;
      }
    }

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_string_dynamic_t object = f_string_dynamic_t_initialize;
    f_string_dynamic_t content = f_string_dynamic_t_initialize;

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (data->process_pipe) {
        status = fss_basic_list_write_process_pipe(*data, output, quote, &buffer);

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sWhile processing the ", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "input pipe");
            fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol_s[0]);
          }
        }
      }

      if (F_status_is_error_not(status)) {
        if (data->parameters[fss_basic_list_write_parameter_partial].result == f_console_result_found) {

          if (data->parameters[fss_basic_list_write_parameter_object].result == f_console_result_additional) {
            for (f_array_length_t i = 0; i < data->parameters[fss_basic_list_write_parameter_object].values.used; i++) {

              object.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_object].values.array[i]];
              object.used = strnlen(object.string, f_console_length_size);
              object.size = object.used;

              status = fss_basic_list_write_process(*data, output, quote, &object, 0, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
          else {
            for (f_array_length_t i = 0; i < data->parameters[fss_basic_list_write_parameter_content].values.used; i++) {

              content.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_content].values.array[i]];
              content.used = strnlen(content.string, f_console_length_size);
              content.size = content.used;

              status = fss_basic_list_write_process(*data, output, quote, 0, &content, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
        }
        else {
          for (f_array_length_t i = 0; i < data->parameters[fss_basic_list_write_parameter_object].values.used; i++) {

            object.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_object].values.array[i]];
            object.used = strnlen(object.string, f_console_length_size);
            object.size = object.used;

            content.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_content].values.array[i]];
            content.used = strnlen(content.string, f_console_length_size);
            content.size = content.used;

            status = fss_basic_list_write_process(*data, output, quote, &object, &content, &buffer);
            if (F_status_is_error(status)) break;
          } // for
        }

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fl_color_print(data->error.to.stream, data->context.set.error, "%sWhile processing the ", fll_error_print_error);
            fl_color_print(data->error.to.stream, data->context.set.notable, "input arguments");
            fl_color_print(data->error.to.stream, data->context.set.error, ".%c", f_string_eol_s[0]);
          }
        }
        else if (data->error.verbosity != f_console_verbosity_quiet && data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_none) {
          // ensure there is always a newline at the end, unless in quiet mode.
          fprintf(data->output.stream, "%c", f_string_eol_s[0]);
        }
      }

      f_macro_string_dynamic_t_delete_simple(escaped);

      // object and content, though being a "dynamic" type, is being used statically, so clear them up to avoid invalid free().
      object.string = 0;
      object.used = 0;
      object.size = 0;

      content.string = 0;
      content.used = 0;
      content.size = 0;
    }

    if (data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_additional) {
      if (output.id != -1) {
        f_file_stream_close(F_true, &output);
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
      }
    }

    f_macro_string_dynamic_t_delete_simple(buffer);
    f_macro_string_dynamic_t_delete_simple(object);
    f_macro_string_dynamic_t_delete_simple(content);
    fss_basic_list_write_delete_data(data);
    return status;
  }
#endif // _di_fss_basic_list_write_main_

#ifndef _di_fss_basic_list_write_delete_data_
  f_status_t fss_basic_list_write_delete_data(fss_basic_list_write_data_t *data) {

    for (f_string_length_t i = 0; i < fss_basic_list_write_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].values);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);

    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_fss_basic_list_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
