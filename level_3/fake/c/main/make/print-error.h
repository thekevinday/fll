/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fake_make_print_error_h
#define _fake_make_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

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
 * @param parameters
 *   The console parameters.
 * @param index
 *   An index within the console parameters arguments that represents the invalid argument.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_error_argument_invalid_section_
  extern f_status_t fake_make_print_error_argument_invalid_section(fake_setting_t * const setting, const fl_print_t print, const f_console_parameters_t parameters, const f_array_length_t index);
#endif // _di_fake_make_print_error_argument_invalid_section_

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
 * @param section
 *   The name of the missing section.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_error_fakefile_section_missing_
  extern f_status_t fake_make_print_error_fakefile_section_missing(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile, const f_string_static_t section);
#endif // _di_fake_make_print_error_fakefile_section_missing_

/**
 * Print error about an incomplete operation at the end of a section.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param operation
 *   The code of the operation.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_error_operation_incomplete_
  extern f_status_t fake_make_print_error_operation_incomplete(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation);
#endif // _di_fake_make_print_error_operation_incomplete_

/**
 * Print error about program failed.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param return_code
 *   The return code from the program.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_error_program_failed_
  extern f_status_t fake_make_print_error_program_failed(fake_setting_t * const setting, const fl_print_t print, const int return_code);
#endif // _di_fake_make_print_error_program_failed_

/**
 * Print error about program not being found.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param program
 *   The program name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_error_program_not_found_
  extern f_status_t fake_make_print_error_program_not_found(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t program);
#endif // _di_fake_make_print_error_program_not_found_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_print_error_h
