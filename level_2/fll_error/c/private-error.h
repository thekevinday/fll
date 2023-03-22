/**
 * FLL - Level 2
 *
 * Project: Error
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FLL_error_h
#define _PRIVATE_FLL_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fll_error_print().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param status
 *   The status code to process.
 *   Make sure this has F_status_set_fine() called if the status code has any error or warning bits.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param flag
 *   One of the fll_error_file_flag_*_e flags.
 *   Consider passing fll_error_file_flag_simple_e, on errors like file not find while trying to find file.
 *
 * @return
 *   F_false is returned on successful print of known errors.
 *   F_true is returned if the status code is unknown.
 *
 * @see fll_error_print()
 * @see fll_error_file_print()
 */
#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)
  extern f_status_t private_fll_error_print(fl_print_t * const print, const f_status_t status, const f_string_t function, const uint8_t flag) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)

/**
 * Special function for printing the "function name".
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 *
 * @return
 *   F_false is returned on successful print of known errors.
 *   F_true is returned if the status code is unknown.
 *
 * @see fll_error_print()
 * @see fll_error_file_print()
 */
#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)
  extern void private_fll_error_print_function(fl_print_t * const print, const f_string_t function) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)

/**
 * Special function for printing the "Unable to" message.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param print
 *   Designates how printing is to be performed.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type_name
 *   A string representing the type.
 * @param message
 *   An additional message to add.
 *   Set to an 0 to not use.
 *
 * @return
 *   F_false is returned on successful print of known errors.
 *   F_true is returned if the status code is unknown.
 *
 * @see fll_error_print()
 * @see fll_error_file_print()
 */
#if !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)
  extern void private_fll_error_print_unable_to(fl_print_t * const print, const f_string_static_t operation, const f_string_static_t name, const f_string_static_t type_name, const f_string_t message) F_attribute_visibility_internal_d;
#endif // !defined(_di_fll_error_print_) || !defined(_di_fll_error_file_print_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_error_h
