#include "fss_status_code.h"
#include "private-fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_process_check_
  f_status_t fss_status_code_process_check(const fss_status_code_main_t main, const f_string_t value) {
    f_number_unsigned_t number = 0;

    f_status_t status = fss_status_code_convert_number(main, value, &number);
    if (F_status_is_error(status)) return status;

    if (main.parameters[fss_status_code_parameter_is_error].result == f_console_result_found) {
      if (F_status_is_error(number)) {
        printf("%s\n", FL_status_string_true);
      }
      else {
        printf("%s\n", FL_status_string_false);
      }
    }
    else if (main.parameters[fss_status_code_parameter_is_warning].result == f_console_result_found) {
      if (F_status_is_warning(number)) {
        printf("%s\n", FL_status_string_true);
      }
      else {
        printf("%s\n", FL_status_string_false);
      }
    }
    else if (main.parameters[fss_status_code_parameter_is_fine].result == f_console_result_found) {
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
  f_status_t fss_status_code_process_number(const fss_status_code_main_t main, const f_string_t value) {
    f_status_t status = F_none;

    {
      const f_string_range_t range = macro_f_string_range_t_initialize(strlen(value));

      f_number_unsigned_t number = 0;

      status = fl_conversion_string_to_number_unsigned(value, range, &number);

      if (status == F_none) {
        f_color_print(main.output.stream, main.context.set.error, "invalid name%c", f_string_eol_s[0]);

        return F_status_set_error(F_parameter);
      }

      if (status == F_data_not || F_status_set_fine(status) == F_parameter) {
        f_color_print(main.output.stream, main.context.set.error, "invalid main%c", f_string_eol_s[0]);

        return status;
      }
    }

    f_status_t code = F_none;

    status = fll_fss_status_from_string(value, &code);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        status = fll_status_from_string(value, &code);
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_data) {
          f_color_print(main.output.stream, main.context.set.error, "unknown name%c", f_string_eol_s[0]);
        }
        else {
          f_color_print(main.output.stream, main.context.set.error, "failed to convert%c", f_string_eol_s[0]);
        }

        return status;
      }
    }

    if (status == F_data) {
      f_color_print(main.output.stream, main.context.set.warning, "unknown code%c", f_string_eol_s[0]);

      return F_none;
    }

    printf("%u\n", code);

    return F_none;
  }
#endif // _di_fss_status_code_process_number_

#ifndef _di_fss_status_code_process_normal_
  f_status_t fss_status_code_process_normal(const fss_status_code_main_t main, const f_string_t value) {
    f_number_unsigned_t number = 0;

    f_status_t status = fss_status_code_convert_number(main, value, &number);
    if (F_status_is_error(status)) return status;

    const f_status_t code = (f_status_t) number;
    f_string_t string = 0;

    status = fll_fss_status_to_string(code, &string);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        f_color_print(main.output.stream, main.context.set.error, "unknown code%c", f_string_eol_s[0]);
      }
      else {
        f_color_print(main.output.stream, main.context.set.error, "failed to convert%c", f_string_eol_s[0]);
      }

      return status;
    }

    printf("%s\n", string);

    return F_none;
  }
#endif // _di_fss_status_code_process_normal_

#ifndef _di_fss_status_code_convert_number_
  f_status_t fss_status_code_convert_number(const fss_status_code_main_t main, const f_string_t value, f_number_unsigned_t *number) {
    const f_string_range_t range = macro_f_string_range_t_initialize(strlen(value));

    f_status_t status = fl_conversion_string_to_number_unsigned(value, range, number);

    if (*number > F_status_size_max_with_signal) {
      f_color_print(main.output.stream, main.context.set.error, "out of range%c", f_string_eol_s[0]);

      return status;
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number_negative) {
        f_color_print(main.output.stream, main.context.set.error, "out of range%c", f_string_eol_s[0]);
      }
      else {
        f_color_print(main.output.stream, main.context.set.error, "invalid number%c", f_string_eol_s[0]);
      }

      return status;
    }

    return F_none;
  }
#endif // _di_fss_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif
