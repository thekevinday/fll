#include "utf8.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_bytesequence_
  f_status_t utf8_print_bytesequence(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t sequence) {

    fl_print_format("%r%r%r", main->output.to, setting->prepend, sequence, setting->append);

    return F_none;
  }
#endif // _di_utf8_print_bytesequence_

#ifndef _di_utf8_print_character_invalid_
  f_status_t utf8_print_character_invalid(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t invalid) {

    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;
    if (!invalid.used) return F_output_not;

    if ((setting->mode & utf8_mode_to_combining_e) || (setting->mode & utf8_mode_to_width_e)) {
      utf8_print_combining_or_width(main, setting, invalid);
    }
    else if (setting->mode & utf8_mode_to_bytesequence_e) {
      fl_print_format("%r%[%r%]%r", main->output.to, setting->prepend, setting->valid_not, invalid, setting->valid_not, setting->append);
    }
    else if (setting->mode & utf8_mode_from_codepoint_e) {
      fl_print_format("%r%[%Q%]%r", main->output.to, setting->prepend, setting->valid_not, invalid, setting->valid_not, setting->append);
    }
    else {
      fl_print_format("%r%[0x", main->output.to, setting->prepend, setting->valid_not);

      for (uint8_t i = 0; i < invalid.used; ++i) {
        fl_print_format("%02_uii", main->output.to, (uint8_t) invalid.string[i]);
      } // for

      fl_print_format("%]%r", main->output.to, setting->valid_not, setting->append);
    }

    return F_none;
  }
#endif // _di_utf8_print_character_invalid_

#ifndef _di_utf8_print_codepoint_
  f_status_t utf8_print_codepoint(fll_program_data_t * const main, utf8_setting_t * const setting, const uint32_t codepoint) {

    if (codepoint < 0x10000) {
      fl_print_format("%rU+%04_U%r", main->output.to, setting->prepend, codepoint, setting->append);
    }
    else if (codepoint < 0x100000) {
      fl_print_format("%rU+%05_U%r", main->output.to, setting->prepend, codepoint, setting->append);
    }
    else {
      fl_print_format("%rU+%06_U%r", main->output.to, setting->prepend, codepoint, setting->append);
    }

    return F_none;
  }
#endif // _di_utf8_print_codepoint_

#ifndef _di_utf8_print_combining_or_width_
  f_status_t utf8_print_combining_or_width(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t sequence) {

    if (setting->mode & utf8_mode_to_combining_e) {
      f_status_t status = f_utf_is_combining(sequence.string, sequence.used);

      if (status == F_true) {
        fl_print_format("%r%r%r", main->output.to, setting->prepend, utf8_string_combining_is_s, setting->append);
      }
      else if (status == F_false) {
        status = f_utf_is_private(sequence.string, sequence.used);

        if (status == F_true) {
          fl_print_format("%r%r%r", main->output.to, setting->prepend, utf8_string_unknown_s, setting->append);
        }
        else if (setting->mode & utf8_mode_to_width_e) {
          utf8_print_width(main, setting, sequence);
        }
        else {
          fl_print_format("%r%r%r", main->output.to, setting->prepend, utf8_string_combining_not_s, setting->append);
        }
      }
      else {
        utf8_print_error_combining_or_width(main, setting);
      }
    }
    else if (setting->mode & utf8_mode_to_width_e) {
      utf8_print_width(main, setting, sequence);
    }

    return F_none;
  }
#endif // _di_utf8_print_combining_or_width_

#ifndef _di_utf8_print_error_combining_or_width_
  f_status_t utf8_print_error_combining_or_width(fll_program_data_t * const main, utf8_setting_t * const setting) {

    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    fl_print_format("%r%[%r%]%r", main->output.to, setting->prepend, setting->valid_not, utf8_string_unknown_s, setting->valid_not, setting->append);

    return F_none;
  }
#endif // _di_utf8_print_error_combining_or_width_

#ifndef _di_utf8_print_error_decode_
  f_status_t utf8_print_error_decode(fll_program_data_t * const main, utf8_setting_t * const setting, const f_status_t status, const f_string_static_t invalid) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    utf8_print_line_first_unlocked(setting, main->error);

    fl_print_format("%[%QFailed to decode character code '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);

    if (invalid.used) {
      fl_print_format("%[0x", main->error.to, main->context.set.notable);

      for (uint8_t i = 0; i < invalid.used; ++i) {
        fl_print_format("%02_uii", main->error.to, (uint8_t) invalid.string[i]);
      } // for

      fl_print_format("%]", main->error.to, main->context.set.notable);
    }

    if (F_status_set_fine(status) == F_utf_not) {
      fl_print_format("%[', not a valid UTF-8 character sequence.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    }
    else if (F_status_set_fine(status) == F_complete_not_utf) {
      fl_print_format("%[', invalid UTF-8 (truncated).%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    }
    else if (F_status_set_fine(status) == F_utf_fragment) {
      fl_print_format("%[', invalid UTF-8 fragment.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    }
    else {
      fl_print_format("%[', error status code%] ", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
      fl_print_format("%[%ui%]", main->error.to, main->context.set.notable, F_status_set_fine(status), main->context.set.notable);
      fl_print_format("%[.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    }

    return F_none;
  }
#endif // _di_utf8_print_error_decode_

#ifndef _di_utf8_print_error_encode_
  f_status_t utf8_print_error_encode(fll_program_data_t * const main, utf8_setting_t * const setting, const f_status_t status, const uint32_t codepoint) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    utf8_print_line_first_unlocked(setting, main->error);

    fl_print_format("%[%QFailed to encode Unicode codepoint '%]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[U+%_U%]", main->error.to, main->context.set.notable, codepoint, main->context.set.notable);

    if (F_status_set_fine(status) == F_utf_not) {
      fl_print_format("%[', not a valid Unicode codepoint.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    }
    else {
      fl_print_format("%[', error status code%] ", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
      fl_print_format("%[%ui%]", main->error.to, main->context.set.notable, F_status_set_fine(status), main->context.set.notable);
      fl_print_format("%[.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);
    }

    return F_none;
  }
#endif // _di_utf8_print_error_encode_

#ifndef _di_utf8_print_error_no_from_
  f_status_t utf8_print_error_no_from(fll_program_data_t * const main, utf8_setting_t * const setting) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    utf8_print_line_first_locked(setting, main->error);

    fll_print_format("%[%QNo from sources are specified, please pipe data, designate a file, or add parameters.%]%r", main->error.to, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);

    return F_none;
  }
#endif // _di_utf8_print_error_no_from_

#ifndef _di_utf8_print_error_parameter_file_name_empty_
  f_status_t utf8_print_error_parameter_file_name_empty(fll_program_data_t * const main, utf8_setting_t * const setting, const f_array_length_t index) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(main->error.to);

    utf8_print_line_first_unlocked(setting, main->error);

    fl_print_format("%[%QNo file specified at parameter index %]", main->error.to, main->context.set.error, main->error.prefix, main->context.set.error);
    fl_print_format("%[%ul%]", main->error.to, main->context.set.notable, index, main->context.set.notable);
    fl_print_format("%[.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);

    return F_none;
  }
#endif // _di_utf8_print_error_parameter_file_name_empty_

#ifndef _di_utf8_print_error_parameter_file_not_found_
  f_status_t utf8_print_error_parameter_file_not_found(fll_program_data_t * const main, utf8_setting_t * const setting, const bool from, const f_string_static_t name) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(main->error.to);

    utf8_print_line_first_unlocked(setting, main->error);

    fl_print_format("%[%QFailed to find the %r file '%]", main->error.to, main->context.set.error, main->error.prefix, from ? utf8_string_from_s : utf8_string_to_s, main->context.set.error);
    fl_print_format("%[%Q%]", main->error.to, main->context.set.notable, name, main->context.set.notable);
    fl_print_format("%['.%]%r", main->error.to, main->context.set.error, main->context.set.error, f_string_eol_s);

    f_file_stream_unlock(main->error.to);

    return F_none;
  }
#endif // _di_utf8_print_error_parameter_file_not_found_

#ifndef _di_utf8_print_error_parameter_file_to_too_many_
  f_status_t utf8_print_error_parameter_file_to_too_many(fll_program_data_t * const main, utf8_setting_t * const setting) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    utf8_print_line_first_locked(setting, main->error);

    fll_print_format("%[%QToo many '%r' files specified, there may only be one '%r' file.%]%r", main->error.to, main->context.set.error, main->error.prefix, utf8_string_to_s, utf8_string_to_s, main->context.set.error, f_string_eol_s);

    return F_none;
  }
#endif // _di_utf8_print_error_parameter_file_to_too_many_

#ifndef _di_utf8_print_flush_
  f_status_t utf8_print_flush(fll_program_data_t * const main, utf8_setting_t * const setting) {

    if (setting->flag & utf8_main_flag_verify_e) return F_output_not;

    if (setting->status == F_interrupt) {
      if (main->output.verbosity != f_console_verbosity_quiet_e) {
        f_file_stream_flush(main->output.to);
      }

      if (main->output.to.stream != main->message.to.stream) {
        if (main->message.verbosity != f_console_verbosity_quiet_e) {
          f_file_stream_flush(main->message.to);
        }
      }
    }

    return F_none;
  }
#endif // _di_utf8_print_flush_

#ifndef _di_utf8_print_help_
  f_status_t utf8_print_help(utf8_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, utf8_program_name_long_s, utf8_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, utf8_short_from_bytesequence_s, utf8_long_from_bytesequence_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The expected input format is byte sequence (character data).");
    fll_program_print_help_option(print, utf8_short_from_codepoint_s, utf8_long_from_codepoint_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The expected input format is codepoint (such as U+0000).");
    fll_program_print_help_option(print, utf8_short_from_file_s, utf8_long_from_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "        Use the given print.to as the input source.");

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, utf8_short_to_bytesequence_s, utf8_long_to_bytesequence_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The print.to format is byte sequence (character data).");
    fll_program_print_help_option(print, utf8_short_to_codepoint_s, utf8_long_to_codepoint_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The print.to format is codepoint (such as U+0000).");
    fll_program_print_help_option(print, utf8_short_to_combining_s, utf8_long_to_combining_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   The print.to format is to print whether or not character is combining or not.");
    fll_program_print_help_option(print, utf8_short_to_file_s, utf8_long_to_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "        Use the given print.to as the print.to destination.");
    fll_program_print_help_option(print, utf8_short_to_width_s, utf8_long_to_width_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       The print.to format is to print the width of a character (either 0, 1, or 2).");

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, utf8_short_headers_s, utf8_long_headers_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Print headers for each section (pipe, file, or parameter).");
    fll_program_print_help_option(print, utf8_short_separate_s, utf8_long_separate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Separate characters by newlines (implied when printing headers).");
    fll_program_print_help_option(print, utf8_short_strip_invalid_s, utf8_long_strip_invalid_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Strip invalid Unicode characters (do not print invalid sequences).");
    fll_program_print_help_option(print, utf8_short_verify_s, utf8_long_verify_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Only perform verification of valid sequences.");

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, utf8_program_name_s, utf8_program_help_parameters_s);

    fl_print_format("%r  The default behavior is to assume the expected input is byte sequence from the command line to be print.to to the screen as codepoints.%r%r", print.to, f_string_eol_s, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Multiple input sources are allowed but only a single print.to destination is allowed.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the parameter '%[%r%r%]', no data is printed and 0 is returned if valid or 1 is returned if invalid.%r%r", print.to, print.set->notable, f_console_symbol_long_enable_s, utf8_long_verify_s, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When using the parameter '%[%r%r%]' with the parameter ", print.to, print.set->notable, f_console_symbol_long_enable_s, utf8_long_to_combining_s, print.set->notable);
    fl_print_format("'%[%r%r%]', the ", print.to, print.set->notable, f_console_symbol_long_enable_s, utf8_long_to_width_s, print.set->notable);
    fl_print_format("'%[%r%]' character is printed to represent the combining and the digits are used to represent widths.%r", print.to, print.set->notable, utf8_string_combining_is_s, print.set->notable, f_string_eol_s);
    fl_print_format("  The combining characters should be considered 1-width by themselves or 0-width when combined.%r", print.to, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_utf8_print_help_

#ifndef _di_utf8_print_line_first_locked_
  f_status_t utf8_print_line_first_locked(utf8_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (utf8_main_flag_verify_e | utf8_main_flag_file_to_e)) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_utf8_print_line_first_locked_

#ifndef _di_utf8_print_line_first_unlocked_
  f_status_t utf8_print_line_first_unlocked(utf8_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (utf8_main_flag_verify_e | utf8_main_flag_file_to_e)) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to);

    return F_none;
  }
#endif // _di_utf8_print_line_first_unlocked_

#ifndef _di_utf8_print_line_last_locked_
  f_status_t utf8_print_line_last_locked(utf8_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (utf8_main_flag_verify_e | utf8_main_flag_file_to_e)) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_utf8_print_line_last_locked_

#ifndef _di_utf8_print_line_last_unlocked_
  f_status_t utf8_print_line_last_unlocked(utf8_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
      if (setting->flag & (utf8_main_flag_verify_e | utf8_main_flag_file_to_e)) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_utf8_print_line_last_unlocked_

#ifndef _di_utf8_print_raw_bytesequence_
  f_status_t utf8_print_raw_bytesequence(fll_program_data_t * const main, utf8_setting_t * const setting, const f_utf_char_t raw, const uint8_t width) {

    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    f_string_static_t character = macro_f_string_static_t_initialize(0, 0, width);

    f_char_t byte[character.used + 1];
    character.string = byte;
    byte[character.used] = 0;

    if (raw) {
      if (width == 1) {
        byte[0] = macro_f_utf_char_t_to_char_4_be(raw);
      }
      else if (width == 2) {
        byte[0] = macro_f_utf_char_t_to_char_3_be(raw);
        byte[1] = macro_f_utf_char_t_to_char_4_be(raw);
      }
      else if (width == 3) {
        byte[0] = macro_f_utf_char_t_to_char_2_be(raw);
        byte[1] = macro_f_utf_char_t_to_char_3_be(raw);
        byte[2] = macro_f_utf_char_t_to_char_4_be(raw);
      }
      else {
        byte[0] = macro_f_utf_char_t_to_char_1_be(raw);
        byte[1] = macro_f_utf_char_t_to_char_2_be(raw);
        byte[2] = macro_f_utf_char_t_to_char_3_be(raw);
        byte[3] = macro_f_utf_char_t_to_char_4_be(raw);
      }
    }
    else {
      memset(byte, 0, sizeof(f_char_t) * width);
    }

    fl_print_format("%r%[%r%]%r", main->output.to, setting->prepend, setting->valid_not, character, setting->valid_not, setting->append);

    return F_none;
  }
#endif // _di_utf8_print_raw_bytesequence_

#ifndef _di_utf8_print_raw_codepoint_
  f_status_t utf8_print_raw_codepoint(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t raw) {

    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    fl_print_format("%r%[%r%]%r", main->output.to, setting->prepend, setting->valid_not, raw, setting->valid_not, setting->append);

    return F_none;
  }
#endif // _di_utf8_print_raw_codepoint_

#ifndef _di_utf8_print_raw_combining_or_width_
  f_status_t utf8_print_raw_combining_or_width(fll_program_data_t * const main, utf8_setting_t * const setting, const uint8_t width) {

    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    if (setting->mode & utf8_mode_to_combining_e) {
      utf8_print_error_combining_or_width(main, setting);
    }
    else if (setting->mode & utf8_mode_to_width_e) {
      const f_string_static_t *character = 0;

      switch (width) {
        case 1:
          character = &utf8_string_width_1_s;
          break;

        case 2:
          character = &utf8_string_width_2_s;
          break;

        case 3:
          character = &utf8_string_width_3_s;
          break;

        case 4:
          character = &utf8_string_width_4_s;
          break;

        default:
          character = &utf8_string_width_0_s;
      }

      fl_print_format("%r%[%r%]%r", main->output.to, setting->prepend, setting->valid_not, *character, setting->valid_not, setting->append);
    }

    return F_none;
  }
#endif // _di_utf8_print_raw_combining_or_width_

#ifndef _di_utf8_print_section_header_file_
  f_status_t utf8_print_section_header_file(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t name, const f_array_length_t index) {

    if (!(setting->flag & (utf8_main_flag_header_e | utf8_main_flag_separate_e))) return F_output_not;
    if (setting->flag & utf8_main_flag_verify_e) return F_output_not;

    f_file_stream_lock(main->output.to);

    if ((main->pipe & fll_program_data_pipe_input_e) || index) {
      f_print_dynamic_raw(f_string_eol_s, main->output.to);
    }
    else {
      f_print_dynamic_raw(setting->line_first, main->output.to);
    }

    if (setting->flag & utf8_main_flag_header_e) {
      fl_print_format("%[File%] ", main->output.to, main->output.set->title, main->output.set->title);

      if (setting->flag & utf8_main_flag_file_to_e) {
        fl_print_format("%[%Q%]: %Q.%r", main->output.to, main->output.set->notable, name, main->output.set->notable, setting->path_files_to.array[0], f_string_eol_s);
      }
      else {
        fl_print_format("%[%Q%]:%r", main->output.to, main->output.set->notable, name, main->output.set->notable, f_string_eol_s);
      }
    }

    f_file_stream_unlock(main->output.to);

    return F_none;
  }
#endif // _di_utf8_print_section_header_file_

#ifndef _di_utf8_print_section_header_parameter_
  f_status_t utf8_print_section_header_parameter(fll_program_data_t * const main, utf8_setting_t * const setting, const f_array_length_t index) {

    if (!(setting->flag & (utf8_main_flag_header_e | utf8_main_flag_separate_e))) return F_output_not;
    if (setting->flag & utf8_main_flag_verify_e) return F_output_not;

    f_file_stream_lock(main->output.to);

    if ((main->pipe & fll_program_data_pipe_input_e) || (setting->flag & utf8_main_flag_file_from_e) || index) {
      f_print_dynamic_raw(f_string_eol_s, main->output.to);
    }
    else {
      f_print_dynamic_raw(setting->line_first, main->output.to);
    }

    if (setting->flag & utf8_main_flag_header_e) {
      fl_print_format("%[Parameter%] ", main->output.to, main->output.set->title, main->output.set->title);
      fl_print_format("%[%ul%]:%r", main->output.to, main->output.set->notable, index, main->output.set->notable, f_string_eol_s);
    }

    f_file_stream_unlock(main->output.to);

    return F_none;
  }
#endif // _di_utf8_print_section_header_parameter_

#ifndef _di_utf8_print_section_header_pipe_
  f_status_t utf8_print_section_header_pipe(fll_program_data_t * const main, utf8_setting_t * const setting) {

    if (!(setting->flag & (utf8_main_flag_header_e | utf8_main_flag_separate_e))) return F_output_not;
    if (setting->flag & utf8_main_flag_verify_e) return F_output_not;

    f_file_stream_lock(main->output.to);

    f_print_dynamic_raw(setting->line_first, main->output.to);

    if (setting->flag & utf8_main_flag_header_e) {
      fl_print_format("%[Pipe%]:%r", main->output.to, main->output.set->title, main->output.set->title, f_string_eol_s);
    }

    f_file_stream_unlock(main->output.to);

    return F_none;
  }
#endif // _di_utf8_print_section_header_pipe_

#ifndef _di_utf8_print_width_
  f_status_t utf8_print_width(fll_program_data_t * const main, utf8_setting_t * const setting, const f_string_static_t sequence) {

    f_status_t status = f_utf_is_wide(sequence.string, sequence.used);

    if (status == F_true) {
      fl_print_format("%r%r%r", main->output.to, setting->prepend, utf8_string_width_2_s, setting->append);

      return F_output_not;
    }

    if (status == F_false) {
      status = f_utf_is_graph(sequence.string, sequence.used);

      if (status == F_true) {
        fl_print_format("%r%r%r", main->output.to, setting->prepend, utf8_string_width_1_s, setting->append);

        return F_output_not;
      }

      if (status == F_false) {
        fl_print_format("%r%r%r", main->output.to, setting->prepend, utf8_string_width_0_s, setting->append);

        return F_output_not;
      }
    }

    utf8_print_error_combining_or_width(main, setting);

    return F_none;
  }
#endif // _di_utf8_print_width_

#ifdef __cplusplus
} // extern "C"
#endif
