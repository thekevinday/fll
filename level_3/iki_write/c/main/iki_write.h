/**
 * FLL - Level 3
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the IKI Write program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program processes files or other input in fss format.
 *
 * This processes in accordance to the IKI specification.
 */
#ifndef _iki_write_h
#define _iki_write_h

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
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/iki.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/iki.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/file.h>
#include <fll/level_2/iki.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// IKI Write includes.
#include <program/iki_write/main/common/define.h>
#include <program/iki_write/main/common/enumeration.h>
#include <program/iki_write/main/common/print.h>
#include <program/iki_write/main/common/string.h>
#include <program/iki_write/main/common/type.h>
#include <program/iki_write/main/common.h>
#include <program/iki_write/main/print/error.h>
#include <program/iki_write/main/print/message.h>
#include <program/iki_write/main/process.h>

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
 *   The program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *     F_true on success when performing verification and verify passed.
 *     F_false on success when performing verification and verify failed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_failure (with error bit) on processing failure.
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *
 *     Errors (with error bit) from: f_iki_object_is().
 *     Errors (with error bit) from: fll_iki_content_escape().
 *
 * @see f_iki_object_is()
 * @see fll_iki_content_escape()
 */
#ifndef _di_iki_write_main_
  extern void iki_write_main(iki_write_main_t * const main);
#endif // _di_iki_write_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_h
