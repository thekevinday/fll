/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
