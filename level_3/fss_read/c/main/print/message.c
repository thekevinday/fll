#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_print_message_help_
  void fss_read_print_message_help(fl_print_t * const print) {

    if (!print) return;

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, fss_read_short_at_s, fss_read_long_at_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "      Select Object at this numeric index.");
    fll_program_print_help_option(print, fss_read_short_content_s, fss_read_long_content_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Print the Content (default).");
    fll_program_print_help_option(print, fss_read_short_columns_s, fss_read_long_columns_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Print the total number of columns.");
    fll_program_print_help_option(print, fss_read_short_delimit_s, fss_read_long_delimit_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Designate how to handle applying delimits.");
    fll_program_print_help_option(print, fss_read_short_depth_s, fss_read_long_depth_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Select Object at this numeric depth.");
    fll_program_print_help_option(print, fss_read_short_empty_s, fss_read_long_empty_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Include empty Content when processing.");
    fll_program_print_help_option(print, fss_read_short_line_s, fss_read_long_line_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Print only the Content at the given line.");
    fll_program_print_help_option(print, fss_read_short_name_s, fss_read_long_name_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Select Object with this name.");
    fll_program_print_help_option(print, fss_read_short_object_s, fss_read_long_object_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Print the Object.");
    fll_program_print_help_option(print, fss_read_short_pipe_s, fss_read_long_pipe_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Print using the special pipe format.");
    fll_program_print_help_option(print, fss_read_short_original_s, fss_read_long_original_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Print with the original quotes and escapes.");
    fll_program_print_help_option(print, fss_read_short_select_s, fss_read_long_select_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Select sub-Content at this index.");
    fll_program_print_help_option(print, fss_read_short_total_s, fss_read_long_total_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Print the total number of lines.");
    fll_program_print_help_option(print, fss_read_short_trim_s, fss_read_long_trim_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Trim Object names on select or print.");
  }
#endif // _di_fss_read_print_message_help_

#ifndef _di_fss_read_print_message_help_note_header_
  void fss_read_print_message_help_note_header(fl_print_t * const print, const f_string_static_t number, const f_string_static_t name) {

    if (!print) return;

    fl_print_format(" %[Notes:%]%r  This program will print the data associated with the given Object and Content based on the FSS", print->to, print->set->notable, print->set->notable, f_string_eol_s);

    if (number.used) {
      fl_print_format("-%Q", print->to, number);

      if (name.used) {
        fl_print_format(" (%Q)", print->to, name);
      }
    }

    fl_print_format(" standard.%r", print->to, f_string_eol_s);
  }
#endif // _di_fss_read_print_message_help_note_header_

#ifndef _di_fss_read_print_message_help_note_
  void fss_read_print_message_help_note(fl_print_t * const print, const uint8_t new_line) {

    if (!print) return;

    f_color_set_context_t * const set = print->set;

    // TODO: this is just copied over and needs to be broken up somehow.
    fl_print_format("%r  All numeric positions (indexes) start at 0 instead of 1.%r", print->to, f_string_eol_s, f_string_eol_s);
    fl_print_format("  For example, a file of 17 lines would range from 0 to 16.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the %[%r%r%] option, an order of operations is enforced on the parameters.%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_depth_s, set->notable, f_string_eol_s);

    fl_print_format("  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%r", print->to, f_string_eol_s);

    fl_print_format("    %[%r%r%]: An Object index at the specified depth.%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_at_s, set->notable, f_string_eol_s);
    fl_print_format("    %[%r%r%]: A new depth within the specified depth, indexed from the root.%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_depth_s, set->notable, f_string_eol_s);
    fl_print_format("    %[%r%r%]: An Object name at the specified depth.%r%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_name_s, set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%] must be in numeric order, but values in between may be skipped.%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_depth_s, set->notable, f_string_eol_s);
    fl_print_format("    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%r", print->to, f_string_eol_s);
    fl_print_format("    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%] selects a Content column.%r%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_select_s, set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Specify both %[%r%r%]", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_object_s, set->notable);
    fl_print_format(" and the %[%r%r%] parameters to get the total objects.%r%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_total_s, set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When both %[%r%r%]", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_at_s, set->notable);
    fl_print_format(" and %[%r%r%] parameters are specified (at the same depth),", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_name_s, set->notable);
    fl_print_format(" the %[%r%r%] parameter value will be treated as a position relative to the specified", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_at_s, set->notable);
    fl_print_format(" %[%r%r%] parameter value.%r%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_name_s, set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program may support parameters, such as %[%r%r%]", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_depth_s, set->notable);
    fl_print_format(" or %[%r%r%], even if not supported by the standard.%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_select_s, set->notable, f_string_eol_s);
    fl_print_format("  This is done to help ensure consistency for scripting.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  For parameters like %[%r%r%],", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_depth_s, set->notable);
    fl_print_format(" if the standard doesn't support nested Content, then only a depth of 0 would be valid.%r", print->to, f_string_eol_s);

    fl_print_format("  For parameters like %[%r%r%],", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_select_s, set->notable);
    fl_print_format(" if the standard doesn't support multiple Content groups, then only a select of 0 would be valid.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%]", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_trim_s, set->notable);
    fl_print_format(" will remove leading and trailing white spaces when selecting objects or when printing objects.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying both the %[%r%r%]", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_object_s, set->notable);
    fl_print_format(" parameter and the %[%r%r%] parameter, the entire Object and Content are printed, including the formatting.%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_content_s, set->notable, f_string_eol_s);
    fl_print_format("  Both the Object and Content printed are already escaped.%r", print->to, f_string_eol_s);

    if (new_line == 0x2) {
      fl_print_format("  Depending on the standard both the Object and Content are separated by either a New Line character '\\n' (U+000A) or a space.%r%r", print->to, f_string_eol_s, f_string_eol_s);
    }
    else if (new_line) {
      fl_print_format("  Both the Object and Content are separated by a New Line character '\\n' (U+000A).%r%r", print->to, f_string_eol_s, f_string_eol_s);
    }
    else {
      fl_print_format("  Both the Object and Content are separated by a space.%r%r", print->to, f_string_eol_s, f_string_eol_s);
    }

    fl_print_format("  The parameter %[%r%r%] accepts the following:%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_delimit_s, set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Do not apply delimits.%r", print->to, set->notable, fss_read_string_none_s, set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: (default) Apply all delimits.%r", print->to, set->notable, fss_read_delimit_mode_name_all_s, set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Apply delimits for Objects.%r", print->to, set->notable, fss_read_delimit_mode_name_object_s, set->notable, f_string_eol_s); // @todo this isn't in embedded_list print, confirm/deny if this is intended or not.
    fl_print_format("  - A number, 0 or greater: apply delimits for Content at the specified depth.%r", print->to, f_string_eol_s);
    fl_print_format("  - A number, 0 or greater, followed by a %[%r%]: (such as '1+') apply delimits for Content at the specified depth and any greater depth (numerically).%r", print->to, set->notable, fss_read_delimit_mode_name_greater_s, set->notable, f_string_eol_s, f_string_eol_s);
    fl_print_format("  - A number, 0 or lesser, followed by a %[%r%]: (such as '1-') apply delimits for Content at the specified depth and any lesser depth (numerically).%r%r", print->to, set->notable, fss_read_delimit_mode_name_lesser_s, set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] parameter may be specified multiple times to customize the delimit behavior.%r", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_delimit_s, set->notable, f_string_eol_s);

    fl_print_format("  The %[%r%r%]", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_delimit_s, set->notable);
    fl_print_format(" values %[%r%]", print->to, set->notable, fss_read_string_none_s, set->notable);
    fl_print_format(" and %[%r%],", print->to, set->notable, fss_read_delimit_mode_name_all_s, set->notable);
    fl_print_format(" overrule all other delimit values.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameters %[%r%r%]", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_columns_s, set->notable);
    fl_print_format(" and %[%r%r%]", print->to, set->notable, f_console_symbol_long_normal_s, fss_read_long_select_s, set->notable);
    fl_print_format(" refer to a Content column.%r", print->to, f_string_eol_s);
    fl_print_format("  The word 'column' is being loosely defined to refer to a specific Content.%r", print->to, f_string_eol_s);
    fl_print_format("  This is not to be confused with a depth.%r", print->to, f_string_eol_s);
  }
#endif // _di_fss_read_print_message_help_note_

#ifndef _di_fss_read_print_message_help_pipe_
  void fss_read_print_message_help_pipe(fl_print_t * const print) {

    if (!print) return;

    // @todo there is a pipe input format but this documentation is for write rather than read, update this as appropriate or remove function entirely.
    fl_print_format("%r  The pipe uses the Backspace character '%[\\b%]' (%[U+0008%]) to designate the start of a Content.%r", print->to, f_string_eol_s, print->set->notable, print->set->notable, print->set->notable, print->set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Form Feed character '%[\\f%]' (%[U+000C%]) to designate the end of the last Content.%r", print->to, print->set->notable, print->set->notable, print->set->notable, print->set->notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Vertical Line character '%[\\v%]' (%[U+000B%]) is used to ignore a Content range (use this both before and after the range).%r", print->to, print->set->notable, print->set->notable, print->set->notable, print->set->notable, f_string_eol_s);
    fl_print_format("  For the pipe, an Object is terminated by either a Backspace character '%[\\b%]' (%[U+0008%])", print->to, print->set->notable, print->set->notable, print->set->notable, print->set->notable);
    fl_print_format(" or a Form Feed character '%[\\f%]' (%[U+000C%]).%r", print->to, print->set->notable, print->set->notable, print->set->notable, print->set->notable, f_string_eol_s);
    fl_print_format("  The end of the pipe represents the end of any Object or Content.%r", print->to, f_string_eol_s);
  }
#endif // _di_fss_read_print_message_help_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
