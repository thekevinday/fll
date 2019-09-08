/**
 * Private source file for firewall.c.
 */
#include <level_3/bit_dump.h>
#include "private-bit_dump.h"

#ifndef _di_bit_dump_file_
  f_return_status bit_dump_file(const bit_dump_data data, const f_string file_name, f_file file) {
    f_status status = f_none;

    uint64_t position = data.first;
    uint64_t row = 0;
    uint8_t size = 0;
    uint8_t byte = 0;
    uint8_t column = 0;

    int8_t width_utf = -1;
    int8_t width_current = 0;
    int8_t width_count = 0;

    // UTF-8 Characters bytes may overflow beyond the data.width.
    // These overflowed bytes should still have placeholders printed in the next text-mode print.
    uint8_t previous_bytes = 0;
    uint8_t previous_invalid = 0;

    f_bool character_reset = 0;
    f_bool found_invalid_utf = f_false;

    // Store the current character data until it can be printed.
    f_utf_string_dynamic characters = f_utf_string_dynamic_initialize;
    f_utf_character character_array[data.width];
    f_utf_string_length character_current = 0;

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
        // UTF-8 characters with width of 4 cannot have any characters of 0x8f as the first byte.
        else if (width_utf == 4 && byte == 0x8f) {
          found_invalid_utf = f_true;
          invalid[character_current] = width_utf;
        }
        // These are not defined in Unicode, and so are considered invalid in UTF-8, regardless of their width_utf.
        else if (byte >= 0xf5) {
          found_invalid_utf = f_true;
          invalid[character_current] = width_utf;
        }
        // Sequences that start with 0xc1 are invalid because UTF-8 does not support overlong ASCII.
        else if (byte == 0xc1) {
          found_invalid_utf = f_true;
          invalid[character_current] = width_utf;
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

      // Handle special case invalid situations, 0xc0 and 0xc1 are used for two-byte encoding of a 7-bit ASCII but are considered invalid by UTF-8.
      // Does not include 0xc0 0x80 because this is considered a overlong NULL in UTF-8, which is a valid NULL.
      if (width_utf == 2 && characters.string[character_current] > 0xc0800000 && characters.string[character_current] <= 0xc0ff0000) {
        found_invalid_utf = f_true;
        invalid[character_current] = width_utf;
      }
      // The unicode codes U+D800 to U+DFFF are for "UTF-16 surrogate halves" which are not supported in UTF-8.
      else if (width_utf == 3 && characters.string[character_current] > 0xefbfb000 && characters.string[character_current] <= 0xc0ff0000) {
        found_invalid_utf = f_true;
        invalid[character_current] = width_utf;
      }

      if (bit_dump_print_character_fragment(data, characters, invalid, width_utf, 1, &previous_bytes, &previous_invalid, &column, &row)) {
        character_reset = f_true;
      }

      if (width_utf > 1) {
        if (bit_dump_print_character_fragment(data, characters, invalid, width_utf, 2, &previous_bytes, &previous_invalid, &column, &row) == f_true) {
          character_reset = f_true;
        }

        if (width_utf > 2) {
          if (bit_dump_print_character_fragment(data, characters, invalid, width_utf, 3, &previous_bytes, &previous_invalid, &column, &row)) {
            character_reset = f_true;
          }

          if (width_utf > 3) {
            if (bit_dump_print_character_fragment(data, characters, invalid, width_utf, 4, &previous_bytes, &previous_invalid, &column, &row)) {
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
    if (column > 0 && column < data.width) {
      previous_bytes = 0;
      previous_invalid = 0;

      while (column < data.width) {
        if (data.mode == bit_dump_mode_hexidecimal) {
          printf("   ");
        }
        else if (data.mode == bit_dump_mode_octal) {
          printf("    ");
        }
        else if (data.mode == bit_dump_mode_binary) {
          printf("         ");
        }
        else if (data.mode == bit_dump_mode_decimal) {
          printf("    ");
        }

        column++;

        if (column < data.width) {
          if (data.mode == bit_dump_mode_hexidecimal && column % 8 == 0) {
            printf(" ");
          }
          else if (data.mode == bit_dump_mode_octal && column % 6 == 0) {
            printf(" ");
          }
          else if (data.mode == bit_dump_mode_binary && column % 4 == 0) {
            printf(" ");
          }
          else if (data.mode == bit_dump_mode_decimal && column % 6 == 0) {
            printf(" ");
          }
        }
      } // while

      if (data.parameters[bit_dump_parameter_text].result == f_console_result_found) {
        bit_dump_print_text(data, characters, invalid, &previous_bytes, &previous_invalid);
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
#endif // _di_bit_dump_file_

#ifndef _di_bit_dump_print_character_fragment_
  f_bool bit_dump_print_character_fragment(const bit_dump_data data, const f_utf_string_dynamic characters, const uint8_t invalid[], const int8_t width_utf, const int8_t byte_current, uint8_t *previous_bytes, uint8_t *previous_invalid, uint8_t *column, uint64_t *row) {
    uint8_t byte = 0;

    f_bool reset = f_false;

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

    if (*column == 0) {
      fl_color_print(f_standard_output, data.context.notable, data.context.reset, "%016X ", (uint64_t) *row);
    }

    if (data.mode == bit_dump_mode_hexidecimal) {
      if (invalid[character_current]) {
        fl_color_print(f_standard_output, data.context.error, data.context.reset, " %02x", (uint8_t) byte);
      }
      else {
        printf(" %02x", (uint8_t) byte);
      }
    }
    else if (data.mode == bit_dump_mode_octal) {
      if (invalid[character_current]) {
        fl_color_print(f_standard_output, data.context.error, data.context.reset, " %03o", (uint8_t) byte);
      }
      else {
        printf(" %03o", (uint8_t) byte);
      }
    }
    else if (data.mode == bit_dump_mode_binary) {
      char binary_string[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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
    else if (data.mode == bit_dump_mode_decimal) {
      if (invalid[character_current]) {
        fl_color_print(f_standard_output, data.context.error, data.context.reset, " %3d", (uint8_t) byte);
      }
      else {
        printf(" %3d", (uint8_t) byte);
      }
    }

    (*column)++;

    if (*column == data.width) {
      uint8_t bytes = 0;

      if (byte_current < width_utf) {
        bytes = width_utf - byte_current;
      }

      reset = f_true;

      if (data.parameters[bit_dump_parameter_text].result == f_console_result_found) {
        bit_dump_print_text(data, characters, invalid, previous_bytes, previous_invalid);
      }
      else {
        printf("%c", f_string_eol);
      }

      *column = 0;
      (*row)++;

      if (bytes == 0) {
        *previous_bytes = 0;
        *previous_invalid = 0;
      }
      else {
        *previous_bytes = bytes;
        *previous_invalid = invalid[character_current];
      }
    }
    else if (data.mode == bit_dump_mode_hexidecimal && *column % 8 == 0) {
      printf(" ");
    }
    else if (data.mode == bit_dump_mode_octal && *column % 6 == 0) {
      printf(" ");
    }
    else if (data.mode == bit_dump_mode_binary && *column % 4 == 0) {
      printf(" ");
    }
    else if (data.mode == bit_dump_mode_decimal && *column % 6 == 0) {
      printf(" ");
    }

    return reset;
  }
#endif // _di_bit_dump_print_character_fragment_

#ifndef _di_bit_dump_print_text_
  void bit_dump_print_text(const bit_dump_data data, const f_utf_string_dynamic characters, const uint8_t invalid[], uint8_t *previous_bytes, uint8_t *previous_invalid) {
    uint8_t j = 0;
    uint8_t output = 0;
    uint8_t width_utf = 0;

    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "  %s ", bit_dump_character_wall);

    // Print placeholders for the remaining fragments of UTF-8 characters printed on previous lines.
    {
      uint8_t bytes_overflow = 0;

      if ((*previous_bytes - 1) > data.width) {
        bytes_overflow = (*previous_bytes) - 1 - data.width;
      }

      if (*previous_bytes > 0) {
        if (data.parameters[bit_dump_parameter_placeholder].result == f_console_result_found) {
          for (; j < *previous_bytes && j < data.width; j++) {
            if (*previous_invalid) {
              fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", bit_dump_character_placeholder);
            }
            else {
              fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", bit_dump_character_placeholder);
            }
          } // for
        }
        else {
          for (; j < *previous_bytes && j < data.width; j++) {
            printf(" ");
          } // for
        }
      }

      if (bytes_overflow > 0) {
        *previous_bytes = bytes_overflow;
      }
      else {
        *previous_bytes = 0;
        *previous_invalid = 0;
      }
    }

    for (uint8_t i = 0; i < characters.used && j < data.width; i++, j++) {
      output = f_macro_utf_character_to_char_1(characters.string[i]);
      width_utf = f_macro_utf_byte_width_is(output);

      if (invalid[i]) {
        fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", bit_dump_character_incomplete);
      }
      else if (output == 0) {
        printf("%s", bit_dump_sequence_null);
      }
      else if (output == 1) {
        printf("%s", bit_dump_sequence_start_of_header);
      }
      else if (output == 2) {
        printf("%s", bit_dump_sequence_start_of_text);
      }
      else if (output == 3) {
        printf("%s", bit_dump_sequence_end_of_text);
      }
      else if (output == 4) {
        printf("%s", bit_dump_sequence_end_of_transmission);
      }
      else if (output == 5) {
        printf("%s", bit_dump_sequence_end_of_enquiry);
      }
      else if (output == 6) {
        printf("%s", bit_dump_sequence_acknowledge);
      }
      else if (output == 7) {
        printf("%s", bit_dump_sequence_bell);
      }
      else if (output == 8) {
        printf("%s", bit_dump_sequence_backspace);
      }
      else if (output == 9) {
        printf("%s", bit_dump_sequence_tab);
      }
      else if (output == 10) {
        printf("%s", bit_dump_sequence_new_line);
      }
      else if (output == 11) {
        printf("%s", bit_dump_sequence_tab_vertical);
      }
      else if (output == 12) {
        printf("%s", bit_dump_sequence_form_feed);
      }
      else if (output == 13) {
        printf("%s", bit_dump_sequence_carriage_return);
      }
      else if (output == 14) {
        printf("%s", bit_dump_sequence_shift_out);
      }
      else if (output == 15) {
        printf("%s", bit_dump_sequence_shift_in);
      }
      else if (output == 16) {
        printf("%s", bit_dump_sequence_data_link_escape);
      }
      else if (output == 17) {
        printf("%s", bit_dump_sequence_device_control_1);
      }
      else if (output == 18) {
        printf("%s", bit_dump_sequence_device_control_2);
      }
      else if (output == 19) {
        printf("%s", bit_dump_sequence_device_control_3);
      }
      else if (output == 20) {
        printf("%s", bit_dump_sequence_device_control_4);
      }
      else if (output == 21) {
        printf("%s", bit_dump_sequence_negative_acknowledge);
      }
      else if (output == 22) {
        printf("%s", bit_dump_sequence_synchronous_idle);
      }
      else if (output == 23) {
        printf("%s", bit_dump_sequence_end_of_transmission_block);
      }
      else if (output == 24) {
        printf("%s", bit_dump_sequence_cancel);
      }
      else if (output == 25) {
        printf("%s", bit_dump_sequence_end_of_medium);
      }
      else if (output == 26) {
        printf("%s", bit_dump_sequence_substitute);
      }
      else if (output == 27) {
        printf("%s", bit_dump_sequence_escape);
      }
      else if (output == 28) {
        printf("%s", bit_dump_sequence_file_separator);
      }
      else if (output == 29) {
        printf("%s", bit_dump_sequence_group_separator);
      }
      else if (output == 30) {
        printf("%s", bit_dump_sequence_record_separator);
      }
      else if (output == 31) {
        printf("%s", bit_dump_sequence_unit_separator);
      }
      else if (output == 32) {
        printf("%s", bit_dump_sequence_space);
      }
      else if (output == 127) {
        printf("%s", bit_dump_sequence_delete);
      }
      else if (f_utf_is_whitespace_character(characters.string[i]) == f_true) {
        printf("%s", bit_dump_sequence_space);
      }
      else if (width_utf == 2 && characters.string[i] == 0xc0800000) {
        // This is an "Overlong Null" and is a valid NULL character.
        printf("%s", bit_dump_sequence_null);
      }
      else if (width_utf == 2 && characters.string[i] >= 0xcc800000 && characters.string[i] <= 0xcdaf0000) {
        // Combining characters should not be combined here, instead display a space.
        printf(" ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xe1aab000 && characters.string[i] <= 0xe1abbf00) {
        // Combining characters should not be combined here, instead display a space.
        printf(" ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xe1b78000 && characters.string[i] <= 0xe1b7bf00) {
        // Combining characters should not be combined here, instead display a space.
        printf(" ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xe2839000 && characters.string[i] <= 0xe283bf00) {
        // Combining characters should not be combined here, instead display a space.
        printf(" ");
      }
      else if (width_utf == 2 && characters.string[i] >= 0xd8900000 && characters.string[i] <= 0xd89a0000) {
        // Combining characters should not be combined here, instead display a space.
        printf(" ");
      }
      else if (width_utf == 2 && characters.string[i] >= 0xc2800000 && characters.string[i] <= 0xc29f0000) {
        // Use space to represent unprintable Latin-1 supplement control codes.
        // 0xc2a00000 happens to be the non-breaking space character and is explicitly handled above.
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
      else if (width_utf == 3 && characters.string[i] >= 0xeda08000 && characters.string[i] <= 0xedadbf00) {
        // Use space to represent High Surrogates codes.
        printf(" ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xedae8000 && characters.string[i] <= 0xedafbf00) {
        // Use space to represent High Private Use Surrogates codes.
        printf(" ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xedb08000 && characters.string[i] <= 0xedbfbf00) {
        // Use space to represent Low Surrogates codes.
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
      else if (width_utf == 4 && characters.string[i] >= 0xf09e8080 && characters.string[i] <= 0xf09fbfbf) {
        // Use space to represent Supplemental Private Use Area-A codes.
        printf(" ");
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf0a08080 && characters.string[i] <= 0xf0a1bfbf) {
        // Use space to represent Supplemental Private Use Area-B codes.
        printf(" ");
      }
      else if (characters.string[i] == f_utf_character_mask_bom) {
        fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", bit_dump_sequence_utf_bom);
      }
      else if (width_utf == 1) {
        // print invalid placeholder for invalid UTF-8 widths.
        if (invalid[i]) {
          fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", bit_dump_character_incomplete);
        }
        else {
          fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", bit_dump_character_incomplete);
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
      }
      else {
        printf("%c", output);
      }

      // When using UTF-8 characters, the character columns will not line up, so print placeholders to simulate the bytes that are not printed, if necessary for alignment.
      if (width_utf > 1 && j + 1 < data.width) {
        if (data.parameters[bit_dump_parameter_placeholder].result == f_console_result_found) {
          if (invalid[i]) {
            fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", bit_dump_character_placeholder);
          }
          else {
            fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", bit_dump_character_placeholder);
          }
        }
        else {
          printf(" ");
        }

        j++;

        if (width_utf > 2 && j + 1 < data.width) {
          if (data.parameters[bit_dump_parameter_placeholder].result == f_console_result_found) {
            if (invalid[i]) {
              fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", bit_dump_character_placeholder);
            }
            else {
              fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", bit_dump_character_placeholder);
            }
          }
          else {
            printf(" ");
          }

          j++;

          if (width_utf > 3 && j + 1 < data.width) {
            if (data.parameters[bit_dump_parameter_placeholder].result == f_console_result_found) {
              if (invalid[i]) {
                fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", bit_dump_character_placeholder);
              }
              else {
                fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", bit_dump_character_placeholder);
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
    if (data.parameters[bit_dump_parameter_placeholder].result == f_console_result_found) {
      for (; j < data.width; j++) {
        if (invalid[j]) {
          fl_color_print(f_standard_output, data.context.error, data.context.reset, "%s", bit_dump_character_placeholder);
        }
        else {
          fl_color_print(f_standard_output, data.context.warning, data.context.reset, "%s", bit_dump_character_placeholder);
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
#endif // _di_bit_dump_file_

#ifndef _di_bit_dump_print_file_error_
  void bit_dump_print_file_error(const fl_color_context context, const f_status status, const f_string function, const f_string file_name) {
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
      fl_color_print(f_standard_error, context.error, context.reset, "CRITICAL ERROR: unable to allocate memory, while trying to access file '");
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
#endif // _di_bit_dump_print_file_error_
