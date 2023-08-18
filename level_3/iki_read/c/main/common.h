/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_common_h
#define _iki_read_common_h

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
 *   The program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_file_exists().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_resize().
 *     Errors (with error bit) from: f_string_maps_resize().
 *     Errors (with error bit) from: f_string_triples_resize().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity_standard().
 *
 * @see f_console_parameter_process()
 * @see f_file_exists()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_resize()
 * @see f_string_maps_resize()
 * @see f_string_triples_resize()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity_standard()
 */
#ifndef _di_iki_read_setting_load_
  extern void iki_read_setting_load(const f_console_arguments_t arguments, iki_read_main_t * const main);
#endif // _di_iki_read_setting_load_

/**
 * Load the specific parameter that uses a substitution type, such as reassign or substitute.
 *
 * This prints error messages as appropriate.
 *
 * @param main
 *   The program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     Errors (with error bit) from: f_string_dynamic_resize().
 *     Errors (with error bit) from: f_string_triples_resize().
 * @param name
 *   The name of the parameter.
 *   This is used for printing error messages.
 * @param triple
 *   The setting, such as setting->substitute, to update.
 *
 * @return
 *   F_true if found and processed.
 *   F_false if not found or not processed.
 *
 * @see f_string_dynamic_resize()
 * @see f_string_triples_resize()
 */
#ifndef _di_iki_read_setting_load_parameter_substitution_
  extern f_status_t iki_read_setting_load_parameter_substitution(iki_read_main_t * const main, const f_console_parameter_t parameter, const f_string_static_t name, f_string_triples_t *triple);
#endif // _di_iki_read_setting_load_parameter_substitution_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_h
