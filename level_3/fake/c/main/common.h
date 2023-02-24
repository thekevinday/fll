/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides common functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_h
#define _fake_common_h

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
#ifndef _di_fake_setting_delete_
  extern f_status_t fake_setting_delete(fake_setting_t * const setting);
#endif // _di_fake_setting_delete_

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
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_fake_setting_load_
  extern void fake_setting_load(const f_console_arguments_t arguments, f_state_t state, fll_program_data_t * const main, fake_setting_t * const setting);
#endif // _di_fake_setting_load_

/**
 * Callback used by f_console_parameter_process() for custom handling of parameters.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param parameters
 *   The parameters array (generally from main.parameters) representing all of the parameters to look for.
 *   This must be of type f_console_parameters_t.
 * @param state
 *   The internal state data primarily managed by f_console_parameter_process().
 *   The state.status is used to represent the return status of this callback.
 * @param data
 *   This must be of the type fake_setting_t.
 *
 * @see f_console_parameter_process()
 */
#ifndef _di_fake_setting_load_parameter_callback_
  extern void fake_setting_load_parameter_callback(const f_console_arguments_t arguments, void * const parameters, f_console_parameter_state_t * const state, void * const data);
#endif // _di_fake_setting_load_parameter_callback_

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
#ifndef _di_fake_setting_unload_
  extern f_status_t fake_setting_unload(fll_program_data_t * const main, fake_setting_t * const setting);
#endif // _di_fake_setting_unload_

/**
 * Deallocate data.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_main()
 */
#ifndef _di_fake_data_delete_
  extern f_status_t fake_data_delete(fake_data_t * const data);
#endif // _di_fake_data_delete_

/**
 * Deallocate make data.
 *
 * @param data
 *   The make data.
 *
 * @return
 *   F_none on success.
 *
 * @see f_fss_nameds_resize()
 * @see f_string_dynamic_resize()
 * @see f_string_maps_resize()
 */
#ifndef _di_fake_make_data_delete_
  extern f_status_t fake_make_data_delete(fake_make_data_t * const data);
#endif // _di_fake_make_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_h
