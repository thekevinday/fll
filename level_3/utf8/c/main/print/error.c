#include "../utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_error_
  f_status_t utf8_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((utf8_main_t *) print->custom)->setting.state.status), function, fll_error_file_flag_fallback_e);

    return F_okay;
  }
#endif // _di_utf8_print_error_

#ifndef _di_utf8_print_error_decode_
  f_status_t utf8_print_error_decode(fl_print_t * const print, const f_string_static_t invalid) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    utf8_main_t * const main = (utf8_main_t *) print->custom;

    if (main->setting.flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    fl_print_format("%[%QFailed to decode character code '%]", print->to, print->set->error, print->prefix, print->set->error);

    if (invalid.used) {
      fl_print_format("%[0x", print->to, print->set->notable);

      for (uint8_t i = 0; i < invalid.used; ++i) {
        fl_print_format("%02_uii", print->to, (uint8_t) invalid.string[i]);
      } // for

      fl_print_format("%]", print->to, print->set->notable);
    }

    if (F_status_set_fine(main->setting.state.status) == F_utf_not) {
      fl_print_format("%[', not a valid UTF-8 character sequence.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);
    }
    else if (F_status_set_fine(main->setting.state.status) == F_complete_not_utf) {
      fl_print_format("%[', invalid UTF-8 (truncated).%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);
    }
    else if (F_status_set_fine(main->setting.state.status) == F_utf_fragment) {
      fl_print_format("%[', invalid UTF-8 fragment.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);
    }
    else {
      fl_print_format("%[', error status code%] ", print->to, print->set->error, print->set->error, f_string_eol_s);
      fl_print_format("%[%ui%]", print->to, print->set->notable, F_status_set_fine(main->setting.state.status), print->set->notable);
      fl_print_format(f_string_format_sentence_end_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);
    }

    return F_okay;
  }
#endif // _di_utf8_print_error_decode_

#ifndef _di_utf8_print_error_encode_
  f_status_t utf8_print_error_encode(fl_print_t * const print, const uint32_t codepoint) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    utf8_main_t * const main = (utf8_main_t *) print->custom;

    if (main->setting.flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    fl_print_format("%[%QFailed to encode Unicode codepoint '%]", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[U+%_U%]", print->to, print->set->notable, codepoint, print->set->notable);

    if (F_status_set_fine(main->setting.state.status) == F_utf_not) {
      fl_print_format("%[', not a valid Unicode codepoint.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);
    }
    else {
      fl_print_format("%[', error status code%] ", print->to, print->set->error, print->set->error, f_string_eol_s);
      fl_print_format("%[%ui%]", print->to, print->set->notable, F_status_set_fine(main->setting.state.status), print->set->notable);
      fl_print_format(f_string_format_sentence_end_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);
    }

    return F_okay;
  }
#endif // _di_utf8_print_error_encode_

#ifndef _di_utf8_print_error_file_
  f_status_t utf8_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    utf8_main_t * const main = (utf8_main_t *) print->custom;

    fll_error_file_print(print, F_status_set_fine(main->setting.state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_okay;
  }
#endif // _di_utf8_print_error_file_

#ifndef _di_utf8_print_error_no_from_
  f_status_t utf8_print_error_no_from(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QNo from sources are specified, please pipe data, designate a file, or add parameters.%]%r", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_okay;
  }
#endif // _di_utf8_print_error_no_from_

#ifndef _di_utf8_print_error_parameter_file_name_empty_
  f_status_t utf8_print_error_parameter_file_name_empty(fl_print_t * const print, const f_number_unsigned_t index) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QNo file specified at parameter index%] ", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%ul%]", print->to, print->set->notable, index, print->set->notable);
    fl_print_format(f_string_format_sentence_end_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_utf8_print_error_parameter_file_name_empty_

#ifndef _di_utf8_print_error_parameter_file_not_found_
  f_status_t utf8_print_error_parameter_file_not_found(fl_print_t * const print, const bool from, const f_string_static_t name) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QFailed to find the %r file '%]", print->to, print->set->error, print->prefix, from ? utf8_string_from_s : utf8_string_to_s, print->set->error);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, name, print->set->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_utf8_print_error_parameter_file_not_found_

#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  f_status_t utf8_print_error_parameter_file_to_too_many(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QToo many '%r' files specified, there may only be one '%r' file.%]%r", print->to, print->set->error, print->prefix, utf8_string_to_s, utf8_string_to_s, print->set->error, f_string_eol_s);

    return F_okay;
  }
#endif // _di_utf8_print_error_parameter_file_to_too_many_

#ifdef __cplusplus
} // extern "C"
#endif
