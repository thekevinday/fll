#include <level_3/fss_status_code.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_print_help_
  f_return_status fss_status_code_print_help(const fss_status_code_data data) {
    fll_program_print_help_header(data.context, fss_status_code_name_long, fss_status_code_version);

    fll_program_print_help_option(data.context, f_console_standard_short_help, f_console_standard_long_help, "    Print this help message.");
    fll_program_print_help_option(data.context, f_console_standard_short_light, f_console_standard_long_light, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(data.context, f_console_standard_short_no_color, f_console_standard_long_no_color, "Do not output in color.");
    fll_program_print_help_option(data.context, f_console_standard_short_version, f_console_standard_long_version, " Print only the version number.");

    printf("%c", f_string_eol);

    fll_program_print_help_option(data.context, fss_status_code_short_is_fine, fss_status_code_long_is_fine, "   Print f_true if the error code is not an error.");
    fll_program_print_help_option(data.context, fss_status_code_short_is_warning, fss_status_code_long_is_warning, "Print f_true if the error code is a warning.");
    fll_program_print_help_option(data.context, fss_status_code_short_is_error, fss_status_code_long_is_error, "  Print f_true if the error code is an error.");
    fll_program_print_help_option(data.context, fss_status_code_short_number, fss_status_code_long_number, "    Convert status code name to number.");

    fll_program_print_help_usage(data.context, fss_status_code_name, "status code(s)");

    return f_none;
  }
#endif // _di_fss_status_code_print_help_

#ifndef _di_fss_status_code_main_
  f_return_status fss_status_code_main(const f_array_length argc, const f_string argv[], fss_status_code_data *data) {
    f_status status = f_none;
    f_status allocation_status = f_none;

    status = fl_process_parameters(argc, argv, data->parameters, fss_status_code_total_parameters, &data->remaining);

    // load colors when not told to show no colors
    if (data->parameters[fss_status_code_parameter_no_color].result == f_console_result_none) {
      fl_macro_color_context_new(allocation_status, data->context);

      if (f_status_is_error(allocation_status)) {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory\n");
        fss_status_code_delete_data(data);
        return allocation_status;
      }

      fl_color_load_context(&data->context, data->parameters[fss_status_code_parameter_light].result == f_console_result_found);
    }

    if (f_status_is_error(status)) {
      status = f_status_set_fine(status);

      if (status == f_no_data) {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // TODO: there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      }
      else if (status == f_allocation_error || status == f_reallocation_error) {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory.");
      }
      else if (status == f_invalid_parameter) {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_process_parameters().");
      }
      else {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_process_parameters().", status);
      }

      fss_status_code_delete_data(data);
      return f_status_set_error(status);
    }

    // execute parameter results
    if (data->parameters[fss_status_code_parameter_help].result == f_console_result_found) {
      fss_status_code_print_help(*data);
    }
    else if (data->parameters[fss_status_code_parameter_version].result == f_console_result_found) {
      fll_program_print_version(fss_status_code_version);
    }
    else if (data->parameters[fss_status_code_parameter_is_error].result == f_console_result_found) {
      if (data->remaining.used > 0) {
        f_array_length counter = 0;

        f_status code = f_none;
        f_u_int true = 0;

        for (; counter < data->remaining.used; counter++) {
          // only numbers are valid status codes.
          if (f_is_digit(argv[data->remaining.array[counter]][0]) == f_false) {
            status = f_false;
            continue;
          }

          long long number = atoll(argv[data->remaining.array[counter]]);
          if (number >= 0x10000 || number < 0) {
            status = f_false;
            continue;
          }

          code = (f_status) number;
          true = f_status_is_error(code) && !f_status_is_warning(code);

          if (status == f_none) {
            status = f_true;
          }

          if (true) {
            printf("%s\n", fl_status_string_true);
          }
          else {
            printf("%s\n", fl_status_string_false);
          }
        } // for
      }
      else {
        status = f_false;
      }
    }
    else if (data->parameters[fss_status_code_parameter_is_warning].result == f_console_result_found) {
      if (data->remaining.used > 0) {
        f_array_length counter = 0;

        f_status code = f_none;
        f_u_int true = 0;

        for (; counter < data->remaining.used; counter++) {
          // only numbers are valid status codes.
          if (f_is_digit(argv[data->remaining.array[counter]][0]) == f_false) {
            status = f_false;
            continue;
          }

          long long number = atoll(argv[data->remaining.array[counter]]);
          if (number >= 0x10000 || number < 0) {
            status = f_false;
            continue;
          }

          code = (f_status) number;
          true = f_status_is_warning(code) && !f_status_is_error(code);

          if (status == f_none) {
            status = f_true;
          }

          if (true) {
            printf("%s\n", fl_status_string_true);
          }
          else {
            printf("%s\n", fl_status_string_false);
          }
        } // for
      }
      else {
        status = f_false;
      }
    }
    else if (data->parameters[fss_status_code_parameter_is_fine].result == f_console_result_found) {
      if (data->remaining.used > 0) {
        f_array_length counter = 0;

        f_status code = f_none;
        f_u_int true = 0;

        for (; counter < data->remaining.used; counter++) {
          // only numbers are valid status codes.
          if (f_is_digit(argv[data->remaining.array[counter]][0]) == f_false) {
            status = f_false;
            continue;
          }

          long long number = atoll(argv[data->remaining.array[counter]]);
          if (number >= 0x10000 || number < 0) {
            status = f_false;
            continue;
          }

          code = (f_status) number;
          true = f_status_is_fine(code);

          if (status == f_none) {
            status = f_true;
          }

          if (true) {
            printf("%s\n", fl_status_string_true);
          }
          else {
            printf("%s\n", fl_status_string_false);
          }
        } // for
      }
      else {
        status = f_false;
      }
    }
    else if (data->parameters[fss_status_code_parameter_number].result == f_console_result_found) {
      if (data->remaining.used > 0) {
        f_array_length counter = 0;
        f_status code = f_none;
        f_status status2 = f_none;

        for (; counter < data->remaining.used; counter++) {
          // numbers are not valid status code strings.
          if (f_is_digit(argv[data->remaining.array[counter]][0]) == f_true) {
            status = f_false;
            continue;
          }

          status2 = fll_status_from_string(argv[data->remaining.array[counter]], &code);

          if (f_status_is_error(status2)) {
            status = status2;
            break;
          }
          else if (status2 == f_invalid_data) {
            status = f_false;
            continue;
          }
          else if (status == f_none) {
            status = f_true;
          }

          printf("%u\n", code);
        } // for
      }
      else {
        status = f_false;
      }
    }
    else if (data->remaining.used > 0 || data->process_pipe) {
      f_array_length counter = 0;

      if (data->process_pipe) {
        // TODO: how should this be done?
      }

      if (data->remaining.used > 0) {
        for (; counter < data->remaining.used; counter++) {
          // only numbers are valid status code.
          if (f_is_digit(argv[data->remaining.array[counter]][0]) == f_false) {
            status = f_false;
            continue;
          }

          long long number = atoll(argv[data->remaining.array[counter]]);
          if (number >= 0x10000 || number < 0) {
            status = f_false;
            continue;
          }
          else if (status == f_none) {
            status = f_true;
          }

          f_status code = (f_status) number;
          f_string string = 0;

          if (fll_fss_status_to_string(code, &string) == f_none) {
            printf("%s\n", string);
          }
          else {
            status = f_false;
          }
        } // for
      }
      else {
        status = f_false;
      }
    }
    else {
      fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: you failed to specify an error code.");
      status = f_status_set_error(f_invalid_parameter);
    }

    fss_status_code_delete_data(data);
    return status;
  }
#endif // _di_fss_status_code_main_

#ifndef _di_fss_status_code_delete_data_
  f_return_status fss_status_code_delete_data(fss_status_code_data *data) {
    f_status status = f_none;
    f_string_length i = 0;

    while (i < fss_status_code_total_parameters) {
      f_macro_string_lengths_delete(status, data->parameters[i].additional);
      i++;
    } // while

    f_macro_string_lengths_delete(status, data->remaining);
    fl_macro_color_context_delete(status, data->context);

    return f_none;
  }
#endif // _di_fss_status_code_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
