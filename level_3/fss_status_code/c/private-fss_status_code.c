#include "fss_status_code.h"
#include "private-common.h"
#include "private-fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_process_check_
  f_status_t fss_status_code_process_check(fll_program_data_t * const main, const f_string_static_t value) {

    f_number_unsigned_t number = 0;

    {
      const f_status_t status = fss_status_code_convert_number(main, value, &number);
      if (F_status_is_error(status)) return status;
    }

    if (main->parameters.array[fss_status_code_parameter_is_error_e].result == f_console_result_found_e) {
      if (F_status_is_error(number)) {
        f_print_dynamic_raw(f_status_true_s, main->output.to.stream);
      }
      else {
        f_print_dynamic_raw(f_status_false_s, main->output.to.stream);
      }

      f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
    }
    else if (main->parameters.array[fss_status_code_parameter_is_warning_e].result == f_console_result_found_e) {
      if (F_status_is_warning(number)) {
        f_print_dynamic_raw(f_status_true_s, main->output.to.stream);
      }
      else {
        f_print_dynamic_raw(f_status_false_s, main->output.to.stream);
      }

      f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
    }
    else if (main->parameters.array[fss_status_code_parameter_is_fine_e].result == f_console_result_found_e) {
      if (F_status_is_fine(number)) {
        f_print_dynamic_raw(f_status_true_s, main->output.to.stream);
      }
      else {
        f_print_dynamic_raw(f_status_false_s, main->output.to.stream);
      }

      f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
    }

    return F_none;
  }
#endif // _di_fss_status_code_process_check_

#ifndef _di_fss_status_code_process_number_
  f_status_t fss_status_code_process_number(fll_program_data_t * const main, const f_string_static_t value) {

    f_status_t status = F_none;

    {
      f_number_unsigned_t number = 0;

      status = fl_conversion_dynamic_to_number_unsigned(value, &number);

      if (status == F_none) {
        fl_print_format("%[invalid name%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

        return F_status_set_error(F_parameter);
      }

      if (status == F_data_not || F_status_set_fine(status) == F_parameter) {
        fl_print_format("%[invalid main%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

        return status;
      }
    }

    f_status_t code = F_none;

    status = fll_fss_status_string_from(value, &code);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        status = fll_status_string_from(value, &code);
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_data) {
          fl_print_format("%[unknown name%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
        }
        else {
          fl_print_format("%[failed to convert%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
        }

        return status;
      }
    }

    if (status == F_data) {
      fl_print_format("%[unknown code%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

      return F_none;
    }

    fl_print_format("%ui%r", main->output.to.stream, code, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_status_code_process_number_

#ifndef _di_fss_status_code_process_normal_
  f_status_t fss_status_code_process_normal(fll_program_data_t * const main, const f_string_static_t value) {

    f_number_unsigned_t number = 0;

    f_status_t status = fss_status_code_convert_number(main, value, &number);
    if (F_status_is_error(status)) return status;

    f_string_static_t name = f_string_static_t_initialize;

    status = fll_fss_status_string_to((f_status_t) number, &name);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        fl_print_format("%[unknown code%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }
      else {
        fl_print_format("%[failed to convert%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }

      return status;
    }

    fl_print_format("%Q%r", main->output.to.stream, name, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_status_code_process_normal_

#ifndef _di_fss_status_code_convert_number_
  f_status_t fss_status_code_convert_number(fll_program_data_t * const main, const f_string_static_t value, f_number_unsigned_t *number) {

    f_status_t status = fl_conversion_dynamic_to_number_unsigned(value, number);

    if (*number > F_status_size_max_with_signal) {
      fl_print_format("%[out of range%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);

      return status;
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number_negative) {
        fl_print_format("%[out of range%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }
      else {
        fl_print_format("%[invalid number%]%r", main->output.to.stream, main->context.set.error, main->context.set.error, f_string_eol_s);
      }

      return status;
    }

    return F_none;
  }
#endif // _di_fss_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif
