#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_print_error_
  f_status_t fss_read_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((fss_read_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_fss_read_print_error_

#ifndef _di_fss_read_print_error_file_
  f_status_t fss_read_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(((fss_read_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_fss_read_print_error_file_

#ifndef _di_fss_read_print_error_parameter_requires_message_
  f_status_t fss_read_print_error_parameter_requires_message(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t message) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe parameter '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%r%r%]", print->to, print->notable, symbol, name, print->notable);
    fl_print_format("%[' requires %Q.%]%r", print->to, print->context, message, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_print_error_parameter_requires_message_

#ifndef _di_fss_read_print_error_parameter_value_before_value_number_
  f_status_t fss_read_print_error_parameter_value_before_value_number(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_number_unsigned_t value, const f_number_unsigned_t before) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe parameter '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%r%r%]", print->to, print->notable, symbol, name, print->notable);
    fl_print_format("%[' may not have the value '%]", print->to, print->context, print->context);
    fl_print_format("%[%ul%]", print->to, print->notable, value, print->notable);
    fl_print_format("%[' before the value '%]", print->to, print->context, print->context);
    fl_print_format("%[%ul%]", print->to, print->notable, before, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_print_error_parameter_value_before_value_number_

#ifndef _di_fss_read_print_error_parameter_value_once_only_number_
  f_status_t fss_read_print_error_parameter_value_once_only_number(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_number_unsigned_t value) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe value '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%ul%]", print->to, print->notable, value, print->notable);
    fl_print_format("%[' may only be specified once for the parameter '%]", print->to, print->context, print->context);
    fl_print_format("%[%r%r%]", print->to, print->notable, symbol, name, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_print_error_parameter_value_once_only_number_

#ifndef _di_fss_read_print_error_one_content_only_
  f_status_t fss_read_print_error_one_content_only(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%r%]", print->to, print->notable, ((fss_read_main_t *) print->custom)->setting.standard, print->notable);
    fl_print_format(" %[standard only supports one Content per Object.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_print_error_one_content_only_

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

    return F_okay;
  }
#endif // _di_fss_read_print_error_unsupported_eol_

#ifdef __cplusplus
} // extern "C"
#endif
