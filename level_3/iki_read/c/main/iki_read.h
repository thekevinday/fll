/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the IKI Read program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format and stores the results in the iki_read_main_t.
 *
 * This processes in accordance to the IKI specification.
 */
#ifndef _iki_read_h
#define _iki_read_h

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
#include <fll/level_0/compare.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/iki.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>

#ifndef _di_thread_support_
  #include <fll/level_0/thread.h>
#endif // _di_thread_support_

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/iki.h>
#include <fll/level_1/print.h>
#include <fll/level_1/signal.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/file.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// IKI Read includes.
#include <program/iki_read/main/common/define.h>
#include <program/iki_read/main/common/enumeration.h>
#include <program/iki_read/main/common/print.h>
#include <program/iki_read/main/common/string.h>
#include <program/iki_read/main/common/type.h>
#include <program/iki_read/main/common.h>
#include <program/iki_read/main/identify.h>
#include <program/iki_read/main/print/data.h>
#include <program/iki_read/main/print/error.h>
#include <program/iki_read/main/print/message.h>
#include <program/iki_read/main/process.h>
#include <program/iki_read/main/signal.h>
#include <program/iki_read/main/thread.h>

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
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.state.status:
 *     F_none on success.
 *     F_true on success when performing verification and verify passed.
 *     F_false on success when performing verification and verify failed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *     F_failure (with error bit) for any other failure.
 */
#ifndef _di_iki_read_main_
  extern void iki_read_main(iki_read_main_t * const main);
#endif // _di_iki_read_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_h
