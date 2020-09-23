#include "fss_basic_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_write_print_help_
  f_return_status fss_basic_write_print_help(const int id, const f_color_context_t context) {

    fll_program_print_help_header(id, context, fss_basic_write_name_long, fss_basic_write_version);

    fll_program_print_help_option(id, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(id, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(id, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(id, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(id, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(id, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(id, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(id, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(id, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(id, context, fss_basic_write_short_content, fss_basic_write_long_content, f_console_symbol_short_enable, f_console_symbol_long_enable, " The content to output.");
    fll_program_print_help_option(id, context, fss_basic_write_short_double, fss_basic_write_long_double, f_console_symbol_short_enable, f_console_symbol_long_enable, " Use double quotes (default).");
    fll_program_print_help_option(id, context, fss_basic_write_short_file, fss_basic_write_long_file, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Specify a file to send output to.");
    fll_program_print_help_option(id, context, fss_basic_write_short_object, fss_basic_write_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, " The object to output.");
    fll_program_print_help_option(id, context, fss_basic_write_short_partial, fss_basic_write_long_partial, f_console_symbol_short_enable, f_console_symbol_long_enable, "Do not output end of object/content character.");
    fll_program_print_help_option(id, context, fss_basic_write_short_single, fss_basic_write_long_single, f_console_symbol_short_enable, f_console_symbol_long_enable, " Use single quotes.");

    fll_program_print_help_usage(id, context, fss_basic_write_name, "");

    return F_none;
  }
#endif // _di_fss_basic_write_print_help_

#ifndef _di_fss_basic_write_main_
  f_return_status fss_basic_write_main(const f_console_arguments_t arguments, fss_basic_write_data *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, fss_basic_write_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { fss_basic_write_parameter_no_color, fss_basic_write_parameter_light, fss_basic_write_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        if (F_status_is_error(status)) {
          fss_basic_write_delete_data(data);
          return status;
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_basic_write_parameter_verbosity_quiet, fss_basic_write_parameter_verbosity_normal, fss_basic_write_parameter_verbosity_verbose, fss_basic_write_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_basic_write_delete_data(data);
          return status;
        }

        if (choice == fss_basic_write_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_basic_write_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_basic_write_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_basic_write_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[fss_basic_write_parameter_help].result == f_console_result_found) {
      fss_basic_write_print_help(data->output, data->context);

      fss_basic_write_delete_data(data);
      return status;
    }

    if (data->parameters[fss_basic_write_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, fss_basic_write_version);

      fss_basic_write_delete_data(data);
      return status;
    }

    f_array_length_t counter = 0;
    bool object = (data->parameters[fss_basic_write_parameter_object].result == f_console_result_found);

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_string_range_t range = f_string_range_t_initialize;

    if (data->process_pipe) {
      f_file_t file = f_file_t_initialize;
      f_string_dynamic_t input = f_string_dynamic_t_initialize;

      file.id = f_type_descriptor_input;

      status = f_file_read(file, &input);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_parameter) {
          fl_color_print_to(data->error.to, data->context.set.error, "INTERNAL ERROR: Invalid parameter when calling f_file_open()%c", f_string_eol[0]);
        }
        else if (status == F_file_found_not) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Unable to find the file '%s'%c", "-", f_string_eol[0]);
        }
        else if (status == F_file_open) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Unable to open the file '%s'%c", "-", f_string_eol[0]);
        }
        else if (status == F_file_descriptor) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: File descriptor error while trying to open the file '%s'%c", "-", f_string_eol[0]);
        }
        else {
          fl_color_print_to(data->error.to, data->context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_open()%c", status, f_string_eol[0]);
        }

        f_macro_string_dynamic_t_delete_simple(input);
        fss_basic_write_delete_data(data);
        return F_status_set_error(status);
      }

      if (input.used) {
        range.start = 0;
        range.stop = input.used - 1;

        if (object) {
          status = fl_fss_basic_object_write(input, 0, &range, &buffer);

          if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
            f_macro_string_dynamic_t_delete_simple(buffer);
            f_macro_string_dynamic_t_delete_simple(input);
            fss_basic_write_delete_data(data);
            return F_status_set_error(status);
          }
        }
        else {
          status = fl_fss_basic_content_write(input, &range, &buffer);

          if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
            f_macro_string_dynamic_t_delete_simple(buffer);
            f_macro_string_dynamic_t_delete_simple(input);
            fss_basic_write_delete_data(data);
            return F_status_set_error(status);
          }
        }

        if (data->parameters[fss_basic_write_parameter_partial].result == f_console_result_found) {
          buffer.used--;
        }
      }

      f_macro_string_dynamic_t_delete_simple(input);
    }
    else if (data->parameters[fss_basic_write_parameter_string].result == f_console_result_additional) {
      f_string_dynamic_t input = f_string_dynamic_t_initialize;

      input.string = arguments.argv[data->parameters[fss_basic_write_parameter_string].additional.array[0]];
      input.used = strnlen(input.string, f_console_length_size);

      if (input.used) {
        range.start = 0;
        range.stop = input.used - 1;

        if (object) {
          status = fl_fss_basic_object_write(input, 0, &range, &buffer);

          if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
            f_macro_string_dynamic_t_delete_simple(buffer);
            fss_basic_write_delete_data(data);
            return F_status_set_error(status);
          }
        }
        else {
          status = fl_fss_basic_content_write(input, &range, &buffer);

          if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
            f_macro_string_dynamic_t_delete_simple(buffer);
            fss_basic_write_delete_data(data);
            return F_status_set_error(status);
          }
        }

        if (data->parameters[fss_basic_write_parameter_partial].result == f_console_result_found) {
          buffer.used--;
        }
      }

      status = F_none;
    }

    if (data->parameters[fss_basic_write_parameter_file].result == f_console_result_additional) {
      f_file_t output = f_file_t_initialize;

      output.flag = f_file_flag_append_wo;

      status = f_file_open(arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]], 0, &output);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        f_file_close(&output.id);

        if (status == F_parameter) {
          fl_color_print_to(data->error.to, data->context.set.error, "INTERNAL ERROR: Invalid parameter when calling f_file_open()%c", f_string_eol[0]);
        }
        else if (status == F_file_found_not) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Unable to find the file '%s'%c", arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]], f_string_eol[0]);
        }
        else if (status == F_file_open) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Unable to open the file '%s'%c", arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]], f_string_eol[0]);
        }
        else if (status == F_file_descriptor) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: File descriptor error while trying to open the file '%s'%c", arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]], f_string_eol[0]);
        }
        else {
          fl_color_print_to(data->error.to, data->context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_open()%c", status, f_string_eol[0]);
        }

        f_macro_string_dynamic_t_delete_simple(buffer);
        fss_basic_write_delete_data(data);
        return status;
      }

      status = f_file_write(output, buffer, 0);
      f_file_close(&output.id);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_parameter) {
          fl_color_print_to(data->error.to, data->context.set.error, "INTERNAL ERROR: Invalid parameter when calling f_file_write()%c", f_string_eol[0]);
        }
        else if (status == F_file_write) {
          fl_color_print_to(data->error.to, data->context.set.error, "ERROR: Unable to write to the file '%s'%c", arguments.argv[data->parameters[fss_basic_write_parameter_file].additional.array[0]], f_string_eol[0]);
        }
        else {
          fl_color_print_to(data->error.to, data->context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_write()%c", status, f_string_eol[0]);
        }

        f_macro_string_dynamic_t_delete_simple(buffer);
        fss_basic_write_delete_data(data);
        return F_status_set_error(status);
      }
    }
    else {
      f_print_dynamic(f_type_output, buffer);
    }

    f_macro_string_dynamic_t_delete_simple(buffer);

    fss_basic_write_delete_data(data);
    return status;
  }
#endif // _di_fss_basic_write_main_

#ifndef _di_fss_basic_write_delete_data_
  f_return_status fss_basic_write_delete_data(fss_basic_write_data *data) {
    f_status_t status = F_none;

    for (f_string_length_t i = 0; i < fss_basic_write_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);
    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_fss_basic_write_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
