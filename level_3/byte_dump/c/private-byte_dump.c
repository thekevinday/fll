#include "byte_dump.h"
#include "private-byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_file_
  f_return_status byte_dump_file(const byte_dump_data_t data, const f_string_t file_name, f_file_t file) {
    f_status_t status = F_none;

    uint64_t position = 0;
    uint8_t size = 0;
    uint8_t byte = 0;
    uint8_t offset = 0;

    int8_t width_utf = -1;
    int8_t width_current = 0;
    int8_t width_count = 0;

    byte_dump_cell_t cell = byte_dump_cell_t_initialize;
    byte_dump_previous_t previous = byte_dump_previous_t_initialize;

    bool character_reset = 0;
    bool found_invalid_utf = F_false;

    // Store the current character data until it can be printed.
    f_utf_string_dynamic_t characters = f_utf_string_dynamic_t_initialize;
    f_utf_character_t character_array[data.width];
    f_utf_string_length_t character_current = 0;

    // The row starts based on the first byte starting point and how many columns of bytes are displayed per row.
    if (data.first > 0) {
      cell.row = data.first / data.width;
      offset = data.first % data.width;
    }

    memset(&character_array, 0, sizeof(f_utf_character_t) * data.width);
    characters.string = character_array;
    characters.used = 0;
    characters.size = data.width;

    // Record when a character is invalid.
    uint8_t invalid[data.width];
    memset(&invalid, 0, sizeof(uint8_t) * data.width);

    while ((size = read(file.id, &byte, 1)) > 0) {

      // Storing the next character is designated by width_utf == -1.
      if (width_utf == -1) {
        width_utf = f_macro_utf_byte_width_is(byte);
        width_count = 0;

        // The character is reset, the characters.used is to be reset.
        if (character_reset) {
          characters.used = 0;
          character_reset = F_false;
          memset(&invalid, 0, sizeof(uint8_t) * data.width);
        }

        character_current = characters.used;
        characters.used++;

        invalid[character_current] = 0;
      }

      // When width_count == 0, then this is that start of a new character sequence.
      if (!width_count) {
        characters.string[character_current] = f_macro_utf_character_t_from_char_1(byte);
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
        width_current = f_macro_utf_byte_width_is(byte);

        if (width_count == 1) {
          characters.string[character_current] |= f_macro_utf_character_t_from_char_2(byte);
        }
        else if (width_count == 2) {
          characters.string[character_current] |= f_macro_utf_character_t_from_char_3(byte);
        }
        else if (width_count == 3) {
          characters.string[character_current] |= f_macro_utf_character_t_from_char_4(byte);
        }

        width_count++;

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

      if (byte_dump_print_character_fragment(data, characters, invalid, width_utf, 1, &previous, &cell, &offset) == F_true) {
        character_reset = F_true;
      }

      if (width_utf > 1) {
        if (byte_dump_print_character_fragment(data, characters, invalid, width_utf, 2, &previous, &cell, &offset) == F_true) {
          character_reset = F_true;
        }

        if (width_utf > 2) {
          if (byte_dump_print_character_fragment(data, characters, invalid, width_utf, 3, &previous, &cell, &offset) == F_true) {
            character_reset = F_true;
          }

          if (width_utf > 3) {
            if (byte_dump_print_character_fragment(data, characters, invalid, width_utf, 4, &previous, &cell, &offset) == F_true) {
              character_reset = F_true;
            }
          }
        }

        if (data.last) {
          position += width_utf;

          if (position >= data.last) break;
        }
      }
      else if (data.last) {
        position++;

        if (position >= data.last) break;
      }

      width_utf = -1;
    } // while

    // Print placeholders to fill out the remaining line and then optionally print the text block.
    if (cell.column > 0 && cell.column < data.width) {
      previous.bytes = 0;
      previous.invalid = 0;

      while (cell.column < data.width) {
        if (data.mode == byte_dump_mode_hexidecimal) {
          fprintf(data.output.stream, "   ");
        }
        else if (data.mode == byte_dump_mode_duodecimal) {
          fprintf(data.output.stream, "    ");
        }
        else if (data.mode == byte_dump_mode_octal) {
          fprintf(data.output.stream, "    ");
        }
        else if (data.mode == byte_dump_mode_binary) {
          fprintf(data.output.stream, "         ");
        }
        else if (data.mode == byte_dump_mode_decimal) {
          fprintf(data.output.stream, "    ");
        }

        cell.column++;

        if (cell.column < data.width) {
          if (data.mode == byte_dump_mode_hexidecimal && cell.column % 8 == 0) {
            fprintf(data.output.stream, " ");
          }
          else if (data.mode == byte_dump_mode_duodecimal && cell.column % 6 == 0) {
            fprintf(data.output.stream, " ");
          }
          else if (data.mode == byte_dump_mode_octal && cell.column % 6 == 0) {
            fprintf(data.output.stream, " ");
          }
          else if (data.mode == byte_dump_mode_binary && cell.column % 4 == 0) {
            fprintf(data.output.stream, " ");
          }
          else if (data.mode == byte_dump_mode_decimal && cell.column % 6 == 0) {
            fprintf(data.output.stream, " ");
          }
        }
      } // while

      if (data.parameters[byte_dump_parameter_text].result == f_console_result_found) {
        byte_dump_print_text(data, characters, invalid, &previous, &offset);
      }
      else {
        fprintf(data.output.stream, "%c", f_string_eol[0]);
      }
    }

    fprintf(data.output.stream, "%c", f_string_eol[0]);

    // make sure to flush standard out to help prevent standard error from causing poblems.
    fflush(f_type_output);

    if (found_invalid_utf) {
      fl_color_print(data.error.to.stream, data.context.set.error, "Invalid UTF-8 codes were detected for file '");
      fl_color_print(data.error.to.stream, data.context.set.notable, "%s", file_name);
      fl_color_print(data.error.to.stream, data.context.set.error, "'.");
      fprintf(data.error.to.stream, "%c%c", f_string_eol[0], f_string_eol[0]);
    }

    if (size < 0) {
      // @todo: determine what the error from read() is and display it.
      fl_color_print(data.error.to.stream, data.context.set.error, "%sread() failed for '", fll_error_print_error);
      fl_color_print(data.error.to.stream, data.context.set.notable, "%s", file_name);
      fl_color_print(data.error.to.stream, data.context.set.error, "'.");
      fprintf(data.error.to.stream, "%c%x", f_string_eol[0], f_string_eol[0]);

      status = F_status_set_error(F_failure);
    }

    fflush(f_type_error);

    return status;
  }
#endif // _di_byte_dump_file_

#ifndef _di_byte_dump_print_character_fragment_
  bool byte_dump_print_character_fragment(const byte_dump_data_t data, const f_utf_string_static_t characters, const uint8_t invalid[], const int8_t width_utf, const int8_t byte_current, byte_dump_previous_t *previous, byte_dump_cell_t *cell, uint8_t *offset) {
    uint8_t byte = 0;

    bool reset = F_false;

    f_utf_string_length_t character_current = characters.used - 1;

    if (byte_current == 1) {
      byte = f_macro_utf_character_t_to_char_1(characters.string[character_current]);
    }
    else if (byte_current == 2) {
      byte = f_macro_utf_character_t_to_char_2(characters.string[character_current]);
    }
    else if (byte_current == 3) {
      byte = f_macro_utf_character_t_to_char_3(characters.string[character_current]);
    }
    else if (byte_current == 4) {
      byte = f_macro_utf_character_t_to_char_4(characters.string[character_current]);
    }

    if (!cell->column) {
      fl_color_print(data.output.stream, data.context.set.notable, "%016X ", (uint64_t) cell->row);

      if (*offset > 0) {
        uint8_t offset_to_print = *offset;

        // Pad the buffer with spaces to hide any skipped bytes (skipped via --first).
        while (offset_to_print > 0 && cell->column < data.width) {
          if (data.mode == byte_dump_mode_hexidecimal) {
            fprintf(data.output.stream, "   ");
          }
          else if (data.mode == byte_dump_mode_duodecimal) {
            fprintf(data.output.stream, "    ");
          }
          else if (data.mode == byte_dump_mode_octal) {
            fprintf(data.output.stream, "    ");
          }
          else if (data.mode == byte_dump_mode_binary) {
            fprintf(data.output.stream, "         ");
          }
          else if (data.mode == byte_dump_mode_decimal) {
            fprintf(data.output.stream, "    ");
          }

          offset_to_print--;
          cell->column++;

          if (cell->column < data.width) {
            if (data.mode == byte_dump_mode_hexidecimal && cell->column % 8 == 0) {
              fprintf(data.output.stream, " ");
            }
            else if (data.mode == byte_dump_mode_duodecimal && cell->column % 6 == 0) {
              fprintf(data.output.stream, " ");
            }
            else if (data.mode == byte_dump_mode_octal && cell->column % 6 == 0) {
              fprintf(data.output.stream, " ");
            }
            else if (data.mode == byte_dump_mode_binary && cell->column % 4 == 0) {
              fprintf(data.output.stream, " ");
            }
            else if (data.mode == byte_dump_mode_decimal && cell->column % 6 == 0) {
              fprintf(data.output.stream, " ");
            }
          }
        }
      }
    }

    if (cell->column < data.width) {
      if (data.mode == byte_dump_mode_hexidecimal) {
        if (invalid[character_current]) {
          fl_color_print(data.output.stream, data.context.set.error, " %02x", (uint8_t) byte);
        }
        else {
          fprintf(data.output.stream, " %02x", (uint8_t) byte);
        }
      }
      else if (data.mode == byte_dump_mode_duodecimal) {
        if (invalid[character_current]) {
          fprintf(data.output.stream, "%s", data.context.error);
        }

        fprintf(data.output.stream, " %01d", byte / 144);

        uint8_t current = (byte % 144) / 12;

        if (current == 11) {
          fprintf(data.output.stream, "b");
        }
        else if (current == 10) {
          fprintf(data.output.stream, "a");
        }
        else {
          fprintf(data.output.stream, "%01d", current);
        }

        current = (byte % 144) % 12;

        if (current == 11) {
          fprintf(data.output.stream, "b");
        }
        else if (current == 10) {
          fprintf(data.output.stream, "a");
        }
        else {
          fprintf(data.output.stream, "%01d", current);
        }

        if (invalid[character_current]) {
          fprintf(data.output.stream, "%s", data.context.reset);
        }
      }
      else if (data.mode == byte_dump_mode_octal) {
        if (invalid[character_current]) {
          fl_color_print(data.output.stream, data.context.set.error, " %03o", (uint8_t) byte);
        }
        else {
          fprintf(data.output.stream, " %03o", (uint8_t) byte);
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
          fl_color_print(data.output.stream, data.context.set.error, " %s", binary_string);
        }
        else {
          fprintf(data.output.stream, " %s", binary_string);
        }
      }
      else if (data.mode == byte_dump_mode_decimal) {
        if (invalid[character_current]) {
          fl_color_print(data.output.stream, data.context.set.error, " %3d", (uint8_t) byte);
        }
        else {
          fprintf(data.output.stream, " %3d", (uint8_t) byte);
        }
      }

      cell->column++;
    }

    if (cell->column == data.width) {
      uint8_t bytes = 0;

      if (byte_current < width_utf) {
        bytes = width_utf - byte_current;
      }

      reset = F_true;

      if (data.parameters[byte_dump_parameter_text].result == f_console_result_found) {
        byte_dump_print_text(data, characters, invalid, previous, offset);
      }
      else {
        fprintf(data.output.stream, "%c", f_string_eol[0]);
      }

      cell->column = 0;
      cell->row++;

      if (!bytes) {
        previous->bytes = 0;
        previous->invalid = 0;
      }
      else {
        previous->bytes = bytes;
        previous->invalid = invalid[character_current];
      }
    }
    else if (data.mode == byte_dump_mode_hexidecimal && cell->column % 8 == 0) {
      fprintf(data.output.stream, " ");
    }
    else if (data.mode == byte_dump_mode_duodecimal && cell->column % 6 == 0) {
      fprintf(data.output.stream, " ");
    }
    else if (data.mode == byte_dump_mode_octal && cell->column % 6 == 0) {
      fprintf(data.output.stream, " ");
    }
    else if (data.mode == byte_dump_mode_binary && cell->column % 4 == 0) {
      fprintf(data.output.stream, " ");
    }
    else if (data.mode == byte_dump_mode_decimal && cell->column % 6 == 0) {
      fprintf(data.output.stream, " ");
    }

    return reset;
  }
#endif // _di_byte_dump_print_character_fragment_

#ifndef _di_byte_dump_print_text_
  void byte_dump_print_text(const byte_dump_data_t data, const f_utf_string_static_t characters, const uint8_t invalid[], byte_dump_previous_t *previous, uint8_t *offset) {
    uint8_t j = 0;
    uint8_t output = 0;
    uint8_t width_utf = 0;
    bool printed = F_false;

    fl_color_print(data.output.stream, data.context.set.notable, "  %s ", byte_dump_character_wall);

    if (*offset > 0) {
      if (data.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
        while (*offset > 0 && j < data.width) {
          fprintf(data.output.stream, ".");
          (*offset)--;
          j++;
        } // while
      }
      else {
        const char *placeholder = " ";

        if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          placeholder = byte_dump_character_placeholder;
        }

        while (*offset > 0 && j < data.width) {
          fl_color_print(data.output.stream, data.context.set.warning, "%s", placeholder);
          (*offset)--;
          j++;
        } // while
      }
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
              fl_color_print(data.output.stream, data.context.set.error, "%s", byte_dump_character_placeholder);
            }
            else if (data.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
              fprintf(data.output.stream, ".");
            }
            else {
              fl_color_print(data.output.stream, data.context.set.warning, "%s", byte_dump_character_placeholder);
            }
          } // for
        }
        else {
          for (; j < previous->bytes && j < data.width; j++) {
            fprintf(data.output.stream, " ");
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

      output = f_macro_utf_character_t_to_char_1(characters.string[i]);
      width_utf = f_macro_utf_byte_width_is(output);

      if (invalid[i]) {
        fl_color_print(data.output.stream, data.context.set.error, "%s", byte_dump_character_incomplete);
      }
      else if (output >= 0 && output <= 32 || output == 127) {
        if (data.presentation == byte_dump_presentation_normal) {
          if (!output) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_null);
          }
          else if (output == 1) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_start_of_header);
          }
          else if (output == 2) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_start_of_text);
          }
          else if (output == 3) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_end_of_text);
          }
          else if (output == 4) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_end_of_transmission);
          }
          else if (output == 5) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_end_of_enquiry);
          }
          else if (output == 6) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_acknowledge);
          }
          else if (output == 7) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_bell);
          }
          else if (output == 8) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_backspace);
          }
          else if (output == 9) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_tab);
          }
          else if (output == 10) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_new_line);
          }
          else if (output == 11) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_tab_vertical);
          }
          else if (output == 12) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_form_feed);
          }
          else if (output == 13) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_carriage_return);
          }
          else if (output == 14) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_shift_out);
          }
          else if (output == 15) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_shift_in);
          }
          else if (output == 16) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_data_link_escape);
          }
          else if (output == 17) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_device_control_1);
          }
          else if (output == 18) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_device_control_2);
          }
          else if (output == 19) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_device_control_3);
          }
          else if (output == 20) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_device_control_4);
          }
          else if (output == 21) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_negative_acknowledge);
          }
          else if (output == 22) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_synchronous_idle);
          }
          else if (output == 23) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_end_of_transmission_block);
          }
          else if (output == 24) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_cancel);
          }
          else if (output == 25) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_end_of_medium);
          }
          else if (output == 26) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_substitute);
          }
          else if (output == 27) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_escape);
          }
          else if (output == 28) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_file_separator);
          }
          else if (output == 29) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_group_separator);
          }
          else if (output == 30) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_record_separator);
          }
          else if (output == 31) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_unit_separator);
          }
          else if (output == 32) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_space);
          }
          else if (output == 127) {
            fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_delete);
          }
        }
        else if (data.presentation == byte_dump_presentation_simple) {
          fprintf(data.output.stream, " ");
        }
        else if (data.presentation == byte_dump_presentation_classic) {
          fprintf(data.output.stream, ".");
        }
      }
      else if (f_utf_character_is_whitespace(characters.string[i]) == F_true) {
        if (data.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
          fprintf(data.output.stream, ".");
        }
        else {
          fl_color_print2(data.output.stream, data.context.set.notable, data.context.set.warning, "%s", byte_dump_sequence_space);
        }
      }
      else if (f_utf_character_is_zero_width(characters.string[i]) == F_true) {
        if (data.presentation == byte_dump_presentation_classic) {
          fprintf(data.output.stream, ".");
        }
        else if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          fl_color_print(data.output.stream, data.context.set.warning, "%s", byte_dump_character_placeholder);
        }
        else {
          fprintf(data.output.stream, " ");
        }
      }
      else if (f_utf_character_is_control(characters.string[i]) == F_true) {
        // print a space (or '.') for control characters.
        if (data.presentation == byte_dump_presentation_classic) {
          fl_color_print(data.output.stream, data.context.set.warning, ".");
        }
        else {
          fprintf(data.output.stream, " ");
        }
      }
      else if (width_utf == 2 && characters.string[i] == 0xd89d0000) {
        // U+061C
        fprintf(data.output.stream, " ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xefbfb000 && characters.string[i] <= 0xefbfbc00) {
        // Use space to represent Specials codes.
        // 0xefbfbd00 is excluded because it is printable (and is the "Replacement Character" code).
        fprintf(data.output.stream, " ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xe290a700 && characters.string[i] <= 0xe290bf00) {
        // Use space to represent Control Pictues codes that are not currently defined but are reserved.
        fprintf(data.output.stream, " ");
      }
      else if (width_utf == 3 && characters.string[i] >= 0xee808000 && characters.string[i] <= 0xefa3bf00) {
        // Use space to represent Private Use Area codes.
        fprintf(data.output.stream, " ");
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf09c80a0 && characters.string[i] <= 0xf09c80bd) {
        // Use space to represent Vaiation Selectors Supplement codes.
        fprintf(data.output.stream, " ");
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf3b08080 && characters.string[i] <= 0xf3bfbfbf) {
        // Use space to represent Supplemental Private Use Area-A codes.
        fprintf(data.output.stream, " ");
      }
      else if (width_utf == 4 && characters.string[i] >= 0xf4808080 && characters.string[i] <= 0xf48fbfbf) {
        // Use space to represent Supplemental Private Use Area-B codes.
        fprintf(data.output.stream, " ");
      }
      else if (width_utf == 1) {
        // print invalid placeholder for invalid UTF-8 widths.
        if (invalid[i]) {
          fl_color_print(data.output.stream, data.context.set.error, "%s", byte_dump_character_incomplete);
        }
        else {
          fl_color_print(data.output.stream, data.context.set.warning, "%s", byte_dump_character_incomplete);
        }
      }
      else if (width_utf > 0) {
        fprintf(data.output.stream, "%c", (uint8_t) output);

        if (width_utf > 1) {
          output = f_macro_utf_character_t_to_char_2(characters.string[i]);
          fprintf(data.output.stream, "%c", (uint8_t) output);

          if (width_utf > 2) {
            output = f_macro_utf_character_t_to_char_3(characters.string[i]);
            fprintf(data.output.stream, "%c", (uint8_t) output);

            if (width_utf > 3) {
              output = f_macro_utf_character_t_to_char_4(characters.string[i]);
              fprintf(data.output.stream, "%c", (uint8_t) output);
            }
          }
        }

        // @todo: implement a function in f_utf, such as f_utf_is_combining(), for detecting these combining characters.
        // print a space for combining characters to combine into, thereby allowing it to be safely and readably displayed.
        if (width_utf == 2 && characters.string[i] >= 0xdea60000 && characters.string[i] <= 0xdeb00000) {
          // Thana combining codes: U+07A6 to U+07B0.
          fprintf(data.output.stream, " ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xcc800000 && characters.string[i] <= 0xcdaf0000) {
          fprintf(data.output.stream, " ");
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe1aab000 && characters.string[i] <= 0xe1abbf00) {
          fprintf(data.output.stream, " ");
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe1b78000 && characters.string[i] <= 0xe1b7bf00) {
          fprintf(data.output.stream, " ");
        }
        else if (width_utf == 3 && characters.string[i] >= 0xe2839000 && characters.string[i] <= 0xe283bf00) {
          fprintf(data.output.stream, " ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd8900000 && characters.string[i] <= 0xd89a0000) {
          fprintf(data.output.stream, " ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd98b0000 && characters.string[i] <= 0xd99f0000) {
          // Arabic, U+064B to U+065F.
          fprintf(data.output.stream, " ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xdb960000 && characters.string[i] <= 0xdb9c0000) {
          // Arabic, U+06D6 to U+06DC.
          fprintf(data.output.stream, " ");
        }
        else if (width_utf == 2 && characters.string[i] >= 0xd6910000 && characters.string[i] <= 0xd6bd0000) {
          // Hebrew, U+0591 to U+05BD.
          fprintf(data.output.stream, " ");
        }
      }
      else {
        fprintf(data.output.stream, "%c", output);
      }

      // When using UTF-8 characters, the character columns will not line up, so print placeholders to simulate the bytes that are not printed, if necessary for alignment.
      if (width_utf > 1 && j + 1 < data.width) {
        if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
          if (invalid[i]) {
            fl_color_print(data.output.stream, data.context.set.error, "%s", byte_dump_character_placeholder);
          }
          else if (data.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
            fprintf(data.output.stream, ".");
          }
          else {
            fl_color_print(data.output.stream, data.context.set.warning, "%s", byte_dump_character_placeholder);
          }
        }
        else {
          fprintf(data.output.stream, " ");
        }

        j++;

        if (width_utf > 2 && j + 1 < data.width) {
          if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
            if (invalid[i]) {
              fl_color_print(data.output.stream, data.context.set.error, "%s", byte_dump_character_placeholder);
            }
            else if (data.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
              fprintf(data.output.stream, ".");
            }
            else {
              fl_color_print(data.output.stream, data.context.set.warning, "%s", byte_dump_character_placeholder);
            }
          }
          else {
            fprintf(data.output.stream, " ");
          }

          j++;

          if (width_utf > 3 && j + 1 < data.width) {
            if (data.parameters[byte_dump_parameter_placeholder].result == f_console_result_found) {
              if (invalid[i]) {
                fl_color_print(data.output.stream, data.context.set.error, "%s", byte_dump_character_placeholder);
              }
              else if (data.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
                fprintf(data.output.stream, ".");
              }
              else {
                fl_color_print(data.output.stream, data.context.set.warning, "%s", byte_dump_character_placeholder);
              }
            }
            else {
              fprintf(data.output.stream, " ");
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
          fl_color_print(data.output.stream, data.context.set.error, "%s", byte_dump_character_placeholder);
        }
        else if (data.parameters[byte_dump_parameter_classic].result == f_console_result_found) {
          fprintf(data.output.stream, ".");
        }
        else {
          fl_color_print(data.output.stream, data.context.set.warning, "%s", byte_dump_character_placeholder);
        }
      } // for
    }
    else {
      for (; j < data.width; j++) {
        fprintf(data.output.stream, " ");
      } // for
    }

    fl_color_print(data.output.stream, data.context.set.notable, " |");
    fprintf(data.output.stream, "%c", f_string_eol[0]);
  }
#endif // _di_byte_dump_file_

#ifdef __cplusplus
} // extern "C"
#endif
