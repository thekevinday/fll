#include <level_3/status_code.h>
#include "private-status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_process_check_
  f_return_status status_code_process_check(const status_code_data data, const f_string value) {
    f_number_unsigned number = 0;
    f_status status = status_code_convert_number(data, value, &number);

    if (f_status_is_error(status)) {
      return status;
    }

    if (data.parameters[status_code_parameter_is_error].result == f_console_result_found) {
      if (f_status_is_error(number)) {
        printf("%s\n", fl_status_string_true);
      }
      else {
        printf("%s\n", fl_status_string_false);
      }
    }
    else if (data.parameters[status_code_parameter_is_warning].result == f_console_result_found) {
      if (f_status_is_warning(number)) {
        printf("%s\n", fl_status_string_true);
      }
      else {
        printf("%s\n", fl_status_string_false);
      }
    }
    else if (data.parameters[status_code_parameter_is_fine].result == f_console_result_found) {
      if (f_status_is_fine(number)) {
        printf("%s\n", fl_status_string_true);
      }
      else {
        printf("%s\n", fl_status_string_false);
      }
    }

    return f_none;
  }
#endif // _di_status_code_process_check_

#ifndef _di_status_code_process_number_
  f_return_status status_code_process_number(const status_code_data data, const f_string value) {
    f_status status = f_none;

    {
      f_number_unsigned number = 0;

      status = fl_console_parameter_to_number_unsigned(value, &number);

      if (status == f_none) {
        fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "invalid name");

        return f_status_set_error(f_invalid_parameter);
      }

      if (status == f_no_data || f_status_set_fine(status) == f_invalid_parameter) {
        fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "invalid data");

        return status;
      }
    }

    f_status code = f_none;

    status = fll_status_from_string(value, &code);

    if (f_status_is_error(status)) {
      if (f_status_set_fine(status) == f_invalid_data) {
        fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "unknown name");
      }
      else {
        fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "failed to convert");
      }

      return status;
    }

    if (status == f_invalid_data) {
      fl_color_print_line(f_standard_output, data.context.warning, data.context.reset, "unknown code");

      return f_none;
    }

    printf("%u\n", code);

    return f_none;
  }
#endif // _di_status_code_process_number_

#ifndef _di_status_code_process_normal_
  f_return_status status_code_process_normal(const status_code_data data, const f_string value) {
    f_number_unsigned number = 0;
    f_status status = status_code_convert_number(data, value, &number);

    if (f_status_is_error(status)) {
      return status;
    }

    f_status code = (f_status) number;
    f_string string = 0;

    status = fl_status_to_string(code, &string);

    if (f_status_is_error(status)) {
      if (f_status_set_fine(status) == f_invalid_data) {
        fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "unknown code");
      }
      else {
        fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "failed to convert");
      }

      return status;
    }

    printf("%s\n", string);

    return f_none;
  }
#endif // _di_status_code_process_normal_

#ifndef _di_status_code_convert_number_
  f_return_status status_code_convert_number(const status_code_data data, const f_string value, f_number_unsigned *number) {
    f_status status = fl_console_parameter_to_number_unsigned(value, number);

    if (*number > f_status_size_max_with_signal) {
      fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "out of range");

      return status;
    }

    if (f_status_is_error(status)) {
      if (f_status_set_fine(status) == f_negative_number) {
        fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "out of range");
      }
      else {
        fl_color_print_line(f_standard_output, data.context.error, data.context.reset, "invalid number");
      }

      return status;
    }

    return f_none;
  }
#endif // _di_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif
