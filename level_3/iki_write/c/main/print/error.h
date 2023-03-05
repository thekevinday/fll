/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_print_error_h
#define _iki_write_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_iki_write_print_error_
  extern f_status_t iki_write_print_error(iki_write_setting_t * const setting, const fl_print_t print, const f_string_t function);
#endif // _di_iki_write_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates how printing is to be performed.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_iki_write_print_error_file_
  extern f_status_t iki_write_print_error_file(iki_write_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_iki_write_print_error_file_

/**
 * Print error message about "main" Object being missing.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_iki_write_print_error_main_missing_
  extern f_status_t iki_write_print_error_main_missing(iki_write_setting_t * const setting, const fl_print_t print);
#endif // _di_iki_write_print_error_main_missing_

/**
 * Print error message about an Object not being valid.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param object
 *   The a string representing the object that is missing.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_iki_write_print_error_object_not_valid_
  extern f_status_t iki_write_print_error_object_not_valid(iki_write_setting_t * const setting, const fl_print_t print, const f_string_static_t object);
#endif // _di_iki_write_print_error_object_not_valid_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_print_error_h
