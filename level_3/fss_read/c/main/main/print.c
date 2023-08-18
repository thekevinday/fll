#include "../fss_read.h"
#include "print.h"
#include "../../basic/fss_read.h"
#include "../../basic_list/fss_read.h"
#include "../../extended/fss_read.h"
#include "../../extended_list/fss_read.h"
#include "../../embedded_list/fss_read.h"
#include "../../payload/fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_main_print_error_format_unknown_
  f_status_t fss_read_main_print_error_format_unknown(fl_print_t * const print, const f_string_static_t value) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe format '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, value, print->set->notable);
    fl_print_format("%[' is not known for the parameter%] ", print->to, print->set->error, print->set->error);
    fl_print_format("%[%Q%Q%]", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_read_long_as_s, print->set->notable);
    fl_print_format("%[.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_main_print_error_format_unknown_

#ifndef _di_fss_read_main_main_print_help_
  f_status_t fss_read_main_print_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fss_read_program_name_long_s, fss_read_program_version_s);

    fss_read_print_message_help(print);

    fll_program_print_help_option(print, fss_read_short_as_s, fss_read_long_as_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "      Designate the supported format to read as.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fss_read_program_name_s, f_string_empty_s);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fss_read_print_message_help_note_header(print, f_string_empty_s, f_string_empty_s);

    fss_read_print_message_help_pipe(print);

    fss_read_print_message_help_note(print, F_false);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    // @todo everything below needs to be reviewed and updated as appropriate.

    fl_print_format("  The '%[%r%r%]' parameter supports the following standards with the specified possible case-sensitive values:%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_read_long_as_s, print->set->notable, f_string_eol_s);

    // FSS-0000 (Basic)
    fl_print_format("    - As %[%r%]         format: ", print->to, print->set->notable, fss_read_basic_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_short_0000_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_read_format_code_long_0000_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_read_format_code_machine_0000_s, print->set->notable, f_string_eol_s);

    // FSS-0001 (Extended)
    fl_print_format("    - As %[%r%]      format: ", print->to, print->set->notable, fss_read_extended_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_short_0001_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_read_format_code_long_0001_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_read_format_code_machine_0001_s, print->set->notable, f_string_eol_s);

    // FSS-0002 (Basic List)
    fl_print_format("    - As %[%r%]    format: ", print->to, print->set->notable, fss_read_basic_list_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_short_0002_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_long_0002_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_read_format_code_human_0002_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_read_format_code_machine_0002_s, print->set->notable, f_string_eol_s);

    // FSS-0003 (Extended List)
    fl_print_format("    - As %[%r%] format: ", print->to, print->set->notable, fss_read_extended_list_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_short_0003_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_read_format_code_long_0003_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_human_0003_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_read_format_code_machine_0003_s, print->set->notable, f_string_eol_s);

    // FSS-0008 (Embedded List)
    fl_print_format("    - As %[%r%] format: ", print->to, print->set->notable, fss_read_embedded_list_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_short_0008_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_long_0008_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_read_format_code_human_0008_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_read_format_code_machine_0008_s, print->set->notable, f_string_eol_s);

    // FSS-000E (Payload)
    fl_print_format("    - As %[%r%]       format: ", print->to, print->set->notable, fss_read_payload_standard_s, print->set->notable);
    fl_print_format("'%[%r%]', ", print->to, print->set->notable, fss_read_format_code_short_000e_s, print->set->notable);
    fl_print_format("'%[%r%]', or ", print->to, print->set->notable, fss_read_format_code_long_000e_s, print->set->notable);
    fl_print_format("'%[%r%]'.%r", print->to, print->set->notable, fss_read_format_code_machine_000e_s, print->set->notable, f_string_eol_s);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fl_print_format("  The %[%r%] format is the default when no ", print->to, print->set->notable, fss_read_basic_standard_s, print->set->notable);
    fl_print_format("'%[%r%r%]' is specified.%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fss_read_long_as_s, print->set->notable, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_read_main_main_print_help_

#ifdef __cplusplus
} // extern "C"
#endif
