#include "../byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_print_error_
  f_status_t byte_dump_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((byte_dump_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_byte_dump_print_error_

#ifndef _di_byte_dump_print_error_file_
  f_status_t byte_dump_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    byte_dump_main_t * const main = (byte_dump_main_t *) print->custom;

    fll_error_file_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_byte_dump_print_error_file_

#ifndef _di_fll_program_print_error_file_code_invalid_
  f_status_t fll_program_print_error_file_code_invalid(fl_print_t * const print, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%r%[Invalid UTF-8 codes were detected for file '%]", print->to, f_string_eol_s, print->set->error, print->set->error);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, name.used ? name : f_string_ascii_minus_s, print->set->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fll_program_print_error_file_code_invalid_

#ifndef _di_byte_dump_print_error_file_none_
  f_status_t byte_dump_print_error_file_none(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QNo files are specified, please pipe data or designate a file.%]%r", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_okay;
  }
#endif // _di_byte_dump_print_error_file_none_

#ifndef _di_fll_program_print_error_file_read_
  f_status_t fll_program_print_error_file_read(fl_print_t * const print, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%Qread() failed for '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, name.used ? name : f_string_ascii_minus_s, print->set->notable);
    fl_print_format("%['.%]%r%r", print->to, print->set->error, print->set->error, f_string_eol_s, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fll_program_print_error_file_read_

#ifndef _di_fll_program_print_error_parameter_first_greater_than_last_
  f_status_t fll_program_print_error_parameter_first_greater_than_last(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    byte_dump_main_t * const main = (byte_dump_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe value '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%ul%]", print->to, print->set->notable, main->setting.first, print->set->notable);
    fl_print_format("%[' for the parameter '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%r%r%]", print->to, print->set->notable, f_console_symbol_long_normal_s, byte_dump_long_first_s, print->set->notable);
    fl_print_format("%[' cannot be greater than the value '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%ul%]", print->to, print->set->notable, main->setting.last, print->set->notable);
    fl_print_format("%[' for the parameter '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%r%r%]", print->to, print->set->notable, f_console_symbol_long_normal_s, byte_dump_long_last_s, print->set->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fll_program_print_error_parameter_first_greater_than_last_

#ifndef _di_byte_dump_print_error_parameter_range_out_
  f_status_t byte_dump_print_error_parameter_range_out(fl_print_t * const print, const f_string_static_t name, const f_number_unsigned_t minimum, const f_number_unsigned_t maximum, const f_string_static_t number) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe value '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, number, print->set->notable);
    fl_print_format("%[' for the parameter '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%r%Q%]", print->to, print->set->notable, f_console_symbol_long_normal_s, name, print->set->notable);
    fl_print_format("%[' can only be a number (inclusively) between %]", print->to, print->set->error, print->set->error);
    fl_print_format("%[ul%]", print->to, print->set->notable, minimum, print->set->notable);
    fl_print_format(" %[and%] ", print->to, print->set->error, print->set->error);
    fl_print_format("%[ul%]", print->to, print->set->notable, maximum, print->set->notable);
    fl_print_format(f_string_format_sentence_end_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_byte_dump_print_error_parameter_range_out_

#ifdef __cplusplus
} // extern "C"
#endif
