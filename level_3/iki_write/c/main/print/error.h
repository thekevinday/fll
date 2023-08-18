/**
 * FLL - Level 3
 *
 * Project: IKI Write
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
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_iki_write_print_error_
  extern f_status_t iki_write_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_iki_write_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
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
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_iki_write_print_error_file_
  extern f_status_t iki_write_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_iki_write_print_error_file_

/**
 * Print error message about "main" Object being missing.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_iki_write_print_error_main_missing_
  extern f_status_t iki_write_print_error_main_missing(fl_print_t * const print);
#endif // _di_iki_write_print_error_main_missing_

/**
 * Print error message about an Object not being valid.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param object
 *   The a string representing the object that is missing.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_iki_write_print_error_object_not_valid_
  extern f_status_t iki_write_print_error_object_not_valid(fl_print_t * const print, const f_string_static_t object);
#endif // _di_iki_write_print_error_object_not_valid_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_print_error_h
