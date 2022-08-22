#include "fss_status_code.h"
#include "private-common.h"
#include "private-fss_status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_process_check_
  f_status_t fss_status_code_process_check(fll_program_data_t * const main, fss_status_code_setting_t * const setting, const f_string_static_t value) {

    f_number_unsigned_t number = 0;

    {
      f_status_t status = fss_status_code_convert_number(main, setting, value, &number);
      if (F_status_is_error(status)) return status;
    }

    if ((setting->flag & fss_status_code_main_flag_error_e) && F_status_is_error(number) || (setting->flag & fss_status_code_main_flag_warning_e) && F_status_is_warning(number) || (setting->flag & fss_status_code_main_flag_fine_e) && F_status_is_fine(number)) {
      f_print_dynamic_raw(f_status_true_s, main->output.to.stream);
    }
    else {
      f_print_dynamic_raw(f_status_false_s, main->output.to.stream);
    }

    f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);

    return F_none;
  }
#endif // _di_fss_status_code_process_check_

#ifndef _di_fss_status_code_process_number_
  f_status_t fss_status_code_process_number(fll_program_data_t * const main, fss_status_code_setting_t * const setting, const f_string_static_t value) {

    f_status_t status = F_none;

    {
      f_number_unsigned_t number = 0;

      status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, value, &number);

      if (status == F_none) {
        fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_invalid_name_s, main->context.set.error, f_string_eol_s);

        return F_status_set_error(F_parameter);
      }

      if (status == F_data_not || F_status_set_fine(status) == F_parameter) {
        fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_invalid_main_s, main->context.set.error, f_string_eol_s);

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
          fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_unknown_name_s, main->context.set.error, f_string_eol_s);
        }
        else {
          fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_failed_to_convert_s, main->context.set.error, f_string_eol_s);
        }

        return status;
      }
    }

    if (status == F_data) {
      fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_unknown_code_s, main->context.set.error, f_string_eol_s);

      return F_none;
    }

    if (setting->flag & fss_status_code_main_flag_error_e) {
      code = F_status_set_error(code);
    }

    if (setting->flag & fss_status_code_main_flag_warning_e) {
      code = F_status_set_warning(code);
    }

    fl_print_format("%ui%r", main->output.to.stream, code, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_status_code_process_number_

#ifndef _di_fss_status_code_process_normal_
  f_status_t fss_status_code_process_normal(fll_program_data_t * const main, fss_status_code_setting_t * const setting, const f_string_static_t value) {

    f_number_unsigned_t number = 0;

    f_status_t status = fss_status_code_convert_number(main, setting, value, &number);
    if (F_status_is_error(status)) return status;

    f_string_static_t name = f_string_static_t_initialize;

    status = fll_fss_status_string_to((f_status_t) number, &name);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_data) {
        fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_unknown_code_s, main->context.set.error, f_string_eol_s);
      }
      else {
        fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_failed_to_convert_s, main->context.set.error, f_string_eol_s);
      }

      return status;
    }

    fl_print_format("%Q%r", main->output.to.stream, name, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_status_code_process_normal_

#ifndef _di_fss_status_code_convert_number_
  f_status_t fss_status_code_convert_number(fll_program_data_t * const main, fss_status_code_setting_t * const setting, const f_string_static_t value, f_number_unsigned_t *number) {

    const f_status_t status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, value, number);

    if (*number > F_status_size_max_with_bits_d) {
      fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_out_of_range_s, main->context.set.error, f_string_eol_s);

      return F_status_set_error(F_number_overflow);
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number_negative) {
        fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_out_of_range_s, main->context.set.error, f_string_eol_s);
      }
      else {
        fl_print_format("%[%r%]%r", main->output.to.stream, main->context.set.error, fss_status_code_invalid_number_s, main->context.set.error, f_string_eol_s);
      }

      return status;
    }

    return F_none;
  }
#endif // _di_fss_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif
