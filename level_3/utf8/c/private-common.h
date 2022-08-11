/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Codepoint modes for converting to/from binary and codepoint values.
 *
 * The special "raw" format is used only for reading from codepoint format where that format represents binary character that is not a valid Unicode character.
 * This is intended to be used to save and restore the original binary data even if that data is invalid.
 *
 * private_utf8_codepoint_mode_*:
 *   - ready:      The codepoint has yet to be processed, skip leading spaces until first 'U' is matched.
 *   - begin:      The first 'U' is matched, look for the '+'.
 *   - number:     The '+' is matched, process numbers.
 *   - end:        The last number is reached (at either white space or EOS/EOF).
 *   - bad:        This is not a valid codepoint.
 *   - bad_begin:  This is the beginning of an invalid codepoint.
 *   - bad_end:    The end of bad is detected, which happens on white space or end of buffer.
 *   - raw_begin:  This is the beginning of a potential raw data (matched '0').
 *   - raw_number: This is the confirmed beginning of raw data (matched 'X'), process numbers.
 *   - raw_end:    The end of raw data is detected, which happens on white space or end of buffer.
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
    utf8_codepoint_mode_raw_begin_e,
    utf8_codepoint_mode_raw_number_e,
    utf8_codepoint_mode_raw_end_e,
  };
#endif // _di__utf8_codepoint_modes_

/**
 * The program data.
 *
 * main:    The main program data.
 * setting: The main program settings.
 * argv:    The argument structure in the progam data parameters for simplifying syntax.
 *
 * main:      The main program data.
 * file:      The output file for writing the processed data to (may potentially default to "output").
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
    utf8_main_setting_t *setting;
    f_string_static_t *argv;

    //f_file_t file;

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
      0, \
      //f_file_t_initialize, \
      f_color_set_t_initialize, \
      f_color_set_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_utf8_data_t_

/**
 * Deallocate program data.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_utf8_data_delete_
  extern void utf8_data_delete(utf8_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_utf8_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
