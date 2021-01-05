/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_byte_dump_h
#define _PRIVATE_byte_dump_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A data structure for character row and column position (cell).
 *
 * column: The column position associated with the character cell.
 * row:    The row position associated with the character cell.
 */
#ifndef _di_byte_dump_cell_t_
  typedef struct {
    uint8_t  column;
    uint64_t row;
  } byte_dump_cell_t;

  #define byte_dump_cell_t_initialize \
    { \
      0, \
      0, \
    }
#endif // _di_byte_dump_cell_t_

/**
 * A data structure for character data that overflowed from a previous line.
 *
 * UTF-8 Characters bytes may overflow beyond the data.width.
 * These overflowed bytes should still have placeholders printed in the next text-mode print.
 *
 * bytes: The number of previous bytes that overflowed from the previous line.
 *        This is used to print the placeholders for the "text" option.
 * invalid: The specific invalid value provided representing the overflowed bytes.
 *          This is used to print the placeholders.
 */
#ifndef _di_byte_dump_previous_t_
  typedef struct {
    uint8_t bytes;
    uint8_t invalid;
  } byte_dump_previous_t;

  #define byte_dump_previous_t_initialize \
    { \
      0, \
      0, \
    }
#endif // _di_byte_previous_cell_

/**
 * Dump the contents of the file to standard out.
 *
 * @param data
 *   The program data.
 * @param file_name
 *   The name of the file.
 * @param file
 *   Data for the file to print.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) on failure, usually when read() fails.
 */
#ifndef _di_byte_dump_file_
  extern f_status_t byte_dump_file(const byte_dump_data_t data, const f_string_t file_name, const f_file_t file) f_gcc_attribute_visibility_internal;
#endif // _di_byte_dump_file_

/**
 * Print a single character hex code and if the width is reached properly terminate the line.
 *
 * @param data
 *   The program data.
 * @param characters
 *   An array of UTF-8 and ASCII characters.
 * @param invalid
 *   An array designating if a given character at the array index is invalid or not.
 *   The values represent the number of bytes in which the invalid character is expected to take up.
 * @param width_utf
 *   The number of bytes that the character completely represents.
 *   A value of 0 represents ASCII.
 * @param byte_current
 *   The UTF-8 character byte block to print, going from left to right first byte is 1, second byte is 2, etc...
 *   A value of 1 is used for ASCII.
 * @param previous
 *   The overflow data from the previous line.
 * @param cell
 *   The data fragment data such that:
 *   - column:
 *     The current column that the character is being printed on.
 *     This value is incremented to represent that the character is printed.
 *     When the max width is reached byte_dump_print_text() is called and this value is reset.
 *   - row:
 *     The current row that the character is being printed on.
 *     When the max width is reached byte_dump_print_text() is called and this value is incremented.
 * @param offset
 *   The offset in which the columns must have applied.
 *   Will be reduced to 0 once used.
 *
 * @return
 *   F_true is returned to designate that a reset is needed.
 *   F_false is returned to designate that a reset is not needed.
 *
 * @see byte_dump_print_text()
 */
#ifndef _di_byte_dump_print_character_fragment_
  extern bool byte_dump_print_character_fragment(const byte_dump_data_t data, const f_utf_string_static_t characters, const uint8_t invalid[], const int8_t width_utf, const int8_t byte_current, byte_dump_previous_t *previous, byte_dump_cell_t *cell, uint8_t *offset) f_gcc_attribute_visibility_internal;
#endif // _di_byte_dump_print_character_fragment_

/**
 * Print the text representation alongside the hex display.
 *
 * This should be called only when text mode is enabled.
 *
 * @param data
 *   The program data.
 * @param characters
 *   An array of UTF-8 and ASCII characters.
 * @param invalid
 *   An array designating if a given character at the array index is invalid or not.
 *   The values represent the number of bytes in which the invalid character is expected to take up.
 * @param previous
 *   The overflow data from the previous line.
 * @param offset
 *   The offset to apply before printing column cells for the row.
 *   Will be reduced to 0 once used.
 */
#ifndef _di_byte_dump_print_text_
  extern void byte_dump_print_text(const byte_dump_data_t data, const f_utf_string_static_t characters, const uint8_t invalid[], byte_dump_previous_t *previous, uint8_t *offset) f_gcc_attribute_visibility_internal;
#endif // _di_byte_dump_print_text_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_byte_dump_h
