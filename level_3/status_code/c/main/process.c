#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_process_check_
  void status_code_process_check(status_code_main_t * const main, const f_string_static_t value) {

    if (!main) return;

    f_number_unsigned_t number = 0;

    {
      status_code_convert_number(main, value, &number);
      if (F_status_is_error(main->setting.state.status)) return;
    }

    f_file_stream_lock(main->program.output.to);

    if ((main->setting.flag & status_code_main_flag_error_e) && F_status_is_error(number) || (main->setting.flag & status_code_main_flag_warning_e) && F_status_is_warning(number) || (main->setting.flag & status_code_main_flag_fine_e) && F_status_is_fine(number)) {
      f_print_dynamic_raw(f_status_true_s, main->program.output.to);
    }
    else {
      f_print_dynamic_raw(f_status_false_s, main->program.output.to);
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    f_file_stream_unlock(main->program.output.to);

    main->setting.state.status = F_okay;
  }
#endif // _di_status_code_process_check_

#ifndef _di_status_code_process_number_
  void status_code_process_number(status_code_main_t * const main, const f_string_static_t value) {

    if (!main) return;

    {
      f_number_unsigned_t number = 0;

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, value, &number);

      if (main->setting.state.status == F_okay) {
        status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_invalid_name_s);

        main->setting.state.status = F_status_set_error(F_parameter);

        return;
      }

      if (main->setting.state.status == F_data_not || F_status_set_fine(main->setting.state.status) == F_parameter) {
        status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_invalid_main_s);

        return;
      }
    }

    f_status_t code = F_okay;

    main->setting.state.status = main->setting.status_string_from(value, &code);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_data) {
        status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_unknown_name_s);
      }
      else {
        status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_failed_to_convert_s);
      }

      return;
    }

    if (main->setting.state.status == F_data) {
      status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_unknown_code_s);

      main->setting.state.status = F_okay;

      return;
    }

    if (main->setting.flag & status_code_main_flag_error_e) {
      code = F_status_set_error(code);
    }

    if (main->setting.flag & status_code_main_flag_warning_e) {
      code = F_status_set_warning(code);
    }

    status_code_print_data_code(&main->program.output, code);

    main->setting.state.status = F_okay;
  }
#endif // _di_status_code_process_number_

#ifndef _di_status_code_process_normal_
  void status_code_process_normal(status_code_main_t * const main, const f_string_static_t value) {

    if (!main) return;

    f_string_static_t name = f_string_static_t_initialize;

    {
      f_number_unsigned_t number = 0;

      status_code_convert_number(main, value, &number);
      if (F_status_is_error(main->setting.state.status)) return;

      main->setting.state.status = main->setting.status_string_to((f_status_t) number, &name);
    }

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_data) {
        status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_unknown_code_s);
      }
      else {
        status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_failed_to_convert_s);
      }

      return;
    }

    status_code_print_data_context_value(&main->program.output, f_color_set_empty_s, name);

    main->setting.state.status = F_okay;
  }
#endif // _di_status_code_process_normal_

#ifdef __cplusplus
} // extern "C"
#endif
