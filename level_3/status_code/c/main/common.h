/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_common_h
#define _status_code_common_h

#ifdef __cplusplus
extern "C" {
#endif

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

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_status_code_setting_load_
  extern void status_code_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, status_code_setting_t * const setting);
#endif // _di_status_code_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: utf8_setting_delete().
 *
 * @see utf8_setting_delete()
 */
#ifndef _di_status_code_setting_unload_
  extern f_status_t status_code_setting_unload(fll_program_data_t * const main, status_code_setting_t * const setting);
#endif // _di_status_code_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_common_h
