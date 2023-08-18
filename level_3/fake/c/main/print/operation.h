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
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
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
  extern f_status_t fake_print_operation_all_complete(fl_print_t * const print);
#endif // _di_fake_print_operation_all_complete_

/**
 * Print message for when the operation is cancelled.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param operation
 *   The identifier of the operation that failed.
 *
 * @return
 *   F_okay on success.
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
  extern f_status_t fake_print_operation_cancelled(fl_print_t * const print, const uint8_t operation);
#endif // _di_fake_print_operation_cancelled_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_operation_h
