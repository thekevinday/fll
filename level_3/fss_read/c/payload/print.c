#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_payload_print_data_object_end_
  f_status_t fss_read_payload_print_data_object_end(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom;

    f_file_stream_lock(print->to);

    if (main->setting.flag & fss_read_main_flag_pipe_format_e) {
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

    return F_okay;
  }
#endif // _di_fss_read_payload_print_data_object_end_

#ifndef _di_fss_read_payload_print_error_parameter_value_payload_
  f_status_t fss_read_payload_print_error_parameter_value_payload(fl_print_t * const print, const f_string_static_t value) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe parameter '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_rr_single_s.string, print->to, print->notable, f_console_symbol_long_normal_s, fss_read_long_payload_s, print->notable);
    fl_print_format("%[' has the value '%]", print->to, print->context, print->context);
    fl_print_format("%[%Q%]", print->to, print->notable, value, print->notable);
    fl_print_format("%[' but must only be one of: '%]", print->to, print->context, print->context);
    fl_print_format("%[%Q%]", print->to, print->notable, fss_read_string_create_s, print->notable);
    fl_print_format("%[', '%]", print->to, print->context, print->context);
    fl_print_format("%[%Q%]", print->to, print->notable, fss_read_string_error_s, print->notable);
    fl_print_format("%[', '%]", print->to, print->context, print->context);
    fl_print_format("%[%Q%]", print->to, print->notable, fss_read_string_none_s, print->notable);
    fl_print_format("%[', and '%]", print->to, print->context, print->context);
    fl_print_format("%[%Q%]", print->to, print->notable, fss_read_string_warn_s, print->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_payload_print_error_parameter_value_payload_

#ifndef fss_read_payload_print_message_help
  f_status_t fss_read_payload_print_message_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_read_payload_program_name_long_s, fss_read_program_version_s);

    fss_read_print_message_help(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_read_payload_program_name_s, f_string_empty_s);

    fss_read_payload_print_message_help_special(print);

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

    fss_read_payload_print_message_help_payload(print);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_payload_print_message_help_

#ifndef _di_fss_read_payload_print_message_help_payload_
  f_status_t fss_read_payload_print_message_help_payload(fl_print_t * const print) {

    if (!print || !print->set) return F_status_set_error(F_output_not);

    fl_print_format("%r  The parameter %[%r%r%] accepts the following:%r", print->to, f_string_eol_s, print->set->notable, f_console_symbol_long_normal_s, fss_read_long_payload_s, print->set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Create the payload Object if it is missing, but with empty Content.%r", print->to, print->set->notable, fss_read_string_create_s, print->set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Do nothing special with payload Object is missing.%r", print->to, print->set->notable, fss_read_string_none_s, print->set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Print error and exit as an error when payload Object is missing.%r", print->to, print->set->notable, fss_read_string_error_s, print->set->notable, f_string_eol_s);
    fl_print_format("  - %[%r%]: Print warning but continue when payload Object is missing.%r", print->to, print->set->notable, fss_read_string_warn_s, print->set->notable, f_string_eol_s);

    return F_okay;
  }
#endif // _di_fss_read_payload_print_message_help_payload_

#ifndef _di_fss_read_payload_print_message_help_special_
  f_status_t fss_read_payload_print_message_help_special(fl_print_t * const print) {

    if (!print || !print->set) return F_status_set_error(F_output_not);

    fl_print_format("%r %[Special Options:%] %r", print->to, f_string_eol_s, print->set->important, print->set->important, f_string_eol_s);

    fll_program_print_help_option_long(print, fss_read_long_payload_s, f_console_symbol_long_normal_s, "Specify custom actions to perform when payload Object is missing.");

    return F_okay;
  }
#endif // _di_fss_read_payload_print_message_help_special_

#ifndef fss_read_payload_print_problem_payload_missing
  f_status_t fss_read_payload_print_problem_payload_missing(fl_print_t * const print) {

    if (!print || print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QDid not find the required %]", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_r_single_s.string, print->to, print->notable, f_fss_payload_s, print->notable);
    fl_print_format(" %[Object.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_payload_print_problem_payload_missing_

#ifdef __cplusplus
} // extern "C"
#endif
