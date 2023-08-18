#include "../status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_print_data_code_
  f_status_t status_code_print_data_code(fl_print_t * const print, const uint16_t code) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_format("%ui%r", print->to, code, f_string_eol_s);

    return F_okay;
  }
#endif // _di_status_code_print_data_code_

#ifndef _di_status_code_print_data_context_value_
  f_status_t status_code_print_data_context_value(fl_print_t * const print, const f_color_set_t context, const f_string_static_t value) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_format("%[%Q%]%r", print->to, context, value, context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_status_code_print_data_context_value_

#ifdef __cplusplus
} // extern "C"
#endif
