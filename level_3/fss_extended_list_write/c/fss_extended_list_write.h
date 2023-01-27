/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides FSS-0003 Extended List write functionality.
 */
#ifndef _fss_extended_list_write_h
#define _fss_extended_list_write_h

// Libc includes.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/fss/extended_list.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Extended List Write includes.
#include <program/fss_extended_list_write/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print copyright.
 *
 * @param file
 *   The file to print to.
 * @param detail
 *   If TRUE, then the detailed copyright is printed (unless _di_detailed_copyright_ is set).
 *   If FALSE, then the short copyright is printed.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_extended_list_write_print_copyright_
  extern f_status_t fss_extended_list_write_print_copyright(const f_file_t file, const bool detail);
#endif // _di_fss_extended_list_write_print_copyright_

/**
 * Print help.
 *
 * @param file
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fss_extended_list_write_print_help_
  extern f_status_t fss_extended_list_write_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_fss_extended_list_write_print_help_

/**
 * Execute main program.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fss_extended_list_write_main_
  extern f_status_t fss_extended_list_write_main(fll_program_data_t * const main, const f_console_arguments_t *arguments);
#endif // _di_fss_extended_list_write_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_list_write_h
