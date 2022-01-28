#include "status_code.h"
#include "private-common.h"
#include "private-status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_process_check_
  f_status_t status_code_process_check(status_code_main_t * const main, const f_string_t value) {

    f_number_unsigned_t number = 0;
    f_status_t status = status_code_convert_number(main, value, &number);

    if (F_status_is_error(status)) {
      return status;
    }

    if (main->parameters[status_code_parameter_is_error_e].result == f_console_result_found_e) {
      if (F_status_is_error(number)) {
        f_print_terminated(f_status_true_s, main->output.to.stream);
      }
      else {
        f_print_terminated(f_status_false_s, main->output.to.stream);
      }

      f_print_dynamic(f_string_eol_s, main->output.to.stream);
    }
    else if (main->parameters[status_code_parameter_is_warning_e].result == f_console_result_found_e) {
      if (F_status_is_warning(number)) {
        f_print_terminated(f_status_true_s, main->output.to.stream);
      }
      else {
        f_print_terminated(f_status_false_s, main->output.to.stream);
      }

      f_print_dynamic(f_string_eol_s, main->output.to.stream);
    }
    else if (main->parameters[status_code_parameter_is_fine_e].result == f_console_result_found_e) {
      if (F_status_is_fine(number)) {
        f_print_terminated(f_status_true_s, main->output.to.stream);
      }
      else {
        f_print_terminated(f_status_false_s, main->output.to.stream);
      }

      f_print_dynamic(f_string_eol_s, main->output.to.stream);
    }

    return F_none;
  }
#endif // _di_status_code_process_check_

#ifndef _di_status_code_process_number_
  f_status_t status_code_process_number(status_code_main_t * const main, const f_string_t value) {

    f_status_t status = F_none;

    {
      const f_string_range_t range = macro_f_string_range_t_initialize(strlen(value));

      f_number_unsigned_t number = 0;

      status = fl_conversion_string_to_number_unsigned(value, range, &number);

      if (status == F_none) {
        fl_print_format("%[invalid name%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

        return F_status_set_error(F_parameter);
      }

      if (status == F_data_not || F_status_set_fine(status) == F_parameter) {
        fl_print_format("%[invalid main%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

        return status;
      }
    }

    f_status_t code = F_none;

    status = fll_status_string_from(value, &code);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        fl_print_format("%[unknown name%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }
      else {
        fl_print_format("%[failed to convert%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }

      return status;
    }

    if (status == F_data) {
      fl_print_format("%[unknown code%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

      return F_none;
    }

    fl_print_format("%ui%q", main->output.to.stream, code, f_string_eol_s);

    return F_none;
  }
#endif // _di_status_code_process_number_

#ifndef _di_status_code_process_normal_
  f_status_t status_code_process_normal(status_code_main_t * const main, const f_string_t value) {

    f_number_unsigned_t number = 0;
    f_status_t status = status_code_convert_number(main, value, &number);

    if (F_status_is_error(status)) {
      return status;
    }

    const f_status_t code = (f_status_t) number;
    f_string_static_t name = 0;

    status = f_status_string_to(code, &name);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        fl_print_format("%[unknown code%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }
      else {
        fl_print_format("%[failed to convert%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }

      return status;
    }

    fl_print_format("%S%q", main->output.to.stream, name, f_string_eol_s);

    return F_none;
  }
#endif // _di_status_code_process_normal_

#ifndef _di_status_code_convert_number_
  f_status_t status_code_convert_number(status_code_main_t * const main, const f_string_t value, f_number_unsigned_t *number) {

    const f_string_range_t range = macro_f_string_range_t_initialize(strlen(value));

    f_status_t status = fl_conversion_string_to_number_unsigned(value, range, number);

    if (*number > F_status_size_max_with_signal) {
      fl_print_format("%[out of range%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

      return status;
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number_negative) {
        fl_print_format("%[out of range%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }
      else {
        fl_print_format("%[invalid number%]%q", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }

      return status;
    }

    return F_none;
  }
#endif // _di_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif
