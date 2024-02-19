#include "../example.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_example_print_message_help_
  f_status_t example_print_message_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, example_program_name_long_s, example_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, example_short_example_s, example_long_example_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "This is an example program parameter.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, example_program_name_s, f_string_empty_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_example_print_message_help_


#ifdef __cplusplus
} // extern "C"
#endif
