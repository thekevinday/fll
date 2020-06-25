#include <level_3/fss_status_code.h>
#include "private-fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_process_check_
  f_return_status fss_status_code_process_check(const fss_status_code_data data, const f_string value) {
    f_number_unsigned number = 0;
    f_status status = fss_status_code_convert_number(data, value, &number);

    if (F_status_is_error(status)) {
      return status;
    }

    if (data.parameters[fss_status_code_parameter_is_error].result == f_console_result_found) {
      if (F_status_is_error(number)) {
        printf("%s\n", FL_status_string_true);
      }
      else {
        printf("%s\n", FL_status_string_false);
      }
    }
    else if (data.parameters[fss_status_code_parameter_is_warning].result == f_console_result_found) {
      if (F_status_is_warning(number)) {
        printf("%s\n", FL_status_string_true);
      }
      else {
        printf("%s\n", FL_status_string_false);
      }
    }
    else if (data.parameters[fss_status_code_parameter_is_fine].result == f_console_result_found) {
      if (F_status_is_fine(number)) {
        printf("%s\n", FL_status_string_true);
      }
      else {
        printf("%s\n", FL_status_string_false);
      }
    }

    return F_none;
  }
#endif // _di_fss_status_code_process_check_

#ifndef _di_fss_status_code_process_number_
  f_return_status fss_status_code_process_number(const fss_status_code_data data, const f_string value) {
    f_status status = F_none;

    {
      const f_string_range range = f_macro_string_range_initialize(strlen(value));

      f_number_unsigned number = 0;

      status = fl_conversion_string_to_number_unsigned(value, &number, range);

      if (status == F_none) {
        fl_color_print_line(f_type_output, data.context.error, data.context.reset, "invalid name");

        return F_status_set_error(F_parameter);
      }

      if (status == F_data_not || F_status_set_fine(status) == F_parameter) {
        fl_color_print_line(f_type_output, data.context.error, data.context.reset, "invalid data");

        return status;
      }
    }

    f_status code = F_none;

    status = fll_fss_status_from_string(value, &code);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        status = fll_status_from_string(value, &code);
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_data) {
          fl_color_print_line(f_type_output, data.context.error, data.context.reset, "unknown name");
        }
        else {
          fl_color_print_line(f_type_output, data.context.error, data.context.reset, "failed to convert");
        }

        return status;
      }
    }

    if (status == F_data) {
      fl_color_print_line(f_type_output, data.context.warning, data.context.reset, "unknown code");

      return F_none;
    }

    printf("%u\n", code);

    return F_none;
  }
#endif // _di_fss_status_code_process_number_

#ifndef _di_fss_status_code_process_normal_
  f_return_status fss_status_code_process_normal(const fss_status_code_data data, const f_string value) {
    f_number_unsigned number = 0;
    f_status status = fss_status_code_convert_number(data, value, &number);

    if (F_status_is_error(status)) {
      return status;
    }

    const f_status code = (f_status) number;
    f_string string = 0;

    status = fll_fss_status_to_string(code, &string);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        fl_color_print_line(f_type_output, data.context.error, data.context.reset, "unknown code");
      }
      else {
        fl_color_print_line(f_type_output, data.context.error, data.context.reset, "failed to convert");
      }

      return status;
    }

    printf("%s\n", string);

    return F_none;
  }
#endif // _di_fss_status_code_process_normal_

#ifndef _di_fss_status_code_convert_number_
  f_return_status fss_status_code_convert_number(const fss_status_code_data data, const f_string value, f_number_unsigned *number) {
    const f_string_range range = f_macro_string_range_initialize(strlen(value));

    f_status status = fl_conversion_string_to_number_unsigned(value, number, range);

    if (*number > F_status_size_max_with_signal) {
      fl_color_print_line(f_type_output, data.context.error, data.context.reset, "out of range");

      return status;
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number_negative) {
        fl_color_print_line(f_type_output, data.context.error, data.context.reset, "out of range");
      }
      else {
        fl_color_print_line(f_type_output, data.context.error, data.context.reset, "invalid number");
      }

      return status;
    }

    return F_none;
  }
#endif // _di_fss_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif
