#include "../utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_print_data_bytesequence_
  f_status_t utf8_print_data_bytesequence(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t sequence) {

    if (!setting) return F_status_set_error(F_output_not);

    fl_print_format("%r%r%r", print.to, setting->prepend, sequence, setting->append);

    return F_none;
  }
#endif // _di_utf8_print_data_bytesequence_

#ifndef _di_utf8_print_data_character_invalid_
  f_status_t utf8_print_data_character_invalid(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t invalid) {

    if (!setting) return F_status_set_error(F_output_not);
    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;
    if (!invalid.used) return F_output_not;

    if ((setting->mode & utf8_mode_to_combining_e) || (setting->mode & utf8_mode_to_width_e)) {
      utf8_print_data_combining_or_width(setting, print, invalid);
    }
    else if (setting->mode & utf8_mode_to_bytesequence_e) {
      fl_print_format("%r%[%r%]%r", print.to, setting->prepend, setting->valid_not, invalid, setting->valid_not, setting->append);
    }
    else if (setting->mode & utf8_mode_from_codepoint_e) {
      fl_print_format("%r%[%Q%]%r", print.to, setting->prepend, setting->valid_not, invalid, setting->valid_not, setting->append);
    }
    else {
      fl_print_format("%r%[0x", print.to, setting->prepend, setting->valid_not);

      for (uint8_t i = 0; i < invalid.used; ++i) {
        fl_print_format("%02_uii", print.to, (uint8_t) invalid.string[i]);
      } // for

      fl_print_format("%]%r", print.to, setting->valid_not, setting->append);
    }

    return F_none;
  }
#endif // _di_utf8_print_data_character_invalid_

#ifndef _di_utf8_print_data_codepoint_
  f_status_t utf8_print_data_codepoint(utf8_setting_t * const setting, const fl_print_t print, const uint32_t codepoint) {

    if (!setting) return F_status_set_error(F_output_not);

    if (codepoint < 0x10000) {
      fl_print_format("%rU+%04_U%r", print.to, setting->prepend, codepoint, setting->append);
    }
    else if (codepoint < 0x100000) {
      fl_print_format("%rU+%05_U%r", print.to, setting->prepend, codepoint, setting->append);
    }
    else {
      fl_print_format("%rU+%06_U%r", print.to, setting->prepend, codepoint, setting->append);
    }

    return F_none;
  }
#endif // _di_utf8_print_data_codepoint_

#ifndef _di_utf8_print_data_combining_or_width_
  f_status_t utf8_print_data_combining_or_width(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t sequence) {

    if (!setting) return F_status_set_error(F_output_not);

    if (setting->mode & utf8_mode_to_combining_e) {
      f_status_t status = f_utf_is_combining(sequence.string, sequence.used);

      if (status == F_true) {
        fl_print_format("%r%r%r", print.to, setting->prepend, utf8_string_combining_is_s, setting->append);
      }
      else if (status == F_false) {
        status = f_utf_is_private(sequence.string, sequence.used);

        if (status == F_true) {
          fl_print_format("%r%r%r", print.to, setting->prepend, utf8_string_unknown_s, setting->append);
        }
        else if (setting->mode & utf8_mode_to_width_e) {
          utf8_print_data_width(setting, print, sequence);
        }
        else {
          fl_print_format("%r%r%r", print.to, setting->prepend, utf8_string_combining_not_s, setting->append);
        }
      }
      else {
        utf8_print_data_combining_or_width_invalid(setting, print);
      }
    }
    else if (setting->mode & utf8_mode_to_width_e) {
      utf8_print_data_width(setting, print, sequence);
    }

    return F_none;
  }
#endif // _di_utf8_print_data_combining_or_width_

#ifndef _di_utf8_print_data_combining_or_width_invalid_
  f_status_t utf8_print_data_combining_or_width_invalid(utf8_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    fl_print_format("%r%[%r%]%r", print.to, setting->prepend, setting->valid_not, utf8_string_unknown_s, setting->valid_not, setting->append);

    return F_none;
  }
#endif // _di_utf8_print_data_combining_or_width_invalid_

#ifndef _di_utf8_print_data_raw_bytesequence_
  f_status_t utf8_print_data_raw_bytesequence(utf8_setting_t * const setting, const fl_print_t print, const f_utf_char_t raw, const uint8_t width) {

    if (!setting) return F_status_set_error(F_output_not);
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

    fl_print_format("%r%[%r%]%r", print.to, setting->prepend, setting->valid_not, character, setting->valid_not, setting->append);

    return F_none;
  }
#endif // _di_utf8_print_data_raw_bytesequence_

#ifndef _di_utf8_print_data_raw_codepoint_
  f_status_t utf8_print_data_raw_codepoint(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t raw) {

    if (!setting) return F_status_set_error(F_output_not);
    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    fl_print_format("%r%[%r%]%r", print.to, setting->prepend, setting->valid_not, raw, setting->valid_not, setting->append);

    return F_none;
  }
