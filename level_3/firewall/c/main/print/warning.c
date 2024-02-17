#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_warning_chain_meaningless_line_
  f_status_t firewall_print_warning_chain_meaningless_line(fl_print_t * const print, const f_number_unsigned_t line) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    firewall_main_t * const main = (firewall_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QAt line%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, line, print->notable);

    if (main->data.file.used && main->data.file.string) {
      fl_print_format(" %[of '%]", print->to, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->data.file, print->notable);
      fl_print_format("%[' ", print->to, print->context);
    }
    else {
      fl_print_format(" %[", print->to, print->context);
    }

    fl_print_format("the chain option is meaningless inside of a custom chain%]%r", print->to, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);
    f_file_stream_flush(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_warning_chain_meaningless_line_

#ifndef _di_firewall_print_warning_content_invalid_missing_line_
  f_status_t firewall_print_warning_content_invalid_missing_line(fl_print_t * const print, const f_number_unsigned_t line, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    firewall_main_t * const main = (firewall_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QAt line%] ", print->to, print->context, print->prefix, print->context);

    if (main->data.file.used && main->data.file.string) {
      fl_print_format(" %[of '%]", print->to, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->data.file, print->notable);
      fl_print_format("%[' ", print->to, print->context);
    }
    else {
      fl_print_format(" %[", print->to, print->context);
    }

    fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, line, print->notable);
    fl_print_format(" %[the object '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);

    if (range.start > range.stop) {
      fl_print_format("%[' has no content.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }
    else {
      fl_print_format("%[' is invalid.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }

    f_file_stream_unlock(print->to);
    f_file_stream_flush(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_warning_content_invalid_missing_line_

#ifndef _di_firewall_print_warning_object_invalid_missing_line_
  f_status_t firewall_print_warning_object_invalid_missing_line(fl_print_t * const print, const f_number_unsigned_t line, const f_string_static_t buffer, const f_range_t range) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    firewall_main_t * const main = (firewall_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QAt line%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_un_single_s.string, print->to, print->notable, line, print->notable);

    if (main->data.file.used && main->data.file.string) {
      fl_print_format(" %[of '%]", print->to, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, main->data.file, print->notable);
      fl_print_format("%[' ", print->to, print->context);
    }
    else {
      fl_print_format(" %[", print->to, print->context);
    }

    if (range.start > range.stop) {
      fl_print_format(" %[the object is missing.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }
    else {
      fl_print_format(" %[the object '%]", print->to, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_range_single_s.string, print->to, print->notable, buffer, range, print->notable);
      fl_print_format("%[' is invalid.%]%r", print->to, print->context, print->context, f_string_eol_s);
    }

    f_file_stream_unlock(print->to);
    f_file_stream_flush(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_warning_object_invalid_missing_line_

#ifndef _di_firewall_print_warning_show_option_unknown_
  f_status_t firewall_print_warning_show_option_unknown(fl_print_t * const print, const f_string_static_t option) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format(firewall_operation_show_s.string, print->to, print->notable, option, print->notable);
    fl_print_format(" %[option '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, option, print->notable);
    fl_print_format("%[' is not known.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);
    f_file_stream_flush(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_warning_show_option_unknown_

#ifdef __cplusplus
} // extern "C"
#endif
