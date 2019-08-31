#include <level_3/fss_status_code.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_print_help_
  f_return_status fss_status_code_print_help(const fss_status_code_data data) {
    printf("\n");
    fl_color_print(f_standard_output, data.context.title, data.context.reset, " %s", fss_status_code_name_long);

    printf("\n");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "  Version %s", fss_status_code_version);


    printf("\n\n");
    fl_color_print(f_standard_output, data.context.important, data.context.reset, " Available Options: ");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_help);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_help);
    printf("      Print this help message");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_light);

    printf(", %s", f_console_symbol_long_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_light);
    printf("     Output using colors that show up better on light backgrounds");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_no_color);

    printf(", %s", f_console_symbol_long_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_no_color);
    printf("  Do not output in color");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_version);

    printf(", %s", f_console_symbol_long_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_version);
    printf("   Print only the version number");


    printf("\n");
    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_short_is_fine);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_long_is_fine);
    printf("     Returns true if the error code is not an error.");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_short_is_warning);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_long_is_warning);
    printf("  Returns true if the error code is a warning.");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_short_is_error);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_long_is_error);
    printf("    Returns true if the error code is an error.");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_short_number);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_long_number);
    printf("      Convert status code name to number.");


    printf("\n\n");
    fl_color_print(f_standard_output, data.context.important, data.context.reset, " Usage: ");

    printf("\n  ");
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_status_code_name);

    printf("  ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" options ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "]");

    printf("  ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "<");

    printf(" error code(s) ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, ">");


    printf("\n\n");

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
      fl_new_color_context(allocation_status, data->context);

      if (f_status_is_error(allocation_status)) {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory\n");
        fss_status_code_delete_data(data);
        return allocation_status;
      }

      fll_colors_load_context(&data->context, data->parameters[fss_status_code_parameter_light].result == f_console_result_found);
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
      fl_program_print_version(fss_status_code_version);
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
      f_delete_string_lengths(status, data->parameters[i].additional);
      i++;
    } // while

    f_delete_string_lengths(status, data->remaining);
    fl_delete_color_context(status, data->context);

    return f_none;
  }
#endif // _di_fss_status_code_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
