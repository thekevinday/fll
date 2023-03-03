#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_error_
  f_status_t utf8_print_error(utf8_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e);

    return F_none;
  }
#endif // _di_utf8_print_error_

#ifndef _di_utf8_print_error_decode_
  f_status_t utf8_print_error_decode(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t invalid) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;
    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    fl_print_format("%[%QFailed to decode character code '%]", print.to, print.set->error, print.prefix, print.set->error);

    if (invalid.used) {
      fl_print_format("%[0x", print.to, print.set->notable);

      for (uint8_t i = 0; i < invalid.used; ++i) {
        fl_print_format("%02_uii", print.to, (uint8_t) invalid.string[i]);
      } // for

      fl_print_format("%]", print.to, print.set->notable);
    }

    if (F_status_set_fine(setting->state.status) == F_utf_not) {
      fl_print_format("%[', not a valid UTF-8 character sequence.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);
    }
    else if (F_status_set_fine(setting->state.status) == F_complete_not_utf) {
      fl_print_format("%[', invalid UTF-8 (truncated).%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);
    }
    else if (F_status_set_fine(setting->state.status) == F_utf_fragment) {
      fl_print_format("%[', invalid UTF-8 fragment.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);
    }
    else {
      fl_print_format("%[', error status code%] ", print.to, print.set->error, print.set->error, f_string_eol_s);
      fl_print_format("%[%ui%]", print.to, print.set->notable, F_status_set_fine(setting->state.status), print.set->notable);
      fl_print_format("%[.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);
    }

    return F_none;
  }
#endif // _di_utf8_print_error_decode_

#ifndef _di_utf8_print_error_encode_
  f_status_t utf8_print_error_encode(utf8_setting_t * const setting, const fl_print_t print, const uint32_t codepoint) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;
    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    fl_print_format("%[%QFailed to encode Unicode codepoint '%]", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[U+%_U%]", print.to, print.set->notable, codepoint, print.set->notable);

    if (F_status_set_fine(setting->state.status) == F_utf_not) {
      fl_print_format("%[', not a valid Unicode codepoint.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);
    }
    else {
      fl_print_format("%[', error status code%] ", print.to, print.set->error, print.set->error, f_string_eol_s);
      fl_print_format("%[%ui%]", print.to, print.set->notable, F_status_set_fine(setting->state.status), print.set->notable);
      fl_print_format("%[.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);
    }

    return F_none;
  }
#endif // _di_utf8_print_error_encode_

#ifndef _di_utf8_print_error_file_
  f_status_t utf8_print_error_file(utf8_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_none;
  }
#endif // _di_utf8_print_error_file_

#ifndef _di_utf8_print_error_no_from_
  f_status_t utf8_print_error_no_from(utf8_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QNo from sources are specified, please pipe data, designate a file, or add parameters.%]%r", print.to, print.set->error, print.prefix, print.set->error, f_string_eol_s);

    return F_none;
  }
#endif // _di_utf8_print_error_no_from_

#ifndef _di_utf8_print_error_parameter_file_name_empty_
  f_status_t utf8_print_error_parameter_file_name_empty(utf8_setting_t * const setting, const fl_print_t print, const f_array_length_t index) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QNo file specified at parameter index%] ", print.to, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%ul%]", print.to, print.set->notable, index, print.set->notable);
    fl_print_format("%[.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_utf8_print_error_parameter_file_name_empty_

#ifndef _di_utf8_print_error_parameter_file_not_found_
  f_status_t utf8_print_error_parameter_file_not_found(utf8_setting_t * const setting, const fl_print_t print, const bool from, const f_string_static_t name) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QFailed to find the %r file '%]", print.to, print.set->error, print.prefix, from ? utf8_string_from_s : utf8_string_to_s, print.set->error);
    fl_print_format("%[%Q%]", print.to, print.set->notable, name, print.set->notable);
    fl_print_format("%['.%]%r", print.to, print.set->error, print.set->error, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_utf8_print_error_parameter_file_not_found_

#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  f_status_t utf8_print_error_parameter_file_to_too_many(utf8_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    utf8_print_line_first(setting, print);

    fll_print_format("%[%QToo many '%r' files specified, there may only be one '%r' file.%]%r", print.to, print.set->error, print.prefix, utf8_string_to_s, utf8_string_to_s, print.set->error, f_string_eol_s);

    return F_none;
  }
#endif // _di_utf8_print_error_parameter_file_to_too_many_

#ifdef __cplusplus
} // extern "C"
#endif
