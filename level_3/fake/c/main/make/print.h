/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fake_make_print_h
#define _fake_make_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print error about a given fakefile missing a section.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param item
 *   The name of the missing section.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_error_fakefile_item_missing_
  extern f_status_t fake_make_print_error_fakefile_item_missing(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_static_t item);
#endif // _di_fake_make_print_error_fakefile_item_missing_

/**
 * Print error about a define setting containing an invalid character.
 *
 * These only allow valid characters in an environment variable name.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param name
 *   The name of the variable containing one or more invalid characters.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_error_define_invalid_character_
  extern f_status_t fake_make_print_error_define_invalid_character(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name);
#endif // _di_fake_make_print_error_define_invalid_character_

/**
 * Print warning about a setting name being already added.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param name
 *   The name of the environment variable that is already added.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_warning_environment_name_already_added_
  extern f_status_t fake_make_print_warning_environment_name_already_added(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name);
#endif // _di_fake_make_print_warning_environment_name_already_added_

/**
 * Print warning about a given environment name being invalid.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param name
 *   The name of the environment variable that is invalid.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_warning_environment_name_invalid_
  extern f_status_t fake_make_print_warning_environment_name_invalid(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t name);
#endif // _di_fake_make_print_warning_environment_name_invalid_

/**
 * Print warning about a given fakefile being empty.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param fakefile
 *   The name or path of the file that is empty.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_warning_fakefile_empty_
  extern f_status_t fake_make_print_warning_fakefile_empty(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile);
#endif // _di_fake_make_print_warning_fakefile_empty_

/**
 * Print message when fake settings content is empty.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param range
 *   The range within the buffer representing the object.
 * @param name
 *   The name of the setting that has an invalid value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_warning_settings_content_empty_
  extern f_status_t fake_make_print_warning_settings_content_empty(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_dynamic_t buffer, const f_string_range_t range, const f_string_static_t name);

#endif // _di_fake_make_print_warning_settings_content_empty_

/**
 * Print warning message when fake settings content is invalid.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param object
 *   The range within the buffer representing the object.
 * @param content
 *   The range within the buffer representing the content.
 * @param name
 *   The name of the setting that has an invalid value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_warning_settings_content_invalid_
  extern f_status_t fake_make_print_warning_settings_content_invalid(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_dynamic_t buffer, const f_string_range_t object, const f_string_range_t content, const f_string_static_t name);
#endif // _di_fake_make_print_warning_settings_content_invalid_

/**
 * Print warning message when settings content has too many values.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param name
 *   The name of the content.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_warning_settings_content_multiple_
  extern f_status_t fake_make_print_warning_settings_content_multiple(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_static_t name);
#endif // _di_fake_make_print_warning_settings_content_multiple_

/**
 * Print warning message when fakefile has too many objects with the same name.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param fakefile
 *   The name or path of the file that is empty.
 * @param buffer
 *   The buffer containing the loaded file content.
 * @param label
 *   A label describing what this object belongs to.
 * @param name
 *   The name of the object.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_warning_settings_object_multiple_
  extern f_status_t fake_make_print_warning_settings_object_multiple(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_static_t label, const f_string_static_t name);
#endif // _di_fake_make_print_warning_settings_object_multiple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_print_h
