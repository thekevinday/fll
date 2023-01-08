#include "fss_payload_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_read_print_help_
  f_status_t fss_payload_read_print_help(fss_payload_read_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, fss_payload_read_program_name_long_s, fss_payload_read_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, fss_payload_read_short_at_s, fss_payload_read_long_at_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "      Select Object at this numeric index.");
    fll_program_print_help_option(print, fss_payload_read_short_content_s, fss_payload_read_long_content_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Print the Content (default).");
    fll_program_print_help_option(print, fss_payload_read_short_columns_s, fss_payload_read_long_columns_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Print the total number of columns.");
    fll_program_print_help_option(print, fss_payload_read_short_delimit_s, fss_payload_read_long_delimit_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Designate how to handle applying delimits.");
    fll_program_print_help_option(print, fss_payload_read_short_depth_s, fss_payload_read_long_depth_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Select Object at this numeric depth.");
    fll_program_print_help_option(print, fss_payload_read_short_empty_s, fss_payload_read_long_empty_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Include empty Content when processing.");
    fll_program_print_help_option(print, fss_payload_read_short_line_s, fss_payload_read_long_line_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Print only the Content at the given line.");
    fll_program_print_help_option(print, fss_payload_read_short_name_s, fss_payload_read_long_name_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Select Object with this name.");
    fll_program_print_help_option(print, fss_payload_read_short_object_s, fss_payload_read_long_object_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Print the Object.");
    fll_program_print_help_option(print, fss_payload_read_short_pipe_s, fss_payload_read_long_pipe_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Print using the special pipe format.");
    fll_program_print_help_option(print, fss_payload_read_short_original_s, fss_payload_read_long_original_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Print with the original quotes and escapes.");
    fll_program_print_help_option(print, fss_payload_read_short_select_s, fss_payload_read_long_select_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Select sub-Content at this index.");
    fll_program_print_help_option(print, fss_payload_read_short_total_s, fss_payload_read_long_total_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Print the total number of lines.");
    fll_program_print_help_option(print, fss_payload_read_short_trim_s, fss_payload_read_long_trim_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Trim Object names on select or print.");

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, fss_payload_read_program_name_s, fll_program_parameter_filenames_s);

    fl_print_format("%r %[Notes:%]%r", print.to, f_string_eol_s, print.set->important, print.set->important, f_string_eol_s);

    fl_print_format("  This program will print the Content associated with the given Object and Content main based on the FSS-000E Payload standard.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  All numeric positions (indexes) start at 0 instead of 1.%r", print.to, f_string_eol_s);
    fl_print_format("  For example, a file of 17 lines would range from 0 to 16.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the %[%r%r%] option, an order of operations is enforced on the parameters.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_depth_s, print.set->notable, f_string_eol_s);

    fl_print_format("  When this order of operations is in effect, parameters to the right of a depth parameter are influenced by that depth parameter:%r", print.to, f_string_eol_s);

    fl_print_format("    %[%r%r%]: An Object index at the specified depth.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_at_s, print.set->notable, f_string_eol_s);
    fl_print_format("    %[%r%r%]: A new depth within the specified depth, indexed from the root.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_depth_s, print.set->notable, f_string_eol_s);
    fl_print_format("    %[%r%r%]: An Object name at the specified depth.%r%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_name_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%] must be in numeric order, but values in between may be skipped.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_depth_s, print.set->notable, f_string_eol_s);
    fl_print_format("    ('-d 0 -a 1 -d 2 -a 2' would specify index 1 at depth 0, any index at depth 1, and index 2 at depth 2.)%r", print.to, f_string_eol_s);
    fl_print_format("    ('-d 2 -a 1 -d 0 -a 2' would be invalid because depth 2 is before depth 1.)%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%] selects a Content column.%r%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_select_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Specify both %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_object_s, print.set->notable);
    fl_print_format(" and the %[%r%r%] parameters to get the total objects.%r%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_total_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When both %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_at_s, print.set->notable);
    fl_print_format(" and %[%r%r%] parameters are specified (at the same depth),", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_name_s, print.set->notable);
    fl_print_format(" the %[%r%r%] parameter value will be treated as a position relative to the specified", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_at_s, print.set->notable);
    fl_print_format(" %[%r%r%] parameter value.%r%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_name_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program may support parameters, such as %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_depth_s, print.set->notable);
    fl_print_format(" or %[%r%r%], even if not supported by the standard.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_select_s, print.set->notable, f_string_eol_s);
    fl_print_format("  This is done to help ensure consistency for scripting.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  For parameters like %[%r%r%],", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_depth_s, print.set->notable);
    fl_print_format(" if the standard doesn't support nested Content, then only a depth of 0 would be valid.%r", print.to, f_string_eol_s);

    fl_print_format("  For parameters like %[%r%r%],", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_select_s, print.set->notable);
    fl_print_format(" if the standard doesn't support multiple Content groups, then only a select of 0 would be valid.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_trim_s, print.set->notable);
    fl_print_format(" will remove leading and trailing white spaces when selecting objects or when printing objects.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying both the %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_object_s, print.set->notable);
    fl_print_format(" parameter and the %[%r%r%] parameter, the entire Object and Content are printed, including the formatting.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_content_s, print.set->notable, f_string_eol_s);
    fl_print_format("  Both the Object and Content printed are already escaped.%r", print.to, f_string_eol_s);
    fl_print_format("  Both the Object and Content are separated by a New Line character '\\n' (U+000A).%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter %[%r%r%] accepts the following:%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_delimit_s, print.set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Do not apply delimits.%r", print.to, print.set->notable, fss_payload_read_delimit_mode_name_none_s, print.set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: (default) Apply all delimits.%r", print.to, print.set->notable, fss_payload_read_delimit_mode_name_all_s, print.set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Apply delimits for Objects.%r", print.to, print.set->notable, fss_payload_read_delimit_mode_name_object_s, print.set->notable, f_string_eol_s);
    fl_print_format("  - A number, 0 or greater: apply delimits for Content at the specified depth.%r", print.to, f_string_eol_s);
    fl_print_format("  - A number, 0 or greater, followed by a %[%r%]: (such as '1+') apply delimits for Content at the specified depth and any greater depth (numerically).%r", print.to, print.set->notable, fss_payload_read_delimit_mode_name_greater_s, print.set->notable, f_string_eol_s, f_string_eol_s);
    fl_print_format("  - A number, 0 or lesser, followed by a %[%r%]: (such as '1-') apply delimits for Content at the specified depth and any lesser depth (numerically).%r%r", print.to, print.set->notable, fss_payload_read_delimit_mode_name_lesser_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] parameter may be specified multiple times to customize the delimit behavior.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_delimit_s, print.set->notable, f_string_eol_s);

    fl_print_format("  The %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_delimit_s, print.set->notable);
    fl_print_format(" values %[%r%]", print.to, print.set->notable, fss_payload_read_delimit_mode_name_none_s, print.set->notable);
    fl_print_format(" and %[%r%],", print.to, print.set->notable, fss_payload_read_delimit_mode_name_all_s, print.set->notable);
    fl_print_format(" overrule all other delimit values.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameters %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_columns_s, print.set->notable);
    fl_print_format(" and %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_select_s, print.set->notable);
    fl_print_format(" refer to a Content column.%r", print.to, f_string_eol_s);
    fl_print_format("  The word 'column' is being loosely defined to refer to a specific Content.%r", print.to, f_string_eol_s);
    fl_print_format("  This is not to be confused with a depth.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  As an exceptional case, a %[%r%r%] of", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_depth_s, print.set->notable);
    fl_print_format(" %[1%] applies only to the explicit Object of", print.to, print.set->notable, print.set->notable);
    fl_print_format(" '%[%r%]'.%r", print.to, print.set->notable, f_fss_header_s, print.set->notable, f_string_eol_s);
    fl_print_format("  Content at this depth is processed as FSS-0001 Extended.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The Content of the explicit Object of", print.to);
    fl_print_format(" '%[%r%]'", print.to, print.set->notable, f_fss_payload_s, print.set->notable, f_string_eol_s);
    fl_print_format(" will not contain any Content close pipe control codes when using", print.to);
    fl_print_format(" %[%r%r%].%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_payload_read_long_pipe_s, print.set->notable, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_payload_read_print_help_

#ifndef _di_fss_payload_read_print_line_first_locked_
  f_status_t fss_payload_read_print_line_first_locked(fss_payload_read_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_fss_payload_read_print_line_first_locked_

#ifndef _di_fss_payload_read_print_line_first_unlocked_
  f_status_t fss_payload_read_print_line_first_unlocked(fss_payload_read_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_fss_payload_read_print_line_first_unlocked_

#ifndef _di_fss_payload_read_print_line_last_locked_
  f_status_t fss_payload_read_print_line_last_locked(fss_payload_read_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (fss_payload_read_main_flag_verify_e | fss_payload_read_main_flag_file_to_e)) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fss_payload_read_print_line_last_locked_

#ifndef _di_fss_payload_read_print_line_last_unlocked_
  f_status_t fss_payload_read_print_line_last_unlocked(fss_payload_read_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (fss_payload_read_main_flag_verify_e | fss_payload_read_main_flag_file_to_e)) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fss_payload_read_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif
