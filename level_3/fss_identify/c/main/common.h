/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_common_h
#define _fss_identify_common_h

#ifdef __cplusplus
extern "C" {
#endif

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
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_fss_identify_setting_load_
  extern void fss_identify_setting_load(const f_console_arguments_t arguments, fss_identify_main_t * const main);
#endif // _di_fss_identify_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_common_h