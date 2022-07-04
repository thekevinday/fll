/**
 * FLL - Level 3
 *
 * Project: UTF-8
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * This is intendend to support Unicode 14.0.
 *
 * This is a program for handling basic UTF-8 related conversions.
 *   - Convert from UTF-8 character to bytesequence.
 *   - Convert from Unicode Codepoint (such as U+0000) to bytesequence.
 *   - Convert from UTF-8 bytesequence to character.
 *   - Convert from UTF-8 bytesequence to Unicode Codepoint (such as U+0000).
 */
#ifndef _utf8_h
#define _utf8_h

// Libc includes.
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// If limits.h does not provide PATH_MAX, define it instead of relying on <linux/limits.h>.
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif /* PATH_MAX */

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/path.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>
#include <fll/level_1/utf.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// UTF-8 includes.
#include <program/utf8/common.h>

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
#ifndef _di_utf8_print_help_
  extern f_status_t utf8_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_utf8_print_help_

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
 *   F_true on success when performing verification and verify passed.
 *   F_false on success when performing verification and verify failed.
 *   F_interrupt on (exit) signal received.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_utf8_main_
  extern f_status_t utf8_main(fll_program_data_t * const main, const f_console_arguments_t *arguments);
#endif // _di_utf8_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_h
