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

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 * @param signal
 *   The signal received.
 */
#ifndef _di_byte_dump_print_signal_received_
  extern void byte_dump_print_signal_received(byte_dump_main_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_byte_dump_print_signal_received_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_byte_dump_signal_received_
  extern f_status_t byte_dump_signal_received(byte_dump_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_byte_dump_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
