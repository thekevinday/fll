/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_common_type_h
#define _utf8_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The utf8 main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * Properties:
 *   - mode: The input/output mode (see utf8_modes_e).
 *   - flag: Flags passed to the main function.
 *
 *   - status_signal: A status used eclusively by the threaded signal handler.
 *   - state:         The state data used when processing the FSS data.
 *
 *   - valid:     Designate the output context set for valid characters.
 *   - valid_not: Designate the output context set for invalid characters.
 *
 *   - append:  A string to append. A value of NULL results in not appending.
 *   - prepend: A string to prepend. A value of NULL results in not prepending.
 *
 *   - buffer: A buffer to use for printing output (generally for storing a block of input from an input file).
 *   - text:   A buffer for storing a series of characters for processing (generally for code point processing).
 *
 *   - path_files_from: An array of all "from" file paths for when the flag utf8_main_flag_file_from_e is set.
 *   - path_files_to:   An array of all "to" file paths for when the flag utf8_main_flag_file_to_e is set.
 *   - remaining:       An array containing all remaining arguments passed to the program.
 */
#ifndef _di_utf8_setting_t_
  typedef struct {
    uint8_t mode;
    uint16_t flag;

    f_status_t status_signal;
    f_state_t state;

    f_color_set_t valid;
    f_color_set_t valid_not;

    f_string_static_t append;
    f_string_static_t prepend;

    f_string_dynamic_t buffer;
    f_string_dynamic_t text;

    f_string_dynamics_t path_files_from;
    f_string_dynamics_t path_files_to;
    f_string_dynamics_t remaining;
  } utf8_setting_t;

  #define utf8_setting_t_initialize \
    { \
      utf8_mode_from_bytesequence_e | utf8_mode_to_codepoint_e, \
      utf8_main_flag_none_e, \
      F_okay, \
      f_state_t_initialize, \
      f_color_set_t_initialize, \
      f_color_set_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_utf8_setting_t_

/**
 * The main program data as a single structure.
 *
 * Properties:
 *   - program: The main program data.
 *   - setting: The settings data.
 */
#ifndef _di_utf8_main_t_
  typedef struct {
    fll_program_data_t program;
    utf8_setting_t setting;
  } utf8_main_t;

  #define utf8_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      utf8_setting_t_initialize, \
    }
#endif // _di_utf8_main_t_

/**
 * Deallocate main program data.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 *
 * @see fll_program_data_delete()
 * @see utf8_setting_delete()
 */
#ifndef _di_utf8_main_delete_
  extern void utf8_main_delete(utf8_main_t * const main);
#endif // _di_utf8_main_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   Must not be NULL.
 *
 *   This does not alter setting.state.status.
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_utf8_setting_delete_
  extern void utf8_setting_delete(utf8_setting_t * const setting);
#endif // _di_utf8_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_type_h
