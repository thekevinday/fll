/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_common_type_h
#define _iki_write_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The iki write main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status_signal: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing the FSS data.
 *
 * quote: This holds the quote used during processing.
 *
 * escaped: A buffer used for escaping strings during processing.
 * buffer:  A buffer used during processing the file.
 * object:  A buffer used to hold an Object during processing.
 * content: A buffer used to hold a Content during processing.
 *
 * objects:  An array of objects passed as values to the "--object" parameter.
 * contents: An array of objects passed as values to the "--content" parameter and must match the length of objects.
 */
#ifndef _di_iki_write_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status_signal;
    f_state_t state;

    f_string_static_t quote;

    f_string_dynamic_t escaped;
    f_string_dynamic_t buffer;
    f_string_dynamic_t object;
    f_string_dynamic_t content;

    f_string_dynamics_t objects;
    f_string_dynamics_t contents;
  } iki_write_setting_t;

  #define iki_write_setting_t_initialize \
    { \
      iki_write_main_flag_none_e, \
      F_okay, \
      f_state_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_iki_write_setting_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 */
#ifndef _di_iki_write_main_t_
  typedef struct {
    fll_program_data_t program;
    iki_write_setting_t setting;
  } iki_write_main_t;

  #define iki_write_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      iki_write_setting_t_initialize, \
    }
#endif // _di_iki_write_main_t_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_iki_write_main_delete_
  extern void iki_write_main_delete(iki_write_main_t * const main);
#endif // _di_iki_write_main_delete_

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
#ifndef _di_iki_write_setting_delete_
  extern f_status_t iki_write_setting_delete(iki_write_setting_t * const setting);
#endif // _di_iki_write_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_common_type_h
