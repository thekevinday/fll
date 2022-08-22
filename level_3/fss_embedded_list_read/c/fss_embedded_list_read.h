/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the FSS Basic List Read program
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the fss_embedded_list_read_main_t.
 *
 * This processes in accordance to the FSS-0008 Embedded List specification.
 */
#ifndef _fss_embedded_list_read_h
#define _fss_embedded_list_read_h

// Libc includes.
#include <dirent.h>
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
#include <fll/level_0/directory.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/file.h>
#include <fll/level_2/fss/embedded_list.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Embedded List Read includes.
#include <program/fss_embedded_list_read/common.h>

#ifdef __cplusplus
extern "C" {
#endif

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
#ifndef _di_fss_embedded_list_read_print_help_
  extern f_status_t fss_embedded_list_read_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_fss_embedded_list_read_print_help_

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
#ifndef _di_fss_embedded_list_read_main_
  extern f_status_t fss_embedded_list_read_main(fll_program_data_t * const main, const f_console_arguments_t arguments);
#endif // _di_fss_embedded_list_read_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_embedded_list_read_h
