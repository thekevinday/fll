#include "payload.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_payload_print_help_
  f_status_t fss_write_payload_print_help(fss_write_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, fss_write_program_name_long_s, fss_write_program_version_s);

    fss_write_print_help(setting, print);

    fll_program_print_help_usage(print, fss_write_program_name_s, f_string_empty_s);

    fl_print_format("%r  The pipe uses the Backspace character '%[\\b%]' (%[U+0008%]) to designate the start of a Content.%r", print.to, f_string_eol_s, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Form Feed character '%[\\f%]' (%[U+000C%]) to designate the end of the last Content.%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Vertical Line character '%[\\v%]' (%[U+000B%]) is used to ignore a Content range, which does nothing in this program.%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  For the pipe, an Object is terminated by either a Backspace character '%[\\b%]' (%[U+0008%])", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable);
    fl_print_format(" or a Form Feed character '%[\\f%]' (%[U+000C%]).%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The end of the pipe represents the end of any Object or Content.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The FSS-000E (Payload) specification does not support quoted names, therefore the parameters '%[%r%r%]'", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_write_long_single_s, print.set->notable);
    fl_print_format(" and '%[%r%r%]' do nothing.%r%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_write_long_double_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program does not use the parameter '%[%r%r%]', which therefore does nothing.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_write_long_ignore_s, print.set->notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%r", print.to, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_write_payload_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
