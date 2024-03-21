/**
 * FLL - Level 3
 *
 * Project: Example
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides an example base project.
 *
 * This program does nothing but can be used as a starting point for new program projects.
 */
#ifndef _example_h
#define _example_h

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
//#include <fll/level_0/compare.h>
#include <fll/level_0/console.h>
//#include <fll/level_0/conversion.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
//#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>

#ifndef _di_thread_support_
  #include <fll/level_0/thread.h>
#endif // _di_thread_support_

// FLL-1 includes.
//#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Example includes.
#include <program/example/main/common/define.h>
#include <program/example/main/common/enumeration.h>
#include <program/example/main/common/print.h>
#include <program/example/main/common/string.h>
#include <program/example/main/common/type.h>
#include <program/example/main/common.h>
#include <program/example/main/print/data.h>
#include <program/example/main/print/debug.h>
#include <program/example/main/print/error.h>
#include <program/example/main/print/message.h>
#include <program/example/main/print/verbose.h>
#include <program/example/main/print/warning.h>
#include <program/example/main/signal.h>
#include <program/example/main/thread.h>

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
 *     F_okay on success.
 *     F_true on success when performing verification and verify passed.
 *     F_false on success when performing verification and verify failed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_example_main_
  extern void example_main(example_main_t * const main);
#endif // _di_example_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _example_h
