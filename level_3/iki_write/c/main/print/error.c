#include "../iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_print_error_
  f_status_t iki_write_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((iki_write_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_iki_write_print_error_

#ifndef _di_iki_write_print_error_file_
  f_status_t iki_write_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    iki_write_main_t * const main = (iki_write_main_t *) print->custom;

    fll_error_file_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_iki_write_print_error_file_

#ifndef _di_iki_write_print_error_main_missing_
  f_status_t iki_write_print_error_main_missing(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QNo main provided, either pipe the main data or use the '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format(f_string_format_rr_single_s.string, print->to, print->set->notable, f_console_symbol_long_normal_s, iki_write_long_object_s, print->set->notable);
    fl_print_format("%[' and the '%]", print->to, print->set->error, print->set->error);
    fl_print_format(f_string_format_rr_single_s.string, print->to, print->set->notable, f_console_symbol_long_normal_s, iki_write_long_content_s, print->set->notable);
    fl_print_format("%[' parameters.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_iki_write_print_error_main_missing_

#ifndef _di_iki_write_print_error_object_not_valid_
  f_status_t iki_write_print_error_object_not_valid(fl_print_t * const print, const f_string_static_t object) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe object '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, object, print->set->notable);
    fl_print_format("%[' is not a valid IKI Object.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_iki_write_print_error_object_not_valid_

#ifdef __cplusplus
} // extern "C"
#endif
