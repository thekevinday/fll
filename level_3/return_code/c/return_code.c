/* FLL - Level 3
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_3/return_code.h>

#ifdef __cplusplus
extern "C"{
#endif

// version printed may be used by scripts, so this will only print the version number and a newline, no extra information or colors
#ifndef _di_return_code_print_version_
  f_return_status return_code_print_version(const return_code_data data) {
    printf("%s\n", return_code_version);

    return f_none;
  }
#endif // _return_code_print_version_

#ifndef _di_return_code_print_help_
  f_return_status return_code_print_help(const return_code_data data) {
    printf("\n");
    fl_print_color(f_standard_output, data.context.title, data.context.reset, " %s", return_code_name_long);

    printf("\n");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "  Version %s", return_code_version);


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
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_short_is_fine);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_long_is_fine);
    printf("     Returns true if the error code is not an error.");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_short_is_warning);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_long_is_warning);
    printf("  Returns true if the error code is a warning.");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_short_is_error);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_long_is_error);
    printf("    Returns true if the error code is an error.");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_short_context);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_long_context);
    printf("     Guess error state from context of error (ignores masks).");


    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Usage: ");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, return_code_name);

    printf("  ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" options ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "]");

    printf("  ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "<");

    printf(" error code(s) ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, ">");


    printf("\n\n");

    return f_none;
  }
#endif // _di_return_code_print_help_

#ifndef _di_return_code_main_
  f_return_status return_code_main(const f_array_length argc, const f_string argv[], return_code_data *data) {
    f_status status            = f_none;
    f_status allocation_status = f_none;

    status = fl_process_parameters(argc, argv, data->parameters, return_code_total_parameters, &data->remaining);

    // load colors when not told to show no colors
    if (data->parameters[return_code_parameter_no_color].result == f_console_result_none) {
      fl_new_color_context(allocation_status, data->context);

      if (f_error_is_error(allocation_status)) {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory\n");
        return_code_delete_data(data);
        return allocation_status;
      }

      fll_colors_load_context(&data->context, data->parameters[return_code_parameter_light].result == f_console_result_found);
    }

    if (f_error_is_error(status)) {
      status = f_error_unmask(status);

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

      return_code_delete_data(data);
      return f_error_set_error(status);
    }

    // execute parameter results
    if (data->parameters[return_code_parameter_help].result == f_console_result_found) {
      return_code_print_help(*data);
    } else if (data->parameters[return_code_parameter_version].result == f_console_result_found) {
      return_code_print_version(*data);
    } else if (data->parameters[return_code_parameter_is_error].result == f_console_result_found && data->remaining.used > 0) {
      f_array_length counter = 0;

      f_status code = f_none;

      for (; counter < data->remaining.used; counter++) {
        code = (f_status) atoll(argv[data->remaining.array[counter]]);

        if (data->parameters[return_code_parameter_context].result == f_console_result_found) {
          if (fl_errors_is_error(code)) {
            return_code_delete_data(data);
            return f_true;
          }
        } else {
          if (f_error_is_error(code)) {
            return_code_delete_data(data);
            return f_true;
          }
        }
      }

      return_code_delete_data(data);
      return f_false;
    } else if (data->parameters[return_code_parameter_is_warning].result == f_console_result_found && data->remaining.used > 0) {
      f_array_length counter = 0;

      f_status code = f_none;

      for (; counter < data->remaining.used; counter++) {
        code = (f_status) atoll(argv[data->remaining.array[counter]]);

        if (data->parameters[return_code_parameter_context].result == f_console_result_found) {
          if (fl_errors_is_warning(code)) {
            return_code_delete_data(data);
            return f_true;
          }
        } else {
          if (f_error_is_warning(code)) {
            return_code_delete_data(data);
            return f_true;
          }
        }
      }

      return_code_delete_data(data);
      return f_false;
    } else if (data->parameters[return_code_parameter_is_fine].result == f_console_result_found && data->remaining.used > 0) {
      f_array_length counter = 0;

      f_status code = f_none;

      for (; counter < data->remaining.used; counter++) {
        code = (f_status) atoll(argv[data->remaining.array[counter]]);

        if (data->parameters[return_code_parameter_context].result == f_console_result_found) {
          if (fl_errors_is_fine(code)) {
            return_code_delete_data(data);
            return f_true;
          }
        } else {
          if (f_error_is_fine(code)) {
            return_code_delete_data(data);
            return f_true;
          }
        }
      }

      return_code_delete_data(data);
      return f_false;
    } else if (data->remaining.used > 0 || data->process_pipe) {
      f_array_length counter = 0;

      if (data->process_pipe) {
        // TODO: how should this be done?
      }

      if (data->remaining.used > 0) {
        for (; counter < data->remaining.used; counter++) {
          f_status code   = (f_status) atoll(argv[data->remaining.array[counter]]);
          f_string string = f_null;

          if (fl_errors_to_string(code, &string) == f_none) {
            printf("%s\n", string);
          }
        } // for
      }
    } else {
      fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: you failed to specify an error code.");
      status = f_error_set_error(f_invalid_parameter);
    }

    return_code_delete_data(data);
    return status;
  }
#endif // _di_return_code_main_

#ifndef _di_return_code_delete_data_
  f_return_status return_code_delete_data(return_code_data *data) {
    f_status        status = f_none;
    f_string_length i      = 0;

    while (i < return_code_total_parameters) {
      f_delete_string_lengths(status, data->parameters[i].additional);
      i++;
    } // while

    f_delete_string_lengths(status, data->remaining);
    fl_delete_color_context(status, data->context);

    return f_none;
  }
#endif // _di_return_code_delete_data_


#ifdef __cplusplus
} // extern "C"
#endif
