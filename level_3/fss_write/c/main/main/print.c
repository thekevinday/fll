#include "../fss_write.h"
#include "print.h"
#include "../../basic/fss_write.h"
#include "../../basic_list/fss_write.h"
#include "../../extended/fss_write.h"
#include "../../extended_list/fss_write.h"
#include "../../embedded_list/fss_write.h"
#include "../../payload/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_main_print_error_format_unknown_
  f_status_t fss_write_main_print_error_format_unknown(fl_print_t * const print, const f_string_static_t value) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe format '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, value, print->set->notable);
    fl_print_format("%[' is not known for the parameter%] ", print->to, print->set->error, print->set->error);
    fl_print_format("%[%Q%Q%]", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_as_s, print->set->notable);
    fl_print_format("%[.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_write_main_print_error_format_unknown_

#ifndef _di_fss_write_main_main_print_help_
  f_status_t fss_write_main_print_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_write_program_name_long_s, fss_write_program_version_s);

    fss_write_print_message_help(print);

    fll_program_print_help_option(print, fss_write_short_as_s, fss_write_long_as_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Designate the supported format to write as.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_write_program_name_s, f_string_empty_s);

    fss_write_print_message_help_pipe(print);

    fss_write_print_message_help_end_next(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fl_print_format("  The '%[%r%r%]' parameter supports the following standards with the specified possible case-sensitive values:%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_as_s, print->set->notable, f_string_eol_s);

    // FSS-0000 (Basic)
    fl_print_format("    - As %[%r%]         format: ", print->to, print->set->notable, fss_write_basic_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_write_format_code_short_0000_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_write_format_code_long_0000_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_write_format_code_human_0000_s, print->set->notable, f_string_eol_s);

    // FSS-0001 (Extended)
    fl_print_format("    - As %[%r%]      format: ", print->to, print->set->notable, fss_write_extended_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_write_format_code_short_0001_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_write_format_code_long_0001_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_write_format_code_human_0001_s, print->set->notable, f_string_eol_s);

    // FSS-0002 (Basic List)
    fl_print_format("    - As %[%r%]    format: ", print->to, print->set->notable, fss_write_basic_list_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_write_format_code_short_0002_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_write_format_code_long_0002_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_write_format_code_human_0002_s, print->set->notable, f_string_eol_s);

    // FSS-0003 (Extended List)
    fl_print_format("    - As %[%r%] format: ", print->to, print->set->notable, fss_write_extended_list_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_write_format_code_short_0003_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_write_format_code_long_0003_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_write_format_code_human_0003_s, print->set->notable, f_string_eol_s);

    // FSS-0008 (Embedded List)
    fl_print_format("    - As %[%r%] format: ", print->to, print->set->notable, fss_write_embedded_list_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_write_format_code_short_0008_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_write_format_code_long_0008_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_write_format_code_human_0008_s, print->set->notable, f_string_eol_s);

    // FSS-000E (Payload)
    fl_print_format("    - As %[%r%]       format: ", print->to, print->set->notable, fss_write_payload_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_write_format_code_short_000e_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_write_format_code_long_000e_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_write_format_code_human_000e_s, print->set->notable, f_string_eol_s);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fl_print_format("  The %[%r%] format is the default when no ", print->to, print->set->notable, fss_write_basic_standard_s, print->set->notable);
    fl_print_format("'%[%r%r%]' is specified.%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_write_long_as_s, print->set->notable, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_fss_write_main_main_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
