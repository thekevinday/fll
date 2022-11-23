#include "extended_list.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_extended_list_print_help_
  f_status_t fss_write_extended_list_print_help(fss_write_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, fss_write_program_name_long_s, fss_write_program_version_s);

    fss_write_print_help(setting, print);

    fll_program_print_help_usage(print, fss_write_program_name_s, f_string_empty_s);

    // @todo

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fss_write_extended_list_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
