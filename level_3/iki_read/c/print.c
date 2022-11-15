#include "iki_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_error_
  f_status_t iki_read_print_error(iki_read_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    iki_read_print_line_first_locked(setting, print);
    fll_error_print(print, F_status_set_fine(setting->status), function, F_true);
    iki_read_print_line_last_locked(setting, print);

    return F_none;
  }
#endif // _di_iki_read_print_error_

#ifndef _di_iki_read_print_error_file_
  f_status_t iki_read_print_error_file(iki_read_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    iki_read_print_line_first_locked(setting, print);
    fll_error_file_print(print, F_status_set_fine(setting->status), function, F_true, name, operation, type);
    iki_read_print_line_last_locked(setting, print);

    return F_none;
  }
#endif // _di_iki_read_print_error_file_

#ifndef _di_iki_read_print_help_
  f_status_t iki_read_print_help(iki_read_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, iki_read_program_name_long_s, iki_read_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, iki_read_short_at_s, iki_read_long_at_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Select variable at this numeric index.");
    fll_program_print_help_option(print, iki_read_short_line_s, iki_read_long_line_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print only the variables at the given line within the file.");
    fll_program_print_help_option(print, iki_read_short_name_s, iki_read_long_name_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Select variables with this name.");
    fll_program_print_help_option(print, iki_read_short_whole_s, iki_read_long_whole_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print all of the data instead of just the IKI variable data.");

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, iki_read_short_content_s, iki_read_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the variable value (aka: content) (default)");
    fll_program_print_help_option(print, iki_read_short_literal_s, iki_read_long_literal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the entire variable (aka: object, content, and syntax).");
    fll_program_print_help_option(print, iki_read_short_object_s, iki_read_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the variable name (aka: object).");
    fll_program_print_help_option(print, iki_read_short_total_s, iki_read_long_total_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print the total number of variables.");

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, iki_read_short_reassign_s, iki_read_long_reassign_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Re-assign the variable for the given name and matching content value with the given string.");
    fll_program_print_help_option(print, iki_read_short_replace_s, iki_read_long_replace_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Simple substitution, replacing the variable for the given name with the given string.");
    fll_program_print_help_option(print, iki_read_short_substitute_s, iki_read_long_substitute_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Substitute the variable for the given name and matching content value with the given string.");
    fll_program_print_help_option(print, iki_read_short_wrap_s, iki_read_long_wrap_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Prepend and append strings for the given name.");

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, iki_read_program_name_s, fll_program_parameter_filenames_s);

    fl_print_format("%r %[Notes:%]%r", print.to, f_string_eol_s, print.set->important, print.set->important, f_string_eol_s);
    fl_print_format("  This program will find and print variables, vocabularies, or content following the IKI standard, without focusing on any particular vocabulary specification.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] option requires 2 additional parameters:", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_replace_s, print.set->notable);
    fl_print_format(" %[<%]%r%[>%]", print.to, print.set->notable, print.set->notable, iki_read_substitution_vocabulary_s, print.set->notable, print.set->notable);
    fl_print_format(" %[<%]%r%[>%].%r", print.to, print.set->notable, print.set->notable, iki_read_substitution_with_s, print.set->notable, print.set->notable, f_string_eol_s);

    fl_print_format("    %[%r%]: The name of the vocabulary whose content is to be substituted.%r", print.to, print.set->notable, iki_read_substitution_vocabulary_s, print.set->notable, f_string_eol_s);
    fl_print_format("    %[%r%]: The new string to use as the substitute.%r%r", print.to, print.set->notable, iki_read_substitution_with_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The vocabulary is case-sensitive and must exactly match.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] and the", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_reassign_s, print.set->notable);
    fl_print_format(" %[%r%r%] options require 3 additional parameters:", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_substitute_s, print.set->notable);
    fl_print_format(" %[<%]%r%[>%]", print.to, print.set->notable, print.set->notable, iki_read_substitution_vocabulary_s, print.set->notable, print.set->notable);
    fl_print_format(" %[<%]%r%[>%]", print.to, print.set->notable, print.set->notable, iki_read_substitution_replace_s, print.set->notable, print.set->notable);
    fl_print_format(" %[<%]%r%[>%].%r", print.to, print.set->notable, print.set->notable, iki_read_substitution_with_s, print.set->notable, print.set->notable, f_string_eol_s);

    fl_print_format("    %[%r%]: The name of the vocabulary whose content is to be substituted or re-assigned.%r", print.to, print.set->notable, iki_read_substitution_vocabulary_s, print.set->notable, f_string_eol_s);
    fl_print_format("    %[%r%]: The content matching this exact string will be substituted or re-assigned.%r", print.to, print.set->notable, iki_read_substitution_replace_s, print.set->notable, f_string_eol_s);
    fl_print_format("    %[%r%]: The new string to use as the substitute or re-assignment.%r%r", print.to, print.set->notable, iki_read_substitution_with_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The vocabulary and replacement are case-sensitive and must exactly match.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] option requires 3 additional parameters:", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_wrap_s, print.set->notable);
    fl_print_format(" %[<%]%r%[>%]", print.to, print.set->notable, print.set->notable, iki_read_substitution_vocabulary_s, print.set->notable, print.set->notable);
    fl_print_format(" %[<%]%r%[>%]", print.to, print.set->notable, print.set->notable, iki_read_substitution_before_s, print.set->notable, print.set->notable);
    fl_print_format(" %[<%]%r%[>%].%r", print.to, print.set->notable, print.set->notable, iki_read_substitution_after_s, print.set->notable, print.set->notable, f_string_eol_s);

    fl_print_format("    %[%r%]: The name of the vocabulary whose content is to be wrapped.%r", print.to, print.set->notable, iki_read_substitution_vocabulary_s, print.set->notable, f_string_eol_s);
    fl_print_format("    %[%r%]: The string to prepend.%r", print.to, print.set->notable, iki_read_substitution_before_s, print.set->notable, f_string_eol_s);
    fl_print_format("    %[%r%]: The string to append.%r%r", print.to, print.set->notable, iki_read_substitution_after_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The vocabulary is case-sensitive and must exactly match.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The difference between %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_replace_s, print.set->notable);
    fl_print_format(" and %[%r%r%] is that the", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_substitute_s, print.set->notable);
    fl_print_format(" %[%r%r%] option substitutes all matching vocabulary names and the", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_replace_s, print.set->notable);
    fl_print_format(" %[%r%r%] option substitutes all matching vocabulary names that must also have the given matching content.%r%r", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_substitute_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_reassign_s, print.set->notable);
    fl_print_format(" option is identical to the %[%r%r%] option", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_substitute_s, print.set->notable);
    fl_print_format(" except that the %[%r%r%] option is ignored (not applied).%r%r", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_wrap_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%]", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_substitute_s, print.set->notable);
    fl_print_format(" option takes priority over the %[%r%r%] option when matching the same variable.%r%r", print.to, print.set->notable, f_console_symbol_long_enable_s, iki_read_long_replace_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The default behavior is to only display content portion of the IKI variable.%r", print.to, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_iki_read_print_help_

#ifndef _di_iki_read_print_line_first_locked_
  f_status_t iki_read_print_line_first_locked(iki_read_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_iki_read_print_line_first_locked_

#ifndef _di_iki_read_print_line_first_unlocked_
  f_status_t iki_read_print_line_first_unlocked(iki_read_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_iki_read_print_line_first_unlocked_

#ifndef _di_iki_read_print_line_last_locked_
  f_status_t iki_read_print_line_last_locked(iki_read_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_iki_read_print_line_last_locked_

#ifndef _di_iki_read_print_line_last_unlocked_
  f_status_t iki_read_print_line_last_unlocked(iki_read_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_iki_read_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif
