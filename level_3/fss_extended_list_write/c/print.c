#include "fss_embedded_list_write.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_write_print_help_
  f_status_t fss_extended_list_write_print_help(fss_extended_list_write_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, fss_extended_list_write_program_name_long_s, fss_extended_list_write_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, fss_extended_list_write_short_file_s, fss_extended_list_write_long_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send data to.");
    fll_program_print_help_option(print, fss_extended_list_write_short_content_s, fss_extended_list_write_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The Content to write.");
    fll_program_print_help_option(print, fss_extended_list_write_short_double_s, fss_extended_list_write_long_double_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(print, fss_extended_list_write_short_ignore_s, fss_extended_list_write_long_ignore_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Ignore a given range within a Content.");
    fll_program_print_help_option(print, fss_extended_list_write_short_object_s, fss_extended_list_write_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The Object to write.");
    fll_program_print_help_option(print, fss_extended_list_write_short_partial_s, fss_extended_list_write_long_partial_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Do not write end of Object/Content character.");
    fll_program_print_help_option(print, fss_extended_list_write_short_prepend_s, fss_extended_list_write_long_prepend_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Prepend the given white space characters to the start of each multi-line Content.");
    fll_program_print_help_option(print, fss_extended_list_write_short_single_s, fss_extended_list_write_long_single_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");
    fll_program_print_help_option(print, fss_extended_list_write_short_trim_s, fss_extended_list_write_long_trim_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Trim Object names.");

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, fss_extended_list_write_program_name_s, f_string_empty_s);

    fl_print_format("%r  The pipe uses the Backspace character '%[\\b%]' (%[U+0008%]) to designate the start of a Content.%r", print.to, f_string_eol_s, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Form Feed character '%[\\f%]' (%[U+000C%]) to designate the end of the last Content.%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Vertical Line character '%[\\v%]' (%[U+000B%]) is used to ignore a Content range (use this both before and after the range).%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  For the pipe, an Object is terminated by either a Backspace character '%[\\b%]' (%[U+0008%])", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable);
    fl_print_format(" or a Form Feed character '%[\\f%]' (%[U+000C%]).%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  The end of the pipe represents the end of any Object or Content.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The FSS-0003 (Extended List) specification does not support quoted names, therefore the parameters '%[%r%r%]'", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_extended_list_write_long_single_s, print.set->notable);
    fl_print_format(" and '%[%r%r%]' do nothing.%r%r", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_extended_list_write_long_double_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter '%[%r%r%]' designates to not escape any valid nested Object or Content within some Content.%r", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_extended_list_write_long_ignore_s, print.set->notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%r", print.to, f_string_eol_s);
    fl_print_format("  This parameter is not used for ignoring anything from the input pipe.%r", print.to, f_string_eol_s);
    fl_print_format("  This parameter must be specified after a '%[%r%r%]'", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_extended_list_write_long_content_s, print.set->notable);
    fl_print_format(" parameter and this applies only to the Content represented by that specific '%[%r%r%]' parameter.%r", print.to, print.set->notable, f_console_symbol_long_enable_s, fss_extended_list_write_long_content_s, print.set->notable, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_extended_list_write_print_help_

#ifndef _di_fss_extended_list_write_print_line_first_locked_
  f_status_t fss_extended_list_write_print_line_first_locked(fss_extended_list_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_fss_extended_list_write_print_line_first_locked_

#ifndef _di_fss_extended_list_write_print_line_first_unlocked_
  f_status_t fss_extended_list_write_print_line_first_unlocked(fss_extended_list_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_fss_extended_list_write_print_line_first_unlocked_

#ifndef _di_fss_extended_list_write_print_line_last_locked_
  f_status_t fss_extended_list_write_print_line_last_locked(fss_extended_list_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (fss_extended_list_write_main_flag_verify_e | fss_extended_list_write_main_flag_file_to_e)) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fss_extended_list_write_print_line_last_locked_

#ifndef _di_fss_extended_list_write_print_line_last_unlocked_
  f_status_t fss_extended_list_write_print_line_last_unlocked(fss_extended_list_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (fss_extended_list_write_main_flag_verify_e | fss_extended_list_write_main_flag_file_to_e)) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fss_extended_list_write_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif
