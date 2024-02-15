#include "../firewall.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_firewall_print_error_
  f_status_t firewall_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((firewall_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_firewall_print_error_

#ifndef _di_firewall_print_error_file_
  f_status_t firewall_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    firewall_main_t * const main = (firewall_main_t *) print->custom;

    fll_error_file_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_firewall_print_error_file_

#ifndef _di_firewall_print_error_file_empty_
  f_status_t firewall_print_error_file_empty(fl_print_t * const print, const f_string_static_t section, const f_string_static_t file) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QNo relevant data is found within the file '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, operation, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_error_file_empty_

#ifndef _di_firewall_print_error_network_device_none_
  f_status_t firewall_print_error_network_device_none(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QCould not find any network devices.%]%r", print->to, print->context, print->prefix, print->context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_firewall_print_error_network_device_none_

#ifndef _di_firewall_print_error_operation_
  f_status_t firewall_print_error_operation(fl_print_t * const print, const f_string_static_t tool, const f_string_statics_t arguments) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    firewall_main_t * const main = (firewall_main_t *) print->custom);

    if (output.verbosity == f_console_verbosity_quiet_e) return;

    f_file_stream_lock(print->to);

    if (F_status_set_fine(main->setting.state.status) == F_memory_not) {
      fl_print_format("%[%QOut of memory while performing requested %r operation:%]", print->to, print->context, output.prefix, tool, print->context);
    }
    else {
      fl_print_format("%[%QFailed to perform requested %r operation:%]", print->to, print->context, output.prefix, tool, print->context);
    }

    fl_print_format("%r  %[%Q", print->to, f_string_eol_s, print->context, tool);

    for (f_number_unsigned_t i = 0; i < arguments.used; ++i) {
      fl_print_format(" %Q", print->to, arguments.array[i]);
    } // for

    fl_print_format("%[', error code%] ", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format(f_string_format_ui_single_s.string, print->to, print->set->notable, F_status_set_fine(main->setting.state.status), print->set->notable);
    fl_print_format(f_string_format_sentence_end_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_error_operation_

#ifndef _di_firewall_print_error_operation_files_missing_
  f_status_t firewall_print_error_operation_files_missing(fl_print_t * const print, const f_string_static_t operation, const f_string_static_t file) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    firewall_main_t * const main = (firewall_main_t *) print->custom);

    f_file_stream_lock(print->to);

    fl_print_format("%[%QFailed to perform%] ", print->to, print->context, output.prefix);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, operation, print->notable);
    fl_print_format(" %[request because the%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, operation, print->notable);
    fl_print_format(" %[instructions are missing from '%]", print->to, print->set->error, print->set->error);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, file, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_error_operation_files_missing_

#ifndef _di_firewall_print_error_operation_specified_not_
  f_status_t firewall_print_error_operation_specified_not(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QNo operation is given.%]%r", print->to, print->context, print->prefix, print->context, f_string_eol_s);

    return F_okay;
  }
#endif // _di_firewall_print_error_operation_specified_not_

#ifndef _di_firewall_print_error_directory_read_
  f_status_t firewall_print_error_directory_read(fl_print_t * const print, const f_string_static_t ) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QFailed to read the device directory '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(firewall_operation_show_s.string, print->to, print->notable, option, print->notable);
    fl_print_format(" %[option '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, option, print->notable);
    fl_print_format("%[' is not known.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);
    f_file_stream_flush(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_error_directory_read_

#ifndef _di_firewall_print_error_unhandled_
  void firewall_print_error_unhandled(const fl_print_t print, const f_string_t function, const f_string_static_t file) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    firewall_main_t * const main = (firewall_main_t *) print->custom);

    fl_print_format("%[%QAn unhandled error (%]", print->to, f_string_eol_s, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_ui_single_s.string, print->to, print->notable, F_status_set_fine(main->setting.state.status), print->notable);
    fl_print_format("%[) has occurred while calling%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, operation, print->notable);

    if (file.used) {
      fl_print_format("%[() for the file%] ", print->to, print->context, print->prefix, print->context);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, file, print->notable);
      fl_print_format(f_string_format_sentence_end_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);
    }
    else {
      fl_print_format("%[().%]%r", print->to, print->context, print->context, f_string_eol_s);
    }

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_firewall_print_error_unhandled_

#ifdef __cplusplus
} // extern "C"
#endif
