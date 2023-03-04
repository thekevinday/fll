#include "iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_print_help_
  f_status_t iki_write_print_help(iki_write_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, iki_write_program_name_long_s, iki_write_program_version_s);

    fll_program_print_help_option(print, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Print this help message.");
    fll_program_print_help_option(print, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(print, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(print, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, "Do not print using color.");
    fll_program_print_help_option(print, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(print, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, "   Decrease verbosity, using only error output.");
    fll_program_print_help_option(print, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, "  Set verbosity to normal.");
    fll_program_print_help_option(print, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(print, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(print, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_inverse_s, f_console_symbol_long_inverse_s, " Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, iki_write_short_backtick_s, iki_write_long_backtick_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Use backtick for quotes.");
    fll_program_print_help_option(print, iki_write_short_content_s, iki_write_long_content_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " The Content to write.");
    fll_program_print_help_option(print, iki_write_short_double_s, iki_write_long_double_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Use double quotes (default).");
    fll_program_print_help_option(print, iki_write_short_file_s, iki_write_long_file_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Specify a file to send data to.");
    fll_program_print_help_option(print, iki_write_short_object_s, iki_write_long_object_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  The Object to write.");
    fll_program_print_help_option(print, iki_write_short_single_s, iki_write_long_single_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Use single quotes.");

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, iki_write_program_name_s, f_string_empty_s);

    fl_print_format("%r %[Notes:%]%r", print.to, f_string_eol_s, print.set->important, print.set->important, f_string_eol_s);
    fl_print_format("  This program will accept Object and Content strings to generate an IKI string, such as %[object:\"content\"%].%r", print.to, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  Each Object must have a Content (and each Content must have an Object).%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The Object is also called the Vocabulary.%r", print.to, f_string_eol_s);
    fl_print_format("  A complete Object and Content set is also called a Variable.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When piping main to this program, a single form-feed character (\\f) (U+000C) must be used to separate each Object from each Content.%r", print.to, f_string_eol_s);
    fl_print_format("  Furthermore, each Object must be followed by a Content.%r", print.to, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_iki_write_print_help_

#ifndef _di_iki_write_print_line_first_
  f_status_t iki_write_print_line_first(iki_write_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->state.status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    if (setting->flag & iki_write_main_flag_print_first_e) {
      fll_print_dynamic_raw(setting->line_first, print.to);

      setting->flag -= iki_write_main_flag_print_first_e;
    }

    return F_none;
  }
#endif // _di_iki_write_print_line_first_

#ifndef _di_iki_write_print_line_last_
  f_status_t iki_write_print_line_last(iki_write_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->state.status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_iki_write_print_line_last_

#ifdef __cplusplus
} // extern "C"
#endif