#endif // _di_utf8_print_data_raw_codepoint_

#ifndef _di_utf8_print_data_raw_combining_or_width_
  f_status_t utf8_print_data_raw_combining_or_width(utf8_setting_t * const setting, const fl_print_t print, const uint8_t width) {

    if (!setting) return F_status_set_error(F_output_not);
    if (setting->flag & (utf8_main_flag_strip_invalid_e | utf8_main_flag_verify_e)) return F_output_not;

    if (setting->mode & utf8_mode_to_combining_e) {
      utf8_print_data_combining_or_width_invalid(setting, print);
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

      fl_print_format("%r%[%r%]%r", print.to, setting->prepend, setting->valid_not, *character, setting->valid_not, setting->append);
    }

    return F_none;
  }
#endif // _di_utf8_print_data_raw_combining_or_width_

#ifndef _di_utf8_print_data_section_header_file_
  f_status_t utf8_print_data_section_header_file(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_array_length_t index) {

    if (!setting) return F_status_set_error(F_output_not);
    if (!(setting->flag & (utf8_main_flag_header_e | utf8_main_flag_separate_e))) return F_output_not;
    if (setting->flag & utf8_main_flag_verify_e) return F_output_not;

    f_file_stream_lock(print.to);

    if (setting->flag & utf8_main_flag_header_e) {
      if (index) {
        f_print_dynamic_raw(f_string_eol_s, print.to);
      }

      fl_print_format("%[File%] ", print.to, print.set->title, print.set->title);

      if (setting->flag & utf8_main_flag_file_to_e) {
        fl_print_format("%[%Q%]: %Q.%r", print.to, print.set->notable, name, print.set->notable, setting->path_files_to.array[0], f_string_eol_s);
      }
      else {
        fl_print_format("%[%Q%]:%r", print.to, print.set->notable, name, print.set->notable, f_string_eol_s);
      }
    }

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_utf8_print_data_section_header_file_

#ifndef _di_utf8_print_data_section_header_parameter_
  f_status_t utf8_print_data_section_header_parameter(utf8_setting_t * const setting, const fl_print_t print, const f_array_length_t index) {

    if (!setting) return F_status_set_error(F_output_not);
    if (!(setting->flag & (utf8_main_flag_header_e | utf8_main_flag_separate_e))) return F_output_not;
    if (setting->flag & utf8_main_flag_verify_e) return F_output_not;

    f_file_stream_lock(print.to);

    if (setting->flag & utf8_main_flag_header_e) {
      if ((setting->flag & (utf8_main_flag_pipe_e | utf8_main_flag_file_from_e)) || index) {
        f_print_dynamic_raw(f_string_eol_s, print.to);
      }

      fl_print_format("%[Parameter%] ", print.to, print.set->title, print.set->title);
      fl_print_format("%[%ul%]:%r", print.to, print.set->notable, index, print.set->notable, f_string_eol_s);
    }
    else {
      if ((setting->flag & (utf8_main_flag_pipe_e | utf8_main_flag_file_from_e)) || index) {
        f_print_dynamic_raw(f_string_eol_s, print.to);
      }
    }

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_utf8_print_data_section_header_parameter_

#ifndef _di_utf8_print_data_section_header_pipe_
  f_status_t utf8_print_data_section_header_pipe(utf8_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (!(setting->flag & (utf8_main_flag_header_e | utf8_main_flag_separate_e))) return F_output_not;
    if (setting->flag & utf8_main_flag_verify_e) return F_output_not;

    if (setting->flag & utf8_main_flag_header_e) {
      fll_print_format("%[Pipe%]:%r", print.to, print.set->title, print.set->title, f_string_eol_s);
    }

    return F_none;
  }
#endif // _di_utf8_print_data_section_header_pipe_

#ifndef _di_utf8_print_data_width_
  f_status_t utf8_print_data_width(utf8_setting_t * const setting, const fl_print_t print, const f_string_static_t sequence) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_status_t status = f_utf_is_wide(sequence.string, sequence.used);

    if (status == F_true) {
      fl_print_format("%r%r%r", print.to, setting->prepend, utf8_string_width_2_s, setting->append);

      return F_output_not;
    }

    if (status == F_false) {
      status = f_utf_is_graph(sequence.string, sequence.used);

      if (status == F_true) {
        fl_print_format("%r%r%r", print.to, setting->prepend, utf8_string_width_1_s, setting->append);

        return F_output_not;
      }

      if (status == F_false) {
        fl_print_format("%r%r%r", print.to, setting->prepend, utf8_string_width_0_s, setting->append);

        return F_output_not;
      }
    }

    utf8_print_data_combining_or_width_invalid(setting, print);

    return F_none;
  }
#endif // _di_utf8_print_data_width_

#ifdef __cplusplus
} // extern "C"
#endif
