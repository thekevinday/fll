#include "byte_dump.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_print_help_
  f_status_t byte_dump_print_help(byte_dump_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    fll_program_print_help_header(print, byte_dump_program_name_long_s, byte_dump_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option(print, byte_dump_short_binary_s, byte_dump_long_binary_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Display binary representation.");
    fll_program_print_help_option(print, byte_dump_short_decimal_s, byte_dump_long_decimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Display decimal representation.");
    fll_program_print_help_option(print, byte_dump_short_duodecimal_s, byte_dump_long_duodecimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Display duodecimal representation.");
    fll_program_print_help_option(print, byte_dump_short_hexidecimal_s, byte_dump_long_hexidecimal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Display hexadecimal representation.");
    fll_program_print_help_option(print, byte_dump_short_octal_s, byte_dump_long_octal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Display octal representation.");
    fll_program_print_help_option(print, byte_dump_short_unicode_s, byte_dump_long_unicode_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Display using Unicode representation for valid Unicode (like: U+0000).");

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option(print, byte_dump_short_first_s, byte_dump_long_first_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Start reading at this byte offset.");
    fll_program_print_help_option(print, byte_dump_short_last_s, byte_dump_long_last_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Stop reading at this (inclusive) byte offset.");

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option(print, byte_dump_short_narrow_s, byte_dump_long_narrow_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Use narrow display, resulting in 1*width reducing size of the text columns.");
    fll_program_print_help_option(print, byte_dump_short_placeholder_s, byte_dump_long_placeholder_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use a placeholder character instead of a space for placeholders.");
    fll_program_print_help_option(print, byte_dump_short_text_s, byte_dump_long_text_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Include a column of text when displaying the bytes.");
    fll_program_print_help_option(print, byte_dump_short_wide_s, byte_dump_long_wide_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Use wide display, resulting in 2*width allowing for space for wide characters in the text columns.");
    fll_program_print_help_option(print, byte_dump_short_width_s, byte_dump_long_width_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Set number of columns of Bytes to display.");

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);
    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fl_print_format(" %[Special Options:%] ", print.to.stream, context.set.important, context.set.important);

    fll_program_print_help_option_long(print.to, context, byte_dump_long_normal_s, f_console_symbol_long_enable_s, " Display UTF-8 symbols for ASCII control codes.");
    fll_program_print_help_option_long(print.to, context, byte_dump_long_simple_s, f_console_symbol_long_enable_s, " Display spaces for ASCII control codes.");
    fll_program_print_help_option_long(print.to, context, byte_dump_long_classic_s, f_console_symbol_long_enable_s, "Display periods for ASCII control codes.");

    fll_program_print_help_usage(print, byte_dump_program_name_s, fll_program_parameter_filenames_s);

    //if (!(setting->flag & XXX_main_flag_line_last_no_e)) {
      f_print_dynamic_raw(f_string_eol_s, print.to.stream);
    //}

    fl_print_format("  When using the %[%r%r%] option, some UTF-8 characters may be replaced by your instance and cause display alignment issues.%r%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_text_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Special UTF-8 characters and non-spacing UTF-8 characters may be replaced with a space (or a placeholder when the %[%r%r%] option is used).%r%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_placeholder_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  UTF-8 \"Combining\" characters might have a space appended to allow a proper display but this may cause copy and paste issues.%r%r", print.to.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When %[%r%r%] is used, any UTF-8 sequences will still be printed in full should any part is found within the requested range.%r%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_last_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the %[%r%r%] option, invalid Unicode will fallback to being displayed using one of the other modes.%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, byte_dump_long_unicode_s, context.set.notable, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    f_file_stream_flush(output);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_byte_dump_print_help_

#ifndef _di_byte_dump_print_line_first_
  void byte_dump_print_line_first(byte_dump_setting_t * const setting, const fl_print_t print, const bool lock) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    if (lock) {
      fll_print_dynamic_raw(setting->line_first, print.to.stream);
    }
    else {
      f_print_dynamic_raw(setting->line_first, print.to.stream);
    }
  }
#endif // _di_byte_dump_print_line_first_

#ifndef _di_byte_dump_print_line_last_
  void byte_dump_print_line_last(byte_dump_setting_t * const setting, const fl_print_t print, const bool lock) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (print.verbosity == f_console_verbosity_error_e && !F_status_is_error(setting->status)) return;
    if (setting->flag & byte_dump_main_flag_verify_e) return;
    if ((setting->flag & byte_dump_main_flag_file_to_e) && !F_status_is_error(setting->status)) return;

    if (lock) {
      fll_print_dynamic_raw(setting->line_last, print.to.stream);
    }
    else {
      f_print_dynamic_raw(setting->line_last, print.to.stream);
    }
  }
#endif // _di_byte_dump_print_line_last_

#ifdef __cplusplus
} // extern "C"
#endif
