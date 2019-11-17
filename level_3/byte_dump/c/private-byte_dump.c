#include <level_3/byte_dump.h>
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_file_
  f_return_status byte_dump_file(const byte_dump_data data, const f_string file_name, f_file file) {
    f_status status = f_none;

    uint64_t position = data.first;
    uint8_t size = 0;
    uint8_t byte = 0;
    uint8_t offset = 0;

    int8_t width_utf = -1;
    int8_t width_current = 0;
    int8_t width_count = 0;

    byte_dump_cell cell = byte_dump_cell_initialize;
    byte_dump_previous previous = byte_dump_previous_initialize;

    bool character_reset = 0;
    bool found_invalid_utf = f_false;

    // Store the current character data until it can be printed.
    f_utf_string_dynamic characters = f_utf_string_dynamic_initialize;
    f_utf_character character_array[data.width];
    f_utf_string_length character_current = 0;

    // The row starts based on the first byte starting point and how many columns of bytes are displayed per row.
    if (data.first > 0) {
      cell.row = data.first / data.width;
      offset = data.first % data.width;
    }

    memset(&character_array, 0, sizeof(f_utf_character) * data.width);
    characters.string = character_array;
    characters.used = 0;
    characters.size = data.width;

    // Record when a character is invalid.
    uint8_t invalid[data.width];
    memset(&invalid, 0, sizeof(uint8_t) * data.width);

    fseek(file.address, data.first, SEEK_SET);

    while ((size = read(file.id, &byte, 1)) > 0) {
      // Storing the next character is designated by width_utf == -1.
      if (width_utf == -1) {
        width_utf = f_macro_utf_byte_width_is(byte);
        width_count = 0;

        // The character is reset, the characters.used is to be reset.
        if (character_reset) {
          characters.used = 0;
          character_reset = f_false;
          memset(&invalid, 0, sizeof(uint8_t) * data.width);
        }

        character_current = characters.used;
        characters.used++;

        invalid[character_current] = 0;
      }

      // When width_count == 0, then this is that start of a new character sequence.
      if (width_count == 0) {
        characters.string[character_current] = f_macro_utf_character_from_char_1(byte);
        width_count = 1;

        // The first character in a UTF-8 sequence cannot have a width of 1.
        if (width_utf == 1) {
          found_invalid_utf = f_true;
          invalid[character_current] = 1;
        }
        // Process the UTF-8 character.
        else if (width_utf > 1) {
          position++;

          if (data.last > 0 && position > data.last) break;

          continue;
        }
      }
      // Process a UTF-8 character fragment.
      else if (width_count < width_utf) {
        width_current = f_macro_utf_byte_width_is(byte);

        if (width_count == 1) {
          characters.string[character_current] |= f_macro_utf_character_from_char_2(byte);
        }
        else if (width_count == 2) {
          characters.string[character_current] |= f_macro_utf_character_from_char_3(byte);
        }
        else if (width_count == 3) {
          characters.string[character_current] |= f_macro_utf_character_from_char_4(byte);
        }

        width_count++;

        // UTF-8 character fragments must have a width of 1 (and ASCII characters can only be the first character in a sequence).
        if (width_current == 1) {
          // Grab the next UTF-8 character fragment if the entire sequence is not collected yet.
          if (width_count < width_utf) {
            position++;

            if (data.last > 0 && position > data.last) break;

            continue;
          }
        }
        else {
          found_invalid_utf = f_true;
          invalid[character_current] = width_utf;
        }
      }

      // At this point: an ASCII character is collected, the entire UTF-8 character sequence is collected, or an invalid UTF-8 was processed.
      if (!invalid[character_current] && width_utf > 1) {
        if (f_utf_character_is_valid(characters.string[character_current]) == f_false) {
          found_invalid_utf = f_true;
          invalid[character_current] = width_utf;
        }
      }

      if (byte_dump_print_character_fragment(data, characters, invalid, width_utf, 1, &previous, &cell, &offset) == f_true) {
        character_reset = f_true;
      }

      if (width_utf > 1) {
        if (byte_dump_print_character_fragment(data, characters, invalid, width_utf, 2, &previous, &cell, &offset) == f_true) {
          character_reset = f_true;
        }

        if (width_utf > 2) {
          if (byte_dump_print_character_fragment(data, characters, invalid, width_utf, 3, &previous, &cell, &offset) == f_true) {
            character_reset = f_true;
          }

          if (width_utf > 3) {
            if (byte_dump_print_character_fragment(data, characters, invalid, width_utf, 4, &previous, &cell, &offset) == f_true) {
              character_reset = f_true;
            }
          }
        }
      }

      width_utf = -1;
      position++;

      if (data.last > 0 && position > data.last) break;
    } // while

    // Print placeholders to fill out the remaining line and then optionally print the text block.
    if (cell.column > 0 && cell.column < data.width) {
      previous.bytes = 0;
      previous.invalid = 0;

      while (cell.column < data.width) {
        if (data.mode == byte_dump_mode_hexidecimal) {
          printf("   ");
        }
        else if (data.mode == byte_dump_mode_duodecimal) {
          printf("    ");
        }
        else if (data.mode == byte_dump_mode_octal) {
          printf("    ");
        }
        else if (data.mode == byte_dump_mode_binary) {
          printf("         ");
        }
        else if (data.mode == byte_dump_mode_decimal) {
          printf("    ");
        }

        cell.column++;

        if (cell.column < data.width) {
          if (data.mode == byte_dump_mode_hexidecimal && cell.column % 8 == 0) {
            printf(" ");
          }
          else if (data.mode == byte_dump_mode_duodecimal && cell.column % 6 == 0) {
            printf(" ");
          }
          else if (data.mode == byte_dump_mode_octal && cell.column % 6 == 0) {
            printf(" ");
          }
          else if (data.mode == byte_dump_mode_binary && cell.column % 4 == 0) {
            printf(" ");
          }
          else if (data.mode == byte_dump_mode_decimal && cell.column % 6 == 0) {
            printf(" ");
          }
        }
      } // while

      if (data.parameters[byte_dump_parameter_text].result == f_console_result_found) {
        byte_dump_print_text(data, characters, invalid, &previous, &offset);
      }
      else {
        printf("%c", f_string_eol);
      }
    }

    printf("%c", f_string_eol);

    // make sure to flush standard out to help prevent standard error from causing poblems.
    fflush(f_standard_output);

    if (found_invalid_utf) {
      fl_color_print(f_standard_error, data.context.error, data.context.reset, "Invalid UTF-8 codes were detected for file '");
      fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "'.");
      printf("%c", f_string_eol);
    }

    if (size < 0) {
      // @todo: determine what the error from read() is and display it.
      fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: read() failed for '");
      fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "'.");
      printf("%c", f_string_eol);
      status = f_status_set_error(f_failure);
    }

    fflush(f_standard_error);

    return status;
  }
