#include "../program.h"
#include "../private-program.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_print_help_header_
  f_status_t fll_program_print_help_header(const fl_print_t print, const f_string_static_t name, const f_string_static_t version) {

    fl_print_format(" %[%Q%]%r", print.to.stream, print.set->title, name, print.set->title, f_string_eol_s);
    fl_print_format("  %[Version %Q%]%r", print.to.stream, print.set->notable, version, print.set->notable, f_string_eol_s);

    fl_print_format("%r %[Available Options:%] ", print.to.stream, f_string_eol_s, print.set->important, print.set->important);

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

    fl_print_format("%r      %Q%[%Q%]  %S", print.to.stream, f_string_eol_s, symbol_long, print.set->standout, option_long, print.set->standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_long_

#ifndef _di_fll_program_print_help_option_other_
  f_status_t fll_program_print_help_option_other(const fl_print_t print, const f_string_static_t option_other, const char *description) {

    fl_print_format("%r  %[%Q%]  %S", print.to.stream, f_string_eol_s, print.set->standout, option_other, print.set->standout, description);

    return F_none;
  }
#endif // _di_fll_program_print_help_option_other_

#ifndef _di_fll_program_print_help_usage_
  f_status_t fll_program_print_help_usage(const fl_print_t print, const f_string_static_t name, const f_string_static_t parameters) {

    fl_print_format("%r%r %[Usage:%]%r", print.to.stream, f_string_eol_s, f_string_eol_s, print.set->important, print.set->important, f_string_eol_s);

    fl_print_format("  %[%Q%]", print.to.stream, print.set->standout, name, print.set->standout);
    fl_print_format(" %[[%] options %[]%]", print.to.stream, print.set->notable, print.set->notable, print.set->notable, print.set->notable);

    if (parameters.used) {
      fl_print_format(" %[[%] %Q %[]%]", print.to.stream, print.set->notable, print.set->notable, parameters, print.set->notable, print.set->notable);
    }

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    return F_none;
  }
#endif // _di_fll_program_print_help_usage_

#ifndef _di_fll_program_print_signal_received_
  f_status_t fll_program_print_signal_received(const fl_print_t print, const f_string_static_t line_first, const f_status_t signal) {

    if (print.verbosity != f_console_verbosity_verbose_e && print.verbosity != f_console_verbosity_debug_e) {
      return F_output_not;
    }

    flockfile(print.to.stream);

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    f_file_stream_flush(print.to);

    fl_print_format("%]%r%[Received signal code %]", print.to.stream, print.set->reset, line_first, print.set->warning, print.set->warning);
    fl_print_format("%[%i%]", print.to.stream, print.set->notable, signal, print.set->notable);
    fl_print_format("%[.%]%r", print.to.stream, print.set->warning, print.set->warning, f_string_eol_s);

    funlockfile(print.to.stream);

    return F_none;
  }
#endif // _di_fll_program_print_signal_received_

#ifndef _di_fll_program_print_version_
  f_status_t fll_program_print_version(const fl_print_t print, const f_string_static_t version) {

    f_print_dynamic(version, print.to.stream);
    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    return F_none;
  }
#endif // _di_fll_program_print_version_

#ifdef __cplusplus
} // extern "C"
#endif
