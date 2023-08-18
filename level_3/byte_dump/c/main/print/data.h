/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print data functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _byte_dump_print_data_h
#define _byte_dump_print_data_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print a single character hex code and if the width is reached properly terminate the line.
 *
 * @param print
 *   Designates the how and where to print.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param sequence
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
 *   The overflow main from the previous line.
 * @param cell
 *   The main fragment main such that:
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
  extern f_status_t byte_dump_print_character_fragment(fl_print_t * const print, const f_utf_string_static_t sequence, const f_char_t invalid[], const uint8_t width_utf, const f_char_t byte_current, byte_dump_previous_t *previous, byte_dump_cell_t *cell, f_char_t *offset);
#endif // _di_byte_dump_print_character_fragment_

/**
 * Print the text representation alongside the hex display.
 *
 * This should be called only when text mode is enabled.
 *
 * @param print
 *   Designates the how and where to print.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The name of the file the header is associated with.
 *   If name.used is 0 then this is assumed to be the input pipe.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_byte_dump_print_file_header_
  extern f_status_t byte_dump_print_file_header(fl_print_t * const print, const f_string_static_t name);
#endif // _di_byte_dump_print_file_header_

/**
 * Print the text representation alongside the hex display.
 *
 * This should be called only when text mode is enabled.
 *
 * @param print
 *   Designates the how and where to print.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param sequence
 *   An array of UTF-8 and ASCII characters.
 * @param invalid
 *   An array designating if a given character at the array index is invalid or not.
 *   The values represent the number of bytes in which the invalid character is expected to take up.
 * @param previous
 *   The overflow main from the previous line.
 * @param offset
 *   The offset to apply before printing column cells for the row.
 *   Will be reduced to 0 once used.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_byte_dump_print_text_
  extern f_status_t byte_dump_print_text(fl_print_t * const print, const f_utf_string_static_t sequence, const f_char_t invalid[], byte_dump_previous_t *previous, f_char_t *offset);
#endif // _di_byte_dump_print_text_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_print_data_h
