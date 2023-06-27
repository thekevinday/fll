/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_common_type_h
#define _status_code_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The status code main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status_thread: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing the FSS data.
 *
 * status_string_from:        A pointer to the status string function (usually either fl_status_string_from() or fll_fss_status_string_from()).
 * status_string_to:          A pointer to the status string function (usually either f_status_string_to() or fll_fss_status_string_to()).
 * status_string_help_detail: Print additional, more detailed help, in the help page.
 */
#ifndef _di_status_code_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status_thread;
    f_state_t state;

    const f_string_static_t *program_name;
    const f_string_static_t *program_name_long;

    f_status_t (*status_string_from)(const f_string_static_t name, f_status_t * const code);
    f_status_t (*status_string_to)(const f_status_t code, f_string_static_t * const name);
    f_status_t (*status_string_help_detail)(fl_print_t * const print);
  } status_code_setting_t;

  #define status_code_setting_t_initialize \
    { \
      status_code_main_flag_none_e, \
      F_none, \
      f_state_t_initialize, \
      0, \
      0, \
      0, \
      0, \
      0, \
    }
#endif // _di_status_code_setting_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 */
#ifndef _di_status_code_main_t_
  typedef struct {
    fll_program_data_t program;
    status_code_setting_t setting;
  } status_code_main_t;

  #define status_code_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      status_code_setting_t_initialize, \
    }
#endif // _di_status_code_main_t_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter data_make.main.setting.state.status.
 */
#ifndef _di_status_code_main_delete_
  extern void status_code_main_delete(status_code_main_t * const main);
#endif // _di_status_code_main_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_status_code_setting_delete_
  extern f_status_t status_code_setting_delete(status_code_setting_t * const setting);
#endif // _di_status_code_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_common_type_h
