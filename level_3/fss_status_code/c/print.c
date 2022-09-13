#include "fss_status_code.h"
#include "private-common.h"
#include "print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_status_code_print_error_cannot_error_warning_number_
  f_status_t fss_status_code_print_error_cannot_error_warning_number(fss_status_code_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QCannot specify the '%]", print.to.stream, print.context, print.prefix, print.context);
    fl_print_format("%[%r%r%]", print.to.stream, print.notable, f_console_symbol_long_enable_s, fss_status_code_long_error_s, print.notable);
    fl_print_format("%[' parameter with the '%]", print.to.stream, print.context, print.context);
    fl_print_format("%[%r%r%]", print.to.stream, print.notable, f_console_symbol_long_enable_s, fss_status_code_long_warning_s, print.notable);
    fl_print_format("%[' parameter when not also specifying the '%]", print.to.stream, print.context, print.context);
    fl_print_format("%[%r%r%]", print.to.stream, print.notable, f_console_symbol_long_enable_s, fss_status_code_long_number_s, print.notable);
    fl_print_format("%[' parameter.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_status_code_print_error_cannot_error_warning_number_

#ifndef _di_fss_status_code_print_error_no_fss_status_codes_
  f_status_t fss_status_code_print_error_no_fss_status_codes(fss_status_code_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_print_format("%[No status code is specified.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_status_code_print_error_no_fss_status_codes_

#ifndef _di_fss_status_code_print_help_
  f_status_t fss_status_code_print_help(fss_status_code_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    fll_program_print_help_header(print, fss_status_code_program_name_long_s, fss_status_code_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option(print, fss_status_code_short_fine_s, fss_status_code_long_fine_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Print F_true or F_false if status code is neither an error nor a warning or print number with neither the error code nor the warning code bits set.");
    fll_program_print_help_option(print, fss_status_code_short_warning_s, fss_status_code_long_warning_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print F_true or F_false if status code is a warning or print number with warning code bit set.");
    fll_program_print_help_option(print, fss_status_code_short_error_s, fss_status_code_long_error_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print F_true or F_false if status code is an error or print number with error code bit set.");
    fll_program_print_help_option(print, fss_status_code_short_number_s, fss_status_code_long_number_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Convert status code name to number.");

    fll_program_print_help_usage(print, fss_status_code_program_name_s, fss_status_code_program_help_parameters_s);

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_status_code_print_help_

#ifndef _di_fss_status_code_print_line_first_locked_
  f_status_t fss_status_code_print_line_first_locked(fss_status_code_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    return F_none;
  }
#endif // _di_fss_status_code_print_line_first_locked_

#ifndef _di_fss_status_code_print_line_first_unlocked_
  f_status_t fss_status_code_print_line_first_unlocked(fss_status_code_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to.stream);

    return F_none;
  }
#endif // _di_fss_status_code_print_line_first_unlocked_

#ifndef _di_fss_status_code_print_line_last_locked_
  f_status_t fss_status_code_print_line_last_locked(fss_status_code_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to.stream);

    return F_none;
  }
#endif // _di_fss_status_code_print_line_last_locked_

#ifndef _di_fss_status_code_print_line_last_unlocked_
  f_status_t fss_status_code_print_line_last_unlocked(fss_status_code_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    return F_none;
  }
#endif // _di_fss_status_code_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif
