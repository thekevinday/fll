#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_payload_print_error_payload_not_last_
  f_status_t fss_read_payload_print_error_payload_not_last(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (!print || print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_print_format("%r%[%QThe payload may only be specified last.%]%r", print->to, f_string_eol_s, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_read_payload_print_error_payload_not_last_

#ifndef _di_fss_read_payload_print_help_
  f_status_t fss_read_payload_print_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_read_payload_program_name_long_s, fss_read_program_version_s);

    fss_read_print_message_help(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_read_payload_program_name_s, f_string_empty_s);

    fss_read_print_message_help_pipe(print);

    fss_read_print_message_help_note(print, F_true);

    fl_print_format("%r  As an exceptional case, a %[%r%r%] of", print->to, f_string_eol_s, print->set->notable, f_console_symbol_long_normal_s, fss_read_long_depth_s, print->set->notable);
    fl_print_format(" %[1%] applies only to the explicit Object of", print->to, print->set->notable, print->set->notable);
    fl_print_format(" '%[%r%]'.%r", print->to, print->set->notable, f_fss_header_s, print->set->notable, f_string_eol_s);
    fl_print_format("  Content at this depth is processed as FSS-0001 (Extended).%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The Content of the explicit Object of", print->to);
    fl_print_format(" '%[%r%]'", print->to, print->set->notable, f_fss_payload_s, print->set->notable, f_string_eol_s);
    fl_print_format(" will not contain any Content close pipe control codes when using", print->to);
    fl_print_format(" %[%r%r%].%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_read_long_pipe_s, print->set->notable, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_payload_print_help_

#ifndef _di_fss_read_payload_print_object_end_
  f_status_t fss_read_payload_print_object_end(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;


    f_file_stream_lock(print->to);

    if (main->setting.flag & fss_read_main_flag_pipe_e) {
      f_print_dynamic_raw(fss_read_pipe_content_start_s, print->to);
    }
    else {
      if (main->setting.flag & fss_read_main_flag_content_e) {
        f_print_dynamic_raw(f_fss_payload_list_open_s, print->to);
        f_print_dynamic_raw(f_fss_payload_list_open_end_s, print->to);
      }
      else {
        f_print_dynamic_raw(f_fss_eol_s, print->to);
      }
    }

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_read_payload_print_object_end_

#ifdef __cplusplus
} // extern "C"
#endif
