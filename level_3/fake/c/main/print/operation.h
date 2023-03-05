/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides print operation functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_print_operation_h
#define _fake_print_operation_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print message for when all operates successfully complete.
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
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_operation_all_complete_
  extern f_status_t fake_print_operation_all_complete(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_print_operation_all_complete_

/**
 * Print message for when the operation is cancelled.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 * @param operation
 *   The identifier of the operation that failed.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_operation_cancelled_
  extern f_status_t fake_print_operation_cancelled(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation);
#endif // _di_fake_print_operation_cancelled_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_operation_h
