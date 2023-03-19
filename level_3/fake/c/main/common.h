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
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program and setting data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_path_directory_cleanup().
 *     Errors (with error bit) from: f_string_dynamic_resize().
 *     Errors (with error bit) from: f_utf_is_word_dash_plus().
 *     Errors (with error bit) from: f_uint8s_increase_by().
 *     Errors (with error bit) from: fll_program_parameter_additional_rip().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity().
 *
 * @see f_console_parameter_process()
 * @see f_path_directory_cleanup()
 * @see f_string_dynamic_resize()
 * @see f_utf_is_word_dash_plus()
 * @see f_uint8s_increase_by()
 * @see fll_program_parameter_additional_rip()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity()
 */
#ifndef _di_fake_setting_load_
  extern void fake_setting_load(const f_console_arguments_t arguments, fake_main_t * const main);
#endif // _di_fake_setting_load_

/**
 * Callback used by f_console_parameter_process() for custom handling of parameters.
 *
 * This prints error messages as appropriate.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param parameters
 *   The parameters array (generally from main.parameters) representing all of the parameters to look for.
 *   This must be of type f_console_parameters_t.
 * @param parameter_state
 *   The internal state data primarily managed by f_console_parameter_process().
 *   The state.status is used to represent the return status of this callback.
 *
 *   This alters parameter_state->state->status:
 *     F_none on success.
 *     F_process on success, designating that processing should be performed (see f_console_parameter_process()).
 *
 *     Errors (with error bit) from: f_uint8s_increase().
 * @param main
 *   This must be of the type fake_main_t.
 *
 * @see f_console_parameter_process()
 * @see f_uint8s_increase()
 */
#ifndef _di_fake_setting_load_parameter_callback_
  extern void fake_setting_load_parameter_callback(const f_console_arguments_t arguments, void * const parameters, f_console_parameter_state_t * const parameter_state, void * const main);
#endif // _di_fake_setting_load_parameter_callback_

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
#ifndef _di_fake_setting_unload_
  extern f_status_t fake_setting_unload(fake_main_t * const main);
#endif // _di_fake_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_h
