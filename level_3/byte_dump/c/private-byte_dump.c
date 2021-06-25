#include "byte_dump.h"
#include "private-common.h"
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_file_
  f_status_t byte_dump_file(const byte_dump_main_t main, const f_string_t file_name, const f_file_t file) {

    f_status_t status = F_none;

    uint64_t position = 0;
    char byte = 0;
    int byte_get = 0;
    uint8_t offset = 0;

    int8_t width_utf = -1;
    int8_t width_current = 0;
    int8_t width_count = 0;

    byte_dump_cell_t cell = byte_dump_cell_t_initialize;
    byte_dump_previous_t previous = byte_dump_previous_t_initialize;

    bool character_reset = 0;
    bool found_invalid_utf = F_false;

    // Store the current character main until it can be printed.
    f_utf_string_dynamic_t characters = f_utf_string_dynamic_t_initialize;
    f_utf_character_t character_array[main.width];
    f_array_length_t character_current = 0;

    // The row starts based on the first byte starting point and how many columns of bytes are displayed per row.
    if (main.first > 0) {
      cell.row = main.first / main.width;
      offset = main.first % main.width;

      // fseek() cannot be used on a PIPE, so read instead of seek.
      if (file_name) {
        byte_get = fseek(file.stream, main.first, SEEK_SET);
      }
      else {
        char skip[main.first];

        byte_get = fread(skip, sizeof(char), main.first, file.stream);
      }
    }

    memset(&character_array, 0, sizeof(f_utf_character_t) * main.width);
    characters.string = character_array;
    characters.used = 0;
    characters.size = main.width;

    // Record when a character is invalid.
    char invalid[main.width];
    memset(&invalid, 0, sizeof(char) * main.width);

    if (byte_get >= 0) {
      for (;;) {

        byte_get = getc(file.stream);

        if (byte_get < 0) break;

        byte = (char) byte_get;

        // Storing the next character is designated by width_utf == -1.
        if (width_utf == -1) {
          width_utf = macro_f_utf_byte_width_is(byte);
          width_count = 0;

          // The character is reset, the characters.used is to be reset.
          if (character_reset) {
            characters.used = 0;
            character_reset = F_false;
            memset(&invalid, 0, sizeof(uint8_t) * main.width);
          }

          character_current = characters.used;
          ++characters.used;

          invalid[character_current] = 0;
        }

        // When width_count == 0, then this is that start of a new character sequence.
        if (!width_count) {
          characters.string[character_current] = macro_f_utf_character_t_from_char_1(byte);
          width_count = 1;

          // The first character in a UTF-8 sequence cannot have a width of 1.
          if (width_utf == 1) {
            found_invalid_utf = F_true;
            invalid[character_current] = 1;
          }
          // Process the UTF-8 character.
          else if (width_utf > 1) {
            continue;
          }
        }
        // Process a UTF-8 character fragment.
        else if (width_count < width_utf) {
          width_current = macro_f_utf_byte_width_is(byte);

          if (width_count == 1) {
            characters.string[character_current] |= macro_f_utf_character_t_from_char_2(byte);
          }
          else if (width_count == 2) {
            characters.string[character_current] |= macro_f_utf_character_t_from_char_3(byte);
          }
          else if (width_count == 3) {
            characters.string[character_current] |= macro_f_utf_character_t_from_char_4(byte);
          }

          ++width_count;

          // UTF-8 character fragments must have a width of 1 (and ASCII characters can only be the first character in a sequence).
          if (width_current == 1) {

            // Grab the next UTF-8 character fragment if the entire sequence is not collected yet.
            if (width_count < width_utf) continue;
          }
          else {
            found_invalid_utf = F_true;
            invalid[character_current] = width_utf;
          }
        }

        // At this point: an ASCII character is collected, the entire UTF-8 character sequence is collected, or an invalid UTF-8 was processed.
        if (!invalid[character_current] && width_utf > 1) {
          if (f_utf_character_is_valid(characters.string[character_current]) == F_false) {
            found_invalid_utf = F_true;
            invalid[character_current] = width_utf;
          }
        }

        if (byte_dump_print_character_fragment(main, characters, invalid, width_utf, 1, &previous, &cell, &offset) == F_true) {
          character_reset = F_true;
        }

        if (width_utf > 1) {
          if (byte_dump_print_character_fragment(main, characters, invalid, width_utf, 2, &previous, &cell, &offset) == F_true) {
            character_reset = F_true;
          }

          if (width_utf > 2) {
            if (byte_dump_print_character_fragment(main, characters, invalid, width_utf, 3, &previous, &cell, &offset) == F_true) {
              character_reset = F_true;
            }

            if (width_utf > 3) {
              if (byte_dump_print_character_fragment(main, characters, invalid, width_utf, 4, &previous, &cell, &offset) == F_true) {
                character_reset = F_true;
              }
            }
          }

          if (main.last) {
            position += width_utf;

            if (position >= main.last) break;
          }
        }
        else if (main.last) {
          ++position;

          if (position >= main.last) break;
        }

        width_utf = -1;
      } // for
    }

    // Print placeholders to fill out the remaining line and then optionally print the text block.
    if (cell.column > 0 && cell.column < main.width) {
      previous.bytes = 0;
      previous.invalid = 0;

      while (cell.column < main.width) {

        if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
          fprintf(main.output.stream, "         ");
        }
        else if (main.mode == byte_dump_mode_hexidecimal) {
          fprintf(main.output.stream, "   ");
        }
        else if (main.mode == byte_dump_mode_duodecimal) {
          fprintf(main.output.stream, "    ");
        }
        else if (main.mode == byte_dump_mode_octal) {
          fprintf(main.output.stream, "    ");
        }
        else if (main.mode == byte_dump_mode_binary) {
          fprintf(main.output.stream, "         ");
        }
        else if (main.mode == byte_dump_mode_decimal) {
          fprintf(main.output.stream, "    ");
        }

        ++cell.column;

        if (cell.column < main.width) {
          if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
            if (!(cell.column % 4)) {
              fprintf(main.output.stream, "%s", f_string_space_s);
            }
          }
          else if (main.mode == byte_dump_mode_hexidecimal) {
            if (!(cell.column % 8)) {
              fprintf(main.output.stream, "%s", f_string_space_s);
            }
          }
          else if (main.mode == byte_dump_mode_duodecimal) {
            if (!(cell.column % 6)) {
              fprintf(main.output.stream, "%s", f_string_space_s);
            }
          }
          else if (main.mode == byte_dump_mode_octal) {
            if (!(cell.column % 6)) {
              fprintf(main.output.stream, "%s", f_string_space_s);
            }
          }
          else if (main.mode == byte_dump_mode_binary) {
            if (!(cell.column % 6)) {
              fprintf(main.output.stream, "%s", f_string_space_s);
            }
          }
          else if (main.mode == byte_dump_mode_decimal) {
            if (!(cell.column % 6)) {
              fprintf(main.output.stream, "%s", f_string_space_s);
            }
          }
        }
      } // while

      if (main.parameters[byte_dump_parameter_text].result == f_console_result_found) {
        byte_dump_print_text(main, characters, invalid, &previous, &offset);
      }
      else {
        fprintf(main.output.stream, "%c", f_string_eol_s[0]);
      }
    }

    fprintf(main.output.stream, "%c", f_string_eol_s[0]);

    // make sure to flush standard out to help prevent standard error from causing poblems.
    fflush(main.output.stream);

    if (found_invalid_utf) {
      f_color_print(main.error.to.stream, main.context.set.error, "Invalid UTF-8 codes were detected for file '");
      f_color_print(main.error.to.stream, main.context.set.notable, "%s", file_name ? file_name : "-");
      f_color_print(main.error.to.stream, main.context.set.error, "'.");
      fprintf(main.error.to.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);
    }

    if (ferror(file.stream)) {
      // @todo: determine what the error is and display it.
      f_color_print(main.error.to.stream, main.context.set.error, "%sread() failed for '", fll_error_print_error);
      f_color_print(main.error.to.stream, main.context.set.notable, "%s", file_name ? file_name : "-");
      f_color_print(main.error.to.stream, main.context.set.error, "'.");
      fprintf(main.error.to.stream, "%c%c", f_string_eol_s[0], f_string_eol_s[0]);

      status = F_status_set_error(F_failure);
    }

    fflush(main.error.to.stream);

    return status;
  }
