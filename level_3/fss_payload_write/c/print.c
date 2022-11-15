#include "fss_payload_write.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_write_print_error_
  f_status_t fss_payload_write_print_error(fss_payload_write_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fss_payload_write_print_line_first_locked(setting, print);
    fll_error_print(print, F_status_set_fine(setting->status), function, F_true);
    fss_payload_write_print_line_last_locked(setting, print);

    return F_none;
  }
#endif // _di_fss_payload_write_print_error_

#ifndef _di_fss_payload_write_print_error_file_
  f_status_t fss_payload_write_print_error_file(fss_payload_write_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fss_payload_write_print_line_first_locked(setting, print);
    fll_error_file_print(print, F_status_set_fine(setting->status), function, F_true, name, operation, type);
    fss_payload_write_print_line_last_locked(setting, print);

    return F_none;
  }
#endif // _di_fss_payload_write_print_error_file_

#ifndef _di_fss_payload_write_print_error_object_not_before_content_
  f_status_t fss_payload_write_print_error_object_not_before_content(fss_payload_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%r%[%QEach '%]", print.to, f_string_eol_s, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%r%r%]", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_object_s, print.set->notable);
    fl_print_format("%[' parameter must be specified before a '%]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%r%r%]", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_content_s, print.set->notable);
    fl_print_format("%[' parameter.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_payload_write_print_error_object_not_before_content_

#ifndef _fss_payload_write_print_error_prepend_only_whitespace_
  f_status_t fss_payload_write_print_error_prepend_only_whitespace(fss_payload_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%r%[%QThe value for the parameter '%]", print.to, f_string_eol_s, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%r%r%]", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_prepend_s, print.set->notable);
    fl_print_format("%[' must only contain white space.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _fss_payload_write_print_error_prepend_only_whitespace_

#ifndef _di_fss_payload_write_print_help_
  f_status_t fss_payload_write_print_help(fss_payload_write_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, fss_payload_write_program_name_long_s, fss_payload_write_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, fss_payload_write_short_file_s, fss_payload_write_long_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send data to.");
    fll_program_print_help_option(print, fss_payload_write_short_content_s, fss_payload_write_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The Content to write.");
    fll_program_print_help_option(print, fss_payload_write_short_double_s, fss_payload_write_long_double_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(print, fss_payload_write_short_ignore_s, fss_payload_write_long_ignore_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Ignore a given range within a Content.");
    fll_program_print_help_option(print, fss_payload_write_short_object_s, fss_payload_write_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The Object to write.");
    fll_program_print_help_option(print, fss_payload_write_short_partial_s, fss_payload_write_long_partial_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Do not write end of Object/Content character.");
    fll_program_print_help_option(print, fss_payload_write_short_prepend_s, fss_payload_write_long_prepend_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Prepend the given white space characters to the start of each multi-line Content.");
    fll_program_print_help_option(print, fss_payload_write_short_single_s, fss_payload_write_long_single_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");
    fll_program_print_help_option(print, fss_payload_write_short_trim_s, fss_payload_write_long_trim_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Trim Object names.");

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, fss_payload_write_program_name_s, f_string_empty_s);

    fl_print_format("%r  The pipe uses the Backspace character '%[\\b%]' (%[U+0008%]) to designate the start of a Content.%r", print.to, f_string_eol_s, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Form Feed character '%[\\f%]' (%[U+000C%]) to designate the end of the last Content.%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Vertical Line character '%[\\v%]' (%[U+000B%]) is used to ignore a Content range, which does nothing in this program.%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  For the pipe, an Object is terminated by either a Backspace character '%[\\b%]' (%[U+0008%])", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable);
    fl_print_format(" or a Form Feed character '%[\\f%]' (%[U+000C%]).%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The end of the pipe represents the end of any Object or Content.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The FSS-000E (Payload) specification does not support quoted names, therefore the parameters '%[%r%r%]'", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_single_s, print.set->notable);
    fl_print_format(" and '%[%r%r%]' do nothing.%r%r", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_double_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program does not use the parameter '%[%r%r%]', which therefore does nothing.%r", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_ignore_s, print.set->notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%r", print.to, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_payload_write_print_help_

#ifndef _di_fss_payload_write_print_line_first_locked_
  f_status_t fss_payload_write_print_line_first_locked(fss_payload_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_fss_payload_write_print_line_first_locked_

#ifndef _di_fss_payload_write_print_line_first_unlocked_
  f_status_t fss_payload_write_print_line_first_unlocked(fss_payload_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_fss_payload_write_print_line_first_unlocked_

#ifndef _di_fss_payload_write_print_line_last_locked_
  f_status_t fss_payload_write_print_line_last_locked(fss_payload_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (fss_payload_write_main_flag_verify_e | fss_payload_write_main_flag_file_to_e)) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fss_payload_write_print_line_last_locked_

#ifndef _di_fss_payload_write_print_line_last_unlocked_
  f_status_t fss_payload_write_print_line_last_unlocked(fss_payload_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (fss_payload_write_main_flag_verify_e | fss_payload_write_main_flag_file_to_e)) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fss_payload_write_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif
