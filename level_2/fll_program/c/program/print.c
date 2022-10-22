#include "../program.h"
#include "../private-program.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_print_error_missing_file_
  f_status_t fll_program_print_error_missing_file(const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QNo files are specified.%]%r", print.to, print.set->error, print.prefix, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_missing_file_

#ifndef _di_fll_program_print_error_missing_variable_not_zero_
  f_status_t fll_program_print_error_missing_variable_not_zero(const fl_print_t print, const f_string_static_t variable) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe %]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%]", print.to, print.set->notable, variable, print.set->notable);
    fl_print_format("%[ is missing or has a length of %]", print.to, print.set->error, print.set->error);
    fl_print_format("%[0%]", print.to, print.set->notable, print.set->notable);
    fl_print_format("%[.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_missing_variable_not_zero_

#ifndef _di_fll_program_print_error_parameter_both_specified_same_amount_
  f_status_t fll_program_print_error_parameter_both_specified_same_amount(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t first, const f_string_static_t second) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, first, print.set->notable);
    fl_print_format("%[' parameter and the '%]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, second, print.set->notable);
    fl_print_format("%[' parameter must be specified the same number of times.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_both_specified_same_amount_

#ifndef _di_fll_program_print_error_parameter_cannot_use_with_
  f_status_t fll_program_print_error_parameter_cannot_use_with(const fl_print_t print, const f_string_static_t symbol_first, const f_string_static_t symbol_second, const f_string_static_t first, const f_string_static_t second) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QCannot specify the '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol_first, first, print.set->notable);
    fl_print_format("%[' parameter with the '%]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol_second, second, print.set->notable);
    fl_print_format("%[' parameter.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_cannot_use_with_

#ifndef _di_fll_program_print_error_parameter_integer_not_
  f_status_t fll_program_print_error_parameter_integer_not(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe value '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%]", print.to, print.set->notable, value, print.set->notable);
    fl_print_format("%[' for the parameter '%]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format("%[' is not a valid integer.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_integer_not_

#ifndef _di_fll_program_print_error_parameter_integer_not_negative_
  f_status_t fll_program_print_error_parameter_integer_not_negative(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe value '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%]", print.to, print.set->notable, value, print.set->notable);
    fl_print_format("%[' for the parameter '%]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format("%[' is not a valid negative integer.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_integer_not_negative_

#ifndef _di_fll_program_print_error_parameter_integer_not_positive_
  f_status_t fll_program_print_error_parameter_integer_not_positive(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe value '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%]", print.to, print.set->notable, value, print.set->notable);
    fl_print_format("%[' for the parameter '%]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format("%[' is not a valid positive integer.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_integer_not_positive_

#ifndef _di_fll_program_print_error_parameter_missing_value_
  f_status_t fll_program_print_error_parameter_missing_value(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe parameter %]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format(" %[is specified, but no value is given.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_missing_value_

#ifndef _di_fll_program_print_error_parameter_missing_value_requires_amount_
  f_status_t fll_program_print_error_parameter_missing_value_requires_amount(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t amount) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe parameter %]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format("%[ is specified, but %]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%Q%]", print.to, print.set->notable, amount, print.set->notable);
    fl_print_format(" %[values are not given.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_missing_value_requires_amount_

#ifndef _di_fll_program_print_error_parameter_must_specify_once_
  f_status_t fll_program_print_error_parameter_must_specify_once(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe parameter '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format("%[' may only be specified once.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_must_specify_once_

#ifndef _di_fll_program_print_error_parameter_must_specify_once_value_
  f_status_t fll_program_print_error_parameter_must_specify_once_value(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe value '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, value, print.set->notable);
    fl_print_format("%[' may only be specified once for the parameter '%]", print.to, print.set->error, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format("%['.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_parameter_must_specify_once_value_

#ifndef _di_fll_program_print_error_pipe_invalid_form_feed_
  f_status_t fll_program_print_error_pipe_invalid_form_feed(const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe pipe has incorrectly placed form-feed characters (\\f).%]%r", print.to, print.set->error, print.prefix, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_pipe_invalid_form_feed_

#ifndef _di_fll_program_print_error_pipe_missing_content_
  f_status_t fll_program_print_error_pipe_missing_content(const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe pipe has no content.%]%r", print.to, print.set->error, print.prefix, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_pipe_missing_content_

#ifndef _di_fll_program_print_error_pipe_object_without_content_
  f_status_t fll_program_print_error_pipe_object_without_content(const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe pipe has an Object without Content.%]%r", print.to, print.set->error, print.prefix, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_error_pipe_object_without_content_

#ifndef _di_fll_program_print_help_header_
  f_status_t fll_program_print_help_header(const fl_print_t print, const f_string_static_t name, const f_string_static_t version) {

    fl_print_format(" %[%Q%]%r", print.to, print.set->title, name, print.set->title, f_string_eol_s);
    fl_print_format("  %[Version %Q%]%r", print.to, print.set->notable, version, print.set->notable, f_string_eol_s);

    fl_print_format("%r %[Available Options:%] ", print.to, f_string_eol_s, print.set->important, print.set->important);

    return F_none;
  }
#endif // _di_fll_program_print_help_header_

#ifndef _di_fll_program_print_help_option_
  f_status_t fll_program_print_help_option(const fl_print_t print, const f_string_static_t option_short, const f_string_static_t option_long, const f_string_static_t symbol_short, const f_string_static_t symbol_long, const char *description) {

    return private_fll_program_print_help_option(print, option_short, option_long, symbol_short, symbol_long, description);
  }
#endif // _di_fll_program_print_help_option_

#ifndef _di_fll_program_print_help_option_standard_
  f_status_t fll_program_print_help_option_standard(const fl_print_t print) {

    private_fll_program_print_help_option(print, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "         Print this help message.");
    private_fll_program_print_help_option(print, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "         Output using colors that show up better on dark backgrounds.");
    private_fll_program_print_help_option(print, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "        Output using colors that show up better on light backgrounds.");
    private_fll_program_print_help_option(print, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "     Do not print using color.");
    private_fll_program_print_help_option(print, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "        Decrease verbosity, silencing most print.to.");
    private_fll_program_print_help_option(print, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "        Decrease verbosity, using only error print.to.");
    private_fll_program_print_help_option(print, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "       Set verbosity to normal.");
    private_fll_program_print_help_option(print, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "      Increase verbosity beyond normal print.to.");
    private_fll_program_print_help_option(print, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "        Enable debugging, significantly increasing verbosity beyond normal print.to.");
    private_fll_program_print_help_option(print, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "      Print only the version number.");
    private_fll_program_print_help_option(print, f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Disable printing of first line.");
    private_fll_program_print_help_option(print, f_console_standard_short_line_last_no_s, f_console_standard_long_line_last_no_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Disable printing of last line.");

    return F_none;
  }
#endif // _di_fll_program_print_help_option_standard_

#ifndef _di_fll_program_print_help_option_long_
  f_status_t fll_program_print_help_option_long(const fl_print_t print, const f_string_static_t option_long, const f_string_static_t symbol_long, const char *description) {

    fl_print_format("%r      %Q%[%Q%]  %S", print.to, f_string_eol_s, symbol_long, print.set->standout, option_long, print.set->standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_long_

#ifndef _di_fll_program_print_help_option_other_
  f_status_t fll_program_print_help_option_other(const fl_print_t print, const f_string_static_t option_other, const char *description) {

    fl_print_format("%r  %[%Q%]  %S", print.to, f_string_eol_s, print.set->standout, option_other, print.set->standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_other_

#ifndef _di_fll_program_print_help_usage_
  f_status_t fll_program_print_help_usage(const fl_print_t print, const f_string_static_t name, const f_string_static_t parameters) {

    fl_print_format(" %[Usage:%]%r", print.to, print.set->important, print.set->important, f_string_eol_s);

    fl_print_format("  %[%Q%]", print.to, print.set->standout, name, print.set->standout);
    fl_print_format(" %[[%] options %[]%]", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable);

    if (parameters.used) {
      fl_print_format(" %[[%] %Q %[]%]", print.to, print.set->notable, print.set->notable, parameters, print.set->notable, print.set->notable);
    }

    f_print_dynamic_raw(f_string_eol_s, print.to);

    return F_none;
  }
#endif // _di_fll_program_print_help_usage_

#ifndef _di_fll_program_print_signal_received_
  f_status_t fll_program_print_signal_received(const fl_print_t print, const f_string_static_t line_first, const uint32_t signal) {

    if (print.verbosity != f_console_verbosity_verbose_e && print.verbosity != f_console_verbosity_debug_e) {
      return F_output_not;
    }

    f_file_stream_lock(print.to);

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    f_file_stream_flush(print.to);

    fl_print_format("%]%r%[Received signal code %]", print.to, print.set->reset, line_first, print.set->warning, print.set->warning);
    fl_print_format("%[%u%]", print.to, print.set->notable, signal, print.set->notable);
    fl_print_format("%[.%]%r", print.to, print.set->warning, print.set->warning, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fll_program_print_signal_received_

#ifndef _di_fll_program_print_version_
  f_status_t fll_program_print_version(const fl_print_t print, const f_string_static_t version) {

    f_print_dynamic(version, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    return F_none;
  }
#endif // _di_fll_program_print_version_

#ifdef __cplusplus
} // extern "C"
#endif
