/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * private_utf8_codepoint_mode_*:
 *   - ready:     The codepoint has yet to be processed, skip leading spaces until first 'U' is matched.
 *   - begin:     The first 'U' is matched, look for the '+'.
 *   - number:    The '+' is matched, process numbers.
 *   - end:       The last number is reached (at either whitespace or EOS/EOF).
 *   - bad:       This is not a valid codepoint.
 *   - bad_begin: This is the beginning of an invalid codepoint.
 *   - bad_end:   The end of bad is detected, which happens on whitespace or end of buffer.
 */
#ifndef _di_utf8_codepoint_modes_
  enum {
    utf8_codepoint_mode_ready_e = 1,
    utf8_codepoint_mode_begin_e,
    utf8_codepoint_mode_number_e,
    utf8_codepoint_mode_end_e,
    utf8_codepoint_mode_bad_e,
    utf8_codepoint_mode_bad_begin_e,
    utf8_codepoint_mode_bad_end_e,
  };
#endif // _di__utf8_codepoint_modes_

/**
 * The program data.
 *
 * main:      The main program data.
 * argv:      The argument structure in fll_program_data_t.parameters for simplifying syntax.
 * file:      The output file for writing the processed data to (may potentially default to "output").
 * mode:      The input/output mode (see utf8_modes).
 * valid:     Designate the output context set for valid characters.
 * valid_not: Designate the output context set for invalid characters.
 * append:    A string to append. A value of NULL results in not appending.
 * prepend:   A string to prepend. A value of NULL results in not prepending.
 * buffer:    A buffer to use for printing output (generally for storing a block of input from an input file).
 * text:      A buffer for storing a series of characters for processing (generally for codepoint processing).
 */
#ifndef _di_utf8_data_t_
  typedef struct {
    fll_program_data_t *main;
    f_string_static_t *argv;

    f_file_t file;
    uint8_t mode;

    f_color_set_t valid;
    f_color_set_t valid_not;

    f_string_static_t append;
    f_string_static_t prepend;

    f_string_dynamic_t buffer;
    f_string_dynamic_t text;
  } utf8_data_t;

  #define utf8_data_t_initialize \
    { \
      0, \
      0, \
      f_file_t_initialize, \
      utf8_mode_from_binary_d | utf8_mode_to_codepoint_d, \
      f_color_set_t_initialize, \
      f_color_set_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_utf8_data_t_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_utf8_signal_received_
  extern f_status_t utf8_signal_received(utf8_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_utf8_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
