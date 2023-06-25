#include "../fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_print_message_help_
  f_status_t fss_identify_print_message_help(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_identify_main_t * const main = (fss_identify_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_identify_program_name_long_s, fss_identify_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, fss_identify_short_content_s, fss_identify_long_content_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Print the Identifier content (the 4-digit hexidecimal type code).");
    fll_program_print_help_option(print, fss_identify_short_object_s, fss_identify_long_object_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Print the Identifier object (the name).");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, fss_identify_short_line_s, fss_identify_long_line_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Print only the Identifier at the given line.");
    fll_program_print_help_option(print, fss_identify_short_name_s, fss_identify_long_name_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Select FSS using this full or partial type name or code.");
    fll_program_print_help_option(print, fss_identify_short_total_s, fss_identify_long_total_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Print the total Identifiers found.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_identify_program_name_s, fss_identify_program_help_parameters_s);

    fl_print_format("%r  The %[%r%r%] parameter refers to the file lines and not the lines in a given file.%r%r", print->to, f_string_eol_s, print->set->notable, f_console_symbol_long_normal_s, fss_identify_long_line_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  If neither the %[%r%r%] nor", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_identify_long_object_s, print->set->notable);
    fl_print_format(" %[%r%r%] are specified, then the default behavior is to print both.%r%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_identify_long_content_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying the %[%r%r%] parameter, neither the", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_identify_long_total_s, print->set->notable);
    fl_print_format(" %[%r%r%] nor the", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_identify_long_object_s, print->set->notable);
    fl_print_format(" %[%r%r%] parameter may be specified.%r%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_identify_long_content_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  An FSS file is identified by the following format: '%[# Object-Content%]'", print->to, print->set->notable, print->set->notable);
    fl_print_format(" where the Object, is a machine-name representing the name and may only consist of 'word' characters and the Content is a 4-digit hexidecimal number representing a particular variant of the Object.%r", print->to, f_string_eol_s);
    fl_print_format("  This identifier, if provided, must exist on the first line in a file and must begin with the pound character: '#'.%r", print->to, f_string_eol_s);
    fl_print_format("  Whitespace must follow this pound character.%r", print->to, f_string_eol_s);
    fl_print_format("  There may be multiple Object and Content pairs, separated by white space, such as: '# fss-0002 fss-0000 iki-0002'.%r", print->to, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_identify_print_message_help_
#ifdef __cplusplus
} // extern "C"
#endif
