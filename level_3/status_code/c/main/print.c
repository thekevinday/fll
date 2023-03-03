#include "status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_print_code_
  f_status_t status_code_print_code(status_code_setting_t * const setting, const fl_print_t print, const uint16_t code) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_format("%ui%r", print.to, code, f_string_eol_s);

    return F_none;
  }
#endif // _di_status_code_print_code_

#ifndef _di_status_code_print_context_value_
  f_status_t status_code_print_context_value(status_code_setting_t * const setting, const fl_print_t print, const f_color_set_t context, const f_string_static_t value) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    fll_print_format("%[%Q%]%r", print.to, context, value, context, f_string_eol_s);

    return F_none;
  }
#endif // _di_status_code_print_context_value_

#ifndef _di_status_code_print_error_
  f_status_t status_code_print_error(status_code_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    status_code_print_line_first_locked(setting, print);
    fll_error_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e);

    return F_none;
  }
#endif // _di_status_code_print_error_

#ifndef _di_status_code_print_error_cannot_error_warning_number_
  f_status_t status_code_print_error_cannot_error_warning_number(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QCannot specify the '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%r%r%]", print.to, print.notable, f_console_symbol_long_normal_s, status_code_long_error_s, print.notable);
    fl_print_format("%[' parameter with the '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%r%]", print.to, print.notable, f_console_symbol_long_normal_s, status_code_long_warning_s, print.notable);
    fl_print_format("%[' parameter when not also specifying the '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%r%]", print.to, print.notable, f_console_symbol_long_normal_s, status_code_long_number_s, print.notable);
    fl_print_format("%[' parameter.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_status_code_print_error_cannot_error_warning_number_

#ifndef _di_status_code_print_error_no_status_codes_
  f_status_t status_code_print_error_no_status_codes(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[No status code is specified.%]%r", print.to, print.context, print.context, f_string_eol_s);

    return F_none;
  }
#endif // _di_status_code_print_error_no_status_codes_

#ifndef _di_status_code_print_error_invalid_callback_
  f_status_t status_code_print_error_invalid_callback(status_code_setting_t * const setting, const fl_print_t print, const f_string_t name) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QInvalid callback specified for '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%s%]", print.to, print.notable, name, print.notable);
    fl_print_format("%[' internal setting.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_status_code_print_error_invalid_callback_

#ifndef _di_status_code_print_help_
  f_status_t status_code_print_help(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

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

    f_print_dynamic_raw(setting->line_last, print.to);

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

#ifndef _di_status_code_print_line_first_data_
  f_status_t status_code_print_line_first_data(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    if (setting->flag & status_code_main_flag_print_first_e) {
      fll_print_dynamic_raw(setting->line_first, print.to);

      setting->flag -= status_code_main_flag_print_first_e;
    }

    return F_none;
  }
#endif // _di_status_code_print_line_first_data_

#ifndef _di_status_code_print_line_first_locked_
  f_status_t status_code_print_line_first_locked(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (setting->flag & status_code_main_flag_print_first_e) {
      fll_print_dynamic_raw(setting->line_first, print.to);

      setting->flag -= status_code_main_flag_print_first_e;
    }
    else {
      fll_print_dynamic_raw(f_string_eol_s, print.to);
    }

    return F_none;
  }
#endif // _di_status_code_print_line_first_locked_

#ifndef _di_status_code_print_line_first_unlocked_
  f_status_t status_code_print_line_first_unlocked(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (setting->flag & status_code_main_flag_print_first_e) {
      fll_print_dynamic_raw(setting->line_first, print.to);

      setting->flag -= status_code_main_flag_print_first_e;
    }
    else {
      fll_print_dynamic_raw(f_string_eol_s, print.to);
    }

    return F_none;
  }
#endif // _di_status_code_print_line_first_unlocked_

#ifndef _di_status_code_print_line_last_locked_
  f_status_t status_code_print_line_last_locked(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_status_code_print_line_last_locked_

#ifndef _di_status_code_print_line_last_unlocked_
  f_status_t status_code_print_line_last_unlocked(status_code_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_status_code_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif
