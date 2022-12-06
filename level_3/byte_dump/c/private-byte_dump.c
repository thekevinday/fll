#include "byte_dump.h"
#include "private-common.h"
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_file_
  f_status_t byte_dump_file(byte_dump_data_t * const data, const f_string_static_t file_name, const f_file_t file) {

    f_status_t status = F_none;

    uint64_t position = 0;
    f_char_t byte = 0;
    f_char_t offset = 0;
    int byte_get = 0;

    int8_t width_utf = -1;
    int8_t width_count = 0;

    byte_dump_cell_t cell = byte_dump_cell_t_initialize;
    byte_dump_previous_t previous = byte_dump_previous_t_initialize;

    bool character_reset = 0;
    bool found_invalid_utf = F_false;

    // Store the current character main until it can be printed.
    f_utf_string_dynamic_t sequence = f_utf_string_dynamic_t_initialize;
    f_utf_char_t block[data->width];
    f_array_length_t current = 0;

    // The row starts based on the first byte starting point and how many columns of bytes are displayed per row.
    if (data->first) {
      cell.row = data->first / data->width;
      offset = data->first % data->width;

      // fseek() cannot be used on a PIPE, so read instead of seek.
      if (file_name.used) {
        byte_get = fseek(file.stream, data->first, SEEK_SET);
      }
      else {
        f_char_t skip[data->first];

        byte_get = fread(skip, 1, data->first, file.stream);
      }
    }

    memset(&block, 0, sizeof(f_utf_char_t) * data->width);
    sequence.string = block;
    sequence.used = 0;
    sequence.size = data->width;

    // Record when a character is invalid.
    f_char_t invalid[data->width];
    memset(&invalid, 0, sizeof(f_char_t) * data->width);

    if (byte_get >= 0) {
      for (;;) {

        if (!((++data->main->signal_check) % byte_dump_signal_check_d)) {
          if (fll_program_standard_signal_received(data->main)) {
            byte_dump_print_signal_received(data);

            return F_status_set_error(F_interrupt);
          }

          data->main->signal_check = 0;
        }

        byte_get = getc(file.stream);

        if (byte_get < 0) {
          if (width_utf == -1 && character_reset) {
            sequence.used = 0;
            character_reset = F_false;
            memset(&invalid, 0, sizeof(f_char_t) * data->width);
          }

          break;
        }

        byte = (f_char_t) byte_get;

        // Storing the next character is designated by width_utf == -1.
        if (width_utf == -1) {
          width_utf = macro_f_utf_byte_width_is(byte);
          width_count = 0;

          // The character is reset, the sequence.used is to be reset.
          if (character_reset) {
            sequence.used = 0;
            character_reset = F_false;
            memset(&invalid, 0, sizeof(f_char_t) * data->width);
          }

          current = sequence.used++;
          invalid[current] = 0;
        }

        // When width_count == 0, then this is that start of a new character sequence.
        if (!width_count) {
          sequence.string[current] = macro_f_utf_char_t_from_char_1(byte);
          width_count = 1;

          // The first character in a UTF-8 sequence cannot have a width of 1.
          if (width_utf == 1) {
            found_invalid_utf = F_true;
            invalid[current] = 1;
          }
          // Process the UTF-8 character.
          else if (width_utf > 1) {
            continue;
          }
        }
        // Process a UTF-8 character fragment.
        else if (width_count < width_utf) {
          if (width_count == 1) {
            sequence.string[current] |= macro_f_utf_char_t_from_char_2(byte);
          }
          else if (width_count == 2) {
            sequence.string[current] |= macro_f_utf_char_t_from_char_3(byte);
          }
          else if (width_count == 3) {
            sequence.string[current] |= macro_f_utf_char_t_from_char_4(byte);
          }

          ++width_count;

          // Grab the next UTF-8 character fragment if the entire sequence is not collected yet.
          if (width_count < width_utf) continue;
        }

        // At this point: an ASCII character is collected, the entire UTF-8 character sequence is collected, or an invalid UTF-8 was processed.
        if (!invalid[current] && width_utf > 1) {
          if (f_utf_character_is_valid(sequence.string[current]) != F_true) {
            found_invalid_utf = F_true;
            invalid[current] = width_utf;
          }
          else if (f_utf_character_is_unassigned(sequence.string[current]) == F_true) {

            // Consider unassigned invalid.
            found_invalid_utf = F_true;
            invalid[current] = width_utf;
          }
        }

        flockfile(data->main->output.to.stream);

        if (byte_dump_print_character_fragment(data, sequence, invalid, width_utf, 1, &previous, &cell, &offset) == F_true) {
          character_reset = F_true;
        }

        if (width_utf > 1) {
          if (byte_dump_print_character_fragment(data, sequence, invalid, width_utf, 2, &previous, &cell, &offset) == F_true) {
            character_reset = F_true;
          }

          if (width_utf > 2) {
            if (byte_dump_print_character_fragment(data, sequence, invalid, width_utf, 3, &previous, &cell, &offset) == F_true) {
              character_reset = F_true;
            }

            if (width_utf > 3) {
              if (byte_dump_print_character_fragment(data, sequence, invalid, width_utf, 4, &previous, &cell, &offset) == F_true) {
                character_reset = F_true;
              }
            }
          }

          if (data->last) {
            position += width_utf;

            if (position >= data->last) {
              funlockfile(data->main->output.to.stream);

              break;
            }
          }
        }
        else if (data->last) {
          ++position;

          if (position >= data->last) {
            funlockfile(data->main->output.to.stream);

            break;
          }
        }

        funlockfile(data->main->output.to.stream);

        width_utf = -1;
      } // for
    }

    flockfile(data->main->output.to.stream);

    // Print placeholders to fill out the remaining line and then optionally print the text block.
    if (cell.column && cell.column < data->width) {
      const uint8_t width_missing = width_utf <= 0 ? 0 : width_utf - width_count;

      if (width_missing) {
        const uint8_t column_offset = data->width - cell.column;
        width_count = 0;

        // Handle incomplete character at the end of the stream.
        found_invalid_utf = F_true;
        invalid[current] = width_utf;

        if (byte_dump_print_character_fragment(data, sequence, invalid, width_utf, 1, &previous, &cell, &offset) == F_true) {
          character_reset = F_true;
        }

        if (++width_count < width_missing) {
          if (byte_dump_print_character_fragment(data, sequence, invalid, width_utf, 2, &previous, &cell, &offset) == F_true) {
            character_reset = F_true;
          }

          if (++width_count < width_missing) {
            if (byte_dump_print_character_fragment(data, sequence, invalid, width_utf, 3, &previous, &cell, &offset) == F_true) {
              character_reset = F_true;
            }

            if (++width_count < width_missing) {
              if (byte_dump_print_character_fragment(data, sequence, invalid, width_utf, 4, &previous, &cell, &offset) == F_true) {
                character_reset = F_true;
              }
            }
          }
        }

        if (character_reset) {
          sequence.used = 0;
          memset(&invalid, 0, sizeof(f_char_t) * data->width);

          previous.bytes = column_offset;
          previous.invalid = previous.bytes;
        }
        else {
          previous.bytes = 0;
          previous.invalid = 0;
        }
      }
      else {
        previous.bytes = 0;
        previous.invalid = 0;
      }
    }

    if (cell.column && cell.column < data->width) {
      while (cell.column < data->width) {

        if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
          f_print_terminated("         ", data->main->output.to.stream);
        }
        else if (data->mode == byte_dump_mode_hexidecimal_e) {
          f_print_terminated("   ", data->main->output.to.stream);
        }
        else if (data->mode == byte_dump_mode_duodecimal_e) {
          f_print_terminated("    ", data->main->output.to.stream);
        }
        else if (data->mode == byte_dump_mode_octal_e) {
          f_print_terminated("    ", data->main->output.to.stream);
        }
        else if (data->mode == byte_dump_mode_binary_e) {
          f_print_terminated("         ", data->main->output.to.stream);
        }
        else if (data->mode == byte_dump_mode_decimal_e) {
          f_print_terminated("    ", data->main->output.to.stream);
        }

        ++cell.column;

        if (cell.column < data->width) {
          if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
            if (!(cell.column % 4)) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }
          }
          else if (data->mode == byte_dump_mode_hexidecimal_e) {
            if (!(cell.column % 8)) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }
          }
          else if (data->mode == byte_dump_mode_duodecimal_e) {
            if (!(cell.column % 6)) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }
          }
          else if (data->mode == byte_dump_mode_octal_e) {
            if (!(cell.column % 6)) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }
          }
          else if (data->mode == byte_dump_mode_binary_e) {
            if (!(cell.column % 6)) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }
          }
          else if (data->mode == byte_dump_mode_decimal_e) {
            if (!(cell.column % 6)) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }
          }
        }
      } // while

      if (data->main->parameters.array[byte_dump_parameter_text_e].result == f_console_result_found_e) {
        byte_dump_print_text(data, sequence, invalid, &previous, &offset);
      }
      else {
        f_print_dynamic_raw(f_string_eol_s, data->main->output.to.stream);
      }
    }

    f_print_dynamic_raw(f_string_eol_s, data->main->output.to.stream);

    funlockfile(data->main->output.to.stream);

    // Make sure to flush standard out to help prevent standard error from causing problems.
    fflush(data->main->output.to.stream);

    if (found_invalid_utf) {
      if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%[Invalid UTF-8 codes were detected for file '%]", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error);
        fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->context.set.notable, file_name.used ? file_name : f_string_ascii_minus_s, data->main->context.set.notable);
        fl_print_format("%['.%]%r%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }
    }

    if (ferror(file.stream)) {
      if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%[%Qread() failed for '%]", data->main->error.to.stream, data->main->context.set.error, data->main->error.prefix, data->main->context.set.error);
        fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->context.set.notable, file_name.used ? file_name : f_string_ascii_minus_s, data->main->context.set.notable);
        fl_print_format("%['.%]%r%r", data->main->error.to.stream, data->main->context.set.error, data->main->context.set.error, f_string_eol_s, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      status = F_status_set_error(F_failure);
    }

    fflush(data->main->error.to.stream);

    return status;
  }
#endif // _di_byte_dump_file_

#ifndef _di_byte_dump_print_character_fragment_
  bool byte_dump_print_character_fragment(byte_dump_data_t * const data, const f_utf_string_static_t sequence, const f_char_t invalid[], const uint8_t width_utf, const f_char_t byte_current, byte_dump_previous_t *previous, byte_dump_cell_t *cell, f_char_t *offset) {

    f_char_t byte = 0;

    bool reset = F_false;

    f_array_length_t current = sequence.used - 1;

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
      fl_print_format("%[%016_UL%] ", data->main->output.to.stream, data->main->context.set.notable, cell->row, data->main->context.set.notable);

      if (*offset) {
        f_char_t offset_to_print = *offset;

        // Pad the buffer with spaces to hide any skipped bytes (skipped via --first).
        while (offset_to_print && cell->column < data->width) {

          if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
            f_print_terminated("         ", data->main->output.to.stream);
          }
          else if (data->mode == byte_dump_mode_hexidecimal_e) {
            f_print_terminated("   ", data->main->output.to.stream);
          }
          else if (data->mode == byte_dump_mode_duodecimal_e) {
            f_print_terminated("    ", data->main->output.to.stream);
          }
          else if (data->mode == byte_dump_mode_octal_e) {
            f_print_terminated("    ", data->main->output.to.stream);
          }
          else if (data->mode == byte_dump_mode_binary_e) {
            f_print_terminated("         ", data->main->output.to.stream);
          }
          else if (data->mode == byte_dump_mode_decimal_e) {
            f_print_terminated("    ", data->main->output.to.stream);
          }

          --offset_to_print;
          ++cell->column;

          if (cell->column < data->width) {
            if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
              if (!(cell->column % 4)) {
                f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
              }
            }
            else if (data->mode == byte_dump_mode_hexidecimal_e) {
              if (!(cell->column % 8)) {
                f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
              }
            }
            else if (data->mode == byte_dump_mode_duodecimal_e) {
              if (!(cell->column % 6)) {
                f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
              }
            }
            else if (data->mode == byte_dump_mode_octal_e) {
              if (!(cell->column % 6)) {
                f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
              }
            }
            else if (data->mode == byte_dump_mode_binary_e) {
              if (!(cell->column % 4)) {
                f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
              }
            }
            else if (data->mode == byte_dump_mode_decimal_e) {
              if (!(cell->column % 6)) {
                f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
              }
            }
          }
        }
      }
    }

    if (cell->column < data->width) {
      if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e && !invalid[current]) {
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
            fl_print_format(" U+%04_U  ", data->main->output.to.stream, unicode);
          }
          else {
            fl_print_format(" U+%06_U", data->main->output.to.stream, unicode);
          }
        }
        else {

          // Pad the sequence that are incomplete fragments of an already printed valid Unicode.
          f_print_terminated("         ", data->main->output.to.stream);
        }
      }
      else {
        if (data->mode == byte_dump_mode_hexidecimal_e) {
          if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
            f_print_terminated("      ", data->main->output.to.stream);
          }

          if (invalid[current]) {
            fl_print_format(" %[%02_uii%]", data->main->output.to.stream, data->main->context.set.error, (uint8_t) byte, data->main->context.set.error);
          }
          else {
            fl_print_format(" %02_uii", data->main->output.to.stream, (uint8_t) byte);
          }
        }
        else if (data->mode == byte_dump_mode_duodecimal_e) {
          if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
            f_print_terminated("     ", data->main->output.to.stream);
          }

          if (invalid[current]) {
            fl_print_format(" %[%03&uii%]", data->main->output.to.stream, data->main->context.set.error, (uint8_t) byte, data->main->context.set.error);
          }
          else {
            fl_print_format(" %03&uii", data->main->output.to.stream, (uint8_t) byte);
          }
        }
        else if (data->mode == byte_dump_mode_octal_e) {
          if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
            f_print_terminated("     ", data->main->output.to.stream);
          }

          if (invalid[current]) {
            fl_print_format(" %[%03@uii%]", data->main->output.to.stream, data->main->context.set.error, (uint8_t) byte, data->main->context.set.error);
          }
          else {
            fl_print_format(" %03@uii", data->main->output.to.stream, (uint8_t) byte);
          }
        }
        else if (data->mode == byte_dump_mode_binary_e) {
          if (invalid[current]) {
            fl_print_format(" %[%08!uii%]", data->main->output.to.stream, data->main->context.set.error, (uint8_t) byte, data->main->context.set.error);
          }
          else {
            fl_print_format(" %08!uii", data->main->output.to.stream, (uint8_t) byte);
          }
        }
        else if (data->mode == byte_dump_mode_decimal_e) {
          if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
            f_print_terminated("     ", data->main->output.to.stream);
          }

          if (invalid[current]) {
            fl_print_format(" %[%3uii%]", data->main->output.to.stream, data->main->context.set.error, (uint8_t) byte, data->main->context.set.error);
          }
          else {
            fl_print_format(" %3uii", data->main->output.to.stream, (uint8_t) byte);
          }
        }
      }

      ++cell->column;
    }

    if (cell->column == data->width) {
      uint8_t bytes = 0;

      if (byte_current < width_utf) {
        bytes = width_utf - byte_current;
      }

      reset = F_true;

      if (data->main->parameters.array[byte_dump_parameter_text_e].result == f_console_result_found_e) {
        byte_dump_print_text(data, sequence, invalid, previous, offset);
      }
      else {
        f_print_dynamic_raw(f_string_eol_s, data->main->output.to.stream);
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
      if (data->main->parameters.array[byte_dump_parameter_unicode_e].result == f_console_result_found_e) {
        if (!(cell->column % 4)) {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
      }
      else if (data->mode == byte_dump_mode_hexidecimal_e) {
        if (!(cell->column % 8)) {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
      }
      else if (data->mode == byte_dump_mode_duodecimal_e) {
        if (!(cell->column % 6)) {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
      }
      else if (data->mode == byte_dump_mode_octal_e) {
        if (!(cell->column % 6)) {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
      }
      else if (data->mode == byte_dump_mode_binary_e) {
        if (!(cell->column % 4)) {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
      }
      else if (data->mode == byte_dump_mode_decimal_e) {
        if (!(cell->column % 6)) {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
      }
    }

    return reset;
  }
#endif // _di_byte_dump_print_character_fragment_

#ifndef _di_byte_dump_print_text_
  void byte_dump_print_text(byte_dump_data_t * const data, const f_utf_string_static_t sequence, const f_char_t invalid[], byte_dump_previous_t *previous, f_char_t *offset) {

    f_char_t c = 0;
    uint8_t at = 0;
    uint8_t width_utf = 0;
    bool print = F_true;

    f_char_t byte[5] = { 0, 0, 0, 0, 0 };

    fl_print_format("  %[%r%] ", data->main->output.to.stream, data->main->context.set.notable, byte_dump_character_wall_s, data->main->context.set.notable);

    if (*offset) {
      if (data->main->parameters.array[byte_dump_parameter_classic_e].result == f_console_result_found_e) {
        while (*offset && at < data->width) {

          f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);

          if (data->options & byte_dump_option_wide_d) {
            f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
          }

          --(*offset);
          ++at;
        } // while
      }
      else {
        if (data->main->parameters.array[byte_dump_parameter_placeholder_e].result == f_console_result_found_e) {
          for (; *offset && at < data->width; --(*offset), ++at) {

            fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.warning, byte_dump_character_placeholder_s, data->main->context.set.warning);

            if (data->options & byte_dump_option_wide_d) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }
          } // for
        }
        else {
          for (; *offset && at < data->width; --(*offset), ++at) {

            f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);

            if (data->options & byte_dump_option_wide_d) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }
          } // for
        }
      }
    }

    // Print placeholders for the remaining fragments of UTF-8 sequence printed on previous lines.
    if (at < data->width) {
      uint8_t bytes_overflow = 0;

      if (previous->bytes - 1 > data->width) {
        bytes_overflow = previous->bytes - 1 - data->width;
      }

      if (previous->bytes) {
        if (data->main->parameters.array[byte_dump_parameter_placeholder_e].result == f_console_result_found_e) {
          for (; at < previous->bytes && at < data->width; ++at) {

            if (previous->invalid) {
              fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.error, byte_dump_character_placeholder_s, data->main->context.set.error);
            }
            else if (data->main->parameters.array[byte_dump_parameter_classic_e].result == f_console_result_found_e) {
              f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);
            }
            else {
              fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.warning, byte_dump_character_placeholder_s, data->main->context.set.warning);
            }

            if (data->options & byte_dump_option_wide_d) {
              f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
            }
          } // for
        }
        else {
          for (; at < previous->bytes && at < data->width; ++at) {

            f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);

            if (data->options & byte_dump_option_wide_d) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
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

    for (uint8_t i = 0; i < sequence.used && at < data->width; ++i, ++at) {

      c = macro_f_utf_char_t_to_char_1(sequence.string[i]);
      width_utf = macro_f_utf_byte_width_is(c);

      if (invalid[i]) {
        fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.error, byte_dump_character_incomplete_s, data->main->context.set.error);

        if (data->options & byte_dump_option_wide_d) {
          f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
        }
      }
      else if (f_utf_character_is_control(sequence.string[i]) == F_true) {
        if (data->presentation == byte_dump_presentation_normal_e) {
          fl_print_format("%[%[", data->main->output.to.stream, data->main->context.set.notable, data->main->context.set.warning);

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

            f_print_safely(byte, width_utf, data->main->output.to.stream);
          }
          else {
            f_print_character_safely(c, data->main->output.to.stream);
          }

          fl_print_format("%]%]", data->main->output.to.stream, data->main->context.set.warning, data->main->context.set.notable);

          if (data->options & byte_dump_option_wide_d) {
            if (f_utf_character_is_wide(sequence.string[i]) != F_true) {
              f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
            }
          }
        }
        else {
          if (data->presentation == byte_dump_presentation_simple_e) {
            f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);

            if (width_utf > 1) {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);

              if (width_utf > 2) {
                f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);

                if (width_utf > 3) {
                  f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
                }
              }
            }
          }
          else if (data->presentation == byte_dump_presentation_classic_e) {
            f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);

            if (width_utf > 1) {
              f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);

              if (width_utf > 2) {
                f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);

                if (width_utf > 3) {
                  f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);
                }
              }
            }
          }

          if (data->options & byte_dump_option_wide_d) {
            f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
          }
        }
      }
      else if (f_utf_character_is_whitespace(sequence.string[i], F_true) == F_true) {
        if (data->main->parameters.array[byte_dump_parameter_classic_e].result == f_console_result_found_e) {
          f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);
        }
        else {
          fl_print_format("%[%[%r%]%]", data->main->output.to.stream, data->main->context.set.notable, data->main->context.set.warning, f_print_sequence_space_s, data->main->context.set.warning, data->main->context.set.notable);
        }

        if (data->options & byte_dump_option_wide_d) {
          f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
        }
      }
      else if (f_utf_character_is_zero_width(sequence.string[i]) == F_true) {
        if (data->presentation == byte_dump_presentation_classic_e) {
          f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);
        }
        else if (data->main->parameters.array[byte_dump_parameter_placeholder_e].result == f_console_result_found_e) {
          fl_print_format("%[%[%r%]%]", data->main->output.to.stream, data->main->context.set.notable, data->main->context.set.warning, byte_dump_character_placeholder_s, data->main->context.set.warning, data->main->context.set.notable);
        }
        else {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }

        if (data->options & byte_dump_option_wide_d) {
          f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
        }
      }
      else if (width_utf) {
        print = F_false;

        if (width_utf == 1) {

          // Print invalid placeholder for invalid UTF-8 widths.
          if (invalid[i]) {
            fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.error, byte_dump_character_incomplete_s, data->main->context.set.error);
          }
          else {
            fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.warning, byte_dump_character_incomplete_s, data->main->context.set.warning);
          }
        }
        else if (width_utf == 2) {
          print = F_true;
        }
        else if (width_utf == 3) {
          if (sequence.string[i] >= 0xefbfb000 && sequence.string[i] <= 0xefbfbc00) {

            // Use space to represent Specials codes.
            // 0xefbfbd00 is excluded because it is printable (and is the "Replacement Character" code).
            f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
          }
          else if (sequence.string[i] >= 0xe290a700 && sequence.string[i] <= 0xe290bf00) {

            // Use space to represent Control Pictues codes that are not currently defined but are reserved.
            f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
          }
          else if (sequence.string[i] >= 0xee808000 && sequence.string[i] <= 0xefa3bf00) {

            // Use space to represent Private Use Area codes.
            f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
          }
          else {
            print = F_true;
          }
        }
        else if (sequence.string[i] >= 0xf09c80a0 && sequence.string[i] <= 0xf09c80bd) {

          // Use space to represent Variation Selectors Supplement codes.
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
        else if (sequence.string[i] >= 0xf3b08080 && sequence.string[i] <= 0xf3bfbfbf) {

          // Use space to represent Supplemental Private Use Area-A codes.
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
        else if (sequence.string[i] >= 0xf4808080 && sequence.string[i] <= 0xf48fbfbf) {

          // Use space to represent Supplemental Private Use Area-B codes.
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
        else {
          print = F_true;
        }

        if (print) {
          f_print_character(c, data->main->output.to.stream);

          if (width_utf > 1) {
            f_print_character(macro_f_utf_char_t_to_char_2(sequence.string[i]), data->main->output.to.stream);

            if (width_utf > 2) {
              f_print_character(macro_f_utf_char_t_to_char_3(sequence.string[i]), data->main->output.to.stream);

              if (width_utf > 3) {
                f_print_character(macro_f_utf_char_t_to_char_4(sequence.string[i]), data->main->output.to.stream);
              }
            }
          }

          if (f_utf_character_is_combining(sequence.string[i]) == F_true) {
            f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
          }

          if (data->options & byte_dump_option_wide_d) {
            if (width_utf == 1 || f_utf_character_is_wide(sequence.string[i]) != F_true) {
              f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
            }
          }
        }
        else {
          if (data->options & byte_dump_option_wide_d) {
            f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
          }
        }
      }
      else {
        f_print_character(c, data->main->output.to.stream);

        if (data->options & byte_dump_option_wide_d) {
          f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
        }
      }

      // Print placeholders when using UTF-8 sequence to simulate the spaces bytes used for the character.
      if (width_utf > 1 && at + 1 < data->width) {
        if (data->main->parameters.array[byte_dump_parameter_placeholder_e].result == f_console_result_found_e) {
          if (invalid[i]) {
            fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.error, byte_dump_character_placeholder_s, data->main->context.set.error);
          }
          else if (data->main->parameters.array[byte_dump_parameter_classic_e].result == f_console_result_found_e) {
            f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);
          }
          else {
            fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.warning, byte_dump_character_placeholder_s, data->main->context.set.warning);
          }
        }
        else {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }

        if (data->options & byte_dump_option_wide_d) {
          f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
        }

        ++at;

        if (width_utf > 2 && at + 1 < data->width) {
          if (data->main->parameters.array[byte_dump_parameter_placeholder_e].result == f_console_result_found_e) {
            if (invalid[i]) {
              fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.error, byte_dump_character_placeholder_s, data->main->context.set.error);
            }
            else if (data->main->parameters.array[byte_dump_parameter_classic_e].result == f_console_result_found_e) {
              f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);
            }
            else {
              fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.warning, byte_dump_character_placeholder_s, data->main->context.set.warning);
            }
          }
          else {
            f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
          }

          if (data->options & byte_dump_option_wide_d) {
            f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
          }

          ++at;

          if (width_utf > 3 && at + 1 < data->width) {
            if (data->main->parameters.array[byte_dump_parameter_placeholder_e].result == f_console_result_found_e) {
              if (invalid[i]) {
                fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.error, byte_dump_character_placeholder_s, data->main->context.set.error);
              }
              else if (data->main->parameters.array[byte_dump_parameter_classic_e].result == f_console_result_found_e) {
                f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);
              }
              else {
                fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.warning, byte_dump_character_placeholder_s, data->main->context.set.warning);
              }
            }
            else {
              f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
            }

            if (data->options & byte_dump_option_wide_d) {
              f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
            }

            ++at;
          }
        }
      }
    } // for

    // Print placeholder for the remaining parts of the line.
    if (data->main->parameters.array[byte_dump_parameter_placeholder_e].result == f_console_result_found_e) {
      for (; at < data->width; ++at) {

        if (invalid[at]) {
          fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.error, byte_dump_character_placeholder_s, data->main->context.set.error);
        }
        else if (data->main->parameters.array[byte_dump_parameter_classic_e].result == f_console_result_found_e) {
          f_print_dynamic_raw(f_string_ascii_period_s, data->main->output.to.stream);
        }
        else {
          fl_print_format("%[%r%]", data->main->output.to.stream, data->main->context.set.warning, byte_dump_character_placeholder_s, data->main->context.set.warning);
        }

        if (data->options & byte_dump_option_wide_d) {
          f_print_dynamic_raw(f_string_ascii_space_s, data->main->output.to.stream);
        }
      } // for
    }
    else {
      for (; at < data->width; ++at) {

        f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);

        if (data->options & byte_dump_option_wide_d) {
          f_print_dynamic_raw(f_string_space_s, data->main->output.to.stream);
        }
      } // for
    }

    fl_print_format(" %[%r%]%r", data->main->output.to.stream, data->main->context.set.notable, byte_dump_character_wall_s, data->main->context.set.notable, f_string_eol_s);
  }
#endif // _di_byte_dump_print_text_

#ifdef __cplusplus
} // extern "C"
#endif
