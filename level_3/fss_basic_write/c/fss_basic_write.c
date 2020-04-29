#include <level_3/fss_basic_write.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_write_print_help_
  f_return_status fss_basic_write_print_help(const fl_color_context context) {
    fll_program_print_help_header(context, fss_basic_write_name_long, fss_basic_write_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol);

    fll_program_print_help_option(context, fss_basic_write_short_object, fss_basic_write_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Write an object instead of content.");
    fll_program_print_help_option(context, fss_basic_write_short_file, fss_basic_write_long_file, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Specify a file to send output to.");
    fll_program_print_help_option(context, fss_basic_write_short_string, fss_basic_write_long_string, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Specify a string to convert.");

    fll_program_print_help_usage(context, fss_basic_write_name, "");

    return f_none;
  }
#endif // _di_fss_basic_write_print_help_

#ifndef _di_fss_basic_write_main_
  f_return_status fss_basic_write_main(const f_console_arguments arguments, fss_basic_write_data *data) {
    f_status status = f_none;

    {
      f_console_parameters parameters = { data->parameters, fss_basic_write_total_parameters };
      f_console_parameter_id ids[3] = { fss_basic_write_parameter_no_color, fss_basic_write_parameter_light, fss_basic_write_parameter_dark };
      f_console_parameter_ids choices = { ids, 3 };

       status = fll_program_parameter_process(arguments, parameters, choices, &data->remaining, &data->context);
    }

    if (f_status_is_error(status)) {
      fss_basic_write_delete_data(data);
      return f_status_set_error(status);
    }

    status = f_none;

    if (data->parameters[fss_basic_write_parameter_help].result == f_console_result_found) {
      fss_basic_write_print_help(data->context);
    }
    else if (data->parameters[fss_basic_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(fss_basic_write_version);
    }
    else {
      f_array_length counter = 0;
      bool object = (data->parameters[fss_basic_write_parameter_object].result == f_console_result_found);

      f_string_dynamic buffer = f_string_dynamic_initialize;
      f_string_location location = f_string_location_initialize;

      if (data->process_pipe) {
        f_file file = f_file_initialize;
        f_string_dynamic input = f_string_dynamic_initialize;

        file.address = f_pipe;

        status = fl_file_read_fifo(file, &input);

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_invalid_parameter) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          }
          else if (status == f_file_not_found) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", "-");
          }
          else if (status == f_file_error_open) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", "-");
          }
          else if (status == f_file_error_descriptor) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", "-");
          }
          else {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_open()", status);
          }

          f_macro_string_dynamic_delete_simple(input);
          fss_basic_write_delete_data(data);
          return f_status_set_error(status);
        }

        location.start = 0;
        location.stop = input.used - 1;

        if (object) {
          status = fl_fss_basic_object_write(&buffer, input, &location);

          if (f_status_is_error(status) || status == f_no_data_on_stop || status == f_no_data_on_eos) {
            return f_status_set_error(status);
          }
        }
        else {
          status = fl_fss_basic_content_write(&buffer, input, &location);

          if (f_status_is_error(status) || status == f_no_data_on_stop || status == f_no_data_on_eos) {
            return f_status_set_error(status);
          }
        }

        f_macro_string_dynamic_delete_simple(input);
      }
      else if (data->parameters[fss_basic_write_parameter_string].result == f_console_result_additional) {
        f_string_dynamic input = f_string_dynamic_initialize;

        input.string = arguments.argv[data->parameters[fss_basic_write_parameter_string].additional.array[0]];
        input.used = strlen(input.string);

        location.start = 0;
        location.stop = input.used - 1;

        if (object) {
          status = fl_fss_basic_object_write(&buffer, input, &location);

          if (f_status_is_error(status) || status == f_no_data_on_stop || status == f_no_data_on_eos) {
            return f_status_set_error(status);
          }
        }
        else {
          status = fl_fss_basic_content_write(&buffer, input, &location);

          if (f_status_is_error(status) || status == f_no_data_on_stop || status == f_no_data_on_eos) {
            return f_status_set_error(status);
          }
        }

        status = f_none;
      }

      if (data->parameters[fss_basic_write_parameter_file].result == f_console_result_additional) {
        f_file output = f_file_initialize;

        output.mode = f_file_write_append;
        status = f_file_open(&output, arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          f_file_close(&output);

          if (status == f_invalid_parameter) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          }
          else if (status == f_file_not_found) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);
          }
          else if (status == f_file_error_open) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);
          }
          else if (status == f_file_error_descriptor) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);
          }
          else {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_open()", status);
          }

          fss_basic_write_delete_data(data);
          return status;
        }

        status = fl_file_write(output, buffer);
        f_file_close(&output);

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_invalid_parameter) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_write()");
          }
          else if (status == f_file_error_write) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to write to the file '%s'", arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);
          }
          else {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling fl_file_write()", status);
          }

          fss_basic_write_delete_data(data);
          return f_status_set_error(status);
        }
      }
      else {
        f_print_string_dynamic(f_standard_output, buffer);
      }
    }

    fss_basic_write_delete_data(data);
    return status;
  }
#endif // _di_fss_basic_write_main_

#ifndef _di_fss_basic_write_delete_data_
  f_return_status fss_basic_write_delete_data(fss_basic_write_data *data) {
    f_status status = f_none;
    f_string_length i = 0;

    while (i < fss_basic_write_total_parameters) {
      f_macro_string_lengths_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_lengths_delete_simple(data->remaining);
    fl_macro_color_context_delete_simple(data->context);

    return f_none;
  }
#endif // _di_fss_basic_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
