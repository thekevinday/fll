/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build warning print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_print_warning_h
#define _fake_build_print_warning_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print error message regarding two parameters contradicting and designating a default fallback parameter.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param symbol_1
 *   The symbol for the first parameter.
 * @param name_1
 *   The name for the first parameter.
 * @param symbol_2
 *   The symbol for the second parameter.
 * @param name_2
 *   The name for the second parameter.
 * @param symbol_3
 *   The symbol for the third parameter (the fallback).
 * @param name_3
 *   The name for the third parameter (the fallback).
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_parameters()
 */
#ifndef _di_fake_build_print_warning_parameters_contradict_
  extern f_status_t fake_build_print_warning_parameters_contradict(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol_1, const f_string_static_t name_1, const f_string_static_t symbol_2, const f_string_static_t name_2, const f_string_static_t symbol_3, const f_string_static_t name_3);
#endif // _di_fake_build_print_warning_parameters_contradict_

/**
 * Print warning message that the setting may only be from a specific set of allowed boolean values.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name for the setting.
 * @param path
 *   The path to the setting file.
 * @param default_to
 *   The value being defaulted to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_build_print_warning_setting_boolean_may_only_be_
  extern f_status_t fake_build_print_warning_setting_boolean_may_only_be(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_string_static_t path, const f_string_static_t default_to);
#endif // _di_fake_build_print_warning_setting_boolean_may_only_be_

/**
 * Print warning message regarding two parameters being both false when using a given language.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name_1
 *   The name for the first setting.
 * @param name_2
 *   The name for the second setting.
 * @param language
 *   The name for the language.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_wrapped_parameters()
 */
#ifndef _di_fake_build_print_error_settings_both_cannot_using_language_
  extern f_status_t fake_build_print_warning_setting_both_cannot_when_language(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name_1, const f_string_static_t name_2, const f_string_static_t name_3);
#endif // _di_fake_build_print_error_settings_both_cannot_using_language_

/**
 * Print warning message that the setting may only be from a specific set of allowed language values.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name for the setting.
 * @param path
 *   The path to the setting file.
 * @param default_to
 *   The value being defaulted to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_build_print_warning_setting_language_may_only_be_
  extern f_status_t fake_build_print_warning_setting_language_may_only_be(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_string_static_t path, const f_string_static_t default_to);
#endif // _di_fake_build_print_warning_setting_language_may_only_be_

/**
 * Print warning message regarding two parameters being both false when using a given language.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name_1
 *   The name for the first setting.
 * @param name_2
 *   The name for the second setting.
 * @param language
 *   The name for the language.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fake_print_context_wrapped_parameters()
 */
#ifndef _di_fake_build_print_warning_setting_required_default_to_
  f_status_t fake_build_print_warning_setting_required_default_to(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_string_static_t path, const f_string_static_t default_to);
#endif // _di_fake_build_print_warning_setting_required_default_to_

/**
 * Print warning message that the setting may only be from a specific set of allowed version values.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param name
 *   The name for the setting.
 * @param path
 *   The path to the setting file.
 * @param default_to
 *   The value being defaulted to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_build_print_warning_setting_version_may_only_be_
  extern f_status_t fake_build_print_warning_setting_version_may_only_be(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name, const f_string_static_t path, const f_string_static_t default_to);
#endif // _di_fake_build_print_warning_setting_version_may_only_be_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_print_warning_h
