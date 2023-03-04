#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_print_error_
  f_status_t status_code_print_error(status_code_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    status_code_print_line_first(setting, print);
    fll_error_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e);

    return F_none;
  }
#endif // _di_status_code_print_error_

#ifndef _di_status_code_print_error_cannot_error_warning_number_
  f_status_t status_code_print_error_cannot_error_warning_number(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QCannot specify the '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%r%r%]", print.to, print.notable, f_console_symbol_long_normal_s, status_code_long_error_s, print.notable);
    fl_print_format("%[' parameter with the '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%r%]", print.to, print.notable, f_console_symbol_long_normal_s, status_code_long_warning_s, print.notable);
    fl_print_format("%[' parameter when not also specifying the '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%r%]", print.to, print.notable, f_console_symbol_long_normal_s, status_code_long_number_s, print.notable);
    fl_print_format("%[' parameter.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_status_code_print_error_cannot_error_warning_number_

#ifndef _di_status_code_print_error_no_status_codes_
  f_status_t status_code_print_error_no_status_codes(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[No status code is specified.%]%r", print.to, print.context, print.context, f_string_eol_s);

    return F_none;
  }
#endif // _di_status_code_print_error_no_status_codes_

#ifndef _di_status_code_print_error_invalid_callback_
  f_status_t status_code_print_error_invalid_callback(status_code_setting_t * const setting, const fl_print_t print, const f_string_t name) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QInvalid callback specified for '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%s%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[' internal setting.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_status_code_print_error_invalid_callback_

#ifdef __cplusplus
} // extern "C"
#endif
