#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_basic_print_help_
  f_status_t fss_write_basic_print_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_write_basic_program_name_long_s, fss_write_program_version_s);

    fss_write_print_message_help(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_write_basic_program_name_s, f_string_empty_s);

    fss_write_print_message_help_pipe(print);

    fss_write_print_message_help_end_next(print);

    fl_print_format("%r  The FSS-0000 (Basic) specification does not support multi-line Content, therefore the parameter '%[%r%r%]'", print->to, f_string_eol_s, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_prepend_s, print->set->notable);
    fl_print_format(" does nothing.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program does not use the parameter '%[%r%r%]', which therefore does nothing.%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_ignore_s, print->set->notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%r", print->to, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_write_basic_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
