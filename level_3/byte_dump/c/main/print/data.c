#include "../byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_print_character_fragment_
  f_status_t byte_dump_print_character_fragment(fl_print_t * const print, const f_utf_string_static_t sequence, const f_char_t invalid[], const uint8_t width_utf, const f_char_t byte_current, byte_dump_previous_t *previous, byte_dump_cell_t *cell, f_char_t *offset) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    byte_dump_main_t * const main = (byte_dump_main_t *) print->custom;

    f_char_t byte = 0;
    bool reset = F_false;
    f_number_unsigned_t current = sequence.used - 1;

    if (byte_current == 1) {
      byte = macro_f_utf_char_t_to_char_1(sequence.string[current]);
    }
    else if (byte_current == 2) {
      byte = macro_f_utf_char_t_to_char_2(sequence.string[current]);
    }
    else if (byte_current == 3) {
      byte = macro_f_utf_char_t_to_char_3(sequence.string[current]);
    }
    else if (byte_current == 4) {
      byte = macro_f_utf_char_t_to_char_4(sequence.string[current]);
    }

    if (!cell->column) {
      fl_print_format("%[%016_UL%] ", print->to, print->set->notable, cell->row, print->set->notable);

      if (*offset) {
        f_char_t offset_to_print = *offset;

        // Pad the buffer with spaces to hide any skipped bytes (skipped via --first).
        while (offset_to_print && cell->column < main->setting.width) {

          f_print_dynamic_raw(byte_dump_padding_s[(main->setting.flag & byte_dump_main_flag_unicode_e) ? 0 : main->setting.mode], print->to);

          --offset_to_print;
          ++cell->column;

          if (cell->column < main->setting.width) {
            if ((main->setting.flag & byte_dump_main_flag_unicode_e) || main->setting.mode == byte_dump_mode_binary_e) {
              if (!(cell->column % 4)) {
                f_print_dynamic_raw(f_string_space_s, print->to);
              }
            }
            else if (main->setting.mode == byte_dump_mode_hexidecimal_e) {
              if (!(cell->column % 8)) {
                f_print_dynamic_raw(f_string_space_s, print->to);
              }
            }
            else if (main->setting.mode == byte_dump_mode_duodecimal_e || main->setting.mode == byte_dump_mode_octal_e || main->setting.mode == byte_dump_mode_decimal_e) {
              if (!(cell->column % 6)) {
                f_print_dynamic_raw(f_string_space_s, print->to);
              }
            }
          }
        } // while
      }
    }

    if (cell->column < main->setting.width) {
      if ((main->setting.flag & byte_dump_main_flag_unicode_e) && !invalid[current]) {
        if (byte_current == 1) {
          uint32_t unicode = 0;

          if (width_utf < 2) {

            // 1 == U+0000 -> U+007F.
            unicode = macro_f_utf_char_t_to_char_1(sequence.string[current]) & 0x7f;
          }
          else if (width_utf == 2) {

            // 2 == U+0080 -> U+07FF.
            unicode = (macro_f_utf_char_t_to_char_1(sequence.string[current]) & 0x1f) << 6;
            unicode |= macro_f_utf_char_t_to_char_2(sequence.string[current]) & 0x3f;
          }
          else if (width_utf == 3) {

            // 3 == U+0800 -> U+FFFF.
            unicode = (macro_f_utf_char_t_to_char_1(sequence.string[current]) & 0xf) << 12;
            unicode |= (macro_f_utf_char_t_to_char_2(sequence.string[current]) & 0x3f) << 6;
            unicode |= macro_f_utf_char_t_to_char_3(sequence.string[current]) & 0x3f;
          }
          else if (width_utf == 4) {

            // 4 == U+10000 -> U+10FFFF.
            unicode = (macro_f_utf_char_t_to_char_1(sequence.string[current]) & 0x7) << 18;
            unicode |= (macro_f_utf_char_t_to_char_2(sequence.string[current]) & 0x3f) << 12;
            unicode |= (macro_f_utf_char_t_to_char_2(sequence.string[current]) & 0x3f) << 6;
            unicode |= macro_f_utf_char_t_to_char_4(sequence.string[current]) & 0x3f;
          }

          if (width_utf < 4) {
            fl_print_format(" U+%04_U  ", print->to, unicode);
          }
          else {
            fl_print_format(" U+%06_U", print->to, unicode);
          }
        }
        else {

          // Pad the sequence that are incomplete fragments of an already printed valid Unicode.
          f_print_dynamic_raw(byte_dump_padding_9_s, print->to);
        }
      }
      else {
        if (main->setting.mode == byte_dump_mode_hexidecimal_e) {
          if (main->setting.flag & byte_dump_main_flag_unicode_e) {
            f_print_dynamic_raw(byte_dump_padding_6_s, print->to);
          }

          if (invalid[current]) {
            fl_print_format(" %[%02_uii%]", print->to, print->set->error, (uint8_t) byte, print->set->error);
          }
          else {
            fl_print_format(" %02_uii", print->to, (uint8_t) byte);
          }
        }
        else if (main->setting.mode == byte_dump_mode_duodecimal_e) {
          if (main->setting.flag & byte_dump_main_flag_unicode_e) {
            f_print_dynamic_raw(byte_dump_padding_5_s, print->to);
          }

          if (invalid[current]) {
            fl_print_format(" %[%03&uii%]", print->to, print->set->error, (uint8_t) byte, print->set->error);
          }
          else {
            fl_print_format(" %03&uii", print->to, (uint8_t) byte);
          }
        }
        else if (main->setting.mode == byte_dump_mode_octal_e) {
          if (main->setting.flag & byte_dump_main_flag_unicode_e) {
            f_print_dynamic_raw(byte_dump_padding_5_s, print->to);
          }

          if (invalid[current]) {
            fl_print_format(" %[%03@uii%]", print->to, print->set->error, (uint8_t) byte, print->set->error);
          }
          else {
            fl_print_format(" %03@uii", print->to, (uint8_t) byte);
          }
        }
        else if (main->setting.mode == byte_dump_mode_binary_e) {
          if (invalid[current]) {
            fl_print_format(" %[%08!uii%]", print->to, print->set->error, (uint8_t) byte, print->set->error);
          }
          else {
            fl_print_format(" %08!uii", print->to, (uint8_t) byte);
          }
        }
        else if (main->setting.mode == byte_dump_mode_decimal_e) {
          if (main->setting.flag & byte_dump_main_flag_unicode_e) {
            f_print_dynamic_raw(byte_dump_padding_5_s, print->to);
          }

          if (invalid[current]) {
            fl_print_format(" %[%3uii%]", print->to, print->set->error, (uint8_t) byte, print->set->error);
          }
          else {
            fl_print_format(" %3uii", print->to, (uint8_t) byte);
          }
        }
      }

      ++cell->column;
    }

    if (cell->column == main->setting.width) {
      uint8_t bytes = 0;

      if (byte_current < width_utf) {
        bytes = width_utf - byte_current;
      }

      reset = F_true;

      if (main->setting.flag & byte_dump_main_flag_text_e) {
        byte_dump_print_text(print, sequence, invalid, previous, offset);
      }
      else {
        f_print_dynamic_raw(f_string_eol_s, print->to);
      }

      cell->column = 0;
      ++cell->row;

      if (bytes) {
        previous->bytes = bytes;
        previous->invalid = invalid[current];
      }
      else {
        previous->bytes = 0;
        previous->invalid = 0;
      }
    }
    else {
      if ((main->setting.flag & byte_dump_main_flag_unicode_e) || main->setting.mode == byte_dump_mode_binary_e) {
        if (!(cell->column % 4)) {
          f_print_dynamic_raw(f_string_space_s, print->to);
        }
      }
      else if (main->setting.mode == byte_dump_mode_hexidecimal_e) {
        if (!(cell->column % 8)) {
          f_print_dynamic_raw(f_string_space_s, print->to);
        }
      }
      else if (main->setting.mode == byte_dump_mode_duodecimal_e || main->setting.mode == byte_dump_mode_octal_e || main->setting.mode == byte_dump_mode_decimal_e) {
        if (!(cell->column % 6)) {
          f_print_dynamic_raw(f_string_space_s, print->to);
        }
      }
    }

    return reset;
  }
#endif // _di_byte_dump_print_character_fragment_

#ifndef _di_byte_dump_print_text_
  f_status_t byte_dump_print_text(fl_print_t * const print, const f_utf_string_static_t sequence, const f_char_t invalid[], byte_dump_previous_t *previous, f_char_t *offset) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    byte_dump_main_t * const main = (byte_dump_main_t *) print->custom;

    f_char_t c = 0;
    uint8_t at = 0;
    uint8_t width_utf = 0;
    bool do_print = F_true;

    f_char_t byte[5] = { 0, 0, 0, 0, 0 };

    fl_print_format("  %[%r%] ", print->to, print->set->notable, byte_dump_character_wall_s, print->set->notable);

    if (*offset) {
      if (main->setting.flag & byte_dump_main_flag_classic_e) {
        while (*offset && at < main->setting.width) {

          f_print_dynamic_raw(f_string_ascii_period_s, print->to);

          if (main->setting.flag & byte_dump_main_flag_wide_e) {
            f_print_dynamic_raw(f_string_ascii_space_s, print->to);
          }

          --(*offset);
          ++at;
        } // while
      }
      else {
        if (main->setting.flag & byte_dump_main_flag_placeholder_e) {
          for (; *offset && at < main->setting.width; --(*offset), ++at) {

            fl_print_format(f_string_format_r_single_s.string, print->to, print->set->warning, byte_dump_character_placeholder_s, print->set->warning);

            if (main->setting.flag & byte_dump_main_flag_wide_e) {
              f_print_dynamic_raw(f_string_space_s, print->to);
            }
          } // for
        }
        else {
          for (; *offset && at < main->setting.width; --(*offset), ++at) {

            f_print_dynamic_raw(f_string_space_s, print->to);

            if (main->setting.flag & byte_dump_main_flag_wide_e) {
              f_print_dynamic_raw(f_string_space_s, print->to);
            }
          } // for
        }
      }
    }

    // Print placeholders for the remaining fragments of UTF-8 sequence printed on previous lines.
    if (at < main->setting.width) {
      uint8_t bytes_overflow = 0;

      if (previous->bytes - 1 > main->setting.width) {
        bytes_overflow = previous->bytes - 1 - main->setting.width;
      }

      if (previous->bytes) {
        if (main->setting.flag & byte_dump_main_flag_placeholder_e) {
          for (; at < previous->bytes && at < main->setting.width; ++at) {

            if (previous->invalid) {
              fl_print_format(f_string_format_r_single_s.string, print->to, print->set->error, byte_dump_character_placeholder_s, print->set->error);
            }
            else if (main->setting.flag & byte_dump_main_flag_classic_e) {
              f_print_dynamic_raw(f_string_ascii_period_s, print->to);
            }
            else {
              fl_print_format(f_string_format_r_single_s.string, print->to, print->set->warning, byte_dump_character_placeholder_s, print->set->warning);
            }

            if (main->setting.flag & byte_dump_main_flag_wide_e) {
              f_print_dynamic_raw(f_string_ascii_space_s, print->to);
            }
          } // for
        }
        else {
          for (; at < previous->bytes && at < main->setting.width; ++at) {

            f_print_dynamic_raw(f_string_space_s, print->to);

            if (main->setting.flag & byte_dump_main_flag_wide_e) {
              f_print_dynamic_raw(f_string_space_s, print->to);
            }
          } // for
        }
      }

      if (bytes_overflow) {
        previous->bytes = bytes_overflow;
      }
      else {
        previous->bytes = 0;
        previous->invalid = 0;
      }
    }

    for (uint8_t i = 0; i < sequence.used && at < main->setting.width; ++i, ++at) {

      c = macro_f_utf_char_t_to_char_1(sequence.string[i]);
      width_utf = macro_f_utf_byte_width_is(c);

      if (invalid[i]) {
        fl_print_format(f_string_format_r_single_s.string, print->to, print->set->error, byte_dump_character_incomplete_s, print->set->error);

        if (main->setting.flag & byte_dump_main_flag_wide_e) {
          f_print_dynamic_raw(f_string_ascii_space_s, print->to);
        }
      }
      else if (f_utf_character_is_control(sequence.string[i]) == F_true) {
        if (main->setting.presentation == byte_dump_presentation_normal_e) {
          fl_print_format("%[%[", print->to, print->set->notable, print->set->warning);

          if (width_utf) {
            byte[0] = c;

            if (width_utf > 1) {
              byte[1] = macro_f_utf_char_t_to_char_2(sequence.string[i]);

              if (width_utf > 2) {
                byte[2] = macro_f_utf_char_t_to_char_3(sequence.string[i]);

                if (width_utf > 3) {
                  byte[3] = macro_f_utf_char_t_to_char_4(sequence.string[i]);
                }
                else {
                  byte[3] = 0;
                }
              }
              else {
                byte[2] = 0;
              }
            }
            else {
              byte[1] = 0;
            }

            f_print_safely(byte, width_utf, print->to);
          }
          else {
            f_print_character_safely(c, print->to);
          }

          fl_print_format("%]%]", print->to, print->set->warning, print->set->notable);

          if (main->setting.flag & byte_dump_main_flag_wide_e) {
            if (f_utf_character_is_wide(sequence.string[i]) != F_true) {
              f_print_dynamic_raw(f_string_ascii_space_s, print->to);
            }
          }
        }
        else {
          if (main->setting.presentation == byte_dump_presentation_simple_e) {
            f_print_dynamic_raw(f_string_space_s, print->to);

            if (width_utf > 1) {
              f_print_dynamic_raw(f_string_space_s, print->to);

              if (width_utf > 2) {
                f_print_dynamic_raw(f_string_space_s, print->to);

                if (width_utf > 3) {
                  f_print_dynamic_raw(f_string_space_s, print->to);
                }
              }
            }
          }
          else if (main->setting.presentation == byte_dump_presentation_classic_e) {
            f_print_dynamic_raw(f_string_ascii_period_s, print->to);

            if (width_utf > 1) {
              f_print_dynamic_raw(f_string_ascii_period_s, print->to);

              if (width_utf > 2) {
                f_print_dynamic_raw(f_string_ascii_period_s, print->to);

                if (width_utf > 3) {
                  f_print_dynamic_raw(f_string_ascii_period_s, print->to);
                }
              }
            }
          }

          if (main->setting.flag & byte_dump_main_flag_wide_e) {
            f_print_dynamic_raw(f_string_ascii_space_s, print->to);
          }
        }
      }
      else if (f_utf_character_is_whitespace(sequence.string[i], F_true) == F_true) {
        if (main->setting.flag & byte_dump_main_flag_classic_e) {
          f_print_dynamic_raw(f_string_ascii_period_s, print->to);
        }
        else {
          fl_print_format(f_string_format_r_double_s.string, print->to, print->set->notable, print->set->warning, f_print_sequence_space_s, print->set->warning, print->set->notable);
        }

        if (main->setting.flag & byte_dump_main_flag_wide_e) {
          f_print_dynamic_raw(f_string_ascii_space_s, print->to);
        }
      }
      else if (f_utf_character_is_zero_width(sequence.string[i]) == F_true) {
        if (main->setting.presentation == byte_dump_presentation_classic_e) {
          f_print_dynamic_raw(f_string_ascii_period_s, print->to);
        }
        else if (main->setting.flag & byte_dump_main_flag_placeholder_e) {
          fl_print_format(f_string_format_r_double_s.string, print->to, print->set->notable, print->set->warning, byte_dump_character_placeholder_s, print->set->warning, print->set->notable);
        }
        else {
          f_print_dynamic_raw(f_string_space_s, print->to);
        }

        if (main->setting.flag & byte_dump_main_flag_wide_e) {
          f_print_dynamic_raw(f_string_ascii_space_s, print->to);
        }
      }
      else if (width_utf) {
        do_print = F_false;

        if (width_utf == 1) {

          // Print invalid placeholder for invalid UTF-8 widths.
          if (invalid[i]) {
            fl_print_format(f_string_format_r_single_s.string, print->to, print->set->error, byte_dump_character_incomplete_s, print->set->error);
          }
          else {
            fl_print_format(f_string_format_r_single_s.string, print->to, print->set->warning, byte_dump_character_incomplete_s, print->set->warning);
          }
        }
        else if (width_utf == 2) {
          do_print = F_true;
        }
        else if (width_utf == 3) {
          if (sequence.string[i] >= 0xefbfb000 && sequence.string[i] <= 0xefbfbc00) {

            // Use space to represent Specials codes.
            // 0xefbfbd00 is excluded because it is printable (and is the "Replacement Character" code).
            f_print_dynamic_raw(f_string_space_s, print->to);
          }
          else if (sequence.string[i] >= 0xe290a700 && sequence.string[i] <= 0xe290bf00) {

            // Use space to represent Control Pictues codes that are not currently defined but are reserved.
            f_print_dynamic_raw(f_string_space_s, print->to);
          }
          else if (sequence.string[i] >= 0xee808000 && sequence.string[i] <= 0xefa3bf00) {

            // Use space to represent Private Use Area codes.
            f_print_dynamic_raw(f_string_space_s, print->to);
          }
          else {
            do_print = F_true;
          }
        }
        else if (sequence.string[i] >= 0xf09c80a0 && sequence.string[i] <= 0xf09c80bd) {

          // Use space to represent Variation Selectors Supplement codes.
          f_print_dynamic_raw(f_string_space_s, print->to);
        }
        else if (sequence.string[i] >= 0xf3b08080 && sequence.string[i] <= 0xf3bfbfbf) {

          // Use space to represent Supplemental Private Use Area-A codes.
          f_print_dynamic_raw(f_string_space_s, print->to);
        }
        else if (sequence.string[i] >= 0xf4808080 && sequence.string[i] <= 0xf48fbfbf) {

          // Use space to represent Supplemental Private Use Area-B codes.
          f_print_dynamic_raw(f_string_space_s, print->to);
        }
        else {
          do_print = F_true;
        }

        if (do_print) {
          f_print_character(c, print->to);

          if (width_utf > 1) {
            f_print_character(macro_f_utf_char_t_to_char_2(sequence.string[i]), print->to);

            if (width_utf > 2) {
              f_print_character(macro_f_utf_char_t_to_char_3(sequence.string[i]), print->to);

              if (width_utf > 3) {
                f_print_character(macro_f_utf_char_t_to_char_4(sequence.string[i]), print->to);
              }
            }
          }

          if (f_utf_character_is_combining(sequence.string[i]) == F_true) {
            f_print_dynamic_raw(f_string_space_s, print->to);
          }

          if (main->setting.flag & byte_dump_main_flag_wide_e) {
            if (width_utf == 1 || f_utf_character_is_wide(sequence.string[i]) != F_true) {
              f_print_dynamic_raw(f_string_ascii_space_s, print->to);
            }
          }
        }
        else {
          if (main->setting.flag & byte_dump_main_flag_wide_e) {
            f_print_dynamic_raw(f_string_ascii_space_s, print->to);
          }
        }
      }
      else {
        f_print_character(c, print->to);

        if (main->setting.flag & byte_dump_main_flag_wide_e) {
          f_print_dynamic_raw(f_string_ascii_space_s, print->to);
        }
      }

      // Print placeholders when using UTF-8 sequence to simulate the spaces bytes used for the character.
      if (width_utf > 1 && at + 1 < main->setting.width) {
        if (main->setting.flag & byte_dump_main_flag_placeholder_e) {
          if (invalid[i]) {
            fl_print_format(f_string_format_r_single_s.string, print->to, print->set->error, byte_dump_character_placeholder_s, print->set->error);
          }
          else if (main->setting.flag & byte_dump_main_flag_classic_e) {
            f_print_dynamic_raw(f_string_ascii_period_s, print->to);
          }
          else {
            fl_print_format(f_string_format_r_single_s.string, print->to, print->set->warning, byte_dump_character_placeholder_s, print->set->warning);
          }
        }
        else {
          f_print_dynamic_raw(f_string_space_s, print->to);
        }

        if (main->setting.flag & byte_dump_main_flag_wide_e) {
          f_print_dynamic_raw(f_string_ascii_space_s, print->to);
        }

        ++at;

        if (width_utf > 2 && at + 1 < main->setting.width) {
          if (main->setting.flag & byte_dump_main_flag_placeholder_e) {
            if (invalid[i]) {
              fl_print_format(f_string_format_r_single_s.string, print->to, print->set->error, byte_dump_character_placeholder_s, print->set->error);
            }
            else if (main->setting.flag & byte_dump_main_flag_classic_e) {
              f_print_dynamic_raw(f_string_ascii_period_s, print->to);
            }
            else {
              fl_print_format(f_string_format_r_single_s.string, print->to, print->set->warning, byte_dump_character_placeholder_s, print->set->warning);
            }
          }
          else {
            f_print_dynamic_raw(f_string_space_s, print->to);
          }

          if (main->setting.flag & byte_dump_main_flag_wide_e) {
            f_print_dynamic_raw(f_string_ascii_space_s, print->to);
          }

          ++at;

          if (width_utf > 3 && at + 1 < main->setting.width) {
            if (main->setting.flag & byte_dump_main_flag_placeholder_e) {
              if (invalid[i]) {
                fl_print_format(f_string_format_r_single_s.string, print->to, print->set->error, byte_dump_character_placeholder_s, print->set->error);
              }
              else if (main->setting.flag & byte_dump_main_flag_classic_e) {
                f_print_dynamic_raw(f_string_ascii_period_s, print->to);
              }
              else {
                fl_print_format(f_string_format_r_single_s.string, print->to, print->set->warning, byte_dump_character_placeholder_s, print->set->warning);
              }
            }
            else {
              f_print_dynamic_raw(f_string_space_s, print->to);
            }

            if (main->setting.flag & byte_dump_main_flag_wide_e) {
              f_print_dynamic_raw(f_string_ascii_space_s, print->to);
            }

            ++at;
          }
        }
      }
    } // for

    // Print placeholder for the remaining parts of the line.
    if (main->setting.flag & byte_dump_main_flag_placeholder_e) {
      for (; at < main->setting.width; ++at) {

        if (invalid[at]) {
          fl_print_format(f_string_format_r_single_s.string, print->to, print->set->error, byte_dump_character_placeholder_s, print->set->error);
        }
        else if (main->setting.flag & byte_dump_main_flag_classic_e) {
          f_print_dynamic_raw(f_string_ascii_period_s, print->to);
        }
        else {
          fl_print_format(f_string_format_r_single_s.string, print->to, print->set->warning, byte_dump_character_placeholder_s, print->set->warning);
        }

        if (main->setting.flag & byte_dump_main_flag_wide_e) {
          f_print_dynamic_raw(f_string_ascii_space_s, print->to);
        }
      } // for
    }
    else {
      for (; at < main->setting.width; ++at) {

        f_print_dynamic_raw(f_string_space_s, print->to);

        if (main->setting.flag & byte_dump_main_flag_wide_e) {
          f_print_dynamic_raw(f_string_space_s, print->to);
        }
      } // for
    }

    fl_print_format(" %[%r%]%r", print->to, print->set->notable, byte_dump_character_wall_s, print->set->notable, f_string_eol_s);

    return F_okay;
  }
#endif // _di_byte_dump_print_text_

#ifndef _di_byte_dump_print_file_header_
  f_status_t byte_dump_print_file_header(fl_print_t * const print, const f_string_static_t name) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    byte_dump_main_t * const main = (byte_dump_main_t *) print->custom;

    f_file_stream_lock(print->to);

    if (name.used) {
      fl_print_format("%[%r of: %]%[", print->to, print->set->title, byte_dump_program_name_long_s, print->set->title, print->set->notable);
      fl_print_format("%Q%] %[(in ", print->to, name, print->set->notable, print->set->title);
    }
    else {
      fl_print_format("%[Piped %q: (in ", print->to, print->set->title, byte_dump_program_name_long_s);
    }

    if (main->setting.mode == byte_dump_mode_hexidecimal_e) {
      f_print_dynamic_raw(byte_dump_hexidecimal_s, print->to);
    }
    else if (main->setting.mode == byte_dump_mode_duodecimal_e) {
      f_print_dynamic_raw(byte_dump_duodecimal_s, print->to);
    }
    else if (main->setting.mode == byte_dump_mode_octal_e) {
      f_print_dynamic_raw(byte_dump_octal_s, print->to);
    }
    else if (main->setting.mode == byte_dump_mode_binary_e) {
      f_print_dynamic_raw(byte_dump_binary_s, print->to);
    }
    else if (main->setting.mode == byte_dump_mode_decimal_e) {
      f_print_dynamic_raw(byte_dump_decimal_s, print->to);
    }

    fl_print_format(")%]%r", print->to, print->set->title, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_byte_dump_print_file_header_

#ifdef __cplusplus
} // extern "C"
#endif
