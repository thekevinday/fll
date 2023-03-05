#include "../iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_error_
  f_status_t iki_read_print_error(iki_read_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e);

    return F_none;
  }
#endif // _di_iki_read_print_error_

#ifndef _di_iki_read_print_error_file_
  f_status_t iki_read_print_error_file(iki_read_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_none;
  }
#endif // _di_iki_read_print_error_file_

#ifdef __cplusplus
} // extern "C"
#endif
