#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_convert_number_
  void status_code_convert_number(status_code_main_t * const main, const f_string_static_t value, f_number_unsigned_t *number) {

    if (!main) return;

    main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, value, number);

    if (*number > F_status_size_max_with_bits_d) {
      status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_out_of_range_s);

      main->setting.state.status = F_status_set_error(F_number_overflow);

      return;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_number_negative) {
        status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_out_of_range_s);
      }
      else {
        status_code_print_data_context_value(&main->program.output, main->program.context.set.error, status_code_invalid_number_s);
      }
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_status_code_convert_number_

#ifdef __cplusplus
} // extern "C"
#endif
