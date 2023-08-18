/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _byte_dump_common_type_h
#define _byte_dump_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A main structure for character row and column position (cell).
 *
 * Properties:
 *   - column: The column position associated with the character cell.
 *   - row:    The row position associated with the character cell.
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
 * Properties:
 *   - bytes:   The number of previous bytes that overflowed from the previous line.
 *              This is used to print the placeholders for the "text" option.
 *   - invalid: The specific invalid value provided representing the overflowed bytes.
 *              This is used to print the placeholders.
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
 * The byte_dump main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * Properties:
 *   - flag: Flags passed to the main function.
 *
 *   - status_signal: A status used eclusively by the threaded signal handler.
 *   - state:         The state data used when processing data.
 *
 *   - first:        The first position.
 *   - last:         The last position.
 *   - mode:         The digit representation mode.
 *   - options:      Additional options.
 *   - presentation: The presentation mode.
 *   - width:        The number of columns.
 *   - files:        An array containing all files to process.
 */
#ifndef _di_byte_dump_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status_signal;
    f_state_t state;

    uint64_t first;
    uint64_t last;
    uint8_t width;
    uint8_t mode;
    uint8_t presentation;

    f_string_dynamics_t files;
  } byte_dump_setting_t;

  #define byte_dump_setting_t_initialize \
    { \
      byte_dump_main_flag_none_e, \
      F_okay, \
      f_state_t_initialize, \
      0, \
      0, \
      8, \
      byte_dump_mode_hexidecimal_e, \
      byte_dump_presentation_normal_e, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_byte_dump_setting_t_

/**
 * The main program data as a single structure.
 *
 * Properties:
 *   - program: The main program data.
 *   - setting: The settings data.
 */
#ifndef _di_byte_dump_main_t_
  typedef struct {
    fll_program_data_t program;
    byte_dump_setting_t setting;
  } byte_dump_main_t;

  #define byte_dump_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      byte_dump_setting_t_initialize, \
    }
#endif // _di_byte_dump_main_t_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_byte_dump_main_delete_
  extern void byte_dump_main_delete(byte_dump_main_t * const main);
#endif // _di_byte_dump_main_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_byte_dump_setting_delete_
  extern f_status_t byte_dump_setting_delete(byte_dump_setting_t * const setting);
#endif // _di_byte_dump_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_common_type_h
