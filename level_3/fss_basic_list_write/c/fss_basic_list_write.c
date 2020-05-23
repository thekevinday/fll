#include <level_3/fss_basic_list_write.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_write_print_help_
  f_return_status fss_basic_list_write_print_help(const fl_color_context context) {
    fll_program_print_help_header(context, fss_basic_list_write_name_long, fss_basic_list_write_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol);

    fll_program_print_help_option(context, fss_basic_list_write_short_object, fss_basic_list_write_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Write an object instead of content.");
    fll_program_print_help_option(context, fss_basic_list_write_short_file, fss_basic_list_write_long_file, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Specify a file to send output to.");
    fll_program_print_help_option(context, fss_basic_list_write_short_string, fss_basic_list_write_long_string, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Specify a string to convert.");

    fll_program_print_help_usage(context, fss_basic_list_write_name, "");

    return F_none;
  }
#endif // _di_fss_basic_list_write_print_help_

#ifndef _di_fss_basic_list_write_main_
  f_return_status fss_basic_list_write_main(const f_console_arguments arguments, fss_basic_list_write_data *data) {
    f_status status = F_none;

    {
      f_console_parameters parameters = { data->parameters, fss_basic_list_write_total_parameters };
      f_console_parameter_id ids[3] = { fss_basic_list_write_parameter_no_color, fss_basic_list_write_parameter_light, fss_basic_list_write_parameter_dark };
      f_console_parameter_ids choices = { ids, 3 };

      status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

      if (F_status_is_error(status)) {
        fss_basic_list_write_delete_data(data);
        return F_status_set_error(status);
      }

      status = F_none;
    }

    if (data->parameters[fss_basic_list_write_parameter_help].result == f_console_result_found) {
      fss_basic_list_write_print_help(data->context);
    }
    else if (data->parameters[fss_basic_list_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(fss_basic_list_write_version);
    }
    else {
      f_array_length counter = 0;
      bool object = (data->parameters[fss_basic_list_write_parameter_object].result == f_console_result_found);

      f_string_dynamic buffer = f_string_dynamic_initialize;
      f_string_range range = f_string_range_initialize;

      if (data->process_pipe) {
        f_file file  = f_file_initialize;
        f_string_dynamic input = f_string_dynamic_initialize;

        file.id = f_type_descriptor_input;

        status = f_file_read(file, &input);

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_parameter) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          }
          else if (status == F_file_found_not) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", "-");
          }
          else if (status == F_file_open) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", "-");
          }
          else if (status == F_file_descriptor) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", "-");
          }
          else {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_open()", status);
          }

          f_macro_string_dynamic_delete_simple(input);
          fss_basic_list_write_delete_data(data);
          return F_status_set_error(status);
        }

        range.start = 0;
        range.stop = input.used - 1;

        if (object) {
          status = fl_fss_basic_list_object_write(input, &range, &buffer);

          if (F_status_is_error(status) || status == F_data_no_stop || status == F_data_no_eos || status == F_data_no_eol) {
            return F_status_set_error(status);
          }
        }
        else {
          status = fl_fss_basic_list_content_write(input, &range, &buffer);

          if (F_status_is_error(status) || status == F_data_no_stop || status == F_data_no_eos || status == F_data_no_eol) {
            return F_status_set_error(status);
          }
        }

        f_macro_string_dynamic_delete_simple(input);
      }
      else if (data->parameters[fss_basic_list_write_parameter_string].result == f_console_result_additional) {
        f_string_dynamic input = f_string_dynamic_initialize;

        input.string = arguments.argv[data->parameters[fss_basic_list_write_parameter_string].additional.array[0]];
        input.used = strlen(input.string);

        range.start = 0;
        range.stop = input.used - 1;

        if (object) {
          status = fl_fss_basic_list_object_write(input, &range, &buffer);

          if (F_status_is_error(status) || status == F_data_no_stop || status == F_data_no_eos || status == F_data_no_eol) {
            return F_status_set_error(status);
          }
        }
        else {
          status = fl_fss_basic_list_content_write(input, &range, &buffer);

          if (F_status_is_error(status) || status == F_data_no_stop || status == F_data_no_eos || status == F_data_no_eol) {
            return F_status_set_error(status);
          }
        }

        status = F_none;
      }

      if (data->parameters[fss_basic_list_write_parameter_file].result == f_console_result_additional) {
        f_file output = f_file_initialize;

        output.flags = f_file_flag_append_wo;

        status = f_file_open(arguments.argv[data->parameters[fss_basic_list_write_parameter_file].additional.array[0]], 0, &output);

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          f_file_close(&output.id);

          if (status == F_parameter) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          }
          else if (status == F_file_found_not) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", arguments.argv[data->parameters[fss_basic_list_write_parameter_file].additional.array[0]]);
          }
          else if (status == F_file_open) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", arguments.argv[data->parameters[fss_basic_list_write_parameter_file].additional.array[0]]);
          }
          else if (status == F_file_descriptor) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", arguments.argv[data->parameters[fss_basic_list_write_parameter_file].additional.array[0]]);
          }
          else {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_open()", status);
          }

          fss_basic_list_write_delete_data(data);
          return F_status_set_error(status);
        }

        status = f_file_write(output, buffer, 0);
        f_file_close(&output.id);

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_parameter) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_write()");
          }
          else if (status == F_file_write) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: Unable to write to the file '%s'", arguments.argv[data->parameters[fss_basic_list_write_parameter_file].additional.array[0]]);
          }
          else {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling fl_file_write()", status);
          }

          fss_basic_list_write_delete_data(data);
          return F_status_set_error(status);
        }
      }
      else {
        f_print_string_dynamic(f_type_output, buffer);
      }
    }

    fss_basic_list_write_delete_data(data);
    return status;
  }
#endif // _di_fss_basic_list_write_main_

#ifndef _di_fss_basic_list_write_delete_data_
  f_return_status fss_basic_list_write_delete_data(fss_basic_list_write_data *data) {
    f_string_length i = 0;

    while (i < fss_basic_list_write_total_parameters) {
      f_macro_string_lengths_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_delete_simple(data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_lengths_delete_simple(data->remaining);
    fl_macro_color_context_delete_simple(data->context);

    return F_none;
  }
#endif // _di_fss_basic_list_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
