#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_extended_list_print_help_
  f_status_t fss_write_extended_list_print_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_write_extended_list_program_name_long_s, fss_write_program_version_s);

    fss_write_print_message_help(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_write_extended_list_program_name_s, f_string_empty_s);

    fss_write_print_message_help_pipe(print);

    fss_write_print_message_help_end_next(print);

    fl_print_format("%r  The FSS-0003 (Extended List) specification does not support quoted names, therefore the parameters '%[%r%r%]'", print->to, f_string_eol_s, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_single_s, print->set->notable);
    fl_print_format(" and '%[%r%r%]' do nothing.%r%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_double_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter '%[%r%r%]' designates to not escape any valid nested Object or Content within some Content.%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_ignore_s, print->set->notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%r", print->to, f_string_eol_s);
    fl_print_format("  This parameter is not used for ignoring anything from the input pipe.%r", print->to, f_string_eol_s);
    fl_print_format("  This parameter must be specified after a '%[%r%r%]'", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_content_s, print->set->notable);
    fl_print_format(" parameter and this applies only to the Content represented by that specific '%[%r%r%]' parameter.%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_content_s, print->set->notable, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_write_extended_list_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
