#include "byte_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_process_file_
  void byte_dump_process_file(byte_dump_main_t * const main, const f_string_static_t name, const f_file_t file) {

    if (!main) return;

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
    f_utf_char_t block[main->setting.width];
    f_number_unsigned_t current = 0;

    // The row starts based on the first byte starting point and how many columns of bytes are displayed per row.
    if (main->setting.first) {
      cell.row = main->setting.first / main->setting.width;
      offset = main->setting.first % main->setting.width;

      // fseek() cannot be used on a PIPE, so read instead of seek.
      if (name.used) {
        byte_get = fseek(file.stream, main->setting.first, SEEK_SET);
      }
      else {
        f_char_t skip[main->setting.first];

        byte_get = fread(skip, 1, main->setting.first, file.stream);
      }
    }

    memset(&block, 0, sizeof(f_utf_char_t) * main->setting.width);
    sequence.string = block;
    sequence.used = 0;
    sequence.size = main->setting.width;

    // Record when a character is invalid.
    f_char_t invalid[main->setting.width];
    memset(&invalid, 0, sizeof(f_char_t) * main->setting.width);

    if (byte_get >= 0) {
      for (;;) {

        if (byte_dump_signal_check(main)) return;

        byte_get = getc(file.stream);

        if (byte_get < 0) {
          if (width_utf == -1 && character_reset) {
            sequence.used = 0;
            character_reset = F_false;
            memset(&invalid, 0, sizeof(f_char_t) * main->setting.width);
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
            memset(&invalid, 0, sizeof(f_char_t) * main->setting.width);
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

        f_file_stream_lock(main->program.output.to);

        if (byte_dump_print_character_fragment(&main->program.output, sequence, invalid, width_utf, 1, &previous, &cell, &offset) == F_true) {
          character_reset = F_true;
        }

        if (width_utf > 1) {
          if (byte_dump_print_character_fragment(&main->program.output, sequence, invalid, width_utf, 2, &previous, &cell, &offset) == F_true) {
            character_reset = F_true;
          }

          if (width_utf > 2) {
            if (byte_dump_print_character_fragment(&main->program.output, sequence, invalid, width_utf, 3, &previous, &cell, &offset) == F_true) {
              character_reset = F_true;
            }

            if (width_utf > 3) {
              if (byte_dump_print_character_fragment(&main->program.output, sequence, invalid, width_utf, 4, &previous, &cell, &offset) == F_true) {
                character_reset = F_true;
              }
            }
          }

          if (main->setting.last) {
            position += width_utf;

            if (position >= main->setting.last) {
              f_file_stream_unlock(main->program.output.to);

              break;
            }
          }
        }
        else if (main->setting.last) {
          ++position;

          if (position >= main->setting.last) {
            f_file_stream_unlock(main->program.output.to);

            break;
          }
        }

        f_file_stream_unlock(main->program.output.to);

        width_utf = -1;
      } // for
    }

    f_file_stream_lock(main->program.output.to);

    // Print placeholders to fill out the remaining line and then optionally print the text block.
    if (cell.column && cell.column < main->setting.width) {
      const uint8_t width_missing = width_utf <= 0 ? 0 : width_utf - width_count;

      if (width_missing) {
        const uint8_t column_offset = main->setting.width - cell.column;
        width_count = 0;

        // Handle incomplete character at the end of the stream.
        found_invalid_utf = F_true;
        invalid[current] = width_utf;

        if (byte_dump_print_character_fragment(&main->program.output, sequence, invalid, width_utf, 1, &previous, &cell, &offset) == F_true) {
          character_reset = F_true;
        }

        if (++width_count < width_missing) {
          if (byte_dump_print_character_fragment(&main->program.output, sequence, invalid, width_utf, 2, &previous, &cell, &offset) == F_true) {
            character_reset = F_true;
          }

          if (++width_count < width_missing) {
            if (byte_dump_print_character_fragment(&main->program.output, sequence, invalid, width_utf, 3, &previous, &cell, &offset) == F_true) {
              character_reset = F_true;
            }

            if (++width_count < width_missing) {
              if (byte_dump_print_character_fragment(&main->program.output, sequence, invalid, width_utf, 4, &previous, &cell, &offset) == F_true) {
                character_reset = F_true;
              }
            }
          }
        }

        if (character_reset) {
          sequence.used = 0;
          memset(&invalid, 0, sizeof(f_char_t) * main->setting.width);

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

    if (cell.column && cell.column < main->setting.width) {
      while (cell.column < main->setting.width) {

        f_print_dynamic_raw(byte_dump_padding_s[(main->setting.flag & byte_dump_main_flag_unicode_e) ? 0 : main->setting.mode], main->program.output.to);

        ++cell.column;

        if (cell.column < main->setting.width) {
          if (main->setting.flag & byte_dump_main_flag_unicode_e) {
            if (!(cell.column % 4)) {
              f_print_dynamic_raw(f_string_space_s, main->program.output.to);
            }
          }
          else if (main->setting.mode == byte_dump_mode_hexidecimal_e) {
            if (!(cell.column % 8)) {
              f_print_dynamic_raw(f_string_space_s, main->program.output.to);
            }
          }
          else if (main->setting.mode == byte_dump_mode_duodecimal_e || main->setting.mode == byte_dump_mode_octal_e || main->setting.mode == byte_dump_mode_binary_e || main->setting.mode == byte_dump_mode_decimal_e) {
            if (!(cell.column % 6)) {
              f_print_dynamic_raw(f_string_space_s, main->program.output.to);
            }
          }
        }
      } // while

      if (main->setting.flag & byte_dump_main_flag_text_e) {
        byte_dump_print_text(&main->program.output, sequence, invalid, &previous, &offset);
      }
      else {
        f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
      }
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    f_file_stream_unlock(main->program.output.to);
    f_file_stream_flush(main->program.output.to);

    if (found_invalid_utf) {
      f_file_stream_flush(main->program.error.to);

      fll_program_print_error_file_code_invalid(&main->program.error, name);
    }

    if (ferror(file.stream)) {
      f_file_stream_flush(main->program.error.to);

      fll_program_print_error_file_read(&main->program.error, name);
    }

    if (!F_status_is_error(main->setting.state.status)) {
      main->setting.state.status = F_none;
    }
  }
#endif // byte_dump_process_file

#ifdef __cplusplus
} // extern "C"
#endif
