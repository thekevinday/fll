#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_extended_list_print_help_
  f_status_t fss_read_extended_list_print_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_read_extended_list_program_name_long_s, fss_read_program_version_s);

    fss_read_print_message_help(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_read_extended_list_program_name_s, f_string_empty_s);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fss_read_print_message_help_note_header(print, fss_read_format_code_short_0003_s, fss_read_format_code_name_0003_s);

    fss_read_print_message_help_pipe(print);

    fss_read_print_message_help_note(print, F_true);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_extended_list_print_help_

#ifndef _di_fss_read_extended_list_print_object_end_
  f_status_t fss_read_extended_list_print_object_end(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    f_file_stream_lock(print->to);

    if (main->setting.flag & fss_read_main_flag_pipe_format_e) {
      f_print_dynamic_raw(fss_read_pipe_content_start_s, print->to);
    }
    else {
      if (main->setting.flag & fss_read_main_flag_content_e) {
        f_print_dynamic_raw(f_fss_extended_list_open_s, print->to);
        f_print_dynamic_raw(f_fss_extended_list_open_end_s, print->to);
      }
      else {
        f_print_dynamic_raw(f_fss_eol_s, print->to);
      }
    }

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_extended_list_print_object_end_

#ifndef _di_fss_read_extended_list_print_set_end_
  f_status_t fss_read_extended_list_print_set_end(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    if ((main->setting.flag & fss_read_main_flag_object_e) && main->setting.flag & fss_read_main_flag_content_e) {
      f_print_dynamic_raw(f_fss_extended_list_close_s, print->to);
      f_print_dynamic_raw(f_fss_extended_list_close_end_s, print->to);
    }

    return F_none;
  }
#endif // _di_fss_read_extended_list_print_set_end_

#ifdef __cplusplus
} // extern "C"
#endif
