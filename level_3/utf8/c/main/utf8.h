/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is intended to support Unicode 15.0.
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
#include <fll/level_0/compare.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/path.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>

#ifndef _di_thread_support_
  #include <fll/level_0/thread.h>
#endif // _di_thread_support_

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// UTF-8 includes.
#include <program/utf8/main/common/define.h>
#include <program/utf8/main/common/enumeration.h>
#include <program/utf8/main/common/print.h>
#include <program/utf8/main/common/string.h>
#include <program/utf8/main/common/type.h>
#include <program/utf8/main/common.h>
#include <program/utf8/main/bytesequence.h>
#include <program/utf8/main/codepoint.h>
#include <program/utf8/main/print/data.h>
#include <program/utf8/main/print/error.h>
#include <program/utf8/main/print/message.h>
#include <program/utf8/main/process.h>
#include <program/utf8/main/signal.h>
#include <program/utf8/main/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 *   The main program data and settings.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *     F_true on success when performing verification and verify passed.
 *     F_false on success when performing verification and verify failed.
 *
 *     F_interrupt (with error bit) on (exit) signal received.
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_utf8_main_
  extern void utf8_main(utf8_main_t * const main);
#endif // _di_utf8_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_h
