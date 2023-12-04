/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_process_h
#define _iki_read_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine the range based on the --line parameter.
 *
 * If the --line parameter is not specified in the console arguments, then range is untouched.
 * The range.start will be greater than main->buffer.used if the --line is not found before buffer end is reached.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.state.status:
 *     F_true is returned if the range is processed.
 *     F_false is returned if the range is not processed.
 *     F_data_not if the range is processed, but the requested line is out of range.
 * @param range
 *   The range value to represent the --line values.
 */
#ifndef _di_iki_read_process_line_
  extern void iki_read_process_line(iki_read_main_t * const main, f_range_t *range);
#endif // _di_iki_read_process_line_

/**
 * Process a given buffer.
 *
 * This will print error messages.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.state.status:
 *     F_okay on success.
 *     F_data_not on success, but nothing done.
 *
 *     F_interrupt (with error bit) on (exit) signal received.
 *
 *     Errors (with error bit) from: iki_read_process_at().
 *     Errors (with error bit) from: iki_read_process_buffer_ranges().
 *     Errors (with error bit) from: iki_read_process_buffer_ranges_whole().
 *
 * @see iki_read_process_at()
 * @see iki_read_process_buffer_ranges()
 * @see iki_read_process_buffer_ranges_whole()
 */
#ifndef _di_iki_read_process_buffer_
  extern void iki_read_process_buffer(iki_read_main_t * const main);
#endif // _di_iki_read_process_buffer_

/**
 * Process a given buffer, printing the given range.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 * @param buffer_range
 *   The range within the buffer to process.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but nothing to print.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_ranges_
  extern void iki_read_process_buffer_ranges(iki_read_main_t * const main, f_range_t *buffer_range);
#endif // _di_iki_read_process_buffer_ranges_

/**
 * Process a given buffer, printing the given buffer in whole mode based on the given ranges.
 *
 * The entire variable is replaced with the value from the associated ranges.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 * @param buffer_range
 *   The range within the buffer to process.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but nothing to print.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_ranges_whole_
  extern void iki_read_process_buffer_ranges_whole(iki_read_main_t * const main, const f_range_t buffer_range);
#endif // _di_iki_read_process_buffer_ranges_whole_

/**
 * Process a given buffer, printing the total.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 * @return
 *   F_okay on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_iki_read_process_buffer_total_
  extern void iki_read_process_buffer_total(iki_read_main_t * const main);
#endif // _di_iki_read_process_buffer_total_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_process_h
