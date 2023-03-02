#include "iki_write.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_print_error_
  f_status_t iki_write_print_error(iki_write_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    iki_write_print_line_first_locked(setting, print);
    fll_error_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e);

    return F_none;
  }
#endif // _di_iki_write_print_error_

#ifndef _di_iki_write_print_error_file_
  f_status_t iki_write_print_error_file(iki_write_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    iki_write_print_line_first_locked(setting, print);
    fll_error_file_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_none;
  }
#endif // _di_iki_write_print_error_file_

#ifndef _di_iki_write_print_error_main_missing_
  f_status_t iki_write_print_error_main_missing(iki_write_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QNo main provided, either pipe the main data or use the '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, iki_write_long_object_s, print.set->notable);
    fl_print_format("%[' and the '%]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, iki_write_long_content_s, print.set->notable);
    fl_print_format("%[' parameters.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_iki_write_print_error_main_missing_

#ifndef _di_iki_write_print_error_object_not_valid_
  f_status_t iki_write_print_error_object_not_valid(iki_write_setting_t * const setting, const fl_print_t print, const f_string_static_t object) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    iki_write_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe object '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%]", print.to, print.set->notable, object, print.set->notable);
    fl_print_format("%[' is not a valid IKI Object.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_iki_write_print_error_object_not_valid_

#ifndef _di_iki_write_print_help_
  f_status_t iki_write_print_help(iki_write_setting_t * const setting, const fl_print_t print) {

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

#ifndef _di_iki_write_print_line_first_locked_
  f_status_t iki_write_print_line_first_locked(iki_write_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->state.status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_iki_write_print_line_first_locked_

#ifndef _di_iki_write_print_line_first_unlocked_
  f_status_t iki_write_print_line_first_unlocked(iki_write_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->state.status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_iki_write_print_line_first_unlocked_

#ifndef _di_iki_write_print_line_last_locked_
  f_status_t iki_write_print_line_last_locked(iki_write_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->state.status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_iki_write_print_line_last_locked_

#ifndef _di_iki_write_print_line_last_unlocked_
  f_status_t iki_write_print_line_last_unlocked(iki_write_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->state.status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_iki_write_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif
