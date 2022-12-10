#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_basic_list_print_help_
  f_status_t fss_write_basic_list_print_help(fss_write_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, setting->program_name_long ? *setting->program_name_long : fss_write_program_name_long_s, fss_write_program_version_s);

    fss_write_print_help(setting, print);

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, setting->program_name ? *setting->program_name : fss_write_program_name_s, f_string_empty_s);

    fss_write_print_help_pipe(setting, print);

    fl_print_format("%r  The FSS-0002 (Basic List) specification does not support quoted names, therefore the parameters '%[%r%r%]'", print.to, f_string_eol_s, print.set->notable, f_console_symbol_long_normal_s, fss_write_long_single_s, print.set->notable);
    fl_print_format(" and '%[%r%r%]' do nothing.%r%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_write_long_double_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program does not use the parameter '%[%r%r%]', which therefore does nothing.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fss_write_long_ignore_s, print.set->notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%r", print.to, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_write_basic_list_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
