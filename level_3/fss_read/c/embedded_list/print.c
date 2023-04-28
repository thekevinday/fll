#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_embedded_list_print_help_
  f_status_t fss_read_embedded_list_print_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_read_embedded_list_program_name_long_s, fss_read_program_version_s);

    fss_read_print_message_help(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_read_embedded_list_program_name_s, f_string_empty_s);

    fss_read_print_message_help_note_header(print, fss_read_format_code_short_0008_s, fss_read_format_code_name_0008_s);

    fss_read_print_message_help_pipe(print);

    fss_read_print_message_help_note(print, F_true);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_embedded_list_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
