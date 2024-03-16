/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_controller_print_h
#define _PRIVATE_controller_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the error, locking the print mutex during the print.
 *
 * @param thread
 *   (optional) The thread data.
 *   Set to NULL to disable locking on the thread (this should be done only if the lock is already in place).
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
 *
 * @see fll_error_print()
 */
#ifndef _di_controller_print_error_
  extern void controller_print_error(controller_thread_t * const thread, fl_print_t * const print, const f_status_t status, const f_string_t function, const uint8_t flag) F_attribute_visibility_internal_d;
#endif // _di_controller_print_error_

/**
 * Print the file error, locking the print mutex during the print.
 *
 * @param thread
 *   (optional) The thread data.
 *   Set to NULL to disable locking on the thread (this should be done only if the lock is already in place).
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
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_controller_print_error_file_
  extern void controller_print_error_file(controller_thread_t * const thread, fl_print_t * const print, const f_status_t status, const f_string_t function, const uint8_t flag, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) F_attribute_visibility_internal_d;
#endif // _di_controller_print_error_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_controller_print_h
