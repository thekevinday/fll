/**
 * FLL - Level 3
 *
 * Project: Example
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _example_print_message_h
#define _example_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be example_main_t.
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
 * @see f_print_dynamic_raw()
 * @see fll_program_print_help_header()
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_usage()
 */
#ifndef _di_example_print_message_help_
  extern f_status_t example_print_message_help(fl_print_t * const print);
#endif // _di_example_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _example_print_message_h
