/* FLL - Level 3
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_3/fss_basic_write.h>

#ifdef __cplusplus
extern "C"{
#endif

// version printed may be used by scripts, so this will only print the version number and a newline, no extra information or colors
#ifndef _di_fss_basic_write_print_version_
  f_return_status fss_basic_write_print_version(const fss_basic_write_data data) {
    printf("%s\n", fss_basic_write_version);

    return f_none;
  }
#endif // _fss_basic_write_print_version_

#ifndef _di_fss_basic_write_print_help_
  f_return_status fss_basic_write_print_help(const fss_basic_write_data data) {
    printf("\n");
    fl_print_color(f_standard_output, data.context.title, data.context.reset, " %s", fss_basic_write_name_long);

    printf("\n");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "  Version %s", fss_basic_write_version);


    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Available Options: ");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_help);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_help);
    printf("      Print this help message");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_light);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_light);
    printf("     Output using colors that show up better on light backgrounds");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_no_color);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_no_color);
    printf("  Do not output in color");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_version);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_version);
    printf("   Print only the version number");


    printf("\n");
    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, fss_basic_write_short_object);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, fss_basic_write_long_object);
    printf("  Write an object instead of content.");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, fss_basic_write_short_file);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, fss_basic_write_long_file);
    printf("    Specify a file to send output to.");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, fss_basic_write_short_string);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, fss_basic_write_long_string);
    printf("  Specify a string to convert.");


    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Usage: ");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, fss_basic_write_name);

    printf("  ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" options ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "]");


    printf("\n\n");

    return f_none;
  }
#endif // _di_fss_basic_write_print_help_

#ifndef _di_fss_basic_write_main_
  f_return_status fss_basic_write_main(const f_array_length argc, const f_string argv[], fss_basic_write_data *data) {
    f_status status            = f_status_initialize;
    f_status allocation_status = f_status_initialize;

    status = fl_process_parameters(argc, argv, data->parameters, fss_basic_write_total_parameters, &data->remaining);

    // load colors when not told to show no colors
    if (data->parameters[fss_basic_write_parameter_no_color].result == f_console_result_none) {
      fll_new_color_context(allocation_status, data->context);

      if (allocation_status == f_none) {
        fll_colors_load_context(&data->context, data->parameters[fss_basic_write_parameter_light].result == f_console_result_found);
      } else {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory\n");
        fss_basic_write_delete_data(data);
        return allocation_status;
      }
    }

    if (status != f_none) {
      if (status == f_no_data) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // TODO: there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      } else if (f_macro_test_for_allocation_errors(status)) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory.");
      } else if (status == f_invalid_parameter) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_process_parameters().");
      } else {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_process_parameters().", status);
      }

      fss_basic_write_delete_data(data);
      return status;
    }

    // execute parameter results
    if (data->parameters[fss_basic_write_parameter_help].result == f_console_result_found) {
      fss_basic_write_print_help(*data);
    } else if (data->parameters[fss_basic_write_parameter_version].result == f_console_result_found) {
      fss_basic_write_print_version(*data);
    } else {
      f_array_length counter = f_array_length_initialize;
      f_bool         object  = (data->parameters[fss_basic_write_parameter_object].result == f_console_result_found);

      f_dynamic_string  buffer   = f_dynamic_string_initialize;
      f_string_location location = f_string_location_initialize;

      if (data->process_pipe) {
        f_file           file  = f_file_initialize;
        f_dynamic_string input = f_dynamic_string_initialize;

        file.file = f_pipe;

        status = fl_file_read_fifo(file, &input);

        if (status != f_none) {
          if (status == f_invalid_parameter) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          } else if (status == f_file_not_found) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", "-");
          } else if (status == f_file_open_error) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", "-");
          } else if (status == f_file_descriptor_error) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", "-");
          } else {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", status);
          }

          f_delete_dynamic_string(status, input);
          fss_basic_write_delete_data(data);
          return status;
        }

        location.start = 0;
        location.stop = input.used - 1;

        if (object) {
          status = fl_fss_basic_object_write(input, &location, &buffer);

          if (f_macro_test_for_no_data_errors(status)) {
            return status;
          }
        } else {
          status = fl_fss_basic_content_write(input, &location, &buffer);

          if (f_macro_test_for_no_data_errors(status)) {
            return status;
          }
        }

        f_delete_dynamic_string(status, input);
      } else if (data->parameters[fss_basic_write_parameter_string].result == f_console_result_additional) {
        f_dynamic_string input = f_dynamic_string_initialize;

        input.string = argv[data->parameters[fss_basic_write_parameter_string].additional.array[0]];
        input.used = strlen(input.string);

        location.start = 0;
        location.stop = input.used - 1;

        if (object) {
          status = fl_fss_basic_object_write(input, &location, &buffer);

          if (f_macro_test_for_no_data_errors(status)) {
            return status;
          }
        } else {
          status = fl_fss_basic_content_write(input, &location, &buffer);

          if (f_macro_test_for_no_data_errors(status)) {
            return status;
          }
        }

        status = f_none;
      }

      if (data->parameters[fss_basic_write_parameter_file].result == f_console_result_additional) {
        f_file output = f_file_initialize;

        output.mode = f_file_write_append;
        status = f_file_open(&output, argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);

        if (status != f_none) {
          f_file_close(&output);

          if (status == f_invalid_parameter) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          } else if (status == f_file_not_found) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);
          } else if (status == f_file_open_error) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);
          } else if (status == f_file_descriptor_error) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);
          } else {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", status);
          }

          fss_basic_write_delete_data(data);
          return status;
        }

        status = fl_file_write(output, buffer);
        f_file_close(&output);

        if (status != f_none) {
          if (status == f_invalid_parameter) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_write()");
          } else if (status == f_file_write_error) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to write to the file '%s'", argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]]);
          } else {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_file_write()", status);
          }

          fss_basic_write_delete_data(data);
          return status;
        }
      } else {
        f_print_dynamic_string(f_standard_output, buffer);
      }
    }

    fss_basic_write_delete_data(data);
    return status;
  }
#endif // _di_fss_basic_write_main_

#ifndef _di_fss_basic_write_delete_data_
  f_return_status fss_basic_write_delete_data(fss_basic_write_data *data) {
    f_status        status = f_status_initialize;
    f_string_length i      = 0;

    while (i < fss_basic_write_total_parameters) {
      f_delete_string_lengths(status, data->parameters[i].additional);
      i++;
    } // while

    f_delete_string_lengths(status, data->remaining);
    fll_delete_color_context(status, data->context);

    return f_none;
  }
#endif // _di_fss_basic_write_delete_data_


#ifdef __cplusplus
} // extern "C"
#endif
