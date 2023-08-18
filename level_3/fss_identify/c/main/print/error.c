#include "../fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_print_error_
  f_status_t fss_identify_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((fss_identify_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_fss_identify_print_error_

#ifndef _di_fss_identify_print_error_file_
  f_status_t fss_identify_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fss_identify_main_t * const main = (fss_identify_main_t *) print->custom;

    fll_error_file_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_fss_identify_print_error_file_

#ifndef _di_fss_identify_print_error_no_from_
  f_status_t fss_identify_print_error_no_from(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QNo sources are specified, please pipe data or designate a file.%]%r", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_okay;
  }
#endif // _di_fss_identify_print_error_no_from_

#ifndef _di_fss_identify_print_error_parameter_file_name_empty_
  f_status_t fss_identify_print_error_parameter_file_name_empty(fl_print_t * const print, const f_number_unsigned_t index) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QEmpt string is not allowed at index%] ", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%ul%] ", print->to, print->set->notable, index, print->set->notable);
    fl_print_format("%[for the parameter '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%r%r%]", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_identify_long_name_s, print->set->notable);
    fl_print_format("%['.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_identify_print_error_parameter_file_name_empty_

#ifndef _di_fss_identify_print_error_parameter_file_name_invalid_
  f_status_t fss_identify_print_error_parameter_file_name_invalid(fl_print_t * const print, const f_number_unsigned_t index, const f_string_static_t name) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe value '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, name, print->set->notable);
    fl_print_format("%[' at index%] ", print->to, print->set->error, print->set->error);
    fl_print_format("%[%ul%] ", print->to, print->set->notable, index, print->set->notable);
    fl_print_format("%[for the parameter '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%r%r%]", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_identify_long_name_s, print->set->notable);
    fl_print_format("%[' may only contain word characters or the dash (minus) character.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_identify_print_error_parameter_file_name_invalid_

#ifdef __cplusplus
} // extern "C"
#endif