#endif // _di_byte_dump_file_

#ifndef _di_byte_dump_print_character_fragment_
  bool byte_dump_print_character_fragment(const byte_dump_data data, const f_utf_string_dynamic characters, const uint8_t invalid[], const int8_t width_utf, const int8_t byte_current, byte_dump_previous *previous, byte_dump_cell *cell, uint8_t *offset) {
    uint8_t byte = 0;

    bool reset = f_false;

    f_utf_string_length character_current = characters.used - 1;

    if (byte_current == 1) {
      byte = f_macro_utf_character_to_char_1(characters.string[character_current]);
    }
    else if (byte_current == 2) {
      byte = f_macro_utf_character_to_char_2(characters.string[character_current]);
    }
    else if (byte_current == 3) {
      byte = f_macro_utf_character_to_char_3(characters.string[character_current]);
    }
    else if (byte_current == 4) {
      byte = f_macro_utf_character_to_char_4(characters.string[character_current]);
    }

    if (cell->column == 0) {
      fl_color_print(f_standard_output, data.context.notable, data.context.reset, "%016X ", (uint64_t) cell->row);

      if (*offset > 0) {
        uint8_t offset_to_print = *offset;

        // Pad the buffer with spaces to hide any skipped bytes (skipped via --first).
        while (offset_to_print > 0 && cell->column < data.width) {
          if (data.mode == byte_dump_mode_hexidecimal) {
            printf("   ");
          }
          else if (data.mode == byte_dump_mode_duodecimal) {
            printf("    ");
          }
          else if (data.mode == byte_dump_mode_octal) {
            printf("    ");
          }
          else if (data.mode == byte_dump_mode_binary) {
            printf("         ");
          }
          else if (data.mode == byte_dump_mode_decimal) {
            printf("    ");
          }

          offset_to_print--;
          cell->column++;

          if (cell->column < data.width) {
            if (data.mode == byte_dump_mode_hexidecimal && cell->column % 8 == 0) {
              printf(" ");
            }
            else if (data.mode == byte_dump_mode_duodecimal && cell->column % 6 == 0) {
              printf(" ");
            }
            else if (data.mode == byte_dump_mode_octal && cell->column % 6 == 0) {
              printf(" ");
            }
            else if (data.mode == byte_dump_mode_binary && cell->column % 4 == 0) {
              printf(" ");
            }
            else if (data.mode == byte_dump_mode_decimal && cell->column % 6 == 0) {
              printf(" ");
            }
          }
        }
      }
    }

    if (cell->column < data.width) {
      if (data.mode == byte_dump_mode_hexidecimal) {
        if (invalid[character_current]) {
          fl_color_print(f_standard_output, data.context.error, data.context.reset, " %02x", (uint8_t) byte);
        }
        else {
          printf(" %02x", (uint8_t) byte);
        }
      }
      else if (data.mode == byte_dump_mode_duodecimal) {
        if (invalid[character_current]) {
          f_print_string_dynamic(f_standard_output, data.context.error);
        }

        printf(" %01d", byte / 144);

        uint8_t current = (byte % 144) / 12;

        if (current == 11) {
          printf("b");
        }
        else if (current == 10) {
          printf("a");
        }
        else {
          printf("%01d", current);
        }

        current = (byte % 144) % 12;

        if (current == 11) {
          printf("b");
        }
        else if (current == 10) {
          printf("a");
        }
        else {
          printf("%01d", current);
        }

        if (invalid[character_current]) {
          f_print_string_dynamic(f_standard_output, data.context.reset);
        }
      }
      else if (data.mode == byte_dump_mode_octal) {
        if (invalid[character_current]) {
          fl_color_print(f_standard_output, data.context.error, data.context.reset, " %03o", (uint8_t) byte);
        }
        else {
          printf(" %03o", (uint8_t) byte);
        }
      }
      else if (data.mode == byte_dump_mode_binary) {
        int8_t binary_string[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

        binary_string[0] = ((byte >> 7) & 0x01) ? '1' : '0';
        binary_string[1] = ((byte >> 6) & 0x01) ? '1' : '0';
        binary_string[2] = ((byte >> 5) & 0x01) ? '1' : '0';
        binary_string[3] = ((byte >> 4) & 0x01) ? '1' : '0';
        binary_string[4] = ((byte >> 3) & 0x01) ? '1' : '0';
        binary_string[5] = ((byte >> 2) & 0x01) ? '1' : '0';
        binary_string[6] = ((byte >> 1) & 0x01) ? '1' : '0';
        binary_string[7] = (byte & 0x01) ? '1' : '0';

        if (invalid[character_current]) {
          fl_color_print(f_standard_output, data.context.error, data.context.reset, " %s", binary_string);
        }
        else {
          printf(" %s", binary_string);
        }
      }
      else if (data.mode == byte_dump_mode_decimal) {
        if (invalid[character_current]) {
          fl_color_print(f_standard_output, data.context.error, data.context.reset, " %3d", (uint8_t) byte);
        }
        else {
          printf(" %3d", (uint8_t) byte);
        }
      }

      cell->column++;
    }

    if (cell->column == data.width) {
      uint8_t bytes = 0;

      if (byte_current < width_utf) {
        bytes = width_utf - byte_current;
      }

      reset = f_true;

      if (data.parameters[byte_dump_parameter_text].result == f_console_result_found) {
        byte_dump_print_text(data, characters, invalid, previous, offset);
      }
      else {
        printf("%c", f_string_eol);
      }

      cell->column = 0;
      cell->row++;

      if (bytes == 0) {
        previous->bytes = 0;
        previous->invalid = 0;
      }
      else {
        previous->bytes = bytes;
        previous->invalid = invalid[character_current];
      }
    }
    else if (data.mode == byte_dump_mode_hexidecimal && cell->column % 8 == 0) {
      printf(" ");
    }
    else if (data.mode == byte_dump_mode_duodecimal && cell->column % 6 == 0) {
      printf(" ");
    }
    else if (data.mode == byte_dump_mode_octal && cell->column % 6 == 0) {
      printf(" ");
    }
    else if (data.mode == byte_dump_mode_binary && cell->column % 4 == 0) {
      printf(" ");
    }
    else if (data.mode == byte_dump_mode_decimal && cell->column % 6 == 0) {
      printf(" ");
    }

    return reset;
  }
#endif // _di_byte_dump_print_character_fragment_

#ifndef _di_byte_dump_print_text_
  void byte_dump_print_text(const byte_dump_data data, const f_utf_string_dynamic characters, const uint8_t invalid[], byte_dump_previous *previous, uint8_t *offset) {
    uint8_t j = 0;
    uint8_t output = 0;
    uint8_t width_utf = 0;
    bool printed = f_false;

    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "  %s ", byte_dump_character_wall);


    if (*offset > 0) {
      f_string placeholder = " ";

      if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
        placeholder = byte_dump_character_placeholder;
      }

      while (*offset > 0 && j < data.width) {
        fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", placeholder);
        (*offset)--;
        j++;
      } // while
    }

    // Print placeholders for the remaining fragments of UTF-8 characters printed on previous lines.
    if (j < data.width) {
      uint8_t bytes_overflow = 0;

      if (previous->bytes - 1 > data.width) {
        bytes_overflow = previous->bytes - 1 - data.width;
      }

      if (previous->bytes > 0) {
        if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          for (; j < previous->bytes && j < data.width; j++) {
            if (previous->invalid) {
              fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", byte_dump_character_placeholder);
            }
            else {
              fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", byte_dump_character_placeholder);
            }
          } // for
        }
        else {
          for (; j < previous->bytes && j < data.width; j++) {
            printf(" ");
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

    for (uint8_t i = 0; i < characters.used && j < data.width; i++, j++) {
      output = f_macro_utf_character_to_char_1(characters.string[i]);
      width_utf = f_macro_utf_byte_width_is(output);

      if (invalid[i]) {
        fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", byte_dump_character_incomplete);
      }
      else if (output >= 0 && output <= 32 || output == 127) {
        if (data.presentation == byte_dump_presentation_normal) {
          if (output == 0) {
            printf("%s", byte_dump_sequence_null);
          }
          else if (output == 1) {
            printf("%s", byte_dump_sequence_start_of_header);
          }
          else if (output == 2) {
            printf("%s", byte_dump_sequence_start_of_text);
          }
          else if (output == 3) {
            printf("%s", byte_dump_sequence_end_of_text);
          }
          else if (output == 4) {
            printf("%s", byte_dump_sequence_end_of_transmission);
          }
          else if (output == 5) {
            printf("%s", byte_dump_sequence_end_of_enquiry);
          }
          else if (output == 6) {
            printf("%s", byte_dump_sequence_acknowledge);
          }
          else if (output == 7) {
            printf("%s", byte_dump_sequence_bell);
          }
          else if (output == 8) {
            printf("%s", byte_dump_sequence_backspace);
          }
          else if (output == 9) {
            printf("%s", byte_dump_sequence_tab);
          }
          else if (output == 10) {
            printf("%s", byte_dump_sequence_new_line);
          }
          else if (output == 11) {
            printf("%s", byte_dump_sequence_tab_vertical);
          }
          else if (output == 12) {
            printf("%s", byte_dump_sequence_form_feed);
          }
          else if (output == 13) {
            printf("%s", byte_dump_sequence_carriage_return);
          }
          else if (output == 14) {
            printf("%s", byte_dump_sequence_shift_out);
          }
          else if (output == 15) {
            printf("%s", byte_dump_sequence_shift_in);
          }
          else if (output == 16) {
            printf("%s", byte_dump_sequence_data_link_escape);
          }
          else if (output == 17) {
            printf("%s", byte_dump_sequence_device_control_1);
          }
          else if (output == 18) {
            printf("%s", byte_dump_sequence_device_control_2);
          }
          else if (output == 19) {
            printf("%s", byte_dump_sequence_device_control_3);
          }
          else if (output == 20) {
            printf("%s", byte_dump_sequence_device_control_4);
          }
          else if (output == 21) {
            printf("%s", byte_dump_sequence_negative_acknowledge);
          }
          else if (output == 22) {
            printf("%s", byte_dump_sequence_synchronous_idle);
          }
          else if (output == 23) {
            printf("%s", byte_dump_sequence_end_of_transmission_block);
          }
          else if (output == 24) {
            printf("%s", byte_dump_sequence_cancel);
          }
          else if (output == 25) {
            printf("%s", byte_dump_sequence_end_of_medium);
          }
          else if (output == 26) {
            printf("%s", byte_dump_sequence_substitute);
          }
          else if (output == 27) {
            printf("%s", byte_dump_sequence_escape);
          }
          else if (output == 28) {
            printf("%s", byte_dump_sequence_file_separator);
          }
          else if (output == 29) {
            printf("%s", byte_dump_sequence_group_separator);
          }
          else if (output == 30) {
            printf("%s", byte_dump_sequence_record_separator);
          }
          else if (output == 31) {
            printf("%s", byte_dump_sequence_unit_separator);
          }
          else if (output == 32) {
            printf("%s", byte_dump_sequence_space);
          }
          else if (output == 127) {
            printf("%s", byte_dump_sequence_delete);
          }
        }
        else if (data.presentation == byte_dump_presentation_simple) {
          printf(" ");
        }
        else if (data.presentation == byte_dump_presentation_classic) {
          printf(".");
        }
      }
      else if (f_utf_character_is_whitespace(characters.string[i]) == f_true) {
        printf("%s", byte_dump_sequence_space);
      }
      else if (f_utf_character_is_control(characters.string[i]) == f_true) {
        // print a space (or '.') for control characters.
        if (data.presentation == byte_dump_presentation_classic) {
          printf(".");
        }
        else {
          printf(" ");
        }
      }
      else if (width_utf == 2 && characters.string[i] == 0xd89d0000) {
        // U+061C
        printf(" ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xefbfb000 && characters.string[i] <= 0xefbfbc00) {
        // Use space to represent Specials codes.
        // 0xefbfbd00 is excluded because it is printable (and is the "Replacement Character" code).
        printf(" ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xe290a700 && characters.string[i] <= 0xe290bf00) {
        // Use space to represent Control Pictues codes that are not currently defined but are reserved.
        printf(" ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xee808000 && characters.string[i] <= 0xefa3bf00) {
        // Use space to represent Private Use Area codes.
        printf(" ");
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf09c80a0 && characters.string[i] <= 0xf09c80bd) {
        // Use space to represent Vaiation Selectors Supplement codes.
        printf(" ");
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf3b08080 && characters.string[i] <= 0xf3bfbfbf) {
        // Use space to represent Supplemental Private Use Area-A codes.
        printf(" ");
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf4808080 && characters.string[i] <= 0xf48fbfbf) {
        // Use space to represent Supplemental Private Use Area-B codes.
        printf(" ");
      }
      else if (width_utf == 1) {
        // print invalid placeholder for invalid UTF-8 widths.
        if (invalid[i]) {
          fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", byte_dump_character_incomplete);
        }
        else {
          fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", byte_dump_character_incomplete);
        }
      }
      else if (width_utf > 0) {
        printf("%c", (uint8_t) output);

        if (width_utf > 1) {
          output = f_macro_utf_character_to_char_2(characters.string[i]);
          printf("%c", (uint8_t) output);

          if (width_utf > 2) {
            output = f_macro_utf_character_to_char_3(characters.string[i]);
            printf("%c", (uint8_t) output);

            if (width_utf > 3) {
              output = f_macro_utf_character_to_char_4(characters.string[i]);
              printf("%c", (uint8_t) output);
            }
          }
        }

        // @todo: implement a function in f_utf, such as f_utf_is_combining(), for detecting these combining characters.
        // print a space for combining characters to combine into, thereby allowing it to be safely and readably displayed.
        if (width_utf == 2 && characters.string[i] >= 0xdea60000 && characters.string[i] <= 0xdeb00000) {
          // Thana combining codes: U+07A6 to U+07B0.
          printf(" ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xcc800000 && characters.string[i] <= 0xcdaf0000) {
          printf(" ");
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe1aab000 && characters.string[i] <= 0xe1abbf00) {
          printf(" ");
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe1b78000 && characters.string[i] <= 0xe1b7bf00) {
          printf(" ");
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe2839000 && characters.string[i] <= 0xe283bf00) {
          printf(" ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd8900000 && characters.string[i] <= 0xd89a0000) {
          printf(" ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd98b0000 && characters.string[i] <= 0xd99f0000) {
          // Arabic, U+064B to U+065F.
          printf(" ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xdb960000 && characters.string[i] <= 0xdb9c0000) {
          // Arabic, U+06D6 to U+06DC.
          printf(" ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd6910000 && characters.string[i] <= 0xd6bd0000) {
          // Hebrew, U+0591 to U+05BD.
          printf(" ");
        }
      }
      else {
        printf("%c", output);
      }

      // When using UTF-8 characters, the character columns will not line up, so print placeholders to simulate the bytes that are not printed, if necessary for alignment.
      if (width_utf > 1 && j + 1 < data.width) {
        if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          if (invalid[i]) {
            fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", byte_dump_character_placeholder);
          }
          else {
            fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", byte_dump_character_placeholder);
          }
        }
        else {
          printf(" ");
        }

        j++;

        if (width_utf > 2 && j + 1 < data.width) {
          if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
            if (invalid[i]) {
              fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", byte_dump_character_placeholder);
            }
            else {
              fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", byte_dump_character_placeholder);
            }
          }
          else {
            printf(" ");
          }

          j++;

          if (width_utf > 3 && j + 1 < data.width) {
            if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
              if (invalid[i]) {
                fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", byte_dump_character_placeholder);
              }
              else {
                fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", byte_dump_character_placeholder);
              }
            }
            else {
              printf(" ");
            }

            j++;
          }
        }
      }
    } // for

    // Print placeholder for the remaining parts of the line.
    if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
      for (; j < data.width; j++) {
        if (invalid[j]) {
          fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", byte_dump_character_placeholder);
        }
        else {
          fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", byte_dump_character_placeholder);
        }
      } // for
    }
    else {
      for (; j < data.width; j++) {
          printf(" ");
      } // for
    }

    fl_color_print(f_standard_output, data.context.notable, data.context.reset, " |");
    printf("%c", f_string_eol);
  }
#endif // _di_byte_dump_file_

#ifndef _di_byte_dump_print_file_error_
  void byte_dump_print_file_error(const fl_color_context context, const f_status status, const f_string function, const f_string file_name) {
    f_status error = f_status_set_fine(status);

    if (error == f_false) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: failed to find file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return;
    }

    if (error == f_invalid_parameter) {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ", function, file_name);
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", function);
      fl_color_print(f_standard_error, context.error, context.reset, "() for the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return;
    }

    if (error == f_invalid_name) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Invalid filename '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return;
    }

    if (error == f_out_of_memory) {
      fl_color_print(f_standard_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to access file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return;
    }

    if (error == f_overflow) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Overflow while trying to access file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return;
    }

    if (error == f_invalid_directory) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Invalid directory while trying to access file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return;
    }

    if (error == f_access_denied) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Access denied while trying to access file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return;
    }

    if (error == f_loop) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Loop while trying to access file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
      return;
    }

    fl_color_print(f_standard_error, context.error, context.reset, "UNKNOWN ERROR: (");
    fl_color_print(f_standard_error, context.notable, context.reset, "%d", error);
    fl_color_print(f_standard_error, context.error, context.reset, ") occurred for file '");
    fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
    fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
  }
#endif // _di_byte_dump_print_file_error_

#ifdef __cplusplus
} // extern "C"
#endif
