#include <level_3/fss_extended_list_read.h>
#include "private-fss_extended_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_print_help_
  f_return_status fss_extended_list_read_print_help(const fss_extended_list_read_data data) {
    fll_program_print_help_header(data.context, fss_extended_list_read_name_long, fss_extended_list_read_version);

    fll_program_print_help_option(data.context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(data.context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(data.context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(data.context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(data.context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol);

    fll_program_print_help_option(data.context, fss_extended_list_read_short_name, fss_extended_list_read_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Find and print content from this object name.");
    fll_program_print_help_option(data.context, fss_extended_list_read_short_count, fss_extended_list_read_long_count, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Find a specific occurrence of the object.");
    fll_program_print_help_option(data.context, fss_extended_list_read_short_total, fss_extended_list_read_long_total, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Print the total number of objects in this file.");
    fll_program_print_help_option(data.context, fss_extended_list_read_short_object, fss_extended_list_read_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Print the object instead of the content.");
    fll_program_print_help_option(data.context, fss_extended_list_read_short_size, fss_extended_list_read_long_size, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print total lines in the given content.");
    fll_program_print_help_option(data.context, fss_extended_list_read_short_line, fss_extended_list_read_long_line, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print only the content at the given line.");

    fll_program_print_help_usage(data.context, fss_extended_list_read_name, "filename(s)");

    return f_none;
  }
#endif // _di_fss_extended_list_read_print_help_

#ifndef _di_fss_extended_list_read_main_
  f_return_status fss_extended_list_read_main(const f_console_arguments arguments, fss_extended_list_read_data *data) {
    f_status status = f_none;

    {
      f_console_parameters parameters = { data->parameters, fss_extended_list_read_total_parameters };
      f_console_parameter_id ids[3] = { fss_extended_list_read_parameter_no_color, fss_extended_list_read_parameter_light, fss_extended_list_read_parameter_dark };
      f_console_parameter_ids choices = { ids, 3 };

      status = fll_program_process_parameters(arguments, parameters, choices, &data->remaining, &data->context);
    }

    if (f_status_is_error(status)) {
      fss_extended_list_read_delete_data(data);
      return f_status_set_error(status);
    }

    f_status status2 = f_none;
    status = f_none;

    // execute parameter results
    if (data->parameters[fss_extended_list_read_parameter_help].result == f_console_result_found) {
      fss_extended_list_read_print_help(*data);
    }
    else if (data->parameters[fss_extended_list_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(fss_extended_list_read_version);
    }
    else if (data->remaining.used > 0 || data->process_pipe) {
      f_string_length counter = 0;
      f_string_length target  = 0;
      f_string_length original_size = data->file_position.total_elements;

      if (data->parameters[fss_extended_list_read_parameter_count].result == f_console_result_additional) {
        target = (f_string_length) atoll(arguments.argv[data->parameters[fss_extended_list_read_parameter_count].additional.array[0]]);
      }

      if (data->process_pipe) {
        f_file file = f_file_initialize;

        file.address = f_pipe;

        status = fl_file_read_fifo(file, &data->buffer);

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_invalid_parameter) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          }
          else if (status == f_file_not_found) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", "-");
          }
          else if (status == f_file_open_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", "-");
          }
          else if (status == f_file_descriptor_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", "-");
          }
          else {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", f_status_set_error(status));
          }

          fss_extended_list_read_delete_data(data);
          return status;
        }

        status = fss_extended_list_read_main_process_file(arguments, data, "-", target);

        if (f_status_is_error(status)) {
          return status;
        }

        // clear buffers before continuing
        f_macro_fss_contents_delete(status2, data->contents);
        f_macro_fss_objects_delete(status2, data->objects);
        f_macro_string_dynamic_delete(status2, data->buffer);
      }

      for (; counter < data->remaining.used; counter++) {
        f_file file = f_file_initialize;

        status = f_file_open(&file, arguments.argv[data->remaining.array[counter]]);

        data->file_position.total_elements = original_size;

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_invalid_parameter) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          }
          else if (status == f_file_not_found) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", arguments.argv[data->remaining.array[counter]]);
          }
          else if (status == f_file_open_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", arguments.argv[data->remaining.array[counter]]);
          }
          else if (status == f_file_descriptor_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", arguments.argv[data->remaining.array[counter]]);
          }
          else {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", f_status_set_error(status));
          }

          fss_extended_list_read_delete_data(data);
          return f_status_set_error(status);
        }

        if (data->file_position.total_elements == 0) {
          fseek(file.address, 0, SEEK_END);

          data->file_position.total_elements = ftell(file.address);

          // skip past empty files
          if (data->file_position.total_elements == 0) {
            f_file_close(&file);
            continue;
          }

          fseek(file.address, 0, SEEK_SET);
        }

        status = fl_file_read(file, data->file_position, &data->buffer);

        f_file_close(&file);

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_invalid_parameter) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_read()");
          }
          else if (status == f_overflow) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Integer overflow while trying to buffer the file '%s'", arguments.argv[data->remaining.array[counter]]);
          }
          else if (status == f_file_not_open) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: The file '%s' is no longer open", arguments.argv[data->remaining.array[counter]]);
          }
          else if (status == f_file_seek_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A seek error occurred while accessing the file '%s'", arguments.argv[data->remaining.array[counter]]);
          }
          else if (status == f_file_read_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A read error occurred while accessing the file '%s'", arguments.argv[data->remaining.array[counter]]);
          }
          else if (status == f_allocation_error || status == f_reallocation_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
          }
          else {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_file_read()", f_status_set_error(status));
          }

          fss_extended_list_read_delete_data(data);
          return f_status_set_error(status);
        }

        status = fss_extended_list_read_main_process_file(arguments, data, arguments.argv[data->remaining.array[counter]], target);

        if (f_status_is_error(status)) {
          return status;
        }

        // clear buffers before repeating the loop
        f_macro_fss_contents_delete(status2, data->contents);
        f_macro_fss_objects_delete(status2, data->objects);
        f_macro_string_dynamic_delete(status2, data->buffer);
      } // for
    }
    else {
      fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: you failed to specify one or more files");
      status = f_status_set_error(f_invalid_parameter);
    }

    fss_extended_list_read_delete_data(data);
    return status;
  }
#endif // _di_fss_extended_list_read_main_

#ifndef _di_fss_extended_list_read_delete_data_
  f_return_status fss_extended_list_read_delete_data(fss_extended_list_read_data *data) {
    f_status status = f_none;
    f_string_length i = 0;

    while (i < fss_extended_list_read_total_parameters) {
      f_macro_string_lengths_delete(status, data->parameters[i].additional);
      i++;
    } // while

    f_macro_fss_contents_delete(status, data->contents);
    f_macro_fss_objects_delete(status, data->objects);
    f_macro_string_dynamic_delete(status, data->buffer);
    f_macro_string_lengths_delete(status, data->remaining);

    fl_macro_color_context_delete(status, data->context);

    return f_none;
  }
#endif // _di_fss_extended_list_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
