/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_common_h
#define _utf8_common_h

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
#ifndef _di_utf8_setting_delete_
  extern f_status_t utf8_setting_delete(utf8_setting_t * const setting);
#endif // _di_utf8_setting_delete_

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
 *   The main program data and settings.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_utf8_setting_load_
  extern void utf8_setting_load(const f_console_arguments_t arguments, utf8_main_t * const main);
#endif // _di_utf8_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program and setting data.
 *   All buffers are deallocated.
 *
 *   This does not alter main.setting.state.status.
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
#ifndef _di_utf8_setting_unload_
  extern f_status_t utf8_setting_unload(utf8_main_t * const main);
#endif // _di_utf8_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_h
