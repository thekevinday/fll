#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_print_help_
  f_status_t status_code_print_help(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);

    f_file_stream_lock(print.to);

    fll_program_print_help_header(
      print,
      setting->program_name_long
        ? *setting->program_name_long
        : status_code_program_name_long_s,
      status_code_program_version_s
    );

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, status_code_short_fine_s, status_code_long_fine_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Print F_true or F_false if status code is neither an error nor a warning or print number with neither the error code nor the warning code bits set.");
    fll_program_print_help_option(print, status_code_short_warning_s, status_code_long_warning_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Print F_true or F_false if status code is a warning or print number with warning code bit set.");
    fll_program_print_help_option(print, status_code_short_error_s, status_code_long_error_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Print F_true or F_false if status code is an error or print number with error code bit set.");
    fll_program_print_help_option(print, status_code_short_number_s, status_code_long_number_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Convert status code name to number.");

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(
      print,
      setting->program_name
        ? *setting->program_name
        : status_code_program_name_s,
      status_code_program_help_parameters_s
    );

    if (setting->status_string_help_detail) {
      setting->status_string_help_detail(setting, print);
    }

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_status_code_print_help_

#ifndef _di_status_code_print_help_detail_
  f_status_t status_code_print_help_detail(void * const void_setting, const fl_print_t print) {

    if (!void_setting) return F_status_set_error(F_output_not);

    fl_print_format("  The FLL programs use a %[16-bit unsigned integer%] to represent the return status of programs and functions.%r%r", print.to, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Programs may print a generic error with one of these codes.%r", print.to, f_string_eol_s);
    fl_print_format("  This is a tool for converting to or converting from these codes.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[16-bit unsigned integer%] also has the first two high-order bits used to represent flags.%r", print.to, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  These flags are the %[error%] bit and the %[warning%] bit.%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  When neither of these flags are set, then the status is considered %[fine%].%r%r", print.to, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  These codes stop at the %[F_status_code_last%] code.%r%r", print.to, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Each code will be printed on its own line.%r", print.to, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  Errors regarding each code may be printed on its own line.%r", print.to, f_string_eol_s);

    return F_none;
  }
#endif // _di_status_code_print_help_detail_

#ifdef __cplusplus
} // extern "C"
#endif
