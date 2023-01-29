/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_write_common_h
#define _fss_write_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fss_write_setting_delete_
  extern f_status_t fss_write_setting_delete(fss_write_setting_t * const setting);
#endif // _di_fss_write_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
 *
 *     F_parameter (with error bit) on parameter error.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_file_stream_open().
 *     Errors (with error bit) from: f_string_dynamics_resize().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity().
 * @param callback
 *   (optional) Designate a function to call after performing the initial processing, but before printing help.
 *   If the function returns F_done, then this function immediately returns, resetting status to F_none.
 *   Set to NULL to disable.
 *
 * @see f_console_parameter_process()
 * @see f_file_stream_open()
 * @see f_string_dynamics_resize()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity()
 */
#ifndef _di_fss_write_setting_load_
  extern void fss_write_setting_load(const f_console_arguments_t arguments, f_state_t state, fll_program_data_t * const main, fss_write_setting_t * const setting, void (*callback)(const f_console_arguments_t arguments, f_state_t state, fll_program_data_t * const main, fss_write_setting_t * const setting));
#endif // _di_fss_write_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.status.
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
#ifndef _di_fss_write_setting_unload_
  extern f_status_t fss_write_setting_unload(fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_common_h
