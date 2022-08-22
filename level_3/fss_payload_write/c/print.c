#include "fss_payload_write.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_write_print_help_
  f_status_t fss_payload_write_print_help(fss_payload_write_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    fll_program_print_help_header(print, fss_payload_write_program_name_long_s, fss_payload_write_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option(print, fss_payload_write_short_file_s, fss_payload_write_long_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send data to.");
    fll_program_print_help_option(print, fss_payload_write_short_content_s, fss_payload_write_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The Content to write.");
    fll_program_print_help_option(print, fss_payload_write_short_double_s, fss_payload_write_long_double_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(print, fss_payload_write_short_ignore_s, fss_payload_write_long_ignore_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Ignore a given range within a Content.");
    fll_program_print_help_option(print, fss_payload_write_short_object_s, fss_payload_write_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The Object to write.");
    fll_program_print_help_option(print, fss_payload_write_short_partial_s, fss_payload_write_long_partial_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Do not write end of Object/Content character.");
    fll_program_print_help_option(print, fss_payload_write_short_prepend_s, fss_payload_write_long_prepend_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Prepend the given white space characters to the start of each multi-line Content.");
    fll_program_print_help_option(print, fss_payload_write_short_single_s, fss_payload_write_long_single_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");
    fll_program_print_help_option(print, fss_payload_write_short_trim_s, fss_payload_write_long_trim_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Trim Object names.");

    fll_program_print_help_usage(print, fss_payload_write_program_name_s, f_string_empty_s);

    fl_print_format("%r  The pipe uses the Backspace character '%[\\b%]' (%[U+0008%]) to designate the start of a Content.%r", print.to.stream, f_string_eol_s, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Form Feed character '%[\\f%]' (%[U+000C%]) to designate the end of the last Content.%r", print.to.stream, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Vertical Line character '%[\\v%]' (%[U+000B%]) is used to ignore a Content range, which does nothing in this program.%r", print.to.stream, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  For the pipe, an Object is terminated by either a Backspace character '%[\\b%]' (%[U+0008%])", print.to.stream, print.set->notable, print.set->notable, print.set->notable, print.set->notable);
    fl_print_format(" or a Form Feed character '%[\\f%]' (%[U+000C%]).%r", print.to.stream, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The end of the pipe represents the end of any Object or Content.%r%r", print.to.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The FSS-000E (Payload) specification does not support quoted names, therefore the parameters '%[%r%r%]'", print.to.stream, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_single_s, print.set->notable);
    fl_print_format(" and '%[%r%r%]' do nothing.%r%r", print.to.stream, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_double_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program does not use the parameter '%[%r%r%]', which therefore does nothing.%r", print.to.stream, print.set->notable, f_console_symbol_long_enable_s, fss_payload_write_long_ignore_s, print.set->notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%r", print.to.stream, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_payload_write_print_help_

#ifndef _di_fss_payload_write_print_line_first_
  void fss_payload_write_print_line_first(fss_payload_write_setting_t * const setting, const fl_print_t print, const bool lock) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    if (lock) {
      fll_print_dynamic_raw(setting->line_first, print.to.stream);
    }
    else {
      f_print_dynamic_raw(setting->line_first, print.to.stream);
    }
  }
#endif // _di_fss_payload_write_print_line_first_

#ifndef _di_fss_payload_write_print_line_last_
  void fss_payload_write_print_line_last(fss_payload_write_setting_t * const setting, const fl_print_t print, const bool lock) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (print.verbosity == f_console_verbosity_error_e && !F_status_is_error(setting->status)) return;
    if (setting->flag & fss_payload_write_main_flag_verify_e) return;
    if ((setting->flag & fss_payload_write_main_flag_file_to_e) && !F_status_is_error(setting->status)) return;

    if (lock) {
      fll_print_dynamic_raw(setting->line_last, print.to.stream);
    }
    else {
      f_print_dynamic_raw(setting->line_last, print.to.stream);
    }
  }
#endif // _di_fss_payload_write_print_line_last_

#ifdef __cplusplus
} // extern "C"
#endif
