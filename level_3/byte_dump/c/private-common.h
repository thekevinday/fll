/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program data.
 *
 * argv:         The argument structure in the progam data parameters for simplifying syntax.
 * first:        The first position.
 * last:         The last position.
 * main:         The main program data.
 * mode:         The digit representation mode.
 * options:      Additional options.
 * presentation: The presentation mode.
 * width:        The number of columns.
 */
#ifndef _di_byte_dump_data_t_
  typedef struct {
    fll_program_data_t *main;
    f_string_static_t *argv;

    uint64_t first;
    uint64_t last;
    uint8_t width;
    uint8_t mode;
    uint8_t presentation;
    uint8_t options;
  } byte_dump_data_t;

  #define byte_dump_data_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      8, \
      byte_dump_mode_hexidecimal_e, \
      byte_dump_presentation_normal_e, \
      byte_dump_option_wide_d, \
    }
#endif // _di_byte_dump_data_t_

/**
 * A main structure for character row and column position (cell).
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
 * A main structure for character main that overflowed from a previous line.
 *
 * UTF-8 Characters bytes may overflow beyond the main.width.
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
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_byte_dump_print_signal_received_
  extern void byte_dump_print_signal_received(byte_dump_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_byte_dump_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
