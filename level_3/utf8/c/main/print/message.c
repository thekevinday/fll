#include "../utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_message_help_
  f_status_t utf8_print_message_help(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    utf8_main_t * const main = (utf8_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, utf8_program_name_long_s, utf8_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, utf8_short_from_bytesequence_s, utf8_long_from_bytesequence_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "The expected input format is byte sequence (character data).");
    fll_program_print_help_option(print, utf8_short_from_codepoint_s, utf8_long_from_codepoint_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   The expected input format is codepoint (such as U+0000).");
    fll_program_print_help_option(print, utf8_short_from_file_s, utf8_long_from_file_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "        Use the given output as the input source.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, utf8_short_to_bytesequence_s, utf8_long_to_bytesequence_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "The output format is byte sequence (character data).");
    fll_program_print_help_option(print, utf8_short_to_codepoint_s, utf8_long_to_codepoint_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   The output format is codepoint (such as U+0000).");
    fll_program_print_help_option(print, utf8_short_to_combining_s, utf8_long_to_combining_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   The output format is to print whether or not character is combining or not.");
    fll_program_print_help_option(print, utf8_short_to_file_s, utf8_long_to_file_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "        Use the given file as the output destination.");
    fll_program_print_help_option(print, utf8_short_to_width_s, utf8_long_to_width_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "       The output format is to print the width of a character (either 0, 1, or 2).");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, utf8_short_headers_s, utf8_long_headers_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "      Print headers for each section (pipe, file, or parameter).");
    fll_program_print_help_option(print, utf8_short_separate_s, utf8_long_separate_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "     Separate characters by newlines (implied when printing headers).");
    fll_program_print_help_option(print, utf8_short_strip_invalid_s, utf8_long_strip_invalid_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Strip invalid Unicode characters (do not print invalid sequences).");
    fll_program_print_help_option(print, utf8_short_verify_s, utf8_long_verify_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "       Only perform verification of valid sequences.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, utf8_program_name_s, utf8_program_help_parameters_s);

    fl_print_format("%r  The default behavior is to assume the expected input is byte sequences from the command line to be output to the screen as codepoints.%r%r", print->to, f_string_eol_s, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Multiple input sources are allowed but only a single output destination is allowed.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the parameter '%[%r%r%]', no data is printed and 0 is returned if valid or 1 is returned if invalid.%r%r", print->to, print->set->notable, f_console_symbol_long_normal_s, utf8_long_verify_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the parameter '%[%r%r%]' with the parameter ", print->to, print->set->notable, f_console_symbol_long_normal_s, utf8_long_to_combining_s, print->set->notable);
    fl_print_format("'%[%r%r%]', the ", print->to, print->set->notable, f_console_symbol_long_normal_s, utf8_long_to_width_s, print->set->notable);
    fl_print_format("'%[%r%]' character is printed to represent the combining and the digits are used to represent widths.%r", print->to, print->set->notable, utf8_string_combining_is_s, print->set->notable, f_string_eol_s);
    fl_print_format("  The combining characters should be considered 1-width by themselves or 0-width when combined.%r", print->to, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_utf8_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif
