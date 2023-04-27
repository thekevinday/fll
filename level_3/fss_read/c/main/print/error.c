#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_print_error_
  f_status_t fss_read_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((fss_read_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_none;
  }
#endif // _di_fss_read_print_error_

#ifndef _di_fss_read_print_error_file_
  f_status_t fss_read_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(((fss_read_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_none;
  }
#endif // _di_fss_read_print_error_file_

#ifndef _di_fss_read_print_error_parameter_same_times_at_least_
  f_status_t fss_read_print_error_parameter_same_times_at_least(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QMust specify the '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%r%r%]", print->to, print->notable, f_console_symbol_long_normal_s, fss_read_long_content_s, print->notable);
    fl_print_format("%[' parameter at least the same number of times as the '%]", print->to, print->context, print->context);
    fl_print_format("%[%r%r%]", print->to, print->notable, f_console_symbol_long_normal_s, fss_read_long_object_s, print->notable);
    fl_print_format("%[' parameter when not specifying the '%]", print->to, print->context, print->context);
    fl_print_format("%[%r%r%]", print->to, print->notable, f_console_symbol_long_normal_s, fss_read_long_partial_s, print->notable);
    fl_print_format("%[' parameter.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_print_error_parameter_same_times_at_least_

#ifndef _di_fss_read_print_error_one_content_only_
  f_status_t fss_read_print_error_one_content_only(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%r%]", print->to, print->notable, ((fss_read_main_t *) print->custom)->setting.standard, print->notable);
    fl_print_format(" %[standard only supports one Content per Object.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_print_error_one_content_only_

#ifndef _fss_read_print_error_prepend_only_whitespace_
  f_status_t fss_read_print_error_prepend_only_whitespace(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe value for the parameter '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%r%r%]", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_read_long_prepend_s, print->set->notable);
    fl_print_format("%[' must only contain white space.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _fss_read_print_error_prepend_only_whitespace_

#ifndef _di_fss_read_print_error_unsupported_eol_
  f_status_t fss_read_print_error_unsupported_eol(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%r%]", print->to, print->notable, ((fss_read_main_t *) print->custom)->setting.standard, print->notable);
    fl_print_format(" %[standard does not support end of line character '%]", print->to, print->context, print->context);
    fl_print_format("%[\\n%]", print->to, print->set->notable, print->set->notable);
    fl_print_format("%[' (%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[U+000A%]", print->to, print->set->notable, print->set->notable);
    fl_print_format("%[) in Objects.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_print_error_unsupported_eol_

#ifdef __cplusplus
} // extern "C"
#endif