#endif // _di_byte_dump_file_

#ifndef _di_byte_dump_print_character_fragment_
  bool byte_dump_print_character_fragment(const byte_dump_main_t main, const f_utf_string_static_t characters, const char invalid[], const uint8_t width_utf, const char byte_current, byte_dump_previous_t *previous, byte_dump_cell_t *cell, uint8_t *offset) {
    char byte = 0;

    bool reset = F_false;

    f_array_length_t character_current = characters.used - 1;

    if (byte_current == 1) {
      byte = macro_f_utf_character_t_to_char_1(characters.string[character_current]);
    }
    else if (byte_current == 2) {
      byte = macro_f_utf_character_t_to_char_2(characters.string[character_current]);
    }
    else if (byte_current == 3) {
      byte = macro_f_utf_character_t_to_char_3(characters.string[character_current]);
    }
    else if (byte_current == 4) {
      byte = macro_f_utf_character_t_to_char_4(characters.string[character_current]);
    }

    if (!cell->column) {
      f_color_print(main.output.stream, main.context.set.notable, "%016X ", (uint64_t) cell->row);

      if (*offset) {
        uint8_t offset_to_print = *offset;

        // Pad the buffer with spaces to hide any skipped bytes (skipped via --first).
        while (offset_to_print && cell->column < main.width) {

          if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
            fprintf(main.output.stream, "         ");
          }
          else if (main.mode == byte_dump_mode_hexidecimal) {
            fprintf(main.output.stream, "   ");
          }
          else if (main.mode == byte_dump_mode_duodecimal) {
            fprintf(main.output.stream, "    ");
          }
          else if (main.mode == byte_dump_mode_octal) {
            fprintf(main.output.stream, "    ");
          }
          else if (main.mode == byte_dump_mode_binary) {
            fprintf(main.output.stream, "         ");
          }
          else if (main.mode == byte_dump_mode_decimal) {
            fprintf(main.output.stream, "    ");
          }

          --offset_to_print;
          ++cell->column;

          if (cell->column < main.width) {
            if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
              if (!(cell->column % 4)) {
                fprintf(main.output.stream, "%s", f_string_space_s);
              }
            }
            else if (main.mode == byte_dump_mode_hexidecimal) {
              if (!(cell->column % 8)) {
                fprintf(main.output.stream, "%s", f_string_space_s);
              }
            }
            else if (main.mode == byte_dump_mode_duodecimal) {
              if (!(cell->column % 6)) {
                fprintf(main.output.stream, "%s", f_string_space_s);
              }
            }
            else if (main.mode == byte_dump_mode_octal) {
              if (!(cell->column % 6)) {
                fprintf(main.output.stream, "%s", f_string_space_s);
              }
            }
            else if (main.mode == byte_dump_mode_binary) {
              if (!(cell->column % 4)) {
                fprintf(main.output.stream, "%s", f_string_space_s);
              }
            }
            else if (main.mode == byte_dump_mode_decimal) {
              if (!(cell->column % 6)) {
                fprintf(main.output.stream, "%s", f_string_space_s);
              }
            }
          }
        }
      }
    }

    if (cell->column < main.width) {
      if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found && !invalid[character_current]) {
        if (byte_current == 1) {
          uint32_t unicode = 0;

          if (width_utf < 2) {

            // 1 == U+0000 -> U+007F
            unicode = macro_f_utf_character_t_to_char_1(characters.string[character_current]) & 0x7f;
          }
          else if (width_utf == 2) {

            // 2 == U+0080 -> U+07FF
            unicode = (macro_f_utf_character_t_to_char_1(characters.string[character_current]) & 0x1f) << 6;
            unicode |= macro_f_utf_character_t_to_char_2(characters.string[character_current]) & 0x3f;
          }
          else if (width_utf == 3) {

            // 3 == U+0800 -> U+FFFF
            unicode = (macro_f_utf_character_t_to_char_1(characters.string[character_current]) & 0xf) << 12;
            unicode |= (macro_f_utf_character_t_to_char_2(characters.string[character_current]) & 0x3f) << 6;
            unicode |= macro_f_utf_character_t_to_char_3(characters.string[character_current]) & 0x3f;
          }
          else if (width_utf == 4) {

            // 4 == U+10000 -> U+10FFFF
            unicode = (macro_f_utf_character_t_to_char_1(characters.string[character_current]) & 0x7) << 18;
            unicode |= (macro_f_utf_character_t_to_char_2(characters.string[character_current]) & 0x3f) << 12;
            unicode |= (macro_f_utf_character_t_to_char_2(characters.string[character_current]) & 0x3f) << 6;
            unicode |= macro_f_utf_character_t_to_char_4(characters.string[character_current]) & 0x3f;
          }

          if (width_utf < 4) {
            fprintf(main.output.stream, " U+%04X  ", (uint32_t) unicode);
          }
          else {
            fprintf(main.output.stream, " U+%06X", (uint32_t) unicode);
          }
        }
        else {

          // Pad the characters that are incomplete fragments of an already printed valid Unicode.
          fprintf(main.output.stream, "         ");
        }
      }
      else {
        if (main.mode == byte_dump_mode_hexidecimal) {
          if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
            fprintf(main.output.stream, "      ");
          }

          if (invalid[character_current]) {
            f_color_print(main.output.stream, main.context.set.error, " %02x", (uint8_t) byte);
          }
          else {
            fprintf(main.output.stream, " %02x", (uint8_t) byte);
          }
        }
        else if (main.mode == byte_dump_mode_duodecimal) {
          if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
            fprintf(main.output.stream, "   ");
          }

          if (invalid[character_current]) {
            fprintf(main.output.stream, "%s", main.context.error.string);
          }

          fprintf(main.output.stream, " %01d", byte / 144);

          uint8_t current = (byte % 144) / 12;

          if (current == 11) {
            fprintf(main.output.stream, "%s", f_string_ascii_b_s);
          }
          else if (current == 10) {
            fprintf(main.output.stream, "%s", f_string_ascii_a_s);
          }
          else {
            fprintf(main.output.stream, "%01d", current);
          }

          current = (byte % 144) % 12;

          if (current == 11) {
            fprintf(main.output.stream, "%s", f_string_ascii_b_s);
          }
          else if (current == 10) {
            fprintf(main.output.stream, "%s", f_string_ascii_a_s);
          }
          else {
            fprintf(main.output.stream, "%01d", current);
          }

          if (invalid[character_current]) {
            fprintf(main.output.stream, "%s", main.context.reset.string);
          }
        }
        else if (main.mode == byte_dump_mode_octal) {
          if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
            fprintf(main.output.stream, "     ");
          }

          if (invalid[character_current]) {
            f_color_print(main.output.stream, main.context.set.error, " %03o", (uint8_t) byte);
          }
          else {
            fprintf(main.output.stream, " %03o", (uint8_t) byte);
          }
        }
        else if (main.mode == byte_dump_mode_binary) {
          char binary_string[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

          binary_string[0] = ((byte >> 7) & 0x01) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[0];
          binary_string[1] = ((byte >> 6) & 0x01) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[0];
          binary_string[2] = ((byte >> 5) & 0x01) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[0];
          binary_string[3] = ((byte >> 4) & 0x01) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[0];
          binary_string[4] = ((byte >> 3) & 0x01) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[0];
          binary_string[5] = ((byte >> 2) & 0x01) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[0];
          binary_string[6] = ((byte >> 1) & 0x01) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[0];
          binary_string[7] = (byte & 0x01) ? f_string_ascii_1_s[0] : f_string_ascii_0_s[0];

          if (invalid[character_current]) {
            f_color_print(main.output.stream, main.context.set.error, " %s", binary_string);
          }
          else {
            fprintf(main.output.stream, " %s", binary_string);
          }
        }
        else if (main.mode == byte_dump_mode_decimal) {
          if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
            fprintf(main.output.stream, "     ");
          }

          if (invalid[character_current]) {
            f_color_print(main.output.stream, main.context.set.error, " %3d", (uint8_t) byte);
          }
          else {
            fprintf(main.output.stream, " %3d", (uint8_t) byte);
          }
        }
      }

      ++cell->column;
    }

    if (cell->column == main.width) {
      uint8_t bytes = 0;

      if (byte_current < width_utf) {
        bytes = width_utf - byte_current;
      }

      reset = F_true;

      if (main.parameters[byte_dump_parameter_text].result == f_console_result_found) {
        byte_dump_print_text(main, characters, invalid, previous, offset);
      }
      else {
        fprintf(main.output.stream, "%c", f_string_eol_s[0]);
      }

      cell->column = 0;
      ++cell->row;

      if (!bytes) {
        previous->bytes = 0;
        previous->invalid = 0;
      }
      else {
        previous->bytes = bytes;
        previous->invalid = invalid[character_current];
      }
    }
    else {
      if (main.parameters[byte_dump_parameter_unicode].result == f_console_result_found) {
        if (!(cell->column % 4)) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
      else if (main.mode == byte_dump_mode_hexidecimal) {
        if (!(cell->column % 8)) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
      else if (main.mode == byte_dump_mode_duodecimal) {
        if (!(cell->column % 6)) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
      else if (main.mode == byte_dump_mode_octal) {
        if (!(cell->column % 6)) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
      else if (main.mode == byte_dump_mode_binary) {
        if (!(cell->column % 4)) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
      else if (main.mode == byte_dump_mode_decimal) {
        if (!(cell->column % 6)) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
    }

    return reset;
  }
#endif // _di_byte_dump_print_character_fragment_

#ifndef _di_byte_dump_print_text_
  void byte_dump_print_text(const byte_dump_main_t main, const f_utf_string_static_t characters, const char invalid[], byte_dump_previous_t *previous, uint8_t *offset) {
    uint8_t j = 0;
    uint8_t output = 0;
    uint8_t width_utf = 0;
    bool printed = F_false;

    f_color_print(main.output.stream, main.context.set.notable, "  %s ", byte_dump_character_wall);

    if (*offset > 0) {
      if (main.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
        while (*offset > 0 && j < main.width) {
          fprintf(main.output.stream, "%s", f_string_ascii_period_s);
          --(*offset);
          ++j;
        } // while
      }
      else {
        const char *placeholder = f_string_space_s;

        if (main.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          placeholder = byte_dump_character_placeholder;
        }

        while (*offset > 0 && j < main.width) {
          f_color_print(main.output.stream, main.context.set.warning, "%s", placeholder);
          --(*offset);
          ++j;
        } // while
      }
    }

    // Print placeholders for the remaining fragments of UTF-8 characters printed on previous lines.
    if (j < main.width) {
      uint8_t bytes_overflow = 0;

      if (previous->bytes - 1 > main.width) {
        bytes_overflow = previous->bytes - 1 - main.width;
      }

      if (previous->bytes > 0) {
        if (main.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          for (; j < previous->bytes && j < main.width; ++j) {

            if (previous->invalid) {
              f_color_print(main.output.stream, main.context.set.error, "%s", byte_dump_character_placeholder);
            }
            else if (main.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
              fprintf(main.output.stream, "%s", f_string_ascii_period_s);
            }
            else {
              f_color_print(main.output.stream, main.context.set.warning, "%s", byte_dump_character_placeholder);
            }
          } // for
        }
        else {
          for (; j < previous->bytes && j < main.width; ++j) {
            fprintf(main.output.stream, "%s", f_string_space_s);
          } // for
        }
      }

      if (bytes_overflow > 0) {
        previous->bytes = bytes_overflow;
      }
      else {
        previous->bytes = 0;
        previous->invalid = 0;
      }
    }

    for (uint8_t i = 0; i < characters.used && j < main.width; ++i, ++j) {

      output = macro_f_utf_character_t_to_char_1(characters.string[i]);
      width_utf = macro_f_utf_byte_width_is(output);

      if (invalid[i]) {
        f_color_print(main.output.stream, main.context.set.error, "%s", byte_dump_character_incomplete);
      }
      else if (output >= 0 && output <= 32 || output == 127) {
        if (main.presentation == byte_dump_presentation_normal) {
          if (!output) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_null);
          }
          else if (output == 1) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_start_of_header);
          }
          else if (output == 2) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_start_of_text);
          }
          else if (output == 3) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_end_of_text);
          }
          else if (output == 4) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_end_of_transmission);
          }
          else if (output == 5) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_end_of_enquiry);
          }
          else if (output == 6) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_acknowledge);
          }
          else if (output == 7) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_bell);
          }
          else if (output == 8) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_backspace);
          }
          else if (output == 9) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_tab);
          }
          else if (output == 10) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_new_line);
          }
          else if (output == 11) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_tab_vertical);
          }
          else if (output == 12) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_form_feed);
          }
          else if (output == 13) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_carriage_return);
          }
          else if (output == 14) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_shift_out);
          }
          else if (output == 15) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_shift_in);
          }
          else if (output == 16) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_data_link_escape);
          }
          else if (output == 17) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_device_control_1);
          }
          else if (output == 18) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_device_control_2);
          }
          else if (output == 19) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_device_control_3);
          }
          else if (output == 20) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_device_control_4);
          }
          else if (output == 21) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_negative_acknowledge);
          }
          else if (output == 22) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_synchronous_idle);
          }
          else if (output == 23) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_end_of_transmission_block);
          }
          else if (output == 24) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_cancel);
          }
          else if (output == 25) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_end_of_medium);
          }
          else if (output == 26) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_substitute);
          }
          else if (output == 27) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_escape);
          }
          else if (output == 28) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_file_separator);
          }
          else if (output == 29) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_group_separator);
          }
          else if (output == 30) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_record_separator);
          }
          else if (output == 31) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_unit_separator);
          }
          else if (output == 32) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_space);
          }
          else if (output == 127) {
            f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_delete);
          }
        }
        else if (main.presentation == byte_dump_presentation_simple) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (main.presentation == byte_dump_presentation_classic) {
          fprintf(main.output.stream, "%s", f_string_ascii_period_s);
        }
      }
      else if (f_utf_character_is_whitespace(characters.string[i]) == F_true) {
        if (main.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
          fprintf(main.output.stream, "%s", f_string_ascii_period_s);
        }
        else {
          f_color_print2(main.output.stream, main.context.set.notable, main.context.set.warning, "%s", byte_dump_sequence_space);
        }
      }
      else if (f_utf_character_is_zero_width(characters.string[i]) == F_true) {
        if (main.presentation == byte_dump_presentation_classic) {
          fprintf(main.output.stream, "%s", f_string_ascii_period_s);
        }
        else if (main.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          f_color_print(main.output.stream, main.context.set.warning, "%s", byte_dump_character_placeholder);
        }
        else {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
      else if (f_utf_character_is_control(characters.string[i]) == F_true) {
        // print a space (or '.') for control characters.
        if (main.presentation == byte_dump_presentation_classic) {
          f_color_print(main.output.stream, main.context.set.warning, f_string_ascii_period_s);
        }
        else {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
      else if (width_utf == 2 && characters.string[i] == 0xd89d0000) {
        // U+061C
        fprintf(main.output.stream, "%s", f_string_space_s);
      }
      else if (width_utf == 3 && characters.string[i] >= 0xefbfb000 && characters.string[i] <= 0xefbfbc00) {
        // Use space to represent Specials codes.
        // 0xefbfbd00 is excluded because it is printable (and is the "Replacement Character" code).
        fprintf(main.output.stream, "%s", f_string_space_s);
      }
      else if (width_utf == 3 && characters.string[i] >= 0xe290a700 && characters.string[i] <= 0xe290bf00) {
        // Use space to represent Control Pictues codes that are not currently defined but are reserved.
        fprintf(main.output.stream, "%s", f_string_space_s);
      }
      else if (width_utf == 3 && characters.string[i] >= 0xee808000 && characters.string[i] <= 0xefa3bf00) {
        // Use space to represent Private Use Area codes.
        fprintf(main.output.stream, "%s", f_string_space_s);
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf09c80a0 && characters.string[i] <= 0xf09c80bd) {
        // Use space to represent Vaiation Selectors Supplement codes.
        fprintf(main.output.stream, "%s", f_string_space_s);
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf3b08080 && characters.string[i] <= 0xf3bfbfbf) {
        // Use space to represent Supplemental Private Use Area-A codes.
        fprintf(main.output.stream, "%s", f_string_space_s);
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf4808080 && characters.string[i] <= 0xf48fbfbf) {
        // Use space to represent Supplemental Private Use Area-B codes.
        fprintf(main.output.stream, "%s", f_string_space_s);
      }
      else if (width_utf == 1) {
        // print invalid placeholder for invalid UTF-8 widths.
        if (invalid[i]) {
          f_color_print(main.output.stream, main.context.set.error, "%s", byte_dump_character_incomplete);
        }
        else {
          f_color_print(main.output.stream, main.context.set.warning, "%s", byte_dump_character_incomplete);
        }
      }
      else if (width_utf > 0) {
        fprintf(main.output.stream, "%c", (uint8_t) output);

        if (width_utf > 1) {
          output = macro_f_utf_character_t_to_char_2(characters.string[i]);
          fprintf(main.output.stream, "%c", (uint8_t) output);

          if (width_utf > 2) {
            output = macro_f_utf_character_t_to_char_3(characters.string[i]);
            fprintf(main.output.stream, "%c", (uint8_t) output);

            if (width_utf > 3) {
              output = macro_f_utf_character_t_to_char_4(characters.string[i]);
              fprintf(main.output.stream, "%c", (uint8_t) output);
            }
          }
        }

        // @todo: implement a function in f_utf, such as f_utf_is_combining(), for detecting these combining characters.
        // print a space for combining characters to combine into, thereby allowing it to be safely and readably displayed.
        if (width_utf == 2 && characters.string[i] >= 0xdea60000 && characters.string[i] <= 0xdeb00000) {
          // Thana combining codes: U+07A6 to U+07B0.
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (width_utf == 2 && characters.string[i] >= 0xcc800000 && characters.string[i] <= 0xcdaf0000) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe1aab000 && characters.string[i] <= 0xe1abbf00) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe1b78000 && characters.string[i] <= 0xe1b7bf00) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe2839000 && characters.string[i] <= 0xe283bf00) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd8900000 && characters.string[i] <= 0xd89a0000) {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd98b0000 && characters.string[i] <= 0xd99f0000) {
          // Arabic, U+064B to U+065F.
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (width_utf == 2 && characters.string[i] >= 0xdb960000 && characters.string[i] <= 0xdb9c0000) {
          // Arabic, U+06D6 to U+06DC.
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd6910000 && characters.string[i] <= 0xd6bd0000) {
          // Hebrew, U+0591 to U+05BD.
          fprintf(main.output.stream, "%s", f_string_space_s);
        }
      }
      else {
        fprintf(main.output.stream, "%c", output);
      }

      // When using UTF-8 characters, the character columns will not line up, so print placeholders to simulate the bytes that are not printed, if necessary for alignment.
      if (width_utf > 1 && j + 1 < main.width) {
        if (main.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          if (invalid[i]) {
            f_color_print(main.output.stream, main.context.set.error, "%s", byte_dump_character_placeholder);
          }
          else if (main.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
            fprintf(main.output.stream, "%s", f_string_ascii_period_s);
          }
          else {
            f_color_print(main.output.stream, main.context.set.warning, "%s", byte_dump_character_placeholder);
          }
        }
        else {
          fprintf(main.output.stream, "%s", f_string_space_s);
        }

        ++j;

        if (width_utf > 2 && j + 1 < main.width) {
          if (main.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
            if (invalid[i]) {
              f_color_print(main.output.stream, main.context.set.error, "%s", byte_dump_character_placeholder);
            }
            else if (main.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
              fprintf(main.output.stream, "%s", f_string_ascii_period_s);
            }
            else {
              f_color_print(main.output.stream, main.context.set.warning, "%s", byte_dump_character_placeholder);
            }
          }
          else {
            fprintf(main.output.stream, "%s", f_string_space_s);
          }

          ++j;

          if (width_utf > 3 && j + 1 < main.width) {
            if (main.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
              if (invalid[i]) {
                f_color_print(main.output.stream, main.context.set.error, "%s", byte_dump_character_placeholder);
              }
              else if (main.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
                fprintf(main.output.stream, "%s", f_string_ascii_period_s);
              }
              else {
                f_color_print(main.output.stream, main.context.set.warning, "%s", byte_dump_character_placeholder);
              }
            }
            else {
              fprintf(main.output.stream, "%s", f_string_space_s);
            }

            ++j;
          }
        }
      }
    } // for

    // Print placeholder for the remaining parts of the line.
    if (main.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
      for (; j < main.width; ++j) {

        if (invalid[j]) {
          f_color_print(main.output.stream, main.context.set.error, "%s", byte_dump_character_placeholder);
        }
        else if (main.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
          fprintf(main.output.stream, "%s", f_string_ascii_period_s);
        }
        else {
          f_color_print(main.output.stream, main.context.set.warning, "%s", byte_dump_character_placeholder);
        }
      } // for
    }
    else {
      for (; j < main.width; ++j) {
        fprintf(main.output.stream, "%s", f_string_space_s);
      } // for
    }

    f_color_print(main.output.stream, main.context.set.notable, " |");
    fprintf(main.output.stream, "%c", f_string_eol_s[0]);
  }
#endif // _di_byte_dump_file_

#ifdef __cplusplus
} // extern "C"
#endif
