#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_process_check_
  void status_code_process_check(fll_program_data_t * const main, status_code_setting_t * const setting, const f_string_static_t value) {

    if (!main || !setting) return;

    f_number_unsigned_t number = 0;

    {
      status_code_convert_number(main, setting, value, &number);
      if (F_status_is_error(setting->state.status)) return;
    }

    f_file_stream_lock(main->output.to);

    status_code_print_line_first_unlocked(setting, main->output);

    if ((setting->flag & status_code_main_flag_error_e) && F_status_is_error(number) || (setting->flag & status_code_main_flag_warning_e) && F_status_is_warning(number) || (setting->flag & status_code_main_flag_fine_e) && F_status_is_fine(number)) {
      f_print_dynamic_raw(f_status_true_s, main->output.to);
    }
    else {
      f_print_dynamic_raw(f_status_false_s, main->output.to);
    }

    f_print_dynamic_raw(f_string_eol_s, main->output.to);

    f_file_stream_unlock(main->output.to);

    setting->state.status = F_none;
  }
#endif // _di_status_code_process_check_

#ifndef _di_status_code_process_number_
  void status_code_process_number(fll_program_data_t * const main, status_code_setting_t * const setting, const f_string_static_t value) {

    if (!main || !setting) return;

    {
      f_number_unsigned_t number = 0;

      setting->state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, value, &number);

      if (setting->state.status == F_none) {
        status_code_print_line_first_data(setting, main->message);

        status_code_print_context_value(setting, main->output, main->context.set.error, status_code_invalid_name_s);

        setting->state.status = F_status_set_error(F_parameter);

        return;
      }

      if (setting->state.status == F_data_not || F_status_set_fine(setting->state.status) == F_parameter) {
        status_code_print_line_first_data(setting, main->message);

        status_code_print_context_value(setting, main->output, main->context.set.error, status_code_invalid_main_s);

        return;
      }
    }

    f_status_t code = F_none;

    setting->state.status = setting->status_string_from(value, &code);

    if (F_status_is_error(setting->state.status)) {
      status_code_print_line_first_data(setting, main->message);

      if (F_status_set_fine(setting->state.status) == F_data) {
        status_code_print_context_value(setting, main->output, main->context.set.error, status_code_unknown_name_s);
      }
      else {
        status_code_print_context_value(setting, main->output, main->context.set.error, status_code_failed_to_convert_s);
      }

      return;
    }

    if (setting->state.status == F_data) {
      status_code_print_line_first_data(setting, main->message);

      status_code_print_context_value(setting, main->output, main->context.set.error, status_code_unknown_code_s);

      setting->state.status = F_none;

      return;
    }

    if (setting->flag & status_code_main_flag_error_e) {
      code = F_status_set_error(code);
    }

    if (setting->flag & status_code_main_flag_warning_e) {
      code = F_status_set_warning(code);
    }

    status_code_print_line_first_data(setting, main->message);

    status_code_print_code(setting, main->output, code);

    setting->state.status = F_none;
  }
#endif // _di_status_code_process_number_

#ifndef _di_status_code_process_normal_
  void status_code_process_normal(fll_program_data_t * const main, status_code_setting_t * const setting, const f_string_static_t value) {

    if (!main || !setting) return;

    f_string_static_t name = f_string_static_t_initialize;

    {
      f_number_unsigned_t number = 0;

      status_code_convert_number(main, setting, value, &number);
      if (F_status_is_error(setting->state.status)) return;

      setting->state.status = setting->status_string_to((f_status_t) number, &name);
    }

    status_code_print_line_first_data(setting, main->message);

    if (F_status_is_error(setting->state.status)) {
      if (F_status_set_fine(setting->state.status) == F_data) {
        status_code_print_context_value(setting, main->output, main->context.set.error, status_code_unknown_code_s);
      }
      else {
        status_code_print_context_value(setting, main->output, main->context.set.error, status_code_failed_to_convert_s);
      }

      return;
    }

    status_code_print_context_value(setting, main->output, f_color_set_empty_s, name);

    setting->state.status = F_none;
  }
#endif // _di_status_code_process_normal_

#ifdef __cplusplus
} // extern "C"
#endif
